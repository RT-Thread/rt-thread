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

// <o> Internal SRAM memory size[Kbytes] <4-32>
//  <i>Default: 32
#if   defined(__SAMC21E15A__) || defined(__ATSAMC21E15A__)
  #define SAMC21_SRAM_SIZE   4
#elif defined(__SAMC21E16A__) || defined(__ATSAMC21E16A__)
  #define SAMC21_SRAM_SIZE   8
#elif defined(__SAMC21E17A__) || defined(__ATSAMC21E17A__)
  #define SAMC21_SRAM_SIZE   16
#elif defined(__SAMC21E18A__) || defined(__ATSAMC21E18A__)
  #define SAMC21_SRAM_SIZE   32
#elif defined(__SAMC21G15A__) || defined(__ATSAMC21G15A__)
  #define SAMC21_SRAM_SIZE   4
#elif defined(__SAMC21G16A__) || defined(__ATSAMC21G16A__)
  #define SAMC21_SRAM_SIZE   8
#elif defined(__SAMC21G17A__) || defined(__ATSAMC21G17A__)
  #define SAMC21_SRAM_SIZE   16
#elif defined(__SAMC21G18A__) || defined(__ATSAMC21G18A__)
  #define SAMC21_SRAM_SIZE   32
#elif defined(__SAMC21J15A__) || defined(__ATSAMC21J15A__)
  #define SAMC21_SRAM_SIZE   4
#elif defined(__SAMC21J16A__) || defined(__ATSAMC21J16A__)
  #define SAMC21_SRAM_SIZE   8
#elif defined(__SAMC21J17A__) || defined(__ATSAMC21J17A__)
  #define SAMC21_SRAM_SIZE   16
#elif defined(__SAMC21J17AU__) || defined(__ATSAMC21J17AU__)
  #define SAMC21_SRAM_SIZE   16
#elif defined(__SAMC21J18A__) || defined(__ATSAMC21J18A__)
  #define SAMC21_SRAM_SIZE   32
#elif defined(__SAMC21J18AU__) || defined(__ATSAMC21J18AU__)
  #define SAMC21_SRAM_SIZE   32
#else
  #error Board does not support the specified device.
#endif

#define SAMC21_SRAM_END        (0x20000000 + SAMC21_SRAM_SIZE * 1024)

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
#define HEAP_END      SAMC21_SRAM_END
#endif

#ifdef RT_USING_SERIAL
#include "hpl_sercom_config.h"
#define DEFAULT_USART_BAUD_RATE CONF_SERCOM_4_USART_BAUD
#endif

void rt_hw_board_init(void);

#endif

