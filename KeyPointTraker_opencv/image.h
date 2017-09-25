#ifndef IMAGE_H
#define IMAGE_H

#include<opencv2/opencv.hpp>

class Image
{
public:
                     Image(std::string filename,std::string window_name_="image");
                     Image(cv::Mat image_,std::string window_name_="image");
                     Image();

  void               show(bool wait=true);  /****
                                               wait is from user  to see the image.
                                               But when inside a video loop,it should set to false.
                                            ***/

  void               setImage(cv::Mat& image);
  cv::Mat            getImage();


private:

    bool                             image_set;
    cv::Mat                          image;
    std::string                      window_name;

};

#endif // IMAGE_H
