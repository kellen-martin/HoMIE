function Irr_D = IrradianceFunc(x)
% Laser
P0 = x(1); % Inital Laser Output Power [mW]
lambda = x(2)*1e-6; % Wavelength [mm]

% Collimator
RC = x(3); % Collimation Radius [mm]
T_f = x(8); % Focus Lens Transmission

% Focus lens
EFL_Focus = x(4); % Focus Lens Effective Focal Length [mm]
T_c = x(9); % Collimator Transmission
n = x(11);

% Sample Housing
z_s = x(5); % Focus Point to Sample Housing Distance [mm]
T_s = x(10); % Sample Housing Transmission

% Detector
z = x(6); % Axial Distance from Focus Point to Detector [mm]

r = x(7); % Radial Distance from the beam center [mm]

w0 = lambda*EFL_Focus/(pi*RC); % Initial Waist [mm]
I0 = 2*P0*T_c*T_f*T_s/(pi*w0^2); % Initial Irradiance [mW/mm^2]
zR = pi*w0^2*n/lambda; % Rayleigh Range [mm]
wz = w0*sqrt(1+(z/zR)^2); % Waist at the Detector [mm]

Irr_D = I0*(w0/wz)^2*exp(-2*r^2/wz^2); % Irradiance at the detector [mW/mm^2]
end