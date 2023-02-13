////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// Finds a point's nearest neighbor
////////////////////////////////////////////////////////////////
// inputs:
//      particle_number - index of main point
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

double FindSearchRadius(int particle_number, vector<Point3d> particles) {

    // pre-deffine a minimum radius
    double min_radius = 10000000; 

    // 
    for(int i = 0; i < particles.size(); i++){
        double dx = particles[particle_number].x - particles[i].x;
        double dy = particles[particle_number].y - particles[i].y;
        double dz = particles[particle_number].z - particles[i].z;
        if (i != particle_number && dx < min_radius && 
                                    dy < min_radius && 
                                    dz < min_radius) {
            double distance = EuclidianDistance(dx, dy, dz);
            if(distance < min_radius) {min_radius = distance};
            }
    }
    return min_radius;
}

void main(){
    vector<Point3d> particles(10);
    vector<double> xs(10) = [5 0 2 4 2 0 3 2 3 4];
    vector<double> ys(10) = [3 5 6 9 2 1 1 3 4 5];
    vector<double> zs(10) = [4 5 3 2 3 6 6 8 2 1];


    for(int i; i<10; i++){
        particles[i].x = xs[i];
        particles[i].y = ys[i];
        particles[i].z = zs[i];
    }

    double sr = FindSearchRadius(2, particles);
}