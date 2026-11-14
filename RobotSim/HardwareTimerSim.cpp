#include "HardwareTimerSim.h"
#include "ApplicationSim.h"
#include "src/SAL/StdTypes.h"

HardwareTimerSim::HardwareTimerSim(QObject *parent) : QObject(parent)
{
    m_timerMotion = new QTimer(this);
    connect(m_timerMotion, &QTimer::timeout, this, &HardwareTimerSim::taskLoopMotion);
    m_timerInput = new QTimer(this);
    connect(m_timerInput, &QTimer::timeout, this, &HardwareTimerSim::taskLoopInput);
}

void HardwareTimerSim::setApplication(ApplicationSim* app)
{
    m_app = app;
}

void HardwareTimerSim::setIntervalMotion(int millis)
{
    m_timerMotion->setInterval(millis);
}

void HardwareTimerSim::setIntervalInput(int millis)
{
    m_timerInput->setInterval(millis);
}

void HardwareTimerSim::enableTaskMotion(bool enable)
{
    if (!enable) {
        m_timerMotion->stop();
    } else {
        m_timerMotion->start();
    }
}

void HardwareTimerSim::enableTaskInput(bool enable)
{
    if (!enable) {
        m_timerInput->stop();
    } else {
        m_timerInput->start();
    }
}

void HardwareTimerSim::taskLoopMotion()
{
    m_app->executeMotionLoop(MOTOR_HEAD);
    m_app->executeMotionLoop(MOTOR_ARM_LEFT);
    m_app->executeMotionLoop(MOTOR_ARM_RIGHT);
    m_app->executeMotionLoop(MOTOR_BODY);
    m_app->executeAudioLoop();
    m_app->executeOledLoop();
    Q_EMIT faceLoopUpdated();
}

void HardwareTimerSim::taskLoopInput()
{
    m_app->executeInputLoop();
}
