#ifndef ORB_DETECTOR_H
#define ORB_DETECTOR_H

#include<opencv2/opencv.hpp>
#include<vector>

class ORB_Detector
{
public:
    ORB_Detector(std::string image_name,int cam_num=0);



    void run();

private:

    cv::ORB featureDetector,featureExtractor;
    std::vector<cv::KeyPoint> train_kp;

    cv::Mat train,train_g,train_desc;
    cv::BFMatcher matcher;
    cv::Mat frame;
    std::vector<std::vector<cv::DMatch> > matches;
    std::vector<cv::DMatch> good_matches;

    void detect_compute_image(cv::Mat& image_to_detect,std::vector<cv::KeyPoint>& kp,cv::Mat& dest_image);
    void train_matcher();
    void run_video();
    void match_train_test(cv::Mat& test_image);
    void Lowes_algorithm();
    int cam_index;



};

#endif // ORB_DETECTOR_H
