#include "image.h"



Image::Image():image_set(false){}

Image::Image(std::string filename, std::string window_name_):
    window_name(window_name_),
    image_set(false)
{
   image=cv::imread(filename);

   if(image.empty())
   {
       std::cout << "Could not load the image.\n";
   }
   else
       image_set=true;
}

Image::Image(cv::Mat image_, std::string window_name_):
    window_name(window_name_),
    image_set(true)
{
    image=image_;
}


void Image::show(bool wait)
{
    cv::imshow(window_name,image);

    if(wait)
       cv::waitKey(20);
}


void Image::setImage(cv::Mat &image)
{
    this->image=image;
    image_set=true;
}

cv::Mat Image::getImage()
{
    return image;
}
