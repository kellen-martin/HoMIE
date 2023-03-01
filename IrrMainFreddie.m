%% Housekeeping
clc
clear all
close all

%% Constants
% Laser
P0 = 3; % Laser Output Power [mW]
lambda = 405; % Wavelength [nm]
NA_laser = 0.13; % Laser Numerical Aperture 

% Collimator
EFL_Coll = 7.5; % Collimator Effective Focal Length [mm]
RC = Collimation([lambda,asin(NA_laser),EFL_Coll]); % Collimated Radius [mm]
T_f = 0.95; % Focus Lens Transmission

% Focus lens
EFL_Focus = 2; % Focus Lens Effective Focal Length [mm]
n = 1.5168; % Refractive Index
T_c = 0.98; % Collimator Transmission

% Sample Housing
z_s = 2.5; % Focus Point to Sample Housing Distance [mm]
T_s = 0.9225; % Sample Housing Transmission

% Detector
z = 21; % Axial Distance from Focus Point to Detector [mm]

r = 0:0.01:12;
Irr_D = zeros(length(r),1);

for i = 1:length(r)
    x = [P0,lambda,RC,EFL_Focus,z_s,z,r(i),T_c,T_f,T_s,n];
    Irr_D(i) = IrradianceFunc(x);
end

figure
hold on
plot(r,Irr_D,'b','LineWidth',2)
plot(-r,Irr_D,'b','LineWidth',2)
xline(11.264/2,'--r','LineWidth',2)
xline(-11.264/2,'--r','LineWidth',2)
xlabel('Radial Distance [mm]')
ylabel('Irradiance [mW/mm^2]')
title('Irradiance at Detector')

[~,i_max] = max(Irr_D);
[~,i_min] = min(abs(r-11.264/2));

fprintf('The maximum Irradiance is %0.4f mW/mm^2 \n',Irr_D(i_max))
fprintf('The minimum Irradiance is %0.4f mW/mm^2 \n',Irr_D(i_min))
