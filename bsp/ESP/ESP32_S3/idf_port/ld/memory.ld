       
       
_esp_flash_mmap_prefetch_pad_size = 16;
_esp_memprot_prefetch_pad_size = 16;
_esp_memprot_align_size = 256;
_esp_mmu_block_size = (0x10000);
MEMORY
{
  iram0_0_seg (RX) : org = (0x40370000 + 0x4000), len = (((0x403CC700 - (0x40378000 - 0x3FC88000)) - 0x3FC88000) + 0x8000 - 0x4000)
  iram0_2_seg (RX) : org = 0x42000020, len = 0x800000-0x20
  dram0_0_seg (RW) : org = (0x3FC88000), len = ((0x403CC700 - (0x40378000 - 0x3FC88000)) - 0x3FC88000)
  drom0_0_seg (R) : org = 0x3C000020, len = 0x2000000-0x20
  rtc_iram_seg(RWX) : org = 0x600fe000, len = 0x2000 - (0 + (24))
  rtc_reserved_seg(RW) : org = 0x600fe000 + 0x2000 - (0 + (24)), len = (0 + (24))
  rtc_slow_seg(RW) : org = 0x50000000 , len = 0x2000
  extern_ram_seg(RWX) : org = 0x3c000020 , len = 0x2000000-0x20
}
_heap_start = _heap_low_start;
_heap_end = 0x40000000;
_data_seg_org = ORIGIN(rtc_data_seg);
REGION_ALIAS("rtc_data_seg", rtc_iram_seg );
REGION_ALIAS("rtc_data_location", rtc_slow_seg );
REGION_ALIAS("default_code_seg", iram0_2_seg);
REGION_ALIAS("default_rodata_seg", drom0_0_seg);
  ASSERT(_flash_rodata_dummy_start == ORIGIN(default_rodata_seg),
         ".flash_rodata_dummy section must be placed at the beginning of the rodata segment.")
