//
//  SoundResourceExtraData.hpp
//  TetrominoGame
//
//  Created by John Geiger on 11/12/21.
//
#pragma once

#ifndef SoundResourceExtraData_hpp
#define SoundResourceExtraData_hpp

#include "Resource.hpp"

namespace Torti {

enum SoundType
{
    SOUND_TYPE_FIRST,
    SOUND_TYPE_MP3 = SOUND_TYPE_FIRST,
    SOUND_TYPE_WAVE,
    SOUND_TYPE_MIDI,
    SOUND_TYPE_OGG,

    // This needs to be the last sound type
    SOUND_TYPE_COUNT,
    SOUND_TYPE_UNKNOWN,
};

///
///
///
class SoundResourceExtraData : public IResourceExtraData
{
public:
    SoundResourceExtraData();
    virtual ~SoundResourceExtraData() { }
    virtual std::string VToString() { return "SoundResourceExtraData"; }
    enum SoundType GetSoundType() { return mSoundType; }
    int GetLengthMilli() const { return mLengthMs; }
    bool IsSoundEffect() { return mIsSoundEffect; }
    
    void Initialize(SoundType type, bool isSoundEffect);

protected:
    enum SoundType mSoundType;        // Is this an Ogg, WAV, etc.?
    bool mIsSoundEffect;              // Is this a sound effect or music?
    bool m_bInitialized;              // Has the sound been initialized
    int mLengthMs;                    // How long the sound is in milliseconds
};

};

#endif /* SoundResourceExtraData_hpp */
