#include <iostream>
#include "threshold_image.h"

int main(int argc , char** argv) {

    if(argc != 2) {

        std::cerr << "Usage:image_path.\n";
        exit(0);
    }

    std::string image_path = argv[1];

    Segmentation::Threshold threshold_image(image_path);
    threshold_image.run();

    return 0;
}
