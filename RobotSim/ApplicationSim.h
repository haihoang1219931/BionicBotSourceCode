#ifndef APPLICATIONSIM_H
#define APPLICATIONSIM_H

#include "../src/SAL/ApplicationController.h"
class MainProcess;
class ApplicationSim: public ApplicationController
{
public:
    ApplicationSim(MainProcess* mainProcess);
    ~ApplicationSim();
    void initRobot() override;
    int printf(const char *fmt, ...) override;
    void msleep(int millis) override;
    long getSystemTime() override;
    void enableHardwareTimer(bool enable) override;
    void enableMotor(MOTOR motorID, bool enable) override;
private:
    MainProcess* m_mainProcess;
    char m_command[MAX_COMMAND_LENGTH];
};

#endif // APPLICATIONSIM_H
