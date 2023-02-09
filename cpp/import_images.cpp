#include <vector>
#include <opencv2/opencv.hpp>
#include <dirent.h>

std::vector<cv::Mat> importImages(std::string directory, int Sn_pixels) {
  std::vector<cv::Mat> images;
  DIR* dir;
  struct dirent* ent;
  if ((dir = opendir(directory.c_str())) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      std::string fileName = ent->d_name;
      // Ignore "." and ".."
      if (fileName != "." && fileName != "..") {
        cv::Mat image = cv::imread(directory + '/' + fileName, cv::IMREAD_GRAYSCALE);
        if (image.empty()) {
          std::cout << "Failed to load image " << fileName << std::endl;
        } else {
          // Crop images from 0 to Sn_pixels
          image = image(cv::Rect(0, 0, Sn_pixels, Sn_pixels));
          images.push_back(image);
        }
      }
    }
    closedir(dir);
  }
  return images;
}