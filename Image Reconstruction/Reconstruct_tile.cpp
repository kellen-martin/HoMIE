#include "header.hpp"

using namespace std;
using namespace cv;


Mat Reconstruct_tile(Mat& input_image, Mat& ref_wave, Mat& template_wave, Mat& apodizer)
{
    int tile_pixels = n_pixels/num_tiles;

    Mat image = input_image(Range(0, Sn_pixels/num_tiles), Range(0, Sn_pixels/num_tiles)).clone();
    resize(image, image, Size(0,0), OVS, OVS, INTER_CUBIC); 
    if(verbose) cout << "Resize image: " << image.rows << " x " << image.cols << " x " << image.channels() << endl;
    if(verbose)
    {
        double max, min;
        Point minLoc, maxLoc;
        minMaxLoc(image, &min, &max);
        cout << "    max pixel value: " << max << endl;
        cout << "    min pixel value: " << min << endl << endl;
    }
    // resize done using bicubic interpolation (this is what MATLAB does by default)

    float down_sz = (n_pixels/OVS)/num_tiles;
    Mat* I2_down = new Mat;
    *I2_down = Mat::zeros(tile_pixels, tile_pixels, CV_32F);

    for(int i = 0; i < ref_wave.rows; i++){
        for(int j = 0; j < ref_wave.cols; j++){

            (*I2_down).at<float>(i,j) = (float)((real(ref_wave.at<complex<float>>(i,j))*real(ref_wave.at<complex<float>>(i,j))) + (imag(ref_wave.at<complex<float>>(i,j))*imag(ref_wave.at<complex<float>>(i,j))));

        }
    }
    (*I2_down) = image - (*I2_down);

    if(verbose) cout << "Calculated abs difference between ref and image" << endl;

    resize((*I2_down), (*I2_down), Size(down_sz/num_tiles, down_sz/num_tiles), 0, 0, INTER_NEAREST);

    // saveRealMat(*I2_down, "../Output-Images/Mat.txt", 3000, 3000); 


    // image downsized using same interpolation as MATLAB 'box' option
    if(verbose) cout << "Resized: " << (*I2_down).rows << " x " << (*I2_down).cols << " x " << (*I2_down).channels() << endl;
    if(verbose)
    {
        double max, min;
        Point minLoc, maxLoc;
        minMaxLoc((*I2_down), &min, &max);
        cout << "    max pixel value: " << max << endl;
        cout << "    min pixel value: " << min << endl << endl;
    }

    Mat* I2_down_fft = new Mat;
    dft((*I2_down), (*I2_down_fft), DFT_COMPLEX_OUTPUT);
    
    delete I2_down;
    
    if(verbose) cout << "Calculated dft of I2_down (I2_down_fft):" << endl;
    if(verbose) cout << "    "  << (*I2_down_fft).rows << " x " << (*I2_down_fft).cols << " x " << (*I2_down_fft).channels() << endl;
    
    // saveComplexMat(*I2_down_fft, "../Output-Images/Mat.txt", 3000, 3000); 

    Mat* I2_up_fft = new Mat;
    (*I2_up_fft) = Mat::zeros(tile_pixels, tile_pixels, CV_32FC2);

    int n1 = (down_sz/num_tiles)/2;
    int n2 = (tile_pixels - 1) - n1;

    Rect up_r1( 0,  0, n1, n1);
    Rect dn_r1( 0,  0, n1, n1);
    Rect up_r2(n2,  0, n1, n1);
    Rect dn_r2(n1,  0, n1, n1);
    Rect up_r3( 0, n2, n1, n1);
    Rect dn_r3( 0, n1, n1, n1);
    Rect up_r4(n2, n2, n1, n1);
    Rect dn_r4(n1, n1, n1, n1);

    (*I2_down_fft)(dn_r1).copyTo((*I2_up_fft)(up_r1));
    (*I2_down_fft)(dn_r2).copyTo((*I2_up_fft)(up_r2));
    (*I2_down_fft)(dn_r3).copyTo((*I2_up_fft)(up_r3));
    (*I2_down_fft)(dn_r4).copyTo((*I2_up_fft)(up_r4));

    delete I2_down_fft;

    if(verbose) cout << "Upsampled fft (I2_up_fft):" << endl;
    if(verbose) cout << "    "  << (*I2_up_fft).rows << " x " << (*I2_up_fft).cols << " x " << (*I2_up_fft).channels() << endl;
    
    // saveComplexMat(*I2_up_fft, "../Output-Images/Mat.txt", 6000, 6000); 

    Mat* I2_up = new Mat;
    idft((*I2_up_fft), (*I2_up), DFT_SCALE | DFT_COMPLEX_OUTPUT);
    
    delete I2_up_fft;

    if(verbose) cout << "Inverse dft into spatial domain (I2_up):" << endl;
    if(verbose) cout << "    "  << (*I2_up).rows << " x " << (*I2_up).cols << " x " << (*I2_up).channels() << endl;

    // saveComplexMat(*I2_up, "../Output-Images/Mat.txt", 6000, 6000); 

    Mat despread = Mat::zeros(tile_pixels, tile_pixels, CV_32FC2);

    for(int i = 0; i < tile_pixels; i++)
    {
        for(int j = 0; j < tile_pixels; j++)
        {
            despread.at<complex<float>>(i,j) = (*I2_up).at<complex<float>>(i,j)*ref_wave.at<complex<float>>(i,j);
        }
    }

    if(verbose) cout << "Multiplied with the reference to get 'despread':" << endl;
    if(verbose) cout << "    " << despread.rows << " x " << despread.cols << " x " << despread.channels() << endl;
    if(verbose)
    {
        double max, min;
        Point minLoc, maxLoc;
        minMaxLoc(despread, &min, &max);
        cout << "    max pixel value: " << max << endl;
        cout << "    min pixel value: " << min << endl << endl;
    }

    // can clear variables here if needed, will have to use 'new' keyword and pointers to allocate/deallocate 
    delete I2_up;
    if(verbose) cout << "Cleared I2 variables" << endl;

    for(int i = 0; i < tile_pixels; i++)
    {
        for(int j = 0; j < tile_pixels; j++)
        {
            despread.at<complex<float>>(i,j) = apodizer.at<float>(i,j)*despread.at<complex<float>>(i,j);
        }
    }  

    
    if(verbose) cout << "Multiplied 'despread' and 'apodizer'" << endl;

    Mat apodizer_temp = Mat::zeros(tile_pixels, tile_pixels, CV_32FC2);
    for(int i = 0; i < tile_pixels; i++)
    {
        for(int j = 0; j < tile_pixels; j++)
        {
            apodizer_temp.at<complex<float>>(i,j) = apodizer.at<float>(i,j)*template_wave.at<complex<float>>(i,j);
        }
    }  

    if(verbose) cout << "Multiplied 'apodizer' and template wave" << endl;

    if(verbose) cout << "Ready to dft to correlate" << endl;

    Mat despread_fft, template_fft;
    dft(despread, despread_fft, DFT_COMPLEX_OUTPUT);
    dft(apodizer_temp, template_fft, DFT_COMPLEX_OUTPUT);
    
    if(verbose) cout << "DFT done" << endl;

    Mat correlated;

    mulSpectrums(despread_fft, template_fft, despread_fft, DFT_COMPLEX_OUTPUT, true);

    // saveComplexMat(despread_fft, "../Output-Images/Mat.txt", 6000, 6000); 

    if(verbose) cout << "Convolution done in frequency domain" << endl;

    idft(despread_fft, correlated, DFT_SCALE | DFT_COMPLEX_OUTPUT);
    
    // saveComplexMat(correlated, "../Output-Images/Mat.txt", 6000, 6000); 

    //// fftshift:

    Mat q1(correlated, Rect(                0,                 0, correlated.cols/2, correlated.rows/2));
    Mat q2(correlated, Rect(correlated.cols/2,                 0, correlated.cols/2, correlated.rows/2));
    Mat q3(correlated, Rect(                0, correlated.rows/2, correlated.cols/2, correlated.rows/2));
    Mat q4(correlated, Rect(correlated.cols/2, correlated.rows/2, correlated.cols/2, correlated.rows/2));

    Mat temp;
    q1.copyTo(temp);
    q4.copyTo(q1);
    temp.copyTo(q4);
    q2.copyTo(temp);
    q3.copyTo(q2);
    temp.copyTo(q3);
    
    if(verbose) cout << "Inverse dft and fftshift complete" << endl;

    if(verbose) cout << "-----------------------------------------------------" << endl;
    if(!verbose) cout << "Reconstruction DONE" << endl << endl;

    return correlated; 



    
     
}