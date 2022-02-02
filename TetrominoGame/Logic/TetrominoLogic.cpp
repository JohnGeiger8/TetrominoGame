//
//  TetrominoLogic.cpp
//  TetrominoGame
//
//  Created by John Geiger on 10/1/21.
//

#include "TetrominoLogic.hpp"
#include "CVar.hpp"

//
// Creates TetrominoLogic with given screen height
//
// Input: `screenHeight` specifies the height of the screen.
//
TetrominoLogic::TetrominoLogic(GameOptions options)
{
    m_pBoard = NULL;
    m_pGameView = NULL;
    mGameCycleTimer = NULL;
    m_pGameSessionTimer = NULL;
    m_pTetrominoMovementTimer = NULL;
    
    mOptions = options;
    
    m_bIsPaused = false;
    m_bIsGameOver = false;
    m_bHasStashed = false;
    
    mDropTime = PIECE_DROP_START_TIME;
    mPlayerLevel = 1;
    CVar gPlayerScore = CVar("playerScore", 0, 0, "Player's current score", CVAR_INTEGER);
    mPlayerScore = 0;
    
    mNextTetrominos = NULL;
    m_pTetromino = NULL;
    m_pStashedTetromino = NULL;
}

//
// Initializes the systems of TetrominoLogic
//
// Returns: true if initialization succeeds.
//
bool TetrominoLogic::Init()
{
    // Initialize the Board and pieces
    m_pBoard = std::make_shared<TetrominoBoard>(mOptions.mScreenHeight);
    if (!m_pBoard->Init())
    {
        printf("Game Board failed initialization failed.");
        return false;
    }
    
    // Initialize the tetrominos
    srand((unsigned int) time(NULL));
    m_pTetromino = std::make_shared<Tetromino>(GetRandomNumber(0, 6), GetRandomNumber(0, 3));
    m_pTetromino->SetX((BOARD_WIDTH / 2) + Tetrominos::GetInitialPositionX(m_pTetromino->GetType(), m_pTetromino->GetRotation()));
    m_pTetromino->SetY(Tetrominos::GetInitialPositionY(m_pTetromino->GetType(), m_pTetromino->GetRotation()));
    
    m_pStashedTetromino = std::make_shared<Tetromino>(-1, -1);
    
    // Next pieces
    mNextTetrominos = std::make_shared<std::deque<TetrominoPointer>>();
    for (int i = 0; i < NUMBER_PREVIEW_PIECES; ++i)
    {
        TetrominoPointer pNextTetromino = std::make_shared<Tetromino>(GetRandomNumber(0, 6), GetRandomNumber(0, 3));
        pNextTetromino->SetY(i * PIECE_BLOCKS);
        pNextTetromino->SetX(BOARD_WIDTH + 5);
        mNextTetrominos->push_back(pNextTetromino);
    }
        
    // Initialize Game View
    m_pGameView = std::make_shared<TetrominoView>();
    if (!m_pGameView->VInit(m_pBoard, m_pTetromino, m_pStashedTetromino, mNextTetrominos))
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
    m_pGameView->VShutdown();
    m_pGameView = NULL;
    
    mNextTetrominos->clear();
    mNextTetrominos = NULL;
    m_pTetromino = NULL;
    m_pStashedTetromino = NULL;
      
    m_pGameSessionTimer->Stop();
    m_pTetrominoMovementTimer->Stop();
    mGameCycleTimer->Stop();
        
    mGameCycleTimer = NULL;
    m_pGameSessionTimer = NULL;
    m_pTetrominoMovementTimer = NULL;
    
    m_pBoard = NULL;
    
    m_bIsPaused = false;
    m_bIsGameOver = false;
    m_bHasStashed = false;
    
    mDropTime = PIECE_DROP_START_TIME;
    mPlayerLevel = 1;
    mPlayerScore = 0;
    UpdateGlobalScore(0);
}

//
// Updates the Tetromino Logic. Called each frame
//
void TetrominoLogic::OnUpdate(SDL_Event* event)
{
    if (m_bIsGameOver)
    {
        m_pGameView->VUpdate();
        OnRender();
        
        if (m_pGameView->m_bGameIsRestarting)
        {
            Shutdown();
            Init();
        }
        
        return;
    }
    
    switch (event->type) {
        case SDL_QUIT:
            Shutdown();
            return;
        case SDL_KEYDOWN:
            if (m_pTetrominoMovementTimer->IsStarted() && m_pTetrominoMovementTimer->GetTicks() < PIECE_MOVE_TIME)
                break;
            
            const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
            if (!m_bIsPaused)
            {
                if (keyStates[SDL_SCANCODE_LEFT])
                {
                    if (m_pBoard->IsPossibleMovement(m_pTetromino->GetXPosition() - 1, m_pTetromino->GetYPosition(), m_pTetromino->GetType(), m_pTetromino->GetRotation()))
                        m_pTetromino->SetX(m_pTetromino->GetXPosition() - 1);
                }
                else if (keyStates[SDL_SCANCODE_RIGHT])
                {
                    if (m_pBoard->IsPossibleMovement(m_pTetromino->GetXPosition() + 1, m_pTetromino->GetYPosition(), m_pTetromino->GetType(), m_pTetromino->GetRotation()))
                        m_pTetromino->SetX(m_pTetromino->GetXPosition() + 1);
                }
                else if (keyStates[SDL_SCANCODE_DOWN])
                {
                    if (m_pBoard->IsPossibleMovement(m_pTetromino->GetXPosition(), m_pTetromino->GetYPosition() + 1, m_pTetromino->GetType(), m_pTetromino->GetRotation()))
                        m_pTetromino->SetY(m_pTetromino->GetYPosition() + 1);
                }
                else if (keyStates[SDL_SCANCODE_S])
                {
                    if (!m_bHasStashed)
                    {
                        StashTetromino();
                        m_bHasStashed = true;
                    }
                }
                else if (keyStates[SDL_SCANCODE_X])
                {
                    // If the piece already can't go down, the mGameCycleTimer shouldn't reset
                    if (m_pBoard->IsPossibleMovement(m_pTetromino->GetXPosition(), m_pTetromino->GetYPosition() + 1, m_pTetromino->GetType(), m_pTetromino->GetRotation()))
                    {
                        // Move piece straight down
                        while (m_pBoard->IsPossibleMovement(m_pTetromino->GetXPosition(), m_pTetromino->GetYPosition() + 1, m_pTetromino->GetType(), m_pTetromino->GetRotation()))
                        {
                            m_pTetromino->SetY(m_pTetromino->GetYPosition() + 1);
                        }
                        
                        // Restart game cycle to give user a chance to move piece sideways
                        mGameCycleTimer->Start();
                        OnRender();
                        return;
                    }
                }
                else if (keyStates[SDL_SCANCODE_Z])
                {
                    if (m_pBoard->IsPossibleMovement(m_pTetromino->GetXPosition(), m_pTetromino->GetYPosition(), m_pTetromino->GetType(), (m_pTetromino->GetRotation() + 1) % 4))
                        m_pTetromino->SetRotation((m_pTetromino->GetRotation() + 1) % 4);
                }
            }
            
            if (keyStates[SDL_SCANCODE_P])
            {
                TogglePause();
            }
            OnRender();
            
            m_pTetrominoMovementTimer->Start();
            
            break;
    }
    
    // If game is paused and view says to resume
    if (m_bIsPaused && m_pGameView->m_bGameIsResuming)
    {
        TogglePause();
        
        OnRender();
        m_pTetrominoMovementTimer->Start();
    }
    
    if (!m_bIsPaused)
    {
        Uint32 time = mGameCycleTimer->GetTicks();

        if (time >= mDropTime) // Move the piece down if possible
        {
            if (m_pBoard->IsPossibleMovement(m_pTetromino->GetXPosition(), m_pTetromino->GetYPosition() + 1, m_pTetromino->GetType(), m_pTetromino->GetRotation()))
            {
                m_pTetromino->SetY(m_pTetromino->GetYPosition() + 1);
                mGameCycleTimer->Start();
            }
            else
            {
                StoreTetrominoAndReset();
            }
            OnRender();
        }
    }
    
    m_pGameView->VUpdate();
}

//
// Does all of the rendering work
//
void TetrominoLogic::OnRender()
{
    m_pGameView->VRender();
}

//
// Stores the current piece and begins a new game cycle
//
void TetrominoLogic::StoreTetrominoAndReset()
{
    m_pBoard->StoreTetromino(m_pTetromino->GetXPosition(), m_pTetromino->GetYPosition(), m_pTetromino->GetType(), m_pTetromino->GetRotation());
    
    UpdateScore(m_pBoard->DeletePossibleLines());
    
    if (m_pBoard->IsGameOver())
    {
        m_bIsGameOver = true;
        m_pGameView->SetGameIsOver();
        return;
    }
    
    CreateNewTetromino();
    mGameCycleTimer->Start();
    m_bHasStashed = false;
}

//
// Stashes the current tetromino
//
void TetrominoLogic::StashTetromino()
{
    if (m_pStashedTetromino->GetType() == -1)
    {
        m_pStashedTetromino->SetTetromino(m_pTetromino->GetType());
        m_pStashedTetromino->SetRotation(m_pTetromino->GetRotation());
        
        // Need to create a new piece to replace stashed piece
        CreateNewTetromino();
    }
    else
    {
        // Swap the current with the stashed tetromino
        TetrominoType stashedType = m_pStashedTetromino->GetType();
        Rotation stashedRotation = m_pStashedTetromino->GetRotation();
        
        m_pStashedTetromino->SetTetromino(m_pTetromino->GetType());
        m_pStashedTetromino->SetRotation(m_pTetromino->GetRotation());
        
        m_pTetromino->SetTetromino(stashedType);
        m_pTetromino->SetRotation(stashedRotation);
        m_pTetromino->SetX((BOARD_WIDTH / 2) + Tetrominos::GetInitialPositionX(m_pTetromino->GetType(), m_pTetromino->GetRotation()));
        m_pTetromino->SetY(Tetrominos::GetInitialPositionY(m_pTetromino->GetType(), m_pTetromino->GetRotation()));
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
    UpdateGlobalScore(mPlayerScore);
    
    mTotalNumberLinesDeleted += numberDeletedLines;
    
    // Increase difficulty every 10 line deletions
    if (mTotalNumberLinesDeleted / mPlayerLevel >= 10)
    {
        mPlayerLevel++;
        mDropTime -= 50;
    }
}

//
// Update the global score variable
//
void TetrominoLogic::UpdateGlobalScore(int score)
{
    CVar g_playerScore = g_cvars.find("playerScore")->second;
    g_playerScore.SetIntValue(score);
    g_cvars.erase("playerScore");
    g_cvars.insert(pair<std::string, CVar>("playerScore", g_playerScore));
}

//
// Creates a new Tetromino
//
void TetrominoLogic::CreateNewTetromino()
{
    // New Tetromino
    m_pTetromino->SetTetromino(mNextTetrominos->front()->GetType());
    m_pTetromino->SetRotation(mNextTetrominos->front()->GetRotation());
    m_pTetromino->SetX((BOARD_WIDTH / 2) + Tetrominos::GetInitialPositionX(m_pTetromino->GetType(), m_pTetromino->GetRotation()));
    m_pTetromino->SetY(Tetrominos::GetInitialPositionY(m_pTetromino->GetType(), m_pTetromino->GetRotation()));
    
    // Next tetrominos update
    mNextTetrominos->pop_front();
    for (TetrominoPointer pTetromino : *mNextTetrominos)
    {
        pTetromino->SetY(pTetromino->GetYPosition() - PIECE_BLOCKS);
    }
    
    TetrominoPointer pNextTetromino = std::make_shared<Tetromino>(GetRandomNumber(0, 6), GetRandomNumber(0, 3));
    pNextTetromino->SetY(2 * PIECE_BLOCKS);
    pNextTetromino->SetX(BOARD_WIDTH + 5);
    mNextTetrominos->push_back(pNextTetromino);
}

//
// Toggles game's pause state
//
void TetrominoLogic::TogglePause()
{
    if (m_bIsPaused)
    {
        mGameCycleTimer->Unpause();
        m_pGameView->UnpauseGame();
        m_bIsPaused = false;
        g_pAudio->VResumeAllSounds();
    }
    else
    {
        mGameCycleTimer->Pause();
        m_pGameView->PauseGame();
        m_bIsPaused = true;
        g_pAudio->VPauseAllSounds();
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
