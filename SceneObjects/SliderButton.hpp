//
//  SliderButton.hpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/7.
//

#ifndef SliderButton_hpp
#define SliderButton_hpp

#include "SystemIncludes.h"

#ifndef DraggableSceneObject_hpp
#include "DraggableSceneObject.hpp"
#endif

class SliderButton : public DraggableSceneObject
{
protected:
    void (*onPercentChange)(double) = nullptr;
    
    bool isDragging = false;
    double currentValue = 0.0;
    
    // 0 = lu, 1 = ld, 2 = rd, 3 = ru
    std::vector<Point2D> sliderBlockPoints;
    // 0 = lu, 1 = ld, 2 = rd, 3 = ru
    std::vector<Point2D> sliderRailPoints;
    
    // Relative points.
    Point2D locationRD;
    
    void updateBlockDisplayPoints();
    
    Color3F railColor = Color3F(176, 196, 222);
    Color3F blockColor = Color3F(30, 144, 255);
    
public:
    
    SliderButton(Point2D locationLeftUp, Point2D locationRightDown);
    
    // Will transfer Relative location of click.
    virtual void onDragStart(int x, int y);
    
    // Will transfer offsets on 2 directions.
    virtual void onDragMove(int x, int y);
    
    // Will transfer Relative location of mouse up.
    virtual void onDragStop(int x, int y);
    
    // The int prameter will receive percent, within 0 and 1, calc from LB and UB.
    void bindPercentListener(void (*onPercentChange)(double))
    {
        this->onPercentChange = onPercentChange;
    }
    
    double getPercentage()
    {
        return currentValue;
    }
    
    void setPercentage(double percentage, bool repaint = true)
    {
        currentValue = math::limit(percentage, 0.0, 1.0);
        updateBlockDisplayPoints();
        if (repaint) glutPostRedisplay();
    }
    
    virtual void repaint();
    
    void resize(int width, int height);
    
    // Pass in an absolute point
    virtual bool isPointInMe(int x, int y);
    
};

#endif /* SliderButton_hpp */
