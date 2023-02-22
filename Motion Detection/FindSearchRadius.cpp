////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// Finds a point's nearest neighbor
////////////////////////////////////////////////////////////////
// inputs:
//      position  - position of particle whose sr you are finding
//      particles - set off all positions 
////////////////////////////////////////////////////////////////
// outputs:
//      radius - the distance to he nearest point 
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
# include "EuclidianDistance.cpp"

using namespace std;
using namespace cv;

double FindSearchRadius(Point3d position, vector<Point3d> particles) {

    // pre-deffine a minimum radius
    double search_radius = 10000000; 

    // 
    for(int i = 0; i < particles.size(); i++){
        double dx = position.x - particles[i].x;
        double dy = position.y - particles[i].y;
        double dz = position.z - particles[i].z;
        if (dx < search_radius && dy < search_radius && dz < search_radius) {
            double distance = EuclidianDistance(dx, dy, dz);
            if(distance < search_radius){
                search_radius = distance;
            }
            }
    }
    return search_radius;
}

int main(){
    vector<Point3d> particles(10);
    vector<double> xs(10);
    vector<double> ys(10);
    vector<double> zs(10);
    

    for(int i; i<10; i++){
        particles[i].x = xs[i];
        particles[i].y = ys[i];
        particles[i].z = zs[i];
    }

    double sr = FindSearchRadius(particles[1], particles);

}