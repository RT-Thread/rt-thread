OUTPUT_ARCH( "riscv" )

ENTRY( _start )

MEMORY
{
    /* Run in FLASH */
    flash (rxai!w) : ORIGIN = 0x08000000, LENGTH = 4096k
    ram   (wxa!ri) : ORIGIN = 0x20000000, LENGTH = 288K

    /* Run in RAM */
/*    flash (rxai!w) : ORIGIN = 0x20000000, LENGTH = 32k
    ram   (wxa!ri) : ORIGIN = 0x20008000, LENGTH = 256K
*/
}


SECTIONS
{
  __stack_size = DEFINED(__stack_size) ? __stack_size : 4K;


  .init           :
  {
    KEEP (*(SORT_NONE(.init)))
  } >flash AT>flash

  .ilalign         :
  {
    . = ALIGN(4);
    PROVIDE( _ilm_lma = . );
  } >flash AT>flash

  .ialign         :
  {
    PROVIDE( _ilm = . );
  } >flash AT>flash

  _sicode = LOADADDR(.code_to_sram);

  .code_to_sram :
  {
    . = ALIGN(4);
    _scode = .;

    *trap_gcc.o* (.text*)
    *port.o* (.text.eclic_mtip_handler)
    *lib_a-memcpy.o* (.text*)
    *wrapper_os.o* (.text.sys_memcpy*)
    *inet_chksum.o* (.text.lwip_standard_chksum)
    /**macsw/modules/ke/ke_event.o* (.rodata.ke_evt_hdlr*)
    *rxl_cntrl.o* (.text.rxl_upload_evt)*/
    *txl_agg.o* (.text.txl_agg_push_mpdu  .text.txl_agg_finish)
    *txl_he.o* (.text.txl_he_tb_prot_trigger .text.txl_he_trigger_push)
    *rxl_hwdesc.o* (.text.rxl_immediate_frame_get  .text.rxl_rxcntrl_frame)


    *txl_agg.o* (.text.* .rodata.*)
    *txl_he.o* (.text.* .rodata.*)
    *rxl_hwdesc.o* (.text.* .rodata.*)

    *drv_uart.o* (.text.USART0_IRQHandler .text.GD32_UART_IRQHandler) /* choose UART on condition */
    *gd32vw55x_usart.o* (.text.usart_interrupt_flag_get .text.usart_interrupt_flag_clear  .text.usart_flag_get .text.usart_flag_clear)
    *gd32vw55x_usart.o* (.text.usart_data_receive .text.usart_data_transmit)
    *gd32vw55x_usart.o* (.text.usart_interrupt_enable .text.usart_interrupt_disable)
    *dev_serial.o*  (.text.rt_hw_serial_isr)
    *save-restore.o* (.text*)


    . = ALIGN(4);
    _ecode = .;
  } >ram AT>flash



  .text           :
  {
    *(.rodata .rodata.*)
    *(.text.unlikely .text.unlikely.*)
    *(.text.startup .text.startup.*)
    *(.text .text.*)
    *(.gnu.linkonce.t.*)

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

    /* section information for modules */
    . = ALIGN(4);
    __rtmsymtab_start = .;
    KEEP(*(RTMSymTab))
    __rtmsymtab_end = .;
  } >flash AT>flash

  .fini           :
  {
    KEEP (*(SORT_NONE(.fini)))
  } >flash AT>flash

  . = ALIGN(4);

  PROVIDE (__etext = .);
  PROVIDE (_etext = .);/*0x80022c8*/
  PROVIDE (etext = .);/*0x80022c8*/
  PROVIDE( _eilm = . );

  .preinit_array  :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >flash AT>flash

  .init_array     :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
    KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >flash AT>flash

  .fini_array     :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
    KEEP (*(.fini_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >flash AT>flash

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
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    /* We don't want to include the .ctor section from
       the crtend.o file until after the sorted ctors.
       The .ctor section from the crtend file contains the
       end of ctors marker and it must be last */
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
  } >flash AT>flash

  .dtors          :
  {
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
  } >flash AT>flash

    . = ALIGN(4);
    PROVIDE( _eilm = . );

  .lalign         :
  {
    . = ALIGN(4);
    PROVIDE( _data_lma = . );
  } >flash AT>flash

  .dalign         :
  {
    . = ALIGN(4);
  } >ram AT>flash


  .data          :
  {
     PROVIDE( _data = . );
    *(.rdata)

    *(.gnu.linkonce.r.*)
    *(.data .data.*)
    *(.gnu.linkonce.d.*)
    . = ALIGN(8);
    PROVIDE( __global_pointer$ = . + 0x800);
    *(.sdata .sdata.*)
    *(.gnu.linkonce.s.*)
    . = ALIGN(8);
    *(.srodata.cst16)
    *(.srodata.cst8)
    *(.srodata.cst4)
    *(.srodata.cst2)
    *(.srodata .srodata.*)
  } >ram AT>flash

  . = ALIGN(4);
  PROVIDE( _edata = . );
  PROVIDE( edata = . );

  PROVIDE( _fbss = . ); /*0X200052A0  0X200002A0*/
  PROVIDE( __bss_start = . );
  .bss            :
  {
    *(.sbss*)
    *(.gnu.linkonce.sb.*)
    *(.bss .bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(4);
  } >ram AT>ram

  . = ALIGN(8);
  PROVIDE( _end = . ); /*0X2000,0340*/
  PROVIDE( end = . );

  .stack ORIGIN(ram) + LENGTH(ram) - __stack_size :
  {
    PROVIDE( _heap_end = . );
    . = __stack_size;
    PROVIDE( _sp = . );
    PROVIDE( __rt_rvstack = .);
  } >ram AT>ram
}
