function frames = AnimationZ(images,numFrames,ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)
tic

figure;
hold on
if nargin == 2
    for i=1:numFrames
        imagesc(sqrt(abs(images{i})));
        cm=colormap('gray');colormap(cm(end:-1:1,:));
        axis square;
        A(i) = getframe;
    end
end
if nargin == 6
    for i=1:numFrames
        imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(images{i}(ROI_y_pix(1):ROI_y_pix(2),ROI_x_pix(1):ROI_x_pix(2)))));
        cm=colormap('gray');colormap(cm(end:-1:1,:));
        axis square;
        A(i) = getframe;
    end
end
frames = A;

time = toc;
fprintf('\nAnimationZ %.2f\n', time)