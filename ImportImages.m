function [map,images] = ImportImages(folder)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Imports images from a specified folder
% (R-DIHM-FUNC-)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Inputs:-
%   folder - name of folder containing images (png)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Outputs: 
%   map - colormap, not really used for much
%   images - matrix of greyscale images from sensor
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Author:
%   Nick Aichholz
% 
% Last Edited: 10/21/22
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

original_files = dir([folder '/*.png']); 
sizeOf = length(original_files);

filename=[folder '/' original_files(1).name];

images{1} = single(imread(filename));

tic

for k=1:sizeOf
  filename=[folder '/' original_files(k).name];
  images{k} = single(imread(filename));
end

[~,map] = imread(filename);

time = toc;
fprintf('\nImportImages %.2f\n', time)


% avgImg = z ./ sizeOf;
