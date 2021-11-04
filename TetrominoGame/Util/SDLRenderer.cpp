//
//  SDLRenderer.cpp
//  TetrominoGame
//
//  Created by John Geiger on 10/13/21.
//

#include "SDLRenderer.hpp"

//
// Create SDL_Renderer, and set the global renderer to it if applicable
//
SDLRenderer::SDLRenderer(SDL_Window* pWindow)
{
    m_pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    if(m_pRenderer == NULL)
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
    }
    else
    {
        SDL_SetRenderDrawColor( m_pRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    }
}

SDLRenderer::~SDLRenderer()
{
    SDL_DestroyRenderer(m_pRenderer);
    m_pRenderer = NULL;
    
    if (g_pRenderer.get() == this)
        g_pRenderer = NULL;
}
