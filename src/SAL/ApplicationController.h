#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include "StdTypes.h"

class Button;
class SmoothMotion;
class EmotionDisplay;
class AudioPlayer;

class ApplicationController
{
public:
    explicit ApplicationController();
    virtual ~ApplicationController();
    
    void loop();
    EMOTION currentEmotion();
    void setEmotion(EMOTION emotion);
    virtual void initRobot() = 0;
    virtual int printf(const char *fmt, ...) = 0;
    virtual void msleep(int millis) = 0;
    virtual long getSystemTime() = 0;
    virtual void enableHardwareTimer(bool enable) = 0;
    virtual void enableMotor(MOTOR motorID, bool enable) = 0;
    int getScreenWidth();
    int getScreenHeight();
    unsigned char* getScreenData();
    float currentAngle(MOTOR motorID);
    void executeMotionLoop(MOTOR motorID);
    void executeAudioLoop();
    void executeOledLoop();
    void executeInputLoop();

protected:
    int m_appTimer;

private:
    EMOTION_STATE emotionStartupTask();
    EMOTION_STATE emotionHappyTask();
    EMOTION_STATE emotionAngryTask();
    EMOTION_STATE emotionTickledTask();
    EMOTION_STATE emotionSupprisedTask();

    EMOTION m_currentEmotion;
    EMOTION_STATE m_emotionState;
    Button* m_touchList[MAX_TOUCH];
    SmoothMotion* m_motionList[MAX_MOTOR];
    EmotionDisplay* m_emotionDisplay;
    AudioPlayer* m_audioPlayer;

};

#endif // APPLICATIONCONTROLLER_H
