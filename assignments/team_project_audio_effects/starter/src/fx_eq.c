/* fx_eq.c — ★ 等化器（EQ）：低通／高通／帶通／Shelving
 *
 *   eq <lowpass|highpass|bandpass|lowshelf|highshelf> <f0_Hz> [Q=0.7071] [gain_dB=0]
 *   例：eq lowpass 4000        eq lowshelf 200 0.7071 6
 *
 * 兩種做法擇一（或都做並比較）：
 *
 * (a) IIR 二階節（biquad）：
 *
 *       y[n] = b0 x[n] + b1 x[n-1] + b2 x[n-2] - a1 y[n-1] - a2 y[n-2]
 *
 *     係數公式見 src/dsp_util.c 的 biquad_design()。Q = 1/√2 時為二階 Butterworth
 *     （通帶最平坦）。更陡的滾降可以串接多個 biquad。
 *
 * (b) FIR 視窗法（線性相位，延遲 (P-1)/2 點；見 dsp_util.c 的 fir_design_lowpass()）：
 *
 *       y[n] = Σ_{k=0}^{P-1} h[k] x[n-k]
 *
 *     FIR 的過渡帶寬度約與 1/P 成正比（Hamming：Δω ≈ 8π/P），截止頻率很低時需要很長的濾波器。
 *
 * 架構文件須附：差分方程、極零點圖、|H(e^jω)| 與 ∠H(e^jω)（由你的係數算出，不是理想曲線）。
 *
 * 邊界情況：f0 ≥ fs/2、Q ≤ 0、極大的 shelving 增益（輸出削波）。
 *
 * 參考文獻：
 *   [1] R. Bristow-Johnson, "Cookbook formulae for audio EQ biquad filter coefficients,"
 *       https://www.w3.org/TR/audio-eq-cookbook/
 *   [2] Oppenheim & Schafer, Discrete-Time Signal Processing, 3rd ed., Ch. 5、Sec. 7.2、7.5。
 *   [3] U. Zölzer (ed.), DAFX: Digital Audio Effects, 2nd ed., Wiley, 2011, Ch. 2。
 */
#include <stdio.h>
#include <string.h>
#include "fx.h"
#include "dsp_util.h"

int fx_eq(const audio_t *in, audio_t *out, int argc, char **argv)
{
    if (argc < 2 || argc > 4) return FX_EARG;

    biquad_type_t type;
    if      (!strcmp(argv[0], "lowpass"))   type = BQ_LOWPASS;
    else if (!strcmp(argv[0], "highpass"))  type = BQ_HIGHPASS;
    else if (!strcmp(argv[0], "bandpass"))  type = BQ_BANDPASS;
    else if (!strcmp(argv[0], "lowshelf"))  type = BQ_LOWSHELF;
    else if (!strcmp(argv[0], "highshelf")) type = BQ_HIGHSHELF;
    else { fprintf(stderr, "eq: unknown type '%s'\n", argv[0]); return FX_EARG; }

    double f0, Q, gain_db;
    if (fx_arg_double(argc, argv, 1, 0.0,      &f0)      != FX_OK) return FX_EARG;
    if (fx_arg_double(argc, argv, 2, 0.707107, &Q)       != FX_OK) return FX_EARG;
    if (fx_arg_double(argc, argv, 3, 0.0,      &gain_db) != FX_OK) return FX_EARG;
    if (f0 <= 0.0 || f0 >= in->fs / 2.0 || Q <= 0.0) {
        fprintf(stderr, "eq: need 0 < f0 < fs/2 and Q > 0\n");
        return FX_EARG;
    }

    /* TODO: 配置 out（與輸入同長），每個聲道各用一組獨立的濾波器狀態，逐點濾波。
     *       左右聲道不可共用狀態變數。 */
    (void)out; (void)type;
    return FX_ENOTIMPL;
}
