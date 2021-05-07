//
//  Variables.h
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/6.
//

#ifndef Variables_h
#define Variables_h

#ifndef SceneObject_hpp
#include "SceneObject.hpp"
#endif

#ifndef PelAdjuster_hpp
#include "SceneObjects/PelAdjuster.hpp"
#endif

#ifndef BottomColorBar_hpp
#include "SceneObjects/BottomColorBar.hpp"
#endif

#ifndef DrawingPolygonObject_hpp
#include "SceneObjects/DrawingPolygonObject.hpp"
#endif

#ifndef AdjustablePolygonObject_hpp
#include "SceneObjects/AdjustablePolygonObject.hpp"
#endif

enum ProgramState
{
    PS_IDLE, PS_DRAWING, PS_SCALING, PS_MOVING, PS_ROTATING
};

int DefaultWindowWidth = 800, DefaultWindowHeight = 600;        //默认的窗口长宽
int MinWindowWidth = 450, MinWindowHeight = 250;        //默认的窗口长宽
int NowWindowWidth = DefaultWindowWidth, NowWindowHeight = DefaultWindowHeight; //当前的窗口长宽

bool LEFT_MOUSE_BUTTON_DOWN = false;
bool RIGHT_MOUSE_BUTTON_DOWN = false;

bool X_KEY_DOWN = false;

SceneObject* MOUSE_DOWN_OBJECT = nullptr;

ProgramState programState = PS_IDLE;

BottomColorBar* bcb = nullptr;
DrawingPolygonObject* dpo = nullptr;
PelAdjuster* pa = nullptr;

AdjustablePolygonObject* copyPasteBoard = nullptr;

Color3F mainColor;

#endif /* Variables_h */
