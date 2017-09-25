#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include<opencv2/opencv.hpp>
class Image;

class VideoPlayer
{
public:
                                              VideoPlayer(int cam_index=0);
    virtual                                  ~VideoPlayer();



    void                                      run(bool show_currentframe=true);


protected:

    cv::VideoCapture                          cap;
    cv::Mat                                   current_frame;
    Image*                                    image_holder;




    void                                      handle_event();
    bool                                      shouldQuit;

    virtual void                              do_magic(){}


};

#endif // VIDEOPLAYER_H
