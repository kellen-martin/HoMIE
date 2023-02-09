#ifndef CALCULATE_TEMPLATE_H
#define CALCULATE_TEMPLATE_H

#include <opencv2/opencv.hpp>

struct Inputs {
  double wavelength;
  int n_pixels;
  double pixel_p;
  double ref_dist;
  double samp_dist;
  double ref_amp;
  double ref_pos_x;
  double ref_pos_y;
  double obj_amp;
};

struct Outputs {
  cv::Mat template_wave;
  cv::Mat ref_wave;
};

Outputs calculateTemplate(const Inputs& inputs);

#endif  // CALCULATE_TEMPLATE_H