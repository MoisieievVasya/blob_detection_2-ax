#include "mavlinkCommand.h"


void mavlinkCommand:: sendPositionTargetLocationNED(float x, float y, float vx, float vy) {

    mavlink_message_t message;
    mavlink_set_position_target_local_ned_t set_position;

    set_position.time_boot_ms = 0; // Set appropriate timestamp
    set_position.target_system = 1; // Target system ID
    set_position.target_component = 1; // Target component ID
    set_position.coordinate_frame = MAV_FRAME_LOCAL_NED;

    // Set type mask to ignore unused parameters
    set_position.type_mask = 3580; // ignore all except X and Y position
    set_position.coordinate_frame = MAV_FRAME_LOCAL_NED;

    // Set position and velocity
    set_position.x = x;
    set_position.y = y;
    set_position.z = 0; // Ignored in 2-axis control
    set_position.vx = vx;
    set_position.vy = vy;
    set_position.vz = 0; // Ignored in 2-axis control

    // Encode the message
    mavlink_msg_set_position_target_local_ned_encode(1, 200, &message, &set_position);

    // Send the message
    sendMavlinkMessage(message);
}

void mavlinkCommand::sendMavlinkMessage(const mavlink_message_t &message) {
    // Dummy function to simulate sending the MAVLink message
    std::cout << "MAVLink message sent: " << message.msgid << std::endl;
    // Implement actual communication interface here
}
