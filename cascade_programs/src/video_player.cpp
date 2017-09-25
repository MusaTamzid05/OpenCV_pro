#include "video_player.h"


#include <iostream>
#include <cstdlib>
#include "detector.h"


namespace IO{


    Video_Player::Video_Player(const std::string& window_name_ ,int cam_num):window_name(window_name_),cam(cam_num){

        init();
    }

    Video_Player::Video_Player(const std::string& video_file_name , const std::string& window_name):cam(video_file_name) , window_name(window_name){

       init(); 
    }

    Video_Player::~Video_Player(){

        if(detector != nullptr)
            delete detector;

    }

    void Video_Player::init(){


        if(!cam.isOpened()){
            std::cerr << "Could not open the camera.\n";
            exit(1);
        }

        should_quit = false;
    }

    void Video_Player::set_detector(Classifier::Detector* detector){

        this->detector = detector;
    }

    void Video_Player::run(){


        while(!should_quit){

            cam >> current_frame;

            if(current_frame.empty()){

                std::cout << "Video ended.\n";
                break;
            }


            if(detector != nullptr)
                show_detector_object();

            char key = char(cv::waitKey(20));


            if (key == 'q'){
                should_quit = true;
                std::cout << "Quiting.\n";
            }

            cv::imshow(window_name, current_frame);
        }
    }

    void Video_Player::show_detector_object(){

        cv::Mat result_image;
        
        detector->get_detect_objects( current_frame , result_image);

        std::string result_window_name = "Result";
        cv::imshow(result_window_name , result_image);

    }

};

