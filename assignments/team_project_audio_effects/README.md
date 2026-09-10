# Team Project：音樂音響效果器（Audio Effects Processor）

佔學期成績 20%。2–3 人一組，以 C 語言實作一個命令列音響效果器，
讀入 WAV（44.1 kHz、16 bits、立體聲）並輸出套用效果後的 WAV。
目標是把本學期學到的 LCCDE、FIR/IIR 濾波、取樣率轉換、FFT 用在真正的音樂上。

## 時程

| 日期 | 事件 |
|---|---|
| 10/15（第 6 週） | 分組登記（LMS） |
| 11/12（第 10 週） | 開題：各組提交一頁企劃（效果器清單、分工、介面設計）於 team repo |
| 12/3（第 13 週） | 進度檢查：至少兩個效果器可執行，附測試音檔 |
| 12/15（二）18:00 | 繳交截止：LMS 登錄 team repo URL＋完整 commit SHA |
| 12/17（第 15 週） | 評測：報告＋展示（現場播放）＋個人口試 |

## 必做效果器（3 人組至少 4 個、2 人組至少 3 個，其中 ★ 為必選）

| 效果 | DSP 核心 | 對應章節／作業 |
|---|---|---|
| ★ 等化器（EQ）：低通／高通／帶通／Shelving | FIR 視窗法或 IIR 二階節（biquad） | Ch. 5, 7；HW2、HW3 |
| ★ 延遲／回音（Delay / Echo） | LCCDE、回授延遲線 | Ch. 2；HW1 |
| 殘響（Reverb）：Schroeder comb + all-pass | IIR 結構、all-pass 系統 | Ch. 5.5, 6 |
| 顫音／震音（Tremolo / Vibrato） | 振幅調變、時變延遲與內插 | Ch. 4 |
| Flanger / Chorus | 時變延遲線 + LFO | Ch. 4, 6 |
| 失真（Distortion / Overdrive） | 非線性映射 + 過取樣（↑L 濾波 ↓M）抗混疊 | Ch. 4.6；HW3 |
| 變速／變調（Time-stretch / Pitch-shift） | 取樣率轉換或 FFT phase vocoder | Ch. 4.6, 8；HW3、HW4 |
| 頻譜顯示／Spectrogram 輸出 | 短時 FFT | Ch. 8, 9；HW4 |

自訂效果器可申請認列。所有濾波、FFT、內插皆須自行以 C 實作，不得呼叫外部 DSP 函式庫；
WAV 讀寫可沿用 HW1 的程式碼。

## 程式介面

    ./fx.exe in.wav out.wav effect1 [params...] [effect2 [params...] ...]
    ./fx.exe input.wav output.wav eq lowpass 4000 echo 0.3 0.5 reverb 0.8

效果器可串接（chain）。每個效果器的參數格式在 `docs/interface.md` 定義。

## Team repo 必備內容

`src/`、`include/`、`tests/`（每個效果器至少一個可自動比對的測試：弦波輸入 → 預期頻譜或振幅）、
`Makefile`、`README.md`（使用說明與每個效果器的原理、方塊圖、頻率響應圖）、
`docs/interface.md`、`TEAM_LOG.md`（每週會議紀錄）、`CONTRIBUTIONS.md`（每人負責項目與 commit 範圍）、
`AI_USAGE.md`（使用 AI 工具的範圍與驗證方式）、`slides.pdf`、`demo/`（示範音檔前後對照）。

## 評分（100 分）

共同 40 分：
- 效果器功能與邊界測試（雜音、削波、極端參數）：20
- 可重現整合：clone 指定 SHA 後 `make` 即可建置、`make test` 全過：10
- 架構文件：方塊圖、每個效果器的差分方程或頻率響應推導：10

個人 60 分：
- C 程式貢獻與協作（commit 紀錄、CONTRIBUTIONS.md）：15
- 角色履行：P（口頭報告）、D（展示整合）、V（測試驗證）；3 人組各一角色，2 人組一人兼 D+V：15
- 個人口試（就自己負責的效果器說明原理與程式）：30

口試未達 15/30 者該次上限 59 分，可於 12/24 上機考後補驗一次。
