#pragma once 

enum class DataType : uint8_t {
    COMMON_COMMAND = 0x01,
    POWERBOARD_COMMAND = 0x02,
    BLDC_COMMAND = 0x03,
    MOTORBOARDC_COMMAND = 0x04,
    MAINBOARD_COMMAND = 0x05,
};

union ID {
    uint16_t id;
    struct {
        uint16_t board_num : 4;
        DataType data_type : 4;
        uint16_t priority : 3;
    } fields;
};