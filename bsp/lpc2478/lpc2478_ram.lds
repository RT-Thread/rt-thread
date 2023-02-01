OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
  . = 0xa0000000;

  __text_start = .;
  .text      :
  {
    *(.vectors)
    *(.text)
    *(.text.*)
  } =0
  __text_end = .;

  __rodata_start = .;
  .rodata   : { *(.rodata) *(.rodata.*) }
  __rodata_end = .;

    . = 0xa0100000;
  . = ALIGN(8);
  __data_start = .;
  .data :
  {
        *(.data)
        *(.data.*)
  }
  __data_end = .;

  . = ALIGN(8);
  __bss_start = .;
  .bss       :
  {
   *(.bss)
   *(.bss.*)
   *(COMMON)
   . = ALIGN(4);
  }
  . = ALIGN(4);
  __bss_end = .;

  . = ALIGN(4);
  __UndStack_start = __bss_end;
  .UndStack : { *(.UndStack) }
  __UndStack_end = ( __UndStack_start + 0x00000100 );

  . = ALIGN(4);
  __IRQStack_start = __UndStack_end;
  .IRQStack : { *(.IRQStack) }
  __IRQStack_end = ( __IRQStack_start + 0x00000100 );

  . = ALIGN(4);
  __FIQStack_start = __IRQStack_end;
  .FIQStack : { *(.FIQStack) }
  __FIQStack_end = ( __FIQStack_start + 0x00000100 );

  . = ALIGN(4);
  __SVCStack_start = __FIQStack_end;
  .SVCStack : { *(.SVCStack) }
  __SVCStack_end = ( __SVCStack_start + 0x00000100 );

  . = ALIGN(4);
  __ABTStack_start = __SVCStack_end;
  .ABTStack : { *(.ABTStack) }
  __ABTStack_end = ( __ABTStack_start + 0x00000100 );

  . = ALIGN(4);
  __USRStack_start = __ABTStack_end;
  .USRStack : { *(.USRStack) }
  __USRStack_end = ( __USRStack_start + 0x00003B00 );

  . = ALIGN(4);
  __Heap_start = __USRStack_end;
  .Heap : { *(.Heap) }
  __Heap_end = (__Heap_start + 0x00008000);


  /* Stabs debugging sections.  */
  .stab 0 : { *(.stab) }
  .stabstr 0 : { *(.stabstr) }
  .stab.excl 0 : { *(.stab.excl) }
  .stab.exclstr 0 : { *(.stab.exclstr) }
  .stab.index 0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment 0 : { *(.comment) }

  _end = .;
}
