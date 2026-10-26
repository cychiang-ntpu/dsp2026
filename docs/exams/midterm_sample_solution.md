# DSP 2026 紙筆期中考題型範例：參考解答

> 對應 [midterm_sample.md](midterm_sample.md)。數值除可精確寫出者（如 0.4536）外，皆四捨五入到小數第 3 位；角度一律為 radian。

---

## 第 1 題　脈衝分解與卷積（8 分）

$`a=0.5`$，差分方程為 $`y[n]=0.5\,y[n-1]+0.5\,x[n]`$；輸入 $`x[0]=1,\ x[1]=2,\ x[2]=-1`$，其餘為 0。

**1.** initial rest，$`y[-1]=0`$：

```math
\begin{aligned}
y[0] &= 0.5\cdot 0 + 0.5\cdot 1 = 0.5\\
y[1] &= 0.5\cdot 0.5 + 0.5\cdot 2 = 1.25\\
y[2] &= 0.5\cdot 1.25 + 0.5\cdot(-1) = 0.125
\end{aligned}
```

**2.** 令 $`x[n]=\delta[n]`$ 遞迴可得 $`h[0]=1-a,\ h[1]=a(1-a),\ \dots`$，即

```math
h[n] = (1-a)\,a^n\,u[n] = 0.5^{\,n+1}u[n], \qquad h[0]=0.5,\ h[1]=0.25,\ h[2]=0.125
```

$`x[n]=\delta[n]+2\delta[n-1]-\delta[n-2]`$，由 LTI 性質 $`y[n]=h[n]+2h[n-1]-h[n-2]`$：

```math
\begin{aligned}
y[0] &= h[0] = 0.5\\
y[1] &= h[1]+2h[0] = 0.25+1 = 1.25\\
y[2] &= h[2]+2h[1]-h[0] = 0.125+0.5-0.5 = 0.125
\end{aligned}
```

與第 1 小題相同。

**3.** $`n\ge 3`$ 時 $`x[n]=0`$，$`y[n]=0.5\,y[n-1]`$，因此

```math
y[n] = y[2]\cdot 0.5^{\,n-2} = 0.125\cdot 0.5^{\,n-2} = 0.5^{\,n+1}, \qquad n\ge 2
```

（也可由 $`h[n]+2h[n-1]-h[n-2]=0.5^{n+1}(1+4-4)`$ 直接得到。）

## 第 2 題　取樣與離散頻率（8 分）

$`x[n]=\cos(2\pi f_0 n/f_s)=\cos(\omega n)`$，$`\omega=2\pi f_0/f_s`$。$`x[n]`$ 為週期序列 $`\iff`$ $`\omega N=2\pi k`$ 有整數解，即 $`\omega/2\pi=k/N`$ 為有理數。

**1.** $`\omega=2\pi\cdot 3000/8000=3\pi/4`$。$`\omega/2\pi=3/8`$，週期序列，最小週期 $`N=8`$。

**2.** $`\omega=2\pi\cdot 3000/4000=3\pi/2`$。$`\omega/2\pi=3/4`$，週期序列，最小週期 $`N=4`$。化到 $`(-\pi,\pi]`$：$`3\pi/2-2\pi=-\pi/2`$。

**3.** $`\cos(-\pi n/2)=\cos(\pi n/2)`$，與 $`1000`$ Hz 弦波以 4000 Hz 取樣所得完全相同（$`2\pi\cdot1000/4000=\pi/2`$）。3000 Hz 超過 Nyquist 頻率 $`f_s/2=2000`$ Hz，發生混疊：數位濾波器看到的是 1000 Hz，所以 HW1 在 $`f_s=4000`$ 時 3000 Hz 的數位結果（$`\lvert H\rvert\approx0.329`$）與連續時間 RC 電路（$`\lvert H\rvert\approx0.132`$）差很多，連相位的正負號都不同；比較時必須先確認 $`f_0<f_s/2`$。

## 第 3 題　以 z 轉換分析 RC 濾波器（17 分）

**1.** 由時間平移性質 $`y[n-1]\leftrightarrow z^{-1}Y(z)`$：

```math
Y(z)=a z^{-1}Y(z)+(1-a)X(z)\ \Rightarrow\
H(z)=\frac{1-a}{1-a z^{-1}}=\frac{(1-a)\,z}{z-a},\qquad |z|>a
```

**2.** 零點 $`z=0`$，極點 $`z=a=0.761`$（實軸上、單位圓內）。

```
          Im
           |
     .-----+-----.        o : zero at 0
    /      |      \       x : pole at 0.761
   |       o    x  |---- Re
    \      |      /
     '-----+-----'
```

有一個不在原點的極點，$`h[n]`$ 無限長，是 **IIR**。

**3.** 由 $`a^n u[n]\leftrightarrow \dfrac{1}{1-az^{-1}}`$（$`|z|>|a|`$）：$`h[n]=(1-a)\,a^n u[n]`$。取 $`a=0.5`$ 即為第 1 題的 $`0.5^{n+1}u[n]`$，一致。

**4.** $`z=e^{j\omega}`$：

```math
H(e^{j\omega})=\frac{1-a}{1-a\cos\omega+ja\sin\omega},\qquad
\lvert H\rvert=\frac{1-a}{\sqrt{1-2a\cos\omega+a^2}},\qquad
\angle H=-\tan^{-1}\!\frac{a\sin\omega}{1-a\cos\omega}
```

向量觀點：$`H(e^{j\omega})=(1-a)\dfrac{e^{j\omega}-0}{e^{j\omega}-a}`$，零點向量長度恆為 1，所以

```math
\lvert H\rvert=\frac{1-a}{\lvert e^{j\omega}-a\rvert},\qquad
\angle H=\omega-\angle(e^{j\omega}-a)
```

- $`\omega=0`$：$`e^{j0}=1`$ 離極點最近，距離 $`1-a`$，$`\lvert H\rvert=1`$。
- $`\omega=\pi`$：$`e^{j\pi}=-1`$ 離極點最遠，距離 $`1+a`$，$`\lvert H\rvert=\dfrac{1-a}{1+a}`$（$`a=0.761`$ 時約 0.136）。

$`\omega`$ 從 0 增加到 $`\pi`$，$`e^{j\omega}`$ 離極點越來越遠，增益單調遞減，所以是低通。

**5.** $`\omega=2\pi\cdot400/8000=\pi/10`$，$`\cos\omega=0.951`$、$`\sin\omega=0.309`$：

```math
\lvert H\rvert=\frac{0.239}{\sqrt{1-2(0.761)(0.951)+0.579}}=\frac{0.239}{0.363}\approx 0.659,\qquad
\angle H=-\tan^{-1}\frac{0.235}{0.276}\approx-0.705
```

連續時間在截止頻率為 $`0.707`$、$`-\pi/4\approx-0.785`$。數位版本增益略小、相位略少，原因是式 (8) 的後向差分只是微分的近似，等效截止頻率約 350 Hz，比 400 Hz 低；取樣率提高後（例如 16 kHz：0.681、$`-0.746`$）會更接近連續時間結果。

## 第 4 題　弦波輸入的輸出（8 分）

**1.** $`e^{j\omega n}\to H(e^{j\omega})e^{j\omega n}`$；$`h[n]`$ 為實數，$`H(e^{-j\omega})=H^*(e^{j\omega})`$，因此 $`\cos(\omega n)\to\lvert H\rvert\cos(\omega n+\angle H)`$。$`\omega_1=2\pi\cdot100/8000=\pi/40`$，$`\omega_2=3\pi/4`$：

```math
y[n]=1.922\cos\!\left(\frac{\pi}{40}n-0.243\right)+0.147\cos\!\left(\frac{3\pi}{4}n-0.337\right)
```

100 Hz 幾乎無損通過；3000 Hz 被衰減到約 1/7。

**2.** $`\omega=3\pi/4`$：$`\sin\omega=0.707`$、$`\cos\omega=-0.707`$。

```math
\angle H=-\tan^{-1}\frac{0.761\times0.707}{1-0.761\times(-0.707)}=-\tan^{-1}\frac{0.538}{1.538}=-\tan^{-1}(0.350)\approx-0.337
```

## 第 5 題　moving average FIR 與 RC 低通比較（17 分）

**1.** $`h[n]=\tfrac14(\delta[n]+\delta[n-1]+\delta[n-2]+\delta[n-3])`$。

```math
H(z)=\frac14\sum_{k=0}^{3}z^{-k}=\frac14\cdot\frac{1-z^{-4}}{1-z^{-1}}\quad(\text{等比級數和})
```

**2.** $`1-z^{-4}=0`$ 的根為 $`z=1,\ j,\ -1,\ -j`$；分母的極點 $`z=1`$ 與零點 $`z=1`$ **抵消**。整理成正冪：

```math
H(z)=\frac{z^3+z^2+z+1}{4z^3}
```

零點在 $`j,\,-1,\,-j`$（單位圓上），三個極點都在原點。原點的極點只代表延遲，$`h[n]`$ 只有 4 個非零值，所以仍是 **FIR**。分式只是寫法，判斷 FIR/IIR 要看抵消後是否有不在原點的極點。

**3.**

```math
H(e^{j\omega})=\frac14\cdot\frac{1-e^{-j4\omega}}{1-e^{-j\omega}}
=\frac14\cdot\frac{e^{-j2\omega}(e^{j2\omega}-e^{-j2\omega})}{e^{-j\omega/2}(e^{j\omega/2}-e^{-j\omega/2})}
=e^{-j1.5\omega}\,\frac{\sin(2\omega)}{4\sin(\omega/2)}
```

| $`\omega`$ | moving average $`\lvert H\rvert`$ | RC（$`a=0.761`$）$`\lvert H\rvert`$ |
|---|---|---|
| 0 | 1（取極限，或 $`\tfrac14\cdot4`$） | 1 |
| $`\pi/4`$ | $`\dfrac{1}{4\sin(\pi/8)}\approx0.653`$ | 0.337 |
| $`\pi/2`$ | 0（$`z=j`$ 為零點） | 0.190 |

moving average 在 $`\pi/2`$ 與 $`\pi`$ 完全歸零（零點落在單位圓上），但 $`\pi/2`$ 與 $`\pi`$ 之間會再升起（旁瓣）；RC 低通單調下降、不會歸零。在 $`\pi/4`$ 處 moving average 衰減得比 RC 少。

**4.**

- Block diagram：$`x[n]`$ 經三個串接的 $`z^{-1}`$ 得到 $`x[n-1],x[n-2],x[n-3]`$，四路相加後乘 $`1/4`$ 得 $`y[n]`$（或四路各乘 $`1/4`$ 再相加）。
- 線性相位：moving average $`h[n]`$ 對 $`n=1.5`$ 對稱，$`\angle H=-1.5\omega`$（在 $`\sin(2\omega)/\sin(\omega/2)`$ 變號處另有 $`\pi`$ 的跳躍），是線性相位。RC 的 $`h[n]=(1-a)a^nu[n]`$ 不對稱，相位 $`-\tan^{-1}\frac{a\sin\omega}{1-a\cos\omega}`$ 不是 $`\omega`$ 的線性函數。
- 乘法次數：moving average 先加後乘只需 1 次（各乘 $`1/4`$ 則 4 次）；RC 需 2 次（$`a\cdot y[n-1]`$、$`(1-a)\cdot x[n]`$）。

## 第 6 題　RC 低通串接一階差分（12 分）

**1.** 一階差分 $`H_2(z)=1-z^{-1}`$，串接即相乘：

```math
H(z)=\frac{(1-a)(1-z^{-1})}{1-a z^{-1}}=\frac{(1-a)(z-1)}{z-a}
```

**2.** 零點 $`z=1`$，極點 $`z=a`$。極點不在原點，是 **IIR**。

**3.** $`H(z)=(1-a)\left[\dfrac{1}{1-az^{-1}}-\dfrac{z^{-1}}{1-az^{-1}}\right]`$，由時間平移性質：

```math
h[n]=(1-a)\left[a^n u[n]-a^{n-1}u[n-1]\right]
```

- $`h[0]=1-a`$
- $`n\ge1`$：$`h[n]=(1-a)(a^n-a^{n-1})=-(1-a)^2a^{n-1}`$

（驗證：$`\sum_n h[n]=(1-a)-(1-a)^2\cdot\frac{1}{1-a}=0=H(1)`$。）

**4.** $`\omega=0`$：$`z=1`$ 是零點，增益 0。$`\omega=\pi`$：$`\dfrac{(1-a)\cdot2}{1+a}=\dfrac{0.478}{1.761}\approx0.271`$。低頻被擋、高頻通過，是**高通**濾波器。

## 第 7 題　C 程式（12 分）

**1.**

```c
void rc_hp(const double *x, double *w, int N, double a)
{
    double y_prev = 0.0;                 /* initial rest: y[-1] = 0 */
    for (int n = 0; n < N; n++) {
        double y = a * y_prev + (1.0 - a) * x[n];
        w[n] = y - y_prev;               /* w[n] = y[n] - y[n-1] */
        y_prev = y;
    }
}
```

評分重點：用變數保存 $`y[n-1]`$ 並初始化為 0、不存取 `x[-1]`／`y[-1]`、型別為 `double`。

**2.**

- `double tau = 1 / fs;` 是整數除法，結果為 0，使 `a = 1`、`1 - a = 0`：輸入完全不起作用，`y[n]` 只是一直複製前一個值。改成 `double tau = 1.0 / fs;`。
- 迴圈在 `n = 0` 時讀取 `y[-1]`，超出陣列範圍（未定義行為）。改成先算 `y[0] = (1 - a) * x[0];` 再從 `n = 1` 開始迴圈，或用 `y_prev` 變數如第 1 小題。
- 註：`M_PI` 不屬於 C 標準，但 gcc／MinGW 的 `math.h` 有提供，本題不算錯誤；指出並改用 `#define PI 3.14159265358979` 者可酌予加分。

**3.**

- moving average：每個輸出先加後乘 $`1/4`$ 只需 1 次，共 $`N`$ 次；若每項各乘 $`1/4`$ 則共 $`4N`$ 次（兩種答案皆可，需說明算法）。
- 第 6 題：每個輸出 2 次（$`a\cdot y[n-1]`$ 與 $`(1-a)\cdot x[n]`$；$`1-a`$ 事先算好），差分只需減法，共 $`2N`$ 次。

## 第 8 題　二階 IIR：複數極點與零點（18 分）

**1.**

```math
Y(z)=X(z)+0.25z^{-2}X(z)-0.81z^{-2}Y(z)\ \Rightarrow\
H(z)=\frac{1+0.25z^{-2}}{1+0.81z^{-2}}=\frac{z^2+0.25}{z^2+0.81}
```

**2.** 零點：$`z^2=-0.25\Rightarrow z=\pm0.5j=0.5e^{\pm j\pi/2}`$。極點：$`z^2=-0.81\Rightarrow z=\pm0.9j=0.9e^{\pm j\pi/2}`$。

```
            Im
         x  +0.9j      x : poles  0.9e^{±jπ/2}
         o  +0.5j      o : zeros  0.5e^{±jπ/2}
   ------+------ Re    （單位圓半徑 1）
         o  -0.5j
         x  -0.9j
```

兩極點皆在單位圓內（$`|p|=0.9<1`$），因果系統**穩定**；極點不在原點，是 **IIR**。

**3.** $`h[n]=\delta[n]+0.25\delta[n-2]-0.81h[n-2]`$：

| $`n`$ | 0 | 1 | 2 | 3 | 4 |
|---|---|---|---|---|---|
| $`h[n]`$ | 1 | 0 | $`0.25-0.81=-0.56`$ | 0 | $`-0.81\times(-0.56)=0.4536`$ |

（奇數項皆為 0；$`n\ge2`$ 的偶數項每兩點乘 $`-0.81`$，以 $`0.9^n`$ 衰減並在 $`\pm`$ 間交替，對應極點角度 $`\pi/2`$ 的振盪。）

**4.** $`H(e^{j\omega})=\dfrac{1+0.25e^{-j2\omega}}{1+0.81e^{-j2\omega}}`$，代入 $`e^{-j2\omega}`$：

| $`\omega`$ | $`e^{-j2\omega}`$ | $`H(e^{j\omega})`$ | $`\lvert H\rvert`$ | $`\angle H`$ |
|---|---|---|---|---|
| 0 | 1 | $`1.25/1.81`$ | 0.691 | 0 |
| $`\pi/4`$ | $`-j`$ | $`\dfrac{1-0.25j}{1-0.81j}`$ | $`\dfrac{1.031}{1.287}=0.801`$ | $`\tan^{-1}0.81-\tan^{-1}0.25=0.436`$ |
| $`\pi/2`$ | $`-1`$ | $`0.75/0.19`$ | 3.947 | 0 |
| $`3\pi/4`$ | $`j`$ | $`\dfrac{1+0.25j}{1+0.81j}`$ | 0.801 | $`-0.436`$ |
| $`\pi`$ | 1 | $`1.25/1.81`$ | 0.691 | 0 |

草圖：

- 振幅：在 $`\omega=\pi/2`$ 有尖峰（約 3.95，約 +11.9 dB），兩側迅速降到 0.7–0.8，對 $`\pi/2`$ 左右對稱。
- 相位：$`0\to\pi/2`$ 間為正，先升到最大約 0.78（$`\omega\approx0.42\pi`$），再在 $`\pi/2`$ 附近快速下降穿過 0；$`\pi/2\to\pi`$ 間為負，與前半段反對稱，$`\omega=\pi`$ 回到 0。

向量解釋：$`\lvert H\rvert=\dfrac{\prod\lvert e^{j\omega}-z_k\rvert}{\prod\lvert e^{j\omega}-p_k\rvert}`$。$`\omega=\pi/2`$ 時 $`e^{j\omega}=j`$ 離極點 $`0.9j`$ 只有 0.1，分母很小：

```math
\lvert H(e^{j\pi/2})\rvert=\frac{|j-0.5j|\,|j+0.5j|}{|j-0.9j|\,|j+0.9j|}=\frac{0.5\times1.5}{0.1\times1.9}=3.947
```

零點離單位圓較遠（0.5），壓不住極點造成的峰值。$`\omega=\pi/2`$ 對應 $`f=f_s/4=12`$ kHz，此濾波器加強 12 kHz 附近的訊號。

**5.** 輸入定義於所有 $`n`$，輸出為 $`\lvert H\rvert`$ 縮放、$`\angle H`$ 相移：

| 輸入 | $`\omega`$ | 輸出 $`y[n]`$ |
|---|---|---|
| $`x_1=1`$ | 0 | $`0.691`$ |
| $`x_2=\cos(\pi n/2)`$ | $`\pi/2`$ | $`3.947\cos(\pi n/2)`$ |
| $`x_3=\cos(\pi n/4+\pi/6)`$ | $`\pi/4`$ | $`0.801\cos(\pi n/4+\pi/6+0.436)`$ |
| $`x_4=(-1)^n`$ | $`\pi`$ | $`0.691(-1)^n`$ |
| $`x_5=x_1+x_3`$ | — | $`0.691+0.801\cos(\pi n/4+\pi/6+0.436)`$（線性疊加） |

類比頻率 $`f=\omega f_s/2\pi`$：$`x_2`$ 為 12 kHz，$`x_3`$ 為 6 kHz（$`x_4`$ 為 24 kHz，即 Nyquist 頻率）。
