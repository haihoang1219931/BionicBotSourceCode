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
