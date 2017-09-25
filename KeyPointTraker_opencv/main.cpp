#include "detectorvideo.h"
#include<iostream>

int main(int argc, char *argv[])
{
    if(argc !=2)
    {
        std::cerr << "Usage:DetectorPattern test.jpg.\n";
        return -1;
    }
    try{

        std::string  image_name=(argv[1]);
        DetectorVideo vid(image_name);
        vid.run();
    }

    catch(std::exception &e)
    {
        std::cout << e.what()<<"\n";
    }
  
    return 0;
}

