#pragma once
#ifndef LOOP_DEFS
#define LOOP_DEFS

#include "loop_header.hpp"

using namespace std;


const string commandFile = "Commands.txt";

const int SETTINGS      = 1;
const int CAPTURE       = 2;
const int DETECT        = 3;
const int DATA          = 4;

const int DIFF_FRAME   = 8;
const int DIFF_STACK   = 9;
const int SINGLE_FRAME = 15;

const int TYPE_RAW        = 5;
const int TYPE_AVG        = 6;
const int TYPE_CLEAN      = 7;
const int TYPE_RECON      = 16;

const int SAVE_FULL_ROI = 10;
const int SAVE_DETECTED = 11;

const int DATA_SUMMARY     = 12;
const int DATA_COMPRESSION = 13;
const int DATA_COMP_EST    = 14;

const int NONE = 0;



#endif