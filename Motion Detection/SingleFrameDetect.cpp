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
// Last Edited: 11/14/22
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

# include <iostream>
# include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void SingleFrameDetect(string img_path) {
// read image
Mat img = imread(img_path);

// Blur image (better edge detection)
Mat img_blur;
GaussianBlur(img, img_blur, Size(3,3), 0, 0, BORDER_DEFAULT);

// Canny Edge Detection
Mat canny;
Canny(img_blur, canny, 100, 200, 3, false);

// Set up vectors
vector<vector<Point>> contours;
vector<Vec4i> hierarchy;

// Find Contours
findContours(canny, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);

// draw contours
Mat img_cont = img.clone();
drawContours(img_cont, contours, -1, Scalar(0,255,0), 1);


// Count objects
cout << "Number of Particles: " << contours.size() << endl;

// Output object locations
vector<Point2d> mass_centers(contours.size());

for(int i = 0; i < contours.size(); i++){
    const Moments mu = moments(contours[i], false);
    mass_centers[i] = Point2d(mu.m10 / mu.m00, mu.m01 / mu.m00);
    cout << "center " << (i + 1) << ": " << mass_centers[i].x << " " << mass_centers[i].y << endl;
}


// Save Images with markers 
imwrite("/home/kells/HoMIE/Motion Detection/cont.png", img_cont);
}

// test of SingleFrameDetect 
int main(){
string img_path = "unnamed.png";
SingleFrameDetect(img_path);
return 0;
}