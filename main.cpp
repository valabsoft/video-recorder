#include <iostream>
#include <thread>

#include "utilities.h"

void consoleOutput(int counter)
{
    using namespace std::chrono;
    auto timer = system_clock::to_time_t(system_clock::now());
    std::tm localTime = *std::localtime(&timer);
    std::ostringstream oss;
    std::string currentTime = "%H:%M:%S";
    oss << std::put_time(&localTime, currentTime.c_str());

    std::cout << oss.str() << ": " << "The video record #" << std::to_string(counter) << " started. Please wait ... " <<  std::endl;
}

int main()
{
    int cameraID = 0;
    // Создаем объект для захвата камеры
    cv::VideoCapture videoCapture(cameraID);

    int videoCounter = 1;

    if (videoCapture.isOpened())
    {
        clock_t mainTimer = clock();
        clock_t videoTimer = mainTimer;
        int videoDuration = 10; // 10 сек - длительность одного ролика

        // Старт первого потока записи
        std::thread counterThread(consoleOutput, videoCounter++);
        counterThread.join();

        std::thread videoThread(mrcv::recordVideo, videoCapture, videoDuration, "chersonesos", CODEC::XVID);
        videoThread.join();

        // Пишем в течении 1 минуты
        while((clock() - mainTimer) <= (60 * CLOCKS_PER_SEC))
        {
            if ((clock() - videoTimer) >= videoDuration * CLOCKS_PER_SEC)
            {
                videoTimer = clock();

                // Запускаем новую запись
                std::thread counterThread(consoleOutput, videoCounter++);
                counterThread.join();

                std::thread videoThread(mrcv::recordVideo, videoCapture, videoDuration, "chersonesos", CODEC::XVID);
                videoThread.join();
            }
        }
    }

    std::cout << "Done..." << std::endl;
    std::cin.get();

    return 0;
}
