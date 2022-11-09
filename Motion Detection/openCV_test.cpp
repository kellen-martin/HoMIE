#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// This scirpt is to test the installation of openCV by testing imread and imwrite
int main() {
    // Defines image loaction
    string path = "../generatedData1/simulated_hologram1.png";

    // Reads Image 
    Mat img = imread(path, IMREAD_GRAYSCALE);

    // saves test image
    imwrite("/home/kells/HoMIE/Motion Detection/test.png", img);
    return 0;
}