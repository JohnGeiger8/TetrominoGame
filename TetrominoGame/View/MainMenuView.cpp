//
//  MainMenuView.cpp
//  TetrominoGame
//
//  Created by John Geiger on 10/25/21.
//

#include "MainMenuView.hpp"
#include "CVar.hpp"
#include "Audio.hpp"
#include "SoundResourceExtraData.hpp"

MainMenuView::MainMenuView()
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
    int screenHeight = g_cvars.find("screenHeight")->second.GetIntValue();
    int screenWidth = g_cvars.find("screenWidth")->second.GetIntValue();
    m_pMenu = std::make_shared<MainMenuUI>();
    
    // Create menu options
    SDL_Color titleColor = { 0x00, 0xFF, 0xFF };
    std::shared_ptr<TitleUI> pTitleUI = std::make_shared<TitleUI>("BLOCK DROPPER", 36, titleColor);
    mStartButton = std::make_shared<MenuButtonUI>("Start");
    mQuitButton = std::make_shared<MenuButtonUI>("Quit");

    mStartButton->VSetWidth(screenWidth / 3);
    mStartButton->VSetHeight(85);
    mQuitButton->VSetWidth(screenWidth / 3);
    mQuitButton->VSetHeight(85);
    
    m_pMenu->VSetPositionX((screenWidth / 2) - (mStartButton->VGetWidth() / 2) - HORIZONTAL_BUTTON_MARGINS);
    mStartButton->VSetPositionX(m_pMenu->VGetPositionX() + HORIZONTAL_BUTTON_MARGINS);
    mQuitButton->VSetPositionX(m_pMenu->VGetPositionX() + HORIZONTAL_BUTTON_MARGINS);
    
    m_pMenu->VSetWidth(mStartButton->VGetWidth() + 2 * HORIZONTAL_BUTTON_MARGINS);
    m_pMenu->VSetHeight(mStartButton->VGetHeight() + mQuitButton->VGetHeight() + 3 * VERTICAL_BUTTON_MARGINS);
    m_pMenu->VSetPositionY((screenHeight / 2) - (m_pMenu->VGetHeight() / 2));
    
    // Title position should be centered because it's text
    pTitleUI->VSetPositionX(m_pMenu->VGetPositionX() + m_pMenu->VGetWidth() / 2);
    pTitleUI->VSetPositionY(m_pMenu->VGetPositionY() + VERTICAL_BUTTON_MARGINS);

    mStartButton->VSetPositionY(pTitleUI->VGetPositionY() + pTitleUI->VGetHeight() + VERTICAL_BUTTON_MARGINS);
    mQuitButton->VSetPositionY(mStartButton->VGetPositionY() + mStartButton->VGetHeight() + VERTICAL_BUTTON_MARGINS);

    // Colors
    mStartButton->SetButtonColor({0x00, 0xFF, 0xFF});
    mQuitButton->SetButtonColor({0x00, 0xFF, 0xFF});
    m_pMenu->SetColor({0x00, 0x00, 0x00, 0x00}); // Transparent
    
    m_pMenu->AddMenuOption(pTitleUI);
    m_pMenu->AddMenuOption(mStartButton);
    m_pMenu->AddMenuOption(mQuitButton);
    VPushElement(m_pMenu);
    
    // Play background music
    Resource resource("Assets/BlockDropperMenuMusic.mp3");
    std::shared_ptr<SoundResourceExtraData> soundData = std::make_shared<SoundResourceExtraData>();
    soundData->Initialize(SOUND_TYPE_MP3, false);
    std::shared_ptr<ResourceHandle> handle = std::make_shared<ResourceHandle>(resource, 0);
    handle->SetExtra(soundData);
    IAudioBuffer* music = g_pAudio->VInitAudioBuffer(handle);
    music->VPlay(1, true);
    
    return successful;
}

//
// Update menu items and check for button clicks
//
void MainMenuView::VUpdate()
{
    HumanView::VUpdate();
    VRender();
    
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
