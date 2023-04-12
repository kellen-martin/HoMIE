// #include "header.hpp"
#include "defs.cpp"
#include "dtypes.cpp"

#ifndef FUNCTION_HEADERS
#define FUNCTION_HEADERS
#include "saveFunctions.cpp"
#include "CalculateTemplate.cpp"
#include "AverageImage.cpp"
#include "DifferenceStack.cpp"
#include "ImportImages.cpp"
#include "linspace.cpp"
#include "PlotFrame.cpp"
#include "Reconstructor.cpp"
#include "dtypes.cpp"
#include "Reconstructor_Kanka1.cpp"
#endif

using namespace std;
using namespace cv;

string output_folder = "../Output Images";

int main()
{
    bool running = true;
    bool command_mode  = false;
    bool image_mode    = true;
    bool parallel_mode = false;
    char inp;

    while(running)
    {
        if(command_mode)
        {
            // find and execute commands
            // pid = fork();
            // if(fork) // parent process
        }
        else if(image_mode)
        {
            // capture and process image

            pid_t pid = fork();

            if(pid < 0)
            {
                // error 
                cout << "Error splitting process" << endl;
                return 1;
            }
            else if(pid == 0)
            {
                // child process here
                // call exec() to run:
                    // captureOEM
                    // Recon
                
                cout << "Exit? (Y/N): ";
                while(true)
                {
                    cin >> char;
                    if((char == 'Y') || (char == 'y'))
                    {
                        running = false;
                        break;
                    }
                    if((char == 'N') || (char == 'n'))
                    {
                        command_mode = true;
                        image_mode = false;
                        break;
                    }
                    cout << "Exit? (Y/N): ";
                }
            }
            else if(pid > 0)
            {
                // parent process here
                // wait for child process pid to finish
            }

        }
        else if(parallel_mode)
        {

        }
    }

    return 0;
}

