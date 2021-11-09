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
    m_pScoreUI = NULL;
    mPlayerScore = 0;
}

//
// Initialize the systems of the Tetromino View, including the board
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
    
    // Initialize text UI items
    int screenHeight = g_cvars.find("screenHeight")->second.GetIntValue();
    int screenWidth = g_cvars.find("screenWidth")->second.GetIntValue();
    int playerScore = g_cvars.find("playerScore")->second.GetIntValue();

//    SDL_Rect stashRectangle = { m_pBoard->GetBoardPositionInPixels() - (BOARD_WIDTH / 2) - 140, screenHeight - (BLOCK_SIZE * BOARD_HEIGHT), 100, 100 };
    SDL_Color textColor = { 0x00, 0xFF, 0xFF, 0xFF };
    std::shared_ptr<TitleUI> pTitleUI = std::make_shared<TitleUI>("BLOCK DROPPER", 48, textColor);
    std::shared_ptr<TitleUI> pScoreTextUI = std::make_shared<TitleUI>("Score", 32, textColor);
    m_pScoreUI = std::make_shared<TitleUI>(std::to_string(playerScore), 32, textColor);
    std::shared_ptr<TitleUI> pStashUI = std::make_shared<TitleUI>("S  to  stash", 16, textColor);

    pTitleUI->VSetPositionX(screenWidth / 2);
    pTitleUI->VSetPositionY(pTitleUI->VGetHeight() + 15);
    pScoreTextUI->VSetPositionX(screenWidth / 2);
    pScoreTextUI->VSetPositionY(120);
    m_pScoreUI->VSetPositionX(screenWidth / 2);
    m_pScoreUI->VSetPositionY(pScoreTextUI->VGetPositionY() + 35);
    pStashUI->VSetPositionX(m_pBoard->GetBoardPositionInPixels() - (BOARD_WIDTH / 2) - 140);
    pStashUI->VSetPositionY(screenHeight - (BLOCK_SIZE * BOARD_HEIGHT));
    
    mScreenElements.push_back(pTitleUI);
    mScreenElements.push_back(pScoreTextUI);
    mScreenElements.push_back(m_pScoreUI);
    mScreenElements.push_back(pStashUI);
    
    return success;
}

//
// Reset everything
//
void TetrominoView::VShutdown()
{
    mPlayerScore = 0;
}

//
// Updates the view, looping through the board and drawing everything
//
void TetrominoView::VUpdate()
{
    int playerScore = g_cvars.find("playerScore")->second.GetIntValue();
    if (playerScore != mPlayerScore)
    {
        m_pScoreUI->VSetTitle(std::to_string(playerScore));
        mPlayerScore = playerScore;
    }
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
// Present everything drawn
//
void TetrominoView::VRender()
{
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
    if (m_pStashedTetromino->GetType() != -1)
        DrawPiece( -PIECE_BLOCKS - 1, 2, m_pStashedTetromino->GetType(), m_pStashedTetromino->GetRotation());
    
    // Draw UI and text elements
    for (ScreenElementPointer &pElement : mScreenElements)
    {
        if (pElement->VIsVisible())
            pElement->VRender();
    }
    
    SDL_RenderPresent(g_pRenderer->GetRenderer());
}
