/* near miss (level 27, Aquatos Base): 400 diff (386 instructions vs retail 403; 0x608 vs
   0x64C). All 14 callees and the data symbols have retail's call/reloc counts. Left: a
   register-allocation cascade (retail saves s0-s4 with self=$s3, &D_001A4C60=$s4,
   &D_001A7E18=$s2 because its lui 0x8000 mask lives across the help call; ours saves s0-s3),
   three missing condition re-tests (fB8/b51/b52), and missing pointer-global reloads after
   lq/sq stores. Recipes: a block-local destination pointer hoists the store target above
   if (A || B) and fills the beql delay; the help block writes the == 0 arm first;
   `long m = -2147483648; if ((v & m) == 0)` gives retail's single-lui mask; a 4-byte pointer
   global read in a bltz delay slot becomes $gp under @ps2as unless the declaration has
   __attribute__((section(".data"))). No div.s/sqrt.s. Flags already correct. */
typedef struct { f32 f0, f4, f8, fC; } S_2548_OBJ;
typedef struct { s32 f0; u8 p4[8]; s32 fC; u8 p10[0x88]; s32 f98; } S_2548_P;
typedef struct { u8 p0[0x10]; s32 f10; u8 p14[0x30]; u16 h44; } S_2548_SUB;
typedef struct { u8 p0[0x30]; vu0_v4 v30; u8 p40[0x30]; vu0_v4 v70; } S_2548_REF;
typedef struct {
    s32 f0;
    u8 p4[0xC];
    vu0_v4 q10;
    u8 b20;
    u8 p21[3];
    S_2548_SUB *f24;
    u8 p28[0xC];
    u16 h34;
    u8 p36[0x32];
    S_2548_P *f68;
    u8 p6C[0x2C];
    s32 f98;
    u8 p9C[0x54];
    vu0_v4 qF0;
} S_2548_E;
typedef struct {
    u8 p0[4];
    s32 f4;
    u8 p8[0x28];
    s32 f30;
    u8 p34[4];
    s32 f38;
    u8 p3C[0x15];
    u8 b51;
    u8 b52;
    u8 p53;
    s32 f54;
    s32 f58;
    u8 p5C[4];
    s32 f60;
    s32 f64;
    u8 p68[0xC];
    s32 f74;
    s32 f78;
    u8 p7C[0x28];
    s32 fA4;
    s32 fA8;
    s32 fAC;
    s32 fB0;
    s32 fB4;
    S_2548_OBJ *fB8;
    s32 fBC;
    s32 fC0;
    u8 pC4[0x14];
    s32 fD8;
    s32 fDC;
    u8 pE0[0xC];
    s32 fEC;
    s32 fF0;
    u8 pF4[0xC];
    s32 f100;
    s32 f104;
    s32 f108;
    s32 f10C;
    s32 f110;
    s32 f114;
    u8 p118[0x14];
    s32 f12C;
} S_2548_D;

extern void func_L27_003A2B98(void *);
extern s32 func_L01_004561E0(u8 *);
extern s32 func_00382380(void *, s32, s32);
extern void func_L01_0041A5B0(s32, s32);
extern void *func_L01_003F2A50(s32, s32);
extern void func_L01_003F2AF8(s32, void *);
extern s32 func_00392B20(void *, s32);
extern s32 func_00392C78(void *);
extern s32 func_L01_00456250(void *);
extern void func_L01_004AA7E8(void *, s32);
extern void func_L23_003D8628(s32, s32, f32);
extern void func_L01_003F5498(s32, f32);
extern void func_L01_0043B510(s32);
extern void func_L01_004450F0(void *, s32, s32);
extern u8 *D_L27_001DED1C;
__asm__(".extern D_L27_001DED1C, 16");
extern u8 *D_001DED1C_sda;
__asm__(".extern D_001DED1C_sda, 4");
extern S_2548_REF *D_L27_001DEE00_003A2548 __attribute__((section(".data")));
extern u8 D_001A4C60_003A2548[];
extern u8 D_L27_001E8180[];
extern s32 D_001A663C[];
extern s32 D_001A8090[];
extern s32 D_001A81B4[];
extern s32 D_001A8ABC[];
extern s32 D_001A7E18[];
extern f32 D_L27_001DE6D0[];

void func_L27_003A2548(u8 *a0) {
    S_2548_D *d = *(S_2548_D **)(a0 + 0x68);
    s32 v;

    if (func_L01_004561E0(a0)) {
        func_L27_003A2B98(a0);
        d->fDC = 0;
    }
    {
        S_2548_P *q = ((S_2548_E *)(D_L27_001DED1C + (d->fEC << 8)))->f68;
        v = 0;
        if (((S_2548_E *)(D_L27_001DED1C + (d->f104 << 8)))->f68->f0 != 0 ||
            ((S_2548_E *)(D_L27_001DED1C + (d->f108 << 8)))->f68->f0 != 0) {
            v = 1;
        }
        q->fC = v;
    }
    {
        S_2548_P *q = ((S_2548_E *)(D_L27_001DED1C + (d->fF0 << 8)))->f68;
        v = 0;
        if (((S_2548_E *)(D_L27_001DED1C + (d->f110 << 8)))->f68->f0 != 0 ||
            ((S_2548_E *)(D_L27_001DED1C + (d->f114 << 8)))->f68->f0 != 0) {
            v = 1;
        }
        q->fC = v;
    }

    ((S_2548_E *)(D_L27_001DED1C + (d->fA8 << 8)))->f68->f98 =
        ((S_2548_E *)(D_L27_001DED1C + (d->f12C << 8)))->f68->f0;

    if (d->f54 >= 0 && func_00382380(D_001A4C60_003A2548, d->f54, 0) != 0) {
        if (D_001A8ABC[0] >= 0) func_L01_0041A5B0(0x140B, 0x10D);
        d->f54 = -1;
    }
    if (d->fB8 == 0) {
        if (func_00382380(D_001A4C60_003A2548, d->fBC, 0) != 0) {
            d->fB8 = func_L01_003F2A50(0, 5);
            if (d->fB8 != 0) d->fB8->f4 = 3.0f;
        }
    } else if (func_00382380(D_001A4C60_003A2548, d->fBC, 0) == 0) {
        func_L01_003F2AF8(0, d->fB8);
        d->fB8 = 0;
    }
    if (((S_2548_E *)(D_L27_001DED1C + (d->fA4 << 8)))->f68->f0 == 0) {
        if (func_00382380(D_001A4C60_003A2548, d->fAC, 0) != 0) {
            *(f32 *)((u8 *)D_001A4C60_003A2548 + 0x19DC) = 0.4363323152065277f;
            if (d->b51 == 0) {
                if (func_00392B20(D_L27_001E8180, 0xC7) != 0) {
                    func_00392C78(D_L27_001E8180);
                    d->b51 = 1;
                }
            } else {
                if (d->f60 >= 0) {
                    ((S_2548_E *)(D_L27_001DED1C + (d->f4 << 8)))->q10 = ((S_2548_REF *)D_L27_001DEE00_003A2548)[d->f60].v30;
                    ((S_2548_E *)(D_L27_001DED1C + (d->f4 << 8)))->qF0 = ((S_2548_REF *)D_L27_001DEE00_003A2548)[d->f60].v70;
                    ((S_2548_E *)(D_L27_001DED1C + (d->f4 << 8)))->h34 &= 0xFFBE;
                    ((S_2548_E *)(D_L27_001DED1C + (d->f4 << 8)))->h34 |= *(u16 *)((u8 *)((S_2548_E *)(D_L27_001DED1C + (d->f4 << 8)))->f24 + 0x44) & 0x1000;
                    ((S_2548_E *)(D_L27_001DED1C + (d->f4 << 8)))->f98 = ((S_2548_SUB *)((S_2548_E *)(D_L27_001DED1C + (d->f4 << 8)))->f24)->f10;
                    ((S_2548_E *)(D_L27_001DED1C + (d->f4 << 8)))->h34 &= 0xFFFD;
                    ((S_2548_E *)(D_L27_001DED1C + (d->f58 << 8)))->h34 |= 0x41;
                    ((S_2548_E *)(D_L27_001DED1C + (d->f58 << 8)))->h34 &= 0xEFFF;
                    ((S_2548_E *)(D_L27_001DED1C + (d->f58 << 8)))->f98 = 0;
                    func_L01_004AA7E8(D_L27_001DED1C + (d->f58 << 8), 1);
                    d->f60 = -1;
                }
            }
            {
long m = -2147483648;
                if (D_001A7E18[0xD1] >= 0) func_L01_0041A5B0(0xBA2, 0x45);
                d->fDC = d->fDC + 1;
                if (d->fDC >= 0x5DD) {
                    s32 v = D_001A7E18[0xD4];
                    if ((v & m) == 0) func_L01_0041A5B0(0xBA3, 0x46);
                }
            }
        }
        if (((S_2548_E *)(D_L27_001DED1C + (d->f10C << 8)))->f68->f0 != 0) {
            ((S_2548_E *)(D_L27_001DED1C + (d->fA4 << 8)))->f68->f0 = 1;
            D_001A663C[0] = 0;
            d->fDC = 0;
        }
    }
    if (d->fB0 >= 0 && func_00382380(D_001A4C60_003A2548, d->fB0, 0) != 0) {
        d->fDC = d->fDC + 1;
        if (d->fDC >= 0xFB) {
            if (D_001A81B4[0] >= 0) func_L01_0041A5B0(0xBA4, 0x47);
            d->fDC = 0;
            d->fB0 = -1;
        }
    }
    if (d->fB4 >= 0 && func_00382380(D_001A4C60_003A2548, d->fB4, 0) != 0 &&
        d->fC0 != -1 &&
        D_001DED1C_sda[(d->fC0 << 8) + 0x20] != 0xFE &&
        D_001DED1C_sda[(d->fC0 << 8) + 0x20] != 0xFD) {
        d->fDC = d->fDC + 1;
        if (d->fDC >= 0x1F5) {
            if (D_001A8090[0] >= 0) func_L01_0041A5B0(0xB94, 0x37);
            d->fB4 = -1;
            d->fDC = 0;
        }
    }
    ((S_2548_E *)(D_L27_001DED1C + (d->f100 << 8)))->f68->fC =
        func_L01_00456250(D_L27_001DED1C + (d->fD8 << 8));
    if (d->f74 == 0 && func_00382380(D_001A4C60_003A2548, d->f78, 0) != 0) {
        if (d->b52 == 0) {
            if (func_00392B20(D_L27_001E8180, 0xC8) != 0) {
                func_00392C78(D_L27_001E8180);
                d->b52 = 1;
            }
        } else {
            func_L01_0043B510(d->f30);
            func_L01_004450F0(a0, 5, 1);
        }
    }
    if (func_00382380(D_001A4C60_003A2548, d->f64, 0) != 0) {
        func_L23_003D8628(0, 1, 25.0f);
        if (D_L27_001DE6D0[0] >= 1.0f) {
            func_L01_003F5498(0, 25.0f);
            func_L01_0043B510(d->f38);
            func_L01_004450F0(a0, 7, 1);
        }
    }
}
