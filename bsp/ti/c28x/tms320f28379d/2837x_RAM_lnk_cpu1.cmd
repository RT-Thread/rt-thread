__heap_end = 0x00F000;

MEMORY
{
PAGE 0 :
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */

    BEGIN          : origin = 0x000000, length = 0x000002
    RAMM0          : origin = 0x000122, length = 0x0002DE
    RESET          : origin = 0x3FFFC0, length = 0x000002
    RAMGS8_15      : origin = 0x013000, length = 0x009000

PAGE 1 :
    RAMM1          : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
    BOOT_RSVD      : origin = 0x000002, length = 0x000120     /* Part of M0, BOOT rom will use this for stack */
    EBSS	       : origin = 0x008000, length = 0x007000     /* RAMLS0-4, 5*0x0800   */
    ECONST         : origin = 0x00F000, length = 0x004000     /* RAMGS0-2, 3*0x1000   */
    CPU2TOCPU1RAM  : origin = 0x03F800, length = 0x000400
    CPU1TOCPU2RAM  : origin = 0x03FC00, length = 0x000400
}

SECTIONS
{
   codestart        : > BEGIN,     PAGE = 0
   
#ifdef __TI_COMPILER_VERSION__
   #if __TI_COMPILER_VERSION__ >= 15009000
    .TI.ramfunc : {} > RAMM0,      PAGE = 0
   #else
   ramfuncs         : > RAMM0      PAGE = 0   
   #endif
#endif   
   .text            : > RAMGS8_15, PAGE = 0
   .cinit           : > RAMM0,     PAGE = 0
   .init_array      : > RAMM0,     PAGE = 0
   .switch          : > RAMM0,     PAGE = 0
   .reset           : > RESET,     PAGE = 0, TYPE = DSECT /* not used, */
   .rti_fn.0.end    : > RAMM1,     PAGE = 1
   .rti_fn.0        : > RAMM1,     PAGE = 1
   .rti_fn.1        : > RAMM1,     PAGE = 1
   .rti_fn.2        : > RAMM1,     PAGE = 1
   .rti_fn.3        : > RAMM1,     PAGE = 1
   .rti_fn.4        : > RAMM1,     PAGE = 1
   .rti_fn.5        : > RAMM1,     PAGE = 1
   .rti_fn.1.end    : > RAMM1,     PAGE = 1
   .rti_fn.6.end    : > RAMM1,     PAGE = 1
   .rti_fn.6        : > RAMM1,     PAGE = 1
   .stack           : > RAMM1,     PAGE = 1
   .sysmem          : > RAMM1,     PAGE = 1
   .bss             : > EBSS,      PAGE = 1
   .data            : > EBSS,
				    LOAD_END(__ebss_end),
				    PAGE = 1
   .const           : > ECONST,  PAGE = 1

   /* finsh symbol table */
   FSymTab          : > RAMM1,   PAGE = 1
   LOAD_START(__fsymtab_start)
   LOAD_END(__fsymtab_end)

   /* The following section definitions are required when using the IPC API Drivers */ 
    GROUP : > CPU1TOCPU2RAM, PAGE = 1 
    {
        PUTBUFFER 
        PUTWRITEIDX 
        GETREADIDX 
    }
    
    GROUP : > CPU2TOCPU1RAM, PAGE = 1
    {
        GETBUFFER :    TYPE = DSECT
        GETWRITEIDX :  TYPE = DSECT
        PUTREADIDX :   TYPE = DSECT
    }  
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
