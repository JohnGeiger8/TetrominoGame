//
//  TetrominoView.cpp
//  TetrominoGame
//
//  Created by John Geiger on 10/1/21.
//

#include "TetrominoView.hpp"
#include "SDLRenderer.hpp"

TetrominoView::TetrominoView()
{
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
bool TetrominoView::Init(std::shared_ptr<TetrominoBoard> pBoard)
{
    bool success = true;
        
    m_pBoard = pBoard;
    if (m_pBoard == NULL)
    {
        printf("Board not initialized.");
        success = false;
    }
    
    mDefaultFontPath = "Assets/PTC55F.ttf";

    return success;
}

//
// Close all fonts in use
//
void TetrominoView::Shutdown()
{
    for (auto it = m_pFonts.begin(); it < m_pFonts.end(); ++it)
    {
        TTF_CloseFont(*it);
    }
    m_pFonts.clear();
}

//
// Updates the view, looping through the board and drawing everything
//
void TetrominoView::Update()
{
    // Clear screen
    SDL_SetRenderDrawColor(g_pRenderer->GetRenderer(), 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(g_pRenderer->GetRenderer());
}

//
// Draws a rectangle using SDL
//
// Input: `xPositionPixels` is the top left x coordinate of the rectangle.
//        `yPositionPixels` is the top left y coordinate of the rectangle.
//        `width` and `height` are the width and height of the rectangle.
//        `color` is the color and `isFilled` determines if the rectangle
//        should be solid or not. Both are optional.
//
void TetrominoView::DrawRectangle(int xPositionPixels, int yPositionPixels, int width, int height, SDL_Color color, bool isFilled)
{
    SDL_Rect rectangle = { xPositionPixels, yPositionPixels, width, height };
    SDL_SetRenderDrawColor(g_pRenderer->GetRenderer(), color.r, color.g, color.b, color.a);
    if (isFilled)
        SDL_RenderFillRect(g_pRenderer->GetRenderer(), &rectangle);
    else
        SDL_RenderDrawRect(g_pRenderer->GetRenderer(), &rectangle);
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
// Present everything drawn
//
void TetrominoView::Render()
{
    SDL_RenderPresent(g_pRenderer->GetRenderer());
}
