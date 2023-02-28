#ifndef TYPES_CPP
#define TYPES_CPP

#include "header.hpp"

using namespace std;
using namespace cv;


struct settings
{
    int FPS;
    // include other settings here or just have FPS as a field of image_set

    // settings(int FPS); // constructor function, initiate a settings variable
    // ^^^^ will have to make a constructor for image_set to call this if we want to
};

struct image_set
{
    // Holds all images taken in one go
    string ID;                      // ID to reference data
    vector<Mat> frames;             // vector of hologram images
    vector<string> movementFlags;   // vector containing any movement flags
    settings sensorSettings;        // settings struct with info on image sensor settings for images
};

struct rval
{
    // return value for calculating template and reference waves
    Mat template_wave;
    Mat ref_wave;
};


#endif