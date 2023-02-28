// #include "header.hpp"
#include "defs.cpp"
#include "dtypes.cpp"

#ifndef FUNCTION_HEADERS
#define FUNCTION_HEADERS
#include "saveFunctions.cpp"
#include "CalculateTemplate.cpp"
#include "AverageImage.cpp"
#include "DifferenceStack.cpp"
#include "ImportImages.cpp"
#include "linspace.cpp"
#include "PlotFrame.cpp"
#include "Reconstructor.cpp"
#include "dtypes.cpp"
#endif

using namespace std;
using namespace cv;


// Region of interest values:
// float ROI_x[2];
// float ROI_y[2];
// int ROI_x_pix[2];
// int ROI_y_pix[2];
string output_folder = "../Output Images";

int main()
{       
    // float ROI_x[2] = {-0.5*1e-3, 0.5*1e-3};
    // float ROI_y[2] = {-0.5*1e-3, 0.5*1e-3};
    // int ROI_x_pix[2] = {(int)n_pixels/2 + (int)(ROI_x[0]/pixel_p), (int)n_pixels/2 + (int)(ROI_x[1]/pixel_p)};
    // int ROI_y_pix[2] = {(int)n_pixels/2 + (int)(ROI_y[0]/pixel_p), (int)n_pixels/2 + (int)(ROI_y[1]/pixel_p)};

    string commandFilename = "Commands.txt";
    string outputFilename = "MicroscopeOutput.txt";

    vector<image_set> MEMORY; // just a variable called memory for now, basically represents bulk storage
    vector<Mat> images;
    
    // can just use MATLAB to generate data if we need, then use the images here
    string input_folder = "../img-sample"; // path to folder from program location

    if(verbose) cout << endl;

    ImportImages(images, input_folder);
    
    // PlotFrame(images[0], "TEST - NO ROI 1", "test1.png", false);
    // PlotFrame(images[1], "TEST - NO ROI 2", "test2.png", false);

    if(verbose) cout << endl << "Returned to Main" << endl << endl;

    if(verbose) cout << "Image size: " << images[0].rows << " x " << images[0].cols << " x " << images[0].channels() << endl << endl;

    // Average images
    Mat avgImg = AverageImage(images);
    // saveRealMat(avgImg, "../Output-Images/avgImg.txt", 3000, 3000);

    // if using first and last arguments to select a range, make indexes zero based
    
    if(verbose) cout << endl << "Returned to Main" << endl << endl;
    if(verbose) cout << "Average Image:" << endl;
    if(verbose) cout << "    " << avgImg.rows << " x " << avgImg.cols << " x " << avgImg.channels() << endl;
    if(verbose)
    {
        double max, min;
        Point minLoc, maxLoc;
        minMaxLoc(avgImg, &min, &max, &minLoc, &maxLoc);
        if(verbose) cout << "    max pixel value: " << max << endl;
        if(verbose) cout << "    min pixel value: " << min << endl << endl;
    }

    // PlotFrame(avgImg, "Average Image", "avgImg-test.png", false);

    // put a call to plotframe here to mirror matlab code
    // plot "Raw Frame 1"

    Mat diffStack = DifferenceStack(images);
    // another call to plotFrame
    // plot "Raw Difference Stack"
    // PlotFrame(diffStack, "Average Image", "dStack-test.png", false);
    // saveRealMat(diffStack, "../Output-Images/diffStack.txt", 3000, 3000);

    if(verbose) cout << endl << "Returned to Main" << endl << endl;
    if(verbose) cout << "Difference Stack:" << endl;
    if(verbose) cout << "    " << diffStack.rows << " x " << diffStack.cols << " x " << diffStack.channels() << endl;
    if(verbose)
    {
        double max, min;
        Point minLoc, maxLoc;
        minMaxLoc(diffStack, &min, &max, &minLoc, &maxLoc);
        if(verbose) cout << "    max pixel value: " << max << endl;
        if(verbose) cout << "    min pixel value: " << min << endl << endl;
    }

    Mat recon = Reconstructor(diffStack, 1);
    // call plotFrame here
    // plot "Reconstructed Image"
    
    if(verbose) cout << endl << "Returned to Main" << endl << endl;

    if(verbose)
    {   

        double max, min;
        Point minLoc, maxLoc;
        minMaxLoc(recon, &min, &max);

        cout << "  Reconstructed image: " << recon.rows << " x " << recon.cols << " x " << recon.channels() << endl;  
        cout << "    max pixel value: " << max << endl;
        cout << "    min pixel value: " << min << endl << endl;
    }
    
    saveComplexMat(recon, "../Output-Images/Mat.txt", 6000, 6000); 


    // if(verbose) cout << "Plotting frame: --------------" << endl;
    // PlotFrame(recon, "Reconstructed 4-frame difference stack", "test-diff.png", true, true);
    // if(verbose) cout << "------------------------------" << endl;



    // vector<string> commands;

    // readCommands(&commands, commandFilename);
    // loop through commands and do desired calculations

    return 0;
}


