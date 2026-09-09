#pragma once

#pragma pack(push, 1)
struct UdpPacket {
    char header[3];
    uint16_t id;
    uint8_t size;          
    uint8_t  data[64];     
};
#pragma pack(pop)