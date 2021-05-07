//
//  DraggableSceneObject.cpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/7.
//

#include "DraggableSceneObject.hpp"

// Will transfer absolute location of mouse down.
void DraggableSceneObject::onMouseDown(int x, int y)
{
    SceneObject::onMouseDown(x, y);
    isDragging = true;
    lastX = x;
    lastY = y;
    Point2D locationOfClick = getRelativePoint(x, y);
    onDragStart(locationOfClick.x, locationOfClick.y);
}

// Will transfer absolute location of mouse move.
void DraggableSceneObject::onMouseMove(int x, int y)
{
    SceneObject::onMouseMove(x, y);
    if (!isDragging) return;
    int newX = x, newY = y;
    if (countOverlapOnly)
    {
        printf("Frag (%d, %d), (%d, %d)\n", lastX, newX, location.x, location.x + width);
        int ovx = math::getOverlapLength(lastX, newX, location.x, location.x + width);
        int ovy = math::getOverlapLength(lastY, newY, location.y, location.y + height);
        onDragMove(ovx, ovy);
    }
    else
    {
        onDragMove(x - lastX, y - lastY);
    }
    lastX = newX;
    lastY = newY;
}

// Will transfer absolute location of mouse up.
void DraggableSceneObject::onMouseUp(int x, int y)
{
    SceneObject::onMouseUp(x, y);
    if (!isDragging) return;
    Point2D locationOfClick = getRelativePoint(x, y);
    onDragStop(locationOfClick.x, locationOfClick.y);
    isDragging = false;
}

void DraggableSceneObject::repaint()
{
    SceneObject::repaint();
}
