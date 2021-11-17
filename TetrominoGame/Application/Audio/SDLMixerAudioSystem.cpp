//
//  SDLMixerAudioSystem.cpp
//  TetrominoGame
//
//  Created by John Geiger on 11/12/21.
//

#include "SDLMixerAudioSystem.hpp"


bool SDLMixerAudioSystem::VInitialize()
{
    if(m_bInitialized)
        return true;

    m_bInitialized = false;
    mAllSamples.clear();

    m_bInitialized = true;

    return true;
}

//
// Shutdown the SDLMixerAudioSystem
//
void SDLMixerAudioSystem::VShutdown()
{
    if(m_bInitialized)
    {
        AudioSystem::VShutdown();
        m_bInitialized = false;
    }
}

//
//
//
IAudioBuffer* SDLMixerAudioSystem::VInitAudioBuffer(std::shared_ptr<ResourceHandle> handle)
{
    std::shared_ptr<SoundResourceExtraData> extra = std::static_pointer_cast<SoundResourceExtraData>(handle->GetExtra());
    
    switch(extra->GetSoundType())
    {
        case SOUND_TYPE_OGG:
        case SOUND_TYPE_WAVE:
        case SOUND_TYPE_MP3:
        case SOUND_TYPE_MIDI:
            // We support WAVs, OGGs, MIDIs, and MP3s
            break;

        default:
            assert(false && "Unknown sound type");
            return NULL;
    }

    // Add audio buffer to the list
    IAudioBuffer *audioBuffer = new SDLMixerAudioBuffer(handle);
    if (!audioBuffer->VInit())
        printf("Error initializing audio buffer.\n");
    mAllSamples.push_front(audioBuffer);
    
    return audioBuffer;
}

//
// Stops the buffer and removes it from the list
//
void SDLMixerAudioSystem::VReleaseAudioBuffer(IAudioBuffer *audioBuffer)
{
    audioBuffer->VStop();
    mAllSamples.remove(audioBuffer);
}



//
//
//
SDLMixerAudioBuffer::SDLMixerAudioBuffer(std::shared_ptr<ResourceHandle> resource)
    : AudioBuffer(resource)
{
    m_pMusic = NULL;
    m_pSound = NULL;
    
    // By default, choose next open channel
    mChannel = -1;
}

//
// Deallocate music and chunk
//
SDLMixerAudioBuffer::~SDLMixerAudioBuffer()
{
    if (m_pSound)
        Mix_FreeChunk(m_pSound);
    else if (m_pMusic)
        Mix_FreeMusic(m_pMusic);
    
    m_pSound = NULL;
    m_pMusic = NULL;
    mChannel = -1;
}

bool SDLMixerAudioBuffer::VInit()
{
    std::shared_ptr<SoundResourceExtraData> extra = std::static_pointer_cast<SoundResourceExtraData>(m_pResource->GetExtra());
    
    if (extra->IsSoundEffect())
        return LoadSoundEffect(extra->GetSoundType());
    else
        return LoadMusic(extra->GetSoundType());
}

//
// Loads SDL Mix sound effect
//
bool SDLMixerAudioBuffer::LoadSoundEffect(SoundType soundType)
{
    switch (soundType)
    {
        case SOUND_TYPE_WAVE:
        case SOUND_TYPE_OGG:
            m_pSound = Mix_LoadWAV(m_pResource->GetName().c_str());
            if (!m_pSound)
            {
                printf("Error loading sound effect. SDL Mix Error: %s\n", Mix_GetError());
                return false;
            }
            break;
        case SOUND_TYPE_MP3:
        case SOUND_TYPE_MIDI:
            printf("Error loading sound effect. MP3 and MIDI file type not supported.");
            return false;
            break;
        default:
            printf("Error loading sound effect");
            return false;
            break;
    }
    
    return true;
}

//
// Loads SDL Mix Music
//
bool SDLMixerAudioBuffer::LoadMusic(SoundType soundType)
{
    switch (soundType)
    {
        case SOUND_TYPE_MP3:
        case SOUND_TYPE_WAVE:
        case SOUND_TYPE_OGG:
        case SOUND_TYPE_MIDI:
            m_pMusic = Mix_LoadMUS(m_pResource->GetName().c_str());
            if (!m_pMusic)
            {
                printf("Error loading Music. SDL Mix Error: %s\n", Mix_GetError());
                return false;
            }
            break;
        default:
            printf("Error loading music.\n");
            return false;
            break;
    }
    
    return true;
}


//
// Plays sound stored in buffer
//
bool SDLMixerAudioBuffer::VPlay(int volume, bool looping)
{
    if (!g_pAudio->VActive())
        return false;
    
    VStop();
    
    mVolume = volume;
    mIsLooping = looping;
    
    // Loops should be -1 if true (-1 means continuously loop) and volume should be converted to 0-128
    int loops = mIsLooping ? -1 : 0;
    int sdlMixVolume = volume * 128;
    
    if (m_pSound)
    {
        m_pSound->volume = sdlMixVolume;
        mChannel = Mix_PlayChannel(mChannel, m_pSound, loops);
        if (mChannel == -1)
        {
            printf("Error playing sound effect. SDL_mixer Error: %s\n", Mix_GetError());
            return false;
        }
    }
    else if (m_pMusic)
    {
        Mix_VolumeMusic(sdlMixVolume);
        if (Mix_PlayMusic(m_pMusic, loops) == -1)
        {
            printf("Error playing music. SDL_mixer Error: %s\n", Mix_GetError());
            return false;
        }
    }
    
    return true;
}

//
// Pauses sound stored in buffer
//
bool SDLMixerAudioBuffer::VPause()
{
    if (!g_pAudio->VActive())
        return false;
    
    if (m_pSound)
    {
        Mix_Pause(mChannel);
    }
    else if (m_pMusic)
    {
        Mix_PauseMusic();
    }
    mIsPaused = true;
    
    return true;
}

//
// Stops stored sound
//
bool SDLMixerAudioBuffer::VStop()
{
    if (!g_pAudio->VActive())
        return false;
    
    if (m_pSound)
    {
        Mix_HaltChannel(mChannel);
    }
    else if (m_pMusic)
    {
        Mix_HaltMusic();
    }
    mIsPaused = true;
    
    return true;
}

//
// Resumes paused sound
//
bool SDLMixerAudioBuffer::VResume()
{
    if (!g_pAudio->VActive())
        return false;
    
    if (m_pSound)
    {
        Mix_Resume(mChannel);
    }
    else if (m_pMusic)
    {
        Mix_ResumeMusic();
    }
    mIsPaused = false;
    
    return true;
}

//
// Pauses/Unpauses sound
//
bool SDLMixerAudioBuffer::VTogglePause()
{
    if (!g_pAudio->VActive())
        return false;
    
    if (mIsPaused)
        VResume();
    else
        VPause();
    
    return true;
}

//
// Returns true if the sound is actively playing
//
bool SDLMixerAudioBuffer::VIsPlaying()
{
    if (!g_pAudio->VActive())
        return false;
    
    bool isPlaying = false;
    if (m_pSound)
        isPlaying = Mix_Playing(mChannel);
    else if (m_pMusic)
        isPlaying = Mix_PlayingMusic();
    
    return isPlaying;
}

//
// Sets volume for sound
//
void SDLMixerAudioBuffer::VSetVolume(int volume)
{
    if (!g_pAudio->VActive())
        return;
    
    mVolume = volume;
    if (m_pSound)
        Mix_Volume(mChannel, volume * 128);
    else if (m_pMusic)
        Mix_VolumeMusic(volume * 128);
}

void SDLMixerAudioBuffer::VSetPosition(unsigned long newPosition)
{
    // FIXME: maybe don't need this
}

