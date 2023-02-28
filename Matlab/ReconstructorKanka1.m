function [reconstructed] = ReconstructorKanka1(image,zslice,inputs,num_tiles)
    rval = zslice;
    
    image = single(image(1:inputs.Sn_pixels,1:inputs.Sn_pixels));
    image = single(imresize(image,inputs.OVS));
    down_sz = inputs.n_pixels/inputs.OVS; %this is what sensor sees
    I2_down = imresize(image - abs(rval.ref_wave).^2, [down_sz, down_sz], 'cubic'); %find intensity then remove its effect
    %cubic was originally grid
    tile_dimension = down_sz/num_tiles;
    
    total = single(zeros(down_sz,down_sz));
%     I2_down_tile = I2_down(1:tile_dimension,1:tile_dimension);
    for i = 1:num_tiles
        y1 = (i-1)*tile_dimension+1;
        for j = 1:num_tiles
            x1 = (j-1)*tile_dimension+1;
            x2 = x1 + tile_dimension - 1;
            y2 = y1 + tile_dimension - 1;
            
            I2_down_tile = I2_down(x1:x2,y1:y2);
            I2_down_fft_tile = fft2(I2_down_tile); %of data
            I2_up_fft_tile   = single(zeros(inputs.n_pixels/num_tiles, inputs.n_pixels/num_tiles)); %insert zeros

            I2_up_fft_tile(              1:tile_dimension/2, 1:tile_dimension/2)         = I2_down_fft_tile(          1:tile_dimension/2, 1:tile_dimension/2);
            I2_up_fft_tile(end-tile_dimension/2+1:end      , 1:tile_dimension/2)         = I2_down_fft_tile(tile_dimension/2+1:end      , 1:tile_dimension/2);
            I2_up_fft_tile(              1:tile_dimension/2, end-tile_dimension/2+1:end) = I2_down_fft_tile(          1:tile_dimension/2, tile_dimension/2+1:end);
            I2_up_fft_tile(end-tile_dimension/2+1:end      , end-tile_dimension/2+1:end) = I2_down_fft_tile(tile_dimension/2+1:end      , tile_dimension/2+1:end);
            I2_up_tile = ifft2(I2_up_fft_tile);
            
            %Reindexing
            nx1 = x1*2-1;
            nx2 = x2*2;
            ny1 = y1*2-1;
            ny2 = y2*2;
            
            ref_wave_tile = rval.ref_wave(nx1:nx2,ny1:ny2);
            despread_tile = I2_up_tile.*ref_wave_tile; % 'despreading' the signal
            total(nx1:nx2,ny1:ny2) = despread_tile;
            
            clear I2_up_tile;
            clear I2_up_fft_tile;
        end
    end
    [X,Y] = meshgrid(single(linspace(-1,1,inputs.n_pixels)), single(linspace(-1,1,inputs.n_pixels)));
    apodizer = single(sqrt(X.^2 + Y.^2) < 1);

    clear X;
    clear Y;
    despread = total;
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
