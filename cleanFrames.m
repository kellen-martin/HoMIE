function [clean] = cleanFrames(images,avgImg)

% path_directory=folder; % 'Folder name'
% original_files=dir([path_directory '/*.png']); 
sizeOf = length(images);

for k=1:sizeOf
%   filename=[path_directory '/' original_files(k).name];
%   [image_orginalTemp{k},map{k}] = imread(filename);
% %   gsImg{k} = rgb2gray(image_orginalTemp{k})
%   image{k} = single(image_orginalTemp{k});
  clean{k} = (avgImg - images{k});
end
% function [clean] = cleanFrames(folder,avgImg)
% 
% path_directory=folder; % 'Folder name'
% original_files=dir([path_directory '/*.png']); 
% sizeOf = length(original_files);
% 
% for k=1:sizeOf
%   filename=[path_directory '/' original_files(k).name];
%   [image_orginalTemp{k},map{k}] = imread(filename);
% %   gsImg{k} = rgb2gray(image_orginalTemp{k})
%   image_orginal{k} = single(image_orginalTemp{k});
%   clean{k} = (avgImg - image_orginal{k});
% end