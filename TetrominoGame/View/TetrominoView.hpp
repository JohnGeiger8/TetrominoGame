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
#include "Menu.hpp"
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
    
    void SetGameIsOver();
    
    bool m_bGameIsRestarting;
    
private:
    // Drawing methods
    void DrawBoard();
    void DrawRectangle(int xPositionPixels, int yPositionPixels, int width, int height, SDL_Color color, bool isFilled = true);
    void DrawPiece(int x, int y, TetrominoType tetromino, Rotation rotation, SDL_Color color, bool isFilled = true);
    void DrawPieceOutline(int x, int y, TetrominoType tetromino, Rotation rotation);
    void CreateGameOverUI(int screenWidth, int screenHeight, int score);
    
    // Stuff to render
    std::shared_ptr<TetrominoBoard> m_pBoard;
    TetrominoPointer m_pTetromino;
    TetrominoPointer m_pStashedTetromino;
    TetrominoList m_pNextTetrominos;
    
    // UI/text stuff
    int mPlayerScore;
    std::shared_ptr<TitleUI> m_pScoreUI;
    std::shared_ptr<MainMenuUI> m_pGameOverUI;
    std::shared_ptr<TitleUI> m_pGameOverScoreUI;
    std::shared_ptr<MenuButtonUI> m_pRestartButton;
    std::shared_ptr<MenuButtonUI> m_pQuitButton;
};

#endif /* TetrominoView_hpp */
