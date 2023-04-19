% Cleaning img
clc;clear all;close all;

% Load the clean image
clean_img = imread('AgathaE0.028.jpg');

% Load the degraded image
deg_img = imread('AgathaE0.028_zslice_0_single.png');

% Finding the average img value of the clean img
sum_clean = 0;
for i = 1:length(clean_img)
    for j = 1:length(clean_img)
        sum_clean = double(clean_img(i,j)) + sum_clean;
    end

end
sum_clean = sum_clean/(2048^2);

% Finding the average img value of the degraded img
sum_deg = 0;
for i = 1:length(deg_img)
    for j = 1:length(deg_img)
        sum_deg = double(deg_img(i,j)) + sum_deg;
    end

end
sum_deg = sum_deg/(911^2);


% Define an initial estimate of the blur kernel
kernel_size = 911;
alpha = 0.99 ; 
kernel = fspecial('gaussian', kernel_size,2);

% Perform blind deconvolution
[recovered_img, estimated_kernel] = deconvblind(deg_img, kernel);

% Display the results
figure()
subplot(1, 3, 1), imshow(deg_img), title('Degraded image')
subplot(1, 3, 2), imshow(recovered_img), title('Recovered image')
subplot(1, 3, 3), imshow(estimated_kernel), title('Estimated kernel')

figure()
imshow(recovered_img);
[cx,cy,c] = improfile(); % allows the user to draw a line in the image; 
% outputs are the x,y pixel coords, and their respective light intensities
% 2 left clicks (one to start, and one to end the line segment), then one
% right click to end the segment

[max_value, max_index] = max(c) ; 
threshold = max_value/2 ; 
lower_index = find(c(1:max_index) < threshold,1,'last'); %
upper_index = find(c(max_index:end) < threshold,1) + max_index -1 ; 
x_unit = cx(2) - cx(1) ; 
fwhm = (cx(upper_index) - cx(lower_index))*x_unit ; 
figure(3); hold on;
plot(cx,c) ; grid on; title('Sample Cross Section','FontSize',18);xlabel('Pixel X Coordinates','FontSize',18);ylabel('Light Intensity','FontSize',18);
%plot(cx(max_index),threshold:max_value,'Marker','x','MarkerColor','b') ; 
yline(threshold,'r','LineWidth',2);
%xline(cx(max_index)) ; 
plot(cx(lower_index+1),threshold,'Marker','x','MarkerEdgeColor','r');
plot(cx(upper_index),threshold,'Marker','x','MarkerEdgeColor','r'); 
