//
//  SDLTextTexture.hpp
//  TetrominoGame
//
//  Created by John Geiger on 11/4/21.
//
#pragma once

#ifndef SDLTextTexture_hpp
#define SDLTextTexture_hpp

#define DEFAULT_FONT_PATH "Assets/ARCADECLASSIC.ttf"

#include <SDL2_ttf/SDL_ttf.h>
#include "SDLTexture.hpp"

class SDLTextTexture : public SDLTexture
{
    std::string mFontPath;
    TTF_Font* m_pFont;
    std::string mText;
    int mFontSize;
    
public:
    SDLTextTexture();
    SDLTextTexture(std::string text, int fontSize)
        : mText(text), mFontSize(fontSize) { m_pFont = NULL; mFontPath = DEFAULT_FONT_PATH; };
    ~SDLTextTexture();
    
    virtual void VShutdown();
    
    bool LoadTextTextureFromFile(std::string path);
    
    // 'Change' instead of 'Set' indicates non-trivial set (re-renders texture)
    void ChangeFontSize(int fontSize);
    void ChangeText(std::string text);
    void ChangeFont(std::string path);
    virtual void VSetColor(Uint8 red, Uint8 green, Uint8 blue);
};

#endif /* SDLTextTexture_hpp */
