#include "SmoothMotion.h"
#include "ApplicationController.h"
#if defined(DEBUG_COMMAND)
#include "../ApplicationArduino.h"
extern ApplicationArduino app;
#endif
SmoothMotion::SmoothMotion(MOTOR id, ApplicationController* app):
    m_app(app),
    m_motionState(MOTION_INIT),
    m_id(id)
{

}

void SmoothMotion::initMotion()
{
    m_currentParam.currentAngle = MOTION_INIT_VALUE;
    m_currentParam.startAngle = MOTION_INIT_VALUE;
    m_currentParam.speed = MOTION_INIT_VALUE;
    m_currentParam.targetAngle = MOTION_INIT_VALUE;
    m_currentParam.progress = MOTION_INIT_VALUE;
}

void SmoothMotion::setEmotionState(float targetAngle,
                                   float speed)
{
  m_targetParam.currentAngle = MOTION_INIT_VALUE;
  m_targetParam.targetAngle = targetAngle;
  m_targetParam.speed = speed;
  m_motionState = MOTION_INIT;
}

MOTION_STATE SmoothMotion::currentState()
{
    return m_motionState;
}

MOTION_STATE SmoothMotion::motionMainFuntion()
{
    MOTION_STATE currentState = m_motionState;
    switch (currentState) {
    case MOTION_IDLE:
    {
        m_app->enableMotor(m_id, false);
        m_motionState = MOTION_DONE;
    }
        break;
    case MOTION_INIT:
    {
        m_app->enableMotor(m_id, true);
        m_motionState = MOTION_INPROGRESS;
        m_currentParam.targetAngle = m_targetParam.targetAngle;
        m_currentParam.speed = m_currentParam.targetAngle - m_currentParam.currentAngle;
    }
        break;
    case MOTION_INPROGRESS:
    {
        float nextAngle = m_currentParam.currentAngle + m_currentParam.speed;
        if(nextAngle * m_currentParam.speed >
                m_currentParam.targetAngle * m_currentParam.speed) {
            m_motionState = MOTION_IDLE;
        }
    }
        break;
    case MOTION_DONE:
        break;
    }
    return currentState;
}

float SmoothMotion::currentAngle()
{
    return m_currentParam.currentAngle;
}
