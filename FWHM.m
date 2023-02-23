% Eric Dean
clc;clear all; close all;

image = imread('reconimage.png');
imshow(image);
[cx,cy,c] = improfile(); % allows the user to draw a line in the image; 
% outputs are the x,y pixel coords, and their respective light intensities
% 2 left clicks (one to start, and one to end the line segment), then one
% right click to end the segment

[max_value, max_index] = max(c) ; 
threshold = max_value/2 ; 
lower_index = find(c(1:max_index) < threshold,1,'last');
upper_index = find(c(max_index:end) < threshold,1) + max_index -1 ; 
x_unit = cx(2) - cx(1) ; 
fwhm = (upper_index - lower_index)*x_unit ; 
plot(cx,c) ; grid on; title('Light Intensity vs Pixel X Coordinate');xlabel('Pixel X Coordinate');ylabel('Pixel Y Coordinate');
yline(threshold,'r');
%roi = drawline('Color','r');