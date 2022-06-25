//
//  Audio.hpp
//  TetrominoGame
//
//  Created by John Geiger on 11/11/21.
//
#pragma once

#ifndef Audio_hpp
#define Audio_hpp

#include <list>
#include "IAudio.hpp"

namespace Torti {

class AudioSystem : public IAudio
{
public:
    AudioSystem();
    ~AudioSystem() { VShutdown(); }
    virtual void VStopAllSounds();
    virtual void VPauseAllSounds();
    virtual void VResumeAllSounds();

    virtual void VShutdown();
    
//    static bool HasSoundCard();
    bool IsPaused() { return m_bAllPaused; }

protected:

    typedef std::list<IAudioBuffer *> AudioBufferList;

    AudioBufferList mAllSamples;    // List of all currently allocated audio buffers
    bool m_bAllPaused;              // Has the sound system been paused?
    bool m_bInitialized;            // Has the sound system been initialized?
};

using AudioSystemPtr = std::shared_ptr<AudioSystem>;
extern AudioSystemPtr g_pAudio;

}

#endif /* Audio_hpp */
