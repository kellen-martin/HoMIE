%Eric Dean  
%Autonomous Panel Tracking 
%11/30/2020
%RSX13
%% Clean

clc;clear;close all;

%% Saving & Opening Video

save_file = 'vidsave.mat';
%vid = VideoReader('test_deployment.mov');
videoReader = VideoReader('test_deployment.mov');
video = vision.VideoFileReader('test_deployment.mov');
viewer = vision.VideoPlayer;

%% Playing video and selecting interest regions

c = 1; % frame counter

while ~isDone(video)

    

if c == 1

image = step(video);
figure ; imshow(image); axis image;
pos = getrect(); 

% Get x & y coords of rect
pos(1) = max(floor(pos(1)), 1 ); %min
pos(2) = max(floor(pos(2)), 1 ); 
pos(3) = min(ceil( pos(1) + pos(3) )); %max
pos(4) = min(ceil( pos(2) + pos(4) )); 

% Index into a new image

newimage = image(pos(2) : pos(4) , pos(1) : pos(3) , :);

%figure ; imshow(newimage) ; axis image

% In new image generate and record eigen points (interest points)
I = rgb2gray(newimage);
brisk = detectBRISKFeatures(I);
pointImage = insertMarker(I,brisk.Location,'+','Color','white');  %%most promising
locs = brisk.Location;
%im = rgb2gray(pointImage);
%[features, valid_locations] = extractFeatures(im, brisk); % valid locations is location of each interest point.
figure ; imshow(pointImage) ; axis image

deltaS_vec = size(locs); %locs are tracking points -- pos is interest region

theta = size(brisk); %direction of interest points relative to box vertice



for j = 1:length(locs) % calculating the position vector between the box vertice & tracking points
        for k = 1:2 
        %need to convert coordinates for entire frame
        locs(j,k) = locs(j,k) + pos(1,k) ;
        %calculating the position change in entire frame
        deltaS_vec(j,k)  = locs(j,k) - pos(1,k) ;
       %finding the angle between the interest region & tracking points
        theta(j) = atand(deltaS_vec(j,2) / deltaS_vec(j,1) );
        end
end

c=0;

else %every other frame besides initial
    
%% With direction of every interest point relative to box vertice
%% move interest region towards each point with equal magnitude of F
%break %% take out after this
image = step(video);
pause(0.8);


for i = 1:size(theta)
    
    pos(1) = pos(1) + 0.01*cosd(theta(i)); %pulling vertice in each point direction -- x
    pos(2) = pos(2) + 0.01*sind(theta(i)); % y coord
    
    pos(3) = pos(3)/2; %halving length and width
    pos(4) = pos(4)/2;
    
    RGB = insertShape(image,'FilledRectangle',pos,'Color',{'White'}); %inserting shape as newimage into each iteration
    imshow(RGB); axis image;
    
    
end

% Get x & y coords of rect
pos(1) = max(floor(pos(1)), 1 ); %min
pos(2) = max(floor(pos(2)), 1 ); 
pos(3) = min(ceil( pos(1) + pos(3) )); %max
pos(4) = min(ceil( pos(2) + pos(4) )); 

newimage = image(pos(2) : pos(4) , pos(1) : pos(3) , :); %define new image after each movement
I = rgb2gray(newimage);
brisk = detectBRISKFeatures(I);
    
end %end of if

end %end of while
    
    





%[x,y,button] = ginput(1);
%x = round(x);
%y = round(y);
%plot region of interest as box

%pos = [x y h l];
%rectangle('Position',pos,'EdgeColor','r');
%hold on;
%plot(x,y,'o','Markersize',12,'Linewidth',1.5);


