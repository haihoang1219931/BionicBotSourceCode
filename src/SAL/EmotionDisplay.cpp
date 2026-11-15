#include "EmotionDisplay.h"

EmotionDisplay::EmotionDisplay(ApplicationController* app):
    m_app(app)
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
