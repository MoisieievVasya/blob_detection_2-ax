#ifndef CONTROLS_H
#define CONTROLS_H

#include "../communication/mavlinkCommand.h"
#include <iostream>

class controls {
public:
    static void adjustDroneVelocity_2ax(float horizontalOffset, float forwardBackwardCorrection);
};



#endif //CONTROLS_H
