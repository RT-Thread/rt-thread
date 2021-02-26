/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author                   Notes
 * 2020-10-28     0xcccccccccccc           Initial Version
 */
/**
 * @addtogroup ls2k
 */
/*@{*/
#ifndef LS2K_DRV_SPI_H
#define LS2K_DRV_SPI_H

#include <rtthread.h>
#include <rthw.h>

// kseg1 byte operation
#define KSEG1_STORE8(addr,val)	 *(volatile char *)(0xffffffffa0000000 | addr) = val
#define KSEG1_LOAD8(addr)	 *(volatile char *)(0xffffffffa0000000 | addr) 
// clock configurations
#define APB_MAX_SPEED 125000000U
#define APB_FREQSCALE (((KSEG1_LOAD8(0xffffffffbfe104d2)>>4)&0x7)+1)
// base addrs
#define SPI_BASE  0x1fff0220
#define PMON_ADDR 0xa1000000
#define FLASH_ADDR 0x000000
// bit bias
#define SPCR      0x0
#define SPSR      0x1
#define FIFO	  0x2
#define TXFIFO    0x2
#define RXFIFO    0x2
#define SPER      0x3
#define PARAM     0x4
#define SOFTCS    0x5
#define PARAM2    0x6
#define RFEMPTY 1
// SPI controller operaion macros
#define SET_SPI(addr,val)        KSEG1_STORE8(SPI_BASE+addr,val)
#define GET_SPI(addr)            KSEG1_LOAD8(SPI_BASE+addr)

#endif
/*@}*/
