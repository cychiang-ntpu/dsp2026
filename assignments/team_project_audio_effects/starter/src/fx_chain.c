/* fx_chain.c — 音訊緩衝區工具與效果器串接。已實作完成，通常不需修改。 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fx.h"

int audio_alloc(audio_t *a, int fs, int ch, size_t frames)
{
    a->fs = fs; a->ch = ch; a->frames = frames;
    a->data = calloc(frames * (size_t)ch + 1, sizeof(double));
    return a->data ? FX_OK : FX_ENOMEM;
}

int audio_copy(const audio_t *src, audio_t *dst)
{
    if (audio_alloc(dst, src->fs, src->ch, src->frames) != FX_OK) return FX_ENOMEM;
    memcpy(dst->data, src->data, src->frames * (size_t)src->ch * sizeof(double));
    return FX_OK;
}

void audio_free(audio_t *a)
{
    free(a->data);
    a->data = NULL; a->frames = 0;
}

const fx_entry_t *fx_find(const char *name)
{
    for (int i = 0; i < fx_count; i++)
        if (!strcmp(fx_table[i].name, name)) return &fx_table[i];
    return NULL;
}

int fx_arg_double(int argc, char **argv, int i, double def, double *val)
{
    if (i >= argc) { *val = def; return FX_OK; }
    char *end;
    *val = strtod(argv[i], &end);
    if (end == argv[i] || *end != '\0') {
        fprintf(stderr, "bad number: '%s'\n", argv[i]);
        return FX_EARG;
    }
    return FX_OK;
}

int fx_run_chain(const audio_t *in, audio_t *out, int argc, char **argv)
{
    audio_t cur;
    int rc = audio_copy(in, &cur);
    if (rc != FX_OK) return rc;

    int i = 0;
    while (i < argc) {
        const fx_entry_t *e = fx_find(argv[i]);
        if (!e) {
            fprintf(stderr, "unknown effect: '%s' (use --list)\n", argv[i]);
            audio_free(&cur);
            return FX_EARG;
        }
        int j = i + 1;                         /* 此效果器的參數到下一個效果器名稱為止 */
        while (j < argc && !fx_find(argv[j])) j++;

        audio_t next = {0, 0, 0, NULL};
        rc = e->run(&cur, &next, j - i - 1, argv + i + 1);
        audio_free(&cur);
        if (rc != FX_OK) {
            if (rc == FX_ENOTIMPL) fprintf(stderr, "effect '%s' is not implemented yet\n", e->name);
            else                   fprintf(stderr, "effect '%s' failed. usage: %s %s\n", e->name, e->name, e->usage);
            audio_free(&next);
            return rc;
        }
        cur = next;
        i = j;
    }
    *out = cur;
    return FX_OK;
}
