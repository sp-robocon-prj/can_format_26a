#pragma once

#pragma pack(push, 1)
struct BLDCTX_CANPacket {
    uint8[4] mode;
    uint16[4] target
    
    bool monitor_flag;
    uint16_t monitor_freq;
};
#pragma pack(pop)
