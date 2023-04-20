#include "header.hpp"
#include "dtypes.cpp"

using namespace std;
using namespace cv;

// 'input' variable contents are passed as globals, change 'temp_dist' to alter z-depth

// struct rval
// {
//     // return value for calculating template and reference waves
//     Mat template_wave;
//     Mat ref_wave;
// };

rval CalculateTemplate()
{
    if(verbose) cout << "----------------- Calculate Template ----------------" << endl;

    string tem_filename = "../templates/OVS-" + to_string(OVS) + "_dist-" + to_string(temp_dist) + ".yml";
    string ref_filename = "../reference/OVS-" + to_string(OVS) + "_dist-" + to_string(ref_dist)  + ".yml";

    
    rval ret;


    ifstream file1(tem_filename);
    ifstream file2(ref_filename);

    if(file1.is_open()){
        file1.close();
        // found a template wave
        
        cv::FileStorage fs_tem(tem_filename, cv::FileStorage::READ);
        cv::Mat temp_wave;
        fs_tem["mat"] >> temp_wave;
        fs_tem.release();

        ret.template_wave = temp_wave;
        
    }else{
        // calculate template here
        float template_pos_x = 0;
        float template_pos_y = 0;
        float template_pos_z = temp_dist;
        
        Mat range = Mat(1, n_pixels , CV_32F);
        for(int i = 0; i < n_pixels; i++)
        {
            range.at<float>(i) = i;
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

        if(verbose) cout << "  template_phase: " << template_phase << endl;
        
        Mat ref_wave       = Mat::zeros(n_pixels, n_pixels, CV_32FC2);
        Mat template_wave  = Mat::zeros(n_pixels, n_pixels, CV_32FC2);
        Mat template_n_waves;
        Mat template_dist;
        Mat r_dist;
        Mat ref_n_waves;

        for(int ix = 0; ix < n_pixels; ix++)
        {
            float x = pixel_x.at<float>(ix);


            /////////////////////////////// template wave calculation: /////////////////////////////
            
            float tempx = x - ref_pos_x;
            Mat tempy = pixel_y - ref_pos_y;


            tempx = x - template_pos_x;
            tempy = pixel_y - template_pos_y;
            multiply(tempy, tempy, tempy);
            template_dist = (tempx*tempx) + (tempy) + (template_pos_z*template_pos_z);

            for(int i = 0; i < template_dist.rows; i++) // calculating reference distance to sensor
            {
                for(int j = 0; j < template_dist.cols; j++)
                {
                    template_dist.at<float>(i,j) = sqrt(template_dist.at<float>(i,j));
                }
            }



            template_n_waves = template_dist/wavelength;

            // cant raise e to the power of a matrix times a complex number inline so need loop:

            for(int i = 0; i < template_n_waves.cols; i++)
            {
                template_wave.at<complex<float>>(ix, i) = ((complex<float>)obj_amp)*exp(I*(complex<float>(((float)(2.0*pi))*(template_n_waves.at<float>(0, i) + template_phase))));

            } // calculated template wave (line 34 MATLAB CalculateTemplate.m) ///////////////////////
            
        }

        ret.template_wave = template_wave;

        FileStorage fs_tem(tem_filename, FileStorage::WRITE);
        fs_tem << "mat" << ret.template_wave;
        fs_tem.release();
    }

    if(file2.is_open()){
        file2.close();
        // found a reference wave

        cv::FileStorage fs_ref(ref_filename, cv::FileStorage::READ);
        cv::Mat ref_wave;
        fs_ref["mat"] >> ref_wave;
        fs_ref.release();

        ret.ref_wave = ref_wave;

    }else{
        // calculate reference here
        Mat range = Mat(1, n_pixels , CV_32F);
        for(int i = 0; i < n_pixels; i++)
        {
            range.at<float>(i) = i;
        }


        Mat pixel_x          = pixel_p*(range - floor(n_pixels/2.0));
        Mat pixel_y          = pixel_p*(range - floor(n_pixels/2.0));
        float ref_pos_z      = ref_dist;

        // Compute the reference wave on the sensor:
        
        Mat ref_wave       = Mat::zeros(n_pixels, n_pixels, CV_32FC2);
        Mat r_dist;
        Mat ref_n_waves;

        for(int ix = 0; ix < n_pixels; ix++)
        {
            float x = pixel_x.at<float>(ix);

            ////////////////////////////// reference wave calculation: ////////////////////////////

            float tempx = x - ref_pos_x;
            Mat tempy = pixel_y - ref_pos_y;
            multiply(tempy, tempy, tempy);
            r_dist = (tempx*tempx) + (tempy) + (ref_pos_z*ref_pos_z);

            for(int i = 0; i < r_dist.rows; i++) // calculating reference distance to sensor
            {
                for(int j = 0; j < r_dist.cols; j++)
                {
                    r_dist.at<float>(i,j) = sqrt(r_dist.at<float>(i,j));
                }
            }



            ref_n_waves = r_dist/wavelength;

            // cant raise e to the power of a matrix times a complex number inline so need loop:

            for(int i = 0; i < ref_n_waves.cols; i++)
            {
                ref_wave.at<complex<float>>(ix, i) = (((complex<float>)(ref_amp))*exp(I*((complex<float>)(((float)(2.0*pi))*ref_n_waves.at<float>(0, i)))));
            } // calculated reference wave (line 30 MATLAB CalculateTemplate.m) ////////////////////
            
        }
        
        ret.ref_wave = ref_wave;

        FileStorage fs_ref(ref_filename, FileStorage::WRITE);
        fs_ref << "mat" << ret.ref_wave;
        fs_ref.release();
    }


    // if(!verbose) cout << "Calculating Templates" << endl;

    // float template_pos_x = 0;
    // float template_pos_y = 0;
    // float template_pos_z = temp_dist;
    
    // Mat range = Mat(1, n_pixels , CV_32F);
    // for(int i = 0; i < n_pixels; i++)
    // {
    //     range.at<float>(i) = i;
    // }


    // Mat pixel_x          = pixel_p*(range - floor(n_pixels/2.0));
    // Mat pixel_y          = pixel_p*(range - floor(n_pixels/2.0));
    // float ref_pos_z      = ref_dist;

    // // Compute the reference wave on the sensor:
    // float xdif = (template_pos_x - ref_pos_x);
    // float ydif = (template_pos_y - ref_pos_y);
    // float zdif = (template_pos_z - ref_pos_z);

    // float dist = (xdif*xdif) + (ydif*ydif) + (zdif*zdif);
    // float template_phase = 2*pi*sqrt(dist)/wavelength;

    // if(verbose) cout << "  template_phase: " << template_phase << endl;
    
    // Mat ref_wave       = Mat::zeros(n_pixels, n_pixels, CV_32FC2);
    // Mat template_wave  = Mat::zeros(n_pixels, n_pixels, CV_32FC2);
    // Mat template_n_waves;
    // Mat template_dist;
    // Mat r_dist;
    // Mat ref_n_waves;

    // for(int ix = 0; ix < n_pixels; ix++)
    // {
    //     float x = pixel_x.at<float>(ix);

    //     ////////////////////////////// reference wave calculation: ////////////////////////////

    //     float tempx = x - ref_pos_x;
    //     Mat tempy = pixel_y - ref_pos_y;
    //     multiply(tempy, tempy, tempy);
    //     r_dist = (tempx*tempx) + (tempy) + (ref_pos_z*ref_pos_z);

    //     for(int i = 0; i < r_dist.rows; i++) // calculating reference distance to sensor
    //     {
    //         for(int j = 0; j < r_dist.cols; j++)
    //         {
    //             r_dist.at<float>(i,j) = sqrt(r_dist.at<float>(i,j));
    //         }
    //     }



    //     ref_n_waves = r_dist/wavelength;

    //     // cant raise e to the power of a matrix times a complex number inline so need loop:

    //     for(int i = 0; i < ref_n_waves.cols; i++)
    //     {
    //         ref_wave.at<complex<float>>(ix, i) = (((complex<float>)(ref_amp))*exp(I*((complex<float>)(((float)(2.0*pi))*ref_n_waves.at<float>(0, i)))));
    //     } // calculated reference wave (line 30 MATLAB CalculateTemplate.m) ////////////////////

    //     /////////////////////////////// template wave calculation: /////////////////////////////



    //     tempx = x - template_pos_x;
    //     tempy = pixel_y - template_pos_y;
    //     multiply(tempy, tempy, tempy);
    //     template_dist = (tempx*tempx) + (tempy) + (template_pos_z*template_pos_z);

    //     for(int i = 0; i < template_dist.rows; i++) // calculating reference distance to sensor
    //     {
    //         for(int j = 0; j < template_dist.cols; j++)
    //         {
    //             template_dist.at<float>(i,j) = sqrt(template_dist.at<float>(i,j));
    //         }
    //     }



    //     template_n_waves = template_dist/wavelength;

    //     // cant raise e to the power of a matrix times a complex number inline so need loop:

    //     for(int i = 0; i < template_n_waves.cols; i++)
    //     {
    //         template_wave.at<complex<float>>(ix, i) = ((complex<float>)obj_amp)*exp(I*(complex<float>(((float)(2.0*pi))*(template_n_waves.at<float>(0, i) + template_phase))));

    //     } // calculated template wave (line 34 MATLAB CalculateTemplate.m) ///////////////////////

        
    // }


    // saveRealMat(ref_n_waves, "../Output-Images/ref_n_waves.txt", 1, 6000);
    // saveComplexMat(ref_wave, "../Output-Images/ref.txt", 6000, 6000);
    // saveComplexMat(template_wave, "../Output-Images/temp.txt", n_pixels, n_pixels);

    // if(verbose) cout << "  pixel_p: " << pixel_p << endl;
    // if(verbose)
    // {
    //     double max, min;
    //     Point minLoc, maxLoc;
    //     minMaxLoc(range, &min, &max);
    //     cout << "  range (final): " << endl;
    //     cout << "      (" << range.rows << " x " << range.cols << " x " << range.channels() << ")" << endl;
    //     cout << "    max pixel value: " << max << endl;
    //     cout << "    min pixel value: " << min << endl << endl;
    // }
    // if(verbose)
    // {
    //     double max, min;
    //     Point minLoc, maxLoc;
    //     minMaxLoc(pixel_x, &min, &max);
    //     cout << "  pixel_x (final): " << endl;
    //     cout << "      (" << pixel_x.rows << " x " << pixel_x.cols << " x " << pixel_x.channels() << ")" << endl;
    //     cout << "    max pixel value: " << max << endl;
    //     cout << "    min pixel value: " << min << endl << endl;
    // }
    // if(verbose)
    // {
    //     double max, min;
    //     Point minLoc, maxLoc;
    //     minMaxLoc(r_dist, &min, &max);
    //     cout << "  r_dist (final): " << endl;
    //     cout << "      (" << r_dist.rows << " x " << r_dist.cols << " x " << r_dist.channels() << ")" << endl;
    //     cout << "    max pixel value: " << max << endl;
    //     cout << "    min pixel value: " << min << endl << endl;
    // }
    // if(verbose)
    // {
    //     double max, min;
    //     Point minLoc, maxLoc;
    //     minMaxLoc(ref_n_waves, &min, &max);
    //     cout << "  ref_n_waves (final): " << endl;
    //     cout << "      (" << ref_n_waves.rows << " x " << ref_n_waves.cols << " x " << ref_n_waves.channels() << ")" << endl;
    //     cout << "    max pixel value: " << max << endl;
    //     cout << "    min pixel value: " << min << endl << endl;
    // }
    // if(verbose)
    // {
    //     double max, min;
    //     Point minLoc, maxLoc;
    //     minMaxLoc(template_n_waves, &min, &max);
    //     cout << "  template_n_waves (final): " << endl;
    //     cout << "      (" << template_n_waves.rows << " x " << template_n_waves.cols << " x " << template_n_waves.channels() << ")" << endl;
    //     cout << "    max pixel value: " << max << endl;
    //     cout << "    min pixel value: " << min << endl << endl;
    // }
    // if(verbose)
    // {
    //     double max, min;
    //     Point minLoc, maxLoc;
    //     minMaxLoc(template_dist, &min, &max);
    //     cout << "  template_dist (final): " << endl;
    //     cout << "      (" << template_dist.rows << " x " << template_dist.cols << " x " << template_dist.channels() << ")" << endl;
    //     cout << "    max pixel value: " << max << endl;
    //     cout << "    min pixel value: " << min << endl << endl;
    // }
    // if(verbose) cout << "Calculated reference and template waves:" << endl;
    // if(verbose) cout << "    reference: " << ret.ref_wave.rows << " x " << ret.ref_wave.cols << " x " << ret.ref_wave.channels() << endl;
    // if(verbose) cout << "    template:  " << template_wave.rows << " x " << ret.template_wave.cols << " x " << ret.template_wave.channels() << endl;
    // if(verbose) cout << "-----------------------------------------------------" << endl;
    // if(!verbose) cout << "Templates DONE" << endl << endl;
    
    return ret;

}