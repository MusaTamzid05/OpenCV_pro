#include "helper.h"

namespace Helper{

    bool is_gray(const cv::Mat& image){

        bool gray_image = false;

        if(image.channels() <= 1)
            gray_image = true;

        return gray_image;
    }
};
