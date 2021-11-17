//
//  Resource.cpp
//  TetrominoGame
//
//  Created by John Geiger on 11/11/21.
//

#include "Resource.hpp"

Resource::Resource(const std::string &name)
{
    mName = name;
    //std::transform(mName.begin(), mName.end(), mName.begin(), (int(*)(int)) std::tolower);
}

ResourceHandle::ResourceHandle(Resource &resource, unsigned int size)
    : mResource(resource)
{
    mSize = size;
}

ResourceHandle::~ResourceHandle()
{
    
}
