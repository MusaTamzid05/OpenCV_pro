#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <opencv2/opencv.hpp>

class Image;

class VideoProcessor
{
public:
    VideoProcessor(bool show_currentFrame_=true,int cap_index=0);
    virtual ~VideoProcessor();
    void run();

protected:


    virtual void                           do_magic(){}

    cv::VideoCapture                       cap;
    cv::Mat                                current_frame;
    Image*                                 m_image;

    cv::ORB                                featureDetector;
    cv::ORB                                featureExtractor;


    bool                                   show_currentFrame;
    bool                                   shouldQuit;

    void                                   handle_event();

};

#endif // VIDEOPROCESSOR_H
