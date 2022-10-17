% Run main first!

ROI_x = [-0.25,0.25]*1e-3; %mm
ROI_y = [-0.75,0.25]*1e-3;
ROI_x_pix = round(inputs.n_pixels/2 + ROI_x/inputs.pixel_p);
ROI_y_pix = round(inputs.n_pixels/2 + ROI_y/inputs.pixel_p);

GenerateGraphMOD(1,1,5,3,images,avgImg,clean,final,ROI_x,ROI_y,ROI_x_pix,ROI_y_pix)