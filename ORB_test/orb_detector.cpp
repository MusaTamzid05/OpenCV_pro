#include "orb_detector.h"
#include<iostream>

#include"helper.h"

using namespace std;
using namespace cv;

const int TOTAL_NEAREST_NEIGBORES=2;
std::string WIN_NAME="Original";

ORB_Detector::ORB_Detector(std::string image_name, int cam_num):cam_index(cam_num)
{
  train=imread(image_name);

  if(train.empty())
  {
     cout<<"Could not load a image.\n";
     exit(1);
  }

  cvtColor(train,train_g,CV_BGR2GRAY);

}

void ORB_Detector::detect_compute_image(Mat& image_to_detect, std::vector<KeyPoint> &kp,Mat &dest_image)
{
    featureDetector.detect(image_to_detect,kp);
    featureExtractor.compute(image_to_detect,kp,dest_image);

   // show_image(train_desc);

}

void ORB_Detector::train_matcher()
{
    vector<Mat> train_desc_collection(1,train_desc);
    matcher.add(train_desc_collection);
    matcher.train();
}

void ORB_Detector::run()
{
    detect_compute_image(train_g,train_kp,train_desc);
    train_matcher();
    run_video();
}

void ORB_Detector::match_train_test(Mat &test_image)
{
    matcher.knnMatch(test_image,matches,TOTAL_NEAREST_NEIGBORES);
}

void ORB_Detector::Lowes_algorithm()
{
    for(unsigned int i=0; i < matches.size(); i++)
    {
        if(matches[i][0].distance < 0.6 * matches[i][1].distance)
        {
            good_matches.push_back(matches[i][0]);

        }
    }
}

void ORB_Detector::run_video()
{
    VideoCapture cap(cam_index);

    if(!cap.isOpened())
    {
        cout<<"Could not open the Video Camera.\n";
        exit(2);
    }


    Mat test,test_g,test_desc;
    vector<KeyPoint> test_kp;

    while(char(waitKey(1))!='q')
    {

        double t0=getTickCount();

        cap >> test;

        if(test.empty())
        {
            continue;
        }

        cvtColor(test,test_g,CV_BGR2GRAY);

        detect_compute_image(test_g,test_kp,test_desc);
        match_train_test(test_desc);
        Lowes_algorithm();
        Mat img_show;

        try{
            drawMatches(test,test_kp,train,train_kp,good_matches,img_show);
        }
        catch(std::exception& e)
        {
            cout<<e.what()<<"\n";
        }

        imshow("Matches",img_show);

        cout<<"Frame rate ="<<getTickFrequency()/(getTickCount()-t0)<<"\n";





    }


}
