# Team Project 程式殼（starter）

這是 [音樂音響效果器](../README.md) 的起始程式。把整個 `starter/` 資料夾的內容複製到你們的 team repo 根目錄，
確認可以編譯後開始填程式。**本檔在你們的 repo 裡要改寫成自己的 README**（使用說明、每個效果器的原理、方塊圖、頻率響應圖）。

範圍：只需完成命令列（CLI）版本，不需要製作圖形介面；圖形介面由教師另行提供。

## 快速上手：編譯並執行第一個效果器

以下指令都在程式殼所在的資料夾（有 `Makefile` 的那一層）執行。
Windows 請用 VSCode 的終端機（PowerShell），環境設定見 [vscode_c_starter.md](../../../docs/tutorials/vscode_c_starter.md)、
Makefile 的觀念見 [makefile_intro.md](../../../docs/tutorials/makefile_intro.md)。

### 1. 編譯

```
mingw32-make
```

macOS／Linux 把 `mingw32-make` 換成 `make`（以下相同）。成功後資料夾裡會多出 `fx.exe`（macOS／Linux 為 `fx`），
過程中不應該出現任何 warning。改了任何 `.c` 或 `.h` 之後再打一次就會重新編譯。

### 2. 看有哪些效果器

```
.\fx --list
```

macOS／Linux 與 Git Bash 寫成 `./fx --list`（以下相同）。輸出的每一列是「效果器名稱＋參數說明」：

```
gain         <dB>
eq           <lowpass|highpass|bandpass|lowshelf|highshelf> <f0_Hz> [Q=0.7071] [gain_dB=0]
echo         <delay_s> <feedback>
tremolo      <rate_Hz> <depth>
...
```

`< >` 是必填參數，`[ ]` 是可省略的參數，等號後面是省略時的預設值。

### 3. 準備一個測試音檔

需要 16-bit PCM 的 WAV 檔。兩種來源：

- 用 HW1 的 `sine_wav_gen` 產生 3 秒、440 Hz 的弦波：

  ```
  .\sine_wav_gen 44100 440 3.0 tone.wav
  ```

- 用自己的音樂：以 Audacity 匯出成「WAV（Microsoft）16-bit PCM」，或用 ffmpeg 轉檔：

  ```
  ffmpeg -i song.mp3 -ar 44100 -ac 2 -c:a pcm_s16le song.wav
  ```

把 WAV 檔放到同一個資料夾。

### 4. 執行最簡單的效果器：tremolo（震音）

`tremolo` 是程式殼裡已經寫好的效果器，讓音量以固定頻率忽大忽小：

```
.\fx tone.wav out.wav tremolo 5 0.8
```

| 位置 | 內容 | 意義 |
|---|---|---|
| 第 1 個 | `tone.wav` | 輸入檔 |
| 第 2 個 | `out.wav` | 輸出檔（已存在會被覆蓋） |
| 第 3 個 | `tremolo` | 效果器名稱 |
| 之後 | `5 0.8` | 該效果器的參數：每秒擺動 5 次、深度 0.8（音量在 0.2 倍與 1 倍之間變化） |

畫面上會印出輸入與輸出的格式：

```
input : tone.wav  (44100 Hz, 2 ch, 132300 frames, 3.000 s)
output: out.wav  (44100 Hz, 2 ch, 132300 frames, 3.000 s)
```

用任何播放器打開 `out.wav`，應該聽到原本平穩的聲音變成每秒抖動 5 次。
試著改參數再聽：`tremolo 1 1.0`（很慢、完全消失再回來）、`tremolo 20 0.5`（很快、較淺）。

對應的程式在 [src/fx_modulation.c](src/fx_modulation.c) 的 `fx_tremolo()`，只有十行左右：

```
y[n] = (1 - d/2 + (d/2)·sin(2π·rate·n/fs)) · x[n]
```

請先讀懂它與 [src/fx_gain.c](src/fx_gain.c)，其他效果器都是照同樣的流程寫。

### 5. 串接多個效果器

效果器名稱一個接一個寫下去，由左到右依序套用：

```
.\fx tone.wav out.wav gain -6 tremolo 5 0.8
```

先把音量降 6 dB，再加震音。

### 6. 看懂錯誤訊息

| 訊息 | 原因 |
|---|---|
| `effect 'tremolo' failed. usage: tremolo <rate_Hz> <depth>` | 參數個數或範圍不對（例如只打 `tremolo 5`） |
| `effect 'echo' is not implemented yet` | 這個效果器還沒實作，就是你們要寫的部分 |
| `unknown effect: 'xxx' (use --list)` | 效果器名稱打錯 |
| `WARNING: 175980 samples clipped ...` | 輸出超過 16-bit 能表示的範圍而被削波（例如 `gain 12`），聲音會破掉；請降低增益 |
| `only 16-bit PCM is supported` | 輸入檔不是 16-bit PCM，照步驟 3 重新轉檔 |

發生錯誤時不會產生輸出檔。

### 7. 執行自動測試

```
mingw32-make test
```

剛拿到時的結果：

```
[PASS] wav roundtrip
[PASS] gain -6 dB
[PASS] tremolo sideband
[NOT IMPLEMENTED] eq lowpass 4000
[NOT IMPLEMENTED] echo impulse

3 passed, 0 failed, 2 not implemented (total 5)
```

最後 make 會顯示 `Error 1`，這是正常的：只要有任何一項不是 PASS，測試就算失敗。
你們把 eq 與 echo 寫對之後會變成 PASS；繳交時必須全部 PASS
（規格：clone 指定 SHA 後 `make` 即可建置、`make test` 全過）。

### 8. 清除編譯產物

```
mingw32-make clean
```

## 哪些已經寫好、哪些要自己寫

| 檔案 | 狀態 | 內容 |
|---|---|---|
| `src/main.c` | 已完成 | 命令列進入點 |
| `src/fx_chain.c` | 已完成 | 音訊緩衝區、效果器串接、參數解析工具 |
| `src/wav.c` | 已完成 | 16-bit PCM WAV 讀寫（含削波計數） |
| `src/fx_table.c` | 已完成，可增刪 | 效果器登記表 |
| `src/fx_gain.c` | 已完成 | 範例：增益，示範函式寫法 |
| `src/fx_modulation.c` 的 tremolo | 已完成 | 範例：震音（振幅調變），可以直接聽，並附測試；**不計入必做數量** |
| `src/dsp_util.c` | **留空** | 共用元件：biquad、延遲線、視窗、FIR、FFT |
| `src/fx_eq.c` ★ | **留空** | 等化器 |
| `src/fx_echo.c` ★ | **留空** | 延遲／回音 |
| `src/fx_reverb.c` | **留空** | Schroeder 殘響 |
| `src/fx_modulation.c` 其餘 | **留空** | vibrato、flanger、chorus |
| `src/fx_distortion.c` | **留空** | 失真（含過取樣） |
| `src/fx_pitch.c` | **留空** | 變速、變調 |
| `src/fx_spectrogram.c` | **留空** | Spectrogram 輸出 |
| `tests/test_fx.c` | 部分完成 | 測試工具與 tremolo、eq、echo 的測試；其餘自行新增 |

留空的檔案裡，參數解析與檢查已經寫好，每個檔案開頭的註解有數學式、邊界情況與參考文獻；
標示 `TODO` 的地方是要你們實作的 DSP 運算，目前回傳 `FX_ENOTIMPL`。

3 人組至少 4 個效果器、2 人組至少 3 個，★ 為必選。不做的效果器，把 `src/fx_table.c` 裡那一列刪掉即可。

## 程式架構

```
in.wav → wav_read → audio_t → 效果 1 → audio_t → 效果 2 → … → wav_write → out.wav
```

- 取樣值為 `double`，正規化到 [-1, 1)，立體聲交錯存放：第 n 個 frame、第 c 聲道是 `data[n * ch + c]`。
- 每個效果器是一個函式 `int fx_xxx(const audio_t *in, audio_t *out, int argc, char **argv)`，
  一次處理整段音訊，輸出長度可以和輸入不同。見 [include/fx.h](include/fx.h) 與範例 [src/fx_gain.c](src/fx_gain.c)。
- 串接時以「下一個效果器名稱」分界，所以參數字串不能和效果器名稱相同。
- 寫檔時超出 [-1, 1) 的取樣值會被削波，`fx` 會印出被削波的個數；評分會測這一項。

## 建議的進行順序

1. `dsp_util.c` 的 biquad 與延遲線 → `fx_eq.c`、`fx_echo.c`，讓 `make test` 五項全過。
2. 選定其餘效果器，先寫測試再寫實作（`tests/test_fx.c` 末段有每個效果器的測試寫法建議）。
3. 命令列格式、效果器名稱與參數順序是固定介面，不可更改（圖形介面會直接呼叫 `fx`）；
   可新增的部分與各組須決定的項目見 [docs/interface.md](docs/interface.md)。

## 規定

- 所有濾波、FFT、內插都要自己用 C 寫，不得呼叫外部 DSP 函式庫。
- 註解裡的數學式是出發點，不是答案：架構文件要有你們自己的推導、極零點圖與由實際係數算出的頻率響應。
- 使用 AI 工具的範圍與驗證方式記錄在 [AI_USAGE.md](AI_USAGE.md)；口試會就你負責的效果器問原理與程式。

## Team repo 必備內容對照

| 規格要求 | 本程式殼 |
|---|---|
| `src/`、`include/`、`tests/`、`Makefile` | 已提供 |
| `README.md` | 改寫本檔 |
| `docs/interface.md` | 固定介面已寫好；補上各組決定的項目與新增的參數 |
| `TEAM_LOG.md`、`CONTRIBUTIONS.md`、`AI_USAGE.md` | 範本，需填寫 |
| `demo/` | 空資料夾，放示範音檔的前後對照 |
| `slides.pdf` | 自行加入 |
