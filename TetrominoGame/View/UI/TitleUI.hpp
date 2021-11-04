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

//
// Represents a button you would place in a menu
//
class TitleUI : public UIElement
{
//    // FIXME: this would be much cleaner with a Font wrapper class
//    std::string mButtonText;
//    TTF_Font* m_pButtonFont;
//    SDL_Surface* m_pTextSurface;
//    SDL_Texture* m_pTextTexture;
//    int mFontSize;
//    SDL_Color mColor;
//    
//public:
//    MenuButtonUI(std::string text = "");
//    ~MenuButtonUI();
//    
//    void SetButtonText(std::string text) { mButtonText = text; };
//    void SetButtonColor(SDL_Color color) { mColor = color; };
//    
//    std::string GetButtonText() { return mButtonText; };
//    SDL_Color GetColor() { return mColor; };
//    
//    // IScreenElement implementation
//    virtual void VUpdate();
//    virtual void VRender(SDL_Renderer* pRenderer);
//    virtual void VDrawText(SDL_Renderer* pRenderer);
//    
//private:
//    void LoadButtonText();
};

#endif /* TitleUI_hpp */
