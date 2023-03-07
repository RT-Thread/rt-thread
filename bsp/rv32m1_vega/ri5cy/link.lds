/* Entry Point */
OUTPUT_ARCH( "riscv" )

STACK_SIZE = DEFINED(__stack_size__) ? __stack_size__ : 0x1000;

/* Specify the memory areas */
MEMORY
{
  m_vector              (RX)  : ORIGIN = 0x000FFF00, LENGTH = 0x00000100
  m_text                (RX)  : ORIGIN = 0x00000000, LENGTH = 0x000FFF00
  m_data                (RW)  : ORIGIN = 0x20000000, LENGTH = 0x00030000 - 0x1800
}

/* Define output sections */
SECTIONS
{
  .vectors : ALIGN(4)
  {
    __VECTOR_TABLE = .;
    KEEP(*(.vectors))
  } > m_vector

  /* The program code and other data goes into internal flash */
  .text :
  {
    . = ALIGN(4);
    KEEP(*(.startup))
    . = ALIGN(4);
    __user_vector = .;
    KEEP(*(user_vectors))
    *(.text)                 /* .text sections (code) */
    *(.text*)                /* .text* sections (code) */
    *(.rodata)               /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)              /* .rodata* sections (constants, strings, etc.) */
    *(.eh_frame)
    *(.init)
    *(.fini)

    /* section information for finsh shell */
    . = ALIGN(4);
    __fsymtab_start = .;
    KEEP(*(FSymTab))
    __fsymtab_end = .;
    . = ALIGN(4);
    __vsymtab_start = .;
    KEEP(*(VSymTab))
    __vsymtab_end = .;
    . = ALIGN(4);

    /* section information for initial. */
    . = ALIGN(4);
    __rt_init_start = .;
    KEEP(*(SORT(.rti_fn*)))
    __rt_init_end = .;
    . = ALIGN(4);
  } > m_text

  .preinit_array :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } > m_text

  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } > m_text

  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } > m_text

  __etext = .;    /* define a global symbol at end of code */
  __global_pointer = .;    /* define a global symbol at end of code */
  __DATA_ROM = .; /* Symbol is used by startup for data initialization */

  .data : AT(__DATA_ROM)
  {
    . = ALIGN(4);
    __DATA_RAM = .;
    __data_start__ = .;      /* create a global symbol at data start */
    *(.data)                 /* .data sections */
    *(.data*)                /* .data* sections */
    *(.sdata .sdata.*)
    *(.heapsram*)            /* This is only for the pulpino official test code. */
    __noncachedata_start__ = .;   /* create a global symbol at ncache data start */
    *(NonCacheable)
    __noncachedata_end__ = .;     /* define a global symbol at ncache data end */
    KEEP(*(.jcr*))
    . = ALIGN(4);
    __data_end__ = .;        /* define a global symbol at data end */
  } > m_data

  __DATA_END = __DATA_ROM + (__data_end__ - __data_start__);
  text_end = ORIGIN(m_text) + LENGTH(m_text);
  ASSERT(__DATA_END <= text_end, "region m_text overflowed with text and data")

  _edata = .;

  .stack :
  {
    . = ALIGN(8);
    __StackLimit = .;
    . += STACK_SIZE;
    __StackTop = .;
  } > m_data

  /* Initializes stack on the end of block */
  PROVIDE(__stack = __StackTop);
  PROVIDE( __rt_rvstack = .);

  /* Uninitialized data section */
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss section */
    . = ALIGN(4);
    __START_BSS = .;
    __bss_start__ = .;
    *(.bss)
    *(.bss*)
    *(.sbss)
    *(.sbss*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
    __END_BSS = .;
  } > m_data

  /* End of uninitalized data segement */
  _end = .;
  PROVIDE(end = .);
}
