//
//  TitleUI.cpp
//  TetrominoGame
//
//  Created by John Geiger on 11/4/21.
//

#include "TitleUI.hpp"

TitleUI::TitleUI(std::string text, int fontSize, SDL_Color color)
    : mTitle(text), mFontSize(fontSize), mColor(color)
{
    m_bIsFocusable = false;
    VLoadTitleText();
}

TitleUI::~TitleUI()
{
    m_pTextTexture = NULL;
}

void TitleUI::VLoadTitleText()
{
    m_pTextTexture = std::make_shared<SDLTextTexture>(mTitle, mFontSize);
    if (m_pTextTexture == NULL)
    {
        printf("Text Texture failed to load in TitleUI");
    }
    else
    {
        // Set color and load texture
        m_pTextTexture->VSetColor(mColor.r, mColor.g, mColor.b);
    }
}

void TitleUI::VUpdate()
{
    
}

void TitleUI::VRender()
{
    VDrawText();
}

void TitleUI::VDrawText()
{
    int w = m_pTextTexture->GetWidth();
    int h = m_pTextTexture->GetHeight();
    Point position = Point(mPositionX - w / 2, mPositionY - h / 2);
    m_pTextTexture->SetPosition(position);
    m_pTextTexture->VRender();
}
