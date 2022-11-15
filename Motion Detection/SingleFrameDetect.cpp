////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// Counts and Marks Objectss in a single frame reconstruction
// (currently a test of several different object detection methods)
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
Mat img = imread(img_path);

////////////// Blob Detection  /////////////////////////////////
// Setup blob detector with default parameters
SimpleBlobDetector::Params params;

params.filterByArea = true;
params.minArea = 1; 

Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params); 

// Detect
vector<KeyPoint> keypoints; 
detector->detect(img, keypoints);

// image with markers 
Mat blobs;
drawKeypoints(img, keypoints, blobs, Scalar(0,0,225), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

////////////// Edge Detection /////////////////////////////////
// Blur image (better edge detection)
Mat img_blur;
GaussianBlur(img, img_blur, Size(3,3), 0, 0, BORDER_DEFAULT);

// Sobel Edge Detection
Mat sobel;
Sobel(img_blur, sobel, CV_64F, 1, 1, 5);

// Canny Edge Detection
Mat canny;
Canny(img_blur, canny, 100, 200, 3, false);

///////////// Contour Detection ////////////////////////////////
// Currently uses the canny edge detection, another option is to binarize the image

// Set up vectors
vector<vector<Point>> contours;
vector<Vec4i> hierarchy;

// Find Contours
findContours(canny, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);

// draw contours
Mat img_cont = img.clone();
drawContours(img_cont, contours, -1, Scalar(0,255,0), 2);

// Mark Objects

// Count objects

// Save Images with markers 
imwrite("/home/kells/HoMIE/Motion Detection/blob.png", blobs);
imwrite("/home/kells/HoMIE/Motion Detection/blur.png", img_blur);
imwrite("/home/kells/HoMIE/Motion Detection/sobel_edges.png", sobel);
imwrite("/home/kells/HoMIE/Motion Detection/canny_edges.png", canny);
imwrite("/home/kells/HoMIE/Motion Detection/cont.png", img_cont);
}

// test of SingleFrameDetect 
int main(){
string img_path = "unnamed.png";
SingleFrameDetect(img_path);
return 0;
}