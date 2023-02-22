# include <iostream>
# include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

class object
{
    public:
    vector<Point3d> positions; // List of an object's positions in time
    double linearity;          // How linear is the set of positions
    bool thresh;               // Does object meet brownian linearity threshhold   
};
