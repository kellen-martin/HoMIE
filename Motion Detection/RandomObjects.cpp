////////////////////////////////////////////
////////////////////////////////////////////
// Creates a set of poistions for objects
////////////////////////////////////////////
////////////////////////////////////////////

#include<iostream>
#include<opencv2/opencv.hpp>
#include<random>
#include<vector>
#include "RandomDirection.cpp"

using namespace std;
using namespace cv;

void RandomObject(int ObjectNumber, vector<Point3d> &positions, vector<double> &areas){
    // define variables and limits
    int frames = 20; 
    int n = 0;
    double speed_min = 1;
    double speed_max = 4;
    double speed;
    double area_min = 1;
    double area_max = 4; 
    double xlim = 500;
    double ylim = 500;
    double zlim = 500;
    int straight_percent = 10;
    int number;
    bool straight; 
    Point3d direction;
    Point3d random_position;
    Point3d new_position;

    srand(time(0));
    for(int i = 0; i<ObjectNumber; i++){

        // decide if object moves in straight line
        number = rand() % 101;
        if(straight_percent>=number){straight = true; RandomDirection(direction);}
        else{straight = false;}


        areas.push_back(area_min + area_max*(double)(rand()) / (RAND_MAX));
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