#include <opencv2/opencv.hpp>

cv::Mat averageImage(const std::vector<cv::Mat>& images)
{
    if (images.empty())
    {
        std::cout << "No images provided." << std::endl;
        return cv::Mat();
    }

    // Initialize average image as the first image
    cv::Mat avg = images[0];

    // Add remaining images to the average image
    for (int i = 1; i < images.size(); i++)
    {
        avg += images[i];
    }

    // Calculate the average image
    avg /= images.size();

    return avg;
}
