/*!
    \file    gd32f20x_gpio.h
    \brief   definitions for the GPIO

    \version 2015-07-15, V1.0.0, firmware for GD32F20x
    \version 2017-06-05, V2.0.0, firmware for GD32F20x
    \version 2018-10-31, V2.1.0, firmware for GD32F20x
    \version 2020-09-30, V2.2.0, firmware for GD32F20x
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

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

#ifndef GD32F20X_GPIO_H
#define GD32F20X_GPIO_H

#include "gd32f20x.h"

/* GPIOx(x=A,B,C,D,E,F,G,H,I) definitions */
#define GPIOA                      (GPIO_BASE + 0x00000000U)
#define GPIOB                      (GPIO_BASE + 0x00000400U)
#define GPIOC                      (GPIO_BASE + 0x00000800U)
#define GPIOD                      (GPIO_BASE + 0x00000C00U)
#define GPIOE                      (GPIO_BASE + 0x00001000U)
#define GPIOF                      (GPIO_BASE + 0x00001400U)
#define GPIOG                      (GPIO_BASE + 0x00001800U)
#define GPIOH                      (GPIO_BASE + 0x00006C00U)
#define GPIOI                      (GPIO_BASE + 0x00007000U)

/* AFIO definitions */
#define AFIO                       AFIO_BASE

/* registers definitions */
/* GPIO registers definitions */
#define GPIO_CTL0(gpiox)           REG32((gpiox) + 0x00U)    /*!< GPIO port control register 0 */
#define GPIO_CTL1(gpiox)           REG32((gpiox) + 0x04U)    /*!< GPIO port control register 1 */
#define GPIO_ISTAT(gpiox)          REG32((gpiox) + 0x08U)    /*!< GPIO port input status register */
#define GPIO_OCTL(gpiox)           REG32((gpiox) + 0x0CU)    /*!< GPIO port output control register */
#define GPIO_BOP(gpiox)            REG32((gpiox) + 0x10U)    /*!< GPIO port bit operation register */
#define GPIO_BC(gpiox)             REG32((gpiox) + 0x14U)    /*!< GPIO bit clear register */
#define GPIO_LOCK(gpiox)           REG32((gpiox) + 0x18U)    /*!< GPIO port configuration lock register */

/* AFIO registers definitions */
#define AFIO_EC                    REG32(AFIO + 0x00U)       /*!< AFIO event control register */
#define AFIO_PCF0                  REG32(AFIO + 0x04U)       /*!< AFIO port configuration register 0 */
#define AFIO_EXTISS0               REG32(AFIO + 0x08U)       /*!< AFIO port EXTI sources selection register 0 */
#define AFIO_EXTISS1               REG32(AFIO + 0x0CU)       /*!< AFIO port EXTI sources selection register 1 */
#define AFIO_EXTISS2               REG32(AFIO + 0x10U)       /*!< AFIO port EXTI sources selection register 2 */
#define AFIO_EXTISS3               REG32(AFIO + 0x14U)       /*!< AFIO port EXTI sources selection register 3 */
#define AFIO_PCF1                  REG32(AFIO + 0x1CU)       /*!< AFIO port configuration register 1 */
#define AFIO_PCF2                  REG32(AFIO + 0x3CU)       /*!< AFIO port configuration register 2 */
#define AFIO_PCF3                  REG32(AFIO + 0x40U)       /*!< AFIO port configuration register 3 */
#define AFIO_PCF4                  REG32(AFIO + 0x44U)       /*!< AFIO port configuration register 4 */
#define AFIO_PCF5                  REG32(AFIO + 0x48U)       /*!< AFIO port configuration register 5 */

/* bits definitions */
/* GPIO_CTL0 */
#define GPIO_CTL0_MD0              BITS(0,1)                 /*!< port 0 mode bits */
#define GPIO_CTL0_CTL0             BITS(2,3)                 /*!< pin 0 configuration bits */
#define GPIO_CTL0_MD1              BITS(4,5)                 /*!< port 1 mode bits */
#define GPIO_CTL0_CTL1             BITS(6,7)                 /*!< pin 1 configuration bits */
#define GPIO_CTL0_MD2              BITS(8,9)                 /*!< port 2 mode bits */
#define GPIO_CTL0_CTL2             BITS(10,11)               /*!< pin 2 configuration bits */
#define GPIO_CTL0_MD3              BITS(12,13)               /*!< port 3 mode bits */
#define GPIO_CTL0_CTL3             BITS(14,15)               /*!< pin 3 configuration bits */
#define GPIO_CTL0_MD4              BITS(16,17)               /*!< port 4 mode bits */
#define GPIO_CTL0_CTL4             BITS(18,19)               /*!< pin 4 configuration bits */
#define GPIO_CTL0_MD5              BITS(20,21)               /*!< port 5 mode bits */
#define GPIO_CTL0_CTL5             BITS(22,23)               /*!< pin 5 configuration bits */
#define GPIO_CTL0_MD6              BITS(24,25)               /*!< port 6 mode bits */
#define GPIO_CTL0_CTL6             BITS(26,27)               /*!< pin 6 configuration bits */
#define GPIO_CTL0_MD7              BITS(28,29)               /*!< port 7 mode bits */
#define GPIO_CTL0_CTL7             BITS(30,31)               /*!< pin 7 configuration bits */

/* GPIO_CTL1 */
#define GPIO_CTL1_MD8              BITS(0,1)                 /*!< port 8 mode bits */
#define GPIO_CTL1_CTL8             BITS(2,3)                 /*!< pin 8 configuration bits */
#define GPIO_CTL1_MD9              BITS(4,5)                 /*!< port 9 mode bits */
#define GPIO_CTL1_CTL9             BITS(6,7)                 /*!< pin 9 configuration bits */
#define GPIO_CTL1_MD10             BITS(8,9)                 /*!< port 10 mode bits */
#define GPIO_CTL1_CTL10            BITS(10,11)               /*!< pin 10 configuration bits */
#define GPIO_CTL1_MD11             BITS(12,13)               /*!< port 11 mode bits */
#define GPIO_CTL1_CTL11            BITS(14,15)               /*!< pin 11 configuration bits */
#define GPIO_CTL1_MD12             BITS(16,17)               /*!< port 12 mode bits */
#define GPIO_CTL1_CTL12            BITS(18,19)               /*!< pin 12 configuration bits */
#define GPIO_CTL1_MD13             BITS(20,21)               /*!< port 13 mode bits */
#define GPIO_CTL1_CTL13            BITS(22,23)               /*!< pin 13 configuration bits */
#define GPIO_CTL1_MD14             BITS(24,25)               /*!< port 14 mode bits */
#define GPIO_CTL1_CTL14            BITS(26,27)               /*!< pin 14 configuration bits */
#define GPIO_CTL1_MD15             BITS(28,29)               /*!< port 15 mode bits */
#define GPIO_CTL1_CTL15            BITS(30,31)               /*!< pin 15 configuration bits */

/* GPIO_ISTAT */
#define GPIO_ISTAT_ISTAT0          BIT(0)                    /*!< pin 0 input status */
#define GPIO_ISTAT_ISTAT1          BIT(1)                    /*!< pin 1 input status */
#define GPIO_ISTAT_ISTAT2          BIT(2)                    /*!< pin 2 input status */
#define GPIO_ISTAT_ISTAT3          BIT(3)                    /*!< pin 3 input status */
#define GPIO_ISTAT_ISTAT4          BIT(4)                    /*!< pin 4 input status */
#define GPIO_ISTAT_ISTAT5          BIT(5)                    /*!< pin 5 input status */
#define GPIO_ISTAT_ISTAT6          BIT(6)                    /*!< pin 6 input status */
#define GPIO_ISTAT_ISTAT7          BIT(7)                    /*!< pin 7 input status */
#define GPIO_ISTAT_ISTAT8          BIT(8)                    /*!< pin 8 input status */
#define GPIO_ISTAT_ISTAT9          BIT(9)                    /*!< pin 9 input status */
#define GPIO_ISTAT_ISTAT10         BIT(10)                   /*!< pin 10 input status */
#define GPIO_ISTAT_ISTAT11         BIT(11)                   /*!< pin 11 input status */
#define GPIO_ISTAT_ISTAT12         BIT(12)                   /*!< pin 12 input status */
#define GPIO_ISTAT_ISTAT13         BIT(13)                   /*!< pin 13 input status */
#define GPIO_ISTAT_ISTAT14         BIT(14)                   /*!< pin 14 input status */
#define GPIO_ISTAT_ISTAT15         BIT(15)                   /*!< pin 15 input status */

/* GPIO_OCTL */
#define GPIO_OCTL_OCTL0            BIT(0)                    /*!< pin 0 output bit */
#define GPIO_OCTL_OCTL1            BIT(1)                    /*!< pin 1 output bit */
#define GPIO_OCTL_OCTL2            BIT(2)                    /*!< pin 2 output bit */
#define GPIO_OCTL_OCTL3            BIT(3)                    /*!< pin 3 output bit */
#define GPIO_OCTL_OCTL4            BIT(4)                    /*!< pin 4 output bit */
#define GPIO_OCTL_OCTL5            BIT(5)                    /*!< pin 5 output bit */
#define GPIO_OCTL_OCTL6            BIT(6)                    /*!< pin 6 output bit */
#define GPIO_OCTL_OCTL7            BIT(7)                    /*!< pin 7 output bit */
#define GPIO_OCTL_OCTL8            BIT(8)                    /*!< pin 8 output bit */
#define GPIO_OCTL_OCTL9            BIT(9)                    /*!< pin 9 output bit */
#define GPIO_OCTL_OCTL10           BIT(10)                   /*!< pin 10 output bit */
#define GPIO_OCTL_OCTL11           BIT(11)                   /*!< pin 11 output bit */
#define GPIO_OCTL_OCTL12           BIT(12)                   /*!< pin 12 output bit */
#define GPIO_OCTL_OCTL13           BIT(13)                   /*!< pin 13 output bit */
#define GPIO_OCTL_OCTL14           BIT(14)                   /*!< pin 14 output bit */
#define GPIO_OCTL_OCTL15           BIT(15)                   /*!< pin 15 output bit */

/* GPIO_BOP */
#define GPIO_BOP_BOP0              BIT(0)                    /*!< pin 0 set bit */
#define GPIO_BOP_BOP1              BIT(1)                    /*!< pin 1 set bit */
#define GPIO_BOP_BOP2              BIT(2)                    /*!< pin 2 set bit */
#define GPIO_BOP_BOP3              BIT(3)                    /*!< pin 3 set bit */
#define GPIO_BOP_BOP4              BIT(4)                    /*!< pin 4 set bit */
#define GPIO_BOP_BOP5              BIT(5)                    /*!< pin 5 set bit */
#define GPIO_BOP_BOP6              BIT(6)                    /*!< pin 6 set bit */
#define GPIO_BOP_BOP7              BIT(7)                    /*!< pin 7 set bit */
#define GPIO_BOP_BOP8              BIT(8)                    /*!< pin 8 set bit */
#define GPIO_BOP_BOP9              BIT(9)                    /*!< pin 9 set bit */
#define GPIO_BOP_BOP10             BIT(10)                   /*!< pin 10 set bit */
#define GPIO_BOP_BOP11             BIT(11)                   /*!< pin 11 set bit */
#define GPIO_BOP_BOP12             BIT(12)                   /*!< pin 12 set bit */
#define GPIO_BOP_BOP13             BIT(13)                   /*!< pin 13 set bit */
#define GPIO_BOP_BOP14             BIT(14)                   /*!< pin 14 set bit */
#define GPIO_BOP_BOP15             BIT(15)                   /*!< pin 15 set bit */
#define GPIO_BOP_CR0               BIT(16)                   /*!< pin 0 clear bit */
#define GPIO_BOP_CR1               BIT(17)                   /*!< pin 1 clear bit */
#define GPIO_BOP_CR2               BIT(18)                   /*!< pin 2 clear bit */
#define GPIO_BOP_CR3               BIT(19)                   /*!< pin 3 clear bit */
#define GPIO_BOP_CR4               BIT(20)                   /*!< pin 4 clear bit */
#define GPIO_BOP_CR5               BIT(21)                   /*!< pin 5 clear bit */
#define GPIO_BOP_CR6               BIT(22)                   /*!< pin 6 clear bit */
#define GPIO_BOP_CR7               BIT(23)                   /*!< pin 7 clear bit */
#define GPIO_BOP_CR8               BIT(24)                   /*!< pin 8 clear bit */
#define GPIO_BOP_CR9               BIT(25)                   /*!< pin 9 clear bit */
#define GPIO_BOP_CR10              BIT(26)                   /*!< pin 10 clear bit */
#define GPIO_BOP_CR11              BIT(27)                   /*!< pin 11 clear bit */
#define GPIO_BOP_CR12              BIT(28)                   /*!< pin 12 clear bit */
#define GPIO_BOP_CR13              BIT(29)                   /*!< pin 13 clear bit */
#define GPIO_BOP_CR14              BIT(30)                   /*!< pin 14 clear bit */
#define GPIO_BOP_CR15              BIT(31)                   /*!< pin 15 clear bit */

/* GPIO_BC */
#define GPIO_BC_CR0                BIT(0)                    /*!< pin 0 clear bit */
#define GPIO_BC_CR1                BIT(1)                    /*!< pin 1 clear bit */
#define GPIO_BC_CR2                BIT(2)                    /*!< pin 2 clear bit */
#define GPIO_BC_CR3                BIT(3)                    /*!< pin 3 clear bit */
#define GPIO_BC_CR4                BIT(4)                    /*!< pin 4 clear bit */
#define GPIO_BC_CR5                BIT(5)                    /*!< pin 5 clear bit */
#define GPIO_BC_CR6                BIT(6)                    /*!< pin 6 clear bit */
#define GPIO_BC_CR7                BIT(7)                    /*!< pin 7 clear bit */
#define GPIO_BC_CR8                BIT(8)                    /*!< pin 8 clear bit */
#define GPIO_BC_CR9                BIT(9)                    /*!< pin 9 clear bit */
#define GPIO_BC_CR10               BIT(10)                   /*!< pin 10 clear bit */
#define GPIO_BC_CR11               BIT(11)                   /*!< pin 11 clear bit */
#define GPIO_BC_CR12               BIT(12)                   /*!< pin 12 clear bit */
#define GPIO_BC_CR13               BIT(13)                   /*!< pin 13 clear bit */
#define GPIO_BC_CR14               BIT(14)                   /*!< pin 14 clear bit */
#define GPIO_BC_CR15               BIT(15)                   /*!< pin 15 clear bit */

/* GPIO_LOCK */
#define GPIO_LOCK_LK0              BIT(0)                    /*!< pin 0 lock bit */
#define GPIO_LOCK_LK1              BIT(1)                    /*!< pin 1 lock bit */
#define GPIO_LOCK_LK2              BIT(2)                    /*!< pin 2 lock bit */
#define GPIO_LOCK_LK3              BIT(3)                    /*!< pin 3 lock bit */
#define GPIO_LOCK_LK4              BIT(4)                    /*!< pin 4 lock bit */
#define GPIO_LOCK_LK5              BIT(5)                    /*!< pin 5 lock bit */
#define GPIO_LOCK_LK6              BIT(6)                    /*!< pin 6 lock bit */
#define GPIO_LOCK_LK7              BIT(7)                    /*!< pin 7 lock bit */
#define GPIO_LOCK_LK8              BIT(8)                    /*!< pin 8 lock bit */
#define GPIO_LOCK_LK9              BIT(9)                    /*!< pin 9 lock bit */
#define GPIO_LOCK_LK10             BIT(10)                   /*!< pin 10 lock bit */
#define GPIO_LOCK_LK11             BIT(11)                   /*!< pin 11 lock bit */
#define GPIO_LOCK_LK12             BIT(12)                   /*!< pin 12 lock bit */
#define GPIO_LOCK_LK13             BIT(13)                   /*!< pin 13 lock bit */
#define GPIO_LOCK_LK14             BIT(14)                   /*!< pin 14 lock bit */
#define GPIO_LOCK_LK15             BIT(15)                   /*!< pin 15 lock bit */
#define GPIO_LOCK_LKK              BIT(16)                   /*!< pin sequence lock key */

/* AFIO_EC */
#define AFIO_EC_PIN                BITS(0,3)                 /*!< event output pin selection */
#define AFIO_EC_PORT               BITS(4,6)                 /*!< event output port selection */
#define AFIO_EC_EOE                BIT(7)                    /*!< event output enable */

/* AFIO_PCF0 */
#define AFIO_PCF0_SPI0_REMAP             BIT(0)              /*!< SPI0 remapping */
#define AFIO_PCF0_I2C0_REMAP             BIT(1)              /*!< I2C0 remapping */
#define AFIO_PCF0_USART0_REMAP           BIT(2)              /*!< USART0 remapping */
#define AFIO_PCF0_USART1_REMAP           BIT(3)              /*!< USART1 remapping */
#define AFIO_PCF0_USART2_REMAP           BITS(4,5)           /*!< USART2 remapping */
#define AFIO_PCF0_TIMER0_REMAP           BITS(6,7)           /*!< TIMER0 remapping */
#define AFIO_PCF0_TIMER1_REMAP           BITS(8,9)           /*!< TIMER1 remapping */
#define AFIO_PCF0_TIMER2_REMAP           BITS(10,11)         /*!< TIMER2 remapping */
#define AFIO_PCF0_TIMER3_REMAP           BIT(12)             /*!< TIMER3 remapping */
#define AFIO_PCF0_CAN0_REMAP             BITS(13,14)         /*!< CAN0 remapping */
#define AFIO_PCF0_PD01_REMAP             BIT(15)             /*!< port D0/port D1 mapping on OSC_IN/OSC_OUT */
#define AFIO_PCF0_TIMER4CH3_IREMAP       BIT(16)             /*!< TIMER4 channel3 internal remapping */
#define AFIO_PCF0_ADC0_ETRGINS_REMAP     BIT(17)             /*!< ADC 0 external trigger inserted conversion remapping */
#define AFIO_PCF0_ADC0_ETRGREG_REMAP     BIT(18)             /*!< ADC 0 external trigger regular conversion remapping */
#define AFIO_PCF0_ADC1_ETRGINS_REMAP     BIT(19)             /*!< ADC 1 external trigger inserted conversion remapping */
#define AFIO_PCF0_ADC1_ETRGREG_REMAP     BIT(20)             /*!< ADC 1 external trigger regular conversion remapping */
#define AFIO_PCF0_ENET_REMAP             BIT(21)             /*!< ethernet MAC I/O remapping */
#define AFIO_PCF0_CAN1_REMAP             BIT(22)             /*!< CAN1 remapping */
#define AFIO_PCF0_ENET_PHY_SEL           BIT(23)             /*!< ethernet MII or RMII PHY selection */
#define AFIO_PCF0_SWJ_CFG                BITS(24,26)         /*!< serial wire JTAG configuration */
#define AFIO_PCF0_SPI2_REMAP             BIT(28)             /*!< SPI2/I2S2 remapping */
#define AFIO_PCF0_TIMER1ITI1_REMAP       BIT(29)             /*!< TIMER1 internal trigger 1 remapping */
#define AFIO_PCF0_PTP_PPS_REMAP          BIT(30)             /*!< ethernet PTP PPS remapping */

/* AFIO_EXTISS0 */
#define AFIO_EXTI0_SS                    BITS(0,3)           /*!< EXTI 0 sources selection */
#define AFIO_EXTI1_SS                    BITS(4,7)           /*!< EXTI 1 sources selection */
#define AFIO_EXTI2_SS                    BITS(8,11)          /*!< EXTI 2 sources selection */
#define AFIO_EXTI3_SS                    BITS(12,15)         /*!< EXTI 3 sources selection */

/* AFIO_EXTISS1 */
#define AFIO_EXTI4_SS                    BITS(0,3)           /*!< EXTI 4 sources selection */
#define AFIO_EXTI5_SS                    BITS(4,7)           /*!< EXTI 5 sources selection */
#define AFIO_EXTI6_SS                    BITS(8,11)          /*!< EXTI 6 sources selection */
#define AFIO_EXTI7_SS                    BITS(12,15)         /*!< EXTI 7 sources selection */

/* AFIO_EXTISS2 */
#define AFIO_EXTI8_SS                    BITS(0,3)           /*!< EXTI 8 sources selection */
#define AFIO_EXTI9_SS                    BITS(4,7)           /*!< EXTI 9 sources selection */
#define AFIO_EXTI10_SS                   BITS(8,11)          /*!< EXTI 10 sources selection */
#define AFIO_EXTI11_SS                   BITS(12,15)         /*!< EXTI 11 sources selection */

/* AFIO_EXTISS3 */
#define AFIO_EXTI12_SS                   BITS(0,3)           /*!< EXTI 12 sources selection */
#define AFIO_EXTI13_SS                   BITS(4,7)           /*!< EXTI 13 sources selection */
#define AFIO_EXTI14_SS                   BITS(8,11)          /*!< EXTI 14 sources selection */
#define AFIO_EXTI15_SS                   BITS(12,15)         /*!< EXTI 15 sources selection */

/* AFIO_PCF1 */
#define AFIO_PCF1_TIMER8_REMAP           BIT(5)              /*!< TIMER8 remapping */
#define AFIO_PCF1_TIMER9_REMAP           BIT(6)              /*!< TIMER9 remapping */
#define AFIO_PCF1_TIMER10_REMAP          BIT(7)              /*!< TIMER10 remapping */
#define AFIO_PCF1_TIMER12_REMAP          BIT(8)              /*!< TIMER12 remapping */
#define AFIO_PCF1_TIMER13_REMAP          BIT(9)              /*!< TIMER13 remapping */
#define AFIO_PCF1_EXMC_NADV              BIT(10)             /*!< EXMC_NADV connect/disconnect */

/* AFIO_PCF2 */
#define AFIO_PCF2_DCI_VSYNC_REMAP        BITS(0,1)           /*!< DCI VSYNC remapping */
#define AFIO_PCF2_DCI_D0_REMAP           BITS(2,3)           /*!< DCI D0 remapping */
#define AFIO_PCF2_DCI_D1_REMAP           BITS(4,5)           /*!< DCI D1 remapping */
#define AFIO_PCF2_DCI_D2_REMAP           BITS(6,7)           /*!< DCI D2 remapping */
#define AFIO_PCF2_DCI_D3_REMAP           BITS(8,9)           /*!< DCI D3 remapping */
#define AFIO_PCF2_DCI_D4_REMAP           BITS(10,11)         /*!< DCI D4 remapping */
#define AFIO_PCF2_DCI_D5_REMAP           BITS(12,13)         /*!< DCI D5 remapping */
#define AFIO_PCF2_DCI_D6_REMAP           BITS(14,15)         /*!< DCI D6 remapping */
#define AFIO_PCF2_DCI_D7_REMAP           BITS(16,17)         /*!< DCI D7 remapping */
#define AFIO_PCF2_DCI_D8_REMAP           BITS(18,19)         /*!< DCI D8 remapping */
#define AFIO_PCF2_DCI_D9_REMAP           BITS(20,21)         /*!< DCI D9 remapping */
#define AFIO_PCF2_DCI_D10_REMAP          BITS(22,23)         /*!< DCI D10 remapping */
#define AFIO_PCF2_DCI_D11_REMAP          BITS(24,25)         /*!< DCI D11 remapping */
#define AFIO_PCF2_DCI_D12_REMAP          BIT(26)             /*!< DCI D12 remapping */
#define AFIO_PCF2_DCI_D13_REMAP          BITS(27,28)         /*!< DCI D13 remapping */
#define AFIO_PCF2_DCI_HSYNC_REMAP        BIT(29)             /*!< DCI HSYNC remapping */
#define AFIO_PCF2_PH01_REMAP             BIT(31)             /*!< PH0/PH1 remapping */

/* AFIO_PCF3 */
#define AFIO_PCF3_TLI_B5_PA3_REMAP       BIT(0)              /*!< TLI B5 PA3 remapping */
#define AFIO_PCF3_TLI_VSYNC_PA4_REMAP    BIT(1)              /*!< TLI VSYNC PA4 remapping */
#define AFIO_PCF3_TLI_G2_PA6_REMAP       BIT(2)              /*!< TLI G2 PA6 remapping */
#define AFIO_PCF3_TLI_R6_PA8_REMAP       BIT(3)              /*!< TLI R6 PA8 remapping */
#define AFIO_PCF3_TLI_R4_PA11_REMAP      BIT(4)              /*!< TLI R4 PA11 remapping */
#define AFIO_PCF3_TLI_R5_PA12_REMAP      BIT(5)              /*!< TLI R5 PA12 remapping */
#define AFIO_PCF3_TLI_R3_PB0_REMAP       BIT(6)              /*!< TLI R3 PB0 remapping */
#define AFIO_PCF3_TLI_R6_PB1_REMAP       BIT(7)              /*!< TLI R6 PB1 remapping */
#define AFIO_PCF3_TLI_B6_PB8_REMAP       BIT(8)              /*!< TLI B6 PB8 remapping */
#define AFIO_PCF3_TLI_B7_PB9_REMAP       BIT(9)              /*!< TLI B7 PB9 remapping */
#define AFIO_PCF3_TLI_G4_PB10_REMAP      BIT(10)             /*!< TLI G4 PB10 remapping */
#define AFIO_PCF3_TLI_G5_PB11_REMAP      BIT(11)             /*!< TLI G5 PB11 remapping */
#define AFIO_PCF3_TLI_HSYNC_PC6_REMAP    BIT(12)             /*!< TLI HSYNC PC6 remapping */
#define AFIO_PCF3_TLI_G6_PC7_REMAP       BIT(13)             /*!< TLI G6 PC7 remapping */
#define AFIO_PCF3_TLI_R2_PC10_REMAP      BIT(14)             /*!< TLI R2 PC10 remapping */
#define AFIO_PCF3_TLI_G7_PD3_REMAP       BIT(15)             /*!< TLI G7 PD3 remapping */
#define AFIO_PCF3_TLI_B2_PD6_REMAP       BIT(16)             /*!< TLI B2 PD6 remapping */
#define AFIO_PCF3_TLI_B3_PD10_REMAP      BIT(17)             /*!< TLI B3 PD10 remapping */
#define AFIO_PCF3_TLI_B0_PE4_REMAP       BIT(18)             /*!< TLI B0 PE4 remapping */
#define AFIO_PCF3_TLI_G0_PE5_REMAP       BIT(19)             /*!< TLI G0 PE5 remapping */
#define AFIO_PCF3_TLI_G1_PE6_REMAP       BIT(20)             /*!< TLI G1 PE6 remapping */
#define AFIO_PCF3_TLI_G3_PE11_REMAP      BIT(21)             /*!< TLI G3 PE11 remapping */
#define AFIO_PCF3_TLI_B4_PE12_REMAP      BIT(22)             /*!< TLI B4 PE12 remapping */
#define AFIO_PCF3_TLI_DE_PE13_REMAP      BIT(23)             /*!< TLI DE PE13 remapping */
#define AFIO_PCF3_TLI_CLK_PE14_REMAP     BIT(24)             /*!< TLI CLK PE14 remapping */
#define AFIO_PCF3_TLI_R7_PE15_REMAP      BIT(25)             /*!< TLI R7 PE15 remapping */
#define AFIO_PCF3_TLI_DE_PF10_REMAP      BIT(26)             /*!< TLI DE PF10 remapping */
#define AFIO_PCF3_TLI_R7_PG6_REMAP       BIT(27)             /*!< TLI R7 PG6 remapping */
#define AFIO_PCF3_TLI_CLK_PG7_REMAP      BIT(28)             /*!< TLI CLK PG7 remapping */
#define AFIO_PCF3_TLI_G3_PG10_REMAP      BIT(29)             /*!< TLI G3 PG10 remapping */
#define AFIO_PCF3_TLI_B2_PG10_REMAP      BIT(30)             /*!< TLI B2 PG10 remapping */
#define AFIO_PCF3_TLI_B3_PG11_REMAP      BIT(31)             /*!< TLI B3 PG11 remapping */

/* AFIO_PCF4 */
#define AFIO_PCF4_TLI_B4_PG12_REMAP      BIT(0)              /*!< TLI B4 PG12 remapping  */
#define AFIO_PCF4_TLI_B1_PG12_REMAP      BIT(1)              /*!< TLI B1 PG12 remapping  */
#define AFIO_PCF4_TLI_R0_PH2_REMAP       BIT(2)              /*!< TLI R0 PH2 remapping  */
#define AFIO_PCF4_TLI_R1_PH3_REMAP       BIT(3)              /*!< TLI R1 PH3 remapping  */
#define AFIO_PCF4_TLI_R2_PH8_REMAP       BIT(4)              /*!< TLI R2 PH8 remapping  */
#define AFIO_PCF4_TLI_R3_PH9_REMAP       BIT(5)              /*!< TLI R3 PH9 remapping  */
#define AFIO_PCF4_TLI_R4_PH10_REMAP      BIT(6)              /*!< TLI R4 PH10 remapping  */
#define AFIO_PCF4_TLI_R5_PH11_REMAP      BIT(7)              /*!< TLI R5 PH11 remapping  */
#define AFIO_PCF4_TLI_R6_PH12_REMAP      BIT(8)              /*!< TLI R6 PH12 remapping  */
#define AFIO_PCF4_TLI_G2_PH13_REMAP      BIT(9)              /*!< TLI G2 PH13 remapping  */
#define AFIO_PCF4_TLI_G3_PH14_REMAP      BIT(10)             /*!< TLI G3 PH14 remapping  */
#define AFIO_PCF4_TLI_G4_PH15_REMAP      BIT(11)             /*!< TLI G4 PH15 remapping  */
#define AFIO_PCF4_TLI_G5_PI0_REMAP       BIT(12)             /*!< TLI G5 PI0 remapping  */
#define AFIO_PCF4_TLI_G6_PI1_REMAP       BIT(13)             /*!< TLI G6 PI1 remapping  */
#define AFIO_PCF4_TLI_G7_PI2_REMAP       BIT(14)             /*!< TLI G7 PI2 remapping  */
#define AFIO_PCF4_TLI_B4_PI4_REMAP       BIT(15)             /*!< TLI B4 PI4 remapping  */
#define AFIO_PCF4_TLI_B5_PI5_REMAP       BIT(16)             /*!< TLI B5 PI5 remapping  */
#define AFIO_PCF4_TLI_B6_PI6_REMAP       BIT(17)             /*!< TLI B6 PI6 remapping  */
#define AFIO_PCF4_TLI_B7_PI7_REMAP       BIT(18)             /*!< TLI B7 PI7 remapping  */
#define AFIO_PCF4_TLI_VSYNC_PI9_REMAP    BIT(19)             /*!< TLI VSYNC PI9 remapping  */
#define AFIO_PCF4_TLI_HSYNC_PI10_REMAP   BIT(20)             /*!< TLI HSYNC PI10 remapping  */
#define AFIO_PCF4_TLI_R0_PH4_REMAP       BIT(21)             /*!< TLI R0 PH4 remapping  */
#define AFIO_PCF4_TLI_R1_PI3_REMAP       BIT(22)             /*!< TLI R1 PI3 remapping  */
#define AFIO_PCF4_SPI1_SCK_REMAP         BIT(23)             /*!< SPI1 SCK remapping  */
#define AFIO_PCF4_SPI2_MOSI_REMAP        BIT(24)             /*!< SPI2 MOSI remapping  */

/* AFIO_PCF5 */
#define AFIO_PCF5_I2C2_REMAP0            BIT(0)              /*!< I2C2 remapping 0 */
#define AFIO_PCF5_I2C2_REMAP1            BIT(1)              /*!< I2C2 remapping 1 */
#define AFIO_PCF5_TIMER1_CH0_REMAP       BIT(2)              /*!< TIMER1 CH0 remapping */
#define AFIO_PCF5_TIMER4_REMAP           BIT(3)              /*!< TIMER4 remapping */
#define AFIO_PCF5_TIMER7_CHON_REMAP      BITS(4,5)           /*!< TIMER7 CHON remapping */
#define AFIO_PCF5_TIMER7_CH_REMAP        BIT(6)              /*!< TIMER7 CH remapping */
#define AFIO_PCF5_I2C1_REMAP             BITS(7,8)           /*!< I2C1 remapping */
#define AFIO_PCF5_SPI1_NSCK_REMAP        BITS(9,10)          /*!< SPI1 NSCK remapping */
#define AFIO_PCF5_SPI1_IO_REMAP          BITS(11,12)         /*!< SPI1 IO remapping */
#define AFIO_PCF5_UART3_REMAP            BIT(13)             /*!< UART3 remapping */
#define AFIO_PCF5_TIMER11_REMAP          BIT(14)             /*!< TIMER11 remapping */
#define AFIO_PCF5_CAN0_ADD_REMAP         BIT(15)             /*!< CAN0 ADD remapping */
#define AFIO_PCF5_ENET_TXD3_REMAP        BIT(16)             /*!< ENET TXD3 remapping */
#define AFIO_PCF5_PPS_HI_REMAP           BIT(17)             /*!< ETH_PPS_OUT remapping */
#define AFIO_PCF5_ENET_TXD01_REMAP       BIT(18)             /*!< ETH_TX_EN/ETH_TXD0/ETH_TXD1 remapping */
#define AFIO_PCF5_ENET_CRSCOL_REMAP      BIT(19)             /*!< ETH_MII_CRS/ETH_MII_COL remapping */
#define AFIO_PCF5_ENET_RX_HI_REMAP       BIT(20)             /*!< ETH_RXD2/ETH_RXD3/ETH_RX_ER remapping */
#define AFIO_PCF5_UART6_REMAP            BIT(21)             /*!< UART6 remapping */
#define AFIO_PCF5_USART5_CK_REMAP        BIT(22)             /*!< USART5 CK remapping */
#define AFIO_PCF5_USART5_RTS_REMAP       BIT(23)             /*!< USART5 RTS remapping */
#define AFIO_PCF5_USART5_CTS_REMAP       BIT(24)             /*!< USART5 CTS remapping */
#define AFIO_PCF5_USART5_TX_REMAP        BIT(25)             /*!< USART5 TX remapping */
#define AFIO_PCF5_USART5_RX_REMAP        BIT(26)             /*!< USART5 RX remapping */
#define AFIO_PCF5_EXMC_SDNWE_REMAP       BIT(27)             /*!< EXMC SDNWE remapping */
#define AFIO_PCF5_EXMC_SDCKE0_REMAP      BIT(28)             /*!< EXMC SDCKE0 remapping */
#define AFIO_PCF5_EXMC_SDCKE1_REMAP      BIT(29)             /*!< EXMC SDCKE1 remapping */
#define AFIO_PCF5_EXMC_SDNE0_REMAP       BIT(30)             /*!< EXMC SDNE0 remapping */
#define AFIO_PCF5_EXMC_SDNE1_REMAP       BIT(30)             /*!< EXMC SDNE1 remapping */

/* constants definitions */
typedef FlagStatus bit_status;

/* GPIO mode values set */
#define GPIO_MODE_SET(n, mode)           ((uint32_t)((uint32_t)(mode) << (4U * (n))))
#define GPIO_MODE_MASK(n)                (0xFU << (4U * (n)))

/* GPIO mode definitions */
#define GPIO_MODE_AIN                    ((uint8_t)0x00U)          /*!< analog input mode */
#define GPIO_MODE_IN_FLOATING            ((uint8_t)0x04U)          /*!< floating input mode */
#define GPIO_MODE_IPD                    ((uint8_t)0x28U)          /*!< pull-down input mode */
#define GPIO_MODE_IPU                    ((uint8_t)0x48U)          /*!< pull-up input mode */
#define GPIO_MODE_OUT_OD                 ((uint8_t)0x14U)          /*!< GPIO output with open-drain */
#define GPIO_MODE_OUT_PP                 ((uint8_t)0x10U)          /*!< GPIO output with push-pull */
#define GPIO_MODE_AF_OD                  ((uint8_t)0x1CU)          /*!< AFIO output with open-drain */
#define GPIO_MODE_AF_PP                  ((uint8_t)0x18U)          /*!< AFIO output with push-pull */

/* GPIO output max speed value */
#define GPIO_OSPEED_10MHZ                ((uint8_t)0x01U)          /*!< output max speed 10MHz */
#define GPIO_OSPEED_2MHZ                 ((uint8_t)0x02U)          /*!< output max speed 2MHz */
#define GPIO_OSPEED_50MHZ                ((uint8_t)0x03U)          /*!< output max speed 50MHz */

/* GPIO event output port definitions */
#define GPIO_EVENT_PORT_GPIOA            ((uint8_t)0x00U)          /*!< event output port A */
#define GPIO_EVENT_PORT_GPIOB            ((uint8_t)0x01U)          /*!< event output port B */
#define GPIO_EVENT_PORT_GPIOC            ((uint8_t)0x02U)          /*!< event output port C */
#define GPIO_EVENT_PORT_GPIOD            ((uint8_t)0x03U)          /*!< event output port D */
#define GPIO_EVENT_PORT_GPIOE            ((uint8_t)0x04U)          /*!< event output port E */

/* GPIO output port source definitions */
#define GPIO_PORT_SOURCE_GPIOA           ((uint8_t)0x00U)          /*!< output port source A */
#define GPIO_PORT_SOURCE_GPIOB           ((uint8_t)0x01U)          /*!< output port source B */
#define GPIO_PORT_SOURCE_GPIOC           ((uint8_t)0x02U)          /*!< output port source C */
#define GPIO_PORT_SOURCE_GPIOD           ((uint8_t)0x03U)          /*!< output port source D */
#define GPIO_PORT_SOURCE_GPIOE           ((uint8_t)0x04U)          /*!< output port source E */
#define GPIO_PORT_SOURCE_GPIOF           ((uint8_t)0x05U)          /*!< output port source F */
#define GPIO_PORT_SOURCE_GPIOG           ((uint8_t)0x06U)          /*!< output port source G */
#define GPIO_PORT_SOURCE_GPIOH           ((uint8_t)0x07U)          /*!< output port source H */
#define GPIO_PORT_SOURCE_GPIOI           ((uint8_t)0x08U)          /*!< output port source I */

/* GPIO event output pin definitions */
#define GPIO_EVENT_PIN_0                 ((uint8_t)0x00U)          /*!< GPIO event pin 0 */
#define GPIO_EVENT_PIN_1                 ((uint8_t)0x01U)          /*!< GPIO event pin 1 */
#define GPIO_EVENT_PIN_2                 ((uint8_t)0x02U)          /*!< GPIO event pin 2 */
#define GPIO_EVENT_PIN_3                 ((uint8_t)0x03U)          /*!< GPIO event pin 3 */
#define GPIO_EVENT_PIN_4                 ((uint8_t)0x04U)          /*!< GPIO event pin 4 */
#define GPIO_EVENT_PIN_5                 ((uint8_t)0x05U)          /*!< GPIO event pin 5 */
#define GPIO_EVENT_PIN_6                 ((uint8_t)0x06U)          /*!< GPIO event pin 6 */
#define GPIO_EVENT_PIN_7                 ((uint8_t)0x07U)          /*!< GPIO event pin 7 */
#define GPIO_EVENT_PIN_8                 ((uint8_t)0x08U)          /*!< GPIO event pin 8 */
#define GPIO_EVENT_PIN_9                 ((uint8_t)0x09U)          /*!< GPIO event pin 9 */
#define GPIO_EVENT_PIN_10                ((uint8_t)0x0AU)          /*!< GPIO event pin 10 */
#define GPIO_EVENT_PIN_11                ((uint8_t)0x0BU)          /*!< GPIO event pin 11 */
#define GPIO_EVENT_PIN_12                ((uint8_t)0x0CU)          /*!< GPIO event pin 12 */
#define GPIO_EVENT_PIN_13                ((uint8_t)0x0DU)          /*!< GPIO event pin 13 */
#define GPIO_EVENT_PIN_14                ((uint8_t)0x0EU)          /*!< GPIO event pin 14 */
#define GPIO_EVENT_PIN_15                ((uint8_t)0x0FU)          /*!< GPIO event pin 15 */

/* GPIO output pin source definitions */
#define GPIO_PIN_SOURCE_0                ((uint8_t)0x00U)          /*!< GPIO pin source 0 */
#define GPIO_PIN_SOURCE_1                ((uint8_t)0x01U)          /*!< GPIO pin source 1 */
#define GPIO_PIN_SOURCE_2                ((uint8_t)0x02U)          /*!< GPIO pin source 2 */
#define GPIO_PIN_SOURCE_3                ((uint8_t)0x03U)          /*!< GPIO pin source 3 */
#define GPIO_PIN_SOURCE_4                ((uint8_t)0x04U)          /*!< GPIO pin source 4 */
#define GPIO_PIN_SOURCE_5                ((uint8_t)0x05U)          /*!< GPIO pin source 5 */
#define GPIO_PIN_SOURCE_6                ((uint8_t)0x06U)          /*!< GPIO pin source 6 */
#define GPIO_PIN_SOURCE_7                ((uint8_t)0x07U)          /*!< GPIO pin source 7 */
#define GPIO_PIN_SOURCE_8                ((uint8_t)0x08U)          /*!< GPIO pin source 8 */
#define GPIO_PIN_SOURCE_9                ((uint8_t)0x09U)          /*!< GPIO pin source 9 */
#define GPIO_PIN_SOURCE_10               ((uint8_t)0x0AU)          /*!< GPIO pin source 10 */
#define GPIO_PIN_SOURCE_11               ((uint8_t)0x0BU)          /*!< GPIO pin source 11 */
#define GPIO_PIN_SOURCE_12               ((uint8_t)0x0CU)          /*!< GPIO pin source 12 */
#define GPIO_PIN_SOURCE_13               ((uint8_t)0x0DU)          /*!< GPIO pin source 13 */
#define GPIO_PIN_SOURCE_14               ((uint8_t)0x0EU)          /*!< GPIO pin source 14 */
#define GPIO_PIN_SOURCE_15               ((uint8_t)0x0FU)          /*!< GPIO pin source 15 */

/* GPIO pin definitions */
#define GPIO_PIN_0                       BIT(0)                    /*!< GPIO pin 0 */
#define GPIO_PIN_1                       BIT(1)                    /*!< GPIO pin 1 */
#define GPIO_PIN_2                       BIT(2)                    /*!< GPIO pin 2 */
#define GPIO_PIN_3                       BIT(3)                    /*!< GPIO pin 3 */
#define GPIO_PIN_4                       BIT(4)                    /*!< GPIO pin 4 */
#define GPIO_PIN_5                       BIT(5)                    /*!< GPIO pin 5 */
#define GPIO_PIN_6                       BIT(6)                    /*!< GPIO pin 6 */
#define GPIO_PIN_7                       BIT(7)                    /*!< GPIO pin 7 */
#define GPIO_PIN_8                       BIT(8)                    /*!< GPIO pin 8 */
#define GPIO_PIN_9                       BIT(9)                    /*!< GPIO pin 9 */
#define GPIO_PIN_10                      BIT(10)                   /*!< GPIO pin 10 */
#define GPIO_PIN_11                      BIT(11)                   /*!< GPIO pin 11 */
#define GPIO_PIN_12                      BIT(12)                   /*!< GPIO pin 12 */
#define GPIO_PIN_13                      BIT(13)                   /*!< GPIO pin 13 */
#define GPIO_PIN_14                      BIT(14)                   /*!< GPIO pin 14 */
#define GPIO_PIN_15                      BIT(15)                   /*!< GPIO pin 15 */
#define GPIO_PIN_ALL                     BITS(0,15)                /*!< GPIO pin all */

/* GPIO remap definitions */
/* AFIO_PCF0 and AFIO_PCF1 remap definitions */
#define GPIO_SPI0_REMAP                  ((uint32_t)0x00000001U)   /*!< SPI0 remapping */
#define GPIO_I2C0_REMAP                  ((uint32_t)0x00000002U)   /*!< I2C0 remapping */
#define GPIO_USART0_REMAP                ((uint32_t)0x00000004U)   /*!< USART0 remapping */
#define GPIO_USART1_REMAP                ((uint32_t)0x00000008U)   /*!< USART1 remapping */
#define GPIO_USART2_PARTIAL_REMAP        ((uint32_t)0x00140010U)   /*!< USART2 partial remapping */
#define GPIO_USART2_FULL_REMAP           ((uint32_t)0x00140030U)   /*!< USART2 full remapping */
#define GPIO_TIMER0_PARTIAL_REMAP        ((uint32_t)0x00160040U)   /*!< TIMER0 partial remapping */
#define GPIO_TIMER0_FULL_REMAP           ((uint32_t)0x001600C0U)   /*!< TIMER0 full remapping */
#define GPIO_TIMER1_PARTIAL_REMAP0       ((uint32_t)0x00180100U)   /*!< TIMER1 partial remapping */
#define GPIO_TIMER1_PARTIAL_REMAP1       ((uint32_t)0x00180200U)   /*!< TIMER1 partial remapping */
#define GPIO_TIMER1_FULL_REMAP           ((uint32_t)0x00180300U)   /*!< TIMER1 full remapping */
#define GPIO_TIMER2_PARTIAL_REMAP        ((uint32_t)0x001A0800U)   /*!< TIMER2 partial remapping */
#define GPIO_TIMER2_FULL_REMAP           ((uint32_t)0x001A0C00U)   /*!< TIMER2 full remapping */
#define GPIO_TIMER3_REMAP                ((uint32_t)0x00001000U)   /*!< TIMER3 remapping */
#define GPIO_CAN0_PARTIAL_REMAP          ((uint32_t)0x001D4000U)   /*!< CAN0 partial remapping */
#define GPIO_CAN0_FULL_REMAP             ((uint32_t)0x001D6000U)   /*!< CAN0 full remapping */
#define GPIO_PD01_REMAP                  ((uint32_t)0x00008000U)   /*!< PD01 remapping */
#define GPIO_TIMER4CH3_IREMAP            ((uint32_t)0x00200001U)   /*!< TIMER4 channel3 internal remapping */
#define GPIO_ADC0_ETRGINS_REMAP          ((uint32_t)0x00200002U)   /*!< ADC0 external trigger inserted conversion remapping */
#define GPIO_ADC0_ETRGREG_REMAP          ((uint32_t)0x00200004U)   /*!< ADC0 external trigger regular conversion remapping */
#define GPIO_ADC1_ETRGINS_REMAP          ((uint32_t)0x00200008U)   /*!< ADC1 external trigger inserted conversion remapping */
#define GPIO_ADC1_ETRGREG_REMAP          ((uint32_t)0x00200010U)   /*!< ADC1 external trigger regular conversion remapping */
#define GPIO_ENET_REMAP                  ((uint32_t)0x00200020U)   /*!< ENET remapping */
#define GPIO_CAN1_REMAP                  ((uint32_t)0x00200040U)   /*!< CAN1 remapping */
#define GPIO_SWJ_NONJTRST_REMAP          ((uint32_t)0x00300100U)   /*!< full SWJ(JTAG-DP + SW-DP),but without NJTRST */
#define GPIO_SWJ_SWDPENABLE_REMAP        ((uint32_t)0x00300200U)   /*!< JTAG-DP disabled and SW-DP enabled */
#define GPIO_SWJ_DISABLE_REMAP           ((uint32_t)0x00300400U)   /*!< JTAG-DP disabled and SW-DP disabled */
#define GPIO_SPI2_REMAP                  ((uint32_t)0x00201100U)   /*!< SPI2 remapping */
#define GPIO_TIMER1ITI1_REMAP            ((uint32_t)0x00202000U)   /*!< TIMER1 internal trigger 1 remapping */
#define GPIO_PTP_PPS_REMAP               ((uint32_t)0x00204000U)   /*!< ethernet PTP PPS remapping */
#define GPIO_TIMER8_REMAP                ((uint32_t)0x80000020U)   /*!< TIMER8 remapping */
#define GPIO_TIMER9_REMAP                ((uint32_t)0x80000040U)   /*!< TIMER9 remapping */
#define GPIO_TIMER10_REMAP               ((uint32_t)0x80000080U)   /*!< TIMER10 remapping */
#define GPIO_TIMER12_REMAP               ((uint32_t)0x80000100U)   /*!< TIMER12 remapping */
#define GPIO_TIMER13_REMAP               ((uint32_t)0x80000200U)   /*!< TIMER13 remapping */
#define GPIO_EXMC_NADV_REMAP             ((uint32_t)0x80000400U)   /*!< EXMC_NADV connect/disconnect */

/* AFIO_PCF2 remap definitions */
#define GPIO_PCF2_DCI_VSYNC_PG9_REMAP    ((uint32_t)0x00000001U)   /*!< DCI VSYNC remapped to PG9 */
#define GPIO_PCF2_DCI_VSYNC_PI5_REMAP    ((uint32_t)0x00000003U)   /*!< DCI VSYNC remapped to PI5 */
#define GPIO_PCF2_DCI_D0_PC6_REMAP       ((uint32_t)0x00000004U)   /*!< DCI D0 remapped to PC6 */
#define GPIO_PCF2_DCI_D0_PH9_REMAP       ((uint32_t)0x0000000CU)   /*!< DCI D0 remapped to PH9 */
#define GPIO_PCF2_DCI_D1_PC7_REMAP       ((uint32_t)0x00000010U)   /*!< DCI D1 remapped to PC7 */
#define GPIO_PCF2_DCI_D1_PH10_REMAP      ((uint32_t)0x00000030U)   /*!< DCI D1 remapped to PH10 */
#define GPIO_PCF2_DCI_D2_PE0_REMAP       ((uint32_t)0x00000040U)   /*!< DCI D2 remapped to PE0 */
#define GPIO_PCF2_DCI_D2_PG10_REMAP      ((uint32_t)0x00000080U)   /*!< DCI D2 remapped to PG10 */
#define GPIO_PCF2_DCI_D2_PH11_REMAP      ((uint32_t)0x000000C0U)   /*!< DCI D2 remapped to PH11 */
#define GPIO_PCF2_DCI_D3_PE1_REMAP       ((uint32_t)0x00000100U)   /*!< DCI D3 remapped to PE1 */
#define GPIO_PCF2_DCI_D3_PG11_REMAP      ((uint32_t)0x00000200U)   /*!< DCI D3 remapped to PG11 */
#define GPIO_PCF2_DCI_D3_PH12_REMAP      ((uint32_t)0x00000300U)   /*!< DCI D3 remapped to PH12 */
#define GPIO_PCF2_DCI_D4_PE4_REMAP       ((uint32_t)0x00000400U)   /*!< DCI D4 remapped to PE4 */
#define GPIO_PCF2_DCI_D4_PH14_REMAP      ((uint32_t)0x00000C00U)   /*!< DCI D4 remapped to PH14 */
#define GPIO_PCF2_DCI_D5_PD3_REMAP       ((uint32_t)0x00001000U)   /*!< DCI D5 remapped to PD3 */
#define GPIO_PCF2_DCI_D5_PI4_REMAP       ((uint32_t)0x00003000U)   /*!< DCI D5 remapped to PI4 */
#define GPIO_PCF2_DCI_D6_PE5_REMAP       ((uint32_t)0x00004000U)   /*!< DCI D6 remapped to PE5 */
#define GPIO_PCF2_DCI_D6_PI6_REMAP       ((uint32_t)0x0000C000U)   /*!< DCI D6 remapped to PI6 */
#define GPIO_PCF2_DCI_D7_PE6_REMAP       ((uint32_t)0x00010000U)   /*!< DCI D7 remapped to PE6 */
#define GPIO_PCF2_DCI_D7_PI7_REMAP       ((uint32_t)0x00030000U)   /*!< DCI D7 remapped to PI7 */
#define GPIO_PCF2_DCI_D8_PH6_REMAP       ((uint32_t)0x00040000U)   /*!< DCI D8 remapped to PH6 */
#define GPIO_PCF2_DCI_D8_PI1_REMAP       ((uint32_t)0x000C0000U)   /*!< DCI D8 remapped to PI1 */
#define GPIO_PCF2_DCI_D9_PH7_REMAP       ((uint32_t)0x00100000U)   /*!< DCI D9 remapped to PH7 */
#define GPIO_PCF2_DCI_D9_PI2_REMAP       ((uint32_t)0x00300000U)   /*!< DCI D9 remapped to PI2 */
#define GPIO_PCF2_DCI_D10_PD6_REMAP      ((uint32_t)0x00400000U)   /*!< DCI D10 remapped to PD6 */
#define GPIO_PCF2_DCI_D10_PI3_REMAP      ((uint32_t)0x00C00000U)   /*!< DCI D10 remapped to PI3 */
#define GPIO_PCF2_DCI_D11_PF10_REMAP     ((uint32_t)0x01000000U)   /*!< DCI D11 remapped to PF10 */
#define GPIO_PCF2_DCI_D11_PH15_REMAP     ((uint32_t)0x03000000U)   /*!< DCI D11 remapped to PH15 */
#define GPIO_PCF2_DCI_D12_PG6_REMAP      ((uint32_t)0x04000000U)   /*!< DCI D12 remapped to PG6 */
#define GPIO_PCF2_DCI_D13_PG15_REMAP     ((uint32_t)0x08000000U)   /*!< DCI D12 remapped to PG15 */
#define GPIO_PCF2_DCI_D13_PI0_REMAP      ((uint32_t)0x18000000U)   /*!< DCI D13 remapped to PI0 */
#define GPIO_PCF2_DCI_HSYNC_PH8_REMAP    ((uint32_t)0x20000000U)   /*!< DCI HSYNC to PH8 */
#define GPIO_PCF2_PH01_REMAP             ((uint32_t)0x80000000U)   /*!< PH0/PH1 remapping */

/* AFIO_PCF3 remap definitions */
#define GPIO_PCF3_TLI_B5_PA3_REMAP       ((uint32_t)0x00000001U)   /*!< TLI B5 remapped to PA3 */
#define GPIO_PCF3_TLI_VSYNC_PA4_REMAP    ((uint32_t)0x00000002U)   /*!< TLI VSYNC remapped to PA4 */
#define GPIO_PCF3_TLI_G2_PA6_REMAP       ((uint32_t)0x00000004U)   /*!< TLI G2 remapped to PA6 */
#define GPIO_PCF3_TLI_R6_PA8_REMAP       ((uint32_t)0x00000008U)   /*!< TLI R6 remapped to PA8 */
#define GPIO_PCF3_TLI_R4_PA11_REMAP      ((uint32_t)0x00000010U)   /*!< TLI R4 remapped to PA11 */
#define GPIO_PCF3_TLI_R5_PA12_REMAP      ((uint32_t)0x00000020U)   /*!< TLI R5 remapped to PA12 */
#define GPIO_PCF3_TLI_R3_PB0_REMAP       ((uint32_t)0x00000040U)   /*!< TLI R3 remapped to PB0 */
#define GPIO_PCF3_TLI_R6_PB1_REMAP       ((uint32_t)0x00000080U)   /*!< TLI R6 remapped to PB1 */
#define GPIO_PCF3_TLI_B6_PB8_REMAP       ((uint32_t)0x00000100U)   /*!< TLI B6 remapped to PB8 */
#define GPIO_PCF3_TLI_B7_PB9_REMAP       ((uint32_t)0x00000200U)   /*!< TLI B7 remapped to PB9 */
#define GPIO_PCF3_TLI_G4_PB10_REMAP      ((uint32_t)0x00000400U)   /*!< TLI G4 remapped to PB10 */
#define GPIO_PCF3_TLI_G5_PB11_REMAP      ((uint32_t)0x00000800U)   /*!< TLI G5 remapped to PB11 */
#define GPIO_PCF3_TLI_HSYNC_PC6_REMAP    ((uint32_t)0x00001000U)   /*!< TLI HSYNC remapped to PC6 */
#define GPIO_PCF3_TLI_G6_PC7_REMAP       ((uint32_t)0x00002000U)   /*!< TLI G6 remapped to PC7 */
#define GPIO_PCF3_TLI_R2_PC10_REMAP      ((uint32_t)0x00004000U)   /*!< TLI R2 remapped to PC10 */
#define GPIO_PCF3_TLI_G7_PD3_REMAP       ((uint32_t)0x00008000U)   /*!< TLI G7 remapped to PD3 */
#define GPIO_PCF3_TLI_B2_PD6_REMAP       ((uint32_t)0x00010000U)   /*!< TLI B2 remapped to PD6 */
#define GPIO_PCF3_TLI_B3_PD10_REMAP      ((uint32_t)0x00020000U)   /*!< TLI B3 remapped to PD10 */
#define GPIO_PCF3_TLI_B0_PE4_REMAP       ((uint32_t)0x00040000U)   /*!< TLI B0 remapped to PE4 */
#define GPIO_PCF3_TLI_G0_PE5_REMAP       ((uint32_t)0x00080000U)   /*!< TLI G0 remapped to PE5 */
#define GPIO_PCF3_TLI_G1_PE6_REMAP       ((uint32_t)0x00100000U)   /*!< TLI G1 remapped to PE6 */
#define GPIO_PCF3_TLI_G3_PE11_REMAP      ((uint32_t)0x00200000U)   /*!< TLI G3 remapped to PE11 */
#define GPIO_PCF3_TLI_B4_PE12_REMAP      ((uint32_t)0x00400000U)   /*!< TLI B4 remapped to PE12 */
#define GPIO_PCF3_TLI_DE_PE13_REMAP      ((uint32_t)0x00800000U)   /*!< TLI DE remapped to PE13 */
#define GPIO_PCF3_TLI_CLK_PE14_REMAP     ((uint32_t)0x01000000U)   /*!< TLI CLK remapped to PE14 */
#define GPIO_PCF3_TLI_R7_PE15_REMAP      ((uint32_t)0x02000000U)   /*!< TLI R7 remapped to PE15 */
#define GPIO_PCF3_TLI_DE_PF10_REMAP      ((uint32_t)0x04000000U)   /*!< TLI DE remapped to PF10 */
#define GPIO_PCF3_TLI_R7_PG6_REMAP       ((uint32_t)0x08000000U)   /*!< TLI R7 remapped to PG6 */
#define GPIO_PCF3_TLI_CLK_PG7_REMAP      ((uint32_t)0x10000000U)   /*!< TLI CLK remapped to PG7 */
#define GPIO_PCF3_TLI_G3_PG10_REMAP      ((uint32_t)0x20000000U)   /*!< TLI G3 remapped to PG10 */
#define GPIO_PCF3_TLI_B2_PG10_REMAP      ((uint32_t)0x40000000U)   /*!< TLI B2 remapped to PG10 */
#define GPIO_PCF3_TLI_B3_PG11_REMAP      ((uint32_t)0x80000000U)   /*!< TLI B3 remapped to PG11 */

/* AFIO_PCF4 remap definitions */
#define GPIO_PCF4_TLI_B4_PG12_REMAP      ((uint32_t)0x00000001U)   /*!< TLI B4 remapped to PG12 */
#define GPIO_PCF4_TLI_B1_PG12_REMAP      ((uint32_t)0x00000002U)   /*!< TLI B1 remapped to PG12 */
#define GPIO_PCF4_TLI_R0_PH2_REMAP2      ((uint32_t)0x00000004U)   /*!< TLI R0 remapped to PH2 */
#define GPIO_PCF4_TLI_R1_PH3_REMAP       ((uint32_t)0x00000008U)   /*!< TLI R1 remapped to PH3 */
#define GPIO_PCF4_TLI_R2_PH8_REMAP       ((uint32_t)0x00000010U)   /*!< TLI R2 remapped to PH8 */
#define GPIO_PCF4_TLI_R3_PH9_REMAP       ((uint32_t)0x00000020U)   /*!< TLI R3 remapped to PH9 */
#define GPIO_PCF4_TLI_R4_PH10_REMAP      ((uint32_t)0x00000040U)   /*!< TLI R4 remapped to PH10 */
#define GPIO_PCF4_TLI_R5_PH11_REMAP      ((uint32_t)0x00000080U)   /*!< TLI R5 remapped to PH11 */
#define GPIO_PCF4_TLI_R6_PH12_REMAP      ((uint32_t)0x00000100U)   /*!< TLI R6 remapped to PH12 */
#define GPIO_PCF4_TLI_G2_PH13_REMAP      ((uint32_t)0x00000200U)   /*!< TLI G2 remapped to PH13 */
#define GPIO_PCF4_TLI_G3_PH14_REMAP      ((uint32_t)0x00000400U)   /*!< TLI G3 remapped to PH14 */
#define GPIO_PCF4_TLI_G4_PH15_REMAP      ((uint32_t)0x00000800U)   /*!< TLI G4 remapped to PH15 */
#define GPIO_PCF4_TLI_G5_PI0_REMAP       ((uint32_t)0x00001000U)   /*!< TLI G5 remapped to PI0 */
#define GPIO_PCF4_TLI_G6_PI1_REMAP       ((uint32_t)0x00002000U)   /*!< TLI G6 remapped to PI1 */
#define GPIO_PCF4_TLI_G7_PI2_REMAP       ((uint32_t)0x00004000U)   /*!< TLI G7 remapped to PI2 */
#define GPIO_PCF4_TLI_B4_PI4_REMAP       ((uint32_t)0x00008000U)   /*!< TLI B4 remapped to PI4 */
#define GPIO_PCF4_TLI_B5_PI5_REMAP       ((uint32_t)0x00010000U)   /*!< TLI B5 remapped to PI5 */
#define GPIO_PCF4_TLI_B6_PI6_REMAP       ((uint32_t)0x00020000U)   /*!< TLI B6 remapped to PI6 */
#define GPIO_PCF4_TLI_B7_PI7_REMAP       ((uint32_t)0x00040000U)   /*!< TLI B7 remapped to PI7 */
#define GPIO_PCF4_TLI_VSYNC_PI9_REMAP    ((uint32_t)0x00080000U)   /*!< TLI VSYNC remapped to PI9 */
#define GPIO_PCF4_TLI_HSYNC_PI10_REMAP   ((uint32_t)0x00100000U)   /*!< TLI HSYNC remapped to PI10 */
#define GPIO_PCF4_TLI_R0_PH4_REMAP       ((uint32_t)0x00200000U)   /*!< TLI R0 remapped to PH4 */
#define GPIO_PCF4_TLI_R1_PI3_REMAP       ((uint32_t)0x00400000U)   /*!< TLI R1 remapped to PI3 */
#define GPIO_PCF4_SPI1_SCK_PD3_REMAP     ((uint32_t)0x00800000U)   /*!< SPI1 SCK remapped to PD3 */
#define GPIO_PCF4_SPI2_MOSI_PD6_REMAP    ((uint32_t)0x01000000U)   /*!< SPI2 MOSI remapped to PD6 */

/* AFIO_PCF5 remap definitions */
#define GPIO_PCF5_I2C2_REMAP0            ((uint32_t)0x00000001U)   /*!< I2C2 remapping 0 */
#define GPIO_PCF5_I2C2_REMAP1            ((uint32_t)0x00000002U)   /*!< I2C2 remapping 1 */
#define GPIO_PCF5_TIMER1_CH0_REMAP       ((uint32_t)0x00000004U)   /*!< TIMER1 CH0 remapped to PA5 */
#define GPIO_PCF5_TIMER4_REMAP           ((uint32_t)0x00000008U)   /*!< TIMER4 CH0 remapping */
#define GPIO_PCF5_TIMER7_CHON_REMAP0     ((uint32_t)0x00000020U)   /*!< TIMER7 CHON remapping 0 */
#define GPIO_PCF5_TIMER7_CHON_REMAP1     ((uint32_t)0x00000030U)   /*!< TIMER7 CHON remapping 1 */
#define GPIO_PCF5_TIMER7_CH_REMAP        ((uint32_t)0x00000040U)   /*!< TIMER7 CH remapping */
#define GPIO_PCF5_I2C1_REMAP0            ((uint32_t)0x00000100U)   /*!< I2C1 remapping 0 */
#define GPIO_PCF5_I2C1_REMAP1            ((uint32_t)0x00000180U)   /*!< I2C1 remapping 1 */
#define GPIO_PCF5_SPI1_NSCK_REMAP0       ((uint32_t)0x00000400U)   /*!< SPI1 NSS/SCK remapping 0 */
#define GPIO_PCF5_SPI1_NSCK_REMAP1       ((uint32_t)0x00000600U)   /*!< SPI1 NSS/SCK remapping 1 */
#define GPIO_PCF5_SPI1_IO_REMAP0         ((uint32_t)0x00000800U)   /*!< SPI1 MISO/MOSI remapping 0 */
#define GPIO_PCF5_SPI1_IO_REMAP1         ((uint32_t)0x00001800U)   /*!< SPI1 MISO/MOSI remapping 1 */
#define GPIO_PCF5_UART3_REMAP            ((uint32_t)0x00002000U)   /*!< UART3 remapping */
#define GPIO_PCF5_TIMER11_REMAP          ((uint32_t)0x00004000U)   /*!< TIMER11 remapping */
#define GPIO_PCF5_CAN0_ADD_REMAP         ((uint32_t)0x00008000U)   /*!< CAN0 addition remapping */
#define GPIO_PCF5_ENET_TXD3_REMAP        ((uint32_t)0x00010000U)   /*!< ETH_TXD3 remapped to PE2 */
#define GPIO_PCF5_PPS_HI_REMAP           ((uint32_t)0x00020000U)   /*!< ETH_PPS_OUT remapped to PG8 */
#define GPIO_PCF5_ENET_TXD01_REMAP       ((uint32_t)0x00040000U)   /*!< ETH_TX_EN/ETH_TXD0/ETH_TXD1 remapping */
#define GPIO_PCF5_ENET_CRSCOL_REMAP      ((uint32_t)0x00080000U)   /*!< ETH_MII_CRS/ETH_MII_COL remapping */
#define GPIO_PCF5_ENET_RX_HI_REMAP       ((uint32_t)0x00100000U)   /*!< ETH_RXD2/ETH_RXD3/ETH_RX_ER remapping */
#define GPIO_PCF5_UART6_REMAP            ((uint32_t)0x00200000U)   /*!< UART6 remapping */
#define GPIO_PCF5_USART5_CK_PG7_REMAP    ((uint32_t)0x00400000U)   /*!< USART5 CK remapped to PG7 */
#define GPIO_PCF5_USART5_RTS_PG12_REMAP  ((uint32_t)0x00800000U)   /*!< USART5 RTS remapped to PG12 */
#define GPIO_PCF5_USART5_CTS_PG13_REMAP  ((uint32_t)0x01000000U)   /*!< USART5 CTS remapped to PG13 */
#define GPIO_PCF5_USART5_TX_PG14_REMAP   ((uint32_t)0x02000000U)   /*!< USART5 TX remapped to PG14 */
#define GPIO_PCF5_USART5_RX_PG9_REMAP    ((uint32_t)0x04000000U)   /*!< USART5 RX remapped to PG9 */
#define GPIO_PCF5_EXMC_SDNWE_PC0_REMAP   ((uint32_t)0x08000000U)   /*!< EXMC SDNWE remapped to PC0 */
#define GPIO_PCF5_EXMC_SDCKE0_PC3_REMAP  ((uint32_t)0x10000000U)   /*!< EXMC SDCKE0 remapped to PC3 */
#define GPIO_PCF5_EXMC_SDCKE1_PB5_REMAP  ((uint32_t)0x20000000U)   /*!< EXMC SDCKE1 remapped to PB5 */
#define GPIO_PCF5_EXMC_SDNE0_PC2_REMAP   ((uint32_t)0x40000000U)   /*!< EXMC SDNE0 remapped to PC2 */
#define GPIO_PCF5_EXMC_SDNE1_PB6_REMAP   ((uint32_t)0x80000000U)   /*!< EXMC SDNE1 remapped to PB6 */

/* AFIO port configuration register selection */
#define GPIO_PCF2                        ((uint8_t)0x02U)          /*!< AFIO port configuration register 2 */
#define GPIO_PCF3                        ((uint8_t)0x03U)          /*!< AFIO port configuration register 3 */
#define GPIO_PCF4                        ((uint8_t)0x04U)          /*!< AFIO port configuration register 4 */
#define GPIO_PCF5                        ((uint8_t)0x05U)          /*!< AFIO port configuration register 5*/

/* ethernet MII or RMII PHY selection */
#define GPIO_ENET_PHY_MII                ((uint32_t)0x00000000U)   /*!< configure ethernet MAC for connection with an MII PHY */
#define GPIO_ENET_PHY_RMII               AFIO_PCF0_ENET_PHY_SEL    /*!< configure ethernet MAC for connection with an RMII PHY */

/* function declarations */
/* initialization functions */
/* reset GPIO port */
void gpio_deinit(uint32_t gpio_periph);
/* reset alternate function I/O(AFIO) */
void gpio_afio_deinit(void);
/* GPIO parameter initialization */
void gpio_init(uint32_t gpio_periph, uint32_t mode, uint32_t speed, uint32_t pin);

/* function configuration */
/* set GPIO pin bit */
void gpio_bit_set(uint32_t gpio_periph, uint32_t pin);
/* reset GPIO pin bit */
void gpio_bit_reset(uint32_t gpio_periph, uint32_t pin);
/* write data to the specified GPIO pin */
void gpio_bit_write(uint32_t gpio_periph, uint32_t pin, bit_status bit_value);
/* write data to the specified GPIO port */
void gpio_port_write(uint32_t gpio_periph, uint16_t data);

/* get GPIO pin input status */
FlagStatus gpio_input_bit_get(uint32_t gpio_periph, uint32_t pin);
/* get GPIO port input status */
uint16_t gpio_input_port_get(uint32_t gpio_periph);
/* get GPIO pin output status */
FlagStatus gpio_output_bit_get(uint32_t gpio_periph, uint32_t pin);
/* get GPIO port output status */
uint16_t gpio_output_port_get(uint32_t gpio_periph);

/* configure GPIO pin remap */
void gpio_pin_remap_config(uint32_t gpio_remap, ControlStatus newvalue);
/* configure GPIO pin remap1 */
void gpio_pin_remap1_config(uint8_t remap_reg, uint32_t remap, ControlStatus newvalue);

/* select GPIO pin exti sources */
void gpio_exti_source_select(uint8_t output_port, uint8_t output_pin);
/* configure GPIO pin event output */
void gpio_event_output_config(uint8_t output_port, uint8_t output_pin);
/* enable GPIO pin event output */
void gpio_event_output_enable(void);
/* disable GPIO pin event output */
void gpio_event_output_disable(void);

/* lock GPIO pin bit */
void gpio_pin_lock(uint32_t gpio_periph, uint32_t pin);

/* select ethernet MII or RMII PHY */
void gpio_ethernet_phy_select(uint32_t enet_sel);

#endif /* GD32F20X_GPIO_H */
