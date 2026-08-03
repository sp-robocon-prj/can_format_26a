### 4250 BLDCドライバ（Data type=0x0A）  

cは全モーターに共通する設定項目（例えば0x105も0x205も結果的に同じものが書き換わるのでどちらでも良い）

|Register ID |name|data type|r/w?|概要|
|:--:|:--:|:--:|:--:|:--:|
|0x0000|NOP||||
|0x0001|MOTOR_TYPE|uint8_t|r/w|接続するドライバの種類|
|0x0002|GEAR_RATIO|float|r/w|モーターのギア比|
|0x0003|MOTOR_STATE|bool|r|ドライバがつながっていたらtrue|
|0x0010|PWM|float|r|現在のPWM|
|0x0011|RPS|uint16_t|r|現在のRPS|
|0x0012|PWM_TARGET|float|r/w|PWM指令値|
|0x0013|RPS_TARGET|uint16_t|r/w|RPS指令値|
|0x0014|ANGLE_TARGET|float(rad)|r/w|角度指定|
|0x0015|SPD_TARGET|float(rad/s)|r/w|速度指定|
|0x0036|ABS_POS|float(rad)|r|アブソリュートエンコーダによる絶対位置|
|0x0037|ABS_SPD|float(rad/s)|r|アブソリュートエンコーダによる絶対速度|
|0x0038|ABS_ENC_INV|bool|r|アブソエンコーダの回転方向反転|
|0x0039|ABS_TURN_CNT|int32_t|r|アブソエンコーダの回転回数|
|0x003A|INC_POS|float(rad)|r|インクリメントエンコーダによる相対位置|
|0x003B|INC_SPD|float(rad/s)|r|インクリメントエンコーダによる相対速度|
|0x003C|INC_ENC_INV|bool|r|インクリメントエンコーダの回転方向反転|
|0x003D|INC_TURN_CNT|int32_t|r|インクリメントエンコーダの回転回数|
|0x01F0|MONITOR_PERIOD|uint16_t(ms)|r/w|データをフィードバックする周期(1ms単位) 0で停止|
|0x01F1|MONITOR_REG|uint64_t|r/w|モニターするレジスタを設定|

### MOTOR_TYPE
|MOTOR_TYPE|接続するドライバの種類|
|:--:|:--:|
|0|NOP|
|1|4250 560kv|
|2|4250 800kv|
|5|2212 1000kv|
|6|2212 2200kv|