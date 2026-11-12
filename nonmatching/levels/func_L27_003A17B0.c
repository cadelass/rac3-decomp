/* near miss (level 27, Aquatos Base): 17 diff (224/224 instructions, 0x380 exact). Left are
   two allocation swaps: retail gives the -1/0xFA constants $t0/$a3 (ours the other way) and
   keeps the index in $v0 (ours $a1), which also hoists the else-path lui/lw above the
   h34 |= 2 store. Recipes: use u128_t casts for all four lq/sq copies (a vu0_v4 struct copy
   lets gcc CSE the pointer globals across the first sq); write address sums as
   (ix << shift) + (s32)base, pointer-first only in the func_L01_004AA7E8 arguments; the same
   address read both $gp and lui needs D_001D545C_sda (hint 4) plus a hinted-16 alias. No
   div.s/sqrt.s. */
typedef int u128_t __attribute__((mode(TI)));
typedef struct { u8 p0[4]; s32 f4; u8 p8[0xC]; s32 f14; s32 f18; s32 f1C; s32 f20; s32 f24; u8 p28[4]; s32 f2C; s32 f30; s32 f34; s32 f38; u8 p3C[0x14]; u8 b50; u8 b51; u8 b52; u8 b53; u8 p54[4]; s32 f58; u8 p5C[4]; s32 f60; u8 p64[8]; s32 f6C; u8 p70[4]; s32 f74; u8 p78[8]; vu0_v4 v80; s32 f90; u8 p94[0x24]; s32 fB8; u8 pBC[0x20]; s32 fDC; } S_3A17B0_D;
typedef struct { u8 p0[0x68]; S_3A17B0_D *f68; } S_3A17B0_O;
typedef struct { u8 p0[0x10]; s32 f10; u8 p14[0x30]; u16 h44; } S_3A17B0_A;
typedef struct { u8 p0[0x10]; vu0_v4 v10; u8 p20[4]; S_3A17B0_A *f24; u8 p28[0xC]; u16 h34; u16 h36; u8 p38[0x60]; s32 f98; u8 p9C[0x54]; vu0_v4 vF0; } S_3A17B0_E;
typedef struct { u8 p0[0x30]; vu0_v4 v30; u8 p40[0x30]; vu0_v4 v70; } S_3A17B0_P;
extern u8 *D_L27_001DED1C_3A17B0;
__asm__(".extern D_L27_001DED1C_3A17B0, 16");
extern S_3A17B0_P *D_L27_001DEE00_3A17B0;
__asm__(".extern D_L27_001DEE00_3A17B0, 16");
extern u8 D_001BBC40[][16];
__asm__(".extern D_001BBC40, 16");
extern s32 D_001D545C_sda;
__asm__(".extern D_001D545C_sda, 4");
extern s32 D_001D545C_3A17B0;
__asm__(".extern D_001D545C_3A17B0, 16");
extern void func_L01_004450F0(void *, s32, s32);
extern s32 func_L01_0045A520(void);
extern void func_L01_004AA7E8(void *, s32);
extern void func_003C7DD8(void *);

void func_L27_003A17B0(S_3A17B0_O *self) {
    S_3A17B0_D *d = self->f68;
    S_3A17B0_E *e;
    s32 i;
    d->b50 = 0;
    d->b51 = 0;
    d->b52 = 0;
    d->b53 = 0;
    e = (S_3A17B0_E *)(D_L27_001DED1C_3A17B0 + (d->f90 << 8));
    d->f14 = 0xFA;
    d->f20 = -1;
    d->f24 = -1;
    d->f18 = 0;
    d->f1C = 0;
    d->f74 = 0;
    d->f6C = 0;
    d->fB8 = 0;
    d->fDC = 0;
    *(u128_t *)&d->v80 = *(u128_t *)&e->v10;
    e->h36 = 0x7F80;
    e->v10.z = e->v10.z + -15.0f;
    func_L01_004450F0(self, 1, 0);
    if (func_L01_0045A520() != 0) {
        d->b51 = 1;
        *(u128_t *)&((S_3A17B0_E *)((d->f4 << 8) + (s32)D_L27_001DED1C_3A17B0))->v10 = *(u128_t *)&D_L27_001DEE00_3A17B0[d->f60].v30;
        *(u128_t *)&((S_3A17B0_E *)((d->f4 << 8) + (s32)D_L27_001DED1C_3A17B0))->vF0 = *(u128_t *)&D_L27_001DEE00_3A17B0[d->f60].v70;
        ((S_3A17B0_E *)((d->f4 << 8) + (s32)D_L27_001DED1C_3A17B0))->h34 &= 0xFFBE;
        ((S_3A17B0_E *)((d->f4 << 8) + (s32)D_L27_001DED1C_3A17B0))->h34 = ((S_3A17B0_E *)((d->f4 << 8) + (s32)D_L27_001DED1C_3A17B0))->h34 | (((S_3A17B0_A *)((S_3A17B0_E *)((d->f4 << 8) + (s32)D_L27_001DED1C_3A17B0))->f24)->h44 & 0x1000);
        ((S_3A17B0_E *)((d->f4 << 8) + (s32)D_L27_001DED1C_3A17B0))->f98 = ((S_3A17B0_A *)((S_3A17B0_E *)((d->f4 << 8) + (s32)D_L27_001DED1C_3A17B0))->f24)->f10;
        ((S_3A17B0_E *)((d->f4 << 8) + (s32)D_L27_001DED1C_3A17B0))->h34 &= 0xFFFD;
        ((S_3A17B0_E *)((d->f58 << 8) + (s32)D_L27_001DED1C_3A17B0))->h34 |= 0x41;
        ((S_3A17B0_E *)((d->f58 << 8) + (s32)D_L27_001DED1C_3A17B0))->h34 &= 0xEFFF;
        ((S_3A17B0_E *)((d->f58 << 8) + (s32)D_L27_001DED1C_3A17B0))->f98 = 0;
        func_L01_004AA7E8((S_3A17B0_E *)(D_L27_001DED1C_3A17B0 + (d->f58 << 8)), 1);
        i = D_001D545C_sda;
    } else {
        d->b51 = 0;
        ((S_3A17B0_E *)((d->f4 << 8) + (s32)D_L27_001DED1C_3A17B0))->h34 |= 0x41;
        ((S_3A17B0_E *)((d->f4 << 8) + (s32)D_L27_001DED1C_3A17B0))->h34 &= 0xEFFF;
        ((S_3A17B0_E *)((d->f4 << 8) + (s32)D_L27_001DED1C_3A17B0))->f98 = 0;
        func_L01_004AA7E8((S_3A17B0_E *)(D_L27_001DED1C_3A17B0 + (d->f4 << 8)), 1);
        ((S_3A17B0_E *)((d->f4 << 8) + (s32)D_L27_001DED1C_3A17B0))->h34 |= 2;
        i = D_001D545C_3A17B0;
    }
    if (D_001BBC40[i][d->f2C] & 0x80) {
        d->b50 = 1;
        func_L01_004450F0(self, 4, 2);
    }
    if (D_001BBC40[D_001D545C_3A17B0][d->f30] & 0x80) {
        d->b52 = 1;
        func_L01_004450F0(self, 5, 1);
    }
    if (D_001BBC40[D_001D545C_3A17B0][d->f34] & 0x80) {
        *(u128_t *)&e->v10 = *(u128_t *)&d->v80;
        d->f74 = 1;
        func_L01_004450F0(self, 6, 2);
    }
    if (D_001BBC40[D_001D545C_3A17B0][d->f38] & 0x80) {
        func_L01_004450F0(self, 7, 1);
    }
    func_003C7DD8(e);
}
