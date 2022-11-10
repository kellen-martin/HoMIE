////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// Counts and Marks Objectss in a single frame reconstruction
// (currently only works for a single z-slice, will be modified 
// for full z stack)
// (R-DIHM-FUNC-1.5)
////////////////////////////////////////////////////////////////
// inputs:
//      img_path - path to image
////////////////////////////////////////////////////////////////
// outputs:
//      object_count - the number of objects found in the frame
//      figure - reconstructed frame with objects marked
//      locations - coordinates of objects
////////////////////////////////////////////////////////////////
// Author(s):
//      Kellen Martin
// 
// Last Edited: 11/10/22
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

# include <iostream>
# include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void SingleFrameDetect(string img_path) {
// read image
Mat img = imread(img_path, IMREAD_GRAYSCALE);

// Blur image (better edge detection)
Mat img_blur;
GaussianBlur(img, img_blur, Size(3,3), 0, 0, BORDER_DEFAULT);

// Sobel Edge Detection
Mat sobel;
Sobel(img_blur, sobel, CV_64F, 1, 1, 5);

// Canny Edge Detection
Mat canny;
Canny(img_blur, canny, 100, 200, 3, false);

// Mark Objects

// Count objects

// Save Images with markers 
imwrite("/home/kells/HoMIE/Motion Detection/sobel_edges.png", sobel);
imwrite("/home/kells/HoMIE/Motion Detection/canny_edges.png", canny);
}

// test of SingleFrameDetect 
void main(){

}