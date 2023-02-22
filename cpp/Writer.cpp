#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

void Writer(Mat image, std::string name)
{
    Mat I, J;
    image.convertTo(I, CV_32F);
    sqrt(abs(I), I);
    double max_I;
    minMaxLoc(I, NULL, &max_I);
    J = I / max_I;
    J.convertTo(J, CV_8UC1, 255, 0);
    bitwise_not(J, J);
    Mat inverted_image = 255 - image;
    imwrite(name + ".png", J);
}