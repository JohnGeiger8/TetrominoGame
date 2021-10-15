//
//  TetrominoView.cpp
//  TetrominoGame
//
//  Created by John Geiger on 10/1/21.
//

#include "TetrominoView.hpp"

TetrominoView::TetrominoView()
{
    m_pRenderer = NULL;
    m_pBoard = NULL;
}

//
// Initialize the systems of the Tetromino View
//
// Input: `pBoard` points to the TetrominoBoard we'll be displaying.
//
// Returns: true if successful.
//
bool TetrominoView::Init(std::shared_ptr<TetrominoBoard> pBoard, SDL_Window* pWindow)
{
    bool success = true;
    
    m_pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    if(m_pRenderer == NULL)
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        SDL_SetRenderDrawColor( m_pRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    }
    
    m_pBoard = pBoard;
    if (m_pBoard == NULL)
    {
        printf("Board not initialized.");
        success = false;
    }

    return success;
}

//
// Run SDL Destroy functions for renderer and window
//
void TetrominoView::Shutdown()
{
    SDL_DestroyRenderer(m_pRenderer);
    m_pRenderer = NULL;
}

//
// Updates the view, looping through the board and drawing everything
//
void TetrominoView::Update()
{
    // Clear screen
    SDL_SetRenderDrawColor(m_pRenderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(m_pRenderer);
}

//
// Draws a rectangle using SDL
//
// Input:
//
void TetrominoView::DrawRectangle(int xPositionPixels, int yPositionPixels, int width, int height, SDL_Color color, bool isFilled)
{
    SDL_Rect rectangle = { xPositionPixels, yPositionPixels, width, height };
    SDL_SetRenderDrawColor(m_pRenderer, color.r, color.g, color.b, color.a);
    if (isFilled)
        SDL_RenderFillRect(m_pRenderer, &rectangle);
    else
        SDL_RenderDrawRect(m_pRenderer, &rectangle);
}

//
// Present everything drawn
//
void TetrominoView::Render()
{
    SDL_RenderPresent(m_pRenderer);
}
