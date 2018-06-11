#include "util.h"

#include <iostream>
#include <opencv2/opencv.hpp>

namespace Util {

    void show(const cv::Mat& image , const std::string& window_name) {

        if(image.empty()){
            std::cerr << "Image is empty.\n";
            return;
        }

        cv::namedWindow(window_name , cv::WINDOW_NORMAL);
        cv::imshow(window_name , image);

        cv::waitKey();

    }


    bool is_gray(const cv::Mat& image) {

        if(image.type() == CV_8UC1)
            return true;

        return false;
    }


    bool is_color(const cv::Mat& image) {


        if(image.type() == CV_8UC3)
            return true;

        return false;

    }


};
