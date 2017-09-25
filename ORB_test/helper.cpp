#include "helper.h"

using namespace cv;
const std::string WIN_NAME="Press q to quit";

void show_image(cv::Mat image)
{
    namedWindow(WIN_NAME,WINDOW_NORMAL);

    while(char(waitKey(1))!= 'q')
    {
        imshow(WIN_NAME,image);
    }
}
