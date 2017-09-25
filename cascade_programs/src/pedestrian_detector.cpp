#include "pedestrian_detector.h"

namespace Classifier{

    Pedestrian_Detector::Pedestrian_Detector():
    Detector("./cascades/hogcascade_predestrians.xml"){


    }

    Pedestrian_Detector::~Pedestrian_Detector(){

        
    }


    void Pedestrian_Detector::get_detect_objects(cv::Mat& image ,  cv::Mat& result_image){

        set_image(image);

        if(!detect()){
            std::cerr << "Error while detecting ..";
            return;
        }

       result_image = this->image.clone(); 


        for(unsigned int i = 0 ; i < detected_objects.size() ; i++){

            cv::Point center(detected_objects[i].x + detected_objects[i].width * 0.5 , detected_objects[i].y + detected_objects[i].height * 0.5);

            cv::ellipse(result_image , center , cv::Size(detected_objects[i].width * 0.5 , detected_objects[i].height * 0.5) ,
                    0 , 0 , 360 , cv::Scalar( 255 , 0 , 255 ) , 5 , 8 , 0);
        }
    }

};
