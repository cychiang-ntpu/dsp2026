/* wav.h — WAV（RIFF, 16-bit PCM）讀寫。已實作完成，可直接使用。 */
#ifndef WAV_H
#define WAV_H

#include "fx.h"

/* 讀入 16-bit PCM WAV，轉成 [-1, 1) 的 double。成功回傳 FX_OK。 */
int wav_read(const char *path, audio_t *a);

/* 寫出 16-bit PCM WAV。超出 [-1, 1) 的取樣值會被飽和（削波），
 * 被削波的取樣值個數寫入 *clipped（clipped 可為 NULL）。 */
int wav_write(const char *path, const audio_t *a, long *clipped);

#endif
