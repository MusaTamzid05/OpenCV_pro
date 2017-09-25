#include <QCoreApplication>
#include"orb_detector.h"
#include<exception>
#include<opencv2/opencv.hpp>
#include<cstdlib>
#include<iostream>

using namespace std;
using namespace cv;



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    try
    {
        if(argc < 2)
        {
            std::cout <<"Usage:ORB_Detector image.\n";
            exit(1);
        }

        int cam_index=0;

        if(argc == 3)
            cam_index=atoi(argv[2]);

        std::string image_name=argv[1];



        ORB_Detector detect(image_name,cam_index);
        detect.run();


        return 0;
    }

     catch (exception& e)
           {

        std::cout << e.what()<<"\n";
    }


    return a.exec();
}
