//
//  Timer.hpp
//  TetrominoGame
//
//  Created by John Geiger on 10/4/21.
//
#pragma once

#ifndef Timer_hpp
#define Timer_hpp

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

using namespace std;

//The application time based timer
class Timer
{
public:
    Timer();

    void Start();
    void Stop();
    void Pause();
    void Unpause();

    //Gets the timer's time
    Uint32 GetTicks();

    //Checks the status of the timer
    bool IsStarted();
    bool IsPaused();

private:
    //The clock time when the timer started
    Uint32 mStartTicks;

    //The ticks stored when the timer was paused
    Uint32 mPausedTicks;

    //The timer status
    bool mPaused;
    bool mStarted;
};


#endif /* Timer_hpp */
