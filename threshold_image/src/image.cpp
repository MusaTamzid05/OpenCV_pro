#include "image.h"

namespace OpenCV {

    std::string Image::window_name = "";

    Image::Image(const std::string& image_path , const std::string& window_name ): current_key('-'){

        image = cv::imread(image_path);

        if(image.empty()) {
            std::cerr << "Could load " << image_path << "\n";
            image_loaded = false;
            return;
        }

        image_loaded = true;

        Image::window_name = window_name;
        cv::namedWindow(window_name , cv::WINDOW_NORMAL);
    }

    Image::~Image() {

        if(image_loaded)
            cv::destroyWindow(window_name);
    }

    void Image::show() {

        if(!image_loaded) {
            std::cerr << "Image load an image first.\n";
            return;
        }

        cv::imshow(window_name , image);

        while(image_loaded) {
            process();

        }


    }


    void Image::process() {

        process_image();
        handle_event();
        current_key = cv::waitKey(1);
    }


    void Image::process_image() {

        // we want to change the current image according to the process.
        // Use this function to change the image

    }

    void Image::handle_event() {

        if(current_key == 'q')
            image_loaded = false;
    }

    void Image::change_image(const std::string& new_window_name , const cv::Mat& new_image) {

        cv::destroyWindow(window_name);
        window_name = new_window_name;
        image = new_image;
    }

};
