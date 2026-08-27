### 4250 BLDCドライバ（Data type=0x0A）  


|Register ID |name|data type|r/w?|概要|
|:--:|:--:|:--:|:--:|:--:|
|0x0000|MODE|uint8_t|r/w|制御モード|
|0x0001|RPS_TARGET|uint16_t|r/w|RPS指令値|
|0x0003|ANGLE_TARGET|float(rad)|r/w|角度指定|
|0x0007|RPS|uint16_t|r|現在のRPS|
|0x000B|INC_POS|float(rad)|r|回転回数|
|0x000F|ANGLE|uint16_t|r|現在の角度|
|0x0011|MONITOR_PERIOD|uint16_t(ms)|r/w|データをフィードバックする周期(1ms単位) 0で停止|
|0x0013|MONITOR_REG|uint64_t|r/w|モニターするレジスタを設定|
|0x001B|MOTOR_TYPE|uint8_t|r/w|接続するドライバの種類|
|0x001D|GEAR_RATIO|float|r/w|モーターのギア比|
|0x0021|ENCODER_PULSE|uint32_t|r/w|1回転ごとのエンコーダのパルス数|
|0x0025|EN_LIMIT_SW|uint32_t|r/w|リミットスイッチを追加するか？|



### MODE
|MODE|制御モード|
|:--:|:--:|
|0|速度モード|
|1|角度モード|

### MOTOR_TYPE
|MOTOR_TYPE|接続するドライバの種類|
|:--:|:--:|
|0|NOP|
|1|4250 560kv|
|2|4250 800kv|
|5|2212 1000kv|
|6|2212 2200kv|