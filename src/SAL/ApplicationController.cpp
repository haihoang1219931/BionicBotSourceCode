#include "ApplicationController.h"
#include "Button.h"
#include "SmoothMotion.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define ROBOT_VERSION "1.0.0"
ApplicationController::ApplicationController()
{
    for(int i=0; i< MAX_TOUCH; i++) {
        m_touchList[i] = new Button(this);
    }
    for(int i=0; i< MAX_MOTOR; i++) {
        m_motionList[i] = new SmoothMotion(i, this);
    }
    m_state = EMOTION_IDLE;
}

ApplicationController::~ApplicationController() {

}

void ApplicationController::loop() {
    m_appTimer++;
#ifdef DEBUG_APP
    this->printf("APP Timer[%d] m_machineState[%d]\r\n",m_appTimer,m_machineState);
#endif
}

EMOTION_STATE ApplicationController::state() {
    return m_state;
}

void ApplicationController::setState(EMOTION_STATE state) {
    if(state != m_state) {
        m_state = state;
#ifdef DEBUG_COMMAND        
        this->printf("APP STATE: %d\r\n",m_state);
#endif
    }
}

void ApplicationController::executeMotionLoop(MOTOR motorID) {

}

void ApplicationController::executeAudioLoop() {

}

void ApplicationController::executeOledLoop() {

}

void ApplicationController::executeInputLoop() {

}
