/* wav_info.c — 讀取 WAV 檔標頭並印出基本資訊
 * 用法： ./wav_info input.wav
 * 目的：練習編譯與執行，並熟悉作業會用到的 WAV（RIFF）格式。
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

    char riff[4], wave[4];
    uint32_t riff_size;
    fread(riff, 1, 4, fp); fread(&riff_size, 4, 1, fp); fread(wave, 1, 4, fp);
    if (memcmp(riff, "RIFF", 4) || memcmp(wave, "WAVE", 4)) {
        fprintf(stderr, "not a RIFF/WAVE file\n"); fclose(fp); return 1;
    }

    /* 逐一走訪 chunk，找 fmt 與 data */
    char id[4]; uint32_t size;
    uint16_t fmt_tag = 0, channels = 0, bits = 0;
    uint32_t fs = 0, data_bytes = 0;
    while (fread(id, 1, 4, fp) == 4 && fread(&size, 4, 1, fp) == 1) {
        if (!memcmp(id, "fmt ", 4)) {
            uint32_t byte_rate; uint16_t block_align;
            fread(&fmt_tag, 2, 1, fp); fread(&channels, 2, 1, fp);
            fread(&fs, 4, 1, fp);      fread(&byte_rate, 4, 1, fp);
            fread(&block_align, 2, 1, fp); fread(&bits, 2, 1, fp);
            fseek(fp, size - 16, SEEK_CUR);
        } else if (!memcmp(id, "data", 4)) {
            data_bytes = size; break;
        } else {
            fseek(fp, size + (size & 1), SEEK_CUR);
        }
    }
    fclose(fp);

    uint32_t frames = (channels && bits) ? data_bytes / (channels * bits / 8) : 0;
    printf("file        : %s\n", argv[1]);
    printf("format tag  : %u (1 = PCM)\n", fmt_tag);
    printf("channels    : %u\n", channels);
    printf("sample rate : %u Hz\n", fs);
    printf("bits/sample : %u\n", bits);
    printf("frames      : %u\n", frames);
    printf("duration    : %.3f s\n", fs ? (double)frames / fs : 0.0);
    return 0;
}
