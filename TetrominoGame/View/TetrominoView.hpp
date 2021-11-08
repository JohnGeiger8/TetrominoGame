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
#include "Tetromino.hpp"
#include "HumanView.hpp"
#include <string>
#include <vector>

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
    virtual void VDrawText(std::string text, SDL_Rect* renderRectangle, SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF}, int fontSize = 16, std::string fontPath = "");
    
    void DrawBoard();
    void DrawRectangle(int xPositionPixels, int yPositionPixels, int width, int height, SDL_Color color, bool isFilled=true);
    
private:
    // Drawing methods
    void DrawPiece(int x, int y, TetrominoType tetromino, Rotation rotation);
    
    std::string mDefaultFontPath;
    std::vector<TTF_Font*> m_pFonts;
    
    // Stuff to render
    std::shared_ptr<TetrominoBoard> m_pBoard;
    TetrominoPointer m_pTetromino;
    TetrominoPointer m_pStashedTetromino;
    TetrominoList m_pNextTetrominos;
};

/*public:
 ScreenElementList mScreenElements;
 std::shared_ptr<IKeyboardHandler> mKeyboardHandler;

 SDL_Renderer* m_pRenderer;

 HumanView();
 ~HumanView();
 
 virtual bool VInit();
 virtual void VShutdown();
 virtual void VUpdate();
 virtual void VRender();
 virtual void VDrawText(std::string text, SDL_Rect* renderRectangle, SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF}, int fontSize = 16, std::string fontPath = "");
 virtual void VProcessMessages(SDL_Event* pEvent);
 
 virtual void VPushElement(ScreenElementPointer pElement);
 virtual void VRemoveElement(ScreenElementPointer pElement);
 */

#endif /* TetrominoView_hpp */
