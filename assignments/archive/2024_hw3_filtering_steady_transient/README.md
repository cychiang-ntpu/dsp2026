# 【歷年題目】DSP Assignment-3 (2024)：Filtering: Steady and Transient States

> 來源：[HackMD 原始頁面](https://hackmd.io/QgTHBIoYRwSuiLTZDn3Gmw)（公布 2024/12/22，截止 2025/1/5）。
> 本題為 113 學年度的作業，**已併入本學期 [HW2 Part B](../../hw2_transform_analysis/)**；此處保留原文供對照。

## 1. 作業學習目標
1.	熟悉 DTFT 以及 IDTFT 的數學以及使用方法
2.	了解在 LTI 系統在做 filtering 時的 transient/steady state 與 impulse response 長度的關係
3.	實作 ideal low-pass filter
4.	了解 Linear phase 以及 minimum phase 的意義


## 2. 作業內容
1. 設計多個 low-pass filter 以符合以下的 spec (specification):
    * 針對取樣率為 $f_s=44100$ Hz 的雙聲道音樂 (\*.wav) 處理。
    * Cutoff frequency 在 $f_c=4000$ Hz 的 linear-phase low-pass filter。
    * 其理想的 frequency response 為
$$H_{lp}(e^{j\omega})=\begin{cases}
1, \text{ } |{\omega}|<\omega_c\\
0, \text{ } \omega_c \leq|\omega| \leq \pi \\
\end{cases}$$
    * 而實作上只能使用以下數學式 FIR system 之 impulse response 來實現，注意! 應該還要再乘上 window，比如 hamming 或是 blackman 才會比較好。
$$h_{M}[n]=\begin{cases}
\frac{\sin(\omega_c n)}{n\pi}*\delta[n-M], \text{ } {0 \leq n\leq 2M}\\
0, \text{otherwise}\\
\end{cases}$$
    * 建立 5 種不同 order 數的 low-pass filter: $M=4, 16, 64, 512, 2048$。注意! order=$2M$。
    
2. 繪製出 impulse response $h_{M}[n]$ for $M=4, 16, 64, 512, 2048$

3. 繪製出 magnitude response:$|H_{M}(e^{j\omega})|$ 以及 phase response:$\angle H_{M}(e^{j\omega})$ for $M=4, 16, 64, 512, 2048$，其中 $H_{M}(e^{j\omega})=\text{DTFT}\{h_{M}[n]\}$ ，繪製的結果要類似課本的圖例，要附上產生$|H_{M}(e^{j\omega})|$資料點以及繪圖的 code 繳交:
![XXXX](https://hackmd.io/_uploads/HkeuvzVB1l.jpg)

4. 實作多個 LCCDE 將 HW1 產生的波形輸入至 $h_{M}[n]$ 為 impulse response 的系統，輸出之波形儲存成 wav 檔。考慮並討論頻率為 1000Hz、3000Hz、4000Hz、5000Hz、8000Hz 的輸入。

5. 討論不同 $M$ 情況下 low-pass filter 的 transient 以及 steady state 的輸出為何?

5. 建立以下 3 種不同 order 數對應 $h_{M}[n]$ 的 minimum-phase low-pass filter: $M=4, 16, 64$，重複以上的 impulse response、magnitude response、phase response 繪製以及濾波實驗，並且和 linear-phase low-pass filter 的結果比較。



    
---

## 3. 要求
### 3.1 程式要求

#### 3.1.1 產生 sine waveform 程式 `sine_wav_gen.c`
使用方法如下：
```
./sine_wav_gen.exe fs f L out_fn
```
其中：
* `sine_wav_gen.exe`: 執行檔檔名
* `fs`: 取樣率 (單位: Hz)
* `f`: sine wave 的頻率 (單位: Hz)
* `L`: sine wave 的長度 (單位: second)
* `out_fn`: 音檔檔名

使用範例：
```
./sine_wav_gen.exe 8000 3000 1.0 sincos_fs8000_f3000_L1.0.wav
```
以上指令可以產生名為 `sincos_fs8000_f3000_L1.0.wav` 的音檔，這個音檔是一個取樣率為 `8000`Hz 的 `1.0` seconds 雙聲道聲音，左聲道為 sine wave，右聲道為 cosine wave，分別模擬 $x_l(t)=\sin(2\pi f t)$ 以及 $x_r(t)=cos(2\pi f t)$，左右聲道一起考量就是在模擬 complex exponential $x(t)=\exp{(j 2\pi f t)}$. 


#### 3.1.2 不同 order 數的 linear-phase 的濾波程式 `Linear_Phase_Filter.c`

使用方法如下：
```
./Linear_Phase_Filter.exe fc M b_fn.txt in_fn.wav out.fn.wav`
```
其中：
* `Linear_Phase_Filter.exe`: 執行檔檔名。
* `fc`: low-pass filter 的 cutoff frequency，單位是 Hz。
* `M`: 2M 是代表 linear phase filter 的 order 數
* `b_fn.txt`: 一個儲存 linear phase filter 係數以及poles/zeros 位置的文字檔，格式自訂。
* `in_fn.wav`: 輸入的音檔檔名 (必須是 WAVE 檔)
* `out_fn.wav`: 經過濾波後的音檔檔名

使用範例：
```
./Linear_Phase_Filter.exe 400 32 coef.txt sincos_fs8000_f3000_L1.0.wav filtered_sincos_fs8000_f3000_L1.0.wav`
```
以上指令可以將名為 `sincos_fs8000_f3000_L1.0.wav` 的音檔，經過 `2*32=64-th order` 的 linear phase filter，且此 filter 的 cutoff frequency 是 `400Hz`，此程式將此 linear-phase filter 的係數以及 poles/zeros 資訊儲存在 `coef.txt` 檔案，對於 complex exponential 中的 sine wave 以及 cosine wave 進行濾波，將濾波的結果儲存成 `filtered_sincos_fs8000_f3000_L1.0.wav`。

請注意！`sincos_fs8000_f3000_L1.0.wav` 檔案已經有紀錄音訊的取樣率，所以在 `RC_filtering.c` 應該可以由 `*.wav` 檔的 header 得到 sampling rate 資訊。


#### 3.1.3 不同 order 數的 minimum-phase 的濾波程式 'Minimum_Phase_Filter.c'

使用方法如下：
```
./Minimum_Phase_Filter.exe fc M b_fn.txt in_fn.wav out.fn.wav`
```
其中：
* `Minimum_Phase_Filter.exe`: 執行檔檔名。
* `fc`: low-pass filter 的 cutoff frequency，單位是 Hz。
* `M`: 2M 是代表 linear phase filter 的 order 數
* `b_fn.txt`: 一個儲存 minimum-phase filter 係數以及poles/zeros 位置的文字檔，格式自訂。
* `in_fn.wav`: 輸入的音檔檔名 (必須是 WAVE 檔)
* `out_fn.wav`: 經過濾波後的音檔檔名

使用範例：
```
./Minimum_Phase_Filter.exe 400 32 coef.txt sincos_fs8000_f3000_L1.0.wav filtered_sincos_fs8000_f3000_L1.0.wav`
```
以上指令可以將名為 `sincos_fs8000_f3000_L1.0.wav` 的音檔，經過 `2*32=64-th order` 的 linear phase filter，且此 filter 的 cutoff frequency 是 `400Hz`，此程式將此 linear-phase filter 的係數以及 poles/zeros 資訊儲存在 `coef.txt` 檔案，對於 complex exponential 中的 sine wave 以及 cosine wave 進行濾波，將濾波的結果儲存成 `filtered_sincos_fs8000_f3000_L1.0.wav`。

#### 3.1.4 一個執行整個作業動作的 Jupyter Notebook file `DSP_Assignment_3.ipynb` 檔案
請在這個 ipynb 檔案裏面包含以下動作：
1. 撰寫 Markdown 說明程式流程以及結果討論。
2. 編譯所有 C Code。
3. 執行所有以 C Code 撰寫並建置好的程式。
    * 包含 linear-phase filter 的 $M=4, 16, 64, 512, 2048$ 以及 1000Hz、3000Hz、4000Hz、5000Hz、8000Hz sine/cosine waves 輸入和對應輸出。
    * 包含 minimum-phase filter 的 $M=4, 16, 64$ 以及 1000Hz、3000Hz、4000Hz、5000Hz、8000Hz sine/cosine waves 輸入和對應輸出。
4. 以 Python 相關函式繪製 $|H_{M}(e^{j\omega})|$ 以及 $\angle H_{M}(e^{j\omega})$，相關參數可以讀取 `Linear_Phase_Filter.c` 以及 `Minimum_Phase_Filter.c` 輸出的 `coef.txt`。
### 3.2 繳交方法
* 請同學將所有作業內容放置於 GitHub project。
* 同學僅要在數位學苑 3.0 繳交提供 GitHub project link 即可。記得將 project 以 private 邀請 cychiang@mail.ntpu.edu.tw。
* GitHub project 裡面包含以下四的檔案：
    1. 產生 sine waveform 程式 `sine_wav_gen.c`
    2. 不同 order 數的 linear-phase 的濾波程式 `Linear_Phase_Filter.c`
    3. 不同 order 數的 minimum-phase 的濾波程式 `Minimum_Phase_Filter.c`
    4. 一個執行整個作業動作的 Jupyter Notebook file `DSP_Assignment_3.ipynb` 檔案
* 作業進行批改時，只會跑 `DSP_Assignment_3.ipynb`，所以所有的動作都在 `DSP_Assignment_3.ipynb` 裡面執行，所以 C code 的編譯以及編譯出程式的執行都是由此 `DSP_Assignment_3.ipynb` 呼叫，所有展示用的圖片都是要用程式產生，不能用手動存檔，批改時只會看 `DSP_Assignment_3.ipynb` 執行產生結果。
    



---

## Hint
1. Find root by GNU Scientific Library (GSL): https://www.gnu.org/software/gsl/doc/html/poly.html#examples
Find root https://docs.sympy.org/latest/guides/solving/find-roots-polynomial.html
