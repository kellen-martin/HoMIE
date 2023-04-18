//////////////////////////////////////////////
//////////////////////////////////////////////
// Motion Detection Functional Test
/////////////////////////////////////////////
/////////////////////////////////////////////

#include <iostream>
#include <opencv2/opencv.hpp>
#include "GroupParticles.cpp"
#include "RandomObjects.cpp"
#include "CalculateLinearity.cpp"

using namespace std;
using namespace cv;

int main(){
    // set number of objects, we will be increasing particle density
    int Object_Number = 50;

    // create set of positions and areas
    vector<Point3d> positions;
    vector<double> areas;

    RandomObject(Object_Number, positions, areas);

    // give to GroupParticles
    vector<object> Objects(Object_Number);
    GroupParticles(positions, areas, Objects);

    // calculate linearity
    for(int i = 0; i<Object_Number; i++){
        Objects[i].linearity=CalculateLinearity(Objects[i].positions);
        if(Objects[i].linearity <= Objects[i].threshold){
            Objects[i].flag = true;
            cout << "Object number "<< i << endl;
            cout << "Linearity "<< endl;
            for(int j = 0; j<Objects[i].positions.size(); j++){
                cout << "x: " << Objects[i].positions[j].x << "y: " << Objects[i].positions[j].y <<"z: " << Objects[i].positions[j].z << endl << endl;

            }
        }
    }

}