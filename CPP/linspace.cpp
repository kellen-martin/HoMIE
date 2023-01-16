#include "header.hpp"

Mat linspace(float start, float end, int n)
{
    float div = (end - start)/(n - 1);
    Mat mat = Mat::zeros(1, n, CV_32F);

    for(int i = 0; i < n; i++)
    {
        mat.at<float>(1,i) = start + i*div;
    }

    return mat;
}