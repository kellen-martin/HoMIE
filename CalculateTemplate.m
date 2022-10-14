function rval = CalculateTemplate(inputs)

wavelength = inputs.wavelength;
n_pixels   = inputs.n_pixels;
pixel_p    = inputs.pixel_p;
ref_dist   = inputs.ref_dist;
samp_dist  = inputs.samp_dist;
ref_amp    = inputs.ref_amp;
ref_pos_x  = inputs.ref_pos_x;
ref_pos_y  = inputs.ref_pos_y;
obj_amp    = inputs.obj_amp;

template_pos_x = 0;
template_pos_y = 0;
template_pos_z = samp_dist;
pixel_x        = pixel_p*([0:n_pixels-1] - floor(n_pixels/2));
pixel_y        = pixel_p*([0:n_pixels-1] - floor(n_pixels/2));
ref_pos_z      = ref_dist; % what distance is laser from the sample

% Compute the reference wave on the sensor:
template_phase = 2*pi*sqrt((template_pos_x - ref_pos_x)^2 + (template_pos_y - ref_pos_y)^2 + (template_pos_z - ref_pos_z)^2)/wavelength;
ref_wave       = single(zeros(n_pixels, n_pixels));
template_wave  = single(zeros(n_pixels, n_pixels));
for ix = 1:n_pixels
    % (we're only vectorizing over the y axis to save memory)
    x = pixel_x(ix);

    ref_dist         = sqrt((x - ref_pos_x).^2 + (pixel_y - ref_pos_y).^2 + ref_pos_z.^2); % distance from referece to each pixel
    ref_n_waves      = ref_dist/wavelength;
    ref_wave(ix, :)  = single(ref_amp*exp(j*2*pi*ref_n_waves));

    template_dist        = sqrt((x - template_pos_x).^2 + (pixel_y - template_pos_y).^2 + template_pos_z.^2); % distance from template-reference-object to each pixel
    template_n_waves     = template_dist/wavelength;        
    template_wave(ix, :) = single(obj_amp*exp(j*(2*pi*template_n_waves + template_phase)));
end

% Construct the return-value:
rval.template_wave = template_wave; clear template_wave;
rval.ref_wave      = ref_wave; clear ref_wave;




