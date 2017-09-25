#ifndef CATEGORIZE_H
#define CATEGORIZE_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <map>
#include <vector>
#include <opencv2/ml/ml.hpp>
class Categorize{
   
    public:

        Categorize(int _cluster);

       void                                           build_vocab();
       void                                           train_classifier();

       void                                           categorize();
    private:
          // map from category.
        std::map<std::string,cv::Mat> templates , objects , postive_data , negative_data;
        
        std::map<std::string,CvSVM> svms;

    
        std::multimap<std::string,cv::Mat> train_set;
        std::vector<std::string>    category_names;
        
        int                         categories;
        int                         cluster;
        cv::Mat                     vocab;

           // features detector and extractor
        std::string remove_extension(std::string filename); 
       cv::Ptr<cv::ORB>                               featureDetector;
       cv::Ptr<cv::ORB>                               descriptorExtractor;
       cv::Ptr<cv::BOWKMeansTrainer>                  bowtrainer;
       cv::Ptr<cv::BOWImgDescriptorExtractor>         bowDescriptorExtractor;
       cv::Ptr<cv::BFMatcher>                         descriptorMatcher;
       
       void                                           make_train_set();

       // make postive and negative image from the images.


       void                                           make_pos_neg();

};
#endif
