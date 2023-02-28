#include "header.hpp"

using namespace std;
using namespace cv;


void linspace(float start, float end, int n, Mat* dest)
{
    if(verbose) cout << "  linspace....";
    float div = (end - start)/(n - 1);
    *dest = Mat::zeros(1, n, CV_32F);

    for(int i = 0; i < n; i++)
    {
        dest->at<float>(0,i) = start + i*div;
    }
    
    if(verbose) cout << "        ... done" << endl;

    return;

}