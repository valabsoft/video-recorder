#include "utilities.h"

#include <iomanip>
#include <chrono>

namespace mrcv
{

std::string generateFileName(std::string filename, std::string fileextension)
{
    using namespace std::chrono;
    auto timer = system_clock::to_time_t(system_clock::now());
    std::tm localTime = *std::localtime(&timer);
    std::ostringstream oss;
    std::string fileName = filename + "_%d%m%Y%H%M%S" + fileextension;
    oss << std::put_time(&localTime, fileName.c_str());
    // return filename + fileextension; // Возвращаем имя файла без таймстемпа
    return oss.str();
}

int recordVideo(cv::VideoCapture videoCapture, int recordinterval, std::string filename, CODEC codec)
{
    //if (cameraid < 0)
    //    return -1; // Код ошибки - ID камеры задан неверно

    //if (recordinterval < UTILITIES_DEFAULT_RECORDER_INTERVAL)
    //    return -2; // Код ошибки - Интервал записи не может быть меньше 10 сек.

    if (filename.empty())
        filename = UTILITIES_DEFAULT_RECORDER_FILENAME;

    // Создаем объект для записи видео
    cv::VideoWriter videoWriter;
    std::string fileExtension;

    // Определяем параметры videoWriter
    // и расширение выходного файла в зависимости от кодека
    int fourccCode;
    switch (codec)
    {
    case CODEC::MJPG:
        fourccCode = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
        fileExtension = ".mp4";
        break;
    case CODEC::mp4v:
        fourccCode = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
        fileExtension = ".mp4";
        break;
    case CODEC::h265:
        fourccCode = cv::VideoWriter::fourcc('h', '2', '6', '5');
        fileExtension = ".mp4";
        break;
    case CODEC::XVID:
        fourccCode = cv::VideoWriter::fourcc('X', 'V', 'I', 'D');
        fileExtension = ".avi";
        break;
    default:
        fourccCode = cv::VideoWriter::fourcc('X', 'V', 'I', 'D');
        fileExtension = ".avi";
        break;
    }

    // Генерируем имя файла с привязкой к текущему времени
    std::string fileName = generateFileName(filename, fileExtension);

    // Разрешение камеры
    cv::Size cameraResolution((int)videoCapture.get(cv::CAP_PROP_FRAME_WIDTH),
                              (int)videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT));

    // FPS камеры
    int cameraFPS = (int)videoCapture.get(cv::CAP_PROP_FPS);
    if (cameraFPS == 0)
        cameraFPS = UTILITIES_DEFAULT_CAMERA_FPS;

    int bufferSize = cameraFPS * recordinterval;

    std::vector<cv::Mat> frames;
    frames.reserve((size_t)bufferSize);

    clock_t timerStart = clock();
    cv::Mat videoFrame;

    // Цикл записи видеопотока в файл
    while((clock() - timerStart) <= (recordinterval * CLOCKS_PER_SEC))
    {
        // Захват фрейма
        videoCapture >> videoFrame;
        frames.push_back(videoFrame.clone());

        // Реальный FPS значительно меньше величины cameraFPS
        // поэтому накапливаем фреймы сколько можем,
        // потом вычисляее реальный FPS и только тогда создаем VideoWriter

        // Накапливаем фреймы
        //if (frameCounter <= customFPS)
        //{
        //    frameCounter++;
        //    frames.push_back(videoFrame.clone());
        //}

        // Сброс счетчиков
        //if (clock() - timerFrame > CLOCKS_PER_SEC)
        //{
        //    frameCounter = 0;
        //    timerFrame = clock();
        //}
    }

    int realFPS = (int)(frames.size() / recordinterval);

    // Сохранение видео
    videoWriter = cv::VideoWriter(fileName, fourccCode, realFPS , cameraResolution);
    if (videoWriter.isOpened())
    {
        for(auto frame : frames)
        {
            videoWriter.write(frame);
        }
        // Освобождение объекта записи видеопотока
        videoWriter.release();
    }

    // Освобождение объекта захвата камеры
    videoCapture.release();

    // Возврат кода нормального завершения работы
    return 0;
}

}
