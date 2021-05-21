

ENTRY(Startup_Aarch32)

HEAP_SIZE   = DEFINED(__heap_size__)           ? __heap_size__          : 0x0400;
ISTACK_SIZE = DEFINED(__irq_stack_size__)      ? __irq_stack_size__     : 0x0800;
CSTACK_SIZE = DEFINED(__stack_size__)          ? __stack_size__         : 0x0800;
USTACK_SIZE = DEFINED(__user_stack_size__)     ? __user_stack_size__    : 0x0800;



/* Specify the memory areas */
MEMORY
{
  m_mode_transform      (RX)   : ORIGIN = 0x80100000, LENGTH = 0x00000200
  m_interrupts          (RX)   : ORIGIN = 0x80100200, LENGTH = 0x00000040
  m_text                (RX)   : ORIGIN = 0x80100240, LENGTH = 0x003ffdc0
  m_data                (RW)   : ORIGIN = 0x80400000, LENGTH = 0x00800000
  m_stack               (RW)   : ORIGIN = 0x80c00000, LENGTH = 0x00400000
}


/* Define output sections */
SECTIONS
{
    . = 0x80100000 ;
    .mode_transform :
    {
        . = ALIGN(4);
        KEEP(*(.Startup_Aarch32))     /* Startup code */
        . = ALIGN(4);
    } > m_mode_transform

    .interrupts :
    {
        __VECTOR_TABLE = .;
        . = ALIGN(4);
        KEEP(*(.Startup_Ft_Aarch32))     /* Startup code */
        . = ALIGN(4);
    } > m_interrupts

    /* The program code and other data goes into DDR RAM */
    .text :
    {
        . = ALIGN(4);
        *(.text)                 /* .text sections (code) */
        *(.text*)                /* .text* sections (code) */
        *(.rodata)               /* .rodata sections (constants, strings, etc.) */
        *(.rodata*)              /* .rodata* sections (constants, strings, etc.) */
        *(.glue_7)               /* glue arm to thumb code */
        *(.glue_7t)              /* glue thumb to arm code */
        *(.eh_frame)
        KEEP (*(.init))
        KEEP (*(.fini))
        _exit = .;
        . = ALIGN(4);
    } > m_text

    .heap :
    {
        . = ALIGN(8);
        __end__ = .;
        PROVIDE(end = .);
        __HeapBase = .;
        . += HEAP_SIZE;
        __HeapLimit = .;
        __heap_limit = .; /* Add for _sbrk */
    } > m_data

    /* Initializes stack on the end of block */
    .stack :
    {   
        __IStackTop   = .;
        __IStackLimit = __IStackTop - ISTACK_SIZE;
        __CStackTop   = __IStackLimit;
        __CStackLimit = __CStackTop - CSTACK_SIZE;
        __UStackTop   = __CStackLimit; 
        __UStackLimit = __UStackTop - USTACK_SIZE;
        PROVIDE(__stack = __CStackTop);
    } > m_stack


    .rodata ALIGN(4) : {*(.rodata*)} >m_data    
	.data ALIGN(4)   : { *(.data) }  >m_data
}

