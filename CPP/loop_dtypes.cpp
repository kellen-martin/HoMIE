#ifndef LOOP_TYPES
#define LOOP_TYPES

#include "loop_header.hpp"

using namespace std;


struct command
{
    int type;
    int detect;
    int frame1;
    int frame2;
    string sampleID;

    int captureFrames;

    command()
    {
        type  = 0;
        detect = 0;

        captureFrames = 0;
        frame1 = 0;
        frame2 = 0;
        sampleID = "";
    }

};

#endif