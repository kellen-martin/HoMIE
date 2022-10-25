function PlotFrame(image,name,ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)
tic
if nargin == 2
    figure
    imagesc(sqrt(abs(image)));
    cm=colormap('gray');colormap(cm(end:-1:1,:));
    axis square;
    title(name);
end
if nargin == 6
    figure
    imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(image(ROI_y_pix(1):ROI_y_pix(2),ROI_x_pix(1):ROI_x_pix(2)))));
    cm=colormap('gray');colormap(cm(end:-1:1,:));
    axis square;
    title(name);
end
time = toc;
fprintf('\nPlotFrameSpecial %.2f\n', time)