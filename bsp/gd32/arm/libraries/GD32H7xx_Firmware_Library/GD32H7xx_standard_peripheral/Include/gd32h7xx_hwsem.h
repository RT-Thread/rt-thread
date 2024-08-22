/*!
    \file    gd32h7xx_hwsem.h
    \brief   definitions for the HWSEM

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

#ifndef GD32H7XX_HWSEM_H
#define GD32H7XX_HWSEM_H

#include "gd32h7xx.h"

/* HWSEM definitions */
#define HWSEM                      HWSEM_BASE                              /*!< HWSEM base address */

/* registers definitions */
#define HWSEM_CTL0                 REG32(HWSEM + 0x00000000U)              /*!< HWSEM control register 0 */
#define HWSEM_CTL1                 REG32(HWSEM + 0x00000004U)              /*!< HWSEM control register 1 */
#define HWSEM_CTL2                 REG32(HWSEM + 0x00000008U)              /*!< HWSEM control register 2 */
#define HWSEM_CTL3                 REG32(HWSEM + 0x0000000CU)              /*!< HWSEM control register 3 */
#define HWSEM_CTL4                 REG32(HWSEM + 0x00000010U)              /*!< HWSEM control register 4 */
#define HWSEM_CTL5                 REG32(HWSEM + 0x00000014U)              /*!< HWSEM control register 5 */
#define HWSEM_CTL6                 REG32(HWSEM + 0x00000018U)              /*!< HWSEM control register 6 */
#define HWSEM_CTL7                 REG32(HWSEM + 0x0000001CU)              /*!< HWSEM control register 7 */
#define HWSEM_CTL8                 REG32(HWSEM + 0x00000020U)              /*!< HWSEM control register 8 */
#define HWSEM_CTL9                 REG32(HWSEM + 0x00000024U)              /*!< HWSEM control register 9 */
#define HWSEM_CTL10                REG32(HWSEM + 0x00000028U)              /*!< HWSEM control register 10 */
#define HWSEM_CTL11                REG32(HWSEM + 0x0000002CU)              /*!< HWSEM control register 11 */
#define HWSEM_CTL12                REG32(HWSEM + 0x00000030U)              /*!< HWSEM control register 12 */
#define HWSEM_CTL13                REG32(HWSEM + 0x00000034U)              /*!< HWSEM control register 13 */
#define HWSEM_CTL14                REG32(HWSEM + 0x00000038U)              /*!< HWSEM control register 14 */
#define HWSEM_CTL15                REG32(HWSEM + 0x0000003CU)              /*!< HWSEM control register 15 */
#define HWSEM_CTL16                REG32(HWSEM + 0x00000040U)              /*!< HWSEM control register 16 */
#define HWSEM_CTL17                REG32(HWSEM + 0x00000044U)              /*!< HWSEM control register 17 */
#define HWSEM_CTL18                REG32(HWSEM + 0x00000048U)              /*!< HWSEM control register 18 */
#define HWSEM_CTL19                REG32(HWSEM + 0x0000004CU)              /*!< HWSEM control register 19 */
#define HWSEM_CTL20                REG32(HWSEM + 0x00000050U)              /*!< HWSEM control register 20 */
#define HWSEM_CTL21                REG32(HWSEM + 0x00000054U)              /*!< HWSEM control register 21 */
#define HWSEM_CTL22                REG32(HWSEM + 0x00000058U)              /*!< HWSEM control register 22 */
#define HWSEM_CTL23                REG32(HWSEM + 0x0000005CU)              /*!< HWSEM control register 23 */
#define HWSEM_CTL24                REG32(HWSEM + 0x00000060U)              /*!< HWSEM control register 24 */
#define HWSEM_CTL25                REG32(HWSEM + 0x00000064U)              /*!< HWSEM control register 25 */
#define HWSEM_CTL26                REG32(HWSEM + 0x00000068U)              /*!< HWSEM control register 26 */
#define HWSEM_CTL27                REG32(HWSEM + 0x0000006CU)              /*!< HWSEM control register 27 */
#define HWSEM_CTL28                REG32(HWSEM + 0x00000070U)              /*!< HWSEM control register 28 */
#define HWSEM_CTL29                REG32(HWSEM + 0x00000074U)              /*!< HWSEM control register 29 */
#define HWSEM_CTL30                REG32(HWSEM + 0x00000078U)              /*!< HWSEM control register 30 */
#define HWSEM_CTL31                REG32(HWSEM + 0x0000007CU)              /*!< HWSEM control register 31 */
#define HWSEM_RLK0                 REG32(HWSEM + 0x00000080U)              /*!< HWSEM read lock register 0 */
#define HWSEM_RLK1                 REG32(HWSEM + 0x00000084U)              /*!< HWSEM read lock register 1 */
#define HWSEM_RLK2                 REG32(HWSEM + 0x00000088U)              /*!< HWSEM read lock register 2 */
#define HWSEM_RLK3                 REG32(HWSEM + 0x0000008CU)              /*!< HWSEM read lock register 3 */
#define HWSEM_RLK4                 REG32(HWSEM + 0x00000090U)              /*!< HWSEM read lock register 4 */
#define HWSEM_RLK5                 REG32(HWSEM + 0x00000094U)              /*!< HWSEM read lock register 5 */
#define HWSEM_RLK6                 REG32(HWSEM + 0x00000098U)              /*!< HWSEM read lock register 6 */
#define HWSEM_RLK7                 REG32(HWSEM + 0x0000009CU)              /*!< HWSEM read lock register 7 */
#define HWSEM_RLK8                 REG32(HWSEM + 0x000000A0U)              /*!< HWSEM read lock register 8 */
#define HWSEM_RLK9                 REG32(HWSEM + 0x000000A4U)              /*!< HWSEM read lock register 9 */
#define HWSEM_RLK10                REG32(HWSEM + 0x000000A8U)              /*!< HWSEM read lock register 10 */
#define HWSEM_RLK11                REG32(HWSEM + 0x000000ACU)              /*!< HWSEM read lock register 11 */
#define HWSEM_RLK12                REG32(HWSEM + 0x000000B0U)              /*!< HWSEM read lock register 12 */
#define HWSEM_RLK13                REG32(HWSEM + 0x000000B4U)              /*!< HWSEM read lock register 13 */
#define HWSEM_RLK14                REG32(HWSEM + 0x000000B8U)              /*!< HWSEM read lock register 14 */
#define HWSEM_RLK15                REG32(HWSEM + 0x000000BCU)              /*!< HWSEM read lock register 15 */
#define HWSEM_RLK16                REG32(HWSEM + 0x000000C0U)              /*!< HWSEM read lock register 16 */
#define HWSEM_RLK17                REG32(HWSEM + 0x000000C4U)              /*!< HWSEM read lock register 17 */
#define HWSEM_RLK18                REG32(HWSEM + 0x000000C8U)              /*!< HWSEM read lock register 18 */
#define HWSEM_RLK19                REG32(HWSEM + 0x000000CCU)              /*!< HWSEM read lock register 19 */
#define HWSEM_RLK20                REG32(HWSEM + 0x000000D0U)              /*!< HWSEM read lock register 20 */
#define HWSEM_RLK21                REG32(HWSEM + 0x000000D4U)              /*!< HWSEM read lock register 21 */
#define HWSEM_RLK22                REG32(HWSEM + 0x000000D8U)              /*!< HWSEM read lock register 22 */
#define HWSEM_RLK23                REG32(HWSEM + 0x000000DCU)              /*!< HWSEM read lock register 23 */
#define HWSEM_RLK24                REG32(HWSEM + 0x000000E0U)              /*!< HWSEM read lock register 24 */
#define HWSEM_RLK25                REG32(HWSEM + 0x000000E4U)              /*!< HWSEM read lock register 25 */
#define HWSEM_RLK26                REG32(HWSEM + 0x000000E8U)              /*!< HWSEM read lock register 26 */
#define HWSEM_RLK27                REG32(HWSEM + 0x000000ECU)              /*!< HWSEM read lock register 27 */
#define HWSEM_RLK28                REG32(HWSEM + 0x000000F0U)              /*!< HWSEM read lock register 28 */
#define HWSEM_RLK29                REG32(HWSEM + 0x000000F4U)              /*!< HWSEM read lock register 29 */
#define HWSEM_RLK30                REG32(HWSEM + 0x000000F8U)              /*!< HWSEM read lock register 30 */
#define HWSEM_RLK31                REG32(HWSEM + 0x000000FCU)              /*!< HWSEM read lock register 31 */
#define HWSEM_INTEN                REG32(HWSEM + 0x00000100U)              /*!< HWSEM interrupt enable register */
#define HWSEM_INTC                 REG32(HWSEM + 0x00000104U)              /*!< HWSEM interrupt flag clear register */
#define HWSEM_STAT                 REG32(HWSEM + 0x00000108U)              /*!< HWSEM status register */
#define HWSEM_INTF                 REG32(HWSEM + 0x0000010CU)              /*!< HWSEM interrupt flag register */
#define HWSEM_UNLK                 REG32(HWSEM + 0x00000140U)              /*!< HWSEM unlock register */
#define HWSEM_KEY                  REG32(HWSEM + 0x00000144U)              /*!< HWSEM key register */

/* bits definitions */
/* HWSEM_CTLx, x=0..31 */
#define HWSEM_CTL_PID              BITS(0,7)                               /*!< HWSEM process ID */
#define HWSEM_CTL_MID              BITS(8,11)                              /*!< HWSEM master ID */
#define HWSEM_CTL_LK               BIT(31)                                 /*!< HWSEM lock */

/* HWSEM_RLKx, x=0..31 */
#define HWSEM_RLK_PID              BITS(0,7)                               /*!< HWSEM read lock register process ID */
#define HWSEM_RLK_MID              BITS(8,11)                              /*!< HWSEM read lock register master ID */
#define HWSEM_RLK_LK               BIT(31)                                 /*!< HWSEM read lock register lock */

/* HWSEM_INTEN */
#define HWSEM_INTEN_SIE0           BIT(0)                                  /*!< enable HWSEM interrupt for semaphore 0 */
#define HWSEM_INTEN_SIE1           BIT(1)                                  /*!< enable HWSEM interrupt for semaphore 1 */
#define HWSEM_INTEN_SIE2           BIT(2)                                  /*!< enable HWSEM interrupt for semaphore 2 */
#define HWSEM_INTEN_SIE3           BIT(3)                                  /*!< enable HWSEM interrupt for semaphore 3 */
#define HWSEM_INTEN_SIE4           BIT(4)                                  /*!< enable HWSEM interrupt for semaphore 4 */
#define HWSEM_INTEN_SIE5           BIT(5)                                  /*!< enable HWSEM interrupt for semaphore 5 */
#define HWSEM_INTEN_SIE6           BIT(6)                                  /*!< enable HWSEM interrupt for semaphore 6 */
#define HWSEM_INTEN_SIE7           BIT(7)                                  /*!< enable HWSEM interrupt for semaphore 7 */
#define HWSEM_INTEN_SIE8           BIT(8)                                  /*!< enable HWSEM interrupt for semaphore 8 */
#define HWSEM_INTEN_SIE9           BIT(9)                                  /*!< enable HWSEM interrupt for semaphore 9 */
#define HWSEM_INTEN_SIE10          BIT(10)                                 /*!< enable HWSEM interrupt for semaphore 10 */
#define HWSEM_INTEN_SIE11          BIT(11)                                 /*!< enable HWSEM interrupt for semaphore 11 */
#define HWSEM_INTEN_SIE12          BIT(12)                                 /*!< enable HWSEM interrupt for semaphore 12 */
#define HWSEM_INTEN_SIE13          BIT(13)                                 /*!< enable HWSEM interrupt for semaphore 13 */
#define HWSEM_INTEN_SIE14          BIT(14)                                 /*!< enable HWSEM interrupt for semaphore 14 */
#define HWSEM_INTEN_SIE15          BIT(15)                                 /*!< enable HWSEM interrupt for semaphore 15 */
#define HWSEM_INTEN_SIE16          BIT(16)                                 /*!< enable HWSEM interrupt for semaphore 16 */
#define HWSEM_INTEN_SIE17          BIT(17)                                 /*!< enable HWSEM interrupt for semaphore 17 */
#define HWSEM_INTEN_SIE18          BIT(18)                                 /*!< enable HWSEM interrupt for semaphore 18 */
#define HWSEM_INTEN_SIE19          BIT(19)                                 /*!< enable HWSEM interrupt for semaphore 19 */
#define HWSEM_INTEN_SIE20          BIT(20)                                 /*!< enable HWSEM interrupt for semaphore 20 */
#define HWSEM_INTEN_SIE21          BIT(21)                                 /*!< enable HWSEM interrupt for semaphore 21 */
#define HWSEM_INTEN_SIE22          BIT(22)                                 /*!< enable HWSEM interrupt for semaphore 22 */
#define HWSEM_INTEN_SIE23          BIT(23)                                 /*!< enable HWSEM interrupt for semaphore 23 */
#define HWSEM_INTEN_SIE24          BIT(24)                                 /*!< enable HWSEM interrupt for semaphore 24 */
#define HWSEM_INTEN_SIE25          BIT(25)                                 /*!< enable HWSEM interrupt for semaphore 25 */
#define HWSEM_INTEN_SIE26          BIT(26)                                 /*!< enable HWSEM interrupt for semaphore 26 */
#define HWSEM_INTEN_SIE27          BIT(27)                                 /*!< enable HWSEM interrupt for semaphore 27 */
#define HWSEM_INTEN_SIE28          BIT(28)                                 /*!< enable HWSEM interrupt for semaphore 28 */
#define HWSEM_INTEN_SIE29          BIT(29)                                 /*!< enable HWSEM interrupt for semaphore 29 */
#define HWSEM_INTEN_SIE30          BIT(30)                                 /*!< enable HWSEM interrupt for semaphore 30 */
#define HWSEM_INTEN_SIE31          BIT(31)                                 /*!< enable HWSEM interrupt for semaphore 31 */

/* HWSEM_INTC */
#define HWSEM_INTC_SIFC0           BIT(0)                                  /*!< clear semaphore 0 flag and interrupt flag */
#define HWSEM_INTC_SIFC1           BIT(1)                                  /*!< clear semaphore 1 flag and interrupt flag */
#define HWSEM_INTC_SIFC2           BIT(2)                                  /*!< clear semaphore 2 flag and interrupt flag */
#define HWSEM_INTC_SIFC3           BIT(3)                                  /*!< clear semaphore 3 flag and interrupt flag */
#define HWSEM_INTC_SIFC4           BIT(4)                                  /*!< clear semaphore 4 flag and interrupt flag */
#define HWSEM_INTC_SIFC5           BIT(5)                                  /*!< clear semaphore 5 flag and interrupt flag */
#define HWSEM_INTC_SIFC6           BIT(6)                                  /*!< clear semaphore 6 flag and interrupt flag */
#define HWSEM_INTC_SIFC7           BIT(7)                                  /*!< clear semaphore 7 flag and interrupt flag */
#define HWSEM_INTC_SIFC8           BIT(8)                                  /*!< clear semaphore 8 flag and interrupt flag */
#define HWSEM_INTC_SIFC9           BIT(9)                                  /*!< clear semaphore 9 flag and interrupt flag */
#define HWSEM_INTC_SIFC10          BIT(10)                                 /*!< clear semaphore 10 flag and interrupt flag */
#define HWSEM_INTC_SIFC11          BIT(11)                                 /*!< clear semaphore 11 flag and interrupt flag */
#define HWSEM_INTC_SIFC12          BIT(12)                                 /*!< clear semaphore 12 flag and interrupt flag */
#define HWSEM_INTC_SIFC13          BIT(13)                                 /*!< clear semaphore 13 flag and interrupt flag */
#define HWSEM_INTC_SIFC14          BIT(14)                                 /*!< clear semaphore 14 flag and interrupt flag */
#define HWSEM_INTC_SIFC15          BIT(15)                                 /*!< clear semaphore 15 flag and interrupt flag */
#define HWSEM_INTC_SIFC16          BIT(16)                                 /*!< clear semaphore 16 flag and interrupt flag */
#define HWSEM_INTC_SIFC17          BIT(17)                                 /*!< clear semaphore 17 flag and interrupt flag */
#define HWSEM_INTC_SIFC18          BIT(18)                                 /*!< clear semaphore 18 flag and interrupt flag */
#define HWSEM_INTC_SIFC19          BIT(19)                                 /*!< clear semaphore 19 flag and interrupt flag */
#define HWSEM_INTC_SIFC20          BIT(20)                                 /*!< clear semaphore 20 flag and interrupt flag */
#define HWSEM_INTC_SIFC21          BIT(21)                                 /*!< clear semaphore 21 flag and interrupt flag */
#define HWSEM_INTC_SIFC22          BIT(22)                                 /*!< clear semaphore 22 flag and interrupt flag */
#define HWSEM_INTC_SIFC23          BIT(23)                                 /*!< clear semaphore 23 flag and interrupt flag */
#define HWSEM_INTC_SIFC24          BIT(24)                                 /*!< clear semaphore 24 flag and interrupt flag */
#define HWSEM_INTC_SIFC25          BIT(25)                                 /*!< clear semaphore 25 flag and interrupt flag */
#define HWSEM_INTC_SIFC26          BIT(26)                                 /*!< clear semaphore 26 flag and interrupt flag */
#define HWSEM_INTC_SIFC27          BIT(27)                                 /*!< clear semaphore 27 flag and interrupt flag */
#define HWSEM_INTC_SIFC28          BIT(28)                                 /*!< clear semaphore 28 flag and interrupt flag */
#define HWSEM_INTC_SIFC29          BIT(29)                                 /*!< clear semaphore 29 flag and interrupt flag */
#define HWSEM_INTC_SIFC30          BIT(30)                                 /*!< clear semaphore 30 flag and interrupt flag */
#define HWSEM_INTC_SIFC31          BIT(31)                                 /*!< clear semaphore 31 flag and interrupt flag */

/* HWSEM_STAT */
#define HWSEM_STAT_SF0             BIT(0)                                  /*!< semaphore 0 unlock event occurs */
#define HWSEM_STAT_SF1             BIT(1)                                  /*!< semaphore 1 unlock event occurs */
#define HWSEM_STAT_SF2             BIT(2)                                  /*!< semaphore 2 unlock event occurs */
#define HWSEM_STAT_SF3             BIT(3)                                  /*!< semaphore 3 unlock event occurs */
#define HWSEM_STAT_SF4             BIT(4)                                  /*!< semaphore 4 unlock event occurs */
#define HWSEM_STAT_SF5             BIT(5)                                  /*!< semaphore 5 unlock event occurs */
#define HWSEM_STAT_SF6             BIT(6)                                  /*!< semaphore 6 unlock event occurs */
#define HWSEM_STAT_SF7             BIT(7)                                  /*!< semaphore 7 unlock event occurs */
#define HWSEM_STAT_SF8             BIT(8)                                  /*!< semaphore 8 unlock event occurs */
#define HWSEM_STAT_SF9             BIT(9)                                  /*!< semaphore 9 unlock event occurs */
#define HWSEM_STAT_SF10            BIT(10)                                 /*!< semaphore 10 unlock event occurs */
#define HWSEM_STAT_SF11            BIT(11)                                 /*!< semaphore 11 unlock event occurs */
#define HWSEM_STAT_SF12            BIT(12)                                 /*!< semaphore 12 unlock event occurs */
#define HWSEM_STAT_SF13            BIT(13)                                 /*!< semaphore 13 unlock event occurs */
#define HWSEM_STAT_SF14            BIT(14)                                 /*!< semaphore 14 unlock event occurs */
#define HWSEM_STAT_SF15            BIT(15)                                 /*!< semaphore 15 unlock event occurs */
#define HWSEM_STAT_SF16            BIT(16)                                 /*!< semaphore 16 unlock event occurs */
#define HWSEM_STAT_SF17            BIT(17)                                 /*!< semaphore 17 unlock event occurs */
#define HWSEM_STAT_SF18            BIT(18)                                 /*!< semaphore 18 unlock event occurs */
#define HWSEM_STAT_SF19            BIT(19)                                 /*!< semaphore 19 unlock event occurs */
#define HWSEM_STAT_SF20            BIT(20)                                 /*!< semaphore 20 unlock event occurs */
#define HWSEM_STAT_SF21            BIT(21)                                 /*!< semaphore 21 unlock event occurs */
#define HWSEM_STAT_SF22            BIT(22)                                 /*!< semaphore 22 unlock event occurs */
#define HWSEM_STAT_SF23            BIT(23)                                 /*!< semaphore 23 unlock event occurs */
#define HWSEM_STAT_SF24            BIT(24)                                 /*!< semaphore 24 unlock event occurs */
#define HWSEM_STAT_SF25            BIT(25)                                 /*!< semaphore 25 unlock event occurs */
#define HWSEM_STAT_SF26            BIT(26)                                 /*!< semaphore 26 unlock event occurs */
#define HWSEM_STAT_SF27            BIT(27)                                 /*!< semaphore 27 unlock event occurs */
#define HWSEM_STAT_SF28            BIT(28)                                 /*!< semaphore 28 unlock event occurs */
#define HWSEM_STAT_SF29            BIT(29)                                 /*!< semaphore 29 unlock event occurs */
#define HWSEM_STAT_SF30            BIT(30)                                 /*!< semaphore 30 unlock event occurs */
#define HWSEM_STAT_SF31            BIT(31)                                 /*!< semaphore 31 unlock event occurs */

/* HWSEM_INTF */
#define HWSEM_INTF_SIF0            BIT(0)                                  /*!< semaphore 00 interrupt is pending */
#define HWSEM_INTF_SIF1            BIT(1)                                  /*!< semaphore 01 interrupt is pending */
#define HWSEM_INTF_SIF2            BIT(2)                                  /*!< semaphore 02 interrupt is pending */
#define HWSEM_INTF_SIF3            BIT(3)                                  /*!< semaphore 03 interrupt is pending */
#define HWSEM_INTF_SIF4            BIT(4)                                  /*!< semaphore 04 interrupt is pending */
#define HWSEM_INTF_SIF5            BIT(5)                                  /*!< semaphore 05 interrupt is pending */
#define HWSEM_INTF_SIF6            BIT(6)                                  /*!< semaphore 06 interrupt is pending */
#define HWSEM_INTF_SIF7            BIT(7)                                  /*!< semaphore 07 interrupt is pending */
#define HWSEM_INTF_SIF8            BIT(8)                                  /*!< semaphore 08 interrupt is pending */
#define HWSEM_INTF_SIF9            BIT(9)                                  /*!< semaphore 09 interrupt is pending */
#define HWSEM_INTF_SIF10           BIT(10)                                 /*!< semaphore 10 interrupt is pending */
#define HWSEM_INTF_SIF11           BIT(11)                                 /*!< semaphore 11 interrupt is pending */
#define HWSEM_INTF_SIF12           BIT(12)                                 /*!< semaphore 12 interrupt is pending */
#define HWSEM_INTF_SIF13           BIT(13)                                 /*!< semaphore 13 interrupt is pending */
#define HWSEM_INTF_SIF14           BIT(14)                                 /*!< semaphore 14 interrupt is pending */
#define HWSEM_INTF_SIF15           BIT(15)                                 /*!< semaphore 15 interrupt is pending */
#define HWSEM_INTF_SIF16           BIT(16)                                 /*!< semaphore 16 interrupt is pending */
#define HWSEM_INTF_SIF17           BIT(17)                                 /*!< semaphore 17 interrupt is pending */
#define HWSEM_INTF_SIF18           BIT(18)                                 /*!< semaphore 18 interrupt is pending */
#define HWSEM_INTF_SIF19           BIT(19)                                 /*!< semaphore 19 interrupt is pending */
#define HWSEM_INTF_SIF20           BIT(20)                                 /*!< semaphore 20 interrupt is pending */
#define HWSEM_INTF_SIF21           BIT(21)                                 /*!< semaphore 21 interrupt is pending */
#define HWSEM_INTF_SIF22           BIT(22)                                 /*!< semaphore 22 interrupt is pending */
#define HWSEM_INTF_SIF23           BIT(23)                                 /*!< semaphore 23 interrupt is pending */
#define HWSEM_INTF_SIF24           BIT(24)                                 /*!< semaphore 24 interrupt is pending */
#define HWSEM_INTF_SIF25           BIT(25)                                 /*!< semaphore 25 interrupt is pending */
#define HWSEM_INTF_SIF26           BIT(26)                                 /*!< semaphore 26 interrupt is pending */
#define HWSEM_INTF_SIF27           BIT(27)                                 /*!< semaphore 27 interrupt is pending */
#define HWSEM_INTF_SIF28           BIT(28)                                 /*!< semaphore 28 interrupt is pending */
#define HWSEM_INTF_SIF29           BIT(29)                                 /*!< semaphore 29 interrupt is pending */
#define HWSEM_INTF_SIF30           BIT(30)                                 /*!< semaphore 30 interrupt is pending */
#define HWSEM_INTF_SIF31           BIT(31)                                 /*!< semaphore 31 interrupt is pending */

/* HWSEM_UNLK */
#define HWSEM_UNLK_MID             BITS(8,11)                              /*!< bus master ID to clear */
#define HWSEM_UNLK_KEY             BITS(16,31)                             /*!< HWSEM semaphore unlock key */

/* HWSEM_KEY */
#define HWSEM_KEY_KEY              BITS(16,31)                             /*!< key for unlocking all semaphores of a bus master */

/* constants definitions */
/* HWSEM register address */
#define HWSEM_CTL(sem)             REG32(((HWSEM) + 0x0U) + 0x4U * (sem))  /*!< the address of HWSEM semaphore control register */
#define HWSEM_RLK(sem)             REG32(((HWSEM) + 0x80U) + 0x4U * (sem)) /*!< the address of HWSEM semaphore read lock register */

/* semaphore index */
typedef enum {
    SEM0 = 0U,                                                             /*!< semaphore 0 */
    SEM1,                                                                  /*!< semaphore 1 */
    SEM2,                                                                  /*!< semaphore 2 */
    SEM3,                                                                  /*!< semaphore 3 */
    SEM4,                                                                  /*!< semaphore 4 */
    SEM5,                                                                  /*!< semaphore 5 */
    SEM6,                                                                  /*!< semaphore 6 */
    SEM7,                                                                  /*!< semaphore 7 */
    SEM8,                                                                  /*!< semaphore 8 */
    SEM9,                                                                  /*!< semaphore 9 */
    SEM10,                                                                 /*!< semaphore 10 */
    SEM11,                                                                 /*!< semaphore 11 */
    SEM12,                                                                 /*!< semaphore 12 */
    SEM13,                                                                 /*!< semaphore 13 */
    SEM14,                                                                 /*!< semaphore 14 */
    SEM15,                                                                 /*!< semaphore 15 */
    SEM16,                                                                 /*!< semaphore 16 */
    SEM17,                                                                 /*!< semaphore 17 */
    SEM18,                                                                 /*!< semaphore 18 */
    SEM19,                                                                 /*!< semaphore 19 */
    SEM20,                                                                 /*!< semaphore 20 */
    SEM21,                                                                 /*!< semaphore 21 */
    SEM22,                                                                 /*!< semaphore 22 */
    SEM23,                                                                 /*!< semaphore 23 */
    SEM24,                                                                 /*!< semaphore 24 */
    SEM25,                                                                 /*!< semaphore 25 */
    SEM26,                                                                 /*!< semaphore 26 */
    SEM27,                                                                 /*!< semaphore 27 */
    SEM28,                                                                 /*!< semaphore 28 */
    SEM29,                                                                 /*!< semaphore 29 */
    SEM30,                                                                 /*!< semaphore 30 */
    SEM31                                                                  /*!< semaphore 31 */
} hwsem_semaphore_enum;

/* hwsem_ctlx register */
#define CTL_PID(regval)          (BITS(0,7) & ((uint32_t)(regval) << 0))   /*!< write value to HWSEM_CTL_PID bit field */
#define GET_CTL_PID(regval)      GET_BITS((regval),0,7)                    /*!< get value of HWSEM_CTL_PID bit field */
#define CTL_MID(regval)          (BITS(8,11) & ((uint32_t)(regval) << 8))  /*!< write value to HWSEM_CTL_MID bit field */
#define GET_CTL_MID(regval)      GET_BITS((regval),8,11)                   /*!< get value of HWSEM_CTL_MID bit field */
#define HWSEM_LOCK               HWSEM_CTL_LK                              /*!< HWSEM semaphore locked */

/* hwsem_unlk register */
#define UNLK_MID(regval)         (BITS(8,11) & ((uint32_t)(regval) << 8))  /*!< write value to HWSEM_CTL_PID bit field */
#define UNLK_KEY(regval)         (BITS(16,31) & ((uint32_t)(regval) << 16))/*!< write value to HWSEM_CTL_PID bit field */

/* hwsem_key register */
#define KEY_KEY(regval)          (BITS(16,31) & ((uint32_t)(regval) << 16))/*!< write value to HWSEM_CTL_PID bit field */
#define GET_KEY_KEY(regval)      GET_BITS((regval),16,31)                  /*!< get value of HWSEM_CTL_PID bit field */

/* AHB bus master ID */
#define HWSEM_MASTER_ID          0x0BU                                     /*!< core CM7 master ID */

/* function declarations */
/* lock & unlock functions */
/* try to lock the specific semaphore by writing process ID */
ErrStatus hwsem_lock_set(hwsem_semaphore_enum semaphore, uint8_t process);
/* try to release the lock of the semaphore by writing process ID */
ErrStatus hwsem_lock_release(hwsem_semaphore_enum semaphore, uint8_t process);
/* try to lock the semaphore by reading */
ErrStatus hwsem_lock_by_reading(hwsem_semaphore_enum semaphore);
/* unlock all semaphores of the master ID */
ErrStatus hwsem_unlock_all(uint16_t key);

/* others */
/* get process ID of the specific semaphore */
uint32_t hwsem_process_id_get(hwsem_semaphore_enum semaphore);
/* get master ID of the specific semaphore */
uint32_t hwsem_master_id_get(hwsem_semaphore_enum semaphore);
/* get the lock status of the semaphore */
FlagStatus hwsem_lock_status_get(hwsem_semaphore_enum semaphore);
/* set the key */
void hwsem_key_set(uint16_t key);
/* get the key */
uint16_t hwsem_key_get(void);

/* flag and interrupt functions */
/* get the HWSEM flag status */
FlagStatus hwsem_flag_get(hwsem_semaphore_enum semaphore);
/* clear HWSEM flag status */
void hwsem_flag_clear(hwsem_semaphore_enum semaphore);
/* get HWSEM interrupt flag status */
FlagStatus hwsem_interrupt_flag_get(hwsem_semaphore_enum semaphore);
/* clear HWSEM interrupt flag */
void hwsem_interrupt_flag_clear(hwsem_semaphore_enum semaphore);
/* enable HWSEM interrupt */
void hwsem_interrupt_enable(hwsem_semaphore_enum semaphore);
/* disable HWSEM interrupt */
void hwsem_interrupt_disable(hwsem_semaphore_enum semaphore);

#endif /* GD32H7XX_HWSEM_H */
