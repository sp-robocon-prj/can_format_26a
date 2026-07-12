# 26a機体の CAN フォーマット

パースしやすいようにjsonで書いてる。   
見やすいからjsonで書いたけど、コメント使えないのは普通にゴミです。
<pre>
.
└── can_format_26a/
    └── pcb_daimiya/
        ├── battery_pcb.json
        └── 4mni_bldc_driver.json
</pre>

- `pcb_daimiya/battery_pcb.json` — バッテリ関連のCANフォーマット定義
- `pcb_daimiya/4mni_bldc_driver.json` — 4mni BLDCドライバ用のCANフォーマット定義