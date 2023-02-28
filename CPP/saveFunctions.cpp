#include "header.hpp"
#include "dtypes.cpp"

using namespace std;
using namespace cv;

void saveRealMat(const cv::Mat_<float>& mat, const std::string& filename, const int rows, const int cols) 
{
    if(verbose) cout << "saving image ...   ";
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                file << mat(i, j) << " ";
            }
            file << std::endl;
        }
        file.close();
    }
    if(verbose) cout << " done." << endl;
}

void saveComplexMat(const cv::Mat_<std::complex<float>>& complexMat, const std::string& filename, const int rows, const int cols) 
{
    if(verbose) cout << "saving image ...   ";
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                file << complexMat(i, j).real() << " " << complexMat(i, j).imag() << " ";
            }
            file << std::endl;
        }
        file.close();
    }
    if(verbose) cout << " done." << endl;
}