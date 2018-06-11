#include <opencv2/opencv.hpp>
#include "image_borderer.h"
#include  "util.h"


int main(int argc , char** argv) {

    if(argc != 2) {
        std::cerr << "Usage:image_path\n";
        exit(1);
    }

    cv::Mat image = cv::imread(argv[1]);

    ImageProcessing::ImageBorderer borderer;
    borderer.border(image);

    Util::show(image);

    return 0;
}
