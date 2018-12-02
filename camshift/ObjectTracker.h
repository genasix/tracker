//
// Created by 한우리 on 2018. 12. 2..
//

#ifndef OBJECT_TRACKING_CAMERA_FRAME_COTROLLER_H
#define OBJECT_TRACKING_CAMERA_FRAME_COTROLLER_H


#include <opencv2/core/types_c.h>
#include <ml.h>

class ObjectTracker {

public:
    ObjectTracker(int width, int height);

public:
    cv::Mat tracking(cv::Mat src);



private:
    const int WIDTH = 640;
    const int HEIGHT = 480;
    int m_id;
    int select_x_, select_y_;
    cv::Mat dst_;
    cv::Rect tracking_rect_;




};


#endif //OBJECT_TRACKING_CAMERA_FRAME_COTROLLER_H

