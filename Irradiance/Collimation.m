function R_C = Collimation(x)
% Inputs: [Wavelength(nm),Divergence Angle (rad),Effective Focal Length (mm)]
% Output: Collimated Radius in mm

lambda = x(1)/1e6; % Wavelength [mm]
theta = x(2); % Divergance Angle [rad]
w0 = lambda/(pi*theta); % Initial Waist [mm]
EFL = x(3); % Focal Length [mm]

zR = pi*w0^2/lambda; % Rayleigh Range [mm]
R_C = w0*sqrt(1+(EFL/zR)^2) + 9e-3; % Collimated Radius [mm]
end