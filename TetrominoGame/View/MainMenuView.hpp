//
//  MainMenuView.hpp
//  TetrominoGame
//
//  Created by John Geiger on 10/25/21.
//
#pragma once

#ifndef MainMenuView_hpp
#define MainMenuView_hpp

#include "UI/Menu.hpp"
#include "UI/TitleUI.hpp"
#include "HumanView.hpp"

class MainMenuView : public HumanView
{
    std::shared_ptr<MainMenuUI> m_pMenu;
    
    std::shared_ptr<MenuButtonUI> mStartButton;
    std::shared_ptr<MenuButtonUI> mQuitButton;

public:
    MainMenuView();
    
    virtual bool VInit();
    virtual void VUpdate();
    virtual void VProcessMessages(SDL_Event* pEvent);

};

#endif /* MainMenuView_hpp */
