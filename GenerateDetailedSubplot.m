function GenerateDetailedSubplot(moment,z_slice,images,avgImg,clean,reconstructed,ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)
% Generates 3 figures, 
% Figure 1: has 3 subfigures that show at a given moment...
%         (1) raw image from sensor
%         (2) zoomed raw image from sensor
%         (3) average image of whole image set
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

xmin = ROI_x(1);
ymin = ROI_y(1);
xmax = ROI_x(2);
ymax = ROI_y(2);

bs = 3;

% if clean == 0
%     clean = avgImg .*0;
% end
    
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
