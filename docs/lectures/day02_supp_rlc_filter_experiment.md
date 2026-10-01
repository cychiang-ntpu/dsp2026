# Day-2 補充：土製 RLC 濾波器的實驗模擬

[← day02_4_simulation_by_discrete.md](day02_4_simulation_by_discrete.md) ｜ [Day-2 總覽](day02_continuous_to_discrete.md) ｜ [day03_speech_signal_representation.md →](day03_speech_signal_representation.md)

## 2. Continuous/Analog World

> 本節為 2021 年「訊號與系統」課程的實作題，保留供有興趣的同學參考；本學期不列入作業。

## 2.1. 實驗目的：
1. 了解電阻的特性 

```math
R=\frac{\rho L}{A} \qquad\text{(1)}
```

其中 $`\rho`$ 代表電阻係數、$`A`$ 代表截面積、$`L`$ 為長度。
2. 了解電容的特性

```math
C=\frac{\kappa\epsilon_0 A}{d} \qquad\text{(2)}
```

其中 $`\kappa`$ 為介電係數(dielectric constant)、$`\epsilon_0`$ 為真空環境為準的介電常數(permittivity of free space)、$`A`$ 代表平行電極板的重疊面積、$`d`$ 代表兩電極板之間的距離。
3. 了解交流電、電阻、電抗、阻抗的意義
4. 理解 RLC 低通濾波器的工作原理
5. 了解怎麼在真正實驗前做「模擬」，「謀定而後動」，「工程施作前都可以精密計算」！


## 2.2. 實驗材料：
1. 烤肉用鋁箔紙 (可作為平行電極板，亦可作為土製電阻的兩端接點使用)
2. 多張 A4 紙張 (可作為 dielectric 電介質)
3. 口紅膠 (可做為黏著電極板和電介質用、亦可做電介質)
4. 保鮮膜 (可作為 dielectric 電介質)
5. 迴紋針 (作為電容或電阻兩端電極接點使用，所以要是全金屬的)
6. 2B 鉛筆 (可做成電阻使用)
7. 訂書機+訂書針 (可做固定土製電阻兩端的鋁箔紙電極使用)
8. 單芯或多芯電線

## 2.3. 實驗設備及工具：
1. 函數產生器
2. 示波器
3. 剝線鉗
4. 鴨嘴鉗


---

## 2.4. 基本題：RC Low-Pass Filter 製作

回答以下 Problems 1-6 (每一題都 15 Points)

請利用以上列出的實驗材料設計出如圖一所示的 RC low-pass filter，以符合以下之規格 (specification/spec)：
1. $`lim_{\omega \to 0} V_{out}(t)=5`$
2. $`lim_{\omega \to \infty} V_{out}(t)=0`$
3. 輸入一個 8,000Hz 的弦波 $`V_{in}(t)=5\cos(2\pi\cdot 8000t)`$，輸出為 $`V_{out}(t)=\frac{5}{\sqrt{2}}\cos(2\pi\cdot 8000t-\frac{\pi}{4})`$

![](https://i.imgur.com/O7CPBVw.png)

### 2.4.1. Problem 1 
請設計一組 $`R`$ 以及 $`C`$ 的值，符合以上的 spec，建議值 $`R\in[1\times 10^4, 2\times 10^4] \Omega`$，$`C \in [10^{-9}, 10^{-8}] \text{F}`$。

Solution: 
因為要讓 $`f=8000Hz`$ 的弦波通過低通濾波器之後的振幅是原本的 $`1/\sqrt2`$ 倍，所以要讓 $`1/\sqrt{1+(2\pi 8000RC)^2}=1/\sqrt{2}`$，也就是要讓：


```math
RC=\frac{1}{2\pi 8000}\approx 1.989436\times 10^{-5} \qquad\text{(1.1)}
```


所以可以做以下 $`R`$ 以及 $`C`$ 的選擇，只要符合數學式(1.1)就好：
1. $`R\approx 1.989436\times 10^{4}\Omega=19.89436k\Omega`$ 以及 $`C\approx 1.0\times 10^{-9} \text{Farad}=1.0 \text{nF(Nanofarads)}`$
2. $`R\approx 1.0\times 10^{4}\Omega=10K\Omega`$ 以及 $`C\approx 1.989436\times 10^{-9} \text{Farad}\approx 1.99 \text{nF(Nanofarads)}`$

### 2.4.2. Problem 2
使用 Geogebra 繪製 $`V_{in}(t)`$ 以及 $`V_{out}(t)`$，將繪製好的 GeoGebra 圖形連結製作成 QR Code，放在繳交作業的 pdf 檔裡。
> GeoGebra 互動圖：https://www.geogebra.org/calculator/qevjwhbp


### 2.4.3. Problem 3
若根據 Problem 1 設計的 $`R`$ 以及 $`C`$ 參數來製作實體的電阻，電阻使用鉛筆來製作，電容使用鋁箔紙以及紙來製作，請手繪製電阻以及電容的設計圖，說明如何製作？

Solution:
1. 電容：製作電容時，將兩片鋁箔紙中間放紙張後以迴紋針固定，透過改變紙張大小及厚度來達成目標電容值。
![](https://i.imgur.com/edCtz4w.jpg)
2. 電阻：用 2B 鉛筆筆跡製作電阻，改變筆跡深淺和筆跡寬度以調整電阻值，將單芯線放置於筆跡兩端再用膠帶固定，單芯線的距離越大電阻越大。
![](https://i.imgur.com/loqOyD1.png)


### 2.4.4. Problem 4
續 Problem 3，根據數學式 (1) 以及 (2) 來設計，則數學式 (1) 裡面的 $`L`$ 和 $`A`$ 是多少？數學式 (2) 的 $`A`$ 和 $`d`$ 是多少？ 請注意 $`\rho`$ 可以找“碳或石墨”的導電度/電阻率做為數據，而 $`\kappa`$ 使用“紙”的 dielectric constant。本題需要計算過程，沒有計算過程不計分。另外，$`\rho`$ 以及 $`\kappa`$ 的值在哪裡找到的，要附上參考文獻（網址或書都可以），沒有附上參考文獻，本題不計分。

Solution:
1. 根據網路上找到的論文(https://iopscience.iop.org/article/10.1088/1742-6596/1144/1/012165/pdf)，鉛筆的電阻率大概是：

```math
\rho=99.94 m\Omega\cdot cm
```

也就是

```math
\rho=99.94\, m\Omega\cdot cm=99.94\times 10^{-2}\, m\Omega\cdot m\approx 1.0\times 10^{-3}\,\Omega\cdot m
```

一張A4紙的厚度大概 $`0.104mm=1.04\times 10^{-4}m\approx 10^{-4}m`$ (https://zhidao.baidu.com/question/1372229580220774859.html)，我們假設用2B鉛筆塗在一張A4的紙上，塗成黑色的部份是厚度為 $`H`$，寬度為 $`W`$，長度為 $`L`$，金黃色的部分是迴紋針可以導電，也就是電阻的兩端，所以由導電的迴紋針看進去這個電阻，截面積 $`A=HW`$，長度是 $`L`$。
![](https://i.imgur.com/tRZ9pt6.png)
電阻值就可以估計為：

```math
R=\frac{\rho L}{HW}=19.89436k\Omega=1.989436\times 10^4\Omega
```

鉛筆在紙上留下的石墨層非常薄，遠小於紙張厚度，這裡假設 $`H\approx 1\,\mu m=10^{-6}m`$，筆跡寬度 $`W=1mm=10^{-3}m`$，則長度可以是：

```math
L=\frac{RHW}{\rho}=\frac{(1.989436\times 10^4)(10^{-6})(10^{-3})}{10^{-3}}\approx 1.99\times 10^{-2}m\approx 2cm
```

2.因為鋁箔紙中間夾的是A4紙，所以我們要找到紙的 dielectric constant $`\kappa=1.4`$ (https://en.wikipedia.org/wiki/Relative_permittivity)，而A4紙的厚度是 $`d=10^{-4}m`$，在 $`C\approx 1.0\times 10^{-9}F`$ 的情況下，兩張鋁箔紙重疊的面積是：

```math
A=\frac{Cd}{\kappa \epsilon_0}=\frac{10^{-9}10^{-4}}{1.4\times 8.85418782\times 10^{-12}}=\frac{10^{-13}}{12.395862948\times 10^{-12}}=8.067207617\times 10^{-3}m^2
```

若鋁箔紙是正方形，則邊長為 $`\sqrt{A}=0.08981763533 m\approx 9cm`$

### 2.4.5. Problem 5
請手寫推導出以下問題：
若

```math
V_{in}(t)=2.5+2.5\sum_{k=0}^{9}\frac{4}{\pi}\frac{sin(2\pi (2k+1)ft)}{2k+1} \qquad\text{(3)}
```

且 

```math
f=2000(Hz) \qquad\text{(4)}
```

則 

```math
V_{out}(t)=?
```


Solution:
![](https://i.imgur.com/k55O2BO.png)

![](https://i.imgur.com/PI8RgM7.png)


### 2.4.6. Problem 6
使用 Geogebra 繪製 Problem 5 的 $`V_{in}(t)`$ 以及 $`V_{out}(t)`$，將繪製好的 GeoGebra 圖形連結製作成 QR Code，放在繳交作業的 pdf 檔裡。
> GeoGebra 互動圖：https://www.geogebra.org/calculator/wxpw2rpt


從上圖可以發現到，輸出的 $`V_{out}(t)`$ 比較於 $`V_{in}(t)`$ 沒有快速上下跳動信號，因為那些快速上下跳動的信號就是頻率比較高的成分， $`V_{in}(t)`$ 的高頻成分 ($`k`$ 比較大的部分)，振幅會被衰減得比較嚴重。

---

## 2.5. 進階題：RLC Filter 製作

回答以下 Problems 7-11 (每一題都 15 Points)

### 2.5.1. Problem 7
如圖二，請求取圖中的 $`A(\omega)`$ 以及 $`\phi(\omega)`$
![](https://i.imgur.com/FIkaLAh.png)

圖2：電阻 (R)、電容(C)、電感(L)串並聯電路

Solution:

![](https://i.imgur.com/yVL9QLn.png)


### 2.5.2. Problem 8
續 Problem 7，若 $`R=1\Omega`$、$`L=\frac{1}{2\pi\cdot 8000} \text{Henry}`$、以及 $`C=\frac{1}{2\pi\cdot 8000} \text{Farad}`$，請用 Geogebra 繪製 $`A(f)`$ 以及 $`\phi(f)`$，小心！橫軸是用 $`f`$ 不是用 $`\omega`$。繪製圖形的時候要調整x/y兩軸的範圍，方便觀察，建議 $`f \in [0, 24000]`$、$`A(f) \in [0, 1]`$、以及 $`\phi \in [-\frac{\pi}{2}, \frac{\pi}{2}]`$。將繪製好的 GeoGebra 圖形連結製作成 QR Code，放在繳交作業的 pdf 檔裡。

Solution for $`A(f)`$:
> GeoGebra 互動圖：https://www.geogebra.org/calculator/ynbwvh8y


Solution for $`\phi(f)`$
> GeoGebra 互動圖：https://www.geogebra.org/calculator/xvbucuww


### 2.5.3. Problem 9
續 Problem 8，請找到 $`A(f)`$ 這個函數的水平漸近線、以及垂直漸近線。

Solution: 
$`A(f)`$ 沒有垂直漸近線，只有水平漸近線 $`A(f) = 1`$

### 2.5.4. Problem 10
續 Problem 8，若圖2中的 $`V_x(t)=V_{in}(t)`$ (數學式(3)、(4)的定義)，則 $`V_y(t)`$ 為何？ 請將數學式寫出來。

Solution:
![](https://i.imgur.com/3S4MZ5H.png)


### 2.5.5. Problem 11
續 Problem 10，使用 Geogebra 繪製 Problem 10 的 $`V_{x}(t)`$ 以及 $`V_{y}(t)`$，將繪製好的 GeoGebra 圖形連結製作成 QR Code，放在繳交作業的 pdf 檔裡。

Solution:
> GeoGebra 互動圖：https://www.geogebra.org/calculator/nbrkmkmj

---

[← day02_4_simulation_by_discrete.md](day02_4_simulation_by_discrete.md) ｜ [Day-2 總覽](day02_continuous_to_discrete.md) ｜ [day03_speech_signal_representation.md →](day03_speech_signal_representation.md)
