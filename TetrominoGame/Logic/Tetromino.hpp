//
//  Tetromino.hpp
//  TetrominoGame
//
//  Created by John Geiger on 11/7/21.
//
#pragma once

#ifndef Tetromino_hpp
#define Tetromino_hpp

#include <deque>
#include "Tetrominos.hpp"

class Tetromino
{
    int mX, mY;
    TetrominoType mTetromino;
    Rotation mRotation;
    
public:
    Tetromino(TetrominoType tetrominoType, Rotation rotation)
        : mTetromino(tetrominoType), mRotation(rotation) { mX = 0; mY = 0; };
    
    int GetXPosition() { return mX; };
    int GetYPosition() { return mY; };
    TetrominoType GetType() { return mTetromino; };
    Rotation GetRotation() { return mRotation; };
    
    void SetRotation(Rotation rotation) { mRotation = rotation; };
    void SetTetromino(TetrominoType type) { mTetromino = type; };
    void SetX(int x) { mX = x; };
    void SetY(int y) { mY = y; };
};

using TetrominoPointer = std::shared_ptr<Tetromino>;
using TetrominoList = std::shared_ptr<std::deque<TetrominoPointer>>;

#endif /* Tetromino_hpp */
