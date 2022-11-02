function [reconstructed] = Reconstructor_Kanka1(image,zslice,inputs,cleaner)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Reconstruct an image at a specified instant and zslice
% Optional ability to clean before reconstruction
% (R-DIHM-FUNC-1.2)
% Partial (R-DIHM-FUNC-1.3)
% Partial (R-DIHM-FUNC-1.4)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Inputs:
%   image - specified image
%   zslice - specified Zslice
%   inputs - structure containing information from main
% Optional Inputs:
%   cleaner - specified image used for cleaning
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Outputs: 
% Default:
%   reconstructed - reconstructed frame at a specified instant and zslice
% W/ Optional Inputs:
%   reconstructed - reconstructed frame at a specified instant and zslice
%       that has been cleaned
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Author:
%   Nick Aichholz
% Last Edited: 10/25/22
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

nTiles = 4; % Total tiles will be (nTiles * nTiles)

tic

inputs.ref_dist = inputs.ref_dist + inputs.z_resolution * (zslice-1);
rval = CalculateTemplate(inputs);

HoloTileSize = (inputs.n_pixels/inputs.OVS)/nTiles;
RefTileSize = (size(rval.ref_wave, 1))/nTiles;

if nargin == 3   % if the number of inputs equals 2
    image = single(image(1:inputs.Sn_pixels,1:inputs.Sn_pixels));
    image = single(imresize(image,inputs.OVS));

%     cleaner = single(cleaner(1:inputs.Sn_pixels,1:inputs.Sn_pixels));
%     cleaner = single(imresize(cleaner,inputs.OVS));
% 
%     image = image - cleaner;

    down_sz = inputs.n_pixels/inputs.OVS; %this is what sensor sees
    I2_down = imresize(image - abs(rval.ref_wave).^2, [down_sz, down_sz], 'box'); %find intensity then remove its effect

    I2_down_fft = fft2(I2_down); %of data
    I2_up_fft   = single(zeros(inputs.n_pixels, inputs.n_pixels)); %insert zeros

    %inverse fft to oversample
    I2_up_fft(              1:down_sz/2, 1:down_sz/2)         = I2_down_fft(          1:down_sz/2, 1:down_sz/2);
    I2_up_fft(end-down_sz/2+1:end      , 1:down_sz/2)         = I2_down_fft(down_sz/2+1:end      , 1:down_sz/2);
    I2_up_fft(              1:down_sz/2, end-down_sz/2+1:end) = I2_down_fft(          1:down_sz/2, down_sz/2+1:end);
    I2_up_fft(end-down_sz/2+1:end      , end-down_sz/2+1:end) = I2_down_fft(down_sz/2+1:end      , down_sz/2+1:end);
    I2_up = ifft2(I2_up_fft);

    despread = I2_up.*rval.ref_wave; % 'despreading' the signal
    % if there was no interference, microscope would not work

    % Begin clearing unused large variables to save memory:
    clear I2_up;
    clear I2_up_fft;

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
    correlated = fftshift(ifft2(despread_fft.*conj(template_fft))); % frequency-domain convolution (correlation)
    reconstructed = correlated;
    clear despread_fft;
    clear template_fft;             
end
if nargin == 4   % if the number of inputs equals 2
    image = single(image(1:inputs.Sn_pixels,1:inputs.Sn_pixels));
    image = single(imresize(image,inputs.OVS));

    cleaner = single(cleaner(1:inputs.Sn_pixels,1:inputs.Sn_pixels));
    cleaner = single(imresize(cleaner,inputs.OVS));

    image = image - cleaner;

    down_sz = inputs.n_pixels/inputs.OVS; %this is what sensor sees
    I2_down = imresize(image - abs(rval.ref_wave).^2, [down_sz, down_sz], 'box'); %find intensity then remove its effect

    %%%%%%%%%%%%%%%%%%%%%%% Split into Tiles here %%%%%%%%%%%%%%%%%%%%%%%%%
    % current size is 3000 by 3000 here (down_sz)
    
    for i = 1:nTiles
        % Tiles themselves arent saved in memory, finding edges here
        
        HoloTileStart(i) = floor((i - 1)*HoloTileSize) + 1;
        HoloTileEnd(i) = ceil(i*HoloTileSize);
        
        RefTileStart(i) = floor((i - 1)*RefTileSize) + 1;
        RefTileEnd(i) = ceil(i*RefTileSize);
        
    end
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    I2_down_fft = fft2(I2_down); %of data
    I2_up_fft   = single(zeros(inputs.n_pixels, inputs.n_pixels)); %insert zeros

    %inverse fft to oversample
    I2_up_fft(              1:down_sz/2, 1:down_sz/2)         = I2_down_fft(          1:down_sz/2, 1:down_sz/2);
    I2_up_fft(end-down_sz/2+1:end      , 1:down_sz/2)         = I2_down_fft(down_sz/2+1:end      , 1:down_sz/2);
    I2_up_fft(              1:down_sz/2, end-down_sz/2+1:end) = I2_down_fft(          1:down_sz/2, down_sz/2+1:end);
    I2_up_fft(end-down_sz/2+1:end      , end-down_sz/2+1:end) = I2_down_fft(down_sz/2+1:end      , down_sz/2+1:end);
    I2_up = ifft2(I2_up_fft);

    despread = I2_up.*rval.ref_wave; % 'despreading' the signal
    % if there was no interference, microscope would not work

    % Begin clearing unused large variables to save memory:
    clear I2_up;
    clear I2_up_fft;

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
    correlated = fftshift(ifft2(despread_fft.*conj(template_fft))); % frequency-domain convolution (correlation)
    reconstructed = correlated;
    clear despread_fft;
    clear template_fft;             
end

time = toc;
fprintf('\nReconstructor %.2f\n', time)