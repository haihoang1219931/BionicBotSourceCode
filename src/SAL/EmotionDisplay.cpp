#include "EmotionDisplay.h"
#include "LCDLibrary.h"

EmotionDisplay::EmotionDisplay(ApplicationController* app, int width, int height):
    m_app(app),
    m_width(width),
    m_height(height)
{

}

void EmotionDisplay::setState(DISPLAY_STATE state)
{
    m_displayState = state;
}

DISPLAY_STATE EmotionDisplay::currentState()
{
    return m_displayState;
}

int EmotionDisplay::getScreenWidth()
{
    return m_width;
}

int EmotionDisplay::getScreenHeight()
{
    return m_height;
}

unsigned char* EmotionDisplay::getScreenData()
{
    return m_frameData;
}

DISPLAY_STATE EmotionDisplay::displayMainFuntion() {
    DISPLAY_STATE currentState = m_displayState;
    switch (currentState) {
    case DISPLAY_IDLE:
    {

    }
        break;
    case DISPLAY_INIT:
    {

    }
        break;
    case DISPLAY_INPROGRESS:
    {

    }
        break;
    case DISPLAY_DONE:
        break;
    }
    return currentState;
}
