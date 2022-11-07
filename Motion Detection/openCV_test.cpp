#include <iostream>
#include <opencv-4.x/include/opencv2/opencv.hpp>

using namespace std;
using namespace cv ;

// This scirpt is to test the installation of openCV by testing imread and imshow
int main() {
    // Defines image loaction
    string path = "../generateData1/simulated_hologram1.png";

    // Reads Image 
    Mat img = imread(path);

    // Displays Image
    imshow("Image", img);

    return 0;
}
