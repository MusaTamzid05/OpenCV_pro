#include "detectorvideo.h"
#include<cstdlib>
#include"image.h"


DetectorVideo::DetectorVideo(std::string testImageName, int total_nearest_neigbore, int cam_index):
    VideoProcessor(false,cam_index),
    nearest_neigbore(total_nearest_neigbore)

{
     train_image=cv::imread(testImageName);

     if(train_image.empty())
     {
         std::cout << "Could not load " << testImageName << " as test image.\n";
         exit(2);
     }

     std::cout << "test image loaded.\n";

     // change the test image to gray for make computation much each

     cv::cvtColor(train_image,train_image,CV_BGR2GRAY);
     Image image(train_image,"Train Image");
     image.show(false);

     if(!patternFound(train_image,train_keypoints,train_desc))
     {

         std::cerr << "No pattern found in the train image..\n";
         std::cout<<"Termination program.\n";
         exit(3);
     }

     std::vector<cv::Mat>  train_desc_collition(1,train_desc);
     matcher.add(train_desc_collition);
     matcher.train();
     std::cout << "tranning with train image is complete.\n";





}


void DetectorVideo::do_magic()
{
     cap >> test_image;
     cv::cvtColor(test_image,test_image,CV_BGR2GRAY);

     if(!patternFound(test_image,test_keypoints,test_desc))
     {
         std::cout << "Pattern now found in the test image.\n";
         return;
     }

     std::vector<std::vector<cv::DMatch> > matches;
     matcher.knnMatch(test_desc,matches,2);


     std::vector<cv::DMatch> good_matches;

     /*
      * we are applying laws algorith here.
      *
     **/
     for(unsigned int i=0; i < matches.size() ; i++)
     {
         if(matches[i][0].distance < 0.6* matches[i][1].distance)
             good_matches.push_back(matches[i][0]);
     }

     cv::Mat img_show;

     cv::drawMatches(test_image,test_keypoints,train_image,train_keypoints,good_matches,img_show);
     cv::imshow("Matches",img_show);
}


bool DetectorVideo::patternFound(cv::Mat &src_image, std::vector<cv::KeyPoint> &keypoints, cv::Mat &dst_image)
{
    featureDetector.detect(src_image,keypoints);

    if(keypoints.empty())
        return false;

    featureDetector.compute(src_image,keypoints,dst_image);

    return true;
}
