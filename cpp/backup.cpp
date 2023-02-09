#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <array>
#include <cmath>

#include "import_images.cpp"
#include "average_image.cpp"
#include "difference_stack.cpp"
#include "plot_frame.cpp"



int main()
{
    struct Inputs {
        double z_resolution = 2e-6;
        int Sn_pixels = 3000;
        int OVS = 2;

        double wavelength = 405e-9;
        double pixel_p = 1.85e-6 / 2; //... / OVS
        int n_pixels = 3000 * 2; //Sn_pixels * OVS
        double ref_dist = 12.0e-3;
        double samp_dist = 8.14e-3;
        int ref_amp = 1;
        int ref_pos_x = 0;
        int ref_pos_y = 0;
        double obj_amp = 0.01;
    };
    Inputs inputs;

    std::array<double, 2> ROI_x = {-5e-4, 5e-4};
    std::array<double, 2> ROI_y = {-5e-4, 5e-4};

    double ROI_x_pix_i = std::round(inputs.n_pixels/2 + ROI_x[0]/inputs.pixel_p);
    double ROI_x_pix_f = std::round(inputs.n_pixels/2 + ROI_x[1]/inputs.pixel_p);
    double ROI_y_pix_i = std::round(inputs.n_pixels/2 + ROI_y[0]/inputs.pixel_p);
    double ROI_y_pix_f = std::round(inputs.n_pixels/2 + ROI_y[1]/inputs.pixel_p);

    std::array<double, 2> ROI_x_pix = {ROI_x_pix_i,ROI_x_pix_f};
    std::array<double, 2> ROI_y_pix = {ROI_y_pix_i,ROI_y_pix_f};
    std::cout << "Y pix" << ROI_x_pix[0] << "," << ROI_x_pix[1] << "/n";
    std::cout << "Y pix" << ROI_y_pix[0] << "," << ROI_y_pix[1] << "/n";

    std::string directory;
    std::cout << "Enter the directory containing the images: ";
    //std::cin >> directory;
    directory = "../holograms/generatedData3b";
    std::vector<cv::Mat> images = importImages(directory,inputs.Sn_pixels);
    
    cv::Mat avg = averageImage(images);
    cv::imshow("Average Image", avg);
    cv::waitKey(0);
    
    cv::Mat diffStack = differenceStack(images);
    cv::imshow("Difference Stack", diffStack);
    cv::waitKey(0);
    
    plotFrame(avg,"average image");
}