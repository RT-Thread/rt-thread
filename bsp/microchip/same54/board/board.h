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

// <o> Internal SRAM memory size[Kbytes] <128-256>
//  <i>Default: 256
#if   defined(__SAME54N19A__) || defined(__ATSAME54N19A__)
  #define SAME5x_SRAM_SIZE   192
#elif defined(__SAME54N20A__) || defined(__ATSAME54N20A__)
  #define SAME5x_SRAM_SIZE   256
#elif defined(__SAME54P19A__) || defined(__ATSAME54P19A__)
  #define SAME5x_SRAM_SIZE   192
#elif defined(__SAME54P20A__) || defined(__ATSAME54P20A__)
  #define SAME5x_SRAM_SIZE   256
#elif defined(__SAME53J18A__) || defined(__ATSAME53J18A__)
  #define SAME5x_SRAM_SIZE   128
#elif defined(__SAME53J19A__) || defined(__ATSAME53J19A__)
  #define SAME5x_SRAM_SIZE   192
#elif defined(__SAME53J20A__) || defined(__ATSAME53J20A__)
  #define SAME5x_SRAM_SIZE   256
#elif defined(__SAME53N19A__) || defined(__ATSAME53N19A__)
  #define SAME5x_SRAM_SIZE   192
#elif defined(__SAME53N20A__) || defined(__ATSAME53N20A__)
  #define SAME5x_SRAM_SIZE   256
#elif defined(__SAME51J18A__) || defined(__ATSAME51J18A__)
  #define SAME5x_SRAM_SIZE   128
#elif defined(__SAME51J19A__) || defined(__ATSAME51J19A__)
  #define SAME5x_SRAM_SIZE   192
#elif defined(__SAME51J20A__) || defined(__ATSAME51J20A__)
  #define SAME5x_SRAM_SIZE   256
#elif defined(__SAME51N19A__) || defined(__ATSAME51N19A__)
  #define SAME5x_SRAM_SIZE   192
#elif defined(__SAME51N20A__) || defined(__ATSAME51N20A__)
  #define SAME5x_SRAM_SIZE   256
#elif defined(__SAMD51J18A__) || defined(__ATSAMD51J18A__)
  #define SAME5x_SRAM_SIZE   128
#elif defined(__SAMD51J19A__) || defined(__ATSAMD51J19A__)
  #define SAME5x_SRAM_SIZE   192
#elif defined(__SAMD51J20A__) || defined(__ATSAMD51J20A__)
  #define SAME5x_SRAM_SIZE   256
#elif defined(__SAMD51N19A__) || defined(__ATSAMD51N19A__)
  #define SAME5x_SRAM_SIZE   192
#elif defined(__SAMD51N20A__) || defined(__ATSAMD51N20A__)
  #define SAME5x_SRAM_SIZE   256
#elif defined(__SAMD51P19A__) || defined(__ATSAMD51P19A__)
  #define SAME5x_SRAM_SIZE   192
#elif defined(__SAMD51P20A__) || defined(__ATSAMD51P20A__)
  #define SAME5x_SRAM_SIZE   256
#else
  #error Board does not support the specified device.
#endif

#define SAME5x_SRAM_END      (0x20000000 + SAME5x_SRAM_SIZE * 1024)

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
#define HEAP_END      SAME5x_SRAM_END
#endif

#ifdef RT_USING_SERIAL
#include "hpl_sercom_config.h"
#define DEFAULT_USART_BAUD_RATE CONF_SERCOM_2_USART_BAUD
#endif

void rt_hw_board_init(void);

#endif

