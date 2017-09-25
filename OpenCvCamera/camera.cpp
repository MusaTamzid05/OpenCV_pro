#include "camera.h"
#include <iostream>
#include <cstdlib>
#include "helper.h"



Camera::Camera(const std::string& window_name_ ,int cam_num):window_name(window_name_),cam(cam_num){

    if(!cam.isOpened()){
        std::cerr << "Could not open the camera.\n";
        exit(1);
    }

    should_quit = false;
}

void Camera::run(){

    cv::Mat current_frame;

    while(!should_quit){

        cam >> current_frame;

        if(current_frame.empty()){

            std::cout << "Video ended.\n";
            break;
        }

        char key = char(cv::waitKey(1));


        if( key == 'p'){

            save_image(current_frame);
            std::cout << "Pic taken.\n";
        }
        else if (key == 'q'){
            should_quit = true;
            std::cout << "Quiting.\n";
        }

        cv::imshow(window_name, current_frame);
    }
}

void Camera::save_image(const cv::Mat& image){

    // it only creates the random name betweet the numbers.
    // so it can override the previos photo.

    std::string random_name = std::to_string(random(1,200));
    cv::imwrite(random_name + ".jpg" , image);
    std::cout << "picture name is " << random_name <<".";
}
