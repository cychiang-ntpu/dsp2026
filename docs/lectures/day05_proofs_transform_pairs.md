# Day-5 附錄：重要轉換對的證明

> 配合 [day05_transform_pairs.md](day05_transform_pairs.md) 速查表。速查表每一條都在這裡推導；上課只需要會其中標 ★ 的七個，其餘都是同一招（幾何級數、尤拉公式、交換 Σ 與 ∫）的重複。
> 整份只用到三個工具：
> **(G) 幾何級數** $`\sum_{n=0}^{\infty}r^n=\dfrac{1}{1-r}`$（$`\vert r\vert<1`$），有限和 $`\sum_{n=0}^{N-1}r^n=\dfrac{1-r^N}{1-r}`$（$`r\ne1`$）；
> **(E) 尤拉** $`\cos\theta=\frac12(e^{j\theta}+e^{-j\theta})`$，$`\sin\theta=\frac1{2j}(e^{j\theta}-e^{-j\theta})`$；
> **(O) 正交性** $`\dfrac{1}{2\pi}\displaystyle\int_{-\pi}^{\pi}e^{j\omega m}d\omega=\delta[m]`$，$`\dfrac1N\displaystyle\sum_{n=0}^{N-1}e^{j\frac{2\pi}{N}mn}=\delta[((m))_N]`$。

## 0. 三個工具的證明

**(G)**：令 $`S_N=\sum_{n=0}^{N-1}r^n`$，則 $`S_N-rS_N=1-r^N`$，故 $`S_N=\dfrac{1-r^N}{1-r}`$。$`\vert r\vert<1`$ 時 $`r^N\to0`$，得無限和。**收斂條件 $`\vert r\vert<1`$ 就是日後所有 ROC 的來源。**

**(E)**：由 $`e^{j\theta}=\cos\theta+j\sin\theta`$ 與 $`e^{-j\theta}=\cos\theta-j\sin\theta`$ 相加、相減即得。

**(O) 連續版**：$`m=0`$ 時積分為 $`\frac{1}{2\pi}\cdot2\pi=1`$；$`m\ne0`$ 時 $`\displaystyle\int_{-\pi}^{\pi}e^{j\omega m}d\omega=\left.\frac{e^{j\omega m}}{jm}\right|_{-\pi}^{\pi}=\frac{e^{j\pi m}-e^{-j\pi m}}{jm}=\frac{2\sin(\pi m)}{m}=0`$。

**(O) 離散版**：$`m`$ 為 $`N`$ 的倍數時每項都是 1，和為 $`N`$；否則 $`r=e^{j2\pi m/N}\ne1`$ 但 $`r^N=1`$，由 (G) 有限和得 $`\dfrac{1-r^N}{1-r}=0`$。

## 1. DTFT 轉換對

### 1.1 ★ $`a^nu[n]\leftrightarrow\dfrac{1}{1-ae^{-j\omega}}`$，$`\vert a\vert<1`$

```math
X(e^{j\omega})=\sum_{n=0}^{\infty}a^ne^{-j\omega n}=\sum_{n=0}^{\infty}\left(ae^{-j\omega}\right)^n=\frac{1}{1-ae^{-j\omega}}
```

由 (G)，收斂需 $`\vert ae^{-j\omega}\vert=\vert a\vert<1`$。

### 1.2 $`\delta[n-n_0]\leftrightarrow e^{-j\omega n_0}`$

級數只有 $`n=n_0`$ 一項非零：$`\sum_n\delta[n-n_0]e^{-j\omega n}=e^{-j\omega n_0}`$。$`n_0=0`$ 得 $`\delta[n]\leftrightarrow1`$。

### 1.3 $`(n+1)a^nu[n]\leftrightarrow\dfrac{1}{(1-ae^{-j\omega})^2}`$

對 1.1 兩邊視為 $`a`$ 的函數微分：左邊 $`\dfrac{d}{da}\sum_n a^ne^{-j\omega n}=\sum_n na^{n-1}e^{-j\omega n}`$，右邊 $`\dfrac{d}{da}\dfrac{1}{1-ae^{-j\omega}}=\dfrac{e^{-j\omega}}{(1-ae^{-j\omega})^2}`$。
故 $`na^{n-1}u[n]\leftrightarrow\dfrac{e^{-j\omega}}{(1-ae^{-j\omega})^2}`$，即 $`na^nu[n]\leftrightarrow\dfrac{ae^{-j\omega}}{(1-ae^{-j\omega})^2}`$。再加上 1.1：

```math
(n+1)a^nu[n]\;\leftrightarrow\;\frac{ae^{-j\omega}}{(1-ae^{-j\omega})^2}+\frac{1}{1-ae^{-j\omega}}=\frac{ae^{-j\omega}+1-ae^{-j\omega}}{(1-ae^{-j\omega})^2}=\frac{1}{(1-ae^{-j\omega})^2}
```

（這也就是「頻域微分」性質 $`nx[n]\leftrightarrow j\,dX/d\omega`$ 的一個實例，見 1.9。）

### 1.4 ★ 矩形窗 $`x[n]=1`$（$`0\le n\le M`$）$`\leftrightarrow\dfrac{\sin[\omega(M+1)/2]}{\sin(\omega/2)}e^{-j\omega M/2}`$

由 (G) 有限和，$`r=e^{-j\omega}`$：

```math
X(e^{j\omega})=\sum_{n=0}^{M}e^{-j\omega n}=\frac{1-e^{-j\omega(M+1)}}{1-e^{-j\omega}}
```

分子分母各提出「半角」：$`1-e^{-j\theta}=e^{-j\theta/2}\left(e^{j\theta/2}-e^{-j\theta/2}\right)=e^{-j\theta/2}\cdot2j\sin(\theta/2)`$。代入

```math
X(e^{j\omega})=\frac{e^{-j\omega(M+1)/2}\,2j\sin[\omega(M+1)/2]}{e^{-j\omega/2}\,2j\sin(\omega/2)}=\frac{\sin[\omega(M+1)/2]}{\sin(\omega/2)}\,e^{-j\omega M/2}
```

$`\omega=0`$ 時用極限（或直接數）得 $`M+1`$。

### 1.5 ★ 理想低通 $`\dfrac{\sin(\omega_cn)}{\pi n}\leftrightarrow\mathbb{1}\{\vert\omega\vert<\omega_c\}`$

這題要從頻域往回做（反轉換）：

```math
x[n]=\frac{1}{2\pi}\int_{-\omega_c}^{\omega_c}1\cdot e^{j\omega n}d\omega=\frac{1}{2\pi}\left.\frac{e^{j\omega n}}{jn}\right|_{-\omega_c}^{\omega_c}=\frac{e^{j\omega_cn}-e^{-j\omega_cn}}{2\pi jn}\overset{(E)}{=}\frac{\sin(\omega_cn)}{\pi n}
```

$`n=0`$ 時 $`x[0]=\frac{1}{2\pi}\cdot2\omega_c=\omega_c/\pi`$，與 $`\lim_{n\to0}\sin(\omega_cn)/(\pi n)`$ 一致。
注意 $`\sum_n\vert x[n]\vert=\infty`$（$`\sim1/n`$ 調和級數），所以正向 DTFT 級數不絕對收斂，只能均方收斂，這就是 Gibbs 現象的根源（Ch. 7）。

### 1.6 $`e^{j\omega_0n}\leftrightarrow\sum_k2\pi\delta(\omega-\omega_0-2\pi k)`$

一樣從反轉換驗證：在一個週期 $`(-\pi,\pi]`$ 內只有一個 $`\delta`$，

```math
\frac{1}{2\pi}\int_{-\pi}^{\pi}2\pi\,\delta(\omega-\omega_0)e^{j\omega n}d\omega=e^{j\omega_0n}
```

$`\omega_0=0`$ 得 $`1\leftrightarrow\sum_k2\pi\delta(\omega-2\pi k)`$。用 (E) 把 $`\cos(\omega_0n)`$ 拆成兩個複指數，再用線性，得 $`\sum_k\pi[\delta(\omega-\omega_0-2\pi k)+\delta(\omega+\omega_0-2\pi k)]`$。

### 1.7 $`u[n]\leftrightarrow\dfrac{1}{1-e^{-j\omega}}+\sum_k\pi\delta(\omega-2\pi k)`$

$`u[n]`$ 不絕對可和，不能直接套 (G)。把它拆成 $`u[n]=\tfrac12+\tfrac12s[n]`$，其中 $`s[n]=u[n]-u[-n-1]`$（$`n\ge0`$ 為 $`+1`$、$`n\le-1`$ 為 $`-1`$；逐點檢查：$`n\ge0`$ 得 $`\frac12+\frac12=1`$，$`n\le-1`$ 得 $`\frac12-\frac12=0`$ ✓）。
$`\tfrac12\leftrightarrow\sum_k\pi\delta(\omega-2\pi k)`$（由 1.6）。$`s[n]`$ 視為 $`a^nu[n]-a^{-n}u[-n-1]`$ 在 $`a\to1^-`$ 的極限，兩項分別由 (G)：

```math
\sum_{n\ge0}a^ne^{-j\omega n}-\sum_{n\le-1}a^{-n}e^{-j\omega n}
=\frac{1}{1-ae^{-j\omega}}-\frac{ae^{j\omega}}{1-ae^{j\omega}}
\;\xrightarrow{a\to1^-}\;\frac{1}{1-e^{-j\omega}}-\frac{e^{j\omega}}{1-e^{j\omega}}
```

而 $`-\dfrac{e^{j\omega}}{1-e^{j\omega}}=\dfrac{e^{j\omega}}{e^{j\omega}-1}=\dfrac{1}{1-e^{-j\omega}}`$（分子分母同除 $`e^{j\omega}`$），故 $`s[n]\leftrightarrow\dfrac{2}{1-e^{-j\omega}}`$。乘 $`\tfrac12`$ 與 DC 項相加即得。

### 1.8 ★ 卷積定理 $`x*h\leftrightarrow XH`$

```math
\sum_n\Big(\sum_kx[k]h[n-k]\Big)e^{-j\omega n}
=\sum_kx[k]\sum_nh[n-k]e^{-j\omega n}
\overset{m=n-k}{=}\sum_kx[k]e^{-j\omega k}\sum_mh[m]e^{-j\omega m}=X(e^{j\omega})H(e^{j\omega})
```

（交換兩個和的次序，絕對可和時合法。）

### 1.9 其餘性質

- **時移**：$`\sum_nx[n-n_d]e^{-j\omega n}\overset{m=n-n_d}{=}e^{-j\omega n_d}\sum_mx[m]e^{-j\omega m}`$。
- **頻移**：$`\sum_ne^{j\omega_0n}x[n]e^{-j\omega n}=\sum_nx[n]e^{-j(\omega-\omega_0)n}=X(e^{j(\omega-\omega_0)})`$。
- **時間反轉**：$`\sum_nx[-n]e^{-j\omega n}\overset{m=-n}{=}\sum_mx[m]e^{j\omega m}=X(e^{-j\omega})`$。
- **頻域微分**：$`\dfrac{dX}{d\omega}=\sum_nx[n](-jn)e^{-j\omega n}`$，兩邊乘 $`j`$：$`j\dfrac{dX}{d\omega}=\sum_n nx[n]e^{-j\omega n}`$。
- **相乘 ↔ 週期卷積**：見 2.10(a)。
- **Parseval**：$`\sum_n\vert x[n]\vert^2=\sum_nx[n]x^*[n]=\sum_nx[n]\Big(\frac{1}{2\pi}\int X^*(e^{j\omega})e^{-j\omega n}d\omega\Big)=\frac{1}{2\pi}\int X^*(e^{j\omega})\underbrace{\sum_nx[n]e^{-j\omega n}}_{X(e^{j\omega})}d\omega`$。
- **實數序列的共軛對稱**：$`X^*(e^{j\omega})=\sum_nx^*[n]e^{j\omega n}=\sum_nx[n]e^{-j(-\omega)n}=X(e^{-j\omega})`$。取模與取角即得 $`\vert X\vert`$ 偶、$`\angle X`$ 奇。

## 2. DFT／IDFT

### 2.1 ★ IDFT 真的是 DFT 的反運算

把 $`X[k]=\sum_{m=0}^{N-1}x[m]W_N^{km}`$ 代入 IDFT：

```math
\frac1N\sum_{k=0}^{N-1}X[k]W_N^{-kn}
=\frac1N\sum_{k=0}^{N-1}\sum_{m=0}^{N-1}x[m]W_N^{k(m-n)}
=\sum_{m=0}^{N-1}x[m]\underbrace{\frac1N\sum_{k=0}^{N-1}e^{-j\frac{2\pi}{N}k(m-n)}}_{\delta[((m-n))_N]\ \text{by (O)}}
=x[n]
```

$`0\le m,n\le N-1`$ 時 $`((m-n))_N=0\iff m=n`$。**$`\frac1N`$ 正是 (O) 離散版的 $`\frac1N`$**；若把 $`\frac1N`$ 放在正轉換或兩邊各放 $`\frac{1}{\sqrt N}`$ 也成立，只是慣例不同。

### 2.2 $`\delta[((n-m))_N]\leftrightarrow W_N^{km}`$，$`1\leftrightarrow N\delta[k]`$

前者級數只剩 $`n=m`$ 一項。後者 $`\sum_{n=0}^{N-1}W_N^{kn}=N\delta[((k))_N]`$，由 (O)；$`0\le k\le N-1`$ 時即 $`N\delta[k]`$。

### 2.3 ★ $`e^{j2\pi k_0n/N}\leftrightarrow N\delta[k-k_0]`$ 與 $`\cos`$

```math
X[k]=\sum_{n=0}^{N-1}e^{j\frac{2\pi}{N}k_0n}e^{-j\frac{2\pi}{N}kn}=\sum_{n=0}^{N-1}e^{-j\frac{2\pi}{N}(k-k_0)n}=N\delta[((k-k_0))_N]
```

$`\cos(2\pi k_0n/N)`$ 由 (E) 拆成 $`\frac12e^{j2\pi k_0n/N}+\frac12e^{-j2\pi k_0n/N}`$，第二項的 $`-k_0`$ 在 $`0..N-1`$ 內對應 $`((-k_0))_N=N-k_0`$，故 $`X[k]=\frac N2(\delta[k-k_0]+\delta[k-(N-k_0)])`$。

**若 $`k_0`$ 不是整數**（頻率不落在格點）：$`e^{-j\frac{2\pi}{N}(k-k_0)n}`$ 的公比 $`r^N=e^{-j2\pi(k-k_0)}\ne1`$，(O) 不再給零，有限和 $`\dfrac{1-e^{-j2\pi(k-k_0)}}{1-e^{-j\frac{2\pi}{N}(k-k_0)}}`$ 對每個 $`k`$ 都非零，這就是 leakage 的數學內容。

### 2.4 $`a^n`$（$`0\le n\le N-1`$）$`\leftrightarrow\dfrac{1-a^N}{1-aW_N^k}`$

(G) 有限和，$`r=aW_N^k`$：$`\dfrac{1-(aW_N^k)^N}{1-aW_N^k}`$，而 $`(W_N^k)^N=e^{-j2\pi k}=1`$。矩形（長 $`L`$）同理，$`r=W_N^k`$、項數 $`L`$，再用 1.4 的半角技巧化成 $`\sin`$ 比。

### 2.5 圓周時移 $`x[((n-m))_N]\leftrightarrow W_N^{km}X[k]`$

關鍵：$`W_N^{kn}`$ 本身是 $`n`$ 的 $`N`$ 週期函數，所以可以把 $`n`$ 換成 $`((n))_N`$ 而不改變值。

```math
\sum_{n=0}^{N-1}x[((n-m))_N]W_N^{kn}
\overset{\ell=((n-m))_N}{=}\sum_{\ell=0}^{N-1}x[\ell]W_N^{k(\ell+m)}=W_N^{km}X[k]
```

（$`n`$ 跑完 $`0..N-1`$ 時 $`\ell`$ 也剛好跑完 $`0..N-1`$，各一次。）

### 2.6 ★ 圓周卷積定理

```math
\sum_{n=0}^{N-1}\Big(\sum_{m=0}^{N-1}x_1[m]x_2[((n-m))_N]\Big)W_N^{kn}
=\sum_{m=0}^{N-1}x_1[m]\underbrace{\sum_{n=0}^{N-1}x_2[((n-m))_N]W_N^{kn}}_{W_N^{km}X_2[k]\ \text{by 2.5}}
=X_2[k]\sum_mx_1[m]W_N^{km}=X_1[k]X_2[k]
```

**為什麼不是線性卷積**：用 IDFT 把 $`X_1[k]X_2[k]`$ 反回來，得到的是 $`x_1`$ 與 $`x_2`$ 先各自做 $`N`$ 週期延拓再做線性卷積、取一個週期的結果。線性卷積長 $`L+P-1`$；若 $`N<L+P-1`$，週期延拓後相鄰週期的尾巴會疊進 $`0..N-1`$ 這一段（time aliasing）。$`N\ge L+P-1`$ 時一個週期內只有一份，圓周＝線性。

### 2.7 Parseval（DFT 版）

```math
\sum_{n=0}^{N-1}\vert x[n]\vert^2=\sum_nx[n]x^*[n]=\sum_nx[n]\Big(\frac1N\sum_kX^*[k]W_N^{kn}\Big)=\frac1N\sum_kX^*[k]\underbrace{\sum_nx[n]W_N^{kn}}_{X[k]}=\frac1N\sum_k\vert X[k]\vert^2
```

### 2.8 實數序列 $`X[((-k))_N]=X^*[k]`$

$`X^*[k]=\sum_nx[n]W_N^{-kn}=\sum_nx[n]W_N^{(-k)n}=X[-k]`$，再用 $`W_N^{kn}`$ 對 $`k`$ 的 $`N`$ 週期性得 $`X[((-k))_N]`$。所以 `rfft` 只存 $`k=0..N/2`$ 不會丟資訊。

### 2.9 ★ 卷積定理的三個版本完整證明

**(a) DTFT**（同 1.8，重抄一次以便對照）。設 $`x,h`$ 絕對可和，$`y=x*h`$：

```math
Y(e^{j\omega})=\sum_{n}\Big(\sum_{k}x[k]h[n-k]\Big)e^{-j\omega n}
=\sum_{k}x[k]\sum_{n}h[n-k]e^{-j\omega n}
```

內層令 $`m=n-k`$（$`k`$ 固定，$`n`$ 跑遍整數則 $`m`$ 也跑遍整數）：$`\sum_mh[m]e^{-j\omega(m+k)}=e^{-j\omega k}H(e^{j\omega})`$。代回：

```math
Y(e^{j\omega})=H(e^{j\omega})\sum_kx[k]e^{-j\omega k}=X(e^{j\omega})H(e^{j\omega})
```

交換 Σ 次序的合法性：$`\sum_n\sum_k\vert x[k]\vert\vert h[n-k]\vert=\big(\sum_k\vert x[k]\vert\big)\big(\sum_m\vert h[m]\vert\big)<\infty`$（Fubini／絕對收斂級數可重排）。順帶證明了 $`y`$ 也絕對可和，且 $`\sum_n\vert y[n]\vert\le\Vert x\Vert_1\Vert h\Vert_1`$。

**(b) z 轉換**。把 $`e^{-j\omega}`$ 換成 $`z^{-1}`$，每一步相同：

```math
Y(z)=\sum_n\Big(\sum_kx[k]h[n-k]\Big)z^{-n}
=\sum_kx[k]z^{-k}\sum_mh[m]z^{-m}=X(z)H(z)
```

合法性要求兩個級數在同一個 $`z`$ 絕對收斂，即 $`z\in R_x\cap R_h`$，所以 $`R_y\supseteq R_x\cap R_h`$。可能更大：若 $`X(z)`$ 的零點抵銷了 $`H(z)`$ 的極點，乘積的 ROC 會往外（或往內）擴。例：$`x[n]=\delta[n]-a\delta[n-1]`$（$`X=1-az^{-1}`$，全平面），$`h[n]=a^nu[n]`$（$`\vert z\vert>\vert a\vert`$），則 $`y[n]=\delta[n]`$、$`Y(z)=1`$、ROC 全平面。

**(c) DFT（圓周卷積）**。$`y[n]=\sum_{m=0}^{N-1}x_1[m]x_2[((n-m))_N]`$，$`0\le n\le N-1`$：

```math
Y[k]=\sum_{n=0}^{N-1}\sum_{m=0}^{N-1}x_1[m]x_2[((n-m))_N]W_N^{kn}
=\sum_{m=0}^{N-1}x_1[m]\underbrace{\sum_{n=0}^{N-1}x_2[((n-m))_N]W_N^{kn}}_{=\,W_N^{km}X_2[k]\ (2.5)}
=X_2[k]\sum_{m=0}^{N-1}x_1[m]W_N^{km}=X_1[k]X_2[k]
```

有限和，交換次序無條件合法。2.5 的關鍵是 $`W_N^{kn}`$ 對 $`n`$ 有 $`N`$ 週期，所以「$`n`$ 跑 $`0..N-1`$」和「$`((n-m))_N`$ 跑 $`0..N-1`$」是同一組指標的重排。

**(d) 圓周卷積何時等於線性卷積**。令 $`\tilde x_i[n]=\sum_rx_i[n-rN]`$ 為週期延拓。則 $`x_1\circledast_Nx_2`$ 在 $`0\le n\le N-1`$ 上等於 $`(x_1*\tilde x_2)[n]=\sum_r(x_1*x_2)[n-rN]`$，即**線性卷積的 $`N`$ 週期延拓取一個週期**。線性卷積 $`x_1*x_2`$ 的支撐為 $`0..L+P-2`$；若 $`N\ge L+P-1`$，各週期副本互不重疊，取 $`0..N-1`$ 就是原樣（後面補零）；若 $`N<L+P-1`$，$`r=1`$ 的副本 $`(x_1*x_2)[n+N]`$ 會疊到 $`n=0..L+P-2-N`$ 上（time aliasing）。

**(e) 從 eigenfunction 看**。由 Day-4 第 2 節，$`e^{j\omega n}\to H(e^{j\omega})e^{j\omega n}`$。反 DTFT 把 $`x[n]=\frac{1}{2\pi}\int X(e^{j\omega})e^{j\omega n}d\omega`$ 寫成複指數的連續疊加；LTI 系統是線性的，且（絕對可和時）可與積分交換，故

```math
y[n]=\frac{1}{2\pi}\int X(e^{j\omega})\,\underbrace{\big(e^{j\omega n}\to\big)}_{\text{通過系統}}\,d\omega
=\frac{1}{2\pi}\int X(e^{j\omega})H(e^{j\omega})e^{j\omega n}d\omega
```

比對反 DTFT 的形式，得 $`Y(e^{j\omega})=X(e^{j\omega})H(e^{j\omega})`$。這是 (a) 的「物理」版本，兩者等價。

**(f) numpy 驗證**（課堂可直接跑）：

```python
import numpy as np
x = np.random.randn(5); h = np.random.randn(4)          # L=5, P=4
lin = np.convolve(x, h)                                  # 長 8
N = 8                                                    # N >= L+P-1
circ = np.fft.ifft(np.fft.fft(x, N) * np.fft.fft(h, N)).real
print(np.allclose(lin, circ))                            # True
N = 6                                                    # N <  L+P-1 -> time aliasing
circ6 = np.fft.ifft(np.fft.fft(x, 6) * np.fft.fft(h, 6)).real
print(np.allclose(circ6, lin[:6] + np.r_[lin[6:], 0, 0, 0, 0]))  # True：尾巴繞回前面
```

### 2.10 ★ 對偶：時域相乘 ↔ 頻域卷積

**(a) DTFT：$`x[n]w[n]\leftrightarrow\dfrac{1}{2\pi}\displaystyle\int_{-\pi}^{\pi}X(e^{j\theta})W(e^{j(\omega-\theta)})d\theta`$（週期卷積）**

把 $`w[n]`$ 用反 DTFT 寫開，代入定義，交換 Σ 與 ∫：

```math
\sum_nx[n]w[n]e^{-j\omega n}
=\sum_nx[n]\Big(\frac{1}{2\pi}\int_{-\pi}^{\pi}W(e^{j\theta})e^{j\theta n}d\theta\Big)e^{-j\omega n}
=\frac{1}{2\pi}\int_{-\pi}^{\pi}W(e^{j\theta})\underbrace{\sum_nx[n]e^{-j(\omega-\theta)n}}_{X(e^{j(\omega-\theta)})}d\theta
```

即 $`\dfrac{1}{2\pi}\displaystyle\int_{-\pi}^{\pi}W(e^{j\theta})X(e^{j(\omega-\theta)})d\theta`$；令 $`\theta'=\omega-\theta`$ 並利用被積函數的 $`2\pi`$ 週期性（積分區間可任意平移一個週期），得到對稱的寫法 $`\dfrac{1}{2\pi}\displaystyle\int_{-\pi}^{\pi}X(e^{j\theta'})W(e^{j(\omega-\theta')})d\theta'`$。
為什麼叫「週期卷積」：普通卷積積分跑 $`(-\infty,\infty)`$，這裡兩個函數都是 $`2\pi`$ 週期，只積一個週期，並多一個 $`\frac{1}{2\pi}`$。
合法性：$`x`$ 絕對可和且 $`W`$ 有界（$`w`$ 絕對可和即可）時，Σ∫ 可交換。

**它就是視窗效應**：取 $`x[n]=e^{j\omega_0n}`$（$`X=2\pi\delta(\omega-\omega_0)`$，一個週期內），截斷後 $`x[n]w[n]`$ 的 DTFT 為 $`\frac{1}{2\pi}\int2\pi\delta(\theta-\omega_0)W(e^{j(\omega-\theta)})d\theta=W(e^{j(\omega-\omega_0)})`$：一根線被換成窗的頻譜（主瓣＋旁瓣）搬到 $`\omega_0`$。矩形窗的 $`W`$ 就是 1.4 的 $`\sin`$ 比。

**(b) DFT：$`x_1[n]x_2[n]\leftrightarrow\dfrac1N\displaystyle\sum_{\ell=0}^{N-1}X_1[\ell]X_2[((k-\ell))_N]`$（頻域圓周卷積）**

把 $`x_2[n]`$ 用 IDFT 寫開：

```math
\sum_{n=0}^{N-1}x_1[n]x_2[n]W_N^{kn}
=\sum_{n=0}^{N-1}x_1[n]\Big(\frac1N\sum_{\ell=0}^{N-1}X_2[\ell]W_N^{-\ell n}\Big)W_N^{kn}
=\frac1N\sum_{\ell=0}^{N-1}X_2[\ell]\underbrace{\sum_{n=0}^{N-1}x_1[n]W_N^{(k-\ell)n}}_{X_1[((k-\ell))_N]}
```

最後一步用 $`W_N^{(k-\ell)n}`$ 對 $`k-\ell`$ 的 $`N`$ 週期性，把指標 $`k-\ell`$（可能為負）折回 $`0..N-1`$。有限和，交換無條件合法。對調 $`x_1,x_2`$ 的角色得對稱寫法。

**$`\frac1N`$ 從哪來**：和 2.1 一樣，是 IDFT 裡的那個 $`\frac1N`$。對照 (a) 的 $`\frac{1}{2\pi}`$：連續頻率一個週期長 $`2\pi`$，離散頻率一個週期 $`N`$ 格，都是「除以一個週期的長度」。

**(c) z 轉換：$`x_1[n]x_2[n]\leftrightarrow\dfrac{1}{2\pi j}\displaystyle\oint_CX_1(v)X_2\!\left(\frac zv\right)v^{-1}dv`$（複卷積定理，選讀）**

把 $`x_2[n]`$ 用反 z 轉換（4.4）寫開：

```math
\sum_nx_1[n]x_2[n]z^{-n}
=\sum_nx_1[n]\Big(\frac{1}{2\pi j}\oint_CX_2(v)v^{n-1}dv\Big)z^{-n}
=\frac{1}{2\pi j}\oint_CX_2(v)\underbrace{\sum_nx_1[n]\Big(\frac zv\Big)^{-n}}_{X_1(z/v)}v^{-1}dv
```

對調兩者角色得上式。$`C`$ 須同時落在 $`R_{x_2}`$ 與「$`z/v\in R_{x_1}`$」的區域內；$`R_{x_1x_2}\supseteq R_{x_1}R_{x_2}`$（兩個 ROC 的半徑逐點相乘）。令 $`z=e^{j\omega}`$、$`v=e^{j\theta}`$（$`dv=je^{j\theta}d\theta`$），這條式子就退化成 (a)，再一次說明 DTFT 是 z 轉換在單位圓上的特例。

**(d) 與 2.9 的對稱**：兩條定理可以互推。對 (a) 用「對偶」（DTFT 與反 DTFT 形式相同，只差正負號與 $`2\pi`$）即得 2.9(a)；DFT 版同理用 2.3 的對偶性質 $`X[n]\leftrightarrow Nx[((-k))_N]`$。上課只需證一邊，另一邊用對偶帶過。

**(e) numpy 驗證**（DFT 版）：

```python
import numpy as np
N = 8
x1 = np.random.randn(N); x2 = np.random.randn(N)
X1 = np.fft.fft(x1); X2 = np.fft.fft(x2)
lhs = np.fft.fft(x1 * x2)
rhs = np.array([sum(X1[l] * X2[(k - l) % N] for l in range(N)) for k in range(N)]) / N
print(np.allclose(lhs, rhs))                             # True
```

DTFT 版可用大 $`N`$ 的 DFT 近似積分來驗證：對長 $`L`$ 的 $`x`$ 與 $`w`$，取 $`N\ge2L-1`$，`fft(x*w, N)` 與「$`\frac1N\,`$fft(x,N) 圓周卷積 fft(w,N)」相等，因為 $`N`$ 點 DFT 正是 DTFT 的取樣，而 $`x w`$ 長度 $`L\le N`$ 不發生 time aliasing。

## 3. z 轉換對

### 3.1 ★ $`a^nu[n]\leftrightarrow\dfrac{1}{1-az^{-1}}`$，ROC $`\vert z\vert>\vert a\vert`$

```math
X(z)=\sum_{n=0}^{\infty}a^nz^{-n}=\sum_{n=0}^{\infty}(az^{-1})^n\overset{(G)}{=}\frac{1}{1-az^{-1}},\qquad\vert az^{-1}\vert<1\iff\vert z\vert>\vert a\vert
```

$`a=1`$ 得 $`u[n]`$。

### 3.2 ★ $`-a^nu[-n-1]\leftrightarrow\dfrac{1}{1-az^{-1}}`$，ROC $`\vert z\vert<\vert a\vert`$

```math
X(z)=-\sum_{n=-\infty}^{-1}a^nz^{-n}\overset{m=-n}{=}-\sum_{m=1}^{\infty}a^{-m}z^{m}=-\sum_{m=1}^{\infty}(a^{-1}z)^m
=-\left(\frac{1}{1-a^{-1}z}-1\right)=\frac{-a^{-1}z}{1-a^{-1}z}
```

分子分母同乘 $`-a z^{-1}`$：$`\dfrac{1}{1-az^{-1}}`$。收斂需 $`\vert a^{-1}z\vert<1\iff\vert z\vert<\vert a\vert`$。
**同一個代數式、兩個 ROC、兩個完全不同的序列**，這就是表上「ROC 一定要寫」的理由。

### 3.3 $`na^nu[n]\leftrightarrow\dfrac{az^{-1}}{(1-az^{-1})^2}`$

用 z 域微分性質（3.6 證）$`nx[n]\leftrightarrow-z\dfrac{dX}{dz}`$：

計算：$`\dfrac{d}{dz}(1-az^{-1})^{-1}=-(1-az^{-1})^{-2}\cdot\dfrac{d}{dz}(1-az^{-1})=-(1-az^{-1})^{-2}\cdot az^{-2}`$。
乘 $`-z`$：$`\dfrac{az^{-1}}{(1-az^{-1})^2}`$。ROC 不變。左邊版本同理對 3.2 微分。

### 3.4 ★ $`r^n\cos(\omega_0n)u[n]`$ 與 $`r^n\sin(\omega_0n)u[n]`$

(E) 拆開，各是 3.1 的 $`a=re^{\pm j\omega_0}`$：

```math
r^n\cos(\omega_0n)u[n]=\tfrac12(re^{j\omega_0})^nu[n]+\tfrac12(re^{-j\omega_0})^nu[n]
\;\leftrightarrow\;\frac12\left[\frac{1}{1-re^{j\omega_0}z^{-1}}+\frac{1}{1-re^{-j\omega_0}z^{-1}}\right]
```

通分：分母 $`(1-re^{j\omega_0}z^{-1})(1-re^{-j\omega_0}z^{-1})=1-r(e^{j\omega_0}+e^{-j\omega_0})z^{-1}+r^2z^{-2}=1-2r\cos(\omega_0)z^{-1}+r^2z^{-2}`$；
分子 $`\frac12[(1-re^{-j\omega_0}z^{-1})+(1-re^{j\omega_0}z^{-1})]=1-r\cos(\omega_0)z^{-1}`$。
$`\sin`$ 版：係數改為 $`\frac1{2j}`$ 與 $`-\frac1{2j}`$，分子 $`\frac{1}{2j}[(1-re^{-j\omega_0}z^{-1})-(1-re^{j\omega_0}z^{-1})]=\frac{r z^{-1}}{2j}(e^{j\omega_0}-e^{-j\omega_0})=r\sin(\omega_0)z^{-1}`$。
ROC：兩個極點模都是 $`r`$，右邊序列 → $`\vert z\vert>r`$。$`r=1`$ 得純 $`\cos`$、$`\sin`$ 的表項。**極點 $`re^{\pm j\omega_0}`$ 就是 biquad 共振器的設計變數**：$`\omega_0`$ 定共振頻率、$`r`$ 定頻寬／衰減速度。

### 3.5 有限長 $`a^n`$（$`0\le n\le N-1`$）

(G) 有限和：$`\sum_{n=0}^{N-1}(az^{-1})^n=\dfrac{1-a^Nz^{-N}}{1-az^{-1}}`$。看似在 $`z=a`$ 有極點，但分子在 $`z=a`$ 也是零（$`a^Na^{-N}=1`$），極零相消；真正的奇點只剩 $`z=0`$（$`N-1`$ 階），所以 ROC 是 $`\vert z\vert>0`$，與「有限長 → 全平面除原點」一致。

### 3.6 性質

- **時移**：$`\sum_nx[n-n_0]z^{-n}\overset{m=n-n_0}{=}z^{-n_0}\sum_mx[m]z^{-m}=z^{-n_0}X(z)`$。$`n_0>0`$ 時多了 $`z^{-n_0}`$，在 $`z=0`$ 可能新增極點（ROC 可能去掉 $`0`$）。
- **指數加權**：$`\sum_nz_0^nx[n]z^{-n}=\sum_nx[n](z/z_0)^{-n}=X(z/z_0)`$；$`z/z_0\in R_x\iff z\in\vert z_0\vert R_x`$。
- **z 域微分**：$`\dfrac{dX}{dz}=\sum_nx[n](-n)z^{-n-1}`$，乘 $`-z`$：$`-z\dfrac{dX}{dz}=\sum_nnx[n]z^{-n}`$。
- **時間反轉**：$`\sum_nx[-n]z^{-n}\overset{m=-n}{=}\sum_mx[m](1/z)^{-m}=X(1/z)`$。
- **卷積**：見 2.9(b)。ROC 至少是交集（可能因極零相消而更大）。
- **初值定理**：因果 $`X(z)=x[0]+x[1]z^{-1}+x[2]z^{-2}+\cdots`$，$`z\to\infty`$ 時只剩 $`x[0]`$。
- **ROC 包含單位圓 ⇔ 穩定**：穩定 $`\iff\sum_n\vert h[n]\vert<\infty\iff\sum_n\vert h[n]\vert\,\vert z\vert^{-n}`$ 在 $`\vert z\vert=1`$ 收斂 $`\iff`$ 單位圓 $`\in`$ ROC（z 轉換在 ROC 內絕對收斂）。因果 → ROC 是最外極點之外的區域，要包含單位圓則所有極點 $`\vert d_k\vert<1`$。

## 4. 反 z 轉換

### 4.1 ★ 部分分式係數公式 $`A_k=(1-d_kz^{-1})X(z)\big|_{z=d_k}`$

設極點相異，$`X(z)=\sum_{i=1}^N\dfrac{A_i}{1-d_iz^{-1}}`$。兩邊乘 $`(1-d_kz^{-1})`$：

```math
(1-d_kz^{-1})X(z)=A_k+\sum_{i\ne k}A_i\frac{1-d_kz^{-1}}{1-d_iz^{-1}}
```

令 $`z=d_k`$：右邊第二項每一項的分子 $`1-d_kd_k^{-1}=0`$，分母 $`1-d_id_k^{-1}\ne0`$（極點相異），全部消失，只剩 $`A_k`$。

**為什麼可以這樣拆**：$`X(z)`$ 是 $`z^{-1}`$ 的有理函數，分母 $`\prod_i(1-d_iz^{-1})`$ 是 $`N`$ 次多項式，分子次數 $`<N`$；$`N`$ 個待定係數 $`A_i`$ 通分後給出一個次數 $`<N`$ 的分子多項式，共 $`N`$ 個自由度，與原分子一一對應（線性方程組非奇異，因為 $`d_i`$ 相異）。分子次數 $`\ge N`$ 時先長除法，餘式才滿足這條件。

**ROC 決定每一項選右邊或左邊**：每一項 $`\dfrac{A_k}{1-d_kz^{-1}}`$ 有兩個候選序列（3.1 與 3.2），但整體 ROC 是所有項 ROC 的交集且必須非空；ROC 在 $`\vert d_k\vert`$ 外的項必須選右邊、在內的必須選左邊，否則交集為空。

### 4.2 重根

若 $`(1-dz^{-1})^s`$，對應項為 $`\sum_{m=1}^s\dfrac{C_m}{(1-dz^{-1})^m}`$；由 3.3 以及重複對 3.1 做 $`\dfrac{d}{da}`$，

```math
\frac{(n+1)(n+2)\cdots(n+m-1)}{(m-1)!}\,a^nu[n]\;\leftrightarrow\;\frac{1}{(1-az^{-1})^m}
```

（$`m=2`$ 就是 1.3 的 $`(n+1)a^nu[n]`$。）

### 4.3 ★ 長除法為什麼對

z 轉換的定義 $`X(z)=\sum_nx[n]z^{-n}`$ 本身就是「以 $`z^{-1}`$ 為變數的冪級數」；在 ROC 內這個級數收斂且**唯一**（Laurent 級數唯一性）。所以只要把 $`X(z)`$ 用任何方法展成在該 ROC 收斂的 $`\sum c_nz^{-n}`$，必有 $`x[n]=c_n`$。
- ROC 在外（因果）：展成 $`z^{-1}`$ 的升冪 $`c_0+c_1z^{-1}+\cdots`$，在 $`\vert z\vert`$ 大時收斂 → 長除法分子分母都按 $`z^{-1}`$ 升冪排。
- ROC 在內（反因果）：展成 $`z`$ 的升冪 → 按 $`z^{-1}`$ 降冪（即 $`z`$ 升冪）排來除。

例：$`\dfrac{1}{1-az^{-1}}`$ 按 $`z^{-1}`$ 升冪除得 $`1+az^{-1}+a^2z^{-2}+\cdots`$，係數 $`a^n`$，即 3.1；按另一方向除得 $`-a^{-1}z-a^{-2}z^2-\cdots`$，係數在 $`n=-1,-2,\dots`$ 為 $`-a^{n}`$，即 3.2。

### 4.4 圍線積分公式從哪來（選讀）

把 $`X(z)=\sum_mx[m]z^{-m}`$ 代入 $`\dfrac{1}{2\pi j}\oint_CX(z)z^{n-1}dz`$，$`C`$ 為 ROC 內逆時針繞原點的圓：

```math
\frac{1}{2\pi j}\oint_C\sum_mx[m]z^{n-m-1}dz=\sum_mx[m]\underbrace{\frac{1}{2\pi j}\oint_Cz^{n-m-1}dz}_{\delta[n-m]}=x[n]
```

其中 $`\dfrac{1}{2\pi j}\oint_Cz^{k-1}dz=\delta[k]`$：令 $`z=re^{j\theta}`$、$`dz=jre^{j\theta}d\theta`$，積分 $`=\dfrac{r^k}{2\pi}\displaystyle\int_0^{2\pi}e^{jk\theta}d\theta`$，由 (O) 連續版得 $`\delta[k]`$。取 $`r=1`$（單位圓在 ROC 內時）就是 DTFT 反轉換公式——**這就是「z 轉換限制在單位圓是 DTFT」的證明**。
有理函數時用留數定理，$`x[n]=\sum\text{Res}[X(z)z^{n-1}]`$，單極點的留數剛好就是 4.1 的 $`A_kd_k^n`$，所以部分分式法與圍線積分是同一件事。

## 5. 串起來的例子的證明（速查表第 5 節）

$`y[n]=(1-\alpha)y[n-1]+\alpha x[n]`$，兩邊 z 轉換（線性＋時移）：$`Y(z)=(1-\alpha)z^{-1}Y(z)+\alpha X(z)`$ → $`H(z)=\dfrac{\alpha}{1-(1-\alpha)z^{-1}}`$。
因果 → ROC $`\vert z\vert>\vert1-\alpha\vert`$；由 3.1，$`h[n]=\alpha(1-\alpha)^nu[n]`$。
$`0<\alpha<2`$ 時 $`\vert1-\alpha\vert<1`$，單位圓在 ROC 內，代 $`z=e^{j\omega}`$：
$`H(e^{j0})=\dfrac{\alpha}{1-(1-\alpha)}=1`$，$`H(e^{j\pi})=\dfrac{\alpha}{1+(1-\alpha)}=\dfrac{\alpha}{2-\alpha}`$，$`0<\alpha<1`$ 時小於 1 → 低通。
最後 $`\sum_{n=0}^{N-1}h[n]e^{-j\omega_kn}`$ 與真正的 $`H(e^{j\omega_k})`$ 差 $`\sum_{n\ge N}\alpha(1-\alpha)^ne^{-j\omega_kn}`$，其模 $`\le\alpha\dfrac{(1-\alpha)^N}{1-(1-\alpha)}=(1-\alpha)^N`$，即截斷誤差 $`\propto(1-\alpha)^N`$。

---

[← day05_transform_pairs.md](day05_transform_pairs.md) ｜ [講義目錄](README.md)
