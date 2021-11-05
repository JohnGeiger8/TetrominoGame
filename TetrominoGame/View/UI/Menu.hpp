//
//  Menu.hpp - Defines basic menu objects
//  TetrominoGame
//
//  Created by John Geiger on 10/24/21.
//
#pragma once

#ifndef Menu_hpp
#define Menu_hpp

#define HORIZONTAL_BUTTON_MARGINS 30
#define VERTICAL_BUTTON_MARGINS 40

#include <SDL2_ttf/SDL_ttf.h>
#include <vector>
#include "Interfaces.hpp"
#include "Timer.hpp"
#include "SDLTextTexture.hpp"

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
    virtual void VRender();
    virtual void VDrawText() { };
};

//
// Represents a button you would place in a menu
//
class MenuButtonUI : public UIElement
{
    std::string mButtonText;
    SDL_Color mColor;
    std::shared_ptr<SDLTextTexture> m_pTextTexture;
    
public:
    MenuButtonUI(std::string text = "");
    ~MenuButtonUI();
    
    void SetButtonText(std::string text) { mButtonText = text; };
    void SetButtonColor(SDL_Color color) { mColor = color; };
    
    std::string GetButtonText() { return mButtonText; };
    SDL_Color GetColor() { return mColor; };
    
    // IScreenElement implementation
    virtual void VUpdate();
    virtual void VRender();
    virtual void VDrawText();
    
private:
    void LoadButtonText();
};

#endif /* Menu_hpp */
