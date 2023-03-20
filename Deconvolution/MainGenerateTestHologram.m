clear;close all;
% test_DHM_2D
% The simulated camera is the AV Alvium 1800 U-1240m C-Mount.
%
% Note that the script uses "single" precision by casting varaibles to
%   single(). This is to save memory and improve processing speed in some cases.
%   The results are not effected.

SENSOR_NX = 2048;  
SENSOR_NY = 2048;
PNG_MEAN_AMPLITUDE = 128; % average pixel amplitude in file to minimize "clipping"
    
WRITE_HOLOGRAM_PNG = true;

    


% Define the physical setup:
%    (all lengths are in meters)
inputs.wavelength  = 405e-9; 
OVS                = 2;           % oversampling factor
inputs.n_pixels    = 2048*OVS;    % size of oversampled region to process
inputs.pixel_p     = 1.85e-6/OVS; % pixel pitch, with oversampling
inputs.ref_dist    = 21e-3;     % reference to sensor dist
inputs.samp_dist   = 18.5e-3;     % sample to sensor dist
inputs.ref_amp     = 1;           % amplitude of reference wave at sensor
inputs.ref_pos_x   = 0;           % x position of laser
inputs.ref_pos_y   = 0;           % y position of laser
inputs.obj_amp     = 0.01;        % scattered light amplitude at sensor
    
% Define zoom region of interest:
% (for viewing after reconstruction)
ROI_x = [-0.5,0.5]*1e-3;
ROI_y = [-0.5,0.5]*1e-3;
ROI_x_pix = round(inputs.n_pixels/2 + ROI_x/inputs.pixel_p);
ROI_y_pix = round(inputs.n_pixels/2 + ROI_y/inputs.pixel_p);
    
for i = 1:1 % was 1:10
    % Define the image sensor and png file parameters:
    PNG_FILENAME = "simulated_hologram"+i+".png";


    % Create some point scatterers ("objects"):
    % inputs.obj_pos_x   = [   0.0, -.45, -0.1, -0.1,   0.0,  0.15, 0.17, 0.46, 0.00]*1e-3;
    % inputs.obj_pos_y   = [ -0.45, -0.0, -0.1,  0.1,   0.0, -0.11, 0.12, 0.00, 0.45]*1e-3;
    % inputs.obj_pos_z   = [   0,0,    0,    0, 0.10,     0,    0,    0,  0,    0]*1e-3 + inputs.samp_dist;
    % inputs.obj_phase   = [   0,0,    0,    0,    0,     0,    0,    0,  0,    0];

%Data 1 9 randoms
    %inputs.obj_pos_x   = %[(-.5 + (.5+.5)*rand(1,9))]*1e-3;
    %inputs.obj_pos_y   = %[(-.5 + (.5+.5)*rand(1,9))]*1e-3;
    %inputs.obj_pos_z   = %[0,    0,    0, 0.10,     0,    0,    0,  0,    0]*1e-3 + inputs.samp_dist;
    %inputs.obj_phase   = %[0,    0,    0,    0,     0,    0,    0,  0,    0];
    
%Data 2 one thing down, 8 randoms
    inputs.obj_pos_x   = [-0.]*1e-4;%[   0.45, (-.5 + (.5+.5)*rand(1,8))]*1e-3;
    inputs.obj_pos_y   = [0]*1e-4;%[ -0.45+.1*i, (-.5 + (.5+.5)*rand(1,8))]*1e-3;
    inputs.obj_pos_z   = [0]*1e-4;%[   0,0,    0,    0, 0.10,     0,    0,    0,  0,    0]*1e-3 + inputs.samp_dist;
    inputs.obj_phase   = [0]*1e-4;%[   0,0,    0,    0,    0,     0,    0,    0,  0,    0];
    
% %Data 3 one thing down, 3 randoms
%     inputs.obj_pos_y   = [   0.45, (-.5 + (.5+.5)*rand(1,3))]*1e-3;
%     inputs.obj_pos_x   = [ -0.45+.1*i, (-.5 + (.5+.5)*rand(1,3))]*1e-3;
%     inputs.obj_pos_z   = [   0,0,    0,    0]*1e-3 + inputs.samp_dist;
%     inputs.obj_phase   = [   0,0,    0,    0];

%%Data 4 one thing moving from NW to SE
%     inputs.obj_pos_y   = [-0.45+.1*i]*1e-3;
%     inputs.obj_pos_x   = [-0.45+.1*i]*1e-3;
%     inputs.obj_pos_z   = [0]*1e-3 + inputs.samp_dist;
%     inputs.obj_phase   = [0];




    % Generate simulated (oversampled) hologram:
    rval = generateDHMHologram2D(inputs);
    
    % Downsample (the original hologram was oversampled to simulate non-infinitesimal
    % pixels, so undo the oversampling to simulate a real camera).
    % Also, subtract out the reference wave's intensity. Note that when
    % processing real holograms, this will be done by subtracting out the
    % average image:
    down_sz = inputs.n_pixels/OVS;
    I2_down = imresize(rval.intensity - abs(rval.ref_wave).^2, [down_sz, down_sz], 'box');

    % if desired, write out the simulated hologram as a png file
    
    if WRITE_HOLOGRAM_PNG
        % First write out the hologram as a png, and use dither noise
        % so the signal isn't rounded away, since it's only an 8 bit image:
        png_image = zeros(SENSOR_NY, SENSOR_NX);
        downsized_n_pixels = inputs.n_pixels/OVS;
        dither_noise = rand(downsized_n_pixels, downsized_n_pixels) - 0.5;
        downsized = round(PNG_MEAN_AMPLITUDE*imresize(rval.intensity, [down_sz, down_sz], 'box') + dither_noise);
        %png_coord_x = [0:downsized_n_pixels-1] - downsized_n_pixels/2 + SENSOR_NX/2;
        %png_coord_y = [0:downsized_n_pixels-1] - downsized_n_pixels/2 + SENSOR_NY/2;
        %png_image(png_coord_y, png_coord_x) = downsized;
        png_image([1:2048],[1:2048]) = downsized;
        imwrite(uint8(round(png_image)), PNG_FILENAME, 'BitDepth', 8);

        % Then read back in the png and overwrite the original hologram, so
        % we reconstruct the png (dithered) version:
%         png_image_read = single(imread(PNG_FILENAME));
%         downsized_read = png_image_read(png_coord_y, png_coord_x)/PNG_MEAN_AMPLITUDE;
%         I2_down = downsized_read - imresize(abs(rval.ref_wave).^2, [down_sz, down_sz], 'box');    
    end

 
    
end

PlotFrame(rval.intensity,"Sim Hologram - Intensity")
[cx,cy,c] = improfile();
figure(2)
plot(cx,c)
%PlotFrame(rval.obj_wave,"Sim Hologram - Obj Wave")
%PlotFrame(rval.ref_wave,"Sim Hologram - Ref Wave")
%PlotFrame(rval.template_wave,"Sim Hologram - Temp  Wave")