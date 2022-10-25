function [avgImg,map,images] = ParAverageImage(folder)

original_files = dir([folder '/*.png']); 
names = {original_files.name};
sizeOf = length(names);

images(1:sizeOf) = gpuArray({zeros(3036, 4024, 'uint8')});

sumCont = gpuArray(zeros(1, sizeOf));

tic

parfor k = 1:sizeOf
  filename = [folder '/' names{k}];
  images{k} = single(imread(filename));
  sumCont(k) = images{k}/sizeOf;
end

avgImg = sum(sumCont);


time = toc;
fprintf('\nTime spent averaging images: %.2f\n', time)

