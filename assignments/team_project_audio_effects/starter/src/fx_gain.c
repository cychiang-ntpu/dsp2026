/* fx_gain.c — 增益（已實作完成的範例，示範效果器函式的寫法）
 *
 *   gain <dB>
 *
 *   y[n] = g · x[n]，g = 10^(dB/20)
 *
 * 寫其他效果器時照這個流程：
 *   1. 解析並檢查參數（錯誤回傳 FX_EARG）
 *   2. audio_alloc() 配置輸出（長度可與輸入不同）
 *   3. 逐聲道處理：第 n 個 frame、第 c 聲道是 data[n * ch + c]
 *   4. 回傳 FX_OK
 */
#include <math.h>
#include "fx.h"

int fx_gain(const audio_t *in, audio_t *out, int argc, char **argv)
{
    double db;
    if (argc != 1 || fx_arg_double(argc, argv, 0, 0.0, &db) != FX_OK) return FX_EARG;

    if (audio_alloc(out, in->fs, in->ch, in->frames) != FX_OK) return FX_ENOMEM;

    double g = pow(10.0, db / 20.0);
    for (int c = 0; c < in->ch; c++)
        for (size_t n = 0; n < in->frames; n++)
            out->data[n * in->ch + c] = g * in->data[n * in->ch + c];

    return FX_OK;
}
