#ifndef IMAGE_BORDERER_H 
#define IMAGE_BODERER_H 


#include <opencv2/opencv.hpp>



namespace ImageProcessing {

    struct Color {
        int blue;
        int green;
        int red;

        Color(int blue , int green , int red);

    };

    class ImageBorderer {

        public:

            ImageBorderer(int width  = 5, const Color& color = Color(0 , 0 , 255));
            virtual ~ImageBorderer(){}

            void border(cv::Mat& image);

        private:

            int width;
            int rows;
            int cols;
            bool gray_image;


            Color border_color;
            cv::Mat image;

            void border_top_and_bottom();
            void border_left_and_right();

            bool is_pixle_already_colored(int row);

    };


};

#endif
