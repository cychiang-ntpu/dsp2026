# tools/ — 課程工具

| 檔案 | 用途 |
|---|---|
| `wav_info.c` | 印出 WAV 檔的聲道數、取樣率、位元數與長度。環境測試用（見 [vscode_c_starter.md](../docs/tutorials/vscode_c_starter.md) 步驟 6），也可用來檢查作業輸出的 WAV 標頭是否正確：標頭宣稱的長度與實際檔案不符、資料長度不是整數個 frame 時會印出 `WARNING`（回傳值 2）；不是 WAV 或缺少 fmt／data chunk 時印出 `error`（回傳值 1）。 |

編譯：`gcc -Wall -Wextra -std=gnu99 wav_info.c -o wav_info`
執行：`.\wav_info input.wav`（macOS/Linux：`./wav_info input.wav`）

陸續發布：HW3/HW4 用的 `input.wav` 測試音檔（11/19 HW3 公布時）、頻譜圖繪製腳本（Python）。
