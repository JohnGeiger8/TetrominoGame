//
//  TetrominoLogic.hpp
//  TetrominoGame
//
//  Created by John Geiger on 10/1/21.
//
#pragma once

#ifndef TetrominoLogic_hpp
#define TetrominoLogic_hpp

#include <time.h>
#include "TetrominoBoard.hpp"
#include "Tetrominos.hpp"
#include "TetrominoView.hpp"
#include "Timer.hpp"

#define PIECE_MOVE_TIME 200 // Time until movement events should be run again
#define PIECE_DROP_START_TIME 700 // Time until piece drops a block


//
// Handles all the game logic
//
class TetrominoLogic
{
public:
    TetrominoLogic(int screenHeight);
    
    bool Init();
    void Shutdown();
    void OnUpdate(SDL_Event* event);
    
    bool IsGameOver() { return mIsGameOver; };

    void CreateNewTetromino();

private:
    int GetRandomNumber(int pA, int pB);

    std::shared_ptr<TetrominoBoard> m_pBoard;
    std::shared_ptr<TetrominoView> m_pGameView;
    
    int mScreenHeight;
    bool mIsPaused;
    bool mIsGameOver;
    int mDropTime; // Time between each piece dropping
    int mXPosition, mYPosition; // Position of the piece that is falling down
    int mNextXPosition, mNextYPosition; // Position of the next piece
    Tetromino mTetromino; // Type of piece that is falling down
    Rotation mRotation; // Rotation of the piece that is falling down
    Tetromino mNextTetromino; // Type of the next piece
    Rotation mNextRotation; // Rotation of the next piece
    std::shared_ptr<Timer> mGameCycleTimer; // Timer tracking Tetromino drop cycle
    std::shared_ptr<Timer> m_pTetrominoMovementTimer; // Timer tracking how long since the user's piece moved
};

#endif /* TetrominoLogic_hpp */
