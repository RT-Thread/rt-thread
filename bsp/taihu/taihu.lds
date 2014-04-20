OUTPUT_ARCH(powerpc)

/* Do we need any of these for elf?
   __DYNAMIC = 0;    */
SECTIONS
{
  .resetvec 0xFFFFFFFC :
  {
    *(.resetvec)
  } = 0xffff

  /* Read-only sections, merged into text segment: */
  . = + SIZEOF_HEADERS;
  .interp : { *(.interp) }
  .hash          : { *(.hash)           }
  .dynsym        : { *(.dynsym)         }
  .dynstr        : { *(.dynstr)         }
  .rel.text      : { *(.rel.text)       }
  .rela.text     : { *(.rela.text)      }
  .rel.data      : { *(.rel.data)       }
  .rela.data     : { *(.rela.data)      }
  .rel.rodata    : { *(.rel.rodata)     }
  .rela.rodata   : { *(.rela.rodata)    }
  .rel.got       : { *(.rel.got)        }
  .rela.got      : { *(.rela.got)       }
  .rel.ctors     : { *(.rel.ctors)      }
  .rela.ctors    : { *(.rela.ctors)     }
  .rel.dtors     : { *(.rel.dtors)      }
  .rela.dtors    : { *(.rela.dtors)     }
  .rel.bss       : { *(.rel.bss)        }
  .rela.bss      : { *(.rela.bss)       }
  .rel.plt       : { *(.rel.plt)        }
  .rela.plt      : { *(.rela.plt)       }
  /* .init          : { *(.init)           } */
  .plt : { *(.plt) }

  .text      :
  {
    KEEP(build/kernel/libcpu/ppc/ppc405/start_gcc.o (.text))

    *(.text)
    *(.fixup)
    *(.got1)
  }
  _etext = .;
  PROVIDE (etext = .);
  .rodata    :
  {
    *(.eh_frame)
    *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
    /* section information for finsh shell */
    . = ALIGN(4);
    __fsymtab_start = .;
    KEEP(*(FSymTab))
    __fsymtab_end = .;
    . = ALIGN(4);
    __vsymtab_start = .;
    KEEP(*(VSymTab))
    __vsymtab_end = .;
  }
  .fini      : { *(.fini)    } =0
  .ctors     : { *(.ctors)   }
  .dtors     : { *(.dtors)   }

  /* Read-write section, merged into data segment: */
  . = (. + 0x00FF) & 0xFFFFFF00;
  _erotext = .;
  PROVIDE (erotext = .);
  .reloc   :
  {
    *(.got)
    _GOT2_TABLE_ = .;
    *(.got2)
    _FIXUP_TABLE_ = .;
    *(.fixup)
  }
  __got2_entries = (_FIXUP_TABLE_ - _GOT2_TABLE_) >>2;
  __fixup_entries = (. - _FIXUP_TABLE_)>>2;

  .data    :
  {
    *(.data)
    *(.data1)
    *(.sdata)
    *(.sdata2)
    *(.dynamic)
    CONSTRUCTORS
  }
  _edata  =  .;
  PROVIDE (edata = .);

  . = .;
  __start___ex_table = .;
  __ex_table : { *(__ex_table) }
  __stop___ex_table = .;

  . = ALIGN(256);
  __init_begin = .;
  .text.init : { *(.text.init) }
  .data.init : { *(.data.init) }
  . = ALIGN(256);
  __init_end = .;

  __bss_start = .;
  .bss (NOLOAD)       :
  {
   *(.sbss) *(.scommon)
   *(.dynbss)
   *(.bss)
   *(COMMON)
   . = ALIGN(4);
  }
  __bss_end = .;

  . = ALIGN(256);

  PROVIDE(__stack_bottom = .);
  . += 0x100000; /* 1MB */
  PROVIDE(__stack_top = .);

  . = ALIGN(256);
  PROVIDE (__heap_start = .);
  . += 0x500000; /* 5MB */
  PROVIDE(__heap_end = .);

  _end = . ;
  PROVIDE (end = .);
}
