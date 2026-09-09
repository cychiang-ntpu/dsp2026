# tools/ — 課程工具

| 檔案 | 用途 |
|---|---|
| `wav_info.c` | 印出 WAV 檔的聲道數、取樣率、位元數與長度。環境測試用（見 tutorials 步驟 6），也可用來檢查作業輸出的 WAV 標頭是否正確。 |

編譯：`gcc -Wall -Wextra -std=c99 wav_info.c -o wav_info`
執行：`./wav_info input.wav`

陸續發布：HW3/HW4 用的 `input.wav` 測試音檔、頻譜圖繪製腳本（Python）。
