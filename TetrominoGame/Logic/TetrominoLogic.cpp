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
    m_pGameSessionTimer = NULL;
    m_pTetrominoMovementTimer = NULL;
    
    mIsPaused = false;
    mIsGameOver = false;
    
    mScreenHeight = screenHeight;
    mDropTime = PIECE_DROP_START_TIME;
    mPlayerLevel = 1;
    mPlayerScore = 0;
    
    mNextXPositions = { };
    mNextYPositions = { };
    mNextTetrominos = { };
    mNextRotations = { };
    
    mXPosition = 0; mYPosition = 0;
    mTetromino = 0;
    mRotation = 0;
    
    mStashedTetromino = -1; // No tetromino there yet
    mStashedRotation = -1;
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
    
    // Next pieces
    for (int i = 0; i < NUMBER_PREVIEW_PIECES; ++i)
    {
        mNextTetrominos.push_back(GetRandomNumber(0, 6));
        mNextRotations.push_back(GetRandomNumber(0, 3));
        mNextXPositions.push_back(BOARD_WIDTH + 5);
        mNextYPositions.push_back(i * PIECE_BLOCKS);
    }
        
    // Initialize Game View
    m_pGameView = std::make_shared<TetrominoView>();
    if (!m_pGameView->Init(m_pBoard, pWindow))
    {
        printf("Error: Game View Initialization failed.");
        return false;
    }
    
    // Initialize each timer
    m_pGameSessionTimer = std::make_shared<Timer>();
    m_pGameSessionTimer->Start();
    
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
    mIsGameOver = true;
    m_pGameSessionTimer->Stop();
    m_pTetrominoMovementTimer->Stop();
    mGameCycleTimer->Stop();
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
            else if (keyStates[SDL_SCANCODE_S])
            {
                StashTetromino();
            }
            else if (keyStates[SDL_SCANCODE_X])
            {
                // Move piece straight down
                while (m_pBoard->IsPossibleMovement(mXPosition, mYPosition + 1, mTetromino, mRotation))
                {
                    mYPosition++;
                }
                
                // Restart game cycle to give user a chance to move piece sideways
                mGameCycleTimer->Start(); // FIXME: bug: user can spam x to avoid timer restarting
                OnRender();
                return;
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
            OnRender();
            
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
                StoreTetrominoAndReset();
            }
            OnRender();
        }
    }
}

//
// Does all of the rendering work
//
void TetrominoLogic::OnRender()
{
    SDL_Rect titleRectangle = { SCREEN_WIDTH / 2, 10, 100, 100 };
    SDL_Rect scoreRectangle = { SCREEN_WIDTH / 2, 120, 100, 100 };
    SDL_Rect stashRectangle = { BOARD_POSITION - (BOARD_WIDTH / 2) - 140, SCREEN_HEIGHT - (BLOCK_SIZE * BOARD_HEIGHT), 100, 100 };
    SDL_Color textColor = { 0x00, 0xFF, 0xFF, 0xFF };
    
    m_pGameView->Update();
    DrawBoard();
    DrawPiece(mXPosition, mYPosition, mTetromino, mRotation);
    
    // Draw next 3 pieces on right side of board
    for (int i = 0; i < NUMBER_PREVIEW_PIECES; ++i)
    {
        DrawPiece(mNextXPositions[i], mNextYPositions[i], mNextTetrominos[i], mNextRotations[i]);
    }
    
    // Draw stashed piece on left side of board
    m_pGameView->DrawText("Stashed [S]", &stashRectangle, textColor, 16);
    if (mStashedTetromino != -1)
        DrawPiece( -PIECE_BLOCKS - 1, 2, mStashedTetromino, mStashedRotation);
    
    m_pGameView->DrawText("Super Fun Game", &titleRectangle, textColor, 48);
    m_pGameView->DrawText("Score: " + std::to_string(mPlayerScore), &scoreRectangle, textColor, 32);
    m_pGameView->Render();
}

//
// Stores the current piece and begins a new game cycle
//
void TetrominoLogic::StoreTetrominoAndReset()
{
    m_pBoard->StoreTetromino(mXPosition, mYPosition, mTetromino, mRotation);
    
    UpdateScore(m_pBoard->DeletePossibleLines());
    
    if (m_pBoard->IsGameOver())
    {
        Shutdown();
        return;
    }
    
    CreateNewTetromino();
    mGameCycleTimer->Start();
}

//
// Stashes the current tetromino
//
void TetrominoLogic::StashTetromino()
{
    if (mStashedTetromino == -1)
    {
        mStashedTetromino = mTetromino;
        mStashedRotation = mRotation;
        
        // Need to create a new piece to replace stashed piece
        CreateNewTetromino();
    }
    else
    {
        // Swap the current with the stashed tetromino
        Tetromino tempTetromino = mStashedTetromino;
        Rotation tempRotation = mStashedRotation;
        mStashedTetromino = mTetromino;
        mStashedRotation = mRotation;
        mTetromino = tempTetromino;
        mRotation = tempRotation;
        
        mXPosition = (BOARD_WIDTH / 2) + Tetrominos::GetInitialPositionX(mTetromino, mRotation);
        mYPosition = Tetrominos::GetInitialPositionY(mTetromino, mRotation);
    }
    
    mGameCycleTimer->Start();
}

//
// Updates the player's score
//
// Input: `numberDeletedLines` is the number of lines the user eliminated on their last move.
//        This determines how many points they receive.
//
void TetrominoLogic::UpdateScore(int numberDeletedLines)
{
    switch (numberDeletedLines)
    {
        case 0:
            return;
        case 1:
            mPlayerScore += mPlayerLevel * 40;
            break;
        case 2:
            mPlayerScore += mPlayerLevel * 100;
            break;
        case 3:
            mPlayerScore += mPlayerLevel * 300;
            break;
        case 4:
            mPlayerScore += mPlayerLevel * 1200;
            break;
    }
    
    mTotalNumberLinesDeleted += numberDeletedLines;
    
    // Increase difficulty every 10 line deletions
    if (mTotalNumberLinesDeleted / mPlayerLevel >= 10)
    {
        mPlayerLevel++;
        mDropTime -= 50;
    }
}

//
// Creates a new Tetromino
//
void TetrominoLogic::CreateNewTetromino()
{
    // New Tetromino
    mTetromino = mNextTetrominos.front();
    mNextTetrominos.pop_front();
    mRotation = mNextRotations.front();
    mNextRotations.pop_front();
    mXPosition = (BOARD_WIDTH / 2) + Tetrominos::GetInitialPositionX(mTetromino, mRotation);
    mYPosition = Tetrominos::GetInitialPositionY(mTetromino, mRotation);
    
    // Next tetromino
    mNextTetrominos.push_back(GetRandomNumber(0, 6));
    mNextRotations.push_back(GetRandomNumber(0, 3));
}

//
// Draws the board
//
void TetrominoLogic::DrawBoard()
{
    // Calculate the limits of the board in pixels
    int leftBorderX = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
    int rightBorderX = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
    int borderY = SCREEN_HEIGHT - (BLOCK_SIZE * BOARD_HEIGHT);

    // Rectangles that delimit the board
    SDL_Color blue = {0x00, 0x00, 0xFF, 0xFF};
    m_pGameView->DrawRectangle(leftBorderX - BOARD_LINE_WIDTH, borderY, BOARD_LINE_WIDTH, SCREEN_HEIGHT - 1, blue);
    m_pGameView->DrawRectangle(rightBorderX, borderY, BOARD_LINE_WIDTH, SCREEN_HEIGHT - 1, blue);

    // Draw blocks stored in board
    for (int i = 0; i < BOARD_WIDTH; ++i)
    {
        for (int j = 0; j < BOARD_HEIGHT; ++j)
        {
            if (!m_pBoard->IsBlockFree(i, j))
            {
                int xPositionPixels = m_pBoard->GetXPositionInPixels(i);
                int yPositionPixels = m_pBoard->GetYPositionInPixels(j);
                m_pGameView->DrawRectangle(xPositionPixels + 1, yPositionPixels + 1, BLOCK_SIZE - 1, BLOCK_SIZE - 1, Tetrominos::GetTetrominoColor(m_pBoard->GetBlockType(i, j)));
            }
        }
    }
}

//
// Draws the given piece at the given position
//
// Input: `x` and `y` represent the position the piece is being drawn to.
//        `tetromino` and `rotation` represent the piece we're drawing.
//
void TetrominoLogic::DrawPiece(int x, int y, Tetromino tetromino, Rotation rotation)
{
    for (int boardX = x, tetrominoX = 0; boardX < x + PIECE_BLOCKS; boardX++, tetrominoX++)
    {
        for (int boardY = y, tetrominoY = 0; boardY < y + PIECE_BLOCKS; boardY++, tetrominoY++)
        {
            if (Tetrominos::GetBlockType(tetromino, rotation, tetrominoY, tetrominoX) != 0)
            {
                int xPositionPixels = m_pBoard->GetXPositionInPixels(boardX);
                int yPositionPixels = m_pBoard->GetYPositionInPixels(boardY);
                m_pGameView->DrawRectangle(xPositionPixels + 1, yPositionPixels + 1, BLOCK_SIZE - 1, BLOCK_SIZE - 1, Tetrominos::GetTetrominoColor(tetromino));
            }
        }
    }
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
