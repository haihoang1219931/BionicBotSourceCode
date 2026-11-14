#ifndef MAINPROCESS_H
#define MAINPROCESS_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QMutex>
#include <QWaitCondition>
#include <QList>

class HardwareTimerSim;
class ApplicationSim;
class VideoRender;
class MainProcess : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList listAngle READ listAngle NOTIFY listAngleChanged)
public:
    explicit MainProcess(QObject *parent = nullptr);
    ~MainProcess();

    QVariantList listAngle();
    void syncRobot();

public Q_SLOTS:
    void setListAngle(int motorID, float angle);

Q_SIGNALS:
    void readyToUpdate();
    void listAngleChanged();

public Q_SLOTS:
    void taskLoop();
    void startService();
    void stopService();
    void setRender(VideoRender* render);
    void updateScreen();
    void pause(bool pause);
    void enableHardwareTimer(bool enable);
    void changeSleepTime(int sleepTime);
    void changeTimerPeriodMotion(int sleepTime);
    void changeTimerPeriodInput(int sleepTime);
private:
    unsigned char m_renderData[93110400]; // 1920x1080 I420
    ApplicationSim* m_application;
    HardwareTimerSim* m_hardwareTimer;
    VideoRender* m_render = nullptr;
    float m_captureStep;
    QVariantList m_listAngle;
    QTimer *m_timer;
};

#endif // MAINPROCESS_H
