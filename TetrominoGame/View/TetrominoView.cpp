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
    m_pFonts = std::vector<TTF_Font*>();
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
    
    if(TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }
    
    mDefaultFontPath = "Assets/PTC55F.ttf";

    return success;
}

//
// Run SDL Destroy functions for renderer and window
//
void TetrominoView::Shutdown()
{
    SDL_DestroyRenderer(m_pRenderer);
    m_pRenderer = NULL;
    
    for (auto it = m_pFonts.begin(); it < m_pFonts.end(); ++it)
    {
        TTF_CloseFont(*it);
    }
    
    TTF_Quit();
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
// Draws text
//
// Input: `text` is the string to be drawn.
//        `renderRectangle` is the center of where the text should be.
//        `textColor` is the color of the text to be drawn.
//        `fontSize` is the font size of the text.
//        `fontPath` is the path to the font to be used for drawing.
//        The final three parameters are optional.
//
void TetrominoView::DrawText(std::string text, SDL_Rect* renderRectangle, SDL_Color textColor, int fontSize, std::string fontPath)
{
    int w, h;
    TTF_Font* pFont;
    
    // Open the font if given
    if (fontPath == "")
        pFont = TTF_OpenFont(mDefaultFontPath.c_str(), fontSize);
    else
        pFont = TTF_OpenFont(fontPath.c_str(), fontSize);
    
    if (pFont == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }
    
    m_pFonts.push_back(pFont);
    
    SDL_Surface* textSurface = TTF_RenderText_Blended(pFont, text.c_str(), textColor);
    if (textSurface == NULL)
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey(textSurface, SDL_TRUE, SDL_MapRGB(textSurface->format, 0xFF, 0xFF, 0xFF));

        //Create texture from surface pixels
        SDL_Texture* texture = SDL_CreateTextureFromSurface(m_pRenderer, textSurface);
        if(texture == NULL)
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
            
            SDL_RenderCopy(m_pRenderer, texture, &srcRect, renderRectangle);
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(textSurface);
    }
}

//
// Present everything drawn
//
void TetrominoView::Render()
{
    SDL_RenderPresent(m_pRenderer);
}
