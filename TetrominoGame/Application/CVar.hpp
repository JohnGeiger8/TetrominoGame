//
//  CVar.hpp
//  TetrominoGame
//
//  Created by John Geiger on 11/1/21.
//
#pragma once

#ifndef CVar_hpp
#define CVar_hpp

#include <string>
#include <map>

enum CVarFlags
{
    CVAR_BOOL,          // variable is a boolean
    CVAR_INTEGER,       // variable is an integer
    CVAR_STRING,        // variable is a string
    CVAR_FLOAT,         // variable is a float
    CVAR_PERSISTENT     // variable should be saved to config file
};

class CVar
{
public:
    // Registers this variable with the global list of CVars
    CVar(std::string name, std::string value, std::string defaultValue, std::string description, int flags);
    CVar(std::string name, int value, int defaultValue, std::string description, int flags);
    CVar(std::string name, float value, float defaultValue, std::string description, int flags);
    CVar(std::string name, bool value, bool defaultValue, std::string description, int flags);

    int GetIntValue();
    std::string GetStringValue();
    float GetFloatValue();
    bool GetBoolValue();
    void SetIntValue(int value) { mValue = std::to_string(value); };
    void SetStringValue(std::string value) { mValue = value; };
    void SetFloatValue(float value) { mValue = std::to_string(value); };
    void SetBoolValue(bool value) { mValue = std::to_string(value); };
    void Reset();

private:
    
    int mFlags;                  // Describes type and nature of CVar
    std::string mValue;          // Holds the CVar's raw value
    std::string mDescription;    // Describes CVar
    std::string mDefaultValue;   // Holds the default value to reset the variable to
    
    bool Init(std::string name, std::string value, std::string defaultValue, std::string description, int flags);
};

// Global list of all CVars:
using GlobalsMap = std::map<std::string, CVar*>;
extern GlobalsMap g_cvars;

#endif /* CVar_hpp */
