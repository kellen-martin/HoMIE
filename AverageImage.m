function [avgImg,map,images] = AverageImage(folder)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Calculates the average image of a folder of images
% (R-DIHM-FUNC-)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Inputs:-
%   folder - name of folder containing images (png)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Outputs: 
%   avgImg - single matrix that is the average frame of all the images
%   map - colormap, not really used for much
%   images - a matrix of greyscale images from sensor
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Author:
%   Nick 
% 
% Last Edited: 10/21/22
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

original_files = dir([folder '/*.png']); 
sizeOf = length(original_files);

filename=[folder '/' original_files(1).name];

images{1} = single(imread(filename));
  
z = single(zeros(size(images{1})));

tic

for k=1:sizeOf
  filename=[folder '/' original_files(k).name];
  images{k} = single(imread(filename));
%   z = imadd(z,images{k});
    z = z + images{k};
end

time = toc;
fprintf('\nTime spent averaging images: %.2f\n', time)

[~,map] = imread(filename);
avgImg = z ./ sizeOf;
