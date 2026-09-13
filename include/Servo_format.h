#pragma once

#pragma pack(push, 1)
struct BLDCTX_CANPacket {
    uint8_t id;
    uint16_t position;
    uint
    bool monitor_flag;
    uint16_t monitor_freq;
};
#pragma pack(pop)
