clc
clear all
close all

%% 
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
%%
% outputs:
% 1 raw frame
% 2 average frame
% 3 clean frame
% 
% 4 difference frame
% 5 difference stack
% 
% 6 detected single frame region
% 7 detected difference frame region
% 8 detected difference stack region
% 
% flags
% 9 summary statistics
% 10 compression
% 11 compression estimation
%%

g = input('Old or New (o/n): ','s');
switch g 
    case 'o'
        fprintf("old\n")
        sampleNum = input("Sample Number: ",'s');
        folder = strcat('DataSets/',sampleNum);
        [~,images] = ImportImages(folder,inputs);
    case 'n'
        fprintf("new\n")

end
stop = 1;
while stop>0
%     done = 'n';
%     if done == 'y'
%         fprintf('done\n')
%         stop = 0;
%     else
        n = input('Option: ');
        switch n
            case 1%raw frame f(frame number)
                fprintf("Raw Frame\n")
                frameNum = input("Frame Number:\n");
                PlotFrame(images{frameNum},'Raw Frame');
            case 2%average frame
                fprintf("Average Frame\n")
                avgFrame = AverageImage(images);
                PlotFrame(avgFrame,'Average Frame');
            case 3
                fprintf("Clean Frames\n")
                avgFrame = AverageImage(images);
                cleanFrame = CleanImages(images,avgFrame);
                for i=1:length(images)
                    PlotFrame(cleanFrame{i},strcat('Clean Frame',num2str(i)));
                end
            case 4%
                fprintf("Difference Frame\n")
                clean = input('Cleaner: (Y=1) ');
                frameA = input('Frame A: ');
                frameB = input('Frame B: ');
                if clean == 1
                    cleaner = AverageImage(images);
                    diffFrame = DifferenceFrame(frameA,frameB,cleaner);
                else
                    diffFrame = DifferenceFrame(frameA,frameB);
                end
                PlotFrame(diffFrame,strcat('Difference Frame (',num2str(frameA),',',num2str(frameB),')'));
            case 5
                fprintf("Difference Stack\n")
                diffStack = (DifferenceStack(images));
                recon = ReconstructorKanka1(diffStack,CalculateTemplate(inputs),inputs,1);
                PlotFrame(recon,'Recon Kanka1',ROI_x,ROI_y,ROI_x_pix,ROI_y_pix);
            case 6
                fprintf("case6\n")
            case 7
                fprintf("case7\n")
            case 8
                fprintf("case8\n")
            case 9
                fprintf("case9\n")
            case 10
                fprintf("case10\n")
            case 11
                fprintf("case11\n")
            case 12
                fprintf("case12\n")
        end
    done = input('Done (y/n): ','s');
    if done == 'y'
        fprintf('done\n')
        stop = 0;
    else
        stop = 1;
    end
end