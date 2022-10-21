function GenerateFrameAnimation(z_slice,n,fps,num_of_frames,reconstructed,ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Generates an animation at a specified z-slice by stepping through
% different frame moments
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

for j=1:num_of_frames
    fig = figure(2);
    imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(reconstructed{z_slice,j}(ROI_y_pix(1):ROI_y_pix(2),ROI_x_pix(1):ROI_x_pix(2)))));
    cm=colormap('gray');colormap(cm(end:-1:1,:));
    axis square;
    A(j) = getframe;
end

figure(2)
title('Frame Animation');
movie(A,n,fps)
