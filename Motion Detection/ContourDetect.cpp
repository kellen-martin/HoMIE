////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// Finds particle locations and areas in a single z-slice
////////////////////////////////////////////////////////////////
// inputs:
//      img_path - path to image
////////////////////////////////////////////////////////////////
// outputs:
//      areas     - areas of contours
//      locations - coordinates of objects
////////////////////////////////////////////////////////////////
// Author(s):
//      Kellen Martin
// 
// Last Edited: 4/5/23
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

# include <iostream>
# include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void ContourDetect(string img_path, vector<Point2d> &locations, vector<double> &areas) {
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

// Output object locations
locations.resize(contours.size());
areas.resize(contours.size());

for(int i = 0; i < contours.size(); i++){
    const Moments mu = moments(contours[i], false);
    areas[i] = contourArea(contours[i]);
    locations[i] = Point2d(mu.m10 / mu.m00, mu.m01 / mu.m00);
}


}

///////////// test of SingleFrameDetect ////////////////////////////////////////////////////////////
/*int main(){
string img_path = "unnamed.png";
vector<Point2d> locations;
vector<double> areas;

ContourDetect(img_path, locations, areas);

cout << locations[2].x << " " << areas[2];
return 0;
}*/