#ifndef CARTOONIFYPLAYER_H
#define CARTOONIFYPLAYER_H

#include "videoplayer.h"

class CartoonifyPlayer:public VideoPlayer
{
public:
                                             CartoonifyPlayer(int cam_index=0);
    virtual void                              do_magic();


private:

  cv::Mat                                           gray;




};

#endif // CARTOONIFYPLAYER_H
