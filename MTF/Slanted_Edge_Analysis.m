% Eric Dean
% MTF From Slanted Edge
% 4/7/2023
% HoMIE

% Cleaning
clc;clear; close all;

% Reading in the slanted edge target image
image = imread('Real Edge from CMOS.jpg');

% Viewing image
figure
imshow(image) ; axis image;
ROI  = getrect();

% Get x & y coords of rect
pos(1) = max(floor(ROI(1)), 1 ); %min
pos(2) = max(floor(ROI(2)), 1 ); 
pos(3) = min(ceil( ROI(1) + ROI(3) )); %max
pos(4) = min(ceil( ROI(2) + ROI(4) )); 

% Index into a new image
newimage = image(pos(2) : pos(4) , pos(1) : pos(3) , :);
figure
imshow(newimage)