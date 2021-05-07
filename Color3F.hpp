//
//  Color3F.hpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/7.
//

#ifndef Color3F_hpp
#define Color3F_hpp

#include <stdio.h>

class Color3F
{
public:
    double r;
    double g;
    double b;
    
    Color3F(int r, int g, int b)
    {
        this->r = r / 255.0;
        this->g = g / 255.0;
        this->b = b / 255.0;
    }
    
    Color3F(double r, double g, double b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    
    Color3F() : r(0), g(0), b(0) { }
    
};

#endif /* Color3F_hpp */
