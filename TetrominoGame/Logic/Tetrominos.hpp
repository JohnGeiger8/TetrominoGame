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

using Tetromino = int;
using Rotation = int;
using TetrominosMatrix = std::vector<std::vector<std::vector<std::vector<int>>>>;
using InitialPositionsMatrix = std::vector<std::vector<std::vector<int>>>;

//
// Allows access to all tetrominos and their info from anywhere
//
namespace Tetrominos
{
    const int GetBlockType(Tetromino tetromino, Rotation rotation, int x, int y);
    const SDL_Color GetTetrominoColor(Tetromino tetromino);
    const int GetInitialPositionX(Tetromino tetromino, Rotation rotation);
    const int GetInitialPositionY(Tetromino tetromino, Rotation rotation);
};

#endif /* Tetrominos_hpp */
