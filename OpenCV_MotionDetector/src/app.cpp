#include "app.h"
#include <string>
#include <cstdlib>


App::App(int cam_index):cam(cam_index){

}


bool App::get_movement_image(cv::Mat& result){


    char key;

    cam >> current_frame;

    if(current_frame.empty())
        return false;


    key =  cv::waitKey(150);

    if(key == 'q')
        return false;

    cam >> reference_frame;


    // calculate the diffrence.
    
    cv::absdiff( current_frame , reference_frame , result );

    return true;

}


void App::process_image(cv::Mat& result){
    
    cvtColor(result , result , CV_BGR2GRAY);
    cv::threshold( result , result , 10 , 255 , CV_THRESH_BINARY );
    
    cv::erode(result , result , 0 );
    cv::dilate(result , result , 0 );


}

int App::get_area_diff(cv::Mat& result){
    
    cv::Scalar avg = cv::mean(result);
    
    int area = (int)avg.val[0];

}

void App::run(){


    std::string window_name = "Result";

    int movement_detector_count = 0;

    while(cam.isOpened()){

        cv::Mat result;

        if(!get_movement_image(result))
            break;

        // make it gray.
        
        this->process_image(result);

        int area = this->get_area_diff(result);


        // typical human movement area is 3 meter.

        if(area >= 25 && area <= 150){

            movement_detector_count++;
            std::cout << movement_detector_count << ".movement detected.\n";

        }



        cv::imshow(window_name , result);

    }
}
