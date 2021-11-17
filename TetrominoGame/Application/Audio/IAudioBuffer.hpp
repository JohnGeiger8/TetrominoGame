//
//  IAudioBuffer.hpp
//  TetrominoGame
//
//  Created by John Geiger on 11/11/21.
//
#pragma once

#ifndef IAudioBuffer_hpp
#define IAudioBuffer_hpp

#include "Resource.hpp"

class IAudioBuffer
{
public:
    virtual ~IAudioBuffer() { };
    
    virtual std::shared_ptr<ResourceHandle> VGetResource()=0;
    
    virtual bool VInit()=0;
    
    virtual bool VPlay(int volume, bool looping)=0;
    virtual bool VPause()=0;
    virtual bool VStop()=0;
    virtual bool VResume()=0;
    
    virtual bool VTogglePause()=0;
    virtual bool VIsPlaying()=0;
    virtual bool VIsLooping() const=0;
    virtual void VSetVolume(int volume)=0;
    virtual int VGetVolume() const=0;
    //virtual float VGetProgress() const=0;
};

#endif /* IAudioBuffer_hpp */
