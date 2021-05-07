//
//  Point2D.hpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/6.
//

#ifndef Point2D_hpp
#define Point2D_hpp

#include <stdio.h>
#include <cmath>

class Point2D
{
public:
    int x;
    int y;

    inline Point2D(int x, int y) : x(x), y(y) { }
    inline Point2D() : x(0), y(0) { }
    
    inline double distance(Point2D point)
    {
        return sqrt((point.x - x) * (point.x - x) + (point.y - y) * (point.y - y));
    }
    
    bool operator == (const Point2D & point)
    {
        return x == point.x && y == point.y;
    }
    
    bool operator != (const Point2D & point)
    {
        return !(*this == point);
    }
    
    Point2D operator - (const Point2D & point)
    {
        return Point2D(x - point.x, y - point.y);
    }
    
    Point2D operator + (const Point2D & point)
    {
        return Point2D(x + point.x, y + point.y);
    }
    
};

#endif /* Point2D_hpp */
