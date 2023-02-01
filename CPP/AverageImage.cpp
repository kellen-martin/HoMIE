#include "header.hpp"

using namespace std;
using namespace cv;


// Average image can be called with 1 or 3 arguments still:

Mat AverageImage(vector<Mat>& images, int first, int last)
{
    // FIRST AND LAST INDEXES MUST BE ZERO BASED
    
    if(verbose) cout << "------------------- Average Image -------------------" << endl;

    int sizeOf = images.size();         // total number of images in set
    int stop = min(last, sizeOf - 1);   // maximum index allowable
    int n = stop - first + 1;           // total images being averaged
    
    Mat z = Mat::zeros(images[0].size(), CV_32F); // accumulator

    for(int i = first; i <= stop; i++)
    {   
        z += images[i];
    }

    if(verbose) cout << "Averaged " << n << "images (frames " << first << " to " << last << ")" << endl;
    if(verbose) cout << "-----------------------------------------------------" << endl;

    return z / n;
}



Mat AverageImage(vector<Mat>& images)
{    
    int sizeOf = images.size();     // total number of images in set
    
    if(verbose) cout << "------------------- Average Image -------------------" << endl;
    
    Mat z = Mat::zeros(images[0].size(), CV_32F);

    for(int i = 0; i < sizeOf; i++)
    {
        z += images[i];
    }

    if(verbose) cout << "Averaged " << sizeOf << " images"  << endl;
    if(verbose) cout << "-----------------------------------------------------" << endl;

    return z / sizeOf;
}