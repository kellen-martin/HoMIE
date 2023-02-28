#include "header.hpp"

using namespace std;
using namespace cv;


Mat Reconstructor(Mat& input_image, int zslice)
{
    if(verbose) cout << "-------------------- Reconstructor ------------------" << endl;

    temp_dist = samp_dist + z_resolution*(zslice - 1);

    if(verbose) cout << "Image in: " << input_image.rows << " x " << input_image.cols << " x " << input_image.channels() << endl;
    if(verbose)
    {
        double max, min;
        Point minLoc, maxLoc;
        minMaxLoc(input_image, &min, &max);
        cout << "    max pixel value: " << max << endl;
        cout << "    min pixel value: " << min << endl << endl;
    }

    
    if(verbose) cout << "Calculating template and reference waves:" << endl;
    if(verbose) cout << "-  -  -  -  -  -  -  -  -   -  -  -  -  -  -  -  -  - " << endl;
    rval waves = CalculateTemplate();
    if(verbose) cout << "-  -  -  -  -  -  -  -  -   -  -  -  -  -  -  -  -  - " << endl;
    if(verbose) cout << "Returned to Reconstructor" << endl;

    // saveComplexMat(waves.template_wave, "../Output-Images/template_wave.txt", 6000, 6000);

    if(verbose)
    {
        double max, min;
        Point minLoc, maxLoc;
        minMaxLoc(waves.template_wave, &min, &max);
        if(verbose) cout << "  Template: ----------------" << endl;
        if(verbose) cout << "    max pixel value: " << max << endl;
        if(verbose) cout << "    min pixel value: " << min << endl << endl;
    }
    if(verbose)
    {
        double max, min;
        Point minLoc, maxLoc;
        minMaxLoc(waves.ref_wave, &min, &max);
        if(verbose) cout << "  Reference: ---------------" << endl;
        if(verbose) cout << "    max pixel value: " << max << endl;
        if(verbose) cout << "    min pixel value: " << min << endl << endl;
    }

    Mat image = input_image(Range(0, Sn_pixels), Range(0, Sn_pixels)).clone();
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

    float down_sz = n_pixels/OVS;
    Mat* I2_down = new Mat;
    *I2_down = Mat::zeros(n_pixels, n_pixels, CV_32F);

    for(int i = 0; i < waves.ref_wave.rows; i++){
        for(int j = 0; j < waves.ref_wave.cols; j++){

            (*I2_down).at<float>(i,j) = (float)((real(waves.ref_wave.at<complex<float>>(i,j))*real(waves.ref_wave.at<complex<float>>(i,j))) + (imag(waves.ref_wave.at<complex<float>>(i,j))*imag(waves.ref_wave.at<complex<float>>(i,j))));

        }
    }
    (*I2_down) = image - (*I2_down);

    if(verbose) cout << "Calculated abs difference between ref and image" << endl;

    resize((*I2_down), (*I2_down), Size(down_sz, down_sz), 0, 0, INTER_NEAREST);

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
    
    if(verbose) cout << "Calculated dft of I2_down (I2_down_fft):" << endl;
    if(verbose) cout << "    "  << (*I2_down_fft).rows << " x " << (*I2_down_fft).cols << " x " << (*I2_down_fft).channels() << endl;
    
    // saveComplexMat(*I2_down_fft, "../Output-Images/Mat.txt", 3000, 3000); 

    Mat* I2_up_fft = new Mat;
    (*I2_up_fft) = Mat::zeros(n_pixels, n_pixels, CV_32FC2);

    Rect up_r1(                         0,                          0, down_sz/2, down_sz/2);
    Rect dn_r1(                         0,                          0, down_sz/2, down_sz/2);
    Rect up_r2((n_pixels - 1) - down_sz/2,                          0, down_sz/2, down_sz/2);
    Rect dn_r2(                 down_sz/2,                          0, down_sz/2, down_sz/2);
    Rect up_r3(                         0, (n_pixels - 1) - down_sz/2, down_sz/2, down_sz/2);
    Rect dn_r3(                         0,                  down_sz/2, down_sz/2, down_sz/2);
    Rect up_r4((n_pixels - 1) - down_sz/2, (n_pixels - 1) - down_sz/2, down_sz/2, down_sz/2);
    Rect dn_r4(                 down_sz/2,                  down_sz/2, down_sz/2, down_sz/2);

    (*I2_down_fft)(dn_r1).copyTo((*I2_up_fft)(up_r1));
    (*I2_down_fft)(dn_r2).copyTo((*I2_up_fft)(up_r2));
    (*I2_down_fft)(dn_r3).copyTo((*I2_up_fft)(up_r3));
    (*I2_down_fft)(dn_r4).copyTo((*I2_up_fft)(up_r4));

    
    if(verbose) cout << "Upsampled fft (I2_up_fft):" << endl;
    if(verbose) cout << "    "  << (*I2_up_fft).rows << " x " << (*I2_up_fft).cols << " x " << (*I2_up_fft).channels() << endl;
    
    // saveComplexMat(*I2_up_fft, "../Output-Images/Mat.txt", 6000, 6000); 

    Mat* I2_up = new Mat;
    idft((*I2_up_fft), (*I2_up), DFT_SCALE | DFT_COMPLEX_OUTPUT);

    if(verbose) cout << "Inverse dft into spatial domain (I2_up):" << endl;
    if(verbose) cout << "    "  << (*I2_up).rows << " x " << (*I2_up).cols << " x " << (*I2_up).channels() << endl;

    // saveComplexMat(*I2_up, "../Output-Images/Mat.txt", 6000, 6000); 

    Mat despread = Mat::zeros(n_pixels, n_pixels, CV_32FC2);

    for(int i = 0; i < n_pixels; i++)
    {
        for(int j = 0; j < n_pixels; j++)
        {
            despread.at<complex<float>>(i,j) = (*I2_up).at<complex<float>>(i,j)*waves.ref_wave.at<complex<float>>(i,j);
        }
    }

    // multiply(I2_up, waves.ref_wave, despread);

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
    delete I2_up_fft;
    delete I2_down;
    delete I2_down_fft;
    // I2_up, I2_up_fft, I2_down, I2_down_fft
    if(verbose) cout << "Cleared I2 variables" << endl;

    Mat* X = new Mat;
    Mat* Y = new Mat;
    Mat* sum = new Mat;

    Mat* linspace_x = new Mat;
    linspace(-1, 1, n_pixels, linspace_x);
    Mat* linspace_y = new Mat;
    linspace(-1, 1, n_pixels, linspace_y);
    if(verbose) cout << "Done with linspace" << endl;
    repeat((*linspace_x), n_pixels, 1, (*X));
    repeat(linspace_y->t(), 1, n_pixels, (*Y));

    delete linspace_x;
    delete linspace_y;

    if(verbose) cout << "Created X and Y arrays (meshgrid):" << endl;
    if(verbose) cout << "    X: " << (*X).rows << " x " << (*X).cols << " x " << (*X).channels() << endl;
    if(verbose) cout << "    Y: " << (*Y).rows << " x " << (*Y).cols << " x " << (*Y).channels() << endl;

    multiply((*X),(*X),(*X));
    multiply((*Y),(*Y),(*Y));
    add((*X),(*Y),(*sum));
    cv::sqrt((*sum), (*sum));
    Mat apodizer = Mat::zeros(n_pixels, n_pixels, CV_32F);

    for(int i = 0; i < n_pixels; i++)
    {
        for(int j = 0; j < n_pixels; j++)
        {
            if(sum->at<float>(i,j) <= 1)
            {
                apodizer.at<float>(i,j) = 1;
            }
        }
    }    // compare((*sum), 1, apodizer, CMP_LT);

    // can clear X, Y, sum if needed
    delete X;
    delete Y;
    delete sum;

    if(verbose) cout << "Created apodizer: " << apodizer.rows << " x " << apodizer.cols << " x " << apodizer.channels() << endl;

    for(int i = 0; i < n_pixels; i++)
    {
        for(int j = 0; j < n_pixels; j++)
        {
            despread.at<complex<float>>(i,j) = apodizer.at<float>(i,j)*despread.at<complex<float>>(i,j);
        }
    }    // multiply(despread, apodizer, despread);

    
    if(verbose) cout << "Multiplied 'despread' and 'apodizer'" << endl;

    Mat apodizer_temp = Mat::zeros(n_pixels, n_pixels, CV_32FC2);
    for(int i = 0; i < n_pixels; i++)
    {
        for(int j = 0; j < n_pixels; j++)
        {
            apodizer_temp.at<complex<float>>(i,j) = apodizer.at<float>(i,j)*waves.template_wave.at<complex<float>>(i,j);
        }
    }    // multiply(apodizer, waves.template_wave, apodizer);
    if(verbose) cout << "Multiplied 'apodizer' and template wave" << endl;

    if(verbose) cout << "Ready to dft to correlate" << endl;

    Mat despread_fft, template_fft;
    dft(despread, despread_fft, DFT_COMPLEX_OUTPUT);
    dft(apodizer_temp, template_fft, DFT_COMPLEX_OUTPUT);
    
    if(verbose) cout << "DFT done" << endl;


    Mat correlated;

    mulSpectrums(despread_fft, template_fft, despread_fft, DFT_COMPLEX_OUTPUT, true);
    
    // despread_fft = despread_fft*(template_fft.conj());

    // Mat conj_mat(template_fft.size(), template_fft.type());
    // for (int i = 0; i < template_fft.rows; i++) {
    //     for (int j = 0; j < template_fft.cols; j++) {
    //         conj_mat.at<complex<float>>(i, j) = conj(template_fft.at<std::complex<float>>(i, j));
    //     }
    // }

    // despread_fft = despread_fft*conj_mat;

    // saveComplexMat(despread_fft, "../Output-Images/Mat.txt", 6000, 6000); 

    if(verbose) cout << "Convolution done in frequency domain" << endl;

    idft(despread_fft, correlated, DFT_SCALE | DFT_COMPLEX_OUTPUT);
    // idft(despread_fft, correlated, DFT_COMPLEX_OUTPUT);
    
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

    return correlated; 

}





Mat Reconstructor(Mat& image, int zslice, Mat& cleaner)
{
    return Reconstructor(image, zslice); // havent actually ipmlemented the cleaner argument yet
}