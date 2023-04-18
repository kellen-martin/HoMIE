////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// Creates a position vector of objects moving in straight line
// and random motion
////////////////////////////////////////////////////////////////
// inputs:
//      positions - set off all positions 
//      areas - set of all object areas
////////////////////////////////////////////////////////////////
// outputs:
////////////////////////////////////////////////////////////////
// Author(s):
//      Kellen Martin
// 
// Last Edited: 4/18/23
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

#include<iostream>
#include<opencv2/opencv.hpp>
#include<random>
#include<vector>
#include "RandomDirection.cpp"

using namespace std;
using namespace cv;

void RandomObject(int ObjectNumber, vector<Point3d> &positions, vector<double> &areas){
    // define variables and limits
    int frames = 20;        // number of frames
    int n = 0;              // positions vector iterator

    // Object speed bounds [distance/frame]
    double speed_min = 1;   // Min object speed
    double speed_max = 4;   // Max object speed
    double speed;

    // Area Limits
    double area_min = 1;    // Minumum object size
    double area_max = 4;    // Maximum object size
    double area;            // temperary area variable

    // Area limits based on sample volume dimensions
    double xlim = 500;      // sample volume length
    double ylim = 500;      // sample volume width
    double zlim = 500;      // sample volume height

    // Variables for chosing motion type
    int straight_percent = 10;  // percent of objects that will move in straight lines
    int number;                 // random number to decide movement type
    bool straight;              // true is object moves straight

    // Movement and position variables
    Point3d direction;          // determines the direction an object will move
    Point3d random_position;    // denotes the starting position
    Point3d new_position;       // denotes an objects updated position

    // Seed rand 
    srand(time(0));

    // Generate position list
    for(int i = 0; i<ObjectNumber; i++){

        // decide if object moves in straight line
        number = rand() % 101;
        if(straight_percent>=number){straight = true; RandomDirection(direction);}
        else{straight = false;}

        // Determine object's area an speed
        area = area_min + area_max*(double)(rand()) / (RAND_MAX);
        areas.push_back(area);
        speed = speed_min + speed_max*((double)(rand()) / (RAND_MAX));

        // generate starting point
        random_position.x = xlim*((double)(rand()) / (RAND_MAX));
        random_position.y = ylim*((double)(rand()) / (RAND_MAX));
        random_position.z = zlim*((double)(rand()) / (RAND_MAX));
        positions.push_back(random_position);
        if(i != 0){n++;}

        // generate subsequent points
        // for an object moving in linearly
        if(straight == true){
            cout << "Straight" << endl;
            for(int j = 0; j<frames-1; j++){
                new_position = positions[n] + speed*direction;
                positions.push_back(new_position);
                areas.push_back(area);
                n++;
            }
        }
        // for an object moving randomly
        else{
            cout << "Random" << endl;
            for(int j = 0; j<frames-1; j++){
                RandomDirection(direction);
                new_position = positions[n] + speed*direction;
                positions.push_back(new_position);
                areas.push_back(area);
                n++;
            }
        }
    }
}

////// Test of RandomObjects //////
/*
int main(){
    int Object_number = 1000;
    vector<Point3d> positions;
    vector<double> areas;

    RandomObject(Object_number, positions, areas);
    cout << positions.size() << endl;
    for(int i = 0; i<positions.size(); i++){
        cout << "x: " << positions[i].x<< " y: "<<positions[i].y<< " z: " << positions[i].z << endl; 
    }

    return 0;
}
*/