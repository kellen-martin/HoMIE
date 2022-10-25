function GenerateDetailedSubplot(moment,z_slice,images,avgImg,clean,reconstructed,ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Generates useful plot for inspection, useful for debugging
% (R-DIHM-FUNC-)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Inputs:
%   moment - specified frame
%   z_slice - specified z-slice 
%   images - a matrix of greyscale images from sensor
%   avgImg - single matrix that is the average frame of all the images
%   clean - a matrix of greyscale cleaned images
%   reconstructed - a matrix of greyscale reconstructed images
%   ROI - 'region of interest'
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Outputs: 
% Generates 1 figure with 8 subplots
%   (1) raw image from sensor
%   (2) average image from stack
%   (3) cleaned image
%   (4) reconstructed image at specified z-slice and time instant
%   (5) zoomed (1)
%   (6) zoomed (2)
%   (7) zoomed (3)
%   (8) zoomed (4)
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

bs = 3;

figure(1)

%row 1
subplot(2,4,1)
hold on
imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(images{moment})));
cm=colormap('gray');colormap(cm(end:-1:1,:));
axis square;
title('Original Frame');
plot(xmin,ymin,'r*')
plot(ymax,ymax,'g*')
hold off

subplot(2,4,2)
imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(avgImg)));
cm=colormap('gray');colormap(cm(end:-1:1,:));
axis square;
title('Average Frame');

subplot(2,4,3)
imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(clean{moment})));
cm=colormap('gray');colormap(cm(end:-1:1,:));
axis square;
title('Clean Frame');

subplot(2,4,4)
imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(reconstructed{z_slice,moment})));
cm=colormap('gray');colormap(cm(end:-1:1,:));
axis square;
title('Reconstructed Frame');

%% Row 2
subplot(2,4,5)
hold on
axis square;
axis([xmin*bs xmax*bs ymin*bs ymax*bs])
title('Zoomed Original Frame');
imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(images{moment})));
cm=colormap('gray');colormap(cm(end:-1:1,:));
plot([xmin xmax xmax xmin xmin],[ymin ymin ymax ymax ymin],'-b','LineWidth',2)
plot(xmin,ymin,'r*')
plot(ymax,ymax,'g*')
hold off

subplot(2,4,6)
hold on
axis square;
axis([xmin*bs xmax*bs ymin*bs ymax*bs])
title('Zoomed Average Frame');
imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(avgImg)));
cm=colormap('gray');colormap(cm(end:-1:1,:));
plot([xmin xmax xmax xmin xmin],[ymin ymin ymax ymax ymin],'-b','LineWidth',2)
hold off

subplot(2,4,7)
hold on
axis square;
axis([xmin*bs xmax*bs ymin*bs ymax*bs])
title('Zoomed Clean Frame');
imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(clean{moment})));
cm=colormap('gray');colormap(cm(end:-1:1,:));
plot([xmin xmax xmax xmin xmin],[ymin ymin ymax ymax ymin],'-b','LineWidth',2)
hold off

subplot(2,4,8)
hold on
axis square;
axis([xmin*bs xmax*bs ymin*bs ymax*bs])
title('Zoomed Reconstructed Frame');
imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(reconstructed{z_slice,moment})));
cm=colormap('gray');colormap(cm(end:-1:1,:));
plot([xmin xmax xmax xmin xmin],[ymin ymin ymax ymax ymin],'-b','LineWidth',2)
hold off
