//
//  AdjustablePolygonObject.hpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/6.
//

#ifndef AdjustablePolygonObject_hpp
#define AdjustablePolygonObject_hpp

#include "SystemIncludes.h"

#ifndef DrawingPolygonObject_hpp
#include "DrawingPolygonObject.hpp"
#endif

#ifndef OperatorIconObject_hpp
#include "OperatorIconObject.hpp"
#endif

#ifndef PelAdjuster_hpp
#include "PelAdjuster.hpp"
#endif

class AdjustablePolygonObject : public SceneObject
{
protected:
    std::vector<Point2D> points;
    
    Color3F color;
    
    PelAdjuster* pelAdjuster;
    
    // Displays the mark of 8 points and frame.
    bool briefAdjustMode = false;
    
    // Displays all the adjustment points.
    bool detailedAdjustMode = false;
    
public:
    AdjustablePolygonObject() : SceneObject()
    {
        setColor(0, 0, 0);
    }
    virtual ~AdjustablePolygonObject() {  }
    
    AdjustablePolygonObject(DrawingPolygonObject *dpo, PelAdjuster* pelAdjuster);
    
    AdjustablePolygonObject(AdjustablePolygonObject* obj);
    
    virtual void repaint();
    
    void setColor(Color3F color) { this->color = color; }
    void setColor(int r, int g, int b) { this->color = Color3F(r, g, b); }
    void setColor(double r, double g, double b) { this->color = Color3F(r, g, b); }
    Color3F getColor() { return color; }
    
    virtual void onMouseDown(int x, int y);
    
    virtual bool isPointInMe(int x, int y);
    
    void setPelAdjuster(PelAdjuster* pelAdjuster) { this->pelAdjuster = pelAdjuster; }
    
    virtual void resize(int width, int height);
    
};

#endif /* AdjustablePolygonObject_hpp */
