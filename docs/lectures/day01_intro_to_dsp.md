# Day-1（第 1 週）：Introduction to DSP

[講義目錄](README.md) ｜ [day02_continuous_to_discrete.md →](day02_continuous_to_discrete.md)


- 日期：2026/9/10（第 1 週，週四）
## 1. 第一眼看 DSP

### 與 Multimedia 脫不了關係
可複習「多媒體訊號處理」課程
[Chapter-1](https://github.com/cychiang-ntpu/ntpu-ce-mmsp-2020/tree/master/Chapter-1#1-introduction-to-multimedia-signal-processing)。

### Why digital?
- Analog vs. digital?
- Continuous vs. discrete?
- 類比系統與數位系統的優缺點

可複習「多媒體訊號處理」課程
[Chapter-2](https://github.com/cychiang-ntpu/ntpu-ce-mmsp-2020/tree/master/Chapter-2#2-digital-data-signal-representation)。

---

## 2. 由 DSP 晶片供應商來看

### 德州儀器（Texas Instruments, TI；TXN-US）
- [Digital signal processors (DSPs) – Overview](https://www.ti.com/product-category/microcontrollers-processors/microprocessors-dsp/overview.html)：TI DSP 產品線與應用領域（音訊、雷達、汽車 ADAS、Edge AI、航太國防）
- [Audio & radar DSP SoCs](https://www.ti.com/product-category/microcontrollers-processors/microprocessors-dsp/audio-radar-dsp-socs/overview.html)
- 白皮書：[Demystifying digital signal processing (DSP) programming](https://www.ti.com/lit/pdf/spry281)（TI, SPRY281）
- 補充：[處理器的種類：CPU、GPU、MCU、DSP、MPU 各是什麼？](https://www.stockfeel.com.tw/%E8%99%95%E7%90%86%E5%99%A8-cpu-gpu-mcu-dsp-mpu/)

### 亞德諾（Analog Devices, ADI；ADI-US）
- https://www.analog.com/en/products.html

### 恩智浦半導體（NXP Semiconductors；NXPI-US）
- https://www.nxp.com/

### 飛思卡爾（Freescale，已被 NXP 收購）
- https://zh.wikipedia.org/wiki/%E9%A3%9E%E6%80%9D%E5%8D%A1%E5%B0%94

---

## 3. 應用

### Communication
- Modulation / Demodulation
- Pulse Shaping Techniques
- Delta-Sigma Modulator
- Oversampled D/A and A/D Converters
- Phase Locked Loop
- Software Defined Radio
- Speech Coding
- Digital Filter

### Image / Video Processing
- [Image compression（JPEG）](https://en.wikipedia.org/wiki/Image_compression)
- [Video coding（H.264）](https://en.wikipedia.org/wiki/Video_coding_format)
- Streaming
- [Digital image processing](https://en.wikipedia.org/wiki/Digital_image_processing)
  - Medical images

### Audio
- [Audio compression](https://zh.wikipedia.org/wiki/%E9%9F%B3%E8%A8%8A%E5%A3%93%E7%B8%AE_(%E6%A0%BC%E5%BC%8F))
- Audio filtering / equalization
- Audio enhancement
- Spatial audio processing
  - [Head-Related Transfer Function（HRTF）](https://zh.wikipedia.org/wiki/%E5%A4%B4%E9%83%A8%E7%9B%B8%E5%85%B3%E4%BC%A0%E8%BE%93%E5%87%BD%E6%95%B0)

### Speech
- Speech coding / compression
- Speech enhancement
- Speech recognition
- Speaker recognition
- Hearing aid

### Avionics（航空電子設備）& Defense（國防工業）
- Radar
- Sonar

---

## 4. 歷史

- **17 世紀**：微積分發明 → 以連續變數函數與微分方程描述物理現象 →
  牛頓使用有限差分法（finite-difference methods），即本課程離散時間系統的特例。

  ![](https://i.imgur.com/vIWH1zu.png)
- **19 世紀初（1805）**：高斯（Carl Friedrich Gauss）已發現快速傅立葉轉換（FFT）的基本原理。
- **1950 年代**：訊號處理主要以類比系統完成；數位電腦已進入企業與實驗室，但速度慢、昂貴、體積大。
- **1950 年代**：數位電腦首次用於 DSP 是在地球物理探勘；受限於取樣頻率，只能把低頻地震訊號錄在磁帶上，
  幾秒的資料要花數分鐘到數小時處理。
- **1950 年代**：因數位電腦的彈性，工程師在做出類比系統之前先用 DSP 模擬它。
  著名例子是 MIT Lincoln Lab 與 Bell Telephone Lab 的 Vocoder 模擬。

  ![](https://i.imgur.com/Zi7v4tA.png)

  > A History of Vocoder Research at Lincoln Laboratory,
  > https://www.ll.mit.edu/publications/journal/pdf/vol03_no2/3.2.1.vocoder.pdf
- **1960 年代**：DSP 系統用來逼近類比訊號處理系統，已可得到很好的類比濾波器近似；
  但速度、成本、體積三個因素，使完整的 DSP 系統仍無法取代類比系統用於語音通訊、雷達處理等。
- **1960 年代**：部分演算法源自數位電腦的彈性，在類比設備上並無對應的實作方式。
- **1965**：Cooley 與 Tukey 公開 FFT，加速了離散時間訊號處理的新觀點 →
  DSP 不再只是類比系統的近似，而有了自己的數學（discrete-time mathematics）。
- **1980 年代**：微處理器的發明，讓 DSP 系統（記憶體、CPU、A/D 與 D/A 轉換）得以低成本實現。

---

## 5. 教科書

Oppenheim, A. V., & Schafer, R. W. (2009). *Discrete-Time Signal Processing* (3rd ed.). Pearson.
ISBN-13: 978-0131988422（課綱指定用書）

![](https://i.imgur.com/36DVd5o.png)

---

## 6. 課本章節（Course Outline）

1. Introduction
2. Discrete-Time Signals and Systems
3. The z-Transform
4. Sampling of Continuous-Time Signals
5. Transform Analysis of Linear Time-Invariant Systems
6. Structures for Discrete-Time Systems
7. Filter-Design Techniques
8. The Discrete Fourier Transform
9. Computation of the Discrete Fourier Transform
10. Fourier Analysis of Signals Using the Discrete Fourier Transform
11. Parametric Signal Modeling
12. Discrete Hilbert Transforms
13. Cepstrum Analysis and Homomorphic Deconvolution

本學期實際進度為 Ch. 1–9（Ch. 6 僅簡介結構與運算量），詳見 [course_plan.md](../course_plan.md)。

---

## 7. 評分方式

本學期的成績結構、週次進度與作業截止日，統一以 [docs/course_plan.md](../course_plan.md) 為準。

作業繳交規範（延續歷年做法）：
- 繳交 C（或 Python）原始碼，push 到個人私人 GitHub repo，並邀請 cychiang@mail.ntpu.edu.tw。
- 以 [Markdown](https://markdown.tw/) 撰寫 README.md 記錄作業（推導、圖表、結果分析）。
- 評分重點：程式正確性、原始碼可讀性、文件（README.md）的品質與正確性。

本學期四份作業：

| 作業 | 主題 |
|---|---|
| [HW1](../../assignments/hw1_rc_lowpass/) | Simulation of RC Low-Pass Filter by DSP |
| [HW2](../../assignments/hw2_transform_analysis/) | Transform Analysis |
| [HW3](../../assignments/hw3_sampling_rate_lccde/) | Changing the Sampling Rate（LCCDE） |
| [HW4](../../assignments/hw4_sampling_rate_fft/) | Changing the Sampling Rate（FFT Filters） |

歷年曾出過的題目（供參考）：Generating Sine Waves、RC Low-Pass Filter Simulation、
[Filtering: Steady and Transient States](../../assignments/archive/2024_hw3_filtering_steady_transient/)、
Linear/Minimum Phase Systems、Changing Sampling Rates、FFT Filters。

---

## 8. 上課影片（舊版錄影）

- DSP Day-1: Introduction to DSP (Part-1)：https://www.youtube.com/watch?v=stfz_41kxYE
- DSP Day-1: Introduction to DSP (Part-2)：https://www.youtube.com/watch?v=OFzc7PAKuf4

---

---

## 9. 複習 RC 低通濾波器 → 見 Day-2

DSP 需要「訊號與系統」的基礎，而其基礎在於交流電、電阻、電抗、阻抗的觀念。
相關內容已併入[Day-2 講義](day02_continuous_to_discrete.md)第 1 節，這也是 HW1 的背景知識。

## 10. 回到 1950 年代：用 DSP 來模擬類比電路 → 見 Day-2 第 3 節

思考：如何用程式語言模擬 RC 電路，對任何輸入 x(t) 求出 y(t)？
推導見 [Day-2 講義](day02_continuous_to_discrete.md)第 3 節，即 [HW1](../../assignments/hw1_rc_lowpass/) 的出發點。

---

# 課後待辦（第 1 週）

1. 依 [vscode_c_starter.md](../tutorials/vscode_c_starter.md) 架好 C 開發環境，編譯 [tools/wav_info.c](../../tools/wav_info.c)。
2. 依 [git_intro.md](../tutorials/git_intro.md) 建立個人私人 repo，邀請 cychiang@mail.ntpu.edu.tw。
3. 預習 [Day-2 講義](day02_continuous_to_discrete.md) 第 1 節（相子與 RC 低通濾波器），為 HW1 做準備。

---

[講義目錄](README.md) ｜ [day02_continuous_to_discrete.md →](day02_continuous_to_discrete.md)
