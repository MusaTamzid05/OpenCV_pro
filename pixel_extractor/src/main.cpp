#include "extractor.h"



int main(int argc , char** argv) {


    cv::Mat image = cv::imread("./test.jpg");
    CV::Pixel_Extractor extractor(image);

    int height= image.rows;
    int width  = image.cols;



    
    cv::Mat result;

    extractor.get_extracted_image(200, 0 , 100 , height, result);
    cv::imwrite("result.jpg" , result);
    



    std::cout << "image saved.\n";


    return 0;
}

