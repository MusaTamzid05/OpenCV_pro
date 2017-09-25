#ifndef  THRESHOLD_H
#define THRESHOLD_H

#include <string>
#include <opencv2/opencv.hpp>


namespace Segmentation {

    class Threshold {

        public:

            Threshold(const std::string& image_path);
            virtual ~Threshold();

            void run();
            void get_image(const cv::Mat& src_image ,int low_s , int high_s ,int low_h ,
                    int high_h ,cv::Mat& final_image);

        private:


            void init_window();
            void init_trackbar();
            void load_hue_saturation_data();
            void threshold_image();
            void clear_noice();
            void handle_event();

            bool is_running;

            std::string original_window_name;




            static int hs_slider; // this hs_slider indicates  if we are changing hue of saturation.
            // 0 means we are changing hue
            // 11 means we are changin saturation.
            


            static int low_slider;
            static int high_slider;

            static int low_s;
            static int high_s;

            static int low_h;
            static int high_h;


            static void on_hs_trackbar(int , void*);
            static void on_low_trackbar(int , void*);
            static void on_high_trackbar(int , void*);


            static std::string  low_threshold_name;
            static std::string  high_threshold_name;
            static std::string  window_name;

            cv::Mat image;
            cv::Mat result_image;
            cv::Mat hs;


    };
};

#endif
