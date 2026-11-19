/* fx.h — 效果器共用介面
 *
 * 整個程式的資料流：
 *
 *   in.wav --wav_read--> audio_t --效果1--> audio_t --效果2--> ... --wav_write--> out.wav
 *
 * 每個效果器是一個函式（fx_fn）：讀入一段完整的音訊 in，配置並填好輸出 out。
 * 輸出長度可以和輸入不同（echo／reverb 會多出尾巴，stretch 會改變長度）。
 */
#ifndef FX_H
#define FX_H

#include <stddef.h>

/* 回傳值 */
#define FX_OK        0
#define FX_EARG      1   /* 參數錯誤 */
#define FX_ENOMEM    2   /* 記憶體不足 */
#define FX_ENOTIMPL  3   /* 尚未實作（程式殼的預設回傳值） */
#define FX_EIO       4   /* 檔案讀寫錯誤 */

/* 音訊緩衝區：取樣值為 double，正規化到 [-1, 1)，多聲道交錯（interleaved）存放。
 * 第 n 個 frame、第 c 聲道的取樣值是 data[n * ch + c]。 */
typedef struct {
    int     fs;      /* 取樣率（Hz） */
    int     ch;      /* 聲道數 */
    size_t  frames;  /* frame 數（每個 frame 含 ch 個取樣值） */
    double *data;    /* frames * ch 個取樣值 */
} audio_t;

int  audio_alloc(audio_t *a, int fs, int ch, size_t frames);  /* 配置並清為 0 */
int  audio_copy(const audio_t *src, audio_t *dst);            /* 配置 dst 並複製 */
void audio_free(audio_t *a);

/* 效果器函式。
 *   in    輸入音訊（不可修改）
 *   out   尚未配置；函式內以 audio_alloc() 配置後填入結果
 *   argc  此效果器的參數個數（不含效果器名稱）
 *   argv  此效果器的參數字串
 * 成功回傳 FX_OK；失敗時不得留下已配置的 out。 */
typedef int (*fx_fn)(const audio_t *in, audio_t *out, int argc, char **argv);

typedef struct {
    const char *name;   /* 命令列上的效果器名稱 */
    fx_fn       run;
    const char *usage;  /* 參數說明，fx --list 會印出 */
} fx_entry_t;

/* 效果器登記表，定義在 src/fx_table.c；新增效果器時在那裡加一列。 */
extern const fx_entry_t fx_table[];
extern const int        fx_count;

const fx_entry_t *fx_find(const char *name);

/* 依命令列串接執行效果器。argv 例：{"eq","lowpass","4000","echo","0.3","0.5"}。
 * 以「下一個效果器名稱」作為分界，所以參數字串不可與任何效果器名稱相同。 */
int fx_run_chain(const audio_t *in, audio_t *out, int argc, char **argv);

/* 讀取第 i 個參數為 double；若 i >= argc 則用預設值 def。格式錯誤回傳 FX_EARG。 */
int fx_arg_double(int argc, char **argv, int i, double def, double *val);

/* 各效果器（src/fx_*.c） */
int fx_gain(const audio_t *in, audio_t *out, int argc, char **argv);
int fx_eq(const audio_t *in, audio_t *out, int argc, char **argv);
int fx_echo(const audio_t *in, audio_t *out, int argc, char **argv);
int fx_reverb(const audio_t *in, audio_t *out, int argc, char **argv);
int fx_tremolo(const audio_t *in, audio_t *out, int argc, char **argv);
int fx_vibrato(const audio_t *in, audio_t *out, int argc, char **argv);
int fx_flanger(const audio_t *in, audio_t *out, int argc, char **argv);
int fx_chorus(const audio_t *in, audio_t *out, int argc, char **argv);
int fx_distortion(const audio_t *in, audio_t *out, int argc, char **argv);
int fx_stretch(const audio_t *in, audio_t *out, int argc, char **argv);
int fx_pitch(const audio_t *in, audio_t *out, int argc, char **argv);
int fx_spectrogram(const audio_t *in, audio_t *out, int argc, char **argv);

#endif
