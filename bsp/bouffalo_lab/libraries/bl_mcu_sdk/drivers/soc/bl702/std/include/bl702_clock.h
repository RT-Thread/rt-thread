/**
  ******************************************************************************
  * @file    bl702_clock.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __BL702_CLOCK_H__
#define __BL702_CLOCK_H__

#include "glb_reg.h"
#include "bl702_hbn.h"
#include "bl702_common.h"

/** @addtogroup  BL702_Peripheral_Driver
 *  @{
 */

/** @addtogroup  CLOCK
 *  @{
 */

/** @defgroup  CLOCK_Public_Types
 *  @{
 */

/**
 *  @brief System clock type definition
 */
typedef enum {
    BL_SYSTEM_CLOCK_ROOT, /*!< ROOT clock */
    BL_SYSTEM_CLOCK_FCLK, /*!< Fast clock/CPU clock */
    BL_SYSTEM_CLOCK_BCLK, /*!< BUS clock */
    BL_SYSTEM_CLOCK_F32K, /*!< F32K clock */
    BL_SYSTEM_CLOCK_XCLK, /*!< XCLK:RC32M or XTAL */
    BL_SYSTEM_CLOCK_XTAL, /*!< XTAL clock */
    BL_SYSTEM_CLOCK_MAX,  /*!< MAX type of system clock */
} BL_System_Clock_Type;

typedef enum {
    BL_PERIPHERAL_CLOCK_UART0,   /*!< UART0 clock */
    BL_PERIPHERAL_CLOCK_UART1,   /*!< UART1 clock */
    BL_PERIPHERAL_CLOCK_SPI0,    /*!< SPI0 clock */
    BL_PERIPHERAL_CLOCK_I2C0,    /*!< I2C0 clock */
    BL_PERIPHERAL_CLOCK_I2S,     /*!< I2S clock */
    BL_PERIPHERAL_CLOCK_GPADC,   /*!< GPADC clock */
    BL_PERIPHERAL_CLOCK_GPDAC,   /*!< GPDAC clock */
    BL_PERIPHERAL_CLOCK_PWM,     /*!< PWM clock */
    BL_PERIPHERAL_CLOCK_IR,      /*!< IR clock */
    BL_PERIPHERAL_CLOCK_FLASH,   /*!< FLASH clock */
    BL_PERIPHERAL_CLOCK_CAM,     /*!< CAM clock */
    BL_PERIPHERAL_CLOCK_QDEC,    /*!< QDEC clock */
    BL_PERIPHERAL_CLOCK_TIMER0,  /*!< TIMER0 clock */
    BL_PERIPHERAL_CLOCK_TIMER1,  /*!< TIMER1 clock */
    BL_PERIPHERAL_CLOCK_WDT,     /*!< WDT clock */
    BL_PERIPHERAL_CLOCK_MAX,
} BL_Peripheral_Type;

/**
 *  @brief SOC clock config type
 */
typedef struct
{
    uint16_t systemClock[BL_SYSTEM_CLOCK_MAX];   /*!< System lock value */
    uint16_t peripheralClock[BL_AHB_SLAVE1_MAX]; /*!< Pewripherals clock value */
    uint32_t i2sClock;                           /*!< I2S clock */
} Clock_Cfg_Type;

/*@} end of group CLOCK_Public_Types */

/** @defgroup  CLOCK_Public_Constants
 *  @{
 */

/** @defgroup  BL_SYSTEM_CLOCK_TYPE
 *  @{
 */
#define IS_BL_SYSTEM_CLOCK_TYPE(type) (((type) == BL_SYSTEM_CLOCK_ROOT) || \
                                       ((type) == BL_SYSTEM_CLOCK_FCLK) || \
                                       ((type) == BL_SYSTEM_CLOCK_BCLK) || \
                                       ((type) == BL_SYSTEM_CLOCK_F32K) || \
                                       ((type) == BL_SYSTEM_CLOCK_XCLK) || \
                                       ((type) == BL_SYSTEM_CLOCK_XTAL) || \
                                       ((type) == BL_SYSTEM_CLOCK_MAX))

/*@} end of group CLOCK_Public_Constants */

/** @defgroup  CLOCK_Public_Macros
 *  @{
 */

/*@} end of group CLOCK_Public_Macros */

/** @defgroup  CLOCK_Public_Functions
 *  @{
 */
uint32_t Clock_System_Clock_Get(BL_System_Clock_Type type);
uint32_t Clock_Peripheral_Clock_Get(BL_Peripheral_Type type);

/*@} end of group CLOCK_Public_Functions */

/*@} end of group CLOCK */

/*@} end of group BL702_Peripheral_Driver */

#endif /* __BL702_CLOCK_H__ */
