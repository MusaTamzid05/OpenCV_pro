#ifndef DETECTORVIDEO_H
#define DETECTORVIDEO_H

#include"videoprocessor.h"

class DetectorVideo:public VideoProcessor

{
public:
                                                       DetectorVideo(std::string testImageName,
                                                                     int total_nearest_neigbore=2,
                                                                     int cam_index=0);

    virtual void                                       do_magic();

private:
    int nearest_neigbore;

    bool                                               patternFound(cv::Mat& src_image,
                                                                      std::vector<cv::KeyPoint>& keypoints,
                                                                      cv::Mat& dst_image);
    void                                               train();






    cv::Mat                                            train_image,train_desc;
    std::vector<cv::KeyPoint>                          train_keypoints;


    cv::Mat                                            test_image,test_desc;
    std::vector<cv::KeyPoint>                          test_keypoints;





    cv::BFMatcher                                      matcher;



};

#endif // DETECTORVIDEO_H
