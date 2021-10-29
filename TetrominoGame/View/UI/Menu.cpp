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
    if (m_pUserInputTimer->GetTicks() > 350)
    {
        if (keyStates[SDL_SCANCODE_DOWN])
        {
            m_pUserInputTimer->Start();
            mMenuOptions[mActiveMenuOption]->VSetFocus(false);
            mActiveMenuOption = (mActiveMenuOption + 1) % mMenuOptions.size();
        }
        else if (keyStates[SDL_SCANCODE_UP])
        {
            m_pUserInputTimer->Start();
            mMenuOptions[mActiveMenuOption]->VSetFocus(false);
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
    mHeight = 0;
    mWidth = 30;
    int maxWidth = 0;
    for (const UIElementPointer &element : mMenuOptions)
    {
        maxWidth = element->VGetWidth() > maxWidth ? element->VGetWidth() : maxWidth;
        mHeight += element->VGetHeight() + 15;
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
    //printf("RemoveMenuOption not implemented");
}


//
//
//
MenuButtonUI::MenuButtonUI(std::string text, bool filled) : mButtonText(text), mIsFilled(filled)
{
    mColor = { 0x00, 0x00, 0xFF };
    mFontSize = 16;
    
    // Initialize font
    m_pButtonFont = TTF_OpenFont("Assets/PTC55F.ttf", mFontSize);
    if (m_pButtonFont == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }
}

//
// Close font of button
//
MenuButtonUI::~MenuButtonUI()
{
    if (m_pButtonFont)
        TTF_CloseFont(m_pButtonFont);
}


//
//
//
void MenuButtonUI::VUpdate()
{

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
    if (m_pButtonFont == NULL)
    {
        printf("Button font not loaded! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }
    
    // Color of text should be same as rectangle if not filled, otherwise should be white or black
    SDL_Color white = {0xEE, 0x00, 0xFF, 0xFF};
    SDL_Color textColor = mIsFilled ? white : mColor;
    
    SDL_Surface* textSurface = TTF_RenderText_Blended(m_pButtonFont, mButtonText.c_str(), textColor);
    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }
    
    // Color key image
    SDL_SetColorKey(textSurface, SDL_TRUE, SDL_MapRGB(textSurface->format, 0xFF, 0xFF, 0xFF));

    // Create texture from surface pixels
    SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, textSurface);
    if (texture == NULL)
    {
        printf("Unable to create texture from %s! SDL Error: %s\n", mButtonText.c_str(), SDL_GetError());
    }
    else
    {
        int w = textSurface->w;
        int h = textSurface->h;
        SDL_Rect srcRect = { 0, 0, w, h };
        SDL_Rect destRect = { mPositionX + mWidth/2 - w/2, mPositionY + mHeight/2 - h/2, w, h };
        
        SDL_RenderCopy(pRenderer, texture, &srcRect, &destRect);
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(textSurface);
}
