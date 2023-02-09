#include "calculate_template.h"

#include <cmath>

Outputs calculateTemplate(const Inputs& inputs) {
  double wavelength = inputs.wavelength;
  int n_pixels = inputs.n_pixels;
  double pixel_p = inputs.pixel_p;
  double ref_dist = inputs.ref_dist;
  double samp_dist = inputs.samp_dist;
  int ref_amp = inputs.ref_amp;
  int ref_pos_x = inputs.ref_pos_x;
  int ref_pos_y = inputs.ref_pos_y;
  double obj_amp = inputs.obj_amp;

  double template_pos_x = 0;
double template_pos_y = 0;
double template_pos_z = samp_dist;
cv::Mat pixel_x(1, n_pixels, CV_64F);
cv::Mat pixel_y(1, n_pixels, CV_64F);
for (int i = 0; i < n_pixels; ++i) {
pixel_x.at<double>(i) = pixel_p * (i - std::floor(n_pixels / 2));
pixel_y.at<double>(i) = pixel_p * (i - std::floor(n_pixels / 2));
}
double ref_pos_z = ref_dist;

double template_phase = 2 * M_PI * std::sqrt(std::pow(template_pos_x - ref_pos_x, 2) + std::pow(template_pos_y - ref_pos_y, 2) + std::pow(template_pos_z - ref_pos_z, 2)) / wavelength;
cv::Mat ref_wave(n_pixels, n_pixels, CV_32FC1);
cv::Mat template_wave(n_pixels, n_pixels, CV_32FC1);
for (int ix = 0; ix < n_pixels; ++ix) {
    double x = pixel_x.at<double>(ix);
    cv::Mat ref_dist(n_pixels, n_pixels, CV_64F);
    for (int iy = 0; iy < n_pixels; ++iy) {
        ref_dist.at<double>(iy, ix) = std::sqrt(std::pow(x - ref_pos_x, 2) + std::pow(pixel_y.at<double>(iy) - ref_pos_y, 2) + std::pow(ref_pos_z, 2));
    }
    cv::Mat ref_n_waves = ref_dist / wavelength;
    ref_wave.col(ix) = ref_amp * cv::exp(1i * 2 * M_PI * ref_n_waves);

    cv::Mat template_dist(n_pixels, n_pixels, CV_64F);
    for (int iy = 0; iy < n_pixels; ++iy) {
        template_dist.at<double>(iy, ix) = std::sqrt(std::pow(x - template_pos_x, 2)


    /*cv::Mat ref_dist(n_pixels, n_pixels, CV_64F);
    for (int iy = 0; iy < n_pixels; ++iy) {
      ref_dist.at<double>(iy, ix) = std::sqrt(std::pow(x - ref_pos_x, 2) + std::pow(pixel_y.at<double>(iy) - ref_pos_y, 2) + std::pow(ref_pos_z, 2));
    }
    cv::Mat ref_n_waves = ref_dist / wavelength;
    ref_wave.col(ix) = ref_amp * cv::exp(1i * 2 * M_PI * ref_n_waves);

    cv::Mat template_dist(n_pixels, n_pixels, CV_64F);
    for (int iy = 0; iy < n_pixels; ++iy) {*/
      template_dist.at<double>(iy, ix) = std::sqrt(std::pow(x - template_pos_x, 2) + std::pow(pixel_y.at<double>(iy) - template_pos_y, 2) + std::pow(template_pos_z, 2));
    }
    cv::Mat template_n_waves = template_dist / wavelength;
    template_wave.col(ix) = obj_amp * cv::exp(1i * (2 * M_PI * template_n_waves + template_phase));
  }

  Outputs outputs;
  outputs.template_wave = template_wave;
  outputs.ref_wave = ref_wave;
  return outputs;
}