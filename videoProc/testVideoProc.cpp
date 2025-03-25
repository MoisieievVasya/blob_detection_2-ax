#include <opencv2/opencv.hpp>
#include "videoProc.h"
#include <string>
#include <iostream>
#include <fstream>

int testVideo() {

  std::string videoPath = "/Users/admin/Documents/GitHub/blod_detection_2-ax/videos/test_video2.mp4";

  // Check if the file exists and is accessible
  if (std::ifstream file(videoPath); !file) {
    std::cerr << "Error: Cannot access video file at " << videoPath << std::endl;
    return 1;
  }
  std::pair<float, float> coords;

  VideoProc::processVideo(videoPath, coords);

  return 0;
}