function [reconstructed] = Reconstructor(image,zslice,inputs)
    rval = zslice;
%     templateTL = 
    image = single(image(1:inputs.Sn_pixels,1:inputs.Sn_pixels));
    image = single(imresize(image,inputs.OVS));
    down_sz = inputs.n_pixels/inputs.OVS; %this is what sensor sees
    I2_down = imresize(image - abs(rval.ref_wave).^2, [down_sz, down_sz], 'cubic'); %find intensity then remove its effect
    %cubic was originally grid

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
