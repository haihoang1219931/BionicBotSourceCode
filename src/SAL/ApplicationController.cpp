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
            this->printf("Starup done\r\n");
            setEmotion(EMOTION_WAKEUP_OPEN_EYES);
        }
    }
        break;
    case EMOTION_WAKEUP_OPEN_EYES: {
        if(emotionWakeupOpenEyesTask() == EMOTION_TASK_DONE) {
            this->printf("Wakeup open eyes done\r\n");
            setEmotion(EMOTION_WAKEUP_LOOK_LEFT);
        }
    }
        break;
    case EMOTION_WAKEUP_LOOK_LEFT: {
        if(emotionWakeupLookLeftTask() == EMOTION_TASK_DONE) {
            this->printf("Wakeup look left done\r\n");
            setEmotion(EMOTION_WAKEUP_LOOK_RIGHT);
        }
    }
        break;
    case EMOTION_WAKEUP_LOOK_RIGHT: {
        if(emotionWakeupLookRightTask() == EMOTION_TASK_DONE) {
            this->printf("Wakeup look right done\r\n");
            setEmotion(EMOTION_WAKEUP_YAWN);
        }
    }
        break;
    case EMOTION_WAKEUP_YAWN: {
        if(emotionWakeupYawnTask() == EMOTION_TASK_DONE) {
            this->printf("Wakeup yawn done\r\n");
            setEmotion(EMOTION_IDLE);
        }
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
    case EMOTION_IDLE: {

    }
        break;
    }
}

EMOTION_STATE ApplicationController::emotionStartupTask() {
    switch (m_emotionState) {
    case EMOTION_TASK_INIT: {
        m_emotionState = EMOTION_TASK_PENDING;
        m_emotionDisplay->initEmotion(EMOTION_START_UP);
        m_motionList[MOTOR_HEAD]->setTarget(0,2);
        m_motionList[MOTOR_ARM_LEFT]->setTarget(0,2);
        m_motionList[MOTOR_ARM_RIGHT]->setTarget(0,2);
        m_motionList[MOTOR_BODY]->setTarget(0,2);
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
EMOTION_STATE ApplicationController::emotionWakeupOpenEyesTask() {
    switch (m_emotionState) {
    case EMOTION_TASK_INIT: {
        m_emotionState = EMOTION_TASK_PENDING;
        m_emotionDisplay->initEmotion(EMOTION_WAKEUP_OPEN_EYES);
        m_motionList[MOTOR_HEAD]->setTarget(0,2);
        m_motionList[MOTOR_ARM_LEFT]->setTarget(0,2);
        m_motionList[MOTOR_ARM_RIGHT]->setTarget(0,2);
        m_motionList[MOTOR_BODY]->setTarget(0,2);
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

EMOTION_STATE ApplicationController::emotionWakeupLookLeftTask() {
    switch (m_emotionState) {
    case EMOTION_TASK_INIT: {
        m_emotionState = EMOTION_TASK_PENDING;
        m_emotionDisplay->initEmotion(EMOTION_WAKEUP_LOOK_LEFT);
        m_motionList[MOTOR_HEAD]->setTarget(10,2);
        m_motionList[MOTOR_ARM_LEFT]->setTarget(30,2);
        m_motionList[MOTOR_ARM_RIGHT]->setTarget(-30,2);
        m_motionList[MOTOR_BODY]->setTarget(10,2);
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

EMOTION_STATE ApplicationController::emotionWakeupLookRightTask() {
    switch (m_emotionState) {
    case EMOTION_TASK_INIT: {
        m_emotionState = EMOTION_TASK_PENDING;
        m_emotionDisplay->initEmotion(EMOTION_WAKEUP_LOOK_RIGHT);
        m_motionList[MOTOR_HEAD]->setTarget(-10,2);
        m_motionList[MOTOR_ARM_LEFT]->setTarget(-30,2);
        m_motionList[MOTOR_ARM_RIGHT]->setTarget(30,2);
        m_motionList[MOTOR_BODY]->setTarget(-10,2);
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

EMOTION_STATE ApplicationController::emotionWakeupYawnTask() {
    switch (m_emotionState) {
    case EMOTION_TASK_INIT: {
        m_emotionState = EMOTION_TASK_PENDING;
        m_emotionDisplay->initEmotion(EMOTION_WAKEUP_YAWN);
        m_motionList[MOTOR_HEAD]->setTarget(0,2);
        m_motionList[MOTOR_ARM_LEFT]->setTarget(90,2);
        m_motionList[MOTOR_ARM_RIGHT]->setTarget(90,2);
        m_motionList[MOTOR_BODY]->setTarget(0,2);
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
EMOTION_STATE ApplicationController::emotionIdleTask() {
    switch (m_emotionState) {
    case EMOTION_TASK_INIT: {
        m_emotionState = EMOTION_TASK_PENDING;
        m_emotionDisplay->initEmotion(EMOTION_IDLE);
        m_motionList[MOTOR_HEAD]->setTarget(0,2);
        m_motionList[MOTOR_ARM_LEFT]->setTarget(0,2);
        m_motionList[MOTOR_ARM_RIGHT]->setTarget(0,2);
        m_motionList[MOTOR_BODY]->setTarget(0,2);
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
