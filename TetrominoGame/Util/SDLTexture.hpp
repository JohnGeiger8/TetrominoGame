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
protected:
    SDL_Texture* mTexture;
    SDL_Color mColor;
    
    int mWidth;
    int mHeight;
    Point mPosition;
    
public:
    SDLTexture();
    ~SDLTexture();
    
    virtual void VSetColor(Uint8 red, Uint8 green, Uint8 blue);
    virtual void VSetBlendMode(SDL_BlendMode blending);
    virtual void VSetAlpha(Uint8 alpha);
    
    void SetPosition(Point position) { mPosition = position; };
    
    Point GetPosition() { return mPosition; };
    int GetWidth() { return mWidth; };
    int GetHeight() { return mHeight; };
    
    // Implements interface
    virtual bool VLoadTextureFromFile(std::string path);
    virtual void VShutdown();
    virtual void VRender();
};

#endif /* SDLTexture_hpp */
