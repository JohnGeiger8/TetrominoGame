//
//  TetrominoLogic.cpp
//  TetrominoGame
//
//  Created by John Geiger on 10/1/21.
//

#include "TetrominoLogic.hpp"

//
// Creates TetrominoLogic with given screen height
//
// Input: `screenHeight` specifies the height of the screen.
//
TetrominoLogic::TetrominoLogic(int screenHeight)
{
    m_pBoard = NULL;
    m_pGameView = NULL;
    mGameCycleTimer = NULL;
    
    mScreenHeight = screenHeight;
    mIsPaused = false;
    mIsGameOver = false;
    mDropTime = PIECE_DROP_START_TIME;
    
    mXPosition = 0; mYPosition = 0;
    mNextXPosition = 0; mNextYPosition = 0;
    mTetromino = 0;
    mRotation = 0;
    mNextTetromino = 0;
    mNextRotation = 0;
}

//
// Initializes the systems of TetrominoLogic
//
// Returns: true if initialization succeeds.
//
bool TetrominoLogic::Init(SDL_Window* pWindow)
{
    // Initialize the Board and pieces
    m_pBoard = std::make_shared<TetrominoBoard>(mScreenHeight);
    if (!m_pBoard->Init())
    {
        printf("Game Board failed initialization failed.");
        return false;
    }
    
    // Initialize the tetrominos
    srand((unsigned int) time(NULL));
    mTetromino = GetRandomNumber(0, 6);
    mRotation = GetRandomNumber(0, 3);
    mXPosition = (BOARD_WIDTH / 2) + Tetrominos::GetInitialPositionX(mTetromino, mRotation);
    mYPosition = Tetrominos::GetInitialPositionY(mTetromino, mRotation);
    
    // Next piece
    mNextTetromino = GetRandomNumber(0, 6);
    mNextRotation = GetRandomNumber(0, 3);
    mNextXPosition = BOARD_WIDTH + 5;
    mNextYPosition = 5;
        
    // Initialize Game View
    m_pGameView = std::make_shared<TetrominoView>();
    if (!m_pGameView->Init(m_pBoard, pWindow))
    {
        printf("Error: Game View Initialization failed.");
        return false;
    }
    
    mGameCycleTimer = std::make_shared<Timer>();
    mGameCycleTimer->Start();
    
    m_pTetrominoMovementTimer = std::make_shared<Timer>();

    return true;
}

//
// Run when user wants to quit
//
void TetrominoLogic::Shutdown()
{
    m_pGameView->Shutdown();
//    delete(mGameCycleTimer);
//    mGameCycleTimer = NULL;
    mIsGameOver = true;
}

//
// Updates the Tetromino Logic. Called each frame
//
void TetrominoLogic::OnUpdate(SDL_Event* event)
{
    switch (event->type) {
        case SDL_QUIT:
            Shutdown();
            return;
        case SDL_KEYDOWN:
            if (m_pTetrominoMovementTimer->IsStarted() && m_pTetrominoMovementTimer->GetTicks() < PIECE_MOVE_TIME)
                break;
            
            const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
            
            if (keyStates[SDL_SCANCODE_LEFT])
            {
                if (m_pBoard->IsPossibleMovement(mXPosition - 1, mYPosition, mTetromino, mRotation))
                    mXPosition--;
            }
            else if (keyStates[SDL_SCANCODE_RIGHT])
            {
                if (m_pBoard->IsPossibleMovement(mXPosition + 1, mYPosition, mTetromino, mRotation))
                    mXPosition++;
            }
            else if (keyStates[SDL_SCANCODE_DOWN])
            {
                if (m_pBoard->IsPossibleMovement(mXPosition, mYPosition + 1, mTetromino, mRotation))
                    mYPosition++;
            }
            else if (keyStates[SDL_SCANCODE_X])
            {
                while (m_pBoard->IsPossibleMovement(mXPosition, mYPosition + 1, mTetromino, mRotation))
                {
                    mYPosition++;
                }
                
                m_pBoard->StoreTetromino(mXPosition, mYPosition, mTetromino, mRotation);
                
                m_pBoard->DeletePossibleLines();
                
                if (m_pBoard->IsGameOver())
                {
                    Shutdown();
                }
                else
                {
                    CreateNewTetromino();
                }
            }
            else if (keyStates[SDL_SCANCODE_Z])
            {
                if (m_pBoard->IsPossibleMovement(mXPosition, mYPosition, mTetromino, (mRotation + 1) % 4))
                    mRotation = (mRotation + 1) % 4;
            }
            else if (keyStates[SDL_SCANCODE_P])
            {
                if (mGameCycleTimer->IsPaused())
                {
                    mGameCycleTimer->Unpause();
                    mIsPaused = false;
                }
                else
                {
                    mGameCycleTimer->Pause();
                    mIsPaused = true;
                }
            }
            
            m_pGameView->Update();
            m_pGameView->DrawPiece(mXPosition, mYPosition, mTetromino, mRotation);
            m_pGameView->DrawPiece(mNextXPosition, mNextYPosition, mNextTetromino, mNextRotation);
            m_pGameView->Render();
            
            m_pTetrominoMovementTimer->Start();
            
            break;
    }
    
    if (!mIsPaused)
    {
        Uint32 time = mGameCycleTimer->GetTicks();

        if (time >= mDropTime) // Move the piece down if possible
        {
            if (m_pBoard->IsPossibleMovement(mXPosition, mYPosition + 1, mTetromino, mRotation))
            {
                mYPosition++;
                mGameCycleTimer->Start();
            }
            else
            {
                m_pBoard->StoreTetromino(mXPosition, mYPosition, mTetromino, mRotation);
                
                m_pBoard->DeletePossibleLines();
                
                if (m_pBoard->IsGameOver())
                {
                    Shutdown();
                    return;
                }
                
                CreateNewTetromino();
                mGameCycleTimer->Start();
            }
            m_pGameView->Update();
            m_pGameView->DrawPiece(mXPosition, mYPosition, mTetromino, mRotation);
            m_pGameView->DrawPiece(mNextXPosition, mNextYPosition, mNextTetromino, mNextRotation);
            m_pGameView->Render();
        }
    }
}

//
// Creates a new Tetromino
//
void TetrominoLogic::CreateNewTetromino()
{
    // New Tetromino
    mTetromino = mNextTetromino;
    mRotation = mNextRotation;
    mXPosition = (BOARD_WIDTH / 2) + Tetrominos::GetInitialPositionX(mTetromino, mRotation);
    mYPosition = Tetrominos::GetInitialPositionY(mTetromino, mRotation);
    
    // FIXME: should these just be vectors/queues/lists?
    
    // Next tetromino
    mNextTetromino = GetRandomNumber(0, 6);
    mNextRotation = GetRandomNumber(0, 3);
}

//
// Creates a random number between `a` and `b`
//
// Input: Range of random number, from `a` to `b`.
// Returns: Random number generated.
//
int TetrominoLogic::GetRandomNumber(int a, int b)
{
    return (rand() % (b - a + 1) + a);
}
