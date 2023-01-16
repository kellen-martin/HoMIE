#include "header.hpp"

int main()
{
    string commandFilename = "Commands.txt";
    string outputFilename = "MicroscopeOutput.txt";

    vector<image_set> MEMORY; // just a variable called memory for now, basically represents bulk storage

    // can just use MATLAB to generate data if we need, then use the images here
    string folder = "GeneratedData3b";
    vector<Mat> images = ImportImages(folder);

    // Average images
    Mat avgImg = AverageImage(images);
    // put a call to plotframe here to mirror matlab code
    // plot "Raw Frame 1"

    Mat diffStack = DifferenceStack(images);
    // another call to plotFrame
    // plot "Raw Difference Stack"

    Mat recon = Reconstructor(diffStack, 1);
    // call plotFrame here
    // plot "Reconstructed Image"



    // vector<string> commands;

    // readCommands(&commands, commandFilename);
    // loop through commands and do desired calculations

    return 0;
}


