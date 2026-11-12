#include "common.h"
#include "structs/moby.h"

/* func_L27_004D7CD8 (level 27, 0x004D7CD8, 0x5F74 bytes): the hero per-frame "decider", a
 * member of the large-function family B (docs/contributing/large-function-families.md), rac2
 * func_L12_002CF7B0 family.  One function, 0xB0 frame, one switch on the hero state (+0x25C4)
 * with 0xB2 = 178 entries (jtbl_002C0EA0); 88 of the cases go to the default block at
 * 0x004DDBAC.  Retail has no COP2/lqc2/sqc2, one div.s (0x004DB70C, two nops before it), and
 * 15 lq/sq words (three 16-byte stack slots at 0x00/0x10/0x20).
 *
 * STATUS (2026-11-12): compiles with the file's flags; check.py reports 5665 diff of 6109
 * retail words.  The entry guards' instruction sequence matches retail opcode for opcode after
 * the prologue; the words do not match positionally because the prologue differs: this
 * candidate has frame 0x30 and saves s0-s4 and ra, retail has frame 0xB0 and saves
 * s3,s0,s1,s2,s4,s5,s6,s7,ra,f20,f21 (the extra registers and the three 16-byte $sp slots come
 * from the case bodies that are not reconstructed yet).  Remaining causes, in order:
 * (1) the missing bodies: register pressure and stack locals, hence prologue/frame;
 * (2) block layout: the 55 unreconstructed case entry blocks and the ~5700 words behind the
 * switch are absent, so every word after 0x004D7FBC diverges;
 * (3) the switch table derived from this partial switch points at this file's labels.
 *
 * This candidate reconstructs the entry guards (0x004D7CD8-0x004D7F98), the dispatch and the
 * end chain (0x004DDBAC-0x004DDC48) from retail; every one of the 178 cases is written and
 * mapped to its retail target, but only case 0x00's entry chain and the guards of the other
 * classes are transcribed: the ~5700 words behind them (60 entry blocks, 1295 basic blocks in
 * all) are still TODO.  Offsets below are byte offsets from D_001A4BE0; a landed version
 * should use structs/hero.h (f25C4 = state, f25CC = state_type, f25C8 = substate,
 * f25D0 = prev_state, f25E4 = body_kind, f25ED = no_firing, f2850 = health, f287E =
 * quick_select_delay, f2882 = quick_switch_recent_, f33C = height_above_ground), structs/
 * moby.h (f43 = cur_seq) and structs/pad.h (held at +0x1A0); the rest is unnamed in them.
 * $gp = 0x001DC8B0: -0x67B8($gp) = D_001D60F8_sda, 0x2018($gp) = D_001DE8C8_sda,
 * -0x6174($gp) = D_001D673C_sda, -0xBE0($gp) = D_001DBCD0_sda, -0x75B4($gp) = D_001D52FC.
 */
typedef struct {
    /* 0x0000 */ u8 pad_0[0x88];
    /* 0x0088 */ f32 f88;
    u8 pad_8C[0x1B8 - 0x8C];
    /* 0x01B8 */ s32 f1B8;
    u8 pad_1BC[0x1C0 - 0x1BC];
    /* 0x01C0 */ s32 f1C0;
    /* 0x01C4 */ s32 f1C4;
    u8 pad_1C8[0x1D2 - 0x1C8];
    /* 0x01D2 */ s16 f1D2;
    u8 pad_1D4[0x234 - 0x1D4];
    /* 0x0234 */ s32 f234;
    u8 pad_238[0x33C - 0x238];
    /* 0x033C */ f32 f33C;
    u8 pad_340[0xC08 - 0x340];
    /* 0x0C08 */ s32 fC08;
    u8 pad_C0C[0x121C - 0xC0C];
    /* 0x121C */ u8 f121C;
    u8 pad_121D[0x1228 - 0x121D];
    /* 0x1228 */ s32 f1228;
    u8 pad_122C[0x12F0 - 0x122C];
    /* 0x12F0 */ struct Moby * f12F0;
    u8 pad_12F4[0x1314 - 0x12F4];
    /* 0x1314 */ s32 f1314;
    u8 pad_1318[0x1436 - 0x1318];
    /* 0x1436 */ u8 f1436;
    u8 pad_1437[0x1A04 - 0x1437];
    /* 0x1A04 */ s32 f1A04;
    u8 pad_1A08[0x25C0 - 0x1A08];
    /* 0x25C0 */ struct Moby * f25C0;
    /* 0x25C4 */ s32 f25C4;
    /* 0x25C8 */ s32 f25C8;
    /* 0x25CC */ s32 f25CC;
    /* 0x25D0 */ s32 f25D0;
    u8 pad_25D4[0x25E4 - 0x25D4];
    /* 0x25E4 */ u8 f25E4;
    u8 pad_25E5[0x25E8 - 0x25E5];
    /* 0x25E8 */ u8 f25E8;
    u8 pad_25E9[0x25ED - 0x25E9];
    /* 0x25ED */ u8 f25ED;
    u8 pad_25EE[0x2850 - 0x25EE];
    /* 0x2850 */ s32 f2850;
    u8 pad_2854[0x2877 - 0x2854];
    /* 0x2877 */ u8 f2877;
    u8 pad_2878[0x287E - 0x2878];
    /* 0x287E */ s16 f287E;
    u8 pad_2880[0x2882 - 0x2880];
    /* 0x2882 */ s16 f2882;
} S_A4BE0_4D7CD8;

typedef struct {
    u8 pad_0[0x1A0];
    /* 0x01A0 */ u32 held;
    /* 0x01A4 */ u32 f1A4;
    u8 pad_1A8[0x1C0 - 0x1A8];
    /* 0x01C0 */ u32 f1C0;
    /* 0x01C4 */ u32 f1C4;
} S_Pad_4D7CD8;

extern S_A4BE0_4D7CD8 D_001A4BE0;
extern u8 *D_001D52FC;
__asm__(".extern D_001D52FC, 16");
extern f32 D_001DE9B0;
__asm__(".extern D_001DE9B0, 16");
extern u8 D_00143A06;
__asm__(".extern D_00143A06, 16");
extern u8 D_001439F4;
__asm__(".extern D_001439F4, 16");
extern s32 D_002D3EF0;
__asm__(".extern D_002D3EF0, 16");
extern s32 D_001DE8C8_sda;
__asm__(".extern D_001DE8C8_sda, 4");

extern s32 func_004C3020(s32);
extern void func_004D7560(void);
extern void func_004D1568(s32, s32);
extern s32 func_004D59A0(void);
extern s32 func_004D53E0(void);
extern s32 func_004D5370(void);
extern s32 func_004D52C0(void);
extern void func_003F5F08(s32, s32, void *, void *, void *, s32, s32);
extern void func_003F6870(void);
extern void func_003F68C8(void);
extern void func_003F72A8(void);
extern void func_003F7BD0(void);
extern void func_003F7C18(void);
extern void func_003F8100(void);
extern void func_004518B0(s32);
extern void func_0044F7D0(s32);
extern void func_004D77B8(void);
extern void func_004D7918(void);
extern void func_004B7A00(void);
extern void func_004D6A38(void);
extern s32 func_003C53A0(s32);
extern s32 func_00438568(s32, s32);
extern s32 func_004E1678(s32);
extern s32 func_004DE7B8(void);
extern void func_0041CF80(s32, s32, s32, s32);

void func_L27_004D7CD8(void)
{
    S_Pad_4D7CD8 *pad;
    struct Moby *e = D_001A4BE0.f25C0;
    s32 f234 = D_001A4BE0.f234;
    s32 state_type0 = D_001A4BE0.f25CC;
    s32 substate0 = D_001A4BE0.f25C8;
    u8 seq0;

    seq0 = e->cur_seq;

    if (f234 != 0) {
        func_004C3020(0);
    } else if (func_004C3020(1) != 0) {
        goto L_004DDBB0;
    }
    func_004D7560();
    if (D_001A4BE0.f2850 <= 0 && (D_001A4BE0.f25C4 == 0 || D_001A4BE0.f25C4 == 2)) {
        func_004D1568(0x39, 1);
        goto L_004DDBB0;
    }
    if (func_004D59A0() != 0) goto L_004DDBB0;
    if (func_004D53E0() != 0) goto L_004DDBB0;
    if (func_004D5370() != 0) goto L_004DDBB0;
    if (func_004D52C0() != 0) goto L_004DDBB0;

    pad = (S_Pad_4D7CD8 *)D_001D52FC;
    if ((pad->f1A4 & 0x10) == 0 && (pad->f1C4 & 0x10) == 0) goto L_004D7F2C;
    if (D_001A4BE0.f121C == 2) goto L_004D7F2C;
    if (D_002D3EF0 != 0) goto L_004D7F2C;
    if (D_00143A06 != 0) goto L_004D7F2C;
    if (D_001DE8C8_sda < 8) goto L_004D7F2C;
    if (D_001A4BE0.f25C4 == 0x58) goto L_004D7F2C;
    if (D_001A4BE0.f25ED != 0 && D_001A4BE0.f25E4 != 1 && D_001A4BE0.f1D2 == 0) goto L_004D7F2C;
    if (D_001A4BE0.f25E8 != 0 && D_001A4BE0.f25E4 != 1 && D_001A4BE0.f1D2 == 0) goto L_004D7F2C;
    if (D_001A4BE0.f25E4 == 1) {
        func_003F5F08(0x23, 0, func_003F7BD0, func_003F7C18, func_003F8100, 0, 0);
    } else if (D_001A4BE0.f25E4 == 0 || D_001A4BE0.f25E4 == 3) {
        D_001A4BE0.f287E = (D_001A4BE0.f2882 != 0) ? 0x16 : 0xC;
        func_003F5F08(0x23, 0, func_003F6870, func_003F68C8, func_003F72A8, 0, 0);
        func_004518B0(0x12C);
        func_0044F7D0(0x96);
    }

L_004D7F2C:
    func_004D77B8();
    func_004D7918();
    if (D_001A4BE0.f88 < D_001DE9B0 && 2.0f < D_001A4BE0.f33C && D_001A4BE0.f25E4 != 2 && D_001A4BE0.f25C4 != 0x79) {
        func_004D1568(0x79, 1);
        goto L_004DDBB0;
    }
    switch (D_001A4BE0.f25C4) {
    case 0x00: goto L_004D7FC0;
    case 0x01: goto L_004D8EE8;
    case 0x02: case 0x2E: case 0x75: goto L_004D9658;
    case 0x03: goto L_004D9EF8;
    case 0x04: goto L_004DA0E8;
    case 0x05: case 0x1C: case 0x1E: case 0x1F: case 0x20: case 0x21: case 0x23: case 0x24: case 0x25: case 0x26: case 0x27: case 0x28: case 0x29: case 0x2A: case 0x2B: case 0x2D: case 0x30: case 0x31: case 0x37: case 0x3A: case 0x3B: case 0x3E: case 0x4C: case 0x50: case 0x5A: case 0x5B: case 0x5C: case 0x5D: case 0x5E: case 0x5F: case 0x60: case 0x61: case 0x62: case 0x64: case 0x65: case 0x69: case 0x6D: case 0x6E: case 0x6F: case 0x70: case 0x71: case 0x72: case 0x74: case 0x76: case 0x7A: case 0x7E: case 0x7F: case 0x81: case 0x83: case 0x85: case 0x87: case 0x89: case 0x8A: case 0x8B: case 0x8C: case 0x8D: case 0x8E: case 0x8F: case 0x90: case 0x92: case 0x93: case 0x94: case 0x95: case 0x96: case 0x97: case 0x98: case 0x99: case 0x9A: case 0x9B: case 0x9C: case 0x9D: case 0x9E: case 0xA1: case 0xA2: case 0xA3: case 0xA4: case 0xA5: case 0xA6: case 0xA7: case 0xA8: case 0xA9: case 0xAA: case 0xAB: case 0xAC: case 0xAD: case 0xAE: case 0xAF: case 0xB0: goto L_004DDBAC;
    case 0x06: case 0x2C: goto L_004DA79C;
    case 0x07: case 0x09: case 0x0A: case 0x0B: case 0x0C: case 0x0D: case 0x0E: case 0x0F: case 0x10: case 0x11: case 0x12: case 0x1B: case 0x38: case 0x6B: case 0x73: case 0x86: goto L_004DAEA0;
    case 0x08: goto L_004DAB30;
    case 0x13: case 0x15: goto L_004D92FC;
    case 0x14: goto L_004D90B8;
    case 0x16: goto L_004DBDBC;
    case 0x17: goto L_004DA260;
    case 0x18: goto L_004DA288;
    case 0x19: case 0x1A: goto L_004DA584;
    case 0x1D: goto L_004DDA10;
    case 0x22: goto L_004DDB00;
    case 0x2F: goto L_004D9070;
    case 0x32: case 0x34: goto L_004D891C;
    case 0x33: goto L_004D8B20;
    case 0x35: goto L_004D8D4C;
    case 0x36: goto L_004D8BD4;
    case 0x39: case 0x43: case 0x56: case 0x63: case 0x6C: case 0x82: case 0x84: case 0x9F: case 0xA0: goto L_004D888C;
    case 0x3C: goto L_004D86F8;
    case 0x3D: goto L_004D8800;
    case 0x3F: goto L_004DBF14;
    case 0x40: goto L_004DC924;
    case 0x41: goto L_004DC7C4;
    case 0x42: goto L_004DCBA4;
    case 0x44: goto L_004DC8B8;
    case 0x45: case 0x48: goto L_004DC250;
    case 0x46: goto L_004DCC08;
    case 0x47: goto L_004DCC24;
    case 0x49: case 0x4A: goto L_004DCEFC;
    case 0x4B: goto L_004DC6B0;
    case 0x4D: goto L_004DC128;
    case 0x4E: goto L_004DC8E8;
    case 0x4F: goto L_004DC780;
    case 0x51: goto L_004DD0D0;
    case 0x52: goto L_004DD834;
    case 0x53: goto L_004DD760;
    case 0x54: goto L_004DD35C;
    case 0x55: goto L_004DD990;
    case 0x57: goto L_004DD290;
    case 0x58: goto L_004DD34C;
    case 0x59: goto L_004DD2CC;
    case 0x66: goto L_004D9C28;
    case 0x67: goto L_004D9D74;
    case 0x68: goto L_004D9D90;
    case 0x6A: goto L_004D9E30;
    case 0x77: goto L_004D8E9C;
    case 0x78: goto L_004D8E40;
    case 0x79: goto L_004DAB0C;
    case 0x7B: goto L_004DA760;
    case 0x7C: goto L_004D963C;
    case 0x7D: goto L_004D9EC0;
    case 0x80: goto L_004D9A58;
    case 0x88: goto L_004D9520;
    case 0x91: goto L_004DBE9C;
    case 0xB1: goto L_004DBD94;
    }

    /* case 0x00: 0x004D7FC0.  Entry chain transcribed through the 0x004D8088 guard; the rest
     * of case 0 (0x004D8088-0x004D86F7) is TODO. */
L_004D7FC0:
    if (((S_Pad_4D7CD8 *)D_001D52FC)->held & func_004E1678(func_00438568(4, 0))) {
        if (D_001A4BE0.f25E4 == 0 && D_001439F4 == 2 && D_001A4BE0.f1228 == 0x6F
            && func_003C53A0(0) == 0) {
            func_004D1568(1, 1);
            goto L_004DDBB0;
        }
    }
    func_004DE7B8();
    if (D_001A4BE0.f2877 != 0) {
        func_004D1568(0x87, 1);
        goto L_004DDBB0;
    }
    if (D_001A4BE0.f1314 != 2) goto L_004D80BC;
    D_001A4BE0.f1436 = 0;
    {
        struct Moby *p = D_001A4BE0.f12F0;
        if (p != 0 && (p->anim_flags & 2) != 0 && p->cur_seq != 1)
            func_0041CF80((s32)p, 1, 0, 6);
    }
    goto L_004D80BC;
L_004D80BC:
    /* TODO: 0x004D80BC and the rest of case 0. */
    goto L_004DDBB0;
L_004DD34C:  /* case 0x58: f25ED = 1, then the end chain */
    D_001A4BE0.f25ED = 1;
    goto L_004DDBB0;

L_004D963C:  /* case 0x7c: jump_landed_ bit 1 -> hero_change_state(0) */
    if ((D_001A4BE0.fC08 & 2) != 0) func_004D1568(0, 1);
    goto L_004DDBB0;

L_004D9D74:  /* case 0x67: same guard, state 0x66 */
    if ((D_001A4BE0.fC08 & 2) != 0) func_004D1568(0x66, 1);
    goto L_004DDBB0;

L_004DBD94:  /* case 0xb1: state_timer >= 0x22 -> state 0x39 or 0 by health */
    if (D_001A4BE0.f1B8 >= 0x22) {
        if (D_001A4BE0.f2850 <= 0) func_004D1568(0x39, 1);
        else func_004D1568(0, 1);
    }
    goto L_004DDBB0;

L_004D86F8:  /* TODO: 0x004D86F8, 10 word(s) in entry chain, ends `beqz $3, .L004D8764`; not reconstructed */
    goto L_004DDBB0;
L_004D8800:  /* TODO: 0x004D8800, 4 word(s) in entry chain, ends `bnel $2, $0, .L004DDBB4`; not reconstructed */
    goto L_004DDBB0;
L_004D888C:  /* TODO: 0x004D888C, 4 word(s) in entry chain, ends `bnel $2, $0, .L004D88B0`; not reconstructed */
    goto L_004DDBB0;
L_004D891C:  /* TODO: 0x004D891C, 4 word(s) in entry chain, ends `bnel $3, $2, .L004D8A38`; not reconstructed */
    goto L_004DDBB0;
L_004D8B20:  /* TODO: 0x004D8B20, 4 word(s) in entry chain, ends `beqz $2, .L004D8B54`; not reconstructed */
    goto L_004DDBB0;
L_004D8BD4:  /* TODO: 0x004D8BD4, 3 word(s) in entry chain, ends `bnez $2, .L004D8C28`; not reconstructed */
    goto L_004DDBB0;
L_004D8D4C:  /* TODO: 0x004D8D4C, 3 word(s) in entry chain, ends `bnez $3, .L004D8D88`; not reconstructed */
    goto L_004DDBB0;
L_004D8E40:  /* TODO: 0x004D8E40, 3 word(s) in entry chain, ends `bgtzl $2, .L004D8E78`; not reconstructed */
    goto L_004DDBB0;
L_004D8E9C:  /* TODO: 0x004D8E9C, 3 word(s) in entry chain, ends `bgtzl $2, .L004D8ED4`; not reconstructed */
    goto L_004DDBB0;
L_004D8EE8:  /* TODO: 0x004D8EE8, 3 word(s) in entry chain, ends `bnez $2, .L004D8F78`; not reconstructed */
    goto L_004DDBB0;
L_004D9070:  /* TODO: 0x004D9070, 7 word(s) in entry chain, ends `bnez $2, .L004DDBB0`; not reconstructed */
    goto L_004DDBB0;
L_004D90B8:  /* TODO: 0x004D90B8, 4 word(s) in entry chain, ends `bne $2, $3, .L004D921C`; not reconstructed */
    goto L_004DDBB0;
L_004D92FC:  /* TODO: 0x004D92FC, 24 word(s) in entry chain, ends `bnel $2, $0, .L004D94F0`; not reconstructed */
    goto L_004DDBB0;
L_004D9520:  /* TODO: 0x004D9520, 10 word(s) in entry chain, ends `bnez $2, .L004D95F8`; not reconstructed */
    goto L_004DDBB0;
L_004D9658:  /* TODO: 0x004D9658, 3 word(s) in entry chain, ends `beqz $2, .L004D96A0`; not reconstructed */
    goto L_004DDBB0;
L_004D9A58:  /* TODO: 0x004D9A58, 13 word(s) in entry chain, ends `bnel $3, $0, .L004D9AA0`; not reconstructed */
    goto L_004DDBB0;
L_004D9C28:  /* TODO: 0x004D9C28, 3 word(s) in entry chain, ends `beqz $2, .L004D9CAC`; not reconstructed */
    goto L_004DDBB0;
L_004D9D90:  /* TODO: 0x004D9D90, 4 word(s) in entry chain, ends `bnez $2, .L004D9DB0`; not reconstructed */
    goto L_004DDBB0;
L_004D9E30:  /* TODO: 0x004D9E30, 4 word(s) in entry chain, ends `beqz $2, .L004D9E88`; not reconstructed */
    goto L_004DDBB0;
L_004D9EC0:  /* TODO: 0x004D9EC0, 13 word(s) in entry chain, ends `b .L004DAB18`; not reconstructed */
    goto L_004DDBB0;
L_004D9EF8:  /* TODO: 0x004D9EF8, 10 word(s) in entry chain, ends `beqz $3, .L004D9F64`; not reconstructed */
    goto L_004DDBB0;
L_004DA0E8:  /* TODO: 0x004DA0E8, 10 word(s) in entry chain, ends `beqz $3, .L004DA154`; not reconstructed */
    goto L_004DDBB0;
L_004DA260:  /* TODO: 0x004DA260, 9 word(s) in entry chain, ends `b .L004DDA00`; not reconstructed */
    goto L_004DDBB0;
L_004DA288:  /* TODO: 0x004DA288, 4 word(s) in entry chain, ends `beqz $2, .L004DA2BC`; not reconstructed */
    goto L_004DDBB0;
L_004DA584:  /* TODO: 0x004DA584, 9 word(s) in entry chain, ends `bne $3, $4, .L004DA5BC`; not reconstructed */
    goto L_004DDBB0;
L_004DA760:  /* TODO: 0x004DA760, 4 word(s) in entry chain, ends `bnel $2, $0, .L004DA780`; not reconstructed */
    goto L_004DDBB0;
L_004DA79C:  /* TODO: 0x004DA79C, 3 word(s) in entry chain, ends `bnez $2, .L004DA818`; not reconstructed */
    goto L_004DDBB0;
L_004DAB0C:  /* TODO: 0x004DAB0C, 4 word(s) in entry chain, ends `bnez $2, .L004DDBB0`; not reconstructed */
    goto L_004DDBB0;
L_004DAB30:  /* TODO: 0x004DAB30, 3 word(s) in entry chain, ends `beqz $2, .L004DAB8C`; not reconstructed */
    goto L_004DDBB0;
L_004DAEA0:  /* TODO: 0x004DAEA0, 3 word(s) in entry chain, ends `beqz $2, .L004DAFC0`; not reconstructed */
    goto L_004DDBB0;
L_004DBDBC:  /* TODO: 0x004DBDBC, 10 word(s) in entry chain, ends `bnel $2, $0, .L004DBE4C`; not reconstructed */
    goto L_004DDBB0;
L_004DBE9C:  /* TODO: 0x004DBE9C, 4 word(s) in entry chain, ends `beqz $2, .L004DBEC0`; not reconstructed */
    goto L_004DDBB0;
L_004DBF14:  /* TODO: 0x004DBF14, 4 word(s) in entry chain, ends `bnez $2, .L004DBF38`; not reconstructed */
    goto L_004DDBB0;
L_004DC128:  /* TODO: 0x004DC128, 3 word(s) in entry chain, ends `bnez $2, .L004DDB74`; not reconstructed */
    goto L_004DDBB0;
L_004DC250:  /* TODO: 0x004DC250, 5 word(s) in entry chain, ends `beqz $2, .L004DDBB0`; not reconstructed */
    goto L_004DDBB0;
L_004DC6B0:  /* TODO: 0x004DC6B0, 4 word(s) in entry chain, ends `bnel $2, $0, .L004DC6EC`; not reconstructed */
    goto L_004DDBB0;
L_004DC780:  /* TODO: 0x004DC780, 16 word(s) in entry chain, ends `b .L004DDBB0`; not reconstructed */
    goto L_004DDBB0;
L_004DC7C4:  /* TODO: 0x004DC7C4, 3 word(s) in entry chain, ends `bnel $2, $0, .L004DC850`; not reconstructed */
    goto L_004DDBB0;
L_004DC8B8:  /* TODO: 0x004DC8B8, 9 word(s) in entry chain, ends `beqz $2, .L004DDBB0`; not reconstructed */
    goto L_004DDBB0;
L_004DC8E8:  /* TODO: 0x004DC8E8, 4 word(s) in entry chain, ends `bnel $2, $0, .L004DC908`; not reconstructed */
    goto L_004DDBB0;
L_004DC924:  /* TODO: 0x004DC924, 3 word(s) in entry chain, ends `bnez $2, .L004DDB74`; not reconstructed */
    goto L_004DDBB0;
L_004DCBA4:  /* TODO: 0x004DCBA4, 4 word(s) in entry chain, ends `bnel $2, $0, .L004DCBE8`; not reconstructed */
    goto L_004DDBB0;
L_004DCC08:  /* TODO: 0x004DCC08, 4 word(s) in entry chain, ends `beqz $2, .L004DDBAC`; not reconstructed */
    goto L_004DDBB0;
L_004DCC24:  /* TODO: 0x004DCC24, 11 word(s) in entry chain, ends `bnel $2, $0, .L004DCC74`; not reconstructed */
    goto L_004DDBB0;
L_004DCEFC:  /* TODO: 0x004DCEFC, 9 word(s) in entry chain, ends `bne $3, $4, .L004DCF34`; not reconstructed */
    goto L_004DDBB0;
L_004DD0D0:  /* TODO: 0x004DD0D0, 4 word(s) in entry chain, ends `beqz $2, .L004DD158`; not reconstructed */
    goto L_004DDBB0;
L_004DD290:  /* TODO: 0x004DD290, 4 word(s) in entry chain, ends `bnel $2, $0, .L004DD2B0`; not reconstructed */
    goto L_004DDBB0;
L_004DD2CC:  /* TODO: 0x004DD2CC, 4 word(s) in entry chain, ends `bnez $2, .L004DD320`; not reconstructed */
    goto L_004DDBB0;
L_004DD35C:  /* TODO: 0x004DD35C, 5 word(s) in entry chain, ends `beqz $2, .L004DDBB0`; not reconstructed */
    goto L_004DDBB0;
L_004DD760:  /* TODO: 0x004DD760, 3 word(s) in entry chain, ends `bnez $2, .L004DDBB0`; not reconstructed */
    goto L_004DDBB0;
L_004DD834:  /* TODO: 0x004DD834, 14 word(s) in entry chain, ends `bnez $2, .L004DD8C0`; not reconstructed */
    goto L_004DDBB0;
L_004DD990:  /* TODO: 0x004DD990, 4 word(s) in entry chain, ends `bnel $2, $0, .L004DD9D4`; not reconstructed */
    goto L_004DDBB0;
L_004DDA10:  /* TODO: 0x004DDA10, 3 word(s) in entry chain, ends `bnez $2, .L004DDA90`; not reconstructed */
    goto L_004DDBB0;
L_004DDB00:  /* TODO: 0x004DDB00, 16 word(s) in entry chain, ends `beqz $2, .L004DDB84`; not reconstructed */
    goto L_004DDBB0;

L_004DDBAC:
L_004DDBB0:
    if (D_001A4BE0.f25CC != state_type0) func_004B7A00();
    if (!(D_001A4BE0.f25D0 == 0x3C && D_001A4BE0.f25C4 == 0x3D) && !(D_001A4BE0.f25D0 == 0x3D && D_001A4BE0.f1A04 == 0))
        func_004D6A38();
    if (substate0 != D_001A4BE0.f25C8) D_001A4BE0.f1C0 = 0;
    if (seq0 != D_001A4BE0.f25C0->cur_seq) D_001A4BE0.f1C4 = 0;
}
