# include <iostream>
# include <opencv2/opencv.hpp>
# include <cmath>
# include <vector> 
# include "EuclidianDistance.cpp"

using namespace std;
using namespace cv;

double CalculateLinearity(vector<Point3d> positions){
    double linearity;
    Point3d direction_2;
    double sum = 0;

    Point3d direction;
    direction = positions[0] - positions[1];
    double magnitude = EuclidianDistance(direction.x, direction.y, direction.z);
    direction = direction/magnitude;

    for(int i = 2; i<positions.size(); i++){
        direction_2 = positions[0] - positions[i];
        magnitude = EuclidianDistance(direction_2.x, direction_2.y, direction_2.z);
        direction_2 = direction_2/magnitude;
        sum = sum + abs(direction.ddot(direction_2));
    }

    linearity = sum/(double)(positions.size()-2);

    return linearity;
}

////// Test of CalculateLinearity //////
/*
int main(){
    vector<Point3d> positions(4);
    double linearity;

    positions[0] = {0,4,0};
    positions[1] = {0,-5,0};
    positions[2] = {0,50,0};
    positions[3] = {0,30,0};

    linearity = CalculateLinearity(positions);

    cout<< linearity << endl;
    return 0;
}
*/