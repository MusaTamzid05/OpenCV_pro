#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include <opencv2/opencv.hpp>

namespace CV {

    class Pixel_Extractor {

        /*
         *
         *  Given cordinates , this class returns the pixle
         *  for that cordinates only.
         */

        public:

            Pixel_Extractor();
            Pixel_Extractor(const cv::Mat& image);
            virtual ~Pixel_Extractor();

            void set_image(const cv::Mat& image);
            void get_extracted_image(int x_pos , int y_pos , int width , int height , cv::Mat& result);

        private:

            bool is_outof_limit(int x_pos , int y_pos , int width , int height);

            cv::Mat image;

            void extract(int x_pos , int y_pos , int width , int height , cv::Mat& result);

    };

};

#endif
