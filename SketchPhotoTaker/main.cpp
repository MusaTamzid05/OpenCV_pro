#include <QCoreApplication>
#include "sketchplayer.h"


int main(int argc, char *argv[])
{
    int cam_index;

    try{

        if(argc ==2)
            cam_index=atoi(argv[1]);
        else if(argc == 1)
            cam_index=0;
        else{
            std::cerr <<"Usage: PhotoTaker cam_index.\n";
            exit(2);
        }

    }

    catch(std::exception& e)
    {
        std::cout << e.what();
        exit(3);
    }




    CartoonifyPlayer vid(cam_index);
    vid.run(false);

    return 0;
}
