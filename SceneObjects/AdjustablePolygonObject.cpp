//
//  AdjustablePolygonObject.cpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/6.
//

#include "AdjustablePolygonObject.hpp"

AdjustablePolygonObject::AdjustablePolygonObject(DrawingPolygonObject *dpo, PelAdjuster* pelAdjuster) : pelAdjuster(pelAdjuster)
{
    points = dpo->getPoints();
    if (points.size() == 0) return;
    int minX = 99999999, maxX = -99999999, minY = 99999999, maxY = -99999999;
    for (int i = 0; i < points.size(); i++)
    {
        minX = std::min(minX, points[i].x);
        maxX = std::max(maxX, points[i].x);
        minY = std::min(minY, points[i].y);
        maxY = std::max(maxY, points[i].y);
    }
    // Make location to the whole polyogn's left up.
    Point2D oldPivot = dpo->getLocation();
    location = Point2D(minX, minY) + oldPivot;
    //printf("New pivot is (%d, %d)\n", location.x, location.y);
    for (int i = 0; i < points.size(); i++)
    {
        points[i] = points[i] + oldPivot - location;
    }
    width = maxX - minX;
    height = maxY - minY;
}

AdjustablePolygonObject::AdjustablePolygonObject(AdjustablePolygonObject* obj)
{
    points = obj->points;
    if (points.size() == 0) return;
    location = obj->getLocation();
    width = obj->getWidth();
    height = obj->getHeight();
    pelAdjuster = obj->pelAdjuster;
    color = obj->color;
}

void AdjustablePolygonObject::repaint()
{
    SceneObject::repaint();
    if (points.size() == 0) return;
    
    // Draw all the lines, including floating line.
    glBegin(GL_POLYGON);
    glColor3f(color.r, color.g, color.b);
    for (int i = 0; i < points.size(); i++)
    {
        Point2D temp = getDisplayPoint(getAbsolutePoint(points[i].x, points[i].y));
        glVertex2i(temp.x, temp.y);
    }
    glEnd();
}

void AdjustablePolygonObject::resize(int width, int height)
{
    int oldWidth = getWidth();
    int oldHeight = getHeight();
    SceneObject::resize(width, height);
    for (int i = 0; i < points.size(); i++)
    {
        points[i].x = points[i].x * width / oldWidth;
        points[i].y = points[i].y * height / oldHeight;
    }
}

bool AdjustablePolygonObject::isPointInMe(int x, int y)
{
    return math::isPointInPolygon(getRelativePoint(x, y), points);
}

void AdjustablePolygonObject::onMouseDown(int x, int y)
{
    pelAdjuster->setMyMaster(this);
}
