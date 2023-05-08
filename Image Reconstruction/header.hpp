#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <dirent.h>
// #include <map>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <complex>
#include <omp.h>
#include "dtypes.cpp"

using namespace std; // using std and cv namespaces (avoid std:: and cv::)
using namespace cv;

#ifndef HEADER_FILE_H
#define HEADER_FILE_H // only defining things in header file once

/////////////////////////// GLOBALS DEFINITIONS /////////////////////////////////////

// Microscope specs and physical dimensions:
extern float Zheight;
extern float z_resolution;
extern int Sn_pixels;
extern int OVS;
extern float wavelength;
extern float pixel_p;
extern int n_pixels;
extern int num_tiles;
extern float ref_dist;
extern float samp_dist;
extern float temp_dist; // <- Change this to recalculate templates at varying z-depth
extern float ref_amp;
extern float ref_pos_x;
extern float ref_pos_y;
extern float obj_amp;
extern double pi;
extern complex<float> I;
extern bool verbose;
extern string output_folder;
extern int n_threads;

////////////////////////////////////////////////////////////////////////////////////////////////


// Functions :

void readCommands(vector<string>& commands, string commandFilename);
Mat AverageImage(vector<Mat>& images, int first, int last);
Mat AverageImage(vector<Mat>& images);
void ImportImages(vector<Mat>& images, string folder);
Mat DifferenceStack(vector<Mat>& images);
rval CalculateTemplate();
Mat Reconstructor(Mat& input_image, int zslice);
// Mat Reconstructor(Mat& image, int zslice, Mat& cleaner);
Mat Reconstructor_Kanka(Mat& input_image, int zslice);
Mat Reconstructor_Kanka(Mat& input_image, vector<int> zslice);
Mat Reconstruct_tile(Mat& input_image, Mat& ref_wave, Mat& template_wave, Mat& apodizer);
// Mat Reconstructor_Kanka(Mat& image, int zslice, Mat& cleaner);
void linspace(float start, float end, int n, Mat* dest);
void PlotFrame(Mat& image, string title);
void PlotFrame(Mat& image, string title, bool ROI);
void PlotFrame(Mat& image, string title, string filename);
void PlotFrame(Mat& image, string title, string filename, bool ROI);
void PlotFrame(Mat& image, string title, string filename, bool ROI, bool SAVE_ONLY);
void saveRealMat(const cv::Mat_<float>& mat, const string& filename, const int rows, const int cols);
void saveComplexMat(const cv::Mat_<std::complex<float>>& complexMat, const string& filename, const int rows, const int cols);

#endif