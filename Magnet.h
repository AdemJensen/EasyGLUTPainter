//
//  Magnet.h
//  easyPinter
//
//  Created by 伊米哇嘎克 on 2021/5/7.
//

#ifndef Magnet_h
#define Magnet_h

#define Magnet int
#define MAGNET_NONE             0
#define MAGNET_STARTING_POINT   1
#define MAGNET_VERTICAL         2
#define MAGNET_HORIZONTAL       4
#define MAGNET_45_DEG_ANGLE     8

bool isMagnetEnabled(Magnet type, int setting);

#endif /* Magnet_h */
