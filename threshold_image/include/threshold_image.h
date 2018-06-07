#ifndef THRESHOLD_IMAGE_H
#define THRESHOLD_IMAGE_H

#include "image.h"
#include <string>


namespace ImageProcessing {


    class ThresholdImage : public OpenCV::Image {


        public:

            ThresholdImage(const std::string& image_path);
            virtual ~ThresholdImage() {}

            void process_image() override;

        private:

            static int min_blue_threshold;
            static int max_blue_threshold;


            static int min_green_threshold;
            static int max_green_threshold;


            static int min_red_threshold;
            static int max_red_threshold;

            static void on_min_blue_threshold(int , void*);
            static void on_max_blue_threshold(int , void*);


            static void on_min_green_threshold(int , void*);
            static void on_max_green_threshold(int , void*);


            static void on_min_red_threshold(int , void*);
            static void on_max_red_threshold(int , void*);

            static std::string min_blue_threshold_trackbar_name;
            static std::string max_blue_threshold_trackbar_name;


            static std::string min_green_threshold_trackbar_name;
            static std::string max_green_threshold_trackbar_name;


            static std::string min_red_threshold_trackbar_name;
            static std::string max_red_threshold_trackbar_name;

            void init_trackbar();

            cv::Mat mask;
            std::string threshold_image_name;

    };
};

#endif
