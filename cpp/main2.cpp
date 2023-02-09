#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    // Load an image
    cv::Mat img = cv::imread("image.jpg", cv::IMREAD_COLOR);

    // Check if the image was loaded successfully
    if(img.empty())
    {
        std::cout << "Error: Image not found." << std::endl;
        return -1;
    }

    // Display the image
    cv::imshow("Image", img);
    cv::waitKey(0);

    return 0;
}
