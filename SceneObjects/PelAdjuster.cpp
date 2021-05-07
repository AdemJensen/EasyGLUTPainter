//
//  PelAdjuster.cpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/7.
//

#include "PelAdjuster.hpp"

void PelAdjusterScaler::repaint()
{
    DraggableSceneObject::repaint();
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
}
bool PelAdjusterScaler::isPointInMe(int x, int y)
{
    return std::abs(getLocation().x - x) <= 8 && std::abs(getLocation().y - y) <= 8;
}
void PelAdjusterScaler::onDragMove(int x, int y)
{
    printf("%d\n", y);
    pa->reshapeMyMaster(pa->getMyMaster()->getLocation(), pa->getMyMaster()->getWidth() + x, pa->getMyMaster()->getHeight() + y);
}

PelAdjuster::PelAdjuster()
{
    scalers[0] = nullptr;
    scalers[1] = nullptr;
    scalers[2] = new PelAdjusterScaler(Point2D(), this);
    scalers[3] = nullptr;
    scalers[4] = nullptr;
    scalers[5] = nullptr;
    scalers[6] = nullptr;
    scalers[7] = nullptr;
    rotators[0] = nullptr;
    rotators[1] = nullptr;
    rotators[2] = nullptr;
    rotators[3] = nullptr;
}

PelAdjuster::~PelAdjuster()
{
    
}

void PelAdjuster::repaint()
{
    SceneObject::repaint();
    if (myMaster == nullptr) return;
    
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    Point2D temp = getDisplayPoint(location.x, location.y);
    glVertex2i(temp.x, temp.y);
    temp = getDisplayPoint(location.x + width, location.y);
    glVertex2i(temp.x, temp.y);
    temp = getDisplayPoint(location.x + width, location.y + height);
    glVertex2i(temp.x, temp.y);
    temp = getDisplayPoint(location.x, location.y + height);
    glVertex2i(temp.x, temp.y);
    glEnd();
    for (int i = 0; i < 8; i++)
    {
        if (scalers[i])
        {
            scalers[i]->repaint();
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (rotators[i])
        {
            rotators[i]->repaint();
        }
    }
    
}

void PelAdjuster::onMouseDown(int x, int y)
{
    if (adjustMode != ADJUST_IDLE)
    {
        printf("Wrong state at PelAdjuster: Mouse down while it's down!\n");
        return;
    }
    if (!myMaster)
    {
        printf("The target master of PelAdjuster is nullptr!\n");
        return;
    }
    for (int i = 0; i < 8; i++)
    {
        if (scalers[i] && scalers[i]->isPointInMe(x, y))
        {
            adjustMode = ADJUST_SCALE;
            mouseActionReceiver = scalers[i];
            mouseActionReceiver->onMouseDown(x, y);
            return;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (rotators[i] && rotators[i]->isPointInMe(x, y))
        {
            adjustMode = ADJUST_ROTATE;
            mouseActionReceiver = rotators[i];
            mouseActionReceiver->onMouseDown(x, y);
            return;
        }
    }
    lastLocation = Point2D(x, y);
    adjustMode = ADJUST_MOVE;
    mouseActionReceiver = this;
}

void PelAdjuster::onMouseMove(int x, int y)
{
    if (!mouseActionReceiver) return;
    if (mouseActionReceiver == this)
    {
        // Move logics
        Point2D newPosition = Point2D(x, y) - lastLocation + location;
        myMaster->reposition(newPosition.x, newPosition.y);
        this->reposition(newPosition.x, newPosition.y);
        lastLocation = Point2D(x, y);
    }
    else
    {
        // Rotator or Scaler
        mouseActionReceiver->onMouseMove(x, y);
    }
}

void PelAdjuster::onMouseUp(int x, int y)
{
    adjustMode = ADJUST_IDLE;
    if (mouseActionReceiver && mouseActionReceiver != this) mouseActionReceiver->onMouseUp(x, y);
    mouseActionReceiver = nullptr;
}

void PelAdjuster::setMyMaster(SceneObject* object)
{
    myMaster = object;
    if (object == nullptr)
    {
        width = 0;
        height = 0;
        location = Point2D();
    }
    else
    {
        width = object->getWidth();
        height = object->getHeight();
        reposition(object->getLocation().x, object->getLocation().y);
    }
}

void PelAdjuster::reshapeMyMaster(Point2D location, int width, int height)
{
    if (myMaster == nullptr) return;
    myMaster->reposition(location.x, location.y);
    myMaster->resize(width, height);
    reposition(location.x, location.y);
    resize(width, height);
}

bool PelAdjuster::isPointInMe(int x, int y)
{
    if (SceneObject::isPointInMe(x, y)) return true;
    for (int i = 0; i < 8; i++)
    {
        if (scalers[i] && scalers[i]->isPointInMe(x, y))
        {
            return true;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (rotators[i] && rotators[i]->isPointInMe(x, y))
        {
            return true;
        }
    }
    return false;
}

void PelAdjuster::reposition(int x, int y)
{
    SceneObject::reposition(x, y);
    
    Point2D temp = getAbsolutePoint(width, height);
    scalers[2]->reposition(temp.x, temp.y);
    scalers[2]->retargetScaleCenter(location);
}
