//
//  IAudio.hpp
//  TetrominoGame
//
//  Created by John Geiger on 11/11/21.
//
#pragma once

#ifndef IAudio_hpp
#define IAudio_hpp

#include <memory>
#include "IAudioBuffer.hpp"
#include "Resource.hpp"

class IAudio
{
public:
    virtual bool VActive()=0;
    
    virtual IAudioBuffer *VInitAudioBuffer(std::shared_ptr<ResourceHandle> soundResource)=0;
    virtual void VReleaseAudioBuffer(IAudioBuffer* audioBuffer)=0;
    
    virtual void VStopAllSounds()=0;
    virtual void VPauseAllSounds()=0;
    virtual void VResumeAllSounds()=0;
    
    virtual bool VInitialize()=0;
    virtual void VShutdown()=0;
};

#endif /* IAudio_hpp */
