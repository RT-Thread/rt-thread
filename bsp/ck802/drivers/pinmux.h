/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     pinmux.h
 * @brief    Header file for the pinmux
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#ifndef PHOBOS_PINMUX_H
#define PHOBOS_PINMUX_H

#include <stdint.h>
#include "pin_name.h"

void phobos_ioreuse_initial(void);
int32_t pin_mux(pin_name_t pin, uint16_t function);

/* IOMUX0L function definition */
#define PA0_UART0_TX      0x00000000
#define PA0_PWM_CH0       0x00000001
#define PA0_UART0_SIROUT  0x00000003
#define PA1_UART0_RX      0x00000000
#define PA1_PWM_CH1       0x00000004
#define PA1_UART0_SIRIN   0x0000000C
#define PA2_UART0_CTS     0x00000000
#define PA2_PWM_CH2       0x00000010
#define PA2_SPI0_CLK      0x00000020
#define PA3_UART0_TRS     0x00000000
#define PA3_PWM_CH3       0x00000040
#define PA3_SPI0_TX       0x00000080
#define PA4_I2C0_SCL      0x00000000
#define PA4_PWM_CH4       0x00000100
#define PA4_SPI0_RX       0x00000200
#define PA5_I2C0_SDA      0x00000000
#define PA5_PWM_CH5       0x00000400
#define PA5_SPI0_CS       0x00000800
#define PA6_SPI0_CLK      0x00000000
#define PA6_ETB_TRIG0     0x00001000
#define PA6_I2C0_SCL      0x00002000
#define PA7_SPI_TX        0x00000000
#define PA7_ETB_TRIG1     0x00004000
#define PA7_I2C0_SDA      0x00008000
#define PA8_SPI0_TX       0x00000000
#define PA8_PWM_FAULT     0x00010000
#define PA8_I2C1_SCL      0x00020000
#define PA9_SPI0_CS       0x00000000
#define PA9_PWM_CH0       0x00040000
#define PA9_I2C1_SDA      0x00080000
#define PA10_UART1_TX     0x00000000
#define PA10_PWM_CH1      0x00100000
#define PA10_UART1_SIROUT 0x00300000
#define PA11_UART1_RX     0x00000000
#define PA11_PWM_CH2      0x00400000
#define PA11_UART1_SIRIN  0x00C00000
#define PA12_UART1_CTS    0x00000000
#define PA12_PWM_CH3      0x01000000
#define PA12_SPI1_CLK     0x02000000
#define PA13_UART1_RTS    0x00000000
#define PA13_PWM_CH4      0x04000000
#define PA13_SPI1_TX      0x08000000
#define PA14_I2C1_SCL     0x00000000
#define PA14_PWM_CH5      0x10000000
#define PA14_SPI1_RX      0x20000000
#define PA15_I2C1_SDA     0x00000000
#define PA15_ETB_TRIG0    0x40000000
#define PA15_SPI1_CS0     0x80000000

/* IOMUX0H function definition */
#define PA16_SPI1_CLK     0x00000000
#define PA16_ETB_TRIG1    0x00000001
#define PA17_SPI1_TX      0x00000000
#define PA17_PWM_FAULT    0x00000004
#define PA18_SPI1_RX      0x00000000
#define PA18_PWM_CH0      0x00000010
#define PA19_SPI1_CS0     0x00000000
#define PA19_PWM_CH1      0x00000040
#define PA20_UART2_RX     0x00000000
#define PA20_PWM_CH2      0x00000100
#define PA21_SPI1_CS2     0x00000000
#define PA21_PWM_CH3      0x00000400
#define PA22_UART2_RX     0x00000000
#define PA22_PWM_CH4      0x00001000
#define PA22_UART2_SIRI   0x00003000
#define PA23_UART2_TX     0x00000000
#define PA23_PWM_CH5      0x00004000
#define PA23_UART2_SIROUT 0x0000C000
#define PA24_UART2_CTS    0x00000000
#define PA24_ETB_TRIG0    0x00010000
#define PA24_SPI1_CS1     0x00020000
#define PA25_UART2_RTS    0x00000000
#define PA25_ETB_TRIG1    0x00040000
#define PA25_SPI1_CS2     0x00080000
#define PA26_UART3_TX     0x00000000
#define PA26_PWM_FAULT    0x00100000
#define PA26_UART3_SIROUT 0x00300000
#define PA27_UART3_RX     0x00000000
#define PA27_PWM_CH0      0x00400000
#define PA27_UART3_SIRIN  0x00C00000
#define PA28_I2S_MCLK     0x00000000
#define PA28_PWM_CH1      0x01000000
#define PA29_I2S_SCLK     0x00000000
#define PA29_PWM_CH2      0x04000000
#define PA30_I2S_WSCLK    0x00000000
#define PA30_PWM_CH3      0x10000000
#define PA31_I2S_SDA      0x00000000
#define PA31_I2C0_SCL     0x40000000
#define PA31_PWM_CH4      0x80000000

/* IOMUX1L function definition */
#define PB0_ADC0       0x00000000
#define PB0_I2C0_SDA   0x00000001
#define PB0_PWM_CH5    0x00000002
#define PB1_ADC1       0x00000000
#define PB1_I2C1_SCL   0x00000004
#define PB1_USI_SCLK   0x00000008
#define PB2_ADC2       0x00000000
#define PB2_I2C1_SDA   0x00000010
#define PB2_USI_SD0    0x00000020
#define PB3_ADC3       0x00000000
#define PB3_SPI1_CLK   0x00000040
#define PB3_USI_SD1    0x00000080
#define PB4_ADC4       0x00000000
#define PB4_SPI1_TX    0x00000100
#define PB4_USI_NSS    0x00000200
#define PB5_ADC5       0x00000000
#define PB5_SPI1_RX    0x00000400
#define PB5_USI_SCLK   0x00000800
#define PB6_ADC6       0x00000000
#define PB6_SPI1_CS0   0x00001000
#define PB6_USI_SD0    0x00002000
#define PB7_ADC7       0x00000000
#define PB7_SPI1_CS1   0x00004000
#define PB7_USI_SD1    0x00008000
#define PB8_ETB_TRIG0  0x00000000
#define PB8_SPI1_CS2   0x00010000
#define PB8_USI_NSS    0x00020000
#define PB9_ETB_TRIG1  0x00000000
#define PB9_UART3_CTS  0x00040000
#define PB10_PWM_FAULT 0x00000000
#define PB10_UART3_RTS 0x00100000


/* flag as identification */
#define GPIO_SET_BIT0  0x00000001
#define GPIO_SET_BIT1  0x00000002
#define GPIO_SET_BIT2  0x00000004
#define GPIO_SET_BIT3  0x00000008
#define GPIO_SET_BIT4  0x00000010
#define GPIO_SET_BIT5  0x00000020
#define GPIO_SET_BIT6  0x00000040
#define GPIO_SET_BIT7  0x00000080
#define GPIO_SET_BIT8  0x00000100
#define GPIO_SET_BIT9  0x00000200
#define GPIO_SET_BIT10 0x00000400
#define GPIO_SET_BIT11 0x00000800
#define GPIO_SET_BIT12 0x00001000
#define GPIO_SET_BIT13 0x00002000
#define GPIO_SET_BIT14 0x00004000
#define GPIO_SET_BIT15 0x00008000
#define GPIO_SET_BIT16 0x00010000
#define GPIO_SET_BIT17 0x00020000
#define GPIO_SET_BIT18 0x00040000
#define GPIO_SET_BIT19 0x00080000
#define GPIO_SET_BIT20 0x00100000
#define GPIO_SET_BIT21 0x00200000
#define GPIO_SET_BIT22 0x00400000
#define GPIO_SET_BIT23 0x00800000
#define GPIO_SET_BIT24 0x01000000
#define GPIO_SET_BIT25 0x02000000
#define GPIO_SET_BIT26 0x04000000
#define GPIO_SET_BIT27 0x08000000
#define GPIO_SET_BIT28 0x10000000
#define GPIO_SET_BIT29 0x20000000
#define GPIO_SET_BIT30 0x40000000
#define GPIO_SET_BIT31 0x80000000

/******************************************************************************
 * phobos gpio control and gpio reuse function
 * selecting regester adddress
 ******************************************************************************/

#define PHOBOS_GIPO0_PORTCTL_REG 0x50018008
#define PHOBOS_GIPO1_PORTCTL_REG 0x60018008
#define PHOBOS_IOMUX0L_REG       0x50018100
#define PHOBOS_IOMUX0H_REG       0x50018104
#define PHOBOS_IOMUX1L_REG       0x50018108

/*************basic gpio reuse v1.0********************************************
 * UART0(PA0,PA1)
 * UART1(PA10,PA11)
 * UART2(PA22,PA23)
 * UART3(PA26,PA27)
 * IIS(PA24,PA25,PA26,PA27)
 * SPI1(PA16,PA17,PA18)
 * IIC0(PA4,PA5)
 ******************************************************************************/
#define GPIO0_REUSE_EN                (GPIO_SET_BIT0|GPIO_SET_BIT1|GPIO_SET_BIT4|GPIO_SET_BIT5|GPIO_SET_BIT6|GPIO_SET_BIT9|GPIO_SET_BIT10|GPIO_SET_BIT11|GPIO_SET_BIT16|GPIO_SET_BIT17|GPIO_SET_BIT18|GPIO_SET_BIT22|GPIO_SET_BIT23|GPIO_SET_BIT26|GPIO_SET_BIT27)
#define GPIO1_REUSE_EN                (GPIO_SET_BIT0)
#define IOMUX0L_FUNCTION_SEL          (PA0_UART0_TX|PA1_UART0_RX|PA4_I2C0_SCL|PA5_I2C0_SDA|PA6_ETB_TRIG0|PA9_PWM_CH0|PA10_UART1_TX|PA11_UART1_RX)
#define IOMUX0H_FUNCTION_SEL          (PA16_SPI1_CLK|PA17_SPI1_TX|PA18_SPI1_RX|PA22_UART2_RX|PA23_UART2_TX|PA26_UART3_TX|PA27_UART3_RX)
#define IOMUX1L_FUNCTION_SEL          (PB0_ADC0)

#define PWM_GPIO0_REUSE_EN          (GPIO0_REUSE_EN|GPIO_SET_BIT0|GPIO_SET_BIT1|GPIO_SET_BIT2|GPIO_SET_BIT12|GPIO_SET_BIT13|GPIO_SET_BIT14)
#define PWM_IOMUX0L_FUNCTION_SEL    (IOMUX0L_FUNCTION_SEL|PA0_PWM_CH0|PA1_PWM_CH1|PA2_PWM_CH2|PA12_PWM_CH3|PA13_PWM_CH4|PA14_PWM_CH5)

#endif /* PHOBOS_PINMUX_H */
