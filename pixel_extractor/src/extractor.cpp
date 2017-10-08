#include "extractor.h"


namespace CV {

    Pixel_Extractor::Pixel_Extractor() {

    }

    Pixel_Extractor::~Pixel_Extractor() {

    }

    Pixel_Extractor::Pixel_Extractor(const cv::Mat& image):image(image) {

    }

    void Pixel_Extractor::set_image(const cv::Mat& image) {

        this->image = image;
    }

    
    bool Pixel_Extractor::is_outof_limit(int x_pos , int y_pos , int width , int height) {

        if(image.empty()) {

            std::cerr << "Image is empty.Cannot get limit.\n";
            return false;
        }

        return x_pos < 0 || x_pos > image.cols || y_pos < 0 || y_pos > image.rows;
    }
    
    
    void Pixel_Extractor::get_extracted_image(int x_pos , int y_pos , int width , int height , cv::Mat& result) {

        if(image.empty()) {
            std::cerr << "Image is empty.Cannot extract!!\n";
            return;
        }

        if(is_outof_limit(x_pos , y_pos , width , height))  {

            std::cerr << "Extraction cordinates are out of limit.\n";
            return;
        }

        extract(x_pos , y_pos , width , height , result);
    }



    void Pixel_Extractor::extract(int x_pos , int y_pos , int width , int height , cv::Mat& result){


        cv::Mat result_temp_image(height, width, CV_8UC3);

        int result_image_row = 0;
        int result_image_col = 0;


        for(int row = y_pos ; row < y_pos + height ; row++){
            for(int col = x_pos ; col < x_pos + width ; col++) {

                result_temp_image.at<cv::Vec3b>(result_image_row , result_image_col) = image.at<cv::Vec3b>(row, col);
                result_image_col++;
                
            }

            result_image_row++;
            result_image_col = 0;
        }


        result = result_temp_image.clone();
    }






};

