#ifndef EMOTIONDISPLAY_H
#define EMOTIONDISPLAY_H
#include "StdTypes.h"

class ApplicationController;
class LCDLibrary;
class EmotionDisplay
{
public:
    EmotionDisplay(ApplicationController* app, int width, int height);
    void initEmotion(EMOTION newEmotion);
    void setState(DISPLAY_STATE state);
    DISPLAY_STATE currentState();
    DISPLAY_STATE displayMainFuntion();
    int getScreenWidth();
    int getScreenHeight();
    unsigned char* getScreenData();

private:
    void displayAnimStartup();
    void displayAnimWakeupOpenEyes();
    void displayAnimWakeupLookLeft();
    void displayAnimWakeupLookRight();
    void displayAnimWakeupYawn();
    void displayAnimIdle();
    void displayAnimHappy();
    void displayAnimAngry();
    void displayAnimTicled();
    void displayAnimSupprised();

    unsigned char m_frameData[9600]; // 320x240 bit
    LCDLibrary* m_lcd;
    int m_width;
    int m_height;
    DisplayParam m_currentParam;
    DISPLAY_STATE m_displayState;
    EMOTION m_currentEmotion;
    int m_animFrameIndex;
    ApplicationController* m_app;
};

#endif // EMOTIONDISPLAY_H
