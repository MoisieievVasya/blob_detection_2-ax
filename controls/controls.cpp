#include "controls.h"


void controls::adjustDroneVelocity_2ax(float horizontalOffset, float forwardBackwardCorrection) {
    // Placeholder function to adjust the drone's velocity
    std::cout << "Horizontal Offset: " << horizontalOffset << ", Forward/Backward Correction: " << forwardBackwardCorrection << std::endl;

    // Adjust the drone's velocity vector to drive the blob toward the center
    float vx = -horizontalOffset * 0.1; // Adjust the scaling factor as needed
    float vy = -forwardBackwardCorrection * 0.1; // Adjust the scaling factor as needed

    mavlinkCommand:: sendPositionTargetLocationNED(horizontalOffset, forwardBackwardCorrection, vx, vy);
}