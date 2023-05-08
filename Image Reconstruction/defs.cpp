#pragma once
#ifndef DEFS_CPP
#define DEFS_CPP

#include "header.hpp"

using namespace std;
using namespace cv;

/////////////////////////// GLOBALS DEFINITIONS /////////////////////////////////////

// Microscope specs and physical dimensions:
float Zheight       = 2e-3;
float z_resolution  = 2e-6;
int Sn_pixels       = 2048;
int OVS             = 6;
float wavelength    = 405e-9;
float pixel_p       = 5.5e-6/OVS;
// float pixel_p       = 1.85e-6/OVS;
int n_pixels        = Sn_pixels*OVS;
int num_tiles       = 1;
float ref_dist      = 21e-3;
float samp_dist     = 18.5e-3;
float temp_dist     = samp_dist; // <- Change this to recalculate templates at varying z-depth
float ref_amp       = 1;
float ref_pos_x     = 0;
float ref_pos_y     = 0;
float obj_amp       = 0.01;
double pi           = acos(-1);
complex<float> I(0, 1);
bool verbose = false;
string optput_folder = "";
int n_threads = 4;

#endif