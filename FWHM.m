% Eric Dean
clc;clear all; close all;

image = imread('reconimage.png');
imshow(image);
[cx,cy,c] = improfile(); % allows the user to draw a line in the image; 
% outputs are the x,y pixel coords, and their respective light intensities
halfmax = max(c)/2 ; 
plot(cx,c) ; grid on; title('Light Intensity vs Pixel X Coordinate');xlabel('Pixel X Coordinate');ylabel('Pixel Y Coordinate');
yline(halfmax,'r');
%roi = drawline('Color','r');