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
    vector<Point3d> positions;             // List of an object's postions 
    double size;                           // Size of the object
    double linearity;                      // How linear is the objects movements 
    bool flag;                             // Does the object meet linearity threshold
};

void GroupParticles( vector<Point3d> positions, vector<double> areas, vector<object> &Objects){
    double sr_margin = 1;      // Expands search radius by this amount
    int o = 0;                 // object iterator
    
    // define the first position and area of the object
    Objects[o].positions[0] = positions[0];
    Objects[o].size = areas[0];

    // remove position from list
    positions.erase(positions.begin());
    areas.erase(areas.begin());

    // Runs if there are still particles to check
    while( positions.empty() == false){
        // Find the search radius 
        double search_radius = FindSearchRadius(Objects[o].positions[0], areas[0], areas, positions, 0);
        search_radius *= sr_margin; 

        // Definition of variables within loop
        bool complete = false;  // marks the completion of an object (true when each position has been checked)
        int checked = 0;        // the number of positions that have been checked
        int n = 1;              // object's position iterator
        int j;                  // length of overall position vector

        // define upper and lower area bounds
        double area_margin = 1;
        double area_min = Objects[o].size/area_margin;
        double area_max = Objects[o].size*area_margin;


        while(complete == false){
            // Check for positions within search radius
            j = positions.size();

            double dx; double dy; double dz;
        
            for(int i = 0; i<j; i++){
                if(areas[i] < area_max &&  areas[i] > area_min){
                    dx = Objects[o].positions[n-1].x - positions[i].x;
                    dy = Objects[o].positions[n-1].y - positions[i].y;
                    dz = Objects[o].positions[n-1].z - positions[i].z;
                    if (dx < search_radius && dy < search_radius && dz < search_radius) {
                        double distance = EuclidianDistance(dx, dy, dz);
                        if(distance <= search_radius) {Objects[o].positions[n] = positions[i]; n += 1; positions.erase(positions.begin()+i);}
                    }
                }
            }

            checked += 1;
            if(checked == n){complete = true;}
        } 
    }
}