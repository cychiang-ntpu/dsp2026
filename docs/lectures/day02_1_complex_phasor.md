# Day-2-1：複數與相子（phasor）

[← Day-2 總覽](day02_continuous_to_discrete.md) ｜ [day02_2_rlc_phase.md →](day02_2_rlc_phase.md)

## 1.1. 複數 (complex number) 和相子 (phasor)

> 歷史上課影片：「交流電、電阻、電抗、阻抗 」系列 - 1 (2021/6)
> 引言一
> 引言二
> 1. 複數 (complex number) 和相子 (phasor)
> 1.1. 以直角座標表示的複數
> 1.2. 以極座標表示的複數
> 1.3. 尤拉表示式 (Euler’s formula)

- 影片：https://www.youtube.com/watch?v=xm51ln3v8-Y

### 1.1.1. 以直角座標表示的複數
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


可以特別注意，在圖一裡面，我們將這個複數使用一個向量 (vector) 來代表它在空間中的位置，也就是說，我們把複數當作是一個向量來描述，這個複數是在複數平面 (complex plane, 或稱 z-plane) 上，這個複數平面為一個 2-dimensional (sub)space，這 complex plane 的 basis vectors 就是實數軸 (real axis) 以及虛數軸 (imaginary axis) 所指的方向向量。$`x`$ 就是複數 $`z`$ 投影在 real axis 的投影量，$`y`$ 就是複數 $`z`$ 投影在 imaginary axis 的投影量。real axis 和 imaginary axis 兩個互相正交，就是因為互相正交，才有有趣的特性。

---

### 1.1.2. 以極座標表示的複數
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

### 1.1.3. 尤拉表示式 (Euler’s formula)
我們亦可用 「尤拉表示式」 (Euler’s formula) 來表示複數，這種表示方法非常方便，並廣泛應用於訊號處理的領域裡面，Euler’s formula 為：

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

### 1.1.4. 相子 (Phasor)
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


我們也可以用以下數學式來表示一個餘弦信號：

```math
C(t)=V_0cos(\omega t+\phi)=Re\{V_0e^{j(\omega t+\phi)}\} \qquad\text{(16)}
```


因為數學式(14)裡面的複數 $`V_0e^{j(\omega t+\phi)}`$ 就是在 z-plane 這個 space 裡面，$`x=Re\{V_0e^{j(\omega t+\phi)}\}`$ 就是在 real axis 上的投影量，$`y=Im\{V_0e^{j(\omega t+\phi)}\}`$ 就是在 imaginary axis 上的投影量。

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


使用 phasor 表示的數學式(25) $`\vec{V}e^{j(\frac{\pi}{2})}`$ 就是原本數學式(23) $`\vec{V}`$ 的相位(phase)偏移(shift)版本，或者說 $`Im\{\vec{V}e^{j(\frac{\pi}{2})}\}`$ 信號是 $`Im\{\vec{V}\}`$ 信號的超前(advanced)版本，或者說 $`C(t)`$ 相對於 $`S(t)`$ 超前了 $`\frac{\pi}{2}`$。

---

#### 重點！
**所以使用 phasor 可以將 $`cos`$ 訊號 ($`C(t)`$) 和 $`sin`$ 訊號 ($`S(t)`$) 使用一樣的表示方法 (如數學式(23)以及(25))，方便表示以及計算。**

---

### 1.1.5 相子的應用

**同樣頻率**的弦波相加減

> 歷史上課影片：「交流電、電阻、電抗、阻抗 」系列 - 3 (2021/6)
> 1.5. 相子的應用

- 影片：https://www.youtube.com/watch?v=m3EyOTck12Y

##### 1.1.5.1. Example 1
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


***注意！1.1.5.1.1 以及 1.1.5.1.2 的解法交互比對來看，便可以了解 1.1.5.1.2 的簡便方法之原理。***

##### 1.1.5.1.1. 高中程度解法（積化和差、和差化積）

![](https://i.imgur.com/ZIIEL6C.png)


##### 1.1.5.1.2. 學過相子的大學解法（向量！）

![](https://i.imgur.com/bply7AC.png)


#### 1.1.5.2. Example 2
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

### Problems (2021/6/1)


```math
X(t)=\sqrt{3} cos(w t-\frac{1}{3}\pi)
```


```math
Y(t)=3 sin(w t+\frac{2}{3}\pi)
```


#### Problem 1
請用積化和差/和差化積計算 $`Z(t)=X(t)+Y(t)`$。將手寫結果掃瞄或照相。

#### Problem 2
請用 phasor 計算 $`Z(t)=X(t)+Y(t)`$。將手寫結果掃瞄或照相。

#### Problem 3
使用 [GeoGebra](https://www.geogebra.org/) 繪製 $`X(t)`$、$`Y(t)`$、以及 $`Z(t)`$，在 README 附上圖與連結。

> 以上三題即本學期 [HW1 Part A](../../assignments/hw1_rc_lowpass/)（A1–A3），請於 HW1 的 README 繳交；
> 解答於 HW1 批改後公布。上面 Example 1、Example 2 為同類型的示範題，可先自行練習。

---

[← Day-2 總覽](day02_continuous_to_discrete.md) ｜ [day02_2_rlc_phase.md →](day02_2_rlc_phase.md)
