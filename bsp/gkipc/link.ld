OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
    . = (DEFINED(PROGRAM_LOAD_ADDRESS)) ? (PROGRAM_LOAD_ADDRESS) : 0xc0200000;
	
	/*
    ************************************************************
    ** NOCACHE_BUFFER for HW & SW
    ************************************************************
    */
    . = ALIGN(4);
    .nocache_buffer :
    {
        PROVIDE(__nocache_buffer_start__ = .);
        *(.nocache_buffer*)
        KEEP(*(.nocache_buffer))
		. = ALIGN(1M);
        PROVIDE(__nocache_buffer_end__ = .);
    }
	

    . = 0xC0300000;
    __text_start = .;
    .text :
    {
    	_stext = .;
        KEEP(*(.ARM1176START))
        KEEP(*(.ARM1176INIT))
        KEEP(*(.ARM1176IVT))
        *(.init)
        *(.text*)
        *(.stub)
        *(.gnu.warning)
        *(.gnu.linkonce.t*)
        
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

        . = ALIGN(4);
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;
        . = ALIGN(4);

        /* section information for modules */
        . = ALIGN(4);
        __rtmsymtab_start = .;
        KEEP(*(RTMSymTab))
        __rtmsymtab_end = .;
        _etext = .;
    }
    PROVIDE(_etext = .);
	__text_end = .;
	
    /*
    ************************************************************
    ** add ro data sections
    ************************************************************
    */
    . = ALIGN(4);
    __rodata_start = .;
    .rodata :
    {
        *(.rodata*)
        . = ALIGN(4);
        *(.gnu.linkonce.r*)
        *(.eh_frame)
    }
    PROVIDE(_end_readonly = .);
    
    /*
    ************************************************************
    ** add rw data sections
    ************************************************************
    */
    .data :
    {
        *(.data*)
        . = ALIGN(4);
        *(.gnu.linkonce.d*) CONSTRUCTORS
    }
    
    /*
    ************************************************************
    ** .bss section which is used for uninitialized data
    ************************************************************
    */
    . = ALIGN(1024);
    .bss :
    {
        PROVIDE(__bss_start__ = .);
        *(.bss*)
        *(COMMON)
        PROVIDE(__bss_end__ = .);
    }

    /*
    ************************************************************
    ** .ctors .dtors are used for c++ constructors/destructors
    ************************************************************
    */
    .ctors :
    {
        PROVIDE(__ctors_start__ = .);
        KEEP(*(SORT(.ctors.*)))
        KEEP(*(.ctors))
        PROVIDE(__ctors_end__ = .);
    }
    .dtors :
    {
        PROVIDE(__dtors_start__ = .);
        KEEP(*(SORT(.dtors.*)) )
        KEEP(*(.dtors) )
        PROVIDE(__dtors_end__ = .);
    }

    /*
    ************************************************************
    ** ARM extensions
    ************************************************************
    */
    .ARM.attributes :
    {
        *(.ARM.attributes)
        *(.ARM.extab*)
        PROVIDE(__exidx_start = .);
        *(.ARM.exidx*)
        PROVIDE(__exidx_end = .);
    }

    /*
    ************************************************************
    ** _end marks the end of code
    ************************************************************
    */
    . = ALIGN(4);
    PROVIDE(_end = .);
    PROVIDE(end = .);

    /*
    ************************************************************
    ** The ".stack" section is used for user stacks, we use the
    ** memory sizes given by the make symbol PROGRAM_STACK_BYTES.
    ** The variables "__stack_end__" and "__stack_start__"
    ** mark the stack buffer to be used by libc functions.
    ************************************************************
    */
    . = ALIGN(8);
    .stack :
    {
        PROVIDE(__stack_end__ = .);
        . += PROGRAM_STACK_BYTES;
        PROVIDE(__stack_start__ = .);
    }

    /*
    ************************************************************
    ** The ".heap" section is used for dynamic data, we use the
    ** memory sizes given by the make symbols PROGRAM_HEAP_BYTES.
    ** The variables "__heap_start__" and "__heap_end__"
    ** mark the heap memory to be used by libc "malloc()"
    ** functions.
    ************************************************************
    */
    . = ALIGN(8);
    .heap :
    {
        PROVIDE(__heap_start__ = .);
        . += PROGRAM_HEAP_BYTES;
        . = ALIGN(1M);
        PROVIDE(__heap_end__ = .);
    }

    /*
    ************************************************************
    ** Stabs debugging sections.
    ************************************************************
    */
    .stab          0 : { *(.stab)          }
    .stabstr       0 : { *(.stabstr)       }
    .stab.excl     0 : { *(.stab.excl)     }
    .stab.exclstr  0 : { *(.stab.exclstr)  }
    .stab.index    0 : { *(.stab.index)    }
    .stab.indexstr 0 : { *(.stab.indexstr) }
    .comment       0 : { *(.comment)       }

    /*
    ************************************************************
    ** DWARF 1
    ************************************************************
    */
    .debug 0 : { *(.debug) }
    .line  0 : { *(.line)  }

    /*
    ************************************************************
    ** GNU DWARF 1 extensions
    ************************************************************
    */
    .debug_srcinfo 0 : { *(.debug_srcinfo) }
    .debug_sfnames 0 : { *(.debug_sfnames) }

    /*
    ************************************************************
    ** DWARF 1.1 and DWARF 2
    ************************************************************
    */
    .debug_aranges  0 : { *(.debug_aranges)  }
    .debug_pubnames 0 : { *(.debug_pubnames) }

    /*
    ************************************************************
    ** DWARF 2
    ************************************************************
    */
    .debug_info    0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev  0 : { *(.debug_abbrev)                  }
    .debug_line    0 : { *(.debug_line)                    }
    .debug_frame   0 : { *(.debug_frame)                   }
    .debug_str     0 : { *(.debug_str)                     }
    .debug_loc     0 : { *(.debug_loc)                     }
    .debug_macinfo 0 : { *(.debug_macinfo)                 }
    .debug_ranges  0 : { *(.debug_ranges)                  }

    /*
    ************************************************************
    ** SGI/MIPS DWARF 2 extensions
    ************************************************************
    */
    .debug_weaknames 0 : { *(.debug_weaknames) }
    .debug_funcnames 0 : { *(.debug_funcnames) }
    .debug_typenames 0 : { *(.debug_typenames) }
    .debug_varnames  0 : { *(.debug_varnames)  }
}
