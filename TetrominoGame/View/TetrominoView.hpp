//
//  TetrominoView.hpp
//  TetrominoGame
//
//  Created by John Geiger on 10/1/21.
//
#pragma once

#ifndef TetrominoView_hpp
#define TetrominoView_hpp

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "TetrominoBoard.hpp"
#include "Tetromino.hpp"
#include "HumanView.hpp"
#include "TitleUI.hpp"

#define NUMBER_PREVIEW_PIECES 3 // Number of pieces to show on side

//
// Handles the rendering and drawing for the application
//
class TetrominoView : public HumanView
{
public:
    TetrominoView();
    
    virtual bool VInit(std::shared_ptr<TetrominoBoard> pBoard, TetrominoPointer pTetromino, TetrominoPointer pStashedTetromino, TetrominoList pNextTetrominos);
    virtual void VUpdate();
    virtual void VShutdown();
    virtual void VRender();
    
    void DrawBoard();
    void DrawRectangle(int xPositionPixels, int yPositionPixels, int width, int height, SDL_Color color, bool isFilled=true);
    
private:
    // Drawing methods
    void DrawPiece(int x, int y, TetrominoType tetromino, Rotation rotation);
    
    // Stuff to render
    std::shared_ptr<TetrominoBoard> m_pBoard;
    TetrominoPointer m_pTetromino;
    TetrominoPointer m_pStashedTetromino;
    TetrominoList m_pNextTetrominos;
    
    // UI/text stuff
    int mPlayerScore;
    std::shared_ptr<TitleUI> m_pScoreUI;
    std::string mDefaultFontPath;
    std::vector<TTF_Font*> m_pFonts;
};

#endif /* TetrominoView_hpp */
