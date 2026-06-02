/* Automatically generated file; DO NOT EDIT */
/* Espressif IoT Development Framework Linker Script */
/* Generated from: /home/wcx/rt-thread/bsp/ESP32_C3/packages/ESP-IDF-latest/components/esp_system/ld/esp32c3/sections.ld.in */

/*
 * SPDX-FileCopyrightText: 2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Default entry point */
ENTRY(call_start_cpu0);

SECTIONS
{
  /**
   * RTC fast memory holds RTC wake stub code,
   * including from any source file named rtc_wake_stub*.c
   */
  .rtc.text :
  {
    . = ALIGN(4);
    _rtc_fast_start = ABSOLUTE(.);

    *(.rtc.literal .rtc.text .rtc.text.*)

    *rtc_wake_stub*.*(.literal .text .literal.* .text.*)
    *(.rtc_text_end_test)

    /* 16B padding for possible CPU prefetch and 4B alignment for PMS split lines */
    . += _esp_memprot_prefetch_pad_size;
    . = ALIGN(4);

    _rtc_text_end = ABSOLUTE(.);
  } > rtc_iram_seg

  /**
   * This section located in RTC FAST Memory area.
   * It holds data marked with RTC_FAST_ATTR attribute.
   * See the file "esp_attr.h" for more information.
   */
  .rtc.force_fast :
  {
    . = ALIGN(4);
    _rtc_force_fast_start = ABSOLUTE(.);

    _coredump_rtc_fast_start = ABSOLUTE(.);
    *(.rtc.fast.coredump .rtc.fast.coredump.*)
    _coredump_rtc_fast_end = ABSOLUTE(.);

    *(.rtc.force_fast .rtc.force_fast.*)
    . = ALIGN(4) ;
    _rtc_force_fast_end = ABSOLUTE(.);
  } > rtc_data_seg

  /**
   * RTC data section holds RTC wake stub
   * data/rodata, including from any source file
   * named rtc_wake_stub*.c and the data marked with
   * RTC_DATA_ATTR, RTC_RODATA_ATTR attributes.
   */
  .rtc.data :
  {
    _rtc_data_start = ABSOLUTE(.);

    _coredump_rtc_start = ABSOLUTE(.);
    *(.rtc.coredump .rtc.coredump.*)
    _coredump_rtc_end = ABSOLUTE(.);
    *(.rtc.data .rtc.data.*)
    *(.rtc.rodata .rtc.rodata.*)

    *rtc_wake_stub*.*(.data .rodata .data.* .rodata.* .bss .bss.*)
    _rtc_data_end = ABSOLUTE(.);
  } > rtc_data_location

  /* RTC bss, from any source file named rtc_wake_stub*.c */
  .rtc.bss (NOLOAD) :
  {
    _rtc_bss_start = ABSOLUTE(.);
    *rtc_wake_stub*.*(.bss .bss.*)
    *rtc_wake_stub*.*(COMMON)

    *(.rtc.bss)

    _rtc_bss_end = ABSOLUTE(.);
  } > rtc_data_location

  /**
   * This section holds data that should not be initialized at power up
   * and will be retained during deep sleep.
   * User data marked with RTC_NOINIT_ATTR will be placed
   * into this section. See the file "esp_attr.h" for more information.
   */
  .rtc_noinit (NOLOAD):
  {
    . = ALIGN(4);
    _rtc_noinit_start = ABSOLUTE(.);
    *(.rtc_noinit .rtc_noinit.*)
    . = ALIGN(4) ;
    _rtc_noinit_end = ABSOLUTE(.);
  } > rtc_data_location

  /**
   * This section located in RTC SLOW Memory area.
   * It holds data marked with RTC_SLOW_ATTR attribute.
   * See the file "esp_attr.h" for more information.
   */
  .rtc.force_slow :
  {
    . = ALIGN(4);
    _rtc_force_slow_start = ABSOLUTE(.);
    *(.rtc.force_slow .rtc.force_slow.*)
    . = ALIGN(4) ;
    _rtc_force_slow_end = ABSOLUTE(.);
  } > rtc_slow_seg

  /* Get size of rtc slow data based on rtc_data_location alias */
  _rtc_slow_length = (ORIGIN(rtc_slow_seg) == ORIGIN(rtc_data_location))
                        ? (_rtc_force_slow_end - _rtc_data_start)
                        : (_rtc_force_slow_end - _rtc_force_slow_start);

  _rtc_fast_length = (ORIGIN(rtc_slow_seg) == ORIGIN(rtc_data_location))
                        ? (_rtc_force_fast_end - _rtc_fast_start)
                        : (_rtc_noinit_end - _rtc_fast_start);

  ASSERT((_rtc_slow_length <= LENGTH(rtc_slow_seg)),
          "RTC_SLOW segment data does not fit.")

  ASSERT((_rtc_fast_length <= LENGTH(rtc_data_seg)),
          "RTC_FAST segment data does not fit.")

  .iram0.text :
  {
    _iram_start = ABSOLUTE(.);
    /* Vectors go to start of IRAM */
    ASSERT(ABSOLUTE(.) % 0x100 == 0, "vector address must be 256 byte aligned");
    KEEP(*(.exception_vectors.text));
    . = ALIGN(4);

    _invalid_pc_placeholder = ABSOLUTE(.);

    /* Code marked as running out of IRAM */
    _iram_text_start = ABSOLUTE(.);

    *(.iram1 .iram1.*)
    *app_trace/app_trace.*(.literal .literal.* .text .text.*)
    *app_trace/app_trace_util.*(.literal .literal.* .text .text.*)
    *app_trace/port_uart.*(.literal .literal.* .text .text.*)
    *esp_event/default_event_loop.*(.literal.esp_event_isr_post .text.esp_event_isr_post)
    *esp_event/esp_event.*(.literal.esp_event_isr_post_to .text.esp_event_isr_post_to)
    *esp_hw_support/cpu.*(.literal.esp_cpu_compare_and_set .text.esp_cpu_compare_and_set)
    *esp_hw_support/cpu.*(.literal.esp_cpu_reset .text.esp_cpu_reset)
    *esp_hw_support/cpu.*(.literal.esp_cpu_stall .text.esp_cpu_stall)
    *esp_hw_support/cpu.*(.literal.esp_cpu_unstall .text.esp_cpu_unstall)
    *esp_hw_support/cpu.*(.literal.esp_cpu_wait_for_intr .text.esp_cpu_wait_for_intr)
    *esp_hw_support/esp_memory_utils.*(.literal .literal.* .text .text.*)
    *esp_hw_support/rtc_clk.*(.literal .literal.* .text .text.*)
    *esp_hw_support/rtc_init.*(.literal.rtc_vddsdio_set_config .text.rtc_vddsdio_set_config)
    *esp_hw_support/rtc_pm.*(.literal .literal.* .text .text.*)
    *esp_hw_support/rtc_sleep.*(.literal .literal.* .text .text.*)
    *esp_hw_support/rtc_time.*(.literal .literal.* .text .text.*)
    *esp_hw_support/systimer.*(.literal .literal.* .text .text.*)
    *esp_ringbuf/(.literal .literal.* .text .text.*)
    *esp_rom/esp_rom_regi2c.*(.literal .literal.* .text .text.*)
    *esp_rom/esp_rom_spiflash.*(.literal .literal.* .text .text.*)
    *esp_rom/esp_rom_systimer.*(.literal .literal.* .text .text.*)
    *esp_system/esp_err.*(.literal .literal.* .text .text.*)
    *esp_system/esp_system.*(.literal.esp_system_abort .text.esp_system_abort)
    *esp_system/ubsan.*(.literal .literal.* .text .text.*)
    *gcc/_divsf3.*(.literal .literal.* .text .text.*)
    *gcc/lib2funcs.*(.literal .literal.* .text .text.*)
    *gcc/save-restore.*(.literal .literal.* .text .text.*)
    *gcov/(.literal .literal.* .text .text.*)
    *hal/cache_hal.*(.literal .literal.* .text .text.*)
    *hal/i2c_hal_iram.*(.literal .literal.* .text .text.*)
    *hal/ledc_hal_iram.*(.literal .literal.* .text .text.*)
    *hal/mmu_hal.*(.literal .literal.* .text .text.*)
    *hal/spi_flash_encrypt_hal_iram.*(.literal .literal.* .text .text.*)
    *hal/spi_flash_hal_gpspi.*(.literal .literal.* .text .text.*)
    *hal/spi_flash_hal_iram.*(.literal .literal.* .text .text.*)
    *hal/spi_hal_iram.*(.literal .literal.* .text .text.*)
    *hal/spi_slave_hal_iram.*(.literal .literal.* .text .text.*)
    *hal/systimer_hal.*(.literal .literal.* .text .text.*)
    *hal/wdt_hal_iram.*(.literal .literal.* .text .text.*)
    *heap/multi_heap.*(.literal .literal.* .text .text.*)
    *heap/tlsf.*(.literal .literal.* .text .text.*)
    *log/log.*(.literal.esp_log_write .text.esp_log_write)
    *log/log_freertos.*(.literal.esp_log_early_timestamp .text.esp_log_early_timestamp)
    *log/log_freertos.*(.literal.esp_log_impl_lock .text.esp_log_impl_lock)
    *log/log_freertos.*(.literal.esp_log_impl_lock_timeout .text.esp_log_impl_lock_timeout)
    *log/log_freertos.*(.literal.esp_log_impl_unlock .text.esp_log_impl_unlock)
    *log/log_freertos.*(.literal.esp_log_timestamp .text.esp_log_timestamp)
    *libnet80211.a:(.wifi0iram .wifi0iram.*)
    *libnet80211.a:(.wifirxiram .wifirxiram.*)
    *libnet80211.a:(.wifislprxiram .wifislprxiram.*)
    *newlib/abort.*(.literal .literal.* .text .text.*)
    *newlib/assert.*(.literal .literal.* .text .text.*)
    *newlib/heap.*(.literal .literal.* .text .text.*)
    *newlib/stdatomic.*(.literal .literal.* .text .text.*)
    *libpp.a:(.wifi0iram .wifi0iram.*)
    *libpp.a:(.wifiorslpiram .wifiorslpiram.*)
    *libpp.a:(.wifirxiram .wifirxiram.*)
    *libpp.a:(.wifislprxiram .wifislprxiram.*)
    *riscv/interrupt.*(.literal .literal.* .text .text.*)
    *riscv/vectors.*(.literal .literal.* .text .text.*)
    *librtc.a:(.literal .literal.* .text .text.*)
    *soc/lldesc.*(.literal .literal.* .text .text.*)
    *spi_flash/flash_brownout_hook.*(.literal .literal.* .text .text.*)
    *spi_flash/memspi_host_driver.*(.literal .literal.* .text .text.*)
    *spi_flash/spi_flash_chip_boya.*(.literal .literal.* .text .text.*)
    *spi_flash/spi_flash_chip_gd.*(.literal .literal.* .text .text.*)
    *spi_flash/spi_flash_chip_generic.*(.literal .literal.* .text .text.*)
    *spi_flash/spi_flash_chip_issi.*(.literal .literal.* .text .text.*)
    *spi_flash/spi_flash_chip_mxic.*(.literal .literal.* .text .text.*)
    *spi_flash/spi_flash_chip_th.*(.literal .literal.* .text .text.*)
    *spi_flash/spi_flash_chip_winbond.*(.literal .literal.* .text .text.*)
    *kernel/src/*.*(.literal .literal.* .text .text.*)
    *kernel/libcpu/risc-v/common/context_gcc.*(.literal .literal.* .text .text.*)
  } > iram0_0_seg

  /**
   * This section is required to skip .iram0.text area because iram0_0_seg and
   * dram0_0_seg reflect the same address space on different buses.
   */
  .dram0.dummy (NOLOAD):
  {
    . = ORIGIN(dram0_0_seg) + _iram_end - _iram_start;
  } > dram0_0_seg

  .dram0.data :
  {
    _data_start = ABSOLUTE(.);
    *(.gnu.linkonce.d.*)
    *(.data1)
    __global_pointer$ = . + 0x800;
    *(.sdata)
    *(.sdata.*)
    *(.gnu.linkonce.s.*)
    *(.gnu.linkonce.s2.*)
    *(.jcr)

    *(EXCLUDE_FILE(*bt/* *libbtdm_app.a *libnimble.a) .data EXCLUDE_FILE(*bt/* *libbtdm_app.a *libnimble.a) .data.*)
    *(.dram1 .dram1.*)
    _coredump_dram_start = ABSOLUTE(.);
    *(.dram2.coredump .dram2.coredump.*)
    _coredump_dram_end = ABSOLUTE(.);
    *app_trace/app_trace.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *app_trace/app_trace_util.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *app_trace/port_uart.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    _btdm_data_start = ABSOLUTE(.);
    *libbtdm_app.a:(.data .data.*)
    . = ALIGN(4);
    _btdm_data_end = ABSOLUTE(.);
    _bt_data_start = ABSOLUTE(.);
    *bt/*(.data .data.*)
    . = ALIGN(4);
    _bt_data_end = ABSOLUTE(.);
    *esp_hw_support/esp_memory_utils.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *esp_hw_support/rtc_clk.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *esp_hw_support/systimer.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *esp_rom/esp_rom_regi2c.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *esp_rom/esp_rom_spiflash.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *esp_rom/esp_rom_systimer.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *esp_system/esp_err.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *esp_system/ubsan.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *gcc/_divsf3.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *gcc/save-restore.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *gcov/(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *hal/cache_hal.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *hal/i2c_hal_iram.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *hal/ledc_hal_iram.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *hal/mmu_hal.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *hal/spi_flash_encrypt_hal_iram.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *hal/spi_flash_hal_gpspi.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *hal/spi_flash_hal_iram.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *hal/spi_hal_iram.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *hal/spi_slave_hal_iram.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *hal/systimer_hal.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *hal/wdt_hal_iram.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *heap/multi_heap.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *heap/tlsf.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *newlib/abort.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *newlib/assert.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *newlib/heap.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *newlib/stdatomic.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    _nimble_data_start = ABSOLUTE(.);
    *libnimble.a:(.data .data.*)
    . = ALIGN(4);
    _nimble_data_end = ABSOLUTE(.);
    *libphy.a:(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *soc/lldesc.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *spi_flash/flash_brownout_hook.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *spi_flash/memspi_host_driver.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *spi_flash/spi_flash_chip_boya.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *spi_flash/spi_flash_chip_gd.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *spi_flash/spi_flash_chip_generic.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *spi_flash/spi_flash_chip_issi.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *spi_flash/spi_flash_chip_mxic.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *spi_flash/spi_flash_chip_th.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *spi_flash/spi_flash_chip_winbond.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *kernel/src/*.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *kernel/libcpu/risc-v/common/context_gcc.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    _data_end = ABSOLUTE(.);
    . = ALIGN(4);
  } > dram0_0_seg

  /**
   * This section holds data that should not be initialized at power up.
   * The section located in Internal SRAM memory region. The macro _NOINIT
   * can be used as attribute to place data into this section.
   * See the "esp_attr.h" file for more information.
   */
  .noinit (NOLOAD):
  {
    . = ALIGN(4);
    _noinit_start = ABSOLUTE(.);
    *(.noinit .noinit.*)
    . = ALIGN(4) ;
    _noinit_end = ABSOLUTE(.);
  } > dram0_0_seg

  .stack :
  {
      . = ALIGN(8);
      __STACKSIZE__ = 51200;
      __stack_start__ = .;
      *(.stack*)
      . += __STACKSIZE__;
      __stack_cpu0 = .;
      __stack_end__ = .;
  } > dram0_0_seg
  PROVIDE( __rt_rvstack = __stack_end__);

  .heap :
  {
      . = ALIGN(8);
      __HEAPSIZE__ = 76800; 
      __heap_start__ = .;
      . += __HEAPSIZE__;
      __heap_end__ = .;
  } > dram0_0_seg

  /* Shared RAM */
  .dram0.bss (NOLOAD) :
  {
    . = ALIGN (8);
    _bss_start = ABSOLUTE(.);

    *(.bss .bss.*)
    *(.dynbss .dynsbss .gnu.linkonce.b .gnu.linkonce.b.* .gnu.linkonce.sb .gnu.linkonce.sb.* .gnu.linkonce.sb2 .gnu.linkonce.sb2.* .sbss .sbss.* .sbss2 .sbss2.* .scommon .share.mem)
    *(.ext_ram.bss .ext_ram.bss.*)
    *(COMMON)
    _bt_bss_start = ABSOLUTE(.);
    *bt/*(.bss .bss.* COMMON)
    . = ALIGN(4);
    _bt_bss_end = ABSOLUTE(.);
    _btdm_bss_start = ABSOLUTE(.);
    *libbtdm_app.a:(.bss .bss.* COMMON)
    . = ALIGN(4);
    _btdm_bss_end = ABSOLUTE(.);
    _nimble_bss_start = ABSOLUTE(.);
    *libnimble.a:(.bss .bss.* COMMON)
    . = ALIGN(4);
    _nimble_bss_end = ABSOLUTE(.);

    *(.dynsbss)
    *(.sbss)
    *(.sbss.*)
    *(.gnu.linkonce.sb.*)
    *(.scommon)
    *(.sbss2)
    *(.sbss2.*)
    *(.gnu.linkonce.sb2.*)
    *(.dynbss)
    *(.share.mem)
    *(.gnu.linkonce.b.*)

    . = ALIGN (8);
    _bss_end = ABSOLUTE(.);
  } > dram0_0_seg

  ASSERT(((_bss_end - ORIGIN(dram0_0_seg)) <= LENGTH(dram0_0_seg)), "DRAM segment data does not fit.")

  .flash.text :
  {
    _stext = .;
    _instruction_reserved_start = ABSOLUTE(.);
    _text_start = ABSOLUTE(.);

    *(EXCLUDE_FILE(*esp_ringbuf/* *gcov/* *librtc.a *app_trace/app_trace.* *app_trace/app_trace_util.* *app_trace/port_uart.* *esp_event/default_event_loop.* *esp_event/esp_event.* *esp_hw_support/cpu.* *esp_hw_support/esp_memory_utils.* *esp_hw_support/rtc_clk.* *esp_hw_support/rtc_init.* *esp_hw_support/rtc_pm.* *esp_hw_support/rtc_sleep.* *esp_hw_support/rtc_time.* *esp_hw_support/systimer.* *esp_rom/esp_rom_regi2c.* *esp_rom/esp_rom_spiflash.* *esp_rom/esp_rom_systimer.* *esp_system/esp_err.* *esp_system/esp_system.* *esp_system/ubsan.* *gcc/_divsf3.* *gcc/lib2funcs.* *gcc/save-restore.* *hal/cache_hal.* *hal/i2c_hal_iram.* *hal/ledc_hal_iram.* *hal/mmu_hal.* *hal/spi_flash_encrypt_hal_iram.* *hal/spi_flash_hal_gpspi.* *hal/spi_flash_hal_iram.* *hal/spi_hal_iram.* *hal/spi_slave_hal_iram.* *hal/systimer_hal.* *hal/wdt_hal_iram.* *heap/multi_heap.* *heap/tlsf.* *log/log.* *log/log_freertos.* *newlib/abort.* *newlib/assert.* *newlib/heap.* *newlib/stdatomic.* *riscv/interrupt.* *riscv/vectors.* *soc/lldesc.* *spi_flash/flash_brownout_hook.* *spi_flash/memspi_host_driver.* *spi_flash/spi_flash_chip_boya.* *spi_flash/spi_flash_chip_gd.* *spi_flash/spi_flash_chip_generic.* *spi_flash/spi_flash_chip_issi.* *spi_flash/spi_flash_chip_mxic.* *spi_flash/spi_flash_chip_th.* *spi_flash/spi_flash_chip_winbond.* *kernel/src/*.* *kernel/libcpu/risc-v/common/context_gcc.*  ) .literal EXCLUDE_FILE(*esp_ringbuf/* *gcov/* *librtc.a *app_trace/app_trace.* *app_trace/app_trace_util.* *app_trace/port_uart.* *esp_event/default_event_loop.* *esp_event/esp_event.* *esp_hw_support/cpu.* *esp_hw_support/esp_memory_utils.* *esp_hw_support/rtc_clk.* *esp_hw_support/rtc_init.* *esp_hw_support/rtc_pm.* *esp_hw_support/rtc_sleep.* *esp_hw_support/rtc_time.* *esp_hw_support/systimer.* *esp_rom/esp_rom_regi2c.* *esp_rom/esp_rom_spiflash.* *esp_rom/esp_rom_systimer.* *esp_system/esp_err.* *esp_system/esp_system.* *esp_system/ubsan.* *gcc/_divsf3.* *gcc/lib2funcs.* *gcc/save-restore.* *hal/cache_hal.* *hal/i2c_hal_iram.* *hal/ledc_hal_iram.* *hal/mmu_hal.* *hal/spi_flash_encrypt_hal_iram.* *hal/spi_flash_hal_gpspi.* *hal/spi_flash_hal_iram.* *hal/spi_hal_iram.* *hal/spi_slave_hal_iram.* *hal/systimer_hal.* *hal/wdt_hal_iram.* *heap/multi_heap.* *heap/tlsf.* *log/log.* *log/log_freertos.* *newlib/abort.* *newlib/assert.* *newlib/heap.* *newlib/stdatomic.* *riscv/interrupt.* *riscv/vectors.* *soc/lldesc.* *spi_flash/flash_brownout_hook.* *spi_flash/memspi_host_driver.* *spi_flash/spi_flash_chip_boya.* *spi_flash/spi_flash_chip_gd.* *spi_flash/spi_flash_chip_generic.* *spi_flash/spi_flash_chip_issi.* *spi_flash/spi_flash_chip_mxic.* *spi_flash/spi_flash_chip_th.* *spi_flash/spi_flash_chip_winbond.* *kernel/src/*.* *kernel/libcpu/risc-v/common/context_gcc.*  ) .literal.* EXCLUDE_FILE(*esp_ringbuf/* *gcov/* *librtc.a *app_trace/app_trace.* *app_trace/app_trace_util.* *app_trace/port_uart.* *esp_event/default_event_loop.* *esp_event/esp_event.* *esp_hw_support/cpu.* *esp_hw_support/esp_memory_utils.* *esp_hw_support/rtc_clk.* *esp_hw_support/rtc_init.* *esp_hw_support/rtc_pm.* *esp_hw_support/rtc_sleep.* *esp_hw_support/rtc_time.* *esp_hw_support/systimer.* *esp_rom/esp_rom_regi2c.* *esp_rom/esp_rom_spiflash.* *esp_rom/esp_rom_systimer.* *esp_system/esp_err.* *esp_system/esp_system.* *esp_system/ubsan.* *gcc/_divsf3.* *gcc/lib2funcs.* *gcc/save-restore.* *hal/cache_hal.* *hal/i2c_hal_iram.* *hal/ledc_hal_iram.* *hal/mmu_hal.* *hal/spi_flash_encrypt_hal_iram.* *hal/spi_flash_hal_gpspi.* *hal/spi_flash_hal_iram.* *hal/spi_hal_iram.* *hal/spi_slave_hal_iram.* *hal/systimer_hal.* *hal/wdt_hal_iram.* *heap/multi_heap.* *heap/tlsf.* *log/log.* *log/log_freertos.* *newlib/abort.* *newlib/assert.* *newlib/heap.* *newlib/stdatomic.* *riscv/interrupt.* *riscv/vectors.* *soc/lldesc.* *spi_flash/flash_brownout_hook.* *spi_flash/memspi_host_driver.* *spi_flash/spi_flash_chip_boya.* *spi_flash/spi_flash_chip_gd.* *spi_flash/spi_flash_chip_generic.* *spi_flash/spi_flash_chip_issi.* *spi_flash/spi_flash_chip_mxic.* *spi_flash/spi_flash_chip_th.* *spi_flash/spi_flash_chip_winbond.* *kernel/src/*.* *kernel/libcpu/risc-v/common/context_gcc.*  ) .text EXCLUDE_FILE(*esp_ringbuf/* *gcov/* *librtc.a *app_trace/app_trace.* *app_trace/app_trace_util.* *app_trace/port_uart.* *esp_event/default_event_loop.* *esp_event/esp_event.* *esp_hw_support/cpu.* *esp_hw_support/esp_memory_utils.* *esp_hw_support/rtc_clk.* *esp_hw_support/rtc_init.* *esp_hw_support/rtc_pm.* *esp_hw_support/rtc_sleep.* *esp_hw_support/rtc_time.* *esp_hw_support/systimer.* *esp_rom/esp_rom_regi2c.* *esp_rom/esp_rom_spiflash.* *esp_rom/esp_rom_systimer.* *esp_system/esp_err.* *esp_system/esp_system.* *esp_system/ubsan.* *gcc/_divsf3.* *gcc/lib2funcs.* *gcc/save-restore.* *hal/cache_hal.* *hal/i2c_hal_iram.* *hal/ledc_hal_iram.* *hal/mmu_hal.* *hal/spi_flash_encrypt_hal_iram.* *hal/spi_flash_hal_gpspi.* *hal/spi_flash_hal_iram.* *hal/spi_hal_iram.* *hal/spi_slave_hal_iram.* *hal/systimer_hal.* *hal/wdt_hal_iram.* *heap/multi_heap.* *heap/tlsf.* *log/log.* *log/log_freertos.* *newlib/abort.* *newlib/assert.* *newlib/heap.* *newlib/stdatomic.* *riscv/interrupt.* *riscv/vectors.* *soc/lldesc.* *spi_flash/flash_brownout_hook.* *spi_flash/memspi_host_driver.* *spi_flash/spi_flash_chip_boya.* *spi_flash/spi_flash_chip_gd.* *spi_flash/spi_flash_chip_generic.* *spi_flash/spi_flash_chip_issi.* *spi_flash/spi_flash_chip_mxic.* *spi_flash/spi_flash_chip_th.* *spi_flash/spi_flash_chip_winbond.* *kernel/src/*.* *kernel/libcpu/risc-v/common/context_gcc.*  ) .text.*)
    *(EXCLUDE_FILE(*libnet80211.a *libpp.a) .wifi0iram EXCLUDE_FILE(*libnet80211.a *libpp.a) .wifi0iram.*)
    *(EXCLUDE_FILE(*libpp.a) .wifiorslpiram EXCLUDE_FILE(*libpp.a) .wifiorslpiram.*)
    *(EXCLUDE_FILE(*libnet80211.a *libpp.a) .wifirxiram EXCLUDE_FILE(*libnet80211.a *libpp.a) .wifirxiram.*)
    *(.wifislpiram .wifislpiram.*)
    *(EXCLUDE_FILE(*libnet80211.a *libpp.a) .wifislprxiram EXCLUDE_FILE(*libnet80211.a *libpp.a) .wifislprxiram.*)
    *esp_event/default_event_loop.*(.text .text.esp_event_handler_instance_register .text.esp_event_handler_instance_unregister .text.esp_event_handler_register .text.esp_event_handler_unregister .text.esp_event_loop_create_default .text.esp_event_loop_delete_default .text.esp_event_post)
    *esp_event/esp_event.*(.text .text.base_node_add_handler .text.base_node_remove_all_handler .text.base_node_remove_handler .text.esp_event_dump .text.esp_event_handler_instance_register_with .text.esp_event_handler_instance_unregister_with .text.esp_event_handler_register_with .text.esp_event_handler_register_with_internal .text.esp_event_handler_unregister_with .text.esp_event_handler_unregister_with_internal .text.esp_event_loop_create .text.esp_event_loop_delete .text.esp_event_loop_run .text.esp_event_loop_run_task .text.esp_event_post_to .text.handler_execute .text.handler_instances_add .text.handler_instances_remove .text.handler_instances_remove_all .text.loop_node_add_handler .text.loop_node_remove_all_handler .text.loop_node_remove_handler)
    *esp_hw_support/cpu.*(.text .text.esp_cpu_clear_breakpoint .text.esp_cpu_clear_watchpoint .text.esp_cpu_configure_region_protection .text.esp_cpu_intr_get_desc .text.esp_cpu_set_breakpoint .text.esp_cpu_set_watchpoint .text.is_intr_num_resv)
    *esp_hw_support/rtc_init.*(.text .text.calibrate_ocode .text.get_dig_dbias_by_efuse .text.get_rtc_dbias_by_efuse .text.rtc_init .text.rtc_vddsdio_get_config .text.set_ocode_by_efuse .text.set_rtc_dig_dbias)
    *esp_system/esp_system.*(.text .text.esp_get_free_heap_size .text.esp_get_free_internal_heap_size .text.esp_get_idf_version .text.esp_get_minimum_free_heap_size .text.esp_register_shutdown_handler .text.esp_unregister_shutdown_handler)
    *log/log.*(.text .text.esp_log_level_get .text.esp_log_level_set .text.esp_log_set_vprintf .text.esp_log_writev .text.heap_bubble_down .text.s_log_level_get_and_unlock)
    *log/log_freertos.*(.text .text.esp_log_system_timestamp)

    *(.stub .gnu.warning .gnu.linkonce.literal.* .gnu.linkonce.t.*.literal .gnu.linkonce.t.*)
    *(.irom0.text) /* catch stray ICACHE_RODATA_ATTR */
    *(.fini.literal)
    *(.fini)
    *(.gnu.version)

    /* section information for finsh shell */
    . = ALIGN(8);
    __fsymtab_start = .;
    KEEP(*(FSymTab))
    __fsymtab_end = .;
    . = ALIGN(8);
    __vsymtab_start = .;
    KEEP(*(VSymTab))
    __vsymtab_end = .;
    . = ALIGN(8);

    /** CPU will try to prefetch up to 16 bytes of
      * of instructions. This means that any configuration (e.g. MMU, PMS) must allow
      * safe access to up to 16 bytes after the last real instruction, add
      * dummy bytes to ensure this
      */
    . += _esp_flash_mmap_prefetch_pad_size;

    _text_end = ABSOLUTE(.);
    _instruction_reserved_end = ABSOLUTE(.);
    _etext = .;

    /**
     * Similar to _iram_start, this symbol goes here so it is
     * resolved by addr2line in preference to the first symbol in
     * the flash.text segment.
     */
    _flash_cache_start = ABSOLUTE(0);
  } > default_code_seg

  /**
   * This dummy section represents the .flash.text section but in default_rodata_seg.
   * Thus, it must have its alignment and (at least) its size.
   */
  .flash_rodata_dummy (NOLOAD):
  {
    _flash_rodata_dummy_start = .;
    /* Start at the same alignment constraint than .flash.text */
    . = ALIGN(ALIGNOF(.flash.text));
    /* Create an empty gap as big as .flash.text section */
    . = . + SIZEOF(.flash.text);
    /* Prepare the alignment of the section above. Few bytes (0x20) must be
     * added for the mapping header. */
    . = ALIGN(0x10000) + 0x20;
    _rodata_reserved_start = .;
  } > default_rodata_seg

  .flash.appdesc : ALIGN(0x10)
  {
    _rodata_start = ABSOLUTE(.);

    *(.rodata_desc .rodata_desc.*)               /* Should be the first.  App version info.        DO NOT PUT ANYTHING BEFORE IT! */
    *(.rodata_custom_desc .rodata_custom_desc.*) /* Should be the second. Custom app version info. DO NOT PUT ANYTHING BEFORE IT! */

    /* Create an empty gap within this section. Thanks to this, the end of this
     * section will match .flash.rodata's begin address. Thus, both sections
     * will be merged when creating the final bin image. */
    . = ALIGN(ALIGNOF(.flash.rodata));
  } >default_rodata_seg

  .flash.rodata : ALIGN(0x10)
  {
    _flash_rodata_start = ABSOLUTE(.);

    *(EXCLUDE_FILE(*gcov/* *libphy.a *app_trace/app_trace.* *app_trace/app_trace_util.* *app_trace/port_uart.* *esp_hw_support/esp_memory_utils.* *esp_hw_support/rtc_clk.* *esp_hw_support/systimer.* *esp_rom/esp_rom_regi2c.* *esp_rom/esp_rom_spiflash.* *esp_rom/esp_rom_systimer.* *esp_system/esp_err.* *esp_system/ubsan.* *gcc/_divsf3.* *gcc/save-restore.* *hal/cache_hal.* *hal/i2c_hal_iram.* *hal/ledc_hal_iram.* *hal/mmu_hal.* *hal/spi_flash_encrypt_hal_iram.* *hal/spi_flash_hal_gpspi.* *hal/spi_flash_hal_iram.* *hal/spi_hal_iram.* *hal/spi_slave_hal_iram.* *hal/systimer_hal.* *hal/wdt_hal_iram.* *heap/multi_heap.* *heap/tlsf.* *newlib/abort.* *newlib/assert.* *newlib/heap.* *newlib/stdatomic.* *soc/lldesc.* *spi_flash/flash_brownout_hook.* *spi_flash/memspi_host_driver.* *spi_flash/spi_flash_chip_boya.* *spi_flash/spi_flash_chip_gd.* *spi_flash/spi_flash_chip_generic.* *spi_flash/spi_flash_chip_issi.* *spi_flash/spi_flash_chip_mxic.* *spi_flash/spi_flash_chip_th.* *spi_flash/spi_flash_chip_winbond.* *kernel/src/*.* *kernel/libcpu/risc-v/common/context_gcc.*  ) .rodata EXCLUDE_FILE(*gcov/* *libphy.a *app_trace/app_trace.* *app_trace/app_trace_util.* *app_trace/port_uart.* *esp_hw_support/esp_memory_utils.* *esp_hw_support/rtc_clk.* *esp_hw_support/systimer.* *esp_rom/esp_rom_regi2c.* *esp_rom/esp_rom_spiflash.* *esp_rom/esp_rom_systimer.* *esp_system/esp_err.* *esp_system/ubsan.* *gcc/_divsf3.* *gcc/save-restore.* *hal/cache_hal.* *hal/i2c_hal_iram.* *hal/ledc_hal_iram.* *hal/mmu_hal.* *hal/spi_flash_encrypt_hal_iram.* *hal/spi_flash_hal_gpspi.* *hal/spi_flash_hal_iram.* *hal/spi_hal_iram.* *hal/spi_slave_hal_iram.* *hal/systimer_hal.* *hal/wdt_hal_iram.* *heap/multi_heap.* *heap/tlsf.* *newlib/abort.* *newlib/assert.* *newlib/heap.* *newlib/stdatomic.* *soc/lldesc.* *spi_flash/flash_brownout_hook.* *spi_flash/memspi_host_driver.* *spi_flash/spi_flash_chip_boya.* *spi_flash/spi_flash_chip_gd.* *spi_flash/spi_flash_chip_generic.* *spi_flash/spi_flash_chip_issi.* *spi_flash/spi_flash_chip_mxic.* *spi_flash/spi_flash_chip_th.* *spi_flash/spi_flash_chip_winbond.* *kernel/src/*.* *kernel/libcpu/risc-v/common/context_gcc.*  ) .rodata.* EXCLUDE_FILE(*gcov/* *libphy.a *app_trace/app_trace.* *app_trace/app_trace_util.* *app_trace/port_uart.* *esp_hw_support/esp_memory_utils.* *esp_hw_support/rtc_clk.* *esp_hw_support/systimer.* *esp_rom/esp_rom_regi2c.* *esp_rom/esp_rom_spiflash.* *esp_rom/esp_rom_systimer.* *esp_system/esp_err.* *esp_system/ubsan.* *gcc/_divsf3.* *gcc/save-restore.* *hal/cache_hal.* *hal/i2c_hal_iram.* *hal/ledc_hal_iram.* *hal/mmu_hal.* *hal/spi_flash_encrypt_hal_iram.* *hal/spi_flash_hal_gpspi.* *hal/spi_flash_hal_iram.* *hal/spi_hal_iram.* *hal/spi_slave_hal_iram.* *hal/systimer_hal.* *hal/wdt_hal_iram.* *heap/multi_heap.* *heap/tlsf.* *newlib/abort.* *newlib/assert.* *newlib/heap.* *newlib/stdatomic.* *soc/lldesc.* *spi_flash/flash_brownout_hook.* *spi_flash/memspi_host_driver.* *spi_flash/spi_flash_chip_boya.* *spi_flash/spi_flash_chip_gd.* *spi_flash/spi_flash_chip_generic.* *spi_flash/spi_flash_chip_issi.* *spi_flash/spi_flash_chip_mxic.* *spi_flash/spi_flash_chip_th.* *spi_flash/spi_flash_chip_winbond.* *kernel/src/*.* *kernel/libcpu/risc-v/common/context_gcc.*  ) .sdata2 EXCLUDE_FILE(*gcov/* *libphy.a *app_trace/app_trace.* *app_trace/app_trace_util.* *app_trace/port_uart.* *esp_hw_support/esp_memory_utils.* *esp_hw_support/rtc_clk.* *esp_hw_support/systimer.* *esp_rom/esp_rom_regi2c.* *esp_rom/esp_rom_spiflash.* *esp_rom/esp_rom_systimer.* *esp_system/esp_err.* *esp_system/ubsan.* *gcc/_divsf3.* *gcc/save-restore.* *hal/cache_hal.* *hal/i2c_hal_iram.* *hal/ledc_hal_iram.* *hal/mmu_hal.* *hal/spi_flash_encrypt_hal_iram.* *hal/spi_flash_hal_gpspi.* *hal/spi_flash_hal_iram.* *hal/spi_hal_iram.* *hal/spi_slave_hal_iram.* *hal/systimer_hal.* *hal/wdt_hal_iram.* *heap/multi_heap.* *heap/tlsf.* *newlib/abort.* *newlib/assert.* *newlib/heap.* *newlib/stdatomic.* *soc/lldesc.* *spi_flash/flash_brownout_hook.* *spi_flash/memspi_host_driver.* *spi_flash/spi_flash_chip_boya.* *spi_flash/spi_flash_chip_gd.* *spi_flash/spi_flash_chip_generic.* *spi_flash/spi_flash_chip_issi.* *spi_flash/spi_flash_chip_mxic.* *spi_flash/spi_flash_chip_th.* *spi_flash/spi_flash_chip_winbond.* *kernel/src/*.* *kernel/libcpu/risc-v/common/context_gcc.*  ) .sdata2.* EXCLUDE_FILE(*gcov/* *libphy.a *app_trace/app_trace.* *app_trace/app_trace_util.* *app_trace/port_uart.* *esp_hw_support/esp_memory_utils.* *esp_hw_support/rtc_clk.* *esp_hw_support/systimer.* *esp_rom/esp_rom_regi2c.* *esp_rom/esp_rom_spiflash.* *esp_rom/esp_rom_systimer.* *esp_system/esp_err.* *esp_system/ubsan.* *gcc/_divsf3.* *gcc/save-restore.* *hal/cache_hal.* *hal/i2c_hal_iram.* *hal/ledc_hal_iram.* *hal/mmu_hal.* *hal/spi_flash_encrypt_hal_iram.* *hal/spi_flash_hal_gpspi.* *hal/spi_flash_hal_iram.* *hal/spi_hal_iram.* *hal/spi_slave_hal_iram.* *hal/systimer_hal.* *hal/wdt_hal_iram.* *heap/multi_heap.* *heap/tlsf.* *newlib/abort.* *newlib/assert.* *newlib/heap.* *newlib/stdatomic.* *soc/lldesc.* *spi_flash/flash_brownout_hook.* *spi_flash/memspi_host_driver.* *spi_flash/spi_flash_chip_boya.* *spi_flash/spi_flash_chip_gd.* *spi_flash/spi_flash_chip_generic.* *spi_flash/spi_flash_chip_issi.* *spi_flash/spi_flash_chip_mxic.* *spi_flash/spi_flash_chip_th.* *spi_flash/spi_flash_chip_winbond.* *kernel/src/*.* *kernel/libcpu/risc-v/common/context_gcc.*  ) .srodata EXCLUDE_FILE(*gcov/* *libphy.a *app_trace/app_trace.* *app_trace/app_trace_util.* *app_trace/port_uart.* *esp_hw_support/esp_memory_utils.* *esp_hw_support/rtc_clk.* *esp_hw_support/systimer.* *esp_rom/esp_rom_regi2c.* *esp_rom/esp_rom_spiflash.* *esp_rom/esp_rom_systimer.* *esp_system/esp_err.* *esp_system/ubsan.* *gcc/_divsf3.* *gcc/save-restore.* *hal/cache_hal.* *hal/i2c_hal_iram.* *hal/ledc_hal_iram.* *hal/mmu_hal.* *hal/spi_flash_encrypt_hal_iram.* *hal/spi_flash_hal_gpspi.* *hal/spi_flash_hal_iram.* *hal/spi_hal_iram.* *hal/spi_slave_hal_iram.* *hal/systimer_hal.* *hal/wdt_hal_iram.* *heap/multi_heap.* *heap/tlsf.* *newlib/abort.* *newlib/assert.* *newlib/heap.* *newlib/stdatomic.* *soc/lldesc.* *spi_flash/flash_brownout_hook.* *spi_flash/memspi_host_driver.* *spi_flash/spi_flash_chip_boya.* *spi_flash/spi_flash_chip_gd.* *spi_flash/spi_flash_chip_generic.* *spi_flash/spi_flash_chip_issi.* *spi_flash/spi_flash_chip_mxic.* *spi_flash/spi_flash_chip_th.* *spi_flash/spi_flash_chip_winbond.* *kernel/src/*.* *kernel/libcpu/risc-v/common/context_gcc.*  ) .srodata.*)
    *(.rodata_wlog_error .rodata_wlog_error.*)
    *(.rodata_wlog_info .rodata_wlog_info.*)
    *(.rodata_wlog_warning .rodata_wlog_warning.*)

    *(.irom1.text) /* catch stray ICACHE_RODATA_ATTR */
    *(.gnu.linkonce.r.*)
    *(.rodata1)
    __XT_EXCEPTION_TABLE_ = ABSOLUTE(.);
    *(.xt_except_table)
    *(.gcc_except_table .gcc_except_table.*)
    *(.gnu.linkonce.e.*)
    *(.gnu.version_r)
    . = (. + 7) & ~ 3;
    /*
     * C++ constructor and destructor tables
     * Don't include anything from crtbegin.o or crtend.o, as IDF doesn't use toolchain crt.
     *
     * RISC-V gcc is configured with --enable-initfini-array so it emits an .init_array section instead.
     * But the init_priority sections will be sorted for iteration in ascending order during startup.
     * The rest of the init_array sections is sorted for iteration in descending order during startup, however.
     * Hence a different section is generated for the init_priority functions which is iterated in
     * ascending order during startup. The corresponding code can be found in startup.c.
     */
    __init_priority_array_start = ABSOLUTE(.);
    KEEP (*(EXCLUDE_FILE (*crtend.* *crtbegin.*) .init_array.*))
    __init_priority_array_end = ABSOLUTE(.);
    __init_array_start = ABSOLUTE(.);
    KEEP (*(EXCLUDE_FILE (*crtend.* *crtbegin.*) .init_array))
    __init_array_end = ABSOLUTE(.);
    KEEP (*crtbegin.*(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.*) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    /* C++ exception handlers table: */
    __XT_EXCEPTION_DESCS_ = ABSOLUTE(.);
    *(.xt_except_desc)
    *(.gnu.linkonce.h.*)
    __XT_EXCEPTION_DESCS_END__ = ABSOLUTE(.);
    *(.xt_except_desc_end)
    *(.dynamic)
    *(.gnu.version_d)
    /* Addresses of memory regions reserved via SOC_RESERVE_MEMORY_REGION() */
    soc_reserved_memory_region_start = ABSOLUTE(.);
    KEEP (*(.reserved_memory_address))
    soc_reserved_memory_region_end = ABSOLUTE(.);
    /* System init functions registered via ESP_SYSTEM_INIT_FN */
    _esp_system_init_fn_array_start = ABSOLUTE(.);
    KEEP (*(SORT_BY_INIT_PRIORITY(.esp_system_init_fn.*)))
    _esp_system_init_fn_array_end = ABSOLUTE(.);
    /* section information for initial. */
    . = ALIGN(4);
    __rt_init_start = .;
    KEEP(*(SORT(.rti_fn*)))
    __rt_init_end = .;
    . = ALIGN(4);
    _rodata_end = ABSOLUTE(.);
    /* Literals are also RO data. */
    _lit4_start = ABSOLUTE(.);
    *(*.lit4)
    *(.lit4.*)
    *(.gnu.linkonce.lit4.*)
    _lit4_end = ABSOLUTE(.);
    . = ALIGN(4);
    _thread_local_start = ABSOLUTE(.);
    *(.tdata)
    *(.tdata.*)
    *(.tbss)
    *(.tbss.*)
    _thread_local_end = ABSOLUTE(.);
    _rodata_reserved_end = ABSOLUTE(.);
    . = ALIGN(ALIGNOF(.eh_frame));
  } > default_rodata_seg

  /* Keep this section shall be at least aligned on 4 */
  .eh_frame : ALIGN(8)
  {
    __eh_frame = ABSOLUTE(.);
    KEEP (*(.eh_frame))
    __eh_frame_end = ABSOLUTE(.);
    /* Guarantee that this section and the next one will be merged by making
     * them adjacent. */
    . = ALIGN(ALIGNOF(.eh_frame_hdr));
  } > default_rodata_seg

  /* To avoid any exception in C++ exception frame unwinding code, this section
   * shall be aligned on 8. */
  .eh_frame_hdr : ALIGN(8)
  {
    __eh_frame_hdr = ABSOLUTE(.);
    KEEP (*(.eh_frame_hdr))
    __eh_frame_hdr_end = ABSOLUTE(.);
  } > default_rodata_seg

  .flash.rodata_noload (NOLOAD) :
  {
    . = ALIGN (4);
    *(.rodata_wlog_debug .rodata_wlog_debug.*)
    *(.rodata_wlog_verbose .rodata_wlog_verbose.*)
  } > default_rodata_seg

  /* Marks the end of IRAM code segment */
  .iram0.text_end (NOLOAD) :
  {
    /* iram_end_test section exists for use by Memprot unit tests only */
    *(.iram_end_test)
    /* ESP32-C3 memprot requires 16B padding for possible CPU prefetch and 512B alignment for PMS split lines */
    . += _esp_memprot_prefetch_pad_size;
    . = ALIGN(_esp_memprot_align_size);
    _iram_text_end = ABSOLUTE(.);
  } > iram0_0_seg

  .iram0.data :
  {
    . = ALIGN(16);
    _iram_data_start = ABSOLUTE(.);

    *(.iram.data .iram.data.*)
    _coredump_iram_start = ABSOLUTE(.);
    *(.iram2.coredump .iram2.coredump.*)
    _coredump_iram_end = ABSOLUTE(.);

    _iram_data_end = ABSOLUTE(.);
  } > iram0_0_seg

  .iram0.bss (NOLOAD) :
  {
    . = ALIGN(16);
    _iram_bss_start = ABSOLUTE(.);

    *(.iram.bss .iram.bss.*)

    _iram_bss_end = ABSOLUTE(.);
    . = ALIGN(16);
    _iram_end = ABSOLUTE(.);
  } > iram0_0_seg

  /* Marks the end of data, bss and possibly rodata  */
  .dram0.heap_start (NOLOAD) :
  {
    . = ALIGN (16);
    _heap_start = ABSOLUTE(.);
  } > dram0_0_seg
}

ASSERT(((_iram_end - ORIGIN(iram0_0_seg)) <= LENGTH(iram0_0_seg)),
          "IRAM0 segment data does not fit.")

ASSERT(((_heap_start - ORIGIN(dram0_0_seg)) <= LENGTH(dram0_0_seg)),
          "DRAM segment data does not fit.")
