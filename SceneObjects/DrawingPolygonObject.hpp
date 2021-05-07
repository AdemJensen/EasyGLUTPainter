//
//  DrawingPolygonObject.hpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/6.
//

#ifndef DrawingPolygonObject_hpp
#define DrawingPolygonObject_hpp

#include "SystemIncludes.h"

#ifndef OperatorIconObject_hpp
#include "OperatorIconObject.hpp"
#endif

class DrawingPolygonObject : public SceneObject
{
protected:
    std::vector<Point2D> points;
    std::vector<OperationIconObject> opios;
    
    // Because this exists even when the location is invalid
    // So this one needs to be absolute!
    Point2D floatingPoint;
    
    bool drawComplete = false;
    
    double MAGNET_DIST = 5.0;

public:
    DrawingPolygonObject() : SceneObject() {  }
    virtual ~DrawingPolygonObject() {  }
    
    // Add a point into list.
    // Returns true if should stop (Will stop if this point overlaps the first).
    // If already stop, return false.
    bool addPoint(int x, int y);
    
    // Remove the last point from list.
    void removeLastPoint();
    
    // Set the floating point's position. Will be adjusted by magnet.
    // Returns true if the point gets magneted and will end.
    bool setFloatingPoint(int x, int y, Magnet magnet = 0);
    
    virtual void repaint();
    virtual bool isPointInMe(int x, int y) { return false; }
    
    // Get floating point.
    Point2D getFloatingPoint() { return floatingPoint; }
    
    // Get all points of this drawer.
    std::vector<Point2D> getPoints() { return points; }
    
    // Is draw complete.
    bool isDrawComplete() { return drawComplete; }
    
};

#endif /* DrawingPolygonObject_hpp */
