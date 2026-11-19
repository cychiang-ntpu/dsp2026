/* test_fx.c — 自動測試（make test）
 *
 * 規格要求：每個效果器至少一個可自動比對的測試（弦波輸入 → 預期頻譜或振幅）。
 * 這裡提供測試工具、三個已通過的範例（wav、gain、tremolo），以及兩個必選效果器（eq、echo）的測試；
 * eq 與 echo 在你們實作前會顯示 NOT IMPLEMENTED，實作正確後變成 PASS。
 * 其餘效果器請照同樣寫法自行新增，並在 main() 的表格加一列。
 *
 * 測試函式回傳：T_PASS、T_FAIL，或 T_TODO（效果器回傳 FX_ENOTIMPL）。
 * 只要有任何一項不是 PASS，程式回傳非 0，make test 就會失敗。
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fx.h"
#include "wav.h"

#define T_PASS 0
#define T_FAIL 1
#define T_TODO 2

#define FS 44100

/* 條件不成立時印出位置並讓測試失敗 */
#define CHECK(cond, ...) \
    do { if (!(cond)) { printf("    line %d: ", __LINE__); printf(__VA_ARGS__); printf("\n"); rc = T_FAIL; } } while (0)

/* ---------- 測試工具（已實作，可直接使用） ---------- */

/* 產生立體聲弦波：amp · sin(2π f n / fs)，兩聲道相同 */
static int gen_sine(audio_t *a, double f, double amp, double seconds)
{
    if (audio_alloc(a, FS, 2, (size_t)(seconds * FS)) != FX_OK) return FX_ENOMEM;
    for (size_t n = 0; n < a->frames; n++) {
        double v = amp * sin(2.0 * M_PI * f * (double)n / FS);
        a->data[2 * n] = a->data[2 * n + 1] = v;
    }
    return FX_OK;
}

/* 產生立體聲脈衝：amp · δ[n] */
static int gen_impulse(audio_t *a, double amp, double seconds)
{
    if (audio_alloc(a, FS, 2, (size_t)(seconds * FS)) != FX_OK) return FX_ENOMEM;
    a->data[0] = a->data[1] = amp;
    return FX_OK;
}

/* 量測聲道 c 在頻率 f 的弦波振幅：對 [start, start + len) 這段訊號與 e^{-j2πfn/fs} 做內積，
 *   A = (2/len) | Σ x[n] e^{-j2πfn/fs} |
 * len 取 f 的整數個週期時沒有頻譜洩漏。start 用來跳過暫態，只量穩態。 */
static double amp_at(const audio_t *a, int c, double f, size_t start, size_t len)
{
    double re = 0.0, im = 0.0;
    if (start + len > a->frames) return -1.0;
    for (size_t n = start; n < start + len; n++) {
        double w = 2.0 * M_PI * f * (double)n / a->fs;
        re += a->data[n * a->ch + c] * cos(w);
        im -= a->data[n * a->ch + c] * sin(w);
    }
    return 2.0 * sqrt(re * re + im * im) / (double)len;
}

static double to_db(double ratio) { return 20.0 * log10(ratio + 1e-300); }

/* 以命令列字串陣列執行效果器串接 */
static int run(const audio_t *in, audio_t *out, int argc, const char **argv)
{
    return fx_run_chain(in, out, argc, (char **)argv);
}

/* ---------- 範例：已通過的測試 ---------- */

/* WAV 寫出再讀回，取樣值誤差應小於 1 LSB（1/32768） */
static int test_wav_roundtrip(void)
{
    int rc = T_PASS;
    audio_t a, b = {0, 0, 0, NULL};
    long clipped = -1;
    if (gen_sine(&a, 1000.0, 0.5, 0.1) != FX_OK) return T_FAIL;
    CHECK(wav_write("test_tmp.wav", &a, &clipped) == FX_OK, "wav_write failed");
    CHECK(clipped == 0, "unexpected clipping: %ld", clipped);
    CHECK(wav_read("test_tmp.wav", &b) == FX_OK, "wav_read failed");
    if (b.data) {
        CHECK(b.fs == a.fs && b.ch == a.ch && b.frames == a.frames, "header mismatch");
        double maxerr = 0.0;
        for (size_t i = 0; b.frames == a.frames && i < a.frames * 2; i++)
            maxerr = fmax(maxerr, fabs(a.data[i] - b.data[i]));
        CHECK(maxerr <= 1.0 / 32768.0, "max error %g > 1 LSB", maxerr);
    }
    remove("test_tmp.wav");
    audio_free(&a); audio_free(&b);
    return rc;
}

/* gain -6.0206 dB：1 kHz 弦波振幅應變為一半 */
static int test_gain(void)
{
    int rc = T_PASS;
    const char *args[] = { "gain", "-6.0206" };
    audio_t in, out = {0, 0, 0, NULL};
    if (gen_sine(&in, 1000.0, 0.5, 1.0) != FX_OK) return T_FAIL;
    int r = run(&in, &out, 2, args);
    if (r == FX_ENOTIMPL) { audio_free(&in); return T_TODO; }
    CHECK(r == FX_OK, "effect returned %d", r);
    if (r == FX_OK) {
        double a = amp_at(&out, 0, 1000.0, 0, FS / 2);
        CHECK(fabs(a - 0.25) < 1e-4, "amplitude %.5f, expected 0.25", a);
    }
    audio_free(&in); audio_free(&out);
    return rc;
}

/* tremolo 10 0.8：輸入 0.5·sin(2π·1000 n/fs)。
 * 理論值：1000 Hz 振幅 A(1 - d/2) = 0.3，旁帶 990、1010 Hz 振幅各 A·d/4 = 0.1。
 * 量測長度 1 秒，三個頻率都是整數個週期。 */
static int test_tremolo(void)
{
    int rc = T_PASS;
    const char *args[] = { "tremolo", "10", "0.8" };
    audio_t in, out = {0, 0, 0, NULL};
    if (gen_sine(&in, 1000.0, 0.5, 1.0) != FX_OK) return T_FAIL;
    int r = run(&in, &out, 3, args);
    if (r == FX_ENOTIMPL) { audio_free(&in); return T_TODO; }
    CHECK(r == FX_OK, "effect returned %d", r);
    if (r == FX_OK) {
        CHECK(out.frames == in.frames, "length changed");
        for (int c = 0; c < 2; c++) {
            double a0 = amp_at(&out, c, 1000.0, 0, FS);
            double lo = amp_at(&out, c,  990.0, 0, FS);
            double hi = amp_at(&out, c, 1010.0, 0, FS);
            CHECK(fabs(a0 - 0.3) < 1e-3, "ch%d: carrier %.4f, expected 0.3", c, a0);
            CHECK(fabs(lo - 0.1) < 1e-3, "ch%d: 990 Hz %.4f, expected 0.1", c, lo);
            CHECK(fabs(hi - 0.1) < 1e-3, "ch%d: 1010 Hz %.4f, expected 0.1", c, hi);
        }
    }
    audio_free(&in); audio_free(&out);
    return rc;
}

/* ---------- 必選效果器的測試 ---------- */

/* eq lowpass 4000：1 kHz 應幾乎不變（±1 dB），10 kHz 至少衰減 12 dB。
 * 跳過前 0.25 秒的暫態，量測 0.5 秒的穩態。 */
static int test_eq_lowpass(void)
{
    int rc = T_PASS;
    const char *args[] = { "eq", "lowpass", "4000" };
    const double freqs[2] = { 1000.0, 10000.0 };
    for (int i = 0; i < 2; i++) {
        audio_t in, out = {0, 0, 0, NULL};
        if (gen_sine(&in, freqs[i], 0.5, 1.0) != FX_OK) return T_FAIL;
        int r = run(&in, &out, 3, args);
        if (r == FX_ENOTIMPL) { audio_free(&in); return T_TODO; }
        CHECK(r == FX_OK, "effect returned %d", r);
        if (r == FX_OK) {
            for (int c = 0; c < 2; c++) {
                double db = to_db(amp_at(&out, c, freqs[i], FS / 4, FS / 2) / 0.5);
                if (i == 0) CHECK(fabs(db) < 1.0, "ch%d: 1 kHz gain %.2f dB, expected within +-1 dB", c, db);
                else        CHECK(db < -12.0,     "ch%d: 10 kHz gain %.2f dB, expected < -12 dB", c, db);
            }
        }
        audio_free(&in); audio_free(&out);
    }
    return rc;
}

/* echo 0.1 0.5：輸入 0.5·δ[n]，D = 4410。
 * y[n] = x[n] + g y[n-D] 的脈衝響應在 n = 0, D, 2D 應為 0.5, 0.25, 0.125，其餘為 0。 */
static int test_echo_impulse(void)
{
    int rc = T_PASS;
    const char *args[] = { "echo", "0.1", "0.5" };
    const size_t D = 4410;
    audio_t in, out = {0, 0, 0, NULL};
    if (gen_impulse(&in, 0.5, 1.0) != FX_OK) return T_FAIL;
    int r = run(&in, &out, 3, args);
    if (r == FX_ENOTIMPL) { audio_free(&in); return T_TODO; }
    CHECK(r == FX_OK, "effect returned %d", r);
    if (r == FX_OK) {
        CHECK(out.frames >= in.frames, "output shorter than input");
        for (int c = 0; c < 2 && out.frames > 2 * D + 1; c++) {
            CHECK(fabs(out.data[0 * 2 + c]       - 0.5)   < 1e-6, "ch%d: y[0] = %g", c, out.data[c]);
            CHECK(fabs(out.data[D * 2 + c]       - 0.25)  < 1e-6, "ch%d: y[D] = %g", c, out.data[D * 2 + c]);
            CHECK(fabs(out.data[2 * D * 2 + c]   - 0.125) < 1e-6, "ch%d: y[2D] = %g", c, out.data[2 * D * 2 + c]);
            CHECK(fabs(out.data[(D / 2) * 2 + c])         < 1e-9, "ch%d: y[D/2] should be 0", c);
            CHECK(fabs(out.data[(D + 1) * 2 + c])         < 1e-9, "ch%d: y[D+1] should be 0", c);
        }
    }
    audio_free(&in); audio_free(&out);
    return rc;
}

/* ---------- TODO：其餘效果器的測試，由各組新增 ----------
 *
 * 寫法建議：
 *   reverb      輸入脈衝，量測輸出能量衰減 60 dB 所需時間，應接近 rt60
 *   vibrato     輸入弦波，輸出 RMS 應與輸入接近；1 kHz 處振幅下降、能量分散到旁帶
 *   flanger     rate 極小時近似固定延遲 D 的 comb，量測 notch 頻率 (2k+1)·fs/(2D)
 *   distortion  輸入 1 kHz，量測 3 kHz、5 kHz 諧波；輸入 5 kHz，比較過取樣前後 9.1 kHz 混疊成分
 *   stretch     輸出長度 = ratio × 輸入長度（±一個 frame）；1 kHz 輸入後主頻仍在 1 kHz
 *   pitch       +12 半音：1 kHz 輸入，輸出主頻在 2 kHz，長度不變
 *   spectrogram 1 kHz 輸入，CSV 每列最大值的欄位應為 round(1000·N/fs)
 *   串接        eq lowpass 4000 echo 0.1 0.5 的結果，應等於分兩次執行的結果
 *   邊界        不合法參數應回傳 FX_EARG；極端參數不得當機、輸出不得有 NaN／Inf
 */

/* ---------- 主程式 ---------- */

typedef struct { const char *name; int (*fn)(void); } test_t;

static const test_t tests[] = {
    { "wav roundtrip",    test_wav_roundtrip },
    { "gain -6 dB",       test_gain },
    { "tremolo sideband", test_tremolo },
    { "eq lowpass 4000",  test_eq_lowpass },
    { "echo impulse",     test_echo_impulse },
    /* TODO: 在這裡加入其餘效果器的測試 */
};

int main(void)
{
    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int count[3] = {0, 0, 0};
    const char *label[3] = { "PASS", "FAIL", "NOT IMPLEMENTED" };

    for (int i = 0; i < n; i++) {
        int r = tests[i].fn();
        if (r < 0 || r > 2) r = T_FAIL;
        count[r]++;
        printf("[%s] %s\n", label[r], tests[i].name);
    }
    printf("\n%d passed, %d failed, %d not implemented (total %d)\n",
           count[T_PASS], count[T_FAIL], count[T_TODO], n);
    return (count[T_FAIL] || count[T_TODO]) ? 1 : 0;
}
