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
#include "Initialization.hpp"
#include "TetrominoBoard.hpp"
#include "Tetromino.hpp"
#include "TetrominoView.hpp"
#include "Timer.hpp"

#define PIECE_MOVE_TIME 130 // Time until movement events should be run again
#define PIECE_DROP_START_TIME 700 // Time until piece drops a block

//
// Handles all the game logic
//
class TetrominoLogic
{
public:
    TetrominoLogic(GameOptions options);
    
    bool Init();
    void Shutdown();
    void OnUpdate(SDL_Event* event);
    void OnRender(); // Can/should this be private
    
    bool IsGameOver() { return m_bIsGameOver; };

    void CreateNewTetromino();

private:
    int GetRandomNumber(int pA, int pB);
    void StoreTetrominoAndReset();
    void StashTetromino();
    void UpdateScore(int numberDeletedLines);
    void DrawBoard();
    void DrawPiece(int x, int y, TetrominoType tetromino, Rotation rotation);

    std::shared_ptr<TetrominoBoard> m_pBoard;
    std::shared_ptr<TetrominoView> m_pGameView;
        
    bool m_bIsPaused;
    bool m_bIsGameOver;
    bool m_bHasStashed;
    
    GameOptions mOptions;
    int mDropTime; // Time between each piece dropping
    int mPlayerLevel;
    int mTotalNumberLinesDeleted;
    int mPlayerScore;
    
    TetrominoPointer m_pTetromino; // Piece that is falling down
    TetrominoPointer m_pStashedTetromino; // Piece that's stashed
    
    TetrominoList mNextTetrominos; // Types of the next 3 pieces
    std::shared_ptr<Timer> m_pGameSessionTimer; // Timer tracking how long the user has been playing session
    std::shared_ptr<Timer> mGameCycleTimer; // Timer tracking Tetromino drop cycle
    std::shared_ptr<Timer> m_pTetrominoMovementTimer; // Timer tracking how long since the user's piece moved
};

#endif /* TetrominoLogic_hpp */
