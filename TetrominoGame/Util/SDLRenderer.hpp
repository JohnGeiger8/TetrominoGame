//
//  SDLRenderer.hpp
//  TetrominoGame
//
//  Created by John Geiger on 10/13/21.
//

#ifndef SDLRenderer_hpp
#define SDLRenderer_hpp

#include <SDL2/SDL.h>
#include "IRenderer.hpp"

//
// Represents an SDL Renderer, inheriting from IRenderer
//
class SDLRenderer : public IRenderer
{
public:
    virtual void VSetBackgroundColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
    virtual bool VOnRestore();
    virtual void VShutdown();
    virtual bool VPreRender();
    virtual bool VPostRender();

private:
    SDL_Renderer* m_pRenderer;
    
};

#endif /* SDLRenderer_hpp */
