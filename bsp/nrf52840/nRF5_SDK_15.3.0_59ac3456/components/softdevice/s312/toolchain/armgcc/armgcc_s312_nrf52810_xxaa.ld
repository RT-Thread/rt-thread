/* Linker script to configure memory regions. */

SEARCH_DIR(.)
GROUP(-lgcc -lc -lnosys)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x24000, LENGTH = 0xc000
  RAM (rwx) :  ORIGIN = 0x20001300, LENGTH = 0x4d00
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
