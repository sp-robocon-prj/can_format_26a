# 26a機体 CANフォーマット準拠 
uint8 priority      # 0~4 (4bit)
uint8 board_num     # 0x0~0xF (4bit)

float32 rps_target
float32 angle_target
float32 gear_ratio
uint32 encoder_resolution
bool en_limit_sw

bool monitor_flag
uint16 monitor_freq