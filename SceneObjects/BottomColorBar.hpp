//
//  BottomColorBar.hpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/7.
//

#ifndef BottomColorBar_hpp
#define BottomColorBar_hpp

#include "SystemIncludes.h"

#ifndef SliderButton_hpp
#include "SliderButton.hpp"
#endif

class BottomColorBar : public SceneObject
{
protected:
    std::vector<Point2D> basePanelPoints;
    std::vector<Point2D> colorIndicatorPoints;
    SliderButton* redSlider = nullptr;
    SliderButton* greenSlider = nullptr;
    SliderButton* blueSlider = nullptr;
    
    SliderButton* mouseDownObject = nullptr;
    
    Color3F panelBackgroundColor = Color3F(255, 240, 245);
    
public:
    
    BottomColorBar(int windowWidth, int windowHeight, int height);
    virtual ~BottomColorBar();
    
    Color3F getColor() { return Color3F(redSlider->getPercentage(), greenSlider->getPercentage(), blueSlider->getPercentage()); }
    void setColor(Color3F color) {
        redSlider->setPercentage(color.r);
        greenSlider->setPercentage(color.g);
        blueSlider->setPercentage(color.b);
    }
    
    virtual void repaint();
    virtual void onMouseDown(int x, int y);
    virtual void onMouseMove(int x, int y);
    virtual void onMouseUp(int x, int y);
    
    // On master window resized.
    virtual void onResizeWindow(int oldSizeX, int oldSizeY, int newSizeX, int newSizeY);
    
};

#endif /* BottomColorBar_hpp */
