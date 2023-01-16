#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <dirent.h>
// #include <map>
#include "opencv.hpp"
#include <cmath>
#include <complex>


using namespace std;
using namespace cv;

// globals:
float Zheight       = 2e-3;
float z_resolution  = 2e-6;
int Sn_pixels       = 3000;
int OVS             = 2;
float wavelength    = 405e-9;
float pixel_p       = 1.85e-6;
int n_pixels        = Sn_pixels*OVS;
float ref_dist      = 12e-3;
float samp_dist     = 8.14e-3;
float temp_dist     = samp_dist; // Change this to recalculate templates at varying z-depth
float ref_amp       = 1;
float ref_pos_x     = 0;
float ref_pos_y     = 0;
float obj_amp       = 0.01;
double pi           = acos(-1);
complex<float> I(0, 1);

float ROI_x[2] = {-0.5*1e-3, 0.5*1e-3};
float ROI_y[2] = {-0.5*1e-3, 0.5*1e-3};
int ROI_x_pix[2] = {n_pixels/2 + ROI_x[0]/pixel_p, n_pixels/2 + ROI_x[1]/pixel_p};
int ROI_y_pix[2] = {n_pixels/2 + ROI_y[0]/pixel_p, n_pixels/2 + ROI_y[1]/pixel_p};

struct settings
{
    int FPS;
    // include other settings here or just have FPS as a field of image_set

    // settings(int FPS); // constructor function, initiate a settings variable
    // ^^^^ will have to make a constructor for image_set to call this if we want to
};

struct image_set
{
    string ID;                      // ID to reference data
    vector<Mat> images;             // vector of hologram images
    vector<string> movementFlags;   // vector containing any movement flags
    settings sensorSettings;        // settings struct with info on image sensor settings for images
};

struct rval
{
    Mat template_wave;
    Mat ref_wave;
};


void readCommands(vector<string>& commands, string commandFilename);
Mat AverageImage(vector<Mat>& images, int first, int last);
Mat AverageImage(vector<Mat>& images);
vector<Mat> ImportImages(string folder);
Mat DifferenceStack(vector<Mat>& images);
rval CalculateTemplate();
Mat Reconstructor(Mat& input_image, int zslice);
Mat Reconstructor(Mat& image, int zslice, Mat& cleaner);
Mat linspace(float start, float end, int n);
void PlotFrame(Mat& image, string title);