# include <iostream> 
# include <opencv2/opencv.hpp>
# include <vector>
# include <algorithm>

using namespace std;
using namespace cv;

void RemoveElements(vector<int> remove, vector<Point3d> &positions, vector<double> &areas){
    // Reorder remove to be in decending order
    sort(remove.rbegin(), remove.rend());

    // recast remove vector to size_t
    vector<size_t> size_t_remove(remove.begin(), remove.end());

    // Erase position elements
    for(const auto& index : size_t_remove){
        positions.erase(positions.begin() + index);
        areas.erase(areas.begin() + index);
    }
}

/*
// test for RemovePositions
int main(){
    vector<Point3d> positions(3);

    positions[0].x = 1;
    positions[0].y = 1;
    positions[0].z = 1;
    positions[1].x = 2;
    positions[1].y = 2;
    positions[1].z = 2;
    positions[2].x = 3;
    positions[2].y = 3;
    positions[2].z = 3;

    // we want to remove 1st and last position
    vector<int> remove = {0, 2};

    // Remove Positions
    RemovePositions(remove, positions);

    cout << "The length of the vector is " << positions.size() << endl;
    cout << "The element remaining is " << positions[0].x << endl;
    return 0;
}
// the output should be
// The length of the vector is 1
// The element remaining is 2
*/


