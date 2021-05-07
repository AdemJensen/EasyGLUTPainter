//
//  DraggableSceneObject.hpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/7.
//

#ifndef DraggableSceneObject_hpp
#define DraggableSceneObject_hpp

#include "SystemIncludes.h"

class DraggableSceneObject : virtual public SceneObject
{
private:
    bool isDragging = false;
    int lastX, lastY;
    
    bool countOverlapOnly = true;
    
protected:
    
    // Will transfer Relative location of click.
    virtual void onDragStart(int x, int y) = 0;
    
    // Will transfer offsets on 2 directions.
    virtual void onDragMove(int x, int y) = 0;
    
    // Will transfer Relative location of mouse up.
    virtual void onDragStop(int x, int y) = 0;

public:
    
    DraggableSceneObject(bool countOverlapOnly = true) : countOverlapOnly(countOverlapOnly) { }
    
    // Will transfer absolute location of mouse down.
    virtual void onMouseDown(int x, int y);
    
    // Will transfer absolute location of mouse move.
    virtual void onMouseMove(int x, int y);
    
    // Will transfer absolute location of mouse up.
    virtual void onMouseUp(int x, int y);
    
    virtual void repaint();
    
};

#endif /* DraggableSceneObject_hpp */
