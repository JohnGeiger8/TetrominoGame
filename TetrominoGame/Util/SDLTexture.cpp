//
//  SDLTexture.cpp
//  TetrominoGame
//
//  Created by John Geiger on 11/4/21.
//

#include <SDL2_image/SDL_image.h>
#include "SDLTexture.hpp"
#include "SDLRenderer.hpp"

SDLTexture::SDLTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
    mPosition = Point(0, 0);
}

//
// Call VShutdown
//
SDLTexture::~SDLTexture()
{
    VShutdown();
}

//
// Destroy texture and reset width/height
//
void SDLTexture::VShutdown()
{
    if(mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

//
// Load the texture from the given file path
//
bool SDLTexture::VLoadTextureFromFile(std::string path)
{
    //Get rid of preexisting texture
    VShutdown();

    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Color key image
        // FIXME: this doesn't really make sense
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(g_pRenderer->GetRenderer(), loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

    mTexture = newTexture;
    return mTexture != NULL;
}

//
// Sets SDL's texture color modulator
//
void SDLTexture::VSetColor(Uint8 red, Uint8 green, Uint8 blue)
{
    mColor = { red, green, blue, 0xFF };
//    SDL_SetTextureColorMod(mTexture, red, green, blue); // FIXME: What is this
}

//
// Sets SDL's blending mode
//
void SDLTexture::VSetBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture, blending);
}
        
//
// Set Texture alpha value
//
void SDLTexture::VSetAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

//
// Render texture to screen using SDL
//
void SDLTexture::VRender()
{
    SDL_Rect renderQuad = { mPosition.x, mPosition.y, mWidth, mHeight };

    //Set clip rendering dimensions
//    if (clip != NULL )
//    {
//        renderQuad.w = clip->w;
//        renderQuad.h = clip->h;
//    }

    SDL_RenderCopy(g_pRenderer->GetRenderer(), mTexture, NULL, &renderQuad);
}
