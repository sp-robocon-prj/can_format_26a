# H723 UDP <-> CAN FD ブリッジ実装ガイド

ROS2側で「要素分割方式（UdpCanFrame.msg）」を利用してUDP通信を行う構成に合わせた、STM32 H723側のC言語実装イメージです。

## ネットワーク設定
* **H723 (自分自身):** `192.168.1.103`, ポート `4001`
* **ROS2 (送信先):** `192.168.1.102`, ポート `4001`

## パケット構造体定義

ROS2側のUDP送信ノード（C++）から送られてくるバイト列とメモリレイアウトを完全に一致させるため、`__attribute__((packed))` を指定します。データサイズは合計 69 bytes になります。

```c
#include <stdint.h>
#include <string.h>

// パディングを無効化してROS2側からのバイト列と完全に一致させる
typedef struct __attribute__((packed)) {
    uint8_t  priority;     
    uint8_t  data_type;    
    uint8_t  board_num;    
    uint16_t register_id;  // リトルエンディアンで送受信
    uint8_t  dlc;          
    uint8_t  data[64];     // CAN FDペイロード
} UdpCanFrame;
```

## UDP受信 -> CAN送信 の処理 (ROS2 -> H723 -> CAN)

LwIPなどのUDP受信コールバック関数内でパケットを受け取った後、29bitの拡張CAN ID（EXT_ID）を組み立ててCANバスへ送信します。

```c
void on_udp_receive(const uint8_t* payload, uint16_t length) {
    if (length != sizeof(UdpCanFrame)) {
        // パケットサイズが一致しない場合は破棄
        return;
    }

    UdpCanFrame* frame = (UdpCanFrame*)payload;

    // 29bit拡張CAN IDの組み立て
    uint32_t can_ext_id = 0;
    
    // bit 27~24: Priority Level
    can_ext_id |= ((uint32_t)(frame->priority & 0x0F)) << 24;
    
    // bit 23~20: Data Type
    can_ext_id |= ((uint32_t)(frame->data_type & 0x0F)) << 20;
    
    // bit 19~16: Board Num
    can_ext_id |= ((uint32_t)(frame->board_num & 0x0F)) << 16;
    
    // bit 15~0: Register ID
    can_ext_id |= ((uint32_t)(frame->register_id & 0xFFFF));

    // --------------------------------------------------
    // TODO: ここでFDCANモジュールの送信関数を呼び出す
    // 例: FDCAN_Transmit(can_ext_id, frame->data, frame->dlc);
    // --------------------------------------------------
}
```

## CAN受信 -> UDP送信 の処理 (CAN -> H723 -> ROS2)

CANバスから受信したメッセージのIDを各要素に分解し、構造体に詰めてROS2へ送信します。

```c
void on_can_receive(uint32_t can_ext_id, const uint8_t* rx_data, uint8_t dlc) {
    UdpCanFrame frame;
    memset(&frame, 0, sizeof(frame));

    // 29bit拡張CAN IDの分解
    frame.priority    = (uint8_t)((can_ext_id >> 24) & 0x0F);
    frame.data_type   = (uint8_t)((can_ext_id >> 20) & 0x0F);
    frame.board_num   = (uint8_t)((can_ext_id >> 16) & 0x0F);
    frame.register_id = (uint16_t)(can_ext_id & 0xFFFF);
    
    frame.dlc = dlc;

    // データのコピー（最大64バイト）
    for(uint8_t i = 0; i < dlc && i < 64; i++){
        frame.data[i] = rx_data[i];
    }

    // --------------------------------------------------
    // TODO: ここでLwIPなどのUDP送信関数を呼び出し、
    // 192.168.1.102:4001 宛に送信する
    // 例: udp_sendto(pcb, pbuf_from_frame, &ros2_ip, 4001);
    // --------------------------------------------------
}
```

## メモ
* H723側のネットワーク処理は割り込みコンテキスト（ISR）内で直接行うのではなく、RTOSのタスクやメインループ内などで処理することをお勧めします。
* `register_id` 等のバイトオーダは H723 (ARM Cortex-M7) と Raspberry Pi (ARM Cortex-A) の両方ともリトルエンディアンであるため、そのままの受け渡しで問題ありません。
