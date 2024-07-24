/*!
    \file    gd32h7xx_syscfg.h
    \brief   definitions for the SYSCFG

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

#ifndef GD32H7XX_SYSCFG_H
#define GD32H7XX_SYSCFG_H

#include "gd32h7xx.h"

/* SYSCFG definitions */
#define SYSCFG                              SYSCFG_BASE                                 /*!< SYSCFG base address */

/* registers definitions */
#define SYSCFG_PMCFG                        REG32(SYSCFG + 0x00000004U)                 /*!< SYSCFG peripheral mode configuration register */
#define SYSCFG_EXTISS0                      REG32(SYSCFG + 0x00000008U)                 /*!< EXTI sources selection register 0 */
#define SYSCFG_EXTISS1                      REG32(SYSCFG + 0x0000000CU)                 /*!< EXTI sources selection register 1 */
#define SYSCFG_EXTISS2                      REG32(SYSCFG + 0x00000010U)                 /*!< EXTI sources selection register 2 */
#define SYSCFG_EXTISS3                      REG32(SYSCFG + 0x00000014U)                 /*!< EXTI sources selection register 3 */
#define SYSCFG_LKCTL                        REG32(SYSCFG + 0x00000018U)                 /*!< SYSCFG lock control register */
#define SYSCFG_CPSCTL                       REG32(SYSCFG + 0x00000020U)                 /*!< SYSCFG I/O compensation control register */
#define SYSCFG_CPSCCCFG                     REG32(SYSCFG + 0x00000028U)                 /*!< SYSCFG I/O compensation cell code configuration */
#define SYSCFG_TIMERCISEL0                  REG32(SYSCFG + 0x00000034U)                 /*!< SYSCFG timer input selection register 0 */
#define SYSCFG_TIMERCISEL1                  REG32(SYSCFG + 0x00000038U)                 /*!< SYSCFG timer input selection register 1 */
#define SYSCFG_TIMERCISEL2                  REG32(SYSCFG + 0x0000003CU)                 /*!< SYSCFG timer input selection register 2 */
#define SYSCFG_TIMERCISEL3                  REG32(SYSCFG + 0x00000040U)                 /*!< SYSCFG timer input selection register 3 */
#define SYSCFG_TIMERCISEL4                  REG32(SYSCFG + 0x00000044U)                 /*!< SYSCFG timer input selection register 4 */
#define SYSCFG_TIMERCISEL5                  REG32(SYSCFG + 0x00000048U)                 /*!< SYSCFG timer input selection register 5 */
#define SYSCFG_TIMERCISEL6                  REG32(SYSCFG + 0x0000004CU)                 /*!< SYSCFG timer input selection register 6 */
#define SYSCFG_CPUICAC                      REG32(SYSCFG + 0x00000054U)                 /*!< SYSCFG CPU icache error status register */
#define SYSCFG_CPUDCAC                      REG32(SYSCFG + 0x00000058U)                 /*!< SYSCFG CPU dcache error status register */
#define SYSCFG_FPUINTEN                     REG32(SYSCFG + 0x0000005CU)                 /*!< SYSCFG FPU interrupt enable register */
#define SYSCFG_SRAMCFG0                     REG32(SYSCFG + 0x00000064U)                 /*!< SYSCFG SRAM configuration register 0*/
#define SYSCFG_SRAMCFG1                     REG32(SYSCFG + 0x00000068U)                 /*!< SYSCFG SRAM configuration register 1*/
#define SYSCFG_USERCFG                      REG32(SYSCFG + 0x00000300U)                 /*!< SYSCFG user configuration register */

/* SYSCFG_PMCFG bits definitions */
#define SYSCFG_PMCFG_I2C0FMPEN              BIT(0)                                      /*!< I2C0 fast mode plus enable */
#define SYSCFG_PMCFG_I2C1FMPEN              BIT(1)                                      /*!< I2C1 fast mode plus enable */
#define SYSCFG_PMCFG_I2C2FMPEN              BIT(2)                                      /*!< I2C2 fast mode plus enable */
#define SYSCFG_PMCFG_I2C3FMPEN              BIT(3)                                      /*!< I2C3 fast mode plus enable */
#define SYSCFG_PMCFG_PB6FMPEN               BIT(4)                                      /*!< I2C fast mode plus on PB6 pin enable */
#define SYSCFG_PMCFG_PB7FMPEN               BIT(5)                                      /*!< I2C fast mode plus on PB7 pin enable */
#define SYSCFG_PMCFG_PB8FMPEN               BIT(6)                                      /*!< I2C fast mode plus on PB8 pin enable */
#define SYSCFG_PMCFG_PB9FMPEN               BIT(7)                                      /*!< I2C fast mode plus on PB9 pin enable */
#define SYSCFG_PMCFG_ENET1_PHY_SEL          BIT(22)                                     /*!< Ethernet1 PHY interface selection */
#define SYSCFG_PMCFG_ENET0_PHY_SEL          BIT(23)                                     /*!< Ethernet0 PHY interface selection */
#define SYSCFG_PMCFG_PA0SWON                BIT(24)                                     /*!< PA0 switch open */
#define SYSCFG_PMCFG_PA1SWON                BIT(25)                                     /*!< PA1 switch open */
#define SYSCFG_PMCFG_PC2SWON                BIT(26)                                     /*!< PC2 switch open */
#define SYSCFG_PMCFG_PC3SWON                BIT(27)                                     /*!< PC3 switch open */

/* SYSCFG_EXTISS0 bits definitions */
#define SYSCFG_EXTISS0_EXTI0_SS             BITS(0,3)                                   /*!< EXTI 0 configuration */
#define SYSCFG_EXTISS0_EXTI1_SS             BITS(4,7)                                   /*!< EXTI 1 configuration */
#define SYSCFG_EXTISS0_EXTI2_SS             BITS(8,11)                                  /*!< EXTI 2 configuration */
#define SYSCFG_EXTISS0_EXTI3_SS             BITS(12,15)                                 /*!< EXTI 3 configuration */

/* SYSCFG_EXTISS1 bits definitions */
#define SYSCFG_EXTISS1_EXTI4_SS             BITS(0,3)                                   /*!< EXTI 4 configuration */
#define SYSCFG_EXTISS1_EXTI5_SS             BITS(4,7)                                   /*!< EXTI 5 configuration */
#define SYSCFG_EXTISS1_EXTI6_SS             BITS(8,11)                                  /*!< EXTI 6 configuration */
#define SYSCFG_EXTISS1_EXTI7_SS             BITS(12,15)                                 /*!< EXTI 7 configuration */

/* SYSCFG_EXTISS2 bits definitions */
#define SYSCFG_EXTISS2_EXTI8_SS             BITS(0,3)                                   /*!< EXTI 8 configuration */
#define SYSCFG_EXTISS2_EXTI9_SS             BITS(4,7)                                   /*!< EXTI 9 configuration */
#define SYSCFG_EXTISS2_EXTI10_SS            BITS(8,11)                                  /*!< EXTI 10 configuration */
#define SYSCFG_EXTISS2_EXTI11_SS            BITS(12,15)                                 /*!< EXTI 11 configuration */

/* SYSCFG_EXTISS3 bits definitions */
#define SYSCFG_EXTISS3_EXTI12_SS            BITS(0,3)                                   /*!< EXTI 12 configuration */
#define SYSCFG_EXTISS3_EXTI13_SS            BITS(4,7)                                   /*!< EXTI 13 configuration */
#define SYSCFG_EXTISS3_EXTI14_SS            BITS(8,11)                                  /*!< EXTI 14 configuration */
#define SYSCFG_EXTISS3_EXTI15_SS            BITS(12,15)                                 /*!< EXTI 15 configuration */

/* SYSCFG_LKCTL bits definitions */
#define SYSCFG_LKCTL_LVD_LOCK              BIT(2)                                       /*!< programmable voltage detector lockup */
#define SYSCFG_LKCTL_CPU_LOCK              BIT(6)                                       /*!< CPU lockup */
#define SYSCFG_LKCTL_BKPRAM_LOCK           BIT(7)                                       /*!< Region 2 backup SRAM ECC double error lockup */
#define SYSCFG_LKCTL_SRAM1_LOCK            BIT(11)                                      /*!< Region 1 SRAM1 ECC double error lockup */
#define SYSCFG_LKCTL_SRAM0_LOCK            BIT(12)                                      /*!< Region 1 SRAM0 ECC double error lockup */
#define SYSCFG_LKCTL_DTCM_LOCK             BIT(13)                                      /*!< Region 0 DTCM ECC double error lock */
#define SYSCFG_LKCTL_ITCM_LOCK             BIT(14)                                      /*!< Region 0 ITCM-RAM ECC double error lock */
#define SYSCFG_LKCTL_AXIRAM_LOCK           BIT(15)                                      /*!< Region 0 AXI-SRAM ECC double error lock */

/* SYSCFG_CPSCTL bits definitions */
#define SYSCFG_CPSCTL_CPS_EN                BIT(0)                                      /*!< I/O compensation cell enable */
#define SYSCFG_CPSCTL_CPS_RDY               BIT(8)                                      /*!< Compensation cell ready flag */
#define SYSCFG_CPSCTL_IOSPDOP               BIT(16)                                     /*!< I/O speed optimization, high-speed at low-voltage */
#define SYSCFG_CPSCTL_IOLV                  BIT(23)                                     /*!< I/O in low voltage state */

/* SYSCFG_CPSCCCFG bits definitions */
#define SYSCFG_CPSCCCFG_NCPSCC              BITS(0,3)                                   /*!< NMOS compensation cell code */
#define SYSCFG_CPSCCCFG_PCPSCC              BITS(4,7)                                   /*!< PMOS compensation cell code */

/* SYSCFG_TIMERCISEL0 bits definitions */
#define SYSCFG_TIMER7_CI0_SEL               BITS(0,3)                                   /*!< selects TIMER7_CI0 input */
#define SYSCFG_TIMER7_CI1_SEL               BITS(4,7)                                   /*!< selects TIMER7_CI1 input */
#define SYSCFG_TIMER7_CI2_SEL               BITS(8,11)                                  /*!< selects TIMER7_CI2 input */
#define SYSCFG_TIMER7_CI3_SEL               BITS(12,15)                                 /*!< selects TIMER7_CI3 input */
#define SYSCFG_TIMER0_CI0_SEL               BITS(16,19)                                 /*!< selects TIMER0_CI0 input */
#define SYSCFG_TIMER0_CI1_SEL               BITS(20,23)                                 /*!< selects TIMER0_CI1 input */
#define SYSCFG_TIMER0_CI2_SEL               BITS(24,27)                                 /*!< selects TIMER0_CI2 input */
#define SYSCFG_TIMER0_CI3_SEL               BITS(28,31)                                 /*!< selects TIMER0_CI3 input */

/* SYSCFG_TIMERCISEL1 bits definitions */
#define SYSCFG_TIMER2_CI0_SEL               BITS(0,3)                                   /*!< selects TIMER2_CI0 input */
#define SYSCFG_TIMER2_CI1_SEL               BITS(4,7)                                   /*!< selects TIMER2_CI1 input */
#define SYSCFG_TIMER2_CI2_SEL               BITS(8,11)                                  /*!< selects TIMER2_CI2 input */
#define SYSCFG_TIMER2_CI3_SEL               BITS(12,15)                                 /*!< selects TIMER2_CI3 input */
#define SYSCFG_TIMER1_CI0_SEL               BITS(16,19)                                 /*!< selects TIMER1_CI0 input */
#define SYSCFG_TIMER1_CI1_SEL               BITS(20,23)                                 /*!< selects TIMER1_CI1 input */
#define SYSCFG_TIMER1_CI2_SEL               BITS(24,27)                                 /*!< selects TIMER1_CI2 input */
#define SYSCFG_TIMER1_CI3_SEL               BITS(28,31)                                 /*!< selects TIMER1_CI3 input */

/* SYSCFG_TIMERCISEL2 bits definitions */
#define SYSCFG_TIMER4_CI0_SEL               BITS(0,3)                                   /*!< selects TIMER4_CI0 input */
#define SYSCFG_TIMER4_CI1_SEL               BITS(4,7)                                   /*!< selects TIMER4_CI1 input */
#define SYSCFG_TIMER4_CI2_SEL               BITS(8,11)                                  /*!< selects TIMER4_CI2 input */
#define SYSCFG_TIMER4_CI3_SEL               BITS(12,15)                                 /*!< selects TIMER4_CI3 input */
#define SYSCFG_TIMER3_CI0_SEL               BITS(16,19)                                 /*!< selects TIMER3_CI0 input */
#define SYSCFG_TIMER3_CI1_SEL               BITS(20,23)                                 /*!< selects TIMER3_CI1 input */
#define SYSCFG_TIMER3_CI2_SEL               BITS(24,27)                                 /*!< selects TIMER3_CI2 input */
#define SYSCFG_TIMER3_CI3_SEL               BITS(28,31)                                 /*!< selects TIMER3_CI3 input */

/* SYSCFG_TIMERCISEL3 bits definitions */
#define SYSCFG_TIMER23_CI0_SEL              BITS(0,3)                                   /*!< selects TIMER23_CI0 input */
#define SYSCFG_TIMER23_CI1_SEL              BITS(4,7)                                   /*!< selects TIMER23_CI1 input */
#define SYSCFG_TIMER23_CI2_SEL              BITS(8,11)                                  /*!< selects TIMER23_CI2 input */
#define SYSCFG_TIMER23_CI3_SEL              BITS(12,15)                                 /*!< selects TIMER23_CI3 input */
#define SYSCFG_TIMER22_CI0_SEL              BITS(16,19)                                 /*!< selects TIMER22_CI0 input */
#define SYSCFG_TIMER22_CI1_SEL              BITS(20,23)                                 /*!< selects TIMER22_CI1 input */
#define SYSCFG_TIMER22_CI2_SEL              BITS(24,27)                                 /*!< selects TIMER22_CI2 input */
#define SYSCFG_TIMER22_CI3_SEL              BITS(28,31)                                 /*!< selects TIMER22_CI3 input */

/* SYSCFG_TIMERCISEL4 bits definitions */
#define SYSCFG_TIMER31_CI0_SEL              BITS(0,3)                                   /*!< selects TIMER31_CI0 input */
#define SYSCFG_TIMER31_CI1_SEL              BITS(4,7)                                   /*!< selects TIMER31_CI1 input */
#define SYSCFG_TIMER31_CI2_SEL              BITS(8,11)                                  /*!< selects TIMER31_CI2 input */
#define SYSCFG_TIMER31_CI3_SEL              BITS(12,15)                                 /*!< selects TIMER31_CI3 input */
#define SYSCFG_TIMER30_CI0_SEL              BITS(16,19)                                 /*!< selects TIMER30_CI0 input */
#define SYSCFG_TIMER30_CI1_SEL              BITS(20,23)                                 /*!< selects TIMER30_CI1 input */
#define SYSCFG_TIMER30_CI2_SEL              BITS(24,27)                                 /*!< selects TIMER30_CI2 input */
#define SYSCFG_TIMER30_CI3_SEL              BITS(28,31)                                 /*!< selects TIMER30_CI3 input */

/* SYSCFG_TIMERCISEL5 bits definitions */
#define SYSCFG_TIMER14_CI0_SEL              BITS(0,3)                                   /*!< selects TIMER14_CI0 input */
#define SYSCFG_TIMER14_CI1_SEL              BITS(4,7)                                   /*!< selects TIMER14_CI1 input */
#define SYSCFG_TIMER40_CI0_SEL              BITS(8,11)                                  /*!< selects TIMER40_CI0 input */
#define SYSCFG_TIMER40_CI1_SEL              BITS(12,15)                                 /*!< selects TIMER40_CI1 input */
#define SYSCFG_TIMER41_CI0_SEL              BITS(16,19)                                 /*!< selects TIMER41_CI0 input */
#define SYSCFG_TIMER41_CI1_SEL              BITS(20,23)                                 /*!< selects TIMER41_CI1 input */
#define SYSCFG_TIMER42_CI0_SEL              BITS(24,27)                                 /*!< selects TIMER42_CI0 input */
#define SYSCFG_TIMER42_CI1_SEL              BITS(28,31)                                 /*!< selects TIMER42_CI1 input */

/* SYSCFG_TIMERCISEL6 bits definitions */
#define SYSCFG_TIMER15_CI0_SEL              BITS(0,3)                                   /*!< selects TIMER15_CI0 input */
#define SYSCFG_TIMER16_CI0_SEL              BITS(4,7)                                   /*!< selects TIMER16_CI0 input */
#define SYSCFG_TIMER43_CI0_SEL              BITS(8,11)                                  /*!< selects TIMER43_CI0 input */
#define SYSCFG_TIMER43_CI1_SEL              BITS(12,15)                                 /*!< selects TIMER43_CI1 input */
#define SYSCFG_TIMER44_CI0_SEL              BITS(16,19)                                 /*!< selects TIMER44_CI0 input */
#define SYSCFG_TIMER44_CI1_SEL              BITS(20,23)                                 /*!< selects TIMER44_CI1 input */

/* CPU ICACHE error status bits definitions */
#define SYSCFG_CPUICAC_CPU_ICERR            BITS(6,27)                                  /*!< CPU ICACHE error bank information */
#define SYSCFG_CPUICAC_CPU_ICDET            BITS(28,31)                                 /*!< CPU ICACHE error detection information */

/* CPU DCACHE error status bits definitions */
#define SYSCFG_CPUDCAC_CPU_DCERR            BITS(6,27)                                  /*!< CPU DCACHE error bank information */
#define SYSCFG_CPUDCAC_CPU_DCDET            BITS(28,31)                                 /*!< CPU DCACHE error detection information */

/* floating point unit interrupt enable bits definitions */
#define SYSCFG_FPUINTEN_IOPIE               BIT(0)                                      /*!< invalid operation interrupt enable */
#define SYSCFG_FPUINTEN_DZIE                BIT(1)                                      /*!< divide-by-zero interrupt enable */
#define SYSCFG_FPUINTEN_UFIE                BIT(2)                                      /*!< underflow interrupt enable */
#define SYSCFG_FPUINTEN_OVFIE               BIT(3)                                      /*!< overflow interrupt enable */
#define SYSCFG_FPUINTEN_IDIE                BIT(4)                                      /*!< input abnormal interrupt enable */
#define SYSCFG_FPUINTEN_IXIE                BIT(5)                                      /*!< inexact interrupt enable */

/* SRAM configuration register 0 */
#define SYSCFG_SRAMCFG0_SECURE_SRAM_SIZE    BITS(0,1)                                   /*!< size of secure sram */

/* SRAM configuration register 1 */
#define SYSCFG_SRAMCFG1_TCM_WAITSTATE       BIT(0)                                      /*!< TCM wait state configuration */

/* TIMER trigger selection register */
#define SYSCFG_TIMERCFG_TSCFG0              BITS(0,4)                                   /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG1              BITS(5,9)                                   /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG2              BITS(10,14)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG3              BITS(16,20)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG4              BITS(21,25)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG5              BITS(26,30)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG6              BITS(0,4)                                   /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG7              BITS(5,9)                                   /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG8              BITS(10,14)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG9              BITS(16,20)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG10             BITS(21,25)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG11             BITS(26,30)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG12             BITS(0,4)                                   /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG13             BITS(5,9)                                   /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG14             BITS(10,14)                                 /*!< TIMER trigger selection */

/* SYSCFG_USERCFG bits definitions */
#define SYSCFG_USERCFG_BOR_TH               BITS(0,1)                                   /*!< BOR threshold status bits */
#define SYSCFG_USERCFG_BOOT_MODE            BITS(4,6)                                   /*!< BOOT mode */

/* constants definitions */
/* I2Cx fast mode plus enable definitions */
#define SYSCFG_I2C0_FMP                     SYSCFG_PMCFG_I2C0FMPEN                      /*!< I2C0 fast mode plus */
#define SYSCFG_I2C1_FMP                     SYSCFG_PMCFG_I2C1FMPEN                      /*!< I2C1 fast mode plus */
#define SYSCFG_I2C2_FMP                     SYSCFG_PMCFG_I2C2FMPEN                      /*!< I2C2 fast mode plus */
#define SYSCFG_I2C3_FMP                     SYSCFG_PMCFG_I2C3FMPEN                      /*!< I2C3 fast mode plus */
#define SYSCFG_I2C_FMP_PB6                  SYSCFG_PMCFG_PB6FMPEN                       /*!< I2C fast mode plus on PB6 pin */
#define SYSCFG_I2C_FMP_PB7                  SYSCFG_PMCFG_PB7FMPEN                       /*!< I2C fast mode plus on PB7 pin */
#define SYSCFG_I2C_FMP_PB8                  SYSCFG_PMCFG_PB8FMPEN                       /*!< I2C fast mode plus on PB8 pin */
#define SYSCFG_I2C_FMP_PB9                  SYSCFG_PMCFG_PB9FMPEN                       /*!< I2C fast mode plus on PB9 pin */

/* pin analog switch definitions */
#define SYSCFG_PA0_ANALOG_SWITCH            SYSCFG_PMCFG_PA0SWON                        /*!< PA0 analog switch */
#define SYSCFG_PA1_ANALOG_SWITCH            SYSCFG_PMCFG_PA1SWON                        /*!< PA1 analog switch */
#define SYSCFG_PC2_ANALOG_SWITCH            SYSCFG_PMCFG_PC2SWON                        /*!< PC2 analog switch */
#define SYSCFG_PC3_ANALOG_SWITCH            SYSCFG_PMCFG_PC3SWON                        /*!< PC3 analog switch */

/* Ethernet PHY mode definitions */
#define SYSCFG_ENET_PHY_MII                 ((uint32_t)0x00000000U)                      /*!< Ethernet PHY interface */
#define SYSCFG_ENET_PHY_RMII                ((uint32_t)0x00000001U)                      /*!< Ethernet PHY interface */

/* Ethernet 0 PHY interface selection */
#define ENET0_MEDIA_INTERFACE(regval)       (SYSCFG_PMCFG_ENET0_PHY_SEL & ((uint32_t)(regval) << 23U))
/* Ethernet 1 PHY interface selection */
#define ENET1_MEDIA_INTERFACE(regval)       (SYSCFG_PMCFG_ENET1_PHY_SEL & ((uint32_t)(regval) << 22U))

/* EXTI source select definitions */
#define EXTISS0                             ((uint8_t)0x00U)                            /*!< EXTI source select register 0 */
#define EXTISS1                             ((uint8_t)0x01U)                            /*!< EXTI source select register 1 */
#define EXTISS2                             ((uint8_t)0x02U)                            /*!< EXTI source select register 2 */
#define EXTISS3                             ((uint8_t)0x03U)                            /*!< EXTI source select register 3 */

/* EXTI source select mask bits definition */
#define EXTI_SS_MASK                        BITS(0,3)                                   /*!< EXTI source select mask */

/* EXTI source select jumping step definition */
#define EXTI_SS_JSTEP                       ((uint8_t)(0x04U))                          /*!< EXTI source select jumping step */

/* EXTI source select moving step definition */
#define EXTI_SS_MSTEP(pin)                  (EXTI_SS_JSTEP * ((pin) % EXTI_SS_JSTEP))   /*!< EXTI source select moving step */

/* EXTI source port definitions */
#define EXTI_SOURCE_GPIOA                   ((uint8_t)0x00U)                            /*!< EXTI GPIOA configuration */
#define EXTI_SOURCE_GPIOB                   ((uint8_t)0x01U)                            /*!< EXTI GPIOB configuration */
#define EXTI_SOURCE_GPIOC                   ((uint8_t)0x02U)                            /*!< EXTI GPIOC configuration */
#define EXTI_SOURCE_GPIOD                   ((uint8_t)0x03U)                            /*!< EXTI GPIOD configuration */
#define EXTI_SOURCE_GPIOE                   ((uint8_t)0x04U)                            /*!< EXTI GPIOE configuration */
#define EXTI_SOURCE_GPIOF                   ((uint8_t)0x05U)                            /*!< EXTI GPIOF configuration */
#define EXTI_SOURCE_GPIOG                   ((uint8_t)0x06U)                            /*!< EXTI GPIOG configuration */
#define EXTI_SOURCE_GPIOH                   ((uint8_t)0x07U)                            /*!< EXTI GPIOH configuration */
#define EXTI_SOURCE_GPIOJ                   ((uint8_t)0x09U)                            /*!< EXTI GPIOJ configuration */
#define EXTI_SOURCE_GPIOK                   ((uint8_t)0x0AU)                            /*!< EXTI GPIOK configuration */

/* EXTI source pin definitions */
#define EXTI_SOURCE_PIN0                    ((uint8_t)0x00U)                            /*!< EXTI GPIO pin0 configuration */
#define EXTI_SOURCE_PIN1                    ((uint8_t)0x01U)                            /*!< EXTI GPIO pin1 configuration */
#define EXTI_SOURCE_PIN2                    ((uint8_t)0x02U)                            /*!< EXTI GPIO pin2 configuration */
#define EXTI_SOURCE_PIN3                    ((uint8_t)0x03U)                            /*!< EXTI GPIO pin3 configuration */
#define EXTI_SOURCE_PIN4                    ((uint8_t)0x04U)                            /*!< EXTI GPIO pin4 configuration */
#define EXTI_SOURCE_PIN5                    ((uint8_t)0x05U)                            /*!< EXTI GPIO pin5 configuration */
#define EXTI_SOURCE_PIN6                    ((uint8_t)0x06U)                            /*!< EXTI GPIO pin6 configuration */
#define EXTI_SOURCE_PIN7                    ((uint8_t)0x07U)                            /*!< EXTI GPIO pin7 configuration */
#define EXTI_SOURCE_PIN8                    ((uint8_t)0x08U)                            /*!< EXTI GPIO pin8 configuration */
#define EXTI_SOURCE_PIN9                    ((uint8_t)0x09U)                            /*!< EXTI GPIO pin9 configuration */
#define EXTI_SOURCE_PIN10                   ((uint8_t)0x0AU)                            /*!< EXTI GPIO pin10 configuration */
#define EXTI_SOURCE_PIN11                   ((uint8_t)0x0BU)                            /*!< EXTI GPIO pin11 configuration */
#define EXTI_SOURCE_PIN12                   ((uint8_t)0x0CU)                            /*!< EXTI GPIO pin12 configuration */
#define EXTI_SOURCE_PIN13                   ((uint8_t)0x0DU)                            /*!< EXTI GPIO pin13 configuration */
#define EXTI_SOURCE_PIN14                   ((uint8_t)0x0EU)                            /*!< EXTI GPIO pin14 configuration */
#define EXTI_SOURCE_PIN15                   ((uint8_t)0x0FU)                            /*!< EXTI GPIO pin15 configuration */

/* MOS mode definitions */
#define PMOS_COMPENSATION                   ((uint8_t)0x00U)                            /*!< PMOS compensation */
#define NMOS_COMPENSATION                   ((uint8_t)0x01U)                            /*!< NMOS compensation */

/* timer input select definition */
#define TIMERCISEL0                         ((uint8_t)0x00U)                            /*!< TIMER input select register 0 */
#define TIMERCISEL1                         ((uint8_t)0x01U)                            /*!< TIMER input select register 1 */
#define TIMERCISEL2                         ((uint8_t)0x02U)                            /*!< TIMER input select register 2 */
#define TIMERCISEL3                         ((uint8_t)0x03U)                            /*!< TIMER input select register 3 */
#define TIMERCISEL4                         ((uint8_t)0x04U)                            /*!< TIMER input select register 4 */
#define TIMERCISEL5                         ((uint8_t)0x05U)                            /*!< TIMER input select register 5 */
#define TIMERCISEL6                         ((uint8_t)0x06U)                            /*!< TIMER input select register 6 */

/* define the timer bit position and its register index offset */
#define TIMER_REGIDX_BIT(regidx, bitpos, value)   (((uint32_t)(regidx) << 24U) | (uint32_t)((bitpos) << 16U)\
        | ((uint32_t)(value)))
#define TIMER_REG_INDEX(val)                (((uint32_t)(val) & 0xFF000000U) >> 24U)
#define TIMER_BIT_POS(val)                  (((uint32_t)(val) & 0x00FF0000U) >> 16U)
#define TIMER_SEL_VAL(val)                  ((uint32_t)(val) & 0x000000FFU)

/* TIMERx channel input select definitions */
typedef enum {
    TIMER7_CI0_INPUT_TIMER7_CH0         = TIMER_REGIDX_BIT(TIMERCISEL0, 0U, 0U),        /*!< select CMP1 output as TIMER7 CI0 */
    TIMER7_CI0_INPUT_CMP1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL0, 0U, 1U),        /*!< select TIMER7 CH0 as TIMER7 CI0 */
    TIMER7_CI1_INPUT_TIMER7_CH1         = TIMER_REGIDX_BIT(TIMERCISEL0, 4U, 0U),        /*!< select TIMER7 CH1 as TIMER7 CI1 */
    TIMER7_CI2_INPUT_TIMER7_CH2         = TIMER_REGIDX_BIT(TIMERCISEL0, 8U, 0U),        /*!< select TIMER7 CH2 as TIMER7 CI2 */
    TIMER7_CI3_INPUT_TIMER7_CH3         = TIMER_REGIDX_BIT(TIMERCISEL0, 12U, 0U),       /*!< select TIMER7 CH3 as TIMER7 CI3 */
    TIMER0_CI0_INPUT_TIMER0_CH0         = TIMER_REGIDX_BIT(TIMERCISEL0, 16U, 0U),       /*!< select CMP0 output as TIMER0 CI0 */
    TIMER0_CI0_INPUT_CMP0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL0, 16U, 1U),       /*!< select TIMER0 CH0 as TIMER0 CI0 */
    TIMER0_CI1_INPUT_TIMER0_CH1         = TIMER_REGIDX_BIT(TIMERCISEL0, 20U, 0U),       /*!< select TIMER0 CH1 as TIMER0 CI1 */
    TIMER0_CI2_INPUT_TIMER0_CH2         = TIMER_REGIDX_BIT(TIMERCISEL0, 24U, 0U),       /*!< select TIMER0 CH2 as TIMER0 CI2 */
    TIMER0_CI3_INPUT_TIMER0_CH3         = TIMER_REGIDX_BIT(TIMERCISEL0, 28U, 0U),       /*!< select TIMER0 CH3 as TIMER0 CI3 */
    TIMER2_CI0_INPUT_TIMER2_CH0         = TIMER_REGIDX_BIT(TIMERCISEL1, 0U, 0U),        /*!< select TIMER2 CH0 as TIMER2 CI0 */
    TIMER2_CI0_INPUT_CMP0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL1, 0U, 1U),        /*!< select CMP0 as TIMER2 CI0 */
    TIMER2_CI0_INPUT_CMP1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL1, 0U, 2U),        /*!< select CMP1 as TIMER2 CI0 */
    TIMER2_CI0_INPUT_CMP0_OR_CMP1_OUT   = TIMER_REGIDX_BIT(TIMERCISEL1, 0U, 3U),        /*!< select CMP0 or CMP1 as TIMER2 CI0 */
    TIMER2_CI1_INPUT_TIMER2_CH1         = TIMER_REGIDX_BIT(TIMERCISEL1, 4U, 0U),        /*!< select TIMER2 CH1 as TIMER2 CI1 */
    TIMER2_CI2_INPUT_TIMER2_CH2         = TIMER_REGIDX_BIT(TIMERCISEL1, 8U, 0U),        /*!< select TIMER2 CH2 as TIMER2 CI2 */
    TIMER2_CI3_INPUT_TIMER2_CH3         = TIMER_REGIDX_BIT(TIMERCISEL1, 12U, 0U),       /*!< select TIMER2 CH3 as TIMER2 CI3 */
    TIMER1_CI0_INPUT_TIMER1_CH0         = TIMER_REGIDX_BIT(TIMERCISEL1, 16U, 0U),       /*!< select TIMER1 CH0 as TIMER1 CI0 */
    TIMER1_CI1_INPUT_TIMER1_CH1         = TIMER_REGIDX_BIT(TIMERCISEL1, 20U, 0U),       /*!< select TIMER1 CH1 as TIMER1 CI1 */
    TIMER1_CI2_INPUT_TIMER1_CH2         = TIMER_REGIDX_BIT(TIMERCISEL1, 24U, 0U),       /*!< select TIMER1 CH2 as TIMER1 CI2 */
    TIMER1_CI3_INPUT_TIMER1_CH3         = TIMER_REGIDX_BIT(TIMERCISEL1, 28U, 0U),       /*!< select TIMER1 CH3 as TIMER1 CI3 */
    TIMER1_CI3_INPUT_CMP0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL1, 28U, 1U),       /*!< select CMP0 output as TIMER1 CI3 */
    TIMER1_CI3_INPUT_CMP1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL1, 28U, 2U),       /*!< select CMP1 output as TIMER1 CI3 */
    TIMER1_CI3_INPUT_CMP0_OR_CMP1_OUT   = TIMER_REGIDX_BIT(TIMERCISEL1, 28U, 3U),       /*!< select CMP0 or CMP1 output as TIMER1 CI3 */
    TIMER4_CI0_INPUT_TIMER4_CH0         = TIMER_REGIDX_BIT(TIMERCISEL2, 0U, 0U),        /*!< select TIMER4 CH0 as TIMER4 CI0 */
    TIMER4_CI1_INPUT_TIMER4_CH1         = TIMER_REGIDX_BIT(TIMERCISEL2, 4U, 0U),        /*!< select TIMER4 CH1 as TIMER4 CI1 */
    TIMER4_CI2_INPUT_TIMER4_CH2         = TIMER_REGIDX_BIT(TIMERCISEL2, 8U, 0U),        /*!< select TIMER4 CH2 as TIMER4 CI2 */
    TIMER4_CI3_INPUT_TIMER4_CH3         = TIMER_REGIDX_BIT(TIMERCISEL2, 12U, 0U),       /*!< select TIMER4 CH3 as TIMER4 CI3 */
    TIMER3_CI0_INPUT_TIMER3_CH0         = TIMER_REGIDX_BIT(TIMERCISEL2, 16U, 0U),       /*!< select TIMER3 CH0 as TIMER3 CI0 */
    TIMER3_CI1_INPUT_TIMER3_CH1         = TIMER_REGIDX_BIT(TIMERCISEL2, 20U, 0U),       /*!< select TIMER3 CH1 as TIMER3 CI1 */
    TIMER3_CI2_INPUT_TIMER3_CH2         = TIMER_REGIDX_BIT(TIMERCISEL2, 24U, 0U),       /*!< select TIMER3 CH2 as TIMER3 CI2 */
    TIMER3_CI3_INPUT_TIMER3_CH3         = TIMER_REGIDX_BIT(TIMERCISEL2, 28U, 0U),       /*!< select TIMER3 CH3 as TIMER3 CI3 */
    TIMER23_CI0_INPUT_TIMER23_CH0       = TIMER_REGIDX_BIT(TIMERCISEL3, 0U, 0U),        /*!< select TIMER23 CH0 as TIMER23 CI0 */
    TIMER23_CI1_INPUT_TIMER23_CH1       = TIMER_REGIDX_BIT(TIMERCISEL3, 4U, 0U),        /*!< select TIMER23 CH1 as TIMER23 CI1 */
    TIMER23_CI2_INPUT_TIMER23_CH2       = TIMER_REGIDX_BIT(TIMERCISEL3, 8U, 0U),        /*!< select TIMER23 CH2 as TIMER23 CI2 */
    TIMER23_CI3_INPUT_TIMER23_CH3       = TIMER_REGIDX_BIT(TIMERCISEL3, 12U, 0U),       /*!< select TIMER23 CH3 as TIMER23 CI3 */
    TIMER22_CI0_INPUT_TIMER22_CH0       = TIMER_REGIDX_BIT(TIMERCISEL3, 16U, 0U),       /*!< select TIMER22 CH0 as TIMER22 CI0 */
    TIMER22_CI1_INPUT_TIMER22_CH1       = TIMER_REGIDX_BIT(TIMERCISEL3, 20U, 0U),       /*!< select TIMER22 CH1 as TIMER22 CI1 */
    TIMER22_CI2_INPUT_TIMER22_CH2       = TIMER_REGIDX_BIT(TIMERCISEL3, 24U, 0U),       /*!< select TIMER22 CH2 as TIMER22 CI2 */
    TIMER22_CI3_INPUT_TIMER22_CH3       = TIMER_REGIDX_BIT(TIMERCISEL3, 28U, 0U),       /*!< select TIMER22 CH3 as TIMER22 CI3 */
    TIMER22_CI3_INPUT_CMP0_OUT          = TIMER_REGIDX_BIT(TIMERCISEL3, 28U, 1U),       /*!< select CMP0 output as TIMER22 CI3 */
    TIMER22_CI3_INPUT_CMP1_OUT          = TIMER_REGIDX_BIT(TIMERCISEL3, 28U, 2U),       /*!< select CMP1 output as TIMER22 CI3 */
    TIMER22_CI3_INPUT_CMP0_OR_CMP1_OUT  = TIMER_REGIDX_BIT(TIMERCISEL3, 28U, 3U),       /*!< select CMP0 or CMP1 output as TIMER22 CI3 */
    TIMER31_CI0_INPUT_TIMER31_CH0       = TIMER_REGIDX_BIT(TIMERCISEL4, 0U, 0U),        /*!< select TIMER31 CH0 as TIMER31 CI0 */
    TIMER31_CI0_INPUT_CMP0_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 0U, 1U),        /*!< select CMP0 output as TIMER31 CI0 */
    TIMER31_CI0_INPUT_CMP1_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 0U, 2U),        /*!< select CMP1 output as TIMER31 CI0 */
    TIMER31_CI0_INPUT_CMP0_OR_CMP1_OUT  = TIMER_REGIDX_BIT(TIMERCISEL4, 0U, 3U),        /*!< select CMP0 or CMP1 output as TIMER31 CI0 */
    TIMER31_CI1_INPUT_TIMER31_CH1       = TIMER_REGIDX_BIT(TIMERCISEL4, 4U, 0U),        /*!< select TIMER31 CH1 as TIMER31 CI1 */
    TIMER31_CI2_INPUT_TIMER31_CH2       = TIMER_REGIDX_BIT(TIMERCISEL4, 8U, 0U),        /*!< select TIMER31 CH2 as TIMER31 CI2 */
    TIMER31_CI3_INPUT_TIMER31_CH3       = TIMER_REGIDX_BIT(TIMERCISEL4, 12U, 0U),       /*!< select TIMER31 CH3 as TIMER31 CI3 */
    TIMER30_CI0_INPUT_TIMER30_CH0       = TIMER_REGIDX_BIT(TIMERCISEL4, 16U, 0U),       /*!< select TIMER30 CH0 as TIMER30 CI0 */
    TIMER30_CI0_INPUT_CMP0_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 16U, 1U),       /*!< select CMP0 output as TIMER30 CI0 */
    TIMER30_CI0_INPUT_CMP1_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 16U, 2U),       /*!< select CMP1 output as TIMER30 CI0 */
    TIMER30_CI0_INPUT_CMP0_OR_CMP1_OUT  = TIMER_REGIDX_BIT(TIMERCISEL4, 16U, 3U),       /*!< select CMP0 or CMP1 output as TIMER30 CI0 */
    TIMER30_CI1_INPUT_TIMER30_CH1       = TIMER_REGIDX_BIT(TIMERCISEL4, 20U, 0U),       /*!< select TIMER30 CH1 as TIMER30 CI1 */
    TIMER30_CI2_INPUT_TIMER30_CH2       = TIMER_REGIDX_BIT(TIMERCISEL4, 24U, 0U),       /*!< select TIMER30 CH2 as TIMER30 CI2 */
    TIMER30_CI3_INPUT_TIMER30_CH3       = TIMER_REGIDX_BIT(TIMERCISEL4, 28U, 0U),       /*!< select TIMER30 CH3 as TIMER30 CI3 */
    TIMER14_CI0_INPUT_TIMER14_CH0       = TIMER_REGIDX_BIT(TIMERCISEL5, 0U, 0U),        /*!< select TIMER14 CH0 as TIMER14 CI0 */
    TIMER14_CI0_INPUT_TIMER1_CH0        = TIMER_REGIDX_BIT(TIMERCISEL5, 0U, 1U),        /*!< select TIMER1 CH0 as TIMER14 CI0 */
    TIMER14_CI0_INPUT_TIMER2_CH0        = TIMER_REGIDX_BIT(TIMERCISEL5, 0U, 2U),        /*!< select TIMER2 CH0 as TIMER14 CI0 */
    TIMER14_CI0_INPUT_TIMER3_CH0        = TIMER_REGIDX_BIT(TIMERCISEL5, 0U, 3U),        /*!< select TIMER3 CH0 as TIMER14 CI0 */
    TIMER14_CI0_INPUT_LXTAL             = TIMER_REGIDX_BIT(TIMERCISEL5, 0U, 4U),        /*!< select LXTAL as TIMER14 CI0 */
    TIMER14_CI0_INPUT_LPIRC4M           = TIMER_REGIDX_BIT(TIMERCISEL5, 0U, 5U),        /*!< select LPIRC4M as TIMER14 CI0 */
    TIMER14_CI0_INPUT_CKOUT1            = TIMER_REGIDX_BIT(TIMERCISEL5, 0U, 6U),        /*!< select CKOUT1 as TIMER14 CI0 */
    TIMER14_CI1_INPUT_TIMER14_CH1       = TIMER_REGIDX_BIT(TIMERCISEL5, 4U, 0U),        /*!< select TIMER14 CH1 as TIMER14 CI1 */
    TIMER14_CI1_INPUT_TIMER1_CH1        = TIMER_REGIDX_BIT(TIMERCISEL5, 4U, 1U),        /*!< select TIMER1 CH1 as TIMER14 CI1 */
    TIMER14_CI1_INPUT_TIMER2_CH1        = TIMER_REGIDX_BIT(TIMERCISEL5, 4U, 2U),        /*!< select TIMER2 CH1 as TIMER14 CI1 */
    TIMER14_CI1_INPUT_TIMER3_CH1        = TIMER_REGIDX_BIT(TIMERCISEL5, 4U, 3U),        /*!< select TIMER3 CH1 as TIMER14 CI1 */
    TIMER40_CI0_INPUT_TIMER40_CH0       = TIMER_REGIDX_BIT(TIMERCISEL5, 8U, 0U),        /*!< select TIMER40 CH0 as TIMER40 CI0 */
    TIMER40_CI0_INPUT_TIMER2_CH0        = TIMER_REGIDX_BIT(TIMERCISEL5, 8U, 1U),        /*!< select TIMER2 CH0 as TIMER40 CI0 */
    TIMER40_CI0_INPUT_TIMER3_CH0        = TIMER_REGIDX_BIT(TIMERCISEL5, 8U, 2U),        /*!< select TIMER3 CH0 as TIMER40 CI0 */
    TIMER40_CI0_INPUT_TIMER4_CH0        = TIMER_REGIDX_BIT(TIMERCISEL5, 8U, 3U),        /*!< select TIMER4 CH0 as TIMER40 CI0 */
    TIMER40_CI0_INPUT_LXTAL             = TIMER_REGIDX_BIT(TIMERCISEL5, 8U, 4U),        /*!< select LXTAL as TIMER40 CI0 */
    TIMER40_CI0_INPUT_LPIRC4M           = TIMER_REGIDX_BIT(TIMERCISEL5, 8U, 5U),        /*!< select LPIRC4M as TIMER40 CI0 */
    TIMER40_CI0_INPUT_CKOUT1            = TIMER_REGIDX_BIT(TIMERCISEL5, 8U, 6U),        /*!< select CKOUT1 as TIMER40 CI0 */
    TIMER40_CI1_INPUT_TIMER40_CH1       = TIMER_REGIDX_BIT(TIMERCISEL5, 12U, 0U),       /*!< select TIMER40 CH1 as TIMER40 CI0 */
    TIMER40_CI1_INPUT_TIMER2_CH1        = TIMER_REGIDX_BIT(TIMERCISEL5, 12U, 1U),       /*!< select TIMER2 CH1 as TIMER40 CI0 */
    TIMER40_CI1_INPUT_TIMER3_CH1        = TIMER_REGIDX_BIT(TIMERCISEL5, 12U, 2U),       /*!< select TIMER3 CH1 as TIMER40 CI0 */
    TIMER40_CI1_INPUT_TIMER4_CH1        = TIMER_REGIDX_BIT(TIMERCISEL5, 12U, 3U),       /*!< select TIMER4 CH1 as TIMER40 CI0 */
    TIMER41_CI0_INPUT_TIMER41_CH0       = TIMER_REGIDX_BIT(TIMERCISEL5, 16U, 0U),       /*!< select TIMER41 CH0 as TIMER41 CI0 */
    TIMER41_CI0_INPUT_TIMER3_CH0        = TIMER_REGIDX_BIT(TIMERCISEL5, 16U, 1U),       /*!< select TIMER3 CH0 as TIMER41 CI0 */
    TIMER41_CI0_INPUT_TIMER4_CH0        = TIMER_REGIDX_BIT(TIMERCISEL5, 16U, 2U),       /*!< select TIMER4 CH0 as TIMER41 CI0 */
    TIMER41_CI0_INPUT_TIMER22_CH0       = TIMER_REGIDX_BIT(TIMERCISEL5, 16U, 3U),       /*!< select TIMER22 CH0 as TIMER41 CI0 */
    TIMER41_CI0_INPUT_LXTAL             = TIMER_REGIDX_BIT(TIMERCISEL5, 16U, 4U),       /*!< select LXTAL as TIMER41 CI0 */
    TIMER41_CI0_INPUT_LPIRC4M           = TIMER_REGIDX_BIT(TIMERCISEL5, 16U, 5U),       /*!< select LPIRC4M as TIMER41 CI0 */
    TIMER41_CI0_INPUT_CKOUT1            = TIMER_REGIDX_BIT(TIMERCISEL5, 16U, 6U),       /*!< select CKOUT1 as TIMER41 CI0 */
    TIMER41_CI1_INPUT_TIMER41_CH1       = TIMER_REGIDX_BIT(TIMERCISEL5, 20U, 0U),       /*!< select TIMER41 CH1 as TIMER41 CI1 */
    TIMER41_CI1_INPUT_TIMER3_CH1        = TIMER_REGIDX_BIT(TIMERCISEL5, 20U, 1U),       /*!< select TIMER3 CH1 as TIMER41 CI1 */
    TIMER41_CI1_INPUT_TIMER4_CH1        = TIMER_REGIDX_BIT(TIMERCISEL5, 20U, 2U),       /*!< select TIMER4 CH1 as TIMER41 CI1 */
    TIMER41_CI1_INPUT_TIMER22_CH1       = TIMER_REGIDX_BIT(TIMERCISEL5, 20U, 3U),       /*!< select TIMER22 CH1 as TIMER41 CI1 */
    TIMER42_CI0_INPUT_TIMER42_CH0       = TIMER_REGIDX_BIT(TIMERCISEL5, 24U, 0U),       /*!< select TIMER42 CH0 as TIMER42 CI0 */
    TIMER42_CI0_INPUT_TIMER4_CH0        = TIMER_REGIDX_BIT(TIMERCISEL5, 24U, 1U),       /*!< select TIMER4 CH0 as TIMER42 CI0 */
    TIMER42_CI0_INPUT_TIMER22_CH0       = TIMER_REGIDX_BIT(TIMERCISEL5, 24U, 2U),       /*!< select TIMER22 CH0 as TIMER42 CI0 */
    TIMER42_CI0_INPUT_TIMER23_CH0       = TIMER_REGIDX_BIT(TIMERCISEL5, 24U, 3U),       /*!< select TIMER23 CH0 as TIMER42 CI0 */
    TIMER42_CI0_INPUT_LXTAL             = TIMER_REGIDX_BIT(TIMERCISEL5, 24U, 4U),       /*!< select LXTAL as TIMER42 CI0 */
    TIMER42_CI0_INPUT_LPIRC4M           = TIMER_REGIDX_BIT(TIMERCISEL5, 24U, 5U),       /*!< select LPIRC4M as TIMER42 CI0 */
    TIMER42_CI0_INPUT_CKOUT1            = TIMER_REGIDX_BIT(TIMERCISEL5, 24U, 6U),       /*!< select CKOUT1 as TIMER42 CI0 */
    TIMER42_CI1_INPUT_TIMER42_CH1       = TIMER_REGIDX_BIT(TIMERCISEL5, 28U, 0U),       /*!< select TIMER42 CH1 as TIMER42 CI1 */
    TIMER42_CI1_INPUT_TIMER4_CH1        = TIMER_REGIDX_BIT(TIMERCISEL5, 28U, 1U),       /*!< select TIMER4 CH1 as TIMER42 CI1 */
    TIMER42_CI1_INPUT_TIMER22_CH1       = TIMER_REGIDX_BIT(TIMERCISEL5, 28U, 2U),       /*!< select TIMER22 CH1 as TIMER42 CI1 */
    TIMER42_CI1_INPUT_TIMER23_CH1       = TIMER_REGIDX_BIT(TIMERCISEL5, 28U, 3U),       /*!< select TIMER23 CH1 as TIMER42 CI1 */
    TIMER15_CI0_INPUT_TIMER15_CH0       = TIMER_REGIDX_BIT(TIMERCISEL6, 0U, 0U),        /*!< select TIMER15 CH0 as TIMER15 CI0 */
    TIMER15_CI0_INPUT_IRC32K            = TIMER_REGIDX_BIT(TIMERCISEL6, 0U, 1U),        /*!< select IRC32K as TIMER15 CI0 */
    TIMER15_CI0_INPUT_LXTAL             = TIMER_REGIDX_BIT(TIMERCISEL6, 0U, 2U),        /*!< select LXTAL as TIMER15 CI0 */
    TIMER15_CI0_INPUT_WKUP_IT           = TIMER_REGIDX_BIT(TIMERCISEL6, 0U, 3U),        /*!< select WKUP IT as TIMER15 CI0 */
    TIMER16_CI0_INPUT_TIMER16_CH0       = TIMER_REGIDX_BIT(TIMERCISEL6, 4U, 0U),        /*!< select TIMER16 CH0 as TIMER16 CI0 */
    TIMER16_CI0_INPUT_HXTAL_RTCDIV      = TIMER_REGIDX_BIT(TIMERCISEL6, 4U, 2U),        /*!< select HXTAL/RTCDIV 1M as TIMER16 CI0 */
    TIMER16_CI0_INPUT_CKOUT0            = TIMER_REGIDX_BIT(TIMERCISEL6, 4U, 3U),        /*!< select CKOUT0 as TIMER16 CI0 */
    TIMER43_CI0_INPUT_TIMER43_CH0       = TIMER_REGIDX_BIT(TIMERCISEL6, 8U, 0U),        /*!< select TIMER43 CH0 as TIMER43 CI0 */
    TIMER43_CI0_INPUT_TIMER22_CH0       = TIMER_REGIDX_BIT(TIMERCISEL6, 8U, 1U),        /*!< select TIMER22 CH0 as TIMER43 CI0 */
    TIMER43_CI0_INPUT_TIMER23_CH0       = TIMER_REGIDX_BIT(TIMERCISEL6, 8U, 2U),        /*!< select TIMER23 CH0 as TIMER43 CI0 */
    TIMER43_CI0_INPUT_TIMER30_CH0       = TIMER_REGIDX_BIT(TIMERCISEL6, 8U, 3U),        /*!< select TIMER30 CH0 as TIMER43 CI0 */
    TIMER43_CI0_INPUT_LXTAL             = TIMER_REGIDX_BIT(TIMERCISEL6, 8U, 4U),        /*!< select LXTAL as TIMER43 CI0 */
    TIMER43_CI0_INPUT_LPIRC4M           = TIMER_REGIDX_BIT(TIMERCISEL6, 8U, 5U),        /*!< select LPIRC4M as TIMER43 CI0 */
    TIMER43_CI0_INPUT_CKOUT1            = TIMER_REGIDX_BIT(TIMERCISEL6, 8U, 6U),        /*!< select CKOUT1 as TIMER43 CI0 */
    TIMER43_CI1_INPUT_TIMER43_CH1       = TIMER_REGIDX_BIT(TIMERCISEL6, 12U, 0U),       /*!< select TIMER43 CH1 as TIMER43 CI1 */
    TIMER43_CI1_INPUT_TIMER22_CH1       = TIMER_REGIDX_BIT(TIMERCISEL6, 12U, 1U),       /*!< select TIMER22 CH1 as TIMER43 CI1 */
    TIMER43_CI1_INPUT_TIMER23_CH1       = TIMER_REGIDX_BIT(TIMERCISEL6, 12U, 2U),       /*!< select TIMER23 CH1 as TIMER43 CI1 */
    TIMER43_CI1_INPUT_TIMER30_CH1       = TIMER_REGIDX_BIT(TIMERCISEL6, 12U, 3U),       /*!< select TIMER30 CH1 as TIMER43 CI1 */
    TIMER44_CI0_INPUT_TIMER44_CH0       = TIMER_REGIDX_BIT(TIMERCISEL6, 16U, 0U),       /*!< select TIMER44 CH0 as TIMER44 CI0 */
    TIMER44_CI0_INPUT_TIMER23_CH0       = TIMER_REGIDX_BIT(TIMERCISEL6, 16U, 1U),       /*!< select TIMER23 CH0 as TIMER44 CI0 */
    TIMER44_CI0_INPUT_TIMER30_CH0       = TIMER_REGIDX_BIT(TIMERCISEL6, 16U, 2U),       /*!< select TIMER30 CH0 as TIMER44 CI0 */
    TIMER44_CI0_INPUT_TIMER31_CH0       = TIMER_REGIDX_BIT(TIMERCISEL6, 16U, 3U),       /*!< select TIMER31 CH0 as TIMER44 CI0 */
    TIMER44_CI0_INPUT_LXTAL             = TIMER_REGIDX_BIT(TIMERCISEL6, 16U, 4U),       /*!< select LXTAL as TIMER44 CI0 */
    TIMER44_CI0_INPUT_LPIRC4M           = TIMER_REGIDX_BIT(TIMERCISEL6, 16U, 5U),       /*!< select LPIRC4M as TIMER44 CI0 */
    TIMER44_CI0_INPUT_CKOUT1            = TIMER_REGIDX_BIT(TIMERCISEL6, 16U, 6U),       /*!< select CKOUT1 as TIMER44 CI0 */
    TIMER44_CI1_INPUT_TIMER44_CH1       = TIMER_REGIDX_BIT(TIMERCISEL6, 20U, 0U),       /*!< select TIMER44 CH1 as TIMER44 CI1 */
    TIMER44_CI1_INPUT_TIMER23_CH1       = TIMER_REGIDX_BIT(TIMERCISEL6, 20U, 1U),       /*!< select TIMER23 CH1 as TIMER44 CI1 */
    TIMER44_CI1_INPUT_TIMER30_CH1       = TIMER_REGIDX_BIT(TIMERCISEL6, 20U, 2U),       /*!< select TIMER30 CH1 as TIMER44 CI1 */
    TIMER44_CI1_INPUT_TIMER31_CH1       = TIMER_REGIDX_BIT(TIMERCISEL6, 20U, 3U),       /*!< select TIMER31 CH1 as TIMER44 CI1 */
} timer_channel_input_enum;

/* timer tigger source select definition */
#define TIMER_SMCFG_TRGSEL_NONE             ((uint8_t)0x00U)                            /*!< trigger input is none */
#define TIMER_SMCFG_TRGSEL_ITI0             ((uint8_t)0x01U)                            /*!< internal trigger 0 */
#define TIMER_SMCFG_TRGSEL_ITI1             ((uint8_t)0x02U)                            /*!< internal trigger 1 */
#define TIMER_SMCFG_TRGSEL_ITI2             ((uint8_t)0x03U)                            /*!< internal trigger 2 */
#define TIMER_SMCFG_TRGSEL_ITI3             ((uint8_t)0x04U)                            /*!< internal trigger 3 */
#define TIMER_SMCFG_TRGSEL_CI0F_ED          ((uint8_t)0x05U)                            /*!< TI0 edge detector */
#define TIMER_SMCFG_TRGSEL_CI0FE0           ((uint8_t)0x06U)                            /*!< filtered TIMER input 0 */
#define TIMER_SMCFG_TRGSEL_CI1FE1           ((uint8_t)0x07U)                            /*!< filtered TIMER input 1 */
#define TIMER_SMCFG_TRGSEL_ETIFP            ((uint8_t)0x08U)                            /*!< external trigger */
#define TIMER_SMCFG_TRGSEL_CI2FE2           ((uint8_t)0x09U)                            /*!< filtered TIMER input 2 */
#define TIMER_SMCFG_TRGSEL_CI3FE3           ((uint8_t)0x0AU)                            /*!< filtered TIMER input 3 */
#define TIMER_SMCFG_TRGSEL_MCI0FEM0         ((uint8_t)0x0BU)                            /*!< filtered output of multi mode channel 0 */
#define TIMER_SMCFG_TRGSEL_MCI1FEM1         ((uint8_t)0x0CU)                            /*!< filtered output of multi mode channel 1 */
#define TIMER_SMCFG_TRGSEL_MCI2FEM2         ((uint8_t)0x0DU)                            /*!< filtered output of multi mode channel 2 */
#define TIMER_SMCFG_TRGSEL_MCI3FEM3         ((uint8_t)0x0EU)                            /*!< filtered output of multi mode channel 3 */
#define TIMER_SMCFG_TRGSEL_ITI12            ((uint8_t)0x11U)                            /*!< internal trigger input 12 */
#define TIMER_SMCFG_TRGSEL_ITI13            ((uint8_t)0x12U)                            /*!< internal trigger input 13 */
#define TIMER_SMCFG_TRGSEL_ITI14            ((uint8_t)0x13U)                            /*!< internal trigger input 14 */
#define TIMER_L0_SMCFG_TRGSEL_ITI4          ((uint8_t)0x09U)                            /*!< internal trigger 4 for General-L0 timer */
#define TIMER_L0_SMCFG_TRGSEL_ITI5          ((uint8_t)0x0AU)                            /*!< internal trigger 5 for General-L0 timer */
#define TIMER_L0_SMCFG_TRGSEL_ITI7          ((uint8_t)0x0CU)                            /*!< internal trigger 7 for General-L0 timer */
#define TIMER_L0_SMCFG_TRGSEL_ITI9          ((uint8_t)0x0EU)                            /*!< internal trigger 9 for General-L0 timer */
#define TIMER_L0_SMCFG_TRGSEL_ITI10         ((uint8_t)0x0FU)                            /*!< internal trigger 10 for General-L0 timer */
#define TIMER_L0_SMCFG_TRGSEL_ITI11         ((uint8_t)0x10U)                            /*!< internal trigger 11 for General-L0 timer */

/* timer tigger mode select definition */
#define TIMER_QUAD_DECODER_MODE0            ((uint8_t)0x00U)                            /*!< quadrature decoder mode 0 */
#define TIMER_QUAD_DECODER_MODE1            ((uint8_t)0x01U)                            /*!< quadrature decoder mode 1 */
#define TIMER_QUAD_DECODER_MODE2            ((uint8_t)0x02U)                            /*!< quadrature decoder mode 2 */
#define TIMER_SLAVE_MODE_RESTART            ((uint8_t)0x03U)                            /*!< restart mode */
#define TIMER_SLAVE_MODE_PAUSE              ((uint8_t)0x04U)                            /*!< pause mode */
#define TIMER_SLAVE_MODE_EVENT              ((uint8_t)0x05U)                            /*!< event mode */
#define TIMER_SLAVE_MODE_EXTERNAL0          ((uint8_t)0x06U)                            /*!< external clock mode 0 */
#define TIMER_SLAVE_MODE_RESTART_EVENT      ((uint8_t)0x07U)                            /*!< restart + event mode */
#define TIMER_NONQUAD_DECODER_MODE0         ((uint8_t)0x08U)                            /*!< non-quadrature decoder mode 0 */
#define TIMER_NONQUAD_DECODER_MODE1         ((uint8_t)0x09U)                            /*!< non-quadrature decoder mode 1 */
#define TIMER_SLAVE_MODE_DISABLE            ((uint8_t)0x0FU)                            /*!< slave mode disable */

#define SYSCFG_TIMERCFG0(syscfg_timerx)     REG32(SYSCFG + 0x100U + (syscfg_timerx) * 0x0CU)/*!< TIMERx configuration register */
#define SYSCFG_TIMERCFG1(syscfg_timerx)     REG32(SYSCFG + 0x104U + (syscfg_timerx) * 0x0CU)/*!< TIMERx configuration register */
#define SYSCFG_TIMERCFG2(syscfg_timerx)     REG32(SYSCFG + 0x108U + (syscfg_timerx) * 0x0CU)/*!< TIMERx configuration register */

#define SYSCFG_TIMER0                       ((uint8_t)0x00U)                            /*!< SYSCFG TIMER0 */
#define SYSCFG_TIMER1                       ((uint8_t)0x01U)                            /*!< SYSCFG TIMER1 */
#define SYSCFG_TIMER2                       ((uint8_t)0x02U)                            /*!< SYSCFG TIMER2 */
#define SYSCFG_TIMER3                       ((uint8_t)0x03U)                            /*!< SYSCFG TIMER3 */
#define SYSCFG_TIMER4                       ((uint8_t)0x04U)                            /*!< SYSCFG TIMER4 */
#define SYSCFG_TIMER7                       ((uint8_t)0x05U)                            /*!< SYSCFG TIMER5 */
#define SYSCFG_TIMER14                      ((uint8_t)0x06U)                            /*!< SYSCFG TIMER6 */
#define SYSCFG_TIMER22                      ((uint8_t)0x07U)                            /*!< SYSCFG TIMER7 */
#define SYSCFG_TIMER23                      ((uint8_t)0x08U)                            /*!< SYSCFG TIMER8 */
#define SYSCFG_TIMER30                      ((uint8_t)0x09U)                            /*!< SYSCFG TIMER9 */
#define SYSCFG_TIMER31                      ((uint8_t)0x0AU)                            /*!< SYSCFG TIMER10 */
#define SYSCFG_TIMER40                      ((uint8_t)0x0BU)                            /*!< SYSCFG TIMER11 */
#define SYSCFG_TIMER41                      ((uint8_t)0x0CU)                            /*!< SYSCFG TIMER12 */
#define SYSCFG_TIMER42                      ((uint8_t)0x0DU)                            /*!< SYSCFG TIMER13 */
#define SYSCFG_TIMER43                      ((uint8_t)0x0EU)                            /*!< SYSCFG TIMER14 */
#define SYSCFG_TIMER44                      ((uint8_t)0x0FU)                            /*!< SYSCFG TIMER15 */

/* TIMER input select mask bits definition */
#define TIMER_IS_MASK                        BITS(0,3)                                  /*!< TIMER source select mask */

/* CACHE mode definitions */
#define ICACHE_STATUS                       ((uint32_t)0x00000000U)                     /*!< select ICACHE */
#define DCACHE_STATUS                       ((uint32_t)0x00000001U)                     /*!< select DCACHE */

/* CACHE status definitions */
#define CPU_CACHE_ERROR_DETECTION           ((uint32_t)0x00000000U)                     /*!< select detection information */
#define CPU_CACHE_ERROR_BANK                ((uint32_t)0x00000001U)                     /*!< select error information */

/* Secure SRAM size definition */
#define SECURE_SRAM_SIZE_0KB                ((uint32_t)0x00000000U)                     /*!< secure SRAM size is 0KB */
#define SECURE_SRAM_SIZE_32KB               ((uint32_t)0x00000001U)                     /*!< secure SRAM size is 32KB */
#define SECURE_SRAM_SIZE_64KB               ((uint32_t)0x00000002U)                     /*!< secure SRAM size is 64KB */
#define SECURE_SRAM_SIZE_128KB              ((uint32_t)0x00000003U)                     /*!< secure SRAM size is 128KB */

/* I/O compensation cell enable/disable */
#define SYSCFG_IO_COMPENSATION_ENABLE       ((uint32_t)0x00000001U)                     /*!< I/O compensation cell enable */
#define SYSCFG_IO_COMPENSATION_DISABLE      ((uint32_t)0x00000000U)                     /*!< I/O compensation cell disable */

/* module lockup */
#define SYSCFG_LVD_LOCKUP                   SYSCFG_LKCTL_LVD_LOCK                       /*!< LVD signal connected */
#define SYSCFG_CPU_LOCKUP                   SYSCFG_LKCTL_CPU_LOCK                       /*!< CPU lockup signal connected */
#define SYSCFG_BKPRAM_LOCKUP                SYSCFG_LKCTL_BKPRAM_LOCK                    /*!< Region 2 backup SRAM ECC double error signal connected */
#define SYSCFG_SRAM1_LOCKUP                 SYSCFG_LKCTL_SRAM1_LOCK                     /*!< Region 1 SRAM1 ECC double error signal connected */
#define SYSCFG_SRAM0_LOCKUP                 SYSCFG_LKCTL_SRAM0_LOCK                     /*!< Region 1 SRAM0 ECC double error signal connected */
#define SYSCFG_DTCM_LOCKUP                  SYSCFG_LKCTL_DTCM_LOCK                      /*!< Region 0 DTCM ECC double error signal connected */
#define SYSCFG_ITCM_LOCKUP                  SYSCFG_LKCTL_ITCM_LOCK                      /*!< Region 0 ITCM-RAM ECC double error signal connected */
#define SYSCFG_AXIRAM_LOCKUP                SYSCFG_LKCTL_AXIRAM_LOCK                    /*!< Region 0 AXI-SRAM ECC double error signal connected */

/* SYSCFG compensation flag definitions */
#define SYSCFG_FLAG_IO_LOW_VOLTAGE          SYSCFG_CPSCTL_IOLV                          /*!< I/O in low voltage state flag, product supply voltage is working below 2.5V */
#define SYSCFG_FLAG_COMPENSATION_READY      SYSCFG_CPSCTL_CPS_RDY                       /*!< I/O compensation cell ready flag */

/* SYSCFG FPU interrupt definitions */
#define SYSCFG_FPUINT_INEXACT               SYSCFG_FPUINTEN_IXIE                        /*!< inexact interrupt */
#define SYSCFG_FPUINT_INPUT_ABNORMAL        SYSCFG_FPUINTEN_IDIE                        /*!< input abnormal interrupt */
#define SYSCFG_FPUINT_OVERFLOW              SYSCFG_FPUINTEN_OVFIE                       /*!< overflow interrupt */
#define SYSCFG_FPUINT_UNDERFLOW             SYSCFG_FPUINTEN_UFIE                        /*!< underflow interrupt */
#define SYSCFG_FPUINT_DIV0                  SYSCFG_FPUINTEN_DZIE                        /*!< divide-by-zero interrupt */
#define SYSCFG_FPUINT_INVALID_OPERATION     SYSCFG_FPUINTEN_IOPIE                       /*!< invalid operation interrupt */

/* BOOT modes definitions */
#define BOOT_SRAM                           ((uint32_t)0x00000000U)                     /*!< BOOT from SRAM (ITCM/DTCM/RAM shared/AXI SRAM) */
#define BOOT_SECURITY                       ((uint32_t)0x00000001U)                     /*!< BOOT from Security */
#define BOOT_SYSTEM                         ((uint32_t)0x00000002U)                     /*!< BOOT_SYS (BootLoader) */
#define BOOT_USER_FLASH                     ((uint32_t)0x00000003U)                     /*!< BOOT_USER (User flash OSPI0/1) */

/* BOR threshold level definitions */
#define BOR_OFF                             ((uint32_t)0x00000000U)                     /*!< no BOR function */
#define BOR_THRESHOLD_VAL1                  ((uint32_t)0x00000001U)                     /*!< BOR threshold value 1 */
#define BOR_THRESHOLD_VAL2                  ((uint32_t)0x00000002U)                     /*!< BOR threshold value 2 */
#define BOR_THRESHOLD_VAL3                  ((uint32_t)0x00000003U)                     /*!< BOR threshold value 3 */

/* function declarations */
/* initialization functions */
/* reset the SYSCFG registers */
void syscfg_deinit(void);

/* peripheral SYSCFG configuration functions */
/* enable I2Cx(x=0,1,2,3) fast mode plus or I2C fast mode plus PBx(x=6,7,8,9) */
void syscfg_i2c_fast_mode_plus_enable(uint32_t i2c_fmp);
/* disable I2Cx(x=0,1,2,3) fast mode plus or I2C fast mode plus PBx(x=6,7,8,9) */
void syscfg_i2c_fast_mode_plus_disable(uint32_t i2c_fmp);
/* open analog switch (Pxy_C and Pxy are separated pads) */
void syscfg_analog_switch_enable(uint32_t gpio_answ);
/* close analog switch (Pxy_C and Pxy are connected through the analog switch) */
void syscfg_analog_switch_disable(uint32_t gpio_answ);
/* configure the PHY interface for the Ethernet MAC */
void syscfg_enet_phy_interface_config(uint32_t ethernet, uint32_t phy_interface);
/* configure the GPIO pin as EXTI line */
void syscfg_exti_line_config(uint8_t exti_port, uint8_t exti_pin);
/* enable module lockup function (function can be disabled by system reset) */
void syscfg_lockup_enable(uint32_t lockup);
/* select timer channel input source */
void syscfg_timer_input_source_select(timer_channel_input_enum timer_input);

/* I/O compensation cell functions */
/* configure the I/O compensation cell */
void syscfg_io_compensation_config(uint32_t syscfg_cps);
/* enable I/O speed optimization, high-speed at low-voltage */
void syscfg_io_low_voltage_speed_optimization_enable(void);
/* disable I/O speed optimization, high-speed at low-voltage */
void syscfg_io_low_voltage_speed_optimization_disable(void);
/* set P/N MOS compensation value */
void syscfg_pnmos_compensation_code_set(uint32_t mos, uint32_t code);

/* secure and boot functions */
/* set secure SRAM size */
void syscfg_secure_sram_size_set(uint32_t size);
/* get secure SRAM size */
uint32_t syscfg_secure_sram_size_get(void);
/* get BOOT mode */
uint32_t syscfg_bootmode_get(void);
/* enable TCM wait state */
void syscfg_tcm_wait_state_enable(void);
/* disable TCM wait state */
void syscfg_tcm_wait_state_disable(void);

/* flag and interrupt functions */
/* FPU interrupt enable */
void syscfg_fpu_interrupt_enable(uint32_t fpu_int);
/* FPU interrupt disable */
void syscfg_fpu_interrupt_disable(uint32_t fpu_int);
/* get compensation cell flags */
FlagStatus syscfg_compensation_flag_get(uint32_t cps_flag);
/* get ICACHE or DCACHE status */
uint32_t syscfg_cpu_cache_status_get(uint32_t cache, uint32_t status);
/* get brownout reset threshold level */
uint32_t syscfg_brownout_reset_threshold_level_get(void);
#endif /* GD32H7XX_SYSCFG_H */
