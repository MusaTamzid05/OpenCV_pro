#include "videoplayer.h"
#include "image.h"
#include<cstdlib>

const int ESC=27;

VideoPlayer::VideoPlayer(int cam_index):
    cap(cam_index),
    image_holder(new Image()),
    shouldQuit(false)

{
    if(!cap.isOpened())
    {
        std::cerr << "Could not open the camera.\n";
        exit(1);
    }


}
VideoPlayer::~VideoPlayer()
{
    delete this->image_holder;
    cv::destroyAllWindows();
}

void VideoPlayer::run(bool show_currentframe)
{
    while(!shouldQuit)
    {
        cap >> current_frame;

        if(current_frame.empty())
        {
            shouldQuit=true;
        }

        do_magic();

        if(show_currentframe)
            cv::imshow("Current frame",current_frame);


        handle_event();
    }
}

void VideoPlayer::handle_event()
{
    char key=cv::waitKey(20);

    if(key == ESC || key == 'q')
    {
        shouldQuit=true;
    }

    else if(key == 's')
    {
        cv::destroyAllWindows();
        std::cout << "Enter the image name:";
        std::string file_name;
        std::cin >> file_name;
        image_holder->saveImage(file_name);


    }
}
