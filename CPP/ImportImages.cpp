#include "header.hpp"

// ImportImages only takes in folder name now, the 'inputs' variable contents are globals

vector<Mat> ImportImages(string folder)
{
    DIR *dir;
    struct dirent *file; // pointer to a file or 'directory entry' within the folder
    vector<Mat> images;

    if((dir = opendir(folder.c_str())) != NULL)
    { // if the folder opens

        while((file != readdir(dir)) != NULL)
        { // while file points to an existing file

            string filename = file->d_name;

            if(filename.substr(filename.find_last_of(".") + 1) == ".png")
            {
                string filePath = folder + "/" + filename;
                Mat image = imread(filePath);

                if(!image.empty())
                {
                    int rows = image.rows;
                    int col = image.cols;

                    image.convertTo(image, CV_32F);

                    if((Sn_pixels <= image.rows) && (Sn_pixels <= col))
                    {
                        images.push_back(image.rowRange(0, Sn_pixels - 1).colRange(0, Sn_pixels - 1));
                    }
                    else
                    {
                        images.push_back(image);
                    }

                }
            }

        }

    }
    else
    {
        cout << "Could not open folder" << endl;
    }

    closedir(dir);

    return images;

}