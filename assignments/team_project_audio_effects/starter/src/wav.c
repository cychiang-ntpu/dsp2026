/* wav.c — WAV（RIFF, 16-bit PCM）讀寫。已實作完成，可直接使用。
 *
 * WAV 檔結構：
 *   "RIFF" <檔案剩餘長度 4 bytes> "WAVE"
 *   一連串 chunk：<4 字元 id> <資料長度 4 bytes> <資料>（長度為奇數時補 1 byte）
 *   必要的 chunk："fmt "（格式）與 "data"（取樣值）
 * 所有整數皆為 little-endian；這裡逐 byte 組合，不依賴機器的位元組順序。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "wav.h"

static uint32_t le16(const unsigned char *p) { return (uint32_t)p[0] | ((uint32_t)p[1] << 8); }
static uint32_t le32(const unsigned char *p) { return le16(p) | (le16(p + 2) << 16); }

static void put16(unsigned char *p, uint32_t v) { p[0] = v & 0xFF; p[1] = (v >> 8) & 0xFF; }
static void put32(unsigned char *p, uint32_t v) { put16(p, v & 0xFFFF); put16(p + 2, v >> 16); }

int wav_read(const char *path, audio_t *a)
{
    FILE *fp = fopen(path, "rb");
    if (!fp) { perror(path); return FX_EIO; }

    unsigned char hdr[12];
    if (fread(hdr, 1, 12, fp) != 12 || memcmp(hdr, "RIFF", 4) || memcmp(hdr + 8, "WAVE", 4)) {
        fprintf(stderr, "%s: not a RIFF/WAVE file\n", path);
        fclose(fp); return FX_EIO;
    }

    int have_fmt = 0, ch = 0, fs = 0, bits = 0, tag = 0;
    unsigned char ck[8];
    while (fread(ck, 1, 8, fp) == 8) {
        uint32_t size = le32(ck + 4);
        if (!memcmp(ck, "fmt ", 4)) {
            unsigned char f[16];
            if (size < 16 || fread(f, 1, 16, fp) != 16) break;
            tag  = (int)le16(f);
            ch   = (int)le16(f + 2);
            fs   = (int)le32(f + 4);
            bits = (int)le16(f + 14);
            have_fmt = 1;
            fseek(fp, (long)(size - 16) + (long)(size & 1), SEEK_CUR);
        } else if (!memcmp(ck, "data", 4)) {
            /* tag 1 = PCM；0xFFFE = WAVE_FORMAT_EXTENSIBLE（內容仍可能是 16-bit PCM） */
            if (!have_fmt || (tag != 1 && tag != 0xFFFE) || bits != 16 || ch < 1) {
                fprintf(stderr, "%s: only 16-bit PCM is supported\n", path);
                fclose(fp); return FX_EIO;
            }
            size_t frames = size / (size_t)(ch * 2);
            unsigned char *raw = malloc(frames * (size_t)ch * 2 + 1);
            if (!raw) { fclose(fp); return FX_ENOMEM; }
            size_t got = fread(raw, (size_t)ch * 2, frames, fp);   /* 檔案被截斷時以實際讀到的為準 */
            fclose(fp);
            if (audio_alloc(a, fs, ch, got) != FX_OK) { free(raw); return FX_ENOMEM; }
            for (size_t i = 0; i < got * (size_t)ch; i++) {
                int16_t s = (int16_t)le16(raw + 2 * i);
                a->data[i] = s / 32768.0;
            }
            free(raw);
            return FX_OK;
        } else {
            fseek(fp, (long)size + (long)(size & 1), SEEK_CUR);    /* 略過 LIST 等其他 chunk */
        }
    }
    fprintf(stderr, "%s: fmt/data chunk not found\n", path);
    fclose(fp);
    return FX_EIO;
}

int wav_write(const char *path, const audio_t *a, long *clipped)
{
    FILE *fp = fopen(path, "wb");
    if (!fp) { perror(path); return FX_EIO; }

    size_t   n          = a->frames * (size_t)a->ch;
    uint32_t data_bytes = (uint32_t)(n * 2);
    unsigned char h[44];
    memcpy(h, "RIFF", 4);       put32(h + 4, 36 + data_bytes);
    memcpy(h + 8, "WAVEfmt ", 8);
    put32(h + 16, 16);          /* fmt chunk 長度 */
    put16(h + 20, 1);           /* PCM */
    put16(h + 22, (uint32_t)a->ch);
    put32(h + 24, (uint32_t)a->fs);
    put32(h + 28, (uint32_t)(a->fs * a->ch * 2));   /* byte rate */
    put16(h + 32, (uint32_t)(a->ch * 2));           /* block align */
    put16(h + 34, 16);          /* bits per sample */
    memcpy(h + 36, "data", 4);  put32(h + 40, data_bytes);

    long nclip = 0;
    int ok = fwrite(h, 1, 44, fp) == 44;
    for (size_t i = 0; ok && i < n; i++) {
        double v = floor(a->data[i] * 32768.0 + 0.5);
        if (v > 32767.0)  { v = 32767.0;  nclip++; }
        if (v < -32768.0) { v = -32768.0; nclip++; }
        unsigned char b[2];
        put16(b, (uint32_t)(uint16_t)(int16_t)v);
        ok = fwrite(b, 1, 2, fp) == 2;
    }
    if (fclose(fp) != 0) ok = 0;
    if (clipped) *clipped = nclip;
    return ok ? FX_OK : FX_EIO;
}
