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
    
    DrawBoard();
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
// Draws the given piece at the given position
//
// Input: `x` and `y` represent the position the piece is being drawn to.
//        `tetromino` and `rotation` represent the piece we're drawing.
//
void TetrominoView::DrawPiece(int x, int y, Tetromino tetromino, Rotation rotation)
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
// Draws all rectangles currently stored in board
//
void TetrominoView::DrawBoard()
{
    // Calculate the limits of the board in pixels
    int leftBorderX = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
    int rightBorderX = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
    int borderY = SCREEN_HEIGHT - (BLOCK_SIZE * BOARD_HEIGHT);

    // Rectangles that delimit the board
    SDL_Color blue = {0x00, 0x00, 0xFF, 0xFF};
    DrawRectangle(leftBorderX - BOARD_LINE_WIDTH, borderY, BOARD_LINE_WIDTH, SCREEN_HEIGHT - 1, blue);
    DrawRectangle(rightBorderX, borderY, BOARD_LINE_WIDTH, SCREEN_HEIGHT - 1, blue);

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
void TetrominoView::Render()
{
    SDL_RenderPresent(m_pRenderer);
}
