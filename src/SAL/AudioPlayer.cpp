#include "AudioPlayer.h"
#include "ApplicationController.h"

AudioPlayer::AudioPlayer(ApplicationController* app):
    m_app(app)
{

}
void AudioPlayer::changeAudio(char* audioFile)
{

}

AUDIO_PLAYER_STATE AudioPlayer::currentState()
{
    return m_audioState;
}

AUDIO_PLAYER_STATE AudioPlayer::audioPlayerMainFuntion() {
    AUDIO_PLAYER_STATE currentState = m_audioState;
    switch (currentState) {
    case AUDIO_PLAYER_IDLE:
    {

    }
        break;
    case AUDIO_PLAYER_INIT:
    {

    }
        break;
    case AUDIO_PLAYER_INPROGRESS:
    {

    }
        break;
    case AUDIO_PLAYER_DONE:
        break;
    }
    return currentState;
}
