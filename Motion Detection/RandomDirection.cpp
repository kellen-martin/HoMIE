#include<iostream>
#include<opencv2/opencv.hpp>
#include<random>
#include<vector>

using namespace std;
using namespace cv;

void RandomDirection(Point3d &direction){
    direction.x = rand() % 10;
    direction.y = rand() % 10;
    direction.z = rand() % 10;
    double mag = sqrt(pow(direction.x, 2) + pow(direction.y,2) + pow(direction.z,2));
    direction = direction/mag;

}

////// Test of RandomDirection /////
/*
int main(){
    Point3d direction;
    RandomDirection(direction);

    cout << direction.x << " "<< direction.y << " "<< direction.z << endl;
    return 0;
}
*/