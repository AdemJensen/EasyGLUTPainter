//
//  Magnet.cpp
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/7.
//

#include "Magnet.h"

bool isMagnetEnabled(Magnet type, int setting)
{
    switch (type)
    {
        case MAGNET_NONE:
            return setting == 0;
        case MAGNET_STARTING_POINT:
            return (setting & MAGNET_STARTING_POINT);
        case MAGNET_VERTICAL:
            return (setting & MAGNET_VERTICAL);
        case MAGNET_HORIZONTAL:
            return (setting & MAGNET_HORIZONTAL);
        case MAGNET_45_DEG_ANGLE:
            return (setting & MAGNET_45_DEG_ANGLE);
    }
    return false;
}
