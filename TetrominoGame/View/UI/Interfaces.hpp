//
//  Interfaces.hpp
//  TetrominoGame
//
//  Created by John Geiger on 10/24/21.
//
#pragma once

#ifndef Interfaces_hpp
#define Interfaces_hpp

#include <list>
#include <string>
#include <SDL2/SDL.h>

class IScreenElement;

using ScreenElementPointer = std::shared_ptr<IScreenElement>;
using ScreenElementList = std::list<ScreenElementPointer>;

//
// Interface that represents any generic UI element
//
class IScreenElement
{
public:
    virtual void VUpdate()=0;
    virtual void VRender()=0;
    virtual void VDrawText()=0;
    virtual bool VIsVisible()=0;
    virtual void VSetVisible(bool visible)=0;
};

//
// Represents generic UI element with position and size
//
class UIElement : public IScreenElement
{
protected:
    int mPositionX, mPositionY;
    int mWidth, mHeight;
    
    bool m_bIsVisible;
    bool m_bIsSelected;
    bool m_bHasFocus;
    bool m_bIsFocusable;
    
public:
    UIElement() { mPositionX = 0; mPositionY = 0; mWidth = 100; mHeight = 100; m_bIsVisible = true; m_bIsSelected = false; m_bHasFocus = false; m_bIsFocusable = true; };
    
    virtual int VGetWidth() { return mWidth; };
    virtual int VGetHeight() { return mHeight; };
    virtual int VGetPositionX() { return mPositionX; };
    virtual int VGetPositionY() { return mPositionY; };
    
    virtual void VSetWidth(int width) { mWidth = width; };
    virtual void VSetHeight(int height) { mHeight = height; };
    virtual void VSetPositionX(int x) { mPositionX = x; };
    virtual void VSetPositionY(int y) { mPositionY = y; };
    
    virtual void VSetSelect(bool selected) { m_bIsSelected = selected; }
    virtual void VSetFocus(bool focus) { m_bHasFocus = focus; }
    virtual bool VIsSelected() { return m_bIsSelected; };
    virtual bool VHasFocus() { return m_bHasFocus; };
    virtual bool VIsFocusable() { return m_bIsFocusable; };
    
    virtual void VUpdate() { };
    virtual bool VIsVisible() { return m_bIsVisible; }
    virtual void VSetVisible(bool visible) { m_bIsVisible = visible; }
};
#endif /* Interfaces_hpp */
