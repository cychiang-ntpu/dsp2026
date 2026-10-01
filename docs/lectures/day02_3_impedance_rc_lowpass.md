# Day-2-3：阻抗與 RC 低通濾波器

[← day02_2_rlc_phase.md](day02_2_rlc_phase.md) ｜ [Day-2 總覽](day02_continuous_to_discrete.md) ｜ [day02_4_simulation_by_discrete.md →](day02_4_simulation_by_discrete.md)

## 1.3. 阻抗以及其應用
阻抗（electrical impedance）是電路中電阻、電感、電容對交流電的阻礙作用的統稱。阻抗衡量流動於電路的交流電所遇到的阻礙。***阻抗將電阻的概念加以延伸至交流電路領域，不僅描述電壓與電流的相對振幅，也描述其相對相位***。當通過電路的電流是直流電時，電阻與阻抗相等，電阻可以視為相位為零的阻抗。

> 歷史上課影片：「交流電、電阻、電抗、阻抗 」系列 - 7 (2021/6)
> 1. 回顧交流電為什麼用 sin cos 表示
> 2. 回顧流經過電阻、電容、以及電感之電流與電壓之關係
> 3. RC 串聯交流電路簡介

- 影片：https://www.youtube.com/watch?v=e51D-vlVCe4

### 1.3.1. RC 串聯交流電路
#### 1.3.1.1. RC串聯阻抗

交流電路中的阻抗，是一個複數，例如圖3.1 顯示一個簡單的 RC 串聯的交流電路，其中阻抗 $`Z`$ 就等於電阻 $`R`$ 與容抗 $`X_C`$ 的和，即 $`Z=R+X_C`$，也就是：


```math
Z=R+\frac{1}{j\omega C} \qquad\text{(3.1)}
```

 


![](https://i.imgur.com/Ls0OKPv.png)
圖3.1：RC串聯電路

當交流電流流過 $`R`$ 和 $`C`$ 串聯的電路時，總電壓降等於電阻所造成的電壓降和電容所造成的電壓降之和，即：


```math
V_a-V_b=V_{RC}=V_R+V_C=IR+\frac{Q}{C} \qquad\text{(3.2)}
```


若以***相子***表示時：


```math
\vec{V_{RC}}=\vec{I}R+\vec{I}\frac{1}{j\omega C}=\vec{I}Z \qquad\text{(3.3)}
```


則 $`Z=R+\frac{1}{j\omega C}`$ 被稱之為此電路之阻抗。

#### 1.3.1.2 於 RC 串聯電路中**電壓**與**電流**的相對**振幅**及相對**相位**

在這裡我們想要了解以下幾個關係：
1. 跨越過RC的電壓 $`V_{RC}`$
2. 流經過RC的電流 $`I`$
3. $`V_{RC}`$ 和 $`I`$ 的相對振幅及相對相位


> 歷史上課影片：「交流電、電阻、電抗、阻抗 」系列 - 8 (2021/6)

- 影片：https://www.youtube.com/watch?v=qpQneqZN-7w

類似於之前分析一個電容或是一個電感的方法，考慮一個角頻率為 $`\omega`$ 的交流電流 $`I(t)=I_psin(\omega t)`$ 流過 RC 的串聯電路，並將此交流電流以相子表示：$`\vec{I}=I_p e^{j \omega t}`$，所以 $`I(t)=Im\{\vec{I}\}`$ ，重寫數學式 (3.3) 可得：


```math
\vec{V_{RC}}=\vec{I}Z=I_p e^{j \omega t}(R+\frac{1}{j\omega C}) \qquad\text{(3.4)}
```


雖然 RC 串聯電路的總阻抗 $`Z=R+\frac{1}{j\omega C}`$ 就是代表電壓 $`V_{RC}`$ 和電流 $`I`$ 之間的比值，但由數學式 (3.4) 並沒有辦法明顯且直接觀察出此關係，因此，我們必須將 $`Z=R+\frac{1}{j\omega C}`$ 改寫成 Euler’s formula 的型式，也就是 $`Z=Ae^{j\phi}`$，其中 $`A`$ 就代表電壓和電流相對的振幅比值，而 $`\phi`$ 就是電壓和電流的相對相位差，可以用以下方法將 $`A`$ 和 $`\phi`$ 求出：


```math
\begin{gathered}
Z=R+\frac{1}{j\omega C}=R+\frac{j}{j^2\omega C}=R-\frac{1}{\omega C}j \\
=\sqrt{R^2+(\frac{1}{\omega C})^2} \exp(j\tan^{-1}(-\frac{1}{\omega RC}))=Ae^{j\phi}
\end{gathered} \qquad\text{(3.5)}
```


所以我們得到：


```math
A=\sqrt{R^2+(\frac{1}{\omega C})^2} \qquad\text{(3.6)}
```


```math
\begin{gathered}
\phi=\tan^{-1}(-\frac{1}{\omega RC})=-\tan^{-1}(\frac{1}{\omega RC})=-\cot^{-1}(\omega RC) \\
=-(\frac{\pi}{2}-\tan^{-1}(\omega RC))=\tan^{-1}(\omega RC)-\frac{\pi}{2}
\end{gathered} \qquad\text{(3.7)}
```


由數學式 (3.6) 和 (3.7) 可以發現到相對振幅 $`A`$ 和相對相位 $`\phi`$ 皆是角頻率 $`\omega`$、電容值 $`C`$ 和電阻值 $`R`$ 的函數，代表說不同頻率的交流電流會造成不同的振幅和相位、不同 RC 參數也會有不同的振幅和相位。如果我們重寫數學式 (3.4)，我們可以得：


```math
\begin{gathered}
\vec{V_{RC}}=\vec{I}Z=I_p e^{j \omega t}(R+\frac{1}{j\omega C})=I_p e^{j \omega t}Ae^{j\phi}=AI_p e^{j(\omega t+\phi)} \\
=\sqrt{R^2+(\frac{1}{\omega C})^2}I_p\exp\{j[\omega t+\tan^{-1}(\omega RC)-\frac{\pi}{2}]\}
\end{gathered} \qquad\text{(3.8)}
```


最後我們以求取虛部的 operator (Im) 將相子 $`\vec{V_{RC}}`$ 轉回跨越RC的弦波電壓變化 $`V_{RC}(t)`$ 得：


```math
\begin{gathered}
V_{RC}(t)=Im\{\vec{V_{RC}}\}=Im[AI_pe^{j(\omega t +\phi)}]=AI_p\sin(\omega t+\phi) \\
=\sqrt{R^2+(\frac{1}{\omega C})^2}I_p\sin[\omega t+\tan^{-1}(\omega RC)-\frac{\pi}{2}]
\end{gathered} \qquad\text{(3.9)}
```


由數學式 (3.9) 可以知道：
1. $`V_{RC}(t)`$仍是一個角頻率為 $`\omega`$ 的正弦波
2. $`V_{RC}(t)`$ 是將原本的電流 $`I(t)=I_p\sin(\omega t)`$ 增益  $`A=\sqrt{R^2+(\frac{1}{\omega C})^2}`$ 倍
3. $`V_{RC}(t)`$ 與電流 $`I(t)=I_p\sin(\omega t)`$ 兩弦波相位差別為 $`\phi=\tan^{-1}(\omega RC)-\frac{\pi}{2}`$
4. $`\phi`$ 會是一個負值，代表電壓 $`V_{RC}(t)`$ 的相位會較電流 $`I(t)`$ 延遲。
> GeoGebra 互動圖：https://www.geogebra.org/calculator/mbmgqqyv


### 1.3.2. RC串聯交流電路之應用- RC低通濾波器 (RC Low-Pass Filter)

> 歷史上課影片：「交流電、電阻、電抗、阻抗 」系列 - 9 (2021/6)

- 影片：https://www.youtube.com/watch?v=J9PVsDiNuaM

https://youtu.be/J9PVsDiNuaM

#### 1.3.2.1 RC 低通濾波器性質推導
圖3.2 RC 電路實現的一個低通電子濾波器，$`V_{in}(t)`$ 代表輸入的電壓，$`V_{out}(t)`$ 代表輸出的電壓，$`V_{out}(t)`$ 將掛載至一個兩端的負載之上，舉例來說 $`V_{in}(t)`$ 可以是智慧型手機耳機音源線的電壓輸出，而 $`V_{out}(t)`$ 可以是一個電腦喇叭的輸入音源線，而此 RC 低通濾波器的功能可以將 $`V_{in}(t)`$ 裡面較高頻的聲音訊號濾除，讓 $`V_{out}(t)`$ 輸出的電壓只保留較低頻的聲音訊號，這個簡單的電路可以應用於由音源線接至中低音喇叭的線路之中。

![](https://i.imgur.com/CPCRSjl.png)

圖3.2：以RC電路實現的一個低通電子濾波器
> GeoGebra 互動圖：https://www.geogebra.org/calculator/rzcb2kcf


此簡單電路包括與一個負載 (如喇叭) 串聯的電阻以及與負載並聯的一個電容，由電容的電抗 $`X_C=\frac{1}{j\omega C}`$ 可得知電容會阻止低頻信號(電流)通過，因此低頻的電流較容易流經負載 (喇叭)，讓電容兩端之電壓振幅較大；反之，較高頻的信號讓電抗 $`X_C=\frac{1}{j\omega C}`$ 減弱，容易造成電容的兩端短路因而電壓振幅較小。以下我們以數學式來進行驗證：

假設 $`V_{in}(t)`$ 的輸入電壓為一個角頻率為 $`\omega`$ 的餘弦波 $`V_{in}(t)=V_pcos(\omega t)=Re(V_pe^{j\omega t})`$，我們想要知道 $`V_{out}(t)`$ 的值為何？

首先將 $`V_{in}(t)`$ 以及 $`V_{out}(t)`$ 使用相子表示，並依據歐姆定律和克希荷夫電壓定律列出關係式，我們可得：


```math
\vec{V_{in}}=V_pe^{j\omega t}=\vec{I}R+\vec{V_{out}}=\vec{I}R+\vec{I}\frac{1}{j\omega C} \qquad\text{(3.10)}
```


```math
\vec{V_{out}}=\vec{I}\frac{1}{j\omega C}=\frac{\vec{V_{in}}}{(R+\frac{1}{j\omega C})}\frac{1}{j\omega C}=\frac{\frac{1}{j\omega C}}{R+\frac{1}{j\omega C}}\vec{V_{in}}=H(\omega)\vec{V_{in}} \qquad\text{(3.11)}
```


數學式 (3.11) 已將 $`\vec{V_{in}}`$ 和 $`\vec{V_{out}}`$ 的關係使用


```math
H(\omega)=\frac{\frac{1}{j\omega C}}{R+\frac{1}{j\omega C}} \qquad\text{(3.12)}
```


這個函數以相乘的形式建立起來，我們稱 ***$`H(\omega)`$ 為「轉換函數」 （transfer function）***。

但是使用 (3.12) 表示會不大容易進行振幅和相位的分析，所以我們改寫此係數成 Euler’s formula可得：


```math
\begin{gathered}
H(\omega)=\frac{\frac{1}{j\omega C}}{R+\frac{1}{j\omega C}}=\frac{1}{1+j\omega RC} \\
=\frac{1}{\sqrt{1+\omega^2 R^2C^2}e^{j\tan^{-1}(\omega RC)}} \\
=\frac{1}{\sqrt{1+\omega^2 R^2C^2}}e^{-j\tan^{-1}(\omega RC)}
\end{gathered} \qquad\text{(3.13)}
```


我們可以令：


```math
A(\omega)=\frac{1}{\sqrt{1+\omega^2 R^2C^2}} \qquad\text{(3.14)}
```


以及


```math
\phi=-\tan^{-1}(\omega RC) \qquad\text{(3.15)}
```


然後重寫 (3.11) 可得：


```math
\vec{V_{out}}=\frac{1}{\sqrt{1+\omega^2R^2C^2}}e^{-j\tan^{-1}(\omega RC)}V_pe^{j\omega t}=A(\omega)V_pe^{j[\omega t+\phi(\omega)]} \qquad\text{(3.16)}
```


因此對數學式(3.16)左右邊都取實部，我們可找到：


```math
V_{out}(t)=A(\omega)V_p\cos(\omega t+\phi(\omega)) \qquad\text{(3.17)}
```


由數學式 (3.17) 可觀察出來：
1. $`V_{out}(t)`$ 的振幅為原本 $`V_{in}(t)`$ 的 $`A(\omega)`$ 倍
2. $`V_{out}(t)`$ 的相位和 $`V_{in}(t)`$ 的相位差為 $`\phi(\omega)`$
3. $`A(\omega)`$ 稱為“轉換函數振幅”(Magnitude of Transfer Function)
4. $`\phi(\omega)`$ 稱為“轉換函數相位”(Phase of Transfer Function)
5. 當 $`\omega=0`$ 時，輸入的電壓為一個直流電 $`V_{in}=V_p\cos(0\cdot t)=V_p`$，則 $`A(0)=1`$ 造成 $`V_{out}(t)=V_p`$，代表此RC低通濾波器的輸出可讓原本的 $`V_{in}=V_p`$ 通過此濾波器，讓 $`V_{in}=V_{out}=V_p`$
6. 如果我們考慮一個極端例子，也就是說極高的頻率 $`\omega\to\infty`$，則 $`\lim_{\omega \to \infty}A(\omega)=0`$，代表高頻率的 $`V_{in}(t)`$無法通過此低通濾波器展現在 $`V_{out}(t)`$ 的振幅上。
7. 如果對 $`A(\omega)`$ 做較一般的討論
    * $`A(\omega)`$ 的最大值發生在 $`\omega =0`$
    * $`A(\omega)`$ 隨著 $`\omega`$ 增加而逐漸變小，代表輸入信號 $`V_{in}(t)`$ 頻率越高，則越不容易在輸出 $`V_{out}(t)`$ 觀察到相對的振幅大小
    * 頻率越低的輸入信號，越容易在輸出觀察到，因此，我們稱此RC電路為一個 “RC低通濾波器”。
> GeoGebra 互動圖：https://www.geogebra.org/calculator/sahmbp6n


#### 1.3.2.2 RC 低通濾波器之截止頻率 (Cutoff Frequency)

截止頻率的定義為轉換函數的振幅由最大值下降至 $`\frac{1}{\sqrt{2}}`$ 倍時的頻率，或輸出平均功率為最大平均功率 $`\frac{1}{2}`$ 時候的頻率，也就是可以找到一個 $`\omega=\omega_c`$ 讓 $`A(\omega_c)=\frac{1}{\sqrt{2}}`$，由數學式 (3.14) 可以知道 ，若輸入信號為


```math
V_{in}=V_p\cos(\omega_c t) \qquad\text{(3.18)}
```


則輸出信號為

```math
V_{out}(t)=\frac{1}{\sqrt{2}}V_p\cos(\omega_c  t-\tan^{-1}(1)) \qquad\text{(3.19)}
```

---

[← day02_2_rlc_phase.md](day02_2_rlc_phase.md) ｜ [Day-2 總覽](day02_continuous_to_discrete.md) ｜ [day02_4_simulation_by_discrete.md →](day02_4_simulation_by_discrete.md)
