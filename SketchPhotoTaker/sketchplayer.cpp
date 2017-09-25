#include "sketchplayer.h"
#include "image.h"

const int MEDIAN_BLUR_FILTER_SIZE=7;
const int LAPCIAN_FILTER_SIZE=5;
const int EDGES_THESHOLD=80;

CartoonifyPlayer::CartoonifyPlayer(int cam_index):
    VideoPlayer(cam_index)
{

}

void CartoonifyPlayer::do_magic()
{
    /**
    This code used here was learn by me from the book "Mastering OpenCV with Practical Computer Vision".
    **/

    cv::cvtColor(current_frame,gray,CV_BGR2GRAY);
    cv::medianBlur(gray,gray,MEDIAN_BLUR_FILTER_SIZE);
    cv::Mat edges;
    cv::Laplacian(gray,edges,CV_8U,LAPCIAN_FILTER_SIZE);

    cv::Mat mask;
    cv::threshold(edges,mask,EDGES_THESHOLD,255,cv::THRESH_BINARY_INV);






    this->image_holder->setImage(mask);
    image_holder->show(false);
}
