function expl(image)
% A = figure;
% imagesc(sqrt(abs(image)));
cm=colormap('gray');colormap(cm(end:-1:1,:));
% axis square;

imwrite(sqrt(abs(image)),cm,inputname(1)+".png")
end

% function out = getVarName(var)
%     out = inputname(1);
% end