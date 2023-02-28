function [map,images] = ImportImages(folder,inputs)
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
%tic

original_files = dir([folder '/*.png']); 
sizeOf = length(original_files);

filename=[folder '/' original_files(1).name];

images{1} = single(imread(filename));

if nargin == 1
    for k=1:sizeOf
      filename=[folder '/' original_files(k).name];
      images{k} = single(imread(filename));
    end
end
if nargin == 2
    for k=1:sizeOf
      filename=[folder '/' original_files(k).name];
      images{k} = single(imread(filename));
      images{k} = single(images{k}(1:inputs.Sn_pixels,1:inputs.Sn_pixels));
    end
end
    
[~,map] = imread(filename);

%time = toc;
%fprintf('\nImportImages %.2f\n', time)


% avgImg = z ./ sizeOf;
