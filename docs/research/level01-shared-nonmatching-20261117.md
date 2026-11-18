# Level 1 shared nonmatching retry — started 2026-11-17, finalized 2026-11-18

Scope: ten canonical L01 functions in cadelass's reserved shared source files,
excluding other contributors' named functions in coordination issue #3. Work stayed
on `pr/level-07-batch-2`, using the shared-tree claims and lock protocol.
The original research snapshot was `ef7b52d2`. Other agents updated the shared
branch before resumption, so that snapshot is not an ancestor of the resumed HEAD
`47d829cb`; the final review scopes this pass's explicit paths. The three changed
owning-file flag rows remain identical to the original snapshot. Other agents'
source, metadata and commits are outside this pass.

## Results

Differences below are raw `check.py` word differences with current owning-file flags,
not old reported scores or masked/aligned comparisons. A candidate is counted as
integrated only after every affected PAL level's full build prints `MATCH`.

| Function | Reproduced baseline | Best | Outcome / remaining condition |
| --- | ---: | ---: | --- |
| `func_L01_0030B818` | 3 | 3 | Unchanged; speculative argument move changes the branch-likely and duplicated increment. |
| `func_L01_0037F860` | 43 | 2 | Missing `divs_nops` row corrected; legal unified VU block still reverses the decrement and `sqc2`. |
| `func_L01_003C5DF0` | 2 | 2 | Unchanged; three legal helper/dataflow forms give the same reversed `lqc2` loads. |
| `func_L01_003E9218` | Compile error | 11 | Improved draft compiles; VU interleaving and a later owner prototype still prevent integration. |
| `func_L01_00445438` | 4 | 4 | Unchanged; scalar argument move/product lie inside retail's first VU sequence. |
| `func_L01_00447490` | 4 | 4 | Unchanged; cached slot removes a required move, table forms do not fix the prefix. |
| `func_L01_00459EF0` | L01: 0; L39: 3 | 0 | MATCH at 49 placements; resolves the moved data and divergent callee with caller-suffixed aliases. |
| `func_L01_004CB128` | 3 | 3 | Unchanged; typed fields/real callee argument leave the same success branch and VU interleaving. |
| `func_L01_00511A98` | 5 | 5 | Unchanged; real hero field is identical, loop-note variants worsen return scheduling. |
| `func_L01_00514750` | 5 | 0 | MATCH at 34 placements; names the fallback constant before destination initialization. |

Two integrated matches, two improved/repaired drafts, six unchanged near misses;
all ten functions were attempted, none skipped. The `0037F860` reduction is a
configuration correction plus an explicit VU dataflow contract, not a newly found
C scheduling solution. The historical draft's implicit `vf2` state across separate
asm blocks is not an accepted zero-difference implementation.

The reserved-scope scan found 485 eligible saved drafts. The other 475 saved
drafts and 129 remaining markers without drafts were outside the requested
ten-function limit, not structural skips. Their exact names are preserved in
local `unattempted.json`; `candidates.json` and `todo-final.tsv` preserve the
selection evidence. The two integrations leave 612 eligible markers in that
reserved scope, including this pass's eight near misses.
These inventory counts describe the original pass, before later concurrent
contributions, and do not override active reservations for future work.

Twenty other saved drafts already have C in their reserved owning files and were
excluded from retries. They are listed separately in local `already-c-drafts.json`;
their files and README rows were preserved. This historical material includes the
already-converted function repaired below and is not additional nonmatching work.

## Pre-existing integration repair

The first full placement run exposed an unrelated earlier portability error in
already-converted `func_L01_003D2A18`, within another reserved shared file,
`L01_003D0D48.c`. Its call used bare `func_003D25D8`, fixing the target to the
level 1 address. In level 9 retail calls the catalogue function at `0x003E48E8`.
The owning file was byte-identical to integration baseline `ef7b52d2` before the
repair. The unchanged baseline reproduces one differing word in level 9;
the corrected `func_L01_003D25D8` call, using its existing real pointer prototype,
matches level 9 and preserves level 1's match. The full build covers all six
placements (1, 9, 12, 20, 26 and 29). This repairs existing C; it is not an eleventh
decompilation attempt or a third new match.

## Evidence and retry conditions

- `00459EF0`: the saved resident data name gives the wrong multiplayer address,
  and level 39 calls a different copy than the catalogue callee. The existing
  caller-alias recipe solves both without a catalogue edit. The scratch object
  audit derives all 49 placements, including level 39's `0x00598770` call.
- `00514750`: initialize `fallback = 0xCC` before calculating `dest`, then
  initialize `previous` and the counter. This applies the existing loop-invariant
  initialization recipe. A `.sdata` alias for the previous-buffer address leaves
  the old five differences unchanged. Independent review then found that the
  owner's short hero type and scalar previous-buffer declaration do not cover
  the loop's accesses. The final implementation uses caller-suffixed resident
  aliases with a private hero request layout and a genuine four-word previous
  array. Both pointer walks remain within their declared extents (the final
  increment forms a legal one-past pointer). A correctly sized `.sdata` array
  declaration preserves the previous address's one-`la` form. The corrected
  object audit covers all 34 placements with zero differences; full builds are
  rerun after this source-quality correction. The earlier neighboring scalar
  buffer loop is pre-existing code outside this retry.
- `0037F860`: the two retail nops at `0x0037F898` and `0x0037F89C` precede
  `div.s` at `0x0037F8A0`; the preceding instruction is a store, not a branch.
  The new row is `func_L01_0037F860 2`. After applying it, the legal VU block
  differs only at `+0x74/+0x78` (`sqc2` versus counter decrement). The existing
  j-operand route cannot compile under this file's current fixed VU-register flags.
- `003E9218`: retail passes both a vector pointer in `a1` and an independent
  float in `f12`. The corrected pointer-plus-float declaration and callee alias
  remove the compile error. The legal intact block is four bytes shorter and
  changes the pointer-load/call-slot order. Its definition also disagrees with a
  later owner declaration. Existing j-form helpers require a separately proven
  whole-file VU flag decision; no per-function flag or ordinary EE asm was used.
- `0030B818`: non-void return metadata, precise typed records, a statement-loop
  wrapper, and next-pointer forms did not resolve the branch; the `.sdata` table
  alias worsened the prologue. Baseline, return-metadata and typed skip forms
  produced identical best wrong bytes (seven checks total).
- `003C5DF0`: `vec_add_ab`, `vec_add_ba` and direct typed j-form loads are
  identical at the residual. Inlining the angle expression worsens 2 to 41.
  Four checks; stopped after three identical wrong forms.
- `00445438`: real callee prototype and splitting complement/product evaluation
  give the original four differences. Three checks; a whole-file VU-register
  change remains unproven and was not adopted.
- `00447490`: cached signed/narrow slot and an inline byte accessor give the
  same shorter wrong body (20 differences); `.sdata` gives 19; a typed strided
  table retains four. Six checks, preserving the original MIT-licensed draft.
- `004CB128`: the real moby parameter and typed fields retain the same three
  differences; early return and shared-success goto forms worsen to 37 and 41.
  Five checks; stopped on three equivalent wrong forms.
- `00511A98`: accessing the actual hero state member retains five differences.
  Two documented loop-note variants worsen to 15. Four checks; the older generic
  switch/branch/result search was not repeated.

No new vector helper, flag, ordinary EE asm, register pin, game-data volatile,
hardcoded game address, or alias macro was introduced. Existing drafts of the
integrated functions remain as historical material; unchanged drafts were retained.

## Validation

The initial level 1 full build printed:

```text
01_veldin: MATCH: 01_veldin.bin sha1 aab9a95641fa24e3acaec9c04369e942b3689e38; as the disc stores it: sha1 1b44af14c1fc005d439bc026a092b5734e6b2fb6
1 of 1 levels match
```

The initial core attempt failed because generated assembly still used old
handwritten/remnant classifications. Regenerating boot_elf assembly fixed that
infrastructure issue; no core source was changed. The repeated full core build
printed all three retail hashes:

```text
MATCH: build/frontbin.bin sha1 5a7ff1fe9c73a63c6ce6fe7b5f80cd7cab3aa553 (0x21DEEC bytes)
MATCH: build/boot_elf/boot_elf.bin sha1 e0a4e82e9a363a64db5a555db8c8f927ef58c3d8 (0x35EE64 bytes)
MATCH: build/i5bootn/i5bootn.bin sha1 c1166658edad1b6b04b7671af77fff53f2560e71 (0xC5E90 bytes)
```

The first placement-build run also encountered childless, zero-CPU `wibo`
processes stalled in futex/IO waits, and a transient assembler failure in level 13
(the identical assembler command passed when repeated). Only this pass's stalled
processes were terminated. That run was stopped before changing the existing
catalogue call above. The final full run uses the same `wibo` binary through a
scratch wrapper that bounds each invocation and retries a failed invocation once.
Persistent compiler errors remain fatal; no source, flags or byte comparison is
changed by a tool retry. Level 30 also needed a repeated build after an assembler
failure without a diagnostic: the unchanged assembler command passed immediately
when repeated. The final placement coverage includes its successful full retry.

The integrated build command was:

```sh
venv/bin/python tools/build_levels.py --setup -P 4 -j 2 \
  --toolchain ~/sn --runner scratch/shared01-nonmatching-20261117/wibo-retry \
  --ee29 ~/ee-gcc2.9-991111-win \
  --ee296 scratch/shared01-nonmatching-20261117/toolchains/ee296 \
  --eeas scratch/shared01-nonmatching-20261117/toolchains/ee-as
```

Its final summary was `48 of 49 levels match`. A repeated full build of the failed level(s), with
the same source, flags and toolchains, printed `1 of 1 levels match`. Across those invocations
all 49 PAL levels printed `MATCH`; `validated-placement-lines.json` records the
49 distinct lines and both ELF/overlay hashes. The original failure messages
remain in the full-build log. The retry command uses `tools/build_levels.py
--setup` with the failed level numbers and the same toolchain/runner arguments.

After independent review, `00514750` received correctly bounded private views
of both four-word buffers. With that final source, a separate complete PAL build
of all34 story placements printed `34 of 34 levels match`. Its exact command/log is
`post-review-build-levels.log`. The code-generating flags stayed unchanged;
caller-suffixed resident aliases preserve the original address forms while
avoiding out-of-bounds arithmetic on the owner's shorter declarations.
`venv/bin/python -m unittest discover -s tests` passed 205 tests (8 skipped).
`tests/check_repository.py` remains failing: 638 errors versus 638 at resumption;
the 0 additional messages are US-map synchronization for this pass's changed source.
The uncapped source/table/progress checks found no unrelated errors. These results
do not establish NTSC-U correctness. Independent review is recorded in the delivery
message and local reviewer evidence.

The initial repository baseline contained 620 errors, all NTSC-U version-map
synchronization errors. NTSC-U retail inputs are absent; carry and US validation
are unavailable, not passing or waived.

Local evidence is under `scratch/shared01-nonmatching-20261117/`: the ten per-function
ledgers and check logs, raw repository-error snapshots, source integration backup,
full build logs and result JSON. The documented ee-gcc 2.96 compiler and Sony
assembler binaries used for validation stay in ignored scratch/toolchains only;
no SDK source, samples, or headers were read or downloaded.

A loaded post-review unit run encountered an existing `/proc/<pid>/status`
cleanup race in `test_check_batch`: the already-terminated compiler disappeared
between opening and reading its status, raising `ProcessLookupError` in the test
helper. No tool or test implementation was changed for this matching pass. The
fresh run with builds stopped passed all 205 tests (8 skipped); its log is
`unit-tests-final-idle.log`.
