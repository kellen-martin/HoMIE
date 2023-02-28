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
T_c = 0.98; % Collimator Transmission

% Sample Housing
z_s = 2.5; % Focus Point to Sample Housing Distance [mm]
T_s = 0.9225; % Sample Housing Transmission

% Detector
z = 21; % Axial Distance from Focus Point to Detector [mm]

