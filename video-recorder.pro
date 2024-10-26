TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        utilities.cpp

HEADERS += \
    common.h \
    utilities.h


win32 {
    INCLUDEPATH += c:\opencv-4.8.0-build\install\include\

    LIBS += c:\opencv-4.8.0-build\bin\libopencv_core480.dll
    LIBS += c:\opencv-4.8.0-build\bin\libopencv_highgui480.dll
    LIBS += c:\opencv-4.8.0-build\bin\libopencv_imgcodecs480.dll
    LIBS += c:\opencv-4.8.0-build\bin\libopencv_features2d480.dll
    LIBS += c:\opencv-4.8.0-build\bin\libopencv_calib3d480.dll
    LIBS += c:\opencv-4.8.0-build\bin\libopencv_videoio480.dll
    LIBS += c:\opencv-4.8.0-build\bin\libopencv_imgproc480.dll
}
unix {
    INCLUDEPATH += /usr/include/opencv4
    LIBS += -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_features2d -lopencv_calib3d -lopencv_videoio -lopencv_imgproc
}
