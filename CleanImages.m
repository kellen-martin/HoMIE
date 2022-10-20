function [clean] = CleanImages(images,avgImg)
% [clean] = array of all clean frames
% images = images takes by image sensor
% avgImg = is the average of 'images'

sizeOf = length(images);

tic

for k=1:sizeOf
    clean{k} = (avgImg - images{k});
end

time = toc;
fprintf('\nTime spent cleaning images: %.2f\n', time)