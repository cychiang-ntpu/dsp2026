# DSP Assignment-1: Simulation of RC Low-Pass Filter by DSP

本作業為歷年題目的聯集：
- 「Generating Sine Waves」（歷年 HW，`sine_wav_gen.c`）
- 「交流電、電阻、電抗、阻抗」講義的相子練習題（Day-2 Problems 1–3）
- 「Simulation of RC Low-Pass Filter by Discrete Signal Processing」（2025 版：https://hackmd.io/@dsp-ce-ntpu/dsp-ce-ntpu-2025-assignment-1 ）

公布第 3 週 9/24，截止 10/8 18:00。

## 學習目標
1. 以複數／相子表示弦波，理解同頻率弦波的相加與相位差
2. 理解線性常係數差分方程（LCCDE）
3. 理解取樣率的基本概念
4. 將連續時間訊號處理轉換為離散時間處理
5. 以 C 語言實作濾波器，以 Python 進行訊號視覺化

## 背景
連續時間的相子分析與 RC 低通轉換函數推導，見
[課堂講義第二部分](../../docs/lectures/dsp2026_lecture_notes.md#第二部分day-2from-continuous-to-discrete)。

RC 電路，輸入 x(t)、輸出 y(t)，由 KVL 得

    x(t) = RC · dy(t)/dt + y(t)

令 t = nτ（τ 為取樣週期）離散化，得式 (8)：

    y[n] = (RC/(RC+τ)) · y[n-1] + (τ/(RC+τ)) · x[n]

## Part A：相子暖身題（手寫，共 3 題）

給定 X(t) = √3 cos(ωt − π/3)，Y(t) = 3 sin(ωt + 2π/3)。

| 題 | 內容 |
|---|---|
| A1 | 用積化和差／和差化積計算 Z(t) = X(t) + Y(t) |
| A2 | 用相子（phasor）計算 Z(t) = X(t) + Y(t)，與 A1 比對 |
| A3 | 用 [GeoGebra](https://www.geogebra.org/) 繪製 X(t)、Y(t)、Z(t)，在 README 附上圖與連結 |

## Part B：RC 低通濾波器（共 7 題）

| 題 | 內容 |
|---|---|
| B1 | x(t) = e^{jΩt}，求 y(t)（轉換函數 H(Ω) 的振幅與相位） |
| B2 | x(t) = e^{jΩt} u(t)，求 y(t)（暫態與穩態） |
| B3–B4 | 數值分析：R = 1000 Ω，C = 1/(2π·400·1000) F；頻率 100 Hz、400 Hz、3000 Hz |
| B5–B6 | 離散時間分析：取樣率 4000 Hz、8000 Hz、16000 Hz，推導式 (8) 並比較與連續時間結果的差異 |
| B7 | C 程式實作式 (8)，以 B4 結果驗證 |

A1–A3、B1–B6 手寫推導（掃描 + LaTeX 轉錄），B7 程式實作。

## 必交 C 程式
1. `sine_wav_gen.c`：產生雙聲道 WAV（左聲道 sine、右聲道 cosine，合起來模擬 e^{j2πft}）

       ./sine_wav_gen.exe fs f L out_fn
       ./sine_wav_gen.exe 8000 3000 1.0 sincos_fs8000_f3000_L1.0.wav

   fs 取樣率（Hz）、f 弦波頻率（Hz）、L 長度（秒）、out_fn 輸出檔名。
   此程式在 HW2 會再次使用，請把 WAV 標頭寫正確（可用 [tools/wav_info.c](../../tools/wav_info.c) 檢查）。

2. `RC_filtering.c`：對 WAV 套用式 (8)，取樣率由 WAV 標頭讀取

       ./RC_filtering.exe in_fn out_fn

## 繳交
- 私人 GitHub repo，邀請 cychiang@mail.ntpu.edu.tw，於 LMS 登錄連結
- 單一 README.md：手寫解答掃描 + LaTeX、C 程式說明、濾波前後波形比較（振幅/相位分析）
- 兩個 C 原始檔、figure 資料夾（推導與分析圖）
- 繪圖可用 Python（librosa、matplotlib）
