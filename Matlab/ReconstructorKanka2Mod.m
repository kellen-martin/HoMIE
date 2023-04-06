function [reconstructed] = ReconstructorKanka2Mod(image, zslice, inputs, num_tiles)
    rval = zslice;
    
    I = single(image(1:inputs.Sn_pixels, 1:inputs.Sn_pixels));
    I0 = abs(rval.ref_wave).^2;
    R = rval.ref_wave;
    I = single(imresize(I, inputs.OVS));
    down_sz = inputs.n_pixels / inputs.OVS;
    U = (I - I0) ./ R;
    tile_dimension = down_sz / num_tiles;

    total = single(zeros(down_sz, down_sz));

    for i = 1:num_tiles
        y1 = (i - 1) * tile_dimension + 1;
        for j = 1:num_tiles
            x1 = (j - 1) * tile_dimension + 1;
            x2 = x1 + tile_dimension - 1;
            y2 = y1 + tile_dimension - 1;

            U_tile = U(x1:x2, y1:y2);
            N = size(U_tile, 1);
            T = inputs.OVS;
            NN = N * T;

            % Create an extended array
            U_extended = zeros(NN, NN);

            % Subdivide the array U_tile into T2 identically sized subarrays
            N_sub = N / T;
            for k = 0:(T - 1)
                for l = 0:(T - 1)
                    m = N_sub * k + 1;
                    n = N_sub * l + 1;
                    U_sub = U_tile(m:m + N_sub - 1, n:n + N_sub - 1);

                    % Fourier transform of the subarray
                    FU_sub = fft2(U_sub);

                    % Add the subarray to the extended array
                    m_extended = NN / 2 - N_sub * k;
                    n_extended = NN / 2 - N_sub * l;
                    U_extended(m_extended:m_extended + N_sub - 1, n_extended:n_extended + N_sub - 1) = ...
                        U_extended(m_extended:m_extended + N_sub - 1, n_extended:n_extended + N_sub - 1) + FU_sub;
                end
            end

            % Perform the inverse Fourier transform and compute the object wave in the focal plane
            I2_up_tile = ifft2(U_extended);

            % Reindexing
            nx1 = x1 * 2 - 1;
            nx2 = x2 * 2;
            ny1 = y1 * 2 - 1;
            ny2 = y2 * 2;

            ref_wave_tile = rval.ref_wave(nx1:nx2, ny1:ny2);
            despread_tile = I2_up_tile .* ref_wave_tile;
            total(nx1:nx2, ny1:ny2) = despread_tile;
        end
    end

    [X, Y] = meshgrid(single(linspace(-1, 1, inputs.n_pixels)), single(linspace(-1, 1, inputs.n_pixels)));
    apodizer = single(sqrt(X.^2 + Y.^2) < 1);

    despread = total;
    % Correlate against template, use apodizer
    despread_fft = fft2(despread .* apodizer);
    template_fft = fft2(rval.template_wave .* apodizer);

    % fftshift rearranged image into a state we can understand
    correlated = fftshift(ifft2(despread_fft .* conj(template_fft))); % frequency-domain convolution (correlation)
    reconstructed = correlated;
end