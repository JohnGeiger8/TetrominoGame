//
//  SDLMixerAudioSystem.hpp
//  TetrominoGame
//
//  Created by John Geiger on 11/12/21.
//
#pragma once

#ifndef SDLMixerAudioSystem_hpp
#define SDLMixerAudioSystem_hpp

#include <SDL2_mixer/SDL_mixer.h>
#include "Audio.hpp"
#include "AudioBuffer.hpp"
#include "SoundResourceExtraData.hpp"
#include "Resource.hpp"

namespace Torti {

class SDLMixerAudioBuffer : public AudioBuffer
{
private:
    Mix_Music* m_pMusic;
    Mix_Chunk* m_pSound;
    
    int mChannel; // Channel sound/music is being played on
    
    bool LoadSoundEffect(SoundType soundType);
    bool LoadMusic(SoundType soundType);
    
public:
    SDLMixerAudioBuffer(std::shared_ptr<ResourceHandle> resource);
    virtual ~SDLMixerAudioBuffer();
    
    virtual bool VInit();

    virtual bool VPlay(int volume, bool looping);
    virtual bool VPause();
    virtual bool VStop();
    virtual bool VResume();

    virtual bool VTogglePause();
    virtual bool VIsPlaying();
    virtual void VSetVolume(int volume);
//    virtual void VSetPosition(unsigned long newPosition);
};


class SDLMixerAudioSystem : public AudioSystem
{
public:
    virtual ~SDLMixerAudioSystem() { VShutdown(); }
    
    virtual bool VActive() { return true; };

    virtual IAudioBuffer *VInitAudioBuffer(std::shared_ptr<ResourceHandle> handle);
    virtual void VReleaseAudioBuffer(IAudioBuffer* audioBuffer);

    virtual void VShutdown();
    virtual bool VInitialize();
};

}

#endif /* SDLMixerAudioSystem_hpp */
