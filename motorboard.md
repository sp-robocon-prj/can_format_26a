### motorboard（Data type=0x0B）  

nはモーターID（0~3）４枚  
cは全モーターに共通する設定項目（例えば0x105も0x205も結果的に同じものが書き換わるのでどちらでも良い）

|Register ID |name|data type|r/w?|概要|
|:--:|:--:|:--:|:--:|:--:|
|0x0n00|NOP||||
|0x0n01|MOTOR_TYPE|uint8_t|r/w|接続するドライバの種類|
|0x0n02|GEAR_RATIO|float|r/w|モーターのギア比|
|0x0n03|MOTOR_STATE|bool|r|ドライバがつながっていたらtrue|
|0x0n10|PWM|float|r|現在のPWM|
|0x0n11|RPS|uint16_t|r|現在のRPS|
|0x0n12|PWM_TARGET|float|r/w|PWM指令値|
|0x0n13|RPS_TARGET|uint16_t|r/w|RPS指令値|
|0x0n14|ANGLE_TARGET|float(rad)|r/w|角度指定|
|0x0n15|SPD_TARGET|float(rad/s)|r/w|速度指定|
|0x0n36|ABS_POS|float(rad)|r|アブソリュートエンコーダによる絶対位置|
|0x0n37|ABS_SPD|float(rad/s)|r|アブソリュートエンコーダによる絶対速度|
|0x0n38|ABS_ENC_INV|bool|r|アブソエンコーダの回転方向反転|
|0x0n39|ABS_TURN_CNT|int32_t|r|アブソエンコーダの回転回数|
|0x0n3A|INC_POS|float(rad)|r|インクリメントエンコーダによる相対位置|
|0x0n3B|INC_SPD|float(rad/s)|r|インクリメントエンコーダによる相対速度|
|0x0n3C|INC_ENC_INV|bool|r|インクリメントエンコーダの回転方向反転|
|0x0n3D|INC_TURN_CNT|int32_t|r|インクリメントエンコーダの回転回数|
|0x0cF0|MONITOR_PERIOD|uint16_t(ms)|r/w|データをフィードバックする周期(1ms単位) 0で停止|
|0x0nF1|MONITOR_REG|uint64_t|r/w|モニターするレジスタを設定|

0x0cF0:cなら全モーター共通の設定。  
0x0nF0:nならモーターID n の設定。


### MOTOR_TYPE
|uint8_t|接続するドライバの種類|
|:--:|:--:|
|0|NOP|
|1|マブチDC 385|
|2|マブチDC 555|
|3|マブチDC 735|
