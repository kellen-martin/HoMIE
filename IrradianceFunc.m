function Irr_D = IrradianceFunc(x)
% Laser
P0 = x(1); % Inital Laser Output Power [mW]
lambda = x(2); % Wavelength [nm]
NA_Laser = x(3); % Laser Numerical Aperture

% Collimator
EFL_Coll = x(4); % Collimator Effective Focal Length [mm]
RC = x(5); % Collimation Radius [mm]
T_f = x(10); % Focus Lens Transmission

% Focus lens
EFL_Focus = x(6); % Focus Lens Effective Focal Length [mm]
T_c = x(11); % Collimator Transmission

% Sample Housing
z_s = x(7); % Focus Point to Sample Housing Distance [mm]
T_s = x(12); % Sample Housing Transmission

% Detector
z = x(8); % Axial Distance from Focus Point to Detector [mm]

r = x(9); % Radial Distance from the beam center [mm]

end