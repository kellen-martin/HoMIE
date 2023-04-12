function complexMat = readComplexMat(filename, rows, cols)
    data = importdata(filename, ' ');
    realPart = data(:,1:2:end);
    imagPart = data(:,2:2:end);
    complexMat = complex(realPart, imagPart);
    complexMat = reshape(complexMat.', cols, rows).';
end