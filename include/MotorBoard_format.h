#pragma once

#pragma pack(push, 1)
struct MotorBoardTX_CANPacket {
    uint8_t mode[4];
    uint16_t target[4];

    bool monitor_flag;
    uint16_t monitor_freq;
};
#pragma pack(pop)
