#include "threshold_image.h"


#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

namespace Segmentation {

    int Threshold::hs_slider = 0;
    int Threshold::low_slider = 30;
    int Threshold::high_slider = 100;

    int Threshold::low_s = 30;
    int Threshold::high_s = 100;

    int Threshold::low_h = 30;
    int Threshold::high_h = 100;

    std::string Threshold::low_threshold_name = "Low threshold";
    std::string Threshold::high_threshold_name =  "High threshold";
    std::string Threshold::window_name =  "Segmentation";


    Threshold::Threshold(const std::string& image_path):
    is_running(false){

        image = cv::imread(image_path);

        if(image.empty()) {

            std::cerr << "Could not open " << image_path << "\n";
            exit(1);
        }

        cvtColor(image , result_image , CV_BGR2HSV);


        init_window();
        init_trackbar();
        is_running = true;

    }



    void Threshold::init_window() {


        original_window_name = "Original";
        cv::namedWindow(original_window_name ,CV_WINDOW_NORMAL );
        cv::namedWindow(window_name,CV_WINDOW_NORMAL );


    }

    Threshold::~Threshold() {

    }


    void Threshold::get_image(const cv::Mat& src_image ,int low_s , int high_s ,int low_h ,
            int high_h ,cv::Mat& final_image){

        if(src_image.empty()) {

            std::cerr << "The image empty.\n";
            return;
        }

        result_image = src_image.clone();

        load_hue_saturation_data();
        threshold_image();
        clear_noice();

        final_image = result_image.clone();


    }

    void Threshold::init_trackbar() {

        cv::createTrackbar("0 = > H \n1 => S" ,  window_name , &hs_slider , 1 , on_hs_trackbar);
        cv::createTrackbar(low_threshold_name , window_name , &low_slider , 255 , on_low_trackbar);
        cv::createTrackbar(high_threshold_name , window_name , &high_slider , 255 , on_high_trackbar);

        std::cout << "Trackbar init.\n";
    }

    void Threshold::run() {



        while(is_running) {

            load_hue_saturation_data();
            threshold_image();
            clear_noice();
            handle_event();


            cv::imshow(original_window_name , image);
            cv::imshow(window_name, result_image);
        }
    }

    void Threshold::handle_event() {

        char key;

        key = cv::waitKey(20) ;
        
        if(key == 'q')
            is_running = false;

    }

    void Threshold::clear_noice() {

        cv::Mat str_el = cv::getStructuringElement(cv::MORPH_ELLIPSE  , cv::Size(7,7));
        cv::morphologyEx(result_image , result_image , cv::MORPH_OPEN , str_el);
        cv::morphologyEx(result_image , result_image , cv::MORPH_CLOSE, str_el);
    }

    void Threshold::threshold_image() {

        cv::inRange(hs ,  cv::Scalar(low_h , low_s) ,
                cv::Scalar(high_h , high_s) , result_image);

    }

    void Threshold::load_hue_saturation_data() {

        int from_to[] = { 0 , 0 , 1 , 1 };
        hs = cv::Mat(image.size() , CV_8UC2);
        cv::mixChannels(&image , 1 , &hs , 1 , from_to ,2);

    }

    void Threshold::on_hs_trackbar(int , void*) {


        // this function is used when you want to change both hue and segmentation.

        switch(hs_slider) {

            case 0:

                cv::setTrackbarPos(low_threshold_name , window_name , low_h);
                cv::setTrackbarPos(high_threshold_name , window_name , high_h);
                break;

            case 1:


                cv::setTrackbarPos(low_threshold_name , window_name , low_s);
                cv::setTrackbarPos(high_threshold_name , window_name, high_s);
                break;
        }


    }

    void Threshold::on_low_trackbar(int , void*) {


        
        switch(hs_slider) {

            case 0:

                low_h = cv::min(high_slider - 1 , low_slider);
                cv::setTrackbarPos(low_threshold_name , window_name, low_h);
                break;

            case 1:


                low_s = cv::min(high_slider - 1 , low_slider);
                cv::setTrackbarPos(low_threshold_name  , window_name , low_s);
                break;
        }
    }


    void Threshold::on_high_trackbar(int , void*) {



        switch(hs_slider) {

            case 0:

                high_h = cv::max(low_slider + 1 , high_slider);
                cv::setTrackbarPos(high_threshold_name, window_name, high_h);
                break;


            case 1:


                high_s = cv::max(low_slider + 1 , high_slider);
                cv::setTrackbarPos(high_threshold_name  , window_name  , high_s);
                break;
        }
    }
    

};
