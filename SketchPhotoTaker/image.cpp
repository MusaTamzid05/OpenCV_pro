#include "image.h"

Image::Image(std::string filename, std::string window_name_):window_name(window_name_)
{
    image=cv::imread(filename);

    if(!IsimageLoaded(image))
        imageLoaded=false;
    else{
        imageLoaded=true;
        cv::namedWindow(window_name,cv::WINDOW_NORMAL);

    }


}
Image::Image(cv::Mat image, std::string window_name):window_name(window_name)
{
    this->image=image;
    imageLoaded=true;
     cv::namedWindow(window_name,cv::WINDOW_NORMAL);

}

Image::Image():imageLoaded(false),window_name("image")
{
     cv::namedWindow(window_name,cv::WINDOW_NORMAL);
}


bool Image::IsimageLoaded(const cv::Mat &image)
{
    if(image.empty())
    {
        std::cerr << "Image could not be loaded ";
        return false;
    }

    return true;
}

void Image::show(bool wait)
{
    if(!imageLoaded)
    {
        std::cerr << "Image is not loaded yet.\n";
        return;
    }

    cv::imshow(window_name,image);

    if(wait)
        cv::waitKey(20);




}
void Image::saveImage(const std::string filename)
{
    if(!imageLoaded)
    {
        std::cerr << "Image is not loaded yet.\n";
        return;
    }

    try
    {
        cv::imwrite(filename,image);
        std::cout<<filename<<" has been saved.\n";
    }
    catch(std::exception& e)
    {
        std::cout << e.what()<<"\n";
    }
}


void Image::setImage(cv::Mat image)
{
    this->image=image;
    imageLoaded=true;
}

void Image::setImage(std::string file_name)
{
    image=cv::imread(file_name);

    if(!IsimageLoaded(image))
        imageLoaded=false;
    else
        imageLoaded=true;
}
