//
//  CVar.cpp
//  TetrominoGame
//
//  Created by John Geiger on 11/1/21.
//

#include "CVar.hpp"
#include "String.hpp"

GlobalsMap g_cvars;

CVar::CVar(std::string name, std::string value, std::string defaultValue, std::string description, int flags)
{
    Init(name, value, defaultValue, description, flags);
}

CVar::CVar(std::string name, int value, int defaultValue, std::string description, int flags)
{
    Init(name, std::to_string(value), std::to_string(defaultValue), description, flags);
}

CVar::CVar(std::string name, float value, float defaultValue, std::string description, int flags)
{
    Init(name, std::to_string(value), std::to_string(defaultValue), description, flags);
}

CVar::CVar(std::string name, bool value, bool defaultValue, std::string description, int flags)
{
    Init(name, std::to_string(value), std::to_string(defaultValue), description, flags);
}

bool CVar::Init(std::string name, std::string value, std::string defaultValue, std::string description, int flags)
{
    mValue = value;
    mDefaultValue = defaultValue;
    mDescription = description;
    mFlags = flags;
    
    trim(mValue);
    trim(mDefaultValue);
    trim(mDescription);
    
    std::pair<std::string, CVar*> thisCvar = std::pair<std::string, CVar*>(name, this);
    g_cvars.insert(thisCvar);
    
    return true;
}

int CVar::GetIntValue()
{
    if (mFlags & CVAR_INTEGER)
        return std::stoi(mValue);
    else
        return std::stoi(mDefaultValue);
}

std::string CVar::GetStringValue()
{
    if (mFlags & CVAR_STRING)
        return mValue;
    else
        return mDefaultValue;
}

float CVar::GetFloatValue()
{
    if (mFlags & CVAR_FLOAT)
        return std::stof(mValue);
    else
        return std::stof(mDefaultValue);
}

bool CVar::GetBoolValue()
{
    if (mFlags & CVAR_BOOL)
        return mValue == "true";
    else
        return mDefaultValue == "true";
}

void CVar::Reset()
{
    mValue = mDefaultValue;
}
