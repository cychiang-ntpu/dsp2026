/* fx_table.c — 效果器登記表。
 * 新增效果器：(1) 在 src/ 新增 fx_xxx.c，(2) 在 include/fx.h 宣告，(3) 在下表加一列，
 * (4) 在 docs/interface.md 寫參數格式，(5) 在 tests/test_fx.c 加測試。
 * 沒有實作的效果器請把那一列刪掉，讓 fx --list 只列出可用的效果器。
 * 效果器名稱與既有參數的順序、單位是固定介面（見 docs/interface.md），不可更改；
 * 只能在既有參數之後新增有預設值的選用參數。 */
#include "fx.h"

const fx_entry_t fx_table[] = {
    /* 名稱          函式            參數說明 */
    { "gain",        fx_gain,        "<dB>" },
    { "eq",          fx_eq,          "<lowpass|highpass|bandpass|lowshelf|highshelf> <f0_Hz> [Q=0.7071] [gain_dB=0]" },
    { "echo",        fx_echo,        "<delay_s> <feedback>" },
    { "reverb",      fx_reverb,      "<rt60_s> [mix=0.3]" },
    { "tremolo",     fx_tremolo,     "<rate_Hz> <depth>" },
    { "vibrato",     fx_vibrato,     "<rate_Hz> <width_ms>" },
    { "flanger",     fx_flanger,     "<rate_Hz> <depth_ms> [feedback=0] [mix=0.5]" },
    { "chorus",      fx_chorus,      "<rate_Hz> <depth_ms> [mix=0.5]" },
    { "distortion",  fx_distortion,  "<drive_dB> [oversample=4]" },
    { "stretch",     fx_stretch,     "<ratio>            (2.0 = 長度變兩倍，音高不變)" },
    { "pitch",       fx_pitch,       "<semitones>        (+12 = 高八度，長度不變)" },
    { "spectrogram", fx_spectrogram, "<out.csv> [N=1024] [hop=256]   (音訊原樣通過)" },
};

const int fx_count = (int)(sizeof(fx_table) / sizeof(fx_table[0]));
