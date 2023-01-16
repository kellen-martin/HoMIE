#include "header.hpp"




Mat Reconstructor(Mat& input_image, int zslice)
{
    temp_dist = ref_dist + z_resolution*(zslice - 1);
    rval waves = CalculateTemplate();

    Mat image = input_image(Range(0, Sn_pixels), Range(0, Sn_pixels)).clone();
    resize(image, image, Size(0,0), OVS, OVS, INTER_CUBIC); 
    // resize done using bicubic interpolation (this is what MATLAB does by default)

    float down_sz = n_pixels/OVS;
    Mat I2_down = image.clone();
    absdiff(waves.ref_wave, Scalar::all(0), I2_down);
    multiply(I2_down, I2_down, I2_down);
    I2_down = image - I2_down;

    resize(I2_down, I2_down, Size(down_sz, down_sz), 0, 0, INTER_NEAREST);
    // image downsized using same interpolation as MATLAB 'box' option

    Mat I2_down_fft;
    dft(I2_down, I2_down_fft, DFT_COMPLEX_OUTPUT);
    
    Mat I2_up_fft = Mat::zeros(n_pixels, n_pixels, CV_32F);
    I2_up_fft.convertTo(I2_up_fft, CV_32FC2);

    I2_up_fft(Range(                          0, down_sz/2), Range(                         0, down_sz/2)) 
        = I2_down_fft(Range(                  0, down_sz/2), Range(                         0, down_sz/2)).clone();
    I2_up_fft(Range( (n_pixels - 1) - down_sz/2, n_pixels) , Range(                         0, down_sz/2)) 
        = I2_down_fft(Range(          down_sz/2, down_sz)  , Range(                         0, down_sz/2)).clone();
    I2_up_fft(Range(                          0, down_sz/2), Range((n_pixels - 1) - down_sz/2, n_pixels))  
        = I2_down_fft(Range(                  0, down_sz/2), Range(                 down_sz/2, down_sz)).clone();
    I2_up_fft(Range( (n_pixels - 1) - down_sz/2, n_pixels) , Range((n_pixels - 1) - down_sz/2, n_pixels))  
        = I2_down_fft(Range(          down_sz/2, down_sz)  , Range(                 down_sz/2, down_sz)).clone();

    Mat I2_up;
    idft(I2_up_fft, I2_up, DFT_SCALE | DFT_REAL_OUTPUT);

    Mat despread;
    multiply(I2_up, waves.ref_wave, despread);

    // can clear variables here if needed, will have to use 'new' keyword and pointers to allocate/deallocate 

    Mat X, Y, sum;
    Mat linspace_x = linspace(-1, 1, n_pixels);
    Mat linspace_y = linspace(-1, 1, n_pixels);
    repeat(linspace_x, n_pixels, 1, X);
    repeat(linspace_y.t(), 1, n_pixels, Y);

    multiply(X,X,X);
    multiply(Y,Y,Y);
    add(X,Y,sum);
    cv::sqrt(sum, sum);
    Mat apodizer = Mat::ones(X.size(), X.type());
    compare(sum, 1, apodizer, CMP_LT);

    // can clear X, Y, sum if needed

    multiply(despread, apodizer, despread);
    multiply(apodizer, waves.template_wave, apodizer);
    Mat despread_fft, template_fft;
    dft(despread, despread_fft, DFT_COMPLEX_OUTPUT);
    dft(apodizer, template_fft, DFT_COMPLEX_OUTPUT);

    Mat correlated;

    mulSpectrums(despread_fft, template_fft, despread_fft, DFT_COMPLEX_OUTPUT, true);

    idft(despread_fft, correlated, DFT_SCALE | DFT_REAL_OUTPUT);

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

    return correlated; 

}





Mat Reconstructor(Mat& image, int zslice, Mat& cleaner)
{
    return Reconstructor(image, zslice); // havent actually ipmlemented the cleaner argument yet
}