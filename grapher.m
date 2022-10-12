function grapher(momement,start,last,images,avgImg,clean,final,ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)

figure(1)
subplot(1,3,1)
imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(images{momement})));
cm=colormap('gray');colormap(cm(end:-1:1,:));
axis square;
title('Original Frame');
subplot(1,3,2)
imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(avgImg)));
cm=colormap('gray');colormap(cm(end:-1:1,:));
axis square;
title('Average Frame');
subplot(1,3,3)
imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(clean{momement})));
cm=colormap('gray');colormap(cm(end:-1:1,:));
axis square;
title('Cleaned Frame');

for j=start:last
    fig = figure(2);
    imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(final{j}(ROI_y_pix(1):ROI_y_pix(2),ROI_x_pix(1):ROI_x_pix(2)))));
    cm=colormap('gray');colormap(cm(end:-1:1,:));
    axis square;
    title('Reconstruction Frame');
    A(j) = getframe;
end

figure(3)
movie(A,10,60)

nothing = 1;
