clc
clear all
close all


% folder = 'Holo';
% [avgImg,map,images] = generateAverageImage(folder);
% clean = cleanFrames(images,avgImg);

clean = importdata('clean.mat');

PNG_MEAN_AMPLITUDE = 128; % average pixel amplitude in file to minimize "clipping"
PNG_FILENAME = "simulated_hologram.png";
WRITE_HOLOGRAM_PNG = false;
NEWCASE = false;

OVS =2; 

% physical specs
SENSOR_NX = 4024;  
SENSOR_NY = 3036;
inputs.wavelength  = 405e-9;      % Blue light
Sn_pixels    = 3000;
inputs.pixel_p     = 1.85e-6/OVS; % pixel pitch, with oversampling

inputs.n_pixels    = Sn_pixels*OVS;    % size of oversampled region to process
inputs.ref_dist    = 12.0e-3;     % reference to sensor dist
inputs.samp_dist   = 8.14e-3;     % sample to sensor dist
inputs.ref_amp     = 1;           % amplitude of reference wave at sensor
inputs.ref_pos_x   = 0;           % x position of laser
inputs.ref_pos_y   = 0;           % y position of laser
inputs.obj_amp     = 0.01;        % scattered light amplitude at sensor

% Define zoom region of interest:
ROI_x = [-0.5,0.5]*1e-3; %mm
ROI_y = [-0.5,0.5]*1e-3;
ROI_x_pix = round(inputs.n_pixels/2 + ROI_x/inputs.pixel_p);
ROI_y_pix = round(inputs.n_pixels/2 + ROI_y/inputs.pixel_p);

% Generate simulated (oversampled) hologram:
rval = templateMaker(inputs); %return value


tic
%% looper
for i = 1:99
% PNG_FILENAME = "simulated_hologram"+i+".png";
%% end looper
i = i
real = clean{i};
real = single(real(1:Sn_pixels,1:Sn_pixels));
real = single(imresize(real,OVS));

% Downsample (the original hologram was oversampled to simulate non-infinitesimal
% pixels, so undo the oversampling to simulate a real camera).
% Also, subtract out the reference wave's intensity. Note that when
% processing real holograms, this will be done by subtracting out the
% average image:
down_sz = inputs.n_pixels/OVS; %this is what sensor sees
I2_down = imresize(real - abs(rval.ref_wave).^2, [down_sz, down_sz], 'box'); %find intensity then remove its effect
% imresize is downsampling
% 'box' is box filter, to deal with light freq being more fine that pixel

% if desired, write out the simulated hologram as a png file
if WRITE_HOLOGRAM_PNG
    % First write out the hologram as a png, and use dither noise
    % so the signal isn't rounded away, since it's only an 8 bit image:
    
    png_image = zeros(SENSOR_NY, SENSOR_NX);
    downsized_n_pixels = inputs.n_pixels/OVS;
    dither_noise = rand(downsized_n_pixels, downsized_n_pixels) - 0.5; % "dithers the data" is important before quantization to 8 bit to preserve data
    
    downsized = round(PNG_MEAN_AMPLITUDE*imresize(real, [down_sz, down_sz], 'box') + dither_noise);
    png_coord_x = [0:downsized_n_pixels-1] - downsized_n_pixels/2 + SENSOR_NX/2;
    png_coord_y = [0:downsized_n_pixels-1] - downsized_n_pixels/2 + SENSOR_NY/2;
    png_image(png_coord_y, png_coord_x) = downsized;
    imwrite(uint8(round(png_image)), PNG_FILENAME, 'BitDepth', 8);

    % Then read back in the png and overwrite the original hologram, so
    % we reconstruct the png (dithered) version:
    png_image_read = single(imread(PNG_FILENAME));
    downsized_read = png_image_read(png_coord_y, png_coord_x)/PNG_MEAN_AMPLITUDE;
    I2_down = downsized_read - imresize(abs(rval.ref_wave).^2, [down_sz, down_sz], 'box');   %over writes line 55 
end

% Upsample (to prevent aliasing) in the frequency domain by inserting zeros. 
% This is more  computationally efficient than upsampling using convolution:
I2_down_fft = fft2(I2_down); %of data
I2_up_fft   = single(zeros(inputs.n_pixels, inputs.n_pixels)); %insert zeros

%inverse fft to oversample
I2_up_fft(              1:down_sz/2, 1:down_sz/2)         = I2_down_fft(          1:down_sz/2, 1:down_sz/2);
I2_up_fft(end-down_sz/2+1:end      , 1:down_sz/2)         = I2_down_fft(down_sz/2+1:end      , 1:down_sz/2);
I2_up_fft(              1:down_sz/2, end-down_sz/2+1:end) = I2_down_fft(          1:down_sz/2, down_sz/2+1:end);
I2_up_fft(end-down_sz/2+1:end      , end-down_sz/2+1:end) = I2_down_fft(down_sz/2+1:end      , down_sz/2+1:end);
I2_up = ifft2(I2_up_fft);


% Now that we've upsampled, we can despread without causing (much)
% alaising. After this operation, our object term is separated from the
% interference term:  (R O* + R* O) R  ~=  R R O* + O
despread = I2_up.*rval.ref_wave; % 'despreading' the signal
% if there was no interference, microscope would not work

% Begin clearing unused large variables to save memory:
clear I2_up;
clear I2_up_fft;

% Define an "apodizer" to eliminate some annoying edge-induced artifacts from the
% 'apodizer' = windowing function, using it to eliminate unneed stuff
% convolutional reconstruction operation. This crops down the image to just
% a circular central portion. We will also apodize the template:
[X,Y] = meshgrid(single(linspace(-1,1,inputs.n_pixels)), single(linspace(-1,1,inputs.n_pixels)));
apodizer = single(sqrt(X.^2 + Y.^2) < 1);

clear X;
clear Y;

% Correlate against template, use apodizer
despread_fft = fft2(despread.*apodizer);
template_fft = fft2(rval.template_wave.*apodizer);
clear apodizer;
clear despread;
% fftshift rearranged image into a state we can understand
correlated{i} = fftshift(ifft2(despread_fft.*conj(template_fft))); % frequency-domain convolution (correlation)
clear despread_fft;
clear template_fft;

% % Plot the reconstructed (zoomed) hologram:
% 
% figure(i)
% imagesc(ROI_x*1000, ROI_y*1000, sqrt(abs(correlated(ROI_y_pix(1):ROI_y_pix(2),ROI_x_pix(1):ROI_x_pix(2)))));
% cm=colormap('gray');colormap(cm(end:-1:1,:));
% axis square;
% % xlabel('x position (mm)');
% % ylabel('y position (mm)');
% % title('Reconstruction (zoomed)');
% 
% % saveas(gcf,['frame' num2str(i) '.png']);
% A(i) = getframe(gcf);
% 
% close
% 
% %% looper
end
toc
% 
% movie(A,3,20)

