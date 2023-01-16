#include "header.hpp"


Mat DifferenceStack(vector<Mat>& images)
{
    Mat temp = Mat::zeros(images[0].size(), CV_32F);

    for(int i = 0; i < images.size() - 1; i += 2)
    {
        temp += (images[i + 1] - images[i]);
    }

    return temp;
}