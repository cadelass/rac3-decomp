/* PAL retry (2026-11-17): 2 raw differing words after the verified divs_nops row of 2.
 * Reproduced baseline: 43 with missing padding. The old split VU form
 * carried implicit vf2 state and is not an accepted match. This legal
 * unified block still swaps the decrement and sqc2 at +0x74/+0x78.
 * Existing j-operand helpers require a proven whole-file VU flag decision.
 * Exact check: tools/check.py this_file.c func_L01_0037F860 --target level_01.
 * See docs/research/level01-shared-nonmatching-20261117.md. */
/* Prior attempt metadata (historical): */
/* PAL near miss (Codex wave 6): near miss: 0 words differ with the file's flags.
 * Worker's note: AUDIT SOURCE HOLD: Split VU sequence carries vf2 implicitly across asm blocks around i--; single block required, unified candidate has 43 raw diffs; w288/func_L01_0037F860.final.log: ALL_PLACES_MATCH func_L01_0037F860 34; TYPE_CONTRACT_PASS; NEEDS divs row ...
 */
#include "common.h"
/* localdecomp:start func_L01_0037F860 */
typedef int Q_0037F860 __attribute__((mode(TI)));
typedef struct {f32 x,y,z,w;} __attribute__((aligned(16))) V_0037F860;
extern s32 D_L01_001E1DC0;
extern f32 D_L01_001DDB84;
extern f32 D_L01_001E1DD0;
extern Q_0037F860 D_L01_0028F5A0[];
extern s32 D_L01_001DDBE8,D_L01_001DDBF0,D_L01_001DDBF4;
extern s32 D_L01_001E1DD4;
extern s32 D_L01_001E1E84;
extern u8 D_L01_001E1E80[3] __attribute__((section(".sdata")));
__asm__(".extern D_L01_001E1E80, 16");
extern Q_0037F860 D_L01_001E1E10[3] __attribute__((section(".sdata")));
__asm__(".extern D_L01_001E1E10, 48");
__asm__(".extern D_L01_001DDB84, 4");
__asm__(".extern D_L01_001E1DD0, 4");
__asm__(".extern D_L01_001DDBE8, 4");
__asm__(".extern D_L01_001DDBF0, 4");
__asm__(".extern D_L01_001DDBF4, 4");
__asm__(".extern D_L01_001E1DC0, 16");
__asm__(".extern D_L01_001E1DD4, 16");
__asm__(".extern D_L01_001E1E84, 16");
void func_L01_0037F860(u8 *m) {
 extern void func_0038CE20(Q_0037F860 *,Q_0037F860 *,f32);
 V_0037F860 step;
 Q_0037F860 *v=*(Q_0037F860 **)(m+0x68);
 s32 i,j;
 Q_0037F860 *p;
 if(D_L01_001E1DC0) {
  D_L01_001E1DC0=0;
  D_L01_001E1DD0=D_L01_001DDB84/12.0f;
  func_0038CE20((Q_0037F860 *)&step,(Q_0037F860 *)(m+0xC0),-D_L01_001E1DD0);
  D_L01_0028F5A0[0]=v[0];
  p=D_L01_0028F5A0+1;
  i=10;
  do {
   __asm__ __volatile__(
       "lqc2 vf2,%1\n\tlqc2 vf1,%2\n\tvadd.xyz vf2,vf2,vf1\n\tsqc2 vf2,%0"
       : "=m"(p[0]) : "m"(p[-1]), "m"(step) : "vf1", "vf2");
   i--;
   p++;
  } while(i>=0);
  D_L01_001DDBE8=0;D_L01_001DDBF0=0;D_L01_001DDBF4=0;
  D_L01_001E1DD4=0;D_L01_001E1E84=0;
  for(j=0;j<3;j++) {
   D_L01_001E1E10[j]=*(Q_0037F860 *)&step;
   D_L01_001E1E80[j]=0;
  }
 }
}
/* localdecomp:end func_L01_0037F860 */
