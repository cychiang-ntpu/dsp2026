# VSCode C 語言開發環境設定教學（新手入門）

這份文件會帶你從零開始，在 Windows 上安裝好所有工具，
並成功執行你的第一個 C 程式 **Hello, World!**。
完全不需要任何程式開發經驗，照著步驟做即可。

---

## 你會安裝的三樣東西

| 工具 | 用途 |
|------|------|
| **VSCode** | 寫程式用的編輯器（就像寫報告用 Word 一樣） |
| **GCC 編譯器** | 把你寫的 C 程式碼「翻譯」成電腦看得懂的執行檔 |
| **C/C++ 擴充套件** | 讓 VSCode 看得懂 C 語言，提供顏色標示、自動補齊、除錯功能 |

---

## 步驟 1：安裝 VSCode

1. 打開瀏覽器，前往 <https://code.visualstudio.com/>
2. 點藍色的 **Download for Windows** 按鈕。
3. 下載完成後打開安裝檔，一路按「下一步」即可。
   建議勾選「加入 PATH」與「將『以 Code 開啟』加入右鍵選單」。
4. 安裝完成後打開 VSCode，看到歡迎畫面就代表成功了。

> 小提示：想要中文介面，可以按 `Ctrl+Shift+X` 打開擴充套件，
> 搜尋「Chinese (Traditional)」安裝後重新啟動。

---

## 步驟 2：安裝 GCC 編譯器（MSYS2）

VSCode 本身不會編譯 C 程式，我們要另外安裝編譯器 GCC。

1. 前往 <https://www.msys2.org/>，下載安裝檔（installer）。
2. 執行安裝檔，安裝路徑保持預設的 `C:\msys64` 即可，一路下一步。
3. 安裝完成後會自動打開一個黑色的 MSYS2 終端機視窗，
   在裡面輸入以下指令後按 Enter（安裝 GCC 工具組）：

   ```
   pacman -S mingw-w64-ucrt-x86_64-gcc
   ```

   過程中問你 `Proceed with installation? [Y/n]` 時，輸入 `Y` 按 Enter。
4. 安裝完成後，把 GCC 加入 Windows 的 PATH（讓系統找得到它）：
   - 按 `Win` 鍵，輸入「環境變數」，打開「編輯系統環境變數」。
   - 點右下角「環境變數」按鈕。
   - 在上半部「使用者變數」中選 `Path`，按「編輯」。
   - 按「新增」，貼上：`C:\msys64\ucrt64\bin`
   - 一路按「確定」關閉所有視窗。
5. 驗證安裝：按 `Win` 鍵輸入 `cmd` 打開命令提示字元，輸入：

   ```
   gcc --version
   ```

   看到類似 `gcc (Rev...) 13.x.x` 的版本訊息就代表成功了！
   如果出現「不是內部或外部命令」，請回頭檢查第 4 步的 PATH 設定，
   並記得**關掉 cmd 重開**再試一次。

---

## 步驟 3：安裝 C/C++ 擴充套件

1. 打開 VSCode。
2. 按 `Ctrl+Shift+X` 打開左側的「擴充套件」面板。
3. 搜尋 `C/C++`，找到 **Microsoft 出品的「C/C++」**，按 **Install**。
4. （建議）順便搜尋並安裝 **Code Runner**，之後按一個鍵就能執行程式。

---

## 步驟 4：寫你的第一個程式 Hello, World!

1. 在電腦上建立一個資料夾，例如 `C:\Users\你的名字\hello_c`。
   > 注意：資料夾與檔案名稱**避免使用中文和空白**，容易出問題。
2. 在 VSCode 中按 `File > Open Folder...`（檔案 > 開啟資料夾），選擇剛建立的資料夾。
3. 在左側檔案總管按「新增檔案」圖示，命名為 `hello.c`。
4. 輸入以下程式碼並存檔（`Ctrl+S`）：

   ```c
   #include <stdio.h>

   int main(void)
   {
       printf("Hello, World!\n");
       return 0;
   }
   ```

---

## 步驟 5：編譯並執行

### 方法一：使用終端機（建議先學會這個）

1. 在 VSCode 中按 `` Ctrl+` ``（Ctrl 加上鍵盤左上角的反引號）打開內建終端機。
2. 輸入以下指令編譯：

   ```
   gcc hello.c -o hello
   ```

3. 沒有任何錯誤訊息就代表編譯成功，接著執行：

   ```
   .\hello
   ```

4. 看到畫面印出：

   ```
   Hello, World!
   ```

   🎉 恭喜你！你已經成功寫出並執行了第一個 C 程式！

### 方法二：使用 Code Runner（有安裝的話）

打開 `hello.c` 後直接按 `Ctrl+Alt+N`，程式會自動編譯並執行，
結果顯示在下方的 OUTPUT 面板。

---

## 常見問題（FAQ）

**Q1：出現 `gcc 不是內部或外部命令`？**
PATH 沒設定好。回到步驟 2 的第 4 步檢查，設定完記得把 VSCode 整個關掉重開。

**Q2：終端機出現亂碼？**
在終端機輸入 `chcp 65001` 切換成 UTF-8 編碼，或把程式裡的中文改成英文。

**Q3：編譯出現紅色錯誤訊息？**
仔細看錯誤訊息中的**行號**，常見原因：
- 少打了分號 `;`
- 括號 `{}` 或引號 `""` 沒有成對
- 字打錯了（例如 `pritnf`）

**Q4：執行 `.\hello` 說找不到檔案？**
代表前一步編譯沒有成功（有錯誤訊息），先把錯誤修好再執行。

---

## 步驟 6：實戰！讀取 WAV 檔標頭（tools/wav_info.c）

環境都設定好之後，來跑一個和這門課直接相關的程式：
讀取一個 WAV 音檔的標頭，印出聲道數、取樣率、位元數與長度。
之後每份作業都要自己讀寫 WAV，先熟悉它長什麼樣子。

### 6-1 取得程式碼並用 VSCode 打開

1. `git clone https://github.com/cychiang-ntpu/dsp2026`（或下載 ZIP）。
2. 在 VSCode 按 `File > Open Folder...`，打開 `dsp2026/tools` 資料夾。
3. 點開 `wav_info.c` 看看，程式有逐段註解說明 RIFF/WAVE 的 chunk 結構。

### 6-2 編譯

按 `` Ctrl+` `` 打開 VSCode 終端機，輸入：

```
gcc -Wall -Wextra -std=c99 wav_info.c -o wav_info
```

沒有錯誤訊息就代表編譯成功，資料夾裡會多出 `wav_info.exe`（macOS/Linux 為 `wav_info`）。

### 6-3 執行

找任何一個 WAV 檔（Windows 內建的 `C:\Windows\Media\*.wav` 也可以），執行：

```
.\wav_info C:\Windows\Media\tada.wav
```

應該會看到類似輸出：

```
channels    : 2
sample rate : 44100 Hz
bits/sample : 16
frames      : 84008
duration    : 1.905 s
```

### 6-4 想一想

- 這個檔案的取樣週期 T 是多少秒？
- 如果要把它變成 8 kHz，要丟掉多少樣本？直接丟掉會發生什麼事？（HW3 的主題）

---

## 下一步

- 試著修改 `printf` 裡的文字，重新編譯執行看看。
- 學習變數：`int age = 20;` 然後用 `printf("%d\n", age);` 印出來。
- 有問題就把**完整的錯誤訊息**複製起來問老師、助教或搜尋。

環境設定好之後，建議照這個順序繼續看其他教學文件：

1. 《終端機基本操作入門》（terminal_basics.md）——打指令的基本功。
2. 《C 語言速查表》（c_cheatsheet.md）——寫作業放旁邊查。
3. 《C 語言錯誤訊息急救手冊》（c_error_guide.md）——編譯失敗時翻開。
4. 《VSCode 除錯教學》（vscode_debug_tutorial.md）——學會逐行除錯。
5. 《Git 入門》（git_intro.md）——幫程式設存檔點。
6. 《Makefile 入門》（makefile_intro.md）——多檔案專案（HW3/HW4）會用到。

祝學習順利！
