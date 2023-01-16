#include "header.hpp"

// Average image can be called with 1 or 3 arguments still:

Mat AverageImage(vector<Mat>& images, int first, int last)
{
    // FIRST AND LAST INDEXES MUST BE ZERO BASED
    
    int sizeOf = images.size();         // total number of images in set
    int stop = min(last, sizeOf - 1);   // maximum index allowable
    int n = stop - first + 1;           // total images being averaged
    
    Mat z = Mat::zeros(images[0].size(), CV_32F); // accumulator

    for(int i = first; i <= stop; i++)
    {
        z += images[i];
    }

    return z / n;
}



Mat AverageImage(vector<Mat>& images)
{    
    int sizeOf = images.size();     // total number of images in set
    
    Mat z = Mat::zeros(images[0].size(), CV_32F);

    for(int i = 0; i <= sizeOf; i++)
    {
        z += images[i];
    }

    return z / sizeOf;
}