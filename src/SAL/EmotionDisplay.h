#ifndef EMOTIONDISPLAY_H
#define EMOTIONDISPLAY_H
#include "StdTypes.h"

class ApplicationController;
class EmotionDisplay
{
public:
    EmotionDisplay(ApplicationController* app);
    void setState(DISPLAY_STATE state);
    DISPLAY_STATE currentState();
    DISPLAY_STATE displayMainFuntion();

private:
    ApplicationController* m_app;
    DisplayParam m_currentParam;
    DISPLAY_STATE m_displayState;
};

#endif // EMOTIONDISPLAY_H
