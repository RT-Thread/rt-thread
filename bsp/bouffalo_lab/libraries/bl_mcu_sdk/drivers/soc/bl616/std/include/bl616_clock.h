/**
  ******************************************************************************
  * @file    bl616_clock.h
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
#ifndef __BL616_CLOCK_H__
#define __BL616_CLOCK_H__

#include "glb_reg.h"
#include "mcu_misc_reg.h"
#include "pds_reg.h"
#include "bl616_glb.h"
#include "bl616_hbn.h"
#include "bl616_common.h"

/** @addtogroup  BL616_Peripheral_Driver
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
    BL_SYSTEM_CLOCK_MCU_ROOT_CLK, /*!< MCU root clock */
    BL_SYSTEM_CLOCK_MCU_CLK,      /*!< MCU Fast clock/CPU clock */
    BL_SYSTEM_CLOCK_MCU_BCLK,     /*!< MCU BUS clock */
    BL_SYSTEM_CLOCK_MCU_PBCLK,    /*!< MCU peri BUS clock */
    BL_SYSTEM_CLOCK_F32K,         /*!< F32K clock */
    BL_SYSTEM_CLOCK_XCLK,         /*!< XCLK:RC32M or XTAL */
    BL_SYSTEM_CLOCK_XTAL,         /*!< XTAL clock */
    BL_SYSTEM_CLOCK_MAX,          /*!< MAX type of system clock */
} BL_System_Clock_Type;

typedef enum {
    BL_MTIMER_SOURCE_CLOCK_MCU_XCLK,     /*!< MCU xclk clock */
    BL_MTIMER_SOURCE_CLOCK_MCU_CLK,      /*!< MCU root clock */
} BL_MTimer_Source_Clock_Type;

/**
 *  @brief SOC clock config type
 */
typedef struct
{
    uint32_t magic;                              /*!< Clock config magic */
    uint32_t systemClock[BL_SYSTEM_CLOCK_MAX];   /*!< System lock value */
    uint32_t peripheralClock[BL_AHB_SLAVE1_MAX]; /*!< Pewripherals clock value */
    uint32_t i2sClock;                           /*!< I2S clock */
} Clock_Cfg_Type;

typedef enum {
    CLOCK_AUPLL_DIV1,
    CLOCK_AUPLL_DIV2,
    CLOCK_AUPLL_DIV2P5,
    CLOCK_AUPLL_DIV3,
    CLOCK_AUPLL_DIV4,
    CLOCK_AUPLL_DIV5,
    CLOCK_AUPLL_DIV6,
    CLOCK_AUPLL_DIV10,
    CLOCK_AUPLL_DIV15,
} CLOCK_AUPLL_Type;
/**
 *  @brief Peripheral clock type definition
 */
typedef enum {
    BL_PERIPHERAL_CLOCK_UART0,       /*!< UART0 clock */
    BL_PERIPHERAL_CLOCK_UART1,       /*!< UART1 clock */
    BL_PERIPHERAL_CLOCK_UART2,       /*!< UART2 clock */
    BL_PERIPHERAL_CLOCK_SPI,         /*!< SPI clock */
    BL_PERIPHERAL_CLOCK_PEC,         /*!< PEC clock */
    BL_PERIPHERAL_CLOCK_DBI,         /*!< DBI clock */
    BL_PERIPHERAL_CLOCK_EMI,         /*!< EMI clock */
    BL_PERIPHERAL_CLOCK_ISP,         /*!< ISP clock */
    BL_PERIPHERAL_CLOCK_I2C0,        /*!< I2C0 clock */
    BL_PERIPHERAL_CLOCK_I2C1,        /*!< I2C1 clock */
    BL_PERIPHERAL_CLOCK_PSRAMB,      /*!< PSRAMB clock */
    BL_PERIPHERAL_CLOCK_FLASH,       /*!< FLASH clock */
    BL_PERIPHERAL_CLOCK_I2S,         /*!< I2S clock */
    BL_PERIPHERAL_CLOCK_IR,          /*!< IR clock */
    BL_PERIPHERAL_CLOCK_ADC,         /*!< ADC clock */
    BL_PERIPHERAL_CLOCK_GPADC,       /*!< GPADC clock */
    BL_PERIPHERAL_CLOCK_GPDAC,       /*!< GPDAC clock */
    BL_PERIPHERAL_CLOCK_CAM,         /*!< CAM clock */
    BL_PERIPHERAL_CLOCK_SDH,         /*!< SDH clock */
    BL_PERIPHERAL_CLOCK_PKA,         /*!< PKA clock */
    BL_PERIPHERAL_CLOCK_MAX,
} BL_Peripheral_Type;

/*@} end of group CLOCK_Public_Types */

/** @defgroup  CLOCK_Public_Constants
 *  @{
 */

/** @defgroup  BL_SYSTEM_CLOCK_TYPE
 *  @{
 */
#define IS_BL_SYSTEM_CLOCK_TYPE(type) (((type) == BL_SYSTEM_CLOCK_MCU_ROOT_CLK) || \
                                       ((type) == BL_SYSTEM_CLOCK_MCU_CLK) ||      \
                                       ((type) == BL_SYSTEM_CLOCK_MCU_BCLK) ||     \
                                       ((type) == BL_SYSTEM_CLOCK_MCU_PBCLK) ||    \
                                       ((type) == BL_SYSTEM_CLOCK_DSP_ROOT_CLK) || \
                                       ((type) == BL_SYSTEM_CLOCK_DSP_CLK) ||      \
                                       ((type) == BL_SYSTEM_CLOCK_DSP_BCLK) ||     \
                                       ((type) == BL_SYSTEM_CLOCK_DSP_PBCLK) ||    \
                                       ((type) == BL_SYSTEM_CLOCK_LP_CLK) ||       \
                                       ((type) == BL_SYSTEM_CLOCK_F32K) ||         \
                                       ((type) == BL_SYSTEM_CLOCK_XCLK) ||         \
                                       ((type) == BL_SYSTEM_CLOCK_XTAL) ||         \
                                       ((type) == BL_SYSTEM_CLOCK_MAX))

/*@} end of group CLOCK_Public_Constants */

/** @defgroup  CLOCK_Public_Macros
 *  @{
 */
#define SYS_CLOCK_CFG_MAGIC (0x12345678)
#define SYS_CLOCK_CFG_ADDR  (0x20010000 + 4 * 1024 - 512)

/*@} end of group CLOCK_Public_Macros */

/** @defgroup  CLOCK_Public_Functions
 *  @{
 */
/*----------*/
uint32_t Clock_System_Clock_Get(BL_System_Clock_Type type);
uint32_t Clock_Peripheral_Clock_Get(BL_Peripheral_Type type);
uint32_t Clock_Audio_ADC_Clock_Get(void);
uint32_t Clock_Audio_DAC_Clock_Get(void);
/*----------*/
uint32_t SystemCoreClockGet(void);
/*----------*/
BL_Err_Type CPU_Set_MTimer_RST(uint8_t rstEn);
BL_Err_Type CPU_Reset_MTimer(void);
BL_Err_Type CPU_Set_MTimer_CLK(uint8_t enable, BL_MTimer_Source_Clock_Type mTimerSourceClockType, uint16_t div);
uint32_t CPU_Get_MTimer_Source_Clock(void);
uint32_t CPU_Get_MTimer_Clock(void);
uint64_t CPU_Get_MTimer_Counter(void);
uint64_t CPU_Get_CPU_Cycle(void);
uint64_t CPU_Get_MTimer_US(void);
uint64_t CPU_Get_MTimer_MS(void);
BL_Err_Type CPU_MTimer_Delay_US(uint32_t cnt);
BL_Err_Type CPU_MTimer_Delay_MS(uint32_t cnt);
uint32_t Clock_Get_EMI_Clk(void);
uint32_t Clock_Get_ISP_Clk(void);
uint32_t Clock_Get_BLAI_Clk(void);
uint32_t Clock_Get_Display_Clk(void);
uint32_t Clock_Get_PSRAMB_Clk(void);
uint32_t Clock_Get_PSRAMB_Clk(void);
uint32_t Clock_Get_H264_Clk(void);
/*----------*/

/*@} end of group CLOCK_Public_Functions */

/*@} end of group CLOCK */

/*@} end of group BL616_Peripheral_Driver */

#endif /* __BL616_CLOCK_H__ */
