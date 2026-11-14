#ifndef SMOOTHMOTION_H
#define SMOOTHMOTION_H
#include "StdTypes.h"

class ApplicationController;
class SmoothMotion {
  public:
    SmoothMotion(uint8_t id, ApplicationController* app);
    void init();
    void changeStateControl(MOTION_STATE newState);
    
  public:
    ApplicationController* m_app;
    int m_targetStep;
    int m_targetDirection;

    uint8_t m_id;
    MOTION_STATE m_state;
};

#endif // SMOOTHMOTION_H
