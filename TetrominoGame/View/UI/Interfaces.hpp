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
    
public:
    UIElement() { mPositionX = 0; mPositionY = 0; mWidth = 100; mHeight = 100; m_bIsVisible = true; };
    
    virtual void VUpdate() { };
    virtual bool VIsVisible() const { return m_bIsVisible; }
    virtual void VSetVisible(bool visible) { m_bIsVisible = visible; }
};
#endif /* Interfaces_hpp */
