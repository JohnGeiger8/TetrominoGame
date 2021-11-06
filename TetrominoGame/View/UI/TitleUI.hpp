//
//  TitleUI.hpp
//  TetrominoGame
//
//  Created by John Geiger on 11/4/21.
//
#pragma once

#ifndef TitleUI_hpp
#define TitleUI_hpp

#include "Interfaces.hpp"
#include "SDLTextTexture.hpp"

//
// Represents a button you would place in a menu
//
class TitleUI : public UIElement
{
    std::shared_ptr<SDLTextTexture> m_pTextTexture;
    std::string mTitle;
    int mFontSize;
    SDL_Color mColor;
    
public:
    TitleUI(std::string text, int fontSize = 24, SDL_Color color = {0xFF, 0xFF, 0xFF});
    ~TitleUI();
    
    virtual void VSetTitle(std::string text) { mTitle = text; };
    virtual void VSetColor(SDL_Color color) { mColor = color; };
    
    virtual std::string VGetTitle() { return mTitle; };
    virtual SDL_Color VGetColor() { return mColor; };
    
    // IScreenElement implementation
    virtual void VUpdate();
    virtual void VRender();
    virtual void VDrawText();
    
    // Overrides
    virtual int VGetWidth() { return m_pTextTexture->GetWidth(); };
    virtual int VGetHeight() { return m_pTextTexture->GetHeight(); };
    
private:
    virtual void VLoadTitleText();
};

#endif /* TitleUI_hpp */
