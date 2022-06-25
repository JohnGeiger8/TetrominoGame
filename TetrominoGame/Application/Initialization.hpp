//
//  Initialization.hpp
//  TetrominoGame
//
//  Created by John Geiger on 10/14/21.
//
#pragma once

#ifndef Initialization_hpp
#define Initialization_hpp

#include <string>

struct GameOptions
{
    // Screen
    int mScreenHeight;
    int mScreenWidth;

    // Sound options
    float mSoundEffectsVolume;
    float mMusicVolume;

    // Look at this to find other options added by the developer
    //tinyxml2::XMLDocument *m_pDoc;

    GameOptions();
//    ~GameOptions() { delete(m_pDoc); }

    //void Init(const char* xmlFilePath, std::string lpCmdLine); 
};

#endif /* Initialization_hpp */
