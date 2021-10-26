//
//  Menu.hpp - Defines basic menu objects
//  TetrominoGame
//
//  Created by John Geiger on 10/24/21.
//
#pragma once

#ifndef Menu_hpp
#define Menu_hpp

#include "Interfaces.hpp"
#include "../InputHandlers/IKeyboardHandler.hpp"
//
// Represents a main menu with a list of options
//
class MainMenuUI : public UIElement
{
private:
    ScreenElementList mMenuOptions;
    
public:
    MainMenuUI();
    
    void AddMenuOption(ScreenElementPointer screenElement);
    void RemoveMenuOption(ScreenElementPointer screenElement);
    
    const ScreenElementList GetMenuOptions() const { return mMenuOptions; }
    
    virtual void VUpdate();
};

//
// Represents a button you would place in a menu
//
class MenuButtonUI : public UIElement
{
    std::string mButtonText;
    bool mIsFilled;
    bool mIsSelected;
    bool mHasFocus;
    SDL_Color mColor;
    
public:
    MenuButtonUI(std::string text = "", bool filled = true)
    : mButtonText(text), mIsFilled(filled) { mColor = { 0x00, 0x00, 0xFF }; };
    
    void Select() { mIsSelected = true; }
    void SetButtonText(std::string text) { mButtonText = text; };
    void SetButtonColor(SDL_Color color) { mColor = color; };
    void SetIsFilled(bool filled) { mIsFilled = filled; };
    std::string GetButtonText() { return mButtonText; };
    
    bool IsSelected() { return mIsSelected; };
    bool HasFocus() { return mHasFocus; };
    
    virtual void VUpdate();
};

#endif /* Menu_hpp */
