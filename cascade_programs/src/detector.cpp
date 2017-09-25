#include "detector.h"
#include "helper.h"

namespace Classifier{

    Detector::Detector(const std::string& classfier_name):
    image_loaded(false) ,
    cascade_loaded(false){

        load_classifier(classfier_name);

        if(!cascade_loaded){

            std::cerr << classfier_name << " could not be loaded.\n";
            return;
        }

        std::cout << "cascade file loaded.\n";


    }

    void Detector::set_image(cv::Mat& image){
        
        this->image = image;

        if(!Helper::is_gray(image)){
            cvtColor(image , gray_image, CV_BGR2GRAY);
            cv::equalizeHist(gray_image , gray_image);
            return;
        }

        this->gray_image  = image;

    }


    void Detector::load_classifier(const std::string& classfier_name){

        if(cascade.load(classfier_name))
            cascade_loaded = true;
    }

    bool Detector::detect(float scale_factor , int min_neighbors , int flags , cv::Size min_size , cv::Size max_size){

        if(!cascade_loaded){
            std::cerr << "Cascade could not be loaded.!!!\n";
            return false;
        }

        if(gray_image.empty()){

            std::cerr << "Set the image in the detector first!!\n";
            return false;
        }



        cascade.detectMultiScale(gray_image, detected_objects , scale_factor , min_neighbors , flags , min_size , max_size);

        std::cout << "Objects : " << detected_objects.size() << "\n";
        return true;

    }


};
