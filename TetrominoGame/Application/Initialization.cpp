//
//  Initialization.cpp
//  TetrominoGame
//
//  Created by John Geiger on 10/14/21.
//

#include "Initialization.hpp"

//
// Initializes game options to reasonable default values
//
GameOptions::GameOptions()
{
    mSoundEffectsVolume = 1.0f;
    mMusicVolume = 1.0f;

    mScreenWidth = 600;
    mScreenHeight = 600;
}
