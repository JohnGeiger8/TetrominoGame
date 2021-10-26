//
//  IKeyboardHandler.hpp
//  TetrominoGame
//
//  Created by John Geiger on 10/25/21.
//
#pragma once

#ifndef IKeyboardHandler_hpp
#define IKeyboardHandler_hpp

#include <SDL2/SDL.h>

class IKeyboardHandler
{
public:
    virtual bool VOnKeyDown(const SDL_Keycode key)=0;
    virtual bool VOnKeyUp(const SDL_Keycode key)=0;
};

#endif /* IKeyboardHandler_hpp */
