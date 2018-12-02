//
// Created by 한우리 on 2018. 12. 2..
//

#include <highgui.h>
#include "ObjectTracker.h"

using namespace cv;
static cv::Point select_p1, select_p2;
static int width, height;
static bool is_selected;

namespace
{
    inline
    int NextTrackerId()
    {
        static int s_id = 0;
        return ++s_id;
    }

    inline
    std::string AppendWindowId(const char* baseName, int id)
    {
        std::stringstream ss;
        ss << baseName << " - " << id;
        return ss.str();
    }

    inline
    CvScalar hsv2rgb(float hue)
    {
        static const int sector_data[][3]= {{0,2,1}, {1,2,0}, {1,0,2},
                                            {2,0,1}, {2,1,0}, {0,1,2}};
        // H' = H / 60
        hue *= 0.01666666666666666666666666666666667f;
        const int sector = cvFloor(hue);
        int p = cvRound(255*(hue - sector)) ^ (sector & 1 ? 255 : 0);
        int rgb[3];
        rgb[sector_data[sector][0]] = 255;
        rgb[sector_data[sector][1]] = 0;
        rgb[sector_data[sector][2]] = p;
        return cvScalar(rgb[2], rgb[1], rgb[0], 0);
    }
} // end anonymous ns

static void onMouse(int event, int x, int y, int flags, void* param) {
    if(event == cv::EVENT_LBUTTONDOWN){
        select_p1 = cv::Point(x, y);
        is_selected = false;
    }else if(event == cv::EVENT_MOUSEMOVE && flags == cv::EVENT_FLAG_LBUTTON){
        x = x > ::width ? ::width : 0;
        y = y > ::height ? ::height : 0;
    }
    else if(event == cv::EVENT_LBUTTONUP){
        select_p2 = cv::Point(x,y); // final point
        is_selected  = true;
    }
}

cv::Mat ObjectTracker::tracking(const cv::Mat src) {
    //todo select roi
    cv::namedWindow("tracker");
    cv::setMouseCallback("tracker", onMouse, NULL);
    cv::Mat dst;
    src.copyTo(dst);
    if(is_selected){
        //todo processing..
        cv::namedWindow("selected");
        try{
            cv::rectangle(dst, ::select_p1, ::select_p2, Scalar(0, 0, 255));
            cv::Mat selected_mat = src(cv::Rect(::select_p1,select_p2));
            imshow("selected",selected_mat);
        }catch (Exception e){
            std::cout << e.msg << std::endl;
        }
    }

    cv::imshow("tracker", dst);

    return cv::Mat();
}



ObjectTracker::ObjectTracker(const int width, const int height) : m_id(NextTrackerId()) {
    ::width = width;
    ::height = height;
}

