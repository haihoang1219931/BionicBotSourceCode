#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include "StdTypes.h"

class Button;
class SmoothMotion;
class EyeDisplay;
class AudioPlayer;

class ApplicationController
{
public:
    explicit ApplicationController();
    virtual ~ApplicationController();
    
    void loop();
    EMOTION_STATE state();
    void setState(EMOTION_STATE state);
    virtual void initRobot() = 0;
    virtual int printf(const char *fmt, ...) = 0;
    virtual void msleep(int millis) = 0;
    virtual long getSystemTime() = 0;
    virtual void enableHardwareTimer(bool enable) = 0;
    void executeMotionLoop(MOTOR motorID);
    void executeAudioLoop();
    void executeOledLoop();
    void executeInputLoop();

public:
    EMOTION_STATE m_state;
    Button* m_touchList[MAX_TOUCH];
    SmoothMotion* m_motionList[MAX_MOTOR];
    EyeDisplay* m_eyeDisplay;
    AudioPlayer* m_audioPlayer;
    int m_appTimer;
};

#endif // APPLICATIONCONTROLLER_H
