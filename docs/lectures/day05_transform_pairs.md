# Day-5（第 5 週）：重要的轉換對 — DTFT、DFT／IDFT、z 轉換與反 z 轉換

> 上課用速查講義。目標：把四種「時域 ↔ 變換域」的對應關係放在同一張表裡，看清楚它們其實是同一件事的四個版本；並熟記最常用的幾組轉換對，之後 Ch. 4–8 都會反覆用到。
> 教科書對應：O&S Table 2.3（DTFT pairs）、Table 3.1（z-transform pairs）、Table 3.2（z 性質）、Table 8.2（DFT 性質）。
> **每一條轉換對與性質的證明**見附錄 [day05_proofs_transform_pairs.md](day05_proofs_transform_pairs.md)，編號與本檔各節對應。

## 0. 四個轉換一張圖

| 轉換 | 正轉換（analysis） | 反轉換（synthesis） | 變數 | 何時用 |
|---|---|---|---|---|
| DTFT | $`X(e^{j\omega})=\sum_{n=-\infty}^{\infty}x[n]e^{-j\omega n}`$ | $`x[n]=\dfrac{1}{2\pi}\displaystyle\int_{-\pi}^{\pi}X(e^{j\omega})e^{j\omega n}\,d\omega`$ | $`\omega`$ 連續、週期 $`2\pi`$ | 頻率響應、理論分析 |
| DFT | $`X[k]=\sum_{n=0}^{N-1}x[n]W_N^{kn}`$ | $`x[n]=\dfrac{1}{N}\sum_{k=0}^{N-1}X[k]W_N^{-kn}`$ | $`k=0,\dots,N-1`$ 離散 | 電腦計算（FFT）、頻譜圖 |
| z 轉換 | $`X(z)=\sum_{n=-\infty}^{\infty}x[n]z^{-n}`$，ROC | $`x[n]=\dfrac{1}{2\pi j}\oint_C X(z)z^{n-1}\,dz`$ | $`z`$ 複數平面 | 系統函數、極零點、穩定性、LCCDE |
| 反 z（實務） | — | 部分分式、長除法、查表 | | 由 $`H(z)`$ 求 $`h[n]`$ |

其中 $`W_N=e^{-j2\pi/N}`$。

三者的關係：

```math
X(e^{j\omega})=X(z)\big|_{z=e^{j\omega}}\quad(\text{ROC 需包含單位圓}),\qquad
X[k]=X(e^{j\omega})\big|_{\omega=2\pi k/N}\quad(x[n]\text{ 長度}\le N)
```

**一句話：z 轉換是最一般的；把 $`z`$ 限制在單位圓上就是 DTFT；再把單位圓等分成 $`N`$ 點取樣就是 DFT。**

## 1. DTFT 重要轉換對（O&S Table 2.3） （證明：附錄第 1 節）

| 序列 $`x[n]`$ | DTFT $`X(e^{j\omega})`$ | 備註 |
|---|---|---|
| $`\delta[n]`$ | $`1`$ | 全頻帶、平坦 |
| $`\delta[n-n_0]`$ | $`e^{-j\omega n_0}`$ | 延遲 = 線性相位 |
| $`1`$（所有 $`n`$） | $`\sum_k 2\pi\,\delta(\omega-2\pi k)`$ | DC |
| $`e^{j\omega_0 n}`$ | $`\sum_k 2\pi\,\delta(\omega-\omega_0-2\pi k)`$ | 單一頻率 |
| $`\cos(\omega_0 n)`$ | $`\sum_k \pi\,[\delta(\omega-\omega_0-2\pi k)+\delta(\omega+\omega_0-2\pi k)]`$ | 兩根線 |
| $`a^nu[n]`$，$`\vert a\vert<1`$ | $`\dfrac{1}{1-ae^{-j\omega}}`$ | 一階 IIR（Day-4 例子 B） |
| $`(n+1)a^nu[n]`$，$`\vert a\vert<1`$ | $`\dfrac{1}{(1-ae^{-j\omega})^2}`$ | 重根 |
| $`u[n]`$ | $`\dfrac{1}{1-e^{-j\omega}}+\sum_k\pi\,\delta(\omega-2\pi k)`$ | 不絕對可和，含 $`\delta`$ |
| $`\dfrac{\sin(\omega_c n)}{\pi n}`$ | $`\begin{cases}1,&\vert\omega\vert<\omega_c\\0,&\omega_c<\vert\omega\vert\le\pi\end{cases}`$ | **理想低通**（Ch. 7 視窗法起點） |
| $`x[n]=\begin{cases}1,&0\le n\le M\\0,&\text{else}\end{cases}`$ | $`\dfrac{\sin[\omega(M+1)/2]}{\sin(\omega/2)}\,e^{-j\omega M/2}`$ | 矩形窗、移動平均（Day-4 例子 A） |

### 1.1 DTFT 性質（O&S Table 2.2，必記）

| 性質 | 時域 | 頻域 |
|---|---|---|
| 線性 | $`ax_1[n]+bx_2[n]`$ | $`aX_1(e^{j\omega})+bX_2(e^{j\omega})`$ |
| 時移 | $`x[n-n_d]`$ | $`e^{-j\omega n_d}X(e^{j\omega})`$ |
| 頻移（調變） | $`e^{j\omega_0 n}x[n]`$ | $`X(e^{j(\omega-\omega_0)})`$ |
| 時間反轉 | $`x[-n]`$ | $`X(e^{-j\omega})`$ |
| 頻域微分 | $`nx[n]`$ | $`j\dfrac{dX(e^{j\omega})}{d\omega}`$ |
| **卷積** | $`x[n]*h[n]`$ | $`X(e^{j\omega})H(e^{j\omega})`$ |
| 相乘（視窗） | $`x[n]w[n]`$ | $`\dfrac{1}{2\pi}\displaystyle\int_{-\pi}^{\pi}X(e^{j\theta})W(e^{j(\omega-\theta)})d\theta`$（週期卷積） |
| Parseval | $`\sum_n\vert x[n]\vert^2`$ | $`=\dfrac{1}{2\pi}\displaystyle\int_{-\pi}^{\pi}\vert X(e^{j\omega})\vert^2d\omega`$ |
| 實數序列 | $`x[n]\in\mathbb{R}`$ | $`X(e^{-j\omega})=X^*(e^{j\omega})`$：$`\vert X\vert`$ 偶、$`\angle X`$ 奇 |

## 2. DFT／IDFT （證明：附錄第 2 節）

### 2.1 定義與符號

```math
X[k]=\sum_{n=0}^{N-1}x[n]\,e^{-j\frac{2\pi}{N}kn},\qquad
x[n]=\frac{1}{N}\sum_{k=0}^{N-1}X[k]\,e^{+j\frac{2\pi}{N}kn},\qquad 0\le n,k\le N-1
```

- $`\frac{1}{N}`$ 放在反轉換（O&S 與 numpy 慣例）。請同學自己驗證：把 IDFT 代回 DFT，用 $`\sum_{n=0}^{N-1}W_N^{(k-m)n}=N\,\delta[k-m]`$（$`0\le k,m\le N-1`$）即得恆等。
- 第 $`k`$ 格對應的數位頻率 $`\omega_k=2\pi k/N`$；若取樣率 $`f_s`$，實際頻率 $`f_k=k\,f_s/N`$（頻率解析度 $`f_s/N`$）。
- **DFT 隱含週期延拓**：所有「移位」都是**圓周移位** $`x[((n-m))_N]`$，所有「卷積」都是**圓周卷積**。

### 2.2 DFT 重要轉換對

| $`x[n]`$，$`0\le n\le N-1`$ | $`X[k]`$，$`0\le k\le N-1`$ | 備註 |
|---|---|---|
| $`\delta[n]`$ | $`1`$ | |
| $`\delta[((n-m))_N]`$ | $`W_N^{km}=e^{-j2\pi km/N}`$ | 圓周移位 |
| $`1`$ | $`N\,\delta[k]`$ | 全部能量在 DC |
| $`e^{j2\pi k_0 n/N}`$ | $`N\,\delta[k-k_0]`$ | 剛好落在格點 → 單一根線 |
| $`\cos(2\pi k_0 n/N)`$ | $`\dfrac{N}{2}\left(\delta[k-k_0]+\delta[k-(N-k_0)]\right)`$ | 對稱出現在 $`k_0`$ 與 $`N-k_0`$ |
| $`a^n`$，$`0\le n\le N-1`$ | $`\dfrac{1-a^N}{1-aW_N^{k}}`$ | 幾何級數有限和 |
| 矩形 $`x[n]=1`$，$`0\le n\le L-1`$（$`L\le N`$） | $`\dfrac{1-W_N^{kL}}{1-W_N^{k}}=\dfrac{\sin(\pi kL/N)}{\sin(\pi k/N)}e^{-j\pi k(L-1)/N}`$ | 就是矩形窗 DTFT 在 $`\omega_k`$ 的取樣 |

**課堂討論點**：$`\cos(2\pi f_0 n/f_s)`$ 若 $`f_0`$ 不是 $`f_s/N`$ 的整數倍，DFT 不會只有兩根線，而是「漏」到鄰近格點（spectral leakage）；這是 Day-3 看到的視窗效應，Ch. 8 會正式講。

### 2.3 DFT 性質（O&S Table 8.2）

| 性質 | 時域 | 頻域 |
|---|---|---|
| 線性 | $`ax_1[n]+bx_2[n]`$ | $`aX_1[k]+bX_2[k]`$ |
| 圓周時移 | $`x[((n-m))_N]`$ | $`W_N^{km}X[k]`$ |
| 圓周頻移 | $`W_N^{-\ell n}x[n]`$ | $`X[((k-\ell))_N]`$ |
| 對偶 | $`X[n]`$ | $`N\,x[((-k))_N]`$ |
| **圓周卷積** | $`\sum_{m=0}^{N-1}x_1[m]x_2[((n-m))_N]`$ | $`X_1[k]X_2[k]`$ |
| 相乘 | $`x_1[n]x_2[n]`$ | $`\dfrac{1}{N}\sum_{\ell}X_1[\ell]X_2[((k-\ell))_N]`$ |
| 共軛對稱（實數 $`x`$） | $`x[n]\in\mathbb{R}`$ | $`X[((-k))_N]=X^*[k]`$ → 只需存 $`k=0..N/2`$（`rfft`） |
| Parseval | $`\sum_{n=0}^{N-1}\vert x[n]\vert^2`$ | $`=\dfrac{1}{N}\sum_{k=0}^{N-1}\vert X[k]\vert^2`$ |

**圓周卷積 vs. 線性卷積**：長 $`L`$ 與長 $`P`$ 的序列做線性卷積長 $`L+P-1`$；要用 DFT 算線性卷積，必須先補零到 $`N\ge L+P-1`$，否則尾巴會「繞回來」疊到前面（time aliasing）。這是 Team Project 用 FFT 做快速卷積（overlap-add）的核心規則。

## 2.5 ★ 卷積定理：時域卷積 ↔ 頻域相乘（證明：附錄第 2.6 與 2.9 節）

這是整門課最重要的一條，三個轉換各有一個版本：

| 轉換 | 時域 | 變換域 | 附帶條件 |
|---|---|---|---|
| DTFT | $`y[n]=x[n]*h[n]=\sum_kx[k]h[n-k]`$ | $`Y(e^{j\omega})=X(e^{j\omega})H(e^{j\omega})`$ | 兩者 DTFT 存在（絕對可和） |
| z | $`y[n]=x[n]*h[n]`$ | $`Y(z)=X(z)H(z)`$ | ROC $`\supseteq R_x\cap R_h`$ |
| DFT | $`y[n]=x_1[n]\circledast_Nx_2[n]=\sum_{m=0}^{N-1}x_1[m]x_2[((n-m))_N]`$（**圓周**卷積） | $`Y[k]=X_1[k]X_2[k]`$ | 要等於線性卷積需 $`N\ge L+P-1`$ |

**為什麼會這樣**（Day-4 第 2 節的 eigenfunction 觀點）：$`e^{j\omega n}`$ 進 LTI 系統出來還是 $`e^{j\omega n}`$，只被乘上 $`H(e^{j\omega})`$。反 DTFT 把 $`x[n]`$ 寫成一堆 $`e^{j\omega n}`$ 的疊加，每一個頻率各自被乘上 $`H(e^{j\omega})`$，疊加回去就是 $`X(e^{j\omega})H(e^{j\omega})`$。卷積定理只是把這句話寫成公式。

**三個直接後果**

1. **串接系統**：$`h_1*h_2\leftrightarrow H_1H_2`$，LTI 串接順序可以交換，總頻率響應是相乘、相位是相加。
2. **系統函數**：$`H(z)=Y(z)/X(z)`$ 才有意義；LCCDE 兩邊 z 轉換後能「除過去」就是因為卷積變成了相乘。
3. **快速卷積**：長 $`L`$ 的 $`x`$ 與長 $`P`$ 的 $`h`$，補零到 $`N\ge L+P-1`$，`ifft(fft(x,N)*fft(h,N))` 的前 $`L+P-1`$ 點就是 `np.convolve(x,h)`，運算量 $`O(N\log N)`$ 而非 $`O(LP)`$（Team Project 的 overlap-add）。

**例**：兩個 3 點移動平均串接。$`h_1=h_2=\tfrac13[1,1,1]`$，$`H_1(e^{j\omega})=H_2(e^{j\omega})=\tfrac13\dfrac{\sin(3\omega/2)}{\sin(\omega/2)}e^{-j\omega}`$（第 1 節矩形窗，$`M=2`$）。
時域：$`h_1*h_2=\tfrac19[1,2,3,2,1]`$（三角窗）。
頻域：$`H_1H_2=\tfrac19\dfrac{\sin^2(3\omega/2)}{\sin^2(\omega/2)}e^{-j2\omega}`$。
檢查 $`\omega=0`$：時域係數和 $`\tfrac19\cdot9=1`$，頻域 $`\tfrac19\cdot3^2=1`$ ✓。檢查 $`\omega=2\pi/3`$：$`\sin(\pi)=0`$ → 零點，兩個系統各有一個零點在此，串接後變成二階零點，$`\vert H\vert`$ 在該處「更平」。

**對偶**：時域相乘 ↔ 頻域（週期）卷積 $`\tfrac{1}{2\pi}X\circledast W`$。這就是視窗效應：截斷 $`x[n]w[n]`$ 讓頻譜被窗的主瓣抹開、旁瓣洩漏（Day-3、Ch. 7、Ch. 8）。

## 3. z 轉換重要轉換對（O&S Table 3.1） （證明：附錄第 3 節）

ROC 一定要跟著寫。**同一個 $`X(z)`$ 配不同 ROC 是不同的序列。**

| 序列 | $`X(z)`$ | ROC |
|---|---|---|
| $`\delta[n]`$ | $`1`$ | 整個 z 平面 |
| $`\delta[n-m]`$ | $`z^{-m}`$ | 全平面，除了 $`z=0`$（$`m>0`$）或 $`z=\infty`$（$`m<0`$） |
| $`u[n]`$ | $`\dfrac{1}{1-z^{-1}}`$ | $`\vert z\vert>1`$ |
| $`-u[-n-1]`$ | $`\dfrac{1}{1-z^{-1}}`$ | $`\vert z\vert<1`$ |
| $`a^nu[n]`$ | $`\dfrac{1}{1-az^{-1}}`$ | $`\vert z\vert>\vert a\vert`$（右邊、因果） |
| $`-a^nu[-n-1]`$ | $`\dfrac{1}{1-az^{-1}}`$ | $`\vert z\vert<\vert a\vert`$（左邊、反因果） |
| $`na^nu[n]`$ | $`\dfrac{az^{-1}}{(1-az^{-1})^2}`$ | $`\vert z\vert>\vert a\vert`$ |
| $`-na^nu[-n-1]`$ | $`\dfrac{az^{-1}}{(1-az^{-1})^2}`$ | $`\vert z\vert<\vert a\vert`$ |
| $`\cos(\omega_0 n)u[n]`$ | $`\dfrac{1-\cos(\omega_0)z^{-1}}{1-2\cos(\omega_0)z^{-1}+z^{-2}}`$ | $`\vert z\vert>1`$ |
| $`\sin(\omega_0 n)u[n]`$ | $`\dfrac{\sin(\omega_0)z^{-1}}{1-2\cos(\omega_0)z^{-1}+z^{-2}}`$ | $`\vert z\vert>1`$ |
| $`r^n\cos(\omega_0 n)u[n]`$ | $`\dfrac{1-r\cos(\omega_0)z^{-1}}{1-2r\cos(\omega_0)z^{-1}+r^2z^{-2}}`$ | $`\vert z\vert>r`$（極點 $`re^{\pm j\omega_0}`$，共振器／biquad） |
| $`r^n\sin(\omega_0 n)u[n]`$ | $`\dfrac{r\sin(\omega_0)z^{-1}}{1-2r\cos(\omega_0)z^{-1}+r^2z^{-2}}`$ | $`\vert z\vert>r`$ |
| $`a^n`$，$`0\le n\le N-1`$ | $`\dfrac{1-a^Nz^{-N}}{1-az^{-1}}`$ | $`\vert z\vert>0`$（有限長 → 全平面除原點） |

### 3.1 ROC 四條規則

1. ROC 是以原點為中心的環狀區域，**不含極點**。
2. 有限長序列：全平面（可能除了 $`0`$ 或 $`\infty`$）。
3. 右邊序列（因果）：ROC 在最外側極點之外 $`\vert z\vert>r_{\max}`$；左邊序列：在最內側極點之內；雙邊序列：環狀。
4. **穩定 ⇔ ROC 包含單位圓；因果且穩定 ⇔ 所有極點在單位圓內**（對應 Day-4 第 5.2 節的表）。

### 3.2 z 轉換性質（O&S Table 3.2）

| 性質 | 時域 | z 域 | ROC |
|---|---|---|---|
| 線性 | $`ax_1[n]+bx_2[n]`$ | $`aX_1(z)+bX_2(z)`$ | 至少 $`R_1\cap R_2`$ |
| **時移** | $`x[n-n_0]`$ | $`z^{-n_0}X(z)`$ | 同 $`R_x`$，可能增減 $`0`$／$`\infty`$ |
| 指數加權 | $`z_0^nx[n]`$ | $`X(z/z_0)`$ | $`\vert z_0\vert R_x`$ |
| z 域微分 | $`nx[n]`$ | $`-z\dfrac{dX(z)}{dz}`$ | $`R_x`$ |
| 共軛 | $`x^*[n]`$ | $`X^*(z^*)`$ | $`R_x`$ |
| 時間反轉 | $`x[-n]`$ | $`X(1/z)`$ | $`1/R_x`$ |
| **卷積** | $`x_1[n]*x_2[n]`$ | $`X_1(z)X_2(z)`$ | 至少 $`R_1\cap R_2`$ |
| 初值定理（因果） | $`x[0]`$ | $`=\lim_{z\to\infty}X(z)`$ | |

時移＋線性＋卷積三條，就足以把任何 LCCDE 變成 $`H(z)=\dfrac{\sum_k b_kz^{-k}}{\sum_k a_kz^{-k}}`$，再從 $`H(z)`$ 反推 $`h[n]`$。

## 4. 反 z 轉換：三種方法 （證明：附錄第 4 節）

### 4.1 查表（最常用）

把 $`X(z)`$ 整理成表中形式。例：$`X(z)=\dfrac{3z^{-1}}{1-0.5z^{-1}}`$，$`\vert z\vert>0.5`$
→ $`3z^{-1}\cdot\dfrac{1}{1-0.5z^{-1}}`$ → 時移一點 → $`x[n]=3\,(0.5)^{n-1}u[n-1]`$。

### 4.2 部分分式（有理函數、極點相異）

```math
X(z)=\frac{B(z)}{A(z)}=\sum_{k=1}^{N}\frac{A_k}{1-d_kz^{-1}},\qquad
A_k=\left(1-d_kz^{-1}\right)X(z)\Big|_{z=d_k}
```

（若分子階數 $`\ge`$ 分母階數，先做長除法分出多項式部分 $`\sum_r B_r z^{-r}`$，對應 $`\delta[n-r]`$。）

每一項依 ROC 選右邊或左邊：

- ROC 在 $`\vert d_k\vert`$ 外 → $`A_kd_k^nu[n]`$
- ROC 在 $`\vert d_k\vert`$ 內 → $`-A_kd_k^nu[-n-1]`$

**例**：$`X(z)=\dfrac{1}{(1-\frac12z^{-1})(1-\frac14z^{-1})}`$

```math
A_1=\frac{1}{1-\frac14\cdot 2}=2,\qquad A_2=\frac{1}{1-\frac12\cdot 4}=-1
\quad\Rightarrow\quad X(z)=\frac{2}{1-\frac12z^{-1}}-\frac{1}{1-\frac14z^{-1}}
```

| ROC | $`x[n]`$ | 性質 |
|---|---|---|
| $`\vert z\vert>\frac12`$ | $`2(\tfrac12)^nu[n]-(\tfrac14)^nu[n]`$ | 因果、穩定 |
| $`\frac14<\vert z\vert<\frac12`$ | $`-2(\tfrac12)^nu[-n-1]-(\tfrac14)^nu[n]`$ | 雙邊、穩定？（單位圓不在 ROC → 不穩定） |
| $`\vert z\vert<\frac14`$ | $`-2(\tfrac12)^nu[-n-1]+(\tfrac14)^nu[-n-1]`$ | 反因果、不穩定 |

重根 $`(1-dz^{-1})^s`$：補上 $`\dfrac{C_m}{(1-dz^{-1})^m}`$ 項，用 $`na^nu[n]\leftrightarrow\dfrac{az^{-1}}{(1-az^{-1})^2}`$ 這組查表。

### 4.3 長除法／冪級數展開

直接把 $`X(z)`$ 展成 $`\sum x[n]z^{-n}`$，係數就是 $`x[n]`$。因果（ROC 在外）→ 用 $`z^{-1}`$ 的升冪除；反因果 → 用 $`z`$ 的升冪除。適合只要前幾項 $`h[0],h[1],\dots`$，或 $`X(z)`$ 不是有理函數時（例：$`\log(1+az^{-1})`$ 用泰勒展開）。

**例**：$`\dfrac{1}{1-az^{-1}}=1+az^{-1}+a^2z^{-2}+\cdots`$ → $`h[n]=a^nu[n]`$，和 Day-4 例子 B 一致。

## 5. 把四張表串起來：一個例子走到底

RC 低通離散化（HW1 式 (8)）得到 $`y[n]=(1-\alpha)y[n-1]+\alpha x[n]`$。

1. **z 轉換**（時移性質）：$`H(z)=\dfrac{\alpha}{1-(1-\alpha)z^{-1}}`$，極點 $`z=1-\alpha`$，因果 → ROC $`\vert z\vert>1-\alpha`$。
2. **反 z**（查表）：$`h[n]=\alpha(1-\alpha)^nu[n]`$。
3. **DTFT**（$`z=e^{j\omega}`$，$`0<\alpha<2`$ 時單位圓在 ROC 內）：$`H(e^{j\omega})=\dfrac{\alpha}{1-(1-\alpha)e^{-j\omega}}`$，$`\vert H(e^{j0})\vert=1`$、$`\vert H(e^{j\pi})\vert=\dfrac{\alpha}{2-\alpha}`$ → 低通。
4. **DFT**：取 $`N`$ 點 $`h[n]`$（截斷）做 `np.fft.fft`，得到的 $`H[k]`$ 就是上式在 $`\omega_k=2\pi k/N`$ 的取樣（截斷誤差 $`\propto(1-\alpha)^N`$）。

## 6. 課堂練習（不需繳交）

1. 求 $`x[n]=(\tfrac13)^nu[n]+2^nu[-n-1]`$ 的 z 轉換與 ROC；它穩定嗎？
2. $`H(z)=\dfrac{1-z^{-1}}{1-0.9z^{-1}}`$，因果。求 $`h[n]`$，並說明它是低通還是高通（提示：看 $`H(e^{j0})`$ 與 $`H(e^{j\pi})`$）。
3. $`N=8`$，$`x[n]=\cos(2\pi\cdot 2n/8)`$ 與 $`x[n]=\cos(2\pi\cdot 2.5n/8)`$，分別用 `np.fft.fft` 算 $`\vert X[k]\vert`$，解釋為什麼一個只有兩根線、一個不是。
4. 長 4 與長 3 的序列各任取一組，用 $`N=4`$ 與 $`N=6`$ 的 DFT 做「相乘後 IDFT」，和 `np.convolve` 比較，指出哪一個發生 time aliasing。

## 7. 課後待辦（第 5 週）

1. 把本講義第 1–3 節三張表親手抄一遍（期中考閉卷，這幾張表是基本配備）。
2. 預習 O&S Ch. 4.1–4.4：取樣定理、混疊、重建。
3. HW1 今日 18:00 截止。

---

[← day04_frequency_response_transient.md](day04_frequency_response_transient.md) ｜ [講義目錄](README.md)
