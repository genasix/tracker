#include <iostream>
#include <opencv2/opencv.hpp>
#include "camshift/ObjectTracker.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    enum { k_cam_width = 640, };
    enum { k_cam_height = 480, };

    cv::VideoCapture capture;
    capture.open(0);
    if(!capture.isOpened()){
        std::cout << "please check you cam" << std::endl;
        return 1;
    }
    capture.set(CV_CAP_PROP_FRAME_WIDTH, k_cam_width);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, k_cam_height);
    ObjectTracker *objectTracker = new ObjectTracker(k_cam_width, k_cam_height);

    cv::Mat mat;
    while(1){
        //todo tracking
        capture >> mat;
        objectTracker->tracking(mat);

        char key = cv::waitKey(10);
        if( key==27)
            break;

    }
    free(objectTracker);
    capture.release();
    std::cout << "camera is stopped" << std::endl;


    return 0;
}