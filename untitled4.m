clc
clear all
close all

N = 6000;
processor = 3e9;
timeMax = 128000;


FLOPs_ReconstructorMod = 108000039;
FLOPs_FFT = (14*N*log2(N) + 2*N)*N;
FLOPs_IFFT = FLOPs_FFT;

FLOPs_Total = FLOPs_ReconstructorMod + FLOPs_FFT + FLOPs_IFFT;
FLOPs_Total = FLOPs_Total * 1000;

time = FLOPs_Total / processor;
processorMin = FLOPs_Total / timeMax;