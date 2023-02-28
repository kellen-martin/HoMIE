function Writer(image,name)
    I = sqrt(abs(image));
    J = I / max(I(:));
    J = uint8(round(J * 255));
    J = 255 - J;
    imwrite(J, colormap(gray(256)), [name '.png'], 'BitDepth', 8);
end