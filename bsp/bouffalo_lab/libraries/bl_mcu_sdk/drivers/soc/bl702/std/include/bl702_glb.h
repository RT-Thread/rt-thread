/**
  ******************************************************************************
  * @file    bl702_glb.h
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
#ifndef __BL702_GLB_H__
#define __BL702_GLB_H__

#include "glb_reg.h"
#include "pds_reg.h"
#include "bl702_gpio.h"
#include "bl702_l1c.h"
#include "bl702_hbn.h"
#include "bl702_aon.h"
#include "bl702_ef_ctrl.h"
#include "bl702_pds.h"
#include "bl702_common.h"
#include "bflb_sf_ctrl.h"
#include "bflb_sf_cfg.h"

/** @addtogroup  BL702_Peripheral_Driver
 *  @{
 */

/** @addtogroup  GLB
 *  @{
 */

/** @defgroup  GLB_Public_Types
 *  @{
 */

/**
 *  @brief GLB root clock type definition
 */
typedef enum {
    GLB_ROOT_CLK_RC32M, /*!< root clock select RC32M */
    GLB_ROOT_CLK_XTAL,  /*!< root clock select XTAL */
    GLB_ROOT_CLK_DLL,   /*!< root clock select DLL others, PLL120M not recommend */
} GLB_ROOT_CLK_Type;

/**
 *  @brief GLB system clock type definition
 */
typedef enum {
    GLB_SYS_CLK_RC32M,    /*!< use RC32M as system clock frequency */
    GLB_SYS_CLK_XTAL,     /*!< use XTAL as system clock */
    GLB_SYS_CLK_DLL57P6M, /*!< use DLL output 57.6M as system clock */
    GLB_SYS_CLK_DLL96M,   /*!< use DLL output 96M as system clock */
    GLB_SYS_CLK_DLL144M,  /*!< use DLL output 144M as system clock, PLL120M not recommend */
} GLB_SYS_CLK_Type;

/**
 *  @brief GLB CAM clock type definition
 */
typedef enum {
    GLB_CAM_CLK_XCLK,   /*!< Select XCLK as CAM clock */
    GLB_CAM_CLK_DLL96M, /*!< Select DLL96M as CAM clock */
} GLB_CAM_CLK_Type;

/**
 *  @brief GLB I2S output ref clock type definition
 */
typedef enum {
    GLB_I2S_OUT_REF_CLK_NONE, /*!< no output reference clock on I2S_0 ref_clock port */
    GLB_I2S_OUT_REF_CLK_SRC,  /*!< output reference clock on I2S_0 ref_clock port */
} GLB_I2S_OUT_REF_CLK_Type;

/**
 *  @brief GLB qdec clock type definition
 */
typedef enum {
    GLB_QDEC_CLK_XCLK, /*!< Select XCLK as QDEC clock */
    GLB_QDEC_CLK_F32K, /*!< Select f32k as QDEC clock (PDS mode) */
} GLB_QDEC_CLK_Type;

/**
 *  @brief GLB DMA clock ID type definition
 */
typedef enum {
    GLB_DMA_CLK_DMA0_CH0, /*!< DMA clock ID:channel 0 */
    GLB_DMA_CLK_DMA0_CH1, /*!< DMA clock ID:channel 1 */
    GLB_DMA_CLK_DMA0_CH2, /*!< DMA clock ID:channel 2 */
    GLB_DMA_CLK_DMA0_CH3, /*!< DMA clock ID:channel 3 */
    GLB_DMA_CLK_DMA0_CH4, /*!< DMA clock ID:channel 4 */
    GLB_DMA_CLK_DMA0_CH5, /*!< DMA clock ID:channel 5 */
    GLB_DMA_CLK_DMA0_CH6, /*!< DMA clock ID:channel 6 */
    GLB_DMA_CLK_DMA0_CH7, /*!< DMA clock ID:channel 7 */
} GLB_DMA_CLK_ID_Type;

/**
 *  @brief GLB clock source type definition
 */
typedef enum {
    GLB_IR_CLK_SRC_XCLK, /*!< IR clock source select XCLK */
} GLB_IR_CLK_SRC_Type;

/**
 *  @brief GLB flash clock type definition
 */
typedef enum {
    GLB_SFLASH_CLK_144M,  /*!< Select 144M as flash clock */
    GLB_SFLASH_CLK_XCLK,  /*!< Select XCLK as flash clock */
    GLB_SFLASH_CLK_57P6M, /*!< Select 57.6M as flash clock */
    GLB_SFLASH_CLK_72M,   /*!< Select 72M as flash clock */
    GLB_SFLASH_CLK_BCLK,  /*!< Select BCLK as flash clock */
    GLB_SFLASH_CLK_96M,   /*!< Select 96M as flash clock */
} GLB_SFLASH_CLK_Type;

/**
 *  @brief GLB chip clock out type definition
 */
typedef enum {
    GLB_CHIP_CLK_OUT_NONE,          /*!< no chip clock out */
    GLB_CHIP_CLK_OUT_I2S_REF_CLK,   /*!< i2s_ref_clk out */
    GLB_CHIP_CLK_OUT_AUDIO_PLL_CLK, /*!< audio_pll_clk out */
    GLB_CHIP_CLK_OUT_XTAL_SOC_32M,  /*!< clk_xtal_soc_32M */
} GLB_CHIP_CLK_OUT_Type;

/**
 *  @brief GLB eth ref clock out type definition
 */
typedef enum {
    GLB_ETH_REF_CLK_OUT_OUTSIDE_50M, /*!< select outside 50MHz RMII ref clock */
    GLB_ETH_REF_CLK_OUT_INSIDE_50M,  /*!< select inside 50MHz RMII ref clock */
} GLB_ETH_REF_CLK_OUT_Type;

/**
 *  @brief GLB SPI pad action type definition
 */
typedef enum {
    GLB_SPI_PAD_ACT_AS_SLAVE,  /*!< SPI pad act as slave */
    GLB_SPI_PAD_ACT_AS_MASTER, /*!< SPI pad act as master */
} GLB_SPI_PAD_ACT_AS_Type;

/**
 *  @brief GLB PKA clock type definition
 */
typedef enum {
    GLB_PKA_CLK_HCLK,   /*!< Select HCLK as PKA clock */
    GLB_PKA_CLK_DLL96M, /*!< Select DLL 96M as PKA clock */
} GLB_PKA_CLK_Type;

/**
 *  @brief BMX arb mode type definition
 */
typedef enum {
    BMX_ARB_FIX,         /*!< 0->fix */
    BMX_ARB_ROUND_ROBIN, /*!< 2->round-robin */
    BMX_ARB_RANDOM,      /*!< 3->random */
} BMX_ARB_Type;

/**
 *  @brief BMX configuration structure type definition
 */
typedef struct {
    uint8_t timeoutEn;   /*!< Bus timeout enable: detect slave no reaponse in 1024 cycles */
    BL_Fun_Type errEn;   /*!< Bus error response enable */
    BMX_ARB_Type arbMod; /*!< 0->fix, 2->round-robin, 3->random */
} BMX_Cfg_Type;

/**
 *  @brief BMX bus err type definition
 */
typedef enum {
    BMX_BUS_ERR_TRUSTZONE_DECODE, /*!< Bus trustzone decode error */
    BMX_BUS_ERR_ADDR_DECODE,      /*!< Bus addr decode error */
} BMX_BUS_ERR_Type;

/**
 *  @brief BMX bus err interrupt type definition
 */
typedef enum {
    BMX_ERR_INT_ERR, /*!< BMX bus err interrupt */
    BMX_ERR_INT_ALL, /*!< BMX bus err interrupt max num */
} BMX_ERR_INT_Type;

/**
 *  @brief BMX time out interrupt type definition
 */
typedef enum {
    BMX_TO_INT_TIMEOUT, /*!< BMX timeout interrupt */
    BMX_TO_INT_ALL,     /*!< BMX timeout interrupt max num */
} BMX_TO_INT_Type;

/**
 *  @brief GLB EM type definition
 */
typedef enum {
    GLB_EM_0KB = 0x0,  /*!< 0x0 --> 0KB */
    GLB_EM_8KB = 0x3,  /*!< 0x3 --> 8KB */
    GLB_EM_16KB = 0xF, /*!< 0xF --> 16KB */
} GLB_EM_Type;

/**
 *  @brief GLB EMAC and CAM pin type definition
 */
typedef enum {
    GLB_EMAC_CAM_PIN_EMAC, /*!< select pin as emac */
    GLB_EMAC_CAM_PIN_CAM,  /*!< select pin as cam */
} GLB_EMAC_CAM_PIN_Type;

/**
 *  @brief GLB RTC clock type definition
 */
typedef enum {
    GLB_MTIMER_CLK_BCLK, /*!< BUS clock */
    GLB_MTIMER_CLK_32K,  /*!< 32KHz */
} GLB_MTIMER_CLK_Type;

/**
 *  @brief GLB ADC clock type definition
 */
typedef enum {
    GLB_ADC_CLK_AUDIO_PLL, /*!< use Audio PLL as ADC clock */
    GLB_ADC_CLK_XCLK,      /*!< use XCLK as ADC clock */
} GLB_ADC_CLK_Type;

/**
 *  @brief GLB DAC clock type definition
 */
typedef enum {
    GLB_DAC_CLK_PLL_32M,   /*!< select PLL 32M as DAC clock source */
    GLB_DAC_CLK_XCLK,      /*!< select XCLK as DAC clock source */
    GLB_DAC_CLK_AUDIO_PLL, /*!< select Audio PLL as DAC clock source */
} GLB_DAC_CLK_Type;

/**
 *  @brief GLB DIG clock source select type definition
 */
typedef enum {
    GLB_DIG_CLK_PLL_32M,   /*!< select PLL 32M as DIG clock source */
    GLB_DIG_CLK_XCLK,      /*!< select XCLK as DIG clock source */
    GLB_DIG_CLK_AUDIO_PLL, /*!< select Audio PLL as DIG clock source */
} GLB_DIG_CLK_Type;

/**
 *  @brief GLB BT bandwidth type definition
 */
typedef enum {
    GLB_BT_BANDWIDTH_1M, /*!< BT bandwidth 1MHz */
    GLB_BT_BANDWIDTH_2M, /*!< BT bandwidth 2MHz */
} GLB_BT_BANDWIDTH_Type;

/**
 *  @brief GLB UART signal type definition
 */
typedef enum {
    GLB_UART_SIG_0, /*!< UART signal 0 */
    GLB_UART_SIG_1, /*!< UART signal 1 */
    GLB_UART_SIG_2, /*!< UART signal 2 */
    GLB_UART_SIG_3, /*!< UART signal 3 */
    GLB_UART_SIG_4, /*!< UART signal 4 */
    GLB_UART_SIG_5, /*!< UART signal 5 */
    GLB_UART_SIG_6, /*!< UART signal 6 */
    GLB_UART_SIG_7, /*!< UART signal 7 */
} GLB_UART_SIG_Type;

/**
 *  @brief GLB UART signal  function type definition
 */
typedef enum {
    GLB_UART_SIG_FUN_UART0_RTS, /*!< UART funtion: UART 0 RTS */
    GLB_UART_SIG_FUN_UART0_CTS, /*!< UART funtion: UART 0 CTS */
    GLB_UART_SIG_FUN_UART0_TXD, /*!< UART funtion: UART 0 TXD */
    GLB_UART_SIG_FUN_UART0_RXD, /*!< UART funtion: UART 0 RXD */
    GLB_UART_SIG_FUN_UART1_RTS, /*!< UART funtion: UART 1 RTS */
    GLB_UART_SIG_FUN_UART1_CTS, /*!< UART funtion: UART 1 CTS */
    GLB_UART_SIG_FUN_UART1_TXD, /*!< UART funtion: UART 1 TXD */
    GLB_UART_SIG_FUN_UART1_RXD, /*!< UART funtion: UART 1 RXD */
} GLB_UART_SIG_FUN_Type;

/**
 *  @brief GLB DLL output clock type definition
 */
typedef enum {
    GLB_DLL_CLK_57P6M, /*!< DLL output 57P6M clock */
    GLB_DLL_CLK_96M,   /*!< DLL output 96M clock */
    GLB_DLL_CLK_144M,  /*!< DLL output 144M clock */
    GLB_DLL_CLK_288M,  /*!< DLL output 288M clock */
    GLB_DLL_CLK_MMDIV, /*!< DLL output mmdiv clock */
} GLB_DLL_CLK_Type;

/**
 *  @brief GLB GPIO interrupt trigger mode type definition
 */
typedef enum {
    GLB_GPIO_INT_TRIG_NEG_PULSE, /*!< GPIO negedge pulse trigger interrupt */
    GLB_GPIO_INT_TRIG_POS_PULSE, /*!< GPIO posedge pulse trigger interrupt */
    GLB_GPIO_INT_TRIG_NEG_LEVEL, /*!< GPIO negedge level trigger interrupt (32k 3T) */
    GLB_GPIO_INT_TRIG_POS_LEVEL, /*!< GPIO posedge level trigger interrupt (32k 3T) */
} GLB_GPIO_INT_TRIG_Type;

/**
 *  @brief GLB GPIO interrupt control mode type definition
 */
typedef enum {
    GLB_GPIO_INT_CONTROL_SYNC,  /*!< GPIO interrupt sync mode */
    GLB_GPIO_INT_CONTROL_ASYNC, /*!< GPIO interrupt async mode */
} GLB_GPIO_INT_CONTROL_Type;

/**
 *  @brief PLL XTAL type definition
 */
typedef enum {
    GLB_DLL_XTAL_NONE,  /*!< XTAL is none */
    GLB_DLL_XTAL_32M,   /*!< XTAL is 32M */
    GLB_DLL_XTAL_RC32M, /*!< XTAL is RC32M */
} GLB_DLL_XTAL_Type;

typedef enum {
    GLB_AHB_CLOCK_IP_CPU,
    GLB_AHB_CLOCK_IP_SDU,
    GLB_AHB_CLOCK_IP_SEC,
    GLB_AHB_CLOCK_IP_DMA_0,
    GLB_AHB_CLOCK_IP_DMA_1,
    GLB_AHB_CLOCK_IP_DMA_2,
    GLB_AHB_CLOCK_IP_CCI,
    GLB_AHB_CLOCK_IP_RF_TOP,
    GLB_AHB_CLOCK_IP_GPIP,
    GLB_AHB_CLOCK_IP_TZC,
    GLB_AHB_CLOCK_IP_EF_CTRL,
    GLB_AHB_CLOCK_IP_SF_CTRL,
    GLB_AHB_CLOCK_IP_EMAC,
    GLB_AHB_CLOCK_IP_UART0,
    GLB_AHB_CLOCK_IP_UART1,
    GLB_AHB_CLOCK_IP_UART2,
    GLB_AHB_CLOCK_IP_UART3,
    GLB_AHB_CLOCK_IP_UART4,
    GLB_AHB_CLOCK_IP_SPI,
    GLB_AHB_CLOCK_IP_I2C,
    GLB_AHB_CLOCK_IP_PWM,
    GLB_AHB_CLOCK_IP_TIMER,
    GLB_AHB_CLOCK_IP_IR,
    GLB_AHB_CLOCK_IP_CHECKSUM,
    GLB_AHB_CLOCK_IP_QDEC,
    GLB_AHB_CLOCK_IP_KYS,
    GLB_AHB_CLOCK_IP_I2S,
    GLB_AHB_CLOCK_IP_USB11,
    GLB_AHB_CLOCK_IP_CAM,
    GLB_AHB_CLOCK_IP_MJPEG,
    GLB_AHB_CLOCK_IP_BT_BLE_NORMAL,
    GLB_AHB_CLOCK_IP_BT_BLE_LP,
    GLB_AHB_CLOCK_IP_ZB_NORMAL,
    GLB_AHB_CLOCK_IP_ZB_LP,
    GLB_AHB_CLOCK_IP_WIFI_NORMAL,
    GLB_AHB_CLOCK_IP_WIFI_LP,
    GLB_AHB_CLOCK_IP_BT_BLE_2_NORMAL,
    GLB_AHB_CLOCK_IP_BT_BLE_2_LP,
    GLB_AHB_CLOCK_IP_EMI_MISC,
    GLB_AHB_CLOCK_IP_PSRAM0_CTRL,
    GLB_AHB_CLOCK_IP_PSRAM1_CTRL,
    GLB_AHB_CLOCK_IP_USB20,
    GLB_AHB_CLOCK_IP_MIX2,
    GLB_AHB_CLOCK_IP_AUDIO,
    GLB_AHB_CLOCK_IP_SDH,
} GLB_AHB_CLOCK_IP_Type;

/*@} end of group GLB_Public_Types */

/** @defgroup  GLB_Public_Constants
 *  @{
 */

/** @defgroup  GLB_ROOT_CLK_TYPE
 *  @{
 */
#define IS_GLB_ROOT_CLK_TYPE(type) (((type) == GLB_ROOT_CLK_RC32M) || \
                                    ((type) == GLB_ROOT_CLK_XTAL) ||  \
                                    ((type) == GLB_ROOT_CLK_DLL))

/** @defgroup  GLB_SYS_CLK_TYPE
 *  @{
 */
#define IS_GLB_SYS_CLK_TYPE(type) (((type) == GLB_SYS_CLK_RC32M) ||    \
                                   ((type) == GLB_SYS_CLK_XTAL) ||     \
                                   ((type) == GLB_SYS_CLK_DLL57P6M) || \
                                   ((type) == GLB_SYS_CLK_DLL96M) ||   \
                                   ((type) == GLB_SYS_CLK_DLL144M))

/** @defgroup  GLB_CAM_CLK_TYPE
 *  @{
 */
#define IS_GLB_CAM_CLK_TYPE(type) (((type) == GLB_CAM_CLK_XCLK) || \
                                   ((type) == GLB_CAM_CLK_DLL96M))

/** @defgroup  GLB_I2S_OUT_REF_CLK_TYPE
 *  @{
 */
#define IS_GLB_I2S_OUT_REF_CLK_TYPE(type) (((type) == GLB_I2S_OUT_REF_CLK_NONE) || \
                                           ((type) == GLB_I2S_OUT_REF_CLK_SRC))

/** @defgroup  GLB_QDEC_CLK_TYPE
 *  @{
 */
#define IS_GLB_QDEC_CLK_TYPE(type) (((type) == GLB_QDEC_CLK_XCLK) || \
                                    ((type) == GLB_QDEC_CLK_F32K))

/** @defgroup  GLB_DMA_CLK_ID_TYPE
 *  @{
 */
#define IS_GLB_DMA_CLK_ID_TYPE(type) (((type) == GLB_DMA_CLK_DMA0_CH0) || \
                                      ((type) == GLB_DMA_CLK_DMA0_CH1) || \
                                      ((type) == GLB_DMA_CLK_DMA0_CH2) || \
                                      ((type) == GLB_DMA_CLK_DMA0_CH3) || \
                                      ((type) == GLB_DMA_CLK_DMA0_CH4) || \
                                      ((type) == GLB_DMA_CLK_DMA0_CH5) || \
                                      ((type) == GLB_DMA_CLK_DMA0_CH6) || \
                                      ((type) == GLB_DMA_CLK_DMA0_CH7))

/** @defgroup  GLB_IR_CLK_SRC_TYPE
 *  @{
 */
#define IS_GLB_IR_CLK_SRC_TYPE(type) (((type) == GLB_IR_CLK_SRC_XCLK))

/** @defgroup  GLB_SFLASH_CLK_TYPE
 *  @{
 */
#define IS_GLB_SFLASH_CLK_TYPE(type) (((type) == GLB_SFLASH_CLK_144M) ||  \
                                      ((type) == GLB_SFLASH_CLK_XCLK) ||  \
                                      ((type) == GLB_SFLASH_CLK_57P6M) || \
                                      ((type) == GLB_SFLASH_CLK_72M) ||   \
                                      ((type) == GLB_SFLASH_CLK_BCLK) ||  \
                                      ((type) == GLB_SFLASH_CLK_96M))

/** @defgroup  GLB_CHIP_CLK_OUT_TYPE
 *  @{
 */
#define IS_GLB_CHIP_CLK_OUT_TYPE(type) (((type) == GLB_CHIP_CLK_OUT_NONE) ||          \
                                        ((type) == GLB_CHIP_CLK_OUT_I2S_REF_CLK) ||   \
                                        ((type) == GLB_CHIP_CLK_OUT_AUDIO_PLL_CLK) || \
                                        ((type) == GLB_CHIP_CLK_OUT_XTAL_SOC_32M))

/** @defgroup  GLB_ETH_REF_CLK_OUT_TYPE
 *  @{
 */
#define IS_GLB_ETH_REF_CLK_OUT_TYPE(type) (((type) == GLB_ETH_REF_CLK_OUT_OUTSIDE_50M) || \
                                           ((type) == GLB_ETH_REF_CLK_OUT_INSIDE_50M))

/** @defgroup  GLB_SPI_PAD_ACT_AS_TYPE
 *  @{
 */
#define IS_GLB_SPI_PAD_ACT_AS_TYPE(type) (((type) == GLB_SPI_PAD_ACT_AS_SLAVE) || \
                                          ((type) == GLB_SPI_PAD_ACT_AS_MASTER))

/** @defgroup  GLB_PKA_CLK_TYPE
 *  @{
 */
#define IS_GLB_PKA_CLK_TYPE(type) (((type) == GLB_PKA_CLK_HCLK) || \
                                   ((type) == GLB_PKA_CLK_DLL96M))

/** @defgroup  BMX_ARB_TYPE
 *  @{
 */
#define IS_BMX_ARB_TYPE(type) (((type) == BMX_ARB_FIX) ||         \
                               ((type) == BMX_ARB_ROUND_ROBIN) || \
                               ((type) == BMX_ARB_RANDOM))

/** @defgroup  BMX_BUS_ERR_TYPE
 *  @{
 */
#define IS_BMX_BUS_ERR_TYPE(type) (((type) == BMX_BUS_ERR_TRUSTZONE_DECODE) || \
                                   ((type) == BMX_BUS_ERR_ADDR_DECODE))

/** @defgroup  BMX_ERR_INT_TYPE
 *  @{
 */
#define IS_BMX_ERR_INT_TYPE(type) (((type) == BMX_ERR_INT_ERR) || \
                                   ((type) == BMX_ERR_INT_ALL))

/** @defgroup  BMX_TO_INT_TYPE
 *  @{
 */
#define IS_BMX_TO_INT_TYPE(type) (((type) == BMX_TO_INT_TIMEOUT) || \
                                  ((type) == BMX_TO_INT_ALL))

/** @defgroup  GLB_EM_TYPE
 *  @{
 */
#define IS_GLB_EM_TYPE(type) (((type) == GLB_EM_0KB) || \
                              ((type) == GLB_EM_8KB) || \
                              ((type) == GLB_EM_16KB))

/** @defgroup  GLB_EMAC_CAM_PIN_TYPE
 *  @{
 */
#define IS_GLB_EMAC_CAM_PIN_TYPE(type) (((type) == GLB_EMAC_CAM_PIN_EMAC) || \
                                        ((type) == GLB_EMAC_CAM_PIN_CAM))

/** @defgroup  GLB_MTIMER_CLK_TYPE
 *  @{
 */
#define IS_GLB_MTIMER_CLK_TYPE(type) (((type) == GLB_MTIMER_CLK_BCLK) || \
                                      ((type) == GLB_MTIMER_CLK_32K))

/** @defgroup  GLB_ADC_CLK_TYPE
 *  @{
 */
#define IS_GLB_ADC_CLK_TYPE(type) (((type) == GLB_ADC_CLK_AUDIO_PLL) || \
                                   ((type) == GLB_ADC_CLK_XCLK))

/** @defgroup  GLB_DAC_CLK_TYPE
 *  @{
 */
#define IS_GLB_DAC_CLK_TYPE(type) (((type) == GLB_DAC_CLK_PLL_32M) || \
                                   ((type) == GLB_DAC_CLK_XCLK) ||    \
                                   ((type) == GLB_DAC_CLK_AUDIO_PLL))

/** @defgroup  GLB_DIG_CLK_TYPE
 *  @{
 */
#define IS_GLB_DIG_CLK_TYPE(type) (((type) == GLB_DIG_CLK_PLL_32M) || \
                                   ((type) == GLB_DIG_CLK_XCLK) ||    \
                                   ((type) == GLB_DIG_CLK_AUDIO_PLL))

/** @defgroup  GLB_BT_BANDWIDTH_TYPE
 *  @{
 */
#define IS_GLB_BT_BANDWIDTH_TYPE(type) (((type) == GLB_BT_BANDWIDTH_1M) || \
                                        ((type) == GLB_BT_BANDWIDTH_2M))

/** @defgroup  GLB_UART_SIG_TYPE
 *  @{
 */
#define IS_GLB_UART_SIG_TYPE(type) (((type) == GLB_UART_SIG_0) || \
                                    ((type) == GLB_UART_SIG_1) || \
                                    ((type) == GLB_UART_SIG_2) || \
                                    ((type) == GLB_UART_SIG_3) || \
                                    ((type) == GLB_UART_SIG_4) || \
                                    ((type) == GLB_UART_SIG_5) || \
                                    ((type) == GLB_UART_SIG_6) || \
                                    ((type) == GLB_UART_SIG_7))

/** @defgroup  GLB_UART_SIG_FUN_TYPE
 *  @{
 */
#define IS_GLB_UART_SIG_FUN_TYPE(type) (((type) == GLB_UART_SIG_FUN_UART0_RTS) || \
                                        ((type) == GLB_UART_SIG_FUN_UART0_CTS) || \
                                        ((type) == GLB_UART_SIG_FUN_UART0_TXD) || \
                                        ((type) == GLB_UART_SIG_FUN_UART0_RXD) || \
                                        ((type) == GLB_UART_SIG_FUN_UART1_RTS) || \
                                        ((type) == GLB_UART_SIG_FUN_UART1_CTS) || \
                                        ((type) == GLB_UART_SIG_FUN_UART1_TXD) || \
                                        ((type) == GLB_UART_SIG_FUN_UART1_RXD))

/** @defgroup  GLB_DLL_CLK_TYPE
 *  @{
 */
#define IS_GLB_DLL_CLK_TYPE(type) (((type) == GLB_DLL_CLK_57P6M) || \
                                   ((type) == GLB_DLL_CLK_96M) ||   \
                                   ((type) == GLB_DLL_CLK_144M) ||  \
                                   ((type) == GLB_DLL_CLK_288M) ||  \
                                   ((type) == GLB_DLL_CLK_MMDIV))

/** @defgroup  GLB_GPIO_INT_TRIG_TYPE
 *  @{
 */
#define IS_GLB_GPIO_INT_TRIG_TYPE(type) (((type) == GLB_GPIO_INT_TRIG_NEG_PULSE) || \
                                         ((type) == GLB_GPIO_INT_TRIG_POS_PULSE) || \
                                         ((type) == GLB_GPIO_INT_TRIG_NEG_LEVEL) || \
                                         ((type) == GLB_GPIO_INT_TRIG_POS_LEVEL))

/** @defgroup  GLB_GPIO_INT_CONTROL_TYPE
 *  @{
 */
#define IS_GLB_GPIO_INT_CONTROL_TYPE(type) (((type) == GLB_GPIO_INT_CONTROL_SYNC) || \
                                            ((type) == GLB_GPIO_INT_CONTROL_ASYNC))

/** @defgroup  GLB_DLL_XTAL_TYPE
 *  @{
 */
#define IS_GLB_DLL_XTAL_TYPE(type) (((type) == GLB_DLL_XTAL_NONE) || \
                                    ((type) == GLB_DLL_XTAL_32M) ||  \
                                    ((type) == GLB_DLL_XTAL_RC32M))

/*@} end of group GLB_Public_Constants */

/** @defgroup  GLB_Public_Macros
 *  @{
 */
#define UART_SIG_SWAP_GPIO0_GPIO7   0x01 /* GPIO0-7   uart_sig[0:7] -> uart_sig[4:7], uart_sig[0:3] */
#define UART_SIG_SWAP_GPIO8_GPIO15  0x02 /* GPIO8-15  uart_sig[0:7] -> uart_sig[4:7], uart_sig[0:3] */
#define UART_SIG_SWAP_GPIO16_GPIO22 0x04 /* GPIO16-22 uart_sig[0:7] -> uart_sig[4:7], uart_sig[0:3] */
#define UART_SIG_SWAP_NONE          0x00 /* GPIO0-22  uart_sig[0:7] <- uart_sig[4:7], uart_sig[0:3] */
#define JTAG_SIG_SWAP_GPIO0_GPIO3   0x01 /* GPIO0-3   E21_TMS/E21_TDI/E21_TCK/E21_TDO -> E21_TCK/E21_TDO/E21_TMS/E21_TDI */
#define JTAG_SIG_SWAP_GPIO4_GPIO7   0x02 /* GPIO4-7   E21_TMS/E21_TDI/E21_TCK/E21_TDO -> E21_TCK/E21_TDO/E21_TMS/E21_TDI */
#define JTAG_SIG_SWAP_GPIO8_GPIO11  0x04 /* GPIO8-11  E21_TMS/E21_TDI/E21_TCK/E21_TDO -> E21_TCK/E21_TDO/E21_TMS/E21_TDI */
#define JTAG_SIG_SWAP_GPIO12_GPIO15 0x08 /* GPIO12-15 E21_TMS/E21_TDI/E21_TCK/E21_TDO -> E21_TCK/E21_TDO/E21_TMS/E21_TDI */
#define JTAG_SIG_SWAP_GPIO16_GPIO19 0x10 /* GPIO16-19 E21_TMS/E21_TDI/E21_TCK/E21_TDO -> E21_TCK/E21_TDO/E21_TMS/E21_TDI */
#define JTAG_SIG_SWAP_GPIO20_GPIO22 0x20 /* GPIO20-22 E21_TMS/E21_TDI/E21_TCK/E21_TDO -> E21_TCK/E21_TDO/E21_TMS/E21_TDI */
#define JTAG_SIG_SWAP_NONE          0x00 /* GPIO0-22  E21_TMS/E21_TDI/E21_TCK/E21_TDO <- E21_TCK/E21_TDO/E21_TMS/E21_TDI */

#define GLB_AHB_CLOCK_CPU             (0x0000000000000001UL)
#define GLB_AHB_CLOCK_SDU             (0x0000000000000002UL)
#define GLB_AHB_CLOCK_SEC             (0x0000000000000004UL)
#define GLB_AHB_CLOCK_DMA_0           (0x0000000000000008UL)
#define GLB_AHB_CLOCK_DMA_1           (0x0000000000000010UL)
#define GLB_AHB_CLOCK_DMA_2           (0x0000000000000020UL)
#define GLB_AHB_CLOCK_CCI             (0x0000000000000040UL)
#define GLB_AHB_CLOCK_RF_TOP          (0x0000000000000080UL)
#define GLB_AHB_CLOCK_GPIP            (0x0000000000000100UL)
#define GLB_AHB_CLOCK_TZC             (0x0000000000000200UL)
#define GLB_AHB_CLOCK_EF_CTRL         (0x0000000000000400UL)
#define GLB_AHB_CLOCK_SF_CTRL         (0x0000000000000800UL)
#define GLB_AHB_CLOCK_EMAC            (0x0000000000001000UL)
#define GLB_AHB_CLOCK_UART0           (0x0000000000002000UL)
#define GLB_AHB_CLOCK_UART1           (0x0000000000004000UL)
#define GLB_AHB_CLOCK_UART2           (0x0000000000008000UL)
#define GLB_AHB_CLOCK_UART3           (0x0000000000010000UL)
#define GLB_AHB_CLOCK_UART4           (0x0000000000020000UL)
#define GLB_AHB_CLOCK_SPI             (0x0000000000040000UL)
#define GLB_AHB_CLOCK_I2C             (0x0000000000080000UL)
#define GLB_AHB_CLOCK_PWM             (0x0000000000100000UL)
#define GLB_AHB_CLOCK_TIMER           (0x0000000000200000UL)
#define GLB_AHB_CLOCK_IR              (0x0000000000400000UL)
#define GLB_AHB_CLOCK_CHECKSUM        (0x0000000000800000UL)
#define GLB_AHB_CLOCK_QDEC            (0x0000000001000000UL)
#define GLB_AHB_CLOCK_KYS             (0x0000000002000000UL)
#define GLB_AHB_CLOCK_I2S             (0x0000000004000000UL)
#define GLB_AHB_CLOCK_USB11           (0x0000000008000000UL)
#define GLB_AHB_CLOCK_CAM             (0x0000000010000000UL)
#define GLB_AHB_CLOCK_MJPEG           (0x0000000020000000UL)
#define GLB_AHB_CLOCK_BT_BLE_NORMAL   (0x0000000040000000UL)
#define GLB_AHB_CLOCK_BT_BLE_LP       (0x0000000080000000UL)
#define GLB_AHB_CLOCK_ZB_NORMAL       (0x0000000100000000UL)
#define GLB_AHB_CLOCK_ZB_LP           (0x0000000200000000UL)
#define GLB_AHB_CLOCK_WIFI_NORMAL     (0x0000000400000000UL)
#define GLB_AHB_CLOCK_WIFI_LP         (0x0000000800000000UL)
#define GLB_AHB_CLOCK_BT_BLE_2_NORMAL (0x0000001000000000UL)
#define GLB_AHB_CLOCK_BT_BLE_2_LP     (0x0000002000000000UL)
#define GLB_AHB_CLOCK_EMI_MISC        (0x0000004000000000UL)
#define GLB_AHB_CLOCK_PSRAM0_CTRL     (0x0000008000000000UL)
#define GLB_AHB_CLOCK_PSRAM1_CTRL     (0x0000010000000000UL)
#define GLB_AHB_CLOCK_USB20           (0x0000020000000000UL)
#define GLB_AHB_CLOCK_MIX2            (0x0000040000000000UL)
#define GLB_AHB_CLOCK_AUDIO           (0x0000080000000000UL)
#define GLB_AHB_CLOCK_SDH             (0x0000100000000000UL)

/*@} end of group GLB_Public_Macros */

/** @defgroup  GLB_Public_Functions
 *  @{
 */
/*----------*/
#ifndef BFLB_USE_HAL_DRIVER
void BMX_ERR_IRQHandler(void);
void BMX_TO_IRQHandler(void);
void GPIO_INT0_IRQHandler(void);
#endif
/*----------*/
GLB_ROOT_CLK_Type GLB_Get_Root_CLK_Sel(void);
BL_Err_Type GLB_Set_System_CLK_Div(uint8_t hclkDiv, uint8_t bclkDiv);
uint8_t GLB_Get_BCLK_Div(void);
uint8_t GLB_Get_HCLK_Div(void);
BL_Err_Type Update_SystemCoreClockWith_XTAL(GLB_DLL_XTAL_Type xtalType);
BL_Err_Type GLB_Set_System_CLK(GLB_DLL_XTAL_Type xtalType, GLB_SYS_CLK_Type clkFreq);
BL_Err_Type System_Core_Clock_Update_From_RC32M(void);
/*----------*/
BL_Err_Type GLB_Set_CAM_CLK(uint8_t enable, GLB_CAM_CLK_Type clkSel, uint8_t div);
BL_Err_Type GLB_Set_MAC154_ZIGBEE_CLK(uint8_t enable);
BL_Err_Type GLB_Set_BLE_CLK(uint8_t enable);
BL_Err_Type GLB_Set_I2S_CLK(uint8_t enable, GLB_I2S_OUT_REF_CLK_Type outRef);
BL_Err_Type GLB_Set_USB_CLK(uint8_t enable);
BL_Err_Type GLB_Set_QDEC_CLK(GLB_QDEC_CLK_Type clkSel, uint8_t div);
/*----------*/
BL_Err_Type GLB_Set_DMA_CLK(uint8_t enable, GLB_DMA_CLK_ID_Type clk);
BL_Err_Type GLB_Set_IR_CLK(uint8_t enable, GLB_IR_CLK_SRC_Type clkSel, uint8_t div);
BL_Err_Type GLB_Set_SF_CLK(uint8_t enable, GLB_SFLASH_CLK_Type clkSel, uint8_t div);
BL_Err_Type GLB_Set_UART_CLK(uint8_t enable, HBN_UART_CLK_Type clkSel, uint8_t div);
/*----------*/
BL_Err_Type GLB_Set_Chip_Out_0_CLK_Sel(GLB_CHIP_CLK_OUT_Type clkSel);
BL_Err_Type GLB_Set_Chip_Out_1_CLK_Sel(GLB_CHIP_CLK_OUT_Type clkSel);
BL_Err_Type GLB_Set_I2C_CLK(uint8_t enable, uint8_t div);
BL_Err_Type GLB_Invert_ETH_RX_CLK(uint8_t enable);
BL_Err_Type GLB_Invert_RF_TEST_O_CLK(uint8_t enable);
BL_Err_Type GLB_Set_SPI_CLK(uint8_t enable, uint8_t div);
BL_Err_Type GLB_Invert_ETH_TX_CLK(uint8_t enable);
BL_Err_Type GLB_Invert_ETH_REF_O_CLK(uint8_t enable);
BL_Err_Type GLB_Set_ETH_REF_O_CLK_Sel(GLB_ETH_REF_CLK_OUT_Type clkSel);
/*----------*/
BL_Err_Type GLB_Set_PKA_CLK_Sel(GLB_PKA_CLK_Type clkSel);
BL_Err_Type GLB_SW_System_Reset(void);
BL_Err_Type GLB_SW_CPU_Reset(void);
BL_Err_Type GLB_SW_POR_Reset(void);
BL_Err_Type GLB_AHB_Slave1_Reset(BL_AHB_Slave1_Type slave1);
BL_Err_Type GLB_AHB_Slave1_Clock_Gate(uint8_t enable, BL_AHB_Slave1_Type slave1);
uint64_t GLB_PER_Clock_Gate_Status_Get(void);
BL_Err_Type GLB_PER_Clock_Gate(uint64_t ips);
BL_Err_Type GLB_PER_Clock_UnGate(uint64_t ips);
/*----------*/
BL_Err_Type GLB_BMX_Init(BMX_Cfg_Type *BmxCfg);
BL_Err_Type GLB_BMX_Addr_Monitor_Enable(void);
BL_Err_Type GLB_BMX_Addr_Monitor_Disable(void);
BL_Err_Type GLB_BMX_BusErrResponse_Enable(void);
BL_Err_Type GLB_BMX_BusErrResponse_Disable(void);
BL_Sts_Type GLB_BMX_Get_Status(BMX_BUS_ERR_Type errType);
uint32_t GLB_BMX_Get_Err_Addr(void);
BL_Err_Type BMX_ERR_INT_Callback_Install(BMX_ERR_INT_Type intType, intCallback_Type *cbFun);
BL_Err_Type BMX_TIMEOUT_INT_Callback_Install(BMX_TO_INT_Type intType, intCallback_Type *cbFun);
/*----------*/
BL_Err_Type GLB_Set_SRAM_RET(uint32_t value);
uint32_t GLB_Get_SRAM_RET(void);
BL_Err_Type GLB_Set_SRAM_SLP(uint32_t value);
uint32_t GLB_Get_SRAM_SLP(void);
BL_Err_Type GLB_Set_SRAM_PARM(uint32_t value);
uint32_t GLB_Get_SRAM_PARM(void);
/*----------*/
BL_Err_Type GLB_Set_EM_Sel(GLB_EM_Type emType);
/*----------*/
BL_Err_Type GLB_SWAP_EMAC_CAM_Pin(GLB_EMAC_CAM_PIN_Type pinType);
BL_Err_Type GLB_Set_Ext_Rst_Smt(uint8_t enable);
BL_Err_Type GLB_Set_Kys_Drv_Col(uint8_t enable);
BL_Err_Type GLB_UART_Sig_Swap_Set(uint8_t swapSel);
BL_Err_Type GLB_JTAG_Sig_Swap_Set(uint8_t swapSel);
BL_Err_Type GLB_CCI_Use_IO_0_1_2_7(uint8_t enable);
BL_Err_Type GLB_CCI_Use_Jtag_Pin(uint8_t enable);
BL_Err_Type GLB_Swap_SPI_0_MOSI_With_MISO(BL_Fun_Type newState);
BL_Err_Type GLB_Set_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_Type mod);
BL_Err_Type GLB_Select_Internal_Flash(void);
BL_Err_Type GLB_Select_External_Flash(void);
BL_Err_Type GLB_Deswap_Flash_Pin(void);
BL_Err_Type GLB_Swap_Flash_CS_IO2_Pin();
BL_Err_Type GLB_Swap_Flash_IO0_IO3_Pin();
BL_Err_Type GLB_Swap_Flash_Pin(void);
BL_Err_Type GLB_Select_Internal_PSram(void);
/*----------*/
BL_Err_Type GLB_Set_PDM_CLK(uint8_t enable, uint8_t div);
/*----------*/
BL_Err_Type GLB_Set_MTimer_CLK(uint8_t enable, GLB_MTIMER_CLK_Type clkSel, uint32_t div);
/*----------*/
BL_Err_Type GLB_Set_ADC_CLK(uint8_t enable, GLB_ADC_CLK_Type clkSel, uint8_t div);
BL_Err_Type GLB_Set_DAC_CLK(uint8_t enable, GLB_DAC_CLK_Type clkSel, uint8_t div);
/*----------*/
BL_Err_Type GLB_Set_DIG_CLK_Sel(GLB_DIG_CLK_Type clkSel);
BL_Err_Type GLB_Set_DIG_512K_CLK(uint8_t enable, uint8_t compensation, uint8_t div);
BL_Err_Type GLB_Set_DIG_32K_CLK(uint8_t enable, uint8_t compensation, uint16_t div);
/*----------*/
BL_Err_Type GLB_Set_BT_Coex_Signal(uint8_t enable, GLB_BT_BANDWIDTH_Type bandWidth,
                                   uint8_t pti, uint8_t channel);
/*----------*/
BL_Err_Type GLB_UART_Fun_Sel(GLB_UART_SIG_Type sig, GLB_UART_SIG_FUN_Type fun);
/*----------*/
BL_Err_Type GLB_Power_Off_DLL(void);
BL_Err_Type GLB_Power_On_DLL(GLB_DLL_XTAL_Type xtalType);
BL_Err_Type GLB_Enable_DLL_All_Clks(void);
BL_Err_Type GLB_Enable_DLL_Clk(GLB_DLL_CLK_Type dllClk);
BL_Err_Type GLB_Disable_DLL_All_Clks(void);
BL_Err_Type GLB_Disable_DLL_Clk(GLB_DLL_CLK_Type dllClk);
/*----------*/
BL_Err_Type GLB_IR_RX_GPIO_Sel(GLB_GPIO_Type gpio);
BL_Err_Type GLB_IR_LED_Driver_Enable(void);
BL_Err_Type GLB_IR_LED_Driver_Disable(void);
BL_Err_Type GLB_IR_LED_Driver_Output_Enable(GLB_GPIO_Type gpio);
BL_Err_Type GLB_IR_LED_Driver_Output_Disable(GLB_GPIO_Type gpio);
BL_Err_Type GLB_IR_LED_Driver_Ibias(uint8_t ibias);
/*----------*/
BL_Err_Type GLB_GPIO_Init(GLB_GPIO_Cfg_Type *cfg);
BL_Err_Type GLB_GPIO_Func_Init(GLB_GPIO_FUNC_Type gpioFun, GLB_GPIO_Type *pinList, uint8_t cnt);
BL_Err_Type GLB_GPIO_INPUT_Enable(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_INPUT_Disable(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_OUTPUT_Enable(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_OUTPUT_Disable(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_Set_HZ(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_Set_Flash_Pad_HZ(void);
BL_Err_Type GLB_Set_Psram_Pad_HZ(void);
uint8_t GLB_GPIO_Get_Fun(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_Write(GLB_GPIO_Type gpioPin, uint32_t val);
uint32_t GLB_GPIO_Read(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_IntMask(GLB_GPIO_Type gpioPin, BL_Mask_Type intMask);
BL_Err_Type GLB_GPIO_IntClear(GLB_GPIO_Type gpioPin, BL_Sts_Type intClear);
BL_Sts_Type GLB_Get_GPIO_IntStatus(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_Set_GPIO_IntMod(GLB_GPIO_Type gpioPin, GLB_GPIO_INT_CONTROL_Type intCtlMod,
                                GLB_GPIO_INT_TRIG_Type intTrgMod);
GLB_GPIO_INT_CONTROL_Type GLB_Get_GPIO_IntCtlMod(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_Int2Mask(GLB_GPIO_Type gpioPin, BL_Mask_Type intMask);
BL_Err_Type GLB_GPIO_Int2Clear(GLB_GPIO_Type gpioPin, BL_Sts_Type intClear);
BL_Sts_Type GLB_Get_GPIO_Int2Status(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_Set_GPIO_Int2Mod(GLB_GPIO_Type gpioPin, GLB_GPIO_INT_CONTROL_Type intCtlMod,
                                 GLB_GPIO_INT_TRIG_Type intTrgMod);
GLB_GPIO_INT_CONTROL_Type GLB_Get_GPIO_Int2CtlMod(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_INT0_IRQHandler_Install(void);
BL_Err_Type GLB_GPIO_INT0_Callback_Install(GLB_GPIO_Type gpioPin, intCallback_Type *cbFun);
BL_Err_Type GLB_GPIO_INT0_Callback_Install2(GLB_GPIO_Type gpioPin, intCallback_Type *cbFun);
/*----------*/;

/*@} end of group GLB_Public_Functions */

/*@} end of group GLB */

/*@} end of group BL702_Peripheral_Driver */

#endif /* __BL702_GLB_H__ */
