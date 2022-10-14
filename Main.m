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
[avgImg,map,images] = generateAverageImage(folder);
clean = cleanFrames(images,avgImg);

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

% Generate simulated (oversampled) hologram:
rval = templateMaker(inputs); %return value


tic

for i = 1:5
    [final{i}] = reconFunc(clean{i},Sn_pixels,OVS,inputs,rval);
    clean{i} = 0;
end
% final = importdata('final.mat');

% parfor i = 1:2
%     [final{i}] = PARreconFunc(clean{i},rval);
% end

toc

% images = importdata('images.mat');
% avgImg = importdata('avgImg.mat');

GenerateGraph(1,1,5,images,avgImg,clean,final,ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)

