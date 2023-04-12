#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <dirent.h>
#include <cmath>
#include <complex>
#include <omp.h>
#include <opencv2/opencv.hpp>
#include "loop_dtypes.cpp"

using namespace std;

#ifndef HEADER_H
#define HEADER_H


// globals declarations here: (as extern)
extern const string commandFile;

extern const int SETTINGS;
extern const int CAPTURE;
extern const int DETECT;
extern const int DATA;

extern const int DIFF_FRAME;
extern const int DIFF_STACK;
extern const int SINGLE_FRAME;

extern const int TYPE_RAW;
extern const int TYPE_AVG;
extern const int TYPE_CLEAN;

extern const int SAVE_FULL_ROI;
extern const int SAVE_DETECTED;

extern const int DATA_SUMMARY;
extern const int DATA_COMPRESSION;
extern const int DATA_COMP_EST;

extern const int NONE;


// function declarations here:

vector<command> loadCommands();


#endif