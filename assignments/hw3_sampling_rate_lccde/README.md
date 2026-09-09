# DSP Assignment-3: Changing the Sampling Rate with a Low-Pass Filter Implemented by LCCDE

參考：2023 版投影片 DSP-Assignment-4(20231224).pdf（當年編為 HW4，去年改編為 HW3 preview version）
（今年公布第 11 週 11/16，截止 12/10）

## 學習目標
- 理解升取樣（up-sampling）與降取樣（down-sampling）
- 以 LCCDE（直接卷積）實作 FIR 低通濾波器
- 觀察訊號的頻譜圖（spectrogram）

## 規格
- 輸入 x[n]：input.wav，立體聲，44.1 kHz，16 bits（T = 1/44100 s）
- 輸出 x̃_d[n]：output.wav，立體聲，8 kHz，16 bits（TM/L = 1/8000 s）
- 系統（O&S Fig. 4.29）：x[n] → ↑L → 低通（增益 L，截止 min(π/L, π/M)）→ ↓M → x̃_d[n]
- 44100/8000 = 441/80，故 L = 80、M = 441

## FIR 低通濾波器（視窗法，Ch. 7.5）

    h[n] = sin[ω_c (n − (P−1)/2)] / [π (n − (P−1)/2)] · w[n]

- ω_c：截止頻率
- w[n]：Hamming、Hanning 或 Kaiser 視窗，n = 0 ~ P−1
- P = 1025

## 要求
- 除繪圖外全部以 C 撰寫
- 繪出 |H(e^{jω})| 證明濾波器正確
- output.wav 可由媒體播放器正常播放

## 今年修訂事項
- 去除「preview version」標示，定稿題目
- 明確寫出 L、M 值與 ω_c = π/441 的推導
- 建議說明多相（polyphase）實作以避免對零值取樣運算（選做加分）
- 繳交方式比照 HW1/HW2：私人 GitHub repo + README
