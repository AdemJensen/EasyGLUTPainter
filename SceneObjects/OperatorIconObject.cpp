//
//  OperatorIconObject.cpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/6.
//

#include "OperatorIconObject.hpp"

OperationIconObject::OperationIconObject(int x, int y) : SceneObject(x, y)
{
    
}

void OperationIconObject::repaint()
{
    SceneObject::repaint();
    // double color[3] = { 72, 61, 139 };
    glBegin(GL_POLYGON);
    glColor3f(0.72, 0.61, 0.139);
    glLineWidth(2);
    Point2D point1 = getDisplayPoint(getAbsolutePoint(-3, -3));
    Point2D point2 = getDisplayPoint(getAbsolutePoint(-3, 3));
    Point2D point3 = getDisplayPoint(getAbsolutePoint(3, 3));
    Point2D point4 = getDisplayPoint(getAbsolutePoint(3, -3));
    glVertex2i(point1.x, point1.y);
    glVertex2i(point2.x, point2.y);
    glVertex2i(point3.x, point3.y);
    glVertex2i(point4.x, point4.y);
    glEnd();
    // printf("DEBUG PAINT OPIO: (%d, %d)\n", location.x, location.y);
}
