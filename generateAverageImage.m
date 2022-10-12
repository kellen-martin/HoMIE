function [avgImg,map,images] = generateAverageImage(folder)

path_directory=folder; % 'Folder name'
original_files=dir([path_directory '/*.png']); 
sizeOf = length(original_files);

filename=[path_directory '/' original_files(1).name];
images{1} = single(imread(filename));
  
z = single(zeros(size(images{1})));

for k=1:sizeOf
  filename=[path_directory '/' original_files(k).name];
  images{k} = single(imread(filename));
%   z = imadd(z,images{k});
    z = z + images{k};
end

[~,map] = imread(filename);
avgImg = z ./ sizeOf;
