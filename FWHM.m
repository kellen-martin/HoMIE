% Eric Dean
clc;clear all; close all;
image = imread('AgathaE0.028_zslice_0_single.png');
figure(1)
imshow(image);
[cx,cy,c] = improfile(); % allows the user to draw a line in the image; 
% outputs are the x,y pixel coords, and their respective light intensities
% 2 left clicks (one to start, and one to end the line segment), then one
% right click to end the segment

[max_value, max_index] = max(c) ; 
threshold = max_value/2 ; 
lower_index = find(c(1:max_index) < threshold,1,'last'); %
upper_index = find(c(max_index:end) < threshold,1) + max_index  ; 
x_unit = cx(2) - cx(1) ; 
fwhm = (cx(upper_index) - cx(lower_index))*x_unit ; 
figure(2); hold on;
plot(cx,c) ; grid on; title('Sample Cross Section','FontSize',18);xlabel('Pixel X Coordinates','FontSize',18);ylabel('Light Intensity','FontSize',18);
%plot(cx(max_index),threshold:max_value,'Marker','x','MarkerColor','b') ; 
yline(threshold,'r','LineWidth',2);
%xline(cx(max_index)) ; 
plot(cx(lower_index+1),threshold,'Marker','x','MarkerEdgeColor','r');
plot(cx(upper_index),threshold,'Marker','x','MarkerEdgeColor','r'); 
