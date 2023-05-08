#include "header.hpp"

using namespace std;
using namespace cv;



Mat DifferenceStack(vector<Mat>& images)
{
    if(verbose) cout << "------------------ Difference Stack -----------------" << endl;

    Mat temp = Mat::zeros(images[0].size(), CV_32F);
    Mat temp1 = Mat::zeros(images[0].size(), CV_32F);
    Mat temp2 = Mat::zeros(images[0].size(), CV_32F);

    if(verbose) cout << "    temp size:  " << temp2.rows << " x " << temp2.cols << " x " << temp2.channels() << endl;
    if(verbose) cout << "    image size: " << images[0].rows << " x " << images[0].cols << " x " << images[0].channels() << endl;

    for(int i = 0; i < images.size() - 1; i += 2)
    {
        temp += (images[i + 1] - images[i]);
    }
    
    if(verbose) cout << "Calculated difference stack (size: " << temp2.rows << " x " << temp2.cols << " x " << temp2.channels() << ")" << endl;
    if(verbose) cout << "-----------------------------------------------------" << endl;

    return temp;
}