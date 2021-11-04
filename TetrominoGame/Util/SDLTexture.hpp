//
//  SDLTexture.hpp
//  TetrominoGame
//
//  Created by John Geiger on 11/4/21.
//
#pragma once

#ifndef SDLTexture_hpp
#define SDLTexture_hpp

#include <SDL2/SDL.h>
#include "ITexture.hpp"
#include "Point.hpp"

class SDLTexture : public ITexture
{
    SDL_Texture* mTexture;
    
    int mWidth;
    int mHeight;
    Point mPosition;
    
public:
    SDLTexture();
    ~SDLTexture();
    
    void SetColor(Uint8 red, Uint8 green, Uint8 blue);
    void SetBlendMode(SDL_BlendMode blending);
    void SetAlpha(Uint8 alpha);
    
    int GetWidth() { return mWidth; };
    int GetHeight() { return mHeight; };
    
    // Implements interface
    virtual bool VLoadTextureFromFile(std::string path);
    virtual void VShutdown();
    virtual void VRender();
};

#endif /* SDLTexture_hpp */
