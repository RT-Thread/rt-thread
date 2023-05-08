/**
  ******************************************************************************
  * @file    bl602_glb.h
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
#ifndef __BL602_GLB_H__
#define __BL602_GLB_H__

#include "glb_reg.h"
#include "pds_reg.h"
#include "bl602_gpio.h"
#include "bl602_l1c.h"
#include "bl602_hbn.h"
#include "bl602_aon.h"
#include "bl602_pds.h"
#include "bl602_common.h"
#include "bflb_sf_ctrl.h"
#include "bflb_sf_cfg.h"

/** @addtogroup  BL602_Peripheral_Driver
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
    GLB_ROOT_CLK_PLL,   /*!< root clock select PLL others */
} GLB_ROOT_CLK_Type;

/**
 *  @brief GLB system clock type definition
 */
typedef enum {
    GLB_SYS_CLK_RC32M,   /*!< use RC32M as system clock frequency */
    GLB_SYS_CLK_XTAL,    /*!< use XTAL as system clock */
    GLB_SYS_CLK_PLL48M,  /*!< use PLL output 48M as system clock */
    GLB_SYS_CLK_PLL120M, /*!< use PLL output 120M as system clock */
    GLB_SYS_CLK_PLL160M, /*!< use PLL output 160M as system clock */
    GLB_SYS_CLK_PLL192M, /*!< use PLL output 192M as system clock */
} GLB_SYS_CLK_Type;

/**
 *  @brief GLB DMA clock ID type definition
 */
typedef enum {
    GLB_DMA_CLK_DMA0_CH0, /*!< DMA clock ID:channel 0 */
    GLB_DMA_CLK_DMA0_CH1, /*!< DMA clock ID:channel 1 */
    GLB_DMA_CLK_DMA0_CH2, /*!< DMA clock ID:channel 2 */
    GLB_DMA_CLK_DMA0_CH3, /*!< DMA clock ID:channel 3 */
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
    GLB_SFLASH_CLK_120M, /*!< Select 120M as flash clock */
    GLB_SFLASH_CLK_XTAL, /*!< Select XTAL as flash clock */
    GLB_SFLASH_CLK_48M,  /*!< Select 48M as flash clock */
    GLB_SFLASH_CLK_80M,  /*!< Select 80M as flash clock */
    GLB_SFLASH_CLK_BCLK, /*!< Select BCLK as flash clock */
    GLB_SFLASH_CLK_96M,  /*!< Select 96M as flash clock */
} GLB_SFLASH_CLK_Type;

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
    GLB_PKA_CLK_HCLK,    /*!< Select HCLK as PKA clock */
    GLB_PKA_CLK_PLL120M, /*!< Select PLL 120M as PKA clock */
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
typedef struct
{
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
    GLB_ADC_CLK_96M,  /*!< use 96M as ADC clock */
    GLB_ADC_CLK_XCLK, /*!< use XCLK as ADC clock */
} GLB_ADC_CLK_Type;

/**
 *  @brief GLB DAC clock type definition
 */
typedef enum {
    GLB_DAC_CLK_32M,  /*!< use 32M as DAC clock */
    GLB_DAC_CLK_XCLK, /*!< use XCLK as DAC clock */
} GLB_DAC_CLK_Type;

/**
 *  @brief GLB DIG clock source select type definition
 */
typedef enum {
    GLB_DIG_CLK_PLL_32M, /*!< select PLL 32M as DIG clock source */
    GLB_DIG_CLK_XCLK,    /*!< select XCLK as DIG clock source */
} GLB_DIG_CLK_Type;

/**
 *  @brief GLB 512K clock out select type definition
 */
typedef enum {
    GLB_512K_CLK_OUT_512K, /*!< select 512K clock out */
    GLB_512K_CLK_OUT_256K, /*!< select 256K clock out */
    GLB_512K_CLK_OUT_128K, /*!< select 128K clock out */
} GLB_512K_CLK_OUT_Type;

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
 *  @brief GLB GPIO real mode type definition
 */
typedef enum {
    GLB_GPIO_REAL_MODE_REG,        /*!< GPIO real function is reg_gpio_x_func_sel */
    GLB_GPIO_REAL_MODE_SDIO = 0x1, /*!< GPIO real function is SDIO */
    GLB_GPIO_REAL_MODE_RF = 0xC,   /*!< GPIO real function is RF */
    GLB_GPIO_REAL_MODE_JTAG = 0xE, /*!< GPIO real function is JTAG */
    GLB_GPIO_REAL_MODE_CCI = 0xF,  /*!< GPIO real function is CCI */
} GLB_GPIO_REAL_MODE_Type;

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
    GLB_PLL_XTAL_NONE,  /*!< XTAL is none */
    GLB_PLL_XTAL_24M,   /*!< XTAL is 24M */
    GLB_PLL_XTAL_32M,   /*!< XTAL is 32M */
    GLB_PLL_XTAL_38P4M, /*!< XTAL is 38.4M */
    GLB_PLL_XTAL_40M,   /*!< XTAL is 40M */
    GLB_PLL_XTAL_26M,   /*!< XTAL is 26M */
    GLB_PLL_XTAL_RC32M, /*!< XTAL is RC32M */
} GLB_PLL_XTAL_Type;

/**
 *  @brief PLL output clock type definition
 */
typedef enum {
    GLB_PLL_CLK_480M, /*!< PLL output clock:480M */
    GLB_PLL_CLK_240M, /*!< PLL output clock:240M */
    GLB_PLL_CLK_192M, /*!< PLL output clock:192M */
    GLB_PLL_CLK_160M, /*!< PLL output clock:160M */
    GLB_PLL_CLK_120M, /*!< PLL output clock:120M */
    GLB_PLL_CLK_96M,  /*!< PLL output clock:96M */
    GLB_PLL_CLK_80M,  /*!< PLL output clock:80M */
    GLB_PLL_CLK_48M,  /*!< PLL output clock:48M */
    GLB_PLL_CLK_32M,  /*!< PLL output clock:32M */
} GLB_PLL_CLK_Type;

/**
 *  @brief PLL configuration structure type definition
 */
typedef struct
{
    uint8_t clkpllIcp1u;        /*!< int mode:0, frac mode:1 */
    uint8_t clkpllIcp5u;        /*!< int mode:2, frac mode:0 */
    uint8_t clkpllIntFracSw;    /*!< 0:int mode, 1:frac mode */
    uint8_t clkpllC3;           /*!< int:3, frac:2 */
    uint8_t clkpllCz;           /*!< int:1, frac:2 */
    uint8_t clkpllRz;           /*!< int:1, frac:5 */
    uint8_t clkpllR4;           /*!< int:2, frac:2 */
    uint8_t clkpllR4Short;      /*!< int:1, frac:0 */
    uint8_t clkpllRefdivRatio;  /*!< ref divider ratio */
    uint8_t clkpllPostdiv;      /*!< >=8 and should be even number */
    uint32_t clkpllSdmin;       /*!< sdmin */
    uint8_t clkpllSelFbClk;     /*!< 0:mod1, 1:mod2, 2:mod3 */
    uint8_t clkpllSelSampleClk; /*!< 0:[16,63)mod3, 1:[32:127)mod4, 2:[64,255)mod5 */
} GLB_PLL_Cfg_Type;

/*@} end of group GLB_Public_Types */

/** @defgroup  GLB_Public_Constants
 *  @{
 */

/** @defgroup  GLB_ROOT_CLK_TYPE
 *  @{
 */
#define IS_GLB_ROOT_CLK_TYPE(type) (((type) == GLB_ROOT_CLK_RC32M) || \
                                    ((type) == GLB_ROOT_CLK_XTAL) ||  \
                                    ((type) == GLB_ROOT_CLK_PLL))

/** @defgroup  GLB_SYS_CLK_TYPE
 *  @{
 */
#define IS_GLB_SYS_CLK_TYPE(type) (((type) == GLB_SYS_CLK_RC32M) ||   \
                                   ((type) == GLB_SYS_CLK_XTAL) ||    \
                                   ((type) == GLB_SYS_CLK_PLL48M) ||  \
                                   ((type) == GLB_SYS_CLK_PLL120M) || \
                                   ((type) == GLB_SYS_CLK_PLL160M) || \
                                   ((type) == GLB_SYS_CLK_PLL192M))

/** @defgroup  GLB_DMA_CLK_ID_TYPE
 *  @{
 */
#define IS_GLB_DMA_CLK_ID_TYPE(type) (((type) == GLB_DMA_CLK_DMA0_CH0) || \
                                      ((type) == GLB_DMA_CLK_DMA0_CH1) || \
                                      ((type) == GLB_DMA_CLK_DMA0_CH2) || \
                                      ((type) == GLB_DMA_CLK_DMA0_CH3))

/** @defgroup  GLB_IR_CLK_SRC_TYPE
 *  @{
 */
#define IS_GLB_IR_CLK_SRC_TYPE(type) (((type) == GLB_IR_CLK_SRC_XCLK))

/** @defgroup  GLB_SFLASH_CLK_TYPE
 *  @{
 */
#define IS_GLB_SFLASH_CLK_TYPE(type) (((type) == GLB_SFLASH_CLK_120M) || \
                                      ((type) == GLB_SFLASH_CLK_XTAL) || \
                                      ((type) == GLB_SFLASH_CLK_48M) ||  \
                                      ((type) == GLB_SFLASH_CLK_80M) ||  \
                                      ((type) == GLB_SFLASH_CLK_BCLK) || \
                                      ((type) == GLB_SFLASH_CLK_96M))

/** @defgroup  GLB_SPI_PAD_ACT_AS_TYPE
 *  @{
 */
#define IS_GLB_SPI_PAD_ACT_AS_TYPE(type) (((type) == GLB_SPI_PAD_ACT_AS_SLAVE) || \
                                          ((type) == GLB_SPI_PAD_ACT_AS_MASTER))

/** @defgroup  GLB_PKA_CLK_TYPE
 *  @{
 */
#define IS_GLB_PKA_CLK_TYPE(type) (((type) == GLB_PKA_CLK_HCLK) || \
                                   ((type) == GLB_PKA_CLK_PLL120M))

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

/** @defgroup  GLB_MTIMER_CLK_TYPE
 *  @{
 */
#define IS_GLB_MTIMER_CLK_TYPE(type) (((type) == GLB_MTIMER_CLK_BCLK) || \
                                      ((type) == GLB_MTIMER_CLK_32K))

/** @defgroup  GLB_ADC_CLK_TYPE
 *  @{
 */
#define IS_GLB_ADC_CLK_TYPE(type) (((type) == GLB_ADC_CLK_96M) || \
                                   ((type) == GLB_ADC_CLK_XCLK))

/** @defgroup  GLB_DAC_CLK_TYPE
 *  @{
 */
#define IS_GLB_DAC_CLK_TYPE(type) (((type) == GLB_DAC_CLK_32M) || \
                                   ((type) == GLB_DAC_CLK_XCLK))

/** @defgroup  GLB_DIG_CLK_TYPE
 *  @{
 */
#define IS_GLB_DIG_CLK_TYPE(type) (((type) == GLB_DIG_CLK_PLL_32M) || \
                                   ((type) == GLB_DIG_CLK_XCLK))

/** @defgroup  GLB_512K_CLK_OUT_TYPE
 *  @{
 */
#define IS_GLB_512K_CLK_OUT_TYPE(type) (((type) == GLB_512K_CLK_OUT_512K) || \
                                        ((type) == GLB_512K_CLK_OUT_256K) || \
                                        ((type) == GLB_512K_CLK_OUT_128K))

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

/** @defgroup  GLB_GPIO_REAL_MODE_TYPE
 *  @{
 */
#define IS_GLB_GPIO_REAL_MODE_TYPE(type) (((type) == GLB_GPIO_REAL_MODE_REG) ||  \
                                          ((type) == GLB_GPIO_REAL_MODE_SDIO) || \
                                          ((type) == GLB_GPIO_REAL_MODE_RF) ||   \
                                          ((type) == GLB_GPIO_REAL_MODE_JTAG) || \
                                          ((type) == GLB_GPIO_REAL_MODE_CCI))

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

/** @defgroup  GLB_PLL_XTAL_TYPE
 *  @{
 */
#define IS_GLB_PLL_XTAL_TYPE(type) (((type) == GLB_PLL_XTAL_NONE) ||  \
                                    ((type) == GLB_PLL_XTAL_24M) ||   \
                                    ((type) == GLB_PLL_XTAL_32M) ||   \
                                    ((type) == GLB_PLL_XTAL_38P4M) || \
                                    ((type) == GLB_PLL_XTAL_40M) ||   \
                                    ((type) == GLB_PLL_XTAL_26M) ||   \
                                    ((type) == GLB_PLL_XTAL_RC32M))

/** @defgroup  GLB_PLL_CLK_TYPE
 *  @{
 */
#define IS_GLB_PLL_CLK_TYPE(type) (((type) == GLB_PLL_CLK_480M) || \
                                   ((type) == GLB_PLL_CLK_240M) || \
                                   ((type) == GLB_PLL_CLK_192M) || \
                                   ((type) == GLB_PLL_CLK_160M) || \
                                   ((type) == GLB_PLL_CLK_120M) || \
                                   ((type) == GLB_PLL_CLK_96M) ||  \
                                   ((type) == GLB_PLL_CLK_80M) ||  \
                                   ((type) == GLB_PLL_CLK_48M) ||  \
                                   ((type) == GLB_PLL_CLK_32M))

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
BL_Err_Type Update_SystemCoreClockWith_XTAL(GLB_PLL_XTAL_Type xtalType);
BL_Err_Type GLB_Set_System_CLK(GLB_PLL_XTAL_Type xtalType, GLB_SYS_CLK_Type clkFreq);
BL_Err_Type System_Core_Clock_Update_From_RC32M(void);
/*----------*/
BL_Err_Type GLB_Set_BLE_CLK(uint8_t enable);
BL_Err_Type GLB_Set_WiFi_Core_CLK(uint8_t clkDiv);
BL_Err_Type GLB_Set_WiFi_Encrypt_CLK(uint8_t clkDiv);
BL_Err_Type GLB_Set_DMA_CLK(uint8_t enable, GLB_DMA_CLK_ID_Type clk);
BL_Err_Type GLB_Set_IR_CLK(uint8_t enable, GLB_IR_CLK_SRC_Type clkSel, uint8_t div);
BL_Err_Type GLB_Set_SF_CLK(uint8_t enable, GLB_SFLASH_CLK_Type clkSel, uint8_t div);
BL_Err_Type GLB_Set_UART_CLK(uint8_t enable, HBN_UART_CLK_Type clkSel, uint8_t div);
BL_Err_Type GLB_Set_I2C_CLK(uint8_t enable, uint8_t div);
BL_Err_Type GLB_Set_SPI_CLK(uint8_t enable, uint8_t div);
/*----------*/
BL_Err_Type GLB_Set_PKA_CLK_Sel(GLB_PKA_CLK_Type clkSel);
BL_Err_Type GLB_SW_System_Reset(void);
BL_Err_Type GLB_SW_CPU_Reset(void);
BL_Err_Type GLB_SW_POR_Reset(void);
BL_Err_Type GLB_AHB_Slave1_Reset(BL_AHB_Slave1_Type slave1);
BL_Err_Type GLB_AHB_Slave1_Clock_Gate(uint8_t enable, BL_AHB_Slave1_Type slave1);
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
BL_Err_Type GLB_Set_OCRAM_Idle(void);
BL_Err_Type GLB_Set_SRAM_RET(uint32_t value);
uint32_t GLB_Get_SRAM_RET(void);
BL_Err_Type GLB_Set_SRAM_SLP(uint32_t value);
uint32_t GLB_Get_SRAM_SLP(void);
BL_Err_Type GLB_Set_SRAM_PARM(uint32_t value);
uint32_t GLB_Get_SRAM_PARM(void);
/*----------*/
BL_Err_Type GLB_Set_EM_Sel(GLB_EM_Type emType);
/*----------*/
BL_Err_Type GLB_UART_Sig_Swap_Set(uint8_t swapSel);
BL_Err_Type GLB_JTAG_Sig_Swap_Set(uint8_t swapSel);
BL_Err_Type GLB_Swap_SPI_0_MOSI_With_MISO(BL_Fun_Type newState);
BL_Err_Type GLB_Set_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_Type mod);
BL_Err_Type GLB_Select_Internal_Flash(void);
BL_Err_Type GLB_Select_External_Flash(void);
BL_Err_Type GLB_Deswap_Flash_Pin(void);
BL_Err_Type GLB_Swap_Flash_Pin(void);
/*----------*/
BL_Err_Type GLB_Set_MTimer_CLK(uint8_t enable, GLB_MTIMER_CLK_Type clkSel, uint32_t div);
/*----------*/
BL_Err_Type GLB_Set_ADC_CLK(uint8_t enable, GLB_ADC_CLK_Type clkSel, uint8_t div);
BL_Err_Type GLB_Set_DAC_CLK(uint8_t enable, GLB_DAC_CLK_Type clkSel, uint8_t div);
/*----------*/
BL_Err_Type GLB_Platform_Wakeup_Enable(void);
BL_Err_Type GLB_Platform_Wakeup_Disable(void);
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
BL_Err_Type GLB_IR_RX_GPIO_Sel(GLB_GPIO_Type gpio);
BL_Err_Type GLB_IR_LED_Driver_Enable(void);
BL_Err_Type GLB_IR_LED_Driver_Disable(void);
BL_Err_Type GLB_IR_LED_Driver_Ibias(uint8_t ibias);
/*----------*/
BL_Err_Type GLB_GPIO_Init(GLB_GPIO_Cfg_Type *cfg);
BL_Err_Type GLB_GPIO_Func_Init(GLB_GPIO_FUNC_Type gpioFun, GLB_GPIO_Type *pinList, uint8_t cnt);
BL_Err_Type GLB_GPIO_INPUT_Enable(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_INPUT_Disable(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_OUTPUT_Enable(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_OUTPUT_Disable(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_Set_PullUp(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_Set_PullDown(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_Set_HZ(GLB_GPIO_Type gpioPin);
uint8_t GLB_GPIO_Get_Fun(GLB_GPIO_Type gpioPin);
GLB_GPIO_REAL_MODE_Type GLB_GPIO_Get_Real_Fun(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_Write(GLB_GPIO_Type gpioPin, uint32_t val);
uint32_t GLB_GPIO_Read(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_IntMask(GLB_GPIO_Type gpioPin, BL_Mask_Type intMask);
BL_Err_Type GLB_GPIO_IntClear(GLB_GPIO_Type gpioPin, BL_Sts_Type intClear);
BL_Sts_Type GLB_Get_GPIO_IntStatus(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_Clr_GPIO_IntStatus(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_Set_GPIO_IntMod(GLB_GPIO_Type gpioPin, GLB_GPIO_INT_CONTROL_Type intCtlMod,
                                GLB_GPIO_INT_TRIG_Type intTrgMod);
GLB_GPIO_INT_CONTROL_Type GLB_Get_GPIO_IntCtlMod(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_INT0_IRQHandler_Install(void);
BL_Err_Type GLB_GPIO_INT0_Callback_Install(GLB_GPIO_Type gpioPin, intCallback_Type *cbFun);

/*@} end of group GLB_Public_Functions */

/*@} end of group GLB */

/*@} end of group BL602_Peripheral_Driver */

#endif /* __BL602_GLB_H__ */
