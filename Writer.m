function Writer(image,name)
ROI_x = [-0.5,0.5]*1e-3; %mm
ROI_y = [-0.5,0.5]*1e-3;
ROI_x_pix = round(2048*5/2 + ROI_x/(5.5e-6/5));
ROI_y_pix = round(2048*5/2 + ROI_y/(5.5e-6/5));
    I = sqrt(abs(image(ROI_x_pix(1):ROI_x_pix(2),ROI_y_pix(1):ROI_y_pix(2))));
    J = I / max(I(:));
    J = uint8(round(J * 255));
    J = 255 - J;
    imwrite(J, colormap(gray(256)), [name '.png'], 'BitDepth', 8);
end