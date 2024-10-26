#ifndef UTILITIES_H
#define UTILITIES_H

#include "common.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <string>

namespace mrcv
{

std::string generateFileName(std::string filename, std::string fileextension);

int recordVideo(
    cv::VideoCapture videoCapture,
    int recordinterval = UTILITIES_DEFAULT_RECORDER_INTERVAL,
    std::string filename = UTILITIES_DEFAULT_RECORDER_FILENAME,
    CODEC codec=CODEC::XVID);

}

#endif // UTILITIES_H
