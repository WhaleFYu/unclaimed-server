#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "chunkify.h"
static int cb(void *c, uint8_t *b, size_t n) { (void)c; (void)b; (void)n; return 0; }
static void on_alarm(int s) { (void)s; fprintf(stderr, "RESULT: HANG (timeout)\n"); _exit(3); }
int main(void) {
    signal(SIGALRM, on_alarm);
    unsigned long sizes[] = {0,1,2,3,4};
    for (int i = 0; i < 5; i++) {
        alarm(5);
        CHUNKIFIER *c = chunkify_init((uint32_t)sizes[i], 64, cb, NULL);
        alarm(0);
        printf("meanlen=%lu -> %s\n", sizes[i], c ? "OK" : "NULL (rejected)");
        fflush(stdout);
        if (c) chunkify_free(c);
    }
    return 0;
}
