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
// Last Edited: 5/10/23
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

# include <iostream>
# include <opencv2/opencv.hpp>
# include <cmath>
# include "EuclidianDistance.cpp"
# include "FindSearchRadius.cpp"
# include "ContourDetect.cpp"

const int frame_rate  = 100;

class object{
    public:
    vector<Point3d> positions;             // List of an object's postions 
    double size;                           // Size of the object
    double linearity;                      // How linear is the objects movements 
    bool flag;                             // Does the object meet linearity threshold
};

void GroupParticles( vector<Point3d> positions, vector<double> areas, vector<object> &Objects){
    // Variable definitions and initialization
        // area filter variables
        double area_margin = 1;    // sets bound for exceptable particle areas
        double area_min;           // minimum allowable area = area/margin
        double area_max;           // maximum allowable area = area*margin

        // iterators and bool variables
        int o = 0;                 // object iterator
        bool complete;             // marks the completion of an object(is true when all of an object's positions have been checked)
        int checked;               // the number of positions that have been checked
        int n;                     // object position iterator
        int j;                     // size of position vector

        // distance variables
        double search_radius;       // search radius based on object's neareats neighbor
        double sr_margin = 1;      // Expands search radius by this amount
        double distance;           // distance between two positions
        double dx;                 // difference between x positions
        double dy;                 // difference between y positions
        double dz;                 // difference between z positions

    while(positions.empty() == false){
        // define the first position and area of the object
        Objects[o].positions[0] = positions[0];
        Objects[o].size = areas[0];

        // Find the search radius 
        search_radius = FindSearchRadius(areas, positions, 0, area_margin);
        search_radius *= sr_margin;     

        // remove position from lists
        positions.erase(positions.begin());
        areas.erase(areas.begin());    

        // define upper and lower area bounds
        area_min = Objects[o].size/area_margin;
        area_max = Objects[o].size*area_margin;

        // initialize loop variables
        complete = false; 
        checked = 0;
        n = 1;

        // 'Connect the dots' 
        while(complete == false){
            // Check for positions within search radius
            j = positions.size();
        
            for(int i = 0; i<j; i++){
                if(areas[i] < area_max &&  areas[i] > area_min){
                    dx = Objects[o].positions[n-1].x - positions[i].x;
                    dy = Objects[o].positions[n-1].y - positions[i].y;
                    dz = Objects[o].positions[n-1].z - positions[i].z;
                    if (dx < search_radius && dy < search_radius && dz < search_radius) {
                        distance = EuclidianDistance(dx, dy, dz);
                        if(distance <= search_radius) {Objects[o].positions[n] = positions[i]; n += 1; positions.erase(positions.begin()+i);}
                    }
                }
            }

            checked += 1;
            if(checked == n){complete = true;}
        } 
        o += 1;
    }
}

// test of GroupParticles
void main(){
    // contour detection
    vector<Point2d> locations;
    vector<double> areas;
    string img_path = "unnamed.png";
    
    ContourDetect(img_path, locations, areas); 

    vector<Point3d> positions;

    for(int i = 0; i<locations.size(); i++){
        positions[i].x = locations[i].x;
        positions[i].y = locations[i].y;
        positions[i].z = 0;
    }

    vector<object> Objects;

    GroupParticles(positions, areas, Objects);
}