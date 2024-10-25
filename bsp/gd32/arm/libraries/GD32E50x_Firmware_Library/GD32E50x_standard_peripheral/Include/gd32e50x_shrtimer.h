/*!
    \file    gd32e50x_shrtimer.h
    \brief   definitions for the SHRTIMER

    \version 2023-12-31, V1.4.0, firmware for GD32E50x
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

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

#ifndef GD32E50X_SHRTIMER_H
#define GD32E50X_SHRTIMER_H

#include "gd32e50x.h"

/* SHRTIMERy(y=0) definitions */
#define SHRTIMER0                                     (SHRTIMER_BASE + 0x00000000U)

/* registers definitions */
/* Master_TIMER registers definitions */
#define SHRTIMER_MTCTL0(shrtimery)                     REG32((shrtimery) + 0x00000000U)             /*!< SHRTIMER Master_TIMER control register 0 */
#define SHRTIMER_MTINTF(shrtimery)                     REG32((shrtimery) + 0x00000004U)             /*!< SHRTIMER Master_TIMER interrupt flag register */
#define SHRTIMER_MTINTC(shrtimery)                     REG32((shrtimery) + 0x00000008U)             /*!< SHRTIMER Master_TIMER interrupt flag clear register */
#define SHRTIMER_MTDMAINTEN(shrtimery)                 REG32((shrtimery) + 0x0000000CU)             /*!< SHRTIMER Master_TIMER DMA and interrupt enable register */
#define SHRTIMER_MTCNT(shrtimery)                      REG32((shrtimery) + 0x00000010U)             /*!< SHRTIMER Master_TIMER counter register */
#define SHRTIMER_MTCAR(shrtimery)                      REG32((shrtimery) + 0x00000014U)             /*!< SHRTIMER Master_TIMER counter auto reload register */
#define SHRTIMER_MTCREP(shrtimery)                     REG32((shrtimery) + 0x00000018U)             /*!< SHRTIMER Master_TIMER counter repetition register */
#define SHRTIMER_MTCMP0V(shrtimery)                    REG32((shrtimery) + 0x0000001CU)             /*!< SHRTIMER Master_TIMER compare 0 value register */
#define SHRTIMER_MTCMP1V(shrtimery)                    REG32((shrtimery) + 0x00000024U)             /*!< SHRTIMER Master_TIMER compare 1 value register */
#define SHRTIMER_MTCMP2V(shrtimery)                    REG32((shrtimery) + 0x00000028U)             /*!< SHRTIMER Master_TIMER compare 2 value register */
#define SHRTIMER_MTCMP3V(shrtimery)                    REG32((shrtimery) + 0x0000002CU)             /*!< SHRTIMER Master_TIMER compare 3 value register */
#define SHRTIMER_MTACTL(shrtimery)                     REG32((shrtimery) + 0x0000007CU)             /*!< SHRTIMER Master_TIMER additional control register */

/* Slave_TIMERx(x=0..4) registers definitions */
#define SHRTIMER_STXCTL0(shrtimery, slavex)            REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000000U)          /*!< SHRTIMER Slave_TIMERx control register 0 */
#define SHRTIMER_STXINTF(shrtimery, slavex)            REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000004U)          /*!< SHRTIMER Slave_TIMERx interrupt flag register */
#define SHRTIMER_STXINTC(shrtimery, slavex)            REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000008U)          /*!< SHRTIMER Slave_TIMERx interrupt flag clear register */
#define SHRTIMER_STXDMAINTEN(shrtimery, slavex)        REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x0000000CU)          /*!< SHRTIMER Slave_TIMERx DMA and interrupt enable register */
#define SHRTIMER_STXCNT(shrtimery, slavex)             REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000010U)          /*!< SHRTIMER Slave_TIMERx counter register */
#define SHRTIMER_STXCAR(shrtimery, slavex)             REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000014U)          /*!< SHRTIMER Slave_TIMERx counter auto reload register */
#define SHRTIMER_STXCREP(shrtimery, slavex)            REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000018U)          /*!< SHRTIMER Slave_TIMERx counter repetition register */
#define SHRTIMER_STXCMP0V(shrtimery, slavex)           REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x0000001CU)          /*!< SHRTIMER Slave_TIMERx compare 0 value register */
#define SHRTIMER_STXCMP0CP(shrtimery, slavex)          REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000020U)          /*!< SHRTIMER Slave_TIMERx compare 0 composite register */
#define SHRTIMER_STXCMP1V(shrtimery, slavex)           REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000024U)          /*!< SHRTIMER Slave_TIMERx compare 1 value register */
#define SHRTIMER_STXCMP2V(shrtimery, slavex)           REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000028U)          /*!< SHRTIMER Slave_TIMERx compare 2 value register */
#define SHRTIMER_STXCMP3V(shrtimery, slavex)           REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x0000002CU)          /*!< SHRTIMER Slave_TIMERx compare 3 value register */
#define SHRTIMER_STXCAP0V(shrtimery, slavex)           REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000030U)          /*!< SHRTIMER Slave_TIMERx capture 0 value register */
#define SHRTIMER_STXCAP1V(shrtimery, slavex)           REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000034U)          /*!< SHRTIMER Slave_TIMERx capture 1 value register */
#define SHRTIMER_STXDTCTL(shrtimery, slavex)           REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000038U)          /*!< SHRTIMER Slave_TIMERx dead-time control register */
#define SHRTIMER_STXCH0SET(shrtimery, slavex)          REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x0000003CU)          /*!< SHRTIMER Slave_TIMERx channel 0 set request register */
#define SHRTIMER_STXCH0RST(shrtimery, slavex)          REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000040U)          /*!< SHRTIMER Slave_TIMERx channel 0 reset request register */
#define SHRTIMER_STXCH1SET(shrtimery, slavex)          REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000044U)          /*!< SHRTIMER Slave_TIMERx channel 1 set request register */
#define SHRTIMER_STXCH1RST(shrtimery, slavex)          REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000048U)          /*!< SHRTIMER Slave_TIMERx channel 1 reset request register */
#define SHRTIMER_STXEXEVFCFG0(shrtimery, slavex)       REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x0000004CU)          /*!< SHRTIMER Slave_TIMERx external event filter configuration register 0 */
#define SHRTIMER_STXEXEVFCFG1(shrtimery, slavex)       REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000050U)          /*!< SHRTIMER Slave_TIMERx external event filter configuration register 1 */
#define SHRTIMER_STXCNTRST(shrtimery, slavex)          REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000054U)          /*!< SHRTIMER Slave_TIMERx counter reset register */
#define SHRTIMER_STXCSCTL(shrtimery, slavex)           REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000058U)          /*!< SHRTIMER Slave_TIMERx carrier-signal control register */
#define SHRTIMER_STXCAP0TRG(shrtimery, slavex)         REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x0000005CU)          /*!< SHRTIMER Slave_TIMERx capture 0 trigger register */
#define SHRTIMER_STXCAP1TRG(shrtimery, slavex)         REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000060U)          /*!< SHRTIMER Slave_TIMERx capture 1 trigger register */
#define SHRTIMER_STXCHOCTL(shrtimery, slavex)          REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000064U)          /*!< SHRTIMER Slave_TIMERx channel output control register */
#define SHRTIMER_STXFLTCTL(shrtimery, slavex)          REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000068U)          /*!< SHRTIMER Slave_TIMERx fault control register */
#define SHRTIMER_STXACTL(shrtimery, slavex)            REG32((shrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x0000007CU)          /*!< SHRTIMER Slave_TIMERx additional control register */

/* common registers definitions */
#define SHRTIMER_CTL0(shrtimery)                       REG32(((shrtimery) + 0x00000380U) + 0x00000000U)            /*!< SHRTIMER control register 0 */
#define SHRTIMER_CTL1(shrtimery)                       REG32(((shrtimery) + 0x00000380U) + 0x00000004U)            /*!< SHRTIMER control register 1 */
#define SHRTIMER_INTF(shrtimery)                       REG32(((shrtimery) + 0x00000380U) + 0x00000008U)            /*!< SHRTIMER interrupt flag register */
#define SHRTIMER_INTC(shrtimery)                       REG32(((shrtimery) + 0x00000380U) + 0x0000000CU)            /*!< SHRTIMER interrupt flag clear register */
#define SHRTIMER_INTEN(shrtimery)                      REG32(((shrtimery) + 0x00000380U) + 0x00000010U)            /*!< SHRTIMER interrupt enable register */
#define SHRTIMER_CHOUTEN(shrtimery)                    REG32(((shrtimery) + 0x00000380U) + 0x00000014U)            /*!< SHRTIMER channel output enable register */
#define SHRTIMER_CHOUTDIS(shrtimery)                   REG32(((shrtimery) + 0x00000380U) + 0x00000018U)            /*!< SHRTIMER channel output disable register */
#define SHRTIMER_CHOUTDISF(shrtimery)                  REG32(((shrtimery) + 0x00000380U) + 0x0000001CU)            /*!< SHRTIMER channel output disable flag register */
#define SHRTIMER_BMCTL(shrtimery)                      REG32(((shrtimery) + 0x00000380U) + 0x00000020U)            /*!< SHRTIMER bunch mode control register */
#define SHRTIMER_BMSTRG(shrtimery)                     REG32(((shrtimery) + 0x00000380U) + 0x00000024U)            /*!< SHRTIMER bunch mode start trigger register */
#define SHRTIMER_BMCMPV(shrtimery)                     REG32(((shrtimery) + 0x00000380U) + 0x00000028U)            /*!< SHRTIMER bunch mode compare value register */
#define SHRTIMER_BMCAR(shrtimery)                      REG32(((shrtimery) + 0x00000380U) + 0x0000002CU)            /*!< SHRTIMER bunch mode counter auto reload register */
#define SHRTIMER_EXEVCFG0(shrtimery)                   REG32(((shrtimery) + 0x00000380U) + 0x00000030U)            /*!< SHRTIMER external event configuration register 0 */
#define SHRTIMER_EXEVCFG1(shrtimery)                   REG32(((shrtimery) + 0x00000380U) + 0x00000034U)            /*!< SHRTIMER external event configuration register 1 */
#define SHRTIMER_EXEVDFCTL(shrtimery)                  REG32(((shrtimery) + 0x00000380U) + 0x00000038U)            /*!< SHRTIMER external event digital filter control register */
#define SHRTIMER_ADCTRIGS0(shrtimery)                  REG32(((shrtimery) + 0x00000380U) + 0x0000003CU)            /*!< SHRTIMER trigger source 0 to ADC register */
#define SHRTIMER_ADCTRIGS1(shrtimery)                  REG32(((shrtimery) + 0x00000380U) + 0x00000040U)            /*!< SHRTIMER trigger source 1 to ADC register */
#define SHRTIMER_ADCTRIGS2(shrtimery)                  REG32(((shrtimery) + 0x00000380U) + 0x00000044U)            /*!< SHRTIMER trigger source 2 to ADC register */
#define SHRTIMER_ADCTRIGS3(shrtimery)                  REG32(((shrtimery) + 0x00000380U) + 0x00000048U)            /*!< SHRTIMER trigger source 3 to ADC register */
#define SHRTIMER_DLLCCTL(shrtimery)                    REG32(((shrtimery) + 0x00000380U) + 0x0000004CU)            /*!< SHRTIMER DLL calibration control register */
#define SHRTIMER_FLTINCFG0(shrtimery)                  REG32(((shrtimery) + 0x00000380U) + 0x00000050U)            /*!< SHRTIMER fault input configuration register 0 */
#define SHRTIMER_FLTINCFG1(shrtimery)                  REG32(((shrtimery) + 0x00000380U) + 0x00000054U)            /*!< SHRTIMER fault input configuration register 1 */
#define SHRTIMER_DMAUPMTR(shrtimery)                   REG32(((shrtimery) + 0x00000380U) + 0x00000058U)            /*!< SHRTIMER DMA update Master_TIMER register */
#define SHRTIMER_DMAUPST0R(shrtimery)                  REG32(((shrtimery) + 0x00000380U) + 0x0000005CU)            /*!< SHRTIMER DMA update Slave_TIMER0 register */
#define SHRTIMER_DMAUPST1R(shrtimery)                  REG32(((shrtimery) + 0x00000380U) + 0x00000060U)            /*!< SHRTIMER DMA update Slave_TIMER1 register */
#define SHRTIMER_DMAUPST2R(shrtimery)                  REG32(((shrtimery) + 0x00000380U) + 0x00000064U)            /*!< SHRTIMER DMA update Slave_TIMER2 register */
#define SHRTIMER_DMAUPST3R(shrtimery)                  REG32(((shrtimery) + 0x00000380U) + 0x00000068U)            /*!< SHRTIMER DMA update Slave_TIMER3 register */
#define SHRTIMER_DMAUPST4R(shrtimery)                  REG32(((shrtimery) + 0x00000380U) + 0x0000006CU)            /*!< SHRTIMER DMA update Slave_TIMER4 register */
#define SHRTIMER_DMATB(shrtimery)                      REG32(((shrtimery) + 0x00000380U) + 0x00000070U)            /*!< SHRTIMER DMA transfer buffer register */

/* bits definitions */
/* Master_TIMER registers */
/* SHRTIMER_MTCTL0 */
#define SHRTIMER_MTCTL0_CNTCKDIV2_0                      BITS(0,2)           /*!< counter clock division */
#define SHRTIMER_MTCTL0_CTNM                             BIT(3)              /*!< continuous mode */
#define SHRTIMER_MTCTL0_CNTRSTM                          BIT(4)              /*!< counter reset mode */
#define SHRTIMER_MTCTL0_HALFM                            BIT(5)              /*!< half mode */
#define SHRTIMER_MTCTL0_SYNISRC                          BITS(8,9)           /*!< synchronization input source */
#define SHRTIMER_MTCTL0_SYNIRST                          BIT(10)             /*!< synchronization input reset counter */
#define SHRTIMER_MTCTL0_SYNISTRT                         BIT(11)             /*!< synchronization input start counter */
#define SHRTIMER_MTCTL0_SYNOPLS                          BITS(12,13)         /*!< synchronization output pulse */
#define SHRTIMER_MTCTL0_SYNOSRC                          BITS(14,15)         /*!< synchronization output source */
#define SHRTIMER_MTCTL0_MTCEN                            BIT(16)             /*!< the counter of Master_TIMER enable */
#define SHRTIMER_MTCTL0_ST0CEN                           BIT(17)             /*!< the counter of Slave_TIMER0 enable */
#define SHRTIMER_MTCTL0_ST1CEN                           BIT(18)             /*!< the counter of Slave_TIMER1 enable */
#define SHRTIMER_MTCTL0_ST2CEN                           BIT(19)             /*!< the counter of Slave_TIMER2 enable */
#define SHRTIMER_MTCTL0_ST3CEN                           BIT(20)             /*!< the counter of Slave_TIMER3 enable */
#define SHRTIMER_MTCTL0_ST4CEN                           BIT(21)             /*!< the counter of Slave_TIMER4 enable */
#define SHRTIMER_MTCTL0_DACTRGS                          BITS(25,26)         /*!< trigger source to DAC */
#define SHRTIMER_MTCTL0_SHWEN                            BIT(27)             /*!< shadow registers enable */
#define SHRTIMER_MTCTL0_UPREP                            BIT(29)             /*!< update event generated by repetition event */
#define SHRTIMER_MTCTL0_UPSEL                            BITS(30,31)         /*!< update event selection */

/* SHRTIMER_MTINTF */
#define SHRTIMER_MTINTF_CMP0IF                           BIT(0)              /*!< compare 0 interrupt flag */
#define SHRTIMER_MTINTF_CMP1IF                           BIT(1)              /*!< compare 1 interrupt flag */
#define SHRTIMER_MTINTF_CMP2IF                           BIT(2)              /*!< compare 2 interrupt flag */
#define SHRTIMER_MTINTF_CMP3IF                           BIT(3)              /*!< compare 3 interrupt flag */
#define SHRTIMER_MTINTF_REPIF                            BIT(4)              /*!< repetition interrupt flag */
#define SHRTIMER_MTINTF_SYNIIF                           BIT(5)              /*!< synchronization input interrupt flag */
#define SHRTIMER_MTINTF_UPIF                             BIT(6)              /*!< update interrupt flag */

/* SHRTIMER_MTINTC */
#define SHRTIMER_MTINTC_CMP0IFC                          BIT(0)              /*!< clear compare 0 interrupt flag */
#define SHRTIMER_MTINTC_CMP1IFC                          BIT(1)              /*!< clear compare 1 interrupt flag */
#define SHRTIMER_MTINTC_CMP2IFC                          BIT(2)              /*!< clear compare 2 interrupt flag */
#define SHRTIMER_MTINTC_CMP3IFC                          BIT(3)              /*!< clear compare 3 interrupt flag */
#define SHRTIMER_MTINTC_REPIFC                           BIT(4)              /*!< clear repetition interrupt flag */
#define SHRTIMER_MTINTC_SYNIIFC                          BIT(5)              /*!< clear synchronization input interrupt flag */
#define SHRTIMER_MTINTC_UPIFC                            BIT(6)              /*!< clear update interrupt flag */

/* SHRTIMER_MTDMAINTEN */
#define SHRTIMER_MTDMAINTEN_CMP0IE                       BIT(0)              /*!< compare 0 interrupt enable */
#define SHRTIMER_MTDMAINTEN_CMP1IE                       BIT(1)              /*!< compare 1 interrupt enable */
#define SHRTIMER_MTDMAINTEN_CMP2IE                       BIT(2)              /*!< compare 2 interrupt enable */
#define SHRTIMER_MTDMAINTEN_CMP3IE                       BIT(3)              /*!< compare 3 interrupt enable */
#define SHRTIMER_MTDMAINTEN_REPIE                        BIT(4)              /*!< repetition interrupt enable */
#define SHRTIMER_MTDMAINTEN_SYNIIE                       BIT(5)              /*!< synchronization input interrupt enable */
#define SHRTIMER_MTDMAINTEN_UPIE                         BIT(6)              /*!< update interrupt enable */
#define SHRTIMER_MTDMAINTEN_CMP0DEN                      BIT(16)             /*!< compare 0 DMA request enable */
#define SHRTIMER_MTDMAINTEN_CMP1DEN                      BIT(17)             /*!< compare 1 DMA request enable */
#define SHRTIMER_MTDMAINTEN_CMP2DEN                      BIT(18)             /*!< compare 2 DMA request enable */
#define SHRTIMER_MTDMAINTEN_CMP3DEN                      BIT(19)             /*!< compare 3 DMA request enable */
#define SHRTIMER_MTDMAINTEN_REPDEN                       BIT(20)             /*!< repetition DMA request enable */
#define SHRTIMER_MTDMAINTEN_SYNIDEN                      BIT(21)             /*!< synchronization input DMA request enable */
#define SHRTIMER_MTDMAINTEN_UPDEN                        BIT(22)             /*!< update DMA request enable */

/* SHRTIMER_MTCNT */
#define SHRTIMER_MTCNT_CNT                               BITS(0,15)          /*!< the current counter value */

/* SHRTIMER_MTCAR */
#define SHRTIMER_MTCAR_CARL                              BITS(0,15)          /*!< counter auto reload value */

/* SHRTIMER_MTCREP */
#define SHRTIMER_MTCREP_CREP                             BITS(0,7)           /*!< counter repetition value */

/* SHRTIMER_MTCMP0V */
#define SHRTIMER_MTCMP0V_CMP0VAL                         BITS(0,15)          /*!< compare 0 value */

/* SHRTIMER_MTCMP1V */
#define SHRTIMER_MTCMP1V_CMP1VAL                         BITS(0,15)          /*!< compare 1 value */

/* SHRTIMER_MTCMP2V */
#define SHRTIMER_MTCMP2V_CMP0VAL                         BITS(0,15)          /*!< compare 2 value */

/* SHRTIMER_MTCMP3V */
#define SHRTIMER_MTCMP3V_CMP0VAL                         BITS(0,15)          /*!< compare 3 value */

/* SHRTIMER_MTACTL */
#define SHRTIMER_MTACTL_CNTCKDIV3                        BIT(3)              /*!< counter clock division */

/* Slave_TIMERx registers(x=0..4) */
/* SHRTIMER_STxCTL0 */
#define SHRTIMER_STXCTL0_CNTCKDIV2_0                     BITS(0,2)           /*!< counter clock division */
#define SHRTIMER_STXCTL0_CTNM                            BIT(3)              /*!< continuous mode */
#define SHRTIMER_STXCTL0_CNTRSTM                         BIT(4)              /*!< counter reset mode */
#define SHRTIMER_STXCTL0_HALFM                           BIT(5)              /*!< half mode */
#define SHRTIMER_STXCTL0_BLNMEN                          BIT(6)              /*!< balanced mode enable */
#define SHRTIMER_STXCTL0_SYNIRST                         BIT(10)             /*!< synchronization input reset counter */
#define SHRTIMER_STXCTL0_SYNISTRT                        BIT(11)             /*!< synchronization input start counter */
#define SHRTIMER_STXCTL0_DELCMP1M                        BITS(12,13)         /*!< compare 1 delayed mode */
#define SHRTIMER_STXCTL0_DELCMP3M                        BITS(14,15)         /*!< compare 3 delayed mode */
#define SHRTIMER_STXCTL0_UPREP                           BIT(17)             /*!< update event generated by repetition event */
#define SHRTIMER_STXCTL0_UPRST                           BIT(18)             /*!< update event generated by reset event */
#define SHRTIMER_STXCTL0_UPBST0                          BIT(19)             /*!< update by Slave_TIMER0 update event */
#define SHRTIMER_STXCTL0_UPBST1                          BIT(20)             /*!< update by Slave_TIMER1 update event */
#define SHRTIMER_STXCTL0_UPBST2                          BIT(21)             /*!< update by Slave_TIMER2 update event */
#define SHRTIMER_STXCTL0_UPBST3                          BIT(22)             /*!< update by Slave_TIMER3 update event */
#define SHRTIMER_STXCTL0_UPBST4                          BIT(23)             /*!< update by Slave_TIMER4 update event */
#define SHRTIMER_STXCTL0_UPBMT                           BIT(24)             /*!< update by Master_TIMER update event */
#define SHRTIMER_STXCTL0_DACTRGS                         BITS(25,26)         /*!< trigger source to DAC */
#define SHRTIMER_STXCTL0_SHWEN                           BIT(27)             /*!< shadow registers enable */
#define SHRTIMER_STXCTL0_UPSEL                           BITS(28,31)         /*!< update event selection */

/* SHRTIMER_STxINTF */
#define SHRTIMER_STXINTF_CMP0IF                          BIT(0)              /*!< compare 0 interrupt flag */
#define SHRTIMER_STXINTF_CMP1IF                          BIT(1)              /*!< compare 1 interrupt flag */
#define SHRTIMER_STXINTF_CMP2IF                          BIT(2)              /*!< compare 2 interrupt flag */
#define SHRTIMER_STXINTF_CMP3IF                          BIT(3)              /*!< compare 3 interrupt flag */
#define SHRTIMER_STXINTF_REPIF                           BIT(4)              /*!< repetition interrupt flag */
#define SHRTIMER_STXINTF_UPIF                            BIT(6)              /*!< update interrupt flag */
#define SHRTIMER_STXINTF_CAP0IF                          BIT(7)              /*!< capture 0 interrupt flag */
#define SHRTIMER_STXINTF_CAP1IF                          BIT(8)              /*!< capture 1 interrupt flag */
#define SHRTIMER_STXINTF_CH0OAIF                         BIT(9)              /*!< channel 0 output active interrupt flag */
#define SHRTIMER_STXINTF_CH0ONAIF                        BIT(10)             /*!< channel 0 output inactive interrupt flag */
#define SHRTIMER_STXINTF_CH1OAIF                         BIT(11)             /*!< channel 1 output active interrupt flag */
#define SHRTIMER_STXINTF_CH1ONAIF                        BIT(12)             /*!< channel 1 output inactive interrupt flag */
#define SHRTIMER_STXINTF_RSTIF                           BIT(13)             /*!< counter reset interrupt flag */
#define SHRTIMER_STXINTF_DLYIIF                          BIT(14)             /*!< delayed IDLE mode entry interrupt flag */
#define SHRTIMER_STXINTF_CBLNF                           BIT(16)             /*!< current balanced flag */
#define SHRTIMER_STXINTF_BLNIF                           BIT(17)             /*!< balanced IDLE flag */
#define SHRTIMER_STXINTF_CH0F                            BIT(20)             /*!< channel 0 output flag */
#define SHRTIMER_STXINTF_CH1F                            BIT(21)             /*!< channel 1 output flag */

/* SHRTIMER_STxINTC */
#define SHRTIMER_STXINTC_CMP0IFC                         BIT(0)              /*!< clear compare 0 interrupt flag */
#define SHRTIMER_STXINTC_CMP1IFC                         BIT(1)              /*!< clear compare 1 interrupt flag */
#define SHRTIMER_STXINTC_CMP2IFC                         BIT(2)              /*!< clear compare 2 interrupt flag */
#define SHRTIMER_STXINTC_CMP3IFC                         BIT(3)              /*!< clear compare 3 interrupt flag */
#define SHRTIMER_STXINTC_REPIFC                          BIT(4)              /*!< clear repetition interrupt flag */
#define SHRTIMER_STXINTC_UPIFC                           BIT(6)              /*!< clear update interrupt flag */
#define SHRTIMER_STXINTC_CAP0IFC                         BIT(7)              /*!< clear capture 0 interrupt flag */
#define SHRTIMER_STXINTC_CAP1IFC                         BIT(8)              /*!< clear capture 1 interrupt flag */
#define SHRTIMER_STXINTC_CH0OAIFC                        BIT(9)              /*!< clear channel 0 output active interrupt flag */
#define SHRTIMER_STXINTC_CH0ONAIFC                       BIT(10)             /*!< clear channel 0 output inactive interrupt flag */
#define SHRTIMER_STXINTC_CH1OAIFC                        BIT(11)             /*!< clear channel 1 output active interrupt flag */
#define SHRTIMER_STXINTC_CH1ONAIFC                       BIT(12)             /*!< clear channel 1 output inactive interrupt flag */
#define SHRTIMER_STXINTC_RSTIFC                          BIT(13)             /*!< clear counter reset interrupt flag */
#define SHRTIMER_STXINTC_DLYIIFC                         BIT(14)             /*!< clear delayed IDLE mode entry interrupt flag */

/* SHRTIMER_STxDMAINTEN */
#define SHRTIMER_STXDMAINTEN_CMP0IE                      BIT(0)              /*!< compare 0 interrupt enable */
#define SHRTIMER_STXDMAINTEN_CMP1IE                      BIT(1)              /*!< compare 1 interrupt enable */
#define SHRTIMER_STXDMAINTEN_CMP2IE                      BIT(2)              /*!< compare 2 interrupt enable */
#define SHRTIMER_STXDMAINTEN_CMP3IE                      BIT(3)              /*!< compare 3 interrupt enable */
#define SHRTIMER_STXDMAINTEN_REPIE                       BIT(4)              /*!< repetition interrupt enable */
#define SHRTIMER_STXDMAINTEN_UPIE                        BIT(6)              /*!< update interrupt enable */
#define SHRTIMER_STXDMAINTEN_CAP0IE                      BIT(7)              /*!< capture 0 interrupt enable */
#define SHRTIMER_STXDMAINTEN_CAP1IE                      BIT(8)              /*!< capture 1 interrupt enable */
#define SHRTIMER_STXDMAINTEN_CH0OAIE                     BIT(9)              /*!< channel 0 output active interrupt enable */
#define SHRTIMER_STXDMAINTEN_CH0ONAIE                    BIT(10)             /*!< channel 0 output inactive interrupt enable */
#define SHRTIMER_STXDMAINTEN_CH1OAIE                     BIT(11)             /*!< channel 1 output active interrupt enable */
#define SHRTIMER_STXDMAINTEN_CH1ONAIE                    BIT(12)             /*!< channel 1 output inactive interrupt enable */
#define SHRTIMER_STXDMAINTEN_RSTIE                       BIT(13)             /*!< counter reset interrupt enable */
#define SHRTIMER_STXDMAINTEN_DLYIIE                      BIT(14)             /*!< delayed IDLE mode entry interrupt enable */
#define SHRTIMER_STXDMAINTEN_CMP0DEN                     BIT(16)             /*!< compare 0 DMA request enable */
#define SHRTIMER_STXDMAINTEN_CMP1DEN                     BIT(17)             /*!< compare 1 DMA request enable */
#define SHRTIMER_STXDMAINTEN_CMP2DEN                     BIT(18)             /*!< compare 2 DMA request enable */
#define SHRTIMER_STXDMAINTEN_CMP3DEN                     BIT(19)             /*!< compare 3 DMA request enable */
#define SHRTIMER_STXDMAINTEN_REPDEN                      BIT(20)             /*!< repetition DMA request enable */
#define SHRTIMER_STXDMAINTEN_UPDEN                       BIT(22)             /*!< update DMA request enable */
#define SHRTIMER_STXDMAINTEN_CAP0DEN                     BIT(23)             /*!< capture 0 DMA request enable */
#define SHRTIMER_STXDMAINTEN_CAP1DEN                     BIT(24)             /*!< capture 1 DMA request enable */
#define SHRTIMER_STXDMAINTEN_CH0OADEN                    BIT(25)             /*!< channel 0 output active DMA request enable */
#define SHRTIMER_STXDMAINTEN_CH0ONADEN                   BIT(26)             /*!< channel 0 output inactive DMA request enable */
#define SHRTIMER_STXDMAINTEN_CH1OADEN                    BIT(27)             /*!< channel 1 output active DMA request enable */
#define SHRTIMER_STXDMAINTEN_CH1ONADEN                   BIT(28)             /*!< channel 1 output inactive DMA request enable */
#define SHRTIMER_STXDMAINTEN_RSTDEN                      BIT(29)             /*!< counter reset DMA request enable */
#define SHRTIMER_STXDMAINTEN_DLYIDEN                     BIT(30)             /*!< delayed IDLE mode entry DMA request enable */

/* SHRTIMER_STxCNT */
#define SHRTIMER_STXCNT_CNT                              BITS(0,15)          /*!< the current counter value */

/* SHRTIMER_STxCAR */
#define SHRTIMER_STXCAR_CARL                             BITS(0,15)          /*!< counter auto reload value */

/* SHRTIMER_STxCREP */
#define SHRTIMER_STXCREP_CREP                            BITS(0,7)           /*!< counter repetition value */

/* SHRTIMER_STxCMP0V */
#define SHRTIMER_STXCMP0V_CMP0VAL                        BITS(0,15)          /*!< compare 0 value */

/* SHRTIMER_STxCMP0CP */
#define SHRTIMER_STXCMP0CP_CMP0VAL                       BITS(0,15)          /*!< compare 0 value */
#define SHRTIMER_STXCMP0CP_CREP                          BITS(16,23)         /*!< counter repetition value */

/* SHRTIMER_STxCMP1V */
#define SHRTIMER_STXCMP1V_CMP1VAL                        BITS(0,15)          /*!< compare 1 value */

/* SHRTIMER_STxCMP2V */
#define SHRTIMER_STXCMP2V_CMP2VAL                        BITS(0,15)          /*!< compare 2 value */

/* SHRTIMER_STxCMP3V */
#define SHRTIMER_STXCMP3V_CMP3VAL                        BITS(0,15)          /*!< compare 3 value */

/* SHRTIMER_STxCAP0V */
#define SHRTIMER_STXCAP0V_CAP0VAL                        BITS(0,15)          /*!< capture 0 value */

/* SHRTIMER_STxCAP1V */
#define SHRTIMER_STXCAP1V_CAP1VAL                        BITS(0,15)          /*!< capture 1 value */

/* SHRTIMER_STxDTCTL */
#define SHRTIMER_STXDTCTL_DTRCFG8_0                      BITS(0,8)           /*!< rising edge dead-time value */
#define SHRTIMER_STXDTCTL_DTRS                           BIT(9)              /*!< the sign of rising edge dead-time value */
#define SHRTIMER_STXDTCTL_DTGCKDIV                       BITS(10,13)         /*!< dead time generator clock division */
#define SHRTIMER_STXDTCTL_DTRSPROT                       BIT(14)             /*!< dead-time rising edge protection for sign */
#define SHRTIMER_STXDTCTL_DTRSVPROT                      BIT(15)             /*!< dead-time rising edge protection for value and sign */
#define SHRTIMER_STXDTCTL_DTFCFG8_0                      BITS(16,24)         /*!< falling edge dead-time value */
#define SHRTIMER_STXDTCTL_DTFS                           BIT(25)             /*!< the sign of falling edge dead-time value */
#define SHRTIMER_STXDTCTL_DTFSPROT                       BIT(30)             /*!< dead-time falling edge protection for sign */
#define SHRTIMER_STXDTCTL_DTFSVPROT                      BIT(31)             /*!< dead-time falling edge protection for value and sign */

/* SHRTIMER_STxCH0SET */
#define SHRTIMER_STXCH0SET_CH0SSEV                       BIT(0)              /*!< software event generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SRST                       BIT(1)              /*!< Slave_TIMERx reset event generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SPER                       BIT(2)              /*!< Slave_TIMERx period event generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SCMP0                      BIT(3)              /*!< Slave_TIMERx compare 0 event generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SCMP1                      BIT(4)              /*!< Slave_TIMERx compare 1 event generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SCMP2                      BIT(5)              /*!< Slave_TIMERx compare 2 event generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SCMP3                      BIT(6)              /*!< Slave_TIMERx compare 3 event generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SMTPER                     BIT(7)              /*!< Master_TIMER period event generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SMTCMP0                    BIT(8)              /*!< Master_TIMER compare 0 event generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SMTCMP1                    BIT(9)              /*!< Master_TIMER compare 1 event generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SMTCMP2                    BIT(10)             /*!< Master_TIMER compare 2 event generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SMTCMP3                    BIT(11)             /*!< Master_TIMER compare 3 event generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SSTEV0                     BIT(12)             /*!< Slave_TIMERx interconnection event 0 generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SSTEV1                     BIT(13)             /*!< Slave_TIMERx interconnection event 1 generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SSTEV2                     BIT(14)             /*!< Slave_TIMERx interconnection event 2 generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SSTEV3                     BIT(15)             /*!< Slave_TIMERx interconnection event 3 generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SSTEV4                     BIT(16)             /*!< Slave_TIMERx interconnection event 4 generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SSTEV5                     BIT(17)             /*!< Slave_TIMERx interconnection event 5 generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SSTEV6                     BIT(18)             /*!< Slave_TIMERx interconnection event 6 generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SSTEV7                     BIT(19)             /*!< Slave_TIMERx interconnection event 7 generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SSTEV8                     BIT(20)             /*!< Slave_TIMERx interconnection event 8 generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SEXEV0                     BIT(21)             /*!< external event 0 generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SEXEV1                     BIT(22)             /*!< external event 1 generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SEXEV2                     BIT(23)             /*!< external event 2 generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SEXEV3                     BIT(24)             /*!< external event 3 generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SEXEV4                     BIT(25)             /*!< external event 4 generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SEXEV5                     BIT(26)             /*!< external event 5 generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SEXEV6                     BIT(27)             /*!< external event 6 generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SEXEV7                     BIT(28)             /*!< external event 7 generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SEXEV8                     BIT(29)             /*!< external event 8 generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SEXEV9                     BIT(30)             /*!< external event 9 generates channel 0 ��set request�� */
#define SHRTIMER_STXCH0SET_CH0SUP                        BIT(31)             /*!< update event generates channel 0 ��set request�� */

/* SHRTIMER_STxCH0RST */
#define SHRTIMER_STXCH0RST_CH0RSSEV                      BIT(0)              /*!< software event generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSRST                      BIT(1)              /*!< Slave_TIMERx reset event generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSPER                      BIT(2)              /*!< Slave_TIMERx period event generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSCMP0                     BIT(3)              /*!< Slave_TIMERx compare 0 event generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSCMP1                     BIT(4)              /*!< Slave_TIMERx compare 1 event generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSCMP2                     BIT(5)              /*!< Slave_TIMERx compare 2 event generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSCMP3                     BIT(6)              /*!< Slave_TIMERx compare 3 event generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSMTPER                    BIT(7)              /*!< Master_TIMER period event generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSMTCMP0                   BIT(8)              /*!< Master_TIMER compare 0 event generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSMTCMP1                   BIT(9)              /*!< Master_TIMER compare 1 event generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSMTCMP2                   BIT(10)             /*!< Master_TIMER compare 2 event generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSMTCMP3                   BIT(11)             /*!< Master_TIMER compare 3 event generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSSTEV0                    BIT(12)             /*!< Slave_TIMERx interconnection event 0 generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSSTEV1                    BIT(13)             /*!< Slave_TIMERx interconnection event 1 generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSSTEV2                    BIT(14)             /*!< Slave_TIMERx interconnection event 2 generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSSTEV3                    BIT(15)             /*!< Slave_TIMERx interconnection event 3 generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSSTEV4                    BIT(16)             /*!< Slave_TIMERx interconnection event 4 generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSSTEV5                    BIT(17)             /*!< Slave_TIMERx interconnection event 5 generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSSTEV6                    BIT(18)             /*!< Slave_TIMERx interconnection event 6 generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSSTEV7                    BIT(19)             /*!< Slave_TIMERx interconnection event 7 generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSSTEV8                    BIT(20)             /*!< Slave_TIMERx interconnection event 8 generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSEXEV0                    BIT(21)             /*!< external event 0 generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSEXEV1                    BIT(22)             /*!< external event 1 generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSEXEV2                    BIT(23)             /*!< external event 2 generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSEXEV3                    BIT(24)             /*!< external event 3 generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSEXEV4                    BIT(25)             /*!< external event 4 generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSEXEV5                    BIT(26)             /*!< external event 5 generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSEXEV6                    BIT(27)             /*!< external event 6 generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSEXEV7                    BIT(28)             /*!< external event 7 generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSEXEV8                    BIT(29)             /*!< external event 8 generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSEXEV9                    BIT(30)             /*!< external event 9 generates channel 0 ��reset request�� */
#define SHRTIMER_STXCH0RST_CH0RSUP                       BIT(31)             /*!< update event generates channel 0 ��reset request�� */

/* SHRTIMER_STxCH1SET */
#define SHRTIMER_STXCH1SET_CH1SSEV                       BIT(0)              /*!< software event generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SRST                       BIT(1)              /*!< Slave_TIMERx reset event generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SPER                       BIT(2)              /*!< Slave_TIMERx period event generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SCMP0                      BIT(3)              /*!< Slave_TIMERx compare 0 event generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SCMP1                      BIT(4)              /*!< Slave_TIMERx compare 1 event generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SCMP2                      BIT(5)              /*!< Slave_TIMERx compare 2 event generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SCMP3                      BIT(6)              /*!< Slave_TIMERx compare 3 event generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SMTPER                     BIT(7)              /*!< Master_TIMER period event generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SMTCMP0                    BIT(8)              /*!< Master_TIMER compare 0 event generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SMTCMP1                    BIT(9)              /*!< Master_TIMER compare 1 event generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SMTCMP2                    BIT(10)             /*!< Master_TIMER compare 2 event generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SMTCMP3                    BIT(11)             /*!< Master_TIMER compare 3 event generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SSTEV0                     BIT(12)             /*!< Slave_TIMERx interconnection event 0 generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SSTEV1                     BIT(13)             /*!< Slave_TIMERx interconnection event 1 generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SSTEV2                     BIT(14)             /*!< Slave_TIMERx interconnection event 2 generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SSTEV3                     BIT(15)             /*!< Slave_TIMERx interconnection event 3 generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SSTEV4                     BIT(16)             /*!< Slave_TIMERx interconnection event 4 generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SSTEV5                     BIT(17)             /*!< Slave_TIMERx interconnection event 5 generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SSTEV6                     BIT(18)             /*!< Slave_TIMERx interconnection event 6 generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SSTEV7                     BIT(19)             /*!< Slave_TIMERx interconnection event 7 generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SSTEV8                     BIT(20)             /*!< Slave_TIMERx interconnection event 8 generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SEXEV0                     BIT(21)             /*!< external event 0 generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SEXEV1                     BIT(22)             /*!< external event 1 generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SEXEV2                     BIT(23)             /*!< external event 2 generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SEXEV3                     BIT(24)             /*!< external event 3 generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SEXEV4                     BIT(25)             /*!< external event 4 generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SEXEV5                     BIT(26)             /*!< external event 5 generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SEXEV6                     BIT(27)             /*!< external event 6 generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SEXEV7                     BIT(28)             /*!< external event 7 generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SEXEV8                     BIT(29)             /*!< external event 8 generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SEXEV9                     BIT(30)             /*!< external event 9 generates channel 1 ��set request�� */
#define SHRTIMER_STXCH1SET_CH1SUP                        BIT(31)             /*!< update event generates channel 1 ��set request�� */

/* SHRTIMER_STxCH1RST */
#define SHRTIMER_STXCH1RST_CH1RSSEV                      BIT(0)              /*!< software event generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSRST                      BIT(1)              /*!< Slave_TIMERx reset event generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSPER                      BIT(2)              /*!< Slave_TIMERx period event generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSCMP0                     BIT(3)              /*!< Slave_TIMERx compare 0 event generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSCMP1                     BIT(4)              /*!< Slave_TIMERx compare 1 event generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSCMP2                     BIT(5)              /*!< Slave_TIMERx compare 2 event generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSCMP3                     BIT(6)              /*!< Slave_TIMERx compare 3 event generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSMTPER                    BIT(7)              /*!< Master_TIMER period event generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSMTCMP0                   BIT(8)              /*!< Master_TIMER compare 0 event generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSMTCMP1                   BIT(9)              /*!< Master_TIMER compare 1 event generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSMTCMP2                   BIT(10)             /*!< Master_TIMER compare 2 event generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSMTCMP3                   BIT(11)             /*!< Master_TIMER compare 3 event generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSSTEV0                    BIT(12)             /*!< Slave_TIMERx interconnection event 0 generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSSTEV1                    BIT(13)             /*!< Slave_TIMERx interconnection event 1 generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSSTEV2                    BIT(14)             /*!< Slave_TIMERx interconnection event 2 generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSSTEV3                    BIT(15)             /*!< Slave_TIMERx interconnection event 3 generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSSTEV4                    BIT(16)             /*!< Slave_TIMERx interconnection event 4 generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSSTEV5                    BIT(17)             /*!< Slave_TIMERx interconnection event 5 generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSSTEV6                    BIT(18)             /*!< Slave_TIMERx interconnection event 6 generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSSTEV7                    BIT(19)             /*!< Slave_TIMERx interconnection event 7 generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSSTEV8                    BIT(20)             /*!< Slave_TIMERx interconnection event 8 generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSEXEV0                    BIT(21)             /*!< external event 0 generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSEXEV1                    BIT(22)             /*!< external event 1 generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSEXEV2                    BIT(23)             /*!< external event 2 generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSEXEV3                    BIT(24)             /*!< external event 3 generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSEXEV4                    BIT(25)             /*!< external event 4 generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSEXEV5                    BIT(26)             /*!< external event 5 generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSEXEV6                    BIT(27)             /*!< external event 6 generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSEXEV7                    BIT(28)             /*!< external event 7 generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSEXEV8                    BIT(29)             /*!< external event 8 generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSEXEV9                    BIT(30)             /*!< external event 9 generates channel 1 ��reset request�� */
#define SHRTIMER_STXCH1RST_CH1RSUP                       BIT(31)             /*!< update event generates channel 1 ��reset request�� */

/* SHRTIMER_STxEXEVFCFG0 */
#define SHRTIMER_STXEXEVFCFG0_EXEV0MEEN                  BIT(0)              /*!< external event 0 memory */
#define SHRTIMER_STXEXEVFCFG0_EXEV0FM                    BITS(1,4)           /*!< external event 0 filter mode */
#define SHRTIMER_STXEXEVFCFG0_EXEV1MEEN                  BIT(6)              /*!< external event 1 memory */
#define SHRTIMER_STXEXEVFCFG0_EXEV1FM                    BITS(7,10)          /*!< external event 1 filter mode */
#define SHRTIMER_STXEXEVFCFG0_EXEV2MEEN                  BIT(12)             /*!< external event 2 memory */
#define SHRTIMER_STXEXEVFCFG0_EXEV2FM                    BITS(13,16)         /*!< external event 2 filter mode */
#define SHRTIMER_STXEXEVFCFG0_EXEV3MEEN                  BIT(18)             /*!< external event 3 memory */
#define SHRTIMER_STXEXEVFCFG0_EXEV3FM                    BITS(19,22)         /*!< external event 3 filter mode */
#define SHRTIMER_STXEXEVFCFG0_EXEV4MEEN                  BIT(24)             /*!< external event 4 memory */
#define SHRTIMER_STXEXEVFCFG0_EXEV4FM                    BITS(25,28)         /*!< external event 4 filter mode */

/* SHRTIMER_STxEXEVFCFG1 */
#define SHRTIMER_STXEXEVFCFG1_EXEV5MEEN                  BIT(0)              /*!< external event 5 memory */
#define SHRTIMER_STXEXEVFCFG1_EXEV5FM                    BITS(1,4)           /*!< external event 5 filter mode */
#define SHRTIMER_STXEXEVFCFG1_EXEV6MEEN                  BIT(6)              /*!< external event 6 memory */
#define SHRTIMER_STXEXEVFCFG1_EXEV6FM                    BITS(7,10)          /*!< external event 6 filter mode */
#define SHRTIMER_STXEXEVFCFG1_EXEV7MEEN                  BIT(12)             /*!< external event 7 memory */
#define SHRTIMER_STXEXEVFCFG1_EXEV7FM                    BITS(13,16)         /*!< external event 7 filter mode */
#define SHRTIMER_STXEXEVFCFG1_EXEV8MEEN                  BIT(18)             /*!< external event 8 memory */
#define SHRTIMER_STXEXEVFCFG1_EXEV8FM                    BITS(19,22)         /*!< external event 8 filter mode */
#define SHRTIMER_STXEXEVFCFG1_EXEV9MEEN                  BIT(24)             /*!< external event 9 memory */
#define SHRTIMER_STXEXEVFCFG1_EXEV9FM                    BITS(25,28)         /*!< external event 9 filter mode */

/* SHRTIMER_STxCNTRST */
#define SHRTIMER_STXCNTRST_UPRST                         BIT(1)              /*!< Slave_TIMER0 update event resets counter */
#define SHRTIMER_STXCNTRST_CMP1RST                       BIT(2)              /*!< Slave_TIMER0 compare 1 event resets counter */
#define SHRTIMER_STXCNTRST_CMP3RST                       BIT(3)              /*!< Slave_TIMER0 compare 3 event resets counter */
#define SHRTIMER_STXCNTRST_MTPERRST                      BIT(4)              /*!< Master_TIMER period event resets counter */
#define SHRTIMER_STXCNTRST_MTCMP0RST                     BIT(5)              /*!< Master_TIMER compare 0 event resets counter */
#define SHRTIMER_STXCNTRST_MTCMP1RST                     BIT(6)              /*!< Master_TIMER compare 1 event resets counter */
#define SHRTIMER_STXCNTRST_MTCMP2RST                     BIT(7)              /*!< Master_TIMER compare 2 event resets counter */
#define SHRTIMER_STXCNTRST_MTCMP3RST                     BIT(8)              /*!< Master_TIMER compare 3 event resets counter */
#define SHRTIMER_STXCNTRST_EXEV0RST                      BIT(9)              /*!< external event 0 resets counter */
#define SHRTIMER_STXCNTRST_EXEV1RST                      BIT(10)             /*!< external event 1 resets counter */
#define SHRTIMER_STXCNTRST_EXEV2RST                      BIT(11)             /*!< external event 2 resets counter */
#define SHRTIMER_STXCNTRST_EXEV3RST                      BIT(12)             /*!< external event 3 resets counter */
#define SHRTIMER_STXCNTRST_EXEV4RST                      BIT(13)             /*!< external event 4 resets counter */
#define SHRTIMER_STXCNTRST_EXEV5RST                      BIT(14)             /*!< external event 5 resets counter */
#define SHRTIMER_STXCNTRST_EXEV6RST                      BIT(15)             /*!< external event 6 resets counter */
#define SHRTIMER_STXCNTRST_EXEV7RST                      BIT(16)             /*!< external event 7 resets counter */
#define SHRTIMER_STXCNTRST_EXEV8RST                      BIT(17)             /*!< external event 8 resets counter */
#define SHRTIMER_STXCNTRST_EXEV9RST                      BIT(18)             /*!< external event 9 resets counter */
/* For Slave_TIMER0 */
#define SHRTIMER_ST0CNTRST_ST1CMP0RST                    BIT(19)             /*!< Slave_TIMER1 compare 0 event resets counter */
#define SHRTIMER_ST0CNTRST_ST1CMP1RST                    BIT(20)             /*!< Slave_TIMER1 compare 1 event resets counter */
#define SHRTIMER_ST0CNTRST_ST1CMP3RST                    BIT(21)             /*!< Slave_TIMER1 compare 3 event resets counter */
#define SHRTIMER_ST0CNTRST_ST2CMP0RST                    BIT(22)             /*!< Slave_TIMER2 compare 0 event resets counter */
#define SHRTIMER_ST0CNTRST_ST2CMP1RST                    BIT(23)             /*!< Slave_TIMER2 compare 1 event resets counter */
#define SHRTIMER_ST0CNTRST_ST2CMP3RST                    BIT(24)             /*!< Slave_TIMER2 compare 3 event resets counter */
#define SHRTIMER_ST0CNTRST_ST3CMP0RST                    BIT(25)             /*!< Slave_TIMER3 compare 0 event resets counter */
#define SHRTIMER_ST0CNTRST_ST3CMP1RST                    BIT(26)             /*!< Slave_TIMER3 compare 1 event resets counter */
#define SHRTIMER_ST0CNTRST_ST3CMP3RST                    BIT(27)             /*!< Slave_TIMER3 compare 3 event resets counter */
#define SHRTIMER_ST0CNTRST_ST4CMP0RST                    BIT(28)             /*!< Slave_TIMER4 compare 0 event resets counter */
#define SHRTIMER_ST0CNTRST_ST4CMP1RST                    BIT(29)             /*!< Slave_TIMER4 compare 1 event resets counter */
#define SHRTIMER_ST0CNTRST_ST4CMP3RST                    BIT(30)             /*!< Slave_TIMER4 compare 3 event resets counter */
/* For Slave_TIMER1 */
#define SHRTIMER_ST1CNTRST_ST0CMP0RST                    BIT(19)             /*!< Slave_TIMER0 compare 0 event resets counter */
#define SHRTIMER_ST1CNTRST_ST0CMP1RST                    BIT(20)             /*!< Slave_TIMER0 compare 1 event resets counter */
#define SHRTIMER_ST1CNTRST_ST0CMP3RST                    BIT(21)             /*!< Slave_TIMER0 compare 3 event resets counter */
#define SHRTIMER_ST1CNTRST_ST2CMP0RST                    BIT(22)             /*!< Slave_TIMER2 compare 0 event resets counter */
#define SHRTIMER_ST1CNTRST_ST2CMP1RST                    BIT(23)             /*!< Slave_TIMER2 compare 1 event resets counter */
#define SHRTIMER_ST1CNTRST_ST2CMP3RST                    BIT(24)             /*!< Slave_TIMER2 compare 3 event resets counter */
#define SHRTIMER_ST1CNTRST_ST3CMP0RST                    BIT(25)             /*!< Slave_TIMER3 compare 0 event resets counter */
#define SHRTIMER_ST1CNTRST_ST3CMP1RST                    BIT(26)             /*!< Slave_TIMER3 compare 1 event resets counter */
#define SHRTIMER_ST1CNTRST_ST3CMP3RST                    BIT(27)             /*!< Slave_TIMER3 compare 3 event resets counter */
#define SHRTIMER_ST1CNTRST_ST4CMP0RST                    BIT(28)             /*!< Slave_TIMER4 compare 0 event resets counter */
#define SHRTIMER_ST1CNTRST_ST4CMP1RST                    BIT(29)             /*!< Slave_TIMER4 compare 1 event resets counter */
#define SHRTIMER_ST1CNTRST_ST4CMP3RST                    BIT(30)             /*!< Slave_TIMER4 compare 3 event resets counter */
/* For Slave_TIMER2 */
#define SHRTIMER_ST2CNTRST_ST0CMP0RST                    BIT(19)             /*!< Slave_TIMER0 compare 0 event resets counter */
#define SHRTIMER_ST2CNTRST_ST0CMP1RST                    BIT(20)             /*!< Slave_TIMER0 compare 1 event resets counter */
#define SHRTIMER_ST2CNTRST_ST0CMP3RST                    BIT(21)             /*!< Slave_TIMER0 compare 3 event resets counter */
#define SHRTIMER_ST2CNTRST_ST1CMP0RST                    BIT(22)             /*!< Slave_TIMER1 compare 0 event resets counter */
#define SHRTIMER_ST2CNTRST_ST1CMP1RST                    BIT(23)             /*!< Slave_TIMER1 compare 1 event resets counter */
#define SHRTIMER_ST2CNTRST_ST1CMP3RST                    BIT(24)             /*!< Slave_TIMER1 compare 3 event resets counter */
#define SHRTIMER_ST2CNTRST_ST3CMP0RST                    BIT(25)             /*!< Slave_TIMER3 compare 0 event resets counter */
#define SHRTIMER_ST2CNTRST_ST3CMP1RST                    BIT(26)             /*!< Slave_TIMER3 compare 1 event resets counter */
#define SHRTIMER_ST2CNTRST_ST3CMP3RST                    BIT(27)             /*!< Slave_TIMER3 compare 3 event resets counter */
#define SHRTIMER_ST2CNTRST_ST4CMP0RST                    BIT(28)             /*!< Slave_TIMER4 compare 0 event resets counter */
#define SHRTIMER_ST2CNTRST_ST4CMP1RST                    BIT(29)             /*!< Slave_TIMER4 compare 1 event resets counter */
#define SHRTIMER_ST2CNTRST_ST4CMP3RST                    BIT(30)             /*!< Slave_TIMER4 compare 3 event resets counter */
/* For Slave_TIMER3 */
#define SHRTIMER_ST3CNTRST_ST0CMP0RST                    BIT(19)             /*!< Slave_TIMER0 compare 0 event resets counter */
#define SHRTIMER_ST3CNTRST_ST0CMP1RST                    BIT(20)             /*!< Slave_TIMER0 compare 1 event resets counter */
#define SHRTIMER_ST3CNTRST_ST0CMP3RST                    BIT(21)             /*!< Slave_TIMER0 compare 3 event resets counter */
#define SHRTIMER_ST3CNTRST_ST1CMP0RST                    BIT(22)             /*!< Slave_TIMER1 compare 0 event resets counter */
#define SHRTIMER_ST3CNTRST_ST1CMP1RST                    BIT(23)             /*!< Slave_TIMER1 compare 1 event resets counter */
#define SHRTIMER_ST3CNTRST_ST1CMP3RST                    BIT(24)             /*!< Slave_TIMER1 compare 3 event resets counter */
#define SHRTIMER_ST3CNTRST_ST2CMP0RST                    BIT(25)             /*!< Slave_TIMER2 compare 0 event resets counter */
#define SHRTIMER_ST3CNTRST_ST2CMP1RST                    BIT(26)             /*!< Slave_TIMER2 compare 1 event resets counter */
#define SHRTIMER_ST3CNTRST_ST2CMP3RST                    BIT(27)             /*!< Slave_TIMER2 compare 3 event resets counter */
#define SHRTIMER_ST3CNTRST_ST4CMP0RST                    BIT(28)             /*!< Slave_TIMER4 compare 0 event resets counter */
#define SHRTIMER_ST3CNTRST_ST4CMP1RST                    BIT(29)             /*!< Slave_TIMER4 compare 1 event resets counter */
#define SHRTIMER_ST3CNTRST_ST4CMP3RST                    BIT(30)             /*!< Slave_TIMER4 compare 3 event resets counter */
/* For Slave_TIMER4 */
#define SHRTIMER_ST4CNTRST_ST0CMP0RST                    BIT(19)             /*!< Slave_TIMER0 compare 0 event resets counter */
#define SHRTIMER_ST4CNTRST_ST0CMP1RST                    BIT(20)             /*!< Slave_TIMER0 compare 1 event resets counter */
#define SHRTIMER_ST4CNTRST_ST0CMP3RST                    BIT(21)             /*!< Slave_TIMER0 compare 3 event resets counter */
#define SHRTIMER_ST4CNTRST_ST1CMP0RST                    BIT(22)             /*!< Slave_TIMER1 compare 0 event resets counter */
#define SHRTIMER_ST4CNTRST_ST1CMP1RST                    BIT(23)             /*!< Slave_TIMER1 compare 1 event resets counter */
#define SHRTIMER_ST4CNTRST_ST1CMP3RST                    BIT(24)             /*!< Slave_TIMER1 compare 3 event resets counter */
#define SHRTIMER_ST4CNTRST_ST2CMP0RST                    BIT(25)             /*!< Slave_TIMER2 compare 0 event resets counter */
#define SHRTIMER_ST4CNTRST_ST2CMP1RST                    BIT(26)             /*!< Slave_TIMER2 compare 1 event resets counter */
#define SHRTIMER_ST4CNTRST_ST2CMP3RST                    BIT(27)             /*!< Slave_TIMER2 compare 3 event resets counter */
#define SHRTIMER_ST4CNTRST_ST3CMP0RST                    BIT(28)             /*!< Slave_TIMER3 compare 0 event resets counter */
#define SHRTIMER_ST4CNTRST_ST3CMP1RST                    BIT(29)             /*!< Slave_TIMER3 compare 1 event resets counter */
#define SHRTIMER_ST4CNTRST_ST3CMP3RST                    BIT(30)             /*!< Slave_TIMER3 compare 3 event resets counter */

/* SHRTIMER_STxCSCTL */
#define SHRTIMER_STXCSCTL_CSPRD                          BITS(0,3)           /*!< carrier signal period */
#define SHRTIMER_STXCSCTL_CSDTY                          BITS(4,6)           /*!< carrier signal duty cycle */
#define SHRTIMER_STXCSCTL_CSFSTPW                        BITS(7,10)          /*!< first carrier-signal pulse width */

/* SHRTIMER_STxCAP0TRG */
#define SHRTIMER_STXCAP0TRG_CP0BSW                       BIT(0)              /*!< capture 0 triggered by software */
#define SHRTIMER_STXCAP0TRG_CP0BUP                       BIT(1)              /*!< capture 0 triggered by update event */
#define SHRTIMER_STXCAP0TRG_CP0BEXEV0                    BIT(2)              /*!< capture 0 triggered by external event 0 */
#define SHRTIMER_STXCAP0TRG_CP0BEXEV1                    BIT(3)              /*!< capture 0 triggered by external event 1 */
#define SHRTIMER_STXCAP0TRG_CP0BEXEV2                    BIT(4)              /*!< capture 0 triggered by external event 2 */
#define SHRTIMER_STXCAP0TRG_CP0BEXEV3                    BIT(5)              /*!< capture 0 triggered by external event 3 */
#define SHRTIMER_STXCAP0TRG_CP0BEXEV4                    BIT(6)              /*!< capture 0 triggered by external event 4 */
#define SHRTIMER_STXCAP0TRG_CP0BEXEV5                    BIT(7)              /*!< capture 0 triggered by external event 5 */
#define SHRTIMER_STXCAP0TRG_CP0BEXEV6                    BIT(8)              /*!< capture 0 triggered by external event 6 */
#define SHRTIMER_STXCAP0TRG_CP0BEXEV7                    BIT(9)              /*!< capture 0 triggered by external event 7 */
#define SHRTIMER_STXCAP0TRG_CP0BEXEV8                    BIT(10)             /*!< capture 0 triggered by external event 8 */
#define SHRTIMER_STXCAP0TRG_CP0BEXEV9                    BIT(11)             /*!< capture 0 triggered by external event 9 */
#define SHRTIMER_STXCAP0TRG_CP0BST0A                     BIT(12)             /*!< capture 0 triggered by ST0CH0_O output inactive to active transition */
#define SHRTIMER_STXCAP0TRG_CP0BST0NA                    BIT(13)             /*!< capture 0 triggered by ST0CH0_O output active to inactive transition */
#define SHRTIMER_STXCAP0TRG_CP0BST0CMP0                  BIT(14)             /*!< capture 0 triggered by compare 0 event of Slave_TIMER0  */
#define SHRTIMER_STXCAP0TRG_CP0BST0CMP1                  BIT(15)             /*!< capture 0 triggered by compare 1 event of Slave_TIMER0 */
#define SHRTIMER_STXCAP0TRG_CP0BST1A                     BIT(16)             /*!< capture 0 triggered by ST1CH0_O output inactive to active transition */
#define SHRTIMER_STXCAP0TRG_CP0BST1NA                    BIT(17)             /*!< capture 0 triggered by ST1CH0_O output active to inactive transition */
#define SHRTIMER_STXCAP0TRG_CP0BST1CMP0                  BIT(18)             /*!< capture 0 triggered by compare 0 event of Slave_TIMER1 */
#define SHRTIMER_STXCAP0TRG_CP0BST1CMP1                  BIT(19)             /*!< capture 0 triggered by compare 1 event of Slave_TIMER1 */
#define SHRTIMER_STXCAP0TRG_CP0BST2A                     BIT(20)             /*!< capture 0 triggered by ST2CH0_O output inactive to active transition */
#define SHRTIMER_STXCAP0TRG_CP0BST2NA                    BIT(21)             /*!< capture 0 triggered by ST2CH0_O output active to inactive transition */
#define SHRTIMER_STXCAP0TRG_CP0BST2CMP0                  BIT(22)             /*!< capture 0 triggered by compare 0 event of Slave_TIMER2 */
#define SHRTIMER_STXCAP0TRG_CP0BST2CMP1                  BIT(23)             /*!< capture 0 triggered by compare 1 event of Slave_TIMER2 */
#define SHRTIMER_STXCAP0TRG_CP0BST3A                     BIT(24)             /*!< capture 0 triggered by ST3CH0_O output inactive to active transition */
#define SHRTIMER_STXCAP0TRG_CP0BST3NA                    BIT(25)             /*!< capture 0 triggered by ST3CH0_O output active to inactive transition */
#define SHRTIMER_STXCAP0TRG_CP0BST3CMP0                  BIT(26)             /*!< capture 0 triggered by compare 0 event of Slave_TIMER3 */
#define SHRTIMER_STXCAP0TRG_CP0BST3CMP1                  BIT(27)             /*!< capture 0 triggered by compare 1 event of Slave_TIMER3 */
#define SHRTIMER_STXCAP0TRG_CP0BST4A                     BIT(28)             /*!< capture 0 triggered by ST4CH0_O output inactive to active transition */
#define SHRTIMER_STXCAP0TRG_CP0BST4NA                    BIT(29)             /*!< capture 0 triggered by ST4CH0_O output active to inactive transition. */
#define SHRTIMER_STXCAP0TRG_CP0BST4CMP0                  BIT(30)             /*!< capture 0 triggered by compare 0 event of Slave_TIMER4 */
#define SHRTIMER_STXCAP0TRG_CP0BST4CMP1                  BIT(31)             /*!< capture 0 triggered by compare 1 event of Slave_TIMER4 */

/* SHRTIMER_STxCAP1TRG */
#define SHRTIMER_STXCAP1TRG_CP1BSW                       BIT(0)              /*!< capture 1 triggered by software */
#define SHRTIMER_STXCAP1TRG_CP1BUP                       BIT(1)              /*!< capture 1 triggered by update event */
#define SHRTIMER_STXCAP1TRG_CP1BEXEV0                    BIT(2)              /*!< capture 1 triggered by external event 0 */
#define SHRTIMER_STXCAP1TRG_CP1BEXEV1                    BIT(3)              /*!< capture 1 triggered by external event 1 */
#define SHRTIMER_STXCAP1TRG_CP1BEXEV2                    BIT(4)              /*!< capture 1 triggered by external event 2 */
#define SHRTIMER_STXCAP1TRG_CP1BEXEV3                    BIT(5)              /*!< capture 1 triggered by external event 3 */
#define SHRTIMER_STXCAP1TRG_CP1BEXEV4                    BIT(6)              /*!< capture 1 triggered by external event 4 */
#define SHRTIMER_STXCAP1TRG_CP1BEXEV5                    BIT(7)              /*!< capture 1 triggered by external event 5 */
#define SHRTIMER_STXCAP1TRG_CP1BEXEV6                    BIT(8)              /*!< capture 1 triggered by external event 6 */
#define SHRTIMER_STXCAP1TRG_CP1BEXEV7                    BIT(9)              /*!< capture 1 triggered by external event 7 */
#define SHRTIMER_STXCAP1TRG_CP1BEXEV8                    BIT(10)             /*!< capture 1 triggered by external event 8 */
#define SHRTIMER_STXCAP1TRG_CP1BEXEV9                    BIT(11)             /*!< capture 1 triggered by external event 9 */
#define SHRTIMER_STXCAP1TRG_CP1BST0A                     BIT(12)             /*!< capture 1 triggered by ST0CH0_O output inactive to active transition */
#define SHRTIMER_STXCAP1TRG_CP1BST0NA                    BIT(13)             /*!< capture 1 triggered by ST0CH0_O output active to inactive transition */
#define SHRTIMER_STXCAP1TRG_CP1BST0CMP0                  BIT(14)             /*!< capture 1 triggered by compare 0 event of Slave_TIMER0  */
#define SHRTIMER_STXCAP1TRG_CP1BST0CMP1                  BIT(15)             /*!< capture 1 triggered by compare 1 event of Slave_TIMER0 */
#define SHRTIMER_STXCAP1TRG_CP1BST1A                     BIT(16)             /*!< capture 1 triggered by ST1CH0_O output inactive to active transition */
#define SHRTIMER_STXCAP1TRG_CP1BST1NA                    BIT(17)             /*!< capture 1 triggered by ST1CH0_O output active to inactive transition */
#define SHRTIMER_STXCAP1TRG_CP1BST1CMP0                  BIT(18)             /*!< capture 1 triggered by compare 0 event of Slave_TIMER1 */
#define SHRTIMER_STXCAP1TRG_CP1BST1CMP1                  BIT(19)             /*!< capture 1 triggered by compare 1 event of Slave_TIMER1 */
#define SHRTIMER_STXCAP1TRG_CP1BST2A                     BIT(20)             /*!< capture 1 triggered by ST2CH0_O output inactive to active transition */
#define SHRTIMER_STXCAP1TRG_CP1BST2NA                    BIT(21)             /*!< capture 1 triggered by ST2CH0_O output active to inactive transition */
#define SHRTIMER_STXCAP1TRG_CP1BST2CMP0                  BIT(22)             /*!< capture 1 triggered by compare 0 event of Slave_TIMER2 */
#define SHRTIMER_STXCAP1TRG_CP1BST2CMP1                  BIT(23)             /*!< capture 1 triggered by compare 1 event of Slave_TIMER2 */
#define SHRTIMER_STXCAP1TRG_CP1BST3A                     BIT(24)             /*!< capture 1 triggered by ST3CH0_O output inactive to active transition */
#define SHRTIMER_STXCAP1TRG_CP1BST3NA                    BIT(25)             /*!< capture 1 triggered by ST3CH0_O output active to inactive transition */
#define SHRTIMER_STXCAP1TRG_CP1BST3CMP0                  BIT(26)             /*!< capture 1 triggered by compare 0 event of Slave_TIMER3 */
#define SHRTIMER_STXCAP1TRG_CP1BST3CMP1                  BIT(27)             /*!< capture 1 triggered by compare 1 event of Slave_TIMER3 */
#define SHRTIMER_STXCAP1TRG_CP1BST4A                     BIT(28)             /*!< capture 1 triggered by ST4CH0_O output inactive to active transition */
#define SHRTIMER_STXCAP1TRG_CP1BST4NA                    BIT(29)             /*!< capture 1 triggered by ST4CH0_O output active to inactive transition. */
#define SHRTIMER_STXCAP1TRG_CP1BST4CMP0                  BIT(30)             /*!< capture 1 triggered by compare 0 event of Slave_TIMER4 */
#define SHRTIMER_STXCAP1TRG_CP1BST4CMP1                  BIT(31)             /*!< capture 1 triggered by compare 1 event of Slave_TIMER4 */

/* SHRTIMER_STxCHOCTL */
#define SHRTIMER_STXCHOCTL_CH0P                          BIT(1)              /*!< channel 0 output polarity */
#define SHRTIMER_STXCHOCTL_BMCH0IEN                      BIT(2)              /*!< channel 0 IDLE state enable in bunch mode */
#define SHRTIMER_STXCHOCTL_ISO0                          BIT(3)              /*!< channel 0 output idle state */
#define SHRTIMER_STXCHOCTL_CH0FLTOS                      BITS(4,5)           /*!< channel 0 fault output state */
#define SHRTIMER_STXCHOCTL_CH0CSEN                       BIT(6)              /*!< channel 0 carrier-signal mode enable */
#define SHRTIMER_STXCHOCTL_BMCH0DTI                      BIT(7)              /*!< channel 0 dead-time insert in bunch mode */
#define SHRTIMER_STXCHOCTL_DTEN                          BIT(8)              /*!< dead time enable */
#define SHRTIMER_STXCHOCTL_DLYISMEN                      BIT(9)              /*!< delayed IDLE state mode enable */
#define SHRTIMER_STXCHOCTL_DLYISCH                       BITS(10,12)         /*!< delayed IDLE source and channel */
#define SHRTIMER_STXCHOCTL_CH1P                          BIT(17)             /*!< channel 1 output polarity */
#define SHRTIMER_STXCHOCTL_BMCH1IEN                      BIT(18)             /*!< channel 1 IDLE state enable in bunch mode */
#define SHRTIMER_STXCHOCTL_ISO1                          BIT(19)             /*!< channel 1 output idle state */
#define SHRTIMER_STXCHOCTL_CH1FLTOS                      BITS(20,21)         /*!< channel 1 fault output state */
#define SHRTIMER_STXCHOCTL_CH1CSEN                       BIT(22)             /*!< channel 1 carrier-signal mode enable */
#define SHRTIMER_STXCHOCTL_BMCH1DTI                      BIT(23)             /*!< channel 1 dead-time insert in bunch mode */

/* SHRTIMER_STxFLTCTL */
#define SHRTIMER_STXFLTCTL_FLT0EN                        BIT(0)              /*!< fault 0 enable */
#define SHRTIMER_STXFLTCTL_FLT1EN                        BIT(1)              /*!< fault 1 enable */
#define SHRTIMER_STXFLTCTL_FLT2EN                        BIT(2)              /*!< fault 2 enable */
#define SHRTIMER_STXFLTCTL_FLT3EN                        BIT(3)              /*!< fault 3 enable */
#define SHRTIMER_STXFLTCTL_FLT4EN                        BIT(4)              /*!< fault 4 enable */
#define SHRTIMER_STXFLTCTL_FLTENPROT                     BIT(31)             /*!< protect fault enable */

/* SHRTIMER_STxACTL */
#define SHRTIMER_STXACTL_CNTCKDIV3                       BIT(3)              /*!< counter clock division */
#define SHRTIMER_STXACTL_DTRCFG15_9                      BITS(9,15)          /*!< rising edge dead-time value configure */
#define SHRTIMER_STXACTL_DTFCFG15_9                      BITS(25,31)         /*!< falling edge dead-time value configure */

/* Common registers */
/* SHRTIMER_CTL0 */
#define SHRTIMER_CTL0_MTUPDIS                            BIT(0)              /*!< Master_TIMER update disable */
#define SHRTIMER_CTL0_ST0UPDIS                           BIT(1)              /*!< Slave_TIMER0 update disable */
#define SHRTIMER_CTL0_ST1UPDIS                           BIT(2)              /*!< Slave_TIMER1 update disable */
#define SHRTIMER_CTL0_ST2UPDIS                           BIT(3)              /*!< Slave_TIMER2 update disable */
#define SHRTIMER_CTL0_ST3UPDIS                           BIT(4)              /*!< Slave_TIMER3 update disable */
#define SHRTIMER_CTL0_ST4UPDIS                           BIT(5)              /*!< Slave_TIMER4 update disable */
#define SHRTIMER_CTL0_ADTG0USRC                          BITS(16,18)         /*!< SHRTIMER_ADCTRIG0 update source */
#define SHRTIMER_CTL0_ADTG1USRC                          BITS(19,21)         /*!< SHRTIMER_ADCTRIG1 update source */
#define SHRTIMER_CTL0_ADTG2USRC                          BITS(22,24)         /*!< SHRTIMER_ADCTRIG2 update source */
#define SHRTIMER_CTL0_ADTG3USRC                          BITS(25,27)         /*!< SHRTIMER_ADCTRIG3 update source */

/* SHRTIMER_CTL1 */
#define SHRTIMER_CTL1_MTSUP                              BIT(0)              /*!< Master_TIMER software update */
#define SHRTIMER_CTL1_ST0SUP                             BIT(1)              /*!< Slave_TIMER0 software update */
#define SHRTIMER_CTL1_ST1SUP                             BIT(2)              /*!< Slave_TIMER1 software update */
#define SHRTIMER_CTL1_ST2SUP                             BIT(3)              /*!< Slave_TIMER2 software update */
#define SHRTIMER_CTL1_ST3SUP                             BIT(4)              /*!< Slave_TIMER3 software update */
#define SHRTIMER_CTL1_ST4SUP                             BIT(5)              /*!< Slave_TIMER4 software update */
#define SHRTIMER_CTL1_MTSRST                             BIT(8)              /*!< Master_TIMER software reset */
#define SHRTIMER_CTL1_ST0SRST                            BIT(9)              /*!< Slave_TIMER0 software reset */
#define SHRTIMER_CTL1_ST1SRST                            BIT(10)             /*!< Slave_TIMER1 software reset */
#define SHRTIMER_CTL1_ST2SRST                            BIT(11)             /*!< Slave_TIMER2 software reset */
#define SHRTIMER_CTL1_ST3SRST                            BIT(12)             /*!< Slave_TIMER3 software reset */
#define SHRTIMER_CTL1_ST4SRST                            BIT(13)             /*!< Slave_TIMER4 software reset */

/* SHRTIMER_INTF */
#define SHRTIMER_INTF_FLT0IF                             BIT(0)              /*!< fault 0 interrupt flag */
#define SHRTIMER_INTF_FLT1IF                             BIT(1)              /*!< fault 1 interrupt flag */
#define SHRTIMER_INTF_FLT2IF                             BIT(2)              /*!< fault 2 interrupt flag */
#define SHRTIMER_INTF_FLT3IF                             BIT(3)              /*!< fault 3 interrupt flag */
#define SHRTIMER_INTF_FLT4IF                             BIT(4)              /*!< fault 4 interrupt flag */
#define SHRTIMER_INTF_SYSFLTIF                           BIT(5)              /*!< system fault interrupt flag */
#define SHRTIMER_INTF_DLLCALIF                           BIT(16)             /*!< DLL calibration completed interrupt flag */
#define SHRTIMER_INTF_BMPERIF                            BIT(17)             /*!< bunch mode period interrupt flag */

/* SHRTIMER_INTC */
#define SHRTIMER_INTC_FLT0IFC                            BIT(0)              /*!< clear fault 0 interrupt flag */
#define SHRTIMER_INTC_FLT1IFC                            BIT(1)              /*!< clear fault 1 interrupt flag */
#define SHRTIMER_INTC_FLT2IFC                            BIT(2)              /*!< clear fault 2 interrupt flag */
#define SHRTIMER_INTC_FLT3IFC                            BIT(3)              /*!< clear fault 3 interrupt flag */
#define SHRTIMER_INTC_FLT4IFC                            BIT(4)              /*!< clear fault 4 interrupt flag */
#define SHRTIMER_INTC_SYSFLTIFC                          BIT(5)              /*!< clear system fault interrupt flag */
#define SHRTIMER_INTC_DLLCALIFC                          BIT(16)             /*!< clear DLL calibration completed interrupt flag */
#define SHRTIMER_INTC_BMPERIFC                           BIT(17)             /*!< clear bunch mode period interrupt flag */

/* SHRTIMER_INTEN */
#define SHRTIMER_INTEN_FLT0IE                            BIT(0)              /*!< fault 0 interrupt enable */
#define SHRTIMER_INTEN_FLT1IE                            BIT(1)              /*!< fault 1 interrupt enable */
#define SHRTIMER_INTEN_FLT2IE                            BIT(2)              /*!< fault 2 interrupt enable */
#define SHRTIMER_INTEN_FLT3IE                            BIT(3)              /*!< fault 3 interrupt enable */
#define SHRTIMER_INTEN_FLT4IE                            BIT(4)              /*!< fault 4 interrupt enable */
#define SHRTIMER_INTEN_SYSFLTIE                          BIT(5)              /*!< system fault interrupt enable */
#define SHRTIMER_INTEN_DLLCALIE                          BIT(16)             /*!< DLL calibration completed interrupt enable */
#define SHRTIMER_INTEN_BMPERIE                           BIT(17)             /*!< bunch mode period interrupt enable */

/* SHRTIMER_CHOUTEN */
#define SHRTIMER_CHOUTEN_ST0CH0EN                        BIT(0)              /*!< Slave_TIMER0 channel 0 output (ST0CH0_O) enable */
#define SHRTIMER_CHOUTEN_ST0CH1EN                        BIT(1)              /*!< Slave_TIMER0 channel 1 output (ST0CH1_O) enable */
#define SHRTIMER_CHOUTEN_ST1CH0EN                        BIT(2)              /*!< Slave_TIMER1 channel 0 output (ST1CH0_O) enable */
#define SHRTIMER_CHOUTEN_ST1CH1EN                        BIT(3)              /*!< Slave_TIMER1 channel 1 output (ST1CH1_O) enable */
#define SHRTIMER_CHOUTEN_ST2CH0EN                        BIT(4)              /*!< Slave_TIMER2 channel 0 output (ST2CH0_O) enable */
#define SHRTIMER_CHOUTEN_ST2CH1EN                        BIT(5)              /*!< Slave_TIMER2 channel 1 output (ST2CH1_O) enable */
#define SHRTIMER_CHOUTEN_ST3CH0EN                        BIT(6)              /*!< Slave_TIMER3 channel 0 output (ST3CH0_O) enable */
#define SHRTIMER_CHOUTEN_ST3CH1EN                        BIT(7)              /*!< Slave_TIMER3 channel 1 output (ST3CH1_O) enable */
#define SHRTIMER_CHOUTEN_ST4CH0EN                        BIT(8)              /*!< Slave_TIMER4 channel 0 output (ST4CH0_O) enable */
#define SHRTIMER_CHOUTEN_ST4CH1EN                        BIT(9)              /*!< Slave_TIMER4 channel 1 output (ST4CH1_O) enable */

/* SHRTIMER_CHOUTDIS */
#define SHRTIMER_CHOUTDIS_ST0CH0DIS                      BIT(0)              /*!< Slave_TIMER0 channel 0 output (ST0CH0_O) disable */
#define SHRTIMER_CHOUTDIS_ST0CH1DIS                      BIT(1)              /*!< Slave_TIMER0 channel 1 output (ST0CH1_O) disable */
#define SHRTIMER_CHOUTDIS_ST1CH0DIS                      BIT(2)              /*!< Slave_TIMER1 channel 0 output (ST1CH0_O) disable */
#define SHRTIMER_CHOUTDIS_ST1CH1DIS                      BIT(3)              /*!< Slave_TIMER1 channel 1 output (ST1CH1_O) disable */
#define SHRTIMER_CHOUTDIS_ST2CH0DIS                      BIT(4)              /*!< Slave_TIMER2 channel 0 output (ST2CH0_O) disable */
#define SHRTIMER_CHOUTDIS_ST2CH1DIS                      BIT(5)              /*!< Slave_TIMER2 channel 1 output (ST2CH1_O) disable */
#define SHRTIMER_CHOUTDIS_ST3CH0DIS                      BIT(6)              /*!< Slave_TIMER3 channel 0 output (ST3CH0_O) disable */
#define SHRTIMER_CHOUTDIS_ST3CH1DIS                      BIT(7)              /*!< Slave_TIMER3 channel 1 output (ST3CH1_O) disable */
#define SHRTIMER_CHOUTDIS_ST4CH0DIS                      BIT(8)              /*!< Slave_TIMER4 channel 0 output (ST4CH0_O) disable */
#define SHRTIMER_CHOUTDIS_ST4CH1DIS                      BIT(9)              /*!< Slave_TIMER4 channel 1 output (ST4CH1_O) disable */

/* SHRTIMER_CHOUTDISF */
#define SHRTIMER_CHOUTDISF_ST0CH0DISF                    BIT(0)              /*!< Slave_TIMER0 channel 0 output (ST0CH0_O) disable flag */
#define SHRTIMER_CHOUTDISF_ST0CH1DISF                    BIT(1)              /*!< Slave_TIMER0 channel 1 output (ST0CH1_O) disable flag */
#define SHRTIMER_CHOUTDISF_ST1CH0DISF                    BIT(2)              /*!< Slave_TIMER1 channel 0 output (ST1CH0_O) disable flag */
#define SHRTIMER_CHOUTDISF_ST1CH1DISF                    BIT(3)              /*!< Slave_TIMER1 channel 1 output (ST1CH1_O) disable flag */
#define SHRTIMER_CHOUTDISF_ST2CH0DISF                    BIT(4)              /*!< Slave_TIMER2 channel 0 output (ST2CH0_O) disable flag */
#define SHRTIMER_CHOUTDISF_ST2CH1DISF                    BIT(5)              /*!< Slave_TIMER2 channel 1 output (ST2CH1_O) disable flag */
#define SHRTIMER_CHOUTDISF_ST3CH0DISF                    BIT(6)              /*!< Slave_TIMER3 channel 0 output (ST3CH0_O) disable flag */
#define SHRTIMER_CHOUTDISF_ST3CH1DISF                    BIT(7)              /*!< Slave_TIMER3 channel 1 output (ST3CH1_O) disable flag */
#define SHRTIMER_CHOUTDISF_ST4CH0DISF                    BIT(8)              /*!< Slave_TIMER4 channel 0 output (ST4CH0_O) disable flag */
#define SHRTIMER_CHOUTDISF_ST4CH1DISF                    BIT(9)              /*!< Slave_TIMER4 channel 1 output (ST4CH1_O) disable flag */

/* SHRTIMER_BMCTL */
#define SHRTIMER_BMCTL_BMEN                              BIT(0)              /*!< bunch mode enable */
#define SHRTIMER_BMCTL_BMCTN                             BIT(1)              /*!< continuous mode in bunch mode */
#define SHRTIMER_BMCTL_BMCLKS                            BITS(2,5)           /*!< bunch mode clock source */
#define SHRTIMER_BMCTL_BMPSC                             BITS(6,9)           /*!< bunch mode clock division */
#define SHRTIMER_BMCTL_BMSE                              BIT(10)             /*!< bunch mode shadow enable */
#define SHRTIMER_BMCTL_BMMT                              BIT(16)             /*!< Master_TIMER bunch mode */
#define SHRTIMER_BMCTL_BMST0                             BIT(17)             /*!< Slave_TIMER0 bunch mode */
#define SHRTIMER_BMCTL_BMST1                             BIT(18)             /*!< Slave_TIMER1 bunch mode */
#define SHRTIMER_BMCTL_BMST2                             BIT(19)             /*!< Slave_TIMER2 bunch mode */
#define SHRTIMER_BMCTL_BMST3                             BIT(20)             /*!< Slave_TIMER3 bunch mode */
#define SHRTIMER_BMCTL_BMST4                             BIT(21)             /*!< Slave_TIMER4 bunch mode */
#define SHRTIMER_BMCTL_BMOPTF                            BIT(31)             /*!< bunch mode operating flag */

/* SHRTIMER_BMSTRG */
#define SHRTIMER_BMSTRG_SWTRG                            BIT(0)              /*!< software triggers bunch mode operation */
#define SHRTIMER_BMSTRG_MTRST                            BIT(1)              /*!< Master_TIMER reset event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_MTREP                            BIT(2)              /*!< Master_TIMER repetition event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_MTCMP0                           BIT(3)              /*!< Master_TIMER compare 0 event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_MTCMP1                           BIT(4)              /*!< Master_TIMER compare 1 event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_MTCMP2                           BIT(5)              /*!< Master_TIMER compare 2 event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_MTCMP3                           BIT(6)              /*!< Master_TIMER compare 3 event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST0RST                           BIT(7)              /*!< Slave_TIMER0 reset event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST0REP                           BIT(8)              /*!< Slave_TIMER0 repetition event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST0CMP0                          BIT(9)              /*!< Slave_TIMER0 compare 0 event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST0CMP1                          BIT(10)             /*!< Slave_TIMER0 compare 1 event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST1RST                           BIT(11)             /*!< Slave_TIMER1 reset event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST1REP                           BIT(12)             /*!< Slave_TIMER1 repetition event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST1CMP0                          BIT(13)             /*!< Slave_TIMER1 compare 0 event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST1CMP1                          BIT(14)             /*!< Slave_TIMER1 compare 1 event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST2RST                           BIT(15)             /*!< Slave_TIMER2 reset event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST2REP                           BIT(16)             /*!< Slave_TIMER2 repetition event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST2CMP0                          BIT(17)             /*!< Slave_TIMER2 compare 0 event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST2CMP1                          BIT(18)             /*!< Slave_TIMER2 compare 1 event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST3RST                           BIT(19)             /*!< Slave_TIMER3 reset event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST3REP                           BIT(20)             /*!< Slave_TIMER3 repetition event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST3CMP0                          BIT(21)             /*!< Slave_TIMER3 compare 0 event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST3CMP1                          BIT(22)             /*!< Slave_TIMER3 compare 1 event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST4RST                           BIT(23)             /*!< Slave_TIMER4 reset event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST4REP                           BIT(24)             /*!< Slave_TIMER4 repetition event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST4CMP0                          BIT(25)             /*!< Slave_TIMER4 compare 0 event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST4CMP1                          BIT(26)             /*!< Slave_TIMER4 compare 1 event triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST0EXEV6                         BIT(27)             /*!< Slave_TIMER0 period event following external event 6 triggers bunch mode operation */
#define SHRTIMER_BMSTRG_ST3EXEV7                         BIT(28)             /*!< Slave_TIMER3 period event following external event 7 triggers bunch mode operation */
#define SHRTIMER_BMSTRG_EXEV6                            BIT(29)             /*!< external event 6 triggers bunch mode operation */
#define SHRTIMER_BMSTRG_EXEV7                            BIT(30)             /*!< external event 7 triggers bunch mode operation */
#define SHRTIMER_BMSTRG_CISGN                            BIT(31)             /*!< chip internal signal triggers bunch mode operation */

/* SHRTIMER_BMCMPV */
#define SHRTIMER_BMCMPV_BMCMPVAL                         BITS(0,15)          /*!< bunch mode compare value */

/* SHRTIMER_BMCAR */
#define SHRTIMER_BMCAR_BMCARL                            BITS(0,15)          /*!< bunch mode counter auto reload value */

/* SHRTIMER_EXEVCFG0 */
#define SHRTIMER_EXEVCFG0_EXEV0SRC                       BITS(0,1)           /*!< external event 0 source */
#define SHRTIMER_EXEVCFG0_EXEV0P                         BIT(2)              /*!< external event 0 polarity */
#define SHRTIMER_EXEVCFG0_EXEV0EG                        BITS(3,4)           /*!< external event 0 edge sensitivity */
#define SHRTIMER_EXEVCFG0_EXEV1SRC                       BITS(6,7)           /*!< external event 1 source */
#define SHRTIMER_EXEVCFG0_EXEV1P                         BIT(8)              /*!< external event 1 polarity */
#define SHRTIMER_EXEVCFG0_EXEV1EG                        BITS(9,10)          /*!< external event 1 edge sensitivity */
#define SHRTIMER_EXEVCFG0_EXEV2SRC                       BITS(12,13)         /*!< external event 2 source */
#define SHRTIMER_EXEVCFG0_EXEV2P                         BIT(14)             /*!< external event 2 polarity */
#define SHRTIMER_EXEVCFG0_EXEV2EG                        BITS(15,16)         /*!< external event 2 edge sensitivity */
#define SHRTIMER_EXEVCFG0_EXEV3SRC                       BITS(18,19)         /*!< external event 3 source */
#define SHRTIMER_EXEVCFG0_EXEV3P                         BIT(20)             /*!< external event 3 polarity */
#define SHRTIMER_EXEVCFG0_EXEV3EG                        BITS(21,22)         /*!< external event 3 edge sensitivity */
#define SHRTIMER_EXEVCFG0_EXEV4SRC                       BITS(24,25)         /*!< external event 4 source */
#define SHRTIMER_EXEVCFG0_EXEV4P                         BIT(26)             /*!< external event 4 polarity */
#define SHRTIMER_EXEVCFG0_EXEV4EG                        BITS(27,28)         /*!< external event 4 edge sensitivity */

/* SHRTIMER_EXEVCFG1 */
#define SHRTIMER_EXEVCFG1_EXEV5SRC                       BITS(0,1)           /*!< external event 5 source */
#define SHRTIMER_EXEVCFG1_EXEV5P                         BIT(2)              /*!< external event 5 polarity */
#define SHRTIMER_EXEVCFG1_EXEV5EG                        BITS(3,4)           /*!< external event 5 edge sensitivity */
#define SHRTIMER_EXEVCFG1_EXEV6SRC                       BITS(6,7)           /*!< external event 6 source */
#define SHRTIMER_EXEVCFG1_EXEV6P                         BIT(8)              /*!< external event 6 polarity */
#define SHRTIMER_EXEVCFG1_EXEV6EG                        BITS(9,10)          /*!< external event 6 edge sensitivity */
#define SHRTIMER_EXEVCFG1_EXEV7SRC                       BITS(12,13)         /*!< external event 7 source */
#define SHRTIMER_EXEVCFG1_EXEV7P                         BIT(14)             /*!< external event 7 polarity */
#define SHRTIMER_EXEVCFG1_EXEV7EG                        BITS(15,16)         /*!< external event 7 edge sensitivity */
#define SHRTIMER_EXEVCFG1_EXEV8SRC                       BITS(18,19)         /*!< external event 8 source */
#define SHRTIMER_EXEVCFG1_EXEV8P                         BIT(20)             /*!< external event 8 polarity */
#define SHRTIMER_EXEVCFG1_EXEV8EG                        BITS(21,22)         /*!< external event 8 edge sensitivity */
#define SHRTIMER_EXEVCFG1_EXEV9SRC                       BITS(24,25)         /*!< external event 9 source */
#define SHRTIMER_EXEVCFG1_EXEV9P                         BIT(26)             /*!< external event 9 polarity */
#define SHRTIMER_EXEVCFG1_EXEV9EG                        BITS(27,28)         /*!< external event 9 edge sensitivity */

/* SHRTIMER_EXEVDFCTL */
#define SHRTIMER_EXEVDFCTL_EXEV5FC                       BITS(0,3)           /*!< external event 5 filter control */
#define SHRTIMER_EXEVDFCTL_EXEV6FC                       BITS(6,9)           /*!< external event 6 filter control */
#define SHRTIMER_EXEVDFCTL_EXEV7FC                       BITS(12,15)         /*!< external event 7 filter control */
#define SHRTIMER_EXEVDFCTL_EXEV8FC                       BITS(18,21)         /*!< external event 8 filter control */
#define SHRTIMER_EXEVDFCTL_EXEV9FC                       BITS(24,27)         /*!< external event 9 filter control */
#define SHRTIMER_EXEVDFCTL_EXEVFDIV                      BITS(30,31)         /*!< external event digital filter clock division */

/* SHRTIMER_ADCTRIGS0 */
#define SHRTIMER_ADCTRIGS0_TRG0MTC0                      BIT(0)              /*!< SHRTIMER_ADCTRIG0 on Master_TIMER compare 0 event */
#define SHRTIMER_ADCTRIGS0_TRG0MTC1                      BIT(1)              /*!< SHRTIMER_ADCTRIG0 on Master_TIMER compare 1 event */
#define SHRTIMER_ADCTRIGS0_TRG0MTC2                      BIT(2)              /*!< SHRTIMER_ADCTRIG0 on Master_TIMER compare 2 event */
#define SHRTIMER_ADCTRIGS0_TRG0MTC3                      BIT(3)              /*!< SHRTIMER_ADCTRIG0 on Master_TIMER compare 3 event */
#define SHRTIMER_ADCTRIGS0_TRG0MTPER                     BIT(4)              /*!< SHRTIMER_ADCTRIG0 on Master_TIMER period event */
#define SHRTIMER_ADCTRIGS0_TRG0EXEV0                     BIT(5)              /*!< SHRTIMER_ADCTRIG0 on external event 0 */
#define SHRTIMER_ADCTRIGS0_TRG0EXEV1                     BIT(6)              /*!< SHRTIMER_ADCTRIG0 on external event 1 */
#define SHRTIMER_ADCTRIGS0_TRG0EXEV2                     BIT(7)              /*!< SHRTIMER_ADCTRIG0 on external event 2 */
#define SHRTIMER_ADCTRIGS0_TRG0EXEV3                     BIT(8)              /*!< SHRTIMER_ADCTRIG0 on external event 3 */
#define SHRTIMER_ADCTRIGS0_TRG0EXEV4                     BIT(9)              /*!< SHRTIMER_ADCTRIG0 on external event 4 */
#define SHRTIMER_ADCTRIGS0_TRG0ST0C1                     BIT(10)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER0 compare 1 event */
#define SHRTIMER_ADCTRIGS0_TRG0ST0C2                     BIT(11)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER0 compare 2 event */
#define SHRTIMER_ADCTRIGS0_TRG0ST0C3                     BIT(12)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER0 compare 3 event */
#define SHRTIMER_ADCTRIGS0_TRG0ST0PER                    BIT(13)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER0 period event */
#define SHRTIMER_ADCTRIGS0_TRG0ST0RST                    BIT(14)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER0 reset and counter roll-over event */
#define SHRTIMER_ADCTRIGS0_TRG0ST1C1                     BIT(15)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER1 compare 1 event */
#define SHRTIMER_ADCTRIGS0_TRG0ST1C2                     BIT(16)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER1 compare 2 event */
#define SHRTIMER_ADCTRIGS0_TRG0ST1C3                     BIT(17)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER1 compare 3 event */
#define SHRTIMER_ADCTRIGS0_TRG0ST1PER                    BIT(18)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER1 period event */
#define SHRTIMER_ADCTRIGS0_TRG0ST1RST                    BIT(19)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER1 reset and counter roll-over event */
#define SHRTIMER_ADCTRIGS0_TRG0ST2C1                     BIT(20)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER2 compare 1 event */
#define SHRTIMER_ADCTRIGS0_TRG0ST2C2                     BIT(21)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER2 compare 2 event */
#define SHRTIMER_ADCTRIGS0_TRG0ST2C3                     BIT(22)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER2 compare 3 event */
#define SHRTIMER_ADCTRIGS0_TRG0ST2PER                    BIT(23)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER2 period event */
#define SHRTIMER_ADCTRIGS0_TRG0ST3C1                     BIT(24)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER3 compare 1 event */
#define SHRTIMER_ADCTRIGS0_TRG0ST3C2                     BIT(25)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER3 compare 2 event */
#define SHRTIMER_ADCTRIGS0_TRG0ST3C3                     BIT(26)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER3 compare 3 event */
#define SHRTIMER_ADCTRIGS0_TRG0ST3PER                    BIT(27)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER3 period event */
#define SHRTIMER_ADCTRIGS0_TRG0ST4C1                     BIT(28)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER4 compare 1 event */
#define SHRTIMER_ADCTRIGS0_TRG0ST4C2                     BIT(29)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER4 compare 2 event */
#define SHRTIMER_ADCTRIGS0_TRG0ST4C3                     BIT(30)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER4 compare 3 event */
#define SHRTIMER_ADCTRIGS0_TRG0ST4PER                    BIT(31)             /*!< SHRTIMER_ADCTRIG0 on Slave_TIMER4 period event */

/* SHRTIMER_ADCTRIGS1 */
#define SHRTIMER_ADCTRIGS1_TRG1MTC0                      BIT(0)              /*!< SHRTIMER_ADCTRIG1 on Master_TIMER compare 0 event */
#define SHRTIMER_ADCTRIGS1_TRG1MTC1                      BIT(1)              /*!< SHRTIMER_ADCTRIG1 on Master_TIMER compare 1 event */
#define SHRTIMER_ADCTRIGS1_TRG1MTC2                      BIT(2)              /*!< SHRTIMER_ADCTRIG1 on Master_TIMER compare 2 event */
#define SHRTIMER_ADCTRIGS1_TRG1MTC3                      BIT(3)              /*!< SHRTIMER_ADCTRIG1 on Master_TIMER compare 3 event */
#define SHRTIMER_ADCTRIGS1_TRG1MTPER                     BIT(4)              /*!< SHRTIMER_ADCTRIG1 on Master_TIMER period event */
#define SHRTIMER_ADCTRIGS1_TRG1EXEV5                     BIT(5)              /*!< SHRTIMER_ADCTRIG1 on external event 5 */
#define SHRTIMER_ADCTRIGS1_TRG1EXEV6                     BIT(6)              /*!< SHRTIMER_ADCTRIG1 on external event 6 */
#define SHRTIMER_ADCTRIGS1_TRG1EXEV7                     BIT(7)              /*!< SHRTIMER_ADCTRIG1 on external event 7 */
#define SHRTIMER_ADCTRIGS1_TRG1EXEV8                     BIT(8)              /*!< SHRTIMER_ADCTRIG1 on external event 8 */
#define SHRTIMER_ADCTRIGS1_TRG1EXEV9                     BIT(9)              /*!< SHRTIMER_ADCTRIG1 on external event 9 */
#define SHRTIMER_ADCTRIGS1_TRG1ST0C1                     BIT(10)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER0 compare 1 event */
#define SHRTIMER_ADCTRIGS1_TRG1ST0C2                     BIT(11)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER0 compare 2 event */
#define SHRTIMER_ADCTRIGS1_TRG1ST0C3                     BIT(12)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER0 compare 3 event */
#define SHRTIMER_ADCTRIGS1_TRG1ST0PER                    BIT(13)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER0 period event */
#define SHRTIMER_ADCTRIGS1_TRG1ST1C1                     BIT(14)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER1 compare 1 event */
#define SHRTIMER_ADCTRIGS1_TRG1ST1C2                     BIT(15)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER1 compare 2 event */
#define SHRTIMER_ADCTRIGS1_TRG1ST1C3                     BIT(16)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER1 compare 3 event */
#define SHRTIMER_ADCTRIGS1_TRG1ST1PER                    BIT(17)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER1 period event */
#define SHRTIMER_ADCTRIGS1_TRG1ST2C1                     BIT(18)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER2 compare 1 event */
#define SHRTIMER_ADCTRIGS1_TRG1ST2C2                     BIT(19)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER2 compare 2 event */
#define SHRTIMER_ADCTRIGS1_TRG1ST2C3                     BIT(20)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER2 compare 3 event */
#define SHRTIMER_ADCTRIGS1_TRG1ST2PER                    BIT(21)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER2 period event */
#define SHRTIMER_ADCTRIGS1_TRG1ST2RST                    BIT(22)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER2 reset and counter roll-over event */
#define SHRTIMER_ADCTRIGS1_TRG1ST3C1                     BIT(23)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER3 compare 1 event */
#define SHRTIMER_ADCTRIGS1_TRG1ST3C2                     BIT(24)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER3 compare 2 event */
#define SHRTIMER_ADCTRIGS1_TRG1ST3C3                     BIT(25)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER3 compare 3 event */
#define SHRTIMER_ADCTRIGS1_TRG1ST3PER                    BIT(26)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER3 period event */
#define SHRTIMER_ADCTRIGS1_TRG1ST3RST                    BIT(27)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER3 reset and counter roll-over event */
#define SHRTIMER_ADCTRIGS1_TRG1ST4C1                     BIT(28)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER4 compare 1 event */
#define SHRTIMER_ADCTRIGS1_TRG1ST4C2                     BIT(29)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER4 compare 2 event */
#define SHRTIMER_ADCTRIGS1_TRG1ST4C3                     BIT(30)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER4 compare 3 event */
#define SHRTIMER_ADCTRIGS1_TRG1ST4RST                    BIT(31)             /*!< SHRTIMER_ADCTRIG1 on Slave_TIMER4 reset and counter roll-over event */

/* SHRTIMER_ADCTRIGS2 */
#define SHRTIMER_ADCTRIGS2_TRG2MTC0                      BIT(0)              /*!< SHRTIMER_ADCTRIG2 on Master_TIMER compare 0 event */
#define SHRTIMER_ADCTRIGS2_TRG2MTC1                      BIT(1)              /*!< SHRTIMER_ADCTRIG2 on Master_TIMER compare 1 event */
#define SHRTIMER_ADCTRIGS2_TRG2MTC2                      BIT(2)              /*!< SHRTIMER_ADCTRIG2 on Master_TIMER compare 2 event */
#define SHRTIMER_ADCTRIGS2_TRG2MTC3                      BIT(3)              /*!< SHRTIMER_ADCTRIG2 on Master_TIMER compare 3 event */
#define SHRTIMER_ADCTRIGS2_TRG2MTPER                     BIT(4)              /*!< SHRTIMER_ADCTRIG2 on Master_TIMER period event */
#define SHRTIMER_ADCTRIGS2_TRG2EXEV0                     BIT(5)              /*!< SHRTIMER_ADCTRIG2 on external event 0 */
#define SHRTIMER_ADCTRIGS2_TRG2EXEV1                     BIT(6)              /*!< SHRTIMER_ADCTRIG2 on external event 1 */
#define SHRTIMER_ADCTRIGS2_TRG2EXEV2                     BIT(7)              /*!< SHRTIMER_ADCTRIG2 on external event 2 */
#define SHRTIMER_ADCTRIGS2_TRG2EXEV3                     BIT(8)              /*!< SHRTIMER_ADCTRIG2 on external event 3 */
#define SHRTIMER_ADCTRIGS2_TRG2EXEV4                     BIT(9)              /*!< SHRTIMER_ADCTRIG2 on external event 4 */
#define SHRTIMER_ADCTRIGS2_TRG2ST0C1                     BIT(10)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER0 compare 1 event */
#define SHRTIMER_ADCTRIGS2_TRG2ST0C2                     BIT(11)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER0 compare 2 event */
#define SHRTIMER_ADCTRIGS2_TRG2ST0C3                     BIT(12)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER0 compare 3 event */
#define SHRTIMER_ADCTRIGS2_TRG2ST0PER                    BIT(13)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER0 period event */
#define SHRTIMER_ADCTRIGS2_TRG2ST0RST                    BIT(14)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER0 reset and counter roll-over event */
#define SHRTIMER_ADCTRIGS2_TRG2ST1C1                     BIT(15)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER1 compare 1 event */
#define SHRTIMER_ADCTRIGS2_TRG2ST1C2                     BIT(16)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER1 compare 2 event */
#define SHRTIMER_ADCTRIGS2_TRG2ST1C3                     BIT(17)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER1 compare 3 event */
#define SHRTIMER_ADCTRIGS2_TRG2ST1PER                    BIT(18)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER1 period event */
#define SHRTIMER_ADCTRIGS2_TRG2ST1RST                    BIT(19)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER1 reset and counter roll-over event */
#define SHRTIMER_ADCTRIGS2_TRG2ST2C1                     BIT(20)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER2 compare 1 event */
#define SHRTIMER_ADCTRIGS2_TRG2ST2C2                     BIT(21)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER2 compare 2 event */
#define SHRTIMER_ADCTRIGS2_TRG2ST2C3                     BIT(22)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER2 compare 3 event */
#define SHRTIMER_ADCTRIGS2_TRG2ST2PER                    BIT(23)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER2 period event */
#define SHRTIMER_ADCTRIGS2_TRG2ST3C1                     BIT(24)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER3 compare 1 event */
#define SHRTIMER_ADCTRIGS2_TRG2ST3C2                     BIT(25)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER3 compare 2 event */
#define SHRTIMER_ADCTRIGS2_TRG2ST3C3                     BIT(26)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER3 compare 3 event */
#define SHRTIMER_ADCTRIGS2_TRG2ST3PER                    BIT(27)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER3 period event */
#define SHRTIMER_ADCTRIGS2_TRG2ST4C1                     BIT(28)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER4 compare 1 event */
#define SHRTIMER_ADCTRIGS2_TRG2ST4C2                     BIT(29)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER4 compare 2 event */
#define SHRTIMER_ADCTRIGS2_TRG2ST4C3                     BIT(30)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER4 compare 3 event */
#define SHRTIMER_ADCTRIGS2_TRG2ST4PER                    BIT(31)             /*!< SHRTIMER_ADCTRIG2 on Slave_TIMER4 period event */

/* SHRTIMER_ADCTRIGS3 */
#define SHRTIMER_ADCTRIGS3_TRG3MTC0                      BIT(0)              /*!< SHRTIMER_ADCTRIG3 on Master_TIMER compare 0 event */
#define SHRTIMER_ADCTRIGS3_TRG3MTC1                      BIT(1)              /*!< SHRTIMER_ADCTRIG3 on Master_TIMER compare 1 event */
#define SHRTIMER_ADCTRIGS3_TRG3MTC2                      BIT(2)              /*!< SHRTIMER_ADCTRIG3 on Master_TIMER compare 2 event */
#define SHRTIMER_ADCTRIGS3_TRG3MTC3                      BIT(3)              /*!< SHRTIMER_ADCTRIG3 on Master_TIMER compare 3 event */
#define SHRTIMER_ADCTRIGS3_TRG3MTPER                     BIT(4)              /*!< SHRTIMER_ADCTRIG3 on Master_TIMER period event */
#define SHRTIMER_ADCTRIGS3_TRG3EXEV5                     BIT(5)              /*!< SHRTIMER_ADCTRIG3 on external event 5 */
#define SHRTIMER_ADCTRIGS3_TRG3EXEV6                     BIT(6)              /*!< SHRTIMER_ADCTRIG3 on external event 6 */
#define SHRTIMER_ADCTRIGS3_TRG3EXEV7                     BIT(7)              /*!< SHRTIMER_ADCTRIG3 on external event 7 */
#define SHRTIMER_ADCTRIGS3_TRG3EXEV8                     BIT(8)              /*!< SHRTIMER_ADCTRIG3 on external event 8 */
#define SHRTIMER_ADCTRIGS3_TRG3EXEV9                     BIT(9)              /*!< SHRTIMER_ADCTRIG3 on external event 9 */
#define SHRTIMER_ADCTRIGS3_TRG3ST0C1                     BIT(10)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER0 compare 1 event */
#define SHRTIMER_ADCTRIGS3_TRG3ST0C2                     BIT(11)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER0 compare 2 event */
#define SHRTIMER_ADCTRIGS3_TRG3ST0C3                     BIT(12)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER0 compare 3 event */
#define SHRTIMER_ADCTRIGS3_TRG3ST0PER                    BIT(13)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER0 period event */
#define SHRTIMER_ADCTRIGS3_TRG3ST1C1                     BIT(14)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER1 compare 1 event */
#define SHRTIMER_ADCTRIGS3_TRG3ST1C2                     BIT(15)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER1 compare 2 event */
#define SHRTIMER_ADCTRIGS3_TRG3ST1C3                     BIT(16)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER1 compare 3 event */
#define SHRTIMER_ADCTRIGS3_TRG3ST1PER                    BIT(17)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER1 period event */
#define SHRTIMER_ADCTRIGS3_TRG3ST2C1                     BIT(18)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER2 compare 1 event */
#define SHRTIMER_ADCTRIGS3_TRG3ST2C2                     BIT(19)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER2 compare 2 event */
#define SHRTIMER_ADCTRIGS3_TRG3ST2C3                     BIT(20)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER2 compare 3 event */
#define SHRTIMER_ADCTRIGS3_TRG3ST2PER                    BIT(21)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER2 period event */
#define SHRTIMER_ADCTRIGS3_TRG3ST2RST                    BIT(22)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER2 reset and counter roll-over event */
#define SHRTIMER_ADCTRIGS3_TRG3ST3C1                     BIT(23)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER3 compare 1 event */
#define SHRTIMER_ADCTRIGS3_TRG3ST3C2                     BIT(24)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER3 compare 2 event */
#define SHRTIMER_ADCTRIGS3_TRG3ST3C3                     BIT(25)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER3 compare 3 event */
#define SHRTIMER_ADCTRIGS3_TRG3ST3PER                    BIT(26)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER3 period event */
#define SHRTIMER_ADCTRIGS3_TRG3ST3RST                    BIT(27)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER3 reset and counter roll-over event */
#define SHRTIMER_ADCTRIGS3_TRG3ST4C1                     BIT(28)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER4 compare 1 event */
#define SHRTIMER_ADCTRIGS3_TRG3ST4C2                     BIT(29)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER4 compare 2 event */
#define SHRTIMER_ADCTRIGS3_TRG3ST4C3                     BIT(30)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER4 compare 3 event */
#define SHRTIMER_ADCTRIGS3_TRG3ST4RST                    BIT(31)             /*!< SHRTIMER_ADCTRIG3 on Slave_TIMER4 reset and counter roll-over event */

/* SHRTIMER_DLLCCTL */
#define SHRTIMER_DLLCCTL_CLBSTRT                         BIT(0)              /*!< DLL calibration start once */
#define SHRTIMER_DLLCCTL_CLBPEREN                        BIT(1)              /*!< DLL periodic calibration enable */
#define SHRTIMER_DLLCCTL_CLBPER                          BITS(2,3)           /*!< DLL calibration period */

/* SHRTIMER_FLTINCFG0 */
#define SHRTIMER_FLTINCFG0_FLT0INEN                      BIT(0)              /*!< fault 0 input enable */
#define SHRTIMER_FLTINCFG0_FLT0INP                       BIT(1)              /*!< fault 0 input polarity */
#define SHRTIMER_FLTINCFG0_FLT0INSRC                     BIT(2)              /*!< fault 0 input source */
#define SHRTIMER_FLTINCFG0_FLT0INFC                      BITS(3,6)           /*!< fault 0 input filter control */
#define SHRTIMER_FLTINCFG0_FLT0INPROT                    BIT(7)              /*!< protect fault 0 input configuration */
#define SHRTIMER_FLTINCFG0_FLT1INEN                      BIT(8)              /*!< fault 1 input enable */
#define SHRTIMER_FLTINCFG0_FLT1INP                       BIT(9)              /*!< fault 1 input polarity */
#define SHRTIMER_FLTINCFG0_FLT1INSRC                     BIT(10)             /*!< fault 1 input source */
#define SHRTIMER_FLTINCFG0_FLT1INFC                      BITS(11,14)         /*!< fault 1 input filter control */
#define SHRTIMER_FLTINCFG0_FLT1INPROT                    BIT(15)             /*!< protect fault 1 input configuration */
#define SHRTIMER_FLTINCFG0_FLT2INEN                      BIT(16)             /*!< fault 2 input enable */
#define SHRTIMER_FLTINCFG0_FLT2INP                       BIT(17)             /*!< fault 2 input polarity */
#define SHRTIMER_FLTINCFG0_FLT2INSRC                     BIT(18)             /*!< fault 2 input source */
#define SHRTIMER_FLTINCFG0_FLT2INFC                      BITS(19,22)         /*!< fault 2 input filter control */
#define SHRTIMER_FLTINCFG0_FLT2INPROT                    BIT(23)             /*!< protect fault 2 input configuration */
#define SHRTIMER_FLTINCFG0_FLT3INEN                      BIT(24)             /*!< fault 3 input enable */
#define SHRTIMER_FLTINCFG0_FLT3INP                       BIT(25)             /*!< fault 3 input polarity */
#define SHRTIMER_FLTINCFG0_FLT3INSRC                     BIT(26)             /*!< fault 3 input source */
#define SHRTIMER_FLTINCFG0_FLT3INFC                      BITS(27,30)         /*!< fault 3 input filter control */
#define SHRTIMER_FLTINCFG0_FLT3INPROT                    BIT(31)             /*!< protect fault 3 input configuration */

/* SHRTIMER_FLTINCFG1 */
#define SHRTIMER_FLTINCFG1_FLT4INEN                      BIT(0)              /*!< fault 4 input enable */
#define SHRTIMER_FLTINCFG1_FLT4INP                       BIT(1)              /*!< fault 4 input polarity */
#define SHRTIMER_FLTINCFG1_FLT4INSRC                     BIT(2)              /*!< fault 4 input source */
#define SHRTIMER_FLTINCFG1_FLT4INFC                      BITS(3,6)           /*!< fault 4 input filter control */
#define SHRTIMER_FLTINCFG1_FLT4INPROT                    BIT(7)              /*!< protect fault 4 input configuration */
#define SHRTIMER_FLTINCFG1_FLTFDIV                       BITS(24,25)         /*!< fault input digital filter clock division */

/* SHRTIMER_DMAUPMTR */
#define SHRTIMER_DMAUPMTR_MTCTL0                         BIT(0)              /*!< SHRTIMER_MTCTL0 update by DMA mode */
#define SHRTIMER_DMAUPMTR_MTINTC                         BIT(1)              /*!< SHRTIMER_MTINTC update by DMA mode */
#define SHRTIMER_DMAUPMTR_MTDMAINTEN                     BIT(2)              /*!< SHRTIMER_MTDMAINTEN update by DMA mode */
#define SHRTIMER_DMAUPMTR_MTCNT                          BIT(3)              /*!< SHRTIMER_MTCNT update by DMA mode */
#define SHRTIMER_DMAUPMTR_MTCAR                          BIT(4)              /*!< SHRTIMER_MTCAR update by DMA mode */
#define SHRTIMER_DMAUPMTR_MTCREP                         BIT(5)              /*!< SHRTIMER_MTCREP update by DMA mode */
#define SHRTIMER_DMAUPMTR_MTCMP0V                        BIT(6)              /*!< SHRTIMER_MTCMP0V update by DMA mode */
#define SHRTIMER_DMAUPMTR_MTCMP1V                        BIT(7)              /*!< SHRTIMER_MTCMP1V update by DMA mode */
#define SHRTIMER_DMAUPMTR_MTCMP2V                        BIT(8)              /*!< SHRTIMER_MTCMP2V update by DMA mode */
#define SHRTIMER_DMAUPMTR_MTCMP3V                        BIT(9)              /*!< SHRTIMER_MTCMP3V update by DMA mode */
#define SHRTIMER_DMAUPMTR_MTACTL                         BIT(31)             /*!< SHRTIMER_MTACTL update by DMA mode */

/* SHRTIMER_DMAUPSTxR */
#define SHRTIMER_DMAUPSTXR_STXCTL0                       BIT(0)              /*!< SHRTIMER_STxCTL0 update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXINTC                       BIT(1)              /*!< SHRTIMER_STxINTC update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXDMAINTEN                   BIT(2)              /*!< SHRTIMER_STxDMAINTEN update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXCNT                        BIT(3)              /*!< SHRTIMER_STxCNT update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXCAR                        BIT(4)              /*!< SHRTIMER_STxCAR update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXCREP                       BIT(5)              /*!< SHRTIMER_STxCREP update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXCMP0V                      BIT(6)              /*!< SHRTIMER_STxCMP0V update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXCMP1V                      BIT(7)              /*!< SHRTIMER_STxCMP1V update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXCMP2V                      BIT(8)              /*!< SHRTIMER_STxCMP2V update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXCMP3V                      BIT(9)              /*!< SHRTIMER_STxCMP3V update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXDTCTL                      BIT(10)             /*!< SHRTIMER_STxDTCTL update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXCH0SET                     BIT(11)             /*!< SHRTIMER_STxCH0SET update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXCH0RST                     BIT(12)             /*!< SHRTIMER_STxCH0RST update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXCH1SET                     BIT(13)             /*!< SHRTIMER_STxCH1SET update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXCH1RST                     BIT(14)             /*!< SHRTIMER_STxCH1RST update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXEXEVFCFG0                  BIT(15)             /*!< SHRTIMER_STxEXEVFCFG0 update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXEXEVFCFG1                  BIT(16)             /*!< SHRTIMER_STxEXEVFCFG1 update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXCNTRST                     BIT(17)             /*!< SHRTIMER_STxCNTRST update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXCSCTL                      BIT(18)             /*!< SHRTIMER_STxCSCTL update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXCHOCTL                     BIT(19)             /*!< SHRTIMER_STxCHOCTL update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXFLTCTL                     BIT(20)             /*!< SHRTIMER_STxFLTCTL update by DMA mode */
#define SHRTIMER_DMAUPSTXR_STXACTL                       BIT(31)             /*!< SHRTIMER_STxACTL update by DMA mode */

/* SHRTIMER_DMATB */
#define SHRTIMER_DMATB_DMATB                             BITS(0,31)          /*!< DMA transfer buffer */

/* constants definitions */
/* SHRTIMER time base parameters struct definitions */
typedef struct
{
    uint32_t period;                            /*!< period value, min value: 3*tSHRTIMER_CK clock, max value: 0xFFFF �C (1*tSHRTIMER_CK) */
    uint32_t repetitioncounter;                 /*!< the counter repetition value, 0x00~0xFF */
    uint32_t prescaler;                         /*!< prescaler value, refer to: counter clock division */
    uint32_t counter_mode;                      /*!< counter operating mode, refer to: counter operating mode */
}shrtimer_baseinit_parameter_struct;

/* waveform mode initialization parameters struct definitions */
typedef struct {
    uint32_t half_mode;                         /*!< specifies whether or not half mode is enabled, refer to: half mode enabling status */
    uint32_t start_sync;                        /*!< specifies whether or not timer is started by a rising edge on the synchronization input, refer to: synchronous input start timer */
    uint32_t reset_sync;                        /*!< specifies whether or not timer is reset by a rising edge on the synchronization input, refer to: synchronous input reset timer */
    uint32_t dac_trigger;                       /*!< indicates whether or not the a DAC synchronization event is generated, refer to: trigger source to DAC */
    uint32_t shadow;                            /*!< specifies whether or not the shadow registers are enabled, refer to: shadow registers enabling status */
    uint32_t update_selection;                  /*!< the update occurs with respect to DMA mode or STxUPINy (Slave_TIMERx only), refer to: update event selection */
    uint32_t cnt_bunch;                         /*!< the timer behaves during a bunch mode operation, refer to: timer behaves during a bunch mode operation */
    uint32_t repetition_update;                 /*!< specifies whether or not registers update is triggered by the repetition event, refer to: update event generated by repetition event */
}shrtimer_timerinit_parameter_struct;

/* Slave_TIMER general behavior configuration struct definitions */
typedef struct {
    uint32_t balanced_mode;                     /*!< specifies whether or not the balanced mode is enabled, refer to: set balanced mode */
    uint32_t fault_enable;                      /*!< specifies whether or not the fault channels are enabled for the Slave_TIMER, refer to: faut channel enabled for a Slave_TIMER*/
    uint32_t fault_protect ;                    /*!< specifies whether the write protection function is enable or not, refer to: protect fault enable */
    uint32_t deadtime_enable;                   /*!< specifies whether or not dead time insertion is enabled for the timer, refer to: dead time enable */
    uint32_t delayed_idle;                      /*!< the delayed IDLE mode, refer to: set delayed IDLE state mode */
    uint32_t update_source;                     /*!< the source triggering the Slave_TIMER registers update, refer to: update is done synchronously with any other Slave_TIMER or Master_TIMER update */
    uint32_t cnt_reset;                         /*!< the source triggering the Slave_TIMER counter reset, refer to: Slave_TIMER counter reset */
    uint32_t reset_update;                      /*!< specifies whether or not registers update is triggered when the timer counter is reset, refer to: update event generated by reset event */
}shrtimer_timercfg_parameter_struct;

/* compare unit configuration struct definitions */
typedef struct {
    uint32_t compare_value;                     /*!< compare value, min value: 3*tSHRTIMER_CK clock, max value: 0xFFFF �C (1*tSHRTIMER_CK) */
    uint32_t delayed_mode;                      /*!< defining whether the compare register is behaving in regular mode or in delayed mode, refer to: compare 3 or 1 delayed mode */
    uint32_t timeout_value;                     /*!< compare value for compare 0 or 2 when compare 3 or 1 is delayed mode with time out is selected , timeout_value + compare_value must be less than 0xFFFF */
}shrtimer_comparecfg_parameter_struct;

/* external event filtering for Slave_TIMER configuration struct definitions */
typedef struct {
    uint32_t filter_mode;                       /*!< the external event filter mode for Slave_TIMER, refer to: external event filter mode */
    uint32_t memorized;                         /*!< specifies whether or not the signal is memorized, refer to: external event memorized enable */
}shrtimer_exevfilter_parameter_struct;

/* dead time configuration struct definitions */
typedef struct {
    uint32_t prescaler;                         /*!< dead time generator clock division, refer to: dead time prescaler */
    uint32_t rising_value;                      /*!< rising edge dead-time value, 0x0000~0xFFFF */
    uint32_t rising_sign;                       /*!< the sign of rising edge dead-time value, refer to: dead time rising sign */
    uint32_t rising_protect;                    /*!< dead time rising edge protection for value and sign, refer to: dead time rising edge protection for value and sign */
    uint32_t risingsign_protect;                /*!< dead time rising edge protection for sign, refer to: dead time rising edge protection only for sign */
    uint32_t falling_value;                     /*!< falling edge dead-time value, 0x0000~0xFFFF */
    uint32_t falling_sign;                      /*!< the sign of falling edge dead-time value, refer to: dead time falling sign */
    uint32_t falling_protect;                   /*!< dead time falling edge protection for value and sign, refer to: dead time falling edge protection for value and sign */
    uint32_t fallingsign_protect;               /*!< dead time falling edge protection for sign, refer to: dead time falling edge protection only for sign */
}shrtimer_deadtimecfg_parameter_struct;

/* carrier signal configuration struct definitions */
typedef struct {
    uint32_t period;                            /*!< carrier signal period: tCSPRD, 0x0~0xF. tCSPRD = (period + 1) * 16 * tSHRTIMER_CK */
    uint32_t duty_cycle;                        /*!< carrier signal duty cycle, 0x0~0x7, duty cycle = duty_cycle/8 */
    uint32_t first_pulse;                       /*!< first carrier-signal pulse width: tCSFSTPW, 0x0~0xF. tCSFSTPW = (first_pulse+1) * 16 * tSHRTIMER_CK */
}shrtimer_carriersignalcfg_parameter_struct;

/* synchronization configuration struct definitions */
typedef struct {
    uint32_t input_source;                      /*!< the external synchronization input source, refer to: the synchronization input source */
    uint32_t output_source;                     /*!< the source and event to be sent on the external synchronization outputs, refer to: the synchronization output source */
    uint32_t output_polarity;                   /*!< the polarity and length of the pulse to be sent on the external synchronization outputs, refer to: the pulse on the synchronization output pad SHRTIMER_SCOUT */
}shrtimer_synccfg_parameter_struct;

/* bunch mode configuration struct definitions */
typedef struct {
    uint32_t mode;                              /*!< the bunch mode operating mode, refer to: continuous mode in bunch mode */
    uint32_t clock_source;                      /*!< specifies the burst mode clock source, refer to: bunch mode clock source*/
    uint32_t prescaler;                         /*!< the bunch mode prescaler, refer to: bunch mode clock division */
    uint32_t shadow;                            /*!< specifies whether or not preload is enabled for SHRTIMER_BMCMPV and SHRTIMER_BMCAR registers, refer to: bunch mode shadow enable */
    uint32_t trigger;                           /*!< the event triggering the bunch operation, refer to: the event triggers bunch mode operation */
    uint32_t idle_duration;                     /*!< the duration of the IDLE, 0x0000~0xFFFF  */
    uint32_t period;                            /*!< the bunch mode period which is the sum of the IDLE and RUN duration, 0x0001~0xFFFF  */
}shrtimer_bunchmode_parameter_struct;

/* external event configuration struct definitions */
typedef struct {
    uint32_t source;                            /*!< the source of the external event,refer to: external event source  */
    uint32_t polarity;                          /*!< the active level of external event 0 when EXEVyEG[1:0] = 2��b00, refer to: external event polarity */
    uint32_t edge ;                             /*!< the sensitivity of the external event, external event edge sensitivity */
    uint32_t digital_filter;                    /*!< external event filter control, 0x0~0xF */
}shrtimer_exeventcfg_parameter_struct;

/* fault input configuration struct definitions */
typedef struct {
    uint32_t source;                            /*!< the source of the fault input, refer to: fault input source */
    uint32_t polarity;                          /*!< the polarity of the fault input, refer to: fault input polarity */
    uint32_t filter;                            /*!< fault input filter control, 0x0~0xF */
    uint32_t control;                           /*!< fault input enable or disable, refer to: enable or disable fault */
    uint32_t protect ;                          /*!< protect fault input configuration, refer to: protect fault input configuration */
}shrtimer_faultcfg_parameter_struct;

/* ADC trigger configuration struct definitions */
typedef struct {
    uint32_t update_source;                     /*!< the source triggering the update of the SHRTIMER_ADCTRIGSy register, refer to: SHRTIMER_ADCTRIG update source */
    uint32_t trigger;                           /*!< the event triggering the ADC conversion, refer to:  ADC trigger event */
}shrtimer_adctrigcfg_parameter_struct;

/* channel output configuration struct definitions */
typedef struct {
    uint32_t polarity;                          /*!< configure channel output polarity, refer to: channel output polarity */
    uint32_t set_request;                       /*!< configure the event generates channel ��set request��, refer to channel set request */
    uint32_t reset_request;                     /*!< configure the event generates channel ��reset request��, refer to: channel reset request */
    uint32_t idle_bunch;                        /*!< specifies whether channel output can be IDLE state in bunch mode, refer to: channel IDLE state enable in bunch mode */
    uint32_t idle_state;                        /*!< specifies channel output idle state, refer to channel output idle state */
    uint32_t fault_state;                       /*!< specifies the output level when in FAULT state, refer to: channel output in fault state */
    uint32_t carrier_mode;                      /*!< specifies whether or not the carrier-signal mode is enabled, refer to: channel carrier-signal mode enable */
    uint32_t deadtime_bunch;                    /*!< specifies whether or not deadtime is inserted before output entering the IDLE state in bunch mode, refer to: channel dead-time insert in bunch mode */
}shrtimer_channel_outputcfg_parameter_struct;

/* SHRTIMER timer to configure */
#define SHRTIMER_SLAVE_TIMER0                            ((uint32_t)0x00000000U)                                 /*!< index associated to Slave_TIMER0 */
#define SHRTIMER_SLAVE_TIMER1                            ((uint32_t)0x00000001U)                                 /*!< index associated to Slave_TIMER1 */
#define SHRTIMER_SLAVE_TIMER2                            ((uint32_t)0x00000002U)                                 /*!< index associated to Slave_TIMER2 */
#define SHRTIMER_SLAVE_TIMER3                            ((uint32_t)0x00000003U)                                 /*!< index associated to Slave_TIMER3 */
#define SHRTIMER_SLAVE_TIMER4                            ((uint32_t)0x00000004U)                                 /*!< index associated to Slave_TIMER4 */
#define SHRTIMER_MASTER_TIMER                            ((uint32_t)0x00000005U)                                 /*!< index associated to Master_TIMER */
#define SHRTIMER_COMMONINDEX                             ((uint32_t)0x00000006U)                                 /*!< index associated to common registers */

/* compare unit to configure */
#define SHRTIMER_COMPARE0                                ((uint32_t)0x00000000U)                                 /*!< compare unit 0 */
#define SHRTIMER_COMPARE1                                ((uint32_t)0x00000001U)                                 /*!< compare unit 1 */
#define SHRTIMER_COMPARE2                                ((uint32_t)0x00000002U)                                 /*!< compare unit 2 */
#define SHRTIMER_COMPARE3                                ((uint32_t)0x00000003U)                                 /*!< compare unit 3 */
#define SHRTIMER_COMPARE0_COMPOSITE                      ((uint32_t)0x00000005U)                                 /*!< compare 0 composite unit */

/* capture unit to configure */
#define SHRTIMER_CAPTURE_0                               ((uint32_t)0x00000000U)                                 /*!< capture unit 0 */
#define SHRTIMER_CAPTURE_1                               ((uint32_t)0x00000001U)                                 /*!< capture unit 1 */

/* external event to configure */
#define SHRTIMER_EXEVENT_NONE                            ((uint32_t)0x00000000U)                                 /*!< undefined event channel */
#define SHRTIMER_EXEVENT_0                               ((uint32_t)0x00000001U)                                 /*!< extern event 0 */
#define SHRTIMER_EXEVENT_1                               ((uint32_t)0x00000002U)                                 /*!< extern event 1 */
#define SHRTIMER_EXEVENT_2                               ((uint32_t)0x00000004U)                                 /*!< extern event 2 */
#define SHRTIMER_EXEVENT_3                               ((uint32_t)0x00000008U)                                 /*!< extern event 3 */
#define SHRTIMER_EXEVENT_4                               ((uint32_t)0x00000010U)                                 /*!< extern event 4 */
#define SHRTIMER_EXEVENT_5                               ((uint32_t)0x00000020U)                                 /*!< extern event 5 */
#define SHRTIMER_EXEVENT_6                               ((uint32_t)0x00000040U)                                 /*!< extern event 6 */
#define SHRTIMER_EXEVENT_7                               ((uint32_t)0x00000080U)                                 /*!< extern event 7  */
#define SHRTIMER_EXEVENT_8                               ((uint32_t)0x00000100U)                                 /*!< extern event 8 */
#define SHRTIMER_EXEVENT_9                               ((uint32_t)0x00000200U)                                 /*!< extern event 9 */

/* fault to configure */
#define SHRTIMER_FAULT_0                                 ((uint32_t)0x00000000U)                                 /*!< fault 0 */
#define SHRTIMER_FAULT_1                                 ((uint32_t)0x00000001U)                                 /*!< fault 1 */
#define SHRTIMER_FAULT_2                                 ((uint32_t)0x00000002U)                                 /*!< fault 2 */
#define SHRTIMER_FAULT_3                                 ((uint32_t)0x00000004U)                                 /*!< fault 3 */
#define SHRTIMER_FAULT_4                                 ((uint32_t)0x00000008U)                                 /*!< fault 4 */

/* SHRTIMER_ADCTRIG to configure */
#define SHRTIMER_ADCTRIG_0                               ((uint32_t)0x00000000U)                                 /*!< SHRTIMER_ADCTRIG0 */
#define SHRTIMER_ADCTRIG_1                               ((uint32_t)0x00000001U)                                 /*!< SHRTIMER_ADCTRIG1 */
#define SHRTIMER_ADCTRIG_2                               ((uint32_t)0x00000002U)                                 /*!< SHRTIMER_ADCTRIG2 */
#define SHRTIMER_ADCTRIG_3                               ((uint32_t)0x00000003U)                                 /*!< SHRTIMER_ADCTRIG3 */

/* channel to configure */
#define SHRTIMER_ST0_CH0                                 ((uint32_t)0x00000001U)                                 /*!< Slave_TIMER0 channel 0 */
#define SHRTIMER_ST0_CH1                                 ((uint32_t)0x00000002U)                                 /*!< Slave_TIMER0 channel 1 */
#define SHRTIMER_ST1_CH0                                 ((uint32_t)0x00000004U)                                 /*!< Slave_TIMER1 channel 0 */
#define SHRTIMER_ST1_CH1                                 ((uint32_t)0x00000008U)                                 /*!< Slave_TIMER1 channel 1 */
#define SHRTIMER_ST2_CH0                                 ((uint32_t)0x00000010U)                                 /*!< Slave_TIMER2 channel 0 */
#define SHRTIMER_ST2_CH1                                 ((uint32_t)0x00000020U)                                 /*!< Slave_TIMER2 channel 1 */
#define SHRTIMER_ST3_CH0                                 ((uint32_t)0x00000040U)                                 /*!< Slave_TIMER3 channel 0 */
#define SHRTIMER_ST3_CH1                                 ((uint32_t)0x00000080U)                                 /*!< Slave_TIMER3 channel 1 */
#define SHRTIMER_ST4_CH0                                 ((uint32_t)0x00000100U)                                 /*!< Slave_TIMER4 channel 0 */
#define SHRTIMER_ST4_CH1                                 ((uint32_t)0x00000200U)                                 /*!< Slave_TIMER4 channel 1 */

/* the counter to enable/disable */
#define SHRTIMER_MT_COUNTER                              (SHRTIMER_MTCTL0_MTCEN)                                  /*!< the counter of Master_TIMER */
#define SHRTIMER_ST0_COUNTER                             (SHRTIMER_MTCTL0_ST0CEN)                                 /*!< the counter of Slave_TIMER0 */
#define SHRTIMER_ST1_COUNTER                             (SHRTIMER_MTCTL0_ST1CEN)                                 /*!< the counter of Slave_TIMER1 */
#define SHRTIMER_ST2_COUNTER                             (SHRTIMER_MTCTL0_ST2CEN)                                 /*!< the counter of Slave_TIMER2 */
#define SHRTIMER_ST3_COUNTER                             (SHRTIMER_MTCTL0_ST3CEN)                                 /*!< the counter of Slave_TIMER3 */
#define SHRTIMER_ST4_COUNTER                             (SHRTIMER_MTCTL0_ST4CEN)                                 /*!< the counter of Slave_TIMER4 */

/* counter clock division */
#define SHRTIMER_PRESCALER_MUL64                         ((uint32_t)0x00000008U)                                 /* fSHRTIMER_PSSCK = fHPTIM_HPCK = 64 *fSHRTIMER_CK */
#define SHRTIMER_PRESCALER_MUL32                         ((uint32_t)0x00000000U)                                 /* fSHRTIMER_PSSCK = fHPTIM_HPCK/2 = 32 *fSHRTIMER_CK */
#define SHRTIMER_PRESCALER_MUL16                         ((uint32_t)0x00000001U)                                 /* fSHRTIMER_PSSCK = fHPTIM_HPCK/4 = 16 *fSHRTIMER_CK */
#define SHRTIMER_PRESCALER_MUL8                          ((uint32_t)0x00000002U)                                 /* fSHRTIMER_PSSCK = fHPTIM_HPCK/8 = 8 *fSHRTIMER_CK */
#define SHRTIMER_PRESCALER_MUL4                          ((uint32_t)0x00000003U)                                 /* fSHRTIMER_PSSCK = fHPTIM_HPCK/16 = 4 *fSHRTIMER_CK */
#define SHRTIMER_PRESCALER_MUL2                          ((uint32_t)0x00000004U)                                 /* fSHRTIMER_PSSCK = fHPTIM_HPCK/32 = 2*fSHRTIMER_CK */
#define SHRTIMER_PRESCALER_DIV1                          ((uint32_t)0x00000005U)                                 /* fSHRTIMER_PSSCK = fHPTIM_HPCK/64 = fSHRTIMER_CK */
#define SHRTIMER_PRESCALER_DIV2                          ((uint32_t)0x00000006U)                                 /* fSHRTIMER_PSSCK = fHPTIM_HPCK/128 = fSHRTIMER_CK/2 */
#define SHRTIMER_PRESCALER_DIV4                          ((uint32_t)0x00000007U)                                 /* fSHRTIMER_PSSCK = fHPTIM_HPCK/256 = fSHRTIMER_CK/4 */

/* counter operating mode */
#define SHRTIMER_COUNTER_MODE_CONTINOUS                  ((uint32_t)0x00000008U)                                 /*!< the timer operates in continuous (free-running) mode */
#define SHRTIMER_COUNTER_MODE_SINGLEPULSE                ((uint32_t)0x00000000U)                                 /*!< single pulse mode: the counter can be reset only if it stops (period elapsed) */
#define SHRTIMER_COUNTER_MODE_SINGLEPULSE_RETRIGGERABLE  ((uint32_t)0x00000010U)                                 /*!< single pulse mode: the counter can be reset at any time (running or stopped) */

/* half mode enabling status */
#define SHRTIMER_HALFMODE_DISABLED                       ((uint32_t)0x00000000U)                                 /*!< half mode disable */
#define SHRTIMER_HALFMODE_ENABLED                        ((uint32_t)0x00000020U)                                 /*!< half mode enable */

/* synchronous input start timer */
#define SHRTIMER_SYNISTART_DISABLED                      ((uint32_t)0x00000000U)                                 /*!< the synchronous input signal cannot start the counter */
#define SHRTIMER_SYNISTART_ENABLED                       ((uint32_t)0x00000800U)                                 /*!< the synchronous input signal can start the counter */

/* synchronous input reset timer */
#define SHRTIMER_SYNCRESET_DISABLED                      ((uint32_t)0x00000000U)                                 /*!< the synchronous input signal cannot reset the counter */
#define SHRTIMER_SYNCRESET_ENABLED                       ((uint32_t)0x00000400U)                                 /*!< the synchronous input signal can reset the counter */

/* trigger source to DAC */
#define SHRTIMER_DAC_TRIGGER_NONE                        ((uint32_t)0x00000000U)                                 /*!< no DAC trigger event generated */
#define SHRTIMER_DAC_TRIGGER_DACTRIG0                    ((uint32_t)0x02000000U)                                 /*!< DAC trigger event generated on SHRTIMER_DACTRIG0 */
#define SHRTIMER_DAC_TRIGGER_DACTRIG1                    ((uint32_t)0x04000000U)                                 /*!< DAC trigger event generated on SHRTIMER_DACTRIG1 */
#define SHRTIMER_DAC_TRIGGER_DACTRIG2                    ((uint32_t)0x06000000U)                                 /*!< DAC trigger event generated on SHRTIMER_DACTRIG2 */

/* shadow registers enabling status */
#define SHRTIMER_SHADOW_DISABLED                         ((uint32_t)0x00000000U)                                 /*!< the shadow registers are disabled: the write access is directly done into the active registers */
#define SHRTIMER_SHADOW_ENABLED                          ((uint32_t)0x08000000U)                                 /*!< the shadow registers are enabled: the write access is done into the shadow registers */

/* update event selection */
#define SHRTIMER_MT_ST_UPDATE_SELECTION_INDEPENDENT      ((uint32_t)0x00000000U)                                 /*!< update event generated independently from DMA mode */
#define SHRTIMER_MT_ST_UPDATE_SELECTION_DMAMODE          ((uint32_t)0x10000000U)                                 /*!< update event generated when the DMA transfer completed in DMA mode */
#define SHRTIMER_MT_ST_UPDATE_SELECTION_DMAMODE_UPDATE   ((uint32_t)0x20000000U)                                 /*!< update event generated on the update event following the DMA transfer completed in DMA mode */
#define SHRTIMER_ST_UPDATE_SELECTION_STXUPIN2            ((uint32_t)0x50000000U)                                 /*!< update event generated on the rising edge of STxUPIN2 */
#define SHRTIMER_ST_UPDATE_SELECTION_STXUPIN2_UPDATE     ((uint32_t)0x80000000U)                                 /*!< update event generated on the update event following the rising edge of STxUPIN2 */

/* timer behaves during a bunch mode operation */
#define SHRTIMER_TIMERBUNCHNMODE_MAINTAINCLOCK           ((uint32_t)0x00000000U)                                 /*!< counter clock(SHRTIMER_PSCCK) is maintained and the counter operates normally */
#define SHRTIMER_TIMERBUNCHMODE_RESETCOUNTER             ((uint32_t)0x00010000U)                                 /*!< counter clock(SHRTIMER_PSCCK) is stopped and the counter is reset */

/* update event generated by repetition event */
#define SHRTIMER_UPDATEONREPETITION_DISABLED             ((uint32_t)0x00000000U)                                 /*!< update event generated by repetition event disable */
#define SHRTIMER_UPDATEONREPETITION_ENABLED              ((uint32_t)0x20000000U)                                 /*!< update event generated by repetition event enable */

/* set balanced mode */
#define SHRTIMER_STXBALANCEDMODE_DISABLED                ((uint32_t)0x00000000U)                                 /*!< balanced mode disabled */
#define SHRTIMER_STXBALANCEDMODE_ENABLED                 ((uint32_t)0x00000040U)                                 /*!< balanced mode enabled */

/* faut channel enabled for a Slave_TIMER */
#define SHRTIMER_STXFAULTENABLE_NONE                     ((uint32_t)0x00000000U)                                 /*!< no fault enabled */
#define SHRTIMER_STXFAULTENABLE_FAULT0                   (SHRTIMER_STXFLTCTL_FLT0EN)                              /*!< fault 0 enabled */
#define SHRTIMER_STXFAULTENABLE_FAULT1                   (SHRTIMER_STXFLTCTL_FLT1EN)                              /*!< fault 1 enabled */
#define SHRTIMER_STXFAULTENABLE_FAULT2                   (SHRTIMER_STXFLTCTL_FLT2EN)                              /*!< fault 2 enabled */
#define SHRTIMER_STXFAULTENABLE_FAULT3                   (SHRTIMER_STXFLTCTL_FLT3EN)                              /*!< fault 3 enabled */
#define SHRTIMER_STXFAULTENABLE_FAULT4                   (SHRTIMER_STXFLTCTL_FLT4EN)                              /*!< fault 4 enabled */

/* protect fault enable */
#define SHRTIMER_STXFAULT_PROTECT_READWRITE              ((uint32_t)0x00000000U)                                 /*!< protect disable. FLTyEN (y=0..4) is writable */
#define SHRTIMER_STXFAULT_PROTECT_READONLY               (SHRTIMER_STXFLTCTL_FLTENPROT)                           /*!< protect enable. FLTyEN (y=0..4) is read-only */

/* dead time enable */
#define SHRTIMER_STXDEADTIME_DISABLED                    ((uint32_t)0x00000000U)                                 /*!< channel 0 and channel 1 outputs are independent. */
#define SHRTIMER_STXDEADTIME_ENABLED                     (SHRTIMER_STXCHOCTL_DTEN)                                /*!< channel 0 and channel 1 outputs are complementary and dead-time is inserted between channel 0 and channel 1 outputs */

/* set delayed IDLE state mode */
#define SHRTIMER_STXDELAYED_IDLE_DISABLED                ((uint32_t)0x00000000U)                                 /*!< no action */
#define SHRTIMER_STXDELAYED_IDLE_CH0_EEV57               (SHRTIMER_STXCHOCTL_DLYISMEN)                            /*!< channel 0 output delayed IDLE on external event 5 or 7 */
#define SHRTIMER_STXDELAYED_IDLE_CH1_EEV57               (((uint32_t)0x00000400U) | SHRTIMER_STXCHOCTL_DLYISMEN)  /*!< channel 1 output delayed IDLE on external event 5 or 7 */
#define SHRTIMER_STXDELAYED_IDLE_BOTH_EEV57              (((uint32_t)0x00000800U) | SHRTIMER_STXCHOCTL_DLYISMEN)  /*!< channel 0 and channel 1 output delayed IDLE on external event 5 or 7 */
#define SHRTIMER_STXDELAYED_IDLE_BALANCED_EEV57          (((uint32_t)0x00000C00U) | SHRTIMER_STXCHOCTL_DLYISMEN)  /*!< balanced IDLE on external event 5 or 7 */
#define SHRTIMER_STXDELAYED_IDLE_CH0_DEEV68              (((uint32_t)0x00001000U) | SHRTIMER_STXCHOCTL_DLYISMEN)  /*!< channel 0 output delayed IDLE on external event 6 or 8 */
#define SHRTIMER_STXDELAYED_IDLE_CH1_DEEV68              (((uint32_t)0x00001400U) | SHRTIMER_STXCHOCTL_DLYISMEN)  /*!< channel 1 output delayed IDLE on external event 6 or 8 */
#define SHRTIMER_STXDELAYED_IDLE_BOTH_EEV68              (((uint32_t)0x00001800U) | SHRTIMER_STXCHOCTL_DLYISMEN)  /*!< channel 0 and channel 1 output delayed IDLE on external event 6 or 8 */
#define SHRTIMER_STXDELAYED_IDLE_BALANCED_EEV68          (((uint32_t)0x00001C00U) | SHRTIMER_STXCHOCTL_DLYISMEN)  /*!< balanced IDLE on external event 6 or 8 */

/* update is done synchronously with any other Slave_TIMER or Master_TIMER update */
#define SHRTIMER_STXUPDATETRIGGER_NONE                   ((uint32_t)0x00000000U)                                 /*!< register update is disabled */
#define SHRTIMER_STXUPDATETRIGGER_MASTER                 (SHRTIMER_STXCTL0_UPBMT)                                 /*!< update by Master_TIMER update event */
#define SHRTIMER_STXUPDATETRIGGER_ST0                    (SHRTIMER_STXCTL0_UPBST0)                                /*!< update by Slave_TIMER0 update event */
#define SHRTIMER_STXUPDATETRIGGER_ST1                    (SHRTIMER_STXCTL0_UPBST1)                                /*!< update by Slave_TIMER1 update event */
#define SHRTIMER_STXUPDATETRIGGER_ST2                    (SHRTIMER_STXCTL0_UPBST2)                                /*!< update by Slave_TIMER2 update event */
#define SHRTIMER_STXUPDATETRIGGER_ST3                    (SHRTIMER_STXCTL0_UPBST3)                                /*!< update by Slave_TIMER3 update event */
#define SHRTIMER_STXUPDATETRIGGER_ST4                    (SHRTIMER_STXCTL0_UPBST4)                                /*!< update by Slave_TIMER4 update event */

/* Slave_TIMER counter reset */
#define SHRTIMER_STXCNT_RESET_NONE                       ((uint32_t)0x00000000U)                                 /*!< no counter reset trigger */
#define SHRTIMER_STXCNT_RESET_UPDATE                     (SHRTIMER_STXCNTRST_UPRST)                               /*!< the Slave_TIMER counter is reset upon update event */
#define SHRTIMER_STXCNT_RESET_CMP1                       (SHRTIMER_STXCNTRST_CMP1RST)                             /*!< the Slave_TIMER counter is reset upon Slave_TIMER compare 1 event */
#define SHRTIMER_STXCNT_RESET_CMP3                       (SHRTIMER_STXCNTRST_CMP3RST)                             /*!< the Slave_TIMER counter is reset upon Slave_TIMER compare 3 event */
#define SHRTIMER_STXCNT_RESET_MASTER_PER                 (SHRTIMER_STXCNTRST_MTPERRST)                            /*!< the Slave_TIMER counter is reset upon Master_TIMER period event */
#define SHRTIMER_STXCNT_RESET_MASTER_CMP0                (SHRTIMER_STXCNTRST_MTCMP0RST)                           /*!< the Slave_TIMER counter is reset upon Master_TIMER compare 0 event */
#define SHRTIMER_STXCNT_RESET_MASTER_CMP1                (SHRTIMER_STXCNTRST_MTCMP1RST)                           /*!< the Slave_TIMER counter is reset upon Master_TIMER compare 1 event */
#define SHRTIMER_STXCNT_RESET_MASTER_CMP2                (SHRTIMER_STXCNTRST_MTCMP2RST)                           /*!< the Slave_TIMER counter is reset upon Master_TIMER compare 2 event */
#define SHRTIMER_STXCNT_RESET_MASTER_CMP3                (SHRTIMER_STXCNTRST_MTCMP3RST)                           /*!< the Slave_TIMER counter is reset upon Master_TIMER compare 3 event */
#define SHRTIMER_STXCNT_RESET_EEV_0                      (SHRTIMER_STXCNTRST_EXEV0RST)                            /*!< the Slave_TIMER counter is reset upon external event 0 */
#define SHRTIMER_STXCNT_RESET_EEV_1                      (SHRTIMER_STXCNTRST_EXEV1RST)                            /*!< the Slave_TIMER counter is reset upon external event 1 */
#define SHRTIMER_STXCNT_RESET_EEV_2                      (SHRTIMER_STXCNTRST_EXEV2RST)                            /*!< the Slave_TIMER counter is reset upon external event 2 */
#define SHRTIMER_STXCNT_RESET_EEV_3                      (SHRTIMER_STXCNTRST_EXEV3RST)                            /*!< the Slave_TIMER counter is reset upon external event 3 */
#define SHRTIMER_STXCNT_RESET_EEV_4                      (SHRTIMER_STXCNTRST_EXEV4RST)                            /*!< the Slave_TIMER counter is reset upon external event 4 */
#define SHRTIMER_STXCNT_RESET_EEV_5                      (SHRTIMER_STXCNTRST_EXEV5RST)                            /*!< the Slave_TIMER counter is reset upon external event 5 */
#define SHRTIMER_STXCNT_RESET_EEV_6                      (SHRTIMER_STXCNTRST_EXEV6RST)                            /*!< the Slave_TIMER counter is reset upon external event 6 */
#define SHRTIMER_STXCNT_RESET_EEV_7                      (SHRTIMER_STXCNTRST_EXEV7RST)                            /*!< the Slave_TIMER counter is reset upon external event 7 */
#define SHRTIMER_STXCNT_RESET_EEV_8                      (SHRTIMER_STXCNTRST_EXEV8RST)                            /*!< the Slave_TIMER counter is reset upon external event 8 */
#define SHRTIMER_STXCNT_RESET_EEV_9                      (SHRTIMER_STXCNTRST_EXEV9RST)                            /*!< the Slave_TIMER counter is reset upon external event 9 */
#define SHRTIMER_STXCNT_RESET_OTHER0_CMP0                BIT(19)                                                 /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 0 event */
#define SHRTIMER_STXCNT_RESET_OTHER0_CMP1                BIT(20)                                                 /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 1 event */
#define SHRTIMER_STXCNT_RESET_OTHER0_CMP3                BIT(21)                                                 /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 3 event */
#define SHRTIMER_STXCNT_RESET_OTHER1_CMP0                BIT(22)                                                 /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 0 event */
#define SHRTIMER_STXCNT_RESET_OTHER1_CMP1                BIT(23)                                                 /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 1 event */
#define SHRTIMER_STXCNT_RESET_OTHER1_CMP3                BIT(24)                                                 /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 3 event */
#define SHRTIMER_STXCNT_RESET_OTHER2_CMP0                BIT(25)                                                 /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 0 event */
#define SHRTIMER_STXCNT_RESET_OTHER2_CMP1                BIT(26)                                                 /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 1 event */
#define SHRTIMER_STXCNT_RESET_OTHER2_CMP3                BIT(27)                                                 /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 3 event */
#define SHRTIMER_STXCNT_RESET_OTHER3_CMP0                BIT(28)                                                 /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 0 event */
#define SHRTIMER_STXCNT_RESET_OTHER3_CMP1                BIT(29)                                                 /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 1 event */
#define SHRTIMER_STXCNT_RESET_OTHER3_CMP3                BIT(30)                                                 /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 3 event */

/* update event generated by reset event */
#define SHRTIMER_STXUPDATEONRESET_DISABLED               ((uint32_t)0x00000000U)                                 /*!< update event generated by reset event or roll-over event disable */
#define SHRTIMER_STXUPDATEONRESET_ENABLED                (SHRTIMER_STXCTL0_UPRST)                                 /*!< update event generated by reset event or roll-over event enable */

/* compare 3 or 1 delayed mode */
#define SHRTIMER_DELAYEDMODE_DISABLE                     ((uint32_t)0x00000000U)                                 /*!< delayed mode disable */
#define SHRTIMER_DELAYEDMODE_NOTIMEOUT                   ((uint32_t)0x00001000U)                                 /*!< compare event generated only if a capture has occurred */
#define SHRTIMER_DELAYEDMODE_TIMEOUTCMP0                 ((uint32_t)0x00002000U)                                 /*!< compare event generated if a capture has occurred or after a compare 0 match (timeout if capture event is missing) */
#define SHRTIMER_DELAYEDMODE_TIMEOUTCMP2                 ((uint32_t)0x00003000U)                                 /*!< compare event generated if a capture has occurred or after a compare 2 match (timeout if capture event is missing) */

/* capture trigger source */
#define SHRTIMER_CAPTURETRIGGER_NONE                     ((uint32_t)0x00000000U)                                 /*!< capture trigger is disabled */
#define SHRTIMER_CAPTURETRIGGER_UPDATE                   (SHRTIMER_STXCAP0TRG_CP0BUP)                             /*!< capture triggered by update event */
#define SHRTIMER_CAPTURETRIGGER_EXEV_0                   (SHRTIMER_STXCAP0TRG_CP0BEXEV0)                          /*!< capture triggered by external event 0 */
#define SHRTIMER_CAPTURETRIGGER_EXEV_1                   (SHRTIMER_STXCAP0TRG_CP0BEXEV1)                          /*!< capture triggered by external event 1 */
#define SHRTIMER_CAPTURETRIGGER_EXEV_2                   (SHRTIMER_STXCAP0TRG_CP0BEXEV2)                          /*!< capture triggered by external event 2 */
#define SHRTIMER_CAPTURETRIGGER_EXEV_3                   (SHRTIMER_STXCAP0TRG_CP0BEXEV3)                          /*!< capture triggered by external event 3 */
#define SHRTIMER_CAPTURETRIGGER_EXEV_4                   (SHRTIMER_STXCAP0TRG_CP0BEXEV4)                          /*!< capture triggered by external event 4 */
#define SHRTIMER_CAPTURETRIGGER_EXEV_5                   (SHRTIMER_STXCAP0TRG_CP0BEXEV5)                          /*!< capture triggered by external event 5 */
#define SHRTIMER_CAPTURETRIGGER_EXEV_6                   (SHRTIMER_STXCAP0TRG_CP0BEXEV6)                          /*!< capture triggered by external event 6 */
#define SHRTIMER_CAPTURETRIGGER_EXEV_7                   (SHRTIMER_STXCAP0TRG_CP0BEXEV7)                          /*!< capture triggered by external event 7 */
#define SHRTIMER_CAPTURETRIGGER_EXEV_8                   (SHRTIMER_STXCAP0TRG_CP0BEXEV8)                          /*!< capture triggered by external event 8 */
#define SHRTIMER_CAPTURETRIGGER_EXEV_9                   (SHRTIMER_STXCAP0TRG_CP0BEXEV9)                          /*!< capture triggered by external event 9 */
#define SHRTIMER_CAPTURETRIGGER_ST0_ACTIVE               (SHRTIMER_STXCAP0TRG_CP0BST0A)                           /*!< capture triggered by ST0CH0_O output inactive to active transition */
#define SHRTIMER_CAPTURETRIGGER_ST0_INACTIVE             (SHRTIMER_STXCAP0TRG_CP0BST0NA)                          /*!< capture triggered by ST0CH0_O output active to inactive transition */
#define SHRTIMER_CAPTURETRIGGER_ST0_CMP0                 (SHRTIMER_STXCAP0TRG_CP0BST0CMP0)                        /*!< capture triggered by compare 0 event of Slave_TIMER0 */
#define SHRTIMER_CAPTURETRIGGER_ST0_CMP1                 (SHRTIMER_STXCAP0TRG_CP0BST0CMP1)                        /*!< capture triggered by compare 0 event of Slave_TIMER0 */
#define SHRTIMER_CAPTURETRIGGER_ST1_ACTIVE               (SHRTIMER_STXCAP0TRG_CP0BST1A)                           /*!< capture triggered by ST1CH0_O output inactive to active transition */
#define SHRTIMER_CAPTURETRIGGER_ST1_INACTIVE             (SHRTIMER_STXCAP0TRG_CP0BST1NA)                          /*!< capture triggered by ST1CH0_O output active to inactive transition */
#define SHRTIMER_CAPTURETRIGGER_ST1_CMP0                 (SHRTIMER_STXCAP0TRG_CP0BST1CMP0)                        /*!< capture triggered by compare 0 event of Slave_TIMER1 */
#define SHRTIMER_CAPTURETRIGGER_ST1_CMP1                 (SHRTIMER_STXCAP0TRG_CP0BST1CMP1)                        /*!< capture triggered by compare 0 event of Slave_TIMER1 */
#define SHRTIMER_CAPTURETRIGGER_ST2_ACTIVE               (SHRTIMER_STXCAP0TRG_CP0BST2A)                           /*!< capture triggered by ST2CH0_O output inactive to active transition */
#define SHRTIMER_CAPTURETRIGGER_ST2_INACTIVE             (SHRTIMER_STXCAP0TRG_CP0BST2NA)                          /*!< capture triggered by ST2CH0_O output active to inactive transition */
#define SHRTIMER_CAPTURETRIGGER_ST2_CMP0                 (SHRTIMER_STXCAP0TRG_CP0BST2CMP0)                        /*!< capture triggered by compare 0 event of Slave_TIMER2 */
#define SHRTIMER_CAPTURETRIGGER_ST2_CMP1                 (SHRTIMER_STXCAP0TRG_CP0BST2CMP1)                        /*!< capture triggered by compare 0 event of Slave_TIMER2 */
#define SHRTIMER_CAPTURETRIGGER_ST3_ACTIVE               (SHRTIMER_STXCAP0TRG_CP0BST3A)                           /*!< capture triggered by ST3CH0_O output inactive to active transition */
#define SHRTIMER_CAPTURETRIGGER_ST3_INACTIVE             (SHRTIMER_STXCAP0TRG_CP0BST3NA)                          /*!< capture triggered by ST3CH0_O output active to inactive transition */
#define SHRTIMER_CAPTURETRIGGER_ST3_CMP0                 (SHRTIMER_STXCAP0TRG_CP0BST3CMP0)                        /*!< capture triggered by compare 0 event of Slave_TIMER3 */
#define SHRTIMER_CAPTURETRIGGER_ST3_CMP1                 (SHRTIMER_STXCAP0TRG_CP0BST3CMP1)                        /*!< capture triggered by compare 0 event of Slave_TIMER3 */
#define SHRTIMER_CAPTURETRIGGER_ST4_ACTIVE               (SHRTIMER_STXCAP0TRG_CP0BST4A)                           /*!< capture triggered by ST4CH0_O output inactive to active transition */
#define SHRTIMER_CAPTURETRIGGER_ST4_INACTIVE             (SHRTIMER_STXCAP0TRG_CP0BST4NA)                          /*!< capture triggered by ST4CH0_O output active to inactive transition */
#define SHRTIMER_CAPTURETRIGGER_ST4_CMP0                 (SHRTIMER_STXCAP0TRG_CP0BST4CMP0)                        /*!< capture triggered by compare 0 event of Slave_TIMER4 */
#define SHRTIMER_CAPTURETRIGGER_ST4_CMP1                 (SHRTIMER_STXCAP0TRG_CP0BST4CMP1)                        /*!< capture triggered by compare 0 event of Slave_TIMER4 */

/* external event filter mode */
#define SHRTIMER_EXEVFILTER_DISABLE                      ((uint32_t)0x00000000U)                                 /* filter mode disable */
#define SHRTIMER_EXEVFILTER_BLANKINGCMP0                 ((uint32_t)0x00000002U)                                 /*!< blanking mode. the blank is from counter reset/roll-over to SHRTIMER_STxCMP0V */
#define SHRTIMER_EXEVFILTER_BLANKINGCMP1                 ((uint32_t)0x00000004U)                                 /*!< blanking mode. the blank is from counter reset/roll-over to SHRTIMER_STxCMP1V */
#define SHRTIMER_EXEVFILTER_BLANKINGCMP2                 ((uint32_t)0x00000006U)                                 /*!< blanking mode. the blank is from counter reset/roll-over to SHRTIMER_STxCMP2V */
#define SHRTIMER_EXEVFILTER_BLANKINGCMP3                 ((uint32_t)0x00000008U)                                 /*!< blanking mode. the blank is from counter reset/roll-over to SHRTIMER_STxCMP3V */
#define SHRTIMER_EXEVFILTER_BLANKINGSRC0                 ((uint32_t)0x0000000AU)                                 /*!< blanking mode. the blank is from other Slave_TIMERy(not Slave_TIMERx): STBLKSRC0 */
#define SHRTIMER_EXEVFILTER_BLANKINGSRC1                 ((uint32_t)0x0000000CU)                                 /*!< blanking mode. the blank is from other Slave_TIMERy(not Slave_TIMERx): STBLKSRC1 */
#define SHRTIMER_EXEVFILTER_BLANKINGSRC2                 ((uint32_t)0x0000000EU)                                 /*!< blanking mode. the blank is from other Slave_TIMERy(not Slave_TIMERx): STBLKSRC2 */
#define SHRTIMER_EXEVFILTER_BLANKINGSRC3                 ((uint32_t)0x00000010U)                                 /*!< blanking mode. the blank is from other Slave_TIMERy(not Slave_TIMERx): STBLKSRC3 */
#define SHRTIMER_EXEVFILTER_BLANKINGSRC4                 ((uint32_t)0x00000012U)                                 /*!< blanking mode. the blank is from other Slave_TIMERy(not Slave_TIMERx): STBLKSRC4 */
#define SHRTIMER_EXEVFILTER_BLANKINGSRC5                 ((uint32_t)0x00000014U)                                 /*!< blanking mode. the blank is from other Slave_TIMERy(not Slave_TIMERx): STBLKSRC5 */
#define SHRTIMER_EXEVFILTER_BLANKINGSRC6                 ((uint32_t)0x00000016U)                                 /*!< blanking mode. the blank is from other Slave_TIMERy(not Slave_TIMERx): STBLKSRC6 */
#define SHRTIMER_EXEVFILTER_BLANKINGSRC7                 ((uint32_t)0x00000018U)                                 /*!< blanking mode. the blank is from other Slave_TIMERy(not Slave_TIMERx): STBLKSRC7 */
#define SHRTIMER_EXEVFILTER_WINDOWINGCMP1                ((uint32_t)0x0000001AU)                                 /*!< windowing mode. the windowing is from counter reset/roll-over to SHRTIMER_STxCMP1V */
#define SHRTIMER_EXEVFILTER_WINDOWINGCMP2                ((uint32_t)0x0000001CU)                                 /*!< windowing mode. the windowing is from counter reset/roll-over to SHRTIMER_STxCMP2V */
#define SHRTIMER_EXEVFILTER_WINDOWINGSRC                 ((uint32_t)0x0000001EU)                                 /*!< windowing mode. the windowing is from other Slave_TIMERy(not Slave_TIMERx):STWDSRC */

/* external event memorized enable */
#define SHRTIMER_EXEVMEMORIZED_DISABLE                   ((uint32_t)0x00000000U)                                 /*!< external event memory disable */
#define SHRTIMER_EXEVMEMORIZED_ENABLE                    (SHRTIMER_STXEXEVFCFG0_EXEV0MEEN)                        /*!< external event memory  enable. the memorized event is generated as soon as the blanking period or windowing period is completed */

/* dead time prescaler */
#define SHRTIMER_DEADTIME_PRESCALER_MUL64                ((uint32_t)0x0000000AU)                                 /*!< fSHRTIMER_DTGCK = 64* fSHRTIMER_CK */
#define SHRTIMER_DEADTIME_PRESCALER_MUL32                ((uint32_t)0x00000009U)                                 /*!< fSHRTIMER_DTGCK = 32* fSHRTIMER_CK */
#define SHRTIMER_DEADTIME_PRESCALER_MUL16                ((uint32_t)0x00000008U)                                 /*!< fSHRTIMER_DTGCK = 16* fSHRTIMER_CK */
#define SHRTIMER_DEADTIME_PRESCALER_MUL8                 ((uint32_t)0x00000000U)                                 /*!< fSHRTIMER_DTGCK = 8*fSHRTIMER_CK */
#define SHRTIMER_DEADTIME_PRESCALER_MUL4                 ((uint32_t)0x00000001U)                                 /*!< fSHRTIMER_DTGCK = (8*fSHRTIMER_CK)/2 = 4*fSHRTIMER_CK */
#define SHRTIMER_DEADTIME_PRESCALER_MUL2                 ((uint32_t)0x00000002U)                                 /*!< fSHRTIMER_DTGCK = (8*fSHRTIMER_CK)/4 = 2*fSHRTIMER_CK */
#define SHRTIMER_DEADTIME_PRESCALER_DIV1                 ((uint32_t)0x00000003U)                                 /*!< fSHRTIMER_DTGCK = (8*fSHRTIMER_CK)/8 = fSHRTIMER_CK*/
#define SHRTIMER_DEADTIME_PRESCALER_DIV2                 ((uint32_t)0x00000004U)                                 /*!< fSHRTIMER_DTGCK = (8*fSHRTIMER_CK)/16 = fSHRTIMER_CK / 2 */
#define SHRTIMER_DEADTIME_PRESCALER_DIV4                 ((uint32_t)0x00000005U)                                 /*!< fSHRTIMER_DTGCK = (8*fSHRTIMER_CK)/32 = fSHRTIMER_CK / 4 */
#define SHRTIMER_DEADTIME_PRESCALER_DIV8                 ((uint32_t)0x00000006U)                                 /*!< fSHRTIMER_DTGCK = (8*fSHRTIMER_CK)/64 = fSHRTIMER_CK / 8 */
#define SHRTIMER_DEADTIME_PRESCALER_DIV16                ((uint32_t)0x00000007U)                                 /*!< fSHRTIMER_DTGCK = (8*fSHRTIMER_CK)/128 = fSHRTIMER_CK / 16 */

/* dead time rising sign */
#define SHRTIMER_DEADTIME_RISINGSIGN_POSITIVE            ((uint32_t)0x00000000U)                                 /*!< the sign of rising edge dead-time value is positive */
#define SHRTIMER_DEADTIME_RISINGSIGN_NEGATIVE            (SHRTIMER_STXDTCTL_DTRS)                                 /*!< the sign of rising edge dead-time value is negative */

/* dead time rising edge protection for value and sign */
#define SHRTIMER_DEADTIME_RISING_PROTECT_DISABLE         ((uint32_t)0x00000000U)                                 /*!< protect disable. DTRS and DTRCFG[15:0] register are writable */
#define SHRTIMER_DEADTIME_RISING_PROTECT_ENABLE          (SHRTIMER_STXDTCTL_DTRSVPROT)                            /*!< protect enable. DTRS and DTRCFG[15:0] are read-only */

/* dead time rising edge protection only for sign */
#define SHRTIMER_DEADTIME_RISINGSIGN_PROTECT_DISABLE     ((uint32_t)0x00000000U)                                 /*!< protect disable. DTRS bit is writable */
#define SHRTIMER_DEADTIME_RISINGSIGN_PROTECT_ENABLE      (SHRTIMER_STXDTCTL_DTRSPROT)                             /*!< protect enable. DTRS bit is read-only */

/* dead time falling sign */
#define SHRTIMER_DEADTIME_FALLINGSIGN_POSITIVE           ((uint32_t)0x00000000U)                                 /*!< the sign of falling edge dead-time value is positive */
#define SHRTIMER_DEADTIME_FALLINGSIGN_NEGATIVE           (SHRTIMER_STXDTCTL_DTFS)                                 /*!< the sign of falling edge dead-time value is negative */

/* dead time falling edge protection for value and sign */
#define SHRTIMER_DEADTIME_FALLING_PROTECT_DISABLE        ((uint32_t)0x00000000U)                                 /*!< protect disable. DTFS and DTFCFG[15:0] register are writable */
#define SHRTIMER_DEADTIME_FALLING_PROTECT_ENABLE         (SHRTIMER_STXDTCTL_DTFSVPROT)                            /*!< protect enable. DTFS and DTFCFG[15:0] are read-only */

/* dead time falling edge protection only for sign */
#define SHRTIMER_DEADTIME_FALLINGSIGN_PROTECT_DISABLE    ((uint32_t)0x00000000U)                                 /*!< protect disable. DTFS bit is writable */
#define SHRTIMER_DEADTIME_FALLINGSIGN_PROTECT_ENABLE     (SHRTIMER_STXDTCTL_DTFSPROT)                             /*!< protect enable. DTFS bit is read-only */

/* the registers that can be written by DMA mode */
#define SHRTIMER_DMAMODE_NONE                            ((uint32_t)0x00000000U)                                 /*!< no register is updated by DMA mode */
#define SHRTIMER_DMAMODE_CTL0                            (SHRTIMER_DMAUPSTXR_STXCTL0)                             /*!< MTCTL0 or STxCTL0 register is updated by DMA mode */
#define SHRTIMER_DMAMODE_INTC                            (SHRTIMER_DMAUPSTXR_STXINTC)                             /*!< MT or STx register is updated by DMA mode */
#define SHRTIMER_DMAMODE_DMAINTEN                        (SHRTIMER_DMAUPSTXR_STXDMAINTEN)                         /*!< MTINTC or STxINTC register is updated by DMA mode */
#define SHRTIMER_DMAMODE_CNT                             (SHRTIMER_DMAUPSTXR_STXCNT)                              /*!< MTCNT or STxCNT register is updated by DMA mode */
#define SHRTIMER_DMAMODE_CAR                             (SHRTIMER_DMAUPSTXR_STXCAR)                              /*!< MTCAR or STxCAR register is updated by DMA mode */
#define SHRTIMER_DMAMODE_CREP                            (SHRTIMER_DMAUPSTXR_STXCREP)                             /*!< MTCREP or STxCREP register is updated by DMA mode */
#define SHRTIMER_DMAMODE_CMP0V                           (SHRTIMER_DMAUPSTXR_STXCMP0V)                            /*!< MTCMP0V or STxCMP0V register is updated by DMA mode */
#define SHRTIMER_DMAMODE_CMP1V                           (SHRTIMER_DMAUPSTXR_STXCMP1V)                            /*!< MTCMP1V or STxCMP1V register is updated by DMA mode */
#define SHRTIMER_DMAMODE_CMP2V                           (SHRTIMER_DMAUPSTXR_STXCMP2V)                            /*!< MTCMP2V or STxCMP2V register is updated by DMA mode */
#define SHRTIMER_DMAMODE_CMP3V                           (SHRTIMER_DMAUPSTXR_STXCMP3V)                            /*!< MTCMP3V or STxCMP3V register is updated by DMA mode */
#define SHRTIMER_DMAMODE_DTCTL                           (SHRTIMER_DMAUPSTXR_STXDTCTL)                            /*!< STxDTCTL register is updated by DMA mode */
#define SHRTIMER_DMAMODE_CH0SET                          (SHRTIMER_DMAUPSTXR_STXCH0SET)                           /*!< STxCH0SET register is updated by DMA mode */
#define SHRTIMER_DMAMODE_CH0RST                          (SHRTIMER_DMAUPSTXR_STXCH0RST)                           /*!< STxCH0RST register is updated by DMA mode */
#define SHRTIMER_DMAMODE_CH1SET                          (SHRTIMER_DMAUPSTXR_STXCH1SET)                           /*!< STxCH1SET register is updated by DMA mode */
#define SHRTIMER_DMAMODE_CH1RST                          (SHRTIMER_DMAUPSTXR_STXCH1RST)                           /*!< STxCH1RST register is updated by DMA mode */
#define SHRTIMER_DMAMODE_EXEVFCFG0                       (SHRTIMER_DMAUPSTXR_STXEXEVFCFG0)                        /*!< STxEXEVFCFG0 register is updated by DMA mode */
#define SHRTIMER_DMAMODE_EXEVFCFG1                       (SHRTIMER_DMAUPSTXR_STXEXEVFCFG1)                        /*!< STxEXEVFCFG1 register is updated by DMA mode */
#define SHRTIMER_DMAMODE_CNTRST                          (SHRTIMER_DMAUPSTXR_STXCNTRST)                           /*!< STxCNTRST register is updated by DMA mode */
#define SHRTIMER_DMAMODE_CSCTL                           (SHRTIMER_DMAUPSTXR_STXCSCTL)                            /*!< STxCSCTL register is updated by DMA mode */
#define SHRTIMER_DMAMODE_CHOCTL                          (SHRTIMER_DMAUPSTXR_STXCHOCTL)                           /*!< STxCHOCTL register is updated by DMA mode */
#define SHRTIMER_DMAMODE_FLTCTL                          (SHRTIMER_DMAUPSTXR_STXFLTCTL)                           /*!< STxFLTCTL register is updated by DMA mode */
#define SHRTIMER_DMAMODE_ACTL                            (SHRTIMER_DMAUPSTXR_STXACTL)                             /*!< STxACTL register is updated by DMA mode */

/* the synchronization input source */
#define SHRTIMER_SYNCINPUTSOURCE_DISABLE                 ((uint32_t)0x00000000U)                                 /*!< synchronization input disable */
#define SHRTIMER_SYNCINPUTSOURCE_INTERNAL                ((uint32_t)0x00000200U)                                 /*!< internal signal: TIMER0_TRGO in the advanced timer TIMER0 */
#define SHRTIMER_SYNCINPUTSOURCE_EXTERNAL                ((uint32_t)0x00000300U)                                 /*!< external signal: a positive pulse on the SHRTIMER_SCIN pin triggers the Master_TIMER */

/* the synchronization output source */
#define SHRTIMER_SYNCOUTPUTSOURCE_MTSTART                ((uint32_t)0x00000000U)                                 /*!< Master_TIMER start event to be sent to the synchronization output pad SHRTIMER_SCOUT */
#define SHRTIMER_SYNCOUTPUTSOURCE_MTCMP0                 ((uint32_t)0x00004000U)                                 /*!< Master_TIMER compare 0 event to be sent to the synchronization output pad SHRTIMER_SCOUT*/
#define SHRTIMER_SYNCOUTPUTSOURCE_ST0START               ((uint32_t)0x00008000U)                                 /*!< Slave_TIMER0 reset and start event to be sent to the synchronization output pad SHRTIMER_SCOUT */
#define SHRTIMER_SYNCOUTPUTSOURCE_ST0CMP0                ((uint32_t)0x0000C000U)                                 /*!< Slave_TIMER0 compare 0 event to be sent to the synchronization output pad SHRTIMER_SCOUT */

/* the pulse on the synchronization output pad SHRTIMER_SCOUT */
#define SHRTIMER_SYNCOUTPUTPOLARITY_DISABLE              ((uint32_t)0x00000000U)                                 /*!< pulse generated disable. No pulse on SHRTIMER_SCOUT */
#define SHRTIMER_SYNCOUTPUTPOLARITY_POSITIVE             ((uint32_t)0x00002000U)                                 /*!< positive pulse generated on the SHRTIMER_SCOUT. the length of it is 16 tSHRTIMER_CK cycles */
#define SHRTIMER_SYNCOUTPUTPOLARITY_NEGATIVE             ((uint32_t)0x00003000U)                                 /*!< negative pulse generated on the SHRTIMER_SCOUT. the length of it is 16 tSHRTIMER_CK cycles */

/* continuous mode in bunch mode */
#define SHRTIMER_BUNCHMODE_SINGLE                        ((uint32_t)0x00000000U)                                 /*!< single pulse mode. the BM-counter stops by hardware when it reaches the SHRTIMER_BMCAR value */
#define SHRTIMER_BUNCHMODE_CONTINOUS                     (SHRTIMER_BMCTL_BMCTN)                                   /*!< continuous mode. the BM-counter rolls over to zero and counts continuously when it reaches the SHRTIMER_BMCAR value */

/* bunch mode clock source */
#define SHRTIMER_BUNCHMODE_CLOCKSOURCE_MASTER            ((uint32_t)0x00000000U)                                 /*!< the clock source for the bunch mode counter: Master_TIMER counter reset/roll-over event */
#define SHRTIMER_BUNCHMODE_CLOCKSOURCE_ST0               ((uint32_t)0x00000004U)                                 /*!< the clock source for the bunch mode counter: Slave_TIMER0 counter reset/roll-over event */
#define SHRTIMER_BUNCHMODE_CLOCKSOURCE_ST1               ((uint32_t)0x00000008U)                                 /*!< the clock source for the bunch mode counter: Slave_TIMER1 counter reset/roll-over event */
#define SHRTIMER_BUNCHMODE_CLOCKSOURCE_ST2               ((uint32_t)0x0000000CU)                                 /*!< the clock source for the bunch mode counter: Slave_TIMER2 counter reset/roll-over event */
#define SHRTIMER_BUNCHMODE_CLOCKSOURCE_ST3               ((uint32_t)0x00000010U)                                 /*!< the clock source for the bunch mode counter: Slave_TIMER3 counter reset/roll-over event */
#define SHRTIMER_BUNCHMODE_CLOCKSOURCE_ST4               ((uint32_t)0x00000014U)                                 /*!< the clock source for the bunch mode counter: Slave_TIMER4 counter reset/roll-over event */
#define SHRTIMER_BUNCHMODE_CLOCKSOURCE_TIMER6_TRGO       ((uint32_t)0x00000020U)                                 /*!< the clock source for the bunch mode counter: chip internal signal BMCLK2 */
#define SHRTIMER_BUNCHMODE_CLOCKSOURCE_SHRTIMERCK        ((uint32_t)0x00000028U)                                 /*!< the clock source for the bunch mode counter: prescaled fSHRTIMER_CK clock */

/* bunch mode clock division */
#define SHRTIMER_BUNCHMODE_PRESCALER_DIV1                ((uint32_t)0x00000000U)                                 /*!< fSHRTIMER_BMCNTCK = fSHRTIMER_CK */
#define SHRTIMER_BUNCHMODE_PRESCALER_DIV2                ((uint32_t)0x00000040U)                                 /*!< fSHRTIMER_BMCNTCK = fSHRTIMER_CK/2 */
#define SHRTIMER_BUNCHMODE_PRESCALER_DIV4                ((uint32_t)0x00000080U)                                 /*!< fSHRTIMER_BMCNTCK = fSHRTIMER_CK/4 */
#define SHRTIMER_BUNCHMODE_PRESCALER_DIV8                ((uint32_t)0x000000C0U)                                 /*!< fSHRTIMER_BMCNTCK = fSHRTIMER_CK/8 */
#define SHRTIMER_BUNCHMODE_PRESCALER_DIV16               ((uint32_t)0x00000100U)                                 /*!< fSHRTIMER_BMCNTCK = fSHRTIMER_CK/16 */
#define SHRTIMER_BUNCHMODE_PRESCALER_DIV32               ((uint32_t)0x00000140U)                                 /*!< fSHRTIMER_BMCNTCK = fSHRTIMER_CK/32 */
#define SHRTIMER_BUNCHMODE_PRESCALER_DIV64               ((uint32_t)0x00000180U)                                 /*!< fSHRTIMER_BMCNTCK = fSHRTIMER_CK/64 */
#define SHRTIMER_BUNCHMODE_PRESCALER_DIV128              ((uint32_t)0x000001C0U)                                 /*!< fSHRTIMER_BMCNTCK = fSHRTIMER_CK/128 */
#define SHRTIMER_BUNCHMODE_PRESCALER_DIV256              ((uint32_t)0x00000200U)                                 /*!< fSHRTIMER_BMCNTCK = fSHRTIMER_CK/256 */
#define SHRTIMER_BUNCHMODE_PRESCALER_DIV512              ((uint32_t)0x00000240U)                                 /*!< fSHRTIMER_BMCNTCK = fSHRTIMER_CK/512 */
#define SHRTIMER_BUNCHMODE_PRESCALER_DIV1024             ((uint32_t)0x00000280U)                                 /*!< fSHRTIMER_BMCNTCK = fSHRTIMER_CK/1024 */
#define SHRTIMER_BUNCHMODE_PRESCALER_DIV2048             ((uint32_t)0x000002C0U)                                 /*!< fSHRTIMER_BMCNTCK = fSHRTIMER_CK/2048*/
#define SHRTIMER_BUNCHMODE_PRESCALER_DIV4096             ((uint32_t)0x00000300U)                                 /*!< fSHRTIMER_BMCNTCK = fSHRTIMER_CK/4096 */
#define SHRTIMER_BUNCHMODE_PRESCALER_DIV8192             ((uint32_t)0x00000340U)                                 /*!< fSHRTIMER_BMCNTCK = fSHRTIMER_CK/8192 */
#define SHRTIMER_BUNCHMODE_PRESCALER_DIV16384            ((uint32_t)0x00000380U)                                 /*!< fSHRTIMER_BMCNTCK = fSHRTIMER_CK/16384 */
#define SHRTIMER_BUNCHMODE_PRESCALER_DIV32768            ((uint32_t)0x000003C0U)                                 /*!< fSHRTIMER_BMCNTCK = fSHRTIMER_CK/32768 */

/* bunch mode shadow enable */
#define SHRTIMER_BUNCHMODEPRELOAD_DISABLED               ((uint32_t)0x00000000U)                                 /*!< the shadow registers for SHRTIMER_BMCMPV and SHRTIMER_BMCAR registers are disabled */
#define SHRTIMER_BUNCHMODEPRELOAD_ENABLED                (SHRTIMER_BMCTL_BMSE)                                    /*!< the shadow registers for SHRTIMER_BMCMPV and SHRTIMER_BMCAR registers are enabled */

/* the event triggers bunch mode operation */
#define SHRTIMER_BUNCHMODE_TRIGGER_NONE                  ((uint32_t)0x00000000U)                                 /*!< clear all triggers */
#define SHRTIMER_BUNCHMODE_TRIGGER_MTRESET               (SHRTIMER_BMSTRG_MTRST)                                  /*!< Master_TIMER reset event triggers bunch mode operation */
#define SHRTIMER_BUNCHMODE_TRIGGER_MTREPETITION          (SHRTIMER_BMSTRG_MTREP)                                  /*!< Master_TIMER repetition event triggers bunch mode operation */
#define SHRTIMER_BUNCHMODE_TRIGGER_MTCMP0                (SHRTIMER_BMSTRG_MTCMP0)                                 /*!< Master_TIMER compare 0 event triggers bunch mode operation */
#define SHRTIMER_BUNCHMODE_TRIGGER_MTCMP1                (SHRTIMER_BMSTRG_MTCMP1)                                 /*!< Master_TIMER compare 1 event triggers bunch mode operation */
#define SHRTIMER_BUNCHMODE_TRIGGER_MTCMP2                (SHRTIMER_BMSTRG_MTCMP2)                                 /*!< Master_TIMER compare 2 event triggers bunch mode operation */
#define SHRTIMER_BUNCHMODE_TRIGGER_MTCMP3                (SHRTIMER_BMSTRG_MTCMP3)                                 /*!< Master_TIMER compare 3 event triggers bunch mode operation */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST0RESET              (SHRTIMER_BMSTRG_ST0RST)                                 /*!< Slave_TIMER0 reset event triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST0REPETITION         (SHRTIMER_BMSTRG_ST0REP)                                 /*!< Slave_TIMER0 repetition event triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST0CMP0               (SHRTIMER_BMSTRG_ST0CMP0)                                /*!< Slave_TIMER0 compare 0 event triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST0CMP1               (SHRTIMER_BMSTRG_ST0CMP1)                                /*!< Slave_TIMER0 compare 1 event triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST1RESET              (SHRTIMER_BMSTRG_ST1RST)                                 /*!< Slave_TIMER1 reset event triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST1REPETITION         (SHRTIMER_BMSTRG_ST1REP)                                 /*!< Slave_TIMER1 repetition event triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST1CMP0               (SHRTIMER_BMSTRG_ST1CMP0)                                /*!< Slave_TIMER1 compare 0 event triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST1CMP1               (SHRTIMER_BMSTRG_ST1CMP1)                                /*!< Slave_TIMER1 compare 1 event triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST2RESET              (SHRTIMER_BMSTRG_ST2RST)                                 /*!< Slave_TIMER2 reset event triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST2REPETITION         (SHRTIMER_BMSTRG_ST2REP)                                 /*!< Slave_TIMER2 repetition event triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST2CMP0               (SHRTIMER_BMSTRG_ST2CMP0)                                /*!< Slave_TIMER2 compare 0 event triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST2CMP1               (SHRTIMER_BMSTRG_ST2CMP1)                                /*!< Slave_TIMER2 compare 1 event triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST3RESET              (SHRTIMER_BMSTRG_ST3RST)                                 /*!< Slave_TIMER3 reset event triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST3REPETITION         (SHRTIMER_BMSTRG_ST3REP)                                 /*!< Slave_TIMER3 repetition event triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST3CMP0               (SHRTIMER_BMSTRG_ST3CMP0)                                /*!< Slave_TIMER3 compare 0 event triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST3CMP1               (SHRTIMER_BMSTRG_ST3CMP1)                                /*!< Slave_TIMER3 compare 1 event triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST4RESET              (SHRTIMER_BMSTRG_ST4RST)                                 /*!< Slave_TIMER4 reset event triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST4REPETITION         (SHRTIMER_BMSTRG_ST4REP)                                 /*!< Slave_TIMER4 repetition event triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST4CMP0               (SHRTIMER_BMSTRG_ST4CMP0)                                /*!< Slave_TIMER4 compare 0 event triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST4CMP1               (SHRTIMER_BMSTRG_ST4CMP1)                                /*!< Slave_TIMER4 compare 1 event triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST0EVENT6             (SHRTIMER_BMSTRG_ST0EXEV6)                               /*!< Slave_TIMER0 period event following external event 6 triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_ST3EVENT7             (SHRTIMER_BMSTRG_ST3EXEV7)                               /*!< Slave_TIMER3 period event following external event 7 triggers bunch mode operation  */
#define SHRTIMER_BUNCHMODE_TRIGGER_EVENT6                (SHRTIMER_BMSTRG_EXEV6)                                  /*!< external event 6 triggers bunch mode operation */
#define SHRTIMER_BUNCHMODE_TRIGGER_EVENT7                (SHRTIMER_BMSTRG_EXEV7)                                  /*!< external event 7 triggers bunch mode operation */
#define SHRTIMER_BUNCHMODE_TRIGGER_CHIP                  (SHRTIMER_BMSTRG_CISGN)                                  /*!< chip internal signal triggers bunch mode operation */

/* external event source */
#define SHRTIMER_EXEV_SRC0                               ((uint32_t)0x00000000U)                                 /*!< external event y source is EXEVySRC 0 */
#define SHRTIMER_EXEV_SRC1                               ((uint32_t)0x00000001U)                                 /*!< external event y source is EXEVySRC 1 */
#define SHRTIMER_EXEV_SRC2                               ((uint32_t)0x00000002U)                                 /*!< external event y source is EXEVySRC 2 */
#define SHRTIMER_EXEV_SRC3                               ((uint32_t)0x00000003U)                                 /*!< external event y source is EXEVySRC 3 */

/* external event polarity */
#define SHRTIMER_EXEV_POLARITY_HIGH                      ((uint32_t)0x00000000U)                                 /*!< external event y active at high level */
#define SHRTIMER_EXEV_POLARITY_LOW                       (SHRTIMER_EXEVCFG0_EXEV0P)                               /*!< external event y active at low level */

/* external event edge sensitivity */
#define SHRTIMER_EXEV_EDGE_LEVEL                         ((uint32_t)0x00000000U)                                 /*!< level active. active level is defined by EXEVyP bit */
#define SHRTIMER_EXEV_EDGE_RISING                        ((uint32_t)0x00000008U)                                 /*!< rising edge active */
#define SHRTIMER_EXEV_EDGE_FALLING                       ((uint32_t)0x00000010U)                                 /*!< falling edge active */
#define SHRTIMER_EXEV_EDGE_BOTH                          ((uint32_t)0x00000018U)                                 /*!< both edges active */

/* external event digital filter clock division */
#define SHRTIMER_EXEV_PRESCALER_DIV1                     ((uint32_t)0x00000000U)                                 /*!< fSHRTIMER_EXEVFCK = fSHRTIMER_CK */
#define SHRTIMER_EXEV_PRESCALER_DIV2                     ((uint32_t)0x40000000U)                                 /*!< fSHRTIMER_EXEVFCK = fSHRTIMER_CK / 2 */
#define SHRTIMER_EXEV_PRESCALER_DIV4                     ((uint32_t)0x80000000U)                                 /*!< fSHRTIMER_EXEVFCK = fSHRTIMER_CK / 4 */
#define SHRTIMER_EXEV_PRESCALER_DIV8                     ((uint32_t)0xC0000000U)                                 /*!< fSHRTIMER_EXEVFCK = fSHRTIMER_CK / 8 */

/* fault input source */
#define SHRTIMER_FAULT_SOURCE_PIN                        ((uint32_t)0x00000000U)                                 /*!< the source of fault input is chip external pin */
#define SHRTIMER_FAULT_SOURCE_INTERNAL                   (SHRTIMER_FLTINCFG0_FLT0INSRC)                           /*!< the source of fault input is chip internal signal(for example comparator) */

/* fault input polarity */
#define SHRTIMER_FAULT_POLARITY_LOW                      ((uint32_t)0x00000000U)                                 /*!< fault 0 input active at low level */
#define SHRTIMER_FAULT_POLARITY_HIGH                     (SHRTIMER_FLTINCFG0_FLT0INP)                             /*!< fault 0 input active at high  level */

/* enable or disable fault */
#define SHRTIMER_FAULT_CHANNEL_DISABLE                   ((uint32_t)0x00000000U)                                 /*!< fault channel disable */
#define SHRTIMER_FAULT_CHANNEL_ENABLE                    (SHRTIMER_FLTINCFG0_FLT0INEN)                            /*!< fault channel enable */

/* protect fault input configuration */
#define SHRTIMER_FAULT_PROTECT_DISABLE                   ((uint32_t)0x00000000U)                                 /*!< protect disable. FLT0INEN, FLT0INP, FLT0INSRC and FLT0INFC[3:0] is writable */
#define SHRTIMER_FAULT_PROTECT_ENABLE                    (SHRTIMER_FLTINCFG0_FLT0INPROT)                          /*!< protect enable. FLT0INEN, FLT0INP, FLT0INSRC and FLT0INFC[3:0] is read-only */

/* fault input digital filter clock division */
#define SHRTIMER_FAULT_PRESCALER_DIV1                    ((uint32_t)0x00000000U)                                 /*!< fSHRTIMER_FLTFCK = fSHRTIMER_CK */
#define SHRTIMER_FAULT_PRESCALER_DIV2                    ((uint32_t)0x01000000U)                                 /*!< fSHRTIMER_FLTFCK = fSHRTIMER_CK/2 */
#define SHRTIMER_FAULT_PRESCALER_DIV4                    ((uint32_t)0x02000000U)                                 /*!< fSHRTIMER_FLTFCK = fSHRTIMER_CK/4 */
#define SHRTIMER_FAULT_PRESCALER_DIV8                    ((uint32_t)0x03000000U)                                 /*!< fSHRTIMER_FLTFCK = fSHRTIMER_CK/8 */

/* SHRTIMER_ADCTRIG update source */
#define SHRTIMER_ADCTRGI_UPDATE_MT                       ((uint32_t)0x00000000U)                                 /*!< Master_TIMER update event */
#define SHRTIMER_ADCTRGI_UPDATE_ST0                      ((uint32_t)0x00010000U)                                 /*!< Slaver_TIMER0 update event */
#define SHRTIMER_ADCTRGI_UPDATE_ST1                      ((uint32_t)0x00020000U)                                 /*!< Slaver_TIMER1 update event */
#define SHRTIMER_ADCTRGI_UPDATE_ST2                      ((uint32_t)0x00030000U)                                 /*!< Slaver_TIMER2 update event */
#define SHRTIMER_ADCTRGI_UPDATE_ST3                      ((uint32_t)0x00040000U)                                 /*!< Slaver_TIMER3 update event */
#define SHRTIMER_ADCTRGI_UPDATE_ST4                      ((uint32_t)0x00050000U)                                 /*!< Slaver_TIMER4 update event */

/*  ADC trigger event */
#define SHRTIMER_ADCTRGI02_EVENT_NONE                    ((uint32_t)0x00000000U)                                 /*!< no ADC trigger event */
#define SHRTIMER_ADCTRGI02_EVENT_MTCMP0                  (SHRTIMER_ADCTRIGS0_TRG0MTC0)                            /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Master_TIMER compare 0 */
#define SHRTIMER_ADCTRGI02_EVENT_MTCMP1                  (SHRTIMER_ADCTRIGS0_TRG0MTC1)                            /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Master_TIMER compare 1 */
#define SHRTIMER_ADCTRGI02_EVENT_MTCMP2                  (SHRTIMER_ADCTRIGS0_TRG0MTC2)                            /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Master_TIMER compare 2 */
#define SHRTIMER_ADCTRGI02_EVENT_MTCMP3                  (SHRTIMER_ADCTRIGS0_TRG0MTC3)                            /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Master_TIMER compare 3 */
#define SHRTIMER_ADCTRGI02_EVENT_MTPER                   (SHRTIMER_ADCTRIGS0_TRG0MTPER)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Master_TIMER period */
#define SHRTIMER_ADCTRGI02_EVENT_EXEV0                   (SHRTIMER_ADCTRIGS0_TRG0EXEV0)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on external event 0 */
#define SHRTIMER_ADCTRGI02_EVENT_EXEV1                   (SHRTIMER_ADCTRIGS0_TRG0EXEV1)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on external event 1 */
#define SHRTIMER_ADCTRGI02_EVENT_EXEV2                   (SHRTIMER_ADCTRIGS0_TRG0EXEV2)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on external event 2 */
#define SHRTIMER_ADCTRGI02_EVENT_EXEV3                   (SHRTIMER_ADCTRIGS0_TRG0EXEV3)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on external event 3 */
#define SHRTIMER_ADCTRGI02_EVENT_EXEV4                   (SHRTIMER_ADCTRIGS0_TRG0EXEV4)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on external event 4 */
#define SHRTIMER_ADCTRGI02_EVENT_ST0CMP1                 (SHRTIMER_ADCTRIGS0_TRG0ST0C1)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER0 compare 1 */
#define SHRTIMER_ADCTRGI02_EVENT_ST0CMP2                 (SHRTIMER_ADCTRIGS0_TRG0ST0C2)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER0 compare 2 */
#define SHRTIMER_ADCTRGI02_EVENT_ST0CMP3                 (SHRTIMER_ADCTRIGS0_TRG0ST0C3)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER0 compare 3 */
#define SHRTIMER_ADCTRGI02_EVENT_ST0PER                  (SHRTIMER_ADCTRIGS0_TRG0ST0PER)                          /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER0 period */
#define SHRTIMER_ADCTRGI02_EVENT_ST0RST                  (SHRTIMER_ADCTRIGS0_TRG0ST0RST)                          /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER0 reset */
#define SHRTIMER_ADCTRGI02_EVENT_ST1CMP1                 (SHRTIMER_ADCTRIGS0_TRG0ST1C1)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER1 compare 1 */
#define SHRTIMER_ADCTRGI02_EVENT_ST1CMP2                 (SHRTIMER_ADCTRIGS0_TRG0ST1C2)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER1 compare 2 */
#define SHRTIMER_ADCTRGI02_EVENT_ST1CMP3                 (SHRTIMER_ADCTRIGS0_TRG0ST1C3)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER1 compare 3 */
#define SHRTIMER_ADCTRGI02_EVENT_ST1PER                  (SHRTIMER_ADCTRIGS0_TRG0ST1PER)                          /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER1 period */
#define SHRTIMER_ADCTRGI02_EVENT_ST1RST                  (SHRTIMER_ADCTRIGS0_TRG0ST1RST)                          /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER1 reset */
#define SHRTIMER_ADCTRGI02_EVENT_ST2CMP1                 (SHRTIMER_ADCTRIGS0_TRG0ST2C1)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER2 compare 1 */
#define SHRTIMER_ADCTRGI02_EVENT_ST2CMP2                 (SHRTIMER_ADCTRIGS0_TRG0ST2C2)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER2 compare 2 */
#define SHRTIMER_ADCTRGI02_EVENT_ST2CMP3                 (SHRTIMER_ADCTRIGS0_TRG0ST2C3)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER2 compare 3 */
#define SHRTIMER_ADCTRGI02_EVENT_ST2PER                  (SHRTIMER_ADCTRIGS0_TRG0ST2PER)                          /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER2 period */
#define SHRTIMER_ADCTRGI02_EVENT_ST3CMP1                 (SHRTIMER_ADCTRIGS0_TRG0ST3C1)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER3 compare 1 */
#define SHRTIMER_ADCTRGI02_EVENT_ST3CMP2                 (SHRTIMER_ADCTRIGS0_TRG0ST3C2)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER3 compare 2 */
#define SHRTIMER_ADCTRGI02_EVENT_ST3CMP3                 (SHRTIMER_ADCTRIGS0_TRG0ST3C3)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER3 compare 3 */
#define SHRTIMER_ADCTRGI02_EVENT_ST3PER                  (SHRTIMER_ADCTRIGS0_TRG0ST3PER)                          /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER3 period */
#define SHRTIMER_ADCTRGI02_EVENT_ST4CMP1                 (SHRTIMER_ADCTRIGS0_TRG0ST4C1)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER4 compare 1 */
#define SHRTIMER_ADCTRGI02_EVENT_ST4CMP2                 (SHRTIMER_ADCTRIGS0_TRG0ST4C2)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER4 compare 2 */
#define SHRTIMER_ADCTRGI02_EVENT_ST4CMP3                 (SHRTIMER_ADCTRIGS0_TRG0ST4C3)                           /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER4 compare 3 */
#define SHRTIMER_ADCTRGI02_EVENT_ST4PER                  (SHRTIMER_ADCTRIGS0_TRG0ST4PER)                          /*!< SHRTIMER_ADCTRIG0 or SHRTIMER_ADCTRIG2 on Slave_TIMER4 period */

#define SHRTIMER_ADCTRGI13_EVENT_NONE                    ((uint32_t)0x00000000U)                                 /*!< no ADC trigger event */
#define SHRTIMER_ADCTRGI13_EVENT_MTCMP0                  (SHRTIMER_ADCTRIGS1_TRG1MTC0)                            /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Master_TIMER compare 0 */
#define SHRTIMER_ADCTRGI13_EVENT_MTCMP1                  (SHRTIMER_ADCTRIGS1_TRG1MTC1)                            /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Master_TIMER compare 1 */
#define SHRTIMER_ADCTRGI13_EVENT_MTCMP2                  (SHRTIMER_ADCTRIGS1_TRG1MTC2)                            /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Master_TIMER compare 2 */
#define SHRTIMER_ADCTRGI13_EVENT_MTCMP3                  (SHRTIMER_ADCTRIGS1_TRG1MTC3)                            /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Master_TIMER compare 3 */
#define SHRTIMER_ADCTRGI13_EVENT_MTPER                   (SHRTIMER_ADCTRIGS1_TRG1MTPER)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Master_TIMER period */
#define SHRTIMER_ADCTRGI13_EVENT_EXEV5                   (SHRTIMER_ADCTRIGS1_TRG1EXEV5)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on external event 5 */
#define SHRTIMER_ADCTRGI13_EVENT_EXEV6                   (SHRTIMER_ADCTRIGS1_TRG1EXEV6)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on external event 6 */
#define SHRTIMER_ADCTRGI13_EVENT_EXEV7                   (SHRTIMER_ADCTRIGS1_TRG1EXEV7)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on external event 7 */
#define SHRTIMER_ADCTRGI13_EVENT_EXEV8                   (SHRTIMER_ADCTRIGS1_TRG1EXEV8)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on external event 8 */
#define SHRTIMER_ADCTRGI13_EVENT_EXEV9                   (SHRTIMER_ADCTRIGS1_TRG1EXEV9)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on external event 9 */
#define SHRTIMER_ADCTRGI13_EVENT_ST0CMP1                 (SHRTIMER_ADCTRIGS1_TRG1ST0C1)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER0 compare 1 */
#define SHRTIMER_ADCTRGI13_EVENT_ST0CMP2                 (SHRTIMER_ADCTRIGS1_TRG1ST0C2)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER0 compare 2 */
#define SHRTIMER_ADCTRGI13_EVENT_ST0CMP3                 (SHRTIMER_ADCTRIGS1_TRG1ST0C3)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER0 compare 3 */
#define SHRTIMER_ADCTRGI13_EVENT_ST0PER                  (SHRTIMER_ADCTRIGS1_TRG1ST0PER)                          /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER0 period */
#define SHRTIMER_ADCTRGI13_EVENT_ST1CMP1                 (SHRTIMER_ADCTRIGS1_TRG1ST1C1)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER1 compare 1 */
#define SHRTIMER_ADCTRGI13_EVENT_ST1CMP2                 (SHRTIMER_ADCTRIGS1_TRG1ST1C2)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER1 compare 2 */
#define SHRTIMER_ADCTRGI13_EVENT_ST1CMP3                 (SHRTIMER_ADCTRIGS1_TRG1ST1C3)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER1 compare 3 */
#define SHRTIMER_ADCTRGI13_EVENT_ST1PER                  (SHRTIMER_ADCTRIGS1_TRG1ST1PER)                          /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER1 period */
#define SHRTIMER_ADCTRGI13_EVENT_ST2CMP1                 (SHRTIMER_ADCTRIGS1_TRG1ST2C1)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER2 compare 1 */
#define SHRTIMER_ADCTRGI13_EVENT_ST2CMP2                 (SHRTIMER_ADCTRIGS1_TRG1ST2C2)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER2 compare 2 */
#define SHRTIMER_ADCTRGI13_EVENT_ST2CMP3                 (SHRTIMER_ADCTRIGS1_TRG1ST2C3)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER2 compare 3 */
#define SHRTIMER_ADCTRGI13_EVENT_ST2PER                  (SHRTIMER_ADCTRIGS1_TRG1ST2PER)                          /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER2 period */
#define SHRTIMER_ADCTRGI13_EVENT_ST2RST                  (SHRTIMER_ADCTRIGS1_TRG1ST2RST)                          /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER2 reset */
#define SHRTIMER_ADCTRGI13_EVENT_ST3CMP1                 (SHRTIMER_ADCTRIGS1_TRG1ST3C1)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER3 compare 1 */
#define SHRTIMER_ADCTRGI13_EVENT_ST3CMP2                 (SHRTIMER_ADCTRIGS1_TRG1ST3C2)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER3 compare 2 */
#define SHRTIMER_ADCTRGI13_EVENT_ST3CMP3                 (SHRTIMER_ADCTRIGS1_TRG1ST3C3)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER3 compare 3 */
#define SHRTIMER_ADCTRGI13_EVENT_ST3PER                  (SHRTIMER_ADCTRIGS1_TRG1ST3PER)                          /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER3 period */
#define SHRTIMER_ADCTRGI13_EVENT_ST3RST                  (SHRTIMER_ADCTRIGS1_TRG1ST3RST)                          /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER3 reset */
#define SHRTIMER_ADCTRGI13_EVENT_ST4CMP1                 (SHRTIMER_ADCTRIGS1_TRG1ST4C1)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER4 compare 1 */
#define SHRTIMER_ADCTRGI13_EVENT_ST4CMP2                 (SHRTIMER_ADCTRIGS1_TRG1ST4C2)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER4 compare 2 */
#define SHRTIMER_ADCTRGI13_EVENT_ST4CMP3                 (SHRTIMER_ADCTRIGS1_TRG1ST4C3)                           /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER4 compare 3 */
#define SHRTIMER_ADCTRGI13_EVENT_ST4RST                  (SHRTIMER_ADCTRIGS1_TRG1ST4RST)                          /*!< SHRTIMER_ADCTRIG1 or SHRTIMER_ADCTRIG3 on Slave_TIMER4 reset */

/* DLL calibration control */
#define SHRTIMER_CALIBRATION_ONCE                        ((uint32_t)0x88888888U)                                 /*!< DLL calibration start once */
#define SHRTIMER_CALIBRATION_1048576_PERIOD              ((uint32_t)0x00000000U)                                 /*!< 1048576 * tSHRTIMER_CK */
#define SHRTIMER_CALIBRATION_131072_PERIOD               ((uint32_t)0x00000004U)                                 /*!< 131072 * tSHRTIMER_CK */
#define SHRTIMER_CALIBRATION_16384_PERIOD                ((uint32_t)0x00000008U)                                 /*!< 16384 * tSHRTIMER_CK  */
#define SHRTIMER_CALIBRATIO_2048_PERIOD                  ((uint32_t)0x0000000CU)                                 /*!< 2048 * tSHRTIMER_CK */

/* Master_TIMER and Slave_TIMER interrupt enable or disable */
#define SHRTIMER_MT_ST_INT_CMP0                          SHRTIMER_STXDMAINTEN_CMP0IE                              /*!< compare 0 interrupt */
#define SHRTIMER_MT_ST_INT_CMP1                          SHRTIMER_STXDMAINTEN_CMP1IE                              /*!< compare 1 interrupt */
#define SHRTIMER_MT_ST_INT_CMP2                          SHRTIMER_STXDMAINTEN_CMP2IE                              /*!< compare 2 interrupt */
#define SHRTIMER_MT_ST_INT_CMP3                          SHRTIMER_STXDMAINTEN_CMP3IE                              /*!< compare 3 interrupt */
#define SHRTIMER_MT_ST_INT_REP                           SHRTIMER_STXDMAINTEN_REPIE                               /*!< repetition interrupt */
#define SHRTIMER_MT_INT_SYNI                             SHRTIMER_MTDMAINTEN_SYNIIE                               /*!< synchronization input interrupt */
#define SHRTIMER_MT_ST_INT_UPD                           SHRTIMER_STXDMAINTEN_UPIE                                /*!< update interrupt */
#define SHRTIMER_ST_INT_CAP0                             SHRTIMER_STXDMAINTEN_CAP0IE                              /*!< capture 0 interrupt */
#define SHRTIMER_ST_INT_CAP1                             SHRTIMER_STXDMAINTEN_CAP1IE                              /*!< capture 1 interrupt */
#define SHRTIMER_ST_INT_CH0OA                            SHRTIMER_STXDMAINTEN_CH0OAIE                             /*!< channel 0 output active interrupt */
#define SHRTIMER_ST_INT_CH0ONA                           SHRTIMER_STXDMAINTEN_CH0ONAIE                            /*!< channel 0 output inactive interrupt */
#define SHRTIMER_ST_INT_CH1OA                            SHRTIMER_STXDMAINTEN_CH1OAIE                             /*!< channel 1 output active interrupt */
#define SHRTIMER_ST_INT_CH1ONA                           SHRTIMER_STXDMAINTEN_CH1ONAIE                            /*!< channel 1 output inactive interrupt */
#define SHRTIMER_ST_INT_CNTRST                           SHRTIMER_STXDMAINTEN_RSTIE                               /*!< counter reset interrupt */
#define SHRTIMER_ST_INT_DLYIDLE                          SHRTIMER_STXDMAINTEN_DLYIIE                              /*!< delayed IDLE mode entry interrupt */

/* SHRTIMER common interrupt */
#define SHRTIMER_INT_SYSFLT                              SHRTIMER_INTEN_SYSFLTIE                                  /*!< system fault interrupt */
#define SHRTIMER_INT_DLLCAL                              SHRTIMER_INTEN_DLLCALIE                                  /*!< DLL calibration completed interrupt */
#define SHRTIMER_INT_BMPER                               SHRTIMER_INTEN_BMPERIE                                   /*!< bunch mode period interrupt */

/* Master_TIMER and Slave_TIMER interrupt flag */
#define SHRTIMER_MT_ST_INT_FLAG_CMP0                     SHRTIMER_STXINTF_CMP0IF                                  /*!< compare 0 interrupt flag */
#define SHRTIMER_MT_ST_INT_FLAG_CMP1                     SHRTIMER_STXINTF_CMP1IF                                  /*!< compare 1 interrupt flag */
#define SHRTIMER_MT_ST_INT_FLAG_CMP2                     SHRTIMER_STXINTF_CMP2IF                                  /*!< compare 2 interrupt flag */
#define SHRTIMER_MT_ST_INT_FLAG_CMP3                     SHRTIMER_STXINTF_CMP3IF                                  /*!< compare 3 interrupt flag */
#define SHRTIMER_MT_ST_INT_FLAG_REP                      SHRTIMER_STXINTF_REPIF                                   /*!< repetition interrupt flag */
#define SHRTIMER_MT_INT_FLAG_SYNI                        SHRTIMER_MTINTF_SYNIIF                                   /*!< synchronization input interrupt flag */
#define SHRTIMER_MT_ST_INT_FLAG_UPD                      SHRTIMER_STXINTF_UPIF                                    /*!< update interrupt flag */
#define SHRTIMER_ST_INT_FLAG_CAP0                        SHRTIMER_STXINTF_CAP0IF                                  /*!< capture 0 interrupt flag */
#define SHRTIMER_ST_INT_FLAG_CAP1                        SHRTIMER_STXINTF_CAP1IF                                  /*!< capture 1 interrupt flag */
#define SHRTIMER_ST_INT_FLAG_CH0OA                       SHRTIMER_STXINTF_CH0OAIF                                 /*!< channel 0 output active interrupt flag */
#define SHRTIMER_ST_INT_FLAG_CH0ONA                      SHRTIMER_STXINTF_CH0ONAIF                                /*!< channel 0 output inactive interrupt flag */
#define SHRTIMER_ST_INT_FLAG_CH1OA                       SHRTIMER_STXINTF_CH1OAIF                                 /*!< channel 1 output active interrupt flag */
#define SHRTIMER_ST_INT_FLAG_CH1ONA                      SHRTIMER_STXINTF_CH1ONAIF                                /*!< channel 1 output inactive interrupt flag */
#define SHRTIMER_ST_INT_FLAG_CNTRST                      SHRTIMER_STXINTF_RSTIF                                   /*!< counter reset interrupt flag */
#define SHRTIMER_ST_INT_FLAG_DLYIDLE                     SHRTIMER_STXINTF_DLYIIF                                  /*!< delayed IDLE mode entry interrupt flag */

/* SHRTIMER common interrupt flag */
#define SHRTIMER_INT_FLAG_FLT0                           SHRTIMER_INTF_FLT0IF                                     /*!< fault 0 interrupt flag */
#define SHRTIMER_INT_FLAG_FLT1                           SHRTIMER_INTF_FLT1IF                                     /*!< fault 1 interrupt flag */
#define SHRTIMER_INT_FLAG_FLT2                           SHRTIMER_INTF_FLT2IF                                     /*!< fault 2 interrupt flag */
#define SHRTIMER_INT_FLAG_FLT3                           SHRTIMER_INTF_FLT3IF                                     /*!< fault 3 interrupt flag */
#define SHRTIMER_INT_FLAG_FLT4                           SHRTIMER_INTF_FLT4IF                                     /*!< fault 4 interrupt flag */
#define SHRTIMER_INT_FLAG_SYSFLT                         SHRTIMER_INTF_SYSFLTIF                                   /*!< system fault interrupt flag */
#define SHRTIMER_INT_FLAG_DLLCAL                         SHRTIMER_INTF_DLLCALIF                                   /*!< DLL calibration completed interrupt flag */
#define SHRTIMER_INT_FLAG_BMPER                          SHRTIMER_INTF_BMPERIF                                    /*!< bunch mode period interrupt flag */

/* Master_TIMER and Slave_TIMER flag */
#define SHRTIMER_MT_ST_FLAG_CMP0                         SHRTIMER_STXINTF_CMP0IF                                  /*!< compare 0 flag */
#define SHRTIMER_MT_ST_FLAG_CMP1                         SHRTIMER_STXINTF_CMP1IF                                  /*!< compare 1 flag */
#define SHRTIMER_MT_ST_FLAG_CMP2                         SHRTIMER_STXINTF_CMP2IF                                  /*!< compare 2 flag */
#define SHRTIMER_MT_ST_FLAG_CMP3                         SHRTIMER_STXINTF_CMP3IF                                  /*!< compare 3 flag */
#define SHRTIMER_MT_ST_FLAG_REP                          SHRTIMER_STXINTF_REPIF                                   /*!< repetition flag */
#define SHRTIMER_MT_FLAG_SYNI                            SHRTIMER_MTINTF_SYNIIF                                   /*!< synchronization input flag */
#define SHRTIMER_MT_ST_FLAG_UPD                          SHRTIMER_STXINTF_UPIF                                    /*!< update flag */
#define SHRTIMER_ST_FLAG_CAP0                            SHRTIMER_STXINTF_CAP0IF                                  /*!< capture 0 flag */
#define SHRTIMER_ST_FLAG_CAP1                            SHRTIMER_STXINTF_CAP1IF                                  /*!< capture 1 flag */
#define SHRTIMER_ST_FLAG_CH0OA                           SHRTIMER_STXINTF_CH0OAIF                                 /*!< channel 0 output active flag */
#define SHRTIMER_ST_FLAG_CH0ONA                          SHRTIMER_STXINTF_CH0ONAIF                                /*!< channel 0 output inactive flag */
#define SHRTIMER_ST_FLAG_CH1OA                           SHRTIMER_STXINTF_CH1OAIF                                 /*!< channel 1 output active flag */
#define SHRTIMER_ST_FLAG_CH1ONA                          SHRTIMER_STXINTF_CH1ONAIF                                /*!< channel 1 output inactive flag */
#define SHRTIMER_ST_FLAG_CNTRST                          SHRTIMER_STXINTF_RSTIF                                   /*!< counter reset flag */
#define SHRTIMER_ST_FLAG_DLYIDLE                         SHRTIMER_STXINTF_DLYIIF                                  /*!< delayed IDLE mode entry flag */
#define SHRTIMER_ST_FLAG_CBLN                            SHRTIMER_STXINTF_CBLNF                                   /*!< current balanced flag */
#define SHRTIMER_ST_FLAG_BLNIDLE                         SHRTIMER_STXINTF_BLNIF                                   /*!< balanced IDLE flag */
#define SHRTIMER_ST_FLAG_CH0OUT                          SHRTIMER_STXINTF_CH0F                                    /*!< channel 0 output flag */
#define SHRTIMER_ST_FLAG_CH1OUT                          SHRTIMER_STXINTF_CH1F                                    /*!< channel 1 output flag */

/* SHRTIMER common flag */
#define SHRTIMER_FLAG_FLT0                               SHRTIMER_INTF_FLT0IF                                     /*!< fault 0 flag */
#define SHRTIMER_FLAG_FLT1                               SHRTIMER_INTF_FLT1IF                                     /*!< fault 1 flag */
#define SHRTIMER_FLAG_FLT2                               SHRTIMER_INTF_FLT2IF                                     /*!< fault 2 flag */
#define SHRTIMER_FLAG_FLT3                               SHRTIMER_INTF_FLT3IF                                     /*!< fault 3 flag */
#define SHRTIMER_FLAG_FLT4                               SHRTIMER_INTF_FLT4IF                                     /*!< fault 4 flag */
#define SHRTIMER_FLAG_SYSFLT                             SHRTIMER_INTF_SYSFLTIF                                   /*!< system fault flag */
#define SHRTIMER_FLAG_DLLCAL                             SHRTIMER_INTF_DLLCALIF                                   /*!< DLL calibration completed flag */
#define SHRTIMER_FLAG_BMPER                              SHRTIMER_INTF_BMPERIF                                    /*!< bunch mode period flag */

/* Master_TIMER and Slave_TIMER DMA request */
#define SHRTIMER_MT_ST_DMA_CMP0                          SHRTIMER_STXDMAINTEN_CMP0DEN                             /*!< compare 0 DMA request */
#define SHRTIMER_MT_ST_DMA_CMP1                          SHRTIMER_STXDMAINTEN_CMP1DEN                             /*!< compare 1 DMA request */
#define SHRTIMER_MT_ST_DMA_CMP2                          SHRTIMER_STXDMAINTEN_CMP2DEN                             /*!< compare 2 DMA request */
#define SHRTIMER_MT_ST_DMA_CMP3                          SHRTIMER_STXDMAINTEN_CMP3DEN                             /*!< compare 3 DMA request */
#define SHRTIMER_MT_ST_DMA_REP                           SHRTIMER_STXDMAINTEN_REPDEN                              /*!< repetition DMA request */
#define SHRTIMER_MT_DMA_SYNID                            SHRTIMER_MTDMAINTEN_SYNIDEN                              /*!< synchronization input DMA request */
#define SHRTIMER_MT_ST_DMA_UPD                           SHRTIMER_STXDMAINTEN_UPDEN                               /*!< update DMA request */
#define SHRTIMER_ST_DMA_CAP0                             SHRTIMER_STXDMAINTEN_CAP0DEN                             /*!< capture 0 DMA request */
#define SHRTIMER_ST_DMA_CAP1                             SHRTIMER_STXDMAINTEN_CAP1DEN                             /*!< capture 1 DMA request */
#define SHRTIMER_ST_DMA_CH0OA                            SHRTIMER_STXDMAINTEN_CH0OADEN                            /*!< channel 0 output active DMA request */
#define SHRTIMER_ST_DMA_CH0ONA                           SHRTIMER_STXDMAINTEN_CH0ONADEN                           /*!< channel 0 output inactive DMA request */
#define SHRTIMER_ST_DMA_CH1OA                            SHRTIMER_STXDMAINTEN_CH1OADEN                            /*!< channel 1 output active DMA request */
#define SHRTIMER_ST_DMA_CH1ONA                           SHRTIMER_STXDMAINTEN_CH1ONADEN                           /*!< channel 1 output inactive DMA request */
#define SHRTIMER_ST_DMA_CNTRST                           SHRTIMER_STXDMAINTEN_RSTDEN                              /*!< counter reset DMA request */
#define SHRTIMER_ST_DMA_DLYIDLE                          SHRTIMER_STXDMAINTEN_DLYIDEN                             /*!< delay IDLE DMA request */

/* Master_TIMER or Slave_TIMER update by software */
#define SHRTIMER_UPDATE_SW_MT                            (SHRTIMER_CTL1_MTSUP)                                    /*!< Master_TIMER software update */
#define SHRTIMER_UPDATE_SW_ST0                           (SHRTIMER_CTL1_ST0SUP)                                   /*!< Slave_TIMER0 software update */
#define SHRTIMER_UPDATE_SW_ST1                           (SHRTIMER_CTL1_ST1SUP)                                   /*!< Slave_TIMER1 software update */
#define SHRTIMER_UPDATE_SW_ST2                           (SHRTIMER_CTL1_ST2SUP)                                   /*!< Slave_TIMER2 software update */
#define SHRTIMER_UPDATE_SW_ST3                           (SHRTIMER_CTL1_ST3SUP)                                   /*!< Slave_TIMER3 software update */
#define SHRTIMER_UPDATE_SW_ST4                           (SHRTIMER_CTL1_ST4SUP)                                   /*!< Slave_TIMER4 software update */

/* Master_TIMER or Slave_TIMER counter reset by software */
#define SHRTIMER_COUNTER_RESET_SW_MT                     (SHRTIMER_CTL1_MTSRST)                                   /*!< Master_TIMER software reset */
#define SHRTIMER_COUNTER_RESET_SW_ST0                    (SHRTIMER_CTL1_ST0SRST)                                  /*!< Slave_TIMER0 software reset */
#define SHRTIMER_COUNTER_RESET_SW_ST1                    (SHRTIMER_CTL1_ST1SRST)                                  /*!< Slave_TIMER1 software reset */
#define SHRTIMER_COUNTER_RESET_SW_ST2                    (SHRTIMER_CTL1_ST2SRST)                                  /*!< Slave_TIMER2 software reset */
#define SHRTIMER_COUNTER_RESET_SW_ST3                    (SHRTIMER_CTL1_ST3SRST)                                  /*!< Slave_TIMER3 software reset */
#define SHRTIMER_COUNTER_RESET_SW_ST4                    (SHRTIMER_CTL1_ST4SRST)                                  /*!< Slave_TIMER4 software reset */

/* channel output polarity */
#define SHRTIMER_CHANNEL_POLARITY_HIGH                   ((uint32_t)0x00000000U)                                 /*!< channel active high */
#define SHRTIMER_CHANNEL_POLARITY_LOW                    (SHRTIMER_STXCHOCTL_CH0P)                                /*!< channel active low */

/* channel set request */
#define SHRTIMER_CHANNEL_SET_NONE                        ((uint32_t)0x00000000U)                                 /*!< clear all channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_RSTSYNI                     (SHRTIMER_STXCH0SET_CH0SRST)                             /*!< Slave_TIMERx reset event from synchronous input and software can generate channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_PER                         (SHRTIMER_STXCH0SET_CH0SPER)                             /*!< Slave_TIMERx period event can generate ��set request�� */
#define SHRTIMER_CHANNEL_SET_CMP0                        (SHRTIMER_STXCH0SET_CH0SCMP0)                            /*!< Slave_TIMERx compare 0 event can generate ��set request�� */
#define SHRTIMER_CHANNEL_SET_CMP1                        (SHRTIMER_STXCH0SET_CH0SCMP1)                            /*!< Slave_TIMERx compare 1 event can generate ��set request�� */
#define SHRTIMER_CHANNEL_SET_CMP2                        (SHRTIMER_STXCH0SET_CH0SCMP2)                            /*!< Slave_TIMERx compare 2 event can generate ��set request�� */
#define SHRTIMER_CHANNEL_SET_CMP3                        (SHRTIMER_STXCH0SET_CH0SCMP3)                            /*!< Slave_TIMERx compare 3 event can generate ��set request�� */
#define SHRTIMER_CHANNEL_SET_MTPER                       (SHRTIMER_STXCH0SET_CH0SMTPER)                           /*!< Master_TIMER period event generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_MTCMP0                      (SHRTIMER_STXCH0SET_CH0SMTCMP0)                          /*!< Master_TIMER compare 0 event generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_MTCMP1                      (SHRTIMER_STXCH0SET_CH0SMTCMP1)                          /*!< Master_TIMER compare 1 event generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_MTCMP2                      (SHRTIMER_STXCH0SET_CH0SMTCMP2)                          /*!< Master_TIMER compare 2 event generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_MTCMP3                      (SHRTIMER_STXCH0SET_CH0SMTCMP3)                          /*!< Master_TIMER compare 3 event generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_STEV0                       (SHRTIMER_STXCH0SET_CH0SSTEV0)                           /*!< Slave_TIMERx interconnection event 0 generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_STEV1                       (SHRTIMER_STXCH0SET_CH0SSTEV1)                           /*!< Slave_TIMERx interconnection event 1 generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_STEV2                       (SHRTIMER_STXCH0SET_CH0SSTEV2)                           /*!< Slave_TIMERx interconnection event 2 generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_STEV3                       (SHRTIMER_STXCH0SET_CH0SSTEV3)                           /*!< Slave_TIMERx interconnection event 3 generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_STEV4                       (SHRTIMER_STXCH0SET_CH0SSTEV4)                           /*!< Slave_TIMERx interconnection event 4 generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_STEV5                       (SHRTIMER_STXCH0SET_CH0SSTEV5)                           /*!< Slave_TIMERx interconnection event 5 generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_STEV6                       (SHRTIMER_STXCH0SET_CH0SSTEV6)                           /*!< Slave_TIMERx interconnection event 6 generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_STEV7                       (SHRTIMER_STXCH0SET_CH0SSTEV7)                           /*!< Slave_TIMERx interconnection event 7 generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_STEV8                       (SHRTIMER_STXCH0SET_CH0SSTEV8)                           /*!< Slave_TIMERx interconnection event 8 generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_EXEV0                       (SHRTIMER_STXCH0SET_CH0SEXEV0)                           /*!< external event 0 generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_EXEV1                       (SHRTIMER_STXCH0SET_CH0SEXEV1)                           /*!< external event 1 generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_EXEV2                       (SHRTIMER_STXCH0SET_CH0SEXEV2)                           /*!< external event 2 generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_EXEV3                       (SHRTIMER_STXCH0SET_CH0SEXEV3)                           /*!< external event 3 generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_EXEV4                       (SHRTIMER_STXCH0SET_CH0SEXEV4)                           /*!< external event 4 generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_EXEV5                       (SHRTIMER_STXCH0SET_CH0SEXEV5)                           /*!< external event 5 generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_EXEV6                       (SHRTIMER_STXCH0SET_CH0SEXEV6)                           /*!< external event 6 generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_EXEV7                       (SHRTIMER_STXCH0SET_CH0SEXEV7)                           /*!< external event 7 generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_EXEV8                       (SHRTIMER_STXCH0SET_CH0SEXEV8)                           /*!< external event 8 generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_EXEV9                       (SHRTIMER_STXCH0SET_CH0SEXEV9)                           /*!< external event 9 generates channel ��set request�� */
#define SHRTIMER_CHANNEL_SET_UPDATE                      (SHRTIMER_STXCH0SET_CH0SUP)                              /*!< update event generates channel ��set request�� */

/* channel reset request */
#define SHRTIMER_CHANNEL_RESET_NONE                      ((uint32_t)0x00000000U)                                 /*!< clear all channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_RSTSYNI                   (SHRTIMER_STXCH0RST_CH0RSRST)                            /*!< Slave_TIMERx reset event from synchronous input and software can generate channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_PER                       (SHRTIMER_STXCH0RST_CH0RSPER)                            /*!< Slave_TIMERx period event can generate ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_CMP0                      (SHRTIMER_STXCH0RST_CH0RSCMP0)                           /*!< Slave_TIMERx compare 0 event can generate ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_CMP1                      (SHRTIMER_STXCH0RST_CH0RSCMP1)                           /*!< Slave_TIMERx compare 1 event can generate ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_CMP2                      (SHRTIMER_STXCH0RST_CH0RSCMP2)                           /*!< Slave_TIMERx compare 2 event can generate ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_CMP3                      (SHRTIMER_STXCH0RST_CH0RSCMP3)                           /*!< Slave_TIMERx compare 3 event can generate ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_MTPER                     (SHRTIMER_STXCH0RST_CH0RSMTPER)                          /*!< Master_TIMER period event generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_MTCMP0                    (SHRTIMER_STXCH0RST_CH0RSMTCMP0)                         /*!< Master_TIMER compare 0 event generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_MTCMP1                    (SHRTIMER_STXCH0RST_CH0RSMTCMP1)                         /*!< Master_TIMER compare 1 event generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_MTCMP2                    (SHRTIMER_STXCH0RST_CH0RSMTCMP2)                         /*!< Master_TIMER compare 2 event generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_MTCMP3                    (SHRTIMER_STXCH0RST_CH0RSMTCMP3)                         /*!< Master_TIMER compare 3 event generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_STEV0                     (SHRTIMER_STXCH0RST_CH0RSSTEV0)                          /*!< Slave_TIMERx interconnection event 0 generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_STEV1                     (SHRTIMER_STXCH0RST_CH0RSSTEV1)                          /*!< Slave_TIMERx interconnection event 1 generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_STEV2                     (SHRTIMER_STXCH0RST_CH0RSSTEV2)                          /*!< Slave_TIMERx interconnection event 2 generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_STEV3                     (SHRTIMER_STXCH0RST_CH0RSSTEV3)                          /*!< Slave_TIMERx interconnection event 3 generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_STEV4                     (SHRTIMER_STXCH0RST_CH0RSSTEV4)                          /*!< Slave_TIMERx interconnection event 4 generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_STEV5                     (SHRTIMER_STXCH0RST_CH0RSSTEV5)                          /*!< Slave_TIMERx interconnection event 5 generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_STEV6                     (SHRTIMER_STXCH0RST_CH0RSSTEV6)                          /*!< Slave_TIMERx interconnection event 6 generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_STEV7                     (SHRTIMER_STXCH0RST_CH0RSSTEV7)                          /*!< Slave_TIMERx interconnection event 7 generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_STEV8                     (SHRTIMER_STXCH0RST_CH0RSSTEV8)                          /*!< Slave_TIMERx interconnection event 8 generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_EXEV0                     (SHRTIMER_STXCH0RST_CH0RSEXEV0)                          /*!< external event 0 generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_EXEV1                     (SHRTIMER_STXCH0RST_CH0RSEXEV1)                          /*!< external event 1 generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_EXEV2                     (SHRTIMER_STXCH0RST_CH0RSEXEV2)                          /*!< external event 2 generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_EXEV3                     (SHRTIMER_STXCH0RST_CH0RSEXEV3)                          /*!< external event 3 generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_EXEV4                     (SHRTIMER_STXCH0RST_CH0RSEXEV4)                          /*!< external event 4 generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_EXEV5                     (SHRTIMER_STXCH0RST_CH0RSEXEV5)                          /*!< external event 5 generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_EXEV6                     (SHRTIMER_STXCH0RST_CH0RSEXEV6)                          /*!< external event 6 generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_EXEV7                     (SHRTIMER_STXCH0RST_CH0RSEXEV7)                          /*!< external event 7 generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_EXEV8                     (SHRTIMER_STXCH0RST_CH0RSEXEV8)                          /*!< external event 8 generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_EXEV9                     (SHRTIMER_STXCH0RST_CH0RSEXEV9)                          /*!< external event 9 generates channel ��reset request�� */
#define SHRTIMER_CHANNEL_RESET_UPDATE                    (SHRTIMER_STXCH0RST_CH0RSUP)                             /*!< update event generates channel ��reset request�� */

/* channel IDLE state enable in bunch mode */
#define SHRTIMER_CHANNEL_BUNCH_IDLE_DISABLE              ((uint32_t)0x00000000U)                                 /*!< channel output is not affected by the bunch mode */
#define SHRTIMER_CHANNEL_BUNCH_IDLE_ENABLE               (SHRTIMER_STXCHOCTL_BMCH0IEN)                            /*!< channel output can be IDLE state in bunch mode */

/* channel output idle state */
#define SHRTIMER_CHANNEL_IDLESTATE_INACTIVE              ((uint32_t)0x00000000U)                                 /*!< channel idle state output is inactive */
#define SHRTIMER_CHANNEL_IDLESTATE_ACTIVE                (SHRTIMER_STXCHOCTL_ISO0)                                /*!< channel idle state output is active */

/* channel output in fault state */
#define SHRTIMER_CHANNEL_FAULTSTATE_NONE                 ((uint32_t)0x00000000U)                                 /*!< no effect. the output is normally in Run mode when a fault event happened */
#define SHRTIMER_CHANNEL_FAULTSTATE_ACTIVE               ((uint32_t)0x00000010U)                                 /*!< output is active level when in FAULT state */
#define SHRTIMER_CHANNEL_FAULTSTATE_INACTIVE             ((uint32_t)0x00000020U)                                 /*!< output is inactive level when in FAULT state */
#define SHRTIMER_CHANNEL_FAULTSTATE_HIGHZ                ((uint32_t)0x00000030U)                                 /*!< output is Hi-Z when in FAULT state */

/* channel carrier-signal mode enable */
#define SHRTIMER_CHANNEL_CARRIER_DISABLED                ((uint32_t)0x00000000U)                                 /*!< the output is not affected by the fault input */
#define SHRTIMER_CHANNEL_CARRIER_ENABLED                 (SHRTIMER_STXCHOCTL_CH0CSEN)                             /*!< output at active level when in FAULT state */

/* channel dead-time insert in bunch mode */
#define SHRTIMER_CHANNEL_BUNCH_ENTRY_REGULAR             ((uint32_t)0x00000000U)                                 /*!< the output enter IDLE immediately */
#define SHRTIMER_CHANNEL_BUNCH_ENTRY_DEADTIME            ((uint32_t)0x00000080U)                                 /*!< dead-time is inserted before entering the IDLE state */

/* software event generates channel ��set request�� or ��reset request�� */
#define SHRTIMER_CHANNEL_SOFTWARE_SET                    ((uint32_t)0x00000001U)                                 /*!< software event cannot generate request */
#define SHRTIMER_CHANNEL_SOFTWARE_RESET                  ((uint32_t)0x00000002U)                                 /*!< software event can generate request */

/* channel output level */
#define SHRTIMER_CHANNEL_OUTPUT_ACTIVE                   ((uint32_t)0x00000001U)                                 /*!< channel outputs active level */
#define SHRTIMER_CHANNEL_OUTPUT_INACTIVE                 ((uint32_t)0x00000002U)                                 /*!< channel outputs inactive leve */

/* channel run state */
#define SHRTIMER_CHANNEL_STATE_IDLE                      ((uint32_t)0x00000001U)                                 /*!< Run state: the channel output can take the active or inactive level as programmed in the crossbar unit */
#define SHRTIMER_CHANNEL_STATE_RUN                       ((uint32_t)0x00000002U)                                 /*!< Idle state: after an SHRTIMER reset, when the outputs are disabled by software or during a bunch mode operation */
#define SHRTIMER_CHANNEL_STATE_FAULT                     ((uint32_t)0x00000003U)                                 /*!< Fault state: when a fault happen */

/* bunch mode operating flag */
#define SHRTIMER_BUNCHMODE_OPERATION_OFF                 ((uint32_t)0x00000000U)                                 /*!< normal operation. bunch mode is not operation */
#define SHRTIMER_BUNCHMODE_OPERATION_ON                  ((uint32_t)0x80000000U)                                 /*!< bunch mode operation on-going. */

/* function declarations */
/* SHRTIMER timebase configure functions */
/* deinit a SHRTIMER */
void shrtimer_deinit(uint32_t shrtimer_periph);
/* configure and start DLL calibration */
void shrtimer_dll_calibration_start(uint32_t shrtimer_periph, uint32_t calform);
/* initialize SHRTIMER SHRTIMER time base parameters struct with a default value */
void shrtimer_baseinit_struct_para_init(shrtimer_baseinit_parameter_struct* baseinit);
/* initialize Master_TIMER and Slave_TIMER timerbase */
void shrtimer_timers_base_init(uint32_t shrtimer_periph, uint32_t timer_id, shrtimer_baseinit_parameter_struct* baseinit);
/* enable a counter */
void shrtimer_timers_counter_enable(uint32_t shrtimer_periph, uint32_t cntid);
/* disable a counter */
void shrtimer_timers_counter_disable(uint32_t shrtimer_periph, uint32_t cntid);
/* enable the Master_TIMER or Slave_TIMER update event */
void shrtimer_timers_update_event_enable(uint32_t shrtimer_periph, uint32_t timer_id);
/* disable the Master_TIMER or Slave_TIMER update event */
void shrtimer_timers_update_event_disable(uint32_t shrtimer_periph, uint32_t timer_id);
/* trigger the Master_TIMER and Slave_TIMER registers update by software */
void shrtimer_software_update(uint32_t shrtimer_periph, uint32_t timersrc);
/* reset the Master_TIMER and Slave_TIMER counter by software */
void shrtimer_software_counter_reset(uint32_t shrtimer_periph, uint32_t timerrst);

/* SHRTIMER waveform configure functions */
/* initialize waveform mode initialization parameters struct with a default value */
void shrtimer_timerinit_struct_para_init(shrtimer_timerinit_parameter_struct* timerinit);
/* initialize a timer to work in waveform mode */
void shrtimer_timers_waveform_init(uint32_t shrtimer_periph, uint32_t timer_id, shrtimer_timerinit_parameter_struct* timerinitpara);
/* initialize Slave_TIMER general behavior configuration struct with a default value */
void shrtimer_timercfg_struct_para_init(shrtimer_timercfg_parameter_struct* timercgf);
/* configure the general behavior of a Slave_TIMER which work in waveform mode */
void shrtimer_slavetimer_waveform_config(uint32_t shrtimer_periph, uint32_t timer_id, shrtimer_timercfg_parameter_struct * timercfg);
/* initialize compare unit configuration struct with a default value */
void shrtimer_comparecfg_struct_para_init(shrtimer_comparecfg_parameter_struct* comparecfg);
/* configure the compare unit of a Slave_TIMER which work in waveform mode */
void shrtimer_slavetimer_waveform_compare_config(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t comparex, shrtimer_comparecfg_parameter_struct* cmpcfg);
/* initialize channel output configuration struct  with a default value */
void shrtimer_channel_outputcfg_struct_para_init(shrtimer_channel_outputcfg_parameter_struct * channelcfg);
/* configure the channel output of a Slave_TIMER work in waveform mode */
void shrtimer_slavetimer_waveform_channel_config(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t channel, shrtimer_channel_outputcfg_parameter_struct * channelcfg);
/* software generates channel "set request" or "reset request" */
void shrtimer_slavetimer_waveform_channel_software_request(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t channel, uint32_t request);
/* get Slave_TIMER channel output level */
uint32_t shrtimer_slavetimer_waveform_channel_output_level_get(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t channel);
/* get Slave_TIMER channel run state */
uint32_t shrtimer_slavetimer_waveform_channel_state_get(uint32_t shrtimer_periph, uint32_t channel);
/* initialize dead time configuration struct with a default value */
void shrtimer_deadtimercfg_struct_para_init(shrtimer_deadtimecfg_parameter_struct * dtcfg);
/* configure the dead time for Slave_TIMER */
void shrtimer_slavetimer_deadtime_config(uint32_t shrtimer_periph, uint32_t timer_id, shrtimer_deadtimecfg_parameter_struct* dtcfg);
/* initialize carrier signal configuration struct with a default value */
void shrtimer_carriersignalcfg_struct_para_init(shrtimer_carriersignalcfg_parameter_struct* carriercfg);
/* configure the carrier signal mode for Slave_TIMER */
void shrtimer_slavetimer_carriersignal_config(uint32_t shrtimer_periph, uint32_t timer_id, shrtimer_carriersignalcfg_parameter_struct* carriercfg);
/* enable a output channel */
void shrtimer_output_channel_enable(uint32_t shrtimer_periph, uint32_t chid);
/* disable a output channel */
void shrtimer_output_channel_disable(uint32_t shrtimer_periph, uint32_t chid);

/* Master_TIMER and Slave_TIMER numerical related functions */
/* configure the compare value in Master_TIMER */
void shrtimer_mastertimer_compare_value_config(uint32_t shrtimer_periph, uint32_t comparex, uint32_t cmpvalue);
/* get the compare value in Master_TIMER */
uint32_t shrtimer_mastertimer_compare_value_get(uint32_t shrtimer_periph, uint32_t comparex);
/* configure the compare value in Slave_TIMER */
void shrtimer_slavetimer_compare_value_config(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t comparex, uint32_t cmpvalue);
/* get the compare value in Slave_TIMER */
uint32_t shrtimer_slavetimer_compare_value_get(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t comparex);
/* configure the counter value in Master_TIMER and Slave_TIMER */
void shrtimer_timers_counter_value_config(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t cntvalue);
/* get the counter value in Master_TIMER and Slave_TIMER */
uint32_t shrtimer_timers_counter_value_get(uint32_t shrtimer_periph, uint32_t timer_id);
/* configure the counter auto reload value in Master_TIMER and Slave_TIMER */
void shrtimer_timers_autoreload_value_config(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t carlvalue);
/* get the counter auto reload value in Master_TIMER and Slave_TIMER */
uint32_t shrtimer_timers_autoreload_value_get(uint32_t shrtimer_periph, uint32_t timer_id);
/* configure the counter repetition value in Master_TIMER and Slave_TIMER */
void shrtimer_timers_repetition_value_config(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t replvalue);
/* get the counter repetition value in Master_TIMER and Slave_TIMER */
uint32_t shrtimer_timers_repetition_value_get(uint32_t shrtimer_periph, uint32_t timer_id);

/* external event and synchronization configure functions */
/* initialize external event filtering for Slave_TIMER configuration struct with a default value */
void shrtimer_exevfilter_struct_para_init(shrtimer_exevfilter_parameter_struct * exevfilter);
/* configure the external event filtering for Slave_TIMER (blanking, windowing) */
void shrtimer_slavetimer_exevent_filtering_config(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t event_id, shrtimer_exevfilter_parameter_struct* exevfilter);
/* initialize external event configuration struct with a default value */
void shrtimer_exeventcfg_struct_para_init(shrtimer_exeventcfg_parameter_struct * exevcfg);
/* configure the an external event */
void shrtimer_exevent_config(uint32_t shrtimer_periph, uint32_t event_id, shrtimer_exeventcfg_parameter_struct* exevcfg);
/* configure external event digital filter clock division */
void shrtimer_exevent_prescaler(uint32_t shrtimer_periph, uint32_t prescaler);
/* initialize synchronization configuration struct with a default value */
void shrtimer_synccfg_struct_para_init(shrtimer_synccfg_parameter_struct* synccfg);
/* configure the synchronization input/output of the SHRTIMER */
void shrtimer_synchronization_config(uint32_t shrtimer_periph, shrtimer_synccfg_parameter_struct* synccfg);

/* fault configure functions */
/* configure the synchronization input/output of the SHRTIMER */
void shrtimer_faultcfg_struct_para_init(shrtimer_faultcfg_parameter_struct * faultcfg);
/* configure the fault input */
void shrtimer_fault_config(uint32_t shrtimer_periph, uint32_t fault_id, shrtimer_faultcfg_parameter_struct* faultcfg);
/* configure the fault input digital filter clock division */
void shrtimer_fault_prescaler_config(uint32_t shrtimer_periph, uint32_t prescaler);
/* fault input enable */
void shrtimer_fault_input_enable(uint32_t shrtimer_periph, uint32_t fault_id);
/* fault input disable */
void shrtimer_fault_input_disable(uint32_t shrtimer_periph, uint32_t fault_id);

/* DMA configure functions */
/* enable the Master_TIMER and Slave_TIMER DMA request */
void shrtimer_timers_dma_enable(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t dmareq);
/* disable the Master_TIMER and Slave_TIMER DMA request */
void shrtimer_timers_dma_disable(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t dmareq);
/* configure the DMA mode for Master_TIMER or Slave_TIMER */
void shrtimer_dmamode_config(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t regupdate);

/* bunch mode configure functions */
/* initialize bunch mode configuration struct with a default value */
void shrtimer_bunchmode_struct_para_init(shrtimer_bunchmode_parameter_struct* bmcfg);
/* configure bunch mode for the SHRTIMER */
void shrtimer_bunchmode_config(uint32_t shrtimer_periph, shrtimer_bunchmode_parameter_struct* bmcfg);
/* enable the bunch mode */
void shrtimer_bunchmode_enable(uint32_t shrtimer_periph);
/* disable the bunch mode */
void shrtimer_bunchmode_disable(uint32_t shrtimer_periph);
/* get bunch mode operating flag */
uint32_t shrtimer_bunchmode_flag_get(uint32_t shrtimer_periph);
/* bunch mode started by software */
void shrtimer_bunchmode_software_start(uint32_t shrtimer_periph);

/* configure the capture functions in Slave_TIMER */
/* configure the capture source in Slave_TIMER */
void shrtimer_slavetimer_capture_config(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t capturex, uint32_t trgsource);
/* capture triggered by software in Slave_TIMER */
void shrtimer_slavetimer_capture_software(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t capturex);
/* read the capture value */
uint32_t shrtimer_slavetimer_capture_value_read(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t capturex);

/* ADC trigger configure functions */
/* initialize ADC trigger configuration struct with a default value */
void shrtimer_adctrigcfg_struct_para_init(shrtimer_adctrigcfg_parameter_struct* triggercfg);
/* configure the trigger source to ADC and the update source */
void shrtimer_adc_trigger_config(uint32_t shrtimer_periph, uint32_t trigger_id, shrtimer_adctrigcfg_parameter_struct* triggercfg);

/* TIMER interrupt and flag functions */
/* get the Master_TIMER and Slave_TIMER flag */
FlagStatus shrtimer_timers_flag_get(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t flag);
/* clear the Master_TIMER and Slave_TIMER flag */
void shrtimer_timers_flag_clear(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t flag);
/* get the common flag */
FlagStatus shrtimer_common_flag_get(uint32_t shrtimer_periph, uint32_t flag);
/* clear the common flag */
void shrtimer_common_flag_clear(uint32_t shrtimer_periph, uint32_t flag);
/* enable the Master_TIMER and Slave_TIMER interrupt */
void shrtimer_timers_interrupt_enable(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t interrupt);
/* disable the Master_TIMER and Slave_TIMER interrupt */
void shrtimer_timers_interrupt_disable(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t interrupt);
/* clear the Master_TIMER and Slave_TIMER interrupt flag */
FlagStatus shrtimer_timers_interrupt_flag_get(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t interrupt);
/* clear the Master_TIMER and Slave_TIMER interrupt flag */
void shrtimer_timers_interrupt_flag_clear(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t interrupt);
/* enable the common interrupt */
void shrtimer_common_interrupt_enable(uint32_t shrtimer_periph, uint32_t interrupt);
/* disable common interrupt */
void shrtimer_common_interrupt_disable(uint32_t shrtimer_periph, uint32_t interrupt);
/* clear the common interrupt flag */
FlagStatus shrtimer_common_interrupt_flag_get(uint32_t shrtimer_periph, uint32_t interrupt);
/* clear the common interrupt flag */
void shrtimer_common_interrupt_flag_clear(uint32_t shrtimer_periph, uint32_t interrupt);

#endif /* GD32E50X_SHRTIMER_H */
