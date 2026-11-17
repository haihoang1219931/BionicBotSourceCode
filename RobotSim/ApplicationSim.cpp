#include "ApplicationSim.h"
#include "MainProcess.h"
#include "../src/SAL/SmoothMotion.h"
#include <stdio.h>
#include <stdarg.h>
#ifdef __linux__
#include <time.h>
#include <string.h>
#elif _WIN32
#include <time.h>
#include <windows.h>
#else
#endif
ApplicationSim::ApplicationSim(MainProcess* mainProcess):
    m_mainProcess(mainProcess)
{
    memset(m_command,0x00U, sizeof(m_command));
    initRobot();
    m_motionList[MOTOR_HEAD]->setCurrentAngle(30);
    m_motionList[MOTOR_ARM_LEFT]->setCurrentAngle(30);
    m_motionList[MOTOR_ARM_RIGHT]->setCurrentAngle(30);
    m_motionList[MOTOR_BODY]->setCurrentAngle(30);
}

ApplicationSim::~ApplicationSim()
{

}

#define FREQUENCY_TIMER1 1250.0f
void ApplicationSim::initRobot()
{

}


int ApplicationSim::printf(const char *fmt, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, fmt);
    int rc = vsprintf(buffer, fmt, args);
    va_end(args);
    ::printf("%s",buffer);
    fflush(stdout);
    return rc;
}

void ApplicationSim::msleep(int millis)
{
#ifdef __linux__
    //linux code goes here
    struct timespec ts = { millis / 1000, (millis % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
#elif _WIN32
    // windows code goes here
    Sleep(millis);
#else
#endif
}

long ApplicationSim::getSystemTime()
{
#ifdef USE_HARD_TIMER
#ifdef __linux__
    struct timeval curTime;
    gettimeofday(&curTime, NULL);
    return (curTime.tv_usec + curTime.tv_sec*1000000);
#elif _WIN32
    struct timeb curTime;
    ftime(&curTime);
    return (long)(1000*curTime.time + curTime.millitm);
#else
    return 0;
#endif
#else
    return m_appTimer;
#endif
}

void ApplicationSim::enableHardwareTimer(bool enable)
{
    m_mainProcess->enableHardwareTimer(enable);
}

void ApplicationSim::enableMotor(MOTOR motorID, bool enable)
{

}

void ApplicationSim::setMotorAngle(MOTOR motorID, int angle)
{
    Q_UNUSED(motorID);
    Q_UNUSED(angle);
}
