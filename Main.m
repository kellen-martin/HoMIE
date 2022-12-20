clc
clear all
close all

% variables
Zheight            = 2e-3;        % height of sample volume

%inputs
inputs.z_resolution= 2e-6;
inputs.Sn_pixels   = 3000;        % must be smaller than small SENSOR_NX/Y
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

% Define zoom region of interest:
ROI_x = [-0.5,0.5]*1e-3; %mm
ROI_y = [-0.5,0.5]*1e-3;
ROI_x_pix = round(inputs.n_pixels/2 + ROI_x/inputs.pixel_p);
ROI_y_pix = round(inputs.n_pixels/2 + ROI_y/inputs.pixel_p);

tic

% Generate Data:
folder = 'Images';
[~,images] = ImportImages(folder,inputs);

%% Average
avgImg = AverageImage(images);
% PlotFrame(avgImg,'Avg Image')

%% Single Frame Reconstruction
% recon = Reconstructor(images{1}-avgImg,CalculateTemplate(inputs),inputs);

%% Difference Stack Reconstruction - Original
diffStack = (DifferenceStack(images));
% PlotFrame(diffStack,'Raw diffStack');
% Writer(diffStack,'raw')

recon = Reconstructor(diffStack,CalculateTemplate(inputs),inputs);
PlotFrame(recon,'Recon OG',ROI_x,ROI_y,ROI_x_pix,ROI_y_pix);
% Writer(recon(ROI_y_pix(1):ROI_y_pix(2),ROI_x_pix(1):ROI_x_pix(2)),'recon')

%%  Difference Stack Reconstruction - Kanka Method 1
% reconKanka = ReconstructorKanka1(diffStack,CalculateTemplate(inputs),inputs,2);
% PlotFrame(reconKanka,'Recon Kanka',ROI_x,ROI_y,ROI_x_pix,ROI_y_pix);

%% Difference Stack Reconstruction - Original - GPU Method
% g = gpuDevice(1);
% 
% diffStack = DifferenceStack(images);
% diffStack = gpuArray(diffStack);
% recon = Reconstructor(diffStack,CalculateTemplate(inputs),inputs);

%% Z-slice Animation Demonstration
%varies z-slice, keeps time constant
% numFrames = 4;
% for i=1:numFrames
%     inputs.ref_dist = inputs.ref_dist + (i-1)*inputs.z_resolution;
%     template = CalculateTemplate(inputs);
%     reconFrame{i} = Reconstructor(images{i},template,inputs);
% end
% animationRec = AnimationZ(reconFrame,numFrames,ROI_x,ROI_y,ROI_x_pix,ROI_y_pix);
% figure;
% movie(animationRec,2,2)

