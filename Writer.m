function Writer(image,name)

I = sqrt(abs(image));
J = I./max(I);
J = J.*255;
J = 255 - J;
imwrite(J,gray,name+".png");