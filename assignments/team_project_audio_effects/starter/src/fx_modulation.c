/* fx_modulation.c — 以低頻振盪器（LFO）調變的效果：tremolo、vibrato、flanger、chorus
 *
 * 共同元件：LFO
 *
 *   m[n] = sin(2π f_LFO n / fs)，f_LFO 通常 0.1–10 Hz
 *
 * 這四個都是「時變」系統（係數或延遲隨 n 改變），不是 LTI，所以沒有單一的 H(e^jω)；
 * 架構文件請用方塊圖與輸出頻譜圖（spectrogram）說明。
 *
 * ---------------------------------------------------------------------
 * tremolo <rate_Hz> <depth>                 震音：振幅調變（已實作完成，作為可以聽的範例）
 *
 *   y[n] = (1 - d/2 + (d/2) m[n]) · x[n]，  0 ≤ d ≤ 1
 *
 *   增益在 1-d 與 1 之間擺動。輸入單一弦波 A sin(ω0 n) 時，輸出頻譜在 ω0 與
 *   ω0 ± 2π f_LFO/fs 各有一根（時域相乘 ↔ 頻域卷積）：
 *   載波振幅 A(1 - d/2)，兩個旁帶振幅各 A·d/4。tests/test_fx.c 就是用這個結果驗證。
 *   這個效果不需要濾波器，是最簡單的效果器；它不計入各組必做效果器的數量。
 *
 * ---------------------------------------------------------------------
 * vibrato <rate_Hz> <width_ms>              顫音：以時變延遲調變音高
 *
 *   y[n] = x(n - D[n])，  D[n] = D0 + W m[n]，  D0 ≥ W > 0（單位：取樣點，可為非整數）
 *
 *   延遲在變化時，讀取指標相對寫入指標移動，等同局部改變取樣率，
 *   瞬時音高比為 1 - dD[n]/dn。D[n] 不是整數，必須內插（見 dsp_util.c 的 delay_read_frac()）。
 *
 * ---------------------------------------------------------------------
 * flanger <rate_Hz> <depth_ms> [feedback=0] [mix=0.5]
 *
 *   y[n] = x[n] + mix · x(n - D[n])  （無回授）
 *   D[n] 在約 1–10 ms 之間擺動。
 *
 *   D 固定時是 FIR comb：H(e^jω) = 1 + mix · e^-jωD，零點（notch）在 ω = (2k+1)π/D；
 *   D 隨時間改變，notch 就在頻譜上掃動，產生噴射機似的聲音。
 *   加回授：把延遲線的輸出乘上 feedback 再加回延遲線輸入（|feedback| < 1 才穩定）。
 *
 * ---------------------------------------------------------------------
 * chorus <rate_Hz> <depth_ms> [mix=0.5]
 *
 *   結構同 flanger，但基本延遲較長（約 10–30 ms）、不加回授，
 *   通常用 2–3 個 LFO 相位／頻率不同的 voice 相加，模擬多人合奏的些微音高與時間差。
 *
 * 邊界情況：rate ≤ 0、depth 使延遲變成負值、延遲超過延遲線長度、
 * 左右聲道 LFO 是否同相（不同相可做出立體聲展寬）。
 *
 * 參考文獻：
 *   [10] J. Dattorro, "Effect design, Part 2: Delay-line modulation and chorus,"
 *        Journal of the Audio Engineering Society, vol. 45, no. 10, pp. 764–788, 1997.
 *   [4]  T. I. Laakso et al., "Splitting the unit delay," IEEE Signal Processing Magazine,
 *        vol. 13, no. 1, pp. 30–60, 1996.
 *   [3]  U. Zölzer (ed.), DAFX: Digital Audio Effects, 2nd ed., Wiley, 2011,
 *        Ch. 2（delay-based effects）、Ch. 3（modulators）。
 *   [2]  Oppenheim & Schafer, Discrete-Time Signal Processing, 3rd ed.,
 *        Sec. 2.9（調變／windowing 定理）、Sec. 4.5（非整數延遲）。
 */
#include <stdio.h>
#include <math.h>
#include "fx.h"
#include "dsp_util.h"

int fx_tremolo(const audio_t *in, audio_t *out, int argc, char **argv)
{
    double rate, depth;
    if (argc != 2) return FX_EARG;
    if (fx_arg_double(argc, argv, 0, 0.0, &rate)  != FX_OK) return FX_EARG;
    if (fx_arg_double(argc, argv, 1, 0.0, &depth) != FX_OK) return FX_EARG;
    if (rate <= 0.0 || depth < 0.0 || depth > 1.0) {
        fprintf(stderr, "tremolo: need rate_Hz > 0 and 0 <= depth <= 1\n");
        return FX_EARG;
    }

    if (audio_alloc(out, in->fs, in->ch, in->frames) != FX_OK) return FX_ENOMEM;

    for (size_t n = 0; n < in->frames; n++) {
        double m = sin(2.0 * M_PI * rate * (double)n / in->fs);   /* LFO：m[n] */
        double g = 1.0 - depth / 2.0 + (depth / 2.0) * m;         /* 增益在 1-d 與 1 之間擺動 */
        for (int c = 0; c < in->ch; c++)                          /* 兩聲道用同一個 LFO 相位 */
            out->data[n * in->ch + c] = g * in->data[n * in->ch + c];
    }
    return FX_OK;
}

int fx_vibrato(const audio_t *in, audio_t *out, int argc, char **argv)
{
    double rate, width_ms;
    if (argc != 2) return FX_EARG;
    if (fx_arg_double(argc, argv, 0, 0.0, &rate)     != FX_OK) return FX_EARG;
    if (fx_arg_double(argc, argv, 1, 0.0, &width_ms) != FX_OK) return FX_EARG;
    if (rate <= 0.0 || width_ms <= 0.0) {
        fprintf(stderr, "vibrato: need rate_Hz > 0 and width_ms > 0\n");
        return FX_EARG;
    }

    /* TODO */
    (void)in; (void)out;
    return FX_ENOTIMPL;
}

int fx_flanger(const audio_t *in, audio_t *out, int argc, char **argv)
{
    double rate, depth_ms, feedback, mix;
    if (argc < 2 || argc > 4) return FX_EARG;
    if (fx_arg_double(argc, argv, 0, 0.0, &rate)     != FX_OK) return FX_EARG;
    if (fx_arg_double(argc, argv, 1, 0.0, &depth_ms) != FX_OK) return FX_EARG;
    if (fx_arg_double(argc, argv, 2, 0.0, &feedback) != FX_OK) return FX_EARG;
    if (fx_arg_double(argc, argv, 3, 0.5, &mix)      != FX_OK) return FX_EARG;
    if (rate <= 0.0 || depth_ms <= 0.0 || feedback <= -1.0 || feedback >= 1.0 || mix < 0.0 || mix > 1.0) {
        fprintf(stderr, "flanger: need rate_Hz > 0, depth_ms > 0, |feedback| < 1, 0 <= mix <= 1\n");
        return FX_EARG;
    }

    /* TODO */
    (void)in; (void)out;
    return FX_ENOTIMPL;
}

int fx_chorus(const audio_t *in, audio_t *out, int argc, char **argv)
{
    double rate, depth_ms, mix;
    if (argc < 2 || argc > 3) return FX_EARG;
    if (fx_arg_double(argc, argv, 0, 0.0, &rate)     != FX_OK) return FX_EARG;
    if (fx_arg_double(argc, argv, 1, 0.0, &depth_ms) != FX_OK) return FX_EARG;
    if (fx_arg_double(argc, argv, 2, 0.5, &mix)      != FX_OK) return FX_EARG;
    if (rate <= 0.0 || depth_ms <= 0.0 || mix < 0.0 || mix > 1.0) {
        fprintf(stderr, "chorus: need rate_Hz > 0, depth_ms > 0, 0 <= mix <= 1\n");
        return FX_EARG;
    }

    /* TODO */
    (void)in; (void)out;
    return FX_ENOTIMPL;
}
