#pragma once

#pragma pack(push, 1)
struct BLDCTX_CANPacket {
    float rps_target;          
    float  angle_target;
    float gear_ratio;
    uint32_t encoder_resolution;
    bool en_limit_sw;
    bool monitor_flag;
    uint16_t monitor_freq;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BLDCRX_CANPacket {
    float rps;
    float angle;
};
#pragma pack(pop)