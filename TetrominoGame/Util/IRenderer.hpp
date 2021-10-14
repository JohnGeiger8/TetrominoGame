//
//  IRenderer.hpp
//  TetrominoGame
//
//  Created by John Geiger on 10/13/21.
//

#ifndef IRenderer_hpp
#define IRenderer_hpp

//
// Abstracts the renderer implementation
//
class IRenderer
{
public:
    virtual void VSetBackgroundColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a)=0;
    virtual bool VOnRestore()=0;
    virtual void VShutdown()=0;
    virtual bool VPreRender()=0;
    virtual bool VPostRender()=0;
};


#endif /* IRenderer_hpp */
