/* near miss (level 27, Aquatos Base): 63 diff with the divs_nops row func_L27_003A1B30 2
   (255 without it; the first 107 instructions match exactly and the raw count is dominated by
   the 2-instruction shift at the div.s). The C is 644 instructions, retail 646; the two are
   the div.s latency nops. The real residual is 12 instructions of register/scheduling: the
   load order in the o0->pos/vF0 block, two bne where retail has bnel, and a lw/move swap
   before func_00382380. Recipes: the action if body is the whole middle (stopping cse of
   1.0f); D_001A4BE0 is the Hero union (ptr[0x970] / i[0x971] addressing); vec_sub_ba /
   vec_add_ab for the vector block; write d->f70 += 1.0f with a temporary and a.z += -15.0f
   (not -=). File flags are already correct. */
#include "common.h"
#include "vu0.h"

typedef int u128_t __attribute__((mode(TI)));
typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V4_3A1B30;
typedef union {
    u8 b[0x2A00]; s16 h[0x1500]; u16 uh[0x1500]; s32 i[0xA80]; u32 u[0xA80];
    f32 f[0xA80]; u8 *ptr[0xA80]; u128_t q[0x2A0];
} Hero_3A1B30;
typedef struct { u8 p00[0xAA]; s16 hAA; } S_HOBJ_3A1B30;
typedef struct { s32 f0; u8 p04[8]; s32 fC; u8 p10[0x490]; s32 f4A0; } S_M68_3A1B30;
typedef struct {
    u8 p00[0x10];
    V4_3A1B30 pos;
    u8 b20;
    u8 p21[0x47];
    S_M68_3A1B30 *f68;
    u8 p6C[0x84];
    V4_3A1B30 vF0;
} S_MOB_3A1B30;
typedef struct {
    s32 f0, f4, f8; u8 p0C[0x18]; s32 f24; u8 p28[0xC]; s32 f34; u8 p38[4]; s32 f3C;
    u8 p40[0x2C]; s32 f6C; f32 f70; s32 f74; s32 f78; s32 f7C; V4_3A1B30 v80;
    s32 f90, f94, f98, f9C, fA0; u8 pA4[0x20]; s32 fC4, fC8, fCC, fD0, fD4; u8 pD8[4];
    s32 fDC, fE0, fE4, fE8; u8 pEC[8]; s32 fF4, fF8, fFC; u8 p100[0x18];
    s32 f118, f11C, f120, f124, f128;
} S_D_3A1B30;
typedef struct { u8 p00[0x20]; u8 b20; u8 p21[0x47]; S_D_3A1B30 *f68; } S_SELF_3A1B30;
typedef struct { u8 p0[0xD0]; u8 bD0; u8 pD1[0xB]; void *fDC; } S_G7_3A1B30;
typedef struct { u8 p00[0x30]; V4_3A1B30 v30; u8 p40[0x30]; V4_3A1B30 v70; } S_DEE_3A1B30;

extern Hero_3A1B30 D_001A4BE0;
extern u8 *D_001DED1C_sda;
__asm__(".extern D_001DED1C_sda, 4");
extern S_MOB_3A1B30 *D_L27_001DED1C_003A1B30;
__asm__(".extern D_L27_001DED1C_003A1B30, 16");
extern S_DEE_3A1B30 *D_L27_001DEE00_003A1B30;
__asm__(".extern D_L27_001DEE00_003A1B30, 16");
extern u8 D_001A30B0[];
extern u8 D_001BBC40[];
extern s32 D_001D545C[4];
extern s32 D_001B818C[4];
extern u8 D_L27_001E1600[];
extern s32 func_L01_004561E0(void *);
extern void func_L27_003A2E08();
extern s32 func_L01_00456500(void *, s32);
extern void func_L01_0041A5B0(s32, s32);
extern f32 func_0038D160(f32, f32);
extern void func_L22_003B72F0(void *, f32, void *, s32);
extern void func_L27_004D1568(s32, s32);
extern void func_L27_0039F6A8(void *);
extern void func_L01_003EB438(s32, void *, void *, s32, s32, s32);
extern void func_L01_003EB350(s32, void *);
extern void func_003C3A10(void *, s32, s32, s32);
extern f32 func_0038D098(f32);
extern f32 func_0038D0B0(f32);
extern s32 func_L01_00456250(void *);
extern void func_0038CE20(f32, void *, void *);
extern void func_003C7DD8(void *);
extern s32 func_003A52A0(s32, s32, void *);
extern void func_003A4F28(s32);
extern f32 func_0038CF38(void *, void *);
extern void func_L01_003EB3C0(s32, void *);
extern void func_L01_0043B510(s32);
extern void func_L01_004450F0(void *, s32, s32);
extern s32 func_00382380(void *, void *, s32);

void func_L27_003A1B30(S_SELF_3A1B30 *self) {
    S_D_3A1B30 *d = self->f68;
    S_MOB_3A1B30 *m, *o0, *o4;
    S_G7_3A1B30 *g;
    V4_3A1B30 a, b, c;
    f32 x, t, u;
    s32 i;

    if (func_L01_004561E0(self) != 0) {
        func_L27_003A2E08(self);
        d->fDC = 0;
    }
    if (d->f6C == 0) {
        if ((d->fC4 == -1 || ((S_MOB_3A1B30 *)((d->fC4 << 8) + (s32)D_001DED1C_sda))->b20 == 0xFE || ((S_MOB_3A1B30 *)((d->fC4 << 8) + (s32)D_001DED1C_sda))->b20 == 0xFD) ||
            (d->fC8 == -1 || ((S_MOB_3A1B30 *)((d->fC8 << 8) + (s32)D_001DED1C_sda))->b20 == 0xFE || ((S_MOB_3A1B30 *)((d->fC8 << 8) + (s32)D_001DED1C_sda))->b20 == 0xFD) ||
            (d->fCC == -1 || ((S_MOB_3A1B30 *)((d->fCC << 8) + (s32)D_001DED1C_sda))->b20 == 0xFE || ((S_MOB_3A1B30 *)((d->fCC << 8) + (s32)D_001DED1C_sda))->b20 == 0xFD) ||
            (d->fD0 == -1 || ((S_MOB_3A1B30 *)((d->fD0 << 8) + (s32)D_001DED1C_sda))->b20 == 0xFE || ((S_MOB_3A1B30 *)((d->fD0 << 8) + (s32)D_001DED1C_sda))->b20 == 0xFD) ||
            (d->f7C == -1 || ((S_MOB_3A1B30 *)((d->f7C << 8) + (s32)D_001DED1C_sda))->b20 == 0xFE || ((S_MOB_3A1B30 *)((d->f7C << 8) + (s32)D_001DED1C_sda))->b20 == 0xFD) ||
            (d->fD4 == -1 || ((S_MOB_3A1B30 *)((d->fD4 << 8) + (s32)D_001DED1C_sda))->b20 == 0xFE || ((S_MOB_3A1B30 *)((d->fD4 << 8) + (s32)D_001DED1C_sda))->b20 == 0xFD) ||
            (d->f98 == -1 || ((S_MOB_3A1B30 *)((d->f98 << 8) + (s32)D_001DED1C_sda))->b20 == 0xFE || ((S_MOB_3A1B30 *)((d->f98 << 8) + (s32)D_001DED1C_sda))->b20 == 0xFD) ||
            (d->f9C == -1 || ((S_MOB_3A1B30 *)((d->f9C << 8) + (s32)D_001DED1C_sda))->b20 == 0xFE || ((S_MOB_3A1B30 *)((d->f9C << 8) + (s32)D_001DED1C_sda))->b20 == 0xFD))
            d->f6C = 1;
    }
    if (func_L01_00456500(&D_001A4BE0.i[0x20], d->f8) == 0) {
        if ((D_001BBC40[d->f34 + D_001D545C[0] * 16] & 0x80) == 0) {
            if (((S_HOBJ_3A1B30 *)D_001A4BE0.ptr[0x970])->hAA != 0x1A4E &&
                D_001A4BE0.i[0x973] != 0x14 && D_001A4BE0.i[0x973] != 0x19 && D_001B818C[0] >= 0) {
                func_L01_0041A5B0(0xBA6, 0x49);
            }
        }
    }
    if (D_L27_001DED1C_003A1B30[d->fE0].f68->fC == 0) {
        i = d->fC4;
        if (i != -1 && D_L27_001DED1C_003A1B30[i].b20 != 0xFE && D_L27_001DED1C_003A1B30[i].b20 != 0xFD &&
            D_L27_001DED1C_003A1B30[i].f68->f4A0 > 0) {
            a = D_L27_001DED1C_003A1B30[d->f118].pos;
            func_L22_003B72F0(&D_L27_001DED1C_003A1B30[i],
                func_0038D160(((S_MOB_3A1B30 *)D_001A4BE0.ptr[0x970])->pos.x - D_L27_001DED1C_003A1B30[d->f118].pos.x,
                              ((S_MOB_3A1B30 *)D_001A4BE0.ptr[0x970])->pos.y - D_L27_001DED1C_003A1B30[d->f118].pos.y), &a, 0);
        }
    }
    D_L27_001DED1C_003A1B30[d->fE0].f68->fC = D_L27_001DED1C_003A1B30[d->f118].f68->f0;

    if (D_L27_001DED1C_003A1B30[d->fE4].f68->fC == 0) {
        i = d->fCC;
        if (i != -1 && D_L27_001DED1C_003A1B30[i].b20 != 0xFE && D_L27_001DED1C_003A1B30[i].b20 != 0xFD &&
            D_L27_001DED1C_003A1B30[i].f68->f4A0 > 0) {
            a = D_L27_001DED1C_003A1B30[d->f11C].pos;
            func_L22_003B72F0(&D_L27_001DED1C_003A1B30[i],
                func_0038D160(((S_MOB_3A1B30 *)D_001A4BE0.ptr[0x970])->pos.x - D_L27_001DED1C_003A1B30[d->f11C].pos.x,
                              ((S_MOB_3A1B30 *)D_001A4BE0.ptr[0x970])->pos.y - D_L27_001DED1C_003A1B30[d->f11C].pos.y), &a, 0);
        }
    }
    D_L27_001DED1C_003A1B30[d->fE4].f68->fC = D_L27_001DED1C_003A1B30[d->f11C].f68->f0;

    if (D_L27_001DED1C_003A1B30[d->fE8].f68->fC == 0) {
        i = d->fD4;
        if (i != -1 && D_L27_001DED1C_003A1B30[i].b20 != 0xFE && D_L27_001DED1C_003A1B30[i].b20 != 0xFD &&
            D_L27_001DED1C_003A1B30[i].f68->f4A0 > 0) {
            a = D_L27_001DED1C_003A1B30[d->f120].pos;
            func_L22_003B72F0(&D_L27_001DED1C_003A1B30[i],
                func_0038D160(((S_MOB_3A1B30 *)D_001A4BE0.ptr[0x970])->pos.x - D_L27_001DED1C_003A1B30[d->f120].pos.x,
                              ((S_MOB_3A1B30 *)D_001A4BE0.ptr[0x970])->pos.y - D_L27_001DED1C_003A1B30[d->f120].pos.y), &a, 0);
        }
    }
    D_L27_001DED1C_003A1B30[d->fE8].f68->fC = D_L27_001DED1C_003A1B30[d->f120].f68->f0;
    D_L27_001DED1C_003A1B30[d->fF4].f68->fC = D_L27_001DED1C_003A1B30[d->f124].f68->f0;
    D_L27_001DED1C_003A1B30[d->fF8].f68->fC = 1;
    D_L27_001DED1C_003A1B30[d->fFC].f68->fC = D_L27_001DED1C_003A1B30[d->f128].f68->f0;

    if (d->f74 == 0) {
        if (d->f7C != -1 && D_L27_001DED1C_003A1B30[d->f7C].b20 != 0xFE &&
            D_L27_001DED1C_003A1B30[d->f7C].b20 != 0xFD && D_L27_001DED1C_003A1B30[d->f7C].f68->f4A0 > 0) {
            m = &D_L27_001DED1C_003A1B30[d->f90];
            if (D_001A4BE0.i[0x971] != 0x74 && D_001A4BE0.i[0x971] != 0x58) {
                if (((S_HOBJ_3A1B30 *)D_001A4BE0.ptr[0x970])->hAA == 0x1A4E) {
                    func_L27_004D1568(0x58, 0);
                } else {
                    func_L27_004D1568(0x74, 0);
                }
                func_L27_0039F6A8(&D_L27_001DED1C_003A1B30[d->f7C]);
                func_L01_003EB438(0, D_L27_001E1600, D_L27_001E1600 + 0x10, 0, 0, 0);
                func_L01_003EB350(0, &D_L27_001DEE00_003A1B30[d->f94].v30);
                o0 = &D_L27_001DED1C_003A1B30[d->f0];
                o4 = &D_L27_001DED1C_003A1B30[d->f4];
                d->f70 = 0;
                o0->pos = D_L27_001DEE00_003A1B30[d->f78].v30;
                func_003C3A10(o0, 0x14, 0, 4);
                o0->vF0 = D_L27_001DEE00_003A1B30[d->f78].v70;
                a.x = -func_0038D098(o0->vF0.z);
                a.y = -func_0038D0B0(o0->vF0.z);
                a.z = 0;
                a.w = 1.0f;
                vec_add_ab(&o4->pos, &o0->pos, &a);
                o4->vF0 = o0->vF0;
            }
            if (func_L01_00456250(&D_L27_001DED1C_003A1B30[d->f7C]) != 0) {
                x = d->f70 + 1.0f;
                d->f70 = x;
                t = x / 250.0f;
                u = t > 1.0f ? 1.0f : t;
                a = d->v80;
                a.z = a.z + -15.0f;
                b = d->v80;
                vec_sub_ba(&c, &b, &a);
                func_0038CE20(u, &c, &c);
                vec_add_ab(&m->pos, &c, &a);
                func_003C7DD8(m);
                i = d->f24;
                if (i == -1 || ((S_G7_3A1B30 *)(D_001A30B0 + (i << 7)))->fDC != m ||
                    ((S_G7_3A1B30 *)(D_001A30B0 + (i << 7)))->bD0 == 0) {
                    d->f24 = func_003A52A0(0, 4, m);
                }
                if (u >= 1.0f) {
                    d->f74 = 1;
                    i = d->f24;
                    if (i != -1) {
                        g = (S_G7_3A1B30 *)(D_001A30B0 + (i << 7));
                        if (g->fDC == m && g->bD0 != 0) func_003A4F28(i);
                    }
                    d->f24 = -1;
                }
            }
            a.x = 0;
            a.y = -func_0038D160(func_0038CF38(&D_L27_001DEE00_003A1B30[d->f94].v30, &m->pos),
                                 m->pos.z - D_L27_001DEE00_003A1B30[d->f94].v30.z);
            a.z = func_0038D160(m->pos.x - D_L27_001DEE00_003A1B30[d->f94].v30.x,
                                m->pos.y - D_L27_001DEE00_003A1B30[d->f94].v30.y);
            func_L01_003EB3C0(0, &a);
        }
    }
    if (D_L27_001DED1C_003A1B30[d->fA0].f68->f0 == 0) {
        if (d->f98 != -1 && D_L27_001DED1C_003A1B30[d->f98].b20 != 0xFE &&
            D_L27_001DED1C_003A1B30[d->f98].b20 != 0xFD && D_L27_001DED1C_003A1B30[d->f98].f68->f4A0 > 0) {
            if (func_L01_00456250(&D_L27_001DED1C_003A1B30[d->f98]) == 0) {
                func_L27_0039F6A8(&D_L27_001DED1C_003A1B30[d->f98]);
            } else {
                D_L27_001DED1C_003A1B30[d->fA0].f68->f0 = 1;
            }
        }
    }
    if (d->f74 != 0) {
        if (self->b20 == 5) {
            func_L01_0043B510(d->f34);
            D_L27_001DED1C_003A1B30[d->f90].pos = d->v80;
            func_L01_004450F0(self, 6, 2);
        }
    }
    if (func_00382380(&D_001A4BE0.i[0x20], d, 0) != 0) {
        func_L01_0043B510(d->f3C);
        func_L01_004450F0(self, 3, 0);
    }
}
