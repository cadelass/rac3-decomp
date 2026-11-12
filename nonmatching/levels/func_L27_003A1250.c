/* near miss (level 27, Aquatos Base): 12 diff, 344/344 instructions, exactly 0x560. All
   structure, VU0 sequences, loops, branches and delay slots match. Left: three register/
   store-order spots - the b53 block (constant 1 in $v1 and the 0x142D61 address in $v0;
   ours swapped), the selected-target block (retail loads D_001DE0A0 before A4 and stores
   0x150/0x158/0x148/0x15C/0x154; ours pairs A4 first), and d->f6C = 2 in $v0 vs $v1.
   Recipes: an absolute scalar read as X[0] (unsized array) makes cc1 emit the split
   lui/lw where a hint-16 scalar gets ps2as's same-register macro; (x << 8) + (s32)base
   gives offset-first addu, base + (x << 8) gives base-first; the b95 dispatch writes == 0
   first. File flags unchanged (@ps2as + -mvu0-use-vf0-vf2 already set). No div.s/sqrt.s. */
typedef int u128_t __attribute__((mode(TI)));

typedef struct { s32 f0; u8 p4[8]; s32 fC; } S_3A1250_P;
typedef struct {
    u8 p0[0x10];
    vu0_v4 v10;
    u8 p20[0x14];
    u16 h34;
    u8 p36[0x32];
    S_3A1250_P *f68;
    u8 p6C[0x2C];
    s32 f98;
    u8 p9C[0x44];
} S_3A1250_T;
typedef struct {
    u8 p0[0x10];
    s32 f10;
    u8 p14[0xC];
    s32 f20;
    u8 p24[4];
    s32 f28;
    u8 p2C[0x24];
    u8 b50;
    u8 p51[2];
    u8 b53;
    u8 p54[4];
    s32 f58;
    s32 f5C;
    u8 p60[0xC];
    s32 f6C;
    u8 p70[0x84];
    s32 fF4;
    u8 pF8[0x2C];
    s32 f124;
    u8 p128[8];
    vu0_v4 v130;
    vu0_v4 v140;
    s32 f150;
    s32 f154;
    s32 f158;
    s32 f15C;
    u8 p160[0x80];
    s32 f1E0;
} S_3A1250_D;
typedef struct {
    u8 p0[0x10];
    u8 p10[0x10];
    u8 b20;
    u8 p21[7];
    u8 p28[0x40];
    S_3A1250_D *f68;
    u8 p6C[0x29];
    u8 b95;
} S_3A1250_O;
typedef struct { u8 p0[0xD0]; u8 bD0; u8 pD1[0xB]; void *fDC; } S_3A1250_E;
typedef struct { u8 p0[0x30]; vu0_v4 v30; u8 p40[0x30]; f32 f70; f32 f74; f32 f78; u8 p7C[4]; } S_3A1250_R;

extern s32 D_001D6694_sda;
__asm__(".extern D_001D6694_sda, 4");
extern s32 D_L27_001D6690;
__asm__(".extern D_L27_001D6690, 16");
extern s32 D_L27_001E59F0[];
__asm__(".extern D_L27_001E59F0, 16");
extern u8 *D_L27_001DED1C;
__asm__(".extern D_L27_001DED1C, 16");
extern s16 *D_L27_0021B7E0[];
extern s32 D_001DED58_sda;
__asm__(".extern D_001DED58_sda, 4");
typedef struct { u8 pad[0x27D0]; s32 f27D0; } S_3A1250_G;
extern S_3A1250_G D_001A4C60_3A1250;
__asm__(".extern D_001A4C60_3A1250, 16");
extern u8 D_L27_001E8180[];
extern S_3A1250_R *D_L27_001DEE00_3A1250;
__asm__(".extern D_L27_001DEE00_3A1250, 16");
extern f32 D_L27_001D6720;
__asm__(".extern D_L27_001D6720, 16");
extern s32 D_00142C68[];
extern u8 D_00142CC1[];
extern u8 D_00142D61[];
extern s16 D_001A7464[];
extern u8 D_001A30B0[];
extern s32 D_001DE0A0_sda;
__asm__(".extern D_001DE0A0_sda, 4");
extern s32 D_001DE0A4_sda;
__asm__(".extern D_001DE0A4_sda, 4");
extern f32 D_001DE0A8_sda;
__asm__(".extern D_001DE0A8_sda, 4");
extern f32 D_001DE0AC_sda;
__asm__(".extern D_001DE0AC_sda, 4");
extern u8 D_001DE060_sda[8];
__asm__(".extern D_001DE060_sda, 8");

extern s32 func_L01_0044C108(void *);
extern void func_L01_004AA7E8(void *, s32);
extern void func_003A4F28(s32);
extern void func_L27_003A17B0();
extern void func_L27_003A1B30();
extern void func_L27_003A2548();
extern void func_L27_003A2F58();
extern void func_L27_003A3098();
extern void func_L27_003A3310();
extern s32 func_00382380(void *, s32, s32);
extern void func_L01_004450F0(void *, s32, s32);
extern s32 func_L01_004561B8(void *);
extern s32 func_00392B20(void *, s32);
extern void func_00392C78(void *);
extern void func_0039EF28(void);
extern s32 func_L01_004BA800(void);
extern void func_L01_004F50C8(void *, void *, s32, s32);
extern f32 func_L01_0040E570(void *, void *);
extern f32 func_0038CE68(void *, void *);
extern void func_L01_0040C7A0(void *, void *);
extern void func_0038CE20(void *, void *, f32);
extern void func_L01_0040C8A0(void *, void *);
extern void func_L01_004DFEA0(s32);
extern void func_L27_004D1568(s32, s32);
extern void func_L01_00404808(void *, void *);

void func_L27_003A1250(S_3A1250_O *self) {
    S_3A1250_D *d;
    S_3A1250_T *sel;
    S_3A1250_T *t;
    S_3A1250_E *e;
    vu0_v4 buf;
    s16 *q;
    f32 dist;
    f32 best;

    if (func_L01_0044C108((u8 *)self + 0x10) == 0) return;
    d = self->f68;
    if (D_001D6694_sda == 1 || D_001D6694_sda == 2 || D_L27_001D6690 == 1 || D_L27_001D6690 == 2) {
        if (D_001D6694_sda == 2 && D_L27_001E59F0[0] == 1) {
            ((S_3A1250_T *)((d->f58 << 8) + (s32)D_L27_001DED1C))->h34 |= 0x41;
            ((S_3A1250_T *)((d->f58 << 8) + (s32)D_L27_001DED1C))->h34 &= 0xEFFF;
            ((S_3A1250_T *)((d->f58 << 8) + (s32)D_L27_001DED1C))->f98 = 0;
            func_L01_004AA7E8(D_L27_001DED1C + (d->f58 << 8), 1);
        }
        if (d->f20 != -1) {
            e = (S_3A1250_E *)(D_001A30B0 + (d->f20 << 7));
            if (e->fDC == self && e->bD0 != 0) func_003A4F28(d->f20);
        }
        d->f20 = -1;
        return;
    }
    if (self->b95 == 0) {
        if (self->b20 == 0) func_L27_003A17B0(self);
        if (self->b20 == 1) {
            if (func_00382380(&D_001A4C60_3A1250, d->f28, 0)) func_L01_004450F0(self, 2, -1);
        }
        if (self->b20 == 2) {
            if (func_L01_004561B8(self) != 0) {
                if (d->b50 == 0) {
                    if (func_00392B20(D_L27_001E8180, 0xC6) != 0) {
                        func_00392C78(D_L27_001E8180);
                        D_L27_001D6720 = 2.0f;
                        d->b50 = 1;
                    }
                }
            } else {
                func_L01_004450F0(self, 4, 2);
            }
        }
        if (self->b20 == 3) {
            if (func_L01_004561B8(self) != 0) {
                if (!(D_00142C68[0] & 0x200) && d->b53 == 0) {
                    if (func_00392B20(D_L27_001E8180, 0xC9) != 0) {
                        func_00392C78(D_L27_001E8180);
                        d->b53 = 1;
                        D_00142CC1[0] = 1;
                        D_00142D61[0] = 1;
                        func_0039EF28();
                    }
                }
            } else {
                D_001A7464[0] = 0;
            }
        }
        if (self->b20 == 3 && d->f5C == 0 && func_L01_004BA800() == 0) {
            d->f5C = 1;
            func_L01_004F50C8((u8 *)&D_L27_001DEE00_3A1250[d->f1E0].v30, &D_L27_001DEE00_3A1250[d->f1E0].f70, 0, 1);
        }
        ((S_3A1250_T *)((d->fF4 << 8) + (s32)D_L27_001DED1C))->f68->fC =
            ((S_3A1250_T *)((d->f124 << 8) + (s32)D_L27_001DED1C))->f68->f0;
    } else if (self->b95 == 1) {
        func_L27_003A1B30(self);
    } else if (self->b95 == 2) {
        func_L27_003A2548(self);
    }
    func_L27_003A2F58(self);
    func_L27_003A3098(self);
    if (d->f6C == 1) {
        best = 1e8f;
        sel = 0;
        q = D_L27_0021B7E0[d->f10];
        while ((d->f10 & 0xFF) != 0xFF && d->f10 <= D_001DED58_sda && q != 0 &&
               (q[-1] >= 0 || q == D_L27_0021B7E0[d->f10])) {
            t = (S_3A1250_T *)(D_L27_001DED1C + ((*(u16 *)q & 0x7FFF) << 8));
            if (t == 0) break;
            dist = func_L01_0040E570(&t->v10, &D_001A4C60_3A1250);
            if (dist < best) {
                vec_sub_ba(&buf, &D_001A4C60_3A1250, &t->v10);
                if (func_0038CE68(&buf, (u8 *)t + 0xE0) > 0.0f) {
                    best = dist;
                    sel = t;
                }
            }
            q++;
        }
        if (sel != 0) {
            func_L01_0040C7A0(&d->v130, D_001DE060_sda);
            func_0038CE20(&d->v130, (u8 *)sel + 0xE0, D_001DE0AC_sda);
            vec_add_ba(&d->v130, &d->v130, &sel->v10);
            *(u128_t *)((u8 *)d + 0x140) = *(u128_t *)&D_001A4C60_3A1250;
            d->f150 = D_001DE0A0_sda;
            d->f154 = D_001DE0A0_sda;
            d->f158 = D_001DE0A4_sda;
            d->f15C = D_001DE0A4_sda;
            d->v140.z += D_001DE0A8_sda;
            func_L01_004DFEA0(D_001A4C60_3A1250.f27D0);
            func_L27_004D1568(0x82, 1);
            d->f6C = 2;
        }
    }
    if (d->f6C == 2) {
        *(u128_t *)((u8 *)d + 0x140) = *(u128_t *)&D_001A4C60_3A1250;
        d->v140.z += D_001DE0A8_sda;
        func_L01_0040C8A0(&d->v130, D_001DE060_sda);
        func_L01_00404808(func_L27_003A3310, self);
    }
}
