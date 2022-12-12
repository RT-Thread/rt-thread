__heap_end = 0x010000;
MEMORY
{
PAGE 0 :  /* Program Memory */
          /* Memory (RAM/FLASH) blocks can be moved to PAGE1 for data allocation */
          /* BEGIN is used for the "boot to Flash" bootloader mode   */

   BEGIN           	: origin = 0x080000, length = 0x000002
   RESET           	: origin = 0x3FFFC0, length = 0x000002
   RAMGS8_15        : origin = 0x013000, length = 0x009000
   
   /* Flash sectors */
   FLASHA           : origin = 0x080002, length = 0x001FFE	/* on-chip Flash */
   FLASHB           : origin = 0x082000, length = 0x002000	/* on-chip Flash */
   FLASHC           : origin = 0x084000, length = 0x002000	/* on-chip Flash */
   FLASHD           : origin = 0x086000, length = 0x002000	/* on-chip Flash */
   FLASHE           : origin = 0x088000, length = 0x008000	/* on-chip Flash */
   FLASHF           : origin = 0x090000, length = 0x008000	/* on-chip Flash */
   FLASHG           : origin = 0x098000, length = 0x008000	/* on-chip Flash */
   FLASHH           : origin = 0x0A0000, length = 0x008000	/* on-chip Flash */
   FLASHI           : origin = 0x0A8000, length = 0x008000	/* on-chip Flash */
   FLASHJ           : origin = 0x0B0000, length = 0x008000	/* on-chip Flash */
   FLASHK           : origin = 0x0B8000, length = 0x002000	/* on-chip Flash */
   FLASHL           : origin = 0x0BA000, length = 0x002000	/* on-chip Flash */
   FLASHM           : origin = 0x0BC000, length = 0x002000	/* on-chip Flash */
   FLASHN           : origin = 0x0BE000, length = 0x002000	/* on-chip Flash */   

PAGE 1 : /* Data Memory */
         /* Memory (RAM/FLASH) blocks can be moved to PAGE0 for program allocation */
   BOOT_RSVD       : origin = 0x000002, length = 0x000120     /* Part of M0, BOOT rom will use this for stack */
   RAMM0           : origin = 0x000122, length = 0x0002DE
   RAMM1           : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
   EBSS	       	   : origin = 0x008000, length = 0x008000     /* RAMLS0-4, 5*0x0800   */
   CPU2TOCPU1RAM   : origin = 0x03F800, length = 0x000400
   CPU1TOCPU2RAM   : origin = 0x03FC00, length = 0x000400
}


SECTIONS
{
   /* Allocate program areas: */
   .cinit              : > FLASHF      PAGE = 0, ALIGN(4)
   .init_array         : > FLASHF,     PAGE = 0, ALIGN(4)
   .text               : > FLASHE      PAGE = 0, ALIGN(4)
   codestart           : > BEGIN       PAGE = 0, ALIGN(4)

#ifdef __TI_COMPILER_VERSION__
   #if __TI_COMPILER_VERSION__ >= 15009000
    .TI.ramfunc : {} LOAD = FLASHF,
                         RUN = RAMGS8_15,
                         LOAD_START(RamfuncsLoadStart),
                         LOAD_SIZE(RamfuncsLoadSize),
                         LOAD_END(RamfuncsLoadEnd),
                         RUN_START(RamfuncsRunStart),
                         RUN_SIZE(RamfuncsRunSize),
                         RUN_END(RamfuncsRunEnd),
                         PAGE = 0, ALIGN(4)
   #else
   ramfuncs            : LOAD = FLASHF,
                         RUN = RAMGS8_15,
                         LOAD_START(RamfuncsLoadStart),
                         LOAD_SIZE(RamfuncsLoadSize),
                         LOAD_END(RamfuncsLoadEnd),
                         RUN_START(RamfuncsRunStart),
                         RUN_SIZE(RamfuncsRunSize),
                         RUN_END(RamfuncsRunEnd),
                         PAGE = 0, ALIGN(4)   
   #endif
#endif

   FSymTab          : > RAMM1,     PAGE = 1
               LOAD_START(__fsymtab_start)
               LOAD_END(__fsymtab_end)
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

   /* Allocate uninitalized data sections: */
   .stack           : > RAMM1      PAGE = 1
   .sysmem          : > RAMM1      PAGE = 1
   .bss             : > EBSS,	   PAGE = 1
   .data            : > EBSS,
				    LOAD_END(__ebss_end),
				    PAGE = 1

   /* Initalized sections go in Flash */
   .const              : > FLASHF      PAGE = 0, ALIGN(4)
   .switch             : > FLASHF      PAGE = 0, ALIGN(4)
   .reset              : > RESET,      PAGE = 0, TYPE = DSECT /* not used, */
   
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
