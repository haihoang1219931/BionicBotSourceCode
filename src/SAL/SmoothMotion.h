#ifndef SMOOTHMOTION_H
#define SMOOTHMOTION_H
#include "StdTypes.h"

class ApplicationController;
class SmoothMotion {
  public:
    SmoothMotion(MOTOR id, ApplicationController* app);
    void initMotion();
    void setEmotionState(float targetAngle,
                         float speed);
    MOTION_STATE currentState();
    MOTION_STATE motionMainFuntion();
    float currentAngle();
private:
    ApplicationController* m_app;
    ServoParam m_currentParam;
    ServoParam m_targetParam;

    MOTION_STATE m_motionState;

    MOTOR m_id;
};

#endif // SMOOTHMOTION_H
