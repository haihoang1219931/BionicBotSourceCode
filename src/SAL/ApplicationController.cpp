#include "ApplicationController.h"
#include "Button.h"
#include "SmoothMotion.h"
#include "EmotionDisplay.h"
#include "AudioPlayer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define ROBOT_VERSION "1.0.0"
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGH 64
ApplicationController::ApplicationController()
{
    for(int i=0; i< (int)MAX_TOUCH; i++) {
        m_touchList[i] = new Button(this);
    }
    for(int i=0; i< (int)MAX_MOTOR; i++) {
        m_motionList[i] = new SmoothMotion((MOTOR)i, this);
    }
    m_emotionDisplay = new EmotionDisplay(this, DISPLAY_WIDTH, DISPLAY_HEIGH);
    m_audioPlayer = new AudioPlayer(this);
    m_currentEmotion = EMOTION_START_UP;
    m_emotionState = EMOTION_TASK_INIT;
}

ApplicationController::~ApplicationController() {

}

void ApplicationController::loop() {
    m_appTimer++;
#ifdef DEBUG_APP
    this->printf("APP Timer[%d] m_machineState[%d]\r\n",m_appTimer,m_machineState);
#endif
    switch (m_currentEmotion) {
    case EMOTION_START_UP: {
        if(emotionStartupTask() == EMOTION_TASK_DONE) {
            setEmotion(EMOTION_IDLE);
        }
    }
        break;
    case EMOTION_IDLE: {

    }
        break;
    case EMOTION_HAPPY: {
        if(emotionHappyTask() == EMOTION_TASK_DONE) {
            setEmotion(EMOTION_IDLE);
        }
    }
        break;
    case EMOTION_ANGRY: {
        if(emotionAngryTask() == EMOTION_TASK_DONE) {
            setEmotion(EMOTION_IDLE);
        }
    }
        break;
    case EMOTION_TICKLED: {
        if(emotionTickledTask() == EMOTION_TASK_DONE) {
            setEmotion(EMOTION_IDLE);
        }
    }
        break;
    case EMOTION_SUPPRISED: {
        if(emotionSupprisedTask() == EMOTION_TASK_DONE) {
            setEmotion(EMOTION_IDLE);
        }
    }
        break;
    }
}

EMOTION_STATE ApplicationController::emotionStartupTask() {
    switch (m_emotionState) {
    case EMOTION_TASK_INIT: {
        m_emotionState = EMOTION_TASK_PENDING;
        m_emotionDisplay->initEmotion(EMOTION_START_UP);
    }
        break;
    case EMOTION_TASK_PENDING: {
        bool allTaskDone = false;
        allTaskDone =
        m_emotionDisplay->currentState() == DISPLAY_DONE &&
        m_motionList[MOTOR_HEAD]->currentState() == MOTION_DONE &&
        m_motionList[MOTOR_ARM_LEFT]->currentState() == MOTION_DONE &&
        m_motionList[MOTOR_ARM_RIGHT]->currentState() == MOTION_DONE &&
        m_motionList[MOTOR_BODY]->currentState() == MOTION_DONE;
        if(allTaskDone) {
            m_emotionState = EMOTION_TASK_DONE;
        }
    }
        break;
    case EMOTION_TASK_DONE: {
    }
        break;
    }

    return m_emotionState;
}

EMOTION_STATE ApplicationController::emotionHappyTask() {
    switch (m_emotionState) {
    case EMOTION_TASK_INIT: {
        m_emotionState = EMOTION_TASK_PENDING;
    }
        break;
    case EMOTION_TASK_PENDING: {
        bool allTaskDone = false;
        allTaskDone =
        m_emotionDisplay->currentState() == DISPLAY_DONE &&
        m_motionList[MOTOR_HEAD]->currentState() == MOTION_DONE &&
        m_motionList[MOTOR_ARM_LEFT]->currentState() == MOTION_DONE &&
        m_motionList[MOTOR_ARM_RIGHT]->currentState() == MOTION_DONE &&
        m_motionList[MOTOR_BODY]->currentState() == MOTION_DONE;
        if(allTaskDone) {
            m_emotionState = EMOTION_TASK_DONE;
        }
    }
        break;
    case EMOTION_TASK_DONE: {
    }
        break;
    }

    return m_emotionState;
}

EMOTION_STATE ApplicationController::emotionAngryTask() {
    switch (m_emotionState) {
    case EMOTION_TASK_INIT: {
        m_emotionState = EMOTION_TASK_PENDING;
    }
        break;
    case EMOTION_TASK_PENDING: {
        bool allTaskDone = false;
        allTaskDone =
        m_emotionDisplay->currentState() == DISPLAY_DONE &&
        m_motionList[MOTOR_HEAD]->currentState() == MOTION_DONE &&
        m_motionList[MOTOR_ARM_LEFT]->currentState() == MOTION_DONE &&
        m_motionList[MOTOR_ARM_RIGHT]->currentState() == MOTION_DONE &&
        m_motionList[MOTOR_BODY]->currentState() == MOTION_DONE;
        if(allTaskDone) {
            m_emotionState = EMOTION_TASK_DONE;
        }
    }
        break;
    case EMOTION_TASK_DONE: {
    }
        break;
    }

    return m_emotionState;
}

EMOTION_STATE ApplicationController::emotionTickledTask() {
    switch (m_emotionState) {
    case EMOTION_TASK_INIT: {
        m_emotionState = EMOTION_TASK_PENDING;
    }
        break;
    case EMOTION_TASK_PENDING: {
        bool allTaskDone = false;
        allTaskDone =
        m_emotionDisplay->currentState() == DISPLAY_DONE &&
        m_motionList[MOTOR_HEAD]->currentState() == MOTION_DONE &&
        m_motionList[MOTOR_ARM_LEFT]->currentState() == MOTION_DONE &&
        m_motionList[MOTOR_ARM_RIGHT]->currentState() == MOTION_DONE &&
        m_motionList[MOTOR_BODY]->currentState() == MOTION_DONE;
        if(allTaskDone) {
            m_emotionState = EMOTION_TASK_DONE;
        }
    }
        break;
    case EMOTION_TASK_DONE: {
    }
        break;
    }

    return m_emotionState;
}

EMOTION_STATE ApplicationController::emotionSupprisedTask() {
    switch (m_emotionState) {
    case EMOTION_TASK_INIT: {
        m_emotionState = EMOTION_TASK_PENDING;
    }
        break;
    case EMOTION_TASK_PENDING: {
        bool allTaskDone = false;
        allTaskDone =
        m_emotionDisplay->currentState() == DISPLAY_DONE &&
        m_motionList[MOTOR_HEAD]->currentState() == MOTION_DONE &&
        m_motionList[MOTOR_ARM_LEFT]->currentState() == MOTION_DONE &&
        m_motionList[MOTOR_ARM_RIGHT]->currentState() == MOTION_DONE &&
        m_motionList[MOTOR_BODY]->currentState() == MOTION_DONE;
        if(allTaskDone) {
            m_emotionState = EMOTION_TASK_DONE;
        }
    }
        break;
    case EMOTION_TASK_DONE: {
    }
        break;
    }

    return m_emotionState;
}

EMOTION ApplicationController::currentEmotion() {
    return m_currentEmotion;
}

void ApplicationController::setEmotion(EMOTION emotion) {
    if(m_currentEmotion != emotion) {
        m_currentEmotion = emotion;
        m_emotionState = EMOTION_TASK_INIT;
#ifdef DEBUG_COMMAND        
        this->printf("APP STATE: %d\r\n",m_state);
#endif
    }
}

int ApplicationController::getScreenWidth()
{
    return m_emotionDisplay->getScreenWidth();
}

int ApplicationController::getScreenHeight()
{
    return m_emotionDisplay->getScreenHeight();
}

unsigned char* ApplicationController::getScreenData()
{
    return m_emotionDisplay->getScreenData();
}

float ApplicationController::currentAngle(MOTOR motorID) {
    return m_motionList[motorID]->currentAngle();
}

void ApplicationController::executeMotionLoop(MOTOR motorID) {
    m_motionList[motorID]->motionMainFuntion();
}

void ApplicationController::executeAudioLoop() {
    m_audioPlayer->audioPlayerMainFuntion();
}

void ApplicationController::executeOledLoop() {
    m_emotionDisplay->displayMainFuntion();
}

void ApplicationController::executeInputLoop() {

}
