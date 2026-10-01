/* wav_info.c — 讀取 WAV 檔標頭並印出基本資訊
 * 用法： ./wav_info input.wav
 * 目的：練習編譯與執行，並熟悉作業會用到的 WAV（RIFF）格式；
 *       也可用來檢查自己程式輸出的 WAV 標頭是否正確。
 *
 * WAV 檔結構（RIFF）：
 *   "RIFF" <檔案剩餘長度 4 bytes> "WAVE"
 *   接著是一連串 chunk，每個 chunk = <4 字元 id> <資料長度 4 bytes> <資料>
 *   （資料長度為奇數時後面補 1 byte）
 *   必要的 chunk： "fmt "（格式）與 "data"（取樣值）
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s input.wav\n", argv[0]);
        return 1;
    }
    FILE *fp = fopen(argv[1], "rb");
    if (!fp) { perror("fopen"); return 1; }

    /* 實際檔案大小，用來和標頭宣稱的長度比對 */
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char riff[4], wave[4];
    uint32_t riff_size;
    if (fread(riff, 1, 4, fp) != 4 || fread(&riff_size, 4, 1, fp) != 1 ||
        fread(wave, 1, 4, fp) != 4 ||
        memcmp(riff, "RIFF", 4) || memcmp(wave, "WAVE", 4)) {
        fprintf(stderr, "error: not a RIFF/WAVE file\n"); fclose(fp); return 1;
    }

    /* 逐一走訪 chunk，找 fmt 與 data */
    char id[4]; uint32_t size;
    uint16_t fmt_tag = 0, channels = 0, bits = 0;
    uint32_t fs = 0, data_bytes = 0;
    long data_offset = -1;
    int have_fmt = 0;
    while (fread(id, 1, 4, fp) == 4 && fread(&size, 4, 1, fp) == 1) {
        if (!memcmp(id, "fmt ", 4)) {
            uint32_t byte_rate; uint16_t block_align;
            if (size < 16 ||
                fread(&fmt_tag, 2, 1, fp) != 1 || fread(&channels, 2, 1, fp) != 1 ||
                fread(&fs, 4, 1, fp) != 1 || fread(&byte_rate, 4, 1, fp) != 1 ||
                fread(&block_align, 2, 1, fp) != 1 || fread(&bits, 2, 1, fp) != 1) {
                fprintf(stderr, "error: fmt chunk is broken (size = %u)\n", size);
                fclose(fp); return 1;
            }
            have_fmt = 1;
            fseek(fp, (long)(size - 16) + (size & 1), SEEK_CUR);
        } else if (!memcmp(id, "data", 4)) {
            data_bytes = size;
            data_offset = ftell(fp);
            break;
        } else {
            fseek(fp, (long)size + (size & 1), SEEK_CUR);  /* 略過 LIST 等其他 chunk */
        }
    }
    fclose(fp);

    if (!have_fmt)        { fprintf(stderr, "error: no fmt chunk\n");  return 1; }
    if (data_offset < 0)  { fprintf(stderr, "error: no data chunk\n"); return 1; }

    uint32_t frame_bytes = (uint32_t)channels * bits / 8;
    uint32_t frames = frame_bytes ? data_bytes / frame_bytes : 0;
    printf("file        : %s\n", argv[1]);
    printf("format tag  : %u (%s)\n", fmt_tag,
           fmt_tag == 1 ? "PCM" : fmt_tag == 3 ? "IEEE float" :
           fmt_tag == 0xFFFE ? "WAVE_FORMAT_EXTENSIBLE" : "other");
    printf("channels    : %u\n", channels);
    printf("sample rate : %u Hz\n", fs);
    printf("bits/sample : %u\n", bits);
    printf("frames      : %u\n", frames);
    printf("duration    : %.3f s\n", fs ? (double)frames / fs : 0.0);

    /* 檢查標頭與實際檔案是否一致：寫 WAV 時最常見的錯誤 */
    int warn = 0;
    long actual_data = file_size - data_offset;
    if ((long)data_bytes > actual_data) {
        printf("WARNING     : data chunk says %u bytes, but only %ld bytes are in the file\n",
               data_bytes, actual_data);
        warn = 1;
    }
    if ((long)riff_size + 8 != file_size) {
        printf("WARNING     : RIFF size says %ld bytes, actual file size is %ld bytes\n",
               (long)riff_size + 8, file_size);
        warn = 1;
    }
    if (frame_bytes && data_bytes % frame_bytes) {
        printf("WARNING     : data size %u is not a multiple of %u bytes per frame\n",
               data_bytes, frame_bytes);
        warn = 1;
    }
    return warn ? 2 : 0;
}
