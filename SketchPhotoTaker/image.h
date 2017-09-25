#ifndef IMAGE_H
#define IMAGE_H

#include<opencv2/opencv.hpp>
#include<string>


class Image
{
public:
                                                Image(std::string filename, std::string window_name_="Image");
                                                Image(cv::Mat image,std::string window_name="Image");
                                                Image();

    void                                        show(bool wait=true);

    void                                        setImage(std::string file_name);
    void                                        setImage(cv::Mat image);


    void                                        saveImage(const std::string filename);


private:

    cv::Mat                                     image;
    std::string                                 window_name;


    bool                                        imageLoaded;
    bool                                        IsimageLoaded(const cv::Mat& image);
};

#endif // IMAGE_H
