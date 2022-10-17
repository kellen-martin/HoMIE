function GenerateZAnimation(moment,n,fps,num_z_slices,reconstructed,ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)
% Generates 1 figure 

% Variables:
% moment = which frame you'd like diplayed in Figure 1
% n =  plays the movie n number of times
% fps = specifies the number of frames per second
% num_z_slices = number of z slices
% reconstructed = array of reconstructed frames
% roi = region of interest

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