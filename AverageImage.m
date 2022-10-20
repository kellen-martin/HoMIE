function [avgImg,map,images] = AverageImage(folder)

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
