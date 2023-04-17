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
# include <vector> 
# include <iterator>
# include "EuclidianDistance.cpp"
# include "FindSearchRadius.cpp"
# include "ContourDetect.cpp"
# include "RemoveElements.cpp"

const int frame_rate  = 100;

class object{
    public:
    double size;                           // Size of the object
    double linearity;                      // How linear is the objects movements 
    bool flag;                             // Does the object meet linearity threshold
    vector<Point3d> positions;             // List of an object's postions 
};

void GroupParticles( vector<Point3d> positions, vector<double> areas, vector<object> &Objects){
    // Variable definitions and initialization
        // area filter variables
        double area_margin = 1.3;  // sets bound for exceptable particle areas
        double area_min;           // minimum allowable area = area/margin
        double area_max;           // maximum allowable area = area*margin

        // iterators and bool variables
        int o = 0;                 // object iterator
        bool complete;             // marks the completion of an object(is true when all of an object's positions have been checked)
        int checked;               // the number of positions that have been checked
        int n;                     // object position iterator
        vector<int> remove;        // vector of indicies to be removed

        // distance variables
        double search_radius;      // search radius based on object's neareats neighbor
        double sr_margin = 1.3;    // Expands search radius by this amount
        double distance;           // distance between two positions
        double dx;                 // difference between x positions
        double dy;                 // difference between y positions
        double dz;                 // difference between z positions

    while(positions.empty() == false){
        // define the first position and area of the object
        Objects[o].size = areas[0];
        Objects[o].positions.push_back(positions[0]);
        
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
            // check for positions within search radius of similar size
            for(int i = 0; i<positions.size(); i++){
                // check for size
                if(areas[i] < area_max && areas[i] > area_min){
                    // calculate distances
                    dx = Objects[o].positions[checked].x - positions[i].x;
                    dy = Objects[o].positions[checked].y - positions[i].y;
                    dz = Objects[o].positions[checked].z - positions[i].z;

                    // check if distance in one direction is greater that search radius
                    if (dx < search_radius && dy < search_radius && dz < search_radius) {
                        // calculate distance
                        distance = EuclidianDistance(dx, dy, dz);

                        // add position to object  and remove from list if within searh radius
                        if(distance <= search_radius) {
                            Objects[o].positions.push_back(positions[i]); 
                            n += 1; 
                            // add index to positions to be removed
                            remove.push_back(i);
                        }
                    }
                }
            }

            // remove positions and areas
            RemoveElements(remove, positions, areas);

            // erase all elements of remove vector
            remove.clear();
            
            // increment number of object positons checked 
            checked += 1;

            // if every object position has been checked end loop
            if(checked == n){
                complete = true;
                }
        } 
        o += 1;
    }
}

// test of GroupParticles
int main(){
    
    // contour detection
    vector<Point2d> locations;
    vector<double> areas;
    string img_path = "unnamed.png";
    
    
    ContourDetect(img_path, locations, areas); 
    

    //cout << locations.size() << endl;
    //cout << "test";
    vector<Point3d> positions(locations.size());

    for(int i = 0; i<locations.size(); i++){
        positions[i].x = locations[i].x;
        positions[i].y = locations[i].y;
        positions[i].z = 0;
        //cout << positions[i].x << " " << positions[i].y << " "<< positions[i].z << endl;
        //cout << areas[i] << endl;
    }

    vector<object> Objects(16);

    GroupParticles(positions, areas, Objects);


    for(int i = 0; i < Objects.size(); i++){
        cout << Objects[i].positions.size() << endl;
    }
    

    for(int i = 0; i<Objects[2].positions.size(); i++){
        cout << "Position " << i << " x: " << Objects[2].positions[i].x << " y: " << Objects[2].positions[i].y << " z: " << Objects[2].positions[i].z << endl;
    }

    return 0;
    
}