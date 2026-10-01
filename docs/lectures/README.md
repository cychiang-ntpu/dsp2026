# docs/lectures/ — 課堂講義

授課教師：江振宇 副教授，[語音暨多媒體訊號處理實驗室（SMSPL）](https://web.ntpu.edu.tw/~cychiang/)，國立臺北大學通訊工程學系。

講義依上課週次分檔，改寫自教師歷年 HackMD 筆記，第 4 週起為新編：

| 週 | 檔案 | 內容 | 原始來源 |
|---|---|---|---|
| 1 | [day01_intro_to_dsp.md](day01_intro_to_dsp.md) | 課程介紹：DSP 應用、歷史、教科書、評分 | [2021](https://hackmd.io/DuawpzgGTAm1pr1ewb6NSA)、[2022](https://hackmd.io/kdVyXcDLQ9yV7OxeIiVlEg) |
| 2 | [day02_continuous_to_discrete.md](day02_continuous_to_discrete.md) | 從連續到離散：複數與相子、R/L/C 相位關係、阻抗、RC 低通濾波器、以離散模擬連續 | [2021/2024](https://hackmd.io/PkyN4-shQRujFfkdpUT8dg)，源自[「交流電、電阻、電抗、阻抗」](https://hackmd.io/@cychiang-ntpu/Hk3nWkcKd) |
| 2 | ↳ [day02_1_complex_phasor.md](day02_1_complex_phasor.md) | 複數的直角／極座標表示、尤拉公式、相子與其應用、相子練習題（HW1 Part A） | |
| 2 | ↳ [day02_2_rlc_phase.md](day02_2_rlc_phase.md) | 電阻、電感、電容：以弦波與相子計算，以訊號與系統觀點說明 | |
| 2 | ↳ [day02_3_impedance_rc_lowpass.md](day02_3_impedance_rc_lowpass.md) | RC 串聯阻抗、RC 低通濾波器的轉換函數與截止頻率 | |
| 2 | ↳ [day02_4_simulation_by_discrete.md](day02_4_simulation_by_discrete.md) | 由 KVL 微分方程離散化得到 HW1 式 (8) | |
| 2 | ↳ [day02_supp_rlc_filter_experiment.md](day02_supp_rlc_filter_experiment.md) | 鉛筆電阻、鋁箔電容的 RC／RLC 濾波器設計題（補充閱讀，不列入作業） | |
| 3 | [day03_speech_signal_representation.md](day03_speech_signal_representation.md) | 語音信號的表示：麥克風、ADC、傅立葉轉換、窗函數、spectrogram | [HackMD](https://hackmd.io/l9hfP04-Sgm76bunMz05JQ)（編修中） |
| 4 | [day04_frequency_response_transient.md](day04_frequency_response_transient.md) | complex exponential 進入 LTI 系統：頻率響應、穩態與暫態、DTFT、z 轉換入門 | 2026 新編；示範程式 [demos/day04_transient_steady.py](demos/day04_transient_steady.py) |

- [demos/](demos/)：課堂示範程式（Python），講義中的圖由它們產生，同學可自行修改參數重跑。
- [figures/](figures/)：示範程式產生的講義圖。

說明：
- 第 1–3 週講義的圖片由 imgur／HackMD 代管；GeoGebra 互動圖與「歷史上課影片」（2021 年錄影）以連結提供。
- 歷年作業題目已聯集進本學期 HW1–HW4，對應表見 [assignments/README.md](../../assignments/README.md)。
- 成績結構與時程一律以 [course_plan.md](../course_plan.md) 為準。
