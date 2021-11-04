//
//  Menu.cpp
//  TetrominoGame
//
//  Created by John Geiger on 10/24/21.
//

#include "Menu.hpp"

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
void MainMenuUI::VRender(SDL_Renderer* pRenderer)
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
    
    SDL_SetRenderDrawColor(pRenderer, 0x00, 0x00, 0xFF, 0xFF);
    SDL_RenderDrawRect(pRenderer, &menuRect);
    
    for (const UIElementPointer &element : mMenuOptions)
    {
        element->VRender(pRenderer);
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
    mFontSize = 24;
    m_pButtonFont = NULL;
    m_pTextTexture = NULL;
    m_pTextSurface = NULL;
    
    LoadButtonText();
}

//
// Close font of button
//
MenuButtonUI::~MenuButtonUI()
{
    SDL_DestroyTexture(m_pTextTexture);
    m_pTextTexture = NULL;
    
    SDL_FreeSurface(m_pTextSurface);
    m_pTextSurface = NULL;
    
    TTF_CloseFont(m_pButtonFont);
    m_pButtonFont = NULL;
}

//
// Does loading of text texture as needed
//
void MenuButtonUI::LoadButtonText()
{
    if (!m_pButtonFont)
        m_pButtonFont = TTF_OpenFont("Assets/PTC55F.ttf", mFontSize);
    
    if (m_pButtonFont == NULL)
    {
        printf("Button font not loaded! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }
    
    // Color of text should be same as rectangle if not filled, otherwise should be black
    SDL_Color black = { 0x00, 0x00, 0x00, 0xFF };
    SDL_Color textColor = m_bHasFocus ? black : mColor;
    
    // If the surface is already allocated, free the old one first
    if (m_pTextSurface)
        SDL_FreeSurface(m_pTextSurface);
    m_pTextSurface = TTF_RenderText_Blended(m_pButtonFont, mButtonText.c_str(), textColor);
    
    if (m_pTextSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }
    
    // Color key image
    SDL_SetColorKey(m_pTextSurface, SDL_TRUE, SDL_MapRGB(m_pTextSurface->format, 0xFF, 0xFF, 0xFF));
}


//
//
//
void MenuButtonUI::VUpdate()
{
    LoadButtonText();
}

//
// Draw button and text with padding
//
void MenuButtonUI::VRender(SDL_Renderer* pRenderer)
{
    SDL_SetRenderDrawColor(pRenderer, mColor.r, mColor.g, mColor.b, mColor.a);
    
    // Render button rectangle
    SDL_Rect buttonRect = { mPositionX, mPositionY, mWidth, mHeight };
    
    if (m_bHasFocus)
        SDL_RenderFillRect(pRenderer, &buttonRect);
    else
        SDL_RenderDrawRect(pRenderer, &buttonRect);
    
    VDrawText(pRenderer);
}

//
// Draw button text
//
void MenuButtonUI::VDrawText(SDL_Renderer* pRenderer)
{
    // Create texture from surface pixels
    m_pTextTexture = SDL_CreateTextureFromSurface(pRenderer, m_pTextSurface);
    if (m_pTextTexture == NULL)
    {
        printf("Unable to create texture from %s! SDL Error: %s\n", mButtonText.c_str(), SDL_GetError());
    }
    
    int w = m_pTextSurface->w;
    int h = m_pTextSurface->h;
    SDL_Rect srcRect = { 0, 0, w, h };
    SDL_Rect destRect = { mPositionX + mWidth/2 - w/2, mPositionY + mHeight/2 - h/2, w, h };
    
    SDL_RenderCopy(pRenderer, m_pTextTexture, &srcRect, &destRect);
}
