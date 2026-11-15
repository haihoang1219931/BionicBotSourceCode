#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H
#include "StdTypes.h"

class ApplicationController;
class AudioPlayer
{
public:
    AudioPlayer(ApplicationController* m_app);
    void changeAudio(char* audioFile);
    AUDIO_PLAYER_STATE currentState();
    AUDIO_PLAYER_STATE audioPlayerMainFuntion();

private:
    ApplicationController* m_app;
    AUDIO_PLAYER_STATE m_audioState;
};

#endif // AUDIOPLAYER_H
