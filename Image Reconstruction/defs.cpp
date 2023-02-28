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
int Sn_pixels       = 3000;
int OVS             = 2;
float wavelength    = 405e-9;
float pixel_p       = 1.85e-6/OVS;
int n_pixels        = Sn_pixels*OVS;
float ref_dist      = 12e-3;
float samp_dist     = 8.14e-3;
float temp_dist     = samp_dist; // <- Change this to recalculate templates at varying z-depth
float ref_amp       = 1;
float ref_pos_x     = 0;
float ref_pos_y     = 0;
float obj_amp       = 0.01;
double pi           = acos(-1);
complex<float> I(0, 1);
bool verbose = true;
string optput_folder = "";

// Region of interest values:

#endif