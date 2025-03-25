#ifndef VIDEO_PROC_H
#define VIDEO_PROC_H

#include <opencv2/opencv.hpp>
#include <string>
#include "../communication/mavlinkCommand.h"

class VideoProc {
public:
    static void processVideo(const std::string& videoPath, std::pair<float, float>& coords);
    static std::pair<float, float> detectBlob(const cv::Mat& frame);
private:
    static std::pair<float, float> prevCoords;
};

#endif //VIDEO_PROC_H
