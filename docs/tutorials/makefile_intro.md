# Makefile 入門：從打 gcc 指令升級到打 make

作業寫到 HW2 以後，每次編譯都要打這麼長的指令：

```
gcc -Wall -Wextra -std=gnu99 Linear_Phase_Filter.c wav.c -o Linear_Phase_Filter.exe -lm
```

有沒有辦法只打一個短指令就好？有——把指令寫進一個叫 **Makefile** 的檔案，
以後只要打：

```
mingw32-make
```

Team Project 也要求「clone 指定 SHA 後 `make` 即可建置、`make test` 全過」，
所以這份文件是必修。

> **Windows 同學注意**：照 [vscode_c_starter.md](vscode_c_starter.md) 安裝 MSYS2 UCRT64 工具鏈後，
> 你已經有 `C:\msys64\ucrt64\bin\mingw32-make.exe`，在 PowerShell 裡打 `mingw32-make` 就能用。
> 若找不到，在 MSYS2 UCRT64 終端機執行 `pacman -S mingw-w64-ucrt-x86_64-make`。
> 不要用 `pacman -S make`：它裝在 `C:\msys64\usr\bin`，那個資料夾不在你設定的 PATH 裡。
> 以下文字中的 `make` 都是指 `mingw32-make`（macOS/Linux 同學直接打 `make`）。

---

## Makefile 的基本語法：規則

Makefile 由一條條「規則」組成，長這樣：

```makefile
目標: 材料
	怎麼做（指令）
```

用白話說：「想做出**目標**，需要**材料**，做法是執行**指令**」。例如：

```makefile
sine_wav_gen.exe: sine_wav_gen.c
	gcc sine_wav_gen.c -o sine_wav_gen.exe -lm
```

意思是：想做出 `sine_wav_gen.exe`，材料是 `sine_wav_gen.c`，做法是那行 gcc 指令。

> **天字第一號地雷**：指令那行的開頭必須是一個 **Tab**，
> 用空白會出現 `missing separator` 錯誤。在 VSCode 貼上時特別注意。

make 還有一個聰明之處：如果 `sine_wav_gen.c` 從上次編譯後**沒有改過**，
再打 `make` 它會說 `up to date`，直接跳過——檔案多的專案能省下大量時間。

---

## 逐行看懂一個作業用的 Makefile

假設你的 `hw2/` 資料夾裡有三個 C 檔：WAV 讀寫寫在 `wav.c`／`wav.h`，
兩支濾波程式都要用到它。

```makefile
CC     = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -O2
LDLIBS = -lm
```

這是**變數**：`CC` 存編譯器名稱、`CFLAGS` 存編譯選項、`LDLIBS` 存要連結的函式庫。
之後用 `$(CC)`、`$(CFLAGS)` 取出來用，要換編譯器或加選項只需改這裡。

順便認識這些選項（建議你自己編譯時也都加上）：
- `-Wall -Wextra`：打開幾乎所有警告，幫你抓潛在 bug。
- `-std=gnu99`：使用 C99 標準加上 GNU 擴充。**不要用 `-std=c99`**：嚴格 C99 模式下
  `math.h` 不會定義 `M_PI`，你的 `sin(2*M_PI*f*n/fs)` 會出現 `'M_PI' undeclared`。
- `-O2`：最佳化。HW3 對整首歌做 1025 點卷積，有沒有 `-O2` 速度差好幾倍。
- `-lm`：連結數學函式庫（`sin`、`cos`、`sqrt`…）。MSYS2 上不加也能編，
  但 Linux/macOS 一定要加，加了也無害。

```makefile
ifeq ($(OS),Windows_NT)
    EXE = .exe
    RM  = del /Q
else
    EXE =
    RM  = rm -f
endif
```

這是**條件判斷**：Windows 系統會有環境變數 `OS=Windows_NT`，藉此決定
輸出檔名要不要加 `.exe`，以及刪檔指令要用 `del` 還是 `rm`。
（`mingw32-make` 在 Windows 上是透過 `cmd.exe` 執行指令，`cmd` 沒有 `rm`。）

```makefile
PROGS = Linear_Phase_Filter$(EXE) Minimum_Phase_Filter$(EXE)

all: $(PROGS)

Linear_Phase_Filter$(EXE): Linear_Phase_Filter.c wav.c wav.h
	$(CC) $(CFLAGS) Linear_Phase_Filter.c wav.c -o $@ $(LDLIBS)

Minimum_Phase_Filter$(EXE): Minimum_Phase_Filter.c wav.c wav.h
	$(CC) $(CFLAGS) Minimum_Phase_Filter.c wav.c -o $@ $(LDLIBS)
```

- `all` 是第一條規則，所以只打 `make` 時會執行它；它依賴兩支程式，於是兩支都會被編出來。
- `$@` 是「這條規則的目標」，省得把檔名再打一次。
- 把 `wav.h` 也列為材料：改了標頭檔，用到它的程式就會重新編譯。

```makefile
clean:
	$(RM) $(PROGS)

.PHONY: all clean
```

`clean` 是慣例上的「打掃」規則：`make clean` 會刪掉編譯產物，
讓你可以從乾淨狀態重新編譯。`.PHONY` 告訴 make 這些不是真的檔案。

---

## 實際操作

```
mingw32-make            # 編譯（執行第一條規則 all）
mingw32-make            # 再打一次 → 'Nothing to be done for all'，因為都沒改
mingw32-make clean      # 刪掉編譯產物
mingw32-make            # 又會重新編譯了
```

---

## 練習：幫 HW1 寫一個 Makefile

在你的 `hw1/` 資料夾建立檔案（檔名就叫 `Makefile`，沒有副檔名），內容：

```makefile
CC     = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -O2
LDLIBS = -lm

ifeq ($(OS),Windows_NT)
    EXE = .exe
    RM  = del /Q
else
    EXE =
    RM  = rm -f
endif

all: sine_wav_gen$(EXE) RC_filtering$(EXE)

sine_wav_gen$(EXE): sine_wav_gen.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

RC_filtering$(EXE): RC_filtering.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

test: all
	./sine_wav_gen$(EXE) 8000 400 1.0 sincos_fs8000_f400_L1.0.wav
	./RC_filtering$(EXE) sincos_fs8000_f400_L1.0.wav filtered_f400.wav

clean:
	$(RM) sine_wav_gen$(EXE) RC_filtering$(EXE) *.wav

.PHONY: all test clean
```

`$<` 是「第一個材料」。存檔後打 `mingw32-make` 試試（記得指令行開頭是 Tab！），
再打 `mingw32-make test` 會編譯後直接產生測試音檔並濾波。

---

## 常見問題

**Q1：`missing separator. Stop.`？**
指令行開頭用了空白而不是 Tab。刪掉重打一個 Tab。

**Q2：PowerShell 說「無法辨識 'make' 詞彙…」？**
Windows 上的指令名稱是 `mingw32-make`，不是 `make`。見文件開頭的注意事項。

**Q3：`make clean` 出現 `CreateProcess(NULL, rm -f ...) failed`？**
你的 Makefile 在 Windows 上用了 `rm`。照上面的 `ifeq ($(OS),Windows_NT)` 寫法改用 `del /Q`。

**Q4：明明改了程式，make 卻說 up to date？**
檔案忘了存檔（`Ctrl+S`），或你改的檔案不在規則的「材料」清單裡。

**Q5：Makefile 沒有反應？**
確認檔名是 `Makefile` 或 `makefile`（不能有 .txt 之類的副檔名；Windows 檔案總管預設會隱藏副檔名，請打開「副檔名」顯示確認）。
