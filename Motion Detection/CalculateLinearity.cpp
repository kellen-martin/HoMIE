# include <iostream>
# include <opencv2/opencv.hpp>
# include <cmath>
# include <vector> 
# include "EuclidianDistance.cpp"

using namespace std;
using namespace cv;

double CalculateLinearity(vector<Point3d> positions){
    double linearity;

    Point3d direction;
    direction = positions[0] - positions[1];
    double magnitude = EuclidianDistance(direction.x, direction.y, direction.z);
    direction.x = direction.x/magnitude;
    direction.y = direction.y/magnitude;
    direction.z = direction.z/magnitude;

    

    return linearity;
}