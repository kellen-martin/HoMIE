function diffFrame = DifferenceFrame(frameA,frameB,clean)
tic


if nargin == 2
    diffFrame = frameB - frameA;
end
if nargin == 3
    y = clean;
    diffFrame = (frameB - frameA) - ((frameB+frameA)./2);
end
time = toc;
fprintf('\nDifferenceFrame %.2f\n', time)