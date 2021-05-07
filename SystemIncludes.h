//
//  SystemIncludes.h
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/7.
//

#ifndef SystemIncludes_h
#define SystemIncludes_h

#include <cstdio>
#include <vector>

#ifndef Point2D_hpp
#include "Point2D.hpp"
#endif

#ifndef Color3F_hpp
#include "Color3F.hpp"
#endif

#ifndef Math_hpp
#include "Math.hpp"
#endif

#ifndef GL
#define GL
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif

#ifndef SceneObject_hpp
#include "SceneObject.hpp"
#endif

#include "Magnet.h"

#endif /* SystemIncludes_h */
