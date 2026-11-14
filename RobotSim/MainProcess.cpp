#include "MainProcess.h"
#include "ApplicationSim.h"
#include "HardwareTimerSim.h"
#include "VideoDisplay/VideoRender.h"
#include "../src/SAL/SmoothMotion.h"
#include <stdio.h>
MainProcess::MainProcess(QObject *parent) :
    QObject(parent)
{
    m_application = new ApplicationSim(this);
    m_hardwareTimer = new HardwareTimerSim();
    m_hardwareTimer->setApplication(m_application);
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &MainProcess::taskLoop);
    connect(m_hardwareTimer,&HardwareTimerSim::faceLoopUpdated,
            this,& MainProcess::updateScreen);
    changeSleepTime(30);
    changeTimerPeriodMotion(30);
    changeTimerPeriodInput(30);
    for(int i=0; i< MAX_MOTOR; i++)
    {
        m_listAngle.append(0);
    }
    syncRobot();
}

MainProcess::~MainProcess()
{
    stopService();
}

void MainProcess::enableHardwareTimer(bool enable)
{
    m_hardwareTimer->enableTaskMotion(enable);
}

void MainProcess::pause(bool pause){
    if(pause == true){
        m_timer->stop();
    }else{
        m_timer->start();
    }
    m_hardwareTimer->enableTaskMotion(!pause);
}

void MainProcess::syncRobot()
{
    float listArmLength[MAX_MOTOR];

    float listAngle[MAX_MOTOR];
    int numMotor = MAX_MOTOR;
    printf("numMotor[%d]\r\n",numMotor);
    for(int i=0; i< numMotor; i++)
    {
        m_listAngle[i] = listAngle[i];
        printf("m_listAngle[%d] %f\r\n",
               i,m_listAngle[i].toFloat());
    }

    Q_EMIT listAngleChanged();
}

void MainProcess::taskLoop() {
    m_application->loop();
}
void MainProcess::startService() {
    printf("Start\r\n");
    m_timer->start();
    m_hardwareTimer->enableTaskInput(true);
    m_hardwareTimer->enableTaskMotion(true);
}

void MainProcess::stopService() {
    printf("Stop\r\n");
    m_timer->stop();
    m_hardwareTimer->enableTaskMotion(false);
    m_hardwareTimer->enableTaskInput(false);
}
void MainProcess::setRender(VideoRender* render)
{
    m_render = render;
}
void MainProcess::updateScreen() {
    if(m_render != nullptr)
    {
        int width = 128;
        int height = 64;
        memset(m_renderData,0,width*height);
        m_renderData[12*width+15] = 255;
        m_renderData[12*width+16] = 255;
        m_renderData[13*width+15] = 255;
        m_renderData[13*width+16] = 255;
        m_renderData[12*width+114] = 255;
        m_renderData[12*width+115] = 255;
        m_renderData[13*width+114] = 255;
        m_renderData[13*width+115] = 255;
        m_render->handleNewFrame(m_renderData, width, height);
    }
}
void MainProcess::changeSleepTime(int sleepTime)
{
    m_timer->setInterval(sleepTime);

}
void MainProcess::changeTimerPeriodMotion(int sleepTime)
{
    m_hardwareTimer->setIntervalMotion(sleepTime);
}

void MainProcess::changeTimerPeriodInput(int sleepTime)
{
    m_hardwareTimer->setIntervalInput(sleepTime);
}

QVariantList MainProcess::listAngle()
{
    return m_listAngle;
}

void MainProcess::setListAngle(int motorID, float angle)
{
    m_listAngle[motorID] = angle;
}
