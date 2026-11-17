#include "EmotionDisplay.h"
#include "LCDLibrary.h"

#define EYE_WITH 40
#define EYE_HEIGHT 40
EmotionDisplay::EmotionDisplay(ApplicationController* app, int width, int height):
    m_width(width),
    m_height(height),
    m_app(app)
{

}

void EmotionDisplay::setState(DISPLAY_STATE state)
{
    m_displayState = state;
}

void EmotionDisplay::initEmotion(EMOTION newEmotion)
{
    setState(DISPLAY_INIT);
    m_currentEmotion = newEmotion;
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


DISPLAY_STATE EmotionDisplay::displayMainFuntion()
{
    DISPLAY_STATE currentState = m_displayState;
    switch (m_currentEmotion) {
    case EMOTION_START_UP: {
        displayAnimStartup();
    }
        break;
    case EMOTION_WAKEUP_OPEN_EYES: {
        displayAnimWakeupOpenEyes();
    }
        break;
    case EMOTION_WAKEUP_LOOK_LEFT: {
        displayAnimWakeupLookLeft();
    }
        break;
    case EMOTION_WAKEUP_LOOK_RIGHT: {
        displayAnimWakeupLookRight();
    }
        break;
    case EMOTION_WAKEUP_YAWN: {
        displayAnimWakeupYawn();
    }
        break;
    case EMOTION_IDLE: {
        displayAnimIdle();
    }
        break;
    case EMOTION_HAPPY: {
        displayAnimHappy();
    }
        break;
    case EMOTION_ANGRY: {
        displayAnimAngry();
    }
        break;
    case EMOTION_TICKLED: {
        displayAnimTicled();
    }
        break;
    case EMOTION_SUPPRISED: {
        displayAnimSupprised();
    }
        break;
    }
    return m_displayState;
}

void EmotionDisplay::displayAnimStartup()
{
    DISPLAY_STATE currentState = m_displayState;
    switch (currentState) {
    case DISPLAY_IDLE:
    {
        m_animFrameIndex ++;
        if(m_animFrameIndex == 30) {
            m_animFrameIndex = 0;
            m_displayState = DISPLAY_DONE;
            LCDLibrary::clear(m_frameData,m_width,m_height);
        }
    }
        break;
    case DISPLAY_INIT:
    {
        LCDLibrary::clear(m_frameData,m_width,m_height);
        m_displayState = DISPLAY_INPROGRESS;
        m_animFrameIndex = 0;
    }
        break;
    case DISPLAY_INPROGRESS:
    {
        if(m_animFrameIndex <= m_width - 20) {
            LCDLibrary::drawLine(m_frameData,m_width,m_height,10,10,
                                 m_animFrameIndex + 10,10,2);
            LCDLibrary::drawLine(m_frameData,m_width,m_height,m_width - m_animFrameIndex - 10,m_height - 10,
                                 m_width - 10,m_height - 10,2);

        } else if(m_animFrameIndex <= m_width + m_height - 40){
            int index = m_animFrameIndex - (m_width - 20);
            LCDLibrary::drawLine(m_frameData,m_width,m_height,m_width - 10,10,
                                 m_width - 10,10 + index,2);
            LCDLibrary::drawLine(m_frameData,m_width,m_height,10,m_height - 10 - index,
                                 10,m_height - 10,2);
        }
        m_animFrameIndex ++;
        if(m_animFrameIndex > m_width + m_height - 40) {
            m_animFrameIndex = 0;
            m_displayState = DISPLAY_IDLE;
        }
    }
        break;
    case DISPLAY_DONE:
        break;
    }
}

void EmotionDisplay::displayAnimWakeupOpenEyes()
{
    DISPLAY_STATE currentState = m_displayState;
    switch (currentState) {
    case DISPLAY_IDLE:
    {
        m_animFrameIndex ++;
        if(m_animFrameIndex == 30) {
            m_animFrameIndex = 0;
            m_displayState = DISPLAY_DONE;
            LCDLibrary::clear(m_frameData,m_width,m_height);
        }
    }
        break;
    case DISPLAY_INIT:
    {
        LCDLibrary::clear(m_frameData,m_width,m_height);
        m_displayState = DISPLAY_INPROGRESS;
        m_animFrameIndex = 0;
    }
        break;
    case DISPLAY_INPROGRESS:
    {
        if(m_animFrameIndex < EYE_HEIGHT) { // closed eyes
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 10, m_height - 8 - m_animFrameIndex,
                                 EYE_WITH,m_animFrameIndex+1);
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 78, m_height - 8 - m_animFrameIndex,
                                 EYE_WITH,m_animFrameIndex+1);
        } else if(m_animFrameIndex < EYE_HEIGHT + 5) { // blink
            if(m_animFrameIndex == EYE_HEIGHT) {
                LCDLibrary::clear(m_frameData,m_width,m_height);
            }
            int index = m_animFrameIndex - EYE_HEIGHT;
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 10, m_height - 8,
                                 EYE_WITH, 2);
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 78, m_height - 8,
                                 EYE_WITH, 2);
        } else if(m_animFrameIndex < EYE_HEIGHT * 2 + 5) { // draw opened eyes
            if(m_animFrameIndex == EYE_HEIGHT + 5) {
                LCDLibrary::clear(m_frameData,m_width,m_height);
            }
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 10, m_height - 8 - EYE_HEIGHT,
                                 EYE_WITH,EYE_HEIGHT,1,true);
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 78, m_height - 8 - EYE_HEIGHT,
                                 EYE_WITH,EYE_HEIGHT,1,true);
        }
        m_animFrameIndex ++;
        if(m_animFrameIndex >= EYE_HEIGHT * 2 + 5) {
            m_animFrameIndex = 0;
            m_displayState = DISPLAY_IDLE;
        }
    }
        break;
    case DISPLAY_DONE:
        break;
    }
}

void EmotionDisplay::displayAnimWakeupLookLeft()
{
    DISPLAY_STATE currentState = m_displayState;
    switch (currentState) {
    case DISPLAY_IDLE:
    {
        m_animFrameIndex ++;
        if(m_animFrameIndex == 30) {
            m_animFrameIndex = 0;
            m_displayState = DISPLAY_DONE;
            LCDLibrary::clear(m_frameData,m_width,m_height);
        }
    }
        break;
    case DISPLAY_INIT:
    {
        LCDLibrary::clear(m_frameData,m_width,m_height);
        m_displayState = DISPLAY_INPROGRESS;
        m_animFrameIndex = 0;
    }
        break;
    case DISPLAY_INPROGRESS:
    {
        if(m_animFrameIndex < EYE_HEIGHT) { // closed eyes
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 20, m_height - 20 - EYE_HEIGHT,
                                 EYE_WITH, EYE_HEIGHT, 1 , true);
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 88, m_height - 20 - EYE_HEIGHT,
                                 EYE_WITH, EYE_HEIGHT, 1 , true);
        } else if(m_animFrameIndex < EYE_HEIGHT + 5) { // blink
            if(m_animFrameIndex == EYE_HEIGHT) {
                LCDLibrary::clear(m_frameData,m_width,m_height);
            }
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 20, m_height - 20,
                                 EYE_WITH, 2, 1 , true);
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 88, m_height - 20,
                                 EYE_WITH, 2, 1 , true);
        } else if(m_animFrameIndex < EYE_HEIGHT * 2 + 5) { // draw opened eyes
            if(m_animFrameIndex == EYE_HEIGHT + 5) {
                LCDLibrary::clear(m_frameData,m_width,m_height);
            }
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 14, m_height - 20 - EYE_HEIGHT,
                                 EYE_WITH, EYE_HEIGHT, 1 , true);
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 82, m_height - 20 - EYE_HEIGHT,
                                 EYE_WITH, EYE_HEIGHT, 1 , true);
        }
        m_animFrameIndex ++;
        if(m_animFrameIndex >= EYE_HEIGHT * 2 + 5) {
            m_animFrameIndex = 0;
            m_displayState = DISPLAY_IDLE;
        }
    }
        break;
    case DISPLAY_DONE:
        break;
    }
}

void EmotionDisplay::displayAnimWakeupLookRight()
{
    DISPLAY_STATE currentState = m_displayState;
    switch (currentState) {
    case DISPLAY_IDLE:
    {
        m_animFrameIndex ++;
        if(m_animFrameIndex == 30) {
            m_animFrameIndex = 0;
            m_displayState = DISPLAY_DONE;
            LCDLibrary::clear(m_frameData,m_width,m_height);
        }
    }
        break;
    case DISPLAY_INIT:
    {
        LCDLibrary::clear(m_frameData,m_width,m_height);
        m_displayState = DISPLAY_INPROGRESS;
        m_animFrameIndex = 0;
    }
        break;
    case DISPLAY_INPROGRESS:
    {
        if(m_animFrameIndex < EYE_HEIGHT) { // closed eyes
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 4, m_height - 8 - EYE_HEIGHT,
                                 EYE_WITH, EYE_HEIGHT, 1 , true);
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 64, m_height - 8 - EYE_HEIGHT,
                                 EYE_WITH, EYE_HEIGHT, 1 , true);
        } else if(m_animFrameIndex < EYE_HEIGHT + 5) { // blink
            if(m_animFrameIndex == EYE_HEIGHT) {
                LCDLibrary::clear(m_frameData,m_width,m_height);
            }
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 4, m_height - 8,
                                 EYE_WITH, 2, 1 , true);
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 64, m_height - 8,
                                 EYE_WITH, 2, 1 , true);
        } else if(m_animFrameIndex < EYE_HEIGHT * 2 + 5) { // draw opened eyes
            if(m_animFrameIndex == EYE_HEIGHT + 5) {
                LCDLibrary::clear(m_frameData,m_width,m_height);
            }
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 4, m_height - 8 - EYE_HEIGHT,
                                 EYE_WITH, EYE_HEIGHT, 1 , true);
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 64, m_height - 8 - EYE_HEIGHT,
                                 EYE_WITH, EYE_HEIGHT, 1 , true);
        }
        m_animFrameIndex ++;
        if(m_animFrameIndex >= EYE_HEIGHT * 2 + 5) {
            m_animFrameIndex = 0;
            m_displayState = DISPLAY_IDLE;
        }
    }
        break;
    case DISPLAY_DONE:
        break;
    }
}

void EmotionDisplay::displayAnimWakeupYawn()
{
    DISPLAY_STATE currentState = m_displayState;
    switch (currentState) {
    case DISPLAY_IDLE:
    {
        m_animFrameIndex ++;
        if(m_animFrameIndex == 30) {
            m_animFrameIndex = 0;
            m_displayState = DISPLAY_DONE;
            LCDLibrary::clear(m_frameData,m_width,m_height);
        }
    }
        break;
    case DISPLAY_INIT:
    {
        LCDLibrary::clear(m_frameData,m_width,m_height);
        m_displayState = DISPLAY_INPROGRESS;
        m_animFrameIndex = 0;
    }
        break;
    case DISPLAY_INPROGRESS:
    {
        if(m_animFrameIndex < EYE_HEIGHT) { // closed eyes
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 20, m_height - 20,
                                 EYE_WITH,m_animFrameIndex+1);
        } else if(m_animFrameIndex < EYE_HEIGHT + 5) { // blink
            int index = m_animFrameIndex - EYE_HEIGHT;
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 20, m_height - 20,
                                 EYE_WITH, 7 - index);
        } else if(m_animFrameIndex < EYE_HEIGHT * 2 + 5) { // draw opened eyes
            LCDLibrary::drawRect(m_frameData,m_width,m_height,
                                 20, m_height - 20,
                                 EYE_WITH,EYE_HEIGHT);
        }
        m_animFrameIndex ++;
        if(m_animFrameIndex >= EYE_HEIGHT * 2 + 5) {
            m_animFrameIndex = 0;
            m_displayState = DISPLAY_IDLE;
        }
    }
        break;
    case DISPLAY_DONE:
        break;
    }
}

void EmotionDisplay::displayAnimIdle()
{
    DISPLAY_STATE currentState = m_displayState;
    switch (currentState) {
    case DISPLAY_IDLE:
    {
         m_displayState = DISPLAY_DONE;
    }
        break;
    case DISPLAY_INIT:
    {
        LCDLibrary::clear(m_frameData,m_width,m_height);
        m_displayState = DISPLAY_INPROGRESS;
    }
        break;
    case DISPLAY_INPROGRESS:
    {
        m_displayState = DISPLAY_IDLE;
    }
        break;
    case DISPLAY_DONE:
        break;
    }
}

void EmotionDisplay::displayAnimHappy()
{
    DISPLAY_STATE currentState = m_displayState;
    switch (currentState) {
    case DISPLAY_IDLE:
    {
         m_displayState = DISPLAY_DONE;
    }
        break;
    case DISPLAY_INIT:
    {
        LCDLibrary::clear(m_frameData,m_width,m_height);
        m_displayState = DISPLAY_INPROGRESS;
    }
        break;
    case DISPLAY_INPROGRESS:
    {
        m_displayState = DISPLAY_IDLE;
    }
        break;
    case DISPLAY_DONE:
        break;
    }
}

void EmotionDisplay::displayAnimAngry()
{
    DISPLAY_STATE currentState = m_displayState;
    switch (currentState) {
    case DISPLAY_IDLE:
    {
         m_displayState = DISPLAY_DONE;
    }
        break;
    case DISPLAY_INIT:
    {
        LCDLibrary::clear(m_frameData,m_width,m_height);
        m_displayState = DISPLAY_INPROGRESS;
    }
        break;
    case DISPLAY_INPROGRESS:
    {
        m_displayState = DISPLAY_IDLE;
    }
        break;
    case DISPLAY_DONE:
        break;
    }
}

void EmotionDisplay::displayAnimTicled()
{
    DISPLAY_STATE currentState = m_displayState;
    switch (currentState) {
    case DISPLAY_IDLE:
    {
         m_displayState = DISPLAY_DONE;
    }
        break;
    case DISPLAY_INIT:
    {
        LCDLibrary::clear(m_frameData,m_width,m_height);
        m_displayState = DISPLAY_INPROGRESS;
    }
        break;
    case DISPLAY_INPROGRESS:
    {
        m_displayState = DISPLAY_IDLE;
    }
        break;
    case DISPLAY_DONE:
        break;
    }
}

void EmotionDisplay::displayAnimSupprised()
{
    DISPLAY_STATE currentState = m_displayState;
    switch (currentState) {
    case DISPLAY_IDLE:
    {
         m_displayState = DISPLAY_DONE;
    }
        break;
    case DISPLAY_INIT:
    {
        LCDLibrary::clear(m_frameData,m_width,m_height);
        m_displayState = DISPLAY_INPROGRESS;
    }
        break;
    case DISPLAY_INPROGRESS:
    {
        m_displayState = DISPLAY_IDLE;
    }
        break;
    case DISPLAY_DONE:
        break;
    }
}
