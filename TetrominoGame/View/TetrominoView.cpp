//
//  TetrominoView.cpp
//  TetrominoGame
//
//  Created by John Geiger on 10/1/21.
//

#include "TetrominoView.hpp"
#include "CVar.hpp"
#include "SDLRenderer.hpp"

TetrominoView::TetrominoView()
{
    m_pBoard = NULL;
    m_pTetromino = NULL;
    m_pStashedTetromino = NULL;
    m_pNextTetrominos = NULL;
    m_pFonts = std::vector<TTF_Font*>();
}

//
// Initialize the systems of the Tetromino View, including the board and fonts
//
// Input: `pBoard` points to the TetrominoBoard we'll be displaying.
//
// Returns: true if successful.
//
bool TetrominoView::VInit(std::shared_ptr<TetrominoBoard> pBoard, TetrominoPointer pTetromino, TetrominoPointer pStashedTetromino, TetrominoList pNextTetrominos)
{
    bool success = true;
        
    m_pBoard = pBoard;
    if (m_pBoard == NULL)
    {
        printf("Board not initialized.");
        success = false;
    }
    
    m_pTetromino = pTetromino;
    if (m_pTetromino == NULL)
    {
        printf("Tetromino not initialized.");
        success = false;
    }
    
    m_pStashedTetromino = pStashedTetromino;
    if (m_pStashedTetromino == NULL)
    {
        printf("Stashed Tetromino not initialized.");
        success = false;
    }
    
    m_pNextTetrominos = pNextTetrominos;
    if (m_pNextTetrominos == NULL)
    {
        printf("Next Tetrominos not initialized.");
        success = false;
    }
    
    mDefaultFontPath = "Assets/ARCADECLASSIC.ttf";

    return success;
}

//
// Close all fonts in use
//
void TetrominoView::VShutdown()
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
void TetrominoView::VUpdate()
{
//    VRender();
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
// Draws the given piece at the given position
//
// Input: `x` and `y` represent the position the piece is being drawn to.
//        `tetromino` and `rotation` represent the piece we're drawing.
//
void TetrominoView::DrawPiece(int x, int y, TetrominoType tetromino, Rotation rotation)
{
    for (int boardX = x, tetrominoX = 0; boardX < x + PIECE_BLOCKS; boardX++, tetrominoX++)
    {
        for (int boardY = y, tetrominoY = 0; boardY < y + PIECE_BLOCKS; boardY++, tetrominoY++)
        {
            if (Tetrominos::GetBlockType(tetromino, rotation, tetrominoY, tetrominoX) != 0)
            {
                int xPositionPixels = m_pBoard->GetXPositionInPixels(boardX);
                int yPositionPixels = m_pBoard->GetYPositionInPixels(boardY);
                DrawRectangle(xPositionPixels + 1, yPositionPixels + 1, BLOCK_SIZE - 1, BLOCK_SIZE - 1, Tetrominos::GetTetrominoColor(tetromino));
            }
        }
    }
}

//
// Draw the Tetromino board
//
void TetrominoView::DrawBoard()
{
    int screenHeight = g_cvars.find("screenHeight")->second.GetIntValue();

    // Calculate the limits of the board in pixels
    int leftBorderX = m_pBoard->GetBoardPositionInPixels() - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
    int rightBorderX = m_pBoard->GetBoardPositionInPixels() + (BLOCK_SIZE * (BOARD_WIDTH / 2));
    int borderY = screenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

    // Rectangles that delimit the board
    SDL_Color blue = {0x00, 0x00, 0xFF, 0xFF};
    DrawRectangle(leftBorderX - m_pBoard->GetBorderWidthInPixels(), borderY, m_pBoard->GetBorderWidthInPixels(), screenHeight - 1, blue);
    DrawRectangle(rightBorderX, borderY, m_pBoard->GetBorderWidthInPixels(), screenHeight - 1, blue);

    // Draw blocks stored in board
    for (int i = 0; i < BOARD_WIDTH; ++i)
    {
        for (int j = 0; j < BOARD_HEIGHT; ++j)
        {
            if (!m_pBoard->IsBlockFree(i, j))
            {
                int xPositionPixels = m_pBoard->GetXPositionInPixels(i);
                int yPositionPixels = m_pBoard->GetYPositionInPixels(j);
                DrawRectangle(xPositionPixels + 1, yPositionPixels + 1, BLOCK_SIZE - 1, BLOCK_SIZE - 1, Tetrominos::GetTetrominoColor(m_pBoard->GetBlockType(i, j)));
            }
        }
    }
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
void TetrominoView::VDrawText(std::string text, SDL_Rect* renderRectangle, SDL_Color textColor, int fontSize, std::string fontPath)
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
void TetrominoView::VRender()
{
    int screenHeight = g_cvars.find("screenHeight")->second.GetIntValue();
    int screenWidth = g_cvars.find("screenWidth")->second.GetIntValue();
    int playerScore = g_cvars.find("playerScore")->second.GetIntValue();

    SDL_Rect titleRectangle = { screenWidth / 2, 10, 100, 100 };
    SDL_Rect scoreTextRectangle = { screenWidth / 2, 120, 100, 100 };
    SDL_Rect scoreRectangle = { scoreTextRectangle.x, scoreTextRectangle.y + 35, 100, 100 };
    SDL_Rect stashRectangle = { m_pBoard->GetBoardPositionInPixels() - (BOARD_WIDTH / 2) - 140, screenHeight - (BLOCK_SIZE * BOARD_HEIGHT), 100, 100 };
    SDL_Color textColor = { 0x00, 0xFF, 0xFF, 0xFF };
    
    // Clear screen
    SDL_SetRenderDrawColor(g_pRenderer->GetRenderer(), 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(g_pRenderer->GetRenderer());
    
    // Draw Board and pieces
    DrawBoard();
    DrawPiece(m_pTetromino->GetXPosition(), m_pTetromino->GetYPosition(), m_pTetromino->GetType(), m_pTetromino->GetRotation());
    
    // Draw next 3 pieces on right side of board
    for (int i = 0; i < NUMBER_PREVIEW_PIECES; ++i)
    {
        DrawPiece(m_pNextTetrominos->at(i)->GetXPosition(), m_pNextTetrominos->at(i)->GetYPosition(), m_pNextTetrominos->at(i)->GetType(), m_pNextTetrominos->at(i)->GetRotation());
    }
    
    // Draw stashed piece on left side of board
    VDrawText("S  to  stash", &stashRectangle, textColor, 16);
    if (m_pStashedTetromino->GetType() != -1)
        DrawPiece( -PIECE_BLOCKS - 1, 2, m_pStashedTetromino->GetType(), m_pStashedTetromino->GetRotation());
    
    VDrawText("BLOCK  DROPPER", &titleRectangle, textColor, 48);
    VDrawText("Score", &scoreTextRectangle, textColor, 32);
    VDrawText(std::to_string(playerScore), &scoreRectangle, textColor, 32);
    
    SDL_RenderPresent(g_pRenderer->GetRenderer());
}
