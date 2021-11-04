//
//  ITexture.hpp
//  TetrominoGame
//
//  Created by John Geiger on 11/4/21.
//
#pragma once

#ifndef ITexture_hpp
#define ITexture_hpp

#include <string>

//
// Interface for textures
//
class ITexture
{
    virtual bool VLoadTextureFromFile(std::string path)=0;
    virtual void VShutdown()=0;
    virtual void VRender()=0;
};

#endif /* ITexture_hpp */
