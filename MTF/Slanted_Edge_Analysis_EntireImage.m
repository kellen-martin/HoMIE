% Eric Dean
% MTF From 1 Slanted Edge
% 4/12/2023
% HoMIE

% Cleaning
clc;clear;close all;

% Reading in the slanted edge target image
image = imread('Real Edge From CMOS.jpg');

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

newimage = im2gray(newimage);

[~,threshold] = edge(newimage,'sobel');
fudgeFactor = 0.5;
BWs = edge(newimage,'sobel',threshold * fudgeFactor);
figure; imshow(BWs);

[edge_row, edge_col] = find(BWs); % returning the pixel coords where 

P = polyfit((edge_col),flipud(edge_row),1);
y = polyval(P,edge_col);

% Need to plot perpendicular line to the least square regression

figure()

for i = 1:length(edge_col)-33

    x_intersect = edge_col(i); %%
    y_intersect = edge_row(i);
    perp_slope = -1/(P(1));     %%% Creating a perp line for every point on the edge
    b = y_intersect - perp_slope*x_intersect ;
    y_perp = perp_slope.*edge_col + b ; %%%
    
    angle_interest = atand(perp_slope); % EDGE ANGLE

    St_index = i ;
    End_index = St_index + 32; % arbitrary ; found in paper 

    perp_spread = edge_col(St_index:End_index) ; 

    Proj_Point_dists = tand(angle_interest).*perp_spread; 

    %hold on;
    scatter(perp_spread,Proj_Point_dists);
    


end
c1 = edge_col(1);
c2 = edge_col(i);