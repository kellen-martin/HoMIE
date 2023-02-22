% Eric Dean
% hello
clc;clear all; close all;

image = imread('reconimage.png');
imshow(image); axis image;
h_rect = image.roi.Rectangle ; 