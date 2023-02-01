#include "header.hpp"

using namespace std;
using namespace cv;



Mat DifferenceStack(vector<Mat>& images)
{
    if(verbose) cout << "------------------ Difference Stack -----------------" << endl;

    Mat temp = Mat::zeros(images[0].size(), CV_32F);

    for(int i = 0; i < images.size() - 1; i += 2)
    {
        temp += (images[i + 1] - images[i]);
    }
    
    if(verbose) cout << "Calculated difference stack (size: " << temp.rows << " x " << temp.cols << " x " << temp.channels() << ")" << endl;
    if(verbose) cout << "-----------------------------------------------------" << endl;

    return temp;
}