/*!
    \file    gd32h7xx_exti.h
    \brief   definitions for the EXTI

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

#ifndef GD32H7XX_EXTI_H
#define GD32H7XX_EXTI_H

#include "gd32h7xx.h"

/* EXTI definition */
#define EXTI                          EXTI_BASE                      /*!< EXTI base address */

/* registers definitions */
#define EXTI_INTEN0                   REG32(EXTI + 0x00000000U)      /*!< interrupt enable register 0 */
#define EXTI_EVEN0                    REG32(EXTI + 0x00000004U)      /*!< event enable register 0 */
#define EXTI_RTEN0                    REG32(EXTI + 0x00000008U)      /*!< rising edge trigger enable register 0 */
#define EXTI_FTEN0                    REG32(EXTI + 0x0000000CU)      /*!< falling edge trigger enable register 0 */
#define EXTI_SWIEV0                   REG32(EXTI + 0x00000010U)      /*!< software interrupt event register 0 */
#define EXTI_PD0                      REG32(EXTI + 0x00000014U)      /*!< pending register 0 */
#define EXTI_INTEN1                   REG32(EXTI + 0x00000018U)      /*!< interrupt enable register 1 */
#define EXTI_EVEN1                    REG32(EXTI + 0x0000001CU)      /*!< event enable register 1 */
#define EXTI_RTEN1                    REG32(EXTI + 0x00000020U)      /*!< rising edge trigger enable register 1 */
#define EXTI_FTEN1                    REG32(EXTI + 0x00000024U)      /*!< falling edge trigger enable register 1 */
#define EXTI_SWIEV1                   REG32(EXTI + 0x00000028U)      /*!< software interrupt event register 1 */
#define EXTI_PD1                      REG32(EXTI + 0x0000002CU)      /*!< pending register 1 */

/* bits definitions */
/* EXTI_INTEN0 */
#define EXTI_INTEN0_INTEN0            BIT(0)                         /*!< interrupt from line 0 */
#define EXTI_INTEN0_INTEN1            BIT(1)                         /*!< interrupt from line 1 */
#define EXTI_INTEN0_INTEN2            BIT(2)                         /*!< interrupt from line 2 */
#define EXTI_INTEN0_INTEN3            BIT(3)                         /*!< interrupt from line 3 */
#define EXTI_INTEN0_INTEN4            BIT(4)                         /*!< interrupt from line 4 */
#define EXTI_INTEN0_INTEN5            BIT(5)                         /*!< interrupt from line 5 */
#define EXTI_INTEN0_INTEN6            BIT(6)                         /*!< interrupt from line 6 */
#define EXTI_INTEN0_INTEN7            BIT(7)                         /*!< interrupt from line 7 */
#define EXTI_INTEN0_INTEN8            BIT(8)                         /*!< interrupt from line 8 */
#define EXTI_INTEN0_INTEN9            BIT(9)                         /*!< interrupt from line 9 */
#define EXTI_INTEN0_INTEN10           BIT(10)                        /*!< interrupt from line 10 */
#define EXTI_INTEN0_INTEN11           BIT(11)                        /*!< interrupt from line 11 */
#define EXTI_INTEN0_INTEN12           BIT(12)                        /*!< interrupt from line 12 */
#define EXTI_INTEN0_INTEN13           BIT(13)                        /*!< interrupt from line 13 */
#define EXTI_INTEN0_INTEN14           BIT(14)                        /*!< interrupt from line 14 */
#define EXTI_INTEN0_INTEN15           BIT(15)                        /*!< interrupt from line 15 */
#define EXTI_INTEN0_INTEN16           BIT(16)                        /*!< interrupt from line 16 */
#define EXTI_INTEN0_INTEN17           BIT(17)                        /*!< interrupt from line 17 */
#define EXTI_INTEN0_INTEN18           BIT(18)                        /*!< interrupt from line 18 */
#define EXTI_INTEN0_INTEN19           BIT(19)                        /*!< interrupt from line 19 */
#define EXTI_INTEN0_INTEN20           BIT(20)                        /*!< interrupt from line 20 */
#define EXTI_INTEN0_INTEN21           BIT(21)                        /*!< interrupt from line 21 */
#define EXTI_INTEN0_INTEN22           BIT(22)                        /*!< interrupt from line 22 */
#define EXTI_INTEN0_INTEN23           BIT(23)                        /*!< interrupt from line 23 */
#define EXTI_INTEN0_INTEN24           BIT(24)                        /*!< interrupt from line 24 */
#define EXTI_INTEN0_INTEN25           BIT(25)                        /*!< interrupt from line 25 */
#define EXTI_INTEN0_INTEN26           BIT(26)                        /*!< interrupt from line 26 */
#define EXTI_INTEN0_INTEN27           BIT(27)                        /*!< interrupt from line 27 */
#define EXTI_INTEN0_INTEN28           BIT(28)                        /*!< interrupt from line 28 */
#define EXTI_INTEN0_INTEN29           BIT(29)                        /*!< interrupt from line 29 */
#define EXTI_INTEN0_INTEN30           BIT(30)                        /*!< interrupt from line 30 */
#define EXTI_INTEN0_INTEN31           BIT(31)                        /*!< interrupt from line 31 */

/* EXTI_EVEN0 */
#define EXTI_EVEN0_EVEN0              BIT(0)                         /*!< event from line 0 */
#define EXTI_EVEN0_EVEN1              BIT(1)                         /*!< event from line 1 */
#define EXTI_EVEN0_EVEN2              BIT(2)                         /*!< event from line 2 */
#define EXTI_EVEN0_EVEN3              BIT(3)                         /*!< event from line 3 */
#define EXTI_EVEN0_EVEN4              BIT(4)                         /*!< event from line 4 */
#define EXTI_EVEN0_EVEN5              BIT(5)                         /*!< event from line 5 */
#define EXTI_EVEN0_EVEN6              BIT(6)                         /*!< event from line 6 */
#define EXTI_EVEN0_EVEN7              BIT(7)                         /*!< event from line 7 */
#define EXTI_EVEN0_EVEN8              BIT(8)                         /*!< event from line 8 */
#define EXTI_EVEN0_EVEN9              BIT(9)                         /*!< event from line 9 */
#define EXTI_EVEN0_EVEN10             BIT(10)                        /*!< event from line 10 */
#define EXTI_EVEN0_EVEN11             BIT(11)                        /*!< event from line 11 */
#define EXTI_EVEN0_EVEN12             BIT(12)                        /*!< event from line 12 */
#define EXTI_EVEN0_EVEN13             BIT(13)                        /*!< event from line 13 */
#define EXTI_EVEN0_EVEN14             BIT(14)                        /*!< event from line 14 */
#define EXTI_EVEN0_EVEN15             BIT(15)                        /*!< event from line 15 */
#define EXTI_EVEN0_EVEN16             BIT(16)                        /*!< event from line 16 */
#define EXTI_EVEN0_EVEN17             BIT(17)                        /*!< event from line 17 */
#define EXTI_EVEN0_EVEN18             BIT(18)                        /*!< event from line 18 */
#define EXTI_EVEN0_EVEN19             BIT(19)                        /*!< event from line 19 */
#define EXTI_EVEN0_EVEN20             BIT(20)                        /*!< event from line 20 */
#define EXTI_EVEN0_EVEN21             BIT(21)                        /*!< event from line 21 */
#define EXTI_EVEN0_EVEN22             BIT(22)                        /*!< event from line 22 */
#define EXTI_EVEN0_EVEN23             BIT(23)                        /*!< event from line 23 */
#define EXTI_EVEN0_EVEN24             BIT(24)                        /*!< event from line 24 */
#define EXTI_EVEN0_EVEN25             BIT(25)                        /*!< event from line 25 */
#define EXTI_EVEN0_EVEN26             BIT(26)                        /*!< event from line 26 */
#define EXTI_EVEN0_EVEN27             BIT(27)                        /*!< event from line 27 */
#define EXTI_EVEN0_EVEN28             BIT(28)                        /*!< event from line 28 */
#define EXTI_EVEN0_EVEN29             BIT(29)                        /*!< event from line 29 */
#define EXTI_EVEN0_EVEN30             BIT(30)                        /*!< event from line 30 */
#define EXTI_EVEN0_EVEN31             BIT(31)                        /*!< event from line 31 */

/* EXTI_RTEN0 */
#define EXTI_RTEN0_RTEN0              BIT(0)                         /*!< rising edge from line 0 */
#define EXTI_RTEN0_RTEN1              BIT(1)                         /*!< rising edge from line 1 */
#define EXTI_RTEN0_RTEN2              BIT(2)                         /*!< rising edge from line 2 */
#define EXTI_RTEN0_RTEN3              BIT(3)                         /*!< rising edge from line 3 */
#define EXTI_RTEN0_RTEN4              BIT(4)                         /*!< rising edge from line 4 */
#define EXTI_RTEN0_RTEN5              BIT(5)                         /*!< rising edge from line 5 */
#define EXTI_RTEN0_RTEN6              BIT(6)                         /*!< rising edge from line 6 */
#define EXTI_RTEN0_RTEN7              BIT(7)                         /*!< rising edge from line 7 */
#define EXTI_RTEN0_RTEN8              BIT(8)                         /*!< rising edge from line 8 */
#define EXTI_RTEN0_RTEN9              BIT(9)                         /*!< rising edge from line 9 */
#define EXTI_RTEN0_RTEN10             BIT(10)                        /*!< rising edge from line 10 */
#define EXTI_RTEN0_RTEN11             BIT(11)                        /*!< rising edge from line 11 */
#define EXTI_RTEN0_RTEN12             BIT(12)                        /*!< rising edge from line 12 */
#define EXTI_RTEN0_RTEN13             BIT(13)                        /*!< rising edge from line 13 */
#define EXTI_RTEN0_RTEN14             BIT(14)                        /*!< rising edge from line 14 */
#define EXTI_RTEN0_RTEN15             BIT(15)                        /*!< rising edge from line 15 */
#define EXTI_RTEN0_RTEN16             BIT(16)                        /*!< rising edge from line 16 */
#define EXTI_RTEN0_RTEN17             BIT(17)                        /*!< rising edge from line 17 */
#define EXTI_RTEN0_RTEN18             BIT(18)                        /*!< rising edge from line 18 */
#define EXTI_RTEN0_RTEN19             BIT(19)                        /*!< rising edge from line 19 */
#define EXTI_RTEN0_RTEN20             BIT(20)                        /*!< rising edge from line 20 */
#define EXTI_RTEN0_RTEN21             BIT(21)                        /*!< rising edge from line 21 */
#define EXTI_RTEN0_RTEN22             BIT(22)                        /*!< rising edge from line 22 */
#define EXTI_RTEN0_RTEN23             BIT(23)                        /*!< rising edge from line 23 */
#define EXTI_RTEN0_RTEN24             BIT(24)                        /*!< rising edge from line 24 */
#define EXTI_RTEN0_RTEN25             BIT(25)                        /*!< rising edge from line 25 */
#define EXTI_RTEN0_RTEN26             BIT(26)                        /*!< rising edge from line 26 */
#define EXTI_RTEN0_RTEN27             BIT(27)                        /*!< rising edge from line 27 */
#define EXTI_RTEN0_RTEN28             BIT(28)                        /*!< rising edge from line 28 */
#define EXTI_RTEN0_RTEN29             BIT(29)                        /*!< rising edge from line 29 */
#define EXTI_RTEN0_RTEN30             BIT(30)                        /*!< rising edge from line 30 */
#define EXTI_RTEN0_RTEN31             BIT(31)                        /*!< rising edge from line 31 */

/* EXTI_FTEN0 */
#define EXTI_FTEN0_FTEN0              BIT(0)                         /*!< falling edge from line 0 */
#define EXTI_FTEN0_FTEN1              BIT(1)                         /*!< falling edge from line 1 */
#define EXTI_FTEN0_FTEN2              BIT(2)                         /*!< falling edge from line 2 */
#define EXTI_FTEN0_FTEN3              BIT(3)                         /*!< falling edge from line 3 */
#define EXTI_FTEN0_FTEN4              BIT(4)                         /*!< falling edge from line 4 */
#define EXTI_FTEN0_FTEN5              BIT(5)                         /*!< falling edge from line 5 */
#define EXTI_FTEN0_FTEN6              BIT(6)                         /*!< falling edge from line 6 */
#define EXTI_FTEN0_FTEN7              BIT(7)                         /*!< falling edge from line 7 */
#define EXTI_FTEN0_FTEN8              BIT(8)                         /*!< falling edge from line 8 */
#define EXTI_FTEN0_FTEN9              BIT(9)                         /*!< falling edge from line 9 */
#define EXTI_FTEN0_FTEN10             BIT(10)                        /*!< falling edge from line 10 */
#define EXTI_FTEN0_FTEN11             BIT(11)                        /*!< falling edge from line 11 */
#define EXTI_FTEN0_FTEN12             BIT(12)                        /*!< falling edge from line 12 */
#define EXTI_FTEN0_FTEN13             BIT(13)                        /*!< falling edge from line 13 */
#define EXTI_FTEN0_FTEN14             BIT(14)                        /*!< falling edge from line 14 */
#define EXTI_FTEN0_FTEN15             BIT(15)                        /*!< falling edge from line 15 */
#define EXTI_FTEN0_FTEN16             BIT(16)                        /*!< falling edge from line 16 */
#define EXTI_FTEN0_FTEN17             BIT(17)                        /*!< falling edge from line 17 */
#define EXTI_FTEN0_FTEN18             BIT(18)                        /*!< falling edge from line 18 */
#define EXTI_FTEN0_FTEN19             BIT(19)                        /*!< falling edge from line 19 */
#define EXTI_FTEN0_FTEN20             BIT(20)                        /*!< falling edge from line 20 */
#define EXTI_FTEN0_FTEN21             BIT(21)                        /*!< falling edge from line 21 */
#define EXTI_FTEN0_FTEN22             BIT(22)                        /*!< falling edge from line 22 */
#define EXTI_FTEN0_FTEN23             BIT(23)                        /*!< falling edge from line 23 */
#define EXTI_FTEN0_FTEN24             BIT(24)                        /*!< falling edge from line 24 */
#define EXTI_FTEN0_FTEN25             BIT(25)                        /*!< falling edge from line 25 */
#define EXTI_FTEN0_FTEN26             BIT(26)                        /*!< falling edge from line 26 */
#define EXTI_FTEN0_FTEN27             BIT(27)                        /*!< falling edge from line 27 */
#define EXTI_FTEN0_FTEN28             BIT(28)                        /*!< falling edge from line 28 */
#define EXTI_FTEN0_FTEN29             BIT(29)                        /*!< falling edge from line 29 */
#define EXTI_FTEN0_FTEN30             BIT(30)                        /*!< falling edge from line 30 */
#define EXTI_FTEN0_FTEN31             BIT(31)                        /*!< falling edge from line 31 */

/* EXTI_SWIEV0 */
#define EXTI_SWIEV0_SWIEV0            BIT(0)                         /*!< software interrupt/event request from line 0 */
#define EXTI_SWIEV0_SWIEV1            BIT(1)                         /*!< software interrupt/event request from line 1 */
#define EXTI_SWIEV0_SWIEV2            BIT(2)                         /*!< software interrupt/event request from line 2 */
#define EXTI_SWIEV0_SWIEV3            BIT(3)                         /*!< software interrupt/event request from line 3 */
#define EXTI_SWIEV0_SWIEV4            BIT(4)                         /*!< software interrupt/event request from line 4 */
#define EXTI_SWIEV0_SWIEV5            BIT(5)                         /*!< software interrupt/event request from line 5 */
#define EXTI_SWIEV0_SWIEV6            BIT(6)                         /*!< software interrupt/event request from line 6 */
#define EXTI_SWIEV0_SWIEV7            BIT(7)                         /*!< software interrupt/event request from line 7 */
#define EXTI_SWIEV0_SWIEV8            BIT(8)                         /*!< software interrupt/event request from line 8 */
#define EXTI_SWIEV0_SWIEV9            BIT(9)                         /*!< software interrupt/event request from line 9 */
#define EXTI_SWIEV0_SWIEV10           BIT(10)                        /*!< software interrupt/event request from line 10 */
#define EXTI_SWIEV0_SWIEV11           BIT(11)                        /*!< software interrupt/event request from line 11 */
#define EXTI_SWIEV0_SWIEV12           BIT(12)                        /*!< software interrupt/event request from line 12 */
#define EXTI_SWIEV0_SWIEV13           BIT(13)                        /*!< software interrupt/event request from line 13 */
#define EXTI_SWIEV0_SWIEV14           BIT(14)                        /*!< software interrupt/event request from line 14 */
#define EXTI_SWIEV0_SWIEV15           BIT(15)                        /*!< software interrupt/event request from line 15 */
#define EXTI_SWIEV0_SWIEV16           BIT(16)                        /*!< software interrupt/event request from line 16 */
#define EXTI_SWIEV0_SWIEV17           BIT(17)                        /*!< software interrupt/event request from line 17 */
#define EXTI_SWIEV0_SWIEV18           BIT(18)                        /*!< software interrupt/event request from line 18 */
#define EXTI_SWIEV0_SWIEV19           BIT(19)                        /*!< software interrupt/event request from line 19 */
#define EXTI_SWIEV0_SWIEV20           BIT(20)                        /*!< software interrupt/event request from line 20 */
#define EXTI_SWIEV0_SWIEV21           BIT(21)                        /*!< software interrupt/event request from line 21 */
#define EXTI_SWIEV0_SWIEV22           BIT(22)                        /*!< software interrupt/event request from line 22 */
#define EXTI_SWIEV0_SWIEV23           BIT(23)                        /*!< software interrupt/event request from line 23 */
#define EXTI_SWIEV0_SWIEV24           BIT(24)                        /*!< software interrupt/event request from line 24 */
#define EXTI_SWIEV0_SWIEV25           BIT(25)                        /*!< software interrupt/event request from line 25 */
#define EXTI_SWIEV0_SWIEV26           BIT(26)                        /*!< software interrupt/event request from line 26 */
#define EXTI_SWIEV0_SWIEV27           BIT(27)                        /*!< software interrupt/event request from line 27 */
#define EXTI_SWIEV0_SWIEV28           BIT(28)                        /*!< software interrupt/event request from line 28 */
#define EXTI_SWIEV0_SWIEV29           BIT(29)                        /*!< software interrupt/event request from line 29 */
#define EXTI_SWIEV0_SWIEV30           BIT(30)                        /*!< software interrupt/event request from line 30 */
#define EXTI_SWIEV0_SWIEV31           BIT(31)                        /*!< software interrupt/event request from line 31 */

/* EXTI_PD0 */
#define EXTI_PD0_PD0                  BIT(0)                         /*!< interrupt pending status from line 0 */
#define EXTI_PD0_PD1                  BIT(1)                         /*!< interrupt pending status from line 1 */
#define EXTI_PD0_PD2                  BIT(2)                         /*!< interrupt pending status from line 2 */
#define EXTI_PD0_PD3                  BIT(3)                         /*!< interrupt pending status from line 3 */
#define EXTI_PD0_PD4                  BIT(4)                         /*!< interrupt pending status from line 4 */
#define EXTI_PD0_PD5                  BIT(5)                         /*!< interrupt pending status from line 5 */
#define EXTI_PD0_PD6                  BIT(6)                         /*!< interrupt pending status from line 6 */
#define EXTI_PD0_PD7                  BIT(7)                         /*!< interrupt pending status from line 7 */
#define EXTI_PD0_PD8                  BIT(8)                         /*!< interrupt pending status from line 8 */
#define EXTI_PD0_PD9                  BIT(9)                         /*!< interrupt pending status from line 9 */
#define EXTI_PD0_PD10                 BIT(10)                        /*!< interrupt pending status from line 10 */
#define EXTI_PD0_PD11                 BIT(11)                        /*!< interrupt pending status from line 11 */
#define EXTI_PD0_PD12                 BIT(12)                        /*!< interrupt pending status from line 12 */
#define EXTI_PD0_PD13                 BIT(13)                        /*!< interrupt pending status from line 13 */
#define EXTI_PD0_PD14                 BIT(14)                        /*!< interrupt pending status from line 14 */
#define EXTI_PD0_PD15                 BIT(15)                        /*!< interrupt pending status from line 15 */
#define EXTI_PD0_PD16                 BIT(16)                        /*!< interrupt pending status from line 16 */
#define EXTI_PD0_PD17                 BIT(17)                        /*!< interrupt pending status from line 17 */
#define EXTI_PD0_PD18                 BIT(18)                        /*!< interrupt pending status from line 18 */
#define EXTI_PD0_PD19                 BIT(19)                        /*!< interrupt pending status from line 19 */
#define EXTI_PD0_PD20                 BIT(20)                        /*!< interrupt pending status from line 20 */
#define EXTI_PD0_PD21                 BIT(21)                        /*!< interrupt pending status from line 21 */
#define EXTI_PD0_PD22                 BIT(22)                        /*!< interrupt pending status from line 22 */
#define EXTI_PD0_PD23                 BIT(23)                        /*!< interrupt pending status from line 23 */
#define EXTI_PD0_PD24                 BIT(24)                        /*!< interrupt pending status from line 24 */
#define EXTI_PD0_PD25                 BIT(25)                        /*!< interrupt pending status from line 25 */
#define EXTI_PD0_PD26                 BIT(26)                        /*!< interrupt pending status from line 26 */
#define EXTI_PD0_PD27                 BIT(27)                        /*!< interrupt pending status from line 27 */
#define EXTI_PD0_PD28                 BIT(28)                        /*!< interrupt pending status from line 28 */
#define EXTI_PD0_PD29                 BIT(29)                        /*!< interrupt pending status from line 29 */
#define EXTI_PD0_PD30                 BIT(30)                        /*!< interrupt pending status from line 30 */
#define EXTI_PD0_PD31                 BIT(31)                        /*!< interrupt pending status from line 31 */

/* EXTI_INTEN1 */
#define EXTI_INTEN1_INTEN32           BIT(0)                         /*!< interrupt from line 32 */
#define EXTI_INTEN1_INTEN33           BIT(1)                         /*!< interrupt from line 33 */
#define EXTI_INTEN1_INTEN34           BIT(2)                         /*!< interrupt from line 34 */
#define EXTI_INTEN1_INTEN35           BIT(3)                         /*!< interrupt from line 35 */
#define EXTI_INTEN1_INTEN36           BIT(4)                         /*!< interrupt from line 36 */
#define EXTI_INTEN1_INTEN37           BIT(5)                         /*!< interrupt from line 37 */

/* EXTI_EVEN1 */
#define EXTI_EVEN1_EVEN32             BIT(0)                         /*!< event from line 32 */
#define EXTI_EVEN1_EVEN33             BIT(1)                         /*!< event from line 33 */
#define EXTI_EVEN1_EVEN34             BIT(2)                         /*!< event from line 34 */
#define EXTI_EVEN1_EVEN35             BIT(3)                         /*!< event from line 35 */
#define EXTI_EVEN1_EVEN36             BIT(4)                         /*!< event from line 36 */
#define EXTI_EVEN1_EVEN37             BIT(5)                         /*!< event from line 37 */

/* EXTI_RTEN1 */
#define EXTI_RTEN1_RTEN32             BIT(0)                         /*!< rising edge from line 32 */
#define EXTI_RTEN1_RTEN33             BIT(1)                         /*!< rising edge from line 33 */
#define EXTI_RTEN1_RTEN34             BIT(2)                         /*!< rising edge from line 34 */
#define EXTI_RTEN1_RTEN35             BIT(3)                         /*!< rising edge from line 35 */
#define EXTI_RTEN1_RTEN36             BIT(4)                         /*!< rising edge from line 36 */
#define EXTI_RTEN1_RTEN37             BIT(5)                         /*!< rising edge from line 37 */

/* EXTI_FTEN1 */
#define EXTI_FTEN1_FTEN32             BIT(0)                         /*!< falling edge from line 32 */
#define EXTI_FTEN1_FTEN33             BIT(1)                         /*!< falling edge from line 33 */
#define EXTI_FTEN1_FTEN34             BIT(2)                         /*!< falling edge from line 34 */
#define EXTI_FTEN1_FTEN35             BIT(3)                         /*!< falling edge from line 35 */
#define EXTI_FTEN1_FTEN36             BIT(4)                         /*!< falling edge from line 36 */
#define EXTI_FTEN1_FTEN37             BIT(5)                         /*!< falling edge from line 37 */

/* EXTI_SWIEV1 */
#define EXTI_SWIEV1_SWIEV32           BIT(0)                         /*!< software interrupt/event request from line 32 */
#define EXTI_SWIEV1_SWIEV33           BIT(1)                         /*!< software interrupt/event request from line 33 */
#define EXTI_SWIEV1_SWIEV34           BIT(2)                         /*!< software interrupt/event request from line 34 */
#define EXTI_SWIEV1_SWIEV35           BIT(3)                         /*!< software interrupt/event request from line 35 */
#define EXTI_SWIEV1_SWIEV36           BIT(4)                         /*!< software interrupt/event request from line 36 */
#define EXTI_SWIEV1_SWIEV37           BIT(5)                         /*!< software interrupt/event request from line 37 */

/* EXTI_PD1 */
#define EXTI_PD1_PD32                 BIT(0)                         /*!< interrupt pending status from line 32 */
#define EXTI_PD1_PD33                 BIT(1)                         /*!< interrupt pending status from line 33 */
#define EXTI_PD1_PD34                 BIT(2)                         /*!< interrupt pending status from line 34 */
#define EXTI_PD1_PD35                 BIT(3)                         /*!< interrupt pending status from line 35 */
#define EXTI_PD1_PD36                 BIT(4)                         /*!< interrupt pending status from line 36 */
#define EXTI_PD1_PD37                 BIT(5)                         /*!< interrupt pending status from line 37 */

/* constants definitions */
/* define the EXTI bit position and its register group index offset */
#define EXTI_GROUPIDX_BIT(groupidx, bitpos)      (((uint32_t)(groupidx) << 8U) | (uint32_t)(bitpos))
#define EXTI_REG_VAL(linex)                      (EXTI + ((uint32_t)(linex) >> 8U))
#define EXTI_BIT_POS(linex)                      BIT((uint32_t)(linex) & 0x1FU)

/* define the EXTI register groups*/
#define EXTI_GROUP0_OFFSET                       0x00000000U                                         /*!< the index offset of EXTI group0 */
#define EXTI_GROUP1_OFFSET                       0x00000018U                                         /*!< the index offset of EXTI group1 */

/* define the registers in the group*/
#define EXTI_INTEN(exti_group)                   REG32((uint32_t)(exti_group) + 0x00000000U)         /*!< the index offset of register INTEN in the registe group */
#define EXTI_EVEN(exti_group)                    REG32((uint32_t)(exti_group) + 0x00000004U)         /*!< the index offset of register EVEN in the registe group */
#define EXTI_RTEN(exti_group)                    REG32((uint32_t)(exti_group) + 0x00000008U)         /*!< the index offset of register RTEN in the registe group */
#define EXTI_FTEN(exti_group)                    REG32((uint32_t)(exti_group) + 0x0000000CU)         /*!< the index offset of register FTEN in the registe group */
#define EXTI_SWIEV(exti_group)                   REG32((uint32_t)(exti_group) + 0x00000010U)         /*!< the index offset of register SWIEV in the registe group */
#define EXTI_PD(exti_group)                      REG32((uint32_t)(exti_group) + 0x00000014U)         /*!< the index offset of register PD in the registe group */

/* EXTI line number */
typedef enum {
    EXTI_0      = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 0U),    /*!< EXTI line 0 */
    EXTI_1      = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 1U),    /*!< EXTI line 1 */
    EXTI_2      = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 2U),    /*!< EXTI line 2 */
    EXTI_3      = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 3U),    /*!< EXTI line 3 */
    EXTI_4      = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 4U),    /*!< EXTI line 4 */
    EXTI_5      = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 5U),    /*!< EXTI line 5 */
    EXTI_6      = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 6U),    /*!< EXTI line 6 */
    EXTI_7      = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 7U),    /*!< EXTI line 7 */
    EXTI_8      = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 8U),    /*!< EXTI line 8 */
    EXTI_9      = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 9U),    /*!< EXTI line 9 */
    EXTI_10     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 10U),   /*!< EXTI line 10 */
    EXTI_11     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 11U),   /*!< EXTI line 11 */
    EXTI_12     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 12U),   /*!< EXTI line 12 */
    EXTI_13     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 13U),   /*!< EXTI line 13 */
    EXTI_14     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 14U),   /*!< EXTI line 14 */
    EXTI_15     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 15U),   /*!< EXTI line 15 */
    EXTI_16     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 16U),   /*!< EXTI line 16 */
    EXTI_17     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 17U),   /*!< EXTI line 17 */
    EXTI_18     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 18U),   /*!< EXTI line 18 */
    EXTI_19     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 19U),   /*!< EXTI line 19 */
    EXTI_20     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 20U),   /*!< EXTI line 20 */
    EXTI_21     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 21U),   /*!< EXTI line 21 */
    EXTI_22     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 22U),   /*!< EXTI line 22 */
    EXTI_23     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 23U),   /*!< EXTI line 23 */
    EXTI_24     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 24U),   /*!< EXTI line 24 */
    EXTI_25     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 25U),   /*!< EXTI line 25 */
    EXTI_26     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 26U),   /*!< EXTI line 26 */
    EXTI_27     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 27U),   /*!< EXTI line 27 */
    EXTI_28     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 28U),   /*!< EXTI line 28 */
    EXTI_29     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 29U),   /*!< EXTI line 29 */
    EXTI_30     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 30U),   /*!< EXTI line 30 */
    EXTI_31     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 31U),   /*!< EXTI line 31 */
    EXTI_32     = EXTI_GROUPIDX_BIT(EXTI_GROUP1_OFFSET, 32U),   /*!< EXTI line 32 */
    EXTI_33     = EXTI_GROUPIDX_BIT(EXTI_GROUP1_OFFSET, 33U),   /*!< EXTI line 33 */
    EXTI_34     = EXTI_GROUPIDX_BIT(EXTI_GROUP1_OFFSET, 34U),   /*!< EXTI line 34 */
    EXTI_35     = EXTI_GROUPIDX_BIT(EXTI_GROUP1_OFFSET, 35U),   /*!< EXTI line 35 */
    EXTI_36     = EXTI_GROUPIDX_BIT(EXTI_GROUP1_OFFSET, 36U),   /*!< EXTI line 36 */
    EXTI_37     = EXTI_GROUPIDX_BIT(EXTI_GROUP1_OFFSET, 37U)    /*!< EXTI line 37 */
} exti_line_enum;

/* external interrupt and event */
typedef enum {
    EXTI_INTERRUPT = 0,                                         /*!< EXTI interrupt mode */
    EXTI_EVENT                                                  /*!< EXTI event mode */
} exti_mode_enum;

/* interrupt and event trigger mode */
typedef enum {
    EXTI_TRIG_RISING = 0,                                       /*!< EXTI rising edge trigger */
    EXTI_TRIG_FALLING,                                          /*!< EXTI falling edge trigger */
    EXTI_TRIG_BOTH,                                             /*!< EXTI rising and falling edge trigger */
    EXTI_TRIG_NONE                                              /*!< without rising edge or falling edge trigger */
} exti_trig_type_enum;

/* function declarations */
/* initialization, EXTI lines configuration functions */
/* deinitialize the EXTI */
void exti_deinit(void);
/* initialize the EXTI line x */
void exti_init(exti_line_enum linex, exti_mode_enum mode, exti_trig_type_enum trig_type);
/* enable the interrupts from EXTI line x */
void exti_interrupt_enable(exti_line_enum linex);
/* disable the interrupts from EXTI line x */
void exti_interrupt_disable(exti_line_enum linex);
/* enable the events from EXTI line x */
void exti_event_enable(exti_line_enum linex);
/* disable the events from EXTI line x */
void exti_event_disable(exti_line_enum linex);
/* enable the software interrupt event from EXTI line x */
void exti_software_interrupt_enable(exti_line_enum linex);
/* disable the software interrupt event from EXTI line x */
void exti_software_interrupt_disable(exti_line_enum linex);

/* interrupt & flag functions */
/* get EXTI line x interrupt pending flag */
FlagStatus exti_flag_get(exti_line_enum linex);
/* clear EXTI line x interrupt pending flag */
void exti_flag_clear(exti_line_enum linex);
/* get EXTI line x interrupt pending flag */
FlagStatus exti_interrupt_flag_get(exti_line_enum linex);
/* clear EXTI line x interrupt pending flag */
void exti_interrupt_flag_clear(exti_line_enum linex);

#endif /* GD32H7XX_EXTI_H */
