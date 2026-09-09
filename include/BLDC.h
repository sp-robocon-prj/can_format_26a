#pragma once

#pragma pack(push, 1)
struct BLDC_CANPacket {
    uint8_t mode;
    int16_t rps_target;          
    float  angle_target;
    bool monitor_peirod;
    uint16_t monitor_freq;
    uint8_t motor_type;
    float gear_ratio;
    uint32_t encoder_pulse;
    bool en_limit_sw;
};
#pragma pack(pop)