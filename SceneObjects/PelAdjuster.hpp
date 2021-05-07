//
//  PelAdjuster.hpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/7.
//

#ifndef PelAdjuster_hpp
#define PelAdjuster_hpp

#include "SystemIncludes.h"
#include "DraggableSceneObject.hpp"

class PelAdjusterScaler;
class PelAdjusterRotator;
class PelAdjuster;

class PelAdjusterScaler : public DraggableSceneObject
{
protected:
    Point2D scaleCenter;
    PelAdjuster* pa;
    
public:
    PelAdjusterScaler(Point2D scaleCenter, PelAdjuster* pa) : DraggableSceneObject(false),  scaleCenter(scaleCenter), pa(pa) { }
    
    virtual void retargetScaleCenter(Point2D scaleCenter)
    {
        this->scaleCenter = scaleCenter;
    }
    
    virtual void repaint();
    virtual bool isPointInMe(int x, int y);
    virtual void onDragStart(int x, int y) { }
    virtual void onDragMove(int x, int y);
    virtual void onDragStop(int x, int y) { }
};

class PelAdjusterRotator : public DraggableSceneObject
{
public:
    PelAdjusterRotator();
};

class PelAdjuster : public SceneObject
{
protected:
    // 0~3: LU, RU, RD, LD
    // 4~7: U, R, D, L
    PelAdjusterScaler* scalers[8];
    
    // 0~3: LU, RU, RD, LD
    PelAdjusterScaler* rotators[4];
    
    SceneObject* myMaster = nullptr;
    
    #define ADJUST_IDLE 0
    #define ADJUST_MOVE 1
    #define ADJUST_SCALE 2
    #define ADJUST_ROTATE 3
    int adjustMode = ADJUST_IDLE;
    SceneObject* mouseActionReceiver = nullptr;
    
    Point2D lastLocation;
    
public:
    PelAdjuster();
    virtual ~PelAdjuster();
    
    virtual void repaint();
    virtual void onMouseDown(int x, int y);
    virtual void onMouseMove(int x, int y);
    virtual void onMouseUp(int x, int y);
    
    virtual bool isPointInMe(int x, int y);
    
    virtual void setMyMaster(SceneObject* object);
    
    virtual SceneObject* getMyMaster() { return myMaster; }
    
    virtual void reshapeMyMaster(Point2D location, int width, int heigth);
    
    virtual void reposition(int x, int y);
    
};

#endif /* PelAdjuster_hpp */
