#include <opencv2/opencv.hpp>
using namespace cv;
int main(int argc, char** argv)
{
    // Open the camera using its device ID (0 is usually the default camera)
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cerr << "Error: Unable to open camera" << std::endl;
        return -1;
    }
    // Set camera parameters
    cap.set(CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(CAP_PROP_FRAME_HEIGHT, 720);
    cap.set(CAP_PROP_FPS, 30);
    // Capture a single image from the camera
    Mat frame;
    cap.read(frame);
    // Create a window to display the captured image
    namedWindow("Captured Image", WINDOW_NORMAL);
    imshow("Captured Image", frame);
    // Wait for a key event
    waitKey(0);
    // Release the camera and close the window
    cap.release();
    destroyAllWindows();
    return 0;
}







