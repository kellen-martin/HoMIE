function imageWriterMod(image,name,ROI_y_pix,ROI_x_pix)
% load a test image
I = image;

% recreate image
cm = colormap('gray');
cm = colormap(cm(end:-1:1,:));        % grab current colormap
ncolors = size(cm,1);

% do what imagesc does
Iind = double(I) - double(min(I(:)));
Iind = Iind / max(Iind(:));
% quantize image
Iind = round(Iind * ncolors + 0.5);
Iind(Iind > ncolors) = ncolors;
Iind(Iind < 1) = 1;
% convert to RGB from indexed image using cmap as palette
% Irgb = ind2rgb(Iind,cmap);

imwrite(...
    uint8(...
        sqrt(...
            abs(...
                image(ROI_y_pix(1):ROI_y_pix(2),ROI_x_pix(1):ROI_x_pix(2))...
            )...
        )...
    )...
,Iind,name+".png", 'BitDepth', 8);