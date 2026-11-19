/* dsp_util.h — 各效果器共用的 DSP 元件。
 *
 * 這裡只有宣告與資料結構；實作在 src/dsp_util.c，**全部留空，由各組完成**。
 * 介面只是建議，可以自行增減或修改，但請同步更新架構文件。
 */
#ifndef DSP_UTIL_H
#define DSP_UTIL_H

#include <stddef.h>

/* ---------- 二階 IIR（biquad） ---------- */

typedef enum { BQ_LOWPASS, BQ_HIGHPASS, BQ_BANDPASS, BQ_LOWSHELF, BQ_HIGHSHELF } biquad_type_t;

typedef struct {
    double b0, b1, b2, a1, a2;   /* 已除以 a0：H(z) = (b0 + b1 z^-1 + b2 z^-2) / (1 + a1 z^-1 + a2 z^-2) */
    double z1, z2;               /* 狀態變數 */
} biquad_t;

/* 依類型、取樣率 fs、中心／截止頻率 f0（Hz）、Q、增益（dB，僅 shelving 使用）算出係數並清除狀態。 */
int    biquad_design(biquad_t *bq, biquad_type_t type, double fs, double f0, double Q, double gain_db);
void   biquad_reset(biquad_t *bq);
/* 輸入一個取樣值，回傳一個輸出取樣值。 */
double biquad_tick(biquad_t *bq, double x);

/* ---------- 延遲線（circular buffer） ---------- */

typedef struct {
    double *buf;
    size_t  len;   /* 緩衝區長度（最大延遲 + 1 以上） */
    size_t  w;     /* 下一個要寫入的位置 */
} delayline_t;

int    delay_init(delayline_t *d, size_t max_delay);
void   delay_free(delayline_t *d);
void   delay_write(delayline_t *d, double x);          /* 寫入 x[n] 並前進一格 */
double delay_read(const delayline_t *d, size_t D);     /* 讀取 x[n-D]，D 為整數 */
double delay_read_frac(const delayline_t *d, double D);/* 讀取 x(n-D)，D 可為非整數（內插） */

/* ---------- 視窗與 FIR ---------- */

typedef enum { WIN_RECT, WIN_HANN, WIN_HAMMING, WIN_BLACKMAN } window_type_t;

int window_fill(double *w, int N, window_type_t type);

/* 視窗法設計長度 P 的線性相位低通 FIR，截止頻率 wc（rad/sample）。 */
int fir_design_lowpass(double *h, int P, double wc, window_type_t type);

/* 直接卷積：y[n] = Σ_{k=0}^{P-1} h[k] x[n-k]，n = 0..N-1（x[n] = 0 for n < 0）。
 * stride 用於交錯聲道：x[n] 存在 x[n * stride]。 */
int fir_filter(const double *h, int P, const double *x, double *y, size_t N, int stride);

/* ---------- FFT ---------- */

/* 原地（in-place）radix-2 FFT，N 必須是 2 的冪次。inverse != 0 時做 IFFT（含 1/N）。 */
int fft(double *re, double *im, int N, int inverse);

#endif
