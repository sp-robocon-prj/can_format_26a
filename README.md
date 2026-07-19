# 26a機体の CAN フォーマット
[参考:Gakurobo2024_protocol](https://github.com/NITTC-GakuRobo/Gakurobo2024_protocol)

パースしやすいようにyamlで書いてる。   

## ディレクトリツリー
<pre>
.
└── can_format_26a/
    ├── pcb_midarubiccube/
    │   ├── power_board.yaml
    │   ├── common.yaml
    │   └── 4omni_bldc_driver.yaml
    └── README.md
</pre>

## CANフレーム定義

- frame_typeはcan_fd
- id_formatはhexadecimal(16進数)
- id_typeはEXTENDED(29bit)

IDは

| bit | スコープ | 名称 |
|:--:|:--:|:--:|
|1|28|予約 デフォルト0|
|4|27~24|[Priority Level](#priority-level)|
|8|23~16|[Data Type](#data-type)|
|8|15~8|[Board Num](#board-num)|
|8|7~0|[Register ID](#register-id)|

の組み合わせで表現される。

優先度はPriority Levelで決まる。
ただし、コーディングによって変えることができるため、保証はない。

### Priority Level

初期はData Typeで優先度を決めていたが、下位IDでも優先度が必要な場合があるため、Priority Levelを追加した。

| アドレス | Priority Level | 優先度 |
|:--:|:--:|:--:|
| 0x00 | 0 | - |
| 0x01 | 1 | 非常停止 |
| 0x02 | 2 | 高（割り込み） |
| 0x03 | 3 | 中（通常） |
| 0x04 | 4 | 低（ログ、LED） |

### Data Type

| Data Type | name | 役割 |
|:--:|:--:|:--:|
| 0x00 | - | - |
| 0x01 | 共通 | 共通コマンド |
| 0x02 | [電源管理基板](./pcb_midarubiccube/power_board.yaml) | 電源管理 |
| 0x03 | [MainBoard PRO Max](./pcb_midarubiccube/mainboard_pro_max.yaml) | メインボード(raspi5) |
| 0x04 | [Esp32-C5](./pcb_midarubiccube/esp32_c5.yaml) | 代替コントローラー |
| 0x05 | [4250_BLDC_DRIVER](./pcb_midarubiccube/4250_bldc_driver.yaml) | 4250 BLDCドライバ |
| 0x06 | [motor_board](./pcb_midarubiccube/motor_board.yaml) | DCモータードライバ |
| 0x07 | [ロジック電源管理基板](./pcb_midarubiccube/lpb.yaml) | ロジック電源管理 |  |
| 0x08~0xFF | - | 予約 |

### Board Num

各基板固有の値。8bit(0x00~0xFF)

予約済み
| Board Num | 概要 |
|:--:|:--:|
| 0x00 | - |
| 0x01 | 共通 |

### Register ID

命令コマンド。8bit(0x00~0xFF)

共通セット(common.yaml) data_type=0x01
| Register ID | name | r/w | 概要 |
|:--:|:--:|:--:|:--:|
| 0x00 | - | - | - |
| 0x01 | EMS | - | 非常停止 |
| 0x02 | RESET_EMS | - | 非常停止解除 |
| 0x03 | ID_RQ | - | これを受信したデバイスは自身のIDを返せ |
| 0x04~0xFF | - | - | 予約 |

#### ID_RQ

リモートフレームでID_RQを送信することでバス上のデバイスを調べることができる。  
リクエストを受け取ったノードは、自分のData Type,Board IDをdata[0x00,0x00]にセットして返す。  

### raspiとの通信接続

[mainboard pro max](https://github.com/midarubiccube/raspberrypi-io-board)にstm32 h723が乗っていて、基板内udpでつながっている。  
なのでmainboardから出ているcan端子(0x4 dupont)に接続することで、raspiから直でCAN通信ができる。

#### 非常停止

| Priority Level | Data Type | Board Num | Register ID | 概要 |
|:--:|:--:|:--:|:--:|:--:|
| 0x01 | 0x01 | 0x01 | 0x01 | 非常停止 |
| 0x01 | 0x01 | 0x01 | 0x02 | 非常停止解除 |

ロジック電源は非常停止がかかっても電源は落ちない。
また、駆動電源とは独立させる。

## データのサイズなど

データはすべてリトルエディアン。  

- `pcb_midarubiccube/battery_pcb.json` — 安全管理基板のCANフォーマット定義
- `pcb_midarubiccube/4omni_bldc_driver.yaml` — 4OMNI BLDCドライバ用のCANフォーマット定義
- `pcb_midarubiccube/common.yaml` — 共通のCANフォーマット定義

[ディレクトリツリー](https://tree.nathanfriend.com/?s=(%27options!(%27fancy-~fullPath!false~trailingSlash-~rootDot-)~5(%275%27can_format_26a*pcb_midarubiccube3power_board03common034omni_bldc_driver07%E3%80%80README.md%27)~version!%271%27)*7%20-!true0.yaml3*%205source!7%5Cn%017530-*)