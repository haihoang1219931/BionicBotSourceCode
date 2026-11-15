#ifndef EMOTIONDISPLAY_H
#define EMOTIONDISPLAY_H
#include "StdTypes.h"

class ApplicationController;
class EmotionDisplay
{
public:
    EmotionDisplay(ApplicationController* app, int width, int height);
    void setState(DISPLAY_STATE state);
    DISPLAY_STATE currentState();
    DISPLAY_STATE displayMainFuntion();
    int getScreenWidth();
    int getScreenHeight();
    unsigned char* getScreenData();

private:
    int m_width;
    int m_height;
    unsigned char m_frameData[9600]; // 320x240 bit
    ApplicationController* m_app;
    DisplayParam m_currentParam;
    DISPLAY_STATE m_displayState;
};

#endif // EMOTIONDISPLAY_H
