//
//  Math.hpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/7.
//

#ifndef Math_hpp
#define Math_hpp

#include <stdio.h>
#include <vector>

#ifndef Point2D_hpp
#include "Point2D.hpp"
#endif

namespace math {

bool isLinesIntersect(Point2D l1p1, Point2D l1p2, Point2D l2p1, Point2D l2p2);

bool isPointInPolygon(Point2D p, std::vector<Point2D> & points);

double lerp(double s, double a, double b);
int lerp(double s, int a, int b);

double limit(double s, double a, double b);
int limit(int s, int a, int b);

bool isPointInAreaLURD(Point2D s, Point2D LU, Point2D RD);
bool isPointInAreaLDRU(Point2D s, Point2D LD, Point2D RU);

// Get overlapped length of 2 lines.
int getOverlapLength(int f1l, int f1r, int f2l, int f2r);

}

#endif /* Math_hpp */
