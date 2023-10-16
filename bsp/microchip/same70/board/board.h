/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date        Author     Email                     Notes
 * 2019-07-16  Kevin.Liu  kevin.liu.mchp@gmail.com  First Release
 * 2023-09-16  luhuadong  luhuadong@163.com         fix uart config
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#include "sam.h"

// <o> Internal SRAM memory size[Kbytes] <256-384>
//  <i>Default: 384
#if defined(__SAME70J19B__) || defined(__ATSAME70J19B__)
  #define SAME70_SRAM_SIZE   256
#elif defined(__SAME70J20B__) || defined(__ATSAME70J20B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAME70J21B__) || defined(__ATSAME70J21B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAME70N19B__) || defined(__ATSAME70N19B__)
  #define SAME70_SRAM_SIZE   256
#elif defined(__SAME70N20B__) || defined(__ATSAME70N20B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAME70N21B__) || defined(__ATSAME70N21B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAME70Q19B__) || defined(__ATSAME70Q19B__)
  #define SAME70_SRAM_SIZE   256
#elif defined(__SAME70Q20B__) || defined(__ATSAME70Q20B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAME70Q21B__) || defined(__ATSAME70Q21B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAMS70J19B__) || defined(__ATSAMS70J19B__)
  #define SAME70_SRAM_SIZE   256
#elif defined(__SAMS70J20B__) || defined(__ATSAMS70J20B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAMS70J21B__) || defined(__ATSAMS70J21B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAMS70N19B__) || defined(__ATSAMS70N19B__)
  #define SAME70_SRAM_SIZE   256
#elif defined(__SAMS70N20B__) || defined(__ATSAMS70N20B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAMS70N21B__) || defined(__ATSAMS70N21B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAMS70Q19B__) || defined(__ATSAMS70Q19B__)
  #define SAME70_SRAM_SIZE   256
#elif defined(__SAMS70Q20B__) || defined(__ATSAMS70Q20B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAMS70Q21B__) || defined(__ATSAMS70Q21B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAMV70J19B__) || defined(__ATSAMV70J19B__)
  #define SAME70_SRAM_SIZE   256
#elif defined(__SAMV70J20B__) || defined(__ATSAMV70J20B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAMV70J21B__) || defined(__ATSAMV70J21B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAMV70N19B__) || defined(__ATSAMV70N19B__)
  #define SAME70_SRAM_SIZE   256
#elif defined(__SAMV70N20B__) || defined(__ATSAMV70N20B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAMV70N21B__) || defined(__ATSAMV70N21B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAMV70Q19B__) || defined(__ATSAMV70Q19B__)
  #define SAME70_SRAM_SIZE   256
#elif defined(__SAMV70Q20B__) || defined(__ATSAMV70Q20B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAMV70Q21B__) || defined(__ATSAMV70Q21B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAMV71J19B__) || defined(__ATSAMV71J19B__)
  #define SAME70_SRAM_SIZE   256
#elif defined(__SAMV71J20B__) || defined(__ATSAMV71J20B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAMV71J21B__) || defined(__ATSAMV71J21B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAMV71N19B__) || defined(__ATSAMV71N19B__)
  #define SAME70_SRAM_SIZE   256
#elif defined(__SAMV71N20B__) || defined(__ATSAMV71N20B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAMV71N21B__) || defined(__ATSAMV71N21B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAMV71Q19B__) || defined(__ATSAMV71Q19B__)
  #define SAME70_SRAM_SIZE   256
#elif defined(__SAMV71Q20B__) || defined(__ATSAMV71Q20B__)
  #define SAME70_SRAM_SIZE   384
#elif defined(__SAMV71Q21B__) || defined(__ATSAMV71Q21B__)
  #define SAME70_SRAM_SIZE   384
#else
#error Board does not support the specified device
#endif

#define SAME70_SRAM_END    (0x20400000 + SAME70_SRAM_SIZE * 1024)

#if defined(__ARMCC_VERSION)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN    (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN    (__segment_begin("HEAP"))
#define HEAP_END      (__segment_end("HEAP"))
#else
extern int __bss_end;
#define HEAP_BEGIN    (&__bss_end)
#define HEAP_END      SAME70_SRAM_END
#endif

#ifdef RT_USING_SERIAL
#include "hpl_usart_config.h"
#define DEFAULT_USART_BAUD_RATE CONF_USART_1_BAUD
#endif

void rt_hw_board_init(void);

#endif

