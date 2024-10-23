/*!
    \file    gd32e50x_gpio.h
    \brief   definitions for the GPIO

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

#ifndef GD32E50X_GPIO_H
#define GD32E50X_GPIO_H

#include "gd32e50x.h"

/* GPIOx(x=A,B,C,D,E,F,G) definitions */
#define GPIOA                      (GPIO_BASE + 0x00000000U)        /*!< GPIOA bsae address */
#define GPIOB                      (GPIO_BASE + 0x00000400U)        /*!< GPIOB bsae address */
#define GPIOC                      (GPIO_BASE + 0x00000800U)        /*!< GPIOC bsae address */
#define GPIOD                      (GPIO_BASE + 0x00000C00U)        /*!< GPIOD bsae address */
#define GPIOE                      (GPIO_BASE + 0x00001000U)        /*!< GPIOE bsae address */
#define GPIOF                      (GPIO_BASE + 0x00001400U)        /*!< GPIOF bsae address */
#define GPIOG                      (GPIO_BASE + 0x00001800U)        /*!< GPIOG bsae address */

/* AFIO definitions */
#define AFIO                       AFIO_BASE                        /*!< AFIO bsae address */

/* registers definitions */
/* GPIO registers definitions */
#define GPIO_CTL0(gpiox)           REG32((gpiox) + 0x00000000U)     /*!< GPIO port control register 0 */
#define GPIO_CTL1(gpiox)           REG32((gpiox) + 0x00000004U)     /*!< GPIO port control register 1 */
#define GPIO_ISTAT(gpiox)          REG32((gpiox) + 0x00000008U)     /*!< GPIO port input status register */
#define GPIO_OCTL(gpiox)           REG32((gpiox) + 0x0000000CU)     /*!< GPIO port output control register */
#define GPIO_BOP(gpiox)            REG32((gpiox) + 0x00000010U)     /*!< GPIO port bit operation register */
#define GPIO_BC(gpiox)             REG32((gpiox) + 0x00000014U)     /*!< GPIO bit clear register */
#define GPIO_LOCK(gpiox)           REG32((gpiox) + 0x00000018U)     /*!< GPIO port configuration lock register */
#define GPIOx_SPD(gpiox)           REG32((gpiox) + 0x0000003CU)     /*!< GPIO port bit speed register */

/* AFIO registers definitions */
#define AFIO_EC                    REG32(AFIO + 0x00000000U)        /*!< AFIO event control register */
#define AFIO_PCF0                  REG32(AFIO + 0x00000004U)        /*!< AFIO port configuration register 0 */
#define AFIO_EXTISS0               REG32(AFIO + 0x00000008U)        /*!< AFIO port EXTI sources selection register 0 */
#define AFIO_EXTISS1               REG32(AFIO + 0x0000000CU)        /*!< AFIO port EXTI sources selection register 1 */
#define AFIO_EXTISS2               REG32(AFIO + 0x00000010U)        /*!< AFIO port EXTI sources selection register 2 */
#define AFIO_EXTISS3               REG32(AFIO + 0x00000014U)        /*!< AFIO port EXTI sources selection register 3 */
#define AFIO_PCF1                  REG32(AFIO + 0x0000001CU)        /*!< AFIO port configuration register 1 */
#define AFIO_CPSCTL                REG32(AFIO + 0x00000020U)        /*!< IO compensation control register */
#define AFIO_PCFA                  REG32(AFIO + 0x0000003CU)        /*!< AFIO port configuration register A */
#define AFIO_PCFB                  REG32(AFIO + 0x00000040U)        /*!< AFIO port configuration register B */
#define AFIO_PCFC                  REG32(AFIO + 0x00000044U)        /*!< AFIO port configuration register C */
#define AFIO_PCFD                  REG32(AFIO + 0x00000048U)        /*!< AFIO port configuration register D */
#define AFIO_PCFE                  REG32(AFIO + 0x0000004CU)        /*!< AFIO port configuration register E */
#define AFIO_PCFG                  REG32(AFIO + 0x00000054U)        /*!< AFIO port configuration register G */

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

/* GPIO_SPD */
#define GPIO_SPD_SPD0              BIT(0)                    /*!< pin 0 set very high output speed when MDx is 0b11 */
#define GPIO_SPD_SPD1              BIT(1)                    /*!< pin 1 set very high output speed when MDx is 0b11 */
#define GPIO_SPD_SPD2              BIT(2)                    /*!< pin 2 set very high output speed when MDx is 0b11 */
#define GPIO_SPD_SPD3              BIT(3)                    /*!< pin 3 set very high output speed when MDx is 0b11 */
#define GPIO_SPD_SPD4              BIT(4)                    /*!< pin 4 set very high output speed when MDx is 0b11 */
#define GPIO_SPD_SPD5              BIT(5)                    /*!< pin 5 set very high output speed when MDx is 0b11 */
#define GPIO_SPD_SPD6              BIT(6)                    /*!< pin 6 set very high output speed when MDx is 0b11 */
#define GPIO_SPD_SPD7              BIT(7)                    /*!< pin 7 set very high output speed when MDx is 0b11 */
#define GPIO_SPD_SPD8              BIT(8)                    /*!< pin 8 set very high output speed when MDx is 0b11 */
#define GPIO_SPD_SPD9              BIT(9)                    /*!< pin 9 set very high output speed when MDx is 0b11 */
#define GPIO_SPD_SPD10             BIT(10)                   /*!< pin 10 set very high output speed when MDx is 0b11 */
#define GPIO_SPD_SPD11             BIT(11)                   /*!< pin 11 set very high output speed when MDx is 0b11 */
#define GPIO_SPD_SPD12             BIT(12)                   /*!< pin 12 set very high output speed when MDx is 0b11 */
#define GPIO_SPD_SPD13             BIT(13)                   /*!< pin 13 set very high output speed when MDx is 0b11 */
#define GPIO_SPD_SPD14             BIT(14)                   /*!< pin 14 set very high output speed when MDx is 0b11 */
#define GPIO_SPD_SPD15             BIT(15)                   /*!< pin 15 set very high output speed when MDx is 0b11 */

/* AFIO_EC */
#define AFIO_EC_PIN                BITS(0,3)                 /*!< event output pin selection */
#define AFIO_EC_PORT               BITS(4,6)                 /*!< event output port selection */
#define AFIO_EC_EOE                BIT(7)                    /*!< event output enable */

/* AFIO_PCF0 */
#if defined GD32E50X_CL || defined(GD32E508)
/* memory map and bit definitions for GD32E50X_CL and GD32E508 devices */
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
#define AFIO_PCF0_ENET_REMAP             BIT(21)             /*!< ethernet MAC I/O remapping */
#define AFIO_PCF0_CAN1_REMAP             BIT(22)             /*!< CAN1 remapping */
#define AFIO_PCF0_ENET_PHY_SEL           BIT(23)             /*!< ethernet MII or RMII PHY selection */
#define AFIO_PCF0_SWJ_CFG                BITS(24,26)         /*!< serial wire JTAG configuration */
#define AFIO_PCF0_SPI2_REMAP             BIT(28)             /*!< SPI2/I2S2 remapping */
#define AFIO_PCF0_TIMER1ITR1_REMAP       BIT(29)             /*!< TIMER1 internal trigger 1 remapping */
#define AFIO_PCF0_PTP_PPS_REMAP          BIT(30)             /*!< ethernet PTP PPS remapping */
#elif defined GD32EPRT
/* memory map and bit definitions for GD32EPRT devices */
#define AFIO_PCF0_SPI0_REMAP             BIT(0)              /*!< SPI0 remapping */
#define AFIO_PCF0_I2C0_REMAP             BIT(1)              /*!< I2C0 remapping */
#define AFIO_PCF0_USART0_REMAP           BIT(2)              /*!< USART0 remapping */
#define AFIO_PCF0_USART1_REMAP           BIT(3)              /*!< USART1 remapping */
#define AFIO_PCF0_USART2_REMAP           BITS(4,5)           /*!< USART2 remapping */
#define AFIO_PCF0_TIMER0_REMAP           BITS(6,7)           /*!< TIMER0 remapping */
#define AFIO_PCF0_TIMER1_REMAP           BITS(8,9)           /*!< TIMER1 remapping */
#define AFIO_PCF0_TIMER2_REMAP           BITS(10,11)         /*!< TIMER2 remapping */
#define AFIO_PCF0_TIMER3_REMAP           BIT(12)             /*!< TIMER3 remapping */
#define AFIO_PCF0_PD01_REMAP             BIT(15)             /*!< port D0/port D1 mapping on OSC_IN/OSC_OUT */
#define AFIO_PCF0_TIMER4CH3_IREMAP       BIT(16)             /*!< TIMER4 channel3 internal remapping */
#define AFIO_PCF0_ENET_REMAP             BIT(21)             /*!< ethernet MAC I/O remapping */
#define AFIO_PCF0_ENET_PHY_SEL           BIT(23)             /*!< ethernet MII or RMII PHY selection */
#define AFIO_PCF0_SWJ_CFG                BITS(24,26)         /*!< serial wire JTAG configuration */
#define AFIO_PCF0_SPI2_REMAP             BIT(28)             /*!< SPI2/I2S2 remapping */
#define AFIO_PCF0_TIMER1ITR1_REMAP       BIT(29)             /*!< TIMER1 internal trigger 1 remapping */
#define AFIO_PCF0_PTP_PPS_REMAP          BIT(30)             /*!< ethernet PTP PPS remapping */
#else
/* memory map and bit definitions for GD32E50X_HD devices devices */
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
#define AFIO_PCF0_ADC0_ETRGRT_REMAP     BIT(18)             /*!< ADC 0 external trigger routine conversion remapping */
#define AFIO_PCF0_ADC1_ETRGRT_REMAP     BIT(20)             /*!< ADC 1 external trigger routine conversion remapping */
#define AFIO_PCF0_CAN1_REMAP             BIT(22)             /*!< CAN1 remapping */
#define AFIO_PCF0_SWJ_CFG                BITS(24,26)         /*!< serial wire JTAG configuration */
#define AFIO_PCF0_SPI2_REMAP             BIT(28)             /*!< SPI2/I2S2 remapping */
#endif /* GD32E50X_CL and GD32E508 */

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
#define AFIO_PCF1_CTC_REMAP              BITS(11,12)         /*!< CTC remapping */

/* AFIO_CPSCTL */
#define AFIO_CPSCTL_CPS_EN               BIT(0)              /*!< I/O compensation cell enable */
#define AFIO_CPSCTL_CPS_RDY              BIT(8)              /*!< I/O compensation cell is ready or not */

/* AFIO_PCFA */
#define AFIO_PCFA_PA2_AFCFG              BIT(4)              /*!< PA2 AF function configuration bit */
#define AFIO_PCFA_PA3_AFCFG              BIT(6)              /*!< PA3 AF function configuration bit */
#define AFIO_PCFA_PA5_AFCFG              BIT(10)             /*!< PA5 AF function configuration bit */
#define AFIO_PCFA_PA8_AFCFG              BITS(16, 17)        /*!< PA8 AF function configuration bits */
#define AFIO_PCFA_PA9_AFCFG              BITS(18, 19)        /*!< PA9 AF function configuration bits */
#define AFIO_PCFA_PA10_AFCFG             BITS(20, 21)        /*!< PA10 AF function configuration bits */
#define AFIO_PCFA_PA11_AFCFG             BITS(22, 23)        /*!< PA11 AF function configuration bits */
#define AFIO_PCFA_PA12_AFCFG             BITS(24, 25)        /*!< PA12 AF function configuration bits */
#define AFIO_PCFA_PA15_AFCFG             BIT(30)             /*!< PA15 AF function configuration bit */

/* AFIO_PCFB */
#define AFIO_PCFB_PB0_AFCFG              BIT(0)              /*!< PB0 AF function configuration bit */
#define AFIO_PCFB_PB1_AFCFG              BITS(2, 3)          /*!< PB1 AF function configuration bits */
#define AFIO_PCFB_PB2_AFCFG              BITS(4, 5)          /*!< PB2 AF function configuration bits */
#define AFIO_PCFB_PB3_AFCFG              BIT(6)              /*!< PB3 AF function configuration bit */
#define AFIO_PCFB_PB4_AFCFG              BITS(8, 9)          /*!< PB4 AF function configuration bits */
#define AFIO_PCFB_PB5_AFCFG              BITS(10, 11)        /*!< PB5 AF function configuration bits */
#define AFIO_PCFB_PB6_AFCFG              BIT(12)             /*!< PB6 AF function configuration bit */
#define AFIO_PCFB_PB7_AFCFG              BIT(14)             /*!< PB7 AF function configuration bit */
#define AFIO_PCFB_PB8_AFCFG              BITS(16, 17)        /*!< PB8 AF function configuration bits */
#define AFIO_PCFB_PB9_AFCFG              BITS(18, 19)        /*!< PB9 AF function configuration bits */
#define AFIO_PCFB_PB10_AFCFG             BITS(20, 21)        /*!< PB10 AF function configuration bits */
#define AFIO_PCFB_PB11_AFCFG             BITS(22, 23)        /*!< PB11 AF function configuration bits */
#define AFIO_PCFB_PB12_AFCFG             BITS(24, 25)        /*!< PB12 AF function configuration bits */
#define AFIO_PCFB_PB13_AFCFG             BITS(26, 27)        /*!< PB13 AF function configuration bits */
#define AFIO_PCFB_PB14_AFCFG             BITS(28, 29)        /*!< PB14 AF function configuration bits */
#define AFIO_PCFB_PB15_AFCFG             BIT(30)             /*!< PB15 AF function configuration bits */

/* AFIO_PCFC */
#define AFIO_PCFC_PC0_AFCFG              BIT(0)              /*!< PC0 AF function configuration bit */
#define AFIO_PCFC_PC2_AFCFG              BITS(4, 5)          /*!< PC2 AF function configuration bits */
#define AFIO_PCFC_PC3_AFCFG              BIT(6)              /*!< PC3 AF function configuration bit */
#define AFIO_PCFC_PC6_AFCFG              BITS(12, 13)        /*!< PC6 AF function configuration bits */
#define AFIO_PCFC_PC7_AFCFG              BITS(14, 15)        /*!< PC7 AF function configuration bits */
#define AFIO_PCFC_PC8_AFCFG              BITS(16, 17)        /*!< PC8 AF function configuration bits */
#define AFIO_PCFC_PC9_AFCFG              BITS(18, 19)        /*!< PC9 AF function configuration bits */
#define AFIO_PCFC_PC10_AFCFG             BIT(20)             /*!< PC10 AF function configuration bit */
#define AFIO_PCFC_PC11_AFCFG             BITS(22, 23)        /*!< PC11 AF function configuration bits */
#define AFIO_PCFC_PC12_AFCFG             BIT(24)             /*!< PC12 AF function configuration bit */

/* AFIO_PCFD */
#define AFIO_PCFD_PD4_AFCFG              BIT(8)              /*!< PD4 AF function configuration bit */
#define AFIO_PCFD_PD5_AFCFG              BIT(10)             /*!< PD5 AF function configuration bit */

/* AFIO_PCFE */
#define AFIO_PCFE_PE0_AFCFG              BITS(0, 1)          /*!< PE0 AF function configuration bits */
#define AFIO_PCFE_PE1_AFCFG              BITS(2, 3)          /*!< PE1 AF function configuration bits */
#define AFIO_PCFE_PE8_AFCFG              BIT(16)             /*!< PE8 AF function configuration bit */
#define AFIO_PCFE_PE9_AFCFG              BIT(18)             /*!< PE9 AF function configuration bit */
#define AFIO_PCFE_PE10_AFCFG             BIT(20)             /*!< PE10 AF function configuration bit */
#define AFIO_PCFE_PE11_AFCFG             BIT(22)             /*!< PE11 AF function configuration bit */
#define AFIO_PCFE_PE12_AFCFG             BIT(24)             /*!< PE12 AF function configuration bit */
#define AFIO_PCFE_PE13_AFCFG             BIT(26)             /*!< PE13 AF function configuration bit */

/* AFIO_PCFG */
#define AFIO_PCFG_PG6_AFCFG              BIT(12)             /*!< PG6 AF function configuration bit */
#define AFIO_PCFG_PG7_AFCFG              BITS(14, 15)        /*!< PG7 AF function configuration bits */
#define AFIO_PCFG_PG9_AFCFG              BIT(18)             /*!< PG9 AF function configuration bit */
#define AFIO_PCFG_PG10_AFCFG             BIT(20)             /*!< PG10 AF function configuration bit */
#define AFIO_PCFG_PG11_AFCFG             BIT(22)             /*!< PG11 AF function configuration bit */
#define AFIO_PCFG_PG12_AFCFG             BIT(24)             /*!< PG12 AF function configuration bit */
#define AFIO_PCFG_PG13_AFCFG             BIT(26)             /*!< PG13 AF function configuration bit */
#define AFIO_PCFG_PG14_AFCFG             BIT(28)             /*!< PG14 AF function configuration bit */

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
#define GPIO_OSPEED_MAX                  ((uint8_t)0x04U)          /*!< GPIO very high output speed, max speed more than 50MHz */

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

/* AFIO remap mask */
#define PCF0_USART2_REMAP(regval)       (BITS(4,5) & ((uint32_t)(regval) << 4))                           /*!< USART2 remapping */
#define PCF0_TIMER0_REMAP(regval)       (BITS(6,7) & ((uint32_t)(regval) << 6))                           /*!< TIMER0 remapping */
#define PCF0_TIMER1_REMAP(regval)       (BITS(8,9) & ((uint32_t)(regval) << 8))                           /*!< TIMER1 remapping */
#define PCF0_TIMER2_REMAP(regval)       (BITS(10,11) & ((uint32_t)(regval) << 10))                        /*!< TIMER2 remapping */
#define PCF0_CAN0_REMAP(regval)         (BITS(13,14) & ((uint32_t)(regval) << 13))                        /*!< CAN0 remapping */
#define PCF0_SWJ_CFG(regval)            (BITS(24,26) & ((uint32_t)(regval) << 24))                        /*!< serial wire JTAG configuration */
#define PCF1_CTC_REMAP(regval)          (BITS(11,12) & ((uint32_t)(regval) << 11))                        /*!< CTC remapping */

/* GPIO remap definitions */
#define GPIO_SPI0_REMAP                  AFIO_PCF0_SPI0_REMAP                                             /*!< SPI0 remapping */
#define GPIO_I2C0_REMAP                  AFIO_PCF0_I2C0_REMAP                                             /*!< I2C0 remapping */
#define GPIO_USART0_REMAP                AFIO_PCF0_USART0_REMAP                                           /*!< USART0 remapping */
#define GPIO_USART1_REMAP                AFIO_PCF0_USART1_REMAP                                           /*!< USART1 remapping */
#define GPIO_USART2_PARTIAL_REMAP        ((uint32_t)0x00140000U | PCF0_USART2_REMAP(1))                   /*!< USART2 partial remapping */
#define GPIO_USART2_FULL_REMAP           ((uint32_t)0x00140000U | PCF0_USART2_REMAP(3))                   /*!< USART2 full remapping */
#define GPIO_TIMER0_PARTIAL_REMAP        ((uint32_t)0x00160000U | PCF0_TIMER0_REMAP(1))                   /*!< TIMER0 partial remapping */
#define GPIO_TIMER0_FULL_REMAP           ((uint32_t)0x00160000U | PCF0_TIMER0_REMAP(3))                   /*!< TIMER0 full remapping */
#define GPIO_TIMER1_PARTIAL_REMAP0       ((uint32_t)0x00180000U | PCF0_TIMER1_REMAP(1))                   /*!< TIMER1 partial remapping */
#define GPIO_TIMER1_PARTIAL_REMAP1       ((uint32_t)0x00180000U | PCF0_TIMER1_REMAP(2))                   /*!< TIMER1 partial remapping */
#define GPIO_TIMER1_FULL_REMAP           ((uint32_t)0x00180000U | PCF0_TIMER1_REMAP(3))                   /*!< TIMER1 full remapping */
#define GPIO_TIMER2_PARTIAL_REMAP        ((uint32_t)0x001A0000U | PCF0_TIMER2_REMAP(2))                   /*!< TIMER2 partial remapping */
#define GPIO_TIMER2_FULL_REMAP           ((uint32_t)0x001A0000U | PCF0_TIMER2_REMAP(3))                   /*!< TIMER2 full remapping */
#define GPIO_TIMER3_REMAP                AFIO_PCF0_TIMER3_REMAP                                           /*!< TIMER3 remapping */
#define GPIO_CAN0_PARTIAL_REMAP          ((uint32_t)0x001D0000U | PCF0_CAN0_REMAP(2))                     /*!< CAN0 partial remapping */
#define GPIO_CAN0_FULL_REMAP             ((uint32_t)0x001D0000U | PCF0_CAN0_REMAP(3))                     /*!< CAN0 full remapping */
#define GPIO_PD01_REMAP                  AFIO_PCF0_PD01_REMAP                                             /*!< PD01 remapping */
#define GPIO_TIMER4CH3_IREMAP            ((uint32_t)0x00200000U | (AFIO_PCF0_TIMER4CH3_IREMAP >> 16))     /*!< TIMER4 channel3 internal remapping */
#if defined(GD32E50X_HD)
#define GPIO_ADC0_ETRGRT_REMAP          ((uint32_t)0x00200000U | (AFIO_PCF0_ADC0_ETRGRT_REMAP >> 16))   /*!< ADC0 external trigger routine conversion remapping(only for GD32E50X_HD devices) */
#define GPIO_ADC1_ETRGRT_REMAP          ((uint32_t)0x00200000U | (AFIO_PCF0_ADC1_ETRGRT_REMAP >> 16))   /*!< ADC1 external trigger routine conversion remapping(only for GD32E50X_HD devices) */
#endif /* GD32E50X_HD*/
#if (defined(GD32E50X_CL) || defined(GD32E508) || defined(GD32EPRT))
#define GPIO_ENET_REMAP                  ((uint32_t)0x00200000U | (AFIO_PCF0_ENET_REMAP >> 16))           /*!< ENET remapping(only for GD32E50X_CL and GD32E508 devices) */
#endif /* GD32E50X_CL||GD32E508 */
#define GPIO_CAN1_REMAP                  ((uint32_t)0x00200000U | (AFIO_PCF0_CAN1_REMAP >> 16))           /*!< CAN1 remapping(only for GD32E50X_CL and GD32E508 devices) */
#define GPIO_SWJ_NONJTRST_REMAP          ((uint32_t)0x00300000U | (PCF0_SWJ_CFG(1) >> 16))                /*!< full SWJ(JTAG-DP + SW-DP),but without NJTRST */
#define GPIO_SWJ_SWDPENABLE_REMAP        ((uint32_t)0x00300000U | (PCF0_SWJ_CFG(2) >> 16))                /*!< JTAG-DP disabled and SW-DP enabled */
#define GPIO_SWJ_DISABLE_REMAP           ((uint32_t)0x00300000U | (PCF0_SWJ_CFG(4) >> 16))                /*!< JTAG-DP disabled and SW-DP disabled */
#define GPIO_SPI2_REMAP                  ((uint32_t)0x00200000U | (AFIO_PCF0_SPI2_REMAP >> 16))           /*!< SPI2 remapping*/
#if defined(GD32E50X_CL) || defined(GD32E508)
#define GPIO_TIMER1ITR1_REMAP            ((uint32_t)0x00200000U | (AFIO_PCF0_TIMER1ITR1_REMAP >> 16))     /*!< TIMER1 internal trigger 1 remapping(only for GD32E50X_CL and GD32E508 devices) */
#define GPIO_PTP_PPS_REMAP               ((uint32_t)0x00200000U | (AFIO_PCF0_PTP_PPS_REMAP >> 16))        /*!< ethernet PTP PPS remapping(only for GD32E50X_CL and GD32E508 devices) */
#endif /* GD32E50X_CL||GD32E508 */
#define GPIO_TIMER8_REMAP                ((uint32_t)0x80000000U | AFIO_PCF1_TIMER8_REMAP)                 /*!< TIMER8 remapping */
#define GPIO_TIMER9_REMAP                ((uint32_t)0x80000000U | AFIO_PCF1_TIMER9_REMAP)                 /*!< TIMER9 remapping */
#define GPIO_TIMER10_REMAP               ((uint32_t)0x80000000U | AFIO_PCF1_TIMER10_REMAP)                /*!< TIMER10 remapping */
#define GPIO_TIMER12_REMAP               ((uint32_t)0x80000000U | AFIO_PCF1_TIMER12_REMAP)                /*!< TIMER12 remapping */
#define GPIO_TIMER13_REMAP               ((uint32_t)0x80000000U | AFIO_PCF1_TIMER13_REMAP)                /*!< TIMER13 remapping */
#define GPIO_EXMC_NADV_REMAP             ((uint32_t)0x80000000U | AFIO_PCF1_EXMC_NADV)                    /*!< EXMC_NADV connect/disconnect */
#define GPIO_CTC_REMAP0                  ((uint32_t)0x801B0000U | PCF1_CTC_REMAP(1))                      /*!< CTC remapping(PD15) */
#define GPIO_CTC_REMAP1                  ((uint32_t)0x801B0000U | PCF1_CTC_REMAP(2))                      /*!< CTC remapping(PF0) */

/* AFIO_PCFA AFCFG mask */
#define PCFA_PA8_AFCFG(regval)            (BITS(16, 17) & ((uint32_t)(regval) << 16))                      /*!< PA8 AFCFG */
#define PCFA_PA9_AFCFG(regval)            (BITS(18, 19) & ((uint32_t)(regval) << 18))                      /*!< PA9 AFCFG */
#define PCFA_PA10_AFCFG(regval)           (BITS(20, 21) & ((uint32_t)(regval) << 20))                      /*!< PA10 AFCFG */
#define PCFA_PA11_AFCFG(regval)           (BITS(22, 23) & ((uint32_t)(regval) << 22))                      /*!< PA11 AFCFG */
#define PCFA_PA12_AFCFG(regval)           (BITS(24, 25) & ((uint32_t)(regval) << 24))                      /*!< PA12 AFCFG */

/* AFIO_PCFB AFCFG mask */
#define PCFB_PB1_AFCFG(regval)            (BITS(2, 3) & ((uint32_t)(regval) << 2))                         /*!< PB1 AFCFG */
#define PCFB_PB2_AFCFG(regval)            (BITS(4, 5) & ((uint32_t)(regval) << 4))                         /*!< PB2 AFCFG */
#define PCFB_PB4_AFCFG(regval)            (BITS(8, 9) & ((uint32_t)(regval) << 8))                         /*!< PB4 AFCFG */
#define PCFB_PB5_AFCFG(regval)            (BITS(10, 11) & ((uint32_t)(regval) << 10))                      /*!< PB5 AFCFG */
#define PCFB_PB8_AFCFG(regval)            (BITS(16, 17) & ((uint32_t)(regval) << 16))                      /*!< PB8 AFCFG */
#define PCFB_PB9_AFCFG(regval)            (BITS(18, 19) & ((uint32_t)(regval) << 18))                      /*!< PB9 AFCFG */
#define PCFB_PB10_AFCFG(regval)           (BITS(20, 21) & ((uint32_t)(regval) << 20))                      /*!< PB10 AFCFG */
#define PCFB_PB11_AFCFG(regval)           (BITS(22, 23) & ((uint32_t)(regval) << 22))                      /*!< PB11 AFCFG */
#define PCFB_PB12_AFCFG(regval)           (BITS(24, 25) & ((uint32_t)(regval) << 24))                      /*!< PB12 AFCFG */
#define PCFB_PB13_AFCFG(regval)           (BITS(26, 27) & ((uint32_t)(regval) << 26))                      /*!< PB13 AFCFG */
#define PCFB_PB14_AFCFG(regval)           (BITS(28, 29) & ((uint32_t)(regval) << 28))                      /*!< PB14 AFCFG */

/* AFIO_PCFC AFCFG mask */
#define PCFC_PC2_AFCFG(regval)            (BITS(4, 5) & ((uint32_t)(regval) << 4))                         /*!< PC2 AFCFG */
#define PCFC_PC6_AFCFG(regval)            (BITS(12, 13) & ((uint32_t)(regval) << 12))                      /*!< PC6 AFCFG */
#define PCFC_PC7_AFCFG(regval)            (BITS(14, 15) & ((uint32_t)(regval) << 14))                      /*!< PC7 AFCFG */
#define PCFC_PC8_AFCFG(regval)            (BITS(16, 17) & ((uint32_t)(regval) << 16))                      /*!< PC8 AFCFG */
#define PCFC_PC9_AFCFG(regval)            (BITS(18, 19) & ((uint32_t)(regval) << 18))                      /*!< PC9 AFCFG */
#define PCFC_PC11_AFCFG(regval)           (BITS(22, 23) & ((uint32_t)(regval) << 22))                      /*!< PC11 AFCFG */

/* AFIO_PCFE AFCFG mask */
#define PCFE_PE0_AFCFG(regval)            (BITS(0, 1) & ((uint32_t)(regval)))                              /*!< PE0 AFCFG */
#define PCFE_PE1_AFCFG(regval)            (BITS(2, 3) & ((uint32_t)(regval) << 2))                         /*!< PE1 AFCFG */

/* AFIO_PCFG AFCFG mask */
#define PCFG_PG7_AFCFG(regval)            (BITS(14, 15) & ((uint32_t)(regval) << 14))                      /*!< PG7 AFCFG */

/* GPIOA AF function definitions */
#define AFIO_PA2_CMP1_CFG                 AFIO_PCFA_PA2_AFCFG                                              /*!< configure PA2 alternate function to CMP1 */
#define AFIO_PA3_USBHS_CFG                AFIO_PCFA_PA3_AFCFG                                              /*!< configure PA3 alternate function to USBHS */
#define AFIO_PA5_USBHS_CFG                AFIO_PCFA_PA5_AFCFG                                              /*!< configure PA5 alternate function to USBHS */
#define AFIO_PA8_I2C2_CFG                 ((uint32_t)0x00300000U | (PCFA_PA8_AFCFG(1) >> 16))              /*!< configure PA8 alternate function to I2C2 */
#define AFIO_PA8_SHRTIMER_CFG             ((uint32_t)0x00300000U | (PCFA_PA8_AFCFG(2) >> 16))              /*!< configure PA8 alternate function to SHRTIMER */
#define AFIO_PA9_CAN2_CFG                 ((uint32_t)0x00320000U | (PCFA_PA9_AFCFG(1) >> 16))              /*!< configure PA9 alternate function to CAN2 */
#define AFIO_PA9_I2C2_CFG                 ((uint32_t)0x00320000U | (PCFA_PA9_AFCFG(2) >> 16))              /*!< configure PA9 alternate function to I2C2 */
#define AFIO_PA9_SHRTIMER_CFG             ((uint32_t)0x00320000U | (PCFA_PA9_AFCFG(3) >> 16))              /*!< configure PA9 alternate function to SHRTIMER */
#define AFIO_PA10_CAN2_CFG                ((uint32_t)0x00340000U | (PCFA_PA10_AFCFG(1) >> 16))             /*!< configure PA10 alternate function to CAN2 */
#define AFIO_PA10_CMP5_CFG                ((uint32_t)0x00340000U | (PCFA_PA10_AFCFG(2) >> 16))             /*!< configure PA10 alternate function to CMP5 */
#define AFIO_PA10_SHRTIMER_CFG            ((uint32_t)0x00340000U | (PCFA_PA10_AFCFG(3) >> 16))             /*!< configure PA10 alternate function to SHRTIMER */
#define AFIO_PA11_USART5_CFG              ((uint32_t)0x00360000U | (PCFA_PA11_AFCFG(1) >> 16))             /*!< configure PA11 alternate function to USART5 */
#define AFIO_PA11_SHRTIMER_CFG            ((uint32_t)0x00360000U | (PCFA_PA11_AFCFG(2) >> 16))             /*!< configure PA11 alternate function to SHRTIMER */
#define AFIO_PA12_CMP1_CFG                ((uint32_t)0x00380000U | (PCFA_PA12_AFCFG(1) >> 16))             /*!< configure PA12 alternate function to CMP1 */
#define AFIO_PA12_USART5_CFG              ((uint32_t)0x00380000U | (PCFA_PA12_AFCFG(2) >> 16))             /*!< configure PA12 alternate function to USART5 */
#define AFIO_PA12_SHRTIMER_CFG            ((uint32_t)0x00380000U | (PCFA_PA12_AFCFG(3) >> 16))             /*!< configure PA12 alternate function to SHRTIMER */
#define AFIO_PA15_SHRTIMER_CFG            ((uint32_t)0x00200000U | AFIO_PCFA_PA15_AFCFG >> 16)             /*!< configure PA15 alternate function to SHRTIMER */

/* GPIOB AF function definitions */
#define AFIO_PB0_USBHS_CFG                ((uint32_t)0x01000000U | AFIO_PCFB_PB0_AFCFG)                     /*!< configure PB0 alternate function to USBHS */
#define AFIO_PB1_CMP3_CFG                 ((uint32_t)0x01120000U | PCFB_PB1_AFCFG(1))                       /*!< configure PB1 alternate function to CMP3 */
#define AFIO_PB1_USBHS_CFG                ((uint32_t)0x01120000U | PCFB_PB1_AFCFG(2))                       /*!< configure PB1 alternate function to USBHS */
#define AFIO_PB1_SHRTIMER_CFG             ((uint32_t)0x01120000U | PCFB_PB1_AFCFG(3))                       /*!< configure PB1 alternate function to SHRTIMER */
#define AFIO_PB2_USBHS_CFG                ((uint32_t)0x01140000U | PCFB_PB2_AFCFG(2))                       /*!< configure PB2 alternate function to USBHS */
#define AFIO_PB2_SHRTIMER_CFG             ((uint32_t)0x01140000U | PCFB_PB2_AFCFG(1))                       /*!< configure PB2 alternate function to SHRTIMER */
#define AFIO_PB3_SHRTIMER_CFG             ((uint32_t)0x01000000U | AFIO_PCFB_PB3_AFCFG)                     /*!< configure PB3 alternate function to SHRTIMER */
#define AFIO_PB4_I2S2_CFG                 ((uint32_t)0x01180000U | PCFB_PB4_AFCFG(1))                       /*!< configure PB4 alternate function to I2S2 */
#define AFIO_PB4_I2C2_CFG                 ((uint32_t)0x01180000U | PCFB_PB4_AFCFG(2))                       /*!< configure PB4 alternate function to I2C2 */
#define AFIO_PB4_SHRTIMER_CFG             ((uint32_t)0x01180000U | PCFB_PB4_AFCFG(3))                       /*!< configure PB4 alternate function to SHRTIMER */
#define AFIO_PB5_I2C2_CFG                 ((uint32_t)0x011A0000U | PCFB_PB5_AFCFG(1))                       /*!< configure PB5 alternate function to I2C2 */
#define AFIO_PB5_USBHS_CFG                ((uint32_t)0x011A0000U | PCFB_PB5_AFCFG(2))                       /*!< configure PB5 alternate function to USBHS */
#define AFIO_PB5_SHRTIMER_CFG             ((uint32_t)0x011A0000U | PCFB_PB5_AFCFG(3))                       /*!< configure PB5 alternate function to SHRTIMER */
#define AFIO_PB6_SHRTIMER_CFG             ((uint32_t)0x01000000U | AFIO_PCFB_PB6_AFCFG)                     /*!< configure PB6 alternate function to SHRTIMER */
#define AFIO_PB7_SHRTIMER_CFG             ((uint32_t)0x01000000U | AFIO_PCFB_PB7_AFCFG)                     /*!< configure PB7 alternate function to SHRTIMER */
#define AFIO_PB8_I2C2_CFG                 ((uint32_t)0x01300000U | (PCFB_PB8_AFCFG(1) >> 16))               /*!< configure PB8 alternate function to I2C2 */
#define AFIO_PB8_SHRTIMER_CFG             ((uint32_t)0x01300000U | (PCFB_PB8_AFCFG(2) >> 16))               /*!< configure PB8 alternate function to SHRTIMER */
#define AFIO_PB9_CMP1_CFG                 ((uint32_t)0x01320000U | (PCFB_PB9_AFCFG(1) >> 16))               /*!< configure PB9 alternate function to CMP1 */
#define AFIO_PB9_SHRTIMER_CFG             ((uint32_t)0x01320000U | (PCFB_PB9_AFCFG(2) >> 16))               /*!< configure PB9 alternate function to SHRTIMER */
#define AFIO_PB10_CAN2_CFG                ((uint32_t)0x01340000U | (PCFB_PB10_AFCFG(1) >> 16))              /*!< configure PB10 alternate function to CAN2 */
#define AFIO_PB10_USBHS_CFG               ((uint32_t)0x01340000U | (PCFB_PB10_AFCFG(2) >> 16))              /*!< configure PB10 alternate function to USBHS */
#define AFIO_PB10_SHRTIMER_CFG            ((uint32_t)0x01340000U | (PCFB_PB10_AFCFG(3) >> 16))              /*!< configure PB10 alternate function to SHRTIMER */
#define AFIO_PB11_CAN2_CFG                ((uint32_t)0x01360000U | (PCFB_PB11_AFCFG(1) >> 16))              /*!< configure PB11 alternate function to CAN2 */
#define AFIO_PB11_USBHS_CFG               ((uint32_t)0x01360000U | (PCFB_PB11_AFCFG(2) >> 16))              /*!< configure PB11 alternate function to USBHS */
#define AFIO_PB11_SHRTIMER_CFG            ((uint32_t)0x01360000U | (PCFB_PB11_AFCFG(3) >> 16))              /*!< configure PB11 alternate function to SHRTIMER */
#define AFIO_PB12_USBHS_CFG               ((uint32_t)0x01380000U | (PCFB_PB12_AFCFG(2) >> 16))              /*!< configure PB12 alternate function to USBHS */
#define AFIO_PB12_SHRTIMER_CFG            ((uint32_t)0x01380000U | (PCFB_PB12_AFCFG(1) >> 16))              /*!< configure PB12 alternate function to SHRTIMER */
#define AFIO_PB13_USBHS_CFG               ((uint32_t)0x013A0000U | (PCFB_PB13_AFCFG(2) >> 16))              /*!< configure PB13 alternate function to USBHS */
#define AFIO_PB13_SHRTIMER_CFG            ((uint32_t)0x013A0000U | (PCFB_PB13_AFCFG(1) >> 16))              /*!< configure PB13 alternate function to SHRTIMER */
#define AFIO_PB14_I2S1_CFG                ((uint32_t)0x013C0000U | (PCFB_PB14_AFCFG(1) >> 16))              /*!< configure PB14 alternate function to I2S1 */
#define AFIO_PB14_SHRTIMER_CFG            ((uint32_t)0x013C0000U | (PCFB_PB14_AFCFG(2) >> 16))              /*!< configure PB14 alternate function to SHRTIMER */
#define AFIO_PB15_SHRTIMER_CFG            ((uint32_t)0x01200000U | (AFIO_PCFB_PB15_AFCFG >> 16))            /*!< configure PB15 alternate function to SHRTIMER */

/* GPIOC AF function definitions */
#define AFIO_PC0_USBHS_CFG                ((uint32_t)0x02000000U | AFIO_PCFC_PC0_AFCFG)                     /*!< configure PC0 alternate function to USBHS */
#define AFIO_PC2_I2S1_CFG                 ((uint32_t)0x02140000U | PCFC_PC2_AFCFG(1))                       /*!< configure PC2 alternate function to I2S1 */
#define AFIO_PC2_USBHS_CFG                ((uint32_t)0x02140000U | PCFC_PC2_AFCFG(2))                       /*!< configure PC2 alternate function to USBHS */
#define AFIO_PC3_USBHS_CFG                ((uint32_t)0x02000000U | AFIO_PCFC_PC3_AFCFG)                     /*!< configure PC3 alternate function to USBHS */
#define AFIO_PC6_CMP5_CFG                 ((uint32_t)0x021C0000U | PCFC_PC6_AFCFG(1))                       /*!< configure PC6 alternate function to CMP5 */
#define AFIO_PC6_USART5_CFG               ((uint32_t)0x021C0000U | PCFC_PC6_AFCFG(2))                       /*!< configure PC6 alternate function to USART5 */
#define AFIO_PC6_SHRTIMER_CFG             ((uint32_t)0x021C0000U | PCFC_PC6_AFCFG(3))                       /*!< configure PC6 alternate function to SHRTIMER */
#define AFIO_PC7_USART5_CFG               ((uint32_t)0x021E0000U | PCFC_PC7_AFCFG(2))                       /*!< configure PC7 alternate function to USART5 */
#define AFIO_PC7_SHRTIMER_CFG             ((uint32_t)0x021E0000U | PCFC_PC7_AFCFG(1))                       /*!< configure PC7 alternate function to SHRTIMER */
#define AFIO_PC8_USART5_CFG               ((uint32_t)0x02300000U | (PCFC_PC8_AFCFG(2) >> 16))               /*!< configure PC8 alternate function to USART5 */
#define AFIO_PC8_SHRTIMER_CFG             ((uint32_t)0x02300000U | (PCFC_PC8_AFCFG(1) >> 16))               /*!< configure PC8 alternate function to SHRTIMER */
#define AFIO_PC9_I2C2_CFG                 ((uint32_t)0x02320000U | (PCFC_PC9_AFCFG(2) >> 16))               /*!< configure PC9 alternate function to I2C2 */
#define AFIO_PC9_SHRTIMER_CFG             ((uint32_t)0x02320000U | (PCFC_PC9_AFCFG(1) >> 16))               /*!< configure PC9 alternate function to SHRTIMER */
#define AFIO_PC10_I2C2_CFG                ((uint32_t)0x02200000U | (AFIO_PCFC_PC10_AFCFG >> 16))            /*!< configure PC10 alternate function to I2C2 */
#define AFIO_PC11_I2S2_CFG                ((uint32_t)0x02360000U | (PCFC_PC11_AFCFG(2) >> 16))              /*!< configure PC11 alternate function to I2S2 */
#define AFIO_PC11_SHRTIMER_CFG            ((uint32_t)0x02360000U | (PCFC_PC11_AFCFG(1) >> 16))              /*!< configure PC11 alternate function to SHRTIMER */
#define AFIO_PC12_SHRTIMER_CFG            ((uint32_t)0x02200000U | (AFIO_PCFC_PC12_AFCFG >> 16))            /*!< configure PC12 alternate function to SHRTIMER */

/* GPIOD AF function definitions */
#define AFIO_PD4_SHRTIMER_CFG             ((uint32_t)0x03000000U | AFIO_PCFD_PD4_AFCFG)                     /*!< configure PD4 alternate function to SHRTIMER */
#define AFIO_PD5_SHRTIMER_CFG             ((uint32_t)0x03000000U | AFIO_PCFD_PD5_AFCFG)                     /*!< configure PD5 alternate function to SHRTIMER */

/* GPIOE AF function definitions */
#define AFIO_PE0_CAN2_CFG                 ((uint32_t)0x04100000U | PCFE_PE0_AFCFG(1))                       /*!< configure PE0 alternate function to CAN2 */
#define AFIO_PE0_SHRTIMER_CFG             ((uint32_t)0x04100000U | PCFE_PE0_AFCFG(2))                       /*!< configure PE0 alternate function to SHRTIMER */
#define AFIO_PE1_CAN2_CFG                 ((uint32_t)0x04120000U | PCFE_PE1_AFCFG(1))                       /*!< configure PE1 alternate function to CAN2 */
#define AFIO_PE1_SHRTIMER_CFG             ((uint32_t)0x04120000U | PCFE_PE1_AFCFG(2))                       /*!< configure PE1 alternate function to SHRTIMER */
#define AFIO_PE8_CMP1_CFG                 ((uint32_t)0x04200000U | (AFIO_PCFE_PE8_AFCFG >> 16))             /*!< configure PE8 alternate function to CMP1 */
#define AFIO_PE9_CMP3_CFG                 ((uint32_t)0x04200000U | (AFIO_PCFE_PE9_AFCFG >> 16))             /*!< configure PE9 alternate function to CMP3 */
#define AFIO_PE10_CMP5_CFG                ((uint32_t)0x04200000U | (AFIO_PCFE_PE10_AFCFG >> 16))            /*!< configure PE10 alternate function to CMP5 */
#define AFIO_PE11_CMP5_CFG                ((uint32_t)0x04200000U | (AFIO_PCFE_PE11_AFCFG >> 16))            /*!< configure PE11 alternate function to CMP5 */
#define AFIO_PE12_CMP3_CFG                ((uint32_t)0x04200000U | (AFIO_PCFE_PE12_AFCFG >> 16))            /*!< configure PE12 alternate function to CMP3 */
#define AFIO_PE13_CMP1_CFG                ((uint32_t)0x04200000U | (AFIO_PCFE_PE13_AFCFG >> 16))            /*!< configure PE13 alternate function to CMP1 */

/* GPIOG AF function definitions */
#define AFIO_PG6_SHRTIMER_CFG             ((uint32_t)0x06000000U | AFIO_PCFG_PG6_AFCFG)                     /*!< configure PG6 alternate function to SHRTIMER_CFG */
#define AFIO_PG7_USART5_CFG               ((uint32_t)0x061E0000U | PCFG_PG7_AFCFG(1))                       /*!< configure PG7 alternate function to USART5 */
#define AFIO_PG7_SHRTIMER_CFG             ((uint32_t)0x061E0000U | PCFG_PG7_AFCFG(2))                       /*!< configure PG7 alternate function to SHRTIMER */
#define AFIO_PG9_USART5_CFG               ((uint32_t)0x06200000U | (AFIO_PCFG_PG9_AFCFG >> 16))             /*!< configure PG9 alternate function to USART5 */
#define AFIO_PG10_SHRTIMER_CFG            ((uint32_t)0x06200000U | (AFIO_PCFG_PG10_AFCFG >> 16))            /*!< configure PG10 alternate function to SHRTIMER */
#define AFIO_PG11_SHRTIMER_CFG            ((uint32_t)0x06200000U | (AFIO_PCFG_PG11_AFCFG >> 16))            /*!< configure PG11 alternate function to SHRTIMER */
#define AFIO_PG12_SHRTIMER_CFG            ((uint32_t)0x06200000U | (AFIO_PCFG_PG12_AFCFG >> 16))            /*!< configure PG12 alternate function to SHRTIMER */
#define AFIO_PG13_SHRTIMER_CFG            ((uint32_t)0x06200000U | (AFIO_PCFG_PG13_AFCFG >> 16))            /*!< configure PG13 alternate function to SHRTIMER */
#define AFIO_PG14_USART5_CFG              ((uint32_t)0x06200000U | (AFIO_PCFG_PG14_AFCFG >> 16))            /*!< configure PG14 alternate function to USART5 */

#if (defined(GD32E50X_CL) || defined(GD32E508) || defined(GD32EPRT))
/* ethernet MII or RMII PHY selection */
#define GPIO_ENET_PHY_MII                ((uint32_t)0x00000000U)                                            /*!< configure ethernet MAC for connection with an MII PHY */
#define GPIO_ENET_PHY_RMII               AFIO_PCF0_ENET_PHY_SEL                                             /*!< configure ethernet MAC for connection with an RMII PHY */
#endif /* GD32E50X_CL||GD32E508||GD32EPRT */

/* I/O compensation cell enable/disable */
#define GPIO_COMPENSATION_ENABLE         AFIO_CPSCTL_CPS_EN                                                 /*!< I/O compensation cell is enable */
#define GPIO_COMPENSATION_DISABLE        ((uint32_t)0x00000000U)                                            /*!< I/O compensation cell is disable */

/* function declarations */
/* reset GPIO port */
void gpio_deinit(uint32_t gpio_periph);
/* reset alternate function I/O(AFIO) */
void gpio_afio_deinit(void);
/* GPIO parameter initialization */
void gpio_init(uint32_t gpio_periph, uint32_t mode, uint32_t speed, uint32_t pin);

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
void gpio_pin_remap_config(uint32_t remap, ControlStatus newvalue);
/* configure AFIO port alternate function */
void gpio_afio_port_config(uint32_t afio_function, ControlStatus newvalue);

#if (defined(GD32E50X_CL) || defined(GD32E508) || defined(GD32EPRT))
/* select ethernet MII or RMII PHY */
void gpio_ethernet_phy_select(uint32_t enet_sel);
#endif /* GD32E50X_CL||GD32E508||GD32EPRT */

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
/* configure the I/O compensation cell */
void gpio_compensation_config(uint32_t compensation);
/* check the I/O compensation cell is ready or not */
FlagStatus gpio_compensation_flag_get(void);

#endif /* GD32E50X_GPIO_H */
