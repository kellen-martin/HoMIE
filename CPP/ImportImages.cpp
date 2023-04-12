#include "header.hpp"

using namespace std;
using namespace cv;


// ImportImages only takes in folder name now, the 'inputs' variable contents are globals

void ImportImages(vector<Mat>& images, string folder)
{
    if(verbose)
    {
        cout << "------------------- Import Images -------------------" << endl;
    }

    DIR *dir;
    struct dirent *file; // pointer to a file or 'directory entry' within the folder

    if((dir = opendir(folder.c_str())) != NULL)
    { // if the folder opens

        if(verbose) cout << "folder opened" << endl;

        while((file = readdir(dir)) != NULL)
        { // while file points to an existing file

            string filename = file->d_name;

            if(filename.substr(filename.find_last_of(".") + 1) == "png")
            {
                
                if(verbose) cout << "'.png' file found (" << images.size() + 1 << ")" << endl;

                string filePath = folder + "/" + filename;
                Mat input_image = imread(filePath);
                Mat image;
                cvtColor(input_image, image, COLOR_BGR2GRAY);

                if(!image.empty())
                {
                    int rows = image.rows;
                    int col = image.cols;
                    int chan = image.channels();

                    if((Sn_pixels < rows) || (Sn_pixels < col))
                    {
                        image.convertTo(image, CV_32F);
                        images.push_back(image.rowRange(0, Sn_pixels).colRange(0, Sn_pixels).clone());
                        if(verbose) cout << "Resizing image (" << rows << " x " << col << " x " << chan << ")" << endl;
                    }
                    else
                    {
                        image.convertTo(image, CV_32F);
                        images.push_back(image.clone());
                        if(verbose) cout << "'loaded' image" << endl;
                    }

                }
                else
                {
                    cout << "Error loading image - file empty" << endl;
                }
            }else{
                if(verbose) cout << "'" << filename.substr(filename.find_last_of(".") + 1) << "' file found" << endl;
            }

        }

    }
    else
    {
        cout << "Could not open folder" << endl;
    }

    closedir(dir);

    if(verbose) cout << "Number of images found in '" << folder << "': " << images.size() << endl;
    
    if(verbose) cout << "-----------------------------------------------------" << endl;

    return;

}