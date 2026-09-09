### 電源基板（Data type=0x02）

|Register ID |name|data type|r/w?|概要|
|:--:|:--:|:--:|:--:|:--:|
|0x0000|NOP||||
|0x0001|PCU_STATE|uint8_t|rw|電源の状態|
|0x0001|LED_STATUS|uint8_t|rw|LEDの状態|
|0x0002|CELL_N|uint8_t|r/w|リポのセル数|
|0x0003|EX_EMS_TRG|uint8_t|r/w|自動非常停止の条件設定|
|0x0004|EMS_RQ|bool|w|遠隔非常停止リクエスト|
|0x0005|COMMON_EMS_EN|bool|r/w|非常停止がかかった時にCommonReg::EMERGENCY_STOPを発報するか 初期値true|
|0x0006|OUT_V|float(V)|r|現在の電圧|
|0x0020|V_CELL_LIMIT_HIGH|float(V)|r/w|セル当たりの電圧がこれを超えるとアラート|
|0x0011|V_CELL_LIMIT_LOW|float(V)|r/w|セル当たりの電圧がこれを下回るととアラート|
|0x0012|V_LIMIT_HIGH|float(V)|r/w|リポ一つ当たりの電圧がこれを超えるとアラート|
|0x0013|V_LIMIT_LOW|float(V)|r/w|リポ一つ当たりの電圧がこれを下回るととアラート|
|0x0014|OUT_I|float(A)|r|現在の電流|
|0x0015|I_LIMIT|float(A)|r/w|この電流を超えるとアラート|
|0x0030|MONITOR_PERIOD|uint16_t(ms)|r/w|データをフィードバックする周期(1ms単位) 0で停止|
|0x0031|MONITOR_REG|uint64_t|r/w|モニターするレジスタを設定|