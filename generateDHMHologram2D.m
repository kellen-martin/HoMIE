function rval = generateDHMHologram2D(inputs)
% Simulates simple inline lensless digital holographic microscope.
% 
%                                 |
%                                 |
%                                 |
%                                 |
%    *   o                        |
%    .   .                        |  sensor
%    .   .                        |
%    .   .                        |
%    .   .                        |
%    .   .
%    .
%    .   { - - - - - - - - - - - -}
%    .            samp_dist
%                     
%    { - - - - - - - - - - - - - -}
%               ref_dist
%
% "inputs" structure members:
%    wavelength    wavelength (m)
%    n_pixels      Number of pixels (in the x direction) ("N" in the literature)
%    pixel_p       pixel pitch (m) ("p" in the literature)
%    ref_dist      sensor to reference distance (m) ("f" in the literature")
%    samp_dist     sensor to sample distance (m) (only used for creating template) ("s" in the literature)
%    ref_amp       reference amplitude
%    ref_pos_x     referece x position (m)
%    ref_pos_y     referece y position (m)
%    obj_amp       object amplitude
%    obj_pos_x     object x positions (m)
%    obj_pos_y     object x positions (m)
%    obj_pos_z     object z positions (m) relative to sensor
%    obj_phase     object phase shift (radians)
%
% Note that objects are just point scaterrers. obj_pos_x/y/z can be
% vectors of object positions. They all share the same amplitude.
%
% The object z positions should be similar to the sample distance, since they will be
% contained within the sample.
%
% rval member definitions:      
%
%   template : a waveform that can be used to correlate against the hologram to
%      reconstruct point scatterers. The hologram needs to be "despread" ie 
%      "demodulated" first by the reference wave.
%
%   pixel_x/y : x/y coordinates of pixels
%
%   intensity = 
%     I = |R + O|^2 = (R + O)(R* + O*) = R R* + R O* + R* O + O O*
%
%   intensity2 = I - R R* = 
%     I2 = R O* + R* O + O O*
%
%   obj_wave : "O" in the literature
%
%   ref_wave : "R" in the literature
%
% Example:
%     inputs.wavelength  = 405e-9;
%     inputs.n_pixels    = 3000;
%     inputs.pixel_p     = 1.85e-6;
%     inputs.ref_dist    = 12e-3;
%     inputs.samp_dist   = 8.14e-3;
%     inputs.ref_amp     = 1;
%     inputs.ref_pos_x   = 0;
%     inputs.ref_pos_y   = 0;
%     inputs.obj_amp     = 0.01;
%     inputs.obj_pos_x   = [0.0];
%     inputs.obj_pos_y   = [0.0];
%     inputs.obj_pos_z   = [8.14e-3];
%     inputs.obj_phase   = [0];
%     
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

wavelength = inputs.wavelength;
n_pixels   = inputs.n_pixels;
pixel_p    = inputs.pixel_p;
ref_dist   = inputs.ref_dist;
samp_dist  = inputs.samp_dist;
ref_amp    = inputs.ref_amp;
ref_pos_x  = inputs.ref_pos_x;
ref_pos_y  = inputs.ref_pos_y;
obj_amp    = inputs.obj_amp;
obj_pos_x  = inputs.obj_pos_x;
obj_pos_y  = inputs.obj_pos_y;
obj_pos_z  = inputs.obj_pos_z;
obj_phase  = inputs.obj_phase;

n_obj          = numel(obj_pos_x);
template_pos_x = 0;
template_pos_y = 0;
template_pos_z = samp_dist;
sensor_w       = n_pixels*pixel_p;
pixel_x        = pixel_p*([0:n_pixels-1] - floor(n_pixels/2));
pixel_y        = pixel_p*([0:n_pixels-1] - floor(n_pixels/2));
ref_pos_z      = ref_dist;

% Note that most of the calculations below can be considered a form of "physical
% optics" modelling.

% Compute the reference-to-object offset phases (phase of the reference wave
% when it hits each object):
obj_offset_phase = zeros(1, n_obj);
for ii = 1:n_obj    
    obj_offset_phase(ii) = 2*pi*sqrt((obj_pos_x(ii) - ref_pos_x)^2 + (obj_pos_y(ii) - ref_pos_y)^2 + (obj_pos_z(ii) - ref_pos_z)^2)/wavelength; 
end

% Compute the reference wave on the sensor:
template_phase = 2*pi*sqrt((template_pos_x - ref_pos_x)^2 + (template_pos_y - ref_pos_y)^2 + (template_pos_z - ref_pos_z)^2)/wavelength;
ref_wave       = single(zeros(n_pixels, n_pixels));
template_wave  = single(zeros(n_pixels, n_pixels));
obj_wave       = single(zeros(n_pixels, n_pixels));
for ix = 1:n_pixels
    % (we're only vectorizing over the y axis to save memory)
    x = pixel_x(ix);

    ref_dist         = sqrt((x - ref_pos_x).^2 + (pixel_y - ref_pos_y).^2 + ref_pos_z.^2); % distance from referece to each pixel
    ref_n_waves      = ref_dist/wavelength;
    ref_wave(ix, :)  = single(ref_amp*exp(j*2*pi*ref_n_waves));

    template_dist        = sqrt((x - template_pos_x).^2 + (pixel_y - template_pos_y).^2 + template_pos_z.^2); % distance from template-reference-object to each pixel
    template_n_waves     = template_dist/wavelength;        
    template_wave(ix, :) = single(obj_amp*exp(j*(2*pi*template_n_waves + template_phase)));

    for ii = 1:n_obj
        obj_dist        = sqrt((x - obj_pos_x(ii)).^2 + (pixel_y - obj_pos_y(ii)).^2 + obj_pos_z(ii).^2); % distance from object to each pixel
        obj_n_waves     = obj_dist/wavelength; % number of wavelengths from object to each pixel
        obj_wave(ix, :) = single(obj_wave(ix, :) + obj_amp*exp(j*(2*pi*obj_n_waves + obj_offset_phase(ii) + obj_phase(ii))));
    end
end

% Construct the return-value:
%  (clearing the variables probably doesn't matter, since they go out of scope)
rval.template_wave = template_wave; clear template_wave;
rval.intensity     = abs(ref_wave + obj_wave).^2;
rval.ref_wave      = ref_wave; clear ref_wave;
rval.obj_wave      = obj_wave; clear obj_wave;




