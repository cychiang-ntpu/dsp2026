# Day-2-2：交流電路中 R、L、C 的電壓電流相位關係

[← day02_1_complex_phasor.md](day02_1_complex_phasor.md) ｜ [Day-2 總覽](day02_continuous_to_discrete.md) ｜ [day02_3_impedance_rc_lowpass.md →](day02_3_impedance_rc_lowpass.md)

## 1.2. 交流電路中電流與電阻、電感、電容的相位關係

> 歷史上課影片：「交流電、電阻、電抗、阻抗 」系列 - 4 (2021/6)
> 回顧「引言一」：square wave (方波)
> 2.1 電阻的電流與電壓關係

https://youtu.be/quCMmtgoHe4

- 影片：https://www.youtube.com/watch?v=quCMmtgoHe4


### 1.2.1 電阻
##### 1.2.1.1 以弦波計算
如圖四所示，交流電流 $`I(t)=I_psin(\omega t)`$ 流經一電阻 $`R`$，由歐姆定律知，通過電阻 a、b 兩端的電壓降為 $`V_R(t)=I(t)R`$，得到：

```math
V_R(t)=I_p R sin(\omega t) \qquad\text{(32)}
```


![](https://i.imgur.com/DZ32jj5.png)
> GeoGebra 互動圖：https://www.geogebra.org/calculator/t4ymsqeq


---

#### 1.2.1.2 以 phasor 計算

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

圖五顯示 $`\vec{V_R}`$ 和 $`\vec{I}`$ 的相位圖，很明顯地上圖中的電流與電壓是同相位的，也就是沒有**相位差**的意思。

![](https://i.imgur.com/OJWiuHc.png)

---

### 1.2.2 電感

---

> 歷史上課影片：「交流電、電阻、電抗、阻抗 」系列 - 5 (2021/6)
> 2.2 電感的電流與電壓關係


- 影片：https://www.youtube.com/watch?v=NYgt0UxRXHk


#### 1.2.2.1 以弦波計算

交流電路中電感的效應與電阻不同，如圖六所示，假設一交流電流 $`I(t)=I_psin(\omega t)`$ 流經一電感 $`L`$，由電感之特性我們知道通過電感 a b 兩端的電壓降 ($`V_L=V_a-V_b`$) 為：


```math
V_L(t)=L\frac{d I(t)}{dt}=L I_p \omega cos(\omega t)=I_p L\omega sin(\omega t + \frac{\pi}{2}) \qquad\text{(36)}
```

> GeoGebra 互動圖：https://www.geogebra.org/calculator/pd7yxzz7


很明顯地上式中的電流與電感電壓的相位差是 $`\frac{\pi}{2}`$，而且是電感電壓的相位超前電流 $`\frac{\pi}{2}`$。在圖七中表示出電流與電感電壓的相位關係。

![](https://i.imgur.com/yHMVnVD.png)

![](https://i.imgur.com/jTBZ08u.png)

---

#### 1.2.2.2 以 phasor 計算

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


數學式 (40) 裡面的 $`X_L`$ 就類似直流電路中的電阻，我們稱之為電感 (Inductor) 的電抗 (reactance)，或直接稱為感抗 (inductive reactance)，因此單位也是歐姆 (ohm)，習慣上以符號 $`X_L`$ 表示，而複數 $`j=e^{j\frac{\pi}{2}}`$ 表示電感所造成之電位較電流領先 $`\frac{\pi}{2}`$。

值得注意的是 $`X_L=j\omega L`$ 亦可表示為


```math
X_L=j\omega L=\omega L e^{j\frac{\pi}{2}} \qquad\text{(41)}
```


其中 $`\omega L`$ 為實數，代表電壓和電流強度的比值，類似直流電中電阻的物理量，而 $`e^{j\frac{\pi}{2}}`$ 這個 Euler 表示式，便代表電壓會超前電流 $`\frac{\pi}{2}`$。

---

#### 1.2.2.3 以函數/訊號與系統說明

將上述之說法用 “信號與系統” 的觀念來看，如圖八所示。

![](https://i.imgur.com/qbmJJxo.png)


* 可將交流電流 $`I(t)=I_psin(\omega t)`$ 作為一個系統的**輸入信號**，而這個**系統**為一個電感，而這個系統的**輸出信號**為**電位差** $`V_L(t)`$。
* 使用相子來表示 $`\vec{I}=I_pe^{j\omega t}`$ 以及 $`\vec{V_L}=(j\omega L)\vec{I}`$，可以發現到 $`\vec{V_L}`$ 和 $`\vec{I}`$ 是線性關係！
* 我們要觀察的輸出電壓就是經過一個函式 $`F(\omega, x)`$ 的 (線性) 轉換，這個函式的結果會因為不同的 $`\omega`$ 就有不同的輸出大小。
* 也就是說，不同頻率之信號，就有不同的對應電位差大小，且輸入為一個角頻率為 $`\omega`$ 的弦波，輸出仍是一個角頻率為 $`\omega`$ 的弦波。
* 且雖然輸出仍是弦波，但輸出之弦波會超前 (advanced) $`\frac{\pi}{2}`$。
* 不同頻率的輸入信號，就有不同的增益值 $`\omega L`$
* 當電流的頻率越高的時候 ($`\omega \uparrow`$)，則增益值越大 ($`\omega L \uparrow`$)，代表跨越此電感的電位差增加。
* 若以歐姆定律 ($`V=IR`$) 來說明這個關係，$`\omega L`$ 便類似電阻的物理量，也就是說對於角頻率為 $`\omega`$ 的弦波來說，電阻值 (以感抗值稱之較為精確) 是 $`\omega L`$。
* 頻率越高的時候 ($`\omega \uparrow`$ )，感抗值越大 ($`\omega L \uparrow`$)，代表高頻的交流電流較無法通過電感，因此造成電感兩端較大的電位差。
* 反之，頻率越低的時候 ($`\omega \downarrow`$)，感抗值越小 ($`\omega L \downarrow`$)，代表低頻的交流電流較容易通過電感。

> (思考：無限大的電位差，其實就是代表電流無法通過此電感的意思，也就是開路 (open circuit)，而電位差較小，可能代表電流可較無阻礙地通過電感) 

---

### 1.2.3 電容

> 歷史上課影片：「交流電、電阻、電抗、阻抗 」系列 - 6 (2021/6)
> 2.3 電容的電流和電壓關係

- 影片：https://www.youtube.com/watch?v=H-UgQWw8E2g


#### 1.2.3.1 以 phasor 計算

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

#### 1.2.3.2 以函數/訊號與系統來說明

* 類似於電感的敘述，若以“信號與系統”的觀念來看，如圖十所示，可將交流電流 $`I_p(t)=I_p sin(\omega t)`$ 作為一個系統的**輸入信號**，而這個**系統**為一個電容，而這個**系統**的**輸出信號**為電位差 $`V_C(t)`$。
* 我們要觀察的輸出電壓就是經過一個函式 $`F(w,x)`$ 的轉換，這個函式的結果會因為不同的 $`\omega`$ 就有不同的輸出大小。
* 使用相子來表示 $`\vec{I}=I_pe^{j\omega t}`$ 以及 $`\vec{V_C}=(\frac{1}{j\omega C})\vec{I}`$，可以發現到 $`\vec{V_C}`$ 和 $`\vec{I}`$ 是線性關係！
* 也就是說，不同頻率之信號，就有不同的對應電位差大小。
* 且輸入為一個角頻率為  $`\omega`$ 的弦波，輸出仍是一個角頻率為 $`\omega`$ 的弦波，且雖然輸出仍是弦波，但輸出之弦波會延遲 (delay) $`\frac{\pi}{2}`$ 。

![](https://i.imgur.com/fWq6neU.png)


* 不同頻率的輸入信號，就有不同的增益值 $`\frac{1}{\omega C}`$。
* 當電流的頻率越高的時候 ( $`\omega \uparrow`$)，則增益值越小 ($`\frac{1}{\omega C} \downarrow`$ )，代表跨越此電容的電位差減少。
* 若以歐姆定律 ($`V=IR`$) 來說明這個關係，$`\frac{1}{\omega C}`$ 便類似電阻的物理量。
* 也就是說對於角頻率為 $`\omega`$ 的弦波來說，電阻值 (以容抗值稱之較為精確) 是 $`\frac{1}{\omega C}`$。
* 頻率越高的時候 ($`\omega \uparrow`$)，容抗值越小 ($`\frac{1}{\omega C} \downarrow`$)，代表高頻的交流電流較容易通過電容，因此造成電容兩端較小的電位差。
* 反之，頻率越低的時候 ($`\omega \downarrow`$)，容抗值越大 ($`\frac{1}{\omega C} \uparrow`$)，代表低頻的交流電流較難以通過電容。

---

[← day02_1_complex_phasor.md](day02_1_complex_phasor.md) ｜ [Day-2 總覽](day02_continuous_to_discrete.md) ｜ [day02_3_impedance_rc_lowpass.md →](day02_3_impedance_rc_lowpass.md)
