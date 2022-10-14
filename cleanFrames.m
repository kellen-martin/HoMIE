function [clean] = cleanFrames(images,avgImg)
% [clean] = array of all clean frames
% images = images takes by image sensor
% avgImg = is the average of 'images'

sizeOf = length(images);

for k=1:sizeOf
    clean{k} = (avgImg - images{k});
end