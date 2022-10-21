function GenerateZAnimation(moment,n,fps,num_z_slices,reconstructed,ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Generates an animation at a specified frame moment by stepping through
% different z-slices
% (R-DIHM-FUNC-)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Inputs:-
%   z_slice - specified z-slice 
%   n -  plays the movie n number of times
%   fps - specifies the number of frames per second
%   num_of_frames - number of frames
%   reconstructed - a matrix of greyscale reconstructed images
%   ROI - 'region of interest'
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Outputs: 
% Generates 1 figure
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Author:
%   Nick 
% 
% Last Edited: 10/21/22
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

xmin = ROI_x(1);
ymin = ROI_y(1);
xmax = ROI_x(2);
ymax = ROI_y(2);

for z=1:num_z_slices
    fig = figure(3);
    imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(reconstructed{z,moment}(ROI_y_pix(1):ROI_y_pix(2),ROI_x_pix(1):ROI_x_pix(2)))));
    cm=colormap('gray');colormap(cm(end:-1:1,:));
    axis square;
    A(z) = getframe;
end

figure(3)
title('Z Animation');
movie(A,n,fps)