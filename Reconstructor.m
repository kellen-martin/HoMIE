function [reconstructed] = Reconstructor(image,Zslice,inputs,cleaner)
tic

inputs.ref_dist = inputs.ref_dist + inputs.z_resolution * (Zslice-1);
rval = CalculateTemplate(inputs);

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