//
//  Audio.cpp
//  TetrominoGame
//
//  Created by John Geiger on 11/11/21.
//

#include "Audio.hpp"

AudioSystem::AudioSystem()
{
    
}

//
// Stop audio of all samples and clear list
//
void AudioSystem::VShutdown()
{
    AudioBufferList::iterator i = mAllSamples.begin();
    
    while (i != mAllSamples.end())
    {
        (*i)->VStop();
        ++i;
    }
    mAllSamples.clear();
    
    if (g_pAudio.get() == this)
        g_pAudio = NULL;
}

//
// Pause sounds in all audio buffers, including music
//
void AudioSystem::VPauseAllSounds()
{
    AudioBufferList::iterator i;
    AudioBufferList::iterator end;
    for (i = mAllSamples.begin(), end = mAllSamples.end(); i != end; i++)
    {
        IAudioBuffer *audioBuffer = (*i);
        audioBuffer->VPause();
    }
    
    m_bAllPaused = true;
}

//
// Resume sounds in all audio buffers, including music
//
void AudioSystem::VResumeAllSounds()
{
    AudioBufferList::iterator i;
    AudioBufferList::iterator end;
    for (i = mAllSamples.begin(), end = mAllSamples.end(); i != end; i++)
    {
        IAudioBuffer *audioBuffer = (*i);
        audioBuffer->VResume();
    }
    
    m_bAllPaused = false;
}

//
// Stop sounds in all audio buffers
//
void AudioSystem::VStopAllSounds()
{
    IAudioBuffer *audioBuffer = NULL;
    
    AudioBufferList::iterator i, end;
    for (i = mAllSamples.begin(), end = mAllSamples.end(); i != end; i++)
    {
        audioBuffer = (*i);
        audioBuffer->VStop();
    }
    
    m_bAllPaused = false;
}
