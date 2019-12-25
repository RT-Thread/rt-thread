/* Linker script to configure memory regions. */

SEARCH_DIR(.)
GROUP(-lgcc -lc -lnosys)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x12000, LENGTH = 0x6e000
  RAM (rwx) :  ORIGIN = 0x20000b80, LENGTH = 0xf480
}

SECTIONS
{
}

SECTIONS
{
  . = ALIGN(4);
  .mem_section_dummy_ram :
  {
  }

} INSERT AFTER .data;

SECTIONS
{
  .mem_section_dummy_rom :
  {
  }

} INSERT AFTER .text


INCLUDE "nrf_common.ld"
