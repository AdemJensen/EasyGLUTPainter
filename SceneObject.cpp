//
//  SceneObject.cpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/6.
//

#include "SceneObject.hpp"


void SceneObject::repaint()
{
#ifdef DRAW_INTERACTIVE_DEBUG_FRAME
    if (drawInteractiveDebugFrame)
    {
        glBegin(GL_LINE_LOOP);
        glColor3f(1, 0, 0);
        Point2D temp = getDisplayPoint(location.x, location.y);
        glVertex2i(temp.x, temp.y);
        temp = getDisplayPoint(location.x + width, location.y);
        glVertex2i(temp.x, temp.y);
        temp = getDisplayPoint(location.x + width, location.y + height);
        glVertex2i(temp.x, temp.y);
        temp = getDisplayPoint(location.x, location.y + height);
        glVertex2i(temp.x, temp.y);
        glEnd();
    }
#endif
}
