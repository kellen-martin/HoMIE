function [final] = PARreconFunc(real,rval)
% Sn_pixels    = 3000;
% OVS = 2; 

% inputs.pixel_p     = 9.2500e-07; % pixel pitch, with oversampling
% inputs.n_pixels    = 6000;    % size of oversampled region to process
% inputs.ref_dist    = 12.0e-3;     % reference to sensor dist
% inputs.samp_dist   = 8.14e-3;     % sample to sensor dist
% inputs.ref_amp     = 1;           % amplitude of reference wave at sensor
% inputs.ref_pos_x   = 0;           % x position of laser
% inputs.ref_pos_y   = 0;           % y position of laser
% inputs.obj_amp     = 0.01;        % scattered light amplitude at sensor

real = single(real(1:3000,1:3000));
real = single(imresize(real,2));

down_sz = 3000; %this is what sensor sees
I2_down = imresize(real - abs(rval.ref_wave).^2, [down_sz, down_sz], 'box'); %find intensity then remove its effect

I2_down_fft = fft2(I2_down); %of data
I2_up_fft   = single(zeros(6000, 6000)); %insert zeros

I2_up_fft(              1:down_sz/2, 1:down_sz/2)         = I2_down_fft(          1:down_sz/2, 1:down_sz/2);
I2_up_fft(end-down_sz/2+1:end      , 1:down_sz/2)         = I2_down_fft(down_sz/2+1:end      , 1:down_sz/2);
I2_up_fft(              1:down_sz/2, end-down_sz/2+1:end) = I2_down_fft(          1:down_sz/2, down_sz/2+1:end);
I2_up_fft(end-down_sz/2+1:end      , end-down_sz/2+1:end) = I2_down_fft(down_sz/2+1:end      , down_sz/2+1:end);
I2_up = ifft2(I2_up_fft);


% Now that we've upsampled, we can despread without causing (much)
% alaising. After this operation, our object term is separated from the
% interference term:  (R O* + R* O) R  ~=  R R O* + O
despread = I2_up.*rval.ref_wave; % 'despreading' the signal
% if there was no interference, microscope would not work

% Begin clearing unused large variables to save memory:
clear I2_up;
clear I2_up_fft;

% Define an "apodizer" to eliminate some annoying edge-induced artifacts from the
% 'apodizer' = windowing function, using it to eliminate unneed stuff
% convolutional reconstruction operation. This crops down the image to just
% a circular central portion. We will also apodize the template:
[X,Y] = meshgrid(single(linspace(-1,1,6000)), single(linspace(-1,1,6000)));
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
final = correlated;
clear despread_fft;
clear template_fft;