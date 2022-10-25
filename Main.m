clc
clear all
close all

OVS = 2; 
Sn_pixels          = 3000; % must be smaller than small SENSOR_NX/Y


% inputs for template maker
inputs.wavelength  = 405e-9;      % Blue light
inputs.pixel_p     = 1.85e-6/OVS; % pixel pitch, with oversampling
inputs.n_pixels    = Sn_pixels*OVS;    % size of oversampled region to process
inputs.ref_dist    = 12.0e-3;     % reference to sensor dist
inputs.samp_dist   = 8.14e-3;     % sample to sensor dist
inputs.ref_amp     = 1;           % amplitude of reference wave at sensor
inputs.ref_pos_x   = 0;           % x position of laser
inputs.ref_pos_y   = 0;           % y position of laser
inputs.obj_amp     = 0.01;        % scattered light amplitude at sensor

inputs.z_resolution= 2e-6;
inputs.Sn_pixels   = 3000;
inputs.OVS         = 2;

% Define zoom region of interest:
ROI_x = [-0.5,0.5]*1e-3; %mm
ROI_y = [-0.5,0.5]*1e-3;
ROI_x_pix = round(inputs.n_pixels/2 + ROI_x/inputs.pixel_p);
ROI_y_pix = round(inputs.n_pixels/2 + ROI_y/inputs.pixel_p);

% Generate Data:
folder = 'Images';
[~,images] = ImportImages(folder);

avgImg = AverageImage(images,1,length(images));
PlotFrame(avgImg,'average')

diffFrame = DifferenceFrame(images{1},images{2});
PlotFrame(diffFrame,'diffFrame')

diffFrameC = DifferenceFrame(images{1},images{2},1);
PlotFrame(diffFrameC,'diffFrameClean')

diffStack = DifferenceStack(images);
PlotFrame(diffStack,'diffStack')

diffStackC = DifferenceStack(images,1);
PlotFrame(diffStackC,'diffStackClean')

% reconavgImg = ReconstructImages(avgImg,Sn_pixels,OVS,inputs,CalculateTemplate(inputs));
% PlotFrame(reconavgImg,ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)

reconavgImg = Reconstructor(avgImg,1,inputs);
PlotFrame(reconavgImg,'avgImg',ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)

reconavgImgC = Reconstructor(avgImg,1,inputs,avgImg);
PlotFrame(reconavgImg,'avgImgClean',ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)

recondiffFrame = Reconstructor(diffFrame,1,inputs);
PlotFrame(recondiffFrame,'recondiffFrame',ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)

recondiffFrameC = Reconstructor(diffFrame,1,inputs,AverageImage(images,1,2));
PlotFrame(recondiffFrameC,'recondiffFrameClean',ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)

recondiffFrameC2 = Reconstructor(diffFrameC,1,inputs);
PlotFrame(recondiffFrameC2,'recondiffFrameClean2',ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)

recondiffStack = Reconstructor(diffStack,1,inputs);
PlotFrame(recondiffStack,'recondiffStack',ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)

recondiffStackC = Reconstructor(diffStack,1,inputs,avgImg);
PlotFrame(recondiffStackC,'recondiffStackClean',ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)

recondiffStackC2 = Reconstructor(diffStackC,1,inputs);
PlotFrame(recondiffStackC2,'recondiffStackClean',ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)
