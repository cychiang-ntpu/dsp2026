/* fx_echo.c — ★ 延遲／回音（Delay / Echo）
 *
 *   echo <delay_s> <feedback>
 *   例：echo 0.3 0.5      延遲 0.3 秒，每次回音振幅乘 0.5
 *
 * 令 D = round(delay_s · fs)，g = feedback。
 *
 * 單次回音（FIR comb）：
 *
 *   y[n] = x[n] + g x[n-D]              H(z) = 1 + g z^-D
 *
 * 多重回音（IIR／回授 comb，本效果器的預設定義）：
 *
 *   y[n] = x[n] + g y[n-D]              H(z) = 1 / (1 - g z^-D)
 *
 *   脈衝響應 h[n] = Σ_{m≥0} g^m δ[n - mD]：每隔 D 點一個回音，振幅依 g^m 衰減。
 *   D 個極點均勻分布在半徑 |g|^(1/D) 的圓上，穩定條件 |g| < 1。
 *   振幅響應 |H(e^jω)| = 1 / sqrt(1 - 2g cos(ωD) + g^2)，
 *   峰值 1/(1-|g|)、谷值 1/(1+|g|)，像梳子，所以叫 comb filter。
 *
 * 輸出長度：輸入結束後回音還會持續。衰減到 -60 dB 需要 m = ln(0.001)/ln|g| 次回音，
 * 請把輸出延長到尾巴衰減完（並訂一個上限），不要直接截斷。
 *
 * 邊界情況：|g| ≥ 1（不穩定，應拒絕）、delay_s ≤ 0、D 大於輸入長度、
 * 峰值增益 1/(1-|g|) 造成削波（可考慮輸出正規化，並在 docs/interface.md 說明）。
 *
 * 參考文獻：
 *   [2] Oppenheim & Schafer, Discrete-Time Signal Processing, 3rd ed.,
 *       Sec. 2.5（LCCDE）、Sec. 5.2–5.3（有理系統函數的頻率響應）。
 *   [3] U. Zölzer (ed.), DAFX: Digital Audio Effects, 2nd ed., Wiley, 2011, Ch. 2（Filters and Delays）。
 *   [5] J. O. Smith III, Physical Audio Signal Processing,
 *       https://ccrma.stanford.edu/~jos/pasp/ （Feedforward / Feedback Comb Filters）。
 */
#include <stdio.h>
#include "fx.h"
#include "dsp_util.h"

int fx_echo(const audio_t *in, audio_t *out, int argc, char **argv)
{
    double delay_s, g;
    if (argc != 2) return FX_EARG;
    if (fx_arg_double(argc, argv, 0, 0.0, &delay_s) != FX_OK) return FX_EARG;
    if (fx_arg_double(argc, argv, 1, 0.0, &g)       != FX_OK) return FX_EARG;
    if (delay_s <= 0.0 || g <= -1.0 || g >= 1.0) {
        fprintf(stderr, "echo: need delay_s > 0 and |feedback| < 1\n");
        return FX_EARG;
    }

    /* TODO: 算出 D 與輸出長度（含尾巴），配置 out，實作 y[n] = x[n] + g y[n-D]。
     *       不得存取陣列範圍外的元素（n < D 時 y[n-D] = 0，initial rest）。 */
    (void)in; (void)out;
    return FX_ENOTIMPL;
}
