# 2026のA機体のCANフォーマット。
[参考:Gakurobo2024_protocol](https://github.com/NITTC-GakuRobo/Gakurobo2024_protocol)

パースしやすいようにyamlで書いてる。   

## ディレクトリツリー
<pre>
<!-- TREE START -->
.
├── .gitignore
├── BLDCRX.msg
├── BLDCTX.msg
├── PWRManagerRX.msg
├── PWRManagerTX.msg
├── README.md
├── UdpCanFrame.msg
├── include
│   ├── BLDC_format.h
│   ├── ID_format.h
│   ├── PWRManager_format.h
│   └── UDPPacket_format.h
└── md
    ├── 4250_bldc_driver.md
    ├── can_format.md
    ├── h723_udp_can_bridge.md
    ├── motorboard.md
    └── powerboard.md

3 directories, 16 files
<!-- TREE END -->
</pre>

[can_format](./md/can_format.md) 全体のフォーマットの説明。  
[power_board](./md/power_board.md) 電源管理基板のフォーマット。

