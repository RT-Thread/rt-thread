/*!
    \file  gd32vf103_gpio.h
    \brief definitions for the GPIO
    
    \version 2019-06-5, V1.0.0, firmware for GD32VF103
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

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

#ifndef GD32VF103_GPIO_H
#define GD32VF103_GPIO_H

#include "gd32vf103.h"

/* GPIOx(x=A,B,C,D,E) definitions */
#define GPIOA                      (GPIO_BASE + 0x00000000U)
#define GPIOB                      (GPIO_BASE + 0x00000400U)
#define GPIOC                      (GPIO_BASE + 0x00000800U)
#define GPIOD                      (GPIO_BASE + 0x00000C00U)
#define GPIOE                      (GPIO_BASE + 0x00001000U)

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

/* bits definitions */
/* GPIO_CTL0 */
#define GPIO_CTL0_MD0              BITS(0, 1)                /*!< port 0 mode bits */
#define GPIO_CTL0_CTL0             BITS(2, 3)                /*!< pin 0 configuration bits */
#define GPIO_CTL0_MD1              BITS(4, 5)                /*!< port 1 mode bits */
#define GPIO_CTL0_CTL1             BITS(6, 7)                /*!< pin 1 configuration bits */
#define GPIO_CTL0_MD2              BITS(8, 9)                /*!< port 2 mode bits */
#define GPIO_CTL0_CTL2             BITS(10, 11)              /*!< pin 2 configuration bits */
#define GPIO_CTL0_MD3              BITS(12, 13)              /*!< port 3 mode bits */
#define GPIO_CTL0_CTL3             BITS(14, 15)              /*!< pin 3 configuration bits */
#define GPIO_CTL0_MD4              BITS(16, 17)              /*!< port 4 mode bits */
#define GPIO_CTL0_CTL4             BITS(18, 19)              /*!< pin 4 configuration bits */
#define GPIO_CTL0_MD5              BITS(20, 21)              /*!< port 5 mode bits */
#define GPIO_CTL0_CTL5             BITS(22, 23)              /*!< pin 5 configuration bits */
#define GPIO_CTL0_MD6              BITS(24, 25)              /*!< port 6 mode bits */
#define GPIO_CTL0_CTL6             BITS(26, 27)              /*!< pin 6 configuration bits */
#define GPIO_CTL0_MD7              BITS(28, 29)              /*!< port 7 mode bits */
#define GPIO_CTL0_CTL7             BITS(30, 31)              /*!< pin 7 configuration bits */

/* GPIO_CTL1 */
#define GPIO_CTL1_MD8              BITS(0, 1)                /*!< port 8 mode bits */
#define GPIO_CTL1_CTL8             BITS(2, 3)                /*!< pin 8 configuration bits */
#define GPIO_CTL1_MD9              BITS(4, 5)                /*!< port 9 mode bits */
#define GPIO_CTL1_CTL9             BITS(6, 7)                /*!< pin 9 configuration bits */
#define GPIO_CTL1_MD10             BITS(8, 9)                /*!< port 10 mode bits */
#define GPIO_CTL1_CTL10            BITS(10, 11)              /*!< pin 10 configuration bits */
#define GPIO_CTL1_MD11             BITS(12, 13)              /*!< port 11 mode bits */
#define GPIO_CTL1_CTL11            BITS(14, 15)              /*!< pin 11 configuration bits */
#define GPIO_CTL1_MD12             BITS(16, 17)              /*!< port 12 mode bits */
#define GPIO_CTL1_CTL12            BITS(18, 19)              /*!< pin 12 configuration bits */
#define GPIO_CTL1_MD13             BITS(20, 21)              /*!< port 13 mode bits */
#define GPIO_CTL1_CTL13            BITS(22, 23)              /*!< pin 13 configuration bits */
#define GPIO_CTL1_MD14             BITS(24, 25)              /*!< port 14 mode bits */
#define GPIO_CTL1_CTL14            BITS(26, 27)              /*!< pin 14 configuration bits */
#define GPIO_CTL1_MD15             BITS(28, 29)              /*!< port 15 mode bits */
#define GPIO_CTL1_CTL15            BITS(30, 31)              /*!< pin 15 configuration bits */

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
#define AFIO_EC_PIN                BITS(0, 3)                /*!< event output pin selection */
#define AFIO_EC_PORT               BITS(4, 6)                /*!< event output port selection */
#define AFIO_EC_EOE                BIT(7)                    /*!< event output enable */

/* AFIO_PCF0 */
/* memory map and bit definitions for GD32F10X_CL devices */
#define AFIO_PCF0_SPI0_REMAP             BIT(0)              /*!< SPI0 remapping */
#define AFIO_PCF0_I2C0_REMAP             BIT(1)              /*!< I2C0 remapping */
#define AFIO_PCF0_USART0_REMAP           BIT(2)              /*!< USART0 remapping */
#define AFIO_PCF0_USART1_REMAP           BIT(3)              /*!< USART1 remapping */
#define AFIO_PCF0_USART2_REMAP           BITS(4, 5)          /*!< USART2 remapping */
#define AFIO_PCF0_TIMER0_REMAP           BITS(6, 7)          /*!< TIMER0 remapping */
#define AFIO_PCF0_TIMER1_REMAP           BITS(8, 9)          /*!< TIMER1 remapping */
#define AFIO_PCF0_TIMER2_REMAP           BITS(10, 11)        /*!< TIMER2 remapping */
#define AFIO_PCF0_TIMER3_REMAP           BIT(12)             /*!< TIMER3 remapping */
#define AFIO_PCF0_CAN_REMAP              BITS(13, 14)        /*!< CAN remapping */
#define AFIO_PCF0_PD01_REMAP             BIT(15)             /*!< port D0/port D1 mapping on OSC_IN/OSC_OUT */
#define AFIO_PCF0_TIMER4CH3_IREMAP       BIT(16)             /*!< TIMER3 channel3 internal remapping */
#define AFIO_PCF0_SWJ_CFG                BITS(24, 26)        /*!< serial wire JTAG configuration */
#define AFIO_PCF0_SPI2_REMAP             BIT(28)             /*!< SPI2/I2S2 remapping */
#define AFIO_PCF0_TIMER1_ITI1_REMAP      BIT(29)             /*!< TIMER1 internal trigger 1 remapping */

/* AFIO_EXTISS0 */
#define AFIO_EXTI0_SS                    BITS(0, 3)          /*!< EXTI 0 sources selection */
#define AFIO_EXTI1_SS                    BITS(4, 7)          /*!< EXTI 1 sources selection */
#define AFIO_EXTI2_SS                    BITS(8, 11)         /*!< EXTI 2 sources selection */
#define AFIO_EXTI3_SS                    BITS(12, 15)        /*!< EXTI 3 sources selection */

/* AFIO_EXTISS1 */
#define AFIO_EXTI4_SS                    BITS(0, 3)          /*!< EXTI 4 sources selection */
#define AFIO_EXTI5_SS                    BITS(4, 7)          /*!< EXTI 5 sources selection */
#define AFIO_EXTI6_SS                    BITS(8, 11)         /*!< EXTI 6 sources selection */
#define AFIO_EXTI7_SS                    BITS(12, 15)        /*!< EXTI 7 sources selection */

/* AFIO_EXTISS2 */
#define AFIO_EXTI8_SS                    BITS(0, 3)          /*!< EXTI 8 sources selection */
#define AFIO_EXTI9_SS                    BITS(4, 7)          /*!< EXTI 9 sources selection */
#define AFIO_EXTI10_SS                   BITS(8, 11)         /*!< EXTI 10 sources selection */
#define AFIO_EXTI11_SS                   BITS(12, 15)        /*!< EXTI 11 sources selection */

/* AFIO_EXTISS3 */
#define AFIO_EXTI12_SS                   BITS(0, 3)          /*!< EXTI 12 sources selection */
#define AFIO_EXTI13_SS                   BITS(4, 7)          /*!< EXTI 13 sources selection */
#define AFIO_EXTI14_SS                   BITS(8, 11)         /*!< EXTI 14 sources selection */
#define AFIO_EXTI15_SS                   BITS(12, 15)        /*!< EXTI 15 sources selection */

/* AFIO_PCF1 */
#define AFIO_PCF1_EXMC_NADV              BIT(10)             /*!< EXMC_NADV connect/disconnect */

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
#define GPIO_PIN_ALL                     BITS(0, 15)               /*!< GPIO pin all */

/* GPIO remap definitions */
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
#define GPIO_CAN1_REMAP                  ((uint32_t)0x00200040U)   /*!< CAN1 remapping */
#define GPIO_SWJ_NONJTRST_REMAP          ((uint32_t)0x00300100U)   /*!< full SWJ(JTAG-DP + SW-DP),but without NJTRST */
#define GPIO_SWJ_SWDPENABLE_REMAP        ((uint32_t)0x00300200U)   /*!< JTAG-DP disabled */
#define GPIO_SWJ_DISABLE_REMAP           ((uint32_t)0x00300400U)   /*!< JTAG-DP disabled */
#define GPIO_SPI2_REMAP                  ((uint32_t)0x00201100U)   /*!< SPI2 remapping */
#define GPIO_TIMER1ITI1_REMAP            ((uint32_t)0x00202000U)   /*!< TIMER1 internal trigger 1 remapping */
#define GPIO_EXMC_NADV_REMAP             ((uint32_t)0x80000400U)   /*!< EXMC_NADV connect/disconnect */

/* function declarations */
/* reset GPIO port */
void gpio_deinit(uint32_t gpio_periph);
/* reset alternate function I/O(AFIO) */
void gpio_afio_deinit(void);
/* GPIO parameter initialization */
void gpio_init(uint32_t gpio_periph,uint32_t mode,uint32_t speed,uint32_t pin);

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

#endif /* GD32VF103_GPIO_H */
