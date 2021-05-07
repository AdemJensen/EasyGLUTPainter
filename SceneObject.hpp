//
//  SceneObject.hpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/6.
//

#define DRAW_INTERACTIVE_DEBUG_FRAME

#ifndef SceneObject_hpp
#define SceneObject_hpp

#include "SystemIncludes.h"

class SceneObject
{
#ifdef DRAW_INTERACTIVE_DEBUG_FRAME
private:
    bool drawInteractiveDebugFrame = false;
#endif
    
protected:
    Point2D location;   // The location of first point.
    
    int width = 0;
    int height = 0;
    
public:
    
    SceneObject() : location() { }
    SceneObject(Point2D point) : location(point.x, point.y) { }
    SceneObject(int x, int y) : location(x, y) { }
    
    virtual ~SceneObject() {  }
    
    // Get an absolute display location in scene by absolute location in storage.
    inline Point2D getDisplayPoint(int x, int y)
    {
        return Point2D(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
    }
    
    // Get an absolute display location in scene by absolute location in storage.
    inline Point2D getDisplayPoint(Point2D point)
    {
        return Point2D(point.x, glutGet(GLUT_WINDOW_HEIGHT) - point.y);
    }
    
    // Get an absolute location in scene by relative location.
    inline Point2D getAbsolutePoint(int x, int y)
    {
        return Point2D(x + getLocation().x, y + getLocation().y);
    }
    
    // Get an absolute location in scene by relative location.
    inline Point2D getAbsolutePoint(Point2D point)
    {
        return Point2D(point.x + getLocation().x, point.y + getLocation().y);
    }
    
    // Get an relative location in scene by relative location.
    inline Point2D getRelativePoint(int x, int y)
    {
        return Point2D(x - getLocation().x, y - getLocation().y);
    }
    
    // Get an relative location in scene by relative location.
    inline Point2D getRelativePoint(Point2D point)
    {
        return Point2D(point.x - getLocation().x, point.y - getLocation().y);
    }
    
    // Get location.
    virtual Point2D getLocation() { return location; }
    virtual void reposition(int x, int y) { location = Point2D(x, y); }
    
    virtual int getWidth() { return width; }
    virtual int getHeight() { return height; }
    virtual void resize(int width, int height)
    {
        this->width = width;
        this->height = height;
    }
    
    // Called by GL display func.
    // Use OpenGL functions please.
    virtual void repaint() = 0;
    
    // Will transfer absolute location of mouse down.
    virtual void onMouseDown(int x, int y) { }
    
    // Will transfer absolute location of mouse move.
    virtual void onMouseMove(int x, int y)
    {
#ifdef DRAW_INTERACTIVE_DEBUG_FRAME
        drawInteractiveDebugFrame = isPointInMe(x, y);
        // if (drawInteractiveDebugFrame) printf("Now drawing debug frame.\n");
#endif
    }
    
    // Will transfer absolute location of mouse up.
    virtual void onMouseUp(int x, int y) { }
    
    // On master window resized.
    virtual void onResizeWindow(int oldSizeX, int oldSizeY, int newSizeX, int newSizeY) { }
    
    // Pass in an absolute point
    virtual bool isPointInMe(int x, int y)
    {
        return math::isPointInAreaLURD(Point2D(x, y), location, location + Point2D(width, height));
    }
    
};

#endif /* SceneObject_hpp */
