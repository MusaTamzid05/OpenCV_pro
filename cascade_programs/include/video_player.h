#ifndef VIDEO_PLAYER_H 
#define VIDEO_PLAYER_H

#include <string>
#include <opencv2/opencv.hpp>

namespace Classifier{
    class Detector;
};


namespace IO{


    class Video_Player 
    {
        public:
            Video_Player(const std::string& window_name = "Original",int cam_num = 0);
            Video_Player(const std::string& video_file_name , const std::string& window_name);
            virtual ~Video_Player();


            void run();

            void set_detector(Classifier::Detector* detector);

        private:

            void init();

            std::string window_name;
            cv::VideoCapture cam;
            bool should_quit;
            
            cv::Mat current_frame;

            void show_detector_object();

            // set the classfier class you want to use

            Classifier::Detector* detector;
            
    };
}


#endif 

