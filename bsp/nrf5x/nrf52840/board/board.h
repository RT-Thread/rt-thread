#ifndef _BOARD_H_
#define _BOARD_H_

#include <rtthread.h>
#include <rthw.h>
#include "nrf.h"

#define MCU_FLASH_SIZE MCU_FLASH_SIZE_KB*1024
#define MCU_FLASH_END_ADDRESS        ((uint32_t)(MCU_FLASH_START_ADDRESS + MCU_FLASH_SIZE))
#define MCU_SRAM_SIZE MCU_SRAM_SIZE_KB*1024
#define MCU_SRAM_END_ADDRESS        (MCU_SRAM_START_ADDRESS + MCU_SRAM_SIZE)

/* led pins define on board*/
#define DK_BOARD_LED_1  13
#define DK_BOARD_LED_2  14
#define DK_BOARD_LED_3  15
#define DK_BOARD_LED_4  16

/* button pins define on board*/
#define DK_BOARD_BUTTON_1  11
#define DK_BOARD_BUTTON_2  12
#define DK_BOARD_BUTTON_3  24
#define DK_BOARD_BUTTON_4  25

#if defined(__CC_ARM) || defined(__CLANG_ARM)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN      (__segment_end("CSTACK"))
#else
extern int __bss_end;
#define HEAP_BEGIN      ((void *)&__bss_end)
#endif

#define HEAP_END       (0x20000000 + 64*1024)

void rt_hw_board_init(void);

#endif

