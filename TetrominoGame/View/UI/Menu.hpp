//
//  Menu.hpp - Defines basic menu objects
//  TetrominoGame
//
//  Created by John Geiger on 10/24/21.
//
#pragma once

#ifndef Menu_hpp
#define Menu_hpp

#include <SDL2_ttf/SDL_ttf.h>
#include <vector>
#include "Interfaces.hpp"
#include "Timer.hpp"
//#include "../InputHandlers/IKeyboardHandler.hpp"

using UIElementPointer = std::shared_ptr<UIElement>;
using UIElementVector = std::vector<UIElementPointer>;

//
// Represents a main menu with a list of options
//
class MainMenuUI : public UIElement
{
    std::shared_ptr<Timer> m_pUserInputTimer;
    UIElementVector mMenuOptions;
    int mActiveMenuOption;
    
public:
    MainMenuUI();
    ~MainMenuUI();
    
    void AddMenuOption(UIElementPointer screenElement);
    void RemoveMenuOption(UIElementPointer screenElement);    
        
    // IScreenElement implementation
    virtual void VUpdate();
    virtual void VRender(SDL_Renderer* pRenderer);
    virtual void VDrawText(SDL_Renderer* pRenderer) { };
};

//
// Represents a button you would place in a menu
//
class MenuButtonUI : public UIElement
{
    std::string mButtonText;
    TTF_Font* m_pButtonFont;
    int mFontSize;
    bool mIsFilled;
    SDL_Color mColor;
    
public:
    MenuButtonUI(std::string text = "", bool filled = false);
    ~MenuButtonUI();
    
    void SetButtonText(std::string text) { mButtonText = text; };
    void SetButtonColor(SDL_Color color) { mColor = color; };
    void SetIsFilled(bool filled) { mIsFilled = filled; };
    
    std::string GetButtonText() { return mButtonText; };
    SDL_Color GetColor() { return mColor; };
    
    // IScreenElement implementation
    virtual void VUpdate();
    virtual void VRender(SDL_Renderer* pRenderer);
    virtual void VDrawText(SDL_Renderer* pRenderer);
};

#endif /* Menu_hpp */
