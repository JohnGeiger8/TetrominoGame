//
//  MainMenuView.cpp
//  TetrominoGame
//
//  Created by John Geiger on 10/25/21.
//

#include "MainMenuView.hpp"
#include "CVar.hpp"

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
    mStartButton = std::make_shared<MenuButtonUI>("Start");
    mStartButton->VSetPositionX(m_pMenu->VGetPositionX() + 15);
    mStartButton->VSetPositionY(m_pMenu->VGetPositionY() + 15);
    mStartButton->VSetWidth(200);
    mStartButton->VSetHeight(75);
    
    mQuitButton = std::make_shared<MenuButtonUI>("Quit");
    mQuitButton->VSetPositionX(mStartButton->VGetPositionX());
    mQuitButton->VSetPositionY(mStartButton->VGetPositionY() + mStartButton->VGetHeight() + 15);
    mQuitButton->VSetWidth(200);
    mQuitButton->VSetHeight(75);
    
    m_pMenu->AddMenuOption(mStartButton);
    m_pMenu->AddMenuOption(mQuitButton);
    VPushElement(m_pMenu);
    
    return successful;
}

//
// Update menu items and check for button clicks
//
void MainMenuView::VUpdate()
{
    HumanView::VUpdate();
    
    // Start the game
    if (mStartButton->VIsSelected())
    {
        CVar g_isGameStarted = g_cvars.find("isGameStarted")->second;
        g_isGameStarted.SetBoolValue(true);
        g_cvars.erase("isGameStarted");
        g_cvars.insert(pair<std::string, CVar>("isGameStarted", g_isGameStarted));
    }
    
    // Exit the game
    if (mQuitButton->VIsSelected())
    {
        CVar g_isQuitting = g_cvars.find("isQuitting")->second;
        g_isQuitting.SetBoolValue(true);
        g_cvars.erase("isQuitting");
        g_cvars.insert(pair<std::string, CVar>("isQuitting", g_isQuitting));
    }
}


//
// Process SDL messages
//
void MainMenuView::VProcessMessages(SDL_Event *pEvent)
{
    // FIXME: DO I NEED THIS?
}
