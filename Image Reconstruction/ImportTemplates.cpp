#include "header.hpp"

using namespace std;
using namespace cv;


// ImportTemplates only takes in folder name now, the 'inputs' variable contents are globals

void ImportTemplates(vector<Mat>& templates, string folder)
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
                Mat template;

                if(!image.empty())
                {
                    


                }
                else
                {
                    cout << "Error loading template - file empty" << endl;
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

    if(verbose) cout << "Number of templates found in '" << folder << "': " << images.size() << endl;
    
    if(verbose) cout << "-----------------------------------------------------" << endl;

    return;

}