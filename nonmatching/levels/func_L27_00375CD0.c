/* near miss (level 27, Aquatos Base): 389 diff (437 retail words; this candidate 434, the
   3-word gap is the div.s nops). Needs @ps2as and -mvu0-use-vf0-vf2 on the owning file
   (inline float constants; include/vu0.h). First diffs are prologue allocation/scheduling:
   retail keeps &D_001A4BE0 in $s0, $sp in $s3, out2 in $s6; this C gets out2 in $s4/$fp,
   spills count and rematerialises &v230. Div.s nops in retail: 3 1 2 (this C emits 3/0/0).
   Recipes: the two state tests must be separate ifs; write the redundant if (cur == 0); the
   clear-path loop is while (func_003D3CB0(...) != 0) { if (++i >= 7) break; ... } with a
   continue back to the call after arr[count++]=obj; the final cleanup is a bare
   for (i=0;i<count;i++). VU0 mapping is listed in the original report (vec_* helpers). */
#include "common.h"
#include "vu0.h"

typedef int u128_t __attribute__((mode(TI)));
typedef union { u8 b[0x2A00]; s16 h[0x1500]; u16 uh[0x1500]; s32 i[0xA80]; u32 u[0xA80]; f32 f[0xA80]; u8 *ptr[0xA80]; u128_t q[0x2A0]; } Hero;
typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V4;

extern Hero D_001A4BE0;
extern V4 D_L27_001E83E0;
extern u8 *D_L27_001E83D8[];
extern s32 D_L27_001D673C[];
extern u8 *D_L27_0021BC20[];
extern f32 D_001DD7D4_sda;
__asm__(".extern D_001DD7D4_sda, 4");
extern f32 D_001DD7D0_sda;
__asm__(".extern D_001DD7D0_sda, 4");
extern s32 D_001D6740_sda;
__asm__(".extern D_001D6740_sda, 4");

extern void func_0038CE20(void *, void *, f32);
extern s32 func_003D3CB0(void *, void *, s32, void *, s32);
extern u8 *func_00382348(void *);
extern f32 func_0038CF38(void *, void *);
extern f32 func_0038CF00(void *, void *);
extern f32 func_0038CE68(void *, void *);
extern f32 func_0038CEA8(void *);
extern f32 func_0038D0C8(f32);
extern f32 func_0038D160(f32, f32);
extern f32 func_0038DBA0(f32, f32);
extern void func_00382760(void *, f32, f32, f32);

u8 *func_L27_00375CD0(u8 *m, void *p, f32 *out2, f32 *out3)
{
    V4 pos;
    V4 v10;
    V4 v20;
    void *arr[0x80];
    V4 v230;
    V4 v240;
    V4 v250;
    V4 v260;
    u8 *cur;
    u8 *rec;
    u8 *obj;
    void *pvar;
    u8 *saved;
    f32 lim;
    f32 dist;
    f32 head;
    f32 elev;
    f32 diff;
    f32 dot;
    f32 len;
    f32 ang;
    s32 count;
    s32 idx;
    s32 i;
    s32 hit;

    pos = *(V4 *)p;
    pvar = *(void **)(m + 0x68);
    lim = D_001DD7D4_sda;
    saved = 0;

    func_0038CE20(&v10, D_001A4BE0.ptr[0x970] + 0xE0, 0.5f);
    vec_add_ba(&v20, &pos, D_001A4BE0.ptr[0x970] + 0x10);

    if (func_003D3CB0(&v20, &pos, 6, D_001A4BE0.ptr[0x970], 0) != 0) {
        pos = D_L27_001E83E0;
        return 0;
    }

    count = 0;
    for (idx = 0, cur = D_L27_0021BC20[0]; cur != 0; cur = D_L27_0021BC20[++idx]) {
        if (*(u8 *)(cur + 0x20) == 0xFE) continue;
        if (*(u8 *)(cur + 0x20) == 0xFD) continue;
        if (*(s16 *)(cur + 0xAA) == 0x1BC3 || *(s16 *)(cur + 0xAA) == 0x189B ||
            *(s16 *)(cur + 0xAA) == 0x1D3E || *(s16 *)(cur + 0xAA) == 0x1A90) continue;
        v230 = *(V4 *)(cur + 0x10);
        rec = func_00382348(cur);
        if (rec == 0 || *(u8 *)(rec + 0xE) == 3) continue;
        func_0038CE20(&v240, cur + 0xE0, *(f32 *)(rec + 0x10));
        vec_add_ab(&v230, &v230, &v240);
        if (cur == 0 || *(void **)(cur + 0x24) == 0 ||
            *(u8 *)(*(u8 **)(cur + 0x24) + 0x46) != 5) continue;

        head = func_0038D160(v230.x - pos.x, v230.y - pos.y);
        elev = func_0038D160(func_0038CF38(&pos, &v230), v230.z - pos.z);
        diff = func_0038DBA0(*out2, head);
        dist = func_0038CF00(&pos, &v230);

        hit = 0;
        if (D_L27_001D673C[0] != 0 || D_001A4BE0.h[0x1B4] != 0 || D_001D6740_sda != 0) {
            if (dist < 2.5f) {
                vec_sub_ab(&v250, cur + 0x10, D_001A4BE0.ptr[0x970] + 0x10);
                dot = func_0038CE68(&v250, D_001A4BE0.ptr[0x970] + 0xE0);
                if (fabs_asm(dot) < 2.0f) {
                    func_0038CE20(&v260, D_001A4BE0.ptr[0x970] + 0xE0, 0.5f);
                    vec_sub_ab(&v250, &v250, &v260);
                    dot = func_0038CE68(&v250, D_001A4BE0.ptr[0x970] + 0xC0);
                    len = func_0038CEA8(&v250);
                    if (len != 0.0f && 1.5707964f - func_0038D0C8(dot / len) < 1.0471976f) hit = 1;
                }
            }
        } else {
            if (dist < 2.5f) {
                ang = func_0038D160(*(f32 *)(cur + 0x10) - D_001A4BE0.f[0x20],
                                    *(f32 *)(cur + 0x14) - D_001A4BE0.f[0x21]);
                if (func_0038DBA0(*(f32 *)(D_001A4BE0.ptr[0x970] + 0xF8), ang) < 1.0471976f &&
                    fabs_asm(pos.z - v230.z) < 2.0f) hit = 1;
            }
        }
        if (hit) {
            if (func_003D3CB0(&pos, &v230, 6, D_001A4BE0.ptr[0x970], 0) == 0) {
                *out3 = -elev;
                *out2 = head;
                saved = cur;
                goto done;
            }
        }
        if (dist > lim && cur != *(u8 **)(pvar + 0x10)) continue;
        if (dist > D_001DD7D4_sda) continue;

        func_00382760(&v240, dist, *out2, *out3 + *(f32 *)(D_001A4BE0.b + 0x344) * 0.5f);
        vec_add_ab(&v240, &v240, &pos);
        ang = func_0038D0C8(func_0038CF00(&v240, &v230) / (dist + dist));
        ang = ang + ang;
        if (ang > D_001DD7D0_sda * 0.017453292f) {
            rec = func_00382348(cur);
            if (rec != 0) {
                dot = *(u8 *)(rec + 0xA) * 0.125f;
                func_0038D0C8(dot / dist);
                if (dot >= dist) {
                    ang = ang - D_001DD7D0_sda;
                    if (ang < 0.0f) ang = 0.0f;
                }
            }
        }
        if (ang < D_001DD7D0_sda * 0.017453292f) {
            v250 = pos;
            hit = 1;
            i = 0;
            for (;;) {
                if (func_003D3CB0(&v250, &v230, 6, m, 0) == 0) break;
                if (++i >= 7) break;
                obj = D_L27_001E83D8[0];
                if (obj == 0) {
                    hit = 0;
                    break;
                }
                if (*(s16 *)(obj + 0xAA) == 0x1BC3 || *(s16 *)(obj + 0xAA) == 0x189B ||
                    *(s16 *)(obj + 0xAA) == 0x1D3E) {
                    arr[count++] = obj;
                    *(void **)(obj + 0x98) = 0;
                    if (count >= 0x80) break;
                    v250 = D_L27_001E83E0;
                    continue;
                }
                if (obj == cur) break;
                hit = 0;
                break;
            }
        }
        if (hit) {
            *out3 = -elev;
            lim = dist;
            if (diff < 0.17453292f) *out2 = head;
            saved = cur;
            if (cur == *(u8 **)(pvar + 0x10)) break;
        }
    }

done:
    for (i = 0; i < count; i++) {
        obj = arr[i];
        *(void **)(obj + 0x98) = *(void **)(*(u8 **)(obj + 0x24) + 0x10);
    }
    return saved;
}
