/* fx_distortion.c — 失真（Distortion / Overdrive）
 *
 *   distortion <drive_dB> [oversample=4]
 *   例：distortion 20        distortion 20 1（不做過取樣，用來對照混疊）
 *
 * 無記憶非線性映射 y = f(g · x)，g = 10^(drive_dB/20)：
 *
 *   硬削波（hard clip）   f(u) = max(-1, min(1, u))
 *   軟削波（overdrive）   f(u) = tanh(u)
 *   三次軟削波            f(u) = u - u^3/3（|u| ≤ 1），±2/3（|u| > 1）
 *
 * 為什麼需要過取樣：
 *   非線性會產生諧波。輸入 cos(ω0 n) 經奇對稱的 f(·) 後出現 3ω0、5ω0、7ω0…；
 *   超過 π 的諧波會混疊回 [0, π]，變成與音高無關的雜音。
 *   例：fs = 44.1 kHz、f0 = 5 kHz，第 5 諧波 25 kHz 會折回 44.1 - 25 = 19.1 kHz，
 *   第 7 諧波 35 kHz 折回 9.1 kHz。
 *
 * 過取樣架構（O&S Fig. 4.29 的 L = M 特例）：
 *
 *   x[n] → ↑L → 低通（增益 L，截止 π/L）→ f(g·) → 低通（截止 π/L）→ ↓L → y[n]
 *
 *   升到 L·fs 後，L·fs/2 以下的諧波不會混疊；降取樣前的低通把 fs/2 以上的諧波濾掉。
 *   低通可用視窗法 FIR（dsp_util.c 的 fir_design_lowpass()），並補償其延遲。
 *   多相（polyphase）實作可以避免對補進去的零做乘法。
 *
 * 架構文件請附：有／無過取樣時，單一弦波輸入的輸出頻譜比較。
 *
 * 邊界情況：drive 極大（接近方波）、oversample < 1、輸出音量補償、
 * 兩個低通造成的延遲與輸出長度。
 *
 * 參考文獻：
 *   [2]  Oppenheim & Schafer, Discrete-Time Signal Processing, 3rd ed.,
 *        Sec. 4.6（Changing the Sampling Rate Using Discrete-Time Processing）、Sec. 4.7（Multirate）。
 *   [3]  U. Zölzer (ed.), DAFX: Digital Audio Effects, 2nd ed., Wiley, 2011,
 *        Ch. 4（Nonlinear Processing）。
 *   [11] D. T. Yeh, J. S. Abel, and J. O. Smith, "Simplified, physically-informed models of
 *        distortion and overdrive guitar effects pedals," Proc. Int. Conf. Digital Audio
 *        Effects (DAFx-07), Bordeaux, France, 2007.
 */
#include <stdio.h>
#include "fx.h"
#include "dsp_util.h"

int fx_distortion(const audio_t *in, audio_t *out, int argc, char **argv)
{
    double drive_db, os;
    if (argc < 1 || argc > 2) return FX_EARG;
    if (fx_arg_double(argc, argv, 0, 0.0, &drive_db) != FX_OK) return FX_EARG;
    if (fx_arg_double(argc, argv, 1, 4.0, &os)       != FX_OK) return FX_EARG;
    int L = (int)os;
    if (L < 1 || L > 16 || (double)L != os) {
        fprintf(stderr, "distortion: oversample must be an integer in 1..16\n");
        return FX_EARG;
    }

    /* TODO: ↑L、低通、非線性、低通、↓L。L = 1 時直接套用非線性。 */
    (void)in; (void)out;
    return FX_ENOTIMPL;
}
