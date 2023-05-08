#include "header.hpp"

using namespace std;
using namespace cv;


Mat Reconstructor_Kanka(Mat& input_image, vector<int> zslice)
{
    Mat ret;

    if(verbose){
        cout << "----------- Starting Kanka Method -----------" << endl;
    }

    //////////////// calculate reference wave (same for all z-depth)
    
    Mat range = Mat(1, n_pixels , CV_32F);
    for(int i = 0; i < n_pixels; i++)
    {
        range.at<float>(i) = i;
    }


    Mat pixel_x          = pixel_p*(range - floor(n_pixels/2.0));
    Mat pixel_y          = pixel_p*(range - floor(n_pixels/2.0));
    float ref_pos_z      = ref_dist;
    
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

        for(int i = 0; i < r_dist.rows; i++)
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

    for(int i = 0; i < zslice.size(); i++)
    {
        //////////// calculate template for each z-slice

        float template_pos_x = 0;
        float template_pos_y = 0;
        float template_pos_z = temp_dist + zslice[i]*z_resolution;
        
        Mat range = Mat(1, n_pixels , CV_32F);
        for(int i = 0; i < n_pixels; i++)
        {
            range.at<float>(i) = i;
        }

        float xdif = (template_pos_x - ref_pos_x);
        float ydif = (template_pos_y - ref_pos_y);
        float zdif = (template_pos_z - ref_pos_z);

        float dist = (xdif*xdif) + (ydif*ydif) + (zdif*zdif);
        float template_phase = 2*pi*sqrt(dist)/wavelength;
        
        Mat template_wave  = Mat::zeros(n_pixels, n_pixels, CV_32FC2);
        Mat template_n_waves;
        Mat template_dist;

        for(int ix = 0; ix < n_pixels; ix++)
        {
            float x = pixel_x.at<float>(ix);

            /////////////////////////////// template wave calculation: /////////////////////////////

            float tempx = x - template_pos_x;
            Mat tempy = pixel_y - template_pos_y;
            multiply(tempy, tempy, tempy);
            template_dist = (tempx*tempx) + (tempy) + (template_pos_z*template_pos_z);

            for(int i = 0; i < template_dist.rows; i++)
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

        Mat* X = new Mat;
        Mat* Y = new Mat;
        Mat* sum = new Mat;

        Mat* linspace_x = new Mat;
        linspace(-1, 1, n_pixels, linspace_x);
        Mat* linspace_y = new Mat;
        linspace(-1, 1, n_pixels, linspace_y);
        repeat((*linspace_x), n_pixels, 1, (*X));
        repeat(linspace_y->t(), 1, n_pixels, (*Y));

        delete linspace_x;
        delete linspace_y;

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
        } 

        // can clear X, Y, sum if needed
        delete X;
        delete Y;
        delete sum;

        //////////// select tiles

        Mat TileSum = Mat::zeros(n_pixels, n_pixels, CV_32FC2);

        for(int tileX = 0; tileX < num_tiles; tileX++)
        {
            for(int tileY = 0; tileY < num_tiles; tileY++)
            {
                int imageStartX = ((int)((int)input_image.rows/num_tiles))*(tileX);
                int imageStartY = ((int)((int)input_image.cols/num_tiles))*(tileY);

                int wavesStartX = ((int)((int)n_pixels/num_tiles))*(tileX);
                int wavesStartY = ((int)((int)n_pixels/num_tiles))*(tileY);

                int imageEndX = (int)((input_image.rows/num_tiles)*(tileX + 1)) - 1;
                int imageEndY = (int)((input_image.cols/num_tiles)*(tileY + 1)) - 1;

                int wavesEndX = (int)((n_pixels/num_tiles)*(tileX + 1)) - 1;
                int wavesEndY = (int)((n_pixels/num_tiles)*(tileY + 1)) - 1;

                ///////////////////////////////////////////////////////////////////////////////////
                cout << "Tile indexes:" << endl;
                cout << "    imageStartX: " << imageStartX << endl;
                cout << "    imageStartY: " << imageStartY << endl << endl;
                
                cout << "    imageEndX: " << imageEndX << endl;
                cout << "    imageEndY: " << imageEndY << endl << endl;

                cout << "    wavesStartX: " << wavesStartX << endl;
                cout << "    wavesStartY: " << wavesStartY << endl << endl;

                cout << "    wavesEndX: " << wavesEndX << endl;
                cout << "    wavesEndY: " << wavesEndY << endl << endl;
                ///////////////////////////////////////////////////////////////////////////////////

                Rect roi_image(imageStartX, imageStartY, imageEndX - imageStartX + 1, imageEndY - imageStartY + 1);
                Rect roi_waves(wavesStartX, wavesStartY, wavesEndX - wavesStartX + 1, wavesEndY - wavesStartY + 1);

                Mat image_tile = input_image(roi_image);
                Mat ref_tile = ref_wave(roi_waves);
                Mat temp_tile = template_wave(roi_waves);
                Mat apod_tile = apodizer(roi_waves);

                Mat tile = Reconstruct_tile(image_tile, ref_tile, temp_tile, apod_tile);

                for(int totalX = wavesStartX; totalX <= wavesEndX; totalX++){
                    for(int totalY = wavesStartY; totalY <= wavesEndY; totalY++){
                        TileSum.at<complex<float>>(totalX, totalY) = tile.at<complex<float>>(totalX - wavesStartX, totalY - wavesStartY);
                    }
                }
            }
        }



        //////////// give to new reconstructor 

        //////////// add to tile sum


        ret = TileSum;


    }


    
    return ret; 

     
}