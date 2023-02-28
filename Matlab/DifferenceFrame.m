function diffFrame = DifferenceFrame(frameA,frameB,cleaner)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Calculates the difference between two frames
%   Algorithm:
%   frameB - frameA
% Optional ability to clean
% Partial (R-DIHM-FUNC-1.2)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Inputs:
%   frameA - frame to be subtracted
%   frameB - frame to be subtracted from
% Optional Inputs:
%   cleaner - specified image used for cleaning
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Outputs: 
% Default:
%   diffFrame - the difference frame found using algorithm defined above
% W/ Optional Inputs:
%   diffFrame - the difference frame found using algorithm defined above
%       and cleaner is also subtracted
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Author:
%   Nick Aichholz
% Last Edited: 10/25/22
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


tic

if nargin == 2
    diffFrame = frameB - frameA;
end
if nargin == 3
    y = cleaner;
    diffFrame = (frameB - frameA) - cleaner;
end

time = toc;
fprintf('\nDifferenceFrame %.2f\n', time)