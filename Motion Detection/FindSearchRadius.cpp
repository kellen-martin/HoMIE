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

double FindSearchRadius(vector<double> areas, vector<Point3d> particles, int particle_number, double area_margin) {

    // pre-deffine a minimum radius
    double search_radius = 10000000; 

    // define upper and lower area bounds
    double area_min = areas[particle_number]/area_margin;
    double area_max = areas[particle_number]*area_margin;

    double dx; double dy; double dz; double distance;

    // find the closest particle of similar area
    for(int i = 0; i < particles.size(); i++){
        if(areas[i] < area_max &&  areas[i] > area_min && i != particle_number){
            dx = particles[particle_number].x - particles[i].x;
            dy = particles[particle_number].y - particles[i].y;
            dz = particles[particle_number].z - particles[i].z;
            if (dx < search_radius && dy < search_radius && dz < search_radius) {
                distance = EuclidianDistance(dx, dy, dz);
                if(distance < search_radius){
                    search_radius = distance;
                }
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