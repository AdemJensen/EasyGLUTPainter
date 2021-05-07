//
//  Math.cpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/7.
//

#include "Math.hpp"

bool math::isLinesIntersect(Point2D l1p1, Point2D l1p2, Point2D l2p1, Point2D l2p2)
{
    //快速排斥实验
    if ((l1p1.x > l1p2.x ? l1p1.x : l1p2.x) < (l2p1.x < l2p2.x ? l2p1.x : l2p2.x) ||
        (l1p1.y > l1p2.y ? l1p1.y : l1p2.y) < (l2p1.y < l2p2.y ? l2p1.y : l2p2.y) ||
        (l2p1.x > l2p2.x ? l2p1.x : l2p2.x) < (l1p1.x < l1p2.x ? l1p1.x : l1p2.x) ||
        (l2p1.y > l2p2.y ? l2p1.y : l2p2.y) < (l1p1.y < l1p2.y ? l1p1.y : l1p2.y))
    {
        return false;
    }
    //跨立实验
    if ((((l1p1.x - l2p1.x) * (l2p2.y - l2p1.y) - (l1p1.y - l2p1.y) * (l2p2.x - l2p1.x)) *
        ((l1p2.x - l2p1.x) * (l2p2.y - l2p1.y) - (l1p2.y - l2p1.y) * (l2p2.x - l2p1.x))) > 0 ||
        (((l2p1.x - l1p1.x) * (l1p2.y - l1p1.y) - (l2p1.y - l1p1.y) * (l1p2.x - l1p1.x)) *
        ((l2p2.x - l1p1.x) *(l1p2.y - l1p1.y) - (l2p2.y - l1p1.y) * (l1p2.x - l1p1.x))) > 0)
    {
        return false;
    }
    return true;
}

bool math::isPointInPolygon(Point2D p, std::vector<Point2D> & points)
{
    // 交点个数
    int nCross = 0;
    for (int i = 0; i < points.size(); i++)
    {
        Point2D p1 = points[i];
        Point2D p2 = points[(i + 1) % points.size()];// 点P1与P2形成连线
 
        if (p1.y == p2.y) continue;
        if (p.y < std::min(p1.y, p2.y)) continue;
        if (p.y >= std::max(p1.y, p2.y)) continue;
        // 求交点的x坐标（由直线两点式方程转化而来）
 
        double x = (double)(p.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;
 
        // 只统计p1p2与p向右射线的交点
        if (x > p.x) nCross++;
 
    }
 
    // 交点为偶数，点在多边形之外
    // 交点为奇数，点在多边形之内
    if ((nCross % 2) == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

#define LERP(s, a, b) (a + s * (b - a));
double math::lerp(double s, double a, double b)
{
    return LERP(s, a, b);
}
int math::lerp(double s, int a, int b)
{
    return LERP(s, a, b);
}
#undef LERP

#define LIMIT(s, a, b) (std::max(std::min(b, s), a));
double math::limit(double s, double a, double b)
{
    return LIMIT(s, a, b);
}
int math::limit(int s, int a, int b)
{
    return LIMIT(s, a, b);
}
#undef LIMIT

bool math::isPointInAreaLURD(Point2D s, Point2D LU, Point2D RD)
{
    return s.x >= LU.x && s.x <= RD.x && s.y >= LU.y && s.y <= RD.y;
}
bool math::isPointInAreaLDRU(Point2D s, Point2D LD, Point2D RU)
{
    return s.x >= LD.x && s.x <= RU.x && s.y >= RU.y && s.y <= LD.y;
}

int math::getOverlapLength(int f1l, int f1r, int f2l, int f2r)
{
    int resultBase = 1;
    if (f2r < f2l)
    {
        std::swap(f2l, f2r);
        resultBase *= -1;
    }
    if (f1r < f1l)
    {
        std::swap(f1l, f1r);
        resultBase *= -1;
    }
    if (f1l > f2l)
    {
        // We limit the situations down to: f2 is always on the f1's right hand side.
        std::swap(f1l, f2l);
        std::swap(f1r, f2r);
    }
    // Now, let's judge the [f2's left] and [f1's right]
    if (f2l > f1r) return 0;
    else
    {
        // f2 and f1 are intersected.
        return (std::min(f2r, f1r) - f2l) * resultBase;
    }
    
}
