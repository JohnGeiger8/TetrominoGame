//
//  SDLTextTexture.cpp
//  TetrominoGame
//
//  Created by John Geiger on 11/4/21.
//

#include "SDLTextTexture.hpp"
#include "SDLRenderer.hpp"

//
// Initialize members to reasonable defaults
//
SDLTextTexture::SDLTextTexture()
{
    m_pFont = NULL;
    mFontSize = 16;
    mFontPath = DEFAULT_FONT_PATH;
}

//
// Close the font
//
SDLTextTexture::~SDLTextTexture()
{
    VShutdown();
}

//
// Destroys the old texture and font
//
void SDLTextTexture::VShutdown()
{
    SDLTexture::VShutdown();
    
    if (m_pFont != NULL)
    {
        TTF_CloseFont(m_pFont);
        m_pFont = NULL;
    }
}

//
// Load the font at the given path
//
bool SDLTextTexture::LoadTextTextureFromFile(std::string path)
{
    //Get rid of preexisting texture
    VShutdown();
    
    if (path != "")
        mFontPath = path;
        
    m_pFont = TTF_OpenFont(mFontPath.c_str(), mFontSize);
    
    if (m_pFont == NULL)
    {
        printf("Button font not loaded! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    SDL_Surface* pSurface = TTF_RenderText_Blended(m_pFont, mText.c_str(), mColor);
    if (pSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    
    // Color key image
    SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0xFF, 0xFF, 0xFF));
    
    //Create texture from surface pixels
    mTexture = SDL_CreateTextureFromSurface(g_pRenderer->GetRenderer(), pSurface);
    if (mTexture == NULL)
    {
        printf("Unable to create texture from %s! SDL Error: %s\n", mText.c_str(), SDL_GetError());
    }
    else
    {
        mWidth = pSurface->w;
        mHeight = pSurface->h;
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(pSurface);
    
    return mTexture != NULL;
}

//
// Change the font size and trigger a reload of the texture
//
void SDLTextTexture::ChangeFontSize(int fontSize)
{
    mFontSize = fontSize;
    LoadTextTextureFromFile("");
}

//
// Change the text and trigger a reload of the texture
//
void SDLTextTexture::ChangeText(std::string text)
{
    mText = text;
    LoadTextTextureFromFile("");
}

//
// Change the font path and trigger a reload of the texture
//
void SDLTextTexture::ChangeFont(std::string path)
{
    mFontPath = path;
    LoadTextTextureFromFile("");
}

//
// Overrides SDLTexture's method to reload text texture when color is changed
//
void SDLTextTexture::VSetColor(Uint8 red, Uint8 green, Uint8 blue)
{
    mColor = { red, green, blue };
    LoadTextTextureFromFile("");
}
