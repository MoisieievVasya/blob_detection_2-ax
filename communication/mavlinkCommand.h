#ifndef MAVLINKCOMMAND_H
#define MAVLINKCOMMAND_H

#include "../c_library_v2/ardupilotmega/mavlink.h"
#include <iostream>


class mavlinkCommand {
public:
    static void sendPositionTargetLocationNED(float x, float y, float vx, float vy);
private:
    static void sendMavlinkMessage(const mavlink_message_t& message);
};

#endif //MAVLINKCOMMAND_H
