# DSP Assignment-2: Transform Analysis — Linear/Minimum Phase, Steady and Transient States

本作業為歷年題目的聯集：
- 「Transform Analysis: Examine the example」（2025 版：https://hackmd.io/@dsp-ce-ntpu/dsp-ce-ntpu-2025-assignment-2 ）
- 「Filtering: Steady and Transient States」與「Linear/Minimum Phase Systems」
  （2024 版 Assignment-3：https://hackmd.io/QgTHBIoYRwSuiLTZDn3Gmw ，全文存於 [archive/](../archive/2024_hw3_filtering_steady_transient/)）

公布第 7 週 10/22，截止 11/12 18:00。

## 學習目標
1. 計算振幅響應、相位響應與群延遲；依課本理論展示群延遲效應
2. 將 z 轉換轉為 LCCDE 並實作濾波
3. 熟悉 DTFT／IDTFT 的數學與使用方法
4. 了解 LTI 系統濾波時 transient／steady state 與 impulse response 長度的關係
5. 實作截斷（加窗）的理想低通濾波器
6. 了解 linear phase 與 minimum phase 的意義

## Part A：轉換分析（Python，Jupyter）

給定一個因果穩定系統的 z 轉換與極零點圖（課堂公布，例題出自 O&S Ch. 5），完成：
1. **相位響應**：主值相位與連續（unwrapped）相位圖
2. **群延遲與振幅響應**圖
3. **訊號分析**：產生頻率 0.8π、0.2π、0.4π 的弦波乘上 Hanning 視窗，顯示波形與其 DTFT
4. **系統濾波**：推導 LCCDE，作為濾波器套用於第 3 題訊號，顯示輸出並說明群延遲效應

## Part B：Filtering — Steady and Transient States（C + Jupyter）

1. 設計多個 low-pass filter，規格：
   - 針對取樣率 f_s = 44100 Hz 的雙聲道音樂（*.wav）處理
   - cutoff frequency f_c = 4000 Hz 的 linear-phase low-pass filter，理想頻率響應

         H_lp(e^{jω}) = 1, |ω| < ω_c ；0, ω_c ≤ |ω| ≤ π

   - 實作上以下列 FIR impulse response 實現（應再乘上 Hamming 或 Blackman 等視窗）：

         h_M[n] = sin(ω_c (n − M)) / (π (n − M))，0 ≤ n ≤ 2M；否則 0

   - 建立 5 種 order 的 linear-phase low-pass filter：M = 4, 16, 64, 512, 2048（order = 2M）
2. 繪製 impulse response h_M[n]，M = 4, 16, 64, 512, 2048
3. 繪製 magnitude response |H_M(e^{jω})| 與 phase response ∠H_M(e^{jω})，形式比照課本圖例，附產生資料點與繪圖的 code
4. 實作 LCCDE，將 HW1 `sine_wav_gen.c` 產生的波形輸入 h_M[n] 系統，輸出存成 WAV。
   輸入以 f_s = 44100 Hz 產生；考慮並討論輸入頻率 1000、3000、4000、5000、8000 Hz
5. 討論不同 M 下 low-pass filter 的 transient 與 steady state 輸出
6. 建立 M = 4, 16, 64 對應的 **minimum-phase** low-pass filter，重複以上 impulse response、
   magnitude/phase response 繪製與濾波實驗，並與 linear-phase 結果比較

## 必交程式

| 檔案 | 說明 |
|---|---|
| `sine_wav_gen.c` | 同 HW1 |
| `Linear_Phase_Filter.c` | `./Linear_Phase_Filter.exe fc M coef.txt in.wav out.wav`；fc 截止頻率（Hz）、2M 為 order；係數與 poles/zeros 寫入 coef.txt（格式自訂）；取樣率由 WAV 標頭讀取 |
| `Minimum_Phase_Filter.c` | 介面同上，輸出 minimum-phase 版本 |
| `DSP_Assignment_2.ipynb` | Part A 全部內容；Part B 的 Markdown 說明、編譯與執行所有 C 程式（含全部 M 與輸入頻率組合）、讀取 coef.txt 以 Python 繪製 magnitude 與 phase response |

範例：

    ./Linear_Phase_Filter.exe 4000 64 coef.txt sincos_fs44100_f3000_L1.0.wav filtered_sincos_fs44100_f3000_L1.0.wav

## 繳交
- 個人 repo 的 `hw2/` 資料夾（私人 repo，邀請 cychiang@mail.ntpu.edu.tw），於 LMS 登錄 repo URL＋完整 commit SHA
- 批改時只執行 `DSP_Assignment_2.ipynb`：C 程式的編譯與執行、所有展示圖片皆須由 notebook 產生，不得手動存檔；
  報告分數依 notebook 內的 Markdown 說明評分，`hw2/README.md` 只需簡述內容並指向 notebook

## Hint
- 求多項式根：GNU Scientific Library https://www.gnu.org/software/gsl/doc/html/poly.html#examples ，
  或以 Python `numpy.roots` 求根後把係數寫回 C 程式讀取。minimum phase 的建構方法請自行參考課本 Ch. 5.6 並在報告中說明。
