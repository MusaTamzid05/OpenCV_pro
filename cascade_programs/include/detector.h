#ifndef DETECTOR_H
#define DETECTOR_H


#include <opencv2/opencv.hpp>
#include <vector>


namespace Classifier{

    class Detector{

        public:

            Detector(const std::string& classfier_name);

           /* 
            Every classifier that is created must overrite this function.
            Because every classfier detects diffrent objects.So its not possible 
            to draw every detection with the same function.
            So if we create a face classifier,than its will have nose , eye.If
            you use a full body detector , it will have something deffirent 
            to detect.

            */

            virtual void get_detect_objects(cv::Mat& image, cv::Mat& result_image) = 0;

            void set_image(cv::Mat& image);





        protected:

        
            void load_classifier(const std::string& classifier_name);
            
            bool detect(float scale_factor = 1.1 , int min_neighbors = 3 , int flags = 0 , cv::Size minSize = cv::Size(30 , 30) , cv::Size maxSize = cv::Size(150 , 150));

            bool image_loaded;
            bool cascade_loaded;

            cv::Mat image;
            cv::Mat gray_image;


            cv::CascadeClassifier cascade;

            std::vector<cv::Rect> detected_objects; // all the deteced data will be saved in
                                              // this variable.



    };
};

#endif
