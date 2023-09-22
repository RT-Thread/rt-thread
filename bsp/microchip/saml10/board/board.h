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

// <o> Internal SRAM memory size[Kbytes] <4-16>
//  <i>Default: 16
#if   defined(__SAML10E14A__) || defined(__ATSAML10E14A__)
  #define SAML10_SRAM_SIZE   4
#elif defined(__SAML10E15A__) || defined(__ATSAML10E15A__)
  #define SAML10_SRAM_SIZE   8
#elif defined(__SAML10E16A__) || defined(__ATSAML10E16A__)
  #define SAML10_SRAM_SIZE   16
#elif defined(__SAML10D14A__) || defined(__ATSAML10D14A__)
  #define SAML10_SRAM_SIZE   4
#elif defined(__SAML10D15A__) || defined(__ATSAML10D15A__)
  #define SAML10_SRAM_SIZE   8
#elif defined(__SAML10D16A__) || defined(__ATSAML10D16A__)
  #define SAML10_SRAM_SIZE   16
#else
  #error Board does not support the specified device.
#endif

#define SAML10_SRAM_END        (0x20000000 + SAML10_SRAM_SIZE * 1024)

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
#define HEAP_END      SAML10_SRAM_END
#endif

#ifdef RT_USING_SERIAL
#include "hpl_sercom_config.h"
#define DEFAULT_USART_BAUD_RATE CONF_SERCOM_2_USART_BAUD
#endif

void rt_hw_board_init(void);

#endif

