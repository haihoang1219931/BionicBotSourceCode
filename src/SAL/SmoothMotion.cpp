#include "SmoothMotion.h"
#include "ApplicationController.h"
#if defined(DEBUG_COMMAND)
#include "../ApplicationArduino.h"
extern ApplicationArduino app;
#endif
SmoothMotion::SmoothMotion(uint8_t id, ApplicationController* app):
  m_app(app),
  m_id(id),
  m_state(MOTION_INIT)
{
}

void SmoothMotion::changeStateControl(MOTION_STATE newState)
{
  if(m_state != newState) {
    m_state = newState;
  }
}

