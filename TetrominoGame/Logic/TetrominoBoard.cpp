//
//  TetrominoBoard.cpp
//  TetrominoGame
//
//  Created by John Geiger on 10/1/21.
//

#include "TetrominoBoard.hpp"

TetrominoBoard::~TetrominoBoard()
{
    //
}

//
// Initializes board, allocating Tetrominos
//
bool TetrominoBoard::Init()
{
    // Initialize board to blank spaces (FREE_POSITION)
    mBoard = Board(BOARD_WIDTH, std::vector<int>(BOARD_HEIGHT, FREE_POSITION));
    
    mBorderWidth = 6;
    
    return true;
}

//
// Translates the given x position to pixels
//
// Input: int `position` is the given x Position to translate.
//
int TetrominoBoard::GetXPositionInPixels(int position)
{
    return ((mBoardPosition - (BLOCK_SIZE * (BOARD_WIDTH / 2)) ) + (position * BLOCK_SIZE));
}

//
// Translates the given y position to pixels
//
// Input: int `position` is the given y Position to translate.
//
int TetrominoBoard::GetYPositionInPixels(int position)
{
    return ((mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (position * BLOCK_SIZE));
}

//
// Checks if block is free
//
// Input: `x` and `y` represents position of block.
//
bool TetrominoBoard::IsBlockFree(int x, int y)
{
    if (mBoard[x][y] != FREE_POSITION)
        return false;
    
    return true;
}

//
// Get the block number for the position
//
const int TetrominoBoard::GetBlockType(int x, int y)
{
    return mBoard[x][y];
}

//
// Checks if movement for given tetromino is possible
//
// Input: `tetromino` and `rotation` describe the piece being moved. `x` and `y` represent
//        the position the piece is moving to.
//
bool TetrominoBoard::IsPossibleMovement(int x, int y, Tetromino tetromino, Rotation rotation)
{
    // tetrominoX tracks position within tetromino piece; boardX tracks actual board position
    for (int boardX = x, tetrominoX = 0; boardX < x + PIECE_BLOCKS; boardX++, tetrominoX++)
    {
        for (int boardY = y, tetrominoY = 0; boardY < y + PIECE_BLOCKS; boardY++, tetrominoY++)
        {
            // Check if the piece is outside the limits of the board
            if (boardX < 0 || boardX > BOARD_WIDTH - 1 || boardY > BOARD_HEIGHT - 1)
            {
                if (Tetrominos::GetBlockType(tetromino, rotation, tetrominoY, tetrominoX) != 0)
                    return false;
            }

            // Check if the tetromino collides with a block already stored in the map
            if (boardY >= 0)
            {
                if ((Tetrominos::GetBlockType(tetromino, rotation, tetrominoY, tetrominoX) != 0) &&
                    (!IsBlockFree(boardX, boardY)) )
                    return false;
            }
        }
    }
    return true;
}

//
// Stores a tetromino in the board by filling in the appropriate blocks
//
// Input: `x` represents the x position of where the tetromino is going.
//        `y` represents the y position of where the tetromino is going.
//        `tetromino` is the tetromino we're storing, and `rotation` is its rotation.
//
void TetrominoBoard::StoreTetromino(int x, int y, Tetromino tetromino, Rotation rotation)
{
    // Store each block of the piece into the board
    for (int i = x, tetrominoY = 0; i < x + PIECE_BLOCKS; ++i, ++tetrominoY)
    {
        for (int j = y, tetrominoX = 0; j < y + PIECE_BLOCKS; ++j, ++tetrominoX)
        {
            // Store only the blocks of the piece that are not holes
            if (Tetrominos::GetBlockType(tetromino, rotation, tetrominoX, tetrominoY) != 0)
                mBoard[i][j] = tetromino;
        }
    }
}

//
// Deletes a single line on board
//
// Input: `y` is the row to be deleted.
//
void TetrominoBoard::DeleteLine(int y)
{
    for (int j = y; j > 0; --j)
    {
        for (int i = 0; i < BOARD_WIDTH; ++i)
        {
            mBoard[i][j] = mBoard[i][j-1];
        }
    }
}

//
// Deletes any lines that need deleting
//
// Returns: number of lines deleted.
int TetrominoBoard::DeletePossibleLines()
{
    int numberDeletedLines = 0;
    
    for (int j = 0; j < BOARD_HEIGHT; ++j)
    {
        bool deleteRow = true;
        for (int i = 0; i < BOARD_WIDTH; ++i)
        {
            if (mBoard[i][j] == FREE_POSITION)
            {
                deleteRow = false;
                break;
            }
        }
        
        if (deleteRow == true)
        {
            DeleteLine(j);
            ++numberDeletedLines;
        }
    }
    return numberDeletedLines;
}

//
// Checks if game is over
//
bool TetrominoBoard::IsGameOver()
{
    for (int i = 0; i < BOARD_WIDTH; ++i)
    {
        if (mBoard[i][0] != FREE_POSITION)
            return true;
    }
    
    return false;
}

