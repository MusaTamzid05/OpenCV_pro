#include "image_borderer.h"
#include <opencv2/opencv.hpp>

#include "util.h"

namespace ImageProcessing {

    Color::Color(int blue , int green , int red):
        blue(blue) ,
        green(green) ,
        red(red){

    }

    ImageBorderer::ImageBorderer( int width , const Color& color):
        width(width),
        border_color(color) ,
        gray_image(false){


    }

    void ImageBorderer::border(cv::Mat& image) {

        this->image = image;
        cols = image.cols;
        rows = image.rows;
        gray_image = Util::is_gray(image);
        border_top_and_bottom();
        border_left_and_right();


    }




    void ImageBorderer::border_top_and_bottom() {




        for(int i = 0 ; i < cols ; i++) {

            if(gray_image) {

                for(int j = 0 ; j < width ; j++) {

                    image.at<uchar>(j , i) = 0; // if gray,make it black.
                    image.at<uchar>(rows - (1 + j) , i) = 0; 
                }

                continue;
            }


            for(int j = 0 ; j < width; j++) {

                image.at<cv::Vec3b>(j , i)[0] = border_color.blue; 
                image.at<cv::Vec3b>(j , i)[1] = border_color.green; 
                image.at<cv::Vec3b>(j , i)[2] = border_color.red; 

                image.at<cv::Vec3b>(rows - (1 + j), i)[0] =  border_color.blue; 
                image.at<cv::Vec3b>(rows - (1 + j), i)[1] =  border_color.green; 
                image.at<cv::Vec3b>(rows - (1 + j), i)[2] =  border_color.red; 

            }



        }

    }


    void ImageBorderer::border_left_and_right() {


        for(int i = 0 ; i < rows ; i++) {

            if(is_pixle_already_colored(i))
                continue;

            if(gray_image) {

                for(int j = 0 ; j < width ; j++) {
                    image.at<uchar>(i , j) = 0;
                    image.at<uchar>(i , cols - (j + 1)) = 0;
                }

                continue;
            }

            for(int j = 0 ; j < width ; j++) {

                image.at<cv::Vec3b>(i , j)[0] = border_color.blue;
                image.at<cv::Vec3b>(i , j)[1] = border_color.green;
                image.at<cv::Vec3b>(i , j)[2] = border_color.red;


                image.at<cv::Vec3b>(i , cols - (j + 1))[0] = border_color.blue;
                image.at<cv::Vec3b>(i , cols - (j + 1))[1] = border_color.green;
                image.at<cv::Vec3b>(i , cols - (j + 1))[2] = border_color.red;
            }
        }

    }

    bool ImageBorderer::is_pixle_already_colored(int row) {

        return row < width ? true : false;
    }

};
