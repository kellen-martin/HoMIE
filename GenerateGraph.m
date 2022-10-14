function GenerateGraph(moment,start,last,images,avgImg,clean,reconstructed,ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)
% Generates 3 figures, 
% Figure 1: has 3 subfigures that show at a given moment...
%         (1) the raw image from sensor
%         (2) the average image of whole image set
%         (3) the cleaned image
% Figure 2: can be ignored
% Figure 3: is an animation from specified start frame to last frame

% Variables:
% moment = which frame you'd like diplayed in Figure 1
% start = starting frame for animation in figure 3
% last = ending frame for animation in figure 3
% images = array of raw images from sensor
% avgImg = average image of all raw frames
% clean = array of clean frames
% reconstructed = array of reconstructed frames
% roi = region of interest

figure(1)
subplot(1,3,1)
imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(images{moment})));
cm=colormap('gray');colormap(cm(end:-1:1,:));
axis square;
title('Original Frame');
subplot(1,3,2)
imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(avgImg)));
cm=colormap('gray');colormap(cm(end:-1:1,:));
axis square;
title('Average Frame');
subplot(1,3,3)
imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(clean{moment})));
cm=colormap('gray');colormap(cm(end:-1:1,:));
axis square;
title('Cleaned Frame');

for j=start:last
    fig = figure(2);
    imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(reconstructed{j}(ROI_y_pix(1):ROI_y_pix(2),ROI_x_pix(1):ROI_x_pix(2)))));
    cm=colormap('gray');colormap(cm(end:-1:1,:));
    axis square;
    title('Reconstruction Frame');
    A(j) = getframe;
end

figure(3)
movie(A,10,60)

nothing = 1;
