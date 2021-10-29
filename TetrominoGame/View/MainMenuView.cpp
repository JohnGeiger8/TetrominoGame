//
//  MainMenuView.cpp
//  TetrominoGame
//
//  Created by John Geiger on 10/25/21.
//

#include "MainMenuView.hpp"

MainMenuView::MainMenuView(SDL_Renderer *pRenderer) : HumanView(pRenderer)
{
}

//
// Initialize menu and open font
//
// Returns: true if successful.
//
bool MainMenuView::VInit()
{
    bool successful = HumanView::VInit();
    
    // Create menu
    m_pMenu = std::make_shared<MainMenuUI>();
    m_pMenu->VSetPositionX(175);
    m_pMenu->VSetPositionY(50);
    
    // Create menu options
    std::shared_ptr<MenuButtonUI> startButton = std::make_shared<MenuButtonUI>("Start");
    startButton->VSetPositionX(m_pMenu->VGetPositionX() + 15);
    startButton->VSetPositionY(m_pMenu->VGetPositionY() + 15);
    startButton->VSetWidth(200);
    startButton->VSetHeight(75);
    
    std::shared_ptr<MenuButtonUI> quitButton = std::make_shared<MenuButtonUI>("Quit");
    quitButton->VSetPositionX(startButton->VGetPositionX());
    quitButton->VSetPositionY(startButton->VGetPositionY() + startButton->VGetHeight() + 15);
    quitButton->VSetWidth(200);
    quitButton->VSetHeight(75);
    
    m_pMenu->AddMenuOption(startButton);
    m_pMenu->AddMenuOption(quitButton);
    VPushElement(m_pMenu);
    
    return successful;
}

//
// Process SDL messages
//
void MainMenuView::VProcessMessages(SDL_Event *pEvent)
{
    // FIXME: DO I NEED THIS?
}
