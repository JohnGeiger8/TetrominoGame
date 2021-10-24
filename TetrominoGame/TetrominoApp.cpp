//
//  TetrominoApp.cpp
//  TetrominoGame
//
//  Created by John Geiger on 10/1/21.
//

#include <SDL2/SDL.h>
#include "TetrominoApp.hpp"

TetrominoApp::TetrominoApp(int screenHeight)
{
    mScreenHeight = screenHeight;
    mOptions = GameOptions();
    mOptions.mScreenHeight = mScreenHeight;
    
    m_pWindow = NULL;
    m_pGameLogic = NULL;
}

TetrominoApp::~TetrominoApp()
{
    delete(m_pGameLogic);
    m_pGameLogic = NULL;
    
    SDL_DestroyWindow(m_pWindow);
    m_pWindow = NULL;
    
    SDL_Quit();
}

//
// Initializes game logic and SDL
//
bool TetrominoApp::InitGame()
{
    bool successful;
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        successful = false;
    }
    
    // Initialize window
    m_pWindow = SDL_CreateWindow("Tetrominos Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mOptions.mScreenWidth, mOptions.mScreenHeight, SDL_WINDOW_SHOWN );
    if (m_pWindow == NULL)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        successful = false;
    }
    
    // Initialize Game Logic
    m_pGameLogic = new TetrominoLogic(mOptions);
    if (!m_pGameLogic->Init(m_pWindow))
    {
        printf("Error: Game Logic Initialization failed.");
        return false;
    }
    return true;
}

//
// Runs the main loop with SDL
//
void TetrominoApp::MainLoop()
{
    bool isQuitting = false;
    
    SDL_Event event;
    while (!isQuitting)
    {
        if (SDL_PollEvent(&event) != 0 && !m_pGameLogic->IsGameOver())
        {
            if (event.type == SDL_QUIT || m_pGameLogic->IsGameOver())
            {
                isQuitting = true;
            }
        }
        m_pGameLogic->OnUpdate(&event);
    }
}
