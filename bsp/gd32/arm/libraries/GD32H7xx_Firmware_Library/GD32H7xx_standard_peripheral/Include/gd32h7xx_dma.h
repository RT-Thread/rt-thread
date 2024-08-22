/*!
    \file    gd32h7xx_dma.h
    \brief   definitions for the DMA

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#ifndef GD32H7XX_DMA_H
#define GD32H7XX_DMA_H

#include "gd32h7xx.h"

/* DMA definitions */
#define DMA0                               (DMA_BASE)                           /*!< DMA0 base address */
#define DMA1                               (DMA_BASE + 0x00000400U)             /*!< DMA1 base address */

/* DMAMUX definitions */
#define DMAMUX                             DMAMUX_BASE                          /*!< DMA base address */

/* DMA registers definitions */
#define DMA_INTF0(dmax)                    REG32((dmax) + 0x00000000U)          /*!< DMA interrupt flag register 0 */
#define DMA_INTF1(dmax)                    REG32((dmax) + 0x00000004U)          /*!< DMA interrupt flag register 1 */
#define DMA_INTC0(dmax)                    REG32((dmax) + 0x00000008U)          /*!< DMA interrupt flag clear register 0 */
#define DMA_INTC1(dmax)                    REG32((dmax) + 0x0000000CU)          /*!< DMA interrupt flag clear register 1 */
#define DMA_CH0CTL(dmax)                   REG32((dmax) + 0x00000010U)          /*!< DMA channel 0 control register */
#define DMA_CH0CNT(dmax)                   REG32((dmax) + 0x00000014U)          /*!< DMA channel 0 counter register */
#define DMA_CH0PADDR(dmax)                 REG32((dmax) + 0x00000018U)          /*!< DMA channel 0 peripheral base address register */
#define DMA_CH0M0ADDR(dmax)                REG32((dmax) + 0x0000001CU)          /*!< DMA channel 0 memory 0 base address register */
#define DMA_CH0M1ADDR(dmax)                REG32((dmax) + 0x00000020U)          /*!< DMA channel 0 memory 1 base address register */
#define DMA_CH0FCTL(dmax)                  REG32((dmax) + 0x00000024U)          /*!< DMA channel 0 FIFO control register */
#define DMA_CH1CTL(dmax)                   REG32((dmax) + 0x00000028U)          /*!< DMA channel 1 control register */
#define DMA_CH1CNT(dmax)                   REG32((dmax) + 0x0000002CU)          /*!< DMA channel 1 counter register */
#define DMA_CH1PADDR(dmax)                 REG32((dmax) + 0x00000030U)          /*!< DMA channel 1 peripheral base address register */
#define DMA_CH1M0ADDR(dmax)                REG32((dmax) + 0x00000034U)          /*!< DMA channel 1 memory 0 base address register */
#define DMA_CH1M1ADDR(dmax)                REG32((dmax) + 0x00000038U)          /*!< DMA channel 1 memory 1 base address register */
#define DMA_CH1FCTL(dmax)                  REG32((dmax) + 0x0000003CU)          /*!< DMA channel 1 FIFO control register */
#define DMA_CH2CTL(dmax)                   REG32((dmax) + 0x00000040U)          /*!< DMA channel 2 control register */
#define DMA_CH2CNT(dmax)                   REG32((dmax) + 0x00000044U)          /*!< DMA channel 2 counter register */
#define DMA_CH2PADDR(dmax)                 REG32((dmax) + 0x00000048U)          /*!< DMA channel 2 peripheral base address register */
#define DMA_CH2M0ADDR(dmax)                REG32((dmax) + 0x0000004CU)          /*!< DMA channel 2 memory 0 base address register */
#define DMA_CH2M1ADDR(dmax)                REG32((dmax) + 0x00000050U)          /*!< DMA channel 2 memory 1 base address register */
#define DMA_CH2FCTL(dmax)                  REG32((dmax) + 0x00000054U)          /*!< DMA channel 2 FIFO control register */
#define DMA_CH3CTL(dmax)                   REG32((dmax) + 0x00000058U)          /*!< DMA channel 3 control register */
#define DMA_CH3CNT(dmax)                   REG32((dmax) + 0x0000005CU)          /*!< DMA channel 3 counter register */
#define DMA_CH3PADDR(dmax)                 REG32((dmax) + 0x00000060U)          /*!< DMA channel 3 peripheral base address register */
#define DMA_CH3M0ADDR(dmax)                REG32((dmax) + 0x00000064U)          /*!< DMA channel 3 memory 0 base address register */
#define DMA_CH3M1ADDR(dmax)                REG32((dmax) + 0x00000068U)          /*!< DMA channel 3 memory 1 base address register */
#define DMA_CH3FCTL(dmax)                  REG32((dmax) + 0x0000006CU)          /*!< DMA channel 3 FIFO control register */
#define DMA_CH4CTL(dmax)                   REG32((dmax) + 0x00000070U)          /*!< DMA channel 4 control register */
#define DMA_CH4CNT(dmax)                   REG32((dmax) + 0x00000074U)          /*!< DMA channel 4 counter register */
#define DMA_CH4PADDR(dmax)                 REG32((dmax) + 0x00000078U)          /*!< DMA channel 4 peripheral base address register */
#define DMA_CH4M0ADDR(dmax)                REG32((dmax) + 0x0000007CU)          /*!< DMA channel 4 memory 0 base address register */
#define DMA_CH4M1ADDR(dmax)                REG32((dmax) + 0x00000080U)          /*!< DMA channel 4 memory 1 base address register */
#define DMA_CH4FCTL(dmax)                  REG32((dmax) + 0x00000084U)          /*!< DMA channel 4 FIFO control register */
#define DMA_CH5CTL(dmax)                   REG32((dmax) + 0x00000088U)          /*!< DMA channel 5 control register */
#define DMA_CH5CNT(dmax)                   REG32((dmax) + 0x0000008CU)          /*!< DMA channel 5 counter register */
#define DMA_CH5PADDR(dmax)                 REG32((dmax) + 0x00000090U)          /*!< DMA channel 5 peripheral base address register */
#define DMA_CH5M0ADDR(dmax)                REG32((dmax) + 0x00000094U)          /*!< DMA channel 5 memory 0 base address register */
#define DMA_CH5M1ADDR(dmax)                REG32((dmax) + 0x00000098U)          /*!< DMA channel 5 memory 1 base address register */
#define DMA_CH5FCTL(dmax)                  REG32((dmax) + 0x0000009CU)          /*!< DMA channel 5 FIFO control register */
#define DMA_CH6CTL(dmax)                   REG32((dmax) + 0x000000A0U)          /*!< DMA channel 6 control register */
#define DMA_CH6CNT(dmax)                   REG32((dmax) + 0x000000A4U)          /*!< DMA channel 6 counter register */
#define DMA_CH6PADDR(dmax)                 REG32((dmax) + 0x000000A8U)          /*!< DMA channel 6 peripheral base address register */
#define DMA_CH6M0ADDR(dmax)                REG32((dmax) + 0x000000ACU)          /*!< DMA channel 6 memory 0 base address register */
#define DMA_CH6M1ADDR(dmax)                REG32((dmax) + 0x000000B0U)          /*!< DMA channel 6 memory 1 base address register */
#define DMA_CH6FCTL(dmax)                  REG32((dmax) + 0x000000B4U)          /*!< DMA channel 6 FIFO control register */
#define DMA_CH7CTL(dmax)                   REG32((dmax) + 0x000000B8U)          /*!< DMA channel 7 control register */
#define DMA_CH7CNT(dmax)                   REG32((dmax) + 0x000000BCU)          /*!< DMA channel 7 counter register */
#define DMA_CH7PADDR(dmax)                 REG32((dmax) + 0x000000C0U)          /*!< DMA channel 7 peripheral base address register */
#define DMA_CH7M0ADDR(dmax)                REG32((dmax) + 0x000000C4U)          /*!< DMA channel 7 memory 0 base address register */
#define DMA_CH7M1ADDR(dmax)                REG32((dmax) + 0x000000C8U)          /*!< DMA channel 7 memory 1 base address register */
#define DMA_CH7FCTL(dmax)                  REG32((dmax) + 0x000000CCU)          /*!< DMA channel 7 FIFO control register */

/* DMAMUX registers definitions */
#define DMAMUX_RM_CH0CFG                   REG32(DMAMUX + 0x00000000U)          /*!< DMAMUX request multiplexer channel 0 configuration register */
#define DMAMUX_RM_CH1CFG                   REG32(DMAMUX + 0x00000004U)          /*!< DMAMUX request multiplexer channel 1 configuration register */
#define DMAMUX_RM_CH2CFG                   REG32(DMAMUX + 0x00000008U)          /*!< DMAMUX request multiplexer channel 2 configuration register */
#define DMAMUX_RM_CH3CFG                   REG32(DMAMUX + 0x0000000CU)          /*!< DMAMUX request multiplexer channel 3 configuration register */
#define DMAMUX_RM_CH4CFG                   REG32(DMAMUX + 0x00000010U)          /*!< DMAMUX request multiplexer channel 4 configuration register */
#define DMAMUX_RM_CH5CFG                   REG32(DMAMUX + 0x00000014U)          /*!< DMAMUX request multiplexer channel 5 configuration register */
#define DMAMUX_RM_CH6CFG                   REG32(DMAMUX + 0x00000018U)          /*!< DMAMUX request multiplexer channel 6 configuration register */
#define DMAMUX_RM_CH7CFG                   REG32(DMAMUX + 0x0000001CU)          /*!< DMAMUX request multiplexer channel 7 configuration register */
#define DMAMUX_RM_CH8CFG                   REG32(DMAMUX + 0x00000020U)          /*!< DMAMUX request multiplexer channel 8 configuration register */
#define DMAMUX_RM_CH9CFG                   REG32(DMAMUX + 0x00000024U)          /*!< DMAMUX request multiplexer channel 9 configuration register */
#define DMAMUX_RM_CH10CFG                  REG32(DMAMUX + 0x00000028U)          /*!< DMAMUX request multiplexer channel 10 configuration register */
#define DMAMUX_RM_CH11CFG                  REG32(DMAMUX + 0x0000002CU)          /*!< DMAMUX request multiplexer channel 11 configuration register */
#define DMAMUX_RM_CH12CFG                  REG32(DMAMUX + 0x00000030U)          /*!< DMAMUX request multiplexer channel 12 configuration register */
#define DMAMUX_RM_CH13CFG                  REG32(DMAMUX + 0x00000034U)          /*!< DMAMUX request multiplexer channel 13 configuration register */
#define DMAMUX_RM_CH14CFG                  REG32(DMAMUX + 0x00000038U)          /*!< DMAMUX request multiplexer channel 14 configuration register */
#define DMAMUX_RM_CH15CFG                  REG32(DMAMUX + 0x0000003CU)          /*!< DMAMUX request multiplexer channel 15 configuration register */
#define DMAMUX_RM_INTF                     REG32(DMAMUX + 0x00000080U)          /*!< DMAMUX request multiplexer channel interrupt flag register */
#define DMAMUX_RM_INTC                     REG32(DMAMUX + 0x00000084U)          /*!< DMAMUX request multiplexer channel interrupt flag clear register */
#define DMAMUX_RG_CH0CFG                   REG32(DMAMUX + 0x00000100U)          /*!< DMAMUX generator channel 0 configuration register */
#define DMAMUX_RG_CH1CFG                   REG32(DMAMUX + 0x00000104U)          /*!< DMAMUX generator channel 1 configuration register */
#define DMAMUX_RG_CH2CFG                   REG32(DMAMUX + 0x00000108U)          /*!< DMAMUX generator channel 2 configuration register */
#define DMAMUX_RG_CH3CFG                   REG32(DMAMUX + 0x0000010CU)          /*!< DMAMUX generator channel 3 configuration register */
#define DMAMUX_RG_CH4CFG                   REG32(DMAMUX + 0x00000110U)          /*!< DMAMUX generator channel 4 configuration register */
#define DMAMUX_RG_CH5CFG                   REG32(DMAMUX + 0x00000114U)          /*!< DMAMUX generator channel 5 configuration register */
#define DMAMUX_RG_CH6CFG                   REG32(DMAMUX + 0x00000118U)          /*!< DMAMUX generator channel 6 configuration register */
#define DMAMUX_RG_CH7CFG                   REG32(DMAMUX + 0x0000011CU)          /*!< DMAMUX generator channel 7 configuration register */
#define DMAMUX_RG_INTF                     REG32(DMAMUX + 0x00000140U)          /*!< DMAMUX generator channel interrupt flag register */
#define DMAMUX_RG_INTC                     REG32(DMAMUX + 0x00000144U)          /*!< DMAMUX rgenerator channel interrupt flag clear register */

/* bits definitions */
/* DMA_INTF */
#define DMA_INTF_FEEIF                     BIT(0)                               /*!< FIFO error and exception flag */
#define DMA_INTF_SDEIF                     BIT(2)                               /*!< single data mode exception flag */
#define DMA_INTF_TAEIF                     BIT(3)                               /*!< transfer access error flag */
#define DMA_INTF_HTFIF                     BIT(4)                               /*!< half transfer finish flag */
#define DMA_INTF_FTFIF                     BIT(5)                               /*!< full transger finish flag */

/* DMA_INTC */
#define DMA_INTC_FEEIFC                    BIT(0)                               /*!< clear FIFO error and exception flag */
#define DMA_INTC_SDEIFC                    BIT(2)                               /*!< clear single data mode exception flag */
#define DMA_INTC_TAEIFC                    BIT(3)                               /*!< clear single data mode exception flag */
#define DMA_INTC_HTFIFC                    BIT(4)                               /*!< clear half transfer finish flag */
#define DMA_INTC_FTFIFC                    BIT(5)                               /*!< clear full transger finish flag */

/* DMA_CHxCTL,x=0..7 */
#define DMA_CHXCTL_CHEN                    BIT(0)                               /*!< channel x enable */
#define DMA_CHXCTL_SDEIE                   BIT(1)                               /*!< enable bit for channel x single data mode exception interrupt */
#define DMA_CHXCTL_TAEIE                   BIT(2)                               /*!< enable bit for channel x tranfer access error interrupt */
#define DMA_CHXCTL_HTFIE                   BIT(3)                               /*!< enable bit for channel x half transfer finish interrupt */
#define DMA_CHXCTL_FTFIE                   BIT(4)                               /*!< enable bit for channel x full transfer finish interrupt */
#define DMA_CHXCTL_TM                      BITS(6,7)                            /*!< transfer mode */
#define DMA_CHXCTL_CMEN                    BIT(8)                               /*!< circulation mode */
#define DMA_CHXCTL_PNAGA                   BIT(9)                               /*!< next address generation algorithm of peripheral */
#define DMA_CHXCTL_MNAGA                   BIT(10)                              /*!< next address generation algorithm of memory */
#define DMA_CHXCTL_PWIDTH                  BITS(11,12)                          /*!< transfer width of peipheral */
#define DMA_CHXCTL_MWIDTH                  BITS(13,14)                          /*!< transfer width of memory */
#define DMA_CHXCTL_PAIF                    BIT(15)                              /*!< peripheral address increment fixed */
#define DMA_CHXCTL_PRIO                    BITS(16,17)                          /*!< priority level */
#define DMA_CHXCTL_SBMEN                   BIT(18)                              /*!< switch-buffer mode enable */
#define DMA_CHXCTL_MBS                     BIT(19)                              /*!< memory buffer select */
#define DMA_CHXCTL_PBURST                  BITS(21,22)                          /*!< transfer burst type of peripheral */
#define DMA_CHXCTL_MBURST                  BITS(23,24)                          /*!< transfer burst type of memory */

/* DMA_CHxCNT,x=0..7 */
#define DMA_CHXCNT_CNT                     BITS(0,15)                           /*!< transfer counter */

/* DMA_CHxPADDR,x=0..7 */
#define DMA_CHXPADDR_PADDR                 BITS(0,31)                           /*!< peripheral base address */

/* DMA_CHxM0ADDR,x=0..7 */
#define DMA_CHXM0ADDR_M0ADDR               BITS(0,31)                           /*!< memory 0 base address */

/* DMA_CHxM1ADDR,x=0..7 */
#define DMA_CHXM1ADDR_M1ADDR               BITS(0,31)                           /*!< memory 1 base address */

/* DMA_CHxFCTL,x=0..7 */
#define DMA_CHXFCTL_FCCV                   BITS(0,1)                            /*!< FIFO counter critical value */
#define DMA_CHXFCTL_MDMEN                  BIT(2)                               /*!< multi-data mode enable */
#define DMA_CHXFCTL_FCNT                   BITS(3,5)                            /*!< FIFO counter */
#define DMA_CHXFCTL_FEEIE                  BIT(7)                               /*!< FIFO exception interrupt enable */

/* DMAMUX_RM_CHxCFG,x=0..15 */
#define DMAMUX_RM_CHXCFG_MUXID             BITS(0,7)                            /*!< multiplexer input identification */
#define DMAMUX_RM_CHXCFG_SOIE              BIT(8)                               /*!< synchronization overrun interrupt enable */
#define DMAMUX_RM_CHXCFG_EVGEN             BIT(9)                               /*!< event generation enable */
#define DMAMUX_RM_CHXCFG_SYNCEN            BIT(16)                              /*!< synchronization enable */
#define DMAMUX_RM_CHXCFG_SYNCP             BITS(17,18)                          /*!< synchronization input polarity */
#define DMAMUX_RM_CHXCFG_NBR               BITS(19,23)                          /*!< number of DMA requests to forward */
#define DMAMUX_RM_CHXCFG_SYNCID            BITS(24,28)                          /*!< synchronization input identification */

/* DMAMUX_RM_INTF */
#define DMAMUX_RM_INTF_SOIF0               BIT(0)                               /*!< synchronization overrun event flag of request multiplexer channel 0 */
#define DMAMUX_RM_INTF_SOIF1               BIT(1)                               /*!< synchronization overrun event flag of request multiplexer channel 1 */
#define DMAMUX_RM_INTF_SOIF2               BIT(2)                               /*!< synchronization overrun event flag of request multiplexer channel 2 */
#define DMAMUX_RM_INTF_SOIF3               BIT(3)                               /*!< synchronization overrun event flag of request multiplexer channel 3 */
#define DMAMUX_RM_INTF_SOIF4               BIT(4)                               /*!< synchronization overrun event flag of request multiplexer channel 4 */
#define DMAMUX_RM_INTF_SOIF5               BIT(5)                               /*!< synchronization overrun event flag of request multiplexer channel 5 */
#define DMAMUX_RM_INTF_SOIF6               BIT(6)                               /*!< synchronization overrun event flag of request multiplexer channel 6 */
#define DMAMUX_RM_INTF_SOIF7               BIT(7)                               /*!< synchronization overrun event flag of request multiplexer channel 7 */
#define DMAMUX_RM_INTF_SOIF8               BIT(8)                               /*!< synchronization overrun event flag of request multiplexer channel 8 */
#define DMAMUX_RM_INTF_SOIF9               BIT(9)                               /*!< synchronization overrun event flag of request multiplexer channel 9 */
#define DMAMUX_RM_INTF_SOIF10              BIT(10)                              /*!< synchronization overrun event flag of request multiplexer channel 10 */
#define DMAMUX_RM_INTF_SOIF11              BIT(11)                              /*!< synchronization overrun event flag of request multiplexer channel 11 */
#define DMAMUX_RM_INTF_SOIF12              BIT(12)                              /*!< synchronization overrun event flag of request multiplexer channel 12 */
#define DMAMUX_RM_INTF_SOIF13              BIT(13)                              /*!< synchronization overrun event flag of request multiplexer channel 13 */
#define DMAMUX_RM_INTF_SOIF14              BIT(14)                              /*!< synchronization overrun event flag of request multiplexer channel 14 */
#define DMAMUX_RM_INTF_SOIF15              BIT(15)                              /*!< synchronization overrun event flag of request multiplexer channel 15 */

/* DMAMUX_RM_INTC */
#define DMAMUX_RM_INTC_SOIFC0              BIT(0)                               /*!< clear bit for synchronization overrun event flag of request multiplexer channel 0 */
#define DMAMUX_RM_INTC_SOIFC1              BIT(1)                               /*!< clear bit for synchronization overrun event flag of request multiplexer channel 1 */
#define DMAMUX_RM_INTC_SOIFC2              BIT(2)                               /*!< clear bit for synchronization overrun event flag of request multiplexer channel 2 */
#define DMAMUX_RM_INTC_SOIFC3              BIT(3)                               /*!< clear bit for synchronization overrun event flag of request multiplexer channel 3 */
#define DMAMUX_RM_INTC_SOIFC4              BIT(4)                               /*!< clear bit for synchronization overrun event flag of request multiplexer channel 4 */
#define DMAMUX_RM_INTC_SOIFC5              BIT(5)                               /*!< clear bit for synchronization overrun event flag of request multiplexer channel 5 */
#define DMAMUX_RM_INTC_SOIFC6              BIT(6)                               /*!< clear bit for synchronization overrun event flag of request multiplexer channel 6 */
#define DMAMUX_RM_INTC_SOIFC7              BIT(7)                               /*!< clear bit for synchronization overrun event flag of request multiplexer channel 7 */
#define DMAMUX_RM_INTC_SOIFC8              BIT(8)                               /*!< clear bit for synchronization overrun event flag of request multiplexer channel 8 */
#define DMAMUX_RM_INTC_SOIFC9              BIT(9)                               /*!< clear bit for synchronization overrun event flag of request multiplexer channel 9 */
#define DMAMUX_RM_INTC_SOIFC10             BIT(10)                              /*!< clear bit for synchronization overrun event flag of request multiplexer channel 10 */
#define DMAMUX_RM_INTC_SOIFC11             BIT(11)                              /*!< clear bit for synchronization overrun event flag of request multiplexer channel 11 */
#define DMAMUX_RM_INTC_SOIFC12             BIT(12)                              /*!< clear bit for synchronization overrun event flag of request multiplexer channel 12 */
#define DMAMUX_RM_INTC_SOIFC13             BIT(13)                              /*!< clear bit for synchronization overrun event flag of request multiplexer channel 13 */
#define DMAMUX_RM_INTC_SOIFC14             BIT(14)                              /*!< clear bit for synchronization overrun event flag of request multiplexer channel 14 */
#define DMAMUX_RM_INTC_SOIFC15             BIT(15)                              /*!< clear bit for synchronization overrun event flag of request multiplexer channel 15 */

/* DMAMUX_RG_CHxCFG,x=0..7 */
#define DMAMUX_RG_CHXCFG_TID               BITS(0,5)                            /*!< trigger input identification */
#define DMAMUX_RG_CHXCFG_TOIE              BIT(8)                               /*!< trigger overrun interrupt enable */
#define DMAMUX_RG_CHXCFG_RGEN              BIT(16)                              /*!< DMA request generator channel x enable */
#define DMAMUX_RG_CHXCFG_RGTP              BITS(17,18)                          /*!< DMA request generator trigger polarity */
#define DMAMUX_RG_CHXCFG_NBRG              BITS(19,23)                          /*!< number of DMA requests to be generated */

/* DMAMUX_RG_INTF */
#define DMAMUX_RG_INTF_TOIF0               BIT(0)                               /*!< trigger overrun event flag of request generator channel 0 */
#define DMAMUX_RG_INTF_TOIF1               BIT(1)                               /*!< trigger overrun event flag of request generator channel 1 */
#define DMAMUX_RG_INTF_TOIF2               BIT(2)                               /*!< trigger overrun event flag of request generator channel 2 */
#define DMAMUX_RG_INTF_TOIF3               BIT(3)                               /*!< trigger overrun event flag of request generator channel 3 */
#define DMAMUX_RG_INTF_TOIF4               BIT(4)                               /*!< trigger overrun event flag of request generator channel 4 */
#define DMAMUX_RG_INTF_TOIF5               BIT(5)                               /*!< trigger overrun event flag of request generator channel 5 */
#define DMAMUX_RG_INTF_TOIF6               BIT(6)                               /*!< trigger overrun event flag of request generator channel 6 */
#define DMAMUX_RG_INTF_TOIF7               BIT(7)                               /*!< trigger overrun event flag of request generator channel 7 */

/* DMAMUX_RG_INTC */
#define DMAMUX_RG_INTC_TOIFC0              BIT(0)                               /*!< clear bit for trigger overrun event flag of request generator channel 0 */
#define DMAMUX_RG_INTC_TOIFC1              BIT(1)                               /*!< clear bit for trigger overrun event flag of request generator channel 1 */
#define DMAMUX_RG_INTC_TOIFC2              BIT(2)                               /*!< clear bit for trigger overrun event flag of request generator channel 2 */
#define DMAMUX_RG_INTC_TOIFC3              BIT(3)                               /*!< clear bit for trigger overrun event flag of request generator channel 3 */
#define DMAMUX_RG_INTC_TOIFC4              BIT(4)                               /*!< clear bit for trigger overrun event flag of request generator channel 4 */
#define DMAMUX_RG_INTC_TOIFC5              BIT(5)                               /*!< clear bit for trigger overrun event flag of request generator channel 5 */
#define DMAMUX_RG_INTC_TOIFC6              BIT(6)                               /*!< clear bit for trigger overrun event flag of request generator channel 6 */
#define DMAMUX_RG_INTC_TOIFC7              BIT(7)                               /*!< clear bit for trigger overrun event flag of request generator channel 7 */

/* constants definitions */
/* define the DMAMUX bit position and its register index offset */
#define DMAMUX_REGIDX_BIT(regidx, bitpos) (((uint32_t)(regidx) << 6U) | (uint32_t)(bitpos))
#define DMAMUX_REG_VAL(offset)            (REG32(DMAMUX + (((uint32_t)(offset) & 0x0000FFFFU) >> 6U)))
#define DMAMUX_BIT_POS(val)               ((uint32_t)(val) & 0x1FU)
#define DMAMUX_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22U) | (uint32_t)((bitpos2) << 16U) \
        | (((uint32_t)(regidx) << 6U) | (uint32_t)(bitpos)))
#define DMAMUX_REG_VAL2(offset)            (REG32(DMAMUX + ((uint32_t)(offset) >> 22U)))
#define DMAMUX_BIT_POS2(val)               (((uint32_t)(val) & 0x001F0000U) >> 16U)
#define DMAMUX_REG_VAL3(offset)            (REG32(DMAMUX + (((uint32_t)(offset) & 0x0000FFFFU) >> 6U) + 0x4U))

/* register offset */
#define DMAMUX_RM_CH0CFG_REG_OFFSET       ((uint32_t)0x00000000U)                                                      /*!< DMAMUX_RM_CH0CFG register offset */
#define DMAMUX_RM_CH1CFG_REG_OFFSET       ((uint32_t)0x00000004U)                                                      /*!< DMAMUX_RM_CH1CFG register offset */
#define DMAMUX_RM_CH2CFG_REG_OFFSET       ((uint32_t)0x00000008U)                                                      /*!< DMAMUX_RM_CH2CFG register offset */
#define DMAMUX_RM_CH3CFG_REG_OFFSET       ((uint32_t)0x0000000CU)                                                      /*!< DMAMUX_RM_CH3CFG register offset */
#define DMAMUX_RM_CH4CFG_REG_OFFSET       ((uint32_t)0x00000010U)                                                      /*!< DMAMUX_RM_CH4CFG register offset */
#define DMAMUX_RM_CH5CFG_REG_OFFSET       ((uint32_t)0x00000014U)                                                      /*!< DMAMUX_RM_CH5CFG register offset */
#define DMAMUX_RM_CH6CFG_REG_OFFSET       ((uint32_t)0x00000018U)                                                      /*!< DMAMUX_RM_CH6CFG register offset */
#define DMAMUX_RM_CH7CFG_REG_OFFSET       ((uint32_t)0x0000001CU)                                                      /*!< DMAMUX_RM_CH7CFG register offset */
#define DMAMUX_RM_CH8CFG_REG_OFFSET       ((uint32_t)0x00000020U)                                                      /*!< DMAMUX_RM_CH8CFG register offset */
#define DMAMUX_RM_CH9CFG_REG_OFFSET       ((uint32_t)0x00000024U)                                                      /*!< DMAMUX_RM_CH9CFG register offset */
#define DMAMUX_RM_CH10CFG_REG_OFFSET      ((uint32_t)0x00000028U)                                                      /*!< DMAMUX_RM_CH10CFG register offset */
#define DMAMUX_RM_CH11CFG_REG_OFFSET      ((uint32_t)0x0000002CU)                                                      /*!< DMAMUX_RM_CH11CFG register offset */
#define DMAMUX_RM_CH12CFG_REG_OFFSET      ((uint32_t)0x00000030U)                                                      /*!< DMAMUX_RM_CH12CFG register offset */
#define DMAMUX_RM_CH13CFG_REG_OFFSET      ((uint32_t)0x00000034U)                                                      /*!< DMAMUX_RM_CH13CFG register offset */
#define DMAMUX_RM_CH14CFG_REG_OFFSET      ((uint32_t)0x00000038U)                                                      /*!< DMAMUX_RM_CH14CFG register offset */
#define DMAMUX_RM_CH15CFG_REG_OFFSET      ((uint32_t)0x0000003CU)                                                      /*!< DMAMUX_RM_CH15CFG register offset */
#define DMAMUX_RG_CH0CFG_REG_OFFSET       ((uint32_t)0x00000100U)                                                      /*!< DMAMUX_RG_CH0CFG register offset */
#define DMAMUX_RG_CH1CFG_REG_OFFSET       ((uint32_t)0x00000104U)                                                      /*!< DMAMUX_RG_CH1CFG register offset */
#define DMAMUX_RG_CH2CFG_REG_OFFSET       ((uint32_t)0x00000108U)                                                      /*!< DMAMUX_RG_CH2CFG register offset */
#define DMAMUX_RG_CH3CFG_REG_OFFSET       ((uint32_t)0x0000010CU)                                                      /*!< DMAMUX_RG_CH3CFG register offset */
#define DMAMUX_RG_CH4CFG_REG_OFFSET       ((uint32_t)0x00000110U)                                                      /*!< DMAMUX_RG_CH0CFG register offset */
#define DMAMUX_RG_CH5CFG_REG_OFFSET       ((uint32_t)0x00000114U)                                                      /*!< DMAMUX_RG_CH1CFG register offset */
#define DMAMUX_RG_CH6CFG_REG_OFFSET       ((uint32_t)0x00000118U)                                                      /*!< DMAMUX_RG_CH2CFG register offset */
#define DMAMUX_RG_CH7CFG_REG_OFFSET       ((uint32_t)0x0000011CU)                                                      /*!< DMAMUX_RG_CH3CFG register offset */
#define DMAMUX_RM_INTF_REG_OFFSET         ((uint32_t)0x00000080U)                                                      /*!< DMAMUX_RM_INTF register offset */
#define DMAMUX_RG_INTF_REG_OFFSET         ((uint32_t)0x00000140U)                                                      /*!< DMAMUX_RG_INTF register offset */

/* DMA multi-data mode initialize structrue */
typedef struct {
    uint32_t request;                                                                                                  /*!< channel input identification */
    uint32_t periph_addr;                                                                                              /*!< peripheral base address */
    uint32_t periph_width;                                                                                             /*!< transfer data size of peripheral */
    uint32_t periph_inc;                                                                                               /*!< peripheral increasing mode */
    uint32_t memory0_addr;                                                                                             /*!< memory 0 base address */
    uint32_t memory_width;                                                                                             /*!< transfer data size of memory */
    uint32_t memory_inc;                                                                                               /*!< memory increasing mode */
    uint32_t memory_burst_width;                                                                                       /*!< memory burst width */
    uint32_t periph_burst_width;                                                                                       /*!< periph burst width */
    uint32_t critical_value;                                                                                           /*!< FIFO critical */
    uint32_t circular_mode;                                                                                            /*!< DMA circular mode */
    uint32_t direction;                                                                                                /*!< channel data transfer direction */
    uint32_t number;                                                                                                   /*!< channel transfer number */
    uint32_t priority;                                                                                                 /*!< channel priority level */
} dma_multi_data_parameter_struct;

/* DMA single-data mode initialize structrue */
typedef struct {
    uint32_t request;                                                                                                  /*!< channel input identification */
    uint32_t periph_addr;                                                                                              /*!< peripheral base address */
    uint32_t periph_inc;                                                                                               /*!< peripheral increasing mode */
    uint32_t memory0_addr;                                                                                             /*!< memory 0 base address */
    uint32_t memory_inc;                                                                                               /*!< memory increasing mode */
    uint32_t periph_memory_width;                                                                                      /*!< transfer data size of peripheral */
    uint32_t circular_mode;                                                                                            /*!< DMA circular mode */
    uint32_t direction;                                                                                                /*!< channel data transfer direction */
    uint32_t number;                                                                                                   /*!< channel transfer number */
    uint32_t priority;                                                                                                 /*!< channel priority level */
} dma_single_data_parameter_struct;

/* DMAMUX request multiplexer synchronization configuration structure */
typedef struct {
    uint32_t sync_id;                                                                                                  /*!< synchronization input identification */
    uint32_t sync_polarity;                                                                                            /*!< synchronization input polarity */
    uint32_t request_number;                                                                                           /*!< number of DMA requests to forward */
} dmamux_sync_parameter_struct;

/* DMAMUX request generator trigger configuration structure */
typedef struct {
    uint32_t trigger_id;                                                                                               /*!< trigger input identification */
    uint32_t trigger_polarity;                                                                                         /*!< DMAMUX request generator trigger polarity */
    uint32_t request_number;                                                                                           /*!< number of DMA requests to be generated */
} dmamux_gen_parameter_struct;

/* DMA channel select */
typedef enum {
    DMA_CH0 = 0U,                                                                                                      /*!< DMA Channel 0 */
    DMA_CH1,                                                                                                           /*!< DMA Channel 1 */
    DMA_CH2,                                                                                                           /*!< DMA Channel 2 */
    DMA_CH3,                                                                                                           /*!< DMA Channel 3 */
    DMA_CH4,                                                                                                           /*!< DMA Channel 4 */
    DMA_CH5,                                                                                                           /*!< DMA Channel 5 */
    DMA_CH6,                                                                                                           /*!< DMA Channel 6 */
    DMA_CH7                                                                                                            /*!< DMA Channel 7 */
} dma_channel_enum;

/* DMAMUX request multiplexer channel */
typedef enum {
    DMAMUX_MUXCH0 = 0U,                                                                                                /*!< DMAMUX request multiplexer Channel0 */
    DMAMUX_MUXCH1,                                                                                                     /*!< DMAMUX request multiplexer Channel1 */
    DMAMUX_MUXCH2,                                                                                                     /*!< DMAMUX request multiplexer Channel2 */
    DMAMUX_MUXCH3,                                                                                                     /*!< DMAMUX request multiplexer Channel3 */
    DMAMUX_MUXCH4,                                                                                                     /*!< DMAMUX request multiplexer Channel4 */
    DMAMUX_MUXCH5,                                                                                                     /*!< DMAMUX request multiplexer Channel5 */
    DMAMUX_MUXCH6,                                                                                                     /*!< DMAMUX request multiplexer Channel6 */
    DMAMUX_MUXCH7,                                                                                                     /*!< DMAMUX request multiplexer Channel7 */
    DMAMUX_MUXCH8,                                                                                                     /*!< DMAMUX request multiplexer Channel8 */
    DMAMUX_MUXCH9,                                                                                                     /*!< DMAMUX request multiplexer Channel9 */
    DMAMUX_MUXCH10,                                                                                                    /*!< DMAMUX request multiplexer Channel10 */
    DMAMUX_MUXCH11,                                                                                                    /*!< DMAMUX request multiplexer Channel11 */
    DMAMUX_MUXCH12,                                                                                                    /*!< DMAMUX request multiplexer Channel12 */
    DMAMUX_MUXCH13,                                                                                                    /*!< DMAMUX request multiplexer Channel13 */
    DMAMUX_MUXCH14,                                                                                                    /*!< DMAMUX request multiplexer Channel14 */
    DMAMUX_MUXCH15                                                                                                     /*!< DMAMUX request multiplexer Channel15 */
} dmamux_multiplexer_channel_enum;

/* DMAMUX request generator channel */
typedef enum {
    DMAMUX_GENCH0 = 0U,                                                                                                /*!< DMAMUX request generator Channel0 */
    DMAMUX_GENCH1,                                                                                                     /*!< DMAMUX request generator Channel1 */
    DMAMUX_GENCH2,                                                                                                     /*!< DMAMUX request generator Channel2 */
    DMAMUX_GENCH3,                                                                                                     /*!< DMAMUX request generator Channel3 */
    DMAMUX_GENCH4,                                                                                                     /*!< DMAMUX request generator Channel4 */
    DMAMUX_GENCH5,                                                                                                     /*!< DMAMUX request generator Channel5 */
    DMAMUX_GENCH6,                                                                                                     /*!< DMAMUX request generator Channel6 */
    DMAMUX_GENCH7                                                                                                      /*!< DMAMUX request generator Channel7 */
} dmamux_generator_channel_enum;

/* DMAMUX interrupt */
typedef enum {
    /* interrupts in CHxCFG register */
    DMAMUX_INT_MUXCH0_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH0CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 0 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH1_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH1CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 1 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH2_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH2CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 2 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH3_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH3CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 3 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH4_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH4CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 4 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH5_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH5CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 5 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH6_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH6CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 6 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH7_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH7CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 0 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH8_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH8CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 1 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH9_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH9CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 2 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH10_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH10CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 3 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH11_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH11CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 4 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH12_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH12CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 5 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH13_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH13CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 6 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH14_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH14CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 5 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH15_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH15CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 6 synchronization overrun interrupt */
    DMAMUX_INT_GENCH0_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH0CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request generator channel 0 trigger overrun interrupt */
    DMAMUX_INT_GENCH1_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH1CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request generator channel 1 trigger overrun interrupt */
    DMAMUX_INT_GENCH2_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH2CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request generator channel 2 trigger overrun interrupt */
    DMAMUX_INT_GENCH3_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH3CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request generator channel 3 trigger overrun interrupt */
    DMAMUX_INT_GENCH4_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH4CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request generator channel 4 trigger overrun interrupt */
    DMAMUX_INT_GENCH5_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH5CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request generator channel 5 trigger overrun interrupt */
    DMAMUX_INT_GENCH6_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH6CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request generator channel 6 trigger overrun interrupt */
    DMAMUX_INT_GENCH7_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH7CFG_REG_OFFSET, 8U)                                         /*!< DMAMUX request generator channel 7 trigger overrun interrupt */
} dmamux_interrupt_enum;

/* DMAMUX flags */
typedef enum {
    /* flags in INTF register */
    DMAMUX_FLAG_MUXCH0_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 0U),                                         /*!< DMAMUX request multiplexer channel 0 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH1_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 1U),                                         /*!< DMAMUX request multiplexer channel 1 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH2_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 2U),                                         /*!< DMAMUX request multiplexer channel 2 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH3_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 3U),                                         /*!< DMAMUX request multiplexer channel 3 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH4_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 4U),                                         /*!< DMAMUX request multiplexer channel 4 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH5_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 5U),                                         /*!< DMAMUX request multiplexer channel 5 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH6_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 6U),                                         /*!< DMAMUX request multiplexer channel 6 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH7_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 7U),                                         /*!< DMAMUX request multiplexer channel 7 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH8_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 8U),                                         /*!< DMAMUX request multiplexer channel 8 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH9_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 9U),                                         /*!< DMAMUX request multiplexer channel 9 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH10_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 10U),                                        /*!< DMAMUX request multiplexer channel 10 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH11_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 11U),                                        /*!< DMAMUX request multiplexer channel 11 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH12_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 12U),                                        /*!< DMAMUX request multiplexer channel 12 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH13_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 13U),                                        /*!< DMAMUX request multiplexer channel 13 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH14_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 14U),                                        /*!< DMAMUX request multiplexer channel 14 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH15_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 15U),                                        /*!< DMAMUX request multiplexer channel 15 synchronization overrun flag */
    DMAMUX_FLAG_GENCH0_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 0U),                                         /*!< DMAMUX request generator channel 0 trigger overrun flag */
    DMAMUX_FLAG_GENCH1_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 1U),                                         /*!< DMAMUX request generator channel 1 trigger overrun flag */
    DMAMUX_FLAG_GENCH2_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 2U),                                         /*!< DMAMUX request generator channel 2 trigger overrun flag */
    DMAMUX_FLAG_GENCH3_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 3U),                                         /*!< DMAMUX request generator channel 3 trigger overrun flag */
    DMAMUX_FLAG_GENCH4_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 4U),                                         /*!< DMAMUX request generator channel 4 trigger overrun flag */
    DMAMUX_FLAG_GENCH5_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 5U),                                         /*!< DMAMUX request generator channel 5 trigger overrun flag */
    DMAMUX_FLAG_GENCH6_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 6U),                                         /*!< DMAMUX request generator channel 6 trigger overrun flag */
    DMAMUX_FLAG_GENCH7_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 7U)                                          /*!< DMAMUX request generator channel 7 trigger overrun flag */
} dmamux_flag_enum;

/* DMAMUX interrupt flags */
typedef enum {
    /* interrupt flags in INTF register */
    DMAMUX_INT_FLAG_MUXCH0_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 0U, DMAMUX_RM_CH0CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 0 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH1_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 1U, DMAMUX_RM_CH1CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 1 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH2_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 2U, DMAMUX_RM_CH2CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 2 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH3_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 3U, DMAMUX_RM_CH3CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 3 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH4_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 4U, DMAMUX_RM_CH4CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 4 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH5_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 5U, DMAMUX_RM_CH5CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 5 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH6_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 6U, DMAMUX_RM_CH6CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 6 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH7_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 7U, DMAMUX_RM_CH7CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 7 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH8_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 8U, DMAMUX_RM_CH8CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 8 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH9_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 9U, DMAMUX_RM_CH9CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 9 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH10_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 10U, DMAMUX_RM_CH10CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 10 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH11_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 11U, DMAMUX_RM_CH11CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 11 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH12_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 12U, DMAMUX_RM_CH12CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 12 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH13_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 13U, DMAMUX_RM_CH13CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 13 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH14_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 14U, DMAMUX_RM_CH14CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 14 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH15_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 15U, DMAMUX_RM_CH15CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 15 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH0_TO  = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 0U, DMAMUX_RG_CH0CFG_REG_OFFSET, 8U),   /*!< DMAMUX request generator channel 0 trigger overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH1_TO  = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 1U, DMAMUX_RG_CH1CFG_REG_OFFSET, 8U),   /*!< DMAMUX request generator channel 1 trigger overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH2_TO  = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 2U, DMAMUX_RG_CH2CFG_REG_OFFSET, 8U),   /*!< DMAMUX request generator channel 2 trigger overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH3_TO  = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 3U, DMAMUX_RG_CH3CFG_REG_OFFSET, 8U),   /*!< DMAMUX request generator channel 3 trigger overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH4_TO  = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 4U, DMAMUX_RG_CH4CFG_REG_OFFSET, 8U),   /*!< DMAMUX request generator channel 4 trigger overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH5_TO  = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 5U, DMAMUX_RG_CH5CFG_REG_OFFSET, 8U),   /*!< DMAMUX request generator channel 5 trigger overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH6_TO  = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 6U, DMAMUX_RG_CH6CFG_REG_OFFSET, 8U),   /*!< DMAMUX request generator channel 6 trigger overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH7_TO  = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 7U, DMAMUX_RG_CH7CFG_REG_OFFSET, 8U)    /*!< DMAMUX request generator channel 7 trigger overrun interrupt flag */
} dmamux_interrupt_flag_enum;

/* DMA channel flag shift */
#define DMA_FLAG_ADD(flag,channel)        ((uint32_t)((flag)<<((((uint32_t)(channel)*6U))+((uint32_t)(((uint32_t)(channel))>>1U)&0x01U)*4U)))

/* DMA_register address */
#define DMA_CHCTL(dma,channel)            REG32(((dma) + 0x00000010U) + 0x00000018U * (channel))                       /*!< the address of DMA channel CHXCTL register  */
#define DMA_CHCNT(dma,channel)            REG32(((dma) + 0x00000014U) + 0x00000018U * (channel))                       /*!< the address of DMA channel CHXCNT register */
#define DMA_CHPADDR(dma,channel)          REG32(((dma) + 0x00000018U) + 0x00000018U * (channel))                       /*!< the address of DMA channel CHXPADDR register */
#define DMA_CHM0ADDR(dma,channel)         REG32(((dma) + 0x0000001CU) + 0x00000018U * (channel))                       /*!< the address of DMA channel CHXM0ADDR register */
#define DMA_CHM1ADDR(dma,channel)         REG32(((dma) + 0x00000020U) + 0x00000018U * (channel))                       /*!< the address of DMA channel CHXM1ADDR register */
#define DMA_CHFCTL(dma,channel)           REG32(((dma) + 0x00000024U) + 0x00000018U * (channel))                       /*!< the address of DMA channel CHXMADDR register */

/* DMAMUX_RM_CHxCFG base address */
#define DMAMUX_RM_CHXCFG_BASE             (DMAMUX)                                                                     /*!< the base address of DMAMUX request multiplexer channel CHxCFG register */

/* DMAMUX request multiplexer channel shift bit */
#define DMAMUX_RM_CHXCFG(channel)         REG32(DMAMUX_RM_CHXCFG_BASE + 0x04U * (uint32_t)(channel))                   /*!< the address of DMAMUX request multiplexer channel CHxCFG register */

/* DMAMUX_RG_CHxCFG base address */
#define DMAMUX_RG_CHXCFG_BASE             (DMAMUX + 0x00000100U)                                                       /*!< the base address of DMAMUX channel request generator CHxCFG register */

/* DMAMUX request generator channel shift bit */
#define DMAMUX_RG_CHXCFG(channel)         REG32(DMAMUX_RG_CHXCFG_BASE + 0x04U * (uint32_t)(channel))                   /*!< the address of DMAMUX channel request generator CHxCFG register */

/* burst type of memory */
#define CHCTL_MBURST(regval)              (BITS(23,24) & ((uint32_t)(regval) << 23U))
#define DMA_MEMORY_BURST_SINGLE           CHCTL_MBURST(0)                                                              /*!< single burst */
#define DMA_MEMORY_BURST_4_BEAT           CHCTL_MBURST(1)                                                              /*!< 4-beat burst */
#define DMA_MEMORY_BURST_8_BEAT           CHCTL_MBURST(2)                                                              /*!< 8-beat burst */
#define DMA_MEMORY_BURST_16_BEAT          CHCTL_MBURST(3)                                                              /*!< 16-beat burst */

/* burst type of peripheral */
#define CHCTL_PBURST(regval)              (BITS(21,22) & ((uint32_t)(regval) << 21U))
#define DMA_PERIPH_BURST_SINGLE           CHCTL_PBURST(0)                                                              /*!< single burst */
#define DMA_PERIPH_BURST_4_BEAT           CHCTL_PBURST(1)                                                              /*!< 4-beat burst */
#define DMA_PERIPH_BURST_8_BEAT           CHCTL_PBURST(2)                                                              /*!< 8-beat burst */
#define DMA_PERIPH_BURST_16_BEAT          CHCTL_PBURST(3)                                                              /*!< 16-beat burst */

/* channel priority level */
#define CHCTL_PRIO(regval)                (BITS(16,17) & ((uint32_t)(regval) << 16U))
#define DMA_PRIORITY_LOW                  CHCTL_PRIO(0)                                                                /*!< low priority */
#define DMA_PRIORITY_MEDIUM               CHCTL_PRIO(1)                                                                /*!< medium priority */
#define DMA_PRIORITY_HIGH                 CHCTL_PRIO(2)                                                                /*!< high priority */
#define DMA_PRIORITY_ULTRA_HIGH           CHCTL_PRIO(3)                                                                /*!< ultra high priority */

/* transfer data width of memory */
#define CHCTL_MWIDTH(regval)              (BITS(13,14) & ((uint32_t)(regval) << 13U))
#define DMA_MEMORY_WIDTH_8BIT             CHCTL_MWIDTH(0)                                                              /*!< transfer data width of memory is 8-bit */
#define DMA_MEMORY_WIDTH_16BIT            CHCTL_MWIDTH(1)                                                              /*!< transfer data width of memory is 16-bit */
#define DMA_MEMORY_WIDTH_32BIT            CHCTL_MWIDTH(2)                                                              /*!< transfer data width of memory is 32-bit */

/* transfer data width of peripheral */
#define CHCTL_PWIDTH(regval)              (BITS(11,12) & ((uint32_t)(regval) << 11U))
#define DMA_PERIPH_WIDTH_8BIT             CHCTL_PWIDTH(0)                                                              /*!< transfer data width of peripheral is 8-bit */
#define DMA_PERIPH_WIDTH_16BIT            CHCTL_PWIDTH(1)                                                              /*!< transfer data width of peripheral is 16-bit */
#define DMA_PERIPH_WIDTH_32BIT            CHCTL_PWIDTH(2)                                                              /*!< transfer data width of peripheral is 32-bit */

/* channel transfer mode */
#define CHCTL_TM(regval)                  (BITS(6,7) & ((uint32_t)(regval) << 6U))
#define DMA_PERIPH_TO_MEMORY              CHCTL_TM(0)                                                                  /*!< read from peripheral and write to memory */
#define DMA_MEMORY_TO_PERIPH              CHCTL_TM(1)                                                                  /*!< read from memory and write to peripheral */
#define DMA_MEMORY_TO_MEMORY              CHCTL_TM(2)                                                                  /*!< read from memory and write to memory */

/* FIFO counter critical value */
#define CHFCTL_FCCV(regval)               (BITS(0,1) & ((uint32_t)(regval) << 0U))
#define DMA_FIFO_1_WORD                   CHFCTL_FCCV(0)                                                               /*!< critical value 1 word */
#define DMA_FIFO_2_WORD                   CHFCTL_FCCV(1)                                                               /*!< critical value 2 word */
#define DMA_FIFO_3_WORD                   CHFCTL_FCCV(2)                                                               /*!< critical value 3 word */
#define DMA_FIFO_4_WORD                   CHFCTL_FCCV(3)                                                               /*!< critical value 4 word */

/* FIFO counter */
#define DMA_FIFO_CNT_NO_DATA              ((uint32_t)0x00000000U)                                                      /*!< no data */
#define DMA_FIFO_CNT_1_WORD               ((uint32_t)0x00000001U)                                                      /*!< 1 word */
#define DMA_FIFO_CNT_2_WORD               ((uint32_t)0x00000002U)                                                      /*!< 2 words */
#define DMA_FIFO_CNT_3_WORD               ((uint32_t)0x00000003U)                                                      /*!< 3 words */
#define DMA_FIFO_CNT_EMPTY                ((uint32_t)0x00000004U)                                                      /*!< empty */
#define DMA_FIFO_CNT_FULL                 ((uint32_t)0x00000005U)                                                      /*!< full */

/* memory select */
#define DMA_MEMORY_0                      ((uint32_t)0x00000000U)                                                      /*!< select memory 0 */
#define DMA_MEMORY_1                      ((uint32_t)0x00000001U)                                                      /*!< select memory 1 */

/* DMA circular mode */
#define DMA_CIRCULAR_MODE_ENABLE          ((uint32_t)0x00000000U)                                                      /*!< circular mode enable */
#define DMA_CIRCULAR_MODE_DISABLE         ((uint32_t)0x00000001U)                                                      /*!< circular mode disable */

/* DMA flow controller select */
#define DMA_FLOW_CONTROLLER_DMA           ((uint32_t)0x00000000U)                                                      /*!< DMA is the flow controler */
#define DMA_FLOW_CONTROLLER_PERI          ((uint32_t)0x00000001U)                                                      /*!< peripheral is the flow controler */

/* peripheral increasing mode */
#define DMA_PERIPH_INCREASE_ENABLE        ((uint32_t)0x00000000U)                                                      /*!< next address of peripheral is increasing address mode */
#define DMA_PERIPH_INCREASE_DISABLE       ((uint32_t)0x00000001U)                                                      /*!< next address of peripheral is fixed address mode */
#define DMA_PERIPH_INCREASE_FIX           ((uint32_t)0x00000002U)                                                      /*!< next address of peripheral is increasing fixed */

/* memory increasing mode */
#define DMA_MEMORY_INCREASE_ENABLE        ((uint32_t)0x00000000U)                                                      /*!< next address of memory is increasing address mode */
#define DMA_MEMORY_INCREASE_DISABLE       ((uint32_t)0x00000001U)                                                      /*!< next address of memory is fixed address mode */

/* FIFO status */
#define DMA_FIFO_STATUS_NODATA            ((uint32_t)0x00000000U)                                                      /*!< the data in the FIFO less than 1 word */
#define DMA_FIFO_STATUS_1_WORD            ((uint32_t)0x00000001U)                                                      /*!< the data in the FIFO more than 1 word, less than 2 words */
#define DMA_FIFO_STATUS_2_WORD            ((uint32_t)0x00000002U)                                                      /*!< the data in the FIFO more than 2 word, less than 3 words */
#define DMA_FIFO_STATUS_3_WORD            ((uint32_t)0x00000003U)                                                      /*!< the data in the FIFO more than 3 word, less than 4 words */
#define DMA_FIFO_STATUS_EMPTY             ((uint32_t)0x00000004U)                                                      /*!< the data in the FIFO is empty */
#define DMA_FIFO_STATUS_FULL              ((uint32_t)0x00000005U)                                                      /*!< the data in the FIFO is full */

/* DMA reset value */
#define DMA_CHCTL_RESET_VALUE             ((uint32_t)0x00000000U)                                                      /*!< the reset value of DMA channel CHXCTL register */
#define DMA_CHCNT_RESET_VALUE             ((uint32_t)0x00000000U)                                                      /*!< the reset value of DMA channel CHXCNT register */
#define DMA_CHPADDR_RESET_VALUE           ((uint32_t)0x00000000U)                                                      /*!< the reset value of DMA channel CHXPADDR register */
#define DMA_CHMADDR_RESET_VALUE           ((uint32_t)0x00000000U)                                                      /*!< the reset value of DMA channel CHXMADDR register */
#define DMA_CHINTF_RESET_VALUE            ((uint32_t)0x0000003DU)                                                      /*!< clear DMA channel CHXINTFS register */
#define DMA_CHFCTL_RESET_VALUE            ((uint32_t)0x00000000U)                                                      /*!< the reset value of DMA channel CHXFCTL register */

/* flag bits */
#define DMA_FLAG_FEE                      DMA_INTF_FEEIF                                                               /*!< FIFO error and exception flag */
#define DMA_FLAG_SDE                      DMA_INTF_SDEIF                                                               /*!< single data mode exception flag */
#define DMA_FLAG_TAE                      DMA_INTF_TAEIF                                                               /*!< transfer access error flag */
#define DMA_FLAG_HTF                      DMA_INTF_HTFIF                                                               /*!< half transfer finish flag */
#define DMA_FLAG_FTF                      DMA_INTF_FTFIF                                                               /*!< full transfer finish flag */

/* DMA interrupt flag bits */
#define DMA_INT_FLAG_FEE                  DMA_INTF_FEEIF                                                               /*!< FIFO error and exception flag */
#define DMA_INT_FLAG_SDE                  DMA_INTF_SDEIF                                                               /*!< single data mode exception flag */
#define DMA_INT_FLAG_TAE                  DMA_INTF_TAEIF                                                               /*!< transfer access error flag */
#define DMA_INT_FLAG_HTF                  DMA_INTF_HTFIF                                                               /*!< half transfer finish flag */
#define DMA_INT_FLAG_FTF                  DMA_INTF_FTFIF                                                               /*!< full transfer finish flag */

/* DMA interrupt */
#define DMA_INT_SDE                       DMA_CHXCTL_SDEIE                                                             /*!< single data mode exception interrupt */
#define DMA_INT_TAE                       DMA_CHXCTL_TAEIE                                                             /*!< tranfer access error interrupt */
#define DMA_INT_HTF                       DMA_CHXCTL_HTFIE                                                             /*!< half transfer finish interrupt */
#define DMA_INT_FTF                       DMA_CHXCTL_FTFIE                                                             /*!< full transfer finish interrupt */
#define DMA_INT_FEE                       DMA_CHXFCTL_FEEIE                                                            /*!< FIFO exception interrupt */

/* DMAMUX request multiplexer channel input identification */
#define RM_CHXCFG_MUXID(regval)           (BITS(0,7) & ((uint32_t)(regval) << 0U))                                     /*!< multiplexer input identification */
#define DMA_REQUEST_M2M                   RM_CHXCFG_MUXID(0U)                                                          /*!< memory to memory transfer */
#define DMA_REQUEST_GENERATOR0            RM_CHXCFG_MUXID(1U)                                                          /*!< DMAMUX request generator 0 */
#define DMA_REQUEST_GENERATOR1            RM_CHXCFG_MUXID(2U)                                                          /*!< DMAMUX request generator 1 */
#define DMA_REQUEST_GENERATOR2            RM_CHXCFG_MUXID(3U)                                                          /*!< DMAMUX request generator 2 */
#define DMA_REQUEST_GENERATOR3            RM_CHXCFG_MUXID(4U)                                                          /*!< DMAMUX request generator 3 */
#define DMA_REQUEST_GENERATOR4            RM_CHXCFG_MUXID(5U)                                                          /*!< DMAMUX request generator 4 */
#define DMA_REQUEST_GENERATOR5            RM_CHXCFG_MUXID(6U)                                                          /*!< DMAMUX request generator 5 */
#define DMA_REQUEST_GENERATOR6            RM_CHXCFG_MUXID(7U)                                                          /*!< DMAMUX request generator 6 */
#define DMA_REQUEST_GENERATOR7            RM_CHXCFG_MUXID(8U)                                                          /*!< DMAMUX request generator 7 */
#define DMA_REQUEST_ADC0                  RM_CHXCFG_MUXID(9U)                                                          /*!< DMAMUX ADC0 request */
#define DMA_REQUEST_ADC1                  RM_CHXCFG_MUXID(10U)                                                         /*!< DMAMUX ADC1 request */
#define DMA_REQUEST_TIMER0_CH0            RM_CHXCFG_MUXID(11U)                                                         /*!< DMAMUX TIMER0 CH0 request */
#define DMA_REQUEST_TIMER0_CH1            RM_CHXCFG_MUXID(12U)                                                         /*!< DMAMUX TIMER0 CH1 request */
#define DMA_REQUEST_TIMER0_CH2            RM_CHXCFG_MUXID(13U)                                                         /*!< DMAMUX TIMER0 CH2 request */
#define DMA_REQUEST_TIMER0_CH3            RM_CHXCFG_MUXID(14U)                                                         /*!< DMAMUX TIMER0 CH3 request */
#define DMA_REQUEST_TIMER0_MCH0           RM_CHXCFG_MUXID(15U)                                                         /*!< DMAMUX TIMER0 MCH0 request */
#define DMA_REQUEST_TIMER0_MCH1           RM_CHXCFG_MUXID(16U)                                                         /*!< DMAMUX TIMER0 MCH1 request */
#define DMA_REQUEST_TIMER0_MCH2           RM_CHXCFG_MUXID(17U)                                                         /*!< DMAMUX TIMER0 MCH2 request */
#define DMA_REQUEST_TIMER0_MCH3           RM_CHXCFG_MUXID(18U)                                                         /*!< DMAMUX TIMER0 MCH3 request */
#define DMA_REQUEST_TIMER0_UP             RM_CHXCFG_MUXID(19U)                                                         /*!< DMAMUX TIMER0 UP request */
#define DMA_REQUEST_TIMER0_TRG            RM_CHXCFG_MUXID(20U)                                                         /*!< DMAMUX TIMER0 TRG request */
#define DMA_REQUEST_TIMER0_CMT            RM_CHXCFG_MUXID(21U)                                                         /*!< DMAMUX TIMER0 CMT request */
#define DMA_REQUEST_TIMER1_CH0            RM_CHXCFG_MUXID(22U)                                                         /*!< DMAMUX TIMER1 CH0 request */
#define DMA_REQUEST_TIMER1_CH1            RM_CHXCFG_MUXID(23U)                                                         /*!< DMAMUX TIMER1 CH1 request */
#define DMA_REQUEST_TIMER1_CH2            RM_CHXCFG_MUXID(24U)                                                         /*!< DMAMUX TIMER1 CH2 request */
#define DMA_REQUEST_TIMER1_CH3            RM_CHXCFG_MUXID(25U)                                                         /*!< DMAMUX TIMER1 CH3 request */
#define DMA_REQUEST_TIMER1_UP             RM_CHXCFG_MUXID(26U)                                                         /*!< DMAMUX TIMER1 UP request */
#define DMA_REQUEST_TIMER1_TRG            RM_CHXCFG_MUXID(27U)                                                         /*!< DMAMUX TIMER1 TRG request */
#define DMA_REQUEST_TIMER2_CH0            RM_CHXCFG_MUXID(29U)                                                         /*!< DMAMUX TIMER2 CH0 request */
#define DMA_REQUEST_TIMER2_CH1            RM_CHXCFG_MUXID(30U)                                                         /*!< DMAMUX TIMER2 CH1 request */
#define DMA_REQUEST_TIMER2_CH2            RM_CHXCFG_MUXID(31U)                                                         /*!< DMAMUX TIMER2 CH2 request */
#define DMA_REQUEST_TIMER2_CH3            RM_CHXCFG_MUXID(32U)                                                         /*!< DMAMUX TIMER2 CH3 request */
#define DMA_REQUEST_TIMER2_UP             RM_CHXCFG_MUXID(33U)                                                         /*!< DMAMUX TIMER2 UP request */
#define DMA_REQUEST_TIMER2_TRG            RM_CHXCFG_MUXID(35U)                                                         /*!< DMAMUX TIMER2 TRG request */
#define DMA_REQUEST_TIMER3_CH0            RM_CHXCFG_MUXID(36U)                                                         /*!< DMAMUX TIMER3 CH0 request */
#define DMA_REQUEST_TIMER3_CH1            RM_CHXCFG_MUXID(37U)                                                         /*!< DMAMUX TIMER3 CH1 request */
#define DMA_REQUEST_TIMER3_CH2            RM_CHXCFG_MUXID(38U)                                                         /*!< DMAMUX TIMER3 CH2 request */
#define DMA_REQUEST_TIMER3_CH3            RM_CHXCFG_MUXID(39U)                                                         /*!< DMAMUX TIMER3 CH3 request */
#define DMA_REQUEST_TIMER3_TRG            RM_CHXCFG_MUXID(41U)                                                         /*!< DMAMUX TIMER3 TRG request */
#define DMA_REQUEST_TIMER3_UP             RM_CHXCFG_MUXID(42U)                                                         /*!< DMAMUX TIMER3 UP request */
#define DMA_REQUEST_I2C0_RX               RM_CHXCFG_MUXID(43U)                                                         /*!< DMAMUX I2C0 RX request */
#define DMA_REQUEST_I2C0_TX               RM_CHXCFG_MUXID(44U)                                                         /*!< DMAMUX I2C0 TX request */
#define DMA_REQUEST_I2C1_RX               RM_CHXCFG_MUXID(45U)                                                         /*!< DMAMUX I2C1 RX request */
#define DMA_REQUEST_I2C1_TX               RM_CHXCFG_MUXID(46U)                                                         /*!< DMAMUX I2C1 TX request */
#define DMA_REQUEST_SPI0_RX               RM_CHXCFG_MUXID(47U)                                                         /*!< DMAMUX SPI0 RX request */
#define DMA_REQUEST_SPI0_TX               RM_CHXCFG_MUXID(48U)                                                         /*!< DMAMUX SPI0 TX request */
#define DMA_REQUEST_SPI1_RX               RM_CHXCFG_MUXID(49U)                                                         /*!< DMAMUX SPI1 RX request */
#define DMA_REQUEST_SPI1_TX               RM_CHXCFG_MUXID(50U)                                                         /*!< DMAMUX SPI1 TX request */
#define DMA_REQUEST_USART0_RX             RM_CHXCFG_MUXID(51U)                                                         /*!< DMAMUX USART0 RX request */
#define DMA_REQUEST_USART0_TX             RM_CHXCFG_MUXID(52U)                                                         /*!< DMAMUX USART0 TX request */
#define DMA_REQUEST_USART1_RX             RM_CHXCFG_MUXID(53U)                                                         /*!< DMAMUX USART1 RX request */
#define DMA_REQUEST_USART1_TX             RM_CHXCFG_MUXID(54U)                                                         /*!< DMAMUX USART1 TX request */
#define DMA_REQUEST_USART2_RX             RM_CHXCFG_MUXID(55U)                                                         /*!< DMAMUX USART2 RX request */
#define DMA_REQUEST_USART2_TX             RM_CHXCFG_MUXID(56U)                                                         /*!< DMAMUX USART2 TX request */
#define DMA_REQUEST_TIMER7_CH0            RM_CHXCFG_MUXID(57U)                                                         /*!< DMAMUX TIMER7 CH0 request */
#define DMA_REQUEST_TIMER7_CH1            RM_CHXCFG_MUXID(58U)                                                         /*!< DMAMUX TIMER7 CH1 request */
#define DMA_REQUEST_TIMER7_CH2            RM_CHXCFG_MUXID(59U)                                                         /*!< DMAMUX TIMER7 CH2 request */
#define DMA_REQUEST_TIMER7_CH3            RM_CHXCFG_MUXID(60U)                                                         /*!< DMAMUX TIMER7 CH3 request */
#define DMA_REQUEST_TIMER7_MCH0           RM_CHXCFG_MUXID(61U)                                                         /*!< DMAMUX TIMER7 MCH0 request */
#define DMA_REQUEST_TIMER7_MCH1           RM_CHXCFG_MUXID(62U)                                                         /*!< DMAMUX TIMER7 MCH1 request */
#define DMA_REQUEST_TIMER7_MCH2           RM_CHXCFG_MUXID(63U)                                                         /*!< DMAMUX TIMER7 MCH2 request */
#define DMA_REQUEST_TIMER7_MCH3           RM_CHXCFG_MUXID(64U)                                                         /*!< DMAMUX TIMER7 MCH3 request */
#define DMA_REQUEST_TIMER7_UP             RM_CHXCFG_MUXID(65U)                                                         /*!< DMAMUX TIMER7 UP request */
#define DMA_REQUEST_TIMER7_TRG            RM_CHXCFG_MUXID(66U)                                                         /*!< DMAMUX TIMER7 TRG request */
#define DMA_REQUEST_TIMER7_CMT            RM_CHXCFG_MUXID(67U)                                                         /*!< DMAMUX TIMER7 CMT request */
#define DMA_REQUEST_TIMER4_CH0            RM_CHXCFG_MUXID(68U)                                                         /*!< DMAMUX TIMER4 CH0 request */
#define DMA_REQUEST_TIMER4_CH1            RM_CHXCFG_MUXID(69U)                                                         /*!< DMAMUX TIMER4 CH1 request */
#define DMA_REQUEST_TIMER4_CH2            RM_CHXCFG_MUXID(70U)                                                         /*!< DMAMUX TIMER4 CH2 request */
#define DMA_REQUEST_TIMER4_CH3            RM_CHXCFG_MUXID(71U)                                                         /*!< DMAMUX TIMER4 CH3 request */
#define DMA_REQUEST_TIMER4_UP             RM_CHXCFG_MUXID(72U)                                                         /*!< DMAMUX TIMER4 UP request */
#define DMA_REQUEST_TIMER4_CMT            RM_CHXCFG_MUXID(73U)                                                         /*!< DMAMUX TIMER4 CMT request */
#define DMA_REQUEST_TIMER4_TRG            RM_CHXCFG_MUXID(74U)                                                         /*!< DMAMUX TIMER4 TRG request */
#define DMA_REQUEST_SPI2_RX               RM_CHXCFG_MUXID(75U)                                                         /*!< DMAMUX SPI2 RX request */
#define DMA_REQUEST_SPI2_TX               RM_CHXCFG_MUXID(76U)                                                         /*!< DMAMUX SPI2 TX request */
#define DMA_REQUEST_UART3_RX              RM_CHXCFG_MUXID(77U)                                                         /*!< DMAMUX UART3 RX request */
#define DMA_REQUEST_UART3_TX              RM_CHXCFG_MUXID(78U)                                                         /*!< DMAMUX UART3 TX request */
#define DMA_REQUEST_UART4_RX              RM_CHXCFG_MUXID(79U)                                                         /*!< DMAMUX UART4 RX request */
#define DMA_REQUEST_UART4_TX              RM_CHXCFG_MUXID(80U)                                                         /*!< DMAMUX UART4 TX request */
#define DMA_REQUEST_DAC_CH0               RM_CHXCFG_MUXID(81U)                                                         /*!< DMAMUX DAC CH0 request */
#define DMA_REQUEST_DAC_CH1               RM_CHXCFG_MUXID(82U)                                                         /*!< DMAMUX DAC CH1 request */
#define DMA_REQUEST_TIMER5_UP             RM_CHXCFG_MUXID(83U)                                                         /*!< DMAMUX TIMER5 UP request */
#define DMA_REQUEST_TIMER6_UP             RM_CHXCFG_MUXID(84U)                                                         /*!< DMAMUX TIMER6 UP request */
#define DMA_REQUEST_USART5_RX             RM_CHXCFG_MUXID(85U)                                                         /*!< DMAMUX USART5 RX request */
#define DMA_REQUEST_USART5_TX             RM_CHXCFG_MUXID(86U)                                                         /*!< DMAMUX USART5 TX request */
#define DMA_REQUEST_I2C2_RX               RM_CHXCFG_MUXID(87U)                                                         /*!< DMAMUX I2C2 RX request */
#define DMA_REQUEST_I2C2_TX               RM_CHXCFG_MUXID(88U)                                                         /*!< DMAMUX I2C2 TX request */
#define DMA_REQUEST_DCI                   RM_CHXCFG_MUXID(89U)                                                         /*!< DMAMUX DCI request */
#define DMA_REQUEST_CAU_IN                RM_CHXCFG_MUXID(90U)                                                         /*!< DMAMUX CAU IN request */
#define DMA_REQUEST_CAU_OUT               RM_CHXCFG_MUXID(91U)                                                         /*!< DMAMUX CAU OUT request */
#define DMA_REQUEST_HAU_IN                RM_CHXCFG_MUXID(92U)                                                         /*!< DMAMUX HAU IN request */
#define DMA_REQUEST_UART6_RX              RM_CHXCFG_MUXID(93U)                                                         /*!< DMAMUX UART6 RX request */
#define DMA_REQUEST_UART6_TX              RM_CHXCFG_MUXID(94U)                                                         /*!< DMAMUX UART6 TX request */
#define DMA_REQUEST_UART7_RX              RM_CHXCFG_MUXID(95U)                                                         /*!< DMAMUX UART7 RX request */
#define DMA_REQUEST_UART7_TX              RM_CHXCFG_MUXID(96U)                                                         /*!< DMAMUX UART7 TX request */
#define DMA_REQUEST_SPI3_RX               RM_CHXCFG_MUXID(97U)                                                         /*!< DMAMUX SPI3 RX request */
#define DMA_REQUEST_SPI3_TX               RM_CHXCFG_MUXID(98U)                                                         /*!< DMAMUX SPI3 TX request */
#define DMA_REQUEST_SPI4_RX               RM_CHXCFG_MUXID(99U)                                                         /*!< DMAMUX SPI4 RX request */
#define DMA_REQUEST_SPI4_TX               RM_CHXCFG_MUXID(100U)                                                        /*!< DMAMUX SPI4 TX request */
#define DMA_REQUEST_SAI0_B0               RM_CHXCFG_MUXID(101U)                                                        /*!< DMAMUX SAI0 B0 request */
#define DMA_REQUEST_SAI0_B1               RM_CHXCFG_MUXID(102U)                                                        /*!< DMAMUX SAI0 B1 request */
#define DMA_REQUEST_RSPDIF_DATA           RM_CHXCFG_MUXID(103U)                                                        /*!< DMAMUX RSPDIF DATA request */
#define DMA_REQUEST_RSPDIF_CS             RM_CHXCFG_MUXID(104U)                                                        /*!< DMAMUX RSPDIF CS request */
#define DMA_REQUEST_HPDF_FLT0             RM_CHXCFG_MUXID(105U)                                                        /*!< DMAMUX HPDF FLT0 request */
#define DMA_REQUEST_HPDF_FLT1             RM_CHXCFG_MUXID(106U)                                                        /*!< DMAMUX HPDF FLT1 request */
#define DMA_REQUEST_HPDF_FLT2             RM_CHXCFG_MUXID(107U)                                                        /*!< DMAMUX HPDF FLT2 request */
#define DMA_REQUEST_HPDF_FLT3             RM_CHXCFG_MUXID(108U)                                                        /*!< DMAMUX HPDF FLT3 request */
#define DMA_REQUEST_TIMER14_CH0           RM_CHXCFG_MUXID(109U)                                                        /*!< DMAMUX TIMER14 CH0 request */
#define DMA_REQUEST_TIMER14_CH1           RM_CHXCFG_MUXID(110U)                                                        /*!< DMAMUX TIMER14 CH1 request */
#define DMA_REQUEST_TIMER14_MCH0          RM_CHXCFG_MUXID(111U)                                                        /*!< DMAMUX TIMER14 MCH0 request */
#define DMA_REQUEST_TIMER14_UP            RM_CHXCFG_MUXID(112U)                                                        /*!< DMAMUX TIMER14 UP request */
#define DMA_REQUEST_TIMER14_TRG           RM_CHXCFG_MUXID(113U)                                                        /*!< DMAMUX TIMER14 TRG request */
#define DMA_REQUEST_TIMER14_CMT           RM_CHXCFG_MUXID(114U)                                                        /*!< DMAMUX TIMER14 CMT request */
#define DMA_REQUEST_TIMER15_CH0           RM_CHXCFG_MUXID(115U)                                                        /*!< DMAMUX TIMER15 CH0 request */
#define DMA_REQUEST_TIMER15_MCH0          RM_CHXCFG_MUXID(116U)                                                        /*!< DMAMUX TIMER15 MCH0 request */
#define DMA_REQUEST_TIMER15_UP            RM_CHXCFG_MUXID(118U)                                                        /*!< DMAMUX TIMER15 UP request */
#define DMA_REQUEST_TIMER16_CH0           RM_CHXCFG_MUXID(119U)                                                        /*!< DMAMUX TIMER16 CH0 request */
#define DMA_REQUEST_TIMER16_MCH0          RM_CHXCFG_MUXID(120U)                                                        /*!< DMAMUX TIMER16 MCH0 request */
#define DMA_REQUEST_TIMER16_UP            RM_CHXCFG_MUXID(122U)                                                        /*!< DMAMUX TIMER16 TRG request */
#define DMA_REQUEST_ADC2                  RM_CHXCFG_MUXID(123U)                                                        /*!< DMAMUX ADC2 request */
#define DMA_REQUEST_FAC_READ              RM_CHXCFG_MUXID(124U)                                                        /*!< DMAMUX FAC READ request */
#define DMA_REQUEST_FAC_WRITE             RM_CHXCFG_MUXID(125U)                                                        /*!< DMAMUX FAC WRITE request */
#define DMA_REQUEST_TMU_INPUT             RM_CHXCFG_MUXID(126U)                                                        /*!< DMAMUX TMU INPUT request */
#define DMA_REQUEST_TMU_OUTPUT            RM_CHXCFG_MUXID(127U)                                                        /*!< DMAMUX TMU OUTPUT request */
#define DMA_REQUEST_TIMER22_CH0           RM_CHXCFG_MUXID(128U)                                                        /*!< DMAMUX TIMER22 CH0 request */
#define DMA_REQUEST_TIMER22_CH1           RM_CHXCFG_MUXID(129U)                                                        /*!< DMAMUX TIMER22 CH1 request */
#define DMA_REQUEST_TIMER22_CH2           RM_CHXCFG_MUXID(130U)                                                        /*!< DMAMUX TIMER22 CH2 request */
#define DMA_REQUEST_TIMER22_CH3           RM_CHXCFG_MUXID(131U)                                                        /*!< DMAMUX TIMER22 CH3 request */
#define DMA_REQUEST_TIMER22_UP            RM_CHXCFG_MUXID(132U)                                                        /*!< DMAMUX TIMER22 UP request */
#define DMA_REQUEST_TIMER22_TRG           RM_CHXCFG_MUXID(134U)                                                        /*!< DMAMUX TIMER22 TRG request */
#define DMA_REQUEST_TIMER23_CH0           RM_CHXCFG_MUXID(135U)                                                        /*!< DMAMUX TIMER23 CH0 request */
#define DMA_REQUEST_TIMER23_CH1           RM_CHXCFG_MUXID(136U)                                                        /*!< DMAMUX TIMER23 CH1 request */
#define DMA_REQUEST_TIMER23_CH2           RM_CHXCFG_MUXID(137U)                                                        /*!< DMAMUX TIMER23 CH2 request */
#define DMA_REQUEST_TIMER23_CH3           RM_CHXCFG_MUXID(138U)                                                        /*!< DMAMUX TIMER23 CH3 request */
#define DMA_REQUEST_TIMER23_UP            RM_CHXCFG_MUXID(139U)                                                        /*!< DMAMUX TIMER23 UP request */
#define DMA_REQUEST_TIMER23_TRG           RM_CHXCFG_MUXID(141U)                                                        /*!< DMAMUX TIMER23 TRG request */
#define DMA_REQUEST_TIMER30_CH0           RM_CHXCFG_MUXID(142U)                                                        /*!< DMAMUX TIMER30 CH0 request */
#define DMA_REQUEST_TIMER30_CH1           RM_CHXCFG_MUXID(143U)                                                        /*!< DMAMUX TIMER30 CH1 request */
#define DMA_REQUEST_TIMER30_CH2           RM_CHXCFG_MUXID(144U)                                                        /*!< DMAMUX TIMER30 CH2 request */
#define DMA_REQUEST_TIMER30_CH3           RM_CHXCFG_MUXID(145U)                                                        /*!< DMAMUX TIMER30 CH3 request */
#define DMA_REQUEST_TIMER30_UP            RM_CHXCFG_MUXID(146U)                                                        /*!< DMAMUX TIMER30 UP request */
#define DMA_REQUEST_TIMER30_TRG           RM_CHXCFG_MUXID(148U)                                                        /*!< DMAMUX TIMER30 TRG request */
#define DMA_REQUEST_TIMER31_CH0           RM_CHXCFG_MUXID(149U)                                                        /*!< DMAMUX TIMER31 CH0 request */
#define DMA_REQUEST_TIMER31_CH1           RM_CHXCFG_MUXID(150U)                                                        /*!< DMAMUX TIMER31 CH1 request */
#define DMA_REQUEST_TIMER31_CH2           RM_CHXCFG_MUXID(151U)                                                        /*!< DMAMUX TIMER31 CH2 request */
#define DMA_REQUEST_TIMER31_CH3           RM_CHXCFG_MUXID(152U)                                                        /*!< DMAMUX TIMER31 CH3 request */
#define DMA_REQUEST_TIMER31_UP            RM_CHXCFG_MUXID(154U)                                                        /*!< DMAMUX TIMER31 UP request */
#define DMA_REQUEST_TIMER31_TRG           RM_CHXCFG_MUXID(155U)                                                        /*!< DMAMUX TIMER31 TRG request */
#define DMA_REQUEST_TIMER40_CH0           RM_CHXCFG_MUXID(156U)                                                        /*!< DMAMUX TIMER40 CH0 request */
#define DMA_REQUEST_TIMER40_MCH0          RM_CHXCFG_MUXID(157U)                                                        /*!< DMAMUX TIMER40 MCH0 request */
#define DMA_REQUEST_TIMER40_CMT           RM_CHXCFG_MUXID(158U)                                                        /*!< DMAMUX TIMER40 CMT request */
#define DMA_REQUEST_TIMER40_UP            RM_CHXCFG_MUXID(159U)                                                        /*!< DMAMUX TIMER40 UP request */
#define DMA_REQUEST_TIMER41_CH0           RM_CHXCFG_MUXID(160U)                                                        /*!< DMAMUX TIMER41 CH0 request */
#define DMA_REQUEST_TIMER41_MCH0          RM_CHXCFG_MUXID(161U)                                                        /*!< DMAMUX TIMER41 MCH0 request */
#define DMA_REQUEST_TIMER41_CMT           RM_CHXCFG_MUXID(162U)                                                        /*!< DMAMUX TIMER41 CMT request */
#define DMA_REQUEST_TIMER41_UP            RM_CHXCFG_MUXID(163U)                                                        /*!< DMAMUX TIMER41 UP request */
#define DMA_REQUEST_TIMER42_CH0           RM_CHXCFG_MUXID(164U)                                                        /*!< DMAMUX TIMER42 CH0 request */
#define DMA_REQUEST_TIMER42_MCH0          RM_CHXCFG_MUXID(165U)                                                        /*!< DMAMUX TIMER42 MCH0 request */
#define DMA_REQUEST_TIMER42_CMT           RM_CHXCFG_MUXID(166U)                                                        /*!< DMAMUX TIMER42 CMT request */
#define DMA_REQUEST_TIMER42_UP            RM_CHXCFG_MUXID(167U)                                                        /*!< DMAMUX TIMER42 UP request */
#define DMA_REQUEST_TIMER43_CH0           RM_CHXCFG_MUXID(168U)                                                        /*!< DMAMUX TIMER43 CH0 request */
#define DMA_REQUEST_TIMER43_MCH0          RM_CHXCFG_MUXID(169U)                                                        /*!< DMAMUX TIMER43 MCH0 request */
#define DMA_REQUEST_TIMER43_CMT           RM_CHXCFG_MUXID(170U)                                                        /*!< DMAMUX TIMER43 CMT request */
#define DMA_REQUEST_TIMER43_UP            RM_CHXCFG_MUXID(171U)                                                        /*!< DMAMUX TIMER43 UP request */
#define DMA_REQUEST_TIMER44_CH0           RM_CHXCFG_MUXID(172U)                                                        /*!< DMAMUX TIMER44 CH0 request */
#define DMA_REQUEST_TIMER44_MCH0          RM_CHXCFG_MUXID(173U)                                                        /*!< DMAMUX TIMER44 MCH0 request */
#define DMA_REQUEST_TIMER44_CMT           RM_CHXCFG_MUXID(174U)                                                        /*!< DMAMUX TIMER44 CMT request */
#define DMA_REQUEST_TIMER44_UP            RM_CHXCFG_MUXID(175U)                                                        /*!< DMAMUX TIMER44 UP request */
#define DMA_REQUEST_TIMER50_UP            RM_CHXCFG_MUXID(176U)                                                        /*!< DMAMUX TIMER50 UP request */
#define DMA_REQUEST_TIMER51_UP            RM_CHXCFG_MUXID(177U)                                                        /*!< DMAMUX TIMER51 UP request */
#define DMA_REQUEST_SAI1_B0               RM_CHXCFG_MUXID(178U)                                                        /*!< DMAMUX SAI1 B0 request */
#define DMA_REQUEST_SAI1_B1               RM_CHXCFG_MUXID(179U)                                                        /*!< DMAMUX SAI1 B1 request */
#define DMA_REQUEST_SAI2_B0               RM_CHXCFG_MUXID(180U)                                                        /*!< DMAMUX SAI2 B0 request */
#define DMA_REQUEST_SAI2_B1               RM_CHXCFG_MUXID(181U)                                                        /*!< DMAMUX SAI2 B1 request */
#define DMA_REQUEST_SPI5_RX               RM_CHXCFG_MUXID(182U)                                                        /*!< DMAMUX SPI5 RX request */
#define DMA_REQUEST_SPI5_TX               RM_CHXCFG_MUXID(183U)                                                        /*!< DMAMUX SPI5 TX request */
#define DMA_REQUEST_I2C3_RX               RM_CHXCFG_MUXID(184U)                                                        /*!< DMAMUX I2C3 RX request */
#define DMA_REQUEST_I2C3_TX               RM_CHXCFG_MUXID(185U)                                                        /*!< DMAMUX I2C3 TX request */
#define DMA_REQUEST_CAN0                  RM_CHXCFG_MUXID(186U)                                                        /*!< DMAMUX CAN0 request */
#define DMA_REQUEST_CAN1                  RM_CHXCFG_MUXID(187U)                                                        /*!< DMAMUX CAN1 request */
#define DMA_REQUEST_CAN2                  RM_CHXCFG_MUXID(188U)                                                        /*!< DMAMUX CAN2 request */
#define DMA_REQUEST_TIMER40_CH1           RM_CHXCFG_MUXID(189U)                                                        /*!< DMAMUX TIMER40 CH1 request */
#define DMA_REQUEST_TIMER40_TRG           RM_CHXCFG_MUXID(190U)                                                        /*!< DMAMUX TIMER40 TRG request */
#define DMA_REQUEST_TIMER41_CH1           RM_CHXCFG_MUXID(191U)                                                        /*!< DMAMUX TIMER41 CH1 request */
#define DMA_REQUEST_TIMER41_TRG           RM_CHXCFG_MUXID(192U)                                                        /*!< DMAMUX TIMER41 TRG request */
#define DMA_REQUEST_TIMER42_CH1           RM_CHXCFG_MUXID(193U)                                                        /*!< DMAMUX TIMER42 CH1 request */
#define DMA_REQUEST_TIMER42_TRG           RM_CHXCFG_MUXID(194U)                                                        /*!< DMAMUX TIMER42 TRG request */
#define DMA_REQUEST_TIMER43_CH1           RM_CHXCFG_MUXID(195U)                                                        /*!< DMAMUX TIMER43 CH1 request */
#define DMA_REQUEST_TIMER43_TRG           RM_CHXCFG_MUXID(196U)                                                        /*!< DMAMUX TIMER43 TRG request */
#define DMA_REQUEST_TIMER44_CH1           RM_CHXCFG_MUXID(197U)                                                        /*!< DMAMUX TIMER44 CH1 request */
#define DMA_REQUEST_TIMER44_TRG           RM_CHXCFG_MUXID(198U)                                                        /*!< DMAMUX TIMER44 TRG request */

/* DMAMUX request generator trigger input identification */
#define RG_CHXCFG_TID(regval)             (BITS(0,5) & ((uint32_t)(regval) << 0U))                                     /*!< trigger input identification */
#define DMAMUX_TRIGGER_EVT0_OUT           RG_CHXCFG_TID(0U)                                                            /*!< trigger input is Evt0_out */
#define DMAMUX_TRIGGER_EVT1_OUT           RG_CHXCFG_TID(1U)                                                            /*!< trigger input is Evt1_out */
#define DMAMUX_TRIGGER_EVT2_OUT           RG_CHXCFG_TID(2U)                                                            /*!< trigger input is Evt2_out */
#define DMAMUX_TRIGGER_EVT3_OUT           RG_CHXCFG_TID(3U)                                                            /*!< trigger input is Evt3_out */
#define DMAMUX_TRIGGER_EVT4_OUT           RG_CHXCFG_TID(4U)                                                            /*!< trigger input is Evt4_out */
#define DMAMUX_TRIGGER_EVT5_OUT           RG_CHXCFG_TID(5U)                                                            /*!< trigger input is Evt5_out */
#define DMAMUX_TRIGGER_EVT6_OUT           RG_CHXCFG_TID(6U)                                                            /*!< trigger input is Evt6_out */
#define DMAMUX_TRIGGER_EXTI0              RG_CHXCFG_TID(7U)                                                            /*!< trigger input is EXTI0 */
#define DMAMUX_TRIGGER_EXTI1              RG_CHXCFG_TID(8U)                                                            /*!< trigger input is EXTI1 */
#define DMAMUX_TRIGGER_EXTI2              RG_CHXCFG_TID(9U)                                                            /*!< trigger input is EXTI2 */
#define DMAMUX_TRIGGER_EXTI3              RG_CHXCFG_TID(10U)                                                           /*!< trigger input is EXTI3 */
#define DMAMUX_TRIGGER_EXTI4              RG_CHXCFG_TID(11U)                                                           /*!< trigger input is EXTI4 */
#define DMAMUX_TRIGGER_EXTI5              RG_CHXCFG_TID(12U)                                                           /*!< trigger input is EXTI5 */
#define DMAMUX_TRIGGER_EXTI6              RG_CHXCFG_TID(13U)                                                           /*!< trigger input is EXTI6 */
#define DMAMUX_TRIGGER_EXTI7              RG_CHXCFG_TID(14U)                                                           /*!< trigger input is EXTI7 */
#define DMAMUX_TRIGGER_EXTI8              RG_CHXCFG_TID(15U)                                                           /*!< trigger input is EXTI8 */
#define DMAMUX_TRIGGER_EXTI9              RG_CHXCFG_TID(16U)                                                           /*!< trigger input is EXTI9 */
#define DMAMUX_TRIGGER_EXTI10             RG_CHXCFG_TID(17U)                                                           /*!< trigger input is EXTI10 */
#define DMAMUX_TRIGGER_EXTI11             RG_CHXCFG_TID(18U)                                                           /*!< trigger input is EXTI11 */
#define DMAMUX_TRIGGER_EXTI12             RG_CHXCFG_TID(19U)                                                           /*!< trigger input is EXTI12 */
#define DMAMUX_TRIGGER_EXTI13             RG_CHXCFG_TID(20U)                                                           /*!< trigger input is EXTI13 */
#define DMAMUX_TRIGGER_EXTI14             RG_CHXCFG_TID(21U)                                                           /*!< trigger input is EXTI14 */
#define DMAMUX_TRIGGER_EXTI15             RG_CHXCFG_TID(22U)                                                           /*!< trigger input is EXTI15 */
#define DMAMUX_TRIGGER_RTC_WAKEUP         RG_CHXCFG_TID(23U)                                                           /*!< trigger input is wakeup*/
#define DMAMUX_TRIGGER_CMP0_OUTPUT        RG_CHXCFG_TID(24U)                                                           /*!< trigger input is CMP0 output */
#define DMAMUX_TRIGGER_CMP1_OUTPUT        RG_CHXCFG_TID(25U)                                                           /*!< trigger input is CMP1 output */
#define DMAMUX_TRIGGER_I2C0_WAKEUP        RG_CHXCFG_TID(26U)                                                           /*!< trigger input is I2C0 wakeup */
#define DMAMUX_TRIGGER_I2C1_WAKEUP        RG_CHXCFG_TID(27U)                                                           /*!< trigger input is I2C1 wakeup */
#define DMAMUX_TRIGGER_I2C2_WAKEUP        RG_CHXCFG_TID(28U)                                                           /*!< trigger input is I2C2 wakeup */
#define DMAMUX_TRIGGER_I2C3_WAKEUP        RG_CHXCFG_TID(29U)                                                           /*!< trigger input is I2C3 wakeup */
#define DMAMUX_TRIGGER_I2C0_INT_EVENT     RG_CHXCFG_TID(30U)                                                           /*!< trigger input is I2C0 interrupt event */
#define DMAMUX_TRIGGER_I2C1_INT_EVENT     RG_CHXCFG_TID(31U)                                                           /*!< trigger input is I2C1 interrupt event */
#define DMAMUX_TRIGGER_I2C2_INT_EVENT     RG_CHXCFG_TID(32U)                                                           /*!< trigger input is I2C2 interrupt event */
#define DMAMUX_TRIGGER_I2C3_INT_EVENT     RG_CHXCFG_TID(33U)                                                           /*!< trigger input is I2C3 interrupt event */
#define DMAMUX_TRIGGER_ADC2_INT           RG_CHXCFG_TID(34U)                                                           /*!< trigger input is ADC2 interrupt */

/* DMAMUX request generator trigger polarity */
#define RG_CHXCFG_RGTP(regval)            (BITS(17,18) & ((uint32_t)(regval) << 17U))                                  /*!< DMA request generator trigger polarity */
#define DMAMUX_GEN_NO_EVENT               RG_CHXCFG_RGTP(0U)                                                           /*!< no event detection */
#define DMAMUX_GEN_RISING                 RG_CHXCFG_RGTP(1U)                                                           /*!< rising edge */
#define DMAMUX_GEN_FALLING                RG_CHXCFG_RGTP(2U)                                                           /*!< falling edge */
#define DMAMUX_GEN_RISING_FALLING         RG_CHXCFG_RGTP(3U)                                                           /*!< rising and falling edges */

/* number of DMA requests to be generated */
#define RG_CHXCFG_NBRG(regval)            (BITS(19,23) & ((uint32_t)(regval) << 19U))                                  /*!< number of DMA requests to be generated */

/* DMAMUX request multiplexer channel synchronization input identification */
#define RM_CHXCFG_SYNCID(regval)          (BITS(24,28) & ((uint32_t)(regval) << 24U))                                  /*!< synchronization input identification */
#define DMAMUX_SYNC_EVT0_OUT              RM_CHXCFG_SYNCID(0U)                                                         /*!< synchronization input is Evt0_out */
#define DMAMUX_SYNC_EVT1_OUT              RM_CHXCFG_SYNCID(1U)                                                         /*!< synchronization input is Evt1_out */
#define DMAMUX_SYNC_EVT2_OUT              RM_CHXCFG_SYNCID(2U)                                                         /*!< synchronization input is Evt2_out */
#define DMAMUX_SYNC_EVT3_OUT              RM_CHXCFG_SYNCID(3U)                                                         /*!< synchronization input is Evt3_out */
#define DMAMUX_SYNC_EVT4_OUT              RM_CHXCFG_SYNCID(4U)                                                         /*!< synchronization input is Evt4_out */
#define DMAMUX_SYNC_EVT5_OUT              RM_CHXCFG_SYNCID(5U)                                                         /*!< synchronization input is Evt5_out */
#define DMAMUX_SYNC_EVT6_OUT              RM_CHXCFG_SYNCID(6U)                                                         /*!< synchronization input is Evt6_out */
#define DMAMUX_SYNC_EXTI0                 RM_CHXCFG_SYNCID(7U)                                                         /*!< synchronization input is EXTI0 */
#define DMAMUX_SYNC_EXTI1                 RM_CHXCFG_SYNCID(8U)                                                         /*!< synchronization input is EXTI1 */
#define DMAMUX_SYNC_EXTI2                 RM_CHXCFG_SYNCID(9U)                                                         /*!< synchronization input is EXTI2 */
#define DMAMUX_SYNC_EXTI3                 RM_CHXCFG_SYNCID(10U)                                                        /*!< synchronization input is EXTI3 */
#define DMAMUX_SYNC_EXTI4                 RM_CHXCFG_SYNCID(11U)                                                        /*!< synchronization input is EXTI4 */
#define DMAMUX_SYNC_EXTI5                 RM_CHXCFG_SYNCID(12U)                                                        /*!< synchronization input is EXTI5 */
#define DMAMUX_SYNC_EXTI6                 RM_CHXCFG_SYNCID(13U)                                                        /*!< synchronization input is EXTI6 */
#define DMAMUX_SYNC_EXTI7                 RM_CHXCFG_SYNCID(14U)                                                        /*!< synchronization input is EXTI7 */
#define DMAMUX_SYNC_EXTI8                 RM_CHXCFG_SYNCID(15U)                                                        /*!< synchronization input is EXTI8 */
#define DMAMUX_SYNC_EXTI9                 RM_CHXCFG_SYNCID(16U)                                                        /*!< synchronization input is EXTI9 */
#define DMAMUX_SYNC_EXTI10                RM_CHXCFG_SYNCID(17U)                                                        /*!< synchronization input is EXTI10 */
#define DMAMUX_SYNC_EXTI11                RM_CHXCFG_SYNCID(18U)                                                        /*!< synchronization input is EXTI11 */
#define DMAMUX_SYNC_EXTI12                RM_CHXCFG_SYNCID(19U)                                                        /*!< synchronization input is EXTI12 */
#define DMAMUX_SYNC_EXTI13                RM_CHXCFG_SYNCID(20U)                                                        /*!< synchronization input is EXTI13 */
#define DMAMUX_SYNC_EXTI14                RM_CHXCFG_SYNCID(21U)                                                        /*!< synchronization input is EXTI14 */
#define DMAMUX_SYNC_EXTI15                RM_CHXCFG_SYNCID(22U)                                                        /*!< synchronization input is EXTI15 */
#define DMAMUX_SYNC_RTC_WAKEUP            RM_CHXCFG_SYNCID(23U)                                                        /*!< synchronization input is RTC wakeup */
#define DMAMUX_SYNC_CMP0_OUTPUT           RM_CHXCFG_SYNCID(24U)                                                        /*!< synchronization input is CMP0 output */
#define DMAMUX_SYNC_I2C0_WAKEUP           RM_CHXCFG_SYNCID(25U)                                                        /*!< synchronization input is I2C0 wakeup */
#define DMAMUX_SYNC_I2C1_WAKEUP           RM_CHXCFG_SYNCID(26U)                                                        /*!< synchronization input is I2C1 wakeup */
#define DMAMUX_SYNC_I2C2_WAKEUP           RM_CHXCFG_SYNCID(27U)                                                        /*!< synchronization input is I2C2 wakeup */
#define DMAMUX_SYNC_I2C3_WAKEUP           RM_CHXCFG_SYNCID(28U)                                                        /*!< synchronization input is I2C3 wakeup */

/* DMAMUX request multiplexer synchronization input polarity */
#define RM_CHXCFG_SYNCP(regval)           (BITS(17,18) & ((uint32_t)(regval) << 17U))                                  /*!< synchronization input polarity */
#define DMAMUX_SYNC_NO_EVENT              RM_CHXCFG_SYNCP(0U)                                                          /*!< no event detection */
#define DMAMUX_SYNC_RISING                RM_CHXCFG_SYNCP(1U)                                                          /*!< rising edge */
#define DMAMUX_SYNC_FALLING               RM_CHXCFG_SYNCP(2U)                                                          /*!< falling edge */
#define DMAMUX_SYNC_RISING_FALLING        RM_CHXCFG_SYNCP(3U)                                                          /*!< rising and falling edges */

/* number of DMA requests to forward */
#define RM_CHXCFG_NBR(regval)            (BITS(19,23) & ((uint32_t)(regval) << 19U))                                   /*!< number of DMA requests to forward */

/* function declarations */
/* DMA deinitialization and initialization functions */
/* deinitialize DMA registers of a channel */
void dma_deinit(uint32_t dma_periph, dma_channel_enum channelx);
/* initialize the DMA single data mode parameters structure with the default values */
void dma_single_data_para_struct_init(dma_single_data_parameter_struct *init_struct);
/* initialize the DMA multi data mode parameters structure with the default values */
void dma_multi_data_para_struct_init(dma_multi_data_parameter_struct *init_struct);
/* initialize DMA single data mode */
void dma_single_data_mode_init(uint32_t dma_periph, dma_channel_enum channelx, dma_single_data_parameter_struct *init_struct);
/* initialize DMA multi data mode */
void dma_multi_data_mode_init(uint32_t dma_periph, dma_channel_enum channelx, dma_multi_data_parameter_struct *init_struct);

/* DMA configuration functions */
/* configure DMA peripheral base address */
void dma_periph_address_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t address);
/* configure DMA memory base address */
void dma_memory_address_config(uint32_t dma_periph, dma_channel_enum channelx, uint8_t memory_flag, uint32_t address);
/* configure the number of remaining data to be transferred by the DMA */
void dma_transfer_number_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t number);
/* get the number of remaining data to be transferred by the DMA */
uint32_t dma_transfer_number_get(uint32_t dma_periph, dma_channel_enum channelx);
/* configure priority level of DMA channel */
void dma_priority_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t priority);
/* configure transfer burst beats of memory */
void dma_memory_burst_beats_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t mbeat);
/* configure transfer burst beats of peripheral */
void dma_periph_burst_beats_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t pbeat);
/* configure transfer data size of memory */
void dma_memory_width_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t msize);
/* configure transfer data size of peripheral */
void dma_periph_width_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t psize);
/* configure next address increasement algorithm of memory */
void dma_memory_address_generation_config(uint32_t dma_periph, dma_channel_enum channelx, uint8_t generation_algorithm);
/* configure next address increasement algorithm of peripheral */
void dma_peripheral_address_generation_config(uint32_t dma_periph, dma_channel_enum channelx, uint8_t generation_algorithm);
/* enable DMA circulation mode */
void dma_circulation_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable DMA circulation mode */
void dma_circulation_disable(uint32_t dma_periph, dma_channel_enum channelx);
/* enable DMA channel */
void dma_channel_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable DMA channel */
void dma_channel_disable(uint32_t dma_periph, dma_channel_enum channelx);
/* configure the direction of data transfer on the channel */
void dma_transfer_direction_config(uint32_t dma_periph, dma_channel_enum channelx, uint8_t direction);
/* configure DMA switch buffer mode */
void dma_switch_buffer_mode_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t memory1_addr, uint32_t memory_select);
/* get DMA using memory */
uint32_t dma_using_memory_get(uint32_t dma_periph, dma_channel_enum channelx);
/* enable DMA switch buffer mode */
void dma_switch_buffer_mode_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable DMA switch buffer mode */
void dma_switch_buffer_mode_disable(uint32_t dma_periph, dma_channel_enum channelx);
/* get DMA FIFO status */
uint32_t dma_fifo_status_get(uint32_t dma_periph, dma_channel_enum channelx);

/* interrupt & flag functions */
/* get DMA flag */
FlagStatus dma_flag_get(uint32_t dma_periph, dma_channel_enum channelx, uint32_t flag);
/* clear DMA flag */
void dma_flag_clear(uint32_t dma_periph, dma_channel_enum channelx, uint32_t flag);
/* enable DMA interrupt */
void dma_interrupt_enable(uint32_t dma_periph, dma_channel_enum channelx, uint32_t interrupt);
/* disable DMA interrupt */
void dma_interrupt_disable(uint32_t dma_periph, dma_channel_enum channelx, uint32_t interrupt);
/* get DMA interrupt flag */
FlagStatus dma_interrupt_flag_get(uint32_t dma_periph, dma_channel_enum channelx, uint32_t int_flag);
/* clear DMA interrupt flag */
void dma_interrupt_flag_clear(uint32_t dma_periph, dma_channel_enum channelx, uint32_t int_flag);

/* DMAMUX functions */
/* DMAMUX request multiplexer functions */
/* initialize the parameters of DMAMUX synchronization mode structure with the default values */
void dmamux_sync_struct_para_init(dmamux_sync_parameter_struct *init_struct);
/* initialize DMAMUX request multiplexer channel synchronization mode */
void dmamux_synchronization_init(dmamux_multiplexer_channel_enum channelx, dmamux_sync_parameter_struct *init_struct);
/* enable synchronization mode */
void dmamux_synchronization_enable(dmamux_multiplexer_channel_enum channelx);
/* disable synchronization mode */
void dmamux_synchronization_disable(dmamux_multiplexer_channel_enum channelx);
/* enable event generation */
void dmamux_event_generation_enable(dmamux_multiplexer_channel_enum channelx);
/* disable event generation */
void dmamux_event_generation_disable(dmamux_multiplexer_channel_enum channelx);

/* DMAMUX request generator functions */
/* initialize the parameters of DMAMUX request generator structure with the default values */
void dmamux_gen_struct_para_init(dmamux_gen_parameter_struct *init_struct);
/* initialize DMAMUX request generator channel */
void dmamux_request_generator_init(dmamux_generator_channel_enum channelx, dmamux_gen_parameter_struct *init_struct);
/* enable DMAMUX request generator channel */
void dmamux_request_generator_channel_enable(dmamux_generator_channel_enum channelx);
/* disable DMAMUX request generator channel */
void dmamux_request_generator_channel_disable(dmamux_generator_channel_enum channelx);

/* DMAMUX configuration functions */
/* configure synchronization input polarity */
void dmamux_synchronization_polarity_config(dmamux_multiplexer_channel_enum channelx, uint32_t polarity);
/* configure number of DMA requests to forward */
void dmamux_request_forward_number_config(dmamux_multiplexer_channel_enum channelx, uint32_t number);
/* configure synchronization input identification */
void dmamux_sync_id_config(dmamux_multiplexer_channel_enum channelx, uint32_t id);
/* configure multiplexer input identification */
void dmamux_request_id_config(dmamux_multiplexer_channel_enum channelx, uint32_t id);
/* configure trigger input polarity */
void dmamux_trigger_polarity_config(dmamux_generator_channel_enum channelx, uint32_t polarity);
/* configure number of DMA requests to be generated */
void dmamux_request_generate_number_config(dmamux_generator_channel_enum channelx, uint32_t number);
/* configure trigger input identification */
void dmamux_trigger_id_config(dmamux_generator_channel_enum channelx, uint32_t id);

/* interrupt & flag functions */
/* get DMAMUX flag */
FlagStatus dmamux_flag_get(dmamux_flag_enum flag);
/* clear DMAMUX flag */
void dmamux_flag_clear(dmamux_flag_enum flag);
/* enable DMAMUX interrupt */
void dmamux_interrupt_enable(dmamux_interrupt_enum interrupt);
/* disable DMAMUX interrupt */
void dmamux_interrupt_disable(dmamux_interrupt_enum interrupt);
/* get DMAMUX interrupt flag */
FlagStatus dmamux_interrupt_flag_get(dmamux_interrupt_flag_enum int_flag);
/* clear DMAMUX interrupt flag */
void dmamux_interrupt_flag_clear(dmamux_interrupt_flag_enum int_flag);

#endif /* GD32H7XX_DMA_H */
