       
       
_esp_flash_mmap_prefetch_pad_size = 16;
_esp_memprot_prefetch_pad_size = 0;
_esp_memprot_align_size = 0;
_esp_mmu_block_size = (0x10000);
MEMORY
{
  iram0_0_seg (RX) : org = (0x40800000), len = 0x4086E610 - (0x40800000 - 0x40800000) - (0x40800000)
  irom_seg (RX) : org = 0x42000020, len = (0x10000 << 8) - 0x20
  dram0_0_seg (RW) : org = (0x40800000), len = 0x4086E610 - (0x40800000 - 0x40800000) - (0x40800000)
  drom_seg (R) : org = 0x42000020, len = (0x10000 << 8) - 0x20
  lp_ram_seg(RW) : org = 0x50000000, len = 0x4000 - (0 + (24))
  lp_reserved_seg(RW) : org = 0x50000000 + 0x4000 - (0 + (24)), len = (0 + (24))
}
_heap_end = 0x40000000;
_data_seg_org = ORIGIN(rtc_data_seg);
REGION_ALIAS("rtc_iram_seg", lp_ram_seg );
REGION_ALIAS("rtc_data_seg", rtc_iram_seg );
REGION_ALIAS("rtc_slow_seg", rtc_iram_seg );
REGION_ALIAS("rtc_data_location", rtc_iram_seg );
REGION_ALIAS("rtc_reserved_seg", lp_reserved_seg );
  REGION_ALIAS("default_code_seg", irom_seg);
  REGION_ALIAS("default_rodata_seg", drom_seg);
  ASSERT(_flash_rodata_dummy_start == ORIGIN(default_rodata_seg),
         ".flash_rodata_dummy section must be placed at the beginning of the rodata segment.")
