//
//  AudioBuffer.hpp
//  TetrominoGame
//
//  Created by John Geiger on 11/11/21.
//
#pragma once

#ifndef AudioBuffer_hpp
#define AudioBuffer_hpp

#include <memory>
#include "IAudioBuffer.hpp"
#include "Resource.hpp"

namespace Torti {

class AudioBuffer : public IAudioBuffer
{
public:
    virtual std::shared_ptr<ResourceHandle> VGetResource() { return m_pResource; };
    virtual bool VIsLooping() const { return mIsLooping; };
    virtual int VGetVolume() const { return mVolume; };
    
protected:
    std::shared_ptr<ResourceHandle> m_pResource;
    bool mIsPaused;
    bool mIsLooping;
    int mVolume;
    
    AudioBuffer(std::shared_ptr<ResourceHandle> resource)
    {
        m_pResource = resource;
        mIsPaused = false;
        mIsLooping = false;
        mVolume = 0;
    };
};

}

#endif /* AudioBuffer_hpp */
