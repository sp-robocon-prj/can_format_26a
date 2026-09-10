#pragma once 

#pragma pack(push, 1)
struct PWRTX_CANPacket {
    bool pwrstatus;
    uint8_t ledstatus;
    float current_limit;
    float battery_limit;
    
    bool monitor_flag;
    uint16_t monitor_freq;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PWRX_CANPacket {
    float current;
    float battery1_voltage;
    float battery2_voltage;
    float output_voltage;
};
#pragma pack(pop)
