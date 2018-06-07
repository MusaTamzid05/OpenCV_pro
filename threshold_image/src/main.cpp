#include <iostream>
#include "threshold_image.h"

int main(int argc , char** argv) {

    if(argc != 2) {
        std::cerr << "Usage: image_path\n";
        exit(1);
    }


    ImageProcessing::ThresholdImage threshold_image(argv[1]);
    threshold_image.show();


    return 0;
}
