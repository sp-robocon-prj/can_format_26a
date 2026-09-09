# 26a機体の CAN フォーマット

## CANフレーム定義

- frame_typeはcan_fd
- id_typeはBase (11bit)

IDは

| bitレンジ | スコープ | 名称 |
|:--:|:--:|:--:|
|3|11~9|[Priority Level](#priority-level)|
|4|8~5|[Data Type](#data-type)|
|4|4~0|[Board Num](#board-num)|

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
| 0x2 | [電源管理基板](./md/powerboard.md) | 電源管理 |
| 0x3 | [ロジック電源管理基板](./md/logic_power_board.md) | ロジック電源管理 |  |
| 0x6 | [MainBoard PRO Max](./md/mainboard_pro_max.md) | メインボード(raspi5) |
| 0x7 | [Esp32-C5](./md/esp32_c5.md) | 代替コントローラー |
| 0xA | [4250_BLDC_DRIVER](./md/4250_bldc_driver.md) | 4250 BLDCドライバ |
| 0xB | [motorboard](./md/motorboard.md) | DCモータードライバ |
| 0xC | [servoboard](./md/servoboard.md) | サーボモータードライバ |
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

#### サンプル

| Priority Level | Data Type | Board Num | Register ID | 説明 |
|:--:|:--:|:--:|:--:|:--:|
| 0x3 | 0xA | 0x3 | 0x0011 | 4250_BLDC_DRIVER(0xA)のmd0(0x0011)に回転数±pwmを送る |
ID 0x03A30011 DATA -50

## データのサイズなど

データはすべてリトルエディアン。