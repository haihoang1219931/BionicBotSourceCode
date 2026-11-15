TEMPLATE = app
CONFIG += c++11 no_keywords console

QT += qml quick qml
CONFIG += c++11

HEADERS += \
    src/SAL/AudioPlayer.h \
    src/SAL/EmotionDisplay.h \
    src/SAL/SmoothMotion.h \
    src/SAL/Button.h \
    src/SAL/ApplicationController.h \
    src/SAL/StdTypes.h \
    RobotSim/VideoDisplay/VideoRender.h \
    RobotSim/VideoDisplay/I420Render.h \
    RobotSim/HardwareTimerSim.h \
    RobotSim/ApplicationSim.h \
    RobotSim/MainProcess.h

SOURCES += \
    main.cpp \
    src/SAL/AudioPlayer.cpp \
    src/SAL/EmotionDisplay.cpp \
    src/SAL/SmoothMotion.cpp \
    src/SAL/Button.cpp \
    src/SAL/ApplicationController.cpp \
    RobotSim/VideoDisplay/VideoRender.cpp \
    RobotSim/VideoDisplay/I420Render.cpp \
    RobotSim/HardwareTimerSim.cpp \
    RobotSim/ApplicationSim.cpp \
    RobotSim/MainProcess.cpp

RESOURCES += \
    RobotSim/qml.qrc
