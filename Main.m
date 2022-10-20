clc
clear all
close all

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Main Script
%
% Authors: 
%   Nick Aichholz
%   Ryan Jones
%   Kellen Martin
%
% Last Edited: 10/12/22
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Image Reconstruction 

% Generate Data:
folder = 'Images';
[avgImg,~,images] = AverageImage(folder);
clean = CleanImages(images,avgImg);

% Load Data:
% images = importdata('images.mat');
% avgImg = importdata('avgImg.mat');
% clean = importdata('clean.mat');

% Variables
PNG_MEAN_AMPLITUDE = 128; % average pixel amplitude in file to minimize "clipping"
PNG_FILENAME = "simulated_hologram.png";
WRITE_HOLOGRAM_PNG = false;
NEWCASE = false;

OVS = 2; 
Sn_pixels          = 3000; % must be smaller than small SENSOR_NX/Y

% physical specs
SENSOR_NX          = 4024;  
SENSOR_NY          = 3036;
inputs.wavelength  = 405e-9;      % Blue light

% computationally intensive
z_resolution       = 2e-6;        % resolution of microscope
num_z_slices       = 20;          % this will depend on the height of the sample volume
num_of_frames      = 5;

% inputs for template maker
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

% Generate z-slice templates:
inputs.ref_dist(1) = inputs.ref_dist;
for j = 1:num_z_slices
    inputs.ref_dist = inputs.ref_dist + z_resolution * (j-1);
    template(j) = CalculateTemplate(inputs); %return value
end

% Load Data:
% template = importdata('template.mat');

% Cuts down processing time
for c = num_of_frames+1:length(clean)
    clean{c} = 0;
end

% Calculates the final reconstructed images
tic
for j = 1:num_of_frames
    for i = 1:10 %
        [reconstructed{i,j}] = ReconstuctImages(clean{j},Sn_pixels,OVS,inputs,template(i));
    end
    clean{j} = 0;
end
toc

GenerateGraphMOD(1,1,5,3,images,avgImg,clean,reconstructed,ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)