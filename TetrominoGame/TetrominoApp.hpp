//
//  TetrominoApp.hpp
//  TetrominoGame
//
//  Created by John Geiger on 10/1/21.
//
#pragma once

#ifndef TetrominoApp_hpp
#define TetrominoApp_hpp

#include "TetrominoLogic.hpp"
#include "TetrominoView.hpp"
#include "Application/Initialization.hpp"

#define WAIT_TIME 700 // Number of ms that the tetromino remains before going 1 block down

class TetrominoApp
{
private:
    TetrominoLogic* m_pGameLogic;
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    
    GameOptions mOptions;
    int mScreenHeight; // Screen height in pixels
   
public:
    TetrominoApp(int screenHeight);
    ~TetrominoApp();
    
    bool InitGame(); // Initializes the Tetromino App
    void MainLoop(); // Runs the Main Loop of the game
};

#endif /* TetrominoApp_hpp */
