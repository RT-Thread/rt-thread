/*****************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_gpio.h
 **
 ** A detailed description is available at
 ** @link GpioGroup Gpio description @endlink
 **
 **   - 2018-10-12 CDT First version for Device Driver Library of Gpio.
 **
 ******************************************************************************/

#ifndef __HC32F460_GPIO_H__
#define __HC32F460_GPIO_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

#if (DDL_GPIO_ENABLE == DDL_ON)

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup GpioGroup General Purpose Input/Output(GPIO)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
  /**
 *******************************************************************************
 ** \brief GPIO Configuration Mode enumeration
 **
 ******************************************************************************/
typedef enum en_pin_mode
{
    Pin_Mode_In  = 0,                   ///< GPIO Input mode
    Pin_Mode_Out = 1,                   ///< GPIO Output mode
    Pin_Mode_Ana = 2,                   ///< GPIO Analog mode
}en_pin_mode_t;

/**
 *******************************************************************************
 ** \brief GPIO Drive Capacity enumeration
 **
 ******************************************************************************/
typedef enum en_pin_drv
{
    Pin_Drv_L = 0,                      ///< Low Drive Capacity
    Pin_Drv_M = 1,                      ///< Middle Drive Capacity
    Pin_Drv_H = 2,                      ///< High Drive Capacity
}en_pin_drv_t;

/**
 *******************************************************************************
 ** \brief GPIO Output Type enumeration
 ******************************************************************************/
typedef enum en_pin_o_type
{
    Pin_OType_Cmos = 0,                 ///< CMOS
    Pin_OType_Od   = 1,                 ///< Open Drain
}en_pin_o_type_t;


typedef enum en_debug_port
{
    TCK_SWCLK   =   1 << 0,             ///< TCK or SWCLK
    TMS_SWDIO   =   1 << 1,             ///< TMS or SWDIO
    TDO_SWO     =   1 << 2,             ///< TOD or SWD
    TDI         =   1 << 3,             ///< TDI
    TRST        =   1 << 4,             ///< TRest
    ALL_DBG_PIN =   0x1Fu               ///< All above
}en_debug_port_t;
/**
 *******************************************************************************
 ** \brief GPIO Port Index enumeration
 ******************************************************************************/
typedef enum en_port
{
    PortA = 0,                          ///< port group A
    PortB = 1,                          ///< port group B
    PortC = 2,                          ///< port group C
    PortD = 3,                          ///< port group D
    PortE = 4,                          ///< port group E
    PortH = 5,                          ///< port group H
}en_port_t;

/**
 *******************************************************************************
 ** \brief GPIO Pin Index enumeration
 ******************************************************************************/
typedef enum en_pin
{
    Pin00 = (1 <<  0),                  ///< Pin index 00 of each port group
    Pin01 = (1 <<  1),                  ///< Pin index 01 of each port group
    Pin02 = (1 <<  2),                  ///< Pin index 02 of each port group
    Pin03 = (1 <<  3),                  ///< Pin index 03 of each port group
    Pin04 = (1 <<  4),                  ///< Pin index 04 of each port group
    Pin05 = (1 <<  5),                  ///< Pin index 05 of each port group
    Pin06 = (1 <<  6),                  ///< Pin index 06 of each port group
    Pin07 = (1 <<  7),                  ///< Pin index 07 of each port group
    Pin08 = (1 <<  8),                  ///< Pin index 08 of each port group
    Pin09 = (1 <<  9),                  ///< Pin index 09 of each port group
    Pin10 = (1 << 10),                  ///< Pin index 10 of each port group
    Pin11 = (1 << 11),                  ///< Pin index 11 of each port group
    Pin12 = (1 << 12),                  ///< Pin index 12 of each port group
    Pin13 = (1 << 13),                  ///< Pin index 13 of each port group
    Pin14 = (1 << 14),                  ///< Pin index 14 of each port group
    Pin15 = (1 << 15),                  ///< Pin index 15 of each port group
    PinAll= 0xFFFF,                     ///< All pins selected
}en_pin_t;

/**
 *******************************************************************************
 ** \brief GPIO Pin read wait cycle enumeration
 ******************************************************************************/
typedef enum en_read_wait
{
    WaitCycle0  = 0,                    ///< no wait cycle, operation freq. lower than 42MHz
    WaitCycle1  = 1,                    ///< one wait cycle, operation freq. @[42~84)MHz
    WaitCycle2  = 2,                    ///< two wait cycles, operation freq. @[84~126)MHz
    WaitCycle3  = 3,                    ///< three wait cycles, operation freq. @[126~200)MHz
}en_read_wait_t;

/**
 *******************************************************************************
 ** \brief GPIO Function enumeration
 ******************************************************************************/
typedef enum en_port_func
{
    Func_Gpio       = 0u,               ///< function set to gpio
    Func_Fcmref     = 1u,               ///< function set to fcm reference
    Func_Rtcout     = 1u,               ///< function set to rtc output
    Func_Vcout      = 1u,               ///< function set to vc output
    Func_Adtrg      = 1u,               ///< function set to adc trigger
    Func_Mclkout    = 1u,               ///< function set to mclk output
    Func_Tim4       = 2u,               ///< function set to timer4
    Func_Tim6       = 3u,               ///< function set to timer6
    Func_Tima0      = 4u,               ///< function set to timerA
    Func_Tima1      = 5u,               ///< function set to timerA
    Func_Tima2      = 6u,               ///< function set to timerA
    Func_Emb        = 6u,               ///< function set to emb
    Func_Usart_Ck   = 7u,               ///< function set to usart clk
    Func_Spi_Nss    = 7u,               ///< function set to spi nss
    Func_Qspi       = 7u,               ///< function set to qspi
    Func_Key        = 8u,               ///< function set to key
    Func_Sdio       = 9u,               ///< function set to sdio
    Func_I2s        = 10u,              ///< function set to i2s
    Func_UsbF       = 10u,              ///< function set to usb full speed
    Func_Evnpt      = 14u,              ///< function set to event port
    Func_Eventout   = 15u,              ///< function set to event out
    Func_Usart1_Tx  = 32u,              ///< function set to usart tx of ch.1
    Func_Usart3_Tx  = 32u,              ///< function set to usart tx of ch.3
    Func_Usart1_Rx  = 33u,              ///< function set to usart rx of ch.1
    Func_Usart3_Rx  = 33u,              ///< function set to usart rx of ch.3
    Func_Usart1_Rts = 34u,              ///< function set to usart rts of ch.1
    Func_Usart3_Rts = 34u,              ///< function set to usart rts of ch.3
    Func_Usart1_Cts = 35u,              ///< function set to usart cts of ch.1
    Func_Usart3_Cts = 35u,              ///< function set to usart cts of ch.3
    Func_Usart2_Tx  = 36u,              ///< function set to usart tx of ch.2
    Func_Usart4_Tx  = 36u,              ///< function set to usart tx of ch.4
    Func_Usart2_Rx  = 37u,              ///< function set to usart rx of ch.2
    Func_Usart4_Rx  = 37u,              ///< function set to usart rx of ch.4
    Func_Usart2_Rts = 38u,              ///< function set to usart rts of ch.2
    Func_Usart4_Rts = 38u,              ///< function set to usart rts of ch.4
    Func_Usart2_Cts = 39u,              ///< function set to usart cts of ch.2
    Func_Usart4_Cts = 39u,              ///< function set to usart cts of ch.4
    Func_Spi1_Mosi  = 40u,              ///< function set to spi mosi of ch.1
    Func_Spi3_Mosi  = 40u,              ///< function set to spi mosi of ch.3
    Func_Spi1_Miso  = 41u,              ///< function set to spi miso of ch.1
    Func_Spi3_Miso  = 41u,              ///< function set to spi miso of ch.3
    Func_Spi1_Nss0  = 42u,              ///< function set to spi nss0 of ch.1
    Func_Spi3_Nss0  = 42u,              ///< function set to spi nss0 of ch.3
    Func_Spi1_Sck   = 43u,              ///< function set to spi sck of ch.1
    Func_Spi3_Sck   = 43u,              ///< function set to spi sck of ch.3
    Func_Spi2_Mosi  = 44u,              ///< function set to spi mosi of ch.2
    Func_Spi4_Mosi  = 44u,              ///< function set to spi mosi of ch.2
    Func_Spi2_Miso  = 45u,              ///< function set to spi miso of ch.4
    Func_Spi4_Miso  = 45u,              ///< function set to spi miso of ch.4
    Func_Spi2_Nss0  = 46u,              ///< function set to spi nss0 of ch.2
    Func_Spi4_Nss0  = 46u,              ///< function set to spi nss0 of ch.4
    Func_Spi2_Sck   = 47u,              ///< function set to spi sck of ch.2
    Func_Spi4_Sck   = 47u,              ///< function set to spi sck of ch.4
    Func_I2c1_Sda   = 48u,              ///< function set to i2c sda of ch.1
    Func_I2c3_Sda   = 48u,              ///< function set to i2c sda of ch.3
    Func_I2c1_Scl   = 49u,              ///< function set to i2c scl of ch.1
    Func_I2c3_Scl   = 49u,              ///< function set to i2c scl of ch.3
    Func_I2c2_Sda   = 50u,              ///< function set to i2c sda of ch.2
    Func_Can1_Tx    = 50u,              ///< function set to can tx of ch.1
    Func_I2c2_Scl   = 51u,              ///< function set to i2c scl of ch.2
    Func_Can1_Rx    = 51u,              ///< function set to can rx of ch.1
    Func_I2s1_Sd    = 52u,              ///< function set to i2s sd of ch.1
    Func_I2s3_Sd    = 52u,              ///< function set to i2s sd of ch.3
    Func_I2s1_Sdin  = 53u,              ///< function set to i2s sdin of ch.1
    Func_I2s3_Sdin  = 53u,              ///< function set to i2s sdin of ch.3
    Func_I2s1_Ws    = 54u,              ///< function set to i2s ws of ch.1
    Func_I2s3_Ws    = 54u,              ///< function set to i2s ws of ch.3
    Func_I2s1_Ck    = 55u,              ///< function set to i2s ck of ch.1
    Func_I2s3_Ck    = 55u,              ///< function set to i2s ck of ch.3
    Func_I2s2_Sd    = 56u,              ///< function set to i2s sd of ch.2
    Func_I2s4_Sd    = 56u,              ///< function set to i2s sd of ch.4
    Func_I2s2_Sdin  = 57u,              ///< function set to i2s sdin of ch.2
    Func_I2s4_Sdin  = 57u,              ///< function set to i2s sdin of ch.4
    Func_I2s2_Ws    = 58u,              ///< function set to i2s ws of ch.2
    Func_I2s4_Ws    = 58u,              ///< function set to i2s ws of ch.4
    Func_I2s2_Ck    = 59u,              ///< function set to i2s ck of ch.2
    Func_I2s4_Ck    = 59u,              ///< function set to i2s ck of ch.4
}en_port_func_t;

/**
 *******************************************************************************
 ** \brief GPIO init structure definition
 ******************************************************************************/
typedef struct stc_port_init
{
    en_pin_mode_t           enPinMode;      ///< Set pin mode @ref en_pin_mode_t
    en_functional_state_t   enLatch;        ///< Pin output latch enable
    en_functional_state_t   enExInt;        ///< External int enable
    en_functional_state_t   enInvert;       ///< Pin input/output invert enable
    en_functional_state_t   enPullUp;       ///< Internal pull-up resistor enable
    en_pin_drv_t            enPinDrv;       ///< Drive capacity setting @ref en_pin_drv_t
    en_pin_o_type_t         enPinOType;     ///< Output mode setting @ref en_pin_o_type_t
    en_functional_state_t   enPinSubFunc;   ///< Pin sub-function enable
}stc_port_init_t;

/**
 *******************************************************************************
 ** \brief GPIO public setting structure definition
 ******************************************************************************/
typedef struct stc_port_pub_set
{
    en_port_func_t          enSubFuncSel;   ///< Sub-function setting @ref en_port_func_t
    en_read_wait_t          enReadWait;     ///< Read wait cycle setting @ref en_read_wait_t
}stc_port_pub_set_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
extern en_result_t PORT_Init(en_port_t enPort, uint16_t u16Pin,                \
                      const stc_port_init_t *pstcPortInit);
extern en_result_t PORT_DeInit(void);
extern void PORT_Unlock(void);
extern void PORT_Lock(void);
extern en_result_t PORT_DebugPortSetting(uint8_t u8DebugPort, en_functional_state_t enFunc);
extern en_result_t PORT_PubSetting(const stc_port_pub_set_t *pstcPortPubSet);
extern uint16_t PORT_GetData(en_port_t enPort);
extern en_flag_status_t PORT_GetBit(en_port_t enPort, en_pin_t enPin);
extern en_result_t PORT_SetPortData(en_port_t enPort, uint16_t u16Pin);
extern en_result_t PORT_ResetPortData(en_port_t enPort, uint16_t u16Pin);
extern en_result_t PORT_OE(en_port_t enPort, uint16_t u16Pin, en_functional_state_t enNewState);
extern en_result_t PORT_SetBits(en_port_t enPort, uint16_t u16Pin);
extern en_result_t PORT_ResetBits(en_port_t enPort, uint16_t u16Pin);
extern en_result_t PORT_Toggle(en_port_t enPort, uint16_t u16Pin);
extern en_result_t PORT_SetFunc(en_port_t enPort, uint16_t u16Pin,              \
                        en_port_func_t enFuncSel, en_functional_state_t enSubFunc);
extern en_result_t PORT_SetSubFunc(en_port_func_t enFuncSel);

//@} // GpioGroup

#ifdef __cplusplus
}
#endif

#endif /* DDL_GPIO_ENABLE */

#endif /* __HC32F460_GPIO_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
