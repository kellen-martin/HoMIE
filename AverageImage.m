function avgImg = AverageImage(images,first,last)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Calculates the average image from a matrix of images
% Optional ability to specify which frames to average over
% (R-DIHM-FUNC-1.1)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Inputs:
%   images - matrix of images
% Optional Inputs:
%   first - specified starting point
%   last - specified ending point
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Outputs: 
% Default:
%   avgImg - average image of entire set of images
% W/ Optional Inputs:
%   avgImg - average image overspecified duration
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Author:
%   Nick Aichholz
% Last Edited: 10/25/22
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

tic

sizeOf = length(images);
z = single(zeros(size(images{1})));

if nargin == 1
    for k=1:sizeOf
        z = z + images{k};
    end
    
    avgImg = z ./ sizeOf;
end

if nargin == 3
    
    for k=first:last
        z = z + images{k};
    end

    avgImg = z ./ sizeOf;
end

time = toc;
fprintf('\nAverageImage %.2f\n', time)


