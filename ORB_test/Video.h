#ifndef VIDEO_H
#define VIDEO_H

#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<string>

class Video
{
  public:
  
     Video(std::string window_name,bool show_original_frame=true);
     
     void run();
     
     /*
     This do_magic function will do all the image processing stuff.
     Because this class only shows image,this function does nothing.
     But the that will inharit this will have some of its owns
     Process.
     */
     
     protected:
     
     virtual void do_magic(){}
     

  
  
     cv::VideoCapture cap;
     cv::Mat frame;
     
     std::string window_name;
     
     bool camaraOn;
     bool showOriginal;
     

};




#endif
