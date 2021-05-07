//
//  SliderButton.cpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/7.
//

#include "SliderButton.hpp"

#define locationLU (Point2D(0, 0))
// #define SLIDER_BLOCK_WIDTH (std::min(std::max((width / 8), 16), 20))
#define SLIDER_BLOCK_WIDTH 16
#define SLIDER_RAIL_LENGTH (width - SLIDER_BLOCK_WIDTH)

SliderButton::SliderButton(Point2D locationLeftUp, Point2D locationRightDown)
: locationRD(locationRightDown - locationLeftUp)
{
    location = locationLeftUp;
    width = locationRD.x;
    height = locationRD.y;
    // 0 = lu, 1 = ld, 2 = rd, 3 = ru
    sliderRailPoints.push_back(Point2D(locationLU.x + SLIDER_BLOCK_WIDTH / 2,
                                       (locationRD.y + locationLU.y) / 2 - 5));
    sliderRailPoints.push_back(Point2D(locationLU.x + SLIDER_BLOCK_WIDTH / 2,
                                       (locationRD.y + locationLU.y) / 2 + 5));
    sliderRailPoints.push_back(Point2D(locationRD.x - SLIDER_BLOCK_WIDTH / 2,
                                       (locationRD.y + locationLU.y) / 2 + 5));
    sliderRailPoints.push_back(Point2D(locationRD.x - SLIDER_BLOCK_WIDTH / 2,
                                       (locationRD.y + locationLU.y) / 2 - 5));
    sliderBlockPoints.push_back(Point2D());
    sliderBlockPoints.push_back(Point2D());
    sliderBlockPoints.push_back(Point2D());
    sliderBlockPoints.push_back(Point2D());
    setPercentage(0.0);
}

void SliderButton::updateBlockDisplayPoints()
{
    sliderBlockPoints[0].x = sliderBlockPoints[1].x = math::lerp(currentValue, locationLU.x, locationRD.x - SLIDER_BLOCK_WIDTH);
    sliderBlockPoints[2].x = sliderBlockPoints[3].x = math::lerp(currentValue, locationLU.x + SLIDER_BLOCK_WIDTH, locationRD.x);
    sliderBlockPoints[0].y = sliderBlockPoints[3].y = locationLU.y;
    sliderBlockPoints[1].y = sliderBlockPoints[2].y = locationRD.y;
}

// Will transfer Relative location of click.
void SliderButton::onDragStart(int x, int y)
{
    if (math::isPointInPolygon(Point2D(x, y), sliderBlockPoints))
    {
        isDragging = true;
    }
}

// Will transfer offsets on 2 directions.
void SliderButton::onDragMove(int x, int y)
{
    printf("Drag move (%d, %d)\n", x, y);
    if (isDragging)
    {
        double delta = (double) x / SLIDER_RAIL_LENGTH;
        setPercentage(math::limit(currentValue + delta, 0.0, 1.0));
        // Now the [currentValue] should be changed.
        printf("Percentage to (%.2f)\n", currentValue);
        if (onPercentChange) onPercentChange(currentValue);
    }
}

void SliderButton::onDragStop(int x, int y)
{
    isDragging = false;
}

void SliderButton::repaint()
{
    DraggableSceneObject::repaint();
    Point2D temp;
    
    // The Rail inner
    glBegin(GL_POLYGON);
    glColor3f(railColor.r, railColor.g, railColor.b);
    for (int i = 0; i < sliderRailPoints.size(); i++)
    {
        temp = getDisplayPoint(getAbsolutePoint(sliderRailPoints[i].x, sliderRailPoints[i].y));
        glVertex2i(temp.x, temp.y);
    }
    glEnd();
    // The rail boarder
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    for (int i = 0; i < sliderRailPoints.size(); i++)
    {
        temp = getDisplayPoint(getAbsolutePoint(sliderRailPoints[i].x, sliderRailPoints[i].y));
        glVertex2i(temp.x, temp.y);
    }
    glEnd();
    
    // The block inner
    glBegin(GL_POLYGON);
    glColor3f(blockColor.r, blockColor.g, blockColor.b);
    for (int i = 0; i < sliderBlockPoints.size(); i++)
    {
        temp = getDisplayPoint(getAbsolutePoint(sliderBlockPoints[i].x, sliderBlockPoints[i].y));
        glVertex2i(temp.x, temp.y);
    }
    glEnd();
    // The block boarder
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    for (int i = 0; i < sliderBlockPoints.size(); i++)
    {
        temp = getDisplayPoint(getAbsolutePoint(sliderBlockPoints[i].x, sliderBlockPoints[i].y));
        glVertex2i(temp.x, temp.y);
    }
    glEnd();
    
    
}

void SliderButton::resize(int width, int height)
{
    SceneObject::resize(width, height);
    locationRD = Point2D(width, height);
    sliderRailPoints[0] = (Point2D(locationLU.x + SLIDER_BLOCK_WIDTH / 2,
                                       (locationRD.y + locationLU.y) / 2 - 5));
    sliderRailPoints[1] = (Point2D(locationLU.x + SLIDER_BLOCK_WIDTH / 2,
                                       (locationRD.y + locationLU.y) / 2 + 5));
    sliderRailPoints[2] = (Point2D(locationRD.x - SLIDER_BLOCK_WIDTH / 2,
                                       (locationRD.y + locationLU.y) / 2 + 5));
    sliderRailPoints[3] = (Point2D(locationRD.x - SLIDER_BLOCK_WIDTH / 2,
                                       (locationRD.y + locationLU.y) / 2 - 5));
    updateBlockDisplayPoints();
}

bool SliderButton::isPointInMe(int x, int y)
{
    return math::isPointInAreaLURD(Point2D(x, y),
                                   getAbsolutePoint(locationLU), getAbsolutePoint(locationRD));
}

#undef locationLU
