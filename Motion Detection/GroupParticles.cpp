////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// Group positions into individual objects
////////////////////////////////////////////////////////////////
// inputs:
//      particles - set off all positions 
//      Objects - pass by refence to a vector of the custom class object
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
# include "FindSearchRadius.cpp"

const int frame_rate  = 100;

class object{
    public:
    vector<Point3d> positions();           // List of an object's postions 
    double size;                           // Size of the object
    double linearity;                      // How linear is the objects movements 
    bool flag;                             // Does the object meet linearity threshold
};

void GroupParticles( vector<Point3d> positions, vector<object> &Objects){
    double sr_margin = 1;      // Expands search radius by this amount
    int n = 0;                 // object iterator
    
    // define the first position of the object
    object Object; 
    Object.positions[0] = positions[0];
    // vector<Point3d>::iterator = positions.begin();
    positions.erase(0);

    // Runs if there are still particles to check
    while( positions.empty() == false){
        // Find the search radius 
        double search_radius = FindSearchRadius(Object.positions[0], positions);
        search_radius *= sr_margin; 

        // Connect the dots
        bool complete = false;
        while(complete == false){

            // Check for positions within search radius
            int checked = 0; 
            int j = positions.size();
            int n = 1;

            for(int i = 0; i<j; i++){
                double dx = Object.positions[0].x - positions[i].x;
                double dy = Object.positions[0].y - positions[i].y;
                double dz = Object.positions[0].z - positions[i].z;
                if (dx < search_radius && dy < search_radius && dz < search_radius) {
                    double distance = EuclidianDistance(dx, dy, dz);
                    if(distance <= search_radius) {Object.positions[n] = positions[i]; n += 1; positions.erase(i);}
                }

            }

            checked += 1;
            if(checked == n){complete == true;}
        }
    Objects[n] = Object; 
    }
}