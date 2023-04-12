#include "header.hpp"

using namespace std;
using namespace cv;


Mat Reconstructor_Kanka(Mat& input_image, int zslice)
{
    Mat image = input_image(Range(0, Sn_pixels), Range(0, Sn_pixels)).clone();
    resize(image, image, Size(0,0), OVS, OVS, INTER_CUBIC); 

    int down_sz = n_pixels/OVS;
    Mat* I2_down = new Mat;
    *I2_down = Mat::zeros(n_pixels, n_pixels, CV_32F);
    rval waves = CalculateTemplate();

    for(int i = 0; i < waves.ref_wave.rows; i++){
        for(int j = 0; j < waves.ref_wave.cols; j++){

            (*I2_down).at<float>(i,j) = (float)((real(waves.ref_wave.at<complex<float>>(i,j))*real(waves.ref_wave.at<complex<float>>(i,j))) + (imag(waves.ref_wave.at<complex<float>>(i,j))*imag(waves.ref_wave.at<complex<float>>(i,j))));

        }
    }
    (*I2_down) = image - (*I2_down);
    
    resize((*I2_down), (*I2_down), Size(down_sz, down_sz), 0, 0, INTER_CUBIC);

    int tile_dimension = down_sz/num_tiles;

    Mat* total = new Mat;
    *total = Mat::zeros(down_sz, down_sz, CV_32FC2);

    // #pragma omp parallel for collapse(2)

    for(int i = 0; i < num_tiles; i++)
    {        
        for(int j = 0; j < num_tiles; j++)
        {

                cout << endl << "New loop" << endl << endl;
            // #pragma omp parallel
            // {
                int y1 = i*tile_dimension;
                int x1 = j*tile_dimension;
                int x2 = x1 + tile_dimension - 1;
                int y2 = y1 + tile_dimension - 1;
                
                Mat* I2_down_tile = new Mat;
                // (*I2_down_tile) = (*I2_down)(Range(x1, tile_dimension), Range(y1, tile_dimension)).clone();
                (*I2_down_tile) = (*I2_down)(Range(x1, x2 + 1), Range(y1, y2 + 1)).clone();
                Mat* I2_down_fft_tile = new Mat;
                
                ////////////////////////////////////////////////////
                cout << "indexes:" << endl;
                cout << "    x1: " << x1 << endl;
                cout << "    x2: " << x2 << endl;
                cout << "    y1: " << y1 << endl;
                cout << "    y2: " << y2 << endl << endl;
                cout << "    I2_down_tile size:     " << I2_down_tile->cols << endl;
                ////////////////////////////////////////////////////

                dft((*I2_down_tile), (*I2_down_fft_tile), DFT_COMPLEX_OUTPUT);
                
                ////////////////////////////////////////////////////
                cout << "I2_down_tile done" << endl;
                ////////////////////////////////////////////////////

                Mat* I2_up_fft_tile = new Mat;
                (*I2_up_fft_tile) = Mat::zeros(n_pixels/num_tiles, n_pixels/num_tiles, CV_32FC2);

                Rect up_r1(                                          0,                                           0, tile_dimension/2, tile_dimension/2);
                Rect dn_r1(                                          0,                                           0, tile_dimension/2, tile_dimension/2);
                Rect up_r2((n_pixels/num_tiles - 1) - tile_dimension/2,                                           0, tile_dimension/2, tile_dimension/2);
                Rect dn_r2(                           tile_dimension/2,                                           0, tile_dimension/2, tile_dimension/2);
                Rect up_r3(                                          0, (n_pixels/num_tiles - 1) - tile_dimension/2, tile_dimension/2, tile_dimension/2);
                Rect dn_r3(                                          0,                            tile_dimension/2, tile_dimension/2, tile_dimension/2);
                Rect up_r4((n_pixels/num_tiles - 1) - tile_dimension/2, (n_pixels/num_tiles - 1) - tile_dimension/2, tile_dimension/2, tile_dimension/2);
                Rect dn_r4(                           tile_dimension/2,                            tile_dimension/2, tile_dimension/2, tile_dimension/2);
                
                ////////////////////////////////////////////////////
                cout << "ranges created:" << endl;
                cout << "    n_pixels:         " << n_pixels << endl;
                cout << "    num_tiles:        " << num_tiles << endl;
                cout << "    down_sz:          " << down_sz << endl;
                cout << "    tile_dimension:   " << tile_dimension << endl;
                cout << "    tile_dimension/2: " << tile_dimension/2 << endl;
                cout << "    I2_down_fft_tile size: " << I2_down_fft_tile->cols << endl;
                cout << "    I2_up_fft_tile size:   " << I2_up_fft_tile->cols << endl;
                ////////////////////////////////////////////////////

                (*I2_down_fft_tile)(dn_r1).copyTo((*I2_up_fft_tile)(up_r1));
                (*I2_down_fft_tile)(dn_r2).copyTo((*I2_up_fft_tile)(up_r2));
                (*I2_down_fft_tile)(dn_r3).copyTo((*I2_up_fft_tile)(up_r3));
                (*I2_down_fft_tile)(dn_r4).copyTo((*I2_up_fft_tile)(up_r4));
                
                ////////////////////////////////////////////////////
                cout << "I2_up_fft_tile populated" << endl;
                ////////////////////////////////////////////////////
                
                Mat* I2_up_tile = new Mat;
                idft((*I2_up_fft_tile), (*I2_up_tile), DFT_SCALE | DFT_COMPLEX_OUTPUT);

                int nx1 = x1*2;
                int nx2 = x2*2 + 1;
                int ny1 = y1*2;
                int ny2 = y2*2 + 1;

                ////////////////////////////////////////////////////
                cout << "New indexes: " << endl;
                cout << "    nx1: " << nx1 << endl;
                cout << "    nx2: " << nx2 << endl;
                cout << "    ny1: " << ny1 << endl;
                cout << "    ny2: " << ny2 << endl;
                ////////////////////////////////////////////////////


                Mat ref_wave_tile = waves.ref_wave(Range(nx1, nx2 + 1), Range(ny1, ny2 + 1));
                
                ////////////////////////////////////////////////////
                cout << "Ref wave patch copied" << endl;
                ////////////////////////////////////////////////////
                
                Mat* despread_tile = new Mat;
                *despread_tile = Mat::zeros(n_pixels/num_tiles, n_pixels/num_tiles, CV_32FC2);

                for(int i2 = 0; i2 < n_pixels/num_tiles; i2++)
                {
                    for(int j2 = 0; j2 < n_pixels/num_tiles; j2++)
                    {
                        despread_tile->at<complex<float>>(i2,j2) = (*I2_up_tile).at<complex<float>>(i2,j2)*ref_wave_tile.at<complex<float>>(i2,j2);
                    }
                }
                
                despread_tile->copyTo((*total)(Range(nx1, nx2 + 1), Range(ny1, ny2 + 1)));
                
                ////////////////////////////////////////////////////
                cout << "total updated" << endl;
                ////////////////////////////////////////////////////

                delete despread_tile;
                delete I2_down_tile;
                delete I2_up_tile;
                delete I2_down_fft_tile;
                delete I2_up_fft_tile;

            // }

        }
    }

    ////////////////////////////////////////////////////
    cout << "exited loop" << endl;
    ////////////////////////////////////////////////////
    
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

    Mat despread = *total;

    for(int i = 0; i < n_pixels; i++)
    {
        for(int j = 0; j < n_pixels; j++)
        {
            despread.at<complex<float>>(i,j) = apodizer.at<float>(i,j)*despread.at<complex<float>>(i,j);
        }
    }  

    Mat apodizer_temp = Mat::zeros(n_pixels, n_pixels, CV_32FC2);
    for(int i = 0; i < n_pixels; i++)
    {
        for(int j = 0; j < n_pixels; j++)
        {
            apodizer_temp.at<complex<float>>(i,j) = apodizer.at<float>(i,j)*waves.template_wave.at<complex<float>>(i,j);
        }
    }  

    Mat despread_fft, template_fft;
    dft(despread, despread_fft, DFT_COMPLEX_OUTPUT);
    dft(apodizer_temp, template_fft, DFT_COMPLEX_OUTPUT);

    Mat correlated;

    mulSpectrums(despread_fft, template_fft, despread_fft, DFT_COMPLEX_OUTPUT, true);

    idft(despread_fft, correlated, DFT_SCALE | DFT_COMPLEX_OUTPUT);
    
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