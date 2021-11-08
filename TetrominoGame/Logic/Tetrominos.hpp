//
//  Tetrominos.hpp
//  TetrominoGame
//
//  Created by John Geiger on 10/1/21.
//
#pragma once

#ifndef Tetrominos_hpp
#define Tetrominos_hpp

#include <vector>
#include <SDL2/SDL.h>

using TetrominoType = int;
using Rotation = int;
using TetrominosMatrix = std::vector<std::vector<std::vector<std::vector<int>>>>;
using InitialPositionsMatrix = std::vector<std::vector<std::vector<int>>>;

//
// Allows access to all tetrominos and their info from anywhere
//
namespace Tetrominos
{
    const int GetBlockType(TetrominoType tetromino, Rotation rotation, int x, int y);
    const SDL_Color GetTetrominoColor(TetrominoType tetromino);
    const int GetInitialPositionX(TetrominoType tetromino, Rotation rotation);
    const int GetInitialPositionY(TetrominoType tetromino, Rotation rotation);
};

#endif /* Tetrominos_hpp */
