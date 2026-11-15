#include "MainProcess.h"
#include "ApplicationSim.h"
#include "HardwareTimerSim.h"
#include "VideoDisplay/VideoRender.h"
#include "../src/SAL/ApplicationController.h"
#include "../src/SAL/StdTypes.h"
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

void MainProcess::changeEmotion(int emotion)
{
    m_application->setEmotion((EMOTION)emotion);
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
    for(int i=0; i< (int)MAX_MOTOR; i++)
    {
        m_listAngle[i] = m_application->currentAngle((MOTOR)(i));
        printf("m_listAngle[%d] %f\r\n",
               i,m_listAngle[i].toFloat());
    }

    Q_EMIT listAngleChanged(m_listAngle);
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
        int width = m_application->getScreenWidth();
        int height = m_application->getScreenHeight();
        unsigned char* binaryFrame = m_application->getScreenData();
#ifdef DEBUG
        printf("BinaryFrame:\r\n");
        for(int row = 0; row < height; row++) {
            for(int col = 0; col < width/8; col ++) {
                printf(BYTE_TO_BINARY_PATTERN "",BYTE_TO_BINARY (binaryFrame[row*width/8+col]));
            }
            printf("\r\n");
        }
        printf("\r\n");
        printf("RenderFrame:\r\n");
#endif
        int sRow = 8; int sCol = 8;
        for(int row = 0; row < height; row++) {
            for(int col = 0; col < width/8; col ++) {
                for(int bit = 0; bit <8; bit++){
                    // pixel value from
                    // (row * sRow, (col*8+bit)*sCol)
                    // to
                    // ((row+1) * sRow-1, (col*8+bit)*sCol-1)
                    unsigned char pixelValue = (binaryFrame[row*width/8+col] & (0x01 << (7-bit))) == 0 ? 0 : 50;

                    for(int subRow = 0; subRow < sRow-1; subRow++) {
                        for(int subCol = 0; subCol < sCol-1; subCol ++) {
                            m_renderData[(row * sRow + subRow)* width * sCol + ((col*8 + bit)*sCol + subCol)] = pixelValue;
                        }
                    }

                }

            }
#ifdef DEBUG
            printf("\r\n");
#endif
        }
        m_render->handleNewFrame(m_renderData, width*sRow, height*sCol);
    }
    syncRobot();
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

void MainProcess::setListAngle(int motorID, float angle)
{
    m_listAngle[motorID] = angle;
}
