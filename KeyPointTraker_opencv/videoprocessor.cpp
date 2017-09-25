#include "videoprocessor.h"

#include<iostream>
#include<cstdlib>
#include"image.h"

const int ESC=27;

VideoProcessor::VideoProcessor(bool show_currentFrame_,int cap_index):
    cap(cap_index),
    m_image(new Image()),
    show_currentFrame(show_currentFrame_),
    shouldQuit(false)
{
     if(!cap.isOpened())
     {
         std::cout << "Could not initialize the camera.\n";
         exit(1);

     }
}


VideoProcessor::~VideoProcessor()
{
    delete m_image;
}


void VideoProcessor::run()
{
    while(cap.isOpened() && !shouldQuit)
    {
        cap >> current_frame;

        if(current_frame.empty())
        {
            break;
        }

        do_magic();

        if(show_currentFrame){

            m_image->setImage(current_frame);
            m_image->show(false);

        }

        handle_event();





    }
}

void VideoProcessor::handle_event()
{
    char key=cv::waitKey(20);

    if(key =='q' || key == ESC)
        shouldQuit=true;

}




