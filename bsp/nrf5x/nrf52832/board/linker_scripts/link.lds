/* Linker script to configure memory regions. */

SEARCH_DIR(.)
GROUP(-lgcc -lc -lnosys)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 0x80000
  RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x10000
  CODE_RAM (rwx) : ORIGIN = 0x800000, LENGTH = 0x10000
}

INCLUDE "packages/nrfx-v2.1.0/mdk/nrf_common.ld"



