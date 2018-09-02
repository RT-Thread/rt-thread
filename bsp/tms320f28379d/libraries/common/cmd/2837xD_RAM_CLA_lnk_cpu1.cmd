// The user must define CLA_C in the project linker settings if using the
// CLA C compiler
// Project Properties -> C2000 Linker -> Advanced Options -> Command File
// Preprocessing -> --define
#ifdef CLA_C
// Define a size for the CLA scratchpad area that will be used
// by the CLA compiler for local symbols and temps
// Also force references to the special symbols that mark the
// scratchpad are.
CLA_SCRATCHPAD_SIZE = 0x100;
--undef_sym=__cla_scratchpad_end
--undef_sym=__cla_scratchpad_start
#endif //CLA_C

MEMORY
{
PAGE 0 :
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */

   BEGIN           	: origin = 0x000000,   length = 0x000002
   RAMM0           	: origin = 0x000122,   length = 0x0002DE
   RAMD0           	: origin = 0x00B000,   length = 0x000800
   RAMD1            : origin = 0x00B800,   length = 0x000800
   /* RAMLS4      	    : origin = 0x00A000, length = 0x000800 */
   /* RAMLS5           : origin = 0x00A800, length = 0x000800 */
   RAMLS4_5         : origin = 0x00A000,   length = 0x001000 
   RESET           	: origin = 0x3FFFC0,   length = 0x000002

PAGE 1 :

   BOOT_RSVD        : origin = 0x000002,   length = 0x000120     /* Part of M0, BOOT rom will use this for stack */
   RAMM1            : origin = 0x000400,   length = 0x000400     /* on-chip RAM block M1 */

   RAMLS0          	: origin = 0x008000,   length = 0x000800
   RAMLS1          	: origin = 0x008800,   length = 0x000800
   RAMLS2      		: origin = 0x009000,   length = 0x000800
   RAMLS3      		: origin = 0x009800,   length = 0x000800

   RAMGS0           : origin = 0x00C000,   length = 0x001000
   RAMGS1           : origin = 0x00D000,   length = 0x001000
   RAMGS2           : origin = 0x00E000,   length = 0x001000
   RAMGS3           : origin = 0x00F000,   length = 0x001000
   RAMGS4           : origin = 0x010000,   length = 0x001000
   RAMGS5           : origin = 0x011000,   length = 0x001000
   RAMGS6           : origin = 0x012000,   length = 0x001000
   RAMGS7           : origin = 0x013000,   length = 0x001000
   RAMGS8           : origin = 0x014000,   length = 0x001000
   RAMGS9           : origin = 0x015000,   length = 0x001000
   RAMGS10          : origin = 0x016000,   length = 0x001000
   RAMGS11          : origin = 0x017000,   length = 0x001000
   RAMGS12          : origin = 0x018000,   length = 0x001000     /* Only Available on F28379D, F28377D, F28375D devices. Remove line on other devices. */
   RAMGS13          : origin = 0x019000,   length = 0x001000     /* Only Available on F28379D, F28377D, F28375D devices. Remove line on other devices. */
   RAMGS14          : origin = 0x01A000,   length = 0x001000     /* Only Available on F28379D, F28377D, F28375D devices. Remove line on other devices. */
   RAMGS15          : origin = 0x01B000,   length = 0x001000     /* Only Available on F28379D, F28377D, F28375D devices. Remove line on other devices. */

   EMIF1_CS0n       : origin = 0x80000000, length = 0x10000000
   EMIF1_CS2n       : origin = 0x00100000, length = 0x00200000
   EMIF1_CS3n       : origin = 0x00300000, length = 0x00080000
   EMIF1_CS4n       : origin = 0x00380000, length = 0x00060000
   EMIF2_CS0n       : origin = 0x90000000, length = 0x10000000
   EMIF2_CS2n       : origin = 0x00002000, length = 0x00001000

   CANA_MSG_RAM     : origin = 0x049000,   length = 0x000800
   CANB_MSG_RAM     : origin = 0x04B000,   length = 0x000800

   CLA1_MSGRAMLOW   : origin = 0x001480,   length = 0x000080
   CLA1_MSGRAMHIGH  : origin = 0x001500,   length = 0x000080
}

SECTIONS
{
   codestart        : > BEGIN,      PAGE = 0
   .text            : >> RAMM0 | RAMD0 | RAMD1,    PAGE = 0
   .cinit           : > RAMM0,      PAGE = 0
   .pinit           : > RAMM0,      PAGE = 0
   .switch          : > RAMM0,      PAGE = 0
   .reset           : > RESET,      PAGE = 0, TYPE = DSECT /* not used, */

   .stack           : > RAMM1,      PAGE = 1
   .ebss            : > RAMLS2,     PAGE = 1
   .econst          : > RAMLS3,     PAGE = 1
   .esysmem         : > RAMLS3,     PAGE = 1
   Filter_RegsFile  : > RAMGS0,	    PAGE = 1

   .em1_cs0         : > EMIF1_CS0n, PAGE = 1
   .em1_cs2         : > EMIF1_CS2n, PAGE = 1
   .em1_cs3         : > EMIF1_CS3n, PAGE = 1
   .em1_cs4         : > EMIF1_CS4n, PAGE = 1
   .em2_cs0         : > EMIF2_CS0n, PAGE = 1
   .em2_cs2         : > EMIF2_CS2n, PAGE = 1

    /* CLA specific sections */
   Cla1Prog         : > RAMLS4_5, PAGE=0

   CLADataLS0		: > RAMLS0, PAGE=1
   CLADataLS1		: > RAMLS1, PAGE=1

   Cla1ToCpuMsgRAM  : > CLA1_MSGRAMLOW,   PAGE = 1
   CpuToCla1MsgRAM  : > CLA1_MSGRAMHIGH,  PAGE = 1

   /* The following section definition are for SDFM examples */
   Filter1_RegsFile : > RAMGS1,	PAGE = 1, fill=0x1111
   Filter2_RegsFile : > RAMGS2,	PAGE = 1, fill=0x2222
   Filter3_RegsFile : > RAMGS3,	PAGE = 1, fill=0x3333
   Filter4_RegsFile : > RAMGS4,	PAGE = 1, fill=0x4444

#ifdef __TI_COMPILER_VERSION__
   #if __TI_COMPILER_VERSION__ >= 15009000
    .TI.ramfunc : {} > RAMM0,      PAGE = 0
   #else
    ramfuncs    : > RAMM0      PAGE = 0   
   #endif
#endif

#ifdef CLA_C
   /* CLA C compiler sections */
   //
   // Must be allocated to memory the CLA has write access to
   //
   CLAscratch       :
                     { *.obj(CLAscratch)
                     . += CLA_SCRATCHPAD_SIZE;
                     *.obj(CLAscratch_end) } >  RAMLS1,  PAGE = 1

   .scratchpad      : > RAMLS1,       PAGE = 1
   .bss_cla		    : > RAMLS1,       PAGE = 1
   .const_cla	    : > RAMLS1,       PAGE = 1
#endif //CLA_C
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
