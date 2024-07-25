/*
 * File      : usart.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     WCH        the first version
 */
#ifndef __DRV_ETH_H__
#define __DRV_ETH_H__
#include "rthw.h"
#include "rtthread.h"
#include "ch32v30x_eth.h"


/* MII/MDI interface select */
#define PHY_ADDRESS 0x01
#define USE10BASE_T

#ifndef USE10BASE_T
    #define USE_GIGA_MAC
    #ifndef USE_GIGA_MAC
        #define USE_FAST_MAC
        //#define USE_RMII
    #endif
#endif

#define ETH_RXBUFNB        6
#define ETH_TXBUFNB        6

#if 0
#define USE_LOOP_STRUCT  1
#else
#define USE_CHAIN_STRUCT  1
#endif


typedef struct
{
    u32 length;
    u32 buffer;
    ETH_DMADESCTypeDef *descriptor;
}FrameTypeDef;

#endif
