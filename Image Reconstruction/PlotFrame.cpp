#include "defs.cpp"
#include "dtypes.cpp"

using namespace std;
using namespace cv;

float ROI_x[2] = {-0.5*1e-3, 0.5*1e-3};
float ROI_y[2] = {-0.5*1e-3, 0.5*1e-3};
int ROI_x_pix[2] = {(int)n_pixels/2 + (int)(ROI_x[0]/pixel_p), (int)n_pixels/2 + (int)(ROI_x[1]/pixel_p)};
int ROI_y_pix[2] = {(int)n_pixels/2 + (int)(ROI_y[0]/pixel_p), (int)n_pixels/2 + (int)(ROI_y[1]/pixel_p)};

void PlotFrame(Mat& image, string title)
{
    Mat new_image = image.clone();
    // applyColorMap(image, new_image, COLORMAP_BONE);
    new_image = 255 - new_image; // apply reverse grayscale colormap
    double max, min;
    Point minLoc, maxLoc;
    minMaxLoc(new_image, &min, &max, &minLoc, &maxLoc);
    if(verbose) cout << "   max: " << max << endl;
    if(verbose) cout << "   min: " << min << endl;
    double scale = 255/max;
    new_image.convertTo(new_image, CV_8UC1, scale);

    Rect roi(ROI_x_pix[0], ROI_y_pix[0], ROI_x_pix[1], ROI_y_pix[1]);
    Mat image_ROI = new_image(roi);

    imshow(title, image_ROI);
    waitKey(0);

    return;
}

void PlotFrame(Mat& image, string title, bool ROI) 
{// option to plot the whole image, not just roi

    if(ROI){PlotFrame(image, title);}
    else
    {   

        Mat new_image = image.clone();
        // applyColorMap(image, new_image, COLORMAP_BONE);
        new_image = 255 - new_image; // apply reverse grayscale colormap
        double max, min;
        Point minLoc, maxLoc;
        minMaxLoc(new_image, &min, &max, &minLoc, &maxLoc);
        if(verbose) cout << "   max: " << max << endl;
        if(verbose) cout << "   min: " << min << endl;
        double scale = 255/max;
        new_image.convertTo(new_image, CV_8UC1, scale);

        imshow(title, new_image);
        waitKey(0);

    }

    return;

}

void PlotFrame(Mat& image, string title, string filename)
{// save image to file

    Mat new_image = image.clone();
    // applyColorMap(image, new_image, COLORMAP_BONE);
    new_image = 255 - new_image; // apply reverse grayscale colormap
    double max, min;
    Point minLoc, maxLoc;
    minMaxLoc(new_image, &min, &max, &minLoc, &maxLoc);
    if(verbose) cout << "   max: " << max << endl;
    if(verbose) cout << "   min: " << min << endl;
    double scale = 255/max;
    new_image.convertTo(new_image, CV_8UC1, scale);

    Rect roi(ROI_x_pix[0], ROI_y_pix[0], ROI_x_pix[1], ROI_y_pix[1]);
    Mat image_ROI = new_image(roi);

    imshow(title, image_ROI);
    waitKey(0);

    filename = output_folder + "/" + filename;
    imwrite(filename, image_ROI);

    return;

}

void PlotFrame(Mat& image, string title, string filename, bool ROI)
{// option to plot the whole image, not just roi
 // save image to file

    if(ROI){PlotFrame(image, title, filename);}
    else
    {   

        Mat new_image = image.clone();
        new_image.convertTo(new_image, CV_8UC1);
        applyColorMap(new_image, new_image, COLORMAP_BONE);
        // new_image = 255 - new_image; // apply reverse grayscale colormap
        // double max, min;
        // Point minLoc, maxLoc;
        // minMaxLoc(new_image, &min, &max, &minLoc, &maxLoc);
        // if(verbose) cout << "   max: " << max << endl;
        // if(verbose) cout << "   min: " << min << endl;
        // double scale = 255/max;
        // new_image.convertTo(new_image, CV_8UC1, scale);

        imshow(title, new_image);
        waitKey(0);

        filename = output_folder + "/" + filename;
        imwrite(filename, new_image);

    }
    

    return;

}

void PlotFrame(Mat& image, string title, string filename, bool ROI, bool SAVE_ONLY)
{// option to plot the whole image, not just roi
 // save image to file
 // will not use imshow to display image, just saves to a file

    if(!SAVE_ONLY){PlotFrame(image, title, filename, ROI);}
    else
    {

        Mat new_image = image.clone();
        // applyColorMap(image, new_image, COLORMAP_BONE);
        new_image = 255 - new_image; // apply reverse grayscale colormap
        double max, min;
        Point minLoc, maxLoc;
        minMaxLoc(new_image, &min, &max, &minLoc, &maxLoc);
        if(verbose) cout << "   max: " << max << endl;
        if(verbose) cout << "   min: " << min << endl;
        double scale = 255/max;
        new_image.convertTo(new_image, CV_8UC1, scale);

        if(ROI)
        {

            Rect roi(ROI_x_pix[0], ROI_y_pix[0], ROI_x_pix[1], ROI_y_pix[1]);
            Mat image_ROI = new_image(roi);

            filename = output_folder + "/" + filename;
            imwrite(filename, image_ROI);

        }
        else
        {

            filename = output_folder + "/" + filename;
            imwrite(filename, new_image);

        }
    }

    return;

}