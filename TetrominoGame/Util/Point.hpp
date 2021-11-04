//
//  Point.hpp
//  TetrominoGame
//
//  Created by John Geiger on 11/4/21.
//
#pragma once

#ifndef Point_hpp
#define Point_hpp

class Point
{
public:
    Point() { x = 0; y = 0; };
    Point(int x, int y) : x(x), y(y) { };
    
    int x, y;
};

#endif /* Point_hpp */
