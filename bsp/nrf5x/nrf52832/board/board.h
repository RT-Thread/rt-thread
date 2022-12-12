#ifndef _BOARD_H_
#define _BOARD_H_

#include <rtthread.h>
#include <rthw.h>
#include "nrf.h"

#define MCU_FLASH_SIZE MCU_FLASH_SIZE_KB*1024
#define MCU_FLASH_END_ADDRESS        ((uint32_t)(MCU_FLASH_START_ADDRESS + MCU_FLASH_SIZE))
#define MCU_SRAM_SIZE MCU_SRAM_SIZE_KB*1024
#define MCU_SRAM_END_ADDRESS        (MCU_SRAM_START_ADDRESS + MCU_SRAM_SIZE)

#if defined(__ARMCC_VERSION)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN      (__segment_end("CSTACK"))
#else
extern int __bss_end__;
#define HEAP_BEGIN      ((void *)&__bss_end__)
#endif

#define HEAP_END       (MCU_SRAM_END_ADDRESS)

void rt_hw_board_init(void);

#endif

