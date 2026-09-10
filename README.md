# DSP 2026（115-1）數位訊號處理 — 課程資料庫

國立臺北大學通訊工程學系「數位訊號處理」（Digital Signal Processing），3 學分，先修：Signals and Systems。
授課教師：江振宇（[教師個人網頁](https://web.ntpu.edu.tw/~cychiang/)）

| 項目 | 內容 |
|---|---|
| 上課時間 | 每週四 13:10–16:00（午 1–3 節；2026/9/10 起，共 16 週） |
| 教室 | 電 2F07 |
| 課程流水碼 | U4064（大學部：通訊 4、資工 4、電機 4、嵌入式系統／數位多媒體學程） |
| | M5631（研究所：通訊碩、資工碩、電資博、智慧製造與系統應用專班、電機與資通訊專班） |
| 評量 | HW1–HW4 40%、紙筆期中考 20%（11/5）、期末上機考 20%（12/24，考所有作業與 Team Project）、Team Project 音樂音響效果器 20%（12/17 評測） |
| 行事曆 | 見 [docs/course_plan.md](docs/course_plan.md#本課程行事曆依-115-1-校曆) |

本 repo 提供作業規格、去年作業樣本、課程時程與新手教學，供修課同學 clone／fork 使用。

## 教學目標

「**學為所用**」、「**將系統做出來！**」——把 Oppenheim & Schafer 課本中的
數學式與演算法，以 C 語言（分析與繪圖用 Python）親手實現，檢驗自己是否已求甚解。

1. 離散時間訊號與系統、LCCDE、取樣定理
2. z 轉換與轉換分析：頻率響應、極零點、群延遲
3. 多速率訊號處理：升取樣、降取樣、非整數倍取樣率轉換
4. FIR 濾波器設計（視窗法）與 FFT 快速卷積（overlap-add）

本學期的具體實踐：從 RC 電路的數位模擬出發，經過轉換分析，
最後用兩種方法（時域 LCCDE 與頻域 FFT）把 44.1 kHz 音樂轉成 8 kHz，
並比較兩者的結果與運算量。

## 目錄結構

```
dsp2026/
├── assignments/            四份個人作業與 Team Project 規格
│   ├── hw1_rc_lowpass/             RC 低通濾波器數位模擬（C + Python）
│   ├── hw2_transform_analysis/     轉換分析 + 暫態/穩態濾波（C + Jupyter）
│   ├── hw3_sampling_rate_lccde/    取樣率轉換：FIR 低通 + LCCDE（C）
│   ├── hw4_sampling_rate_fft/      取樣率轉換：FFT 濾波器 overlap-add（C）
│   ├── team_project_audio_effects/ Team Project：音樂音響效果器（C，2–3 人一組）
│   └── archive/                    歷年題目原文（2024 Filtering: Steady and Transient States，已併入 HW2）
├── samples_2025/           去年（1141）作業樣本（HIGH / MEDIUM / LOW）
├── docs/                   課程時程與評分方式
│   ├── lectures/           課堂講義（第 1–3 週聯集版：課程介紹、從連續到離散、語音信號表示）
│   └── tutorials/          新手教學（VSCode、終端機、Git、除錯、Makefile…）
└── tools/                  課程工具（wav_info.c；input.wav 測試音檔陸續發布）
```

## 教科書

Oppenheim, A. V., & Schafer, R. W. (2009). *Discrete-Time Signal Processing* (3rd ed.). Pearson. ISBN-13: 978-0131988422

參考書：Mitra, S. K. (2002). *Digital Signal Processing: A Computer-Based Approach* (2nd ed.). McGraw-Hill.

## 第一堂課 checklist

1. 讀 [docs/lectures/dsp2026_lecture_notes.md](docs/lectures/dsp2026_lecture_notes.md)（第 1–3 週講義）與
   [docs/course_plan.md](docs/course_plan.md)：整學期時程、作業與評分。
2. 照 [docs/tutorials/vscode_c_starter.md](docs/tutorials/vscode_c_starter.md)
   架好開發環境，跑出 Hello World，並完成步驟 6 編譯 [tools/wav_info.c](tools/wav_info.c)。
3. 學會 Git：[docs/tutorials/git_intro.md](docs/tutorials/git_intro.md)，
   建立個人私人 repo 並邀請 cychiang@mail.ntpu.edu.tw。
4. 安裝 Python 3 與 `numpy`、`scipy`、`matplotlib`、`librosa`、`jupyter`（HW1 繪圖、HW2 使用）。
5. 瀏覽 [assignments/](assignments/) 與 [samples_2025/](samples_2025/) 了解作業長相。

## 個人作業（HW1–HW4）

| 作業 | 主題 | 語言 | 截止 |
|---|---|---|---|
| HW1 | RC 低通濾波器數位模擬 | C + Python | 10/8 |
| HW2 | 轉換分析 + 暫態/穩態、linear/minimum phase 濾波 | C + Python Jupyter | 11/12 |
| HW3 | 取樣率轉換（LCCDE） | C | 12/10 |
| HW4 | 取樣率轉換（FFT） | C | 12/17 |

繳交方式：push 到個人 GitHub repo，於 LMS 登錄 repo 連結與 commit SHA。詳見 [assignments/README.md](assignments/README.md)。

## Team Project：音樂音響效果器（20%）

2–3 人一組，以 C 實作可串接的命令列效果器（EQ、echo、reverb、flanger、distortion、pitch-shift…），
把 LCCDE、FIR/IIR、取樣率轉換與 FFT 用在真正的音樂上。10/15 分組、11/12 開題、12/15 繳交、12/17 評測。
規格見 [assignments/team_project_audio_effects/](assignments/team_project_audio_effects/)。

## 開發環境還沒設定好？

新手教學都在 [docs/tutorials/](docs/tutorials/)：VSCode／GCC 安裝
（vscode_c_starter.md）、終端機（terminal_basics.md）、C 速查表
（c_cheatsheet.md）、編譯錯誤急救（c_error_guide.md）、逐行除錯
（vscode_debug_tutorial.md）、Git（git_intro.md）、Makefile（makefile_intro.md）。
