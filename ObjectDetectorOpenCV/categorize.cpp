#include "categorize.h"
#include "define.h"
#include <iostream>
#include <cstdlib>



void testImage(const cv::Mat& image,std::string image_name)
{
    if(image.empty())
        std::cout << image_name << " is empty.";
    else
        std::cout << image_name <<" not empty.\n";
}
Categorize::Categorize(int _cluster)
{
  cluster = _cluster;

  // all the intialization
  
  featureDetector = new cv::ORB();
  descriptorExtractor = new cv::ORB();
  bowtrainer       = new cv::BOWKMeansTrainer(cluster);
  descriptorMatcher = (new cv::BFMatcher());
  bowDescriptorExtractor = (new cv::BOWImgDescriptorExtractor(descriptorExtractor , descriptorMatcher));

   // save all images from the template folder.template folder 
   // has the crop image of the object we want to detect.
   // we are gone use this images to both train and 
  // if the object gets detected than we are gone show this
  //  object to user rather showing "object detected"
 for(boost::filesystem::directory_iterator i(TEMPLATE_FOLDER),end_iter ; i != end_iter;i++){

     std::string filename =i->path().filename().string();

     // remove the file extansation.
     std::string category = remove_extension(filename);
     
     // save the image with its category.
     cv::Mat im = cv::imread(TEMPLATE_FOLDER + filename),temp_img;
     objects[category] = im;
   
     // make the image gray and save it im template.
     //
     
    cv::cvtColor(im,temp_img,CV_BGR2GRAY); // templates are the croped image of the object that we want to detect.
     templates[category] = temp_img;

 
 }
     std::cout << "Organized.\n";
     make_train_set();
}

std::string Categorize::remove_extension(std::string file_name){
  int last_idx = file_name.find_last_of(".");
  std::string name = file_name.substr(0,last_idx);
  return name;
}

void Categorize::make_train_set(){
  
    // here we save images according to there 
    // catetegory in training_set
    std::string category;
        
 for(boost::filesystem::recursive_directory_iterator i(TRAIN_FOLDER),end_iter ; i != end_iter;i++){

    // the root folder does not have any image file but the
    // folder that contains the image, so we are basically
    // saving folder name
      if(i.level() == 0) 
      {
          category = (i->path()).filename().string();
          category_names.push_back(category);
        
      }

      else{

          // save the image according to its category name
           std::string filename = std::string(TRAIN_FOLDER) + category + std::string("/") + (i->path()).filename().string();

           // map the image and save it.
           std::pair<std::string,cv::Mat> p(category,cv::imread(filename, CV_LOAD_IMAGE_GRAYSCALE));
           
           train_set.insert(p);


      }
      
 }

 categories = category_names.size();

 std::cout << "Total "<< categories << " of image found.\n";
 
}


void Categorize::build_vocab()
{
    // here we do
    // 1.detect and extract the key point from the template image
    // 2.create a cluster using the descriptorcwe are using.:
   cv::Mat vocab_descriptor;
   // for each image , detect the key points andd then compute

   // templates are crop images of object that we want to detect.
   // we are gono train with this images to get the best key points.

  for(std::map<std::string , cv::Mat>::iterator i = templates.begin(); i!= templates.end() ; i++ ){
  
        std::vector<cv::KeyPoint> kp;
        cv::Mat temp1 = (*i).second;
        cv::Mat desc;
        featureDetector->detect(temp1,kp);  // keypoints from the image detected.

        descriptorExtractor->compute(temp1,kp,desc);  // saving the keypoints to the source

        /**
         * We need to convert the image file to CV_32F because
         * the function BOWKMeansTrainer(Bag of Words trainer using 
         * kmeans) expect floating point data
         *
         * **/
        desc.convertTo(desc,CV_32F); 
        vocab_descriptor.push_back(desc);
  }
   // add the descriptor to bow trainer cluster

  bowtrainer->add(vocab_descriptor);   // adding all the train data to the clustter
  vocab = bowtrainer->cluster();
  // save it to the vocabulary

  cv::Mat temp;

  // the descriptor needs to calculate using the vacab
  // but the bowDescriptorExtractor uses mat format
  //  of CV_8C1 and the vocab uses CV_32F.
  //  so we convert the vocal to CV_8UC1 and
  //  set the descriptor vocabulary to it
  vocab.convertTo(temp,CV_8UC1);
  
  bowDescriptorExtractor->setVocabulary(temp);
  
  cv::FileStorage fs(DATA_FOLDER + "vocab.xml" , cv::FileStorage::WRITE);
  // save the vocabulary

  fs << "vocabulary" << vocab;
  fs.release();

  std::cout << "build vocabulary." << "\n";
}

void Categorize::make_pos_neg(){

    

    for(std::multimap<std::string,cv::Mat>::iterator i = train_set.begin(); i!= train_set.end(); i++ )
    {
        std::string category = (*i).first;

        cv::Mat im = (*i).second , feat; // the training image

        // we are gone detect keypoint from this image
        

        std::vector<cv::KeyPoint> kp;
        featureDetector->detect(im,kp);
        bowDescriptorExtractor->compute(im , kp, feat);
       
        cv::Mat pos , neg;

        for(int cat_index = 0 ; cat_index != categories ; cat_index++)
        {
               // if the data is positive fill the positive 
               //  else fill the negetive map
               
            std::string check_category = category_names[cat_index];

            if(check_category.compare(category) == 0 )
            {
                 postive_data[check_category].push_back(feat);
            }
            else
                negative_data[check_category].push_back(feat);
        }
    }

     // debug message
     
    for(int i = 0; i < categories; i++){
          std::string category = category_names[i];

          std::cout << "Category " << category << ":" << postive_data[category].rows <<" Positives "<< negative_data[category].rows << " Negatives.\n";
          
    }
}

void Categorize::train_classifier(){

    // here we use Support Vector Machine to detect the object
    // first we get the positive and negative data for the
    // image.For each image we start a loop andif the image 
    // is positive we label it 1 else  we label it 0 for 
    // the negative that we train the svm
    
    
    make_pos_neg();

    for(int i = 0 ; i < categories; i++)
    {
       // we make all positive data label 1 and all negative data 
       //  label 0
       
        std::string category = category_names[i];
       
         // first positive data
        cv::Mat train_data = postive_data[category];
        cv::Mat train_labels = cv::Mat::ones(train_data.rows,1,CV_32S);//Note that label was created with label one


        // then the negative data

        train_data.push_back(negative_data[category]);
        cv::Mat m = cv::Mat::zeros(negative_data[category].rows,1,CV_32S);
        train_labels.push_back(m);

        //svms[category].train(train_data,train_labels);
        svms[category].train(train_data,train_labels);
        
        // Save the SVM file

        std::string svm_filename = std::string(DATA_FOLDER) + category+ std::string("SVL.xml");

        svms[category].save(svm_filename.c_str());

        std::cout << "Train and saved SVM for category " << category <<"\n";

    }
}


void Categorize::categorize()
{
   
   cv::VideoCapture cap(0);

   if(!cap.isOpened())
   {
        std::cerr << "Could not open the video Camera.\n";
        exit(1);

   }
   std::cout << "Strating to categorize object.\n";
   cv::namedWindow(WINDOW_NAME);

   // run this program while the user does not press 'q'
   
   while(char(cv::waitKey(1))!='q')
    {

        cv::Mat  frame , frame_g;
        cap >> frame;
        cv::imshow(WINDOW_NAME,frame);

        cv::cvtColor(frame,frame_g,CV_BGRA2GRAY);
       

        // detector the keypoints of the current image and 
        // compute with the descriptor.
        
        std::vector<cv::KeyPoint> kp;

        cv::Mat test;
        
        featureDetector->detect(frame_g,kp);
        bowDescriptorExtractor->compute(frame_g,kp,test);


        float best_score = 777;
        std::string predicted_category;

        for(int i=0;i < categories ; i++)
        {
               std::string category = category_names[i];

               // choose image with the lowest score.
               // choosing the object with the most 
               // nagetive  sign distance .
               float prediction = svms[category].predict(test,true);
               //std::cout << "Prediction :" << prediction << "\n";
               

               if(prediction < best_score)
               {
                     best_score = prediction;
                     predicted_category = category;


               }

            

        }

           cv::imshow("Detected object ",objects[predicted_category]);

        


    }

}
