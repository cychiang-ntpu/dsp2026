/* dsp_util.c — 共用 DSP 元件。
 *
 * 本檔所有函式的本體都留空（標示 TODO），由各組依註解中的數學式完成。
 * 完成一個函式後，把該函式的 TODO 與暫時的 return 值換成你的實作。
 * 規定：不得呼叫外部 DSP 函式庫（FFTW、KissFFT、libsamplerate…）。
 */
#include <stdlib.h>
#include <math.h>
#include "fx.h"
#include "dsp_util.h"

/* ====================================================================
 * 二階 IIR（biquad）
 *
 * 系統函數：
 *
 *            b0 + b1 z^-1 + b2 z^-2
 *   H(z) = --------------------------
 *            a0 + a1 z^-1 + a2 z^-2
 *
 * 差分方程（係數已除以 a0）：
 *
 *   y[n] = b0 x[n] + b1 x[n-1] + b2 x[n-2] - a1 y[n-1] - a2 y[n-2]
 *
 * 係數公式（RBJ Audio EQ Cookbook，由類比原型經 bilinear transform 並做頻率預扭曲）：
 *
 *   w0 = 2π f0 / fs，  α = sin(w0) / (2Q)，  A = 10^(gain_dB / 40)（shelving 用）
 *
 *   低通     b0 = (1 - cos w0)/2   b1 =  1 - cos w0     b2 = (1 - cos w0)/2
 *            a0 = 1 + α            a1 = -2 cos w0       a2 = 1 - α
 *
 *   高通     b0 = (1 + cos w0)/2   b1 = -(1 + cos w0)   b2 = (1 + cos w0)/2
 *            a0, a1, a2 同低通
 *
 *   帶通     b0 = α                b1 = 0               b2 = -α        （峰值增益 0 dB）
 *            a0, a1, a2 同低通
 *
 *   低頻 shelving
 *            b0 =    A[(A+1) - (A-1)cos w0 + 2√A α]
 *            b1 =  2A[(A-1) - (A+1)cos w0]
 *            b2 =    A[(A+1) - (A-1)cos w0 - 2√A α]
 *            a0 =      (A+1) + (A-1)cos w0 + 2√A α
 *            a1 =  -2[(A-1) + (A+1)cos w0]
 *            a2 =      (A+1) + (A-1)cos w0 - 2√A α
 *
 *   高頻 shelving
 *            b0 =    A[(A+1) + (A-1)cos w0 + 2√A α]
 *            b1 = -2A[(A-1) + (A+1)cos w0]
 *            b2 =    A[(A+1) + (A-1)cos w0 - 2√A α]
 *            a0 =      (A+1) - (A-1)cos w0 + 2√A α
 *            a1 =   2[(A-1) - (A+1)cos w0]
 *            a2 =      (A+1) - (A-1)cos w0 - 2√A α
 *
 * 架構文件須交代：極點位置與穩定條件（a1、a2 的 stability triangle）、
 * 你選用的結構（direct form I / II / transposed II）與理由。
 *
 * 參考文獻：
 *   [1] R. Bristow-Johnson, "Cookbook formulae for audio EQ biquad filter coefficients."
 *       （W3C Audio EQ Cookbook：https://www.w3.org/TR/audio-eq-cookbook/）
 *   [2] A. V. Oppenheim and R. W. Schafer, Discrete-Time Signal Processing, 3rd ed.,
 *       Sec. 6.3（IIR 的基本結構）、Sec. 7.2（bilinear transformation）。
 *   [3] U. Zölzer (ed.), DAFX: Digital Audio Effects, 2nd ed., Wiley, 2011, Ch. 2（Filters）。
 * ==================================================================== */

int biquad_design(biquad_t *bq, biquad_type_t type, double fs, double f0, double Q, double gain_db)
{
    /* TODO: 依上面的公式計算 b0, b1, b2, a1, a2（記得除以 a0），並清除狀態。
     *       檢查 0 < f0 < fs/2、Q > 0，不合法時回傳 FX_EARG。 */
    (void)bq; (void)type; (void)fs; (void)f0; (void)Q; (void)gain_db;
    return FX_ENOTIMPL;
}

void biquad_reset(biquad_t *bq)
{
    /* TODO: 狀態變數歸零（initial rest）。 */
    (void)bq;
}

double biquad_tick(biquad_t *bq, double x)
{
    /* TODO: 實作差分方程，更新狀態並回傳 y[n]。
     *
     * Transposed direct form II（只需兩個狀態變數）：
     *   y[n]  = b0 x[n] + z1[n-1]
     *   z1[n] = b1 x[n] - a1 y[n] + z2[n-1]
     *   z2[n] = b2 x[n] - a2 y[n]
     */
    (void)bq; (void)x;
    return 0.0;
}

/* ====================================================================
 * 延遲線（circular buffer）
 *
 * 實現 z^-D。用長度 len 的環狀緩衝區與寫入指標 w：
 *
 *   寫入：buf[w] = x[n]，w = (w + 1) mod len
 *   讀取：x[n - D] = buf[(w - 1 - D) mod len]，0 ≤ D ≤ len - 1
 *         （注意 C 的 % 對負數的行為；size_t 相減會 underflow）
 *
 * 非整數延遲 D = i + f（i 為整數部分，0 ≤ f < 1）：
 *
 *   線性內插    x(n - D) ≈ (1 - f) x[n - i] + f x[n - i - 1]
 *
 * 線性內插等於一個兩點 FIR，H(e^jω) = (1-f) + f e^-jω，高頻會衰減（f = 0.5 時 ω = π 為零點）。
 * 進階可改用 Lagrange 三次內插或一階 all-pass 內插，並在架構文件比較頻率響應。
 *
 * 參考文獻：
 *   [4] T. I. Laakso, V. Välimäki, M. Karjalainen, and U. K. Laine,
 *       "Splitting the unit delay: Tools for fractional delay filter design,"
 *       IEEE Signal Processing Magazine, vol. 13, no. 1, pp. 30–60, Jan. 1996.
 *   [5] J. O. Smith III, Physical Audio Signal Processing, online book,
 *       https://ccrma.stanford.edu/~jos/pasp/ （Delay Lines、Delay-Line Interpolation）。
 * ==================================================================== */

int delay_init(delayline_t *d, size_t max_delay)
{
    /* TODO: 配置 max_delay + 2 個取樣值（多一格給內插用）並清為 0。 */
    (void)d; (void)max_delay;
    return FX_ENOTIMPL;
}

void delay_free(delayline_t *d)
{
    /* TODO: 釋放緩衝區。 */
    (void)d;
}

void delay_write(delayline_t *d, double x)
{
    /* TODO */
    (void)d; (void)x;
}

double delay_read(const delayline_t *d, size_t D)
{
    /* TODO */
    (void)d; (void)D;
    return 0.0;
}

double delay_read_frac(const delayline_t *d, double D)
{
    /* TODO: 非整數延遲（線性內插或更高階）。 */
    (void)d; (void)D;
    return 0.0;
}

/* ====================================================================
 * 視窗與 FIR（視窗法）
 *
 * 視窗（n = 0, 1, ..., N-1，令 M = N - 1）：
 *
 *   Rectangular   w[n] = 1
 *   Hann          w[n] = 0.5  - 0.5  cos(2πn/M)
 *   Hamming       w[n] = 0.54 - 0.46 cos(2πn/M)
 *   Blackman      w[n] = 0.42 - 0.5  cos(2πn/M) + 0.08 cos(4πn/M)
 *
 * 線性相位低通（長度 P，延遲 (P-1)/2）：
 *
 *            sin[ωc (n - (P-1)/2)]
 *   h[n] = ------------------------- · w[n]，  n = 0..P-1；n = (P-1)/2 時取極限值 ωc/π
 *              π (n - (P-1)/2)
 *
 * 高通可由 δ[n - (P-1)/2] - h_lp[n] 得到（P 為奇數），帶通為兩個低通相減。
 *
 * 直接卷積：
 *
 *   y[n] = Σ_{k=0}^{P-1} h[k] x[n-k]
 *
 * 每個輸出取樣值 P 次乘法。濾波器很長時改用 FFT overlap-add（HW4）。
 *
 * 參考文獻：
 *   [2] Oppenheim & Schafer, Sec. 7.5（Design of FIR Filters by Windowing）、Table 7.2。
 *   [6] F. J. Harris, "On the use of windows for harmonic analysis with the discrete
 *       Fourier transform," Proc. IEEE, vol. 66, no. 1, pp. 51–83, Jan. 1978.
 * ==================================================================== */

int window_fill(double *w, int N, window_type_t type)
{
    /* TODO */
    (void)w; (void)N; (void)type;
    return FX_ENOTIMPL;
}

int fir_design_lowpass(double *h, int P, double wc, window_type_t type)
{
    /* TODO */
    (void)h; (void)P; (void)wc; (void)type;
    return FX_ENOTIMPL;
}

int fir_filter(const double *h, int P, const double *x, double *y, size_t N, int stride)
{
    /* TODO */
    (void)h; (void)P; (void)x; (void)y; (void)N; (void)stride;
    return FX_ENOTIMPL;
}

/* ====================================================================
 * FFT（radix-2）
 *
 * DFT 與 IDFT：
 *
 *   X[k] = Σ_{n=0}^{N-1} x[n] e^{-j2πkn/N}
 *   x[n] = (1/N) Σ_{k=0}^{N-1} X[k] e^{+j2πkn/N}
 *
 * Decimation-in-time：把 x[n] 分成偶數點 g[n] = x[2n] 與奇數點 h[n] = x[2n+1]，
 * 各做 N/2 點 DFT 得 G[k]、H[k]，令 W_N = e^{-j2π/N}：
 *
 *   X[k]       = G[k] + W_N^k H[k]
 *   X[k + N/2] = G[k] - W_N^k H[k]，  k = 0..N/2-1      （butterfly）
 *
 * 原地運算的做法：先做 bit-reversal 重排，再做 log2(N) 級 butterfly。
 * 運算量 (N/2) log2(N) 次複數乘法，直接計算 DFT 則是 N^2 次。
 * IFFT 可用同一個程式：把指數的正負號反過來（或先取共軛、FFT、再取共軛），最後除以 N。
 *
 * 參考文獻：
 *   [2] Oppenheim & Schafer, Sec. 9.2（Decimation-in-Time FFT Algorithms）。
 *   [7] J. W. Cooley and J. W. Tukey, "An algorithm for the machine calculation of
 *       complex Fourier series," Mathematics of Computation, vol. 19, no. 90,
 *       pp. 297–301, 1965.
 * ==================================================================== */

int fft(double *re, double *im, int N, int inverse)
{
    /* TODO: 檢查 N 為 2 的冪次；bit-reversal；butterfly；inverse 時除以 N。 */
    (void)re; (void)im; (void)N; (void)inverse;
    return FX_ENOTIMPL;
}
