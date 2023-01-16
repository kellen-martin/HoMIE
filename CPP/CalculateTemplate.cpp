#include "header.hpp"

// 'input' variable contents are passed as globals, change 'temp_dist' to alter z-depth

rval CalculateTemplate()
{
    float template_pos_x = 0;
    float template_pos_y = 0;
    float template_pos_z = temp_dist;
    
    Mat range = Mat(1, n_pixels , CV_32S);
    for(int i = 0; i < n_pixels; i++)
    {
        range.at<int>(i) = i;
    }


    Mat pixel_x          = pixel_p*(range - floor(n_pixels/2.0));
    Mat pixel_y          = pixel_p*(range - floor(n_pixels/2.0));
    float ref_pos_z      = ref_dist;

    // Compute the reference wave on the sensor:
    float xdif = (template_pos_x - ref_pos_x);
    float ydif = (template_pos_y - ref_pos_y);
    float zdif = (template_pos_z - ref_pos_z);

    float dist = (xdif*xdif) + (ydif*ydif) + (zdif*zdif);
    float template_phase = 2*pi*sqrt(dist)/wavelength;

    // Mat ref_wave      = Mat::zeros(n_pixels, n_pixels, CV_32F);
    // Mat template_wave = Mat::zeros(n_pixels, n_pixels, CV_32F); // single precision real valued
    
    Mat temp      = Mat::zeros(n_pixels, n_pixels, CV_32F);
    Mat ref_wave, template_wave;

    temp.convertTo(ref_wave, CV_32FC2);
    temp.convertTo(template_wave, CV_32FC2); // single precision complex valued

    for(int ix = 0; ix < n_pixels; ix++)
    {
        float x = pixel_x.at<float>(ix);

        ////////////////////////////// reference wave calculation: ////////////////////////////

        float tempx = x - ref_pos_x;
        Mat tempy = pixel_y - ref_pos_y;
        multiply(tempy, tempy, tempy);
        Mat r_dist = (tempx*tempx) + (tempy) + (ref_pos_z*ref_pos_z);

        for(int i = 0; i < r_dist.rows; i++) // calculating reference distance to sensor
        {
            for(int j = 0; j < r_dist.cols; j++)
            {
                r_dist.at<float>(i,j) = sqrt(r_dist.at<float>(i,j));
            }
        }



        Mat ref_n_waves = r_dist/wavelength;

        // cant raise e to the power of a matrix times a complex number inline so need loop:

        for(int i = 0; i < ref_n_waves.rows; i++)
        {
            ref_wave.at<complex<float>>(ix, i) = (ref_amp*exp(I*(complex<float>(2.0*pi*ref_n_waves.at<float>(1, i)))));

        } // calculated reference wave (line 30 MATLAB CalculateTemplate.m) ////////////////////

        /////////////////////////////// template wave calculation: /////////////////////////////

        float tempx = x - template_pos_x;
        Mat tempy = pixel_y - template_pos_y;
        multiply(tempy, tempy, tempy);
        Mat template_dist = (tempx*tempx) + (tempy) + (template_pos_z*template_pos_z);

        for(int i = 0; i < template_dist.rows; i++) // calculating reference distance to sensor
        {
            for(int j = 0; j < template_dist.cols; j++)
            {
                template_dist.at<float>(i,j) = sqrt(template_dist.at<float>(i,j));
            }
        }



        Mat template_n_waves = template_dist/wavelength;

        // cant raise e to the power of a matrix times a complex number inline so need loop:

        for(int i = 0; i < template_n_waves.rows; i++)
        {
            template_wave.at<complex<float>>(ix, i) = (obj_amp*exp(I*(complex<float>(2.0*pi*(template_n_waves.at<float>(1, i) + template_phase)))));

        } // calculated template wave (line 34 MATLAB CalculateTemplate.m) ///////////////////////

        
    }

    rval ret;
    ret.ref_wave = ref_wave;
    ret.template_wave = template_wave;

    return ret;

}