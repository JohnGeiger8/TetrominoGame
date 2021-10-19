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

#define BOARD_LINE_WIDTH 6 // Width of each of the two lines that delimit the board
#define BLOCK_SIZE 16 // Width and Height of each block of a piece
#define BOARD_POSITION 320 // Center position of the board from the left of the screen
#define BOARD_WIDTH 10 // Board width in blocks
#define BOARD_HEIGHT 20 // Board height in blocks
#define MIN_VERTICAL_MARGIN 20 // Minimum vertical margin for the board limit
#define MIN_HORIZONTAL_MARGIN 20 // Minimum horizontal margin for the board limit
#define PIECE_BLOCKS 5 // Number of horizontal and vertical blocks of a matrix piece

//
// Defines the game board for the Tetromino Game
//
class TetrominoBoard
{
    using Board = std::vector<std::vector<int>>;
    
public:
    TetrominoBoard(int screenHeight) : mScreenHeight(screenHeight) { };
    ~TetrominoBoard();
    
    bool Init();
    
    int GetXPositionInPixels(int position);
    int GetYPositionInPixels(int position);
    
    bool IsBlockFree(int x, int y);
    bool IsPossibleMovement(int x, int y, Tetromino tetromino, Rotation rotation);
    
    void StoreTetromino(int x, int y, Tetromino tetromino, Rotation rotation);
    const int GetBlockType(int x, int y);
    
    int DeletePossibleLines();
    bool IsGameOver();
    
private:
    enum { FREE_POSITION = -2 };
    Board mBoard;
    int mScreenHeight;
    
    void DeleteLine(int y);
    
};

#endif /* TetrominoBoard_hpp */
