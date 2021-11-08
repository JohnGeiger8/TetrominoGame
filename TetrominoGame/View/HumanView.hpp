//
//  HumanView.hpp
//  TetrominoGame
//
//  Created by John Geiger on 10/26/21.
//
#pragma once

#ifndef HumanView_hpp
#define HumanView_hpp

#include "UI/Interfaces.hpp"
#include "InputHandlers/IKeyboardHandler.hpp"

class HumanView
{
public:
    ScreenElementList mScreenElements;
    std::shared_ptr<IKeyboardHandler> mKeyboardHandler;

    HumanView();
    ~HumanView();
    
    virtual bool VInit();
    virtual void VShutdown();
    virtual void VUpdate();
    virtual void VRender();
    virtual void VDrawText(std::string text, SDL_Rect* renderRectangle, SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF}, int fontSize = 16, std::string fontPath = "");
    virtual void VProcessMessages(SDL_Event* pEvent);
    
    virtual void VPushElement(ScreenElementPointer pElement);
    virtual void VRemoveElement(ScreenElementPointer pElement);
    
};

#endif /* HumanView_hpp */
