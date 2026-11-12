/* near miss (level 27, Aquatos Base): 1 diff, the catalogue-cut-delay-slot class (as
   func_L01_00350040 and func_L11_004AFFF0). Retail is `lbu $v0,0($a0); jr $ra` and its
   delay-slot `sltiu $v0,$v0,1` is counted as the 4-byte LINKER_REMNANT func_L27_00410030 at
   0x00410030. C emits the comparison before the jr, so the function is 12 bytes in the other
   order and the build shifts. Needs the remnant to become this function's delay slot. */
s32 func_L27_00410028(u8 *p)
{
    return p[0] == 0;
}
