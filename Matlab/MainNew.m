% Main script
clc;
clear all;
close all;

% variables
Zheight = 2e-3; % height of sample volume

% inputs
inputs.z_resolution = 2e-6;
inputs.Sn_pixels = 3000; % must be smaller than small SENSOR_NX/Y
inputs.OVS = 2;

% inputs
inputs.wavelength = 405e-9; % Blue light
inputs.pixel_p = 1.85e-6 / inputs.OVS; % pixel pitch, with oversampling
inputs.n_pixels = inputs.Sn_pixels * inputs.OVS; % size of oversampled region to process
inputs.ref_dist = 12.0e-3; % reference to sensor dist
inputs.samp_dist = 8.14e-3; % sample to sensor dist
inputs.ref_amp = 1; % amplitude of reference wave at sensor
inputs.ref_pos_x = 0; % x position of laser
inputs.ref_pos_y = 0; % y position of laser
inputs.obj_amp = 0.01; % scattered light amplitude at sensor

% Define zoom region of interest:
ROI_x = [-0.5, 0.5] * 1e-3; % mm
ROI_y = [-0.5, 0.5] * 1e-3;
ROI_x_pix = round(inputs.n_pixels / 2 + ROI_x / inputs.pixel_p);
ROI_y_pix = round(inputs.n_pixels / 2 + ROI_y / inputs.pixel_p);

tic;

% Generate Data:
folder = 'DataSets/RealHolograms';
[~, images] = ImportImages(folder, inputs);

% Select a specific hologram image
hologram_image = images(:, :, 1); % Replace 1 with the index of the desired image

% Convert the hologram image to double precision
I = double(hologram_image);

% Set the necessary parameters for the function
I0 = ...; % Reference intensity matrix (should have the same dimensions as I)
R = ...; % Phase term matrix (should have the same dimensions as I)
x = inputs.pixel_p; % Sampling pitch
z = inputs.samp_dist; % Propagation distance
lambda = inputs.wavelength; % Wavelength
T = ...; % Resampling factor

% Call the ReconstructorKanka2 function
O = ReconstructorKanka2(I, I0, R, x, z, lambda, T);

% Display the reconstructed object
imagesc(abs(O));
colormap(gray);
axis image;
title('Reconstructed Object');
