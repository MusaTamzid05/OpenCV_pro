#ifndef UTIL_H
#define UTIL_H

#include <string>

namespace cv {
    class Mat;
};

namespace Util {
    void show(const cv::Mat& image , const std::string& window_name = "Image");

    bool is_gray(const cv::Mat& image);
    bool is_color(const cv::Mat& image);
};


#endif
