# Day-2（第 2 週）：From Continuous to Discrete

[← day01_intro_to_dsp.md](day01_intro_to_dsp.md) ｜ [講義目錄](README.md) ｜ [day02_1_complex_phasor.md →](day02_1_complex_phasor.md)


- 日期：2026/9/17（第 2 週，週四）
- 與本學期作業的關係：第 1 節（相子、阻抗、RC 低通濾波器的轉換函數）與第 3 節（以離散訊號模擬 RC 電路）
  是 [HW1](../../assignments/hw1_rc_lowpass/) Part A 與 Part B 的背景知識；第 2 節土製 RLC 濾波器實驗為補充閱讀，本學期不列入作業。

## 本講內容

| 節 | 檔案 | 內容 |
|---|---|---|
| 1.1 | [day02_1_complex_phasor.md](day02_1_complex_phasor.md) | 複數的直角／極座標表示、尤拉公式、相子與其應用、相子練習題（HW1 Part A） |
| 1.2 | [day02_2_rlc_phase.md](day02_2_rlc_phase.md) | 電阻、電感、電容：以弦波與相子計算，以訊號與系統觀點說明 |
| 1.3 | [day02_3_impedance_rc_lowpass.md](day02_3_impedance_rc_lowpass.md) | RC 串聯阻抗、RC 低通濾波器的轉換函數與截止頻率 |
| 3（接 1.3） | [day02_4_simulation_by_discrete.md](day02_4_simulation_by_discrete.md) | 由 KVL 微分方程離散化得到 HW1 式 (8) |
| 補充（原第 2 節） | [day02_supp_rlc_filter_experiment.md](day02_supp_rlc_filter_experiment.md) | 鉛筆電阻、鋁箔電容的 RC／RLC 濾波器設計題（補充閱讀，不列入作業） |

建議閱讀順序：1.1 → 1.2 → 1.3 → 3；第 2 節為補充閱讀。

## 1. Very Fundamentals of Continuous Signals and Systems

## 引言一
為什麼要以某一個頻率的正弦 (sin)或餘弦(cos)電壓或電流來分析電路呢？當閱讀以下的內容時，別忘了思考此問題！
> 回顧在數位邏輯實驗中給的 clock 訊號，比如最大振幅是 5V 的方波 (square wave)：

```math
\begin{gathered}
x(t)=2.5+2.5\sum_{k=0}^{K}\frac{4}{\pi}\frac{sin(2\pi (2k+1)ft)}{2k+1} \\
K\rightarrow \infty
\end{gathered}
```


> 就是由不同頻率和振幅組合而成的！
> GeoGebra 互動圖：https://www.geogebra.org/calculator/xdbctsqv


## 引言二
為什麼要學複數 (Complex Number)？在接下來的介紹可以解答這個問題的部分答案！複數在正弦或餘弦交流電路的運算分析中，是一個非常簡單且有利的工具，而在電路中以複數所表示的電壓、電流等物理量，我們通稱之為相子 (phasor)，接下來首先介紹如何使用複數表示某個頻率的交流信號。

接著閱讀 [1.1 複數與相子](day02_1_complex_phasor.md)。

---

[← day01_intro_to_dsp.md](day01_intro_to_dsp.md) ｜ [講義目錄](README.md) ｜ [day02_1_complex_phasor.md →](day02_1_complex_phasor.md)
