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
 * @file     pn_name.h
 * @brief    header file for the pin_name
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#ifndef _PINNAMES_H
#define _PINNAMES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    PA0_TXD0_PWM0_XX_SIROUT0 = 0,
    PA1_RXD0_PWM1_XX_SIRIN0,
    PA2_CTS0_PWM2_SPI0CLK_XX,
    PA3_RTS0_PWM3_SPI0TX_XX,
    PA4_SCL0_PWM4_SPI0RX_XX,
    PA5_SDA0_PWM5_SPI0CS_XX,
    PA6_SPI0CLK_PWMTRIG0_SCL0_XX,
    PA7_SPI0TX_PWMTRIG1_SDA0_XX,
    PA8_SPI0RX_TRIGFAULT_SCL1_XX,
    PA9_SPI0CS_PWM0_SDA1_XX,
    PA10_TXD1_PWM1_XX_SIROUT1,
    PA11_RXD1_PWM2_XX_SIRIN1,
    PA12_CTS1_PWM3_SPI1CLK_XX,
    PA13_RTS1_PWM4_SPI1TX_XX,
    PA14_SCL1_PWM5_SPI1RX_XX,
    PA15_SDA1_PWMTRIG0_SPI1CS0_XX,
    PA16_SPI1CLK_PWMTRIG1_XX_XX,
    PA17_SPI1TX_PWMFAULT_XX_XX,
    PA18_SPI1RX_PWM0_XX_XX,
    PA19_SPI1CS0_PWM1_XX_XX,
    PA20_SPI1CS1_PWM2_XX_XX,
    PA21_SPI1CS2_PWM3_XX_XX,
    PA22_RXD2_PWM4_XX_SIRIN2,
    PA23_TXD2_PWM5_XX_SIROUT2,
    PA24_CTS2_PWMTRIG0_SPI1CS1_XX,
    PA25_XX_PWMTRIG1_SPI1CS2_XX,
    PA26_TXD3_PWMFAULT_XX_SIROUT3,
    PA27_RXD3_PWM0_XX_SIRIN3,
    PA28_I2SMCLK_PWM1_XX_XX,
    PA29_I2SSCLK_PWM2_XX_XX,
    PA30_I2SWSCLK_PWM3_XX_XX,
    PA31_I2SSDA__SCL0_PWM4_XX,
    PB0_ADC0_SDA0_PWM5_XX,
    PB1_ADC1_SCL1_USISCLK_XX,
    PB2_ADC2_SDA1_USISD0_XX,
    PB3_ADC3_SPI1CLK_USISD1_XX,
    PB4_ADC4_SPI1TX_USINSS_XX,
    PB5_ADC5_SPI1RX_USISCLK_XX,
    PB6_ADC6_SPI1CS0_USISD0_XX,
    PB7_ADC7_SPI1CS1_USISD1_XX,
    PB8_PWMTRIG0_SPI1CS2_USINSS_XX,
    PB9_PWMTRIG1_CTS3_XX_XX,
    PB10_PWMFAULT_RTS3_XX_XX
}
pin_name_t;

typedef enum
{
    PORTA = 0,
    PORTB = 1
} port_name_t;

#ifdef __cplusplus
}
#endif

#endif
