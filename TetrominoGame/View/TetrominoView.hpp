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
#include <SDL2_ttf/SDL_ttf.h>
#include "TetrominoBoard.hpp"
#include <string>
#include <vector>

//
// Handles the rendering and drawing for the application
//
class TetrominoView
{
public:
    TetrominoView();
    
    bool Init(std::shared_ptr<TetrominoBoard> pBoard, SDL_Renderer* pRenderer);
    void Update();
    void Shutdown();
    
    void DrawRectangle(int xPositionPixels, int yPositionPixels, int width, int height, SDL_Color color, bool isFilled=true);
    void DrawText(std::string text, SDL_Rect* renderRectangle, SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF}, int fontSize = 16, std::string fontPath = "");
    void Render();
    
private:
    std::string mDefaultFontPath;
    std::vector<TTF_Font*> m_pFonts;
    SDL_Renderer* m_pRenderer;
    std::shared_ptr<TetrominoBoard> m_pBoard;
};


#endif /* TetrominoView_hpp */
