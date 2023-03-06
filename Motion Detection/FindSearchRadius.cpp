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
# include <stdlib.h>
# include <time.h>

using namespace std;
using namespace cv;

double FindSearchRadius(Point3d position, vector<Point3d> particles, int particle_number) {

    // pre-deffine a minimum radius
    double search_radius = 10000000; 

    // 
    for(int i = 0; i < particles.size(); i++){
        double dx = position.x - particles[i].x;
        double dy = position.y - particles[i].y;
        double dz = position.z - particles[i].z;
        if (i != particle_number && dx < search_radius && dy < search_radius && dz < search_radius) {
            double distance = EuclidianDistance(dx, dy, dz);
            if(distance < search_radius){
                search_radius = distance;
            }
            }
    }
    return search_radius;
}

/* Test for FindSearchRadius
int main(){
   vector<Point3d> particles(3);
    

    for(int i = 0; i<3; i++){
        particles[i].x = rand() % 20;
        particles[i].y = rand() % 20;
        particles[i].z = rand() % 20;
        cout << particles[i].x << " " << particles[i].y << " "<< particles[i].z << endl;
    }

    double sr = FindSearchRadius(particles[1], particles, 1);

    cout << "The search radius is " << sr << endl;
} */