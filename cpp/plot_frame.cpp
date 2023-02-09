#include <opencv2/opencv.hpp>
#include <iostream>

void plotFrame(const cv::Mat& image, const std::string& name)
{
    cv::Mat image_f;
    image.convertTo(image_f, CV_32F);
    cv::Mat sqrt_image;
    cv::sqrt(cv::abs(image_f), sqrt_image);
    cv::imshow(name, sqrt_image);
    cv::waitKey(0);
}