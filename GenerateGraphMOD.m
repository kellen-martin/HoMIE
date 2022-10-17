function GenerateGraphMOD(moment,start,last,z,images,avgImg,clean,reconstructed,ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)
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
subplot(1,2,1)
hold on
imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(images{moment})));
cm=colormap('gray');colormap(cm(end:-1:1,:));
axis square;
title('Original Frame');
% rectangle('position',[ROI_x(1) ROI_y(1) ROI_x(2) ROI_y(2)],'EdgeColor','r')
xmin = ROI_x(1);
ymin = ROI_y(1);
xmax = ROI_x(2);
ymax = ROI_y(2);
plot([xmin xmax xmax xmin xmin],[ymin ymin ymax ymax ymin],'-o','LineWidth',10)
% rectangle('position',[xmin ymin xmax ymax],'EdgeColor','b')
plot(ROI_x(1),ROI_y(1),'r*')
plot(ROI_x(2),ROI_y(2),'r*')
hold off
subplot(1,2,2)
imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(avgImg)));
cm=colormap('gray');colormap(cm(end:-1:1,:));
axis square;
title('Average Frame');

for j=start:last
    fig = figure(2);
    imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(reconstructed{z,j}(ROI_y_pix(1):ROI_y_pix(2),ROI_x_pix(1):ROI_x_pix(2)))));
    cm=colormap('gray');colormap(cm(end:-1:1,:));
    axis square;
    title('Reconstruction Frame');
    A(j) = getframe;
end

figure(3)
movie(A,10,60)

nothing = 1;
