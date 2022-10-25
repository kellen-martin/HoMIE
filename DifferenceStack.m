function diffStack = DifferenceStack(images,clean)
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
    y = clean;
    temp = 0;
    i = 1;
    while i < length(images)/2
        temp = temp+(images{i+1}-images{i});
        i = i+2;
    end
    diffStack = temp - AverageImage(images,1,length(images));
end

time = toc;
fprintf('\nDifferenceStack %.2f\n', time)