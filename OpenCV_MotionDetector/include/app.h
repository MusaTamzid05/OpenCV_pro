#ifndef APP_H
#define APP_H

#include <opencv2/opencv.hpp>

class App{

    public:

        App(int cam_index = 0);
        void run();


    private:

        bool get_movement_image(cv::Mat& image);
        void process_image(cv::Mat& image);
        int get_area_diff(cv::Mat& result);

        cv::VideoCapture cam;

        cv::Mat current_frame;
        cv::Mat reference_frame; // this frame will be taken after waiting 150 microseconds.

};

#endif
