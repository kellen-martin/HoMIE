// #include "header.hpp"
#include "defs.cpp"
#include "dtypes.cpp"
#include "loop_defs.cpp" // for global variables
#include "loop_dtypes.cpp" // for data types

#ifndef FUNCTION_HEADERS
#define FUNCTION_HEADERS
#include "saveFunctions.cpp"
#include "CalculateTemplate.cpp"
#include "AverageImage.cpp"
#include "DifferenceStack.cpp"
#include "ImportImages.cpp"
#include "linspace.cpp"
#include "PlotFrame.cpp"
#include "Reconstructor.cpp"
#include "dtypes.cpp"
#include "Reconstructor_Kanka1.cpp"
#endif

#ifndef LOOP_FUNCTIONS
#define LOOP_FUNCTIONS
#include "loadCommands.cpp"
#endif


using namespace std;
using namespace cv;

string output_folder = "../Output-Images";

#ifndef ROI_val
#define ROI_val
float ROI_x[2] = {-0.5*1e-3, 0.5*1e-3};
float ROI_y[2] = {-0.5*1e-3, 0.5*1e-3};
int ROI_x_pix[2] = {(int)n_pixels/2 + (int)(ROI_x[0]/(pixel_p)), (int)n_pixels/2 + (int)(ROI_x[1]/(pixel_p))};
int ROI_y_pix[2] = {(int)n_pixels/2 + (int)(ROI_y[0]/(pixel_p)), (int)n_pixels/2 + (int)(ROI_y[1]/(pixel_p))};
#endif

int main(int argc, char *argv[])
{       
    vector<int> frames;

    string input_folder(argv[1]);
    string sampleID = input_folder;
    int type;
    int frame1;
    int frame2;
    vector<int> z_slices;

    string input(argv[2]);
    if(input == "DIFF_STACK"){
        type = DIFF_STACK;

        string in2(argv[3]);
        frame1 = stoi(in2);
        string in3(argv[4]);
        frame2 = stoi(in3);

        string z(argv[5]);
        if(z == "ALL"){
            z_slices.push_back(-1);
        }else{
            for(int j = 5; j < argc; j++)
            {
                string slice(argv[j]);
                z_slices.push_back(stoi(slice));
            }
        }

    }else if(input == "DIFF_FRAME"){
        type = DIFF_FRAME;
        
        string in2(argv[3]);
        frame1 = stoi(in2);
        string in3(argv[4]);
        frame2 = stoi(in3);
        
        string z(argv[5]);
        if(z == "ALL"){
            z_slices.push_back(-1);
        }else{
            for(int j = 5; j < argc; j++)
            {
                string slice(argv[j]);
                z_slices.push_back(stoi(slice));
            }
        }

    }else{
        type = SINGLE_FRAME;
        
        string in2(argv[3]);
        frame1 = stoi(in2);
        
        string z(argv[4]);
        if(z == "ALL"){
            z_slices.push_back(-1);
        }else{
            for(int j = 4; j < argc; j++)
            {
                string slice(argv[j]);
                z_slices.push_back(stoi(slice));
            }
        }
    }
    

    vector<Mat> images;
    
    input_folder = "../holograms/" + input_folder; // path to folder from program location

    if(verbose) cout << endl;

    ImportImages(images, input_folder);
    
    if(verbose) cout << endl << "Returned to Main" << endl << endl;
    
    // selecting desired images: ---------------------------------
    if(type == SINGLE_FRAME){

        if(frame1 <= images.size()){
            images.erase(images.begin(), images.begin() + (frame1 - 1));
            images.erase(images.begin() + 1, images.end());
            /////////////////////////////////////////////////////////////////////
            if(verbose) cout << "single frame images: " << images.size() << endl;
            /////////////////////////////////////////////////////////////////////
        }
        
    }else if(type == DIFF_FRAME){
        if(frame1 <= images.size() && frame2 <= images.size()){
            images.erase(images.begin(), images.begin() + (frame1 - 1));
            images.erase(images.begin() + 1, images.begin() + (frame2 - frame1));
            images.erase(images.begin() + 2, images.end());
            /////////////////////////////////////////////////////////////////////
            if(verbose) cout << "Diff frame images: " << images.size() << endl;
            /////////////////////////////////////////////////////////////////////
        }

    }else if(type == DIFF_STACK){
        if(frame1 <= images.size() && frame2 <= images.size()){
            images.erase(images.begin(), images.begin() + (frame1 - 1));
            images.erase(images.begin() + frame2 - frame1 + 1, images.end());
            /////////////////////////////////////////////////////////////////////
            if(verbose) cout << "Diff stack images: " << images.size() << endl;
            /////////////////////////////////////////////////////////////////////
        }
    }
    // -----------------------------------------------------------

    if(verbose) cout << "Image size: " << images[0].rows << " x " << images[0].cols << " x " << images[0].channels() << endl << endl;

    Mat avgImg;
    if(images.size() > 1){
        // Average images
        avgImg = AverageImage(images);
        if(verbose) cout << endl << "Returned to Main" << endl << endl;
    }else{
        avgImg = images[0];
    }

    // if using first and last arguments to select a range, make indexes zero based
    
    if(verbose) cout << "Average Image:" << endl;
    if(verbose) cout << "    " << avgImg.rows << " x " << avgImg.cols << " x " << avgImg.channels() << endl;
    if(verbose)
    {
        double max, min;
        Point minLoc, maxLoc;
        minMaxLoc(avgImg, &min, &max, &minLoc, &maxLoc);
        if(verbose) cout << "    max pixel value: " << max << endl;
        if(verbose) cout << "    min pixel value: " << min << endl << endl;
    }

    Mat diffStack;
    if(images.size() > 1){
        diffStack = DifferenceStack(images);
    }else{
        diffStack = images[0];
    }
    // saveRealMat(diffStack, "../Output-Images/diffStack.txt", 3000, 3000);

    if(verbose) cout << endl << "Returned to Main" << endl << endl;
    if(verbose) cout << "Difference Stack:" << endl;
    if(verbose) cout << "    " << diffStack.rows << " x " << diffStack.cols << " x " << diffStack.channels() << endl;
    if(verbose)
    {
        double max, min;
        Point minLoc, maxLoc;
        minMaxLoc(diffStack, &min, &max, &minLoc, &maxLoc);
        if(verbose) cout << "    max pixel value: " << max << endl;
        if(verbose) cout << "    min pixel value: " << min << endl << endl;
    }
    
    // Mat recon = Reconstructor_Kanka(diffStack, 1);

    if(z_slices[0] == -1){
        // reconstruct all 1000 z-slices
        for(int slice = -500; slice <= 500; slice+=20){

            if(verbose) cout << "Reconstructing z-slice " << slice + 501 << ": " << endl << endl;

            Mat recon = Reconstructor(diffStack, slice);
            // Mat recon = Reconstructor_Kanka(diffStack, slice);

            if(verbose) cout << "Reconstructed z-slice " << slice + 501 << ", saving..." << endl << endl;

            string name = "detect_recon/" + sampleID + "_z-slice_" + to_string(slice + 501); // set the name of the output image

            // define the grayscale colormap with 256 levels
            Mat colormap(1, 256, CV_8UC1);
            for (int i = 0; i < 256; i++) {
                colormap.at<uchar>(i) = i;
            }

            if(verbose) cout << "defined colormap" << endl;

            // set the image format options
            vector<int> params = {IMWRITE_PNG_COMPRESSION, 0, IMWRITE_PNG_BILEVEL, 0,
                                  IMWRITE_PNG_STRATEGY, IMWRITE_PNG_STRATEGY_DEFAULT};

            if(verbose) cout << "defined format options" << endl;
            
            
            Mat outImage = Mat::zeros(ROI_x_pix[1] - ROI_x_pix[0] + 1, ROI_y_pix[1] - ROI_y_pix[0] + 1, CV_32F);
            float max;

            if(verbose) cout << "starting intensity" << endl;

            if(verbose){
                cout << "Region of interest (ROI):" << endl;
                cout << "    ROI_x_pix: " << ROI_x_pix[0] << " - " << ROI_x_pix[1] << endl;
                cout << "    ROI_y_pix: " << ROI_y_pix[0] << " - " << ROI_y_pix[1] << endl;
                cout << "    recon size: " << recon.rows << " x " << recon.cols << endl;
            }

            for(int pixX = 0; pixX <= ROI_x_pix[1] - ROI_x_pix[0]; pixX++){
                for(int pixY = 0; pixY <= ROI_y_pix[1] - ROI_y_pix[0]; pixY++){
                    std::complex<float> temp = recon.at<complex<float>>(ROI_x_pix[0] + pixX, ROI_y_pix[0] + pixY);
                    // if(verbose) cout << "accessed recon variable" << endl;

                    float ABS = std::abs(temp);

                    // if(verbose) cout << "abs found" << endl;

                    outImage.at<float>(pixX, pixY) = sqrt(ABS);
                    
                    // if(verbose) cout << "Intensity found" << endl;

                    if(outImage.at<float>(pixX, pixY) > max){
                        max = outImage.at<float>(pixX, pixY);
                    }

                }
            }

            
            if(verbose) cout << "found intensity and max value" << endl;

            outImage = outImage / max;
            Mat J = Mat::zeros(ROI_x_pix[1] - ROI_x_pix[0] + 1, ROI_y_pix[1] - ROI_y_pix[0] + 1, CV_8UC1);
            
            for(int pixX = 0; pixX <= ROI_x_pix[1] - ROI_x_pix[0]; pixX++){
                for(int pixY = 0; pixY <= ROI_y_pix[1] - ROI_y_pix[0]; pixY++){

                    J.at<uint8_t>(pixX, pixY) = round(outImage.at<float>(pixX, pixY) * 255);
                    J.at<uint8_t>(pixX, pixY) = 255 - J.at<uint8_t>(pixX, pixY);

                }
            }
        
            Mat J_gray;
            // applyColorMap(J, J_gray, colormap);

            // save the image with the specified options
            imwrite(input_folder + "/" + name + ".png", J, params);

            pid_t child = fork();

            if(child == 0){
                // child process (uncomment to add motion detection here)

                // vector<const char*> args = {"./take_commands", nullptr};
                // execvp(args[0], const_cast<char* const*>(args.data()));
                // return 1;

                return 0;
            }else{
                // parent process
                int status;
                pid_t terminated = waitpid(child, &status, 0);
                cout << endl;
            }
        }
    }else{
        // reconstruct z-slices in z_slices vector

        for(int i = 0; i < z_slices.size(); i++){
            // Mat recon = Reconstructor_Kanka(diffStack, z_slices[i]);
            Mat recon = Reconstructor(diffStack, z_slices[i]);
            string name = "detect_recon"; // set the name of the output image

            // define the grayscale colormap with 256 levels
            Mat colormap(1, 256, CV_8UC1);
            for (int i = 0; i < 256; i++) {
                colormap.at<uchar>(i) = i;
            }

            // set the image format options
            vector<int> params = {IMWRITE_PNG_COMPRESSION, 0, IMWRITE_PNG_BILEVEL, 0,
                                  IMWRITE_PNG_STRATEGY, IMWRITE_PNG_STRATEGY_DEFAULT};

            
            
            Mat outImage = Mat::zeros(ROI_x_pix[1] - ROI_x_pix[0] + 1, ROI_y_pix[1] - ROI_y_pix[0] + 1, CV_32F);
            float max;
            for(int pixX = 0; pixX <= ROI_x_pix[1] - ROI_x_pix[0]; pixX++){
                for(int pixY = 0; pixY <= ROI_y_pix[1] - ROI_y_pix[0]; pixY++){

                    outImage.at<float>(pixX, pixY) = sqrt(abs(recon.at<complex<float>>(ROI_x_pix[0] + pixX, ROI_y_pix[0] + pixY)));
                    if(outImage.at<float>(pixX, pixY) > max) max = outImage.at<float>(pixX, pixY);

                }
            }

            outImage = outImage / max;
            Mat J = Mat::zeros(ROI_x_pix[1] - ROI_x_pix[0] + 1, ROI_y_pix[1] - ROI_y_pix[0] + 1, CV_8UC1);
            
            for(int pixX = 0; pixX <= ROI_x_pix[1] - ROI_x_pix[0]; pixX++){
                for(int pixY = 0; pixY <= ROI_y_pix[1] - ROI_y_pix[0]; pixY++){

                    J.at<uint8_t>(pixX, pixY) = round(outImage.at<float>(pixX, pixY) * 255);
                    J.at<uint8_t>(pixX, pixY) = 255 - J.at<uint8_t>(pixX, pixY);

                }
            }

            Mat J_gray;
            // applyColorMap(J, J_gray, colormap);

            // save the image with the specified options
            imwrite(input_folder + "/" + name + ".png", J, params);

            pid_t child = fork();

            if(child == 0){
                // child process (uncomment to add motion detection here)

                // vector<const char*> args = {"./take_commands", nullptr};
                // execvp(args[0], const_cast<char* const*>(args.data()));
                // return 1;

                return 0;
            }else{
                // parent process
                int status;
                pid_t terminated = waitpid(child, &status, 0);
                cout << endl;
            }

        }
    }
    
    if(verbose) cout << endl << "Returned to Main" << endl << endl;

    // if(verbose)
    // {   

    //     double max, min;
    //     Point minLoc, maxLoc;
    //     minMaxLoc(recon, &min, &max);

    //     cout << "  Reconstructed image: " << recon.rows << " x " << recon.cols << " x " << recon.channels() << endl;  
    //     cout << "    max pixel value: " << max << endl;
    //     cout << "    min pixel value: " << min << endl << endl;
    // }
    
    // saveComplexMat(recon, "../Output-Images/Mat.txt", n_pixels, n_pixels); 
    // FileStorage file("mat.yml", FileStorage::WRITE);
    // file << "mat" << recon;
    // file.release();

    return 0;
}


