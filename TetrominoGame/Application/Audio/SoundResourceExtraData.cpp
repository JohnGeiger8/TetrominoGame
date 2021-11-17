//
//  SoundResourceExtraData.cpp
//  TetrominoGame
//
//  Created by John Geiger on 11/12/21.
//

#include "SoundResourceExtraData.hpp"

SoundResourceExtraData::SoundResourceExtraData()
    : mSoundType(SOUND_TYPE_UNKNOWN), m_bInitialized(false), mLengthMs(0)
{
    
}

//
// Initializes fields of extra sound data
//
void SoundResourceExtraData::Initialize(SoundType type, bool isSoundEffect)
{
    mSoundType = type;
    mIsSoundEffect = isSoundEffect;
    m_bInitialized = true;
}
