#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <opencv2/opencv.hpp>

namespace OpenCV {

    class Image {

        public:

            Image(const std::string& image_path , const std::string& window_name = "Normal");
            virtual ~Image();

            void show();

        protected:

            static std::string window_name;
            bool image_loaded;
            cv::Mat image;
            char current_key;

            void process();
            virtual void process_image();
            void handle_event();

            void change_image(const std::string& new_window_name , const cv::Mat& new_image);

    };
};

#endif
