/* Default linker script, for normal executables */
OUTPUT_FORMAT("elf32-avr32", "elf32-avr32",
          "elf32-avr32")
OUTPUT_ARCH(avr32:uc)
ENTRY(_start)
SEARCH_DIR("/home/mingwbuild/mingwavr32/avr32/lib");
/* Do we need any of these for elf?
   __DYNAMIC = 0;    */
MEMORY
{
    FLASH (rxai!w) : ORIGIN = 0x80000000, LENGTH = 256K
    CPUSRAM (wxa!ri) : ORIGIN = 0x00000004, LENGTH = 0x7FFC
    USERPAGE : ORIGIN = 0x80800000, LENGTH = 512
    FACTORYPAGE : ORIGIN = 0x80800200, LENGTH = 512
}
SECTIONS
{
  /* Read-only sections, merged into text segment: */
  PROVIDE (__executable_start = 0x80000000); . = 0x80000000;
  .interp         : { *(.interp) } >FLASH AT>FLASH
  .reset : {  *(.reset) } >FLASH AT>FLASH
  .hash           : { *(.hash) } >FLASH AT>FLASH
  .dynsym         : { *(.dynsym) } >FLASH AT>FLASH
  .dynstr         : { *(.dynstr) } >FLASH AT>FLASH
  .gnu.version    : { *(.gnu.version) } >FLASH AT>FLASH
  .gnu.version_d  : { *(.gnu.version_d) } >FLASH AT>FLASH
  .gnu.version_r  : { *(.gnu.version_r) } >FLASH AT>FLASH
  .rel.init       : { *(.rel.init) } >FLASH AT>FLASH
  .rela.init      : { *(.rela.init) } >FLASH AT>FLASH
  .rel.text       : { *(.rel.text .rel.text.* .rel.gnu.linkonce.t.*) } >FLASH AT>FLASH
  .rela.text      : { *(.rela.text .rela.text.* .rela.gnu.linkonce.t.*) } >FLASH AT>FLASH
  .rel.fini       : { *(.rel.fini) } >FLASH AT>FLASH
  .rela.fini      : { *(.rela.fini) } >FLASH AT>FLASH
  .rel.rodata     : { *(.rel.rodata .rel.rodata.* .rel.gnu.linkonce.r.*) } >FLASH AT>FLASH
  .rela.rodata    : { *(.rela.rodata .rela.rodata.* .rela.gnu.linkonce.r.*) } >FLASH AT>FLASH
  .rel.data.rel.ro   : { *(.rel.data.rel.ro*) } >FLASH AT>FLASH
  .rela.data.rel.ro   : { *(.rel.data.rel.ro*) } >FLASH AT>FLASH
  .rel.data       : { *(.rel.data .rel.data.* .rel.gnu.linkonce.d.*) } >FLASH AT>FLASH
  .rela.data      : { *(.rela.data .rela.data.* .rela.gnu.linkonce.d.*) } >FLASH AT>FLASH
  .rel.tdata      : { *(.rel.tdata .rel.tdata.* .rel.gnu.linkonce.td.*) } >FLASH AT>FLASH
  .rela.tdata     : { *(.rela.tdata .rela.tdata.* .rela.gnu.linkonce.td.*) } >FLASH AT>FLASH
  .rel.tbss   : { *(.rel.tbss .rel.tbss.* .rel.gnu.linkonce.tb.*) } >FLASH AT>FLASH
  .rela.tbss      : { *(.rela.tbss .rela.tbss.* .rela.gnu.linkonce.tb.*) } >FLASH AT>FLASH
  .rel.ctors      : { *(.rel.ctors) } >FLASH AT>FLASH
  .rela.ctors     : { *(.rela.ctors) } >FLASH AT>FLASH
  .rel.dtors      : { *(.rel.dtors) } >FLASH AT>FLASH
  .rela.dtors     : { *(.rela.dtors) } >FLASH AT>FLASH
  .rel.got        : { *(.rel.got) } >FLASH AT>FLASH
  .rela.got       : { *(.rela.got) } >FLASH AT>FLASH
  .rel.bss        : { *(.rel.bss .rel.bss.* .rel.gnu.linkonce.b.*) } >FLASH AT>FLASH
  .rela.bss       : { *(.rela.bss .rela.bss.* .rela.gnu.linkonce.b.*) } >FLASH AT>FLASH
  .rel.plt        : { *(.rel.plt) } >FLASH AT>FLASH
  .rela.plt       : { *(.rela.plt) } >FLASH AT>FLASH
  .init           :
  {
    KEEP (*(.init))
  } >FLASH AT>FLASH =0xd703d703
  .plt            : { *(.plt) } >FLASH AT>FLASH
  .text           :
  {
    *(.text .stub .text.* .gnu.linkonce.t.*)
    KEEP (*(.text.*personality*))
    /* .gnu.warning sections are handled specially by elf32.em.  */
    *(.gnu.warning)
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
  } >FLASH AT>FLASH =0xd703d703
  .fini           :
  {
    KEEP (*(.fini))
  } >FLASH AT>FLASH =0xd703d703
  PROVIDE (__etext = .);
  PROVIDE (_etext = .);
  PROVIDE (etext = .);
  .rodata         : { *(.rodata .rodata.* .gnu.linkonce.r.*) } >FLASH AT>FLASH
  .rodata1        : { *(.rodata1) } >FLASH AT>FLASH
  .eh_frame_hdr : { *(.eh_frame_hdr) } >FLASH AT>FLASH
  .eh_frame       : ONLY_IF_RO { KEEP (*(.eh_frame)) } >FLASH AT>FLASH
  .gcc_except_table   : ONLY_IF_RO { KEEP (*(.gcc_except_table)) *(.gcc_except_table.*) } >FLASH AT>FLASH
  .dalign   : { . = ALIGN(8); PROVIDE(_data_lma = .); } >FLASH AT>FLASH
  PROVIDE (_data = ORIGIN(CPUSRAM));
  . = ORIGIN(CPUSRAM);
  /* Exception handling  */
  .eh_frame       : ONLY_IF_RW { KEEP (*(.eh_frame)) } >CPUSRAM AT>FLASH
  .gcc_except_table   : ONLY_IF_RW { KEEP (*(.gcc_except_table)) *(.gcc_except_table.*) } >CPUSRAM AT>FLASH
  /* Thread Local Storage sections  */
  .tdata      : { *(.tdata .tdata.* .gnu.linkonce.td.*) } >CPUSRAM AT>FLASH
  .tbss       : { *(.tbss .tbss.* .gnu.linkonce.tb.*) *(.tcommon) } >CPUSRAM
  /* Ensure the __preinit_array_start label is properly aligned.  We
     could instead move the label definition inside the section, but
     the linker would then create the section even if it turns out to
     be empty, which isn't pretty.  */
  PROVIDE (__preinit_array_start = ALIGN(32 / 8));
  .preinit_array     : { KEEP (*(.preinit_array)) } >CPUSRAM AT>FLASH
  PROVIDE (__preinit_array_end = .);
  PROVIDE (__init_array_start = .);
  .init_array     : { KEEP (*(.init_array)) } >CPUSRAM AT>FLASH
  PROVIDE (__init_array_end = .);
  PROVIDE (__fini_array_start = .);
  .fini_array     : { KEEP (*(.fini_array)) } >CPUSRAM AT>FLASH
  PROVIDE (__fini_array_end = .);
  .ctors          :
  {
    /* gcc uses crtbegin.o to find the start of
       the constructors, so we make sure it is
       first.  Because this is a wildcard, it
       doesn't matter if the user does not
       actually link against crtbegin.o; the
       linker won't look for a file to match a
       wildcard.  The wildcard also means that it
       doesn't matter which directory crtbegin.o
       is in.  */
    KEEP (*crtbegin*.o(.ctors))
    /* We don't want to include the .ctor section from
       from the crtend.o file until after the sorted ctors.
       The .ctor section from the crtend file contains the
       end of ctors marker and it must be last */
    KEEP (*(EXCLUDE_FILE (*crtend*.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
  } >CPUSRAM AT>FLASH
  .dtors          :
  {
    KEEP (*crtbegin*.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend*.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
  } >CPUSRAM AT>FLASH
  .jcr            : { KEEP (*(.jcr)) } >CPUSRAM AT>FLASH
  .data.rel.ro : { *(.data.rel.ro.local) *(.data.rel.ro*) } >CPUSRAM AT>FLASH
  .dynamic        : { *(.dynamic) } >CPUSRAM AT>FLASH
  .got            : { *(.got.plt) *(.got) } >CPUSRAM AT>FLASH
  .data           :
  {
    *(.data .data.* .gnu.linkonce.d.*)
    KEEP (*(.gnu.linkonce.d.*personality*))
    SORT(CONSTRUCTORS)
  } >CPUSRAM AT>FLASH
  .data1          : { *(.data1) } >CPUSRAM AT>FLASH
  .balign   : { . = ALIGN(8); _edata = .; } >CPUSRAM AT>FLASH
  _edata = .;
  PROVIDE (edata = .);
  __bss_start = .;
  .bss            :
  {
   *(.dynbss)
   *(.bss .bss.* .gnu.linkonce.b.*)
   *(COMMON)
   /* Align here to ensure that the .bss section occupies space up to
      _end.  Align after .bss to ensure correct alignment even if the
      .bss section disappears because there are no input sections.  */
   . = ALIGN(8);
  } >CPUSRAM
  . = ALIGN(8);
  _end = .;
  PROVIDE (end = .);
  __heap_start__ = ALIGN(8);
  . = ORIGIN(CPUSRAM) + LENGTH(CPUSRAM) - _stack_size;
  __heap_end__ = .;
  /* Stabs debugging sections.  */
  .stab          0 : { *(.stab) }
  .stabstr       0 : { *(.stabstr) }
  .stab.excl     0 : { *(.stab.excl) }
  .stab.exclstr  0 : { *(.stab.exclstr) }
  .stab.index    0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment       0 : { *(.comment) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
  .stack         ORIGIN(CPUSRAM) + LENGTH(CPUSRAM) - _stack_size :
  {
    _stack = .;
    *(.stack)
    . = _stack_size;
    _estack = .;
  } >CPUSRAM
  .userpage :  { *(.userpage .userpage.*)  } >USERPAGE AT>USERPAGE
  .factorypage :  { *(.factorypage .factorypage.*)  } >FACTORYPAGE AT>FACTORYPAGE
  /DISCARD/ : { *(.note.GNU-stack) }
}
