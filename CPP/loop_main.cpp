#include "loop_defs.cpp" // for global variables
#include "loop_dtypes.cpp" // for data types

#ifndef LOOP_FUNCTIONS
#define LOOP_FUNCTIONS
#include "loadCommands.cpp"
#endif


using namespace std;

int main()
{
    // load commands here
    vector<command> commands = loadCommands();

    int n = commands.size();

    for(int i = 0; i < n; i++)
    {
        // switch on type:
        switch(commands[i].type)
        {
            case NONE:
                // undefined command
                break;


            case SETTINGS:
                // change image sensor settings
                break;


            case CAPTURE:
                // capture images
                // fork and use sdk program to capture n frames
                break;


            case DETECT:
                // do motion detection on a reconstruction

                // switch(commands[i].frame)
                // {
                //     case NONE:
                //         // undefined detection command
                //         break;

                //     case TYPE_RAW:
                //         // single frame reconstruction
                //         break;

                //     case TYPE_AVG:
                //         // average frame reconstruction
                //         break;

                //     case TYPE_CLEAN:
                //         // cleaned frame reconstruction
                //         break;

                //     case DIFF_FRAME:
                //         // difference frame reconstruction
                //         break;

                //     case DIFF_STACK:
                //         // difference stack reconstruction
                //         break;

                //     default:
                //         // unexpected detection command
                //         break;
                // }

                // check for saving reconstruction here

                break;


            case DATA:
                // send compression data
                break;


            default:
                // unexpected command
                break;
        }
    }

    return 0;
}