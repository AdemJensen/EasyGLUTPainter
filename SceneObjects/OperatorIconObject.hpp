//
//  OperatorIconObject.hpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/6.
//

#ifndef OperatorIconObject_hpp
#define OperatorIconObject_hpp

#include <stdio.h>

#include "SystemIncludes.h"

class OperationIconObject : public SceneObject
{
public:
    OperationIconObject(int x, int y);
    
    virtual ~OperationIconObject() {  }
    
    virtual void repaint();
};

#endif /* OperatorIconObject_hpp */
