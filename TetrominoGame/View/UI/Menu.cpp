//
//  Menu.cpp
//  TetrominoGame
//
//  Created by John Geiger on 10/24/21.
//

#include "Menu.hpp"
#include "SDLRenderer.hpp"

MainMenuUI::MainMenuUI()
{
    // First option is active by default
    mActiveMenuOption = 0;
    
    m_pUserInputTimer = std::make_shared<Timer>();
    m_pUserInputTimer->Start();
    
    mMenuOptions = { };
}

MainMenuUI::~MainMenuUI()
{
    m_pUserInputTimer->Stop();
    mMenuOptions.clear();
}

void MainMenuUI::VUpdate()
{
    if (mMenuOptions.size() == 0)
        return;
    
    // Check keystates
    const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
    
    // Only check down/up input if 300 ms has passed since last input
    if (m_pUserInputTimer->GetTicks() > 150)
    {
        if (keyStates[SDL_SCANCODE_DOWN])
        {
            m_pUserInputTimer->Start();
            mMenuOptions[mActiveMenuOption]->VSetFocus(false);
            mMenuOptions[mActiveMenuOption]->VUpdate();
            mActiveMenuOption = (mActiveMenuOption + 1) % mMenuOptions.size();
        }
        else if (keyStates[SDL_SCANCODE_UP])
        {
            m_pUserInputTimer->Start();
            mMenuOptions[mActiveMenuOption]->VSetFocus(false);
            mMenuOptions[mActiveMenuOption]->VUpdate();
            mActiveMenuOption = (mActiveMenuOption - 1) % mMenuOptions.size();
        }
        
        mMenuOptions[mActiveMenuOption]->VSetFocus(true);
    }
    
    if (keyStates[SDL_SCANCODE_RETURN] || keyStates[SDL_SCANCODE_SPACE])
        mMenuOptions[mActiveMenuOption]->VSetSelect(true);
    
    for (const UIElementPointer &element : mMenuOptions)
    {
        element->VUpdate();
    }
}

//
// Render menu itself and each menu option
//
void MainMenuUI::VRender()
{
    // Update the width and height of menu based on options (with built-in margins)
    mHeight = VERTICAL_BUTTON_MARGINS;
    mWidth = HORIZONTAL_BUTTON_MARGINS * 2;
    int maxWidth = 0;
    for (const UIElementPointer &element : mMenuOptions)
    {
        maxWidth = element->VGetWidth() > maxWidth ? element->VGetWidth() : maxWidth;
        mHeight += element->VGetHeight() + VERTICAL_BUTTON_MARGINS;
    }
    mWidth += maxWidth;
    
    SDL_Rect menuRect = { mPositionX, mPositionY, mWidth, mHeight };
    
    SDL_SetRenderDrawColor(g_pRenderer->GetRenderer(), 0x00, 0x00, 0xFF, 0xFF);
    SDL_RenderDrawRect(g_pRenderer->GetRenderer(), &menuRect);
    
    for (const UIElementPointer &element : mMenuOptions)
    {
        element->VRender();
    }
}

void MainMenuUI::AddMenuOption(UIElementPointer screenElement)
{
    if (screenElement != NULL)
        mMenuOptions.push_back(screenElement);
}

void MainMenuUI::RemoveMenuOption(UIElementPointer screenElement)
{
    // FIXME: implement
}


//
//
//
MenuButtonUI::MenuButtonUI(std::string text) : mButtonText(text)
{
    mColor = { 0x00, 0x00, 0xFF };
    m_pTextTexture = NULL;
    
    LoadButtonText();
}

//
// Close font of button
//
MenuButtonUI::~MenuButtonUI()
{
    m_pTextTexture = NULL;
}

//
// Does loading of text texture as needed
//
void MenuButtonUI::LoadButtonText()
{
    m_pTextTexture = std::make_shared<SDLTextTexture>(mButtonText, 24);
    
    // Color of text should be same as rectangle if not filled, otherwise should be black
    m_bHasFocus ? m_pTextTexture->VSetColor(0x00, 0x00, 0x00) : m_pTextTexture->VSetColor(mColor.r, mColor.g, mColor.b);
}


//
// Makes updates to button based on its state
//
void MenuButtonUI::VUpdate()
{
    // Color of text should be same as rectangle if not filled, otherwise should be black
    m_bHasFocus ? m_pTextTexture->VSetColor(0x00, 0x00, 0x00) : m_pTextTexture->VSetColor(mColor.r, mColor.g, mColor.b);
}

//
// Draw button and text with padding
//
void MenuButtonUI::VRender()
{
    SDL_SetRenderDrawColor(g_pRenderer->GetRenderer(), mColor.r, mColor.g, mColor.b, mColor.a);
    
    // Render button rectangle
    SDL_Rect buttonRect = { mPositionX, mPositionY, mWidth, mHeight };
    
    if (m_bHasFocus)
        SDL_RenderFillRect(g_pRenderer->GetRenderer(), &buttonRect);
    else
        SDL_RenderDrawRect(g_pRenderer->GetRenderer(), &buttonRect);
    
    VDrawText();
}

//
// Draw button text
//
void MenuButtonUI::VDrawText()
{
    int w = m_pTextTexture->GetWidth();
    int h = m_pTextTexture->GetHeight();
    Point position = Point(mPositionX + mWidth/2 - w/2, mPositionY + mHeight/2 - h/2);
    m_pTextTexture->SetPosition(position);
    m_pTextTexture->VRender();
}
