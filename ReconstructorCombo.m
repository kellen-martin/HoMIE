function [reconstructed] = ReconstructorCombo(image,zslice,inputs,nTiles)
rval = zslice;
image = single(image(1:inputs.Sn_pixels,1:inputs.Sn_pixels));
image = single(imresize(image,inputs.OVS));
down_sz = inputs.n_pixels/inputs.OVS; %this is what sensor sees
I2_down = imresize(image - abs(rval.ref_wave).^2, [down_sz, down_sz], 'cubic'); %find intensity then remove its effect
%cubic was originally grid

if nargin == 3   % Not using Kanka 1 method
    I2_down_fft = fft2(I2_down); %of data
    I2_up_fft   = single(zeros(inputs.n_pixels, inputs.n_pixels)); %insert zeros

    I2_up_fft(              1:down_sz/2, 1:down_sz/2)         = I2_down_fft(          1:down_sz/2, 1:down_sz/2);
    I2_up_fft(end-down_sz/2+1:end      , 1:down_sz/2)         = I2_down_fft(down_sz/2+1:end      , 1:down_sz/2);
    I2_up_fft(              1:down_sz/2, end-down_sz/2+1:end) = I2_down_fft(          1:down_sz/2, down_sz/2+1:end);
    I2_up_fft(end-down_sz/2+1:end      , end-down_sz/2+1:end) = I2_down_fft(down_sz/2+1:end      , down_sz/2+1:end);
    I2_up = ifft2(I2_up_fft);

    despread = I2_up.*rval.ref_wave; % 'despreading' the signal
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
if nargin == 4   % First Kanka method
    
    HoloTileSize = (inputs.n_pixels/inputs.OVS)/nTiles;
    RefTileSize = inputs.n_pixels;

    image = single(image(1:inputs.Sn_pixels,1:inputs.Sn_pixels));
    image = single(imresize(image,inputs.OVS));

    down_sz = inputs.n_pixels/inputs.OVS; %this is what sensor sees
    I2_down = imresize(image - abs(rval.ref_wave).^2, [down_sz, down_sz], 'box'); %find intensity then remove its effect
    % ^^^^ I believe this step is taken care of with the average frame
           % stuff
    % I2_down = image;

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
    ref_pixel_p = inputs.pixel_p/nTiles;

    for i = 1:nTiles % Tiles in the y-direction

        for j = 1:nTiles % Tiles in the x-direction

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
            patch = single(zeros(RefTileSize));

            % CALCULATE REFERENCE PATCH HERE ----------------------------------

                pixel_x   = ref_pixel_p*([RefTileStart(j)-1:RefTileEnd(j)-1] - floor(inputs.n_pixels*nTiles/2));
                pixel_y   = ref_pixel_p*([RefTileStart(i)-1:RefTileEnd(i)-1] - floor(inputs.n_pixels*nTiles/2));
                ref_pos_z = inputs.ref_dist;


                for ix = 1:RefTileSize

                    x = pixel_x(ix);

                    ref_dist     = sqrt((x - inputs.ref_pos_x).^2 + (pixel_y - inputs.ref_pos_y).^2 + ref_pos_z.^2);
                    ref_n_waves  = ref_dist/inputs.wavelength;
                    patch(ix, :) = single(inputs.ref_amp*exp(1i*2*pi*ref_n_waves));

                end

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

    % CALCULATE TEMPLATE WAVE HERE --------------------------------------------
        % Can't calculate with the reference wave due to different pixel
        % positions

        template_pos_x = 0;
        template_pos_y = 0;
        template_pos_z = inputs.samp_dist;
        pixel_x = inputs.pixel_p*([0:inputs.n_pixels-1] - floor(inputs.n_pixels/2));
        pixel_y = inputs.pixel_p*([0:inputs.n_pixels-1] - floor(inputs.n_pixels/2));

        template_phase = 2*pi*sqrt((template_pos_x - inputs.ref_pos_x)^2 + (template_pos_y - inputs.ref_pos_y)^2 + (template_pos_z - inputs.ref_dist)^2)/inputs.wavelength;

        for ix = 1:inputs.n_pixels

            x = pixel_x(ix);

            template_dist        = sqrt((x - template_pos_x).^2 + (pixel_y - template_pos_y).^2 + template_pos_z.^2); % distance from template-reference-object to each pixel
            template_n_waves     = template_dist/inputs.wavelength;        
            template_wave(ix, :) = single(inputs.obj_amp*exp(1i*(2*pi*template_n_waves + template_phase)));

        end

    % -------------------------------------------------------------------------


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
end
           
