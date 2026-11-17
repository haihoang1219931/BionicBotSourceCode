#include "EmotionDisplay.h"
#include "LCDLibrary.h"

#define EYE_WITH 40
#define EYE_HEIGHT 40
#define EYE_RADIUS 6
EmotionDisplay::EmotionDisplay(ApplicationController* app, int width, int height):
    m_width(width),
    m_height(height),
    m_app(app)
{
    m_lcd = new LCDLibrary(m_frameData, 128, 64);
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
            m_lcd->clearBuffer();
        }
    }
        break;
    case DISPLAY_INIT:
    {
        m_lcd->clearBuffer();
        m_displayState = DISPLAY_INPROGRESS;
        m_animFrameIndex = 0;
    }
        break;
    case DISPLAY_INPROGRESS:
    {
        if(m_animFrameIndex <= m_width - 20) {
            m_lcd->drawLine(10,10,
                                 m_animFrameIndex + 10,10,2);
            m_lcd->drawLine(m_width - m_animFrameIndex - 10,m_height - 10,
                                 m_width - 10,m_height - 10,2);

        } else if(m_animFrameIndex <= m_width + m_height - 40){
            int index = m_animFrameIndex - (m_width - 20);
            m_lcd->drawLine(m_width - 10,10,
                                 m_width - 10,10 + index,2);
            m_lcd->drawLine(10,m_height - 10 - index,
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
            m_lcd->clearBuffer();
        }
    }
        break;
    case DISPLAY_INIT:
    {
        m_lcd->clearBuffer();
        m_displayState = DISPLAY_INPROGRESS;
        m_animFrameIndex = 0;
    }
        break;
    case DISPLAY_INPROGRESS:
    {
        if(m_animFrameIndex < EYE_HEIGHT) { // closed eyes
            m_lcd->drawRBox(10, m_height - 12 - m_animFrameIndex/2,
                                 EYE_WITH,m_animFrameIndex+1,EYE_RADIUS);
            m_lcd->drawRBox(78, m_height - 12 - m_animFrameIndex/2,
                                 EYE_WITH,m_animFrameIndex+1,EYE_RADIUS);
        } else if(m_animFrameIndex < EYE_HEIGHT + 5) { // blink
            if(m_animFrameIndex == EYE_HEIGHT) {
                m_lcd->clearBuffer();
            }
            int index = m_animFrameIndex - EYE_HEIGHT;
            m_lcd->drawLine(10, m_height - 12,
                                 10+EYE_WITH, m_height - 12, 2);
            m_lcd->drawLine(78, m_height - 12,
                                 78+EYE_WITH, m_height - 12, 2);
        } else if(m_animFrameIndex < EYE_HEIGHT * 2 + 5) { // draw opened eyes
            if(m_animFrameIndex == EYE_HEIGHT + 5) {
                m_lcd->clearBuffer();
            }
            m_lcd->drawRBox(
                                 10, m_height - 12 - EYE_HEIGHT,
                                 EYE_WITH,EYE_HEIGHT,EYE_RADIUS);
            m_lcd->drawRBox(
                                 78, m_height - 12 - EYE_HEIGHT,
                                 EYE_WITH,EYE_HEIGHT,EYE_RADIUS);
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
            m_lcd->clearBuffer();
        }
    }
        break;
    case DISPLAY_INIT:
    {
        m_lcd->clearBuffer();
        m_displayState = DISPLAY_INPROGRESS;
        m_animFrameIndex = 0;
    }
        break;
    case DISPLAY_INPROGRESS:
    {
        if(m_animFrameIndex < EYE_HEIGHT) { // closed eyes
            m_lcd->drawRBox(20, m_height - 12 - EYE_HEIGHT,
                                 EYE_WITH, EYE_HEIGHT,EYE_RADIUS);
            m_lcd->drawRBox(88, m_height - 12 - EYE_HEIGHT,
                                 EYE_WITH, EYE_HEIGHT,EYE_RADIUS);
        } else if(m_animFrameIndex < EYE_HEIGHT + 5) { // blink
            if(m_animFrameIndex == EYE_HEIGHT) {
                m_lcd->clearBuffer();
            }
            m_lcd->drawLine(20, m_height - 12,
                                 20+EYE_WITH, m_height - 12, 2);
            m_lcd->drawLine(88, m_height - 12,
                                 88+EYE_WITH, m_height - 12, 2);
        } else if(m_animFrameIndex < EYE_HEIGHT * 2 + 5) { // draw opened eyes
            if(m_animFrameIndex == EYE_HEIGHT + 5) {
                m_lcd->clearBuffer();
            }
            m_lcd->drawRBox(14, m_height - 12 - EYE_HEIGHT,
                                 EYE_WITH, EYE_HEIGHT,EYE_RADIUS);
            m_lcd->drawRBox(82, m_height - 12 - EYE_HEIGHT,
                                 EYE_WITH, EYE_HEIGHT,EYE_RADIUS);
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
            m_lcd->clearBuffer();
        }
    }
        break;
    case DISPLAY_INIT:
    {
        m_lcd->clearBuffer();
        m_displayState = DISPLAY_INPROGRESS;
        m_animFrameIndex = 0;
    }
        break;
    case DISPLAY_INPROGRESS:
    {
        if(m_animFrameIndex < EYE_HEIGHT) { // closed eyes
            m_lcd->drawRBox(4, m_height - 12 - EYE_HEIGHT,
                                 EYE_WITH, EYE_HEIGHT,EYE_RADIUS);
            m_lcd->drawRBox(64, m_height - 12 - EYE_HEIGHT,
                                 EYE_WITH, EYE_HEIGHT,EYE_RADIUS);
        } else if(m_animFrameIndex < EYE_HEIGHT + 5) { // blink
            if(m_animFrameIndex == EYE_HEIGHT) {
                m_lcd->clearBuffer();
            }
            m_lcd->drawLine(4, m_height - 12,
                                 4+EYE_WITH, m_height - 12, 2);
            m_lcd->drawLine(64, m_height - 12,
                                 64+EYE_WITH, m_height - 12, 2);
        } else if(m_animFrameIndex < EYE_HEIGHT * 2 + 5) { // draw opened eyes
            if(m_animFrameIndex == EYE_HEIGHT + 5) {
                m_lcd->clearBuffer();
            }
            m_lcd->drawRBox(4, m_height - 12 - EYE_HEIGHT,
                                 EYE_WITH, EYE_HEIGHT,EYE_RADIUS);
            m_lcd->drawRBox(64, m_height - 12 - EYE_HEIGHT,
                                 EYE_WITH, EYE_HEIGHT,EYE_RADIUS);
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
            m_lcd->clearBuffer();
        }
    }
        break;
    case DISPLAY_INIT:
    {
        m_lcd->clearBuffer();
        m_displayState = DISPLAY_INPROGRESS;
        m_animFrameIndex = 0;
    }
        break;
    case DISPLAY_INPROGRESS:
    {
        if(m_animFrameIndex < EYE_HEIGHT*2) { // closed eyes
            int shakeX = rand()%3;
            int shakeY = rand()%3;
            m_lcd->drawRBox(14 + shakeX, m_height - 12 - EYE_HEIGHT + shakeY,
                                 EYE_WITH, EYE_HEIGHT/2,EYE_RADIUS);
            m_lcd->drawRBox(74 + shakeX, m_height - 12 - EYE_HEIGHT + shakeY,
                                 EYE_WITH, EYE_HEIGHT/2,EYE_RADIUS);
        }
        m_animFrameIndex ++;
        if(m_animFrameIndex >= EYE_HEIGHT * 2) {
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
        m_lcd->clearBuffer();
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
        m_lcd->clearBuffer();
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
        m_lcd->clearBuffer();
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
        m_lcd->clearBuffer();
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
        m_lcd->clearBuffer();
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
