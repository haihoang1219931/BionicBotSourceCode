#include "SmoothMotion.h"
#include "ApplicationController.h"
#include <math.h>
#ifndef abs
#define abs(x) ((x) > 0 ? (x) : -(x))
#endif
SmoothMotion::SmoothMotion(MOTOR id, ApplicationController* app):
    m_app(app),
    m_motionState(MOTION_INIT),
    m_id(id)
{
    initMotion();
}

void SmoothMotion::initMotion()
{
    m_currentParam.currentAngle = MOTION_INIT_VALUE;
    m_currentParam.startAngle = MOTION_INIT_VALUE;
    m_currentParam.speed = MOTION_INIT_VALUE;
    m_currentParam.targetAngle = MOTION_INIT_VALUE;
    m_currentParam.progress = MOTION_INIT_VALUE;
}

void SmoothMotion::setTarget(int targetAngle,
                                   int speed)
{
  m_targetParam.targetAngle = targetAngle;
  m_targetParam.speed = targetAngle > m_currentParam.currentAngle ? abs(speed) : -abs(speed);
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
        m_currentParam.speed = m_targetParam.speed;
    }
        break;
    case MOTION_INPROGRESS:
    {
        int nextAngle = m_currentParam.currentAngle + m_currentParam.speed;
        if(nextAngle * m_currentParam.speed >
                m_currentParam.targetAngle * m_currentParam.speed) {
            m_motionState = MOTION_IDLE;
        } else {
            m_currentParam.currentAngle = nextAngle;
            m_app->setMotorAngle(m_id,nextAngle);
#ifdef DEBUG_MOTION
            m_app->printf("Motion[%d] c[%d]/t[%d] s[%d]\r\n",
                          m_id,m_currentParam.currentAngle,m_currentParam.targetAngle,m_currentParam.speed);
#endif
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

void SmoothMotion::setCurrentAngle(int currentAngle)
{
    m_currentParam.currentAngle = currentAngle;
}
