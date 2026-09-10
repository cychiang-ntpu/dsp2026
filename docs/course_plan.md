# 課程時程與評分摘要（DSP 2026，115-1）

依據教師資訊系統 115-1「數位訊號處理」課程大綱（3 學分，先修：Signals and Systems）。
上課時間：每週四 13:10–16:00（午 1–3 節），教室電 2F07；2026/9/10－2026/12/24，共 16 週。
課程流水碼：U4064（大學部）、M5631（研究所），兩班合班上課，作業與評量相同。

## 成績結構（比照 mmsp2026 作法）

| 項目 | 比例 | 說明 |
|---|---|---|
| 個人作業 HW1–HW4 | 40% | 每份 10%；GitHub repo 繳交，LMS 登錄 repo URL＋完整 commit SHA |
| 紙筆期中考 | 20% | 11/5（第 9 週）第一節；50 分鐘閉卷；範圍至第 8 週（Ch. 2–5） |
| 個人期末上機考 | 20% | 12/24（第 16 週）三節課內；140 分鐘作答；範圍為 HW1–HW4 與 Team Project 全部內容：現場修改／擴充自己的作業與效果器程式 |
| Team Project：音樂音響效果器 | 20% | 2–3 人一組；團隊 40 分＋個人 60 分；12/15 繳交、12/17 評測。規格見 [team_project_audio_effects/](../assignments/team_project_audio_effects/) |

課綱之評量方式登錄為平時作業 100%；實際計分依本表，期中考與期末上機考皆歸入平時成績項下。

## 週次進度

| 週 | 週四日期 | 課綱主題（O&S 章節） | 本 repo 對應內容 | 作業 |
|---|---|---|---|---|
| 1 | 9/10 | Introduction to DSP；Discrete-time signals and systems I（Ch. 1–2） | [課程介紹](lectures/dsp2026_lecture_notes.md#第一部分day-1introduction-to-dsp)；開發環境與 Git | |
| 2 | 9/17 | Discrete-time signals and systems II（Ch. 2） | [從連續到離散](lectures/dsp2026_lecture_notes.md#第二部分day-2from-continuous-to-discrete)：相子、阻抗、RC 低通轉換函數；LTI、卷積、LCCDE；WAV 讀寫 | |
| 3 | 9/24 | Z-transform I（Ch. 3） | RC 電路離散化；補充：[語音信號的表示](lectures/dsp2026_lecture_notes.md#第三部分語音信號的表示補充教材) | **HW1 公布** |
| 4 | 10/1 | Z-transform II（Ch. 3） | ROC、系統函數 | |
| 5 | 10/8 | Sampling of Continuous-Time Signals I（Ch. 4） | 取樣定理、混疊、重建 | **HW1 截止 10/8** |
| 6 | 10/15 | Sampling of Continuous-Time Signals II（Ch. 4） | 多速率：↑L、↓M、非整數倍轉換（Ch. 4.6–4.7） | Team Project 分組登記 |
| 7 | 10/22 | Transform Analysis of LTI Systems I（Ch. 5） | 頻率響應、極零點、群延遲、相位 unwrap | **HW2 公布** |
| 8 | 10/29 | Transform Analysis of LTI Systems II（Ch. 5） | linear/minimum phase；FIR 濾波的暫態與穩態 | |
| 9 | 11/5 | Midterm | **紙筆期中考**（第一節，50 分鐘）；其餘時間講授 Ch. 6 | |
| 10 | 11/12 | Structure for Discrete-Time System I（Ch. 6） | 直接型、多相結構、biquad；效果器架構簡介 | **HW2 截止 11/12**；Team Project 開題 |
| 11 | 11/19 | Structure for Discrete-Time System II（Ch. 6） | 運算量分析 | **HW3 公布** |
| 12 | 11/26 | Filter Design Techniques I（Ch. 7） | FIR 視窗法：Hamming / Hanning / Kaiser（Ch. 7.5） | **HW4 公布** |
| 13 | 12/3 | Filter Design Techniques II（Ch. 7） | 視窗法設計範例；HW3 實作細節 | Team Project 進度檢查 |
| 14 | 12/10 | Discrete Fourier Transform I（Ch. 8） | DFT、圓周卷積、視窗效應 | **HW3 截止 12/10** |
| 15 | 12/17 | Discrete Fourier Transform II（Ch. 8） | Team Project 評測（報告＋展示＋口試）；上機模擬與補強；AOL 問卷 | **HW4 截止 12/17**；Team 繳交 12/15 18:00 |
| 16 | 12/24 | Computation of the DFT I（Ch. 9） | **個人期末上機考**（三節課內，140 分鐘） | |

## 本課程行事曆（依 115-1 校曆）

校曆：[國立臺北大學 115 學年度第 1 學期行事曆](https://www.ntpu.edu.tw/)（教務處公告，115/3/18 第 87 次行政會議通過）。
本課程每週四上課，16 個週四皆為上課日或考試日，未被國定假日影響。

| 週 | 週四 | 校曆事項（影響本課程者） |
|---|---|---|
| — | 9/7（一） | 開始上課；9/7–9/14 加退選；9/15–9/21 人工加簽；9/19–9/21 線上確認選課 |
| 1 | 9/10 | 第一次上課 |
| 3 | 9/24 | 地震避難掩護正式演練（當日）；9/25（五）中秋節、9/28（一）教師節放假，不影響週四 |
| 6 | 10/15 | 10/17 上課達三分之一 |
| 7 | 10/22 | 10/24（六）光復節、10/26（一）補假，不影響週四 |
| 8 | 10/29 | **學士班期中考週（10/27–11/2）**；10/31 校慶，上課達二分之一 |
| 9 | 11/5 | 紙筆期中考（第一節）；11/3–11/14 申請棄修；11/7（六）校慶活動 |
| 11 | 11/19 | 11/21 上課達三分之二 |
| 12 | 11/26 | 11/28（六）地方公職人員選舉停課，不影響週四 |
| 15 | 12/17 | 學士班申請休學截止日 |
| 16 | 12/24 | **學士班期末考週（12/21–12/24）**；本課期末上機考；12/25 行憲紀念日；12/28 寒假開始 |
| — | 1/5、1/12 | 開課於 4 年級班／全部班級成績繳送截止 |

注意事項：
- 第 8 週（10/29）在學士班期中考週內，U4064 大學部同學若有他科期中考衝堂，請提前告知；本課當週仍照常上課（HW2 已於前一週公布）。
- 第 16 週（12/24）在學士班期末考週內，本課於該週舉行期末上機考；HW4 已於 12/17 截止，遲交最多 3 日（至 12/20）。
- 大四同學成績須於 1/5 前繳送，上機考成績於 12/31 前公布。

## 重要日期

| 日期 | 事件 |
|---|---|
| 9/10 | 第 1 週：建置個人 GitHub repo，邀請 cychiang@mail.ntpu.edu.tw |
| 9/24 | HW1 公布 |
| 10/8 18:00 | HW1 截止 |
| 10/22 | HW2 公布 |
| 11/5 | 紙筆期中考（第一節，50 分鐘） |
| 11/12 18:00 | HW2 截止 |
| 11/19 | HW3 公布（含 input.wav 測試音檔） |
| 11/26 | HW4 公布 |
| 12/10 18:00 | HW3 截止 |
| 10/15 | Team Project 分組登記 |
| 11/12 | Team Project 開題（一頁企劃） |
| 12/3 | Team Project 進度檢查 |
| 12/15 18:00 | Team Project 繳交截止（repo URL＋SHA） |
| 12/17 18:00 | HW4 截止 |
| 12/17 | Team Project 評測；上機模擬與補強；AOL 問卷（課堂填寫） |
| 12/24 | 個人期末上機考（三節課內，140 分鐘） |

## 作業一覽（規格見 [assignments/](../assignments/)）

| 作業 | 語言 | 核心內容 | 公布 | 截止 |
|---|---|---|---|---|
| [HW1](../assignments/hw1_rc_lowpass/) RC 低通模擬 | C + Python 繪圖 | Part A 相子暖身 3 題；Part B 7 題連續/離散分析推導 + `sine_wav_gen.c`、`RC_filtering.c` | 9/24 | 10/8 |
| [HW2](../assignments/hw2_transform_analysis/) 轉換分析 | C + Python Jupyter | Part A 給定 H(z)：相位/群延遲/振幅響應；Hanning 視窗弦波經 LCCDE 濾波。Part B 截斷理想低通 FIR（M=4…2048）的暫態/穩態；linear vs. minimum phase | 10/22 | 11/12 |
| [HW3](../assignments/hw3_sampling_rate_lccde/) 取樣率轉換（LCCDE） | C | 44.1 kHz → 8 kHz（L=80, M=441），視窗法 FIR P=1025，直接卷積 | 11/19 | 12/10 |
| [HW4](../assignments/hw4_sampling_rate_fft/) 取樣率轉換（FFT） | C | 同 HW3 規格；overlap-add P=441、Q=1025、N=2048；自行實作 FFT | 11/26 | 12/17 |

## 作業評分（每份 10 分）

- repo 可存取、本人 commit 紀錄完整，登錄的 SHA 可建置：1 分
- 程式可編譯執行、輸出符合規格（WAV 可播放）：4 分
- README 報告：推導/原理說明、圖表、結果分析：4 分
- 程式碼品質與註解：1 分
- 遲交每日扣 10%，最多 3 日。繳交登錄 repo URL＋完整 commit SHA，不接受可移動的 tag 或 ZIP。

## Team Project 評分（100 分）

共同 40：效果器功能／邊界測試 20＋可重現整合 10＋架構文件 10。
個人 60：C 貢獻與協作 15＋P/D/V 角色履行 15＋個人口試 30。
口試未達 15/30 → 上限 59，可於 12/24 上機考後補驗一次。詳見 [規格](../assignments/team_project_audio_effects/)。

## 期末上機考

- 12/24 三節課內，140 分鐘；個人作答，可攜帶並使用自己的 HW1–HW4 與 Team Project 程式碼。
- 範圍就是所有作業與 Team Project：題目以 HW1–HW4 及效果器為基礎，現場要求修改參數、
  換規格或新增功能（例如改截止頻率、換視窗、改 L/M、把效果器串成新組合），以 C 完成並輸出 WAV。
- 驗收：現場以 wav_info 檢查標頭，以頻譜圖或指定測試訊號比對結果；並就自己的程式口頭說明原理。
- 沒有自己親手寫過作業與效果器的同學，上機考難以在時限內完成，請平時務必自己實作。
- 12/17 課堂進行上機模擬與環境檢查。

## 教科書與參考書（依課綱）

- 指定用書：Oppenheim, A. V., & Schafer, R. W. (2009). *Discrete-Time Signal Processing* (3rd ed.). Pearson.
  ISBN-13: 978-0131988422
- 參考書：Mitra, S. K. (2002). *Digital Signal Processing: A Computer-Based Approach* (2nd ed.). McGraw-Hill.

## 與去年（1141）的差異

- 上課日改為週四，學期 9/10–12/24 共 16 週；HW4 截止由 1/8 提前至 12/17。
- 成績結構比照 mmsp2026：作業 40%、紙筆期中考 20%、期末上機考 20%、Team Project（音樂音響效果器）20%。期末改為上機考，HW4 截止因此提前至 12/17。
- HW1 併入相子暖身題；HW2 併入 2024 年「Filtering: Steady and Transient States」（linear/minimum phase），使 HW1–HW4 涵蓋歷年全部六個題目。
- HW3 去年為 preview version，今年定稿並補上 L、M、ω_c 推導。
- HW3/HW4 繳交方式與 HW1/HW2 統一為 GitHub repo。
