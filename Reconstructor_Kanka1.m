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
tic

nTiles = 4; % Total tiles will be (nTiles * nTiles)

inputs.ref_dist = inputs.ref_dist + inputs.z_resolution * (zslice-1);

HoloTileSize = (inputs.n_pixels/inputs.OVS)/nTiles;
RefTileSize = inputs.n_pixels;

image = single(image(1:inputs.Sn_pixels,1:inputs.Sn_pixels));
image = single(imresize(image,inputs.OVS));
    
if nargin == 3   % No cleaning argument
end
if nargin == 4   % cleaner argument used
    cleaner = single(cleaner(1:inputs.Sn_pixels,1:inputs.Sn_pixels));
    cleaner = single(imresize(cleaner,inputs.OVS));

    image = image - cleaner;
end

down_sz = inputs.n_pixels/inputs.OVS; %this is what sensor sees
%     I2_down = imresize(image - abs(rval.ref_wave).^2, [down_sz, down_sz], 'box'); %find intensity then remove its effect
% ^^^^ I believe this step is taken care of with the average frame
       % stuff
I2_down = image;

%%%%%%%%%%%%%%%%%%%%%%%%% Split into Tiles here %%%%%%%%%%%%%%%%%%%%%%%%%%%
% current size is 3000 by 3000 here (down_sz)

for i = 1:nTiles
    % Tiles themselves arent saved in memory, finding edges here

    HoloTileStart(i) = floor((i - 1)*HoloTileSize) + 1;
    HoloTileEnd(i) = ceil(i*HoloTileSize);

    RefTileStart(i) = floor((i - 1)*RefTileSize) + 1;
    RefTileEnd(i) = ceil(i*RefTileSize);

end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

TileSum = single(zeros(inputs.n_pixels));
tileSize = floor(HoloTileSize);

for i = 1:nTiles

    for j = 1:nTiles

        %%%%%%%%%%%%%%%%%%%% Each tile processed here %%%%%%%%%%%%%%%%%%%%%

        % upsample each hologram "tile" to same size as reference "patch"
            % make this 6000x6000   <???> 
                % current output size
                % reference wave is then (6000*nTiles)x(6000*nTiles)
                    % LARGE!
                    % maybe calculate the patch of reference as needed
                        % save memory                        

        % multiply this with ref wave and add to sum

        % Selecting tile and allocating reference wave patch
        tile_down_fft = fft2(I2_down(HoloTileStart(i):HoloTileEnd(i), HoloTileStart(j):HoloTileEnd(j)));
        patch = single(zeros(inputs.n_pixels));

        % CALCULATE REFERENCE PATCH HERE ----------------------------------
        

            
                %           < CODE NOT DONE YET >

                

        % -----------------------------------------------------------------

        tile_up_fft   = single(zeros(inputs.n_pixels));

        tile_up_fft(              1:tileSize/2, 1:tileSize/2)         = tile_down_fft(          1:tileSize/2, 1:tileSize/2);
        tile_up_fft(end-tileSize/2+1:end      , 1:tileSize/2)         = tile_down_fft(tileSize/2+1:end      , 1:tileSize/2);
        tile_up_fft(              1:tileSize/2, end-tileSize/2+1:end) = tile_down_fft(          1:tileSize/2, tileSize/2+1:end);
        tile_up_fft(end-tileSize/2+1:end      , end-tileSize/2+1:end) = tile_down_fft(tileSize/2+1:end      , tileSize/2+1:end);

        tile_up = ifft2(tile_up_fft); % Upsampled tile

        TileSum = TileSum + tile_up.*patch;

        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    end

end



% Begin clearing unused large variables to save memory:
clear tile_up;
clear tile_up_fft;
clear patch;
clear tile_down_fft;

[X,Y] = meshgrid(single(linspace(-1,1,inputs.n_pixels)), single(linspace(-1,1,inputs.n_pixels)));
apodizer = single(sqrt(X.^2 + Y.^2) < 1);

clear X;
clear Y;

% Correlate against template, use apodizer
despread_fft = fft2(TileSum.*apodizer);
template_fft = fft2(template_wave.*apodizer);
clear apodizer;
clear despread;

% fftshift rearranged image into a state we can understand
correlated = fftshift(ifft2(despread_fft.*conj(template_fft))); % frequency-domain convolution (correlation)
reconstructed = correlated;
clear despread_fft;
clear template_fft;             

time = toc;
fprintf('\nReconstructor %.2f\n', time)