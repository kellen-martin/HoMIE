% Eric Dean
% gain = 0db
clc;clear all; close all;

image = imread('Direct View 3_9 0d05ms.tif');
whos image
info = imfinfo('Direct View 3_9 0d05ms.tif');
[counts,binlocs] = imhist(image);  % intensity distribution in the image