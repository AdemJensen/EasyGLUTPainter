//
//  BottomColorBar.cpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/7.
//

#include "BottomColorBar.hpp"

#define BCB_SECTION_LEFT_LX location.x
#define BCB_SECTION_LEFT_WIDTH (width / 6)
#define BCB_SECTION_LEFT_RX (BCB_SECTION_LEFT_WIDTH + location.x)

#define BCB_SECTION_RIGHT_WIDTH (width - BCB_SECTION_LEFT_WIDTH)
#define BCB_SECTION_RIGHT_LX BCB_SECTION_LEFT_RX
#define BCB_SECTION_RIGHT_RX (location.x + width)

#define BCB_SECTION_RIGHT_EACH_SLIDER_AREA_WIDTH (BCB_SECTION_RIGHT_WIDTH / 3)
// 4 deviders devides the 3 sliders.
#define BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_1 BCB_SECTION_RIGHT_LX
#define BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_2 (BCB_SECTION_RIGHT_LX + BCB_SECTION_RIGHT_EACH_SLIDER_AREA_WIDTH)
#define BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_3 (BCB_SECTION_RIGHT_LX + BCB_SECTION_RIGHT_EACH_SLIDER_AREA_WIDTH * 2)
#define BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_4 BCB_SECTION_RIGHT_RX

#define BCB_UY location.y
#define BCB_DY (location.y + height)
#define BCB_CHARACTER_VGAP (height - 13) / 2

BottomColorBar::BottomColorBar(int windowWidth, int windowHeight, int height)
{
    this->width = windowWidth;
    this->height = height;
    this->location = Point2D(0, windowHeight - height);
    
    redSlider = new SliderButton(Point2D(BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_1 + 32, BCB_UY + 10), Point2D(BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_2 - 10, BCB_DY - 10));
    greenSlider = new SliderButton(Point2D(BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_2 + 32, BCB_UY + 10), Point2D(BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_3 - 10, BCB_DY - 10));
    blueSlider = new SliderButton(Point2D(BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_3 + 32, BCB_UY + 10), Point2D(BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_4 - 10, BCB_DY - 10));
}

BottomColorBar::~BottomColorBar()
{
    delete redSlider;
    delete greenSlider;
    delete blueSlider;
}

void BottomColorBar::repaint()
{
    SceneObject::repaint();
    
    Point2D temp;
    
    // Paint panel
    glColor3f(panelBackgroundColor.r, panelBackgroundColor.g, panelBackgroundColor.b);
    glBegin(GL_POLYGON);
    temp = getDisplayPoint(location.x, location.y);
    glVertex2i(temp.x, temp.y);
    temp = getDisplayPoint(location.x + width, location.y);
    glVertex2i(temp.x, temp.y);
    temp = getDisplayPoint(location.x + width, location.y + height);
    glVertex2i(temp.x, temp.y);
    temp = getDisplayPoint(location.x, location.y + height);
    glVertex2i(temp.x, temp.y);
    glEnd();
    
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    temp = getDisplayPoint(location.x, location.y);
    glVertex2i(temp.x, temp.y);
    temp = getDisplayPoint(location.x + width, location.y);
    glVertex2i(temp.x, temp.y);
    glEnd();
    
    // Paint color block on the left
    Color3F currentColor = getColor();
    glColor3f(currentColor.r, currentColor.g, currentColor.b);
    glBegin(GL_POLYGON);
    temp = getDisplayPoint(BCB_SECTION_LEFT_LX + 20, BCB_UY + 10);
    glVertex2i(temp.x, temp.y);
    temp = getDisplayPoint(BCB_SECTION_LEFT_RX - 20, BCB_UY + 10);
    glVertex2i(temp.x, temp.y);
    temp = getDisplayPoint(BCB_SECTION_LEFT_RX - 20, BCB_DY - 10);
    glVertex2i(temp.x, temp.y);
    temp = getDisplayPoint(BCB_SECTION_LEFT_LX + 20, BCB_DY - 10);
    glVertex2i(temp.x, temp.y);
    glEnd();
    
    // Paint right sub panel
    redSlider->repaint();
    greenSlider->repaint();
    blueSlider->repaint();
    temp = getDisplayPoint(BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_1 + 15, BCB_DY - BCB_CHARACTER_VGAP);
    glRasterPos2i(temp.x, temp.y);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'R');
    temp = getDisplayPoint(BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_2 + 15, BCB_DY - BCB_CHARACTER_VGAP);
    glRasterPos2i(temp.x, temp.y);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'G');
    temp = getDisplayPoint(BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_3 + 15, BCB_DY - BCB_CHARACTER_VGAP);
    glRasterPos2i(temp.x, temp.y);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'B');
    
}

void BottomColorBar::onMouseDown(int x, int y)
{
    SceneObject::onMouseDown(x, y);
    
    if (redSlider->isPointInMe(x, y))
    {
        mouseDownObject = redSlider;
        redSlider->onMouseDown(x, y);
    }
    else if (greenSlider->isPointInMe(x, y))
    {
        mouseDownObject = greenSlider;
        greenSlider->onMouseDown(x, y);
    }
    else if (blueSlider->isPointInMe(x, y))
    {
        mouseDownObject = blueSlider;
        blueSlider->onMouseDown(x, y);
    }
}

void BottomColorBar::onMouseMove(int x, int y)
{
    SceneObject::onMouseMove(x, y);
    
    redSlider->onMouseMove(x, y);
    greenSlider->onMouseMove(x, y);
    blueSlider->onMouseMove(x, y);
}

void BottomColorBar::onMouseUp(int x, int y)
{
    SceneObject::onMouseUp(x, y);
    
    if (mouseDownObject) mouseDownObject->onMouseUp(x, y);
}


void BottomColorBar::onResizeWindow(int oldSizeX, int oldSizeY, int newSizeX, int newSizeY)
{
    this->width = newSizeX;
    this->location = Point2D(0, newSizeY - height);
    redSlider->reposition(BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_1 + 32, BCB_UY + 10);
    redSlider->resize((BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_2 - 10) - (BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_1 + 32), (BCB_DY - 10) - (BCB_UY + 10));
    greenSlider->reposition(BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_2 + 32, BCB_UY + 10);
    greenSlider->resize((BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_3 - 10) - (BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_2 + 32), (BCB_DY - 10) - (BCB_UY + 10));
    blueSlider->reposition(BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_3 + 32, BCB_UY + 10);
    blueSlider->resize((BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_4 - 10) - (BCB_SECTION_RIGHT_SLIDER_DEVIDER_X_3 + 32), (BCB_DY - 10) - (BCB_UY + 10));
    
}
