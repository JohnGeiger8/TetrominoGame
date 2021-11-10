//
//  HumanView.cpp
//  TetrominoGame
//
//  Created by John Geiger on 10/26/21.
//

#include <SDL2_ttf/SDL_ttf.h>
#include "HumanView.hpp"
#include "SDLRenderer.hpp"

HumanView::HumanView()
{
//    mScreenElements = NULL;
}

HumanView::~HumanView()
{
}

//
// Initialize screen element list
//
bool HumanView::VInit()
{
    bool successful = true;
    
    mScreenElements = ScreenElementList();
    
    return successful;
}

//
// Clears all elements or sets to null
//
void HumanView::VShutdown()
{
    mScreenElements.clear();
    mKeyboardHandler = NULL;
}


//
// Update all screen elements
//
void HumanView::VUpdate()
{
    for (ScreenElementPointer &pElement : mScreenElements)
    {
        pElement->VUpdate();
    }
}

//
// Render all screen elements that are visible
//
void HumanView::VRender()
{
    SDL_SetRenderDrawColor(g_pRenderer->GetRenderer(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(g_pRenderer->GetRenderer());

    for (ScreenElementPointer &pElement : mScreenElements)
    {
        if (pElement->VIsVisible())
            pElement->VRender();
    }
    SDL_RenderPresent(g_pRenderer->GetRenderer());
}

//
// Draw text
//
// FIXME: how to properly use this? this implementation isn't really right anyway, need to close font somewhere
//
void HumanView::VDrawText(std::string text, SDL_Rect* renderRectangle, SDL_Color textColor, int fontSize, std::string fontPath)
{
    int w, h;
    TTF_Font* pFont;

    // Open the font if given
    if (fontPath == "")
        return;
    else
        pFont = TTF_OpenFont(fontPath.c_str(), fontSize);

    if (pFont == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Surface* textSurface = TTF_RenderText_Blended(pFont, text.c_str(), textColor);
    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }
    //Color key image
    SDL_SetColorKey(textSurface, SDL_TRUE, SDL_MapRGB(textSurface->format, 0xFF, 0xFF, 0xFF));

    //Create texture from surface pixels
    SDL_Texture* texture = SDL_CreateTextureFromSurface(g_pRenderer->GetRenderer(), textSurface);
    if (texture == NULL)
    {
        printf("Unable to create texture from %s! SDL Error: %s\n", text.c_str(), SDL_GetError());
    }
    else
    {
        w = textSurface->w;
        h = textSurface->h;
        SDL_Rect srcRect = { 0, 0, w, h };
        
        renderRectangle->h = h;
        renderRectangle->w = w;
        renderRectangle->x -= w/2; // Convert center to top left
        
        SDL_RenderCopy(g_pRenderer->GetRenderer(), texture, &srcRect, renderRectangle);
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(textSurface);
}

//
// Process SDL Event messages
//
void HumanView::VProcessMessages(SDL_Event* pEvent)
{
    switch (pEvent->type)
    {
        case SDL_KEYDOWN:
            if (mKeyboardHandler)
                mKeyboardHandler->VOnKeyDown(pEvent->key.keysym.sym);
            break;
            
        case SDL_KEYUP:
            if (mKeyboardHandler)
                mKeyboardHandler->VOnKeyUp(pEvent->key.keysym.sym);
            break;
            
        case SDL_QUIT:
            VShutdown();
            break;
            
        default:
            break;
    }
}

//
// Push IScreenElement to the list
//
void HumanView::VPushElement(ScreenElementPointer pElement)
{
    mScreenElements.push_front(pElement);
}

//
// Remove IScreenElement from the list
//
void HumanView::VRemoveElement(ScreenElementPointer pElement)
{
    mScreenElements.remove(pElement);
}
