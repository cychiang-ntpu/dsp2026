# DSP Assignment-4: Changing Sampling Rate with FFT Filters

參考：去年投影片 DSP-Assignment-4 (20251223).pdf（公布 2025/12/23，截止 2026/01/08）
（今年公布第 12 週 11/26，截止 12/17 18:00）

## 學習目標
- 理解升取樣與降取樣
- 以 overlap-add 方法實作 FFT 低通濾波器

## 規格
與 HW3 相同：input.wav（44.1 kHz 立體聲 16 bits）→ output.wav（8 kHz 立體聲 16 bits），
x[n] → ↑L → 低通（增益 L，截止 min(π/L, π/M)）→ ↓M。

## 低通濾波器（FFT，逐框處理）
將 x_e[n] 切成長度 P 的區段：

    x_e[n] = Σ_{r=0}^{∞} x_r[n − rP]，  x_r[n] = x_e[n + rP]（0 ≤ n ≤ P−1），否則 0

時域：x̃_i[n] = x_e[n] * h[n] = Σ_r y_r[n − rP]，y_r[n] = x_r[n] * h[n]，h[n] 長度 Q
頻域：Y_r[k] = X_r[k] H[k]，k = 0 ~ N−1，N ≥ P + Q − 1

## 參數
| 參數 | 值 | 說明 |
|---|---|---|
| P | 441 | 每框樣本數 |
| Q | 1025 | 低通濾波器長度（同 HW3 的 P；本作業改以 Q 表示，P 另作框長） |
| N | 2048 | FFT 點數，x_r、h 補零至 2048 |
| H[k] | FFT{h[n]} | |

**Stop to think**：能否直接在頻域設計理想低通 H[k]（通帶 = L、阻帶 = 0），跳過 h[n] 的視窗法設計？
請在 README 回答「可以／不可以」並以圓周卷積與 overlap-add 的條件說明理由，最好附上實驗比較。

## 要求
- 全部以 C 撰寫（含 FFT，不得呼叫外部 FFT 函式庫）
- 低通濾波必須用 overlap-add 實作
- output.wav 可由媒體播放器正常播放

## 今年修訂事項
- 截止日提前至 12/17（第 15 週），第 16 週 12/24 為期末上機考
- 要求與 HW3 輸出比較：兩者差異的 SNR，以及運算量（乘法次數）比較
- 繳交方式比照 HW1/HW2：個人 repo 的 `hw4/` 資料夾 + README，LMS 登錄 repo URL＋commit SHA
