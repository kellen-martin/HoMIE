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
#include "Reconstructor_Kanka1.cpp"
#endif

using namespace std;
using namespace cv;

string output_folder = "../Output Images";

int main()
{       

    string commandFilename = "Commands.txt";
    string outputFilename = "MicroscopeOutput.txt";

    vector<image_set> MEMORY; // just a variable called memory for now, basically represents bulk storage
    vector<Mat> images;
    
    string input_folder = "../img-sample"; // path to folder from program location

    if(verbose) cout << endl;

    ImportImages(images, input_folder);

    if(verbose) cout << endl << "Returned to Main" << endl << endl;

    if(verbose) cout << "Image size: " << images[0].rows << " x " << images[0].cols << " x " << images[0].channels() << endl << endl;

    // Average images
    Mat avgImg = AverageImage(images);

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

    Mat diffStack = DifferenceStack(images);

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
    
    // Mat recon = Reconstructor_Kanka(diffStack, 1);
    Mat recon = Reconstructor(diffStack, 1);
    
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

    return 0;
}


