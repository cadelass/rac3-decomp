/* PAL near miss (Codex wave 7): near miss: 2 words differ with the file's flags.
 * Best form (2026-11-17): naming the first loop's 0xFFFF as `u16 empty` extends its
 * live range (30 vs 26 luids) and lowers its priority below `ready` (0.333 vs
 * 0.341), which fixes the $s3/$s4 pair; 10 -> 2 diffs. The 2 left are the second
 * loop's two 0xFFFF: its condition literal is folded, so the store `e` and it swap
 * $t1/$t2.
 */
#include "common.h"

extern u16 D_001D54D8[32] __attribute__((section(".sdata")));
extern u16 D_001D5516;
s32 func_L01_004226C8(void) {
    extern s32 func_L01_00419CC0(s32);
    s32 i, j, n, e;
    s32 ready = 1;
    u16 empty = 0xFFFF;
    u16 *p = D_001D54D8;
    for (i = 31; i >= 0; i--, p++) {
        if (*p != empty) {
            s32 id = *p & 0x3FFF;
            if (!func_L01_00419CC0(id) || id == 0) {
                *p = empty;
                ready = 0;
            }
        }
    }
    i = 0;
    e = 0xFFFF;
    while (i < 32) {
        n = i + 1;
        if (D_001D54D8[i] == 0xFFFF) {
            for (j = n; j < 32; j++) {
                u16 v = D_001D54D8[j];
                if (v != 0xFFFF) ready = 1;
                D_001D54D8[j-1] = v;
            }
            D_001D5516 = e;
        }
        i = n;
    }
    return ready;
}
