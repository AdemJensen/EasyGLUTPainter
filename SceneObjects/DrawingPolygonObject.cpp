//
//  DrawingPolygonObject.cpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/6.
//

#include "DrawingPolygonObject.hpp"

bool DrawingPolygonObject::addPoint(int x, int y)
{
    if (drawComplete) return false;
    if (points.size() == 0) {
        location = Point2D(x, y);
        points.push_back(Point2D(0, 0));
        opios.push_back(OperationIconObject(x, y));
        return false;
    }
    else
    {
        if (points.size() != 1 && getRelativePoint(x, y) == points[0])
        {
            // not adding an duplicated opio.
            drawComplete = true;
            return true;
        }
        else
        {
            Point2D relativeLoc = getRelativePoint(x, y);
            points.push_back(relativeLoc);
            opios.push_back(OperationIconObject(x, y));
            return false;
        }
    }
}

void DrawingPolygonObject::removeLastPoint()
{
    if (points.size() == 0 || drawComplete) return;
    points.pop_back();
    opios.pop_back();
}

bool DrawingPolygonObject::setFloatingPoint(int x, int y, Magnet magnet)
{
    floatingPoint = Point2D(x, y);
    if (points.size() == 0) return false;
    if (isMagnetEnabled(MAGNET_STARTING_POINT, magnet))
    {
        if (floatingPoint.distance(getAbsolutePoint(points[0])) < MAGNET_DIST)
        {
            floatingPoint = getAbsolutePoint(points[0]);
            return true;
        }
        return false;
    }
    Point2D lastPoint = getAbsolutePoint(points[points.size() - 1]);
    if (isMagnetEnabled(MAGNET_VERTICAL, magnet) && isMagnetEnabled(MAGNET_HORIZONTAL, magnet))
    {
        int distY = std::abs(lastPoint.x - x); // Dist to Y axis.
        int distX = std::abs(lastPoint.y - y);
        if (distX > distY)
        {
            // Magnets to Y axis, the x remains unchanged.
            floatingPoint.x = lastPoint.x;
        }
        else
        {
            // Magnets to X axis, the y remains unchanged.
            floatingPoint.y = lastPoint.y;
        }
        return false;
    }
    if (isMagnetEnabled(MAGNET_VERTICAL, magnet))
    {
        // Magnets to Y axis, the x remains unchanged.
        floatingPoint.x = lastPoint.x;
        return false;
    }
    if (isMagnetEnabled(MAGNET_HORIZONTAL, magnet))
    {
        // Magnets to X axis, the y remains unchanged.
        floatingPoint.y = lastPoint.y;
        return false;
    }
    return false;
}

void DrawingPolygonObject::repaint()
{
    SceneObject::repaint();
    if (points.size() == 0) return;
    
    // Draw all the lines, including floating line.
    glBegin(GL_LINE_STRIP);
    glColor3f(0, 0, 0);
    // glLineWidth(1);
    Point2D temp = getDisplayPoint(getAbsolutePoint(points[0].x, points[0].y));
    glVertex2i(temp.x, temp.y);
    for (int i = 1; i < points.size(); i++)
    {
        // There is a bug on drawing lines.
        // If 2 lines gets to close, it will be set to (0, 0)
        // Therefore we need a distance check to avoid that.
        if (points[i - 1].distance(points[i]) < 2) continue;
        temp = getDisplayPoint(getAbsolutePoint(points[i].x, points[i].y));
        glVertex2i(temp.x, temp.y);
    }
    temp = getDisplayPoint(floatingPoint);
    glVertex2i(temp.x, temp.y);
    glEnd();
    
    // Draw opios.
    for (int i = 0; i < opios.size(); i++)
    {
        opios[i].repaint();
    }
    
    // DEBUG: floating point.
    OperationIconObject(floatingPoint.x, floatingPoint.y).repaint();
    
}
