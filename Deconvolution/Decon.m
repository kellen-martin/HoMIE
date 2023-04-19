% Eric Dean
% hello
clc;clear all; close all;

image = imread('AgathaE0.028_zslice_0_single.png');


%%
% Nonessential image processing
%whos image

%figure
%imhist(image) % intensity distribution in the image

%image2 = histeq(image);
%figure
%imshow(image2)

%%
% Selecting a cross section of the hologram
figure(1)
imshow(image);
[cx,cy,c] = improfile(); % allows the user to draw a line in the image;

figure(2)
plot(cx,c)



%%
%{
% Image Decon
PSF = fspecial('gaussian',7,10); % rot sym gaussian low pass filter - size = 7 - std = 10

% Creating a weight array to specify the pixels to be processed
INITPSF = ones(size(PSF));
%V = .0001;
WT = zeros(size(image));
WT(5:end-4,5:end-4) = 1;

[J,psfr] = deconvblind(image,INITPSF,20,[],WT);%,20,10*sqrt(V),WT) ; 
subplot(1,2,1);imshow(J);
title('Deconvoluted Image');
subplot(1,2,2);imshow(image)
title('Original Image');
%}




%%
% Pixel Intensities
%{
B = rgb2gray(image); 
B2 = rgb2gray(J);
intensity = B(30,30) 
intensity2 = B2(30,30)
figure
imshow(B2);
figure
imhist(B2);
h_rect = imrect(B2);
%}
%% 
% Plotting the pixel intensities as a function of pixel location
%{
figure
B3 = im2double(B2); % pixel intensity


for i=1:715

    for j = 1:1366
        scatter(i,j,10,B3(i,j),'filled')
        
    end
    
end
%}


