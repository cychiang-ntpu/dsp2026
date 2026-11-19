/* main.c — 命令列進入點。已實作完成，通常不需修改。
 *
 *   ./fx in.wav out.wav effect1 [params...] [effect2 [params...] ...]
 *   ./fx input.wav output.wav eq lowpass 4000 echo 0.3 0.5 reverb 0.8
 *   ./fx --list
 */
#include <stdio.h>
#include <string.h>
#include "fx.h"
#include "wav.h"

static void usage(const char *prog)
{
    fprintf(stderr, "usage: %s in.wav out.wav effect1 [params...] [effect2 [params...] ...]\n", prog);
    fprintf(stderr, "       %s --list\n", prog);
}

int main(int argc, char *argv[])
{
    if (argc == 2 && !strcmp(argv[1], "--list")) {
        for (int i = 0; i < fx_count; i++)
            printf("%-12s %s\n", fx_table[i].name, fx_table[i].usage);
        return 0;
    }
    if (argc < 3) { usage(argv[0]); return 1; }

    audio_t in, out;
    int rc = wav_read(argv[1], &in);
    if (rc != FX_OK) return rc;
    printf("input : %s  (%d Hz, %d ch, %lu frames, %.3f s)\n",
           argv[1], in.fs, in.ch, (unsigned long)in.frames, (double)in.frames / in.fs);

    rc = fx_run_chain(&in, &out, argc - 3, argv + 3);
    audio_free(&in);
    if (rc != FX_OK) return rc;

    long clipped = 0;
    rc = wav_write(argv[2], &out, &clipped);
    if (rc == FX_OK) {
        printf("output: %s  (%d Hz, %d ch, %lu frames, %.3f s)\n",
               argv[2], out.fs, out.ch, (unsigned long)out.frames, (double)out.frames / out.fs);
        if (clipped > 0)
            printf("WARNING: %ld samples clipped (output too loud; lower the gain)\n", clipped);
    }
    audio_free(&out);
    return rc;
}
