/* fx_reverb.c — 殘響（Reverb）：Schroeder comb + all-pass
 *
 *   reverb <rt60_s> [mix=0.3]
 *   例：reverb 0.8        殘響時間 0.8 秒
 *
 * Schroeder 殘響器：N 個並聯的回授 comb filter，後面串接數個 all-pass filter。
 *
 *              ┌─ comb 1 ─┐
 *   x[n] ──┬──┼─ comb 2 ─┼── Σ ── all-pass 1 ── all-pass 2 ── r[n]
 *          │   ├─ comb 3 ─┤
 *          │   └─ comb 4 ─┘
 *          └────────────────────────────────────────── 與 r[n] 依 mix 混合 → y[n]
 *
 *   y[n] = (1 - mix) x[n] + mix · r[n]
 *
 * 回授 comb（延遲 D_i、增益 g_i）：
 *
 *   c[n] = x[n - D_i] + g_i c[n - D_i]          H(z) = z^-D / (1 - g z^-D)
 *
 *   每繞一圈（D_i 點）振幅乘 g_i。要在 T60 秒內衰減 60 dB：
 *
 *   g_i = 10^( -3 D_i / (fs · T60) )
 *
 * All-pass（延遲 D、增益 g）：
 *
 *   v[n] = -g u[n] + u[n - D] + g v[n - D]      H(z) = (-g + z^-D) / (1 - g z^-D)
 *
 *   |H(e^jω)| = 1（對所有 ω），只改變相位，用來增加回音密度而不改變音色。
 *   請在架構文件證明 |H| = 1，並畫出極零點（零點是極點的共軛倒數）。
 *
 * 常用參數（Schroeder 原始設計的量級，44.1 kHz 時請換算成取樣點數）：
 *   comb 延遲      29.7、37.1、41.1、43.7 ms（彼此不成整數比，避免回音重疊）
 *   all-pass 延遲  5.0、1.7 ms，g = 0.7
 *   延遲換算成點數後最好取互質的整數。
 *
 * 進階：Moorer 在 comb 的回授路徑加一階低通，模擬空氣與牆面對高頻的吸收：
 *   c[n] = x[n - D] + g · LP{c}[n - D]，LP：w[n] = (1 - d) u[n] + d w[n - 1]
 *
 * 輸出長度：延長約 T60 秒讓殘響衰減完。
 * 邊界情況：rt60 ≤ 0、mix 不在 [0, 1]、極長的 rt60（g → 1）、輸出削波。
 *
 * 參考文獻：
 *   [8] M. R. Schroeder, "Natural sounding artificial reverberation,"
 *       Journal of the Audio Engineering Society, vol. 10, no. 3, pp. 219–223, 1962.
 *   [9] J. A. Moorer, "About this reverberation business,"
 *       Computer Music Journal, vol. 3, no. 2, pp. 13–28, 1979.
 *   [2] Oppenheim & Schafer, Discrete-Time Signal Processing, 3rd ed., Sec. 5.5（All-Pass Systems）。
 *   [5] J. O. Smith III, Physical Audio Signal Processing,
 *       https://ccrma.stanford.edu/~jos/pasp/ （Schroeder Reverberators、Freeverb）。
 */
#include <stdio.h>
#include "fx.h"
#include "dsp_util.h"

int fx_reverb(const audio_t *in, audio_t *out, int argc, char **argv)
{
    double rt60, mix;
    if (argc < 1 || argc > 2) return FX_EARG;
    if (fx_arg_double(argc, argv, 0, 0.0, &rt60) != FX_OK) return FX_EARG;
    if (fx_arg_double(argc, argv, 1, 0.3, &mix)  != FX_OK) return FX_EARG;
    if (rt60 <= 0.0 || mix < 0.0 || mix > 1.0) {
        fprintf(stderr, "reverb: need rt60_s > 0 and 0 <= mix <= 1\n");
        return FX_EARG;
    }

    /* TODO: 由 rt60 算出各 comb 的 g_i；每個聲道各一組 comb 與 all-pass 的延遲線；
     *       配置 out（含殘響尾巴），逐點計算。 */
    (void)in; (void)out;
    return FX_ENOTIMPL;
}
