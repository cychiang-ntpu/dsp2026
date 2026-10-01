# Day-2（第 2 週）：From Continuous to Discrete

[← day01_intro_to_dsp.md](day01_intro_to_dsp.md) ｜ [講義目錄](README.md) ｜ [day03_speech_signal_representation.md →](day03_speech_signal_representation.md)


- 日期：2026/9/17（第 2 週，週四）
- 與本學期作業的關係：第 1 節（相子、阻抗、RC 低通濾波器的轉換函數）與第 3 節（以離散訊號模擬 RC 電路）
  是 [HW1](../../assignments/hw1_rc_lowpass/) Part A 與 Part B 的背景知識；第 2 節土製 RLC 濾波器實驗為補充閱讀，本學期不列入作業。

## 1. Very Fundamentals of Continuous Signals and Systems
### 引言一
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


### 引言二
為什麼要學複數 (Complex Number)？在接下來的介紹可以解答這個問題的部分答案！複數在正弦或餘弦交流電路的運算分析中，是一個非常簡單且有利的工具，而在電路中以複數所表示的電壓、電流等物理量，我們通稱之為相子 (phasor)，接下來首先介紹如何使用複數表示某個頻率的交流信號。

---

### 1.1. 複數 (complex number) 和相子 (phasor)

> 歷史上課影片：「交流電、電阻、電抗、阻抗 」系列 - 1 (2021/6)
> 引言一
> 引言二
> 1. 複數 (complex number) 和相子 (phasor)
> 1.1. 以直角座標表示的複數
> 1.2. 以極座標表示的複數
> 1.3. 尤拉表示式 (Euler’s formula)

- 影片：https://www.youtube.com/watch?v=xm51ln3v8-Y

#### 1.1.1. 以直角座標表示的複數
複數 (complex number) 通常我們習慣使用符號 $`z`$ 表示，而複數在直角座標系統 (Cartesian coordinate system) 的表示法是：

```math
z=x+jy \qquad\text{(1)}
```

其中 $`j`$ 定義為 $`\sqrt{-1}`$，$`x`$ 稱為實部 (real part)、$`y`$ 稱為虛部 (imaginary part)，而 $`x`$ 和 $`y`$ 為實數 (real number)。我們可以將複數 $`z`$ 以圖一表示。

![](https://i.imgur.com/b7G3jzp.png)
**圖一**


通常我們可以用 $`Re\{z\}`$ 來表示 complex number $`z`$ 的實部，$`Re`$ 就是 real 的縮寫，而 $`Im\{z\}`$ 來表示 complex number $`z`$ 的虛部，$`Im`$ 就是 imaginary 的縮寫，所以：


```math
x=Re\{z\} \qquad\text{(2)}
```


```math
y=Im\{z\} \qquad\text{(3)}
```


可以特別注意，在圖一裡面，我們將這個複數使用一個向量 (vector) 來代表它在空間中的位置，也就是說，我們把複數當作是一個向量來描述，這個複數是在複數平面 (complex plane, 或稱 z-plane) 上，這個複數平面為一個 2-dimensional (sub)space，這 complex plane 的 basis vectors 就是實數軸 (real axis) 以及虛數軸 (imaginary axis) 所指的方向向量。$`x`$ 就是虛數 $`z`$ 投影在 real axis 的投影量，$`y`$ 就是虛數 $`z`$ 投影在 imaginary axis 的投影量。real axis 和 imaginary axis 兩個互相正交，就是因為互相正交，才有有趣的特性。

---

#### 1.1.2. 以極座標表示的複數
我們亦可以使用極座標方式來表示複數如下：

```math
z=r\cos\theta+j\ r\ sin\theta=r(cos\theta+j\ sin\theta) \qquad\text{(4)}
```

其中 $`x=r\cos\theta`$、$`y=r\sin\theta`$、$`r=(x^2+y^2)^{(1/2)}`$ 為半徑 (radius)，$`\theta`$ 為輻角 (angle)，若 $`x`$ 為正實數 (positive real number) 則 $`z`$ 會在第一和第四象限，則

```math
\theta=tan^{-1}(y/x) \qquad\text{(5)}
```

其中 $`tan^{-1}`$ 是 arctangent，也就是 $`tan`$ 的反函數 (inverse function)，若 $`x`$ 為負實數 (negative real number)，$`z`$ 在第二和第三象限，則

```math
\theta=tan^{-1}(y/x)+\pi \qquad\text{(6)}
```


---

#### 1.1.3. 尤拉表示式 (Euler’s formula)
我們亦可用 「尤拉表示式」 (Euler’s formula) 來表示複數，這種表示方法非常方便，並廣泛應用於訊號處裡的領域裡面，Euler’s formula 為：

```math
e^{j\theta}=cos\theta+j\sin\theta \qquad\text{(7)}
```

因此接下來便可以利用數學式(7)來表示複數數學式(4)的複數 $`z`$：

```math
z=x+jy=r(cos\theta+j\ sin\theta)=re^{j\theta} \qquad\text{(8)}
```

**很重要!!** 數學式(8)可以很簡潔地表示一個複數。

複數之間的加減法，要先轉化成直角座標表示後，實部與實部、虛部與虛部相加(減)後即可，比如：

```math
z_1=r_1e^{j\theta_1}=r_1(cos\theta_1+j\ sin\theta_1)=r_1cos\theta_1+j\ r_1 sin\theta_1=x_1+jy_1 \qquad\text{(9)}
```


```math
z_2=r_2e^{j\theta_2}=r_2(cos\theta_2+j\ sin\theta_2)=r_2cos\theta_2+j\ r_2 sin\theta_2=x_2+jy_2 \qquad\text{(10)}
```


```math
\begin{gathered}
z=az_1+bz_2=a(x_1+jy_1)+b(x_2+jy_2) \\
=(ax_1+bx_2)+j(ay_1+by_2)
\end{gathered} \qquad\text{(11)}
```

其中 $`a`$ 以及 $`b`$ 都是任意實數，所以 $`z`$ 的實部為 $`ax_1+bx_2`$，$`z`$ 的虛部為 $`ay_1+by_2`$。而相乘或相除，則以尤拉表示式運算較方便，例如兩複數相乘：

```math
z_1z_2=(r_1e^{j\theta_1})(r_2e^{j\theta_2})=(r_1r_2)e^{j\theta_1}e^{j\theta_2}=(r_1r_2)e^{j(\theta_1+\theta_2)} \qquad\text{(12)}
```

或兩複數相除：

```math
z_1/z_2=\frac{r_1e^{j\theta_1}}{r_2e^{j\theta_2}}=\frac{r_1}{r_2}\frac{e^{j\theta_1}}{e^{j\theta_2}}=(r_1/r_2)e^{j(\theta_1-\theta_2)} \qquad\text{(13)}
```


---

#### 1.1.4. 相子 (Phasor)
Phasor 是用來描述同一個頻率下$`cos`$和$`sin`$的共同表示方法及工具

> 歷史上課影片：「交流電、電阻、電抗、阻抗 」系列 - 2 (2021/6)
> 1.4. 相子 (Phasor)

- 影片：https://www.youtube.com/watch?v=Qd4CT9nfJQI


在定義好以尤拉表示式的複數之後，接下來我們便可利用此表示式來表示一個正弦信號：

```math
S(t)=V_0sin(\omega t+\phi)=Im\{V_0e^{j(\omega t+\phi)}\} \qquad\text{(14)}
```


其中


```math
V_0e^{j(\omega t+\phi)}=V_0cos(\omega t+\phi)+jV_0sin(\omega t+\phi) \qquad\text{(15)}
```


我們也可以用以下數學是來表示ㄧ個餘弦信號：

```math
C(t)=V_0cos(\omega t+\phi)=Re\{V_0e^{j(\omega t+\phi)}\} \qquad\text{(16)}
```


因為數學式(14)裡面的複數 $`V_0e^{j(\omega t+\phi))}`$ 就是在 z-plane 這個 space 裡面，$`x=Re\{V_0e^{j(\omega t+\phi)}\}`$ 就是在 real axis 上的投影量，$`y=Im\{V_0e^{j(\omega t+\phi)}\}`$ 就是在 imaginary axis 上的投影量。

以實際生活上的例子來說，台灣家用電就是振幅為 $`110\sqrt2`$ Volts 或 $`220\sqrt2`$ Volts 的 60 Hz交流電，以數學來表示就是這個信號 $`S(t)`$：


```math
S(t)=110\sqrt{2}sin(2\pi \cdot 60 \cdot t+\phi)=Im\{110\sqrt{2}e^{j(2\pi \cdot 60 \cdot t+\phi)}\} \qquad\text{(17)}
```


其中 $`V_0`$ 為振幅：

```math
V_0=110\sqrt2 \qquad\text{(18)}
```

> 有沒有覺得很奇怪，一般不是說家用電是 110 V 嗎？為什麼振幅是 $`110\sqrt{2}`$？ 請自行去找到答案。


$`\omega`$ 為角頻率(angular frequency)：

```math
\omega=2\times \pi\times f \qquad\text{(19)}
```


```math
f=60 \text{(unit: Hz)} \qquad\text{(20)}
```


$`t`$ 是時間，單位為秒 (second)，$`\phi`$ 稱為相位 (phase)，值域範圍通常考慮 $`(-\pi,\pi]`$ 或是 $`[0, 2\pi)`$。正弦($`sin`$)以及餘弦($`cos`$)如果用 Euler 表示的話，可以是一樣的數學形式，比如說餘弦 $`C(t)`$ 也可以使用 Euler 的 $`Im\{\}`$ 來表示：


```math
C(t)=V_0cos(\omega t+\phi)=V_0sin(\omega t+\phi+\frac{\pi}{2})=Im\{V_0e^{j(\omega t+\phi+\frac{\pi}{2})}\} \qquad\text{(21)}
```


可以觀察到數學式(21)的 $`C(t)`$ 和數學式(14)的 $`S(t)`$ 可以使用一樣的數學形式 $`Im\{Ve^{j\theta}\}`$ 表示，所以簡單來講，$`sin`$ 以及 $`cos`$ 差別只在相位，可以用一樣的 Euler's formula 來表示之，所以我們可以把這個複數 $`V_0e^{j(\omega t+\phi)}`$ 當作向量 $`\vec{V}`$ 來表示，這樣的表示方法就是「相子」(Phasor)：


```math
\vec{V}=V_0e^{j(\omega t+\phi)} \qquad\text{(22)}
```


我們還是可以利用 $`Im\{\cdot\}`$ 以及 $`Re\{\cdot\}`$ 這兩個 operators 來把 $`S(t)`$ 以及 $`C(t)`$ 由 phasor 還原回來，也就是：


```math
S(t)=Im\{\vec{V}\} \qquad\text{(23)}
```


```math
C(t)=Re\{\vec{V}\} \qquad\text{(24)}
```


如果把 $`C(t)`$ 要從 phasor 以 $`Im\{\}`$ 這個 operator 轉換回來，我們可利用數學式(21)改寫數學式(24)變成：


```math
\begin{gathered}
C(t)=Im\{V_0e^{j(\omega t+\phi+\frac{\pi}{2})}\}=Im\{V_0e^{j(\omega t+\phi)}e^{j(\frac{\pi}{2})}\} \\
=Im\{\vec{V}e^{j(\frac{\pi}{2})}\}
\end{gathered} \qquad\text{(25)}
```


使用 phasor 表示的數學式(25) $`\vec{V}e^{j(\frac{\pi}{2})}`$ 就是原本數學式(23) $`\vec{V}`$ 的相位(phase)偏移(shift)版本，或著說 $`Im\{\vec{V}e^{j(\frac{\pi}{2})}\}`$ 信號是 $`Im\{\vec{V}\}`$ 信號的延遲(delay)版本，或著說 $`C(t)`$ 相對於 $`S(t)`$ 超前了 $`\frac{\pi}{2}`$。

---

##### 重點！
**所以使用 phasor 可以將 $`cos`$ 訊號 ($`C(t)`$) 和 $`sin`$ 訊號 ($`S(t)`$) 可以使一樣的表示方法 (如數學式(23)以及(25))，方便表示以及計算。**

---

#### 1.1.5 相子的應用

**同樣頻率**的弦波相加減

> 歷史上課影片：「交流電、電阻、電抗、阻抗 」系列 - 3 (2021/6)
> 1.5. 相子的應用

- 影片：https://www.youtube.com/watch?v=m3EyOTck12Y

###### 1.1.5.1. Example 1
相位圖使得交流電的運算方便了許多，下面的例子就是一個很好的證明。若有兩個同角頻率的弦波信號：

```math
V_A(t)=V_0sin(\omega t) \qquad\text{(26)}
```


```math
V_B(t)=V_0sin(\omega t+\frac{2\pi}{3}) \qquad\text{(27)}
```


```math
V_C(t)=V_A(t)-V_B(t)=? \qquad\text{(28)}
```

> GeoGebra 互動圖：https://www.geogebra.org/calculator/dtjwrz4s


***注意！1.5.1 以及 1.5.2 的解法交互比對來看，便可以了解 1.5.1 的簡便方法之原理。***

###### 1.1.5.1.1. 高中程度解法（積化和差、和差化積）

![](https://i.imgur.com/ZIIEL6C.png)


###### 1.1.5.1.2. 學過相子的大學解法（向量！）

![](https://i.imgur.com/bply7AC.png)


##### 1.1.5.2. Example 2
相位圖使得交流電的運算方便了許多，下面的例子就是一個很好的證明。若有兩個同角頻率的弦波信號：

```math
V_A(t)=2sin(\omega t+\frac{2\pi}{3}) \qquad\text{(29)}
```


```math
V_B(t)=sin(\omega t-\frac{2\pi}{3}) \qquad\text{(30)}
```


```math
V_C(t)=V_A(t)+V_B(t)=? \qquad\text{(31)}
```


Ans:
![](https://i.imgur.com/L58fVvV.png)
> GeoGebra 互動圖：https://www.geogebra.org/calculator/aaxcemuy


---

#### Problems (2021/6/1)


```math
X(t)=\sqrt{3} cos(w t-\frac{1}{3}\pi)
```


```math
Y(t)=3 sin(w t+\frac{2}{3}\pi)
```


##### Problem 1
請用積化和差/和差化積計算 $`Z(t)=X(t)+Y(t)`$。將手寫結果掃瞄或照相。

##### Problem 2
請用 phasor 計算 $`Z(t)=X(t)+Y(t)`$。將手寫結果掃瞄或照相。

##### Problem 3
使用 [GeoGebra](https://www.geogebra.org/) 繪製 $`X(t)`$、$`Y(t)`$、以及 $`Z(t)`$，在 README 附上圖與連結。

> 以上三題即本學期 [HW1 Part A](../../assignments/hw1_rc_lowpass/)（A1–A3），請於 HW1 的 README 繳交；
> 解答於 HW1 批改後公布。上面 Example 1、Example 2 為同類型的示範題，可先自行練習。


---

### 1.2. 交流電路中電流與電阻、電感、電容的相位關係

> 歷史上課影片：「交流電、電阻、電抗、阻抗 」系列 - 4 (2021/6)
> 回顧「引言一」：square wave (方波)
> 2.1 電阻的電流與電壓關係

https://youtu.be/quCMmtgoHe4

- 影片：https://www.youtube.com/watch?v=quCMmtgoHe4


#### 1.2.1 電阻
###### 1.2.1.1 以弦波計算
如圖四所示，交流電流 $`I(t)=I_psin(\omega t)`$ 流經一電阻 $`R`$，由歐姆定律知，通過電阻 a、b 兩端的電壓降為 $`V_R(t)=I(t)R`$，得到：

```math
V_R(t)=I_p R sin(\omega t) \qquad\text{(32)}
```


![](https://i.imgur.com/DZ32jj5.png)
> GeoGebra 互動圖：https://www.geogebra.org/calculator/t4ymsqeq


---

##### 1.2.1.2 以 phasor 計算

若用“相子”表示數學式(32)，得到：

```math
\vec{V_R}=\vec{I} R \qquad\text{(33)}
```

>  注意！ $`\vec{V_R}`$ 和 $`\vec{I}`$ 是線性關係！

其中

```math
\vec{V_R}=I_p R e^{j \omega t} \qquad\text{(34)}
```


```math
\vec{I}=I_p e^{j \omega t} \qquad\text{(35)}
```

圖五顯示 $`\vec{V_R}`$ 和 $`\vec{I}`$ 的相位圖，很明顯地上圖中的電流與電阻是同相位的，也就是沒有**相位差**的意思。

![](https://i.imgur.com/OJWiuHc.png)

---

#### 1.2.2 電感

---

> 歷史上課影片：「交流電、電阻、電抗、阻抗 」系列 - 5 (2021/6)
> 2.2 電感的電流與電壓關係


- 影片：https://www.youtube.com/watch?v=NYgt0UxRXHk


##### 1.2.2.1 以弦波計算

交流電路中電感的效應與電阻不同，如圖六所示，假設一交流電流 $`I(t)=I_psin(\omega t)`$ 流經一電感 $`L`$，由電感之特性我們知道通過電感 a b 兩端的電壓降 ($`V_L=V_a-V_b`$) 為：


```math
V_L(t)=L\frac{d I(t)}{dt}=L I_p \omega cos(\omega t)=I_p L\omega sin(\omega t + \frac{\pi}{2}) \qquad\text{(36)}
```

> GeoGebra 互動圖：https://www.geogebra.org/calculator/pd7yxzz7


很明顯地上式中的電流與電感的相位差是 $`\frac{\pi}{2}`$，而且是電感的相位超前電流 $`\frac{\pi}{2}`$。在圖七中表示出電流與電感的相位關係。

![](https://i.imgur.com/yHMVnVD.png)

![](https://i.imgur.com/jTBZ08u.png)

---

##### 1.2.2.2 以 phasor 計算

將數學式 (36) 的 $`V_L(t)`$和 $`I(t)`$ 可用相子表示：

```math
\vec{V_L}=I_p \omega L e^{j(\omega t+\frac{\pi}{2})}=I_p \omega L e^{j\omega t}e^{j\frac{\pi}{2}}=(j\omega L)I_p e^{j\omega t} \qquad\text{(37)}
```


```math
\vec{I}=I_p e^{j\omega t} \qquad\text{(38)}
```


若將 $`V_L(t)`$ 和 $`I(t)`$ 以 $`V=IR`$ 的方式表示如下：


```math
\vec{V_L}=\vec{I} X_L= (I_p e^{j\omega t})(j\omega L) \qquad\text{(39)}
```

>  注意！ $`\vec{V_L}`$ 和 $`\vec{I}`$ 是線性關係！

其中


```math
X_L=j\omega L \qquad\text{(40)}
```


數學式 (40) 裡面的 $`X_L`$ 就類似直流電路中的電阻，我們稱 為電感 (Inductor) 的電抗 (reactance)，或直接稱為感抗 (inductive reactance)，因此單位也是歐姆 (ohm)，習慣上以符號 $`X_L`$ 表示，而複數 $`j=e^{j\frac{\pi}{2}}`$ 表示電感所造成之電位較電流領先 $`\frac{\pi}{2}`$。

值得注意的是 $`X_L=j\omega L`$ 亦可表示為


```math
X_L=j\omega L=\omega L e^{j\frac{\pi}{2}} \qquad\text{(41)}
```


其中 $`\omega L`$ 為實數，代表電壓和電流強度的比值，類似直流電中電阻的物理量，而 $`e^{j\frac{\pi}{2}}`$ 這個 Euler 表示式，便代表電壓會超前電流 $`\frac{\pi}{2}`$。

---

##### 1.2.2.3 以函數/訊號與系統說明

將上述之說法用 “信號與系統” 的觀念來看，如圖八所示。

![](https://i.imgur.com/qbmJJxo.png)


* 可將交流電流 $`I(t)=I_psin(\omega t)`$ 作為做為一個系統的**輸入信號**，而這個**系統**為一個電感，而這個系統的**輸出信號**為**電位差** $`V_L(t)`$。
* 使用相子來表示 $`\vec{I}=I_pe^{j\omega t}`$ 以及 $`\vec{V_L}=(j\omega L)\vec{I}`$，可以發現到 $`\vec{V_L}`$ 和 $`\vec{I}`$ 是線性關係！
* 我們要觀察的輸出電壓就是經過一個函式 $`F(\omega, x)`$ 的 (線性) 轉換，這個函式的結果會因為不同的 $`\omega`$ 就有不同的輸出大小。
* 也就是說，不同頻率之信號，就有不同的對應電位差大小，且輸入為一個角頻率為 $`\omega`$ 的弦波，輸出仍是一個角頻率為 $`\omega`$ 的弦波。
* 且雖然輸出仍是弦波，但輸出之弦波會超前 (advanced) $`\frac{\pi}{2}`$。
* 不同頻率的輸入信號，就有不同的增益值 $`\omega L`$
* 當電流的頻率越高的時候 ($`\omega \uparrow`$)，則增益值越大 ($`\omega L \uparrow`$)，代表跨越此電感的電位差增加。
* 若以歐姆定律 ($`V=IR`$) 來說明這個關係，$`\omega L`$ 便類似電阻的物理量，也就是說對於角頻率為 $`\omega`$ 的弦波來說，電阻值 (以感抗值稱之較為精確) 是 $`\omega L`$。
* 頻率越高的時候 ($`\omega \uparrow`$ )，感抗值越大 ($`\omega L \uparrow`$)，代表高頻的交流電流較無法通過電感，因此造成電感兩端較大的電位差。
* 反之，頻率越低的時候 ($`\omega \downarrow`$)，感抗值越小 ($`\omega L \downarrow`$)，代表低頻的交流電流較容易通過電感。

> (思考：無限大的電位差，其實就是代表電流無法通過此電感的意思，也就是開路 (open circuit)，而電位差較小，可能代表電流可較無阻礙地的通過電感) 

---

#### 1.2.3 電容

> 歷史上課影片：「交流電、電阻、電抗、阻抗 」系列 - 6 (2021/6)
> 2.3 電容的電流和電壓關係

- 影片：https://www.youtube.com/watch?v=H-UgQWw8E2g


##### 1.2.3.1 以 phasor 計算

圖九交流電路中 $`I(t)=I_psin(\omega t)`$，而電容兩端電位差 ($`V_C=V_a-V_b`$) 和電容儲存電荷量的關係為 $`Q(t)=CV(t)`$，而電流 $`I(t)`$ 和 $`Q(t)`$ 的關係為：


```math
I(t)=\frac{d Q(t)}{dt}=\frac{d(CV(t))}{dt} \qquad\text{(42)}
```


![](https://i.imgur.com/goeOWx1.png)

將電流以相子表示 ($`\vec{I}=I_p e^{j\omega t}`$)，並對數學式(42)的所有項目對時間積分，我們得：


```math
\vec{Q}(t)=\int_{}^{}\vec{I}dt=\int_{}^{}I_p e^{j\omega t}dt=\frac{1}{j\omega}I_pe^{j\omega t}+K=C\vec{V_C} \qquad\text{(43)}
```


其中 $`K`$ 為一個與初始條件有關的常數，此初始條件又和某個時間點電容所包含的電荷量 ($`Q(t)=Im\{\vec{Q(t)}\}`$) 有關，為了分析方便，在此我們設定 $`K=0`$，也就是將 $`t=0`$ 這個時間點電容所包含的電荷量設為以下數學式(44)的值：


```math
\begin{gathered}
Q(0)=Im\{\frac{1}{j\omega}I_pe^{j\omega t}+K\} \Big|  t=0, K=0 \\
=Im\{\frac{j}{j^2\omega}I_pe^{j\omega\cdot0}+0\} \\
=Im\{\frac{-j}{\omega}I_p\cdot 1+0\}=\frac{-I_p}{\omega}
\end{gathered} \qquad\text{(44)}
```


若把 $`K`$ 設定為 $`0`$，重新改寫數學式(43)，我們可得一個很簡潔的結果如下式：


```math
\vec{V_C}=\frac{1}{j\omega C}I_pe^{j\omega t}=\frac{1}{j\omega C}\vec{I}=\frac{1}{\omega C}e^{j\frac{-\pi}{2}}\vec{I}=\vec{I} X_C \qquad\text{(45)}
```

>  注意！ $`\vec{V_C}`$ 和 $`\vec{I}`$ 是線性關係！

我們稱數學式(45)中的 $`X_C=\frac{1}{j\omega C}`$ 為電容 (Capacitor) 的電抗 (Reactance)，或直接稱容抗 (Capacitive Reactance)，習慣上以符號 $`X_C`$ 表示，而複數 $`1/j`$ 表示電容所造成之電位較電流延遲 (delay) $`\frac{\pi}{2}`$ (如圖九所示)。值得注意的是 $`X_C=\frac{1}{j\omega C}`$ 亦可表示為


```math
X_C=\frac{1}{j\omega C}=\frac{1}{\omega C}e^{j\frac{-\pi}{2}} \qquad\text{(46)}
```


其中 $`\frac{1}{\omega C}`$ 為實數，代表電壓和電流強度的比值，類似直流電中電阻的物理量，而 $`e^{j\frac{-\pi}{2}}`$ 這個 Euler 表示式，便代表電壓之相位會比電流延遲 (delay) $`\frac{\pi}{2}`$。
> GeoGebra 互動圖：https://www.geogebra.org/calculator/w79j5ned


![](https://i.imgur.com/JErZZKn.png)

---

##### 1.2.3.2 以函數/訊號與系統來說明

* 類似於電感的敘述，若以“信號與系統”的觀念來看，如圖十所示，可將交流電流 $`I_p(t)=I_p sin(\omega t)`$ 作為做為一個系統的**輸入信號**，而這個**系統**為一個電容，而這個**系統**的**輸出信號**為電位差 $`V_C(t)`$。
* 我們要觀察的輸出電壓就是經過一個函式 $`F(w,x)`$ 的轉換，這個函式的結果會因為不同的 $`\omega`$ 就有不同的輸出大小。
* 使用相子來表示 $`\vec{I}=I_pe^{j\omega t}`$ 以及 $`\vec{V_C}=(\frac{1}{j\omega C})\vec{I}`$，可以發現到 $`\vec{V_C}`$ 和 $`\vec{I}`$ 是線性關係！
* 也就是說，不同頻率之信號，就有不同的對應電位差大小。
* 且輸入為一個角頻率為  $`\omega`$ 的弦波，輸出仍是一個角頻率為 $`\omega`$ 的弦波，且雖然輸出仍是弦波，但輸出之弦波會延遲 (delay) $`\frac{\pi}{2}`$ 。

![](https://i.imgur.com/fWq6neU.png)


* 不同頻率的輸入信號，就有不同的增益值 $`\frac{1}{\omega C}`$。
* 當電流的頻率越高的時候 ( $`\omega \uparrow`$)，則增益值越小 ($`\frac{1}{\omega C} \downarrow`$ )，代表跨越此電容的電位差減少。
* 若以歐姆定律 ($`V=IR`$) 來說明這個關係，$`\frac{1}{\omega C}`$ 便類似電阻的物理量。
* 也就是說對於角頻率為 $`\omega`$ 的弦波來說，電阻值 (以容抗值稱之較為精確) 是 $`\frac{1}{\omega C}`$。
* 頻率越高的時候 ($`\omega \uparrow`$)，容抗值越小 ($`\frac{1}{\omega C} \downarrow`$)，代表高頻的交流電流較容易通過電容，因此造成電感兩端較小的電位差。
* 反之，頻率越低的時候 ($`\omega \downarrow`$)，容抗值越大 ($`\frac{1}{\omega C} \uparrow`$)，代表低頻的交流電流較難以通過電容。

---

### 1.3. 阻抗以及其應用
阻抗（electrical impedance）是電路中電阻、電感、電容對交流電的阻礙作用的統稱。阻抗衡量流動於電路的交流電所遇到的阻礙。***阻抗將電阻的概念加以延伸至交流電路領域，不僅描述電壓與電流的相對振幅，也描述其相對相位***。當通過電路的電流是直流電時，電阻與阻抗相等，電阻可以視為相位為零的阻抗。

> 歷史上課影片：「交流電、電阻、電抗、阻抗 」系列 - 7 (2021/6)
> 1. 回顧交流電為什麼用 sin cos 表示
> 2. 回顧流經過電阻、電容、以及電感之電流與電壓之關係
> 3. RC 串聯交流電路簡介

- 影片：https://www.youtube.com/watch?v=e51D-vlVCe4

#### 1.3.1. RC 串聯交流電路
##### 1.3.1.1. RC串聯阻抗

交流電路中的阻抗，是一個複數，例如圖3.1 顯示一個簡單的 RC 串聯的交流電路，其中阻抗 $`Z`$ 就等於電阻 $`R`$ 與容抗 $`X_C`$ 的和，即 $`Z=R+Z_C`$，也就是：


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

##### 1.3.1.2 於 RC 串聯電路中**電壓**與**電流**的相對**振幅**及相對**相位**

在這裡我們想要了解以下幾個關係：
1. 跨越過RC的電壓 $`V_{RC}`$
2. 流經過RC的電流 $`I`$
3. $`V_{RC}`$ 和 $`I`$ 的相對振幅及相對相位


> 歷史上課影片：「交流電、電阻、電抗、阻抗 」系列 - 8 (2021/6)

- 影片：https://www.youtube.com/watch?v=qpQneqZN-7w

類似於之前分析一個電容或是一個電感的方法，考慮一個角頻率為 $`\omega`$ 的交流電流 $`I(t)=I_psin(\omega t)`$ 流過 RC 的串流電路，並將此交流電流以相子表示：$`\vec{I}=I_p e^{j \omega t}`$，所以 $`I(t)=Im\{\vec{I}\}`$ ，重寫數學式 (3.3) 可得：


```math
\vec{V_{RC}}=\vec{I}Z=I_p e^{j \omega t}(R+\frac{1}{j\omega C}) \qquad\text{(3.4)}
```


雖然 RC 串聯電路的總共阻抗 $`Z=R+\frac{1}{j\omega C}`$ 就是代表電壓 $`V_{RC}`$ 和電流 $`I`$ 之間的比值，但由數學式 (3.4) 並沒有辦法明顯且直接觀察出此關係，因此，我們必須將 $`Z=R+\frac{1}{j\omega C}`$ 改寫成 Euler’s formula 的型式，也就是 $`Z=Ae^{j\phi}`$，其中 $`A`$ 就代表電流和電壓相對的振幅比值，而 $`\phi`$ 就是電壓和電流的相對相位差，可以用以下方法將 $`A`$ 和 $`\phi`$ 求出：


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


由數學式 (3.6) 和 (3.7) 可以發現到相對振福 $`A`$ 和相對相位 $`\phi`$ 皆是角頻率 $`\omega`$、電容值 $`C`$ 和電阻值 $`R`$ 的函數，代表說不同頻率的交流電流會造成不同的振幅和相位、不同 RC 參數也會有不同的振幅和相位。如果我們重寫數學式 (3.4)，我們可以得：


```math
\begin{gathered}
\vec{V_{RC}}=\vec{I}Z=I_p e^{j \omega t}(R+\frac{1}{j\omega C})=I_p e^{j \omega t}Ae^{j\phi}=AI_p e^{j \omega t+\phi} \\
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


#### 1.3.2. RC串聯交流電路之應用- RC低通濾波器 (RC Low-Pass Filter)

> 歷史上課影片：「交流電、電阻、電抗、阻抗 」系列 - 9 (2021/6)

- 影片：https://www.youtube.com/watch?v=J9PVsDiNuaM

https://youtu.be/J9PVsDiNuaM

##### 1.3.2.1 RC 低通濾波器性質推導
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


這個函數以相乘的形式建立起來，我們稱 ***$`H(\omega)`$ 為「轉換函數」 （transfer funtion）***。

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
5. 當 $`\omega=0`$ 時，輸入的電壓為一個直流電 $`V_{in}=V_p\cos(0\cdot t)=V_p`$，則 $`A(0)=1`$ 造成 $`V_{out}(t)=V_p`$，代表輸出此RC低通濾波器的輸出可讓原本的 $`V_{in}=V_p`$ 通過此濾波器，讓 $`V_{in}=V_{out}=V_p`$
6. 如果我們考慮一個極端例子，也就是說極高的頻率 $`\omega\to\infty`$，則 $`\lim_{\omega \to \infty}A(\omega)=0`$，代表高頻率的 $`V_{in}(t)`$無法通過此低通濾波器展現在 $`V_{out}(t)`$ 的振幅上。
7. 如果對 $`A(\omega)`$ 做較一般的討論
    * $`A(\omega)`$ 的最大值發生在 $`\omega =0`$
    * $`A(\omega)`$ 隨著 $`\omega`$ 增加而逐漸變小，代表輸入信號 $`V_{in}(t)`$ 頻率越高，則越不容易在輸出 $`V_{out}(t)`$ 觀察到相對的振幅大小
    * 頻率越低的輸入信號，越容易在輸出觀察到，因此，我們稱此RC電路為一個 “RC低通濾波器”。
> GeoGebra 互動圖：https://www.geogebra.org/calculator/sahmbp6n


##### 1.3.2.2 RC 低通濾波器之截止頻率 (Cutoff Frequency)

截止頻率的定義為轉換函數的振幅由最大值下降至 $`\frac{1}{\sqrt{2}}`$ 倍時的頻率，或輸出平均功率為最大平均功率 $`\frac{1}{2}`$ 時侯的頻率，也就是可以找到一個 $`\omega=\omega_c`$ 讓 $`A(\omega_c)=\frac{1}{\sqrt{2}}`$，由數學式 (3.14) 可以知道 ，若輸入信號為


```math
V_{in}=V_p\cos(\omega_c t) \qquad\text{(3.18)}
```


則輸出信號為

```math
V_{out}(t)=\frac{1}{\sqrt{2}}V_p\cos(\omega_c  t-\tan^{-1}(1)) \qquad\text{(3.19)}
```


## 2. Continuous/Analog World：土製 RLC 濾波器的實驗模擬（補充閱讀）

> 本節為 2021 年「訊號與系統」課程的實作題，保留供有興趣的同學參考；本學期不列入作業。

### 2.1. 實驗目的：
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


### 2.2. 實驗材料：
1. 烤肉用鋁箔紙 (可作為平行電極板，亦可作為土製電阻的兩端接點使用)
2. 多張 A4 紙張 (可作為 dielectric 電介質)
3. 口紅膠 (可做為黏著電極板和電介質用、亦可做電介質)
4. 保鮮膜 (可作為 dielectric 電介質)
5. 迴紋針 (作為電容或電阻兩端電極接點使用，所以要是全金屬的)
6. 2B 鉛筆 (可做成電阻使用)
7. 釘書機+訂書針 (可做固定土製電阻兩端的鋁箔紙電極使用)
8. 單芯或多芯電線

### 2.3. 實驗設備及工具：
1. 函數產生器
2. 示波器
3. 剝線鉗
4. 鴨嘴鉗


---

### 2.4. 基本題：RC Low-Pass Filter 製作

回答以下 Problems 1-6 (每一題都 15 Points)

請利用以上列出的實驗材料設計出如圖一所示的 RC low-pass filter，以符合以下之規格 (specification/spec)：
1. $`lim_{\omega \to 0} V_{out}(t)=5`$
2. $`lim_{\omega \to \infty} V_{out}(t)=0`$
3. 輸入一個 8,000Hz 的弦波 $`V_{in}(t)=5\cos(2\pi\cdot 8000t)`$，輸出為 $`V_{out}(t)=\frac{5}{\sqrt{2}}\cos(2\pi\cdot 8000t-\frac{\pi}{4})`$

![](https://i.imgur.com/O7CPBVw.png)

#### 2.4.1. Problem 1 
請設計一組 $`R`$ 以及 $`C`$ 的值，符合以上的 spec，建議值 $`R\in[1\times 10^4, 2\times 10^4] \Omega`$，$`C \in [10^{-9}, 10^{-8}] \text{F}`$。

Solution: 
因為要讓 $`f=8000Hz`$ 的弦波通過低通濾波器之後的振幅是原本的 $`1/\sqrt2`$ 倍，所以要讓 $`1/\sqrt{1+(2\pi 8000RC)^2}=1/\sqrt{2}`$，也就是要讓：


```math
RC=\frac{1}{2\pi 8000}\approx 1.989436\times 10^{-5} \qquad\text{(1.1)}
```


所以可以做以下 $`R`$ 以及 $`C`$ 的選擇，只要符合數學式(1.1)就好：
1. $`R\approx 1.989436\times 10^{4}\Omega=19.8936K\Omega`$ 以及 $`C\approx 1.0\times 10^{-9} \text{Farad}=1.0 \text{nF(Nanofarads)}`$
2. $`R\approx 1.0\times 10^{4}\Omega=10K\Omega`$ 以及 $`C\approx 1.989436\times 10^{-9} \text{Farad}=1.0 \text{nF(Nanofarads)}`$

#### 2.4.2. Problem 2
使用 Geogebra 繪製 $`V_{in}(t)`$ 以及 $`V_{out}(t)`$，將繪製好的 GeoGebra 圖形連結製作成 QR Code，放在繳交作業的 pdf 檔裡。
> GeoGebra 互動圖：https://www.geogebra.org/calculator/qevjwhbp


#### 2.4.3. Problem 3
若根據 Problem 1 設計的 $`R`$ 以及 $`C`$ 參數來製作實體的電阻，電阻使用鉛筆來製作，電容使用鋁箔紙以及紙來製作，請手繪制電阻以及電容的設計圖，說明如何製作？

Solution:
1. 電容：製作電容時，將兩片鋁鉑紙中間放紙張後以迴紋針固定，透過改變紙張大小及厚度來達成目標電容值。
![](https://i.imgur.com/edCtz4w.jpg)
2. 電阻：用 2B 鉛筆筆跡製作電阻，改變筆跡深淺和筆跡寬度以調整電阻值，將單芯線放置於筆跡兩端再用膠帶固定，單芯線的距離越大電阻越大。
![](https://i.imgur.com/loqOyD1.png)


#### 2.4.4. Problem 4
續 Problem 3，根據數學式 (1) 以及 (2) 來設計，則數學式 (1) 裡面的 $`L`$ 和 $`A`$ 是多少？數學式 (2) 的 $`A`$ 和 $`d`$ 是多少？ 請注意 $`\rho`$ 可以找“碳或石墨”的導電度/電阻率做為數據，而 $`\kappa`$ 使用“紙”的 dielectric constant。本題需要計算過程，沒有計算過程不計分。另外，$`\rho`$ 以及 $`\kappa`$ 的直在哪裡找到的，要附上參考文獻（網址或書都可以），沒有附上參考文獻，本題不計分。

Solution:
1. 根據網路上找到的論文(https://iopscience.iop.org/article/10.1088/1742-6596/1144/1/012165/pdf)，鉛筆的電阻率大概是：

```math
\rho=99.94 m\Omega\cdot cm
```

也就是

```math
\rho=99.94\times 100 m\Omega\cdot m\approx 10\Omega\cdot m
```

一張A4只的厚度大概 $`0.104mm=1.04\times 10^{-4}m\approx 10^{-4}m`$ (https://zhidao.baidu.com/question/1372229580220774859.html)，我們假設用2B鉛筆塗在一張A4的紙上，圖成黑色的部份是厚度為 $`H`$，寬度為 $`W`$，長度為 $`L`$，金黃色的部分是迴紋針可以導電，也就是電阻的兩端，所以由導電的迴紋針看進去這個電阻，截面積 $`A=HW`$，長度是 $`L`$。
![](https://i.imgur.com/tRZ9pt6.png)
電阻值就可以估計為：

```math
R=\frac{\rho L}{HW}=19.8936K\Omega=1.98936\times 10^4\Omega
```

把鉛筆畫在紙上可以假設是A4紙厚度的 $`\frac{1}{2}`$，也就是 $`H=5\times 10^{-5}`$ 寬度是$`1cm=10^{-2}m`$，則長度可以是：

```math
L=\frac{RHW}{\rho}=\frac{(1.98936\times 10^4)(5\times 10^{-5})(10^{-2})}{10}=9.9468\times 10^{-3}m\approx 1cm
```

2.因為鋁箔紙中間夾的是A4紙，所以我們要到紙的 dielectric constant $`\kappa=1.4`$ (https://en.wikipedia.org/wiki/Relative_permittivity)，而A4紙的厚度是 $`d=10^{-4}m`$，在 $`C\approx 1.0\times 10^{-9}F`$ 的情況下，兩張鋁箔紙重疊的面積是：

```math
A=\frac{Cd}{\kappa \epsilon_0}=\frac{10^{-9}10^{-4}}{1.4\times 8.85418782\times 10^{-12}}=\frac{10^{-13}}{12.395862948\times 10^{-12}}=8.067207617\times 10^{-3}m^2
```

若鋁箔紙是正方形，則邊長為 $`\sqrt{A}=0.08981763533 m\approx 9cm`$

#### 2.4.5. Problem 5
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


#### 2.4.6. Problem 6
使用 Geogebra 繪製 Problem 5 的 $`V_{in}(t)`$ 以及 $`V_{out}(t)`$，將繪製好的 GeoGebra 圖形連結製作成 QR Code，放在繳交作業的 pdf 檔裡。
> GeoGebra 互動圖：https://www.geogebra.org/calculator/wxpw2rpt


從上圖可以發現到，輸出的 $`V_{out}(t)`$ 比較於 $`V_{in}(t)`$ 沒有快速上下跳動信號，因為那些快速上下跳動的信號就是頻率比較高的成分， $`V_{in}(t)`$ 的高頻成分 ($`k`$ 比較大的部分)，振幅會被衰減的比較嚴重。

---

### 2.5. 進階題：RLC Filter 製作

回答以下 Problems 7-11 (每一題都 15 Points)

#### 2.5.1. Problem 7
如圖二，請求取圖中的 $`A(\omega)`$ 以及 $`\phi(\omega)`$
![](https://i.imgur.com/FIkaLAh.png)

圖2：電阻 (R)、電容(C)、電感(L)串並聯電路

Solution:

![](https://i.imgur.com/yVL9QLn.png)


#### 2.5.2. Problem 8
續 Problem 7，若 $`R=1\Omega`$、$`L=\frac{1}{2\pi\cdot 8000} \text{Henry}`$、以及 $`C=\frac{1}{2\pi\cdot 8000} \text{Farad}`$，請用 Geogebra 繪製 $`A(f)`$ 以及 $`\phi(f)`$，小心！橫軸是用 $`f`$ 不是用 $`\omega`$。繪製圖形的時候要調整x/y兩軸的範圍，方便觀察，建議 $`f \in [0, 24000]`$、$`A(f) \in [0, 1]`$、以及 $`\phi \in [-\frac{\pi}{2}, \frac{\pi}{2}]`$。將繪製好的 GeoGebra 圖形連結製作成 QR Code，放在繳交作業的 pdf 檔裡。

Solution for $`A(f)`$:
> GeoGebra 互動圖：https://www.geogebra.org/calculator/ynbwvh8y


Solution for $`\phi(f)`$
> GeoGebra 互動圖：https://www.geogebra.org/calculator/xvbucuww


#### 2.5.3. Problem 9
續 Problem 8，請找到 $`A(f)`$ 這個函數的水平漸近線、以及垂直漸近線。

Solution: 
$`A(f)`$ 沒有垂直漸近線，只有水平漸近線 $`H(f) = 1`$

#### 2.5.4. Problem 10
續 Problem 8，若圖2中的 $`V_x(t)=V_{in}(t)`$ (數學式(3)、(4)的定義)，則 $`V_y(t)`$ 為何？ 請將數學式寫出來。

Solution:
![](https://i.imgur.com/3S4MZ5H.png)


#### 2.5.5. Problem 11
續 Problem 10，使用 Geogebra 繪製 Problem 10 的 $`V_{x}(t)`$ 以及 $`V_{y}(t)`$，將繪製好的 GeoGebra 圖形連結製作成 QR Code，放在繳交作業的 pdf 檔裡。

Solution:
> GeoGebra 互動圖：https://www.geogebra.org/calculator/nbrkmkmj


## 3. Simulation 'Continuous' by 'Discrete'
### 3.1. Simulation of RC Low-Pass Filter by Discrete Signal Processing

以下投影片推導由 x(t) = RC·dy/dt + y(t) 離散化得到
y[n] = (RC/(RC+τ))·y[n−1] + (τ/(RC+τ))·x[n]，即 [HW1](../../assignments/hw1_rc_lowpass/) 式 (8)。

![](https://i.imgur.com/QTorNFt.png)

![](https://i.imgur.com/2HOJ05Y.png)

![](https://i.imgur.com/5OpsCf5.png)

![](https://i.imgur.com/gUNzyTT.png)

![](https://i.imgur.com/LtfW2Z1.png)

---

[← day01_intro_to_dsp.md](day01_intro_to_dsp.md) ｜ [講義目錄](README.md) ｜ [day03_speech_signal_representation.md →](day03_speech_signal_representation.md)
