////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// Calculates the distance between 2 points in three dimensions
////////////////////////////////////////////////////////////////
// inputs:
//      dx - x distance
//      dy - y distance
//      dz - z distance
////////////////////////////////////////////////////////////////
// outputs:
//      distance - distance between the points
////////////////////////////////////////////////////////////////
// Author(s):
//      Kellen Martin
// 
// Last Edited: 2/13/23
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


# include <iostream>
# include <opencv2/opencv.hpp>
# include <cmath>

using namespace std;
using namespace cv;

double EuclidianDistance(double dx, double dy, double dz) {
// distance equation
double distance;
distance = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));

return distance;

}

int main() {
    Point3d point_1, point_2;
    point_1.x = 3;
    point_1.y = 6;
    point_1.z = 4;

    point_2.x = 7;
    point_2.y = 1;
    point_2.z = 9;

    double dx = point_1.x - point_2.x;
    double dy = point_1.y - point_2.y;
    double dz = point_1.z - point_2.z;

    double dist;
    dist = EuclidianDistance(dx, dy, dz);
    cout << "The distance is " << dist << endl;

    // if this works the output should be 8.12404
return 0; 
}