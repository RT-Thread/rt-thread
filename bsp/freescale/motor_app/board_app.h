/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 *
 */

// <<< Use Configuration Wizard in Context Menu >>>
#ifndef __BOARD_APP_H__
#define __BOARD_APP_H__

#include <board.h>

#define _STR(v) #v
#define STR(v) _STR(v)
#define CONSOLE_DEVICE "uart"STR(BOARD_DEBUG_UART_INSTANCE)
#define FINSH_DEVICE_NAME   CONSOLE_DEVICE

extern unsigned int m_data_start;
extern unsigned int m_data_end;

#if 0

  #ifdef __CC_ARM
  extern int Image$$RW_IRAM1$$ZI$$Limit;
  #define SRAM_BEGIN    (&Image$$RW_IRAM1$$ZI$$Limit)
  #elif __ICCARM__
  #pragma section="HEAP"
  #define SRAM_BEGIN    (__segment_end("HEAP"))
  #else
  extern int __bss_end;
  #define SRAM_BEGIN    (&__bss_end)
  #endif

  /* board configuration */
#define SRAM_SIZE   128
#define SRAM_END    ((uint32_t)SRAM_BEGIN + (SRAM_SIZE * 1024))  
  
#else

  /* Addresses for VECTOR_TABLE and VECTOR_RAM come from the linker file */
  #if defined(__CC_ARM) /* Keil MDK */
      extern uint32_t Image$$ARM_LIB_HEAP$$Base[];
      extern uint32_t Image$$ARM_LIB_STACK$$ZI$$Base[];
      extern uint32_t Image$$VECTOR_ROM$$Base[];
      extern uint32_t Image$$VECTOR_RAM$$Base[];
      #define __VECTOR_TABLE Image$$VECTOR_ROM$$Base
      #define __VECTOR_RAM Image$$VECTOR_RAM$$Base
      #define __HEAP_START Image$$ARM_LIB_HEAP$$Base
      #define __HEAP_END Image$$ARM_LIB_STACK$$ZI$$Base  /* Segment is defined in opposite way (from higher address to lower) than usually!!!  */
  #elif defined(__ICCARM__) /* IAR */
      #pragma section = "ZI"
      #define __ZI_END  (__section_end("ZI"))
      #pragma section = "RW"
      #define __RW_END  (__section_end("RW"))
      #pragma section = "HEAP"
      #define __HEAP_START  (__section_begin("HEAP"))
      #pragma section = "CSTACK"
      #define __HEAP_END  (__section_begin("CSTACK"))
      extern uint32_t __VECTOR_TABLE[NUMBER_OF_INT_VECTORS * sizeof(uint32_t)];
      extern uint32_t __VECTOR_RAM[NUMBER_OF_INT_VECTORS * sizeof(uint32_t)];
  #elif defined(__GNUC__) /* GCC */
      extern uint32_t __bss_end__[];
      extern uint32_t __StackLimit[];
      #define __HEAP_START __bss_end__
      #define __HEAP_END  __StackLimit
      extern uint32_t __VECTOR_TABLE[NUMBER_OF_INT_VECTORS * sizeof(uint32_t)];
      extern uint32_t __VECTOR_RAM[NUMBER_OF_INT_VECTORS * sizeof(uint32_t)];
  #else
      #error Unsupported tool
  #endif

/* board configuration */
#define SRAM_BEGIN  __HEAP_START
#define SRAM_END    __HEAP_END
      
#endif




#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

void rt_hw_board_init(void);

void gpio_init();


#if defined(__cplusplus)
}
#endif /* __cplusplus */




#endif

// <<< Use Configuration Wizard in Context Menu >>>
