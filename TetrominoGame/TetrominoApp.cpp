//
//  TetrominoApp.cpp
//  TetrominoGame
//
//  Created by John Geiger on 10/1/21.
//

#include <SDL2_image/SDL_image.h>
#include "TetrominoApp.hpp"

SDLRendererPtr g_pRenderer;

TetrominoApp::TetrominoApp(int screenHeight)
{
    mScreenHeight = screenHeight;
    mOptions = GameOptions();
    mOptions.mScreenHeight = mScreenHeight;
    
    m_pWindow = NULL;
    m_pGameLogic = NULL;
    m_pMainMenu = NULL;
    
    // Globals
    CVar g_screenHeight = CVar("screenHeight", screenHeight, 600, "Height of user's window screen", CVAR_INTEGER);
    CVar g_screenWidth = CVar("screenWidth", mOptions.mScreenWidth, 600, "Width of user's window screen", CVAR_INTEGER);
    CVar g_bGameStarted = CVar("isGameStarted", false, false, "Has the actual gameplay loop begun", CVAR_BOOL);
    CVar g_bIsQuitting = CVar("isQuitting", false, false, "The game should be shutting down if true", CVAR_BOOL);
}

TetrominoApp::~TetrominoApp()
{
    m_pGameLogic = NULL;
    m_pMainMenu = NULL;
    
    IMG_Quit();
    TTF_Quit();
    
    g_pRenderer = NULL;
    
    SDL_DestroyWindow(m_pWindow);
    m_pWindow = NULL;
    
    SDL_Quit();
}

//
// Initializes game logic and SDL
//
bool TetrominoApp::InitGame()
{
    bool successful = true;
    
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
    
    // Initialize Global Renderer
    g_pRenderer = std::make_shared<SDLRenderer>(m_pWindow);
    
    // Initialize Font library
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        successful = false;
    }
    
    // Initialize SDL Image with PNG loading
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        successful = false;
    }
    
    // Initialize Main Menu
    m_pMainMenu = std::make_shared<MainMenuView>();
    if (!m_pMainMenu->VInit())
    {
        printf("Error: Main Menu Initialization failed.");
        successful = false;
    }
    
    // Initialize Game Logic
    m_pGameLogic = std::make_shared<TetrominoLogic>(mOptions);
    if (!m_pGameLogic->Init())
    {
        printf("Error: Game Logic Initialization failed.");
        successful = false;
    }
    
    return successful;
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
            if (event.type == SDL_QUIT || m_pGameLogic->IsGameOver() || g_cvars.find("isQuitting")->second.GetBoolValue())
            {
                isQuitting = true;
            }
        }
        
        CVar g_isGameStarted = g_cvars.find("isGameStarted")->second;
        if (g_isGameStarted.GetBoolValue())
            m_pGameLogic->OnUpdate(&event);
        else
        {
            if (isQuitting)
            {
                m_pMainMenu->VShutdown();
            }
            else
            {
                m_pMainMenu->VUpdate();
                m_pMainMenu->VProcessMessages(&event);
            }
        }
    }
}
