#include "videoProc.h"

#include "../controls/controls.h"
#include <thread>
#include <vector>

std::pair<float, float> VideoProc::prevCoords = {0, 0};

void VideoProc::processVideo(const std::string& videoPath, std::pair<float, float>& coords) {

    // Read video file
    cv::VideoCapture cap(videoPath);
    if (!cap.isOpened()) {
        std::cerr << "Error opening video file" << std::endl;
        return;
    }

    // Read video frame by frame and detect blob
    cv::Mat frame;
    std::vector<std::thread> threads;
    while (cap.read(frame)) {
        if (frame.empty()) {
            break;
        }
        coords = detectBlob(frame);
        threads.emplace_back(controls::adjustDroneVelocity_2ax, coords.first, coords.second);
    }
}

std::pair<float, float> VideoProc::detectBlob(const cv::Mat& frame) {

    // Apply GaussianBlur to reduce noise
    cv::Mat blurred;
    cv::GaussianBlur(frame, blurred, cv::Size(3, 3), 1.5);

    // Convert to grayscale
    cv::Mat gray;
    cv::cvtColor(blurred, gray, cv::COLOR_BGR2GRAY);


    // Apply Laplacian of Gaussian (LoG) filter
    cv::Mat log;
    cv::Laplacian(gray, log, CV_16U, 3);
    cv::convertScaleAbs(log, log);


    // Apply thresholding to enhance edges
    cv::Mat thresholded;
    cv::threshold(log, thresholded, 22, 255, cv::THRESH_BINARY);


    // for debugging and setting params
    cv::imshow("LoG", log);
    cv::imshow("Blur", blurred);


    // Set up the SimpleBlobDetector parameters
    cv::SimpleBlobDetector::Params params;
    params.filterByArea = true;
    params.minArea = 10; // Detect smaller objects
    params.maxArea = 5000;


    // Create a SimpleBlobDetector
    cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);

    // Detect blobs
    std::vector<cv::KeyPoint> keypoints;
    detector->detect(thresholded, keypoints);

    // Select the largest blob
    if (!keypoints.empty()) {
        auto largestBlob = std::max_element(keypoints.begin(), keypoints.end(),
        [](const cv::KeyPoint& a, const cv::KeyPoint& b) {return a.size < b.size;});

        // Calculate the centroid of the largest blob
        cv::Point2f centroid = largestBlob->pt;

        // Calculate the center of the image
        cv::Point2f imageCenter(frame.cols / 2.0f, frame.rows / 2.0f);

        // Calculate the horizontal offset (X-Axis)
        float horizontalOffset = centroid.x - imageCenter.x;

        // Calculate the forward/backward correction (Y-Axis)
        float forwardBackwardCorrection = imageCenter.y - centroid.y;

        // Draw detected blobs as red circles
        cv::Mat output;
        cv::drawKeypoints(frame, std::vector<cv::KeyPoint>{*largestBlob}, output, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

        // Show the output image
        cv::imshow("Blobs", output);
        cv::waitKey(1);

        // Update previous coordinates and blob
        prevCoords = std::make_pair(horizontalOffset, forwardBackwardCorrection);

        return prevCoords;
    } else {
        // Draw the previous blob on the current frame
        cv::Mat output;
        cv::drawKeypoints(frame, keypoints, output, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

        // Show the output image
        cv::imshow("Blobs", output);
        cv::waitKey(1);
        return prevCoords;
    }
}

