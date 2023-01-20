#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// This scirpt is to test the installation of openCV by testing imread and imshow
int main() {
    // Defines image loaction
    string path = "../generateData1/simulated_hologram1.png";
    
    // Reads Image 
    Mat img = imread(path);

    // saves test image
    imwrite("/home/kells/HoMIE/Motion Detection/test.png", img);
    return 0;
}
