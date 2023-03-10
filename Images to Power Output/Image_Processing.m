% Eric Dean
clc;clear all; close all;

image = imread('Direct View 3_9 0d05ms.tif');
whos image
info = imfinfo('Direct View 3_9 0d05ms.tif');
imhist(image,8) % intensity distribution in the image