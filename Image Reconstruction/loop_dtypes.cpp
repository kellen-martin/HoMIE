#ifndef LOOP_TYPES
#define LOOP_TYPES

#include "loop_header.hpp"

using namespace std;


struct command
{
    string sampleID;

    int type;
    int detect;
    int frame1;
    int frame2;
    int returnType;

    int captureFrames;

    command()
    {
        sampleID = "";

        type  = 0;
        detect = 0;
        frame1 = 0;
        frame2 = 0;
        returnType = 0;
        
        captureFrames = 0;
    }

};

#endif