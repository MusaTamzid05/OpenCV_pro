#include "threshold_image.h"


namespace ImageProcessing {

    const int MAX_THRESHOLD = 255;
    const int MIN_THRESHOLD = 0;


    std::string ThresholdImage::min_blue_threshold_trackbar_name = "min_blue_threshold_window";
    std::string ThresholdImage::max_blue_threshold_trackbar_name = "max_blue_threshold_window";


    std::string ThresholdImage::min_green_threshold_trackbar_name = "min_green_threshold_window";
    std::string ThresholdImage::max_green_threshold_trackbar_name = "max_green_threshold_window";


    std::string ThresholdImage::min_red_threshold_trackbar_name = "min_red_threshold_window";
    std::string ThresholdImage::max_red_threshold_trackbar_name = "max_red_threshold_window";


    int ThresholdImage::min_blue_threshold = 0;
    int ThresholdImage::max_blue_threshold = 255;


    int ThresholdImage::min_green_threshold = 0;
    int ThresholdImage::max_green_threshold = 255;


    int ThresholdImage::min_red_threshold = 0;
    int ThresholdImage::max_red_threshold = 255;


    ThresholdImage::ThresholdImage(const std::string& image_path):OpenCV::Image(image_path , "Source Image") {

        init_trackbar();
        mask = image.clone();
        threshold_image_name = "Threshold Window";
        cv::namedWindow(threshold_image_name , cv::WINDOW_NORMAL);

    }


    void ThresholdImage::init_trackbar() {


        cv::createTrackbar(min_blue_threshold_trackbar_name, window_name , &min_blue_threshold , MAX_THRESHOLD, on_min_blue_threshold);
        cv::createTrackbar(max_blue_threshold_trackbar_name, window_name , &max_blue_threshold , MAX_THRESHOLD, on_max_blue_threshold);


        cv::createTrackbar(min_green_threshold_trackbar_name, window_name , &min_green_threshold , MAX_THRESHOLD, on_min_green_threshold);
        cv::createTrackbar(max_green_threshold_trackbar_name, window_name , &max_green_threshold , MAX_THRESHOLD, on_max_green_threshold);


        cv::createTrackbar(min_red_threshold_trackbar_name, window_name , &min_red_threshold , MAX_THRESHOLD, on_min_red_threshold);
        cv::createTrackbar(max_red_threshold_trackbar_name, window_name , &max_red_threshold , MAX_THRESHOLD, on_max_red_threshold);


    }


    void ThresholdImage::process_image() {


        cv::inRange(image , cv::Scalar(min_blue_threshold , min_green_threshold , min_red_threshold),
                           cv::Scalar(max_blue_threshold , max_green_threshold , max_red_threshold) , mask);

        cv::imshow(threshold_image_name , mask);


    }


    void ThresholdImage::on_min_blue_threshold(int , void*) {


        if(min_blue_threshold > max_blue_threshold) {

            min_blue_threshold = max_blue_threshold - 1;
            cv::setTrackbarPos(min_blue_threshold_trackbar_name , window_name , min_blue_threshold);
        }

    }


    void ThresholdImage::on_max_blue_threshold(int , void*) {

        if(max_blue_threshold < min_blue_threshold)
            max_blue_threshold = min_blue_threshold  + 1;

        cv::setTrackbarPos(max_blue_threshold_trackbar_name , window_name , max_blue_threshold);

    }


    void ThresholdImage::on_min_green_threshold(int , void*) {


        if(min_green_threshold > max_green_threshold) {

            min_green_threshold = max_green_threshold - 1;
            cv::setTrackbarPos(min_green_threshold_trackbar_name , window_name , min_green_threshold);
        }

    }


    void ThresholdImage::on_max_green_threshold(int , void*) {

        if(max_green_threshold < min_green_threshold)
            max_green_threshold = min_green_threshold  + 1;

        cv::setTrackbarPos(max_green_threshold_trackbar_name , window_name , max_green_threshold);

    }


    void ThresholdImage::on_min_red_threshold(int , void*) {


        if(min_red_threshold > max_red_threshold) {

            min_red_threshold = max_red_threshold - 1;
            cv::setTrackbarPos(min_red_threshold_trackbar_name , window_name , min_red_threshold);
        }

    }


    void ThresholdImage::on_max_red_threshold(int , void*) {

        if(max_red_threshold < min_red_threshold)
            max_red_threshold = min_red_threshold  + 1;

        cv::setTrackbarPos(max_red_threshold_trackbar_name , window_name , max_red_threshold);

    }


};
