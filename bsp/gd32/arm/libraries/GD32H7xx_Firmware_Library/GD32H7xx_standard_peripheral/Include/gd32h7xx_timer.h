/*!
    \file    gd32h7xx_timer.h
    \brief   definitions for the TIMER

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


#ifndef GD32H7XX_TIMER_H
#define GD32H7XX_TIMER_H

#include "gd32h7xx.h"

/* TIMER definitions */
#define TIMER0                           (TIMER_BASE + 0x00010000U)                 /*!< TIMER0 base address */
#define TIMER1                           (TIMER_BASE + 0x00000000U)                 /*!< TIMER1 base address */
#define TIMER2                           (TIMER_BASE + 0x00000400U)                 /*!< TIMER2 base address */
#define TIMER3                           (TIMER_BASE + 0x00000800U)                 /*!< TIMER3 base address */
#define TIMER4                           (TIMER_BASE + 0x00000C00U)                 /*!< TIMER4 base address */
#define TIMER5                           (TIMER_BASE + 0x00001000U)                 /*!< TIMER5 base address */
#define TIMER6                           (TIMER_BASE + 0x00001400U)                 /*!< TIMER6 base address */
#define TIMER7                           (TIMER_BASE + 0x00010400U)                 /*!< TIMER7 base address */
#define TIMER14                          (TIMER_BASE + 0x00014000U)                 /*!< TIMER14 base address */
#define TIMER15                          (TIMER_BASE + 0x00014400U)                 /*!< TIMER15 base address */
#define TIMER16                          (TIMER_BASE + 0x00014800U)                 /*!< TIMER16 base address */
#define TIMER22                          (TIMER_BASE + 0x0000E000U)                 /*!< TIMER22 base address */
#define TIMER23                          (TIMER_BASE + 0x0000E400U)                 /*!< TIMER23 base address */
#define TIMER30                          (TIMER_BASE + 0x0000E800U)                 /*!< TIMER30 base address */
#define TIMER31                          (TIMER_BASE + 0x0000EC00U)                 /*!< TIMER31 base address */
#define TIMER40                          (TIMER_BASE + 0x0001D000U)                 /*!< TIMER40 base address */
#define TIMER41                          (TIMER_BASE + 0x0001D400U)                 /*!< TIMER41 base address */
#define TIMER42                          (TIMER_BASE + 0x0001D800U)                 /*!< TIMER42 base address */
#define TIMER43                          (TIMER_BASE + 0x0001DC00U)                 /*!< TIMER43 base address */
#define TIMER44                          (TIMER_BASE + 0x0001F000U)                 /*!< TIMER44 base address */
#define TIMER50                          (TIMER_BASE + 0x0000F000U)                 /*!< TIMER50 base address */
#define TIMER51                          (TIMER_BASE + 0x0000F400U)                 /*!< TIMER51 base address */

/* registers definitions */
#define TIMER_CTL0(timerx)               REG32((timerx) + 0x00000000U)              /*!< TIMER control register 0 */
#define TIMER_CTL1(timerx)               REG32((timerx) + 0x00000004U)              /*!< TIMER control register 1 */
#define TIMER_SMCFG(timerx)              REG32((timerx) + 0x00000008U)              /*!< TIMER slave mode configuration register */
#define TIMER_DMAINTEN(timerx)           REG32((timerx) + 0x0000000CU)              /*!< TIMER DMA and interrupt enable register */
#define TIMER_INTF(timerx)               REG32((timerx) + 0x00000010U)              /*!< TIMER interrupt flag register */
#define TIMER_SWEVG(timerx)              REG32((timerx) + 0x00000014U)              /*!< TIMER software event generation register */
#define TIMER_CHCTL0(timerx)             REG32((timerx) + 0x00000018U)              /*!< TIMER channel control register 0 */
#define TIMER_CHCTL1(timerx)             REG32((timerx) + 0x0000001CU)              /*!< TIMER channel control register 1 */
#define TIMER_CHCTL2(timerx)             REG32((timerx) + 0x00000020U)              /*!< TIMER channel control register 2 */
#define TIMER_CNT(timerx)                REG32((timerx) + 0x00000024U)              /*!< TIMER counter register */
#define TIMER_CNTL(timerx)               REG32((timerx) + 0x00000024U)              /*!< TIMER counter low register (only for TIMERx, x=50,51) */
#define TIMER_PSC(timerx)                REG32((timerx) + 0x00000028U)              /*!< TIMER prescaler register */
#define TIMER_CAR(timerx)                REG32((timerx) + 0x0000002CU)              /*!< TIMER counter auto reload register */
#define TIMER_CARL(timerx)               REG32((timerx) + 0x0000002CU)              /*!< TIMER counter auto reload low register (only for TIMERx, x=50,51) */
#define TIMER_CREP0(timerx)              REG32((timerx) + 0x00000030U)              /*!< TIMER counter repetition register 0 */
#define TIMER_CH0CV(timerx)              REG32((timerx) + 0x00000034U)              /*!< TIMER channel 0 capture or compare value register */
#define TIMER_CH1CV(timerx)              REG32((timerx) + 0x00000038U)              /*!< TIMER channel 1 capture or compare value register */
#define TIMER_CH2CV(timerx)              REG32((timerx) + 0x0000003CU)              /*!< TIMER channel 2 capture or compare value register */
#define TIMER_CH3CV(timerx)              REG32((timerx) + 0x00000040U)              /*!< TIMER channel 3 capture or compare value register */
#define TIMER_CCHP(timerx)               REG32((timerx) + 0x00000044U)              /*!< TIMER channel complementary protection register */
#define TIMER_MCHCTL0(timerx)            REG32((timerx) + 0x00000048U)              /*!< TIMER multi mode channel control register 0 */
#define TIMER_MCHCTL1(timerx)            REG32((timerx) + 0x0000004CU)              /*!< TIMER multi mode channel control register 1 */
#define TIMER_MCHCTL2(timerx)            REG32((timerx) + 0x00000050U)              /*!< TIMER multi mode channel control register 2 */
#define TIMER_MCH0CV(timerx)             REG32((timerx) + 0x00000054U)              /*!< TIMER multi mode channel 0 capture or compare value register */
#define TIMER_MCH1CV(timerx)             REG32((timerx) + 0x00000058U)              /*!< TIMER multi mode channel 1 capture or compare value register */
#define TIMER_MCH2CV(timerx)             REG32((timerx) + 0x0000005CU)              /*!< TIMER multi mode channel 2 capture or compare value register */
#define TIMER_MCH3CV(timerx)             REG32((timerx) + 0x00000060U)              /*!< TIMER multi mode channel 3 capture or compare value register */
#define TIMER_CH0COMV_ADD(timerx)        REG32((timerx) + 0x00000064U)              /*!< TIMER channel 0 additional compare value register */
#define TIMER_CH1COMV_ADD(timerx)        REG32((timerx) + 0x00000068U)              /*!< TIMER channel 1 additional compare value register */
#define TIMER_CH2COMV_ADD(timerx)        REG32((timerx) + 0x0000006CU)              /*!< TIMER channel 2 additional compare value register */
#define TIMER_CH3COMV_ADD(timerx)        REG32((timerx) + 0x00000070U)              /*!< TIMER channel 3 additional compare value register */
#define TIMER_CTL2(timerx)               REG32((timerx) + 0x00000074U)              /*!< TIMER control register 2 */
#define TIMER_FCCHP0(timerx)             REG32((timerx) + 0x0000007CU)              /*!< TIMER free complementary channel protection register 0 */
#define TIMER_FCCHP1(timerx)             REG32((timerx) + 0x00000080U)              /*!< TIMER free complementary channel protection register 1 */
#define TIMER_FCCHP2(timerx)             REG32((timerx) + 0x00000084U)              /*!< TIMER free complementary channel protection register 2 */
#define TIMER_FCCHP3(timerx)             REG32((timerx) + 0x00000088U)              /*!< TIMER free complementary channel protection register 3 */
#define TIMER_AFCTL0(timerx)             REG32((timerx) + 0x0000008CU)              /*!< TIMER alternate function control register 0 */
#define TIMER_AFCTL1(timerx)             REG32((timerx) + 0x00000090U)              /*!< TIMER alternate function control register 1 */
#define TIMER_WDGPER(timerx)             REG32((timerx) + 0x00000094U)              /*!< TIMER watchdog counter period register */
#define TIMER_CREP1(timerx)              REG32((timerx) + 0x00000098U)              /*!< TIMER counter repetition register 1 */
#define TIMER_CNTH(timerx)               REG32((timerx) + 0x000000D0U)              /*!< TIMER counter high register (only for TIMERx, x=50,51) */
#define TIMER_CARH(timerx)               REG32((timerx) + 0x000000D4U)              /*!< TIMER counter auto reload high register (only for TIMERx, x=50,51) */
#define TIMER_DMACFG(timerx)             REG32((timerx) + 0x000000E0U)              /*!< TIMER DMA configuration register */
#define TIMER_DMATB(timerx)              REG32((timerx) + 0x000000E4U)              /*!< TIMER DMA transfer buffer register */
#define TIMER_CFG(timerx)                REG32((timerx) + 0x000000FCU)              /*!< TIMER configuration register */

/* bits definitions */
/* TIMER_CTL0 */
#define TIMER_CTL0_CEN                   BIT(0)                                     /*!< TIMER counter enable */
#define TIMER_CTL0_UPDIS                 BIT(1)                                     /*!< update disable */
#define TIMER_CTL0_UPS                   BIT(2)                                     /*!< update source */
#define TIMER_CTL0_SPM                   BIT(3)                                     /*!< single pulse mode */
#define TIMER_CTL0_DIR                   BIT(4)                                     /*!< timer counter direction */
#define TIMER_CTL0_CAM                   BITS(5,6)                                  /*!< counter aligned mode selection */
#define TIMER_CTL0_ARSE                  BIT(7)                                     /*!< auto-reload shadow enable */
#define TIMER_CTL0_CKDIV                 BITS(8,9)                                  /*!< clock division */
#define TIMER_CTL0_UPIFBUEN              BIT(11)                                    /*!< UPIF bit backup enable */

/* TIMER_CTL1 */
#define TIMER_CTL1_CCSE                  BIT(0)                                     /*!< commutation control shadow enable */
#define TIMER_CTL1_CCUC                  (BIT(2) | BITS(30,31))                     /*!< commutation control shadow register update control */
#define TIMER_CTL1_DMAS                  BIT(3)                                     /*!< DMA request source selection */
#define TIMER_CTL1_MMC0                  BITS(4,6)                                  /*!< master mode control 0 */
#define TIMER_CTL1_TI0S                  BIT(7)                                     /*!< channel 0 trigger input selection(hall mode selection) */
#define TIMER_CTL1_ISO0                  BIT(8)                                     /*!< idle state of channel 0 output */
#define TIMER_CTL1_ISO0N                 BIT(9)                                     /*!< idle state of channel 0 complementary output */
#define TIMER_CTL1_ISO1                  BIT(10)                                    /*!< idle state of channel 1 output */
#define TIMER_CTL1_ISO1N                 BIT(11)                                    /*!< idle state of channel 1 complementary output */
#define TIMER_CTL1_ISO2                  BIT(12)                                    /*!< idle state of channel 2 output */
#define TIMER_CTL1_ISO2N                 BIT(13)                                    /*!< idle state of channel 2 complementary output */
#define TIMER_CTL1_ISO3                  BIT(14)                                    /*!< idle state of channel 3 output */
#define TIMER_CTL1_ISO3N                 BIT(15)                                    /*!< idle state of channel 3 complementary output */
#define TIMER_CTL1_MMC1                  BITS(20,22)                                /*!< master mode control 1 */

/* TIMER_SMCFG */
#define TIMER_SMCFG_MSM                  BIT(7)                                     /*!< master-slave mode */
#define TIMER_SMCFG_ETFC                 BITS(8,11)                                 /*!< external trigger filter control */
#define TIMER_SMCFG_ETPSC                BITS(12,13)                                /*!< external trigger prescaler */
#define TIMER_SMCFG_SMC1                 BIT(14)                                    /*!< part of SMC for enable external clock mode 1 */
#define TIMER_SMCFG_ETP                  BIT(15)                                    /*!< external trigger polarity */

/* TIMER_DMAINTEN */
#define TIMER_DMAINTEN_UPIE              BIT(0)                                     /*!< update interrupt enable */
#define TIMER_DMAINTEN_CH0IE             BIT(1)                                     /*!< channel 0 capture or compare interrupt enable */
#define TIMER_DMAINTEN_CH1IE             BIT(2)                                     /*!< channel 1 capture or compare interrupt enable */
#define TIMER_DMAINTEN_CH2IE             BIT(3)                                     /*!< channel 2 capture or compare interrupt enable */
#define TIMER_DMAINTEN_CH3IE             BIT(4)                                     /*!< channel 3 capture or compare interrupt enable */
#define TIMER_DMAINTEN_CMTIE             BIT(5)                                     /*!< commutation interrupt request enable */
#define TIMER_DMAINTEN_TRGIE             BIT(6)                                     /*!< trigger interrupt enable */
#define TIMER_DMAINTEN_BRKIE             BIT(7)                                     /*!< break interrupt enable */
#define TIMER_DMAINTEN_UPDEN             BIT(8)                                     /*!< update DMA request enable */
#define TIMER_DMAINTEN_CH0DEN            BIT(9)                                     /*!< channel 0 capture or compare DMA request enable */
#define TIMER_DMAINTEN_CH1DEN            BIT(10)                                    /*!< channel 1 capture or compare DMA request enable */
#define TIMER_DMAINTEN_CH2DEN            BIT(11)                                    /*!< channel 2 capture or compare DMA request enable */
#define TIMER_DMAINTEN_CH3DEN            BIT(12)                                    /*!< channel 3 capture or compare DMA request enable */
#define TIMER_DMAINTEN_CMTDEN            BIT(13)                                    /*!< commutation DMA request enable */
#define TIMER_DMAINTEN_TRGDEN            BIT(14)                                    /*!< trigger DMA request enable */
#define TIMER_DMAINTEN_DECJIE            BIT(16)                                    /*!< quadrature decoder signal jump (the two signals jump at the same time) interrupt enable */
#define TIMER_DMAINTEN_DECDISIE          BIT(17)                                    /*!< quadrature decoder signal disconnection interrupt enable */
#define TIMER_DMAINTEN_MCH0IE            BIT(20)                                    /*!< multi mode channel 0 capture or compare interrupt enable */
#define TIMER_DMAINTEN_MCH1IE            BIT(21)                                    /*!< multi mode channel 1 capture or compare interrupt enable */
#define TIMER_DMAINTEN_MCH2IE            BIT(22)                                    /*!< multi mode channel 2 capture or compare interrupt enable */
#define TIMER_DMAINTEN_MCH3IE            BIT(23)                                    /*!< multi mode channel 3 capture or compare interrupt enable */
#define TIMER_DMAINTEN_MCH0DEN           BIT(24)                                    /*!< multi mode channel 0 capture or compare DMA request enable */
#define TIMER_DMAINTEN_MCH1DEN           BIT(25)                                    /*!< multi mode channel 1 capture or compare DMA request enable */
#define TIMER_DMAINTEN_MCH2DEN           BIT(26)                                    /*!< multi mode channel 2 capture or compare DMA request enable */
#define TIMER_DMAINTEN_MCH3DEN           BIT(27)                                    /*!< multi mode channel 3 capture or compare DMA request enable */
#define TIMER_DMAINTEN_CH0COMADDIE       BIT(28)                                    /*!< channel 0 additional compare interrupt enable */
#define TIMER_DMAINTEN_CH1COMADDIE       BIT(29)                                    /*!< channel 1 additional compare interrupt enable */
#define TIMER_DMAINTEN_CH2COMADDIE       BIT(30)                                    /*!< channel 2 additional compare interrupt enable */
#define TIMER_DMAINTEN_CH3COMADDIE       BIT(31)                                    /*!< channel 3 additional compare interrupt enable */

/* TIMER_INTF */
#define TIMER_INTF_UPIF                  BIT(0)                                     /*!< update interrupt flag */
#define TIMER_INTF_CH0IF                 BIT(1)                                     /*!< channel 0 capture or compare interrupt flag */
#define TIMER_INTF_CH1IF                 BIT(2)                                     /*!< channel 1 capture or compare interrupt flag */
#define TIMER_INTF_CH2IF                 BIT(3)                                     /*!< channel 2 capture or compare interrupt flag */
#define TIMER_INTF_CH3IF                 BIT(4)                                     /*!< channel 3 capture or compare interrupt flag */
#define TIMER_INTF_CMTIF                 BIT(5)                                     /*!< channel commutation interrupt flag */
#define TIMER_INTF_TRGIF                 BIT(6)                                     /*!< trigger interrupt flag */
#define TIMER_INTF_BRK0IF                BIT(7)                                     /*!< BREAK0 interrupt flag */
#define TIMER_INTF_BRK1IF                BIT(8)                                     /*!< BREAK1 interrupt flag */
#define TIMER_INTF_CH0OF                 BIT(9)                                     /*!< channel 0 over capture flag */
#define TIMER_INTF_CH1OF                 BIT(10)                                    /*!< channel 1 over capture flag */
#define TIMER_INTF_CH2OF                 BIT(11)                                    /*!< channel 2 over capture flag */
#define TIMER_INTF_CH3OF                 BIT(12)                                    /*!< channel 3 over capture flag */
#define TIMER_INTF_SYSBIF                BIT(13)                                    /*!< system source break interrupt flag */
#define TIMER_INTF_DECJIF                BIT(16)                                    /*!< quadrature decoder signal jump (the two signals jump at the same time) interrupt flag */
#define TIMER_INTF_DECDISIF              BIT(17)                                    /*!< quadrature decoder signal disconnection interrupt flag */
#define TIMER_INTF_MCH0IF                BIT(20)                                    /*!< multi mode channel 0 capture or compare interrupt flag */
#define TIMER_INTF_MCH1IF                BIT(21)                                    /*!< multi mode channel 1 capture or compare interrupt flag */
#define TIMER_INTF_MCH2IF                BIT(22)                                    /*!< multi mode channel 2 capture or compare interrupt flag */
#define TIMER_INTF_MCH3IF                BIT(23)                                    /*!< multi mode channel 3 capture or compare interrupt flag */
#define TIMER_INTF_MCH0OF                BIT(24)                                    /*!< multi mode channel 0 over capture flag */
#define TIMER_INTF_MCH1OF                BIT(25)                                    /*!< multi mode channel 1 over capture flag */
#define TIMER_INTF_MCH2OF                BIT(26)                                    /*!< multi mode channel 2 over capture flag */
#define TIMER_INTF_MCH3OF                BIT(27)                                    /*!< multi mode channel 3 over capture flag */
#define TIMER_INTF_CH0COMADDIF           BIT(28)                                    /*!< channel 0 additional compare interrupt flag */
#define TIMER_INTF_CH1COMADDIF           BIT(29)                                    /*!< channel 1 additional compare interrupt flag */
#define TIMER_INTF_CH2COMADDIF           BIT(30)                                    /*!< channel 2 additional compare interrupt flag */
#define TIMER_INTF_CH3COMADDIF           BIT(31)                                    /*!< channel 3 additional compare interrupt flag */

/* TIMER_SWEVG */
#define TIMER_SWEVG_UPG                  BIT(0)                                     /*!< update event generate */
#define TIMER_SWEVG_CH0G                 BIT(1)                                     /*!< channel 0 capture or compare event generation */
#define TIMER_SWEVG_CH1G                 BIT(2)                                     /*!< channel 1 capture or compare event generation */
#define TIMER_SWEVG_CH2G                 BIT(3)                                     /*!< channel 2 capture or compare event generation */
#define TIMER_SWEVG_CH3G                 BIT(4)                                     /*!< channel 3 capture or compare event generation */
#define TIMER_SWEVG_CMTG                 BIT(5)                                     /*!< channel commutation event generation */
#define TIMER_SWEVG_TRGG                 BIT(6)                                     /*!< trigger event generation */
#define TIMER_SWEVG_BRK0G                BIT(7)                                     /*!< BREAK0 event generation */
#define TIMER_SWEVG_BRK1G                BIT(8)                                     /*!< BREAK1 event generation */
#define TIMER_SWEVG_MCH0G                BIT(20)                                    /*!< multi mode channel 0 capture or compare event generation */
#define TIMER_SWEVG_MCH1G                BIT(21)                                    /*!< multi mode channel 1 capture or compare event generation */
#define TIMER_SWEVG_MCH2G                BIT(22)                                    /*!< multi mode channel 2 capture or compare event generation */
#define TIMER_SWEVG_MCH3G                BIT(23)                                    /*!< multi mode channel 3 capture or compare event generation */
#define TIMER_SWEVG_CH0COMADDG           BIT(28)                                    /*!< channel 0 additional compare event generation */
#define TIMER_SWEVG_CH1COMADDG           BIT(29)                                    /*!< channel 1 additional compare event generation */
#define TIMER_SWEVG_CH2COMADDG           BIT(30)                                    /*!< channel 2 additional compare event generation */
#define TIMER_SWEVG_CH3COMADDG           BIT(31)                                    /*!< channel 3 additional compare event generation */

/* TIMER_CHCTL0 */
/* output compare mode */
#define TIMER_CHCTL0_CH0MS               (BITS(0,1) | BIT(30))                      /*!< channel 0 mode selection */
#define TIMER_CHCTL0_CH0COMSEN           BIT(3)                                     /*!< channel 0 output compare shadow enable */
#define TIMER_CHCTL0_CH0COMCTL           (BITS(4,6) | BIT(16))                      /*!< channel 0 output compare control */
#define TIMER_CHCTL0_CH0COMCEN           BIT(7)                                     /*!< channel 0 output compare clear enable */
#define TIMER_CHCTL0_CH1MS               (BITS(8,9) | BIT(31))                      /*!< channel 1 mode selection */
#define TIMER_CHCTL0_CH1COMSEN           BIT(11)                                    /*!< channel 1 output compare shadow enable */
#define TIMER_CHCTL0_CH1COMCTL           (BITS(12,14) | BIT(24))                    /*!< channel 1 output compare control */
#define TIMER_CHCTL0_CH1COMCEN           BIT(15)                                    /*!< channel 1 output compare clear enable */
#define TIMER_CHCTL0_CH0COMADDSEN        BIT(28)                                    /*!< channel 0 additional compare output shadow enable */
#define TIMER_CHCTL0_CH1COMADDSEN        BIT(29)                                    /*!< channel 1 additional compare output shadow enable */
/* input capture mode */
#define TIMER_CHCTL0_CH0CAPPSC           BITS(2,3)                                  /*!< channel 0 input capture prescaler */
#define TIMER_CHCTL0_CH0CAPFLT           BITS(4,7)                                  /*!< channel 0 input capture filter control */
#define TIMER_CHCTL0_CH1CAPPSC           BITS(10,11)                                /*!< channel 1 input capture prescaler */
#define TIMER_CHCTL0_CH1CAPFLT           BITS(12,15)                                /*!< channel 1 input capture filter control */

/* TIMER_CHCTL1 */
/* output compare mode */
#define TIMER_CHCTL1_CH2MS               (BITS(0,1) | BIT(30))                      /*!< channel 2 mode selection */
#define TIMER_CHCTL1_CH2COMSEN           BIT(3)                                     /*!< channel 2 output compare shadow enable */
#define TIMER_CHCTL1_CH2COMCTL           (BITS(4,6) | BIT(16))                      /*!< channel 2 output compare control */
#define TIMER_CHCTL1_CH2COMCEN           BIT(7)                                     /*!< channel 2 output compare clear enable */
#define TIMER_CHCTL1_CH3MS               (BITS(8,9) | BIT(31))                      /*!< channel 3 mode selection */
#define TIMER_CHCTL1_CH3COMSEN           BIT(11)                                    /*!< channel 3 output compare shadow enable */
#define TIMER_CHCTL1_CH3COMCTL           (BITS(12,14) | BIT(24))                    /*!< channel 3 output compare control */
#define TIMER_CHCTL1_CH3COMCEN           BIT(15)                                    /*!< channel 3 output compare clear enable */
#define TIMER_CHCTL1_CH2COMADDSEN        BIT(28)                                    /*!< channel 2 additional compare output shadow enable */
#define TIMER_CHCTL1_CH3COMADDSEN        BIT(29)                                    /*!< channel 3 additional compare output shadow enable */
/* input capture mode */
#define TIMER_CHCTL1_CH2CAPPSC           BITS(2,3)                                  /*!< channel 2 input capture prescaler */
#define TIMER_CHCTL1_CH2CAPFLT           BITS(4,7)                                  /*!< channel 2 input capture filter control */
#define TIMER_CHCTL1_CH3CAPPSC           BITS(10,11)                                /*!< channel 3 input capture prescaler */
#define TIMER_CHCTL1_CH3CAPFLT           BITS(12,15)                                /*!< channel 3 input capture filter control */

/* TIMER_CHCTL2 */
#define TIMER_CHCTL2_CH0EN               BIT(0)                                     /*!< channel 0 capture or compare function enable */
#define TIMER_CHCTL2_CH0P                BIT(1)                                     /*!< channel 0 capture or compare function polarity */
#define TIMER_CHCTL2_CH0NEN              BIT(2)                                     /*!< channel 0 complementary output enable */
#define TIMER_CHCTL2_CH0NP               BIT(3)                                     /*!< channel 0 complementary output polarity */
#define TIMER_CHCTL2_CH1EN               BIT(4)                                     /*!< channel 1 capture or compare function enable */
#define TIMER_CHCTL2_CH1P                BIT(5)                                     /*!< channel 1 capture or compare function polarity */
#define TIMER_CHCTL2_CH1NEN              BIT(6)                                     /*!< channel 1 complementary output enable */
#define TIMER_CHCTL2_CH1NP               BIT(7)                                     /*!< channel 1 complementary output polarity */
#define TIMER_CHCTL2_CH2EN               BIT(8)                                     /*!< channel 2 capture or compare function enable */
#define TIMER_CHCTL2_CH2P                BIT(9)                                     /*!< channel 2 capture or compare function polarity */
#define TIMER_CHCTL2_CH2NEN              BIT(10)                                    /*!< channel 2 complementary output enable */
#define TIMER_CHCTL2_CH2NP               BIT(11)                                    /*!< channel 2 complementary output polarity */
#define TIMER_CHCTL2_CH3EN               BIT(12)                                    /*!< channel 3 capture or compare function enable */
#define TIMER_CHCTL2_CH3P                BIT(13)                                    /*!< channel 3 capture or compare function polarity */
#define TIMER_CHCTL2_CH3NEN              BIT(14)                                    /*!< channel 3 complementary output enable */
#define TIMER_CHCTL2_CH3NP               BIT(15)                                    /*!< channel 3 complementary output polarity */

#define TIMER_CHCTL2_MCH0EN              BIT(2)                                     /*!< multi mode channel 0 capture or compare function enable */
#define TIMER_CHCTL2_MCH0P               BIT(3)                                     /*!< multi mode channel 0 complementary output polarity */
#define TIMER_CHCTL2_MCH1EN              BIT(6)                                     /*!< multi mode channel 1 capture or compare function enable */
#define TIMER_CHCTL2_MCH1P               BIT(7)                                     /*!< multi mode channel 1 complementary output polarity */
#define TIMER_CHCTL2_MCH2EN              BIT(10)                                    /*!< multi mode channel 2 capture or compare function enable */
#define TIMER_CHCTL2_MCH2P               BIT(11)                                    /*!< multi mode channel 2 complementary output polarity */
#define TIMER_CHCTL2_MCH3EN              BIT(14)                                    /*!< multi mode channel 3 capture or compare function enable */
#define TIMER_CHCTL2_MCH3P               BIT(15)                                    /*!< multi mode channel 3 complementary output polarity */

/* TIMER_CNT */
#define TIMER_CNT_UPIFBU                 BIT(31)                                    /*!< UPIF bit backup */
#define TIMER_CNT_CNT                    BITS(0,15)                                 /*!< 16 bit timer counter */

/* TIMER_PSC */
#define TIMER_PSC_PSC                    BITS(0,15)                                 /*!< prescaler value of the counter clock */

/* TIMER_CAR */
#define TIMER_CAR_CARL                   BITS(0,15)                                 /*!< 16 bit counter auto reload value */

/* TIMER_CREP0 */
#define TIMER_CREP0_CREP0                BITS(0,7)                                  /*!< counter repetition value 0 */

/* TIMER_CH0CV */
#define TIMER_CH0CV_CH0VAL               BITS(0,15)                                 /*!< 16 bit capture or compare value of channel 0 */

/* TIMER_CH1CV */
#define TIMER_CH1CV_CH1VAL               BITS(0,15)                                 /*!< 16 bit capture or compare value of channel 1 */

/* TIMER_CH2CV */
#define TIMER_CH2CV_CH2VAL               BITS(0,15)                                 /*!< 16 bit capture or compare value of channel 2 */

/* TIMER_CH3CV */
#define TIMER_CH3CV_CH3VAL               BITS(0,15)                                 /*!< 16 bit capture or compare value of channel 3 */

/* TIMER_CCHP */
#define TIMER_CCHP_DTCFG                 BITS(0,7)                                  /*!< dead time configure */
#define TIMER_CCHP_PROT                  BITS(8,9)                                  /*!< complementary register protect control */
#define TIMER_CCHP_IOS                   BIT(10)                                    /*!< idle mode off-state configure */
#define TIMER_CCHP_ROS                   BIT(11)                                    /*!< run mode off-state configure */
#define TIMER_CCHP_BRK0EN                BIT(12)                                    /*!< BREAK0 input signal enable */
#define TIMER_CCHP_BRK0P                 BIT(13)                                    /*!< BREAK0 input signal polarity */
#define TIMER_CCHP_OAEN                  BIT(14)                                    /*!< output automatic enable */
#define TIMER_CCHP_POEN                  BIT(15)                                    /*!< primary output enable */
#define TIMER_CCHP_BRK0F                 BITS(16,19)                                /*!< BREAK0 input signal filter */
#define TIMER_CCHP_BRK1F                 BITS(20,23)                                /*!< BREAK1 input signal filter */
#define TIMER_CCHP_BRK1EN                BIT(24)                                    /*!< BREAK1 input signal enable */
#define TIMER_CCHP_BRK1P                 BIT(25)                                    /*!< BREAK1 input signal polarity */
#define TIMER_CCHP_BRK0REL               BIT(26)                                    /*!< BREAK0 input released */
#define TIMER_CCHP_BRK1REL               BIT(27)                                    /*!< BREAK1 input released */
#define TIMER_CCHP_BRK0LK                BIT(28)                                    /*!< BREAK0 input locked */
#define TIMER_CCHP_BRK1LK                BIT(29)                                    /*!< BREAK1 input locked */

/* TIMER_MCHCTL0 */
/* output compare mode */
#define TIMER_MCHCTL0_MCH0MS             (BITS(0,1) | BIT(30))                      /*!< multi mode channel 0 I/O mode selection */
#define TIMER_MCHCTL0_MCH0COMSEN         BIT(3)                                     /*!< multi mode channel 0 output compare shadow enable */
#define TIMER_MCHCTL0_MCH0COMCTL         (BITS(4,6) | BIT(16))                      /*!< multi mode channel 0 compare output control */
#define TIMER_MCHCTL0_MCH0COMCEN         BIT(7)                                     /*!< multi mode channel 0 output compare clear enable */
#define TIMER_MCHCTL0_MCH1MS             (BITS(8,9) | BIT(31))                      /*!< multi mode channel 1 I/O mode selection */
#define TIMER_MCHCTL0_MCH1COMSEN         BIT(11)                                    /*!< multi mode channel 1 output compare shadow enable */
#define TIMER_MCHCTL0_MCH1COMCTL         (BITS(12,14) | BIT(24))                    /*!< multi mode channel 1 compare output control */
#define TIMER_MCHCTL0_MCH1COMCEN         BIT(15)                                    /*!< multi mode channel 1 output compare clear enable */
/* input capture mode */
#define TIMER_MCHCTL0_MCH0CAPPSC         BITS(2,3)                                  /*!< multi mode channel 0 input capture prescaler */
#define TIMER_MCHCTL0_MCH0CAPFLT         BITS(4,7)                                  /*!< multi mode channel 0 input capture filter control */
#define TIMER_MCHCTL0_MCH1CAPPSC         BITS(10,11)                                /*!< multi mode channel 1 input capture prescaler */
#define TIMER_MCHCTL0_MCH1CAPFLT         BITS(12,15)                                /*!< multi mode channel 1 input capture filter control */

/* TIMER_MCHCTL1 */
/* output compare mode */
#define TIMER_MCHCTL1_MCH2MS             (BITS(0,1) | BIT(30))                      /*!< multi mode channel 2 I/O mode selection */
#define TIMER_MCHCTL1_MCH2COMSEN         BIT(3)                                     /*!< multi mode channel 2 output compare shadow enable */
#define TIMER_MCHCTL1_MCH2COMCTL         (BITS(4,6) | BIT(16))                      /*!< multi mode channel 2 compare output control */
#define TIMER_MCHCTL1_MCH2COMCEN         BIT(7)                                     /*!< multi mode channel 2 output compare clear enable */
#define TIMER_MCHCTL1_MCH3MS             (BITS(8,9) | BIT(31))                      /*!< multi mode channel 3 I/O mode selection */
#define TIMER_MCHCTL1_MCH3COMSEN         BIT(11)                                    /*!< multi mode channel 3 output compare shadow enable */
#define TIMER_MCHCTL1_MCH3COMCTL         (BITS(12,14) | BIT(24))                    /*!< multi mode channel 3 compare output control */
#define TIMER_MCHCTL1_MCH3COMCEN         BIT(15)                                    /*!< multi mode channel 3 output compare clear enable */
/* input capture mode */
#define TIMER_MCHCTL1_MCH2CAPPSC         BITS(2,3)                                  /*!< multi mode channel 2 input capture prescaler */
#define TIMER_MCHCTL1_MCH2CAPFLT         BITS(4,7)                                  /*!< multi mode channel 2 input capture filter control */
#define TIMER_MCHCTL1_MCH3CAPPSC         BITS(10,11)                                /*!< multi mode channel 3 input capture prescaler */
#define TIMER_MCHCTL1_MCH3CAPFLT         BITS(12,15)                                /*!< multi mode channel 3 input capture filter control */

/* TIMER_MCHCTL2 */
#define TIMER_MCHCTL2_MCH0FP             BITS(0,1)                                  /*!< multi mode channel 0 capture or compare function polarity */
#define TIMER_MCHCTL2_MCH1FP             BITS(2,3)                                  /*!< multi mode channel 1 capture or compare function polarity */
#define TIMER_MCHCTL2_MCH2FP             BITS(4,5)                                  /*!< multi mode channel 2 capture or compare function polarity */
#define TIMER_MCHCTL2_MCH3FP             BITS(6,7)                                  /*!< multi mode channel 3 capture or compare function polarity */

/* TIMER_MCH0CV */
#define TIMER_MCH0CV_MCH0VAL             BITS(0,15)                                 /*!< 16 bit capture or compare value of multi mode channel 0 */

/* TIMER_MCH1CV */
#define TIMER_MCH1CV_MCH1VAL             BITS(0,15)                                 /*!< 16 bit capture or compare value of multi mode channel 1 */

/* TIMER_MCH2CV */
#define TIMER_MCH2CV_MCH2VAL             BITS(0,15)                                 /*!< 16 bit capture or compare value of multi mode channel 2 */

/* TIMER_MCH3CV */
#define TIMER_MCH3CV_MCH3VAL             BITS(0,15)                                 /*!< 16 bit capture or compare value of multi mode channel 3 */

/* TIMER_CH0COMV_ADD */
#define TIMER_CH0COMV_ADD_CH0COMVAL      BITS(0,15)                                 /*!< additional compare value of channel 0 */

/* TIMER_CH1COMV_ADD */
#define TIMER_CH1COMV_ADD_CH1COMVAL      BITS(0,15)                                 /*!< additional compare value of channel 1 */

/* TIMER_CH2COMV_ADD */
#define TIMER_CH2COMV_ADD_CH2COMVAL      BITS(0,15)                                 /*!< additional compare value of channel 2 */

/* TIMER_CH3COMV_ADD */
#define TIMER_CH3COMV_ADD_CH3COMVAL      BITS(0,15)                                 /*!< additional compare value of channel 3 */

/* TIMER_CTL2 */
#define TIMER_CTL2_DTIENCH0              BIT(0)                                     /*!< dead time inserted enable for channel 0 and channel 0N */
#define TIMER_CTL2_DTIENCH1              BIT(1)                                     /*!< dead time inserted enable for channel 1 and channel 1N */
#define TIMER_CTL2_DTIENCH2              BIT(2)                                     /*!< dead time inserted enable for channel 2 and channel 2N */
#define TIMER_CTL2_DTIENCH3              BIT(3)                                     /*!< dead time inserted enable for channel 3 and channel 3N */
#define TIMER_CTL2_BRKENCH0              BIT(4)                                     /*!< break control enable for channel 0 and multi mode channel 0 */
#define TIMER_CTL2_BRKENCH1              BIT(5)                                     /*!< break control enable for channel 1 and multi mode channel 1 */
#define TIMER_CTL2_BRKENCH2              BIT(6)                                     /*!< break control enable for channel 2 and multi mode channel 2 */
#define TIMER_CTL2_BRKENCH3              BIT(7)                                     /*!< break control enable for channel 3 and multi mode channel 3 */
#define TIMER_CTL2_CH0OMPSEL             BITS(8,9)                                  /*!< channel 0 output march pulse select */
#define TIMER_CTL2_CH1OMPSEL             BITS(10,11)                                /*!< channel 1 output march pulse select */
#define TIMER_CTL2_CH2OMPSEL             BITS(12,13)                                /*!< channel 2 output march pulse select */
#define TIMER_CTL2_CH3OMPSEL             BITS(14,15)                                /*!< channel 3 output march pulse select */
#define TIMER_CTL2_DECJDEN               BIT(18)                                    /*!< quadrature decoder signal jump (the two signals jump at the same time) detection enable */
#define TIMER_CTL2_DECDISDEN             BIT(19)                                    /*!< quadrature decoder signal disconnection detection enable */
#define TIMER_CTL2_MCH0MSEL              BITS(20,21)                                /*!< multi mode channel 0 mode select */
#define TIMER_CTL2_MCH1MSEL              BITS(22,23)                                /*!< multi mode channel 1 mode select */
#define TIMER_CTL2_MCH2MSEL              BITS(24,25)                                /*!< multi mode channel 2 mode select */
#define TIMER_CTL2_MCH3MSEL              BITS(26,27)                                /*!< multi mode channel 3 mode select */
#define TIMER_CTL2_CH0CPWMEN             BIT(28)                                    /*!< channel 0 composite PWM mode enable */
#define TIMER_CTL2_CH1CPWMEN             BIT(29)                                    /*!< channel 1 composite PWM mode enable */
#define TIMER_CTL2_CH2CPWMEN             BIT(30)                                    /*!< channel 2 composite PWM mode enable */
#define TIMER_CTL2_CH3CPWMEN             BIT(31)                                    /*!< channel 3 composite PWM mode enable */

/* TIMER_FCCHP0 */
#define TIMER_FCCHP0_DTCFG               BITS(0,7)                                  /*!< dead time configure */
#define TIMER_FCCHP0_IOS                 BIT(10)                                    /*!< idle mode off-state configure */
#define TIMER_FCCHP0_ROS                 BIT(11)                                    /*!< run mode off-state configure */
#define TIMER_FCCHP0_FCCHP0EN            BIT(31)                                    /*!< free complementary channel protection register 0 enable */

/* TIMER_FCCHP1 */
#define TIMER_FCCHP1_DTCFG               BITS(0,7)                                  /*!< dead time configure */
#define TIMER_FCCHP1_IOS                 BIT(10)                                    /*!< idle mode off-state configure */
#define TIMER_FCCHP1_ROS                 BIT(11)                                    /*!< run mode off-state configure */
#define TIMER_FCCHP1_FCCHP1EN            BIT(31)                                    /*!< free complementary channel protection register 1 enable */

/* TIMER_FCCHP2 */
#define TIMER_FCCHP2_DTCFG               BITS(0,7)                                  /*!< dead time configure */
#define TIMER_FCCHP2_IOS                 BIT(10)                                    /*!< idle mode off-state configure */
#define TIMER_FCCHP2_ROS                 BIT(11)                                    /*!< run mode off-state configure */
#define TIMER_FCCHP2_FCCHP2EN            BIT(31)                                    /*!< free complementary channel protection register 2 enable */

/* TIMER_FCCHP3 */
#define TIMER_FCCHP3_DTCFG               BITS(0,7)                                  /*!< dead time configure */
#define TIMER_FCCHP3_IOS                 BIT(10)                                    /*!< idle mode off-state configure */
#define TIMER_FCCHP3_ROS                 BIT(11)                                    /*!< run mode off-state configure */
#define TIMER_FCCHP3_FCCHP3EN            BIT(31)                                    /*!< free complementary channel protection register 3 enable */

/* TIMER_AFCTL0 */
#define TIMER_AFCTL0_BRK0IN0EN           BIT(0)                                     /*!< BREAK0 BRKIN0 alternate function input enable */
#define TIMER_AFCTL0_BRK0IN1EN           BIT(1)                                     /*!< BREAK0 BRKIN1 alternate function input enable */
#define TIMER_AFCTL0_BRK0IN2EN           BIT(2)                                     /*!< BREAK0 BRKIN2 alternate function input enable */
#define TIMER_AFCTL0_BRK0HPDFEN          BIT(8)                                     /*!< BREAK0 HPDF input enable */
#define TIMER_AFCTL0_BRK0CMP0EN          BIT(9)                                     /*!< BREAK0 CMP0 enable */
#define TIMER_AFCTL0_BRK0CMP1EN          BIT(10)                                    /*!< BREAK0 CMP1 enable */
#define TIMER_AFCTL0_BRK0IN0P            BIT(16)                                    /*!< BREAK0 BRKIN0 alternate function input polarity */
#define TIMER_AFCTL0_BRK0IN1P            BIT(17)                                    /*!< BREAK0 BRKIN1 alternate function input polarity */
#define TIMER_AFCTL0_BRK0IN2P            BIT(18)                                    /*!< BREAK0 BRKIN2 alternate function input polarity */
#define TIMER_AFCTL0_BRK0CMP0P           BIT(25)                                    /*!< BREAK0 CMP0 input polarity */
#define TIMER_AFCTL0_BRK0CMP1P           BIT(26)                                    /*!< BREAK0 CMP1 input polarity */

/* TIMER_AFCTL1 */
#define TIMER_AFCTL1_BRK1IN0EN           BIT(0)                                     /*!< BREAK1 BRKIN0 alternate function input enable */
#define TIMER_AFCTL1_BRK1IN1EN           BIT(1)                                     /*!< BREAK1 BRKIN1 alternate function input enable */
#define TIMER_AFCTL1_BRK1IN2EN           BIT(2)                                     /*!< BREAK1 BRKIN2 alternate function input enable */
#define TIMER_AFCTL1_BRK1HPDFEN          BIT(8)                                     /*!< BREAK1 HPDF input enable */
#define TIMER_AFCTL1_BRK1CMP0EN          BIT(9)                                     /*!< BREAK1 CMP0 enable */
#define TIMER_AFCTL1_BRK1CMP1EN          BIT(10)                                    /*!< BREAK1 CMP1 enable */
#define TIMER_AFCTL1_BRK1IN0P            BIT(16)                                    /*!< BREAK1 BRKIN0 alternate function input polarity */
#define TIMER_AFCTL1_BRK1IN1P            BIT(17)                                    /*!< BREAK1 BRKIN1 alternate function input polarity */
#define TIMER_AFCTL1_BRK1IN2P            BIT(18)                                    /*!< BREAK1 BRKIN2 alternate function input polarity */
#define TIMER_AFCTL1_BRK1CMP0P           BIT(25)                                    /*!< BREAK1 CMP0 input polarity */
#define TIMER_AFCTL1_BRK1CMP1P           BIT(26)                                    /*!< BREAK1 CMP1 input polarity */

/* TIMER_WDGPER */
#define TIMER_WDGPER_WDGPER              BITS(0,31)                                 /*!< watchdog counter period value */

/* TIMER_CREP1 */
#define TIMER_CREP1_CREP1                BITS(0,31)                                 /*!< counter repetition value 1 */

/* TIMER_DMACFG */
#define TIMER_DMACFG_DMATA               BITS(0,5)                                  /*!< DMA transfer access start address */
#define TIMER_DMACFG_DMATC               BITS(8,13)                                 /*!< DMA transfer count */

/* TIMER_DMATB */
#define TIMER_DMATB_DMATB                BITS(0,31)                                 /*!< DMA transfer buffer */

/* TIMER_CFG */
#define TIMER_CFG_OUTSEL                 BIT(0)                                     /*!< the output value selection */
#define TIMER_CFG_CHVSEL                 BIT(1)                                     /*!< write CHxVAL register selection */
#define TIMER_CFG_CREPSEL                BIT(2)                                     /*!< the counter repetition register selection */
#define TIMER_CFG_CCUSEL                 BIT(3)                                     /*!< commutation control shadow register update select */

/* constants definitions */
/* UPIFBU bit state */
typedef enum {VALID_RESET = 0, VALID_SET = 1, INVALID = 2} UPIFBUStatus;

/* TIMER init parameter struct definitions */
typedef struct {
    uint16_t prescaler;                                                             /*!< prescaler value */
    uint16_t alignedmode;                                                           /*!< aligned mode */
    uint16_t counterdirection;                                                      /*!< counter direction */
    uint64_t period;                                                                /*!< period value */
    uint16_t clockdivision;                                                         /*!< clock division value */
    uint32_t repetitioncounter;                                                     /*!< the counter repetition value */
} timer_parameter_struct;

/* break parameter struct definitions */
typedef struct {
    uint32_t runoffstate;                                                           /*!< run mode off-state */
    uint32_t ideloffstate;                                                          /*!< idle mode off-state */
    uint32_t deadtime;                                                              /*!< dead time */
    uint32_t outputautostate;                                                       /*!< output automatic enable */
    uint32_t protectmode;                                                           /*!< complementary register protect control */
    uint32_t break0state;                                                           /*!< BREAK0 input enable */
    uint32_t break0filter;                                                          /*!< BREAK0 input filter */
    uint32_t break0polarity;                                                        /*!< BREAK0 input polarity */
    uint32_t break0lock;                                                            /*!< BREAK0 input lock */
    uint32_t break0release;                                                         /*!< BREAK0 input release */
    uint32_t break1state;                                                           /*!< BREAK1 input enable */
    uint32_t break1filter;                                                          /*!< BREAK1 input filter */
    uint32_t break1polarity;                                                        /*!< BREAK1 input polarity */
    uint32_t break1lock;                                                            /*!< BREAK1 input lock */
    uint32_t break1release;                                                         /*!< BREAK1 input release */
} timer_break_parameter_struct;

/* channel output parameter struct definitions */
typedef struct {
    uint16_t outputstate;                                                           /*!< channel output state */
    uint16_t outputnstate;                                                          /*!< channel complementary output state */
    uint16_t ocpolarity;                                                            /*!< channel output polarity */
    uint16_t ocnpolarity;                                                           /*!< channel complementary output polarity */
    uint16_t ocidlestate;                                                           /*!< idle state of channel output */
    uint16_t ocnidlestate;                                                          /*!< idle state of channel complementary output */
} timer_oc_parameter_struct;

/* multi mode channel output parameter struct definitions */
typedef struct {
    uint16_t outputmode;                                                            /*!< multi mode channel output mode selection */
    uint16_t outputstate;                                                           /*!< multi mode channel output state */
    uint16_t ocpolarity;                                                            /*!< multi mode channel output polarity */
} timer_omc_parameter_struct;

/* channel input parameter struct definitions */
typedef struct {
    uint16_t icpolarity;                                                            /*!< channel input polarity */
    uint16_t icselection;                                                           /*!< channel input mode selection */
    uint16_t icprescaler;                                                           /*!< channel input capture prescaler */
    uint16_t icfilter;                                                              /*!< channel input capture filter control */
} timer_ic_parameter_struct;

/* channel free complementary parameter struct definitions */
typedef struct {
    uint32_t freecomstate;                                                          /*!< free complementary channel protection enable */
    uint32_t runoffstate;                                                           /*!< run mode off-state */
    uint32_t ideloffstate;                                                          /*!< idle mode off-state */
    uint32_t deadtime;                                                              /*!< dead time */
} timer_free_complementary_parameter_struct;

/* TIMER interrupt enable or disable */
#define TIMER_INT_UP                        TIMER_DMAINTEN_UPIE                     /*!< update interrupt */
#define TIMER_INT_CH0                       TIMER_DMAINTEN_CH0IE                    /*!< channel 0 capture or compare interrupt */
#define TIMER_INT_CH1                       TIMER_DMAINTEN_CH1IE                    /*!< channel 1 capture or compare interrupt */
#define TIMER_INT_CH2                       TIMER_DMAINTEN_CH2IE                    /*!< channel 2 capture or compare interrupt */
#define TIMER_INT_CH3                       TIMER_DMAINTEN_CH3IE                    /*!< channel 3 capture or compare interrupt */
#define TIMER_INT_CMT                       TIMER_DMAINTEN_CMTIE                    /*!< channel commutation interrupt flag */
#define TIMER_INT_TRG                       TIMER_DMAINTEN_TRGIE                    /*!< trigger interrupt */
#define TIMER_INT_BRK                       TIMER_DMAINTEN_BRKIE                    /*!< break interrupt */
#define TIMER_INT_DECJ                      TIMER_DMAINTEN_DECJIE                   /*!< quadrature decoder signal jump (the two signals jump at the same time) interrupt */
#define TIMER_INT_DECDIS                    TIMER_DMAINTEN_DECDISIE                 /*!< quadrature decoder signal disconnection interrupt */
#define TIMER_INT_MCH0                      TIMER_DMAINTEN_MCH0IE                   /*!< multi mode channel 0 capture or compare interrupt */
#define TIMER_INT_MCH1                      TIMER_DMAINTEN_MCH1IE                   /*!< multi mode channel 1 capture or compare interrupt */
#define TIMER_INT_MCH2                      TIMER_DMAINTEN_MCH2IE                   /*!< multi mode channel 2 capture or compare interrupt */
#define TIMER_INT_MCH3                      TIMER_DMAINTEN_MCH3IE                   /*!< multi mode channel 3 capture or compare interrupt */
#define TIMER_INT_CH0COMADD                 TIMER_DMAINTEN_CH0COMADDIE              /*!< channel 0 additional compare interrupt */
#define TIMER_INT_CH1COMADD                 TIMER_DMAINTEN_CH1COMADDIE              /*!< channel 1 additional compare interrupt */
#define TIMER_INT_CH2COMADD                 TIMER_DMAINTEN_CH2COMADDIE              /*!< channel 2 additional compare interrupt */
#define TIMER_INT_CH3COMADD                 TIMER_DMAINTEN_CH3COMADDIE              /*!< channel 3 additional compare interrupt */

/* TIMER interrupt flag */
#define TIMER_INT_FLAG_UP                   TIMER_INTF_UPIF                         /*!< update interrupt flag */
#define TIMER_INT_FLAG_CH0                  TIMER_INTF_CH0IF                        /*!< channel 0 capture or compare interrupt flag */
#define TIMER_INT_FLAG_CH1                  TIMER_INTF_CH1IF                        /*!< channel 1 capture or compare interrupt flag */
#define TIMER_INT_FLAG_CH2                  TIMER_INTF_CH2IF                        /*!< channel 2 capture or compare interrupt flag */
#define TIMER_INT_FLAG_CH3                  TIMER_INTF_CH3IF                        /*!< channel 3 capture or compare interrupt flag */
#define TIMER_INT_FLAG_CMT                  TIMER_INTF_CMTIF                        /*!< channel commutation interrupt flag */
#define TIMER_INT_FLAG_TRG                  TIMER_INTF_TRGIF                        /*!< trigger interrupt flag */
#define TIMER_INT_FLAG_BRK0                 TIMER_INTF_BRK0IF                       /*!< BREAK0 interrupt flag */
#define TIMER_INT_FLAG_BRK1                 TIMER_INTF_BRK1IF                       /*!< BREAK1 interrupt flag */
#define TIMER_INT_FLAG_SYSB                 TIMER_INTF_SYSBIF                       /*!< system source break interrupt flag */
#define TIMER_INT_FLAG_DECJ                 TIMER_INTF_DECJIF                       /*!< quadrature decoder signal jump (the two signals jump at the same time) interrupt flag */
#define TIMER_INT_FLAG_DECDIS               TIMER_INTF_DECDISIF                     /*!< quadrature decoder signal disconnection interrupt flag */
#define TIMER_INT_FLAG_MCH0                 TIMER_INTF_MCH0IF                       /*!< multi mode channel 0 capture or compare interrupt flag */
#define TIMER_INT_FLAG_MCH1                 TIMER_INTF_MCH1IF                       /*!< multi mode channel 1 capture or compare interrupt flag */
#define TIMER_INT_FLAG_MCH2                 TIMER_INTF_MCH2IF                       /*!< multi mode channel 2 capture or compare interrupt flag */
#define TIMER_INT_FLAG_MCH3                 TIMER_INTF_MCH3IF                       /*!< multi mode channel 3 capture or compare interrupt flag */
#define TIMER_INT_FLAG_CH0COMADD            TIMER_INTF_CH0COMADDIF                  /*!< channel 0 additional compare interrupt flag */
#define TIMER_INT_FLAG_CH1COMADD            TIMER_INTF_CH1COMADDIF                  /*!< channel 1 additional compare interrupt flag */
#define TIMER_INT_FLAG_CH2COMADD            TIMER_INTF_CH2COMADDIF                  /*!< channel 2 additional compare interrupt flag */
#define TIMER_INT_FLAG_CH3COMADD            TIMER_INTF_CH3COMADDIF                  /*!< channel 3 additional compare interrupt flag */

/* TIMER flag */
#define TIMER_FLAG_UP                       TIMER_INTF_UPIF                         /*!< update flag */
#define TIMER_FLAG_CH0                      TIMER_INTF_CH0IF                        /*!< channel 0 capture or compare flag */
#define TIMER_FLAG_CH1                      TIMER_INTF_CH1IF                        /*!< channel 1 capture or compare flag */
#define TIMER_FLAG_CH2                      TIMER_INTF_CH2IF                        /*!< channel 2 capture or compare flag */
#define TIMER_FLAG_CH3                      TIMER_INTF_CH3IF                        /*!< channel 3 capture or compare flag */
#define TIMER_FLAG_CMT                      TIMER_INTF_CMTIF                        /*!< channel commutation flag */
#define TIMER_FLAG_TRG                      TIMER_INTF_TRGIF                        /*!< trigger flag */
#define TIMER_FLAG_BRK0                     TIMER_INTF_BRK0IF                       /*!< BREAK0 flag */
#define TIMER_FLAG_BRK1                     TIMER_INTF_BRK1IF                       /*!< BREAK1 flag */
#define TIMER_FLAG_CH0O                     TIMER_INTF_CH0OF                        /*!< channel 0 overcapture flag */
#define TIMER_FLAG_CH1O                     TIMER_INTF_CH1OF                        /*!< channel 1 overcapture flag */
#define TIMER_FLAG_CH2O                     TIMER_INTF_CH2OF                        /*!< channel 2 overcapture flag */
#define TIMER_FLAG_CH3O                     TIMER_INTF_CH3OF                        /*!< channel 3 overcapture flag */
#define TIMER_FLAG_SYSB                     TIMER_INTF_SYSBIF                       /*!< system source break flag */
#define TIMER_FLAG_DECJ                     TIMER_INTF_DECJIF                       /*!< quadrature decoder signal jump (the two signals jump at the same time) flag */
#define TIMER_FLAG_DECDIS                   TIMER_INTF_DECDISIF                     /*!< quadrature decoder signal disconnection flag */
#define TIMER_FLAG_MCH0                     TIMER_INTF_MCH0IF                       /*!< multi mode channel 0 capture or compare flag */
#define TIMER_FLAG_MCH1                     TIMER_INTF_MCH1IF                       /*!< multi mode channel 1 capture or compare flag */
#define TIMER_FLAG_MCH2                     TIMER_INTF_MCH2IF                       /*!< multi mode channel 2 capture or compare flag */
#define TIMER_FLAG_MCH3                     TIMER_INTF_MCH3IF                       /*!< multi mode channel 3 capture or compare flag */
#define TIMER_FLAG_MCH0O                    TIMER_INTF_MCH0OF                       /*!< multi mode channel 0 overcapture flag */
#define TIMER_FLAG_MCH1O                    TIMER_INTF_MCH1OF                       /*!< multi mode channel 1 overcapture flag */
#define TIMER_FLAG_MCH2O                    TIMER_INTF_MCH2OF                       /*!< multi mode channel 2 overcapture flag */
#define TIMER_FLAG_MCH3O                    TIMER_INTF_MCH3OF                       /*!< multi mode channel 3 overcapture flag */
#define TIMER_FLAG_CH0COMADD                TIMER_INTF_CH0COMADDIF                  /*!< channel 0 additional compare flag */
#define TIMER_FLAG_CH1COMADD                TIMER_INTF_CH1COMADDIF                  /*!< channel 1 additional compare flag */
#define TIMER_FLAG_CH2COMADD                TIMER_INTF_CH2COMADDIF                  /*!< channel 2 additional compare flag */
#define TIMER_FLAG_CH3COMADD                TIMER_INTF_CH3COMADDIF                  /*!< channel 3 additional compare flag */

/* TIMER DMA source */
#define TIMER_DMA_UPD                       TIMER_DMAINTEN_UPDEN                    /*!< update DMA request */
#define TIMER_DMA_CH0D                      TIMER_DMAINTEN_CH0DEN                   /*!< channel 0 capture or compare DMA request */
#define TIMER_DMA_CH1D                      TIMER_DMAINTEN_CH1DEN                   /*!< channel 1 capture or compare DMA request */
#define TIMER_DMA_CH2D                      TIMER_DMAINTEN_CH2DEN                   /*!< channel 2 capture or compare DMA request */
#define TIMER_DMA_CH3D                      TIMER_DMAINTEN_CH3DEN                   /*!< channel 3 capture or compare DMA request */
#define TIMER_DMA_CMTD                      TIMER_DMAINTEN_CMTDEN                   /*!< commutation DMA request */
#define TIMER_DMA_TRGD                      TIMER_DMAINTEN_TRGDEN                   /*!< trigger DMA request */
#define TIMER_DMA_MCH0D                     TIMER_DMAINTEN_MCH0DEN                  /*!< multi mode channel 0 capture or compare DMA request */
#define TIMER_DMA_MCH1D                     TIMER_DMAINTEN_MCH1DEN                  /*!< multi mode channel 1 capture or compare DMA request */
#define TIMER_DMA_MCH2D                     TIMER_DMAINTEN_MCH2DEN                  /*!< multi mode channel 2 capture or compare DMA request */
#define TIMER_DMA_MCH3D                     TIMER_DMAINTEN_MCH3DEN                  /*!< multi mode channel 3 capture or compare DMA request */

/* channel DMA request source selection */
#define TIMER_DMAREQUEST_UPDATEEVENT        TIMER_CTL1_DMAS                         /*!< DMA request of channel n is sent when update event occurs */
#define TIMER_DMAREQUEST_CHANNELEVENT       ((uint32_t)0x00000000U)                 /*!< DMA request of channel n is sent when channel n event occurs */

/* DMA access base address */
#define DMACFG_DMATA(regval)                (BITS(0,5) & ((uint32_t)(regval) << 0U))
#define TIMER_DMACFG_DMATA_CTL0             DMACFG_DMATA(0)                         /*!< DMA transfer address is TIMER_CTL0 */
#define TIMER_DMACFG_DMATA_CTL1             DMACFG_DMATA(1)                         /*!< DMA transfer address is TIMER_CTL1 */
#define TIMER_DMACFG_DMATA_SMCFG            DMACFG_DMATA(2)                         /*!< DMA transfer address is TIMER_SMCFG */
#define TIMER_DMACFG_DMATA_DMAINTEN         DMACFG_DMATA(3)                         /*!< DMA transfer address is TIMER_DMAINTEN */
#define TIMER_DMACFG_DMATA_INTF             DMACFG_DMATA(4)                         /*!< DMA transfer address is TIMER_INTF */
#define TIMER_DMACFG_DMATA_SWEVG            DMACFG_DMATA(5)                         /*!< DMA transfer address is TIMER_SWEVG */
#define TIMER_DMACFG_DMATA_CHCTL0           DMACFG_DMATA(6)                         /*!< DMA transfer address is TIMER_CHCTL0 */
#define TIMER_DMACFG_DMATA_CHCTL1           DMACFG_DMATA(7)                         /*!< DMA transfer address is TIMER_CHCTL1 */
#define TIMER_DMACFG_DMATA_CHCTL2           DMACFG_DMATA(8)                         /*!< DMA transfer address is TIMER_CHCTL2 */
#define TIMER_DMACFG_DMATA_CNT              DMACFG_DMATA(9)                         /*!< DMA transfer address is TIMER_CNT */
#define TIMER_DMACFG_DMATA_PSC              DMACFG_DMATA(10)                        /*!< DMA transfer address is TIMER_PSC */
#define TIMER_DMACFG_DMATA_CAR              DMACFG_DMATA(11)                        /*!< DMA transfer address is TIMER_CAR */
#define TIMER_DMACFG_DMATA_CREP0            DMACFG_DMATA(12)                        /*!< DMA transfer address is TIMER_CREP0 */
#define TIMER_DMACFG_DMATA_CH0CV            DMACFG_DMATA(13)                        /*!< DMA transfer address is TIMER_CH0CV */
#define TIMER_DMACFG_DMATA_CH1CV            DMACFG_DMATA(14)                        /*!< DMA transfer address is TIMER_CH1CV */
#define TIMER_DMACFG_DMATA_CH2CV            DMACFG_DMATA(15)                        /*!< DMA transfer address is TIMER_CH2CV */
#define TIMER_DMACFG_DMATA_CH3CV            DMACFG_DMATA(16)                        /*!< DMA transfer address is TIMER_CH3CV */
#define TIMER_DMACFG_DMATA_CCHP             DMACFG_DMATA(17)                        /*!< DMA transfer address is TIMER_CCHP */
#define TIMER_DMACFG_DMATA_MCHCTL0          DMACFG_DMATA(18)                        /*!< DMA transfer address is TIMER_MCHCTL0 */
#define TIMER_DMACFG_DMATA_MCHCTL1          DMACFG_DMATA(19)                        /*!< DMA transfer address is TIMER_MCHCTL1 */
#define TIMER_DMACFG_DMATA_MCHCTL2          DMACFG_DMATA(20)                        /*!< DMA transfer address is TIMER_MCHCTL2 */
#define TIMER_DMACFG_DMATA_MCH0CV           DMACFG_DMATA(21)                        /*!< DMA transfer address is TIMER_MCH0CV */
#define TIMER_DMACFG_DMATA_MCH1CV           DMACFG_DMATA(22)                        /*!< DMA transfer address is TIMER_MCH1CV */
#define TIMER_DMACFG_DMATA_MCH2CV           DMACFG_DMATA(23)                        /*!< DMA transfer address is TIMER_MCH2CV */
#define TIMER_DMACFG_DMATA_MCH3CV           DMACFG_DMATA(24)                        /*!< DMA transfer address is TIMER_MCH3CV */
#define TIMER_DMACFG_DMATA_CH0COMV_ADD      DMACFG_DMATA(25)                        /*!< DMA transfer address is TIMER_CH0COMV_ADD */
#define TIMER_DMACFG_DMATA_CH1COMV_ADD      DMACFG_DMATA(26)                        /*!< DMA transfer address is TIMER_CH1COMV_ADD */
#define TIMER_DMACFG_DMATA_CH2COMV_ADD      DMACFG_DMATA(27)                        /*!< DMA transfer address is TIMER_CH2COMV_ADD */
#define TIMER_DMACFG_DMATA_CH3COMV_ADD      DMACFG_DMATA(28)                        /*!< DMA transfer address is TIMER_CH3COMV_ADD */
#define TIMER_DMACFG_DMATA_CTL2             DMACFG_DMATA(29)                        /*!< DMA transfer address is TIMER_CTL2 */
#define TIMER_DMACFG_DMATA_FCCHP0           DMACFG_DMATA(30)                        /*!< DMA transfer address is TIMER_FCCHP0 */
#define TIMER_DMACFG_DMATA_FCCHP1           DMACFG_DMATA(31)                        /*!< DMA transfer address is TIMER_FCCHP1 */
#define TIMER_DMACFG_DMATA_FCCHP2           DMACFG_DMATA(32)                        /*!< DMA transfer address is TIMER_FCCHP2 */
#define TIMER_DMACFG_DMATA_FCCHP3           DMACFG_DMATA(33)                        /*!< DMA transfer address is TIMER_FCCHP3 */
#define TIMER_DMACFG_DMATA_AFCTL0           DMACFG_DMATA(34)                        /*!< DMA transfer address is TIMER_AFCTL0 */
#define TIMER_DMACFG_DMATA_AFCTL1           DMACFG_DMATA(35)                        /*!< DMA transfer address is TIMER_AFCTL1 */
#define TIMER_DMACFG_DMATA_WDGPER           DMACFG_DMATA(36)                        /*!< DMA transfer address is TIMER_WDGPER */
#define TIMER_DMACFG_DMATA_CREP1            DMACFG_DMATA(37)                        /*!< DMA transfer address is TIMER_CREP1 */

/* DMA access burst length */
#define DMACFG_DMATC(regval)                (BITS(8,13) & ((uint32_t)(regval) << 8U))
#define TIMER_DMACFG_DMATC_1TRANSFER        DMACFG_DMATC(0)                         /*!< DMA transfer 1 time */
#define TIMER_DMACFG_DMATC_2TRANSFER        DMACFG_DMATC(1)                         /*!< DMA transfer 2 times */
#define TIMER_DMACFG_DMATC_3TRANSFER        DMACFG_DMATC(2)                         /*!< DMA transfer 3 times */
#define TIMER_DMACFG_DMATC_4TRANSFER        DMACFG_DMATC(3)                         /*!< DMA transfer 4 times */
#define TIMER_DMACFG_DMATC_5TRANSFER        DMACFG_DMATC(4)                         /*!< DMA transfer 5 times */
#define TIMER_DMACFG_DMATC_6TRANSFER        DMACFG_DMATC(5)                         /*!< DMA transfer 6 times */
#define TIMER_DMACFG_DMATC_7TRANSFER        DMACFG_DMATC(6)                         /*!< DMA transfer 7 times */
#define TIMER_DMACFG_DMATC_8TRANSFER        DMACFG_DMATC(7)                         /*!< DMA transfer 8 times */
#define TIMER_DMACFG_DMATC_9TRANSFER        DMACFG_DMATC(8)                         /*!< DMA transfer 9 times */
#define TIMER_DMACFG_DMATC_10TRANSFER       DMACFG_DMATC(9)                         /*!< DMA transfer 10 times */
#define TIMER_DMACFG_DMATC_11TRANSFER       DMACFG_DMATC(10)                        /*!< DMA transfer 11 times */
#define TIMER_DMACFG_DMATC_12TRANSFER       DMACFG_DMATC(11)                        /*!< DMA transfer 12 times */
#define TIMER_DMACFG_DMATC_13TRANSFER       DMACFG_DMATC(12)                        /*!< DMA transfer 13 times */
#define TIMER_DMACFG_DMATC_14TRANSFER       DMACFG_DMATC(13)                        /*!< DMA transfer 14 times */
#define TIMER_DMACFG_DMATC_15TRANSFER       DMACFG_DMATC(14)                        /*!< DMA transfer 15 times */
#define TIMER_DMACFG_DMATC_16TRANSFER       DMACFG_DMATC(15)                        /*!< DMA transfer 16 times */
#define TIMER_DMACFG_DMATC_17TRANSFER       DMACFG_DMATC(16)                        /*!< DMA transfer 17 times */
#define TIMER_DMACFG_DMATC_18TRANSFER       DMACFG_DMATC(17)                        /*!< DMA transfer 18 times */
#define TIMER_DMACFG_DMATC_19TRANSFER       DMACFG_DMATC(18)                        /*!< DMA transfer 19 times */
#define TIMER_DMACFG_DMATC_20TRANSFER       DMACFG_DMATC(19)                        /*!< DMA transfer 20 times */
#define TIMER_DMACFG_DMATC_21TRANSFER       DMACFG_DMATC(20)                        /*!< DMA transfer 21 times */
#define TIMER_DMACFG_DMATC_22TRANSFER       DMACFG_DMATC(21)                        /*!< DMA transfer 22 times */
#define TIMER_DMACFG_DMATC_23TRANSFER       DMACFG_DMATC(22)                        /*!< DMA transfer 23 times */
#define TIMER_DMACFG_DMATC_24TRANSFER       DMACFG_DMATC(23)                        /*!< DMA transfer 24 times */
#define TIMER_DMACFG_DMATC_25TRANSFER       DMACFG_DMATC(24)                        /*!< DMA transfer 25 times */
#define TIMER_DMACFG_DMATC_26TRANSFER       DMACFG_DMATC(25)                        /*!< DMA transfer 26 times */
#define TIMER_DMACFG_DMATC_27TRANSFER       DMACFG_DMATC(26)                        /*!< DMA transfer 27 times */
#define TIMER_DMACFG_DMATC_28TRANSFER       DMACFG_DMATC(27)                        /*!< DMA transfer 28 times */
#define TIMER_DMACFG_DMATC_29TRANSFER       DMACFG_DMATC(28)                        /*!< DMA transfer 29 times */
#define TIMER_DMACFG_DMATC_30TRANSFER       DMACFG_DMATC(29)                        /*!< DMA transfer 30 times */
#define TIMER_DMACFG_DMATC_31TRANSFER       DMACFG_DMATC(30)                        /*!< DMA transfer 31 times */
#define TIMER_DMACFG_DMATC_32TRANSFER       DMACFG_DMATC(31)                        /*!< DMA transfer 32 times */
#define TIMER_DMACFG_DMATC_33TRANSFER       DMACFG_DMATC(32)                        /*!< DMA transfer 33 times */
#define TIMER_DMACFG_DMATC_34TRANSFER       DMACFG_DMATC(33)                        /*!< DMA transfer 34 times */
#define TIMER_DMACFG_DMATC_35TRANSFER       DMACFG_DMATC(34)                        /*!< DMA transfer 35 times */
#define TIMER_DMACFG_DMATC_36TRANSFER       DMACFG_DMATC(35)                        /*!< DMA transfer 36 times */
#define TIMER_DMACFG_DMATC_37TRANSFER       DMACFG_DMATC(36)                        /*!< DMA transfer 37 times */
#define TIMER_DMACFG_DMATC_38TRANSFER       DMACFG_DMATC(37)                        /*!< DMA transfer 38 times */

/* TIMER software event generation source */
#define TIMER_EVENT_SRC_UPG                 TIMER_SWEVG_UPG                         /*!< update event generation */
#define TIMER_EVENT_SRC_CH0G                TIMER_SWEVG_CH0G                        /*!< channel 0 capture or compare event generation */
#define TIMER_EVENT_SRC_CH1G                TIMER_SWEVG_CH1G                        /*!< channel 1 capture or compare event generation */
#define TIMER_EVENT_SRC_CH2G                TIMER_SWEVG_CH2G                        /*!< channel 2 capture or compare event generation */
#define TIMER_EVENT_SRC_CH3G                TIMER_SWEVG_CH3G                        /*!< channel 3 capture or compare event generation */
#define TIMER_EVENT_SRC_CMTG                TIMER_SWEVG_CMTG                        /*!< channel commutation event generation */
#define TIMER_EVENT_SRC_TRGG                TIMER_SWEVG_TRGG                        /*!< trigger event generation */
#define TIMER_EVENT_SRC_BRK0G               TIMER_SWEVG_BRK0G                       /*!< BREAK0 event generation */
#define TIMER_EVENT_SRC_BRK1G               TIMER_SWEVG_BRK1G                       /*!< BREAK1 event generation */
#define TIMER_EVENT_SRC_MCH0G               TIMER_SWEVG_MCH0G                       /*!< multi mode channel 0 capture or compare event generation */
#define TIMER_EVENT_SRC_MCH1G               TIMER_SWEVG_MCH1G                       /*!< multi mode channel 1 capture or compare event generation */
#define TIMER_EVENT_SRC_MCH2G               TIMER_SWEVG_MCH2G                       /*!< multi mode channel 2 capture or compare event generation */
#define TIMER_EVENT_SRC_MCH3G               TIMER_SWEVG_MCH3G                       /*!< multi mode channel 3 capture or compare event generation */
#define TIMER_EVENT_SRC_CH0COMADDG          TIMER_SWEVG_CH0COMADDG                  /*!< channel 0 additional compare event generation */
#define TIMER_EVENT_SRC_CH1COMADDG          TIMER_SWEVG_CH1COMADDG                  /*!< channel 1 additional compare event generation */
#define TIMER_EVENT_SRC_CH2COMADDG          TIMER_SWEVG_CH2COMADDG                  /*!< channel 2 additional compare event generation */
#define TIMER_EVENT_SRC_CH3COMADDG          TIMER_SWEVG_CH3COMADDG                  /*!< channel 3 additional compare event generation */

/* center-aligned mode selection */
#define CTL0_CAM(regval)                    ((uint16_t)(BITS(5,6) & ((uint32_t)(regval) << 5U)))
#define TIMER_COUNTER_EDGE                  CTL0_CAM(0)                             /*!< edge-aligned mode */
#define TIMER_COUNTER_CENTER_DOWN           CTL0_CAM(1)                             /*!< center-aligned and counting down assert mode */
#define TIMER_COUNTER_CENTER_UP             CTL0_CAM(2)                             /*!< center-aligned and counting up assert mode */
#define TIMER_COUNTER_CENTER_BOTH           CTL0_CAM(3)                             /*!< center-aligned and counting up/down assert mode */

/* TIMER prescaler reload mode */
#define TIMER_PSC_RELOAD_NOW                TIMER_SWEVG_UPG                         /*!< the prescaler is loaded right now */
#define TIMER_PSC_RELOAD_UPDATE             ((uint32_t)0x00000000U)                 /*!< the prescaler is loaded at the next update event */

/* count direction */
#define TIMER_COUNTER_UP                    ((uint16_t)0x0000U)                     /*!< counter up direction */
#define TIMER_COUNTER_DOWN                  ((uint16_t)TIMER_CTL0_DIR)              /*!< counter down direction */

/* specify division ratio between TIMER clock and dead-time and sampling clock */
#define CTL0_CKDIV(regval)                  ((uint16_t)(BITS(8,9) & ((uint32_t)(regval) << 8U)))
#define TIMER_CKDIV_DIV1                    CTL0_CKDIV(0)                           /*!< clock division value is 1, fDTS = fTIMER_CK */
#define TIMER_CKDIV_DIV2                    CTL0_CKDIV(1)                           /*!< clock division value is 2, fDTS = fTIMER_CK/2 */
#define TIMER_CKDIV_DIV4                    CTL0_CKDIV(2)                           /*!< clock division value is 4, fDTS = fTIMER_CK/4 */

/* single pulse mode */
#define TIMER_SP_MODE_SINGLE                TIMER_CTL0_SPM                          /*!< single pulse mode */
#define TIMER_SP_MODE_REPETITIVE            ((uint32_t)0x00000000U)                 /*!< repetitive pulse mode */

/* update source */
#define TIMER_UPDATE_SRC_REGULAR            TIMER_CTL0_UPS                          /*!< update generate only by counter overflow/underflow */
#define TIMER_UPDATE_SRC_GLOBAL             ((uint32_t)0x00000000U)                 /*!< update generate by setting of UPG bit or the counter overflow/underflow,or the slave mode controller trigger */

/* run mode off-state configure */
#define TIMER_ROS_STATE_ENABLE              ((uint32_t)TIMER_CCHP_ROS)              /*!< when POEN bit is set, the channel output signals(CHx_O/MCHx_O) are enabled, with relationship to CHxEN/CHxNEN bits */
#define TIMER_ROS_STATE_DISABLE             ((uint32_t)0x00000000U)                 /*!< when POEN bit is set, the channel output signals(CHx_O/MCHx_O) are disabled */

/* idle mode off-state configure */
#define TIMER_IOS_STATE_ENABLE              ((uint32_t)TIMER_CCHP_IOS)              /*!< when POEN bit is reset, the channel output signals(CHx_O/MCHx_O) are enabled, with relationship to CHxEN/CHxNEN bits */
#define TIMER_IOS_STATE_DISABLE             ((uint32_t)0x00000000U)                 /*!< when POEN bit is reset, the channel output signals(CHx_O/MCHx_O) are disabled */

/* output automatic enable */
#define TIMER_OUTAUTO_ENABLE                ((uint32_t)TIMER_CCHP_OAEN)             /*!< output automatic enable */
#define TIMER_OUTAUTO_DISABLE               ((uint32_t)0x00000000U)                 /*!< output automatic disable */

/* complementary register protect control */
#define CCHP_PROT(regval)                   ((uint16_t)(BITS(8, 9) & ((uint32_t)(regval) << 8U)))
#define TIMER_CCHP_PROT_OFF                 CCHP_PROT(0)                            /*!< protect disable */
#define TIMER_CCHP_PROT_0                   CCHP_PROT(1)                            /*!< PROT mode 0 */
#define TIMER_CCHP_PROT_1                   CCHP_PROT(2)                            /*!< PROT mode 1 */
#define TIMER_CCHP_PROT_2                   CCHP_PROT(3)                            /*!< PROT mode 2 */

/* BREAK0 input signal enable */
#define TIMER_BREAK0_ENABLE                 ((uint32_t)TIMER_CCHP_BRK0EN)           /*!< BREAK0 input signal enable */
#define TIMER_BREAK0_DISABLE                ((uint32_t)0x00000000U)                 /*!< BREAK0 input signal disable */

/* BREAK0 input signal polarity */
#define TIMER_BREAK0_POLARITY_LOW           ((uint32_t)0x00000000U)                 /*!< BREAK0 input signal polarity is low */
#define TIMER_BREAK0_POLARITY_HIGH          ((uint32_t)TIMER_CCHP_BRK0P)            /*!< BREAK0 input signal polarity is high */

/* BREAK1 input signal enable */
#define TIMER_BREAK1_ENABLE                 ((uint32_t)TIMER_CCHP_BRK1EN)           /*!< BREAK1 input signal enable */
#define TIMER_BREAK1_DISABLE                ((uint32_t)0x00000000U)                 /*!< BREAK1 input signal disable */

/* BREAK1 input signal polarity */
#define TIMER_BREAK1_POLARITY_LOW           ((uint32_t)0x00000000U)                 /*!< BREAK1 input signal polarity is low */
#define TIMER_BREAK1_POLARITY_HIGH          ((uint32_t)TIMER_CCHP_BRK1P)            /*!< BREAK1 input signal polarity is high */

/* BREAK0 input released */
#define TIMER_BREAK0_RELEASE                ((uint32_t)TIMER_CCHP_BRK0REL)          /*!< BREAK0 input is released */
#define TIMER_BREAK0_UNRELEASE              ((uint32_t)0x00000000U)                 /*!< BREAK0 input is unreleased */

/* BREAK1 input released */
#define TIMER_BREAK1_RELEASE                ((uint32_t)TIMER_CCHP_BRK1REL)          /*!< BREAK1 input is released */
#define TIMER_BREAK1_UNRELEASE              ((uint32_t)0x00000000U)                 /*!< BREAK1 input is unreleased */

/* BREAK0 input locked */
#define TIMER_BREAK0_LK_ENABLE              ((uint32_t)TIMER_CCHP_BRK0LK)           /*!< BREAK0 input locked enable */
#define TIMER_BREAK0_LK_DISABLE             ((uint32_t)0x00000000U)                 /*!< BREAK0 input locked disable */

/* BREAK1 input locked */
#define TIMER_BREAK1_LK_ENABLE              ((uint32_t)TIMER_CCHP_BRK1LK)           /*!< BREAK1 input locked enable */
#define TIMER_BREAK1_LK_DISABLE             ((uint32_t)0x00000000U)                 /*!< BREAK1 input locked disable */

/* free complementary channel protection configure */
#define TIMER_FCCHP_STATE_ENABLE            ((uint32_t)TIMER_FCCHP0_FCCHP0EN)       /*!< free complementary channel protection enable */
#define TIMER_FCCHP_STATE_DISABLE           ((uint32_t)0x00000000U)                 /*!< free complementary channel protection disable */

/* TIMER BREAK0/BREAK1 */
#define TIMER_BREAK0                        ((uint16_t)0x0000U)                     /*!< TIMER BREAK0 */
#define TIMER_BREAK1                        ((uint16_t)0x0001U)                     /*!< TIMER BREAK1 */

/* TIMER break input enable */
#define TIMER_BRKIN0                        TIMER_AFCTL0_BRK0IN0EN                  /*!< BREAKx BRKIN0 alternate function input enable */
#define TIMER_BRKIN1                        TIMER_AFCTL0_BRK0IN1EN                  /*!< BREAKx BRKIN1 alternate function input enable */
#define TIMER_BRKIN2                        TIMER_AFCTL0_BRK0IN2EN                  /*!< BREAKx BRKIN2 alternate function input enable */
#define TIMER_BRKCMP0                       TIMER_AFCTL0_BRK0CMP0EN                 /*!< BREAKx CMP0 input enable */
#define TIMER_BRKCMP1                       TIMER_AFCTL0_BRK0CMP1EN                 /*!< BREAKx CMP1 input enable */
#define TIMER_BRKHPDF                       TIMER_AFCTL0_BRK0HPDFEN                 /*!< BREAKx HPDF input enable */

/* TIMER external break input polarity */
#define TIMER_BRKIN0P                       TIMER_AFCTL0_BRK0IN0P                   /*!< BREAKx BRKIN0 polarity */
#define TIMER_BRKIN1P                       TIMER_AFCTL0_BRK0IN1P                   /*!< BREAKx BRKIN1 polarity */
#define TIMER_BRKIN2P                       TIMER_AFCTL0_BRK0IN2P                   /*!< BREAKx BRKIN2 polarity */
#define TIMER_BRKCMP0P                      TIMER_AFCTL0_BRK0CMP0P                  /*!< BREAKx CMP0 polarity */
#define TIMER_BRKCMP1P                      TIMER_AFCTL0_BRK0CMP1P                  /*!< BREAKx CMP1 polarity */

/* TIMER break external input polarity*/
#define TIMER_BRKIN_POLARITY_LOW            ((uint16_t)0x0000U)                     /*!< TIMER break external input signal will not be inverted */
#define TIMER_BRKIN_POLARITY_HIGH           ((uint16_t)0x0001U)                     /*!< TIMER break external input signal will be inverted */

/* TIMER channel n(n=0,1,2,3) */
#define TIMER_CH_0                          ((uint16_t)0x0000U)                     /*!< TIMER channel 0 */
#define TIMER_CH_1                          ((uint16_t)0x0001U)                     /*!< TIMER channel 1 */
#define TIMER_CH_2                          ((uint16_t)0x0002U)                     /*!< TIMER channel 2 */
#define TIMER_CH_3                          ((uint16_t)0x0003U)                     /*!< TIMER channel 3 */
#define TIMER_MCH_0                         ((uint16_t)0x0010U)                     /*!< TIMER multi mode channel 0 */
#define TIMER_MCH_1                         ((uint16_t)0x0011U)                     /*!< TIMER multi mode channel 1 */
#define TIMER_MCH_2                         ((uint16_t)0x0012U)                     /*!< TIMER multi mode channel 2 */
#define TIMER_MCH_3                         ((uint16_t)0x0013U)                     /*!< TIMER multi mode channel 3 */

/* channel enable state */
#define TIMER_CCX_ENABLE                    ((uint16_t)0x0001U)                     /*!< channel enable */
#define TIMER_CCX_DISABLE                   ((uint16_t)0x0000U)                     /*!< channel disable */

/* channel complementary output enable state */
#define TIMER_CCXN_ENABLE                   ((uint16_t)0x0004U)                     /*!< channel complementary enable */
#define TIMER_CCXN_DISABLE                  ((uint16_t)0x0000U)                     /*!< channel complementary disable */

/* multi mode channel enable state */
#define TIMER_MCCX_ENABLE                   ((uint16_t)0x0004U)                     /*!< multi mode channel enable */
#define TIMER_MCCX_DISABLE                  ((uint16_t)0x0000U)                     /*!< multi mode channel disable */

/* channel output polarity */
#define TIMER_OC_POLARITY_HIGH              ((uint16_t)0x0000U)                     /*!< channel output polarity is high */
#define TIMER_OC_POLARITY_LOW               ((uint16_t)0x0002U)                     /*!< channel output polarity is low */

/* channel complementary output polarity */
#define TIMER_OCN_POLARITY_HIGH             ((uint16_t)0x0000U)                     /*!< channel complementary output polarity is high */
#define TIMER_OCN_POLARITY_LOW              ((uint16_t)0x0008U)                     /*!< channel complementary output polarity is low */

/* multi mode channel output polarity */
#define TIMER_OMC_POLARITY_HIGH             ((uint16_t)0x0000U)                     /*!< multi mode channel output polarity is high */
#define TIMER_OMC_POLARITY_LOW              ((uint16_t)0x0001U)                     /*!< multi mode channel output polarity is low */

/* idle state of channel output */
#define TIMER_OC_IDLE_STATE_HIGH            ((uint16_t)0x0100U)                     /*!< idle state of channel output is high */
#define TIMER_OC_IDLE_STATE_LOW             ((uint16_t)0x0000U)                     /*!< idle state of channel output is low */

/* idle state of channel complementary output */
#define TIMER_OCN_IDLE_STATE_HIGH           ((uint16_t)0x0200U)                     /*!< idle state of channel complementary output is high */
#define TIMER_OCN_IDLE_STATE_LOW            ((uint16_t)0x0000U)                     /*!< idle state of channel complementary output is low */

/* idle state of multi mode channel output */
#define TIMER_OMC_IDLE_STATE_HIGH           ((uint16_t)0x0100U)                     /*!< idle state of multi mode channel output is high */
#define TIMER_OMC_IDLE_STATE_LOW            ((uint16_t)0x0000U)                     /*!< idle state of multi mode channel output is low */

/* channel output compare mode */
#define TIMER_OC_MODE_TIMING                ((uint32_t)0x00000000U)                 /*!< timing mode */
#define TIMER_OC_MODE_ACTIVE                ((uint32_t)0x00000010U)                 /*!< active mode */
#define TIMER_OC_MODE_INACTIVE              ((uint32_t)0x00000020U)                 /*!< inactive mode */
#define TIMER_OC_MODE_TOGGLE                ((uint32_t)0x00000030U)                 /*!< toggle mode */
#define TIMER_OC_MODE_LOW                   ((uint32_t)0x00000040U)                 /*!< force low mode */
#define TIMER_OC_MODE_HIGH                  ((uint32_t)0x00000050U)                 /*!< force high mode */
#define TIMER_OC_MODE_PWM0                  ((uint32_t)0x00000060U)                 /*!< PWM mode 0 */
#define TIMER_OC_MODE_PWM1                  ((uint32_t)0x00000070U)                 /*!< PWM mode 1 */
#define TIMER_OC_MODE_DSPM0                 ((uint32_t)0x00010000U)                 /*!< delayable SPM mode 0 */
#define TIMER_OC_MODE_DSPM1                 ((uint32_t)0x00010010U)                 /*!< delayable SPM mode 1 */

/* channel output compare shadow enable */
#define TIMER_OC_SHADOW_ENABLE              ((uint16_t)0x0008U)                     /*!< channel output compare shadow enable */
#define TIMER_OC_SHADOW_DISABLE             ((uint16_t)0x0000U)                     /*!< channel output compare shadow disable */

/* channel output compare clear enable */
#define TIMER_OC_CLEAR_ENABLE               ((uint16_t)0x0080U)                     /*!< channel output clear function enable */
#define TIMER_OC_CLEAR_DISABLE              ((uint16_t)0x0000U)                     /*!< channel output clear function disable */

/* channel control shadow register update control */
#define CTL1_CCUC(regval)                   ((BIT(2) & ((uint32_t)(regval) << 2U)) | (BITS(30,31) & ((uint32_t)(regval) << 29U)))
#define TIMER_UPDATECTL_CCU                 CTL1_CCUC(0)                            /*!< the shadow registers update by when CMTG bit is set */
#define TIMER_UPDATECTL_CCUTRI              CTL1_CCUC(1)                            /*!< the shadow registers update by when CMTG bit is set or an rising edge of TRGI occurs */
#define TIMER_UPDATECTL_CCUOVER             CTL1_CCUC(4)                            /*!< the shadow registers update by when the overflow event occurs */
#define TIMER_UPDATECTL_CCUUNDER            CTL1_CCUC(5)                            /*!< the shadow registers update by when the underflow event occurs */
#define TIMER_UPDATECTL_CCUOVERUNDER        CTL1_CCUC(6)                            /*!< the shadow registers update by when the overflow or underflow event occurs */

/* channel input capture polarity */
#define TIMER_IC_POLARITY_RISING            ((uint16_t)0x0000U)                     /*!< input capture rising edge */
#define TIMER_IC_POLARITY_FALLING           ((uint16_t)0x0002U)                     /*!< input capture falling edge*/
#define TIMER_IC_POLARITY_BOTH_EDGE         ((uint16_t)0x000AU)                     /*!< input capture both edge */

/* TIMER input capture selection */
#define TIMER_IC_SELECTION_DIRECTTI         ((uint16_t)0x0001U)                     /*!< channel n is configured as input and icy is mapped on CIy / CINy */
#define TIMER_IC_SELECTION_INDIRECTTI       ((uint16_t)0x0002U)                     /*!< channel n is configured as input and icy is mapped on opposite input */
#define TIMER_IC_SELECTION_ITS              ((uint16_t)0x0003U)                     /*!< channel n is configured as input and icy is mapped on ITS */
#define TIMER_IC_SELECTION_PAIR             ((uint16_t)0x0004U)                     /*!< channel n is configured as input and icy is mapped on the other channel of same pair */

/* channel input capture prescaler */
#define TIMER_IC_PSC_DIV1                   ((uint16_t)0x0000U)                     /*!< no prescaler */
#define TIMER_IC_PSC_DIV2                   ((uint16_t)0x0004U)                     /*!< divided by 2 */
#define TIMER_IC_PSC_DIV4                   ((uint16_t)0x0008U)                     /*!< divided by 4 */
#define TIMER_IC_PSC_DIV8                   ((uint16_t)0x000CU)                     /*!< divided by 8 */

/* master mode control 0 */
#define CTL1_MMC0(regval)                   (BITS(4,6) & ((uint32_t)(regval) << 4U))
#define TIMER_TRI_OUT0_SRC_RESET            CTL1_MMC0(0)                            /*!< the UPG bit as trigger output 0 */
#define TIMER_TRI_OUT0_SRC_ENABLE           CTL1_MMC0(1)                            /*!< the counter enable signal as trigger output 0 */
#define TIMER_TRI_OUT0_SRC_UPDATE           CTL1_MMC0(2)                            /*!< update event as trigger output 0 */
#define TIMER_TRI_OUT0_SRC_CH0              CTL1_MMC0(3)                            /*!< a capture or a compare match occurred in channel 0 as trigger output 0 */
#define TIMER_TRI_OUT0_SRC_O0CPRE           CTL1_MMC0(4)                            /*!< O0CPRE as trigger output 0 */
#define TIMER_TRI_OUT0_SRC_O1CPRE           CTL1_MMC0(5)                            /*!< O1CPRE as trigger output 0 */
#define TIMER_TRI_OUT0_SRC_O2CPRE           CTL1_MMC0(6)                            /*!< O2CPRE as trigger output 0 */
#define TIMER_TRI_OUT0_SRC_O3CPRE           CTL1_MMC0(7)                            /*!< O3CPRE as trigger output 0 */

/* master mode control 1 */
#define CTL1_MMC1(regval)                   (BITS(20,22) & ((uint32_t)(regval) << 20U))
#define TIMER_TRI_OUT1_SRC_RESET            CTL1_MMC1(0)                            /*!< the UPG bit as trigger output 1 */
#define TIMER_TRI_OUT1_SRC_ENABLE           CTL1_MMC1(1)                            /*!< the counter enable signal TIMER_CTL0_CEN as trigger output 1 */
#define TIMER_TRI_OUT1_SRC_UPDATE           CTL1_MMC1(2)                            /*!< update event as trigger output 1 */
#define TIMER_TRI_OUT1_SRC_CH0              CTL1_MMC1(3)                            /*!< a capture or a compare match occurred in channel 0 as trigger output 1 */
#define TIMER_TRI_OUT1_SRC_O0CPRE           CTL1_MMC1(4)                            /*!< O0CPRE as trigger output 1 */
#define TIMER_TRI_OUT1_SRC_O1CPRE           CTL1_MMC1(5)                            /*!< O1CPRE as trigger output 1 */
#define TIMER_TRI_OUT1_SRC_O2CPRE           CTL1_MMC1(6)                            /*!< O2CPRE as trigger output 1 */
#define TIMER_TRI_OUT1_SRC_O3CPRE           CTL1_MMC1(7)                            /*!< O3CPRE as trigger output 1 */

/* TIMER decoder detection enable */
#define TIMER_DECJUMPDEN                    TIMER_CTL2_DECJDEN                      /*!< quadrature decoder signal jump (the two signals jump at the same time) detection enable */
#define TIMER_DECDISCONNECTDEN              TIMER_CTL2_DECDISDEN                    /*!< quadrature decoder signal disconnection detection enable */

/* master slave mode selection */
#define TIMER_MASTER_SLAVE_MODE_ENABLE      TIMER_SMCFG_MSM                         /*!< master slave mode enable */
#define TIMER_MASTER_SLAVE_MODE_DISABLE     ((uint32_t)0x00000000U)                 /*!< master slave mode disable */

/* external trigger prescaler */
#define SMCFG_ETPSC(regval)                 (BITS(12,13) & ((uint32_t)(regval) << 12U))
#define TIMER_EXT_TRI_PSC_OFF               SMCFG_ETPSC(0)                          /*!< no divided */
#define TIMER_EXT_TRI_PSC_DIV2              SMCFG_ETPSC(1)                          /*!< divided by 2 */
#define TIMER_EXT_TRI_PSC_DIV4              SMCFG_ETPSC(2)                          /*!< divided by 4 */
#define TIMER_EXT_TRI_PSC_DIV8              SMCFG_ETPSC(3)                          /*!< divided by 8 */

/* external trigger polarity */
#define TIMER_ETP_FALLING                   TIMER_SMCFG_ETP                         /*!< active low or falling edge active */
#define TIMER_ETP_RISING                    ((uint32_t)0x00000000U)                 /*!< active high or rising edge active */

/* channel 0 trigger input selection */
#define TIMER_HALLINTERFACE_ENABLE          TIMER_CTL1_TI0S                         /*!< TIMER hall sensor mode enable */
#define TIMER_HALLINTERFACE_DISABLE         ((uint32_t)0x00000000U)                 /*!< TIMER hall sensor mode disable */

/* TIMER write CHxVAL register selection */
#define TIMER_CHVSEL_ENABLE                 ((uint16_t)TIMER_CFG_CHVSEL)            /*!< write CHxVAL register selection enable */
#define TIMER_CHVSEL_DISABLE                ((uint16_t)0x0000U)                     /*!< write CHxVAL register selection disable */

/* TIMER output value selection enable */
#define TIMER_OUTSEL_ENABLE                 ((uint16_t)TIMER_CFG_OUTSEL)            /*!< output value selection enable */
#define TIMER_OUTSEL_DISABLE                ((uint16_t)0x0000U)                     /*!< output value selection disable */

/* TIMER commutation control shadow register update selection enable */
#define TIMER_CCUSEL_ENABLE                 ((uint16_t)TIMER_CFG_CCUSEL)            /*!< commutation control shadow register update selection enable */
#define TIMER_CCUSEL_DISABLE                ((uint16_t)0x0000U)                     /*!< commutation control shadow register update selection disable */

/* channel additional output compare shadow enable */
#define TIMER_ADD_SHADOW_ENABLE             ((uint16_t)0x0001U)                     /*!< channel additional output shadow state enable */
#define TIMER_ADD_SHADOW_DISABLE            ((uint16_t)0x0000U)                     /*!< channel additional output shadow state disable */

/* channel output compare shadow enable */
#define TIMER_OMC_SHADOW_ENABLE             ((uint16_t)0x0008U)                     /*!< multi mode channel output shadow state enable */
#define TIMER_OMC_SHADOW_DISABLE            ((uint16_t)0x0000U)                     /*!< multi mode channel output shadow state disable */

/* channel output compare clear enable */
#define TIMER_OMC_CLEAR_ENABLE              ((uint16_t)0x0080U)                     /*!< multi mode channel output clear function enable */
#define TIMER_OMC_CLEAR_DISABLE             ((uint16_t)0x0000U)                     /*!< multi mode channel output clear function disable */

/* TIMER counter repetition register selection */
#define TIMER_CREP1_ENABLE                  ((uint16_t)TIMER_CFG_CREPSEL)           /*!< the update event rate is depended to TIMERx_CREP1 register */
#define TIMER_CREP0_ENABLE                  ((uint16_t)0x0000U)                     /*!< the update event rate is depended to TIMERx_CREP0 register */

/* TIMER output value selection */
#define TIMER_PULSE_OUTPUT_NORMAL           ((uint16_t)0x0000U)                     /*!< channel output normal */
#define TIMER_PULSE_OUTPUT_CNT_UP           ((uint16_t)0x0001U)                     /*!< pulse output only when counting up */
#define TIMER_PULSE_OUTPUT_CNT_DOWN         ((uint16_t)0x0002U)                     /*!< pulse output only when counting down */
#define TIMER_PULSE_OUTPUT_CNT_BOTH         ((uint16_t)0x0003U)                     /*!< pulse output when counting up or down */
#define TIMER_PULSE_OUTPUT_MASK             ((uint16_t)0x0003U)                     /*!< pulse output mode mask */

/* multi mode channel input capture polarity */
#define TIMER_IMC_POLARITY_RISING           ((uint16_t)0x0000U)                     /*!< multi mode channel input capture rising edge */
#define TIMER_IMC_POLARITY_FALLING          ((uint16_t)0x0001U)                     /*!< multi mode channel input capture falling edge */
#define TIMER_IMC_POLARITY_BOTH_EDGE        ((uint16_t)0x0003U)                     /*!< multi mode channel input capture both edge */

/* channel output polarity */
#define TIMER_OC_MCH_POLARITY_HIGH          ((uint16_t)0x0000U)                     /*!< channel output polarity is high */
#define TIMER_OC_MCH_POLARITY_LOW           ((uint16_t)0x0001U)                     /*!< channel output polarity is low */

/* TIMER multi mode channel mode selection */
#define TIMER_MCH_MODE_INDEPENDENTLY        ((uint16_t)0x0000U)                     /*!< multi mode channel work in independently mode */
#define TIMER_MCH_MODE_COMPLEMENTARY        ((uint16_t)0x0003U)                     /*!< multi mode channel work in complementary output mode */
#define TIMER_MCH_MODE_MASK                 ((uint16_t)0x0003U)                     /*!< multi mode channel mode mask */

/* function declarations */
/* TIMER timebase */
/* deinit a TIMER */
void timer_deinit(uint32_t timer_periph);
/* initialize TIMER init parameter struct */
void timer_struct_para_init(timer_parameter_struct *initpara);
/* initialize TIMER counter */
void timer_init(uint32_t timer_periph, timer_parameter_struct *initpara);
/* enable a TIMER */
void timer_enable(uint32_t timer_periph);
/* disable a TIMER */
void timer_disable(uint32_t timer_periph);
/* enable the auto reload shadow function */
void timer_auto_reload_shadow_enable(uint32_t timer_periph);
/* disable the auto reload shadow function */
void timer_auto_reload_shadow_disable(uint32_t timer_periph);
/* enable the update event */
void timer_update_event_enable(uint32_t timer_periph);
/* disable the update event */
void timer_update_event_disable(uint32_t timer_periph);
/* set TIMER counter alignment mode */
void timer_counter_alignment(uint32_t timer_periph, uint16_t aligned);
/* set TIMER counter up direction */
void timer_counter_up_direction(uint32_t timer_periph);
/* set TIMER counter down direction */
void timer_counter_down_direction(uint32_t timer_periph);

/* configure TIMER prescaler */
void timer_prescaler_config(uint32_t timer_periph, uint16_t prescaler, uint32_t pscreload);
/* configure TIMER repetition register value */
void timer_repetition_value_config(uint32_t timer_periph, uint16_t ccsel, uint32_t repetition);
/* configure TIMER runtime repetition register value */
uint32_t timer_runtime_repetition_value_read(uint32_t timer_periph);
/* configure TIMER autoreload register value */
void timer_autoreload_value_config(uint32_t timer_periph, uint64_t autoreload);
/* read TIMER autoreload register value */
uint64_t timer_autoreload_value_read(uint32_t timer_periph);
/* configure TIMER counter register value */
void timer_counter_value_config(uint32_t timer_periph, uint64_t counter);
/* read TIMER counter value */
uint64_t timer_counter_read(uint32_t timer_periph);
/* read TIMER prescaler value */
uint16_t timer_prescaler_read(uint32_t timer_periph);
/* configure TIMER single pulse mode */
void timer_single_pulse_mode_config(uint32_t timer_periph, uint32_t spmode);
/* configure timer delayable single pulse mode */
void timer_delayable_single_pulse_mode_config(uint32_t timer_periph, uint16_t channel, uint32_t dspmode, uint16_t cnt_dir);
/* configure TIMER update source */
void timer_update_source_config(uint32_t timer_periph, uint32_t update);

/* TIMER DMA and event */
/* enable the TIMER DMA */
void timer_dma_enable(uint32_t timer_periph, uint32_t dma);
/* disable the TIMER DMA */
void timer_dma_disable(uint32_t timer_periph, uint32_t dma);
/* channel DMA request source selection */
void timer_channel_dma_request_source_select(uint32_t timer_periph, uint32_t dma_request);
/* configure the TIMER DMA transfer */
void timer_dma_transfer_config(uint32_t timer_periph, uint32_t dma_baseaddr, uint32_t dma_lenth);
/* software generate events */
void timer_event_software_generate(uint32_t timer_periph, uint32_t event);

/* TIMER channel complementary protection */
/* initialize TIMER break parameter struct */
void timer_break_struct_para_init(timer_break_parameter_struct *breakpara);
/* configure TIMER break function */
void timer_break_config(uint32_t timer_periph, timer_break_parameter_struct *breakpara);
/* enable TIMER break function */
void timer_break_enable(uint32_t timer_periph, uint16_t break_num);
/* disable TIMER break function */
void timer_break_disable(uint32_t timer_periph, uint16_t break_num);
/* enable TIMER output automatic function */
void timer_automatic_output_enable(uint32_t timer_periph);
/* disable TIMER output automatic function */
void timer_automatic_output_disable(uint32_t timer_periph);
/* configure TIMER primary output function */
void timer_primary_output_config(uint32_t timer_periph, ControlStatus newvalue);
/* configure channel commutation control shadow register */
void timer_channel_control_shadow_config(uint32_t timer_periph, ControlStatus newvalue);
/* configure TIMER channel control shadow register update control */
void timer_channel_control_shadow_update_config(uint32_t timer_periph, uint32_t ccuctl);

/* TIMER channel output */
/* initialize TIMER channel output parameter struct */
void timer_channel_output_struct_para_init(timer_oc_parameter_struct *ocpara);
/* configure TIMER channel output function */
void timer_channel_output_config(uint32_t timer_periph, uint16_t channel, timer_oc_parameter_struct *ocpara);
/* configure TIMER channel output compare mode */
void timer_channel_output_mode_config(uint32_t timer_periph, uint16_t channel, uint32_t ocmode);
/* configure TIMER channel output pulse value */
void timer_channel_output_pulse_value_config(uint32_t timer_periph, uint16_t channel, uint32_t pulse);
/* configure TIMER channel output shadow function */
void timer_channel_output_shadow_config(uint32_t timer_periph, uint16_t channel, uint16_t ocshadow);
/* configure TIMER channel output clear function */
void timer_channel_output_clear_config(uint32_t timer_periph, uint16_t channel, uint16_t occlear);
/* configure TIMER channel output polarity */
void timer_channel_output_polarity_config(uint32_t timer_periph, uint16_t channel, uint16_t ocpolarity);
/* configure TIMER channel complementary output polarity */
void timer_channel_complementary_output_polarity_config(uint32_t timer_periph, uint16_t channel, uint16_t ocnpolarity);
/* configure TIMER channel enable state */
void timer_channel_output_state_config(uint32_t timer_periph, uint16_t channel, uint32_t state);
/* configure TIMER channel complementary output enable state */
void timer_channel_complementary_output_state_config(uint32_t timer_periph, uint16_t channel, uint16_t ocnstate);

/* TIMER channel input */
/* initialize TIMER channel input parameter struct */
void timer_channel_input_struct_para_init(timer_ic_parameter_struct *icpara);
/* configure TIMER input capture parameter */
void timer_input_capture_config(uint32_t timer_periph, uint16_t channel, timer_ic_parameter_struct *icpara);
/* configure TIMER channel input capture prescaler value */
void timer_channel_input_capture_prescaler_config(uint32_t timer_periph, uint16_t channel, uint16_t prescaler);
/* read TIMER channel capture compare register value */
uint32_t timer_channel_capture_value_register_read(uint32_t timer_periph, uint16_t channel);
/* configure TIMER input pwm capture function */
void timer_input_pwm_capture_config(uint32_t timer_periph, uint16_t channel, timer_ic_parameter_struct *icpwm);
/* configure TIMER hall sensor mode */
void timer_hall_mode_config(uint32_t timer_periph, uint32_t hallmode);

/* TIMER multi mode channel */
/* initialize TIMER multi mode channel output parameter struct */
void timer_multi_mode_channel_output_parameter_struct_init(timer_omc_parameter_struct *omcpara);
/* configure TIMER multi mode channel output function */
void timer_multi_mode_channel_output_config(uint32_t timer_periph, uint16_t channel, timer_omc_parameter_struct *omcpara);
/* multi mode channel mode select */
void timer_multi_mode_channel_mode_config(uint32_t timer_periph, uint32_t channel, uint32_t multi_mode_sel);

/* TIMER master and slave mode */
/* select TIMER input trigger source */
void timer_input_trigger_source_select(uint32_t timer_periph, uint32_t intrigger);
/* select TIMER master mode output 0 trigger source */
void timer_master_output0_trigger_source_select(uint32_t timer_periph, uint32_t outrigger);
/* select TIMER master mode output 1 trigger source */
void timer_master_output1_trigger_source_select(uint32_t timer_periph, uint32_t outrigger);
/* select TIMER slave mode */
void timer_slave_mode_select(uint32_t timer_periph, uint32_t slavemode);
/* configure TIMER master slave mode */
void timer_master_slave_mode_config(uint32_t timer_periph, uint32_t masterslave);

/* configure TIMER external trigger input */
void timer_external_trigger_config(uint32_t timer_periph, uint32_t extprescaler, uint32_t extpolarity, uint32_t extfilter);
/* configure TIMER quadrature decoder mode */
void timer_quadrature_decoder_mode_config(uint32_t timer_periph, uint32_t decomode, uint16_t ic0polarity, uint16_t ic1polarity);
/* configure TIMER non-quadrature decoder mode */
void timer_non_quadrature_decoder_mode_config(uint32_t timer_periph, uint32_t decomode, uint16_t ic1polarity);
/* configure TIMER internal clock mode */
void timer_internal_clock_config(uint32_t timer_periph);
/* configure TIMER the internal trigger as external clock input */
void timer_internal_trigger_as_external_clock_config(uint32_t timer_periph, uint32_t intrigger);
/* configure TIMER the external trigger as external clock input */
void timer_external_trigger_as_external_clock_config(uint32_t timer_periph, uint32_t extrigger, uint16_t extpolarity, uint32_t extfilter);
/* configure TIMER the external clock mode 0 */
void timer_external_clock_mode0_config(uint32_t timer_periph, uint32_t extprescaler, uint32_t extpolarity, uint32_t extfilter);
/* configure TIMER the external clock mode 1 */
void timer_external_clock_mode1_config(uint32_t timer_periph, uint32_t extprescaler, uint32_t extpolarity, uint32_t extfilter);
/* disable TIMER the external clock mode 1 */
void timer_external_clock_mode1_disable(uint32_t timer_periph);

/* TIMER configure */
/* configure TIMER write CHxVAL register selection */
void timer_write_chxval_register_config(uint32_t timer_periph, uint16_t ccsel);
/* configure TIMER output value selection */
void timer_output_value_selection_config(uint32_t timer_periph, uint16_t outsel);
/* configure commutation control shadow register update selection */
void timer_commutation_control_shadow_register_config(uint32_t timer_periph, uint16_t ccssel);
/* configure TIMER output match pulse selection */
void timer_output_match_pulse_select(uint32_t timer_periph, uint32_t channel, uint16_t pulsesel);

/* TIMER composite PWM mode */
/* configure the TIMER composite PWM mode */
void timer_channel_composite_pwm_mode_config(uint32_t timer_periph, uint32_t channel, ControlStatus newvalue);
/* configure the TIMER composite PWM mode output pulse value */
void timer_channel_composite_pwm_mode_output_pulse_value_config(uint32_t timer_periph, uint32_t channel, uint32_t pulse, uint32_t add_pulse);
/* configure TIMER channel additional compare value */
void timer_channel_additional_compare_value_config(uint32_t timer_periph, uint16_t channel, uint32_t value);
/* configure TIMER channel additional output shadow function */
void timer_channel_additional_output_shadow_config(uint32_t timer_periph, uint16_t channel, uint16_t aocshadow);
/* read TIMER channel additional compare value */
uint32_t timer_channel_additional_compare_value_read(uint32_t timer_periph, uint16_t channel);

/* TIMER break external inputs */
/* configure TIMER break external source */
void timer_break_external_source_config(uint32_t timer_periph, uint16_t break_num, uint32_t break_src, ControlStatus newvalue);
/* configure TIMER break polarity */
void timer_break_external_polarity_config(uint32_t timer_periph, uint16_t break_num, uint32_t break_src, uint16_t bkinpolarity);
/* configure TIMER break lock function */
void timer_break_lock_config(uint32_t timer_periph, uint16_t break_num, ControlStatus newvalue);
/* configure the TIMER break lock release function */
void timer_break_lock_release_config(uint32_t timer_periph, uint16_t break_num, ControlStatus newvalue);

/* TIMER channel free complementary protection */
/* configure the TIMER channel break function */
void timer_channel_break_control_config(uint32_t timer_periph, uint32_t channel, ControlStatus newvalue);
/* configure the TIMER channel dead time function */
void timer_channel_dead_time_config(uint32_t timer_periph, uint32_t channel, ControlStatus newvalue);
/* initialize TIMER channel free complementary parameter struct with a default value */
void timer_free_complementary_struct_para_init(timer_free_complementary_parameter_struct *freecompara);
/* configure channel free complementary protection */
void timer_channel_free_complementary_config(uint32_t timer_periph, uint16_t channel, timer_free_complementary_parameter_struct *fcpara);

/* TIMER quadrature decoder signal detection function */
/* configure quadrature decoder signal disconnection detection watchdog value */
void timer_watchdog_value_config(uint32_t timer_periph, uint32_t value);
/* read quadrature decoder signal disconnection detection watchdog value */
uint32_t timer_watchdog_value_read(uint32_t timer_periph);
/* configure quadrature decoder signal disconnection detection function */
void timer_decoder_disconnection_detection_config(uint32_t timer_periph, ControlStatus newvalue);
/* configure decoder signal jump detection function */
void timer_decoder_jump_detection_config(uint32_t timer_periph, ControlStatus newvalue);

/* TIMER UPIF bit backup function */
/* configure the UPIF bit backup function */
void timer_upif_backup_config(uint32_t timer_periph, ControlStatus newvalue);
/* get the UPIFBU bit in the TIMERx_CNT register */
UPIFBUStatus timer_upifbu_bit_get(uint32_t timer_periph);

/* TIMER interrupt and flag */
/* get TIMER flags */
FlagStatus timer_flag_get(uint32_t timer_periph, uint32_t flag);
/* clear TIMER flags */
void timer_flag_clear(uint32_t timer_periph, uint32_t flag);
/* enable the TIMER interrupt */
void timer_interrupt_enable(uint32_t timer_periph, uint32_t interrupt);
/* disable the TIMER interrupt */
void timer_interrupt_disable(uint32_t timer_periph, uint32_t interrupt);
/* get TIMER interrupt flags */
FlagStatus timer_interrupt_flag_get(uint32_t timer_periph, uint32_t int_flag);
/* clear TIMER interrupt flags */
void timer_interrupt_flag_clear(uint32_t timer_periph, uint32_t int_flag);

#endif /* GD32H7XX_TIMER_H */
