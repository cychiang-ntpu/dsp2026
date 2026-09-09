# DSP Assignment-1: Simulation of RC Low-Pass Filter by DSP

參考：去年版本 https://hackmd.io/@dsp-ce-ntpu/dsp-ce-ntpu-2025-assignment-1
（去年公布 2025/09/21，截止 2025/10/09；今年公布第 3 週 9/21，截止 10/8）

## 學習目標
1. 理解線性常係數差分方程（LCCDE）
2. 理解取樣率的基本概念
3. 將連續時間訊號處理轉換為離散時間處理
4. 以 C 語言實作濾波器
5. 以 Python 進行訊號視覺化

## 背景
RC 電路，輸入 x(t)、輸出 y(t)，由 KVL 得

    x(t) = RC · dy(t)/dt + y(t)

令 t = nτ（τ 為取樣週期）離散化，得式 (8)：

    y[n] = (RC/(RC+τ)) · y[n-1] + (τ/(RC+τ)) · x[n]

## 題目（共 7 題）
| 題 | 內容 |
|---|---|
| 1 | x(t) = e^{jΩt}，求 y(t) |
| 2 | x(t) = e^{jΩt} u(t)，求 y(t) |
| 3–4 | 數值分析：R = 1000 Ω，C = 1/(2π·400·1000) F；頻率 100 Hz、400 Hz、3000 Hz |
| 5–6 | 離散時間分析：取樣率 4000 Hz、8000 Hz、16000 Hz |
| 7 | C 程式實作式 (8)，以第 4 題結果驗證 |

題 1–6 手寫推導（掃描 + LaTeX 轉錄），題 7 程式實作。

## 必交 C 程式
1. `sine_wav_gen.c`：產生雙聲道 WAV（sine / cosine）
   `./sine_wav_gen.exe fs f L out_fn`
2. `RC_filtering.c`：對 WAV 套用式 (8)
   `./RC_filtering.exe in_fn out_fn`

## 繳交
- 私人 GitHub repo，邀請 cychiang@mail.ntpu.edu.tw
- 單一 README.md：手寫解答掃描 + LaTeX、C 程式說明、濾波前後波形比較（振幅/相位分析）
- 兩個 C 原始檔、figure 資料夾（推導與分析圖）
- 繪圖可用 Python（librosa、matplotlib）
