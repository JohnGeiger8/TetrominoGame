//
//  TetrominoView.cpp
//  TetrominoGame
//
//  Created by John Geiger on 10/1/21.
//

#include "TetrominoView.hpp"
#include "CVar.hpp"
#include "SDLRenderer.hpp"

TetrominoView::TetrominoView()
{
    m_pBoard = NULL;
    m_pTetromino = NULL;
    m_pStashedTetromino = NULL;
    m_pNextTetrominos = NULL;
    m_pScoreUI = NULL;
    m_pGameOverUI = NULL;
    m_pGameOverScoreUI = NULL;
    m_pRestartButton = NULL;
    m_pQuitButton = NULL;
    
    mPlayerScore = 0;
    m_bGameIsRestarting = false;
}

//
// Initialize the systems of the Tetromino View, including the board
//
// Input: `pBoard` points to the TetrominoBoard we'll be displaying.
//
// Returns: true if successful.
//
bool TetrominoView::VInit(std::shared_ptr<TetrominoBoard> pBoard, TetrominoPointer pTetromino, TetrominoPointer pStashedTetromino, TetrominoList pNextTetrominos)
{
    bool success = true;
        
    m_pBoard = pBoard;
    if (m_pBoard == NULL)
    {
        printf("Board not initialized.");
        success = false;
    }
    
    m_pTetromino = pTetromino;
    if (m_pTetromino == NULL)
    {
        printf("Tetromino not initialized.");
        success = false;
    }
    
    m_pStashedTetromino = pStashedTetromino;
    if (m_pStashedTetromino == NULL)
    {
        printf("Stashed Tetromino not initialized.");
        success = false;
    }
    
    m_pNextTetrominos = pNextTetrominos;
    if (m_pNextTetrominos == NULL)
    {
        printf("Next Tetrominos not initialized.");
        success = false;
    }
    
    // Initialize text UI items
    int screenHeight = g_cvars.find("screenHeight")->second.GetIntValue();
    int screenWidth = g_cvars.find("screenWidth")->second.GetIntValue();
    int playerScore = g_cvars.find("playerScore")->second.GetIntValue();

//    SDL_Rect stashRectangle = { m_pBoard->GetBoardPositionInPixels() - (BOARD_WIDTH / 2) - 140, screenHeight - (BLOCK_SIZE * BOARD_HEIGHT), 100, 100 };
    SDL_Color textColor = { 0x00, 0xFF, 0xFF, 0xFF };
    std::shared_ptr<TitleUI> pTitleUI = std::make_shared<TitleUI>("BLOCK DROPPER", 48, textColor);
    std::shared_ptr<TitleUI> pScoreTextUI = std::make_shared<TitleUI>("Score", 32, textColor);
    m_pScoreUI = std::make_shared<TitleUI>(std::to_string(playerScore), 32, textColor);
    std::shared_ptr<TitleUI> pStashUI = std::make_shared<TitleUI>("S  to  stash", 16, textColor);

    pTitleUI->VSetPositionX(screenWidth / 2);
    pTitleUI->VSetPositionY(pTitleUI->VGetHeight() + 15);
    pScoreTextUI->VSetPositionX(screenWidth / 2);
    pScoreTextUI->VSetPositionY(120);
    m_pScoreUI->VSetPositionX(screenWidth / 2);
    m_pScoreUI->VSetPositionY(pScoreTextUI->VGetPositionY() + 35);
    pStashUI->VSetPositionX(m_pBoard->GetBoardPositionInPixels() - (BOARD_WIDTH / 2) - 140);
    pStashUI->VSetPositionY(screenHeight - (BLOCK_SIZE * BOARD_HEIGHT));
    
    CreateGameOverUI(screenWidth, screenHeight, playerScore);
   
    VPushElement(m_pGameOverUI);
    VPushElement(pTitleUI);
    VPushElement(pScoreTextUI);
    VPushElement(m_pScoreUI);
    VPushElement(pStashUI);
    
    return success;
}

//
// Build Game Over UI to be displayed when game ends
//
void TetrominoView::CreateGameOverUI(int screenWidth, int screenHeight, int score)
{
    SDL_Color titleColor = { 0x00, 0xFF, 0xFF };
    
    m_pGameOverUI = std::make_shared<MainMenuUI>();
    
    std::shared_ptr<TitleUI> pTitleUI = std::make_shared<TitleUI>("GAME  OVER!", 36, titleColor);
    m_pGameOverScoreUI = std::make_shared<TitleUI>(std::to_string(mPlayerScore), 28, SDL_Color({0xFF, 0xFF, 0x00}));
    m_pRestartButton = std::make_shared<MenuButtonUI>("Restart");
    m_pQuitButton = std::make_shared<MenuButtonUI>("Quit");

    m_pRestartButton->VSetWidth(screenWidth / 3);
    m_pRestartButton->VSetHeight(85);
    m_pQuitButton->VSetWidth(screenWidth / 3);
    m_pQuitButton->VSetHeight(85);
    
    m_pGameOverUI->VSetPositionX((screenWidth / 2) - (m_pRestartButton->VGetWidth() / 2) - HORIZONTAL_BUTTON_MARGINS);
    m_pRestartButton->VSetPositionX(m_pGameOverUI->VGetPositionX() + HORIZONTAL_BUTTON_MARGINS);
    m_pQuitButton->VSetPositionX(m_pGameOverUI->VGetPositionX() + HORIZONTAL_BUTTON_MARGINS);
    
    m_pGameOverUI->VSetWidth(m_pRestartButton->VGetWidth() + 2 * HORIZONTAL_BUTTON_MARGINS);
    m_pGameOverUI->VSetHeight(m_pRestartButton->VGetHeight() + m_pQuitButton->VGetHeight() + 3 * VERTICAL_BUTTON_MARGINS);
    m_pGameOverUI->VSetPositionY((screenHeight / 2) - (m_pGameOverUI->VGetHeight() / 2));
    
    // Title position should be centered because it's text
    pTitleUI->VSetPositionX(m_pGameOverUI->VGetPositionX() + m_pGameOverUI->VGetWidth() / 2);
    pTitleUI->VSetPositionY(m_pGameOverUI->VGetPositionY());
    m_pGameOverScoreUI->VSetPositionX(pTitleUI->VGetPositionX());
    m_pGameOverScoreUI->VSetPositionY(pTitleUI->VGetPositionY() + VERTICAL_BUTTON_MARGINS);

    m_pRestartButton->VSetPositionY(m_pGameOverScoreUI->VGetPositionY() + m_pGameOverScoreUI->VGetHeight());
    m_pQuitButton->VSetPositionY(m_pRestartButton->VGetPositionY() + m_pRestartButton->VGetHeight() + VERTICAL_BUTTON_MARGINS);

    // Colors
    m_pRestartButton->SetButtonColor({0x00, 0xFF, 0xFF});
    m_pQuitButton->SetButtonColor({0x00, 0xFF, 0xFF});
    m_pGameOverUI->SetColor({0x00, 0xFF, 0xFF, 0xFF});
    
    m_pGameOverUI->AddMenuOption(pTitleUI);
    m_pGameOverUI->AddMenuOption(m_pGameOverScoreUI);
    m_pGameOverUI->AddMenuOption(m_pRestartButton);
    m_pGameOverUI->AddMenuOption(m_pQuitButton);
    
    // Invisible until game ends
    m_pGameOverUI->VSetVisible(false);
}

//
// Reset everything
//
void TetrominoView::VShutdown()
{
    m_pBoard = NULL;
    m_pTetromino = NULL;
    m_pStashedTetromino = NULL;
    m_pNextTetrominos = NULL;
    m_pScoreUI = NULL;
    m_pGameOverUI = NULL;
    m_pGameOverScoreUI = NULL;
    m_pRestartButton = NULL;
    m_pQuitButton = NULL;
    
    mPlayerScore = 0;
    m_bGameIsRestarting = false;
}

//
// Updates the view, looping through the board and drawing everything
//
void TetrominoView::VUpdate()
{
    int playerScore = g_cvars.find("playerScore")->second.GetIntValue();
    if (playerScore != mPlayerScore)
    {
        m_pScoreUI->VSetTitle(std::to_string(playerScore));
        m_pGameOverScoreUI->VSetTitle(std::to_string(playerScore));
        mPlayerScore = playerScore;
    }
    
    // Game is over
    if (m_pGameOverUI->VIsVisible())
    {
        HumanView::VUpdate();
        
        // Restart the game
        if (m_pRestartButton->VIsSelected())
        {
            m_bGameIsRestarting = true;
        }
        
        // Exit the game
        if (m_pQuitButton->VIsSelected())
        {
            CVar g_isQuitting = g_cvars.find("isQuitting")->second;
            g_isQuitting.SetBoolValue(true);
            g_cvars.erase("isQuitting");
            g_cvars.insert(pair<std::string, CVar>("isQuitting", g_isQuitting));
        }
    }
}

//
// Draws a rectangle using SDL
//
// Input: `xPositionPixels` is the top left x coordinate of the rectangle.
//        `yPositionPixels` is the top left y coordinate of the rectangle.
//        `width` and `height` are the width and height of the rectangle.
//        `color` is the color and `isFilled` determines if the rectangle
//        should be solid or not. Both are optional.
//
void TetrominoView::DrawRectangle(int xPositionPixels, int yPositionPixels, int width, int height, SDL_Color color, bool isFilled)
{
    SDL_Rect rectangle = { xPositionPixels, yPositionPixels, width, height };
    SDL_SetRenderDrawColor(g_pRenderer->GetRenderer(), color.r, color.g, color.b, color.a);
    if (isFilled)
        SDL_RenderFillRect(g_pRenderer->GetRenderer(), &rectangle);
    else
        SDL_RenderDrawRect(g_pRenderer->GetRenderer(), &rectangle);
}

//
// Draws the given piece at the given position
//
// Input: `x` and `y` represent the position the piece is being drawn to.
//        `tetromino` and `rotation` represent the piece we're drawing.
//
void TetrominoView::DrawPiece(int x, int y, TetrominoType tetromino, Rotation rotation)
{
    for (int boardX = x, tetrominoX = 0; boardX < x + PIECE_BLOCKS; boardX++, tetrominoX++)
    {
        for (int boardY = y, tetrominoY = 0; boardY < y + PIECE_BLOCKS; boardY++, tetrominoY++)
        {
            if (Tetrominos::GetBlockType(tetromino, rotation, tetrominoY, tetrominoX) != 0)
            {
                int xPositionPixels = m_pBoard->GetXPositionInPixels(boardX);
                int yPositionPixels = m_pBoard->GetYPositionInPixels(boardY);
                DrawRectangle(xPositionPixels + 1, yPositionPixels + 1, BLOCK_SIZE - 1, BLOCK_SIZE - 1, Tetrominos::GetTetrominoColor(tetromino));
            }
        }
    }
}

//
// Draw the Tetromino board
//
void TetrominoView::DrawBoard()
{
    int screenHeight = g_cvars.find("screenHeight")->second.GetIntValue();

    // Calculate the limits of the board in pixels
    int leftBorderX = m_pBoard->GetBoardPositionInPixels() - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
    int rightBorderX = m_pBoard->GetBoardPositionInPixels() + (BLOCK_SIZE * (BOARD_WIDTH / 2));
    int borderY = screenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

    // Rectangles that delimit the board
    SDL_Color blue = {0x00, 0x00, 0xFF, 0xFF};
    DrawRectangle(leftBorderX - m_pBoard->GetBorderWidthInPixels(), borderY, m_pBoard->GetBorderWidthInPixels(), screenHeight - 1, blue);
    DrawRectangle(rightBorderX, borderY, m_pBoard->GetBorderWidthInPixels(), screenHeight - 1, blue);

    // Draw blocks stored in board
    for (int i = 0; i < BOARD_WIDTH; ++i)
    {
        for (int j = 0; j < BOARD_HEIGHT; ++j)
        {
            if (!m_pBoard->IsBlockFree(i, j))
            {
                int xPositionPixels = m_pBoard->GetXPositionInPixels(i);
                int yPositionPixels = m_pBoard->GetYPositionInPixels(j);
                DrawRectangle(xPositionPixels + 1, yPositionPixels + 1, BLOCK_SIZE - 1, BLOCK_SIZE - 1, Tetrominos::GetTetrominoColor(m_pBoard->GetBlockType(i, j)));
            }
        }
    }
}

//
// Present everything drawn
//
void TetrominoView::VRender()
{
    // Clear screen
    SDL_SetRenderDrawColor(g_pRenderer->GetRenderer(), 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(g_pRenderer->GetRenderer());
    
    // Draw Board and pieces
    DrawBoard();
    DrawPiece(m_pTetromino->GetXPosition(), m_pTetromino->GetYPosition(), m_pTetromino->GetType(), m_pTetromino->GetRotation());
    
    // Draw next 3 pieces on right side of board
    for (int i = 0; i < NUMBER_PREVIEW_PIECES; ++i)
    {
        DrawPiece(m_pNextTetrominos->at(i)->GetXPosition(), m_pNextTetrominos->at(i)->GetYPosition(), m_pNextTetrominos->at(i)->GetType(), m_pNextTetrominos->at(i)->GetRotation());
    }
    
    // Draw stashed piece on left side of board
    if (m_pStashedTetromino->GetType() != -1)
        DrawPiece( -PIECE_BLOCKS - 1, 2, m_pStashedTetromino->GetType(), m_pStashedTetromino->GetRotation());
    
    // Draw UI and text elements
    for (ScreenElementPointer &pElement : mScreenElements)
    {
        if (pElement->VIsVisible())
            pElement->VRender();
    }
    
    SDL_RenderPresent(g_pRenderer->GetRenderer());
}

void TetrominoView::SetGameIsOver()
{
    m_pGameOverUI->VSetVisible(true);
}
