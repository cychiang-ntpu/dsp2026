# DSP Assignment-2: Transform Analysis: Examine the example

參考：去年版本 https://hackmd.io/@dsp-ce-ntpu/dsp-ce-ntpu-2025-assignment-2
（去年公布 2025/10/30，截止 2025/11/13；今年公布第 7 週 10/19，截止 11/12）

## 學習目標
1. 計算振幅響應、相位響應與群延遲
2. 依課本理論展示群延遲效應
3. 將 z 轉換轉為 LCCDE

## 題目
給定一個因果穩定系統的 z 轉換與極零點圖，以 Python（Jupyter Notebook）完成：
1. **相位響應**：主值相位與連續（unwrapped）相位圖
2. **群延遲與振幅響應**圖
3. **訊號分析**：產生頻率 0.8π、0.2π、0.4π 的弦波乘上 Hanning 視窗，顯示波形與其 DTFT
4. **系統濾波**：推導 LCCDE，作為濾波器套用於第 3 題訊號，顯示輸出

## 繳交
- GitHub repo，私人存取授權 cychiang@mail.ntpu.edu.tw，於 LMS 只繳交連結
- 一個 *.ipynb，含說明原理與實作的註解

參考：Oppenheim & Schafer, Discrete-Time Signal Processing, 3rd ed.（例題出自 Ch. 5）
