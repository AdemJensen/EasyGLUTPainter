#define GL_SILENCE_DEPRECATION
#define GL
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include <iostream>
#include <vector>

#include "Variables.h"

#include "SystemIncludes.h"

#include "SceneObjects/OperatorIconObject.hpp"
#include "SceneObjects/DrawingPolygonObject.hpp"
#include "SceneObjects/AdjustablePolygonObject.hpp"
#include "SceneObjects/SliderButton.hpp"
#include "SceneObjects/BottomColorBar.hpp"

OperationIconObject opio = OperationIconObject(0, 0);

// Back is the top.
std::vector<SceneObject*> objects;

void masterDrawFunction()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);       //设置背景色 (R,G,B,alpha)
    glMatrixMode(GL_PROJECTION);            //投影
    glClear(GL_COLOR_BUFFER_BIT);           // 清空原颜色
    glColor3f(1.0, 0.0, 0.0);

    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->repaint();
    }
    
    pa->repaint();
    dpo->repaint();
    bcb->repaint();
    
    glFlush();
}

// 鼠标移动
void onMouseMove(int x, int y) {//坐标转换
    //printf("Mouse move at location (%d, %d)\n", x, y);
    if (programState == PS_DRAWING && !((DrawingPolygonObject*) dpo)->isDrawComplete())
    {
        if (X_KEY_DOWN)
        {
            ((DrawingPolygonObject*) dpo)->setFloatingPoint(x, y, MAGNET_VERTICAL | MAGNET_HORIZONTAL);
        }
        else
        {
            ((DrawingPolygonObject*) dpo)->setFloatingPoint(x, y, MAGNET_STARTING_POINT);
        }
    }
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->onMouseMove(x, y);
    }
    pa->onMouseMove(x, y);
    bcb->onMouseMove(x, y);
    if (pa->getMyMaster() == nullptr)
    {
        mainColor = bcb->getColor();
    }
    else
    {
        ((AdjustablePolygonObject*) pa->getMyMaster())->setColor(bcb->getColor());
    }
    glutPostRedisplay();
}


// 鼠标
void onMouseButton(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {//鼠标按下
        LEFT_MOUSE_BUTTON_DOWN = true;
        //printf("Mouse down at location (%d, %d)\n", x, y);
        if (bcb->isPointInMe(x, y))
        {
            MOUSE_DOWN_OBJECT = bcb;
            bcb->onMouseDown(x, y);
        }
        else
        {
            if (programState == PS_DRAWING)
            {
                MOUSE_DOWN_OBJECT = nullptr;
                Point2D floatingPoint = dpo->getFloatingPoint();
                bool res = dpo->addPoint(floatingPoint.x, floatingPoint.y);
                if (res)
                {
                    AdjustablePolygonObject* temp = new AdjustablePolygonObject(dpo, pa);
                    temp->setColor(bcb->getColor());
                    objects.push_back(temp);
                    delete dpo;
                    dpo = new DrawingPolygonObject();
                    programState = PS_IDLE;
                }
            }
            else
            {
                if (pa->isPointInMe(x, y))
                {
                    MOUSE_DOWN_OBJECT = pa;
                    pa->onMouseDown(x, y);
                }
                else
                {
                    bool notTriggered = true;
                    for (int i = (int) objects.size() - 1; i >= 0 ; i--)
                    {
                        if (objects[i]->isPointInMe(x, y))
                        {
                            MOUSE_DOWN_OBJECT = objects[i];
                            objects[i]->onMouseDown(x, y);
                            Color3F temp3 = ((AdjustablePolygonObject*) objects[i])->getColor();
                            bcb->setColor(((AdjustablePolygonObject*) objects[i])->getColor());
                            notTriggered = false;
                            break;
                        }
                    }
                    if (notTriggered)
                    {
                        MOUSE_DOWN_OBJECT = nullptr;
                        pa->setMyMaster(nullptr);
                        bcb->setColor(mainColor);
                    }
                }
            }
        }
        glutPostRedisplay();
    }
    else
    {
        if (MOUSE_DOWN_OBJECT) MOUSE_DOWN_OBJECT->onMouseUp(x, y);
    }
}

bool isInObjectList(SceneObject* obj)
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (obj == objects[i]) return true;
    }
    return false;
}

void removeFromObjectList(SceneObject* obj)
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (obj == objects[i])
        {
            objects.erase(objects.begin() + i);
            return;
        }
    }
}

// 键盘按下
void onKeyDown(unsigned char key, int x, int y)
{
    switch (key) {
        case 'x':
            X_KEY_DOWN = true;
            if (programState == PS_IDLE)
            {
                if (!isInObjectList(copyPasteBoard))
                {
                    delete copyPasteBoard;
                }
                copyPasteBoard = (AdjustablePolygonObject*) pa->getMyMaster();
                pa->setMyMaster(nullptr);
                bcb->setColor(mainColor);
                removeFromObjectList(copyPasteBoard);
                glutPostRedisplay();
            }
            break;
        case 'd':
            if (programState == PS_IDLE)
            {
                SceneObject* objToRemove = pa->getMyMaster();
                if (copyPasteBoard == objToRemove) copyPasteBoard = nullptr;
                removeFromObjectList(objToRemove);
                pa->setMyMaster(nullptr);
                bcb->setColor(mainColor);
                delete objToRemove;
                glutPostRedisplay();
            }
            break;
        case 'q':
            programState = PS_DRAWING;
            pa->setMyMaster(nullptr);
            break;
        case 'w':
            programState = PS_IDLE;
            break;
        case 'z':
            if (programState == PS_DRAWING)
            {
                dpo->removeLastPoint();
                glutPostRedisplay();
            }
            break;
        case 'c':
            if (programState == PS_IDLE)
            {
                if (!isInObjectList(copyPasteBoard))
                {
                    delete copyPasteBoard;
                }
                copyPasteBoard = (AdjustablePolygonObject*) pa->getMyMaster();
            }
            break;
        case 'v':
            if (programState == PS_IDLE && copyPasteBoard)
            {
                AdjustablePolygonObject* obj = new AdjustablePolygonObject(copyPasteBoard);
                objects.push_back(obj);
                obj->reposition(x, y);
                pa->setMyMaster(obj);
                bcb->setColor(obj->getColor());
                glutPostRedisplay();
            }
            break;
        case 'u':   // Move up
            if (programState == PS_IDLE && pa->getMyMaster())
            {
                SceneObject* temp = pa->getMyMaster();
                for (int i = 0; i < objects.size() - 1; i++)
                {
                    if (objects[i] == temp)
                    {
                        std::swap(objects[i], objects[i + 1]);
                        glutPostRedisplay();
                        break;
                    }
                }
            }
            break;
        case 'j':   // Move down
            if (programState == PS_IDLE && pa->getMyMaster())
            {
                SceneObject* temp = pa->getMyMaster();
                for (int i = 1; i < objects.size(); i++)
                {
                    if (objects[i] == temp)
                    {
                        std::swap(objects[i], objects[i - 1]);
                        glutPostRedisplay();
                        break;
                    }
                }
            }
            break;
            
        default:
            break;
    }
}

// 键盘弹起
void onKeyUp(unsigned char key, int x, int y)
{
    switch (key) {
        case 'x':
            X_KEY_DOWN = false;
            break;
            
        default:
            break;
    }
}

// 窗口大小改变时调用
void onWindowSizeChanged(GLsizei w, GLsizei h) {
    if (w < MinWindowWidth || h < MinWindowHeight)
    {
        w = std::max(MinWindowWidth, w);
        h = std::max(MinWindowHeight, h);
    }
    int oldWindowWidth = NowWindowWidth;
    int oldWindowHeight = NowWindowHeight;
    NowWindowWidth = w;
    NowWindowHeight = h;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, NowWindowWidth, 0.0, NowWindowHeight);
    
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->onResizeWindow(oldWindowWidth, oldWindowHeight, NowWindowWidth, NowWindowHeight);
    }
    
}

int main(int argc, char ** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(400, 400);

    glutInitWindowSize(DefaultWindowWidth, DefaultWindowHeight);
   
    glutCreateWindow("EasyPainter");
   
    glutDisplayFunc(masterDrawFunction);
    glutReshapeFunc(onWindowSizeChanged);   // 窗口变化时使图形不会发生变形
    glutMotionFunc(onMouseMove);            // 注册鼠标移动
    glutPassiveMotionFunc(onMouseMove);     // 注册鼠标移动
    glutMouseFunc(onMouseButton);           // 鼠标点击
    glutKeyboardFunc(onKeyDown);            // 键盘按下
    glutKeyboardUpFunc(onKeyUp);            // 键盘弹起
    
    dpo = new DrawingPolygonObject();
    bcb = new BottomColorBar(NowWindowWidth, NowWindowHeight, 50);
    pa = new PelAdjuster();
    
    glutMainLoop();
    
    for (int i = 0; i < objects.size(); i++)
    {
        delete objects[i];
    }
    delete bcb;
    delete dpo;
    delete pa;
    delete copyPasteBoard;
}
