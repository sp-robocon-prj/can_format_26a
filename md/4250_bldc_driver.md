### 4250 BLDCドライバ（Data type=0x0A）  

|name|data type|r/w?|概要|
|:--:|:--:|:--:|:--:|
|MODE|uint8_t|r/w|制御モード|
|RPS_TARGET|uint16_t|r/w|RPS指令値|
|ANGLE_TARGET|float(rad)|r/w|角度指定|
|MONITOR_PERIOD|uint16_t(ms)|r/w|データをフィードバックする周期(1ms単位) 0で停止|
|MONITOR_REG|uint64_t|r/w|モニターするレジスタを設定|
|MOTOR_TYPE|uint8_t|r/w|接続するドライバの種類|
|GEAR_RATIO|float|r/w|モーターのギア比|
|ENCODER_PULSE|uint32_t|r/w|1回転ごとのエンコーダのパルス数|
|EN_LIMIT_SW|uint32_t|r/w|リミットスイッチを追加するか？|
|RPS|uint16_t|r|現在のRPS|
|INC_POS|float(rad)|r|回転回数|
|ANGLE|uint16_t|r|現在の角度|


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