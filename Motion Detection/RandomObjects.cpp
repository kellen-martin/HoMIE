////////////////////////////////////////////
////////////////////////////////////////////
// Creates a set of poistions for objects
////////////////////////////////////////////
////////////////////////////////////////////

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
unsing namespave cv;

void RandomObject(int ObjectNumber, vector<Point3d> positions, vector<double> areas){
    // define variables and limits
    int frames = 20; 
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

    for(int i = 0; i<ObjectNumber, i++){
        // decide if object moves in straight line
        int number = rand() % 101;
        if(straight_percent<=number){straight = true;}
        else{straight = false;}


        areas.pushback(area_max*(float)(rand) / (float)(RAND_MAX));
        speed = speed_min + speed_max*((float)(rand) / (float)(RAND_MAX));

        // generate starting point

        // generate subsequent points
        for(int j = 0: j<frames, j++){

        }
    }
}