#include <opencv2/opencv.hpp>

// Function to calculate the difference image from a vector of images
cv::Mat differenceStack(const std::vector<cv::Mat>& images)
{
    if (images.empty())
    {
        std::cout << "No images provided." << std::endl;
        return cv::Mat();
    }

    // Initialize difference image as the first image
    cv::Mat diff = images[0];

    // Subtract the second image from the first, and add the result to the difference image
    // Then subtract the fourth image from the third, and add the result to the difference image
    // And so on...
    for (int i = 0; i < images.size(); i += 2)
    {
        // Check if the images are empty
        if (images[i].empty() || images[i+1].empty())
        {
            std::cout << "You need an even number of images to find the difference stack." << std::endl;
            return cv::Mat();
        }

        diff += images[i+1] - images[i];
        std::cout << "Image" << i+1 << " - Image: " << i << std::endl;
    }

    return diff;
}