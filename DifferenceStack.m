function diffStack = DifferenceStack(images,cleaner)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Calculates the difference stack
%   Algorithm:
%   frameA, frameB, frameC, frameD...
%   (frameB - frameA) + (frameD - frameC) + ...
% Optional ability to clean
% Partial (R-DIHM-FUNC-1.3)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Inputs:
%   images - matrix of images
% Optional Inputs:
%   cleaner - specified image used for cleaning
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Outputs: 
% Default:
%   diffStack - the difference stack found using the algorithm  defined
%       above
% W/ Optional Inputs:
%   diffFrame - the difference between frame A and B and the cleaner frame
%       is also subtracted
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Author:
%   Nick Aichholz
% Last Edited: 10/25/22
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

tic

if nargin == 1
    temp = 0;
    i = 1;
    while i < length(images)/2
        temp = temp+(images{i+1}-images{i});
        i = i+2;
    end

    diffStack = temp;
end
if nargin == 2
    y = cleaner;
    temp = 0;
    i = 1;
    while i < length(images)/2
        temp = temp+(images{i+1}-images{i});
        i = i+2;
    end
    diffStack = temp - cleaner;
end

time = toc;
fprintf('\nDifferenceStack %.2f\n', time)