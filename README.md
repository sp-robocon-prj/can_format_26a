# 26a機体の CAN フォーマット  [fork:Gakurobo2024_protocol](https://github.com/NITTC-GakuRobo/Gakurobo2024_protocol)

パースしやすいようにyamlで書いてる。   

## ディレクトリツリー
<pre>
.
└── can_format_26a/
    ├── pcb_daimiya/
    │   ├── battery_pcb.yaml
    │   └── 4mni_bldc_driver.yaml
    └── README.md
</pre>

## CANフレーム定義

- frame_typeはcan_fd
- id_formatはhexadecimal(16進数)
- id_typeはSTANDARD(11bit)

IDは
- [Priority level](#priority-level)
- [Data type](#data-type)
- [Board ID](#board-id)
- [Register ID](#register-id)

の4つの情報を組み合わせで表現される。

| name | bit | 個数 |
|:--:|:--:|:--:|
| Priority_level | 2 | 4 |
| board_id | 4 | 16 |
| command | 5 | 32 |

### Priority level

優先度。2bit(0~4) 

| name | 優先度 | 役割 |
|:--:|:--:|:--:|
| 最優先 | 0 | Emergency |
| 高 | 1 | Control |
| 中 | 2 | Service |
| 低 | 3 | Background |

### Board ID

基板固有の値。4bit(0~15)

| Board ID | name | 役割 |
|:--:|:--:|:--:|
| 0x00 | - | 予約 |
| 0x01 | [電源管理基板](./pcb_daimiya/power_board.yaml) | 電源管理 |
| 0x02 | [4OMNI_BLDC_DRIVER](./pcb_daimiya/4omni_bldc_driver.yaml) | 4輪オムニ |
| 0x03 | - | 予約 |
| 0x04 | - | 予約 |
| 0x05 | - | 予約 |
| 0x06 | - | 予約 |
| 0x07 | - | 予約 |
| 0x08 | - | 予約 |
| 0x09 | - | 予約 |
| 0x0A | - | 予約 |
| 0x0B | - | 予約 |
| 0x0C | - | 予約 |
| 0x0D | - | 予約 |
| 0x0E | - | 予約 |
| 0x0F | - | 予約 |

### Command

命令。5bit(0~31)

共通セット 0x00~0x07
| command | name | board_id | r/w? | 概要 |
|:--:|:--:|:--:|:--:|:--:|
| 0x00 | - | 共通 | - | 予約 |
| 0x01 | EMS | 共通 | - | 非常停止 |
| 0x02 | RESET_EMS | 共通 | - | 非常停止解除 |
| 0x03 | ID_RQ | 共通 | - | これを受信したデバイスは自身のIDを返せ |
| 0x04 | - | 共通 | - |  |
| 0x05 | - | 共通 | - | 予約 |
| 0x06 | - | 共通 | - | 予約 |
| 0x07 | - | 共通 | - | 予約 |

#### ID_RQ

リモートフレームでID_RQを送信することでバス上のデバイスを調べることができる。  
リクエストを受け取ったデバイスは、Board IDに自身のID（ロータリーDIPの値）、data[0]に基板の形式を入れてData type 0x0で返す。  

#### PCU_STATE  

**PCU_STATE!=0ならなんかヤバいことが起きてるので非常停止シーケンス起動しろ**  

|bit|名称|概要|
|:--:|:--:|:--:|
|0|RESET_EMS|0で正常|
|1|EMS|非常停止中|
|2|SOFT_EMS|ソフトウェア非常停止|
|3|OIA|過電流アラート|

なおソフトウェア非常停止は遠隔非常停止などのソフトウェアによる非常停止全般を指す。  
EMS 0、1で電源基板のリレーのON/OFFを示す。  
| 物理非常停止ボタン | ソフトウェア非常停止ボタン |概要|
|:--:|:--:|:--:|
| 0 | 0 | 非常停止なし |
| 1 | 0 | 物理非常停止中 |
| 0 | 2 | ソフトウェア非常停止 |
| 1 | 2 | 物理非常停止中&ソフトウェア非常停止 |

PCU_STATEは変化があった場合即座に発報される。

### raspiとの通信接続

[mainboard pro max](https://github.com/midarubiccube/raspberrypi-io-board)にstm32 h723が乗っていて、基板内udpでつながっている。  
なのでmainboardから出ているcan端子(4pin ポケットコネクタ)に接続することで、raspiから直でCAN通信ができる.

#### 非常停止

共通コマンドのEMERGENCY_STOPが来るとすべてのモータはPWMモードに移行して停止する。  
RESET_EMERGENCY_STOPでモード設定などは復活するが、電源が落ちた状態でモーターを回すと、回転数情報などがバグるためPOSがずれる可能性が高いため注意。  
非常停止解除時に原点出しシーケンスを起動するのが望ましい。  

## データのサイズなど

データはすべてリトルエディアン。  

- `pcb_daimiya/battery_pcb.json` — 安全管理基板のCANフォーマット定義
- `pcb_daimiya/4mni_bldc_driver.yaml` — 4mni BLDCドライバ用のCANフォーマット定義

https://tree.nathanfriend.com/?s=(%27options!(%27fancy-~fullPath!false~trailingSlash-~rootDot-)~0(%270%27can_format_26a*pcb_daimiya5battery_pcb.json54mni_bldc_driver.yaml3%E3%80%80README.md%27)~version!%271%27)*3%20-!true0source!3%5Cn5*%20%01530-*