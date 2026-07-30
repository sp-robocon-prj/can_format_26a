# 26a機体の CAN フォーマット

## CANフレーム定義

- frame_typeはcan_fd
- id_typeはEXTENDED(29bit)

IDは

| bitレンジ | スコープ | 名称 |
|:--:|:--:|:--:|
|1|28|予約 デフォルト0|
|4|27~24|[Priority Level](#priority-level)|
|4|23~20|[Data Type](#data-type)|
|4|19~16|[Board Num](#board-num)|
|16|15~0|[Register ID](#register-id)|

の組み合わせで表現される。

優先度はPriority Levelで決まる。
ただし、コーディングによって変えることができるため、保証はない。

### Priority Level

初期はData Typeで優先度を決めていたが、下位IDでも優先度が必要な場合があるため、Priority Levelを追加した。

| アドレス | Priority Level | 優先度 |
|:--:|:--:|:--:|
| 0x0 | 0 | - |
| 0x1 | 1 | 非常停止 |
| 0x2 | 2 | 高（割り込み） |
| 0x3 | 3 | 中（通常） |
| 0x4 | 4 | 低（ログ、LED） |

### Data Type

| Data Type | name | 役割 |
|:--:|:--:|:--:|
| 0x0 | - | - |
| 0x1 | 共通 | 共通コマンド |
| 0x2 | [電源管理基板](./pcb_midarubiccube/power_board.yaml) | 電源管理 |
| 0x3 | [ロジック電源管理基板](./pcb_midarubiccube/lpb.yaml) | ロジック電源管理 |  |
| 0x6 | [MainBoard PRO Max](./pcb_midarubiccube/mainboard_pro_max.yaml) | メインボード(raspi5) |
| 0x7 | [Esp32-C5](./pcb_midarubiccube/esp32_c5.yaml) | 代替コントローラー |
| 0xA | [4250_BLDC_DRIVER](./pcb_midarubiccube/4250_bldc_driver.yaml) | 4250 BLDCドライバ |
| 0xB | [motor_board](./pcb_midarubiccube/motor_board.yaml) | DCモータードライバ |
| 0xC~0xF | - | 予約 |

### Board Num

各基板固有の値。4bit(0x0~0xF)

予約済み
| Board Num | 概要 |
|:--:|:--:|
| 0x0 | - |
| 0x1 | 共通 |

### Register ID

命令コマンド。16bit(0x0000~0xFFFF)

共通セット(common.yaml) data_type=0x01
| Register ID | name | r/w | 概要 |
|:--:|:--:|:--:|:--:|
| 0x0000 | - | - | - |
| 0x0001 | EMS | - | 非常停止 |
| 0x0002 | RESET_EMS | - | 非常停止解除 |
| 0x0003 | ID_RQ | - | これを受信したデバイスは自身のIDを返せ |
| 0x0004~0xFFFF | - | - | 予約 |

#### ID_RQ

リモートフレームでID_RQを送信することでバス上のデバイスを調べることができる。  
リクエストを受け取ったノードは、自分のData Type,Board IDをdata type=0x03,0x04に返す。  

### raspiとの通信接続

[mainboard pro max](https://github.com/midarubiccube/raspberrypi-io-board)にstm32 h723が乗っていて、基板内udpでつながっている。  
なのでmainboardから出ているcan端子(0x4 dupont)に接続することで、raspiから直でCAN通信ができる。

#### 非常停止

| Priority Level | Data Type | Board Num | Register ID | 概要 |
|:--:|:--:|:--:|:--:|:--:|
| 0x01 | 0x01 | 0x01 | 0x01 | 非常停止 |
| 0x01 | 0x01 | 0x01 | 0x02 | 非常停止解除 |

ロジック電源は非常停止が押されていても落ちない。
また、駆動電源とは独立しているロジック電源を使用する。

### motorboard（Data type=0x06）  

nはモーターID（0~3）  
cは全モーターに共通する設定項目（例えば0x105も0x205も結果的に同じものが書き換わるのでどちらでも良い）

|Register ID |name|data type|r/w?|概要|
|:--:|:--:|:--:|:--:|:--:|
|0x0n00|NOP||||
|0x0n01|MOTOR_TYPE|uint8_t|r/w|接続するドライバの種類|
|0x0n02|GEAR_RATIO|float|r/w|モーターのギア比|
|0x0n03|MOTOR_STATE|bool|r|ドライバがつながっていたらtrue|
|0x0n10|PWM|float|r|現在のPWM|
|0x0n11|PWM_TARGET|float|r/w|PWM指令値|
|0x0n12|ANGLE_TARGET|float(rad)|w|角度指定|
|0x0n36|ABS_POS|float(rad)|r|アブソリュートエンコーダによる絶対位置|
|0x0n37|ABS_SPD|float(rad/s)|r|アブソリュートエンコーダによる絶対速度|
|0x0n38|ABS_ENC_INV|bool|r/w|アブソエンコーダの回転方向反転|
|0x0n39|ABS_TURN_CNT|int32_t|r/w|アブソエンコーダの回転回数|
|0x0n3A|INC_POS|float(rad)|r|インクリメントエンコーダによる相対位置|
|0x0n3B|INC_SPD|float(rad/s)|r|インクリメントエンコーダによる相対速度|
|0x0n3C|INC_ENC_INV|bool|r/w|インクリメントエンコーダの回転方向反転|
|0x0n3D|INC_TURN_CNT|int32_t|r/w|インクリメントエンコーダの回転回数|
|0x0cF0|MONITOR_PERIOD|uint16_t(ms)|r/w|データをフィードバックする周期(1ms単位) 0で停止|
|0x0nF1|MONITOR_REG|uint64_t|r/w|モニターするレジスタを設定|


MOTOR_TYPE
|uint8_t|接続するドライバの種類|
|:--:|:--:|
|0|NOP|
|1|マブチDC 385|
|2|マブチDC 555|
|3|マブチDC 735|

#### サンプル

| Priority Level | Data Type | Board Num | Register ID | 説明 |
|:--:|:--:|:--:|:--:|:--:|
| 0x03 | 0x06 | 0x03 | 0x05（回転数rps） | 4250_BLDC_DRIVER 0x03に回転数±を送る |
| 0x01 | 0x01 | 0x01 | 0x02 |  |

## データのサイズなど

データはすべてリトルエディアン。