clc
clear all
close all

% variables
Zheight            = 2e-3;        % height of sample volume

%inputs
inputs.z_resolution= 2e-6;
inputs.Sn_pixels   = 3000;        % must be smaller than small SENSOR_NX/Y
% inputs.Sn_pixels   = 700;       % must be smaller than small SENSOR_NX/Y
inputs.OVS         = 2;

% inputs
inputs.wavelength  = 405e-9;      % Blue light
inputs.pixel_p     = 1.85e-6/inputs.OVS; % pixel pitch, with oversampling
inputs.n_pixels    = inputs.Sn_pixels*inputs.OVS;    % size of oversampled region to process
inputs.ref_dist    = 12.0e-3;     % reference to sensor dist
inputs.samp_dist   = 8.14e-3;     % sample to sensor dist
inputs.ref_amp     = 1;           % amplitude of reference wave at sensor
inputs.ref_pos_x   = 0;           % x position of laser
inputs.ref_pos_y   = 0;           % y position of laser
inputs.obj_amp     = 0.01;        % scattered light amplitude at sensor

[~,images] = ImportImages('test',inputs);
image = (255-images{1});
I2_down_fft = fft2(image);
% PlotFrame(image,'image')

Writer(image,"low")
% PlotFrame(I2_down_fft,'image')

down_sz = inputs.n_pixels/inputs.OVS; %this is what sensor sees

I2_up_fft   = single(zeros(inputs.n_pixels, inputs.n_pixels)); %insert zeros

I2_up_fft(              1:down_sz/2, 1:down_sz/2)         = I2_down_fft(          1:down_sz/2, 1:down_sz/2);
I2_up_fft(end-down_sz/2+1:end      , 1:down_sz/2)         = I2_down_fft(down_sz/2+1:end      , 1:down_sz/2);
I2_up_fft(              1:down_sz/2, end-down_sz/2+1:end) = I2_down_fft(          1:down_sz/2, down_sz/2+1:end);
I2_up_fft(end-down_sz/2+1:end      , end-down_sz/2+1:end) = I2_down_fft(down_sz/2+1:end      , down_sz/2+1:end);
I2_up_fft1 = I2_up_fft;
I2_up1 = ifft2(I2_up_fft1);

I2_up_fft   = single(zeros(inputs.n_pixels, inputs.n_pixels)); %insert zeros
I2_up_fft(              1:down_sz/2, 1:down_sz/2)         = I2_down_fft(          1:down_sz/2, down_sz/2+1:end);
I2_up_fft(end-down_sz/2+1:end      , 1:down_sz/2)         = I2_down_fft(down_sz/2+1:end      , 1:down_sz/2);
I2_up_fft(              1:down_sz/2, end-down_sz/2+1:end) = I2_down_fft(          1:down_sz/2, 1:down_sz/2);
I2_up_fft(end-down_sz/2+1:end      , end-down_sz/2+1:end) = I2_down_fft(down_sz/2+1:end      , down_sz/2+1:end);
I2_up_fft2 = I2_up_fft;
I2_up2 = ifft2(I2_up_fft2);

PlotFrame(I2_up1,"1")
% PlotFrame(I2_up2,"2")

a = 0.0155140;
b = 0.00534738;
fk = [a b a; 0 0 0; -a -b -a];

a = 0.03744;
b = 0.970049;
fkg = [a a a; a b a; a a a];

% kernal = [-1 -1 -1; -1 8 -1; -1 -1 -1];
% ridgeUp = conv2(I2_up1,kernal,'same');
% PlotFrame(ridgeUp,"ridgeUp")
% 
% ridgeDown = conv2(image,kernal,'same');
% PlotFrame(ridgeDown,"ridgeDown")


% use im2double()/im2single() instead of double()/single()
smooth_image = conv2(im2single(I2_up1), fkg, 'same');
% smooth_image is already class 'single'
vert_ = conv2(smooth_image, fk.', 'same'); % d/dx
hor_ = conv2(smooth_image, fk, 'same'); % d/dy
final = sqrt(vert_.^2 + hor_.^2); % gradient magnitude
imshow(final)

% PlotFrame(I2_up,'I2_up')
Writer(I2_up1,"I2_up1")
Writer(I2_up2,"I2_up2")