#include "camera.h"
#include <cstdlib>
#include <memory>

int main(int argc ,char **argv){

    try{
        
        int cam_num;
        if(argc == 2)
            cam_num = atoi(argv[1]);
        else
            cam_num = 0;

        auto cam =  std::make_shared<Camera>("Press p to take pic", cam_num);
        cam->run();

    }
    catch(std::exception &e){
        std::cerr << e.what() << "\n";
    }

    return 0;
}
