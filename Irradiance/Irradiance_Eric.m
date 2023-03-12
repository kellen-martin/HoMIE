% Irradiance Function
% The purpose of this script is to create a beam expansion and irradiance
% model that incorporates distance along the optical axis, and lens
% properties
% 2/27/2023

% Laser Parameters
NA_laser = 0.13/1000; % [mrad -> rad]
Fiber_rad = (9e-6)/2 ; %[um -> m] 1/e^2 point
Out_P = 3/1000 ; % [mW->W]

% Collimator Parameters
%r_c = 0.98/1000 ; %[mm - > m]

% Focus Lens Parameters
%FL_focus = 2/1000 ; %[mm - > m]

% Radius from the laser to the collimator
z = 0:0.5:7.5 ; z = z./1000 ; % [mm - > m]
r_z = z*tan(NA_laser) + Fiber_rad ; 

% Irradiance from the laser to the collimator
Irr_col = Out_P./(pi.*r_z.^2) ; Irr_col = Irr_col./((1000^2)*10);% [W/m^2 -> mw/mm^2]

%%

% Refraction angle from the focus lens
%theta = (r_c/FL_focus) ; % 

% Radius from the focus lens to the image sensor
%z_lensless = 0:2:21 ; % [mm] 
%r_z_lensless = z_lensless*tan(theta) ; 

% Irradiance from the focus lens to the sample housing
%Irr_sens = (Out_P*T_C*T_FL)/(pi*r_z_lensless^2) ; % 



