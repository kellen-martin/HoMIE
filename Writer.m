function Writer(image,name)

I = sqrt(abs(image));
% J = imadjust(I,stretchlim(I),[0 1]);
J = I./max(I);
% J = imadjust(I);
% J = mat2gray(I, [0,255]);
J = J.*255;
J = 255 - J;
imwrite(J,gray,name+".png");