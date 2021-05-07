# EasyGLUTPainter

A simple painter system made of GLUT.

## About
This is the Grapics homework 1, it is required to use OpenGL library and GLUT to make a simple drawer.

The project was written and built on XCode on MacOS. If you want to build it on your Windows platform, do the following:
- Install `freeglut` library.
- Prepare a C++ compiler environment.
- Open the `SystemIncludes.h`, you will see the following includes:
```cpp
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
```
That only works on Mac. Please change it to your GL and GLUT library.

## Debug Draw
I have removed the debug draw (red interactive frame), you can get it back by removing the following comment sign in file `SceneObject.hpp`:

```cpp
// #define DRAW_INTERACTIVE_DEBUG_FRAME
```

Removing the comment sign `//` in the front will activate the debug draw. All the scene objects will display a red frame when you move your mouse on it.

## How to use
When build and run, you will see the following frame:

![image.png](https://i.loli.net/2021/05/08/4waVLrD5ux6JhWv.png)

All the functions are switched and achieved by keyboard:
- `Q`: Start drawing a new polygon (Drives program into DRAW mode).
- `W`: Switch the program state back to IDLE (Stop drawing polygon, default program mode, called IDLE mode).
- `D`: Delete a selected polygon.
- `C`: Copy a polygon (Into a program-wide paste board, not system-wide).
- `X`: Cut a polygon (Into a program-wide paste board, not system-wide).
- `V`: Paste a polygon (From program-wide paste board, not system-wide).
- `U`: Move a polygon to the front (level + 1).
- `J`: Move a polygon to the back (level - 1).

When drawing polygon, you can hold key `X` to draw vertical and horizontal lines:

![image.png](https://i.loli.net/2021/05/08/5R3UC2OGovy1kIs.png)

Under IDLE mode, you can click a polygon to modify it:

![image.png](https://i.loli.net/2021/05/08/uXh2jqGDbKVZ8lo.png)

- Dragging the polygon: Move
- Dragging polygon's right-bottom corner: Scale
- Dragging bottom bars: Change color.

When clicking on a polygon, the bottom bar will show its color. When no polygon selected, the bottom bar will have a "master color", which will be the color of newly drawed polygons.

## License
This program does not have any license, you can use this program whatever you like (Except for making it your homework, because I already done that)!
