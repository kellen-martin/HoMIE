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
% folder = 'holograms/generatedData3b';
folder = 'holograms/generatedData3b';
[~,images] = ImportImages(folder,inputs);

%% Average
avgImg = AverageImage(images);
PlotFrame(avgImg,'Avg Image')
Writer(avgImg,'avgIMG')

%% Single Frame Reconstruction
recon = Reconstructor(images{1},CalculateTemplate(inputs),inputs);
PlotFrame(recon,'Single Frame',ROI_x,ROI_y,ROI_x_pix,ROI_y_pix);

%% Difference Stack Reconstruction - Original
stack = (DifferenceStack(images));
PlotFrame(stack,'Raw diffStack');
Writer(stack,'stackraw')
reStack = Reconstructor(stack,CalculateTemplate(inputs),inputs);
PlotFrame(reStack,'Recon stack',ROI_x,ROI_y,ROI_x_pix,ROI_y_pix);
% Writer(reStack(ROI_y_pix(1):ROI_y_pix(2),ROI_x_pix(1):ROI_x_pix(2)),'stackrecon')

% diff = DifferenceFrame(images{1},images{2},avgImg);
% PlotFrame(diff,'Raw diffFrame');
% Writer(diffFrame,'diffraw')
% reDiff = Reconstructor(diff,CalculateTemplate(inputs),inputs);
% PlotFrame(reDiff,'Recon diff',ROI_x,ROI_y,ROI_x_pix,ROI_y_pix);
% Writer(recon(ROI_y_pix(1):ROI_y_pix(2),ROI_x_pix(1):ROI_x_pix(2)),'diffrecon')


%%  Difference Stack Reconstruction - Kanka Method 1
% reconKanka = ReconstructorKanka1(diffStack,CalculateTemplate(inputs),inputs,2);
% PlotFrame(reconKanka,'Recon Kanka',ROI_x,ROI_y,ROI_x_pix,ROI_y_pix);
% Writer(reconKanka(ROI_y_pix(1):ROI_y_pix(2),ROI_x_pix(1):ROI_x_pix(2)),'reconKanka')

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

%% Stress Test
% numFrames = 4;
% tic
% for i=1:numFrames
%     inputs.ref_dist = inputs.ref_dist + (i-1)*inputs.z_resolution;
%     template = CalculateTemplate(inputs);
%     reconFrameOG{i} = Reconstructor(images{i},template,inputs);
% end
% toc
% inputs.ref_dist    = 12.0e-3;
% 
% tic
% for i=1:numFrames
%     inputs.ref_dist = inputs.ref_dist + (i-1)*inputs.z_resolution;
%     template = CalculateTemplate(inputs);
%     reconFrameKanka2{i} = ReconstructorKanka1(images{i},template,inputs,2);
% end
% toc
% inputs.ref_dist    = 12.0e-3;
% 
% tic
% for i=1:numFrames
%     inputs.ref_dist = inputs.ref_dist + (i-1)*inputs.z_resolution;
%     template = CalculateTemplate(inputs);
%     reconFrameKanka3{i} = ReconstructorKanka1(images{i},template,inputs,3);
% end
% toc
% inputs.ref_dist    = 12.0e-3;
% 
% g = gpuDevice(1);
% tic
% for i=1:numFrames
%     inputs.ref_dist = inputs.ref_dist + (i-1)*inputs.z_resolution;
%     template = CalculateTemplate(inputs);
%     frame = gpuArray(images{i});
%     reconFrameKanka2GPU{i} = ReconstructorKanka1(frame,template,inputs,2);
% end
% toc
% inputs.ref_dist    = 12.0e-3;
% 
% g = gpuDevice(1);
% tic
% for i=1:numFrames
%     inputs.ref_dist = inputs.ref_dist + (i-1)*inputs.z_resolution;
%     template = CalculateTemplate(inputs);
%     frame = gpuArray(images{i});
%     reconFrameKanka3GPU{i} = ReconstructorKanka1(frame,template,inputs,3);
% end
% toc