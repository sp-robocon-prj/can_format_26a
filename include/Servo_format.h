#pragma once

#pragma pack(push, 1)
struct ServoTX_CANPacket {   
    uint8_t channel;
    int16_t position[3];
    int16_t time[3];
    int16_t speed[3];

    bool monitor_flag;
    uint16_t monitor_freq;
};
#pragma pack(pop)
