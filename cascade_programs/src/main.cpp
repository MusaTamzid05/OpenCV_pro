#include "pedestrian_detector.h"
#include "video_player.h"


int main(int argc , char** argv){

    //Classifier::Pedestrian_Detector detector;
    
    IO::Video_Player vid("/home/musa/pedestrians.mp4" , "pedestrians");
    vid.set_detector(new Classifier::Pedestrian_Detector());

    vid.run();
    return 0;
}
