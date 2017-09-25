#include "detector.h"

namespace Classifier{
    
    class Pedestrian_Detector: public Detector{

        public:

            Pedestrian_Detector();
            virtual ~Pedestrian_Detector();

            virtual void get_detect_objects(cv::Mat& image , cv::Mat& result_image);
    };

};
