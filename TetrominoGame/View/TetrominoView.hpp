//
//  TetrominoView.hpp
//  TetrominoGame
//
//  Created by John Geiger on 10/1/21.
//
#pragma once

#ifndef TetrominoView_hpp
#define TetrominoView_hpp

#include <SDL2/SDL.h>
#include "TetrominoBoard.hpp"

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 600

//
// Handles the rendering and drawing for the application
//
class TetrominoView
{
public:
    TetrominoView();
    
    bool Init(std::shared_ptr<TetrominoBoard> pBoard, SDL_Window* pWindow);
    void Update();
    void Shutdown();
    
    void DrawPiece(int x, int y, Tetromino tetromino, Rotation rotation);
    void Render();
    
private:
    SDL_Renderer* m_pRenderer;
    std::shared_ptr<TetrominoBoard> m_pBoard;
    
    void DrawBoard();
    void DrawRectangle(int xPositionPixels, int yPositionPixels, int width, int height, SDL_Color color, bool isFilled=true);
};


#endif /* TetrominoView_hpp */
