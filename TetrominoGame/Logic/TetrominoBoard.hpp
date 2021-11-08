//
//  TetrominoBoard.hpp
//  TetrominoGame
//
//  Created by John Geiger on 10/1/21.
//
#pragma once

#ifndef TetrominoBoard_hpp
#define TetrominoBoard_hpp

#include "Tetrominos.hpp"

#define BOARD_WIDTH 10 // Board width in blocks
#define BOARD_HEIGHT 20 // Board height in blocks
#define BLOCK_SIZE 16 // Width and Height of each block of a piece in pixels
#define PIECE_BLOCKS 5 // Number of horizontal and vertical blocks of a matrix piece

//
// Defines the game board for the Tetromino Game
//
class TetrominoBoard
{
    using Board = std::vector<std::vector<int>>;
    
public:
    TetrominoBoard(int screenHeight, int boardPosition = 320) : mScreenHeight(screenHeight), mBoardPosition(boardPosition) { };
    ~TetrominoBoard();
    
    bool Init();
    
    int GetXPositionInPixels(int position);
    int GetYPositionInPixels(int position);
    int GetBorderWidthInPixels() { return mBorderWidth; };
    int GetBoardPositionInPixels() { return mBoardPosition; };
    
    bool IsBlockFree(int x, int y);
    bool IsPossibleMovement(int x, int y, TetrominoType tetromino, Rotation rotation);
    
    void StoreTetromino(int x, int y, TetrominoType tetromino, Rotation rotation);
    const int GetBlockType(int x, int y);
    
    int DeletePossibleLines();
    bool IsGameOver();
    
private:
    enum { FREE_POSITION = -2 };
    int mScreenHeight;
    
    Board mBoard;
    int mBoardPosition;    // Center position of the board from the left of the screen
    int mBorderWidth;      // Width of each of the two lines that delimit the board
    
    void DeleteLine(int y);
    
};

#endif /* TetrominoBoard_hpp */
