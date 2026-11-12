/* near miss (level 27, Aquatos Base): 436 diff (466 instructions vs retail 457; 0x748 vs
   0x724). Structurally correct (0x180 frame, six callee-saved float regs, all VU0 sequences),
   but the entry-pointer allocation differs across the body ($s1/$s4 vs retail $s2/$s3; retail
   strength-reduces entry+4 into $s0 and spills count). Catalogue's last word is jr $ra and its
   delay slot is the existing LINKER_REMNANT func_L27_0042003C, the documented class.
   Needs -mvu0-use-vf0-vf2 and @ps2as on the owning file. One sqrt.s (0x41FE44) with 2 nops
   -> divs_nops row func_L27_0041F918 2.

   Recipes: SN cc1 has HAVE_casesi 0 and CASE_VALUES_THRESHOLD 5, so a 5-way dispatch becomes
   a jump table; adding two far empty labels (case 100: case 101: break;) makes the balanced
   compare tree retail has. Shared tails must be explicit gotos (4pi/3 r^3 block and the phase-2
   rejection sampling); duplicating them costs ~45 instructions. Constants as locals control
   hoisting (k/halfpi hoisted; 4.1887903f/4.1877432f literal inside the case bodies). The
   switch index must be s32. VU0 helper mapping is in the original report. */
#include "common.h"
#include "vu0.h"

typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V4_41F918;

typedef struct {
    u32 flags;
    union {
        u32 index;
        f32 value;
        struct { s16 a; s16 b; } pair;
    } u;
    u32 pad8;
    f32 f0C;
    V4_41F918 v;
} E_41F918;

typedef struct {
    u8 pad0[2];
    s16 count2;
    s32 count;
    u8 pad8[8];
    E_41F918 entries[1];
} H_41F918;

typedef struct { u8 pad0[0x10]; H_41F918 *hdr; } P_41F918;

typedef struct {
    u8 pad0[0x10];
    V4_41F918 pos;
    u8 pad20[4];
    P_41F918 *p24;
    u8 pad28[4];
    f32 scale2C;
    u8 pad30[0x90];
    V4_41F918 mtx[3];
} S_41F918;

extern void func_003C97F0(void *, s32, s32);
extern f32 func_003824E0(f32, f32);
extern f32 func_00382538(void);
extern f32 func_0038CEA8(void *);
extern void func_0038CE20(void *, void *, f32);
extern void func_0038CE50(void *, void *, f32);
extern void func_0038D000(void *, void *, void *);
extern f32 func_0038D098(f32);
extern f32 func_0038D0B0(f32);
extern void func_L01_0040E408(void *, void *, f32);
extern void func_12FF10(void *, void *, f32);

s32 func_L27_0041F918(S_41F918 *s, s32 max, u8 *out, s32 mask, f32 density)
{
    f32 w[20];
    E_41F918 *ptrs[20];
    V4_41F918 tmp;
    V4_41F918 v;
    V4_41F918 v2;
    V4_41F918 v3;
    V4_41F918 v4;
    H_41F918 *h;
    E_41F918 *e;
    f32 total = 0.0f;
    f32 k = 0.0009765625f;
    f32 halfpi = 1.5707964f;
    s32 count = 0;
    s32 i = 0;
    s32 n;
    s32 idx;
    u32 last;
    f32 fr;
    f32 lo;
    f32 hgt;
    f32 zz;
    f32 ang;
    f32 uuu;
    f32 volr;
    s32 etype;

    h = s->p24->hdr;
    if (h == 0) return 0;
    if (h->count2 != 0) func_003C97F0(s, h->count2, 0);
    if (h->count <= 0) return 0;
    e = h->entries;
    do {
        u32 flags;
        s32 type;
        flags = e->flags;
        last = flags >> 31;
        type = flags & 0xFF;
        if ((((mask >> i) ^ 1) & 1) == 0 && (flags & 0x20000)) {
            ptrs[count] = e;
            switch (type) {
            case 0:
            case 1:
                tmp = e->v;
                func_0038CE50(&tmp, &tmp, s->scale2C * k);
                volr = tmp.z;
                goto vol;
            case 2:
                tmp = *(V4_41F918 *)(0x70000000 + e->u.index * 16);
                v = e->v;
                vec_add_ab(&tmp, &tmp, &v);
                func_0038CE20(&tmp, &tmp, s->scale2C * k);
                volr = e->f0C * s->scale2C * k;
            vol:
                w[count] = 4.1887903f * volr * volr * volr;
                break;
            case 3:
                tmp = e->v;
                func_0038CE20(&tmp, &tmp, s->scale2C);
                w[count] = 4.1877432f * (tmp.z * s->scale2C * k) * (tmp.z * s->scale2C * k)
                           * (tmp.z * s->scale2C * k)
                           + (tmp.z * s->scale2C * k) * halfpi * (tmp.z * s->scale2C * k)
                                 * (tmp.z * s->scale2C * k) * (e->u.value * (s->scale2C * k));
                break;
            case 4:
                func_12FF10(&tmp, (V4_41F918 *)(0x70000000 + e->u.pair.a * 16), s->scale2C * k);
                func_12FF10(&v, (V4_41F918 *)(0x70000000 + e->u.pair.b * 16), s->scale2C * k);
                vec_sub_ab(&v2, &tmp, &v);
                w[count] = (e->f0C * s->scale2C * k) * halfpi * (e->f0C * s->scale2C * k)
                           * func_0038CEA8(&v2);
                break;
            case 100:
            case 101:
                break;
            }
            total += w[count];
            count++;
        }
        e++;
        i++;
    } while (!last);
    n = (s32)(density * total + 0.5f);
    if (max < n) n = max;
    for (i = 0; i < n; i++) {
        f32 t = func_003824E0(0.0f, total);
        idx = 0;
        if (count > 0 && t >= w[0]) {
            f32 acc = w[0];
            for (idx = 1; idx < count; idx++) {
                t -= acc;
                acc = w[idx];
                if (t < acc) break;
            }
        }
        e = ptrs[idx];
        etype = e->flags & 0xFF;
        switch (etype) {
        case 0:
        case 1:
            tmp = e->v;
            func_0038CE20(&tmp, &tmp, s->scale2C);
            fr = tmp.z;
            goto sample;
        case 2:
            tmp = *(V4_41F918 *)(0x70000000 + e->u.index * 16);
            v = e->v;
            vec_add_ab(&tmp, &tmp, &v);
            func_0038CE20(&tmp, &tmp, s->scale2C);
            fr = e->f0C;
        sample:
            fr = fr * s->scale2C * 0.0009765625f;
            lo = -fr;
            func_L01_0040E408(&tmp, &tmp, 1024.0f);
            do {
                v.x = func_003824E0(lo, fr);
                v.y = func_003824E0(lo, fr);
                v.z = func_003824E0(lo, fr);
            } while (func_0038CEA8(&v) > fr);
            vec_add_ba(&v, &v, &tmp);
            func_0038D000(&v, &v, s->mtx);
            vec_add_ba((V4_41F918 *)(out + i * 16), &v, &s->pos);
            break;
        case 3:
            tmp = e->v;
            func_0038CE20(&tmp, &tmp, s->scale2C);
            fr = tmp.z * s->scale2C * 0.0009765625f;
            hgt = e->u.value * s->scale2C * 0.0009765625f;
            func_L01_0040E408(&tmp, &tmp, 1024.0f);
            fr = sqrt_asm(func_003824E0(0.0f, fr * fr));
            zz = func_003824E0(0.0f, hgt);
            ang = func_00382538();
            v.x = func_0038D098(ang) * fr;
            v.y = func_0038D0B0(ang) * fr;
            v.z = zz;
            vec_add_ba(&v, &v, &s->pos);
            vec_add_ba((V4_41F918 *)(out + i * 16), &v, &tmp);
            break;
        case 4:
            func_12FF10(&tmp, (V4_41F918 *)(0x70000000 + e->u.pair.a * 16), s->scale2C * 0.0009765625f);
            func_12FF10(&v, (V4_41F918 *)(0x70000000 + e->u.pair.b * 16), s->scale2C * 0.0009765625f);
            vec_sub_ba(&v2, &v, &tmp);
            uuu = func_003824E0(0.0f, 1.0f);
            func_0038CE20(&v2, &v2, uuu);
            vec_add_ab(&v3, &v2, &tmp);
            func_L01_0040E408(&v3, &v3, 1024.0f);
            fr = e->f0C * s->scale2C * 0.0009765625f;
            lo = -fr;
            do {
                v4.x = func_003824E0(lo, fr);
                v4.y = func_003824E0(lo, fr);
                v4.z = func_003824E0(lo, fr);
            } while (func_0038CEA8(&v4) > fr);
            vec_add_ba(&v4, &v4, &v3);
            func_0038D000(&v4, &v4, s->mtx);
            vec_add_ba((V4_41F918 *)(out + i * 16), &v4, &s->pos);
            break;
        case 100:
        case 101:
            break;
        }
    }
    return n;
}
