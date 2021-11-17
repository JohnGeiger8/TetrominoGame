//
//  Resource.hpp
//  TetrominoGame
//
//  Created by John Geiger on 11/11/21.
//
#pragma once

#ifndef Resource_hpp
#define Resource_hpp

#include <string>

//
// Attaches extra data to a particular resource, such as the length and format of a sound file.
//
class IResourceExtraData
{
public:
    virtual std::string VToString()=0;
};

//
// Represents a resource for caching
//
class Resource
{
public:
    std::string mName;
    Resource(const std::string &name);
};

//
// Holds a Resource, its extra data, and its size
//
class ResourceHandle
{
protected:
    Resource mResource;
    unsigned int mSize;
    std::shared_ptr<IResourceExtraData> m_pExtra;

public:
    ResourceHandle(Resource &resource, unsigned int size);

    virtual ~ResourceHandle();

    const std::string GetName() { return mResource.mName; }
    unsigned int Size() const { return mSize; }

    std::shared_ptr<IResourceExtraData> GetExtra() { return m_pExtra; }
    void SetExtra(std::shared_ptr<IResourceExtraData> extra) { m_pExtra = extra; }
};

#endif /* Resource_hpp */
