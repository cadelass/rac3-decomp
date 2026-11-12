/*
 * func_L27_004CA9C8  (level 27, Aquatos Base)  - PARTIAL reconstruction.
 * Catalogue size 0x55E8 = 21992 bytes = 5498 words (header says 5369 instructions;
 * the .s spans 5374 words including the 8-word slack at 0x4CFFB0).
 *
 * WHAT THIS FILE RECONSTRUCTS (in retail block order):
 *   - The prologue and the switch dispatch (0x4CA9C8..0x4CAA48): frame 0x100, saved
 *     GPRs s0-s7/fp/ra and f20-f23, the state/oldStep/snapshot loads, the
 *     `sltiu $3,$4,0xB2` guard and the jump-table call.
 *   - The whole physical body of the first jump-table group (0x4CAA48..0x4CAF80),
 *     which is the target of states
 *     0x00,0x01,0x03,0x04,0x1C,0x1D,0x1E,0x39,0x72,0x74,0x82:
 *       * three common calls (F0558/F52E0/EE850),
 *       * the state==1||0x1D guard and its snapshot/statistics update,
 *       * the state==3 func_004D7448 gate,
 *       * the state==4 animation/lean block (L4CABCC..L4CAD68),
 *       * the state==3 scale block (L4CAD7C..L4CAE94),
 *       * the shared tail L4CAEBC..L4CAF7C (two particle/vector calls and the
 *         0x1479/0x142CAD gate), including the L4CFF00 and L4CFF34 tails it jumps to.
 *   - The end chain (0x4CFF44..0x4CFFAC): qzero for states 0x3C/0x64/0x65, the
 *     oldStep/animation change clears at +0x1C0/+0x1C4, and the epilogue.
 *   - One VU0 case group, 0x49/0x4A at 0x4CFA20..0x4CFB78: its two vsub triples, one
 *     vadd triple and the vec_add/vec_sub sequences are written with the
 *     include/vu0.h vec_* helpers (retail's exact operand/load order picked the
 *     _ab/_ba form); it also shows the func_0038CE90 argument swap by state.
 *   - ALL 178 jump-table cases are listed (0x00..0xB1) and routed to the correct
 *     retail block name; every block we did not transcribe goes to `finish` with a
 *     comment giving its retail address. This keeps the dispatch shape (dense table,
 *     bound 0xB2) and documents the full case -> block map.
 *
 * WHAT IS MISSING: the other 45 jump-table blocks (see the case map at the bottom).
 * They are ~5000 instructions of per-state gameplay code.  Each block was decoded
 * far enough to name its callees and data (see the case map); the bodies are not
 * transcribed.
 *
 * KNOWN CODEGEN GAPS vs retail (this cannot match yet):
 *   - The prologue saves s0-s7/fp/f20-f23 because the full function uses them; this
 *     partial uses far fewer, so the save sequence differs even though every
 *     instruction in the reconstructed part is a faithful translation.
 *   - Block order: gcc places switch bodies in source order; retail interleaves the
 *     46 blocks (the case map below is retail address order, not source order).
 *   - The twin draft nonmatching/levels/func_L08_004D6580.c (0.991 to this function,
 *     same family A1 in docs/contributing/large-function-families.md) is the best
 *     starting point for the missing bodies; it is 4128 instructions of C and needs
 *     L27 constants/callees and D_L27 names.
 *   - VU0: this function has 46 lqc2 / 22 sqc2 / 23 COP2 arithmetic words (91 COP2
 *     total). The rebuilt 0x49/0x4A group uses vec_sub_ab/vec_sub_ba/vec_add_ab/
 *     vec_add_ba from include/vu0.h; those need -mvu0-use-vf0-vf2 on this file's
 *     flag line (the line currently lacks it). The other blocks' VU0 triples are
 *     the same helpers (see the case map / the L08 twin draft).
 *
 * FLAGS (config/levels/text_parts.txt:1631):
 *   -O2 -G8 -fopt-stack -mno-check-zero-division
 * This candidate is checked with `--as ps2as` (retail builds every float constant
 * inline `lui`/`ori`/`mtc1`) and `--flags=-mvu0-use-vf0-vf2` for the vec_* helpers.
 * The owning file's line would therefore need `@ps2as` and, once VU0 C lands,
 * `-mvu0-use-vf0-vf2` (whole-file flags; it has no other C yet).
 * div.s: 12 in retail; the two in the rebuilt state==4 block are at 0x4CACEC and
 * 0x4CACF0. Retail's nop counts in order are `2 0 2 0 0 2 0 0 0 2 0 2`, exactly
 * the row the twin func_L08_004D6580 already has in config/levels/divs_nops.txt;
 * func_L27_004CA9C8 needs the same row (not added; repo untouched). No sqrt.s.
 */

#include "common.h"
#include "vu0.h"

typedef int u128_t __attribute__((mode(TI)));

/* The single player-state object (same views as L27_004D1568.c). */
typedef union {
    u8 b[0x2A00];
    s16 h[0x1500];
    u16 uh[0x1500];
    s32 i[0xA80];
    u32 u[0xA80];
    f32 f[0xA80];
    u8 *ptr[0xA80];
    u128_t q[0x2A0];
} Hero;

typedef struct { u16 count; u16 pad; u32 maximum; u32 levels; } Statistics;

extern Hero D_001A4BE0;              /* 0x001A4BE0, core player state        */
extern u8 D_001A4CD0[];              /* 0x001A4CD0, 16-byte particle state   */
extern Statistics D_001A7C10[];      /* 0x001A7C10, stat rows                */
extern s32 D_001D4C38;               /* 0x001D4C38, gp -0x7C78               */
extern u32 D_001D545C;               /* 0x001D545C, gp? absolute here        */
extern u8 D_00142CAD;                /* 0x00142CAD, core flag byte           */
extern u8 D_L27_001E1A00[];          /* level data, read as base-0x368       */
extern u8 D_001A4C60[];              /* 0x001A4C60, core vector anchor       */
extern f32 D_L27_002F2380[];         /* level data, vector scale table       */

extern void func_L01_004F0558(f32, f32);
extern void func_L01_004F52E0(f32, f32, f32);
extern void func_L01_004EE850(f32, s32);
extern void func_0038D000(void *, void *, void *);
extern void func_L01_004EEDD0(s32, f32, f32, f32);
extern s32 func_L01_00507268(void);
extern void func_L01_0050FB40(s32, s32, f32);
extern void func_L01_004E5030(f32, f32, f32, f32);
extern void func_L01_004EF128(f32, f32);
extern void func_L01_004F4730(f32);
extern void func_L01_00510F08(s32, s32, f32);
extern void func_L01_004F3F40(void);
extern f32 func_0038D160(f32, f32);
extern s32 func_0038CE90(void *, void *, void *);
extern void func_0038CF68(void *, void *, f32);
extern s32 func_L01_004E8318(s32, s32, s32);

/* Retail jump-table group boundaries (level-27 addresses).
 *
 *    0x4CAA48  0x00 0x01 0x03 0x04 0x1C 0x1D 0x1E 0x39 0x72 0x74 0x82  <- reconstructed
 *    0x4CAF80  0x32 0x33 0x34
 *    0x4CBCF8  0x78
 *    0x4CBD68  0x77
 *    0x4CBDAC  0x6C 0x84
 *    0x4CBF5C  0x35 0x36
 *    0x4CC224  0x2F
 *    0x4CC394  0x14
 *    0x4CC890  0x15 0x88
 *    0x4CCBC4  0x13
 *    0x4CD144  0x7C
 *    0x4CD294  0x22
 *    0x4CD378  0x02 0x75
 *    0x4CDAD0  0x80
 *    0x4CDE78  0x17 0x18
 *    0x4CDF1C  0x46 0x47
 *    0x4CDFBC  0x19 0x1A
 *    0x4CE0DC  0x06 0x2C
 *    0x4CE120  0x79
 *    0x4CE1D8  0x08
 *    0x4CE400  0x07 0x09 0x0A 0x0B 0x0C 0x0D 0x0E 0x0F 0x10 0x11 0x12 0x1B
 *              0x38 0x45 0x48 0x54 0x5F 0x69 0x6B 0x73 0x86 0xA2 0xA7 0xAC
 *    0x4CEB58  0x16 0xB1
 *    0x4CEC0C  0x91
 *    0x4CEC3C  0x66
 *    0x4CF004  0x67
 *    0x4CF09C  0x68
 *    0x4CF108  0x6A
 *    0x4CF180  0x7D
 *    0x4CF1B0  0x3F 0x43
 *    0x4CF244  0x4D
 *    0x4CF560  0x4B
 *    0x4CF5F4  0x4E 0x7B
 *    0x4CF640  0x4F
 *    0x4CF664  0x41
 *    0x4CF6BC  0x44
 *    0x4CF700  0x40 0x4C
 *    0x4CF9B8  0x42
 *    0x4CFA20  0x49 0x4A
 *    0x4CFB7C  0x51 0x56 0x59
 *    0x4CFC20  0x57
 *    0x4CFC74  0x58
 *    0x4CFC88  0x53
 *    0x4CFD30  0x52
 *    0x4CFEA0  0x55
 *    0x4CFF44  0x3C 0x64 0x65   (qzero then finish)
 *    0x4CFF50  default + 0x05 0x1F..0x2B(ex 0x2C) 0x2D..0x31 0x37 0x3A 0x3B ...
 *              (the common epilogue tail)
 */

s32 func_L27_004CA9C8(void) {
    u8 *snap;
    u32 state;
    s32 oldStep;
    u8 anim;
    f32 f20, f21;
    f32 f0, f1, f2, f13;
    s32 a;

    snap = D_001A4BE0.ptr[0x970];        /* 0x25C0 */
    state = D_001A4BE0.u[0x971];         /* 0x25C4 */
    oldStep = D_001A4BE0.i[0x972];       /* 0x25C8 */
    anim = snap[0x43];

    switch (state) {

    /* ---- 0x4CAA48: the common group body ------------------------------- */
    case 0x00: case 0x01: case 0x03: case 0x04:
    case 0x1C: case 0x1D: case 0x1E:
    case 0x39: case 0x72: case 0x74: case 0x82: {
        func_L01_004F0558(0.5f, 0.04000000283122063f);
        func_L01_004F52E0(3.700000047683716f, 0.0f, 0.3499999940395355f);
        func_L01_004EE850(1.0f, 0);

        if (state == 0x01 || state == 0x1D) {
            if (D_001A4BE0.b[0x25E5]) {
                u8 v[16];
                *(u128_t *)v = 0;
                *(f32 *)v = 1.0f;
                func_0038D000(D_001A4BE0.b + 0x190, v, D_L27_001E1A00);
                f0 = *(f32 *)((u8 *)D_L27_001E1A00 - 0x368);
                func_L01_004EEDD0(0, 1.440000057220459f, 0.0f, 3.490658760070801f);
                D_001A4BE0.f[0x68] = f0;                 /* 0x1A0 */
                if (D_001A4BE0.b[0x25EC] && D_001A4BE0.i[0x6E] == 0x64) {
                    if (D_001A7C10[18].count < 0xFFFF) D_001A7C10[18].count++;
                    if (D_001A7C10[18].maximum < (u32)((D_001D4C38 * 5 + 2) / 6))
                        D_001A7C10[18].maximum = (u32)((D_001D4C38 * 5 + 2) / 6);
                    D_001A7C10[18].levels =
                        (D_001A7C10[18].levels | (1u << D_001D545C)) | 0x80000000u;
                }
            }
        }
        goto L_4CAB9C;
    }

    /* ---- 0x4CAF80: 0x32 0x33 0x34 ------------------------------------- */
    case 0x32: case 0x33: case 0x34: goto finish;   /* retail 0x004CAF80 */

    /* ---- 0x4CBCF8: 0x78 ------------------------------------------------ */
    case 0x78: goto finish;                          /* retail 0x004CBCF8 */

    /* ---- 0x4CBD68: 0x77 ------------------------------------------------ */
    case 0x77: goto finish;                          /* retail 0x004CBD68 */

    /* ---- 0x4CBDAC: 0x6C 0x84 ------------------------------------------ */
    case 0x6C: case 0x84: goto finish;               /* retail 0x004CBDAC */

    /* ---- 0x4CBF5C: 0x35 0x36 ------------------------------------------ */
    case 0x35: case 0x36: goto finish;               /* retail 0x004CBF5C */

    /* ---- 0x4CC224: 0x2F ------------------------------------------------ */
    case 0x2F: goto finish;                          /* retail 0x004CC224 */

    /* ---- 0x4CC394: 0x14 ------------------------------------------------ */
    case 0x14: goto finish;                          /* retail 0x004CC394 */

    /* ---- 0x4CC890: 0x15 0x88 ------------------------------------------ */
    case 0x15: case 0x88: goto finish;               /* retail 0x004CC890 */

    /* ---- 0x4CCBC4: 0x13 ------------------------------------------------ */
    case 0x13: goto finish;                          /* retail 0x004CCBC4 */

    /* ---- 0x4CD144: 0x7C ------------------------------------------------ */
    case 0x7C: goto finish;                          /* retail 0x004CD144 */

    /* ---- 0x4CD294: 0x22 ------------------------------------------------ */
    case 0x22: goto finish;                          /* retail 0x004CD294 */

    /* ---- 0x4CD378: 0x02 0x75 ------------------------------------------ */
    case 0x02: case 0x75: goto finish;               /* retail 0x004CD378 */

    /* ---- 0x4CDAD0: 0x80 ------------------------------------------------ */
    case 0x80: goto finish;                          /* retail 0x004CDAD0 */

    /* ---- 0x4CDE78: 0x17 0x18 ------------------------------------------ */
    case 0x17: case 0x18: goto finish;               /* retail 0x004CDE78 */

    /* ---- 0x4CDF1C: 0x46 0x47 ------------------------------------------ */
    case 0x46: case 0x47: goto finish;               /* retail 0x004CDF1C */

    /* ---- 0x4CDFBC: 0x19 0x1A ------------------------------------------ */
    case 0x19: case 0x1A: goto finish;               /* retail 0x004CDFBC */

    /* ---- 0x4CE0DC: 0x06 0x2C ------------------------------------------ */
    case 0x06: case 0x2C: goto finish;               /* retail 0x004CE0DC */

    /* ---- 0x4CE120: 0x79 ------------------------------------------------ */
    case 0x79: goto finish;                          /* retail 0x004CE120 */

    /* ---- 0x4CE1D8: 0x08 ------------------------------------------------ */
    case 0x08: goto finish;                          /* retail 0x004CE1D8 */

    /* ---- 0x4CE400: the movement/common states ------------------------- */
    case 0x07: case 0x09: case 0x0A: case 0x0B: case 0x0C: case 0x0D:
    case 0x0E: case 0x0F: case 0x10: case 0x11: case 0x12: case 0x1B:
    case 0x38: case 0x45: case 0x48: case 0x54: case 0x5F: case 0x69:
    case 0x6B: case 0x73: case 0x86: case 0xA2: case 0xA7: case 0xAC:
        goto finish;                                 /* retail 0x004CE400 */

    /* ---- 0x4CEB58: 0x16 0xB1 ------------------------------------------ */
    case 0x16: case 0xB1: goto finish;               /* retail 0x004CEB58 */

    /* ---- 0x4CEC0C: 0x91 ------------------------------------------------ */
    case 0x91: goto finish;                          /* retail 0x004CEC0C */

    /* ---- 0x4CEC3C: 0x66 ------------------------------------------------ */
    case 0x66: goto finish;                          /* retail 0x004CEC3C */

    /* ---- 0x4CF004: 0x67 ------------------------------------------------ */
    case 0x67: goto finish;                          /* retail 0x004CF004 */

    /* ---- 0x4CF09C: 0x68 ------------------------------------------------ */
    case 0x68: goto finish;                          /* retail 0x004CF09C */

    /* ---- 0x4CF108: 0x6A ------------------------------------------------ */
    case 0x6A: goto finish;                          /* retail 0x004CF108 */

    /* ---- 0x4CF180: 0x7D ------------------------------------------------ */
    case 0x7D: goto finish;                          /* retail 0x004CF180 */

    /* ---- 0x4CF1B0: 0x3F 0x43 ------------------------------------------ */
    case 0x3F: case 0x43: goto finish;               /* retail 0x004CF1B0 */

    /* ---- 0x4CF244: 0x4D ------------------------------------------------ */
    case 0x4D: goto finish;                          /* retail 0x004CF244 */

    /* ---- 0x4CF560: 0x4B ------------------------------------------------ */
    case 0x4B: goto finish;                          /* retail 0x004CF560 */

    /* ---- 0x4CF5F4: 0x4E 0x7B ------------------------------------------ */
    case 0x4E: case 0x7B: goto finish;               /* retail 0x004CF5F4 */

    /* ---- 0x4CF640: 0x4F ------------------------------------------------ */
    case 0x4F: goto finish;                          /* retail 0x004CF640 */

    /* ---- 0x4CF664: 0x41 ------------------------------------------------ */
    case 0x41: goto finish;                          /* retail 0x004CF664 */

    /* ---- 0x4CF6BC: 0x44 ------------------------------------------------ */
    case 0x44: goto finish;                          /* retail 0x004CF6BC */

    /* ---- 0x4CF700: 0x40 0x4C ------------------------------------------ */
    case 0x40: case 0x4C: goto finish;               /* retail 0x004CF700 */

    /* ---- 0x4CF9B8: 0x42 ------------------------------------------------ */
    case 0x42: goto finish;                          /* retail 0x004CF9B8 */

    /* ---- 0x4CFA20: 0x49 0x4A (VU0 block) ------------------------------- */
    case 0x49: case 0x4A: {
        vu0_v4 t00, t40, t50, t60;
        f32 ret;
        s32 idx;
        D_001A4BE0.f[0xC00 / 4] = 1.2999999523162842f;
        vec_sub_ba(D_001A4BE0.b + 0x190, D_001A4BE0.b + 0x510,
                   D_001A4BE0.b + 0x500);
        ret = func_0038D160(*(f32 *)(D_001A4BE0.b + 0x190),
                            *(f32 *)(D_001A4BE0.b + 0x194));
        func_L01_004EEDD0(0, 0.028800001367926598f, 0.2880000174045563f,
                          0.09424778819084167f);
        D_001A4BE0.f[0x1A0 / 4] = ret;
        vec_sub_ab(&t60, D_001A4BE0.b + 0x510, D_001A4BE0.b + 0x500);
        qzero(D_001A4BE0.b + 0xF0);
        if (D_001A4BE0.u[0x971] == 0x49)
            func_0038CE90(&t40, D_001A4BE0.b + 0x2E0, &t60);
        else
            func_0038CE90(&t40, &t60, D_001A4BE0.b + 0x2E0);
        func_0038CF68(&t40, &t40, 0.20000000298023224f);
        vec_add_ba(&t50, D_001A4C60, &t40);
        if (func_L01_004E8318((s32)D_001A4C60, (s32)(D_001A4C60 + 0x10), 0) == 0)
            goto finish;
        if (func_L01_004E8318((s32)&t50, (s32)(D_001A4C60 + 0x10), (s32)&t00) == 0)
            goto finish;
        vec_sub_ba(D_001A4C60 + 0x70, &t00, D_001A4C60);
        idx = (s32)*(f32 *)(D_001A4C60 + 0xB98);
        func_0038CF68(D_001A4C60 + 0x70, D_001A4C60 + 0x70,
                      D_L27_002F2380[idx] * 0.5f);
        goto finish;
    }

    /* ---- 0x4CFB7C: 0x51 0x56 0x59 ------------------------------------- */
    case 0x51: case 0x56: case 0x59: goto finish;    /* retail 0x004CFB7C */

    /* ---- 0x4CFC20: 0x57 ------------------------------------------------ */
    case 0x57: goto finish;                          /* retail 0x004CFC20 */

    /* ---- 0x4CFC74: 0x58 ------------------------------------------------ */
    case 0x58: goto finish;                          /* retail 0x004CFC74 */

    /* ---- 0x4CFC88: 0x53 ------------------------------------------------ */
    case 0x53: goto finish;                          /* retail 0x004CFC88 */

    /* ---- 0x4CFD30: 0x52 ------------------------------------------------ */
    case 0x52: goto finish;                          /* retail 0x004CFD30 */

    /* ---- 0x4CFEA0: 0x55 ------------------------------------------------ */
    case 0x55: goto finish;                          /* retail 0x004CFEA0 */

    /* ---- 0x4CFF44: 0x3C 0x64 0x65 (clear the particle state, then end) - */
    case 0x3C: case 0x64: case 0x65:
        qzero(D_001A4CD0);
        goto finish;

    /* ---- unnamed/Z: 0x05 0x1F..0x2B 0x2D..0x31 0x37 0x3A 0x3B 0x3D..0x5E ...
     *      (every value 0x00..0xB1 without a body above lands on 0x4CFF50) - */
    default:
        goto finish;                                 /* retail 0x004CFF50 */
    }

    /* ---- L4CAB9C: state==3 gate then the state==4 lean block ----------- */
L_4CAB9C:
    if (D_001A4BE0.u[0x971] == 3 && func_L01_00507268() != 0) goto finish;
    if (D_001A4BE0.u[0x971] != 4) goto L_4CAD6C;

    if (!(0.20000000298023224f < D_001A4BE0.f[0x2838 / 4]) &&
        anim != 0x0E && anim != 0x0F)
        goto L_4CAD6C;

    if (D_001A4BE0.u[0x971] == 4)
        func_L01_004EEDD0(0, 0.002880000276491046f, 0.10080000758171082f,
                          0.19896754622459412f);

    f2 = D_001A4BE0.f[0x1A4 / 4];
    if (0.0069813174195587635f < fabs_asm(f2)) {
        a = (f2 < 0.0f) ? 1 : 0;
        if (anim != (u8)(a + 0x0E))
            func_L01_0050FB40(a + 0x0E, 0, 4.0f);
        f0 = fabs_asm(f2) * 5.0f;
        f0 = f0 / 6.0f;
        f0 = f0 / 0.06632252037525177f;
        D_001A4BE0.f[0xC00 / 4] = f0;
        if (f0 < 0.550000011920929f) D_001A4BE0.f[0xC00 / 4] = 0.550000011920929f;
        if (2.5f < D_001A4BE0.f[0xC00 / 4]) D_001A4BE0.f[0xC00 / 4] = 2.5f;
    } else {
        if (f2 == 0.0f && anim != 0x0D)
            func_L01_0050FB40(0x0D, 0, 6.0f);
    }
    goto L_4CAD6C;

    /* ---- L4CAD6C: state==3 scale/logic, else pick the shared scale ----- */
L_4CAD6C:
    D_001A4BE0.i[0x1B0 / 4] = 0;
    if (state == 3) {
        f1 = 1.0f;
        f13 = D_001A4BE0.f[0x17C / 4] + f1;
        if (f1 < f13) f13 = f1;
        f20 = f13 * 0.01080000028014183f;
        D_001A4BE0.f[0x282C / 4] = f20;
        if (snap[0x42] == snap[0x43]) {
            f13 = D_001A4BE0.f[0x174 / 4] / f20;
            if (4.0f < f13 && (f32)snap[0x41] < 5.0f) {
                func_L01_004E5030(20.0f, f13, 0.5f, -1.0f);
                if (1.100000023841858f < D_001A4BE0.f[0xC00 / 4])
                    D_001A4BE0.f[0xC00 / 4] = 1.100000023841858f;
            } else if (6.5f < (f32)snap[0x41]) {
                D_001A4BE0.f[0xC00 / 4] = 1.0f;
            }
        }
    } else {
        f20 = (state == 4) ? 0.01080000028014183f : 0.007080000825226307f;
    }

    /* ---- L4CAEBC: shared tail ------------------------------------------ */
L_4CAEBC:
    f21 = 0.0f;
    func_L01_004EF128(0.0f, f20);
    qzero(D_001A4CD0);
    func_L01_004F4730(f20);

    if (D_001A4BE0.b[0x1479] && D_00142CAD) {
        if (0.20000000298023224f < D_001A4BE0.f[0x33C / 4])
            goto L_4CFF00;
        func_L01_00510F08((s32)D_001A4CD0, (s32)D_001A4CD0,
                          0.02160000056028366f);
        if (D_001A4BE0.i[0x35C / 4] != 0) {
            *(u128_t *)(D_001A4BE0.b + 0x80) =
                *(u128_t *)(D_001A4BE0.b + 0x2F0);
            D_001A4BE0.f[0x33C / 4] = f21;
            D_001A4BE0.h[0x36E / 2] = 0;
        }
        goto finish;
    }

    func_L01_004F3F40();
    if (D_001A4BE0.h[0x36E / 2] != 0)
        goto finish;                       /* retail .L004CFE64, not reconstructed */
    func_L01_00510F08((s32)(D_001A4BE0.b + 0xF0),
                      (s32)(D_001A4BE0.b + 0xF0), 0.02160000056028366f);
    goto finish;

    /* ---- L4CFF00: tail reached from the particle gate ------------------ */
L_4CFF00:
    func_L01_00510F08((s32)D_001A4CD0, (s32)(D_001A4CD0 + 0x30),
                      0.008799999952316284f);
    goto finish;

    /* ---- end chain (0x4CFF50/0x4CFF54) --------------------------------- */
finish:
    if (oldStep != D_001A4BE0.i[0x25C8 / 4])
        D_001A4BE0.i[0x1C0 / 4] = 0;
    if (anim != D_001A4BE0.ptr[0x970][0x43])
        D_001A4BE0.i[0x1C4 / 4] = 0;
    return 0;
}
