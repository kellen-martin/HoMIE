% Eric Dean
% MTF From Slanted Edge
% 4/7/2023
% HoMIE

% Cleaning
clc;clear;close all;

% Reading in the slanted edge target image
image = imread('slanted edge 2.jpg');

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

newimage = rgb2gray(newimage);

[~,threshold] = edge(newimage,'sobel');
fudgeFactor = 0.5;
BWs = edge(newimage,'sobel',threshold * fudgeFactor);
figure; imshow(BWs);

[edge_row, edge_col] = find(BWs); % returning the pixel coords where 

P = polyfit((edge_col),flipud(edge_row),1);
y = polyval(P,edge_col);


figure() ;
hold on;
plot(edge_col,y)
Angle_deg = atan(P(1))*180/pi; % slope of the line

% Need to plot perpendicular line to the least square regression

midpt_x = edge_col(floor(length(edge_col)/2)) ;
midpt_y = y(floor(length(y)/2)) ;
perp_slope = -1/(P(1));
b = midpt_y - perp_slope*midpt_x ; 
y_perp = perp_slope.*edge_col + b ; 

plot(edge_col,y_perp);
axis equal;% yay 
yline(midpt_y,'g'); 
angle_interest = atand(perp_slope); % EDGE ANGLE
title('Edge with Perpendicular Line and Y-Line');xlabel('Pixel X Coords');ylabel('Pixel Y Coords');
legend('Edge','Perp','Y-Line')

% Project Points from Y-Line onto the Perp Line

St_index = floor(length(edge_col)/2);
End_index =  floor(length(edge_col)/2) + 32 ; 

perp_spread = edge_col(St_index:End_index) ; 

Proj_Point_dists = tand(angle_interest).*perp_spread;   % Want to do this for every row :)

% Plotting the ESF for one row
figure();
plot(perp_spread,Proj_Point_dists);






