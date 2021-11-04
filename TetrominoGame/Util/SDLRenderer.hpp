//
//  SDLRenderer.hpp
//  TetrominoGame
//
//  Created by John Geiger on 10/13/21.
//

#ifndef SDLRenderer_hpp
#define SDLRenderer_hpp

#include <SDL2/SDL.h>
#include <memory>

//
// Wraps the SDL_Renderer class
//
class SDLRenderer
{
public:
    SDLRenderer(SDL_Window* pWindow);
    ~SDLRenderer();

    SDL_Renderer* GetRenderer() { return m_pRenderer; };
private:
    SDL_Renderer* m_pRenderer;
    
};

using SDLRendererPtr = std::shared_ptr<SDLRenderer>;
extern SDLRendererPtr g_pRenderer;

#endif /* SDLRenderer_hpp */
