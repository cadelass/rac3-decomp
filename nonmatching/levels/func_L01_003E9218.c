/* PAL retry (2026-11-17): 11 raw differing words, improved from a declaration compile error.
 * Retail passes both a vector pointer in a1 and an independent f12 value.
 * The corrected declaration compiles here, but still conflicts with a later
 * owner prototype; VU interleaving also remains. No flag override was used.
 * Exact check: tools/check.py this_file.c func_L01_003E9218 --target level_01.
 * See docs/research/level01-shared-nonmatching-20261117.md. */
/* Prior attempt metadata (historical): */
/* PAL near miss (Codex wave 8): near miss: does not compile in its file's context yet (declaration conflicts; the worker's note at the top has the details).
 * Worker's note: Compile blocked by existing callee signature void func_L01_003E8FE8(u8 *, f32): retail passes stack vector pointer in a1 (offset 0x10), no mtc1; existing func_L01_003E9218(u8 *, f32) also contradicts live pointer a1 at entry. Requires both signatures ...
 */
#include "common.h"
/* localdecomp:start func_L01_003E9218 */
typedef struct { f32 x,y,z,w; } __attribute__((aligned(16))) Vec_003E9218;
/* The integer vector argument and independent f12 value are passed onward. */
void func_L01_003E9218(u8 *camera, Vec_003E9218 *position, f32 amount) {
    extern void func_L01_003E8FE8_003E9218(u8 *, Vec_003E9218 *, f32);
    Vec_003E9218 delta;
    u8 *follow=*(u8 **)(camera+0x70);
    __asm__ __volatile__("lqc2 $vf1, %1\n\tlqc2 $vf2, %2\n\tvsub.xyz $vf1, $vf1, $vf2\n\tsqc2 $vf1, %0"
        : "=m"(delta) : "m"(*position), "m"(*(Vec_003E9218 *)(follow+0x60)) : "vf1", "vf2");
    func_L01_003E8FE8_003E9218(camera,&delta,amount);
}
/* localdecomp:end func_L01_003E9218 */
