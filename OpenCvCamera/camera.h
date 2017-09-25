#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <opencv2/opencv.hpp>


class Camera
{
    public:
        Camera(const std::string& window_name = "Original",int cam_num = 0);
        void run();

    private:

        std::string window_name;
        cv::VideoCapture cam;
        bool should_quit;
        
        void save_image(const cv::Mat& image);
};


#endif 
