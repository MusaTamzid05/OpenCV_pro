
#include"Video.h"

#include<iostream>

using namespace std;
using namespace cv;


Video::Video(string window_name,bool show_original_frame):cap(1),showOriginal(show_original_frame)
{
  
    if(!cap.isOpened())
    {
         cout<<"Cant open the camara.\n";
         camaraOn=false;
    }
    
    camaraOn=true;
    this->window_name=window_name;
}

void Video::run()
{
  if(!camaraOn)
        return;
        
  if(showOriginal)     
     namedWindow(window_name);
  
  while(cap.isOpened()&& char(waitKey(1)) !='q' )
  {
  
     cap >> frame;
     
     do_magic();
     
     if(showOriginal)
     imshow(window_name,frame);
     
     
  }
  
  
}
