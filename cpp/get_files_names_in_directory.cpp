#include <opencv2/opencv.hpp>
#include <dirent.h>

// Function to get the list of file names in a directory
std::vector<std::string> getFilesNamesInDirectory(std::string directory)
{
    std::vector<std::string> fileNames;
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(directory.c_str())) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            std::string fileName = ent->d_name;
            // Ignore "." and ".."
            if (fileName != "." && fileName != "..")
            {
                fileNames.push_back(fileName);
            }
        }
        closedir(dir);
    }
    return fileNames;
}