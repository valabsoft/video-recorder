#ifndef COMMON_H
#define COMMON_H

#include <string>

// Константы модуля UTILITIES

const std::string UTILITIES_DEFAULT_RECORDER_FILENAME = "video";
const int UTILITIES_DEFAULT_RECORDER_INTERVAL = 5;
const int UTILITIES_DEFAULT_CAMERA_FPS = 25;

// Структуры

enum class CODEC
{
    XVID,
    MJPG,
    mp4v,
    h265
};

#endif // COMMON_H
