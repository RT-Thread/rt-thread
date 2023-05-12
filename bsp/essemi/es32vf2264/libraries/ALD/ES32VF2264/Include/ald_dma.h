/**
  *********************************************************************************
  *
  * @file    ald_dma.h
  * @brief   DMA module Library.
  *
  * @version V1.0
  * @date    16 Feb. 2023
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          16 Feb. 2023    AE Team         The first version
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  * SPDX-License-Identifier: Apache-2.0
  *
  * Licensed under the Apache License, Version 2.0 (the License); you may
  * not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  * www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an AS IS BASIS, WITHOUT
  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  **********************************************************************************
  */

#ifndef __ALD_DMA_H__
#define __ALD_DMA_H__

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "ald_utils.h"

/** @addtogroup ES32VF2264_ALD
  * @{
  */

/** @addtogroup DMA
  * @{
  */

/**
  * @defgroup DMA_Public_Macros DMA Public Macros
  * @{
  */
#define ALD_DMA_CH_COUNT    7U
/**
  * @}
  */

/**
  * @defgroup DMA_Public_Types DMA Public Types
  * @{
  */

/**
  * @brief Input source to DMA channel
  */
typedef enum {
    ALD_DMA_MSEL_NONE    = 0x0U,    /**< NONE */
    ALD_DMA_MSEL_GPIO    = 0x1U,    /**< GPIO */
    ALD_DMA_MSEL_ADC     = 0x2U,    /**< ADC */
    ALD_DMA_MSEL_CRC     = 0x3U,    /**< CRC */
    ALD_DMA_MSEL_EUART0  = 0x4U,    /**< EUART0 */
    ALD_DMA_MSEL_EUART1  = 0x5U,    /**< EUART1 */
    ALD_DMA_MSEL_CUART0  = 0x6U,    /**< CUART0 */
    ALD_DMA_MSEL_CUART1  = 0x7U,    /**< CUART1 */
    ALD_DMA_MSEL_CUART2  = 0x8U,    /**< CUART2 */
    ALD_DMA_MSEL_SPI0    = 0x9U,    /**< SPI0 */
    ALD_DMA_MSEL_SPI1    = 0xAU,    /**< SPI1 */
    ALD_DMA_MSEL_I2C0    = 0xBU,    /**< I2C0 */
    ALD_DMA_MSEL_I2C1    = 0xCU,    /**< I2C1 */
    ALD_DMA_MSEL_AD16C4T = 0xDU,    /**< AD16C4T */
    ALD_DMA_MSEL_GP16C4T0= 0xEU,    /**< GP16C4T0 */
    ALD_DMA_MSEL_GP16C4T1= 0xFU,    /**< GP16C4T1 */
    ALD_DMA_MSEL_GP16C4T2= 0x10U,   /**< GP16C4T2 */
    ALD_DMA_MSEL_PIS     = 0x11U,   /**< PIS */
    ALD_DMA_MSEL_BS16T   = 0x12U,   /**< BS16T */
} ald_dma_msel_t;

/**
  * @brief Input signal to DMA channel
  */
typedef enum {
    ALD_DMA_MSIGSEL_NONE           = 0x0U,   /**< NONE */
    ALD_DMA_MSIGSEL_EXTI_0         = 0x0U,   /**< External interrupt 0 */
    ALD_DMA_MSIGSEL_EXTI_1         = 0x1U,   /**< External interrupt 1 */
    ALD_DMA_MSIGSEL_EXTI_2         = 0x2U,   /**< External interrupt 2 */
    ALD_DMA_MSIGSEL_EXTI_3         = 0x3U,   /**< External interrupt 3 */
    ALD_DMA_MSIGSEL_EXTI_4         = 0x4U,   /**< External interrupt 4 */
    ALD_DMA_MSIGSEL_EXTI_5         = 0x5U,   /**< External interrupt 5 */
    ALD_DMA_MSIGSEL_EXTI_6         = 0x6U,   /**< External interrupt 6 */
    ALD_DMA_MSIGSEL_EXTI_7         = 0x7U,   /**< External interrupt 7 */
    ALD_DMA_MSIGSEL_EXTI_8         = 0x8U,   /**< External interrupt 8 */
    ALD_DMA_MSIGSEL_EXTI_9         = 0x9U,   /**< External interrupt 9 */
    ALD_DMA_MSIGSEL_EXTI_10        = 0xAU,   /**< External interrupt 10 */
    ALD_DMA_MSIGSEL_EXTI_11        = 0xBU,   /**< External interrupt 11 */
    ALD_DMA_MSIGSEL_EXTI_12        = 0xCU,   /**< External interrupt 12 */
    ALD_DMA_MSIGSEL_EXTI_13        = 0xDU,   /**< External interrupt 13 */
    ALD_DMA_MSIGSEL_EXTI_14        = 0xEU,   /**< External interrupt 14 */
    ALD_DMA_MSIGSEL_EXTI_15        = 0xFU,   /**< External interrupt 15 */
    ALD_DMA_MSIGSEL_ADC            = 0x0U,   /**< ADC mode */
    ALD_DMA_MSIGSEL_CRC            = 0x0U,   /**< CRC */
    ALD_DMA_MSIGSEL_UART_RNR       = 0x0U,   /**< UART reveive */
    ALD_DMA_MSIGSEL_UART_TXEMPTY   = 0x1U,   /**< UART transmit */
    ALD_DMA_MSIGSEL_SPI_RNR        = 0x0U,   /**< SPI receive */
    ALD_DMA_MSIGSEL_SPI_TXEMPTY    = 0x1U,   /**< SPI transmit */
    ALD_DMA_MSIGSEL_I2C_RNR        = 0x0U,   /**< I2C receive */
    ALD_DMA_MSIGSEL_I2C_TXEMPTY    = 0x1U,   /**< I2C transmit */
    ALD_DMA_MSIGSEL_TIMER_CH1      = 0x0U,   /**< TIM channal 1 */
    ALD_DMA_MSIGSEL_TIMER_CH2      = 0x1U,   /**< TIM channal 2 */
    ALD_DMA_MSIGSEL_TIMER_CH3      = 0x2U,   /**< TIM channal 3 */
    ALD_DMA_MSIGSEL_TIMER_CH4      = 0x3U,   /**< TIM channal 4 */
    ALD_DMA_MSIGSEL_TIMER_TRI      = 0x4U,   /**< TIM trigger */
    ALD_DMA_MSIGSEL_TIMER_COMP     = 0x5U,   /**< TIM compare */
    ALD_DMA_MSIGSEL_TIMER_UPDATE   = 0x6U,   /**< TIM update */
    ALD_DMA_MSIGSEL_PIS_CH0        = 0x0U,   /**< PIS channal 0 */
    ALD_DMA_MSIGSEL_PIS_CH1        = 0x1U,   /**< PIS channal 1 */
    ALD_DMA_MSIGSEL_PIS_CH2        = 0x2U,   /**< PIS channal 2 */
    ALD_DMA_MSIGSEL_PIS_CH3        = 0x3U,   /**< PIS channal 3 */
    ALD_DMA_MSIGSEL_PIS_CH4        = 0x4U,   /**< PIS channal 4 */
    ALD_DMA_MSIGSEL_PIS_CH5        = 0x5U,   /**< PIS channal 5 */
    ALD_DMA_MSIGSEL_PIS_CH6        = 0x6U,   /**< PIS channal 6 */
    ALD_DMA_MSIGSEL_PIS_CH7        = 0x7U,   /**< PIS channal 7 */
    ALD_DMA_MSIGSEL_BSTIM          = 0x0U,   /**< BSTIM */
} ald_dma_msigsel_t;

/**
  * @brief Priority of DMA channel
  */
typedef enum
{
    ALD_DMA_LOW_PRIORITY     = 0,
    ALD_DMA_MEDIUM_PRIORITY  = 1,
    ALD_DMA_HIGH_PRIORUTY    = 2,
    ALD_DMA_HIGHEST_PRIORITY = 3
} ald_dma_priority_t;

/**
  * @brief data increment
  */
typedef enum
{
    ALD_DMA_DATA_INC_DISABLE  = 0x0U,
    ALD_DMA_DATA_INC_ENABLE   = 0x1U,
} ald_dma_data_inc_t;

/**
  * @brief Data size
  */
typedef enum {
    ALD_DMA_DATA_SIZE_BYTE     = 0x0U,  /**< Byte */
    ALD_DMA_DATA_SIZE_HALFWORD = 0x1U,  /**< Halfword */
    ALD_DMA_DATA_SIZE_WORD     = 0x2U,  /**< Word */
} ald_dma_data_size_t;

/**
  * @brief Interrupt flag trigger mode
  */
typedef enum
{
    ALD_DMA_IT_FLAG_TC  = 0x0U,  /**< DMA transfer complete interrupt */
    ALD_DMA_IT_FLAG_HT  = 0x1U,  /**< DMA transfer half complete interrupt */
} ald_dma_it_flag_t;

/**
  * @brief Control how many DMA transfers can occur
  *        before the controller re-arbitrates
  */
typedef enum {
    ALD_DMA_R_POWER_1    = 0x0U,    /**< Arbitrates after each DMA transfer */
    ALD_DMA_R_POWER_2    = 0x1U,    /**< Arbitrates after 2 DMA transfer */
    ALD_DMA_R_POWER_4    = 0x2U,    /**< Arbitrates after 4 DMA transfer */
    ALD_DMA_R_POWER_8    = 0x3U,    /**< Arbitrates after 8 DMA transfer */
    ALD_DMA_R_POWER_16   = 0x4U,    /**< Arbitrates after 16 DMA transfer */
    ALD_DMA_R_POWER_32   = 0x5U,    /**< Arbitrates after 32 DMA transfer */
    ALD_DMA_R_POWER_64   = 0x6U,    /**< Arbitrates after 64 DMA transfer */
    ALD_DMA_R_POWER_128  = 0x7U,    /**< Arbitrates after 128 DMA transfer */
    ALD_DMA_R_POWER_256  = 0x8U,    /**< Arbitrates after 256 DMA transfer */
    ALD_DMA_R_POWER_512  = 0x9U,    /**< Arbitrates after 512 DMA transfer */
    ALD_DMA_R_POWER_1024 = 0xAU,    /**< Arbitrates after 1024 DMA transfer */
} ald_dma_arbiter_config_t;

/**
  * @brief Callback function pointer and param
  */
typedef struct {
    void (*cplt_tc_cbk)(void *arg);   /**< DMA transfers complete callback */
    void (*cplt_ht_cbk)(void* arg);   /**< DMA transfers half complete callback */
    void *cplt_tc_arg;                /**< The parameter of cplt_tc_cbk() */
    void *cplt_ht_arg;                /**< The parameter of cplt_ht_cbk() */
} ald_dma_call_back_t;

/**
  * @brief DMA channal configure structure
  */
typedef struct {
    void *src;                       /**< Source data begin pointer */
    void *dst;                       /**< Destination data begin pointer */
    uint16_t size;                   /**< The total number of DMA transfers that DMA cycle contains */
    ald_dma_data_size_t src_data_width;  /**< Source data width */
    ald_dma_data_size_t dst_data_width;  /**< Dest data width */
    ald_dma_data_inc_t src_inc;          /**< Source increment type */
    ald_dma_data_inc_t dst_inc;          /**< Destination increment type */
    ald_dma_arbiter_config_t R_power;    /**< Control how many DMA transfers can occur before re-arbitrates */
    ald_dma_priority_t priority;         /**< High priority or default priority */
    TypeFunc mem_to_mem;             /**< Enable/disable memory to memory mode */
    TypeFunc circle_mode;            /**< Enable/disable circular mode */
    ald_dma_msel_t msel;                 /**< Input source to DMA channel */
    ald_dma_msigsel_t msigsel;           /**< Input signal to DMA channel */
    uint8_t channel;                 /**< Channel index */
} ald_dma_config_t;

/** @defgroup ALD_DMA_Public_Constants DMA Public Constants
  * @{
  */
/**
  * brief ALD_DMA_CHANNEL DMA channel
  */
#define ALD_DMA_CH_0 0x0U   /**< Channel 0 */
#define ALD_DMA_CH_1 0x1U   /**< Channel 1 */
#define ALD_DMA_CH_2 0x2U   /**< Channel 2 */
#define ALD_DMA_CH_3 0x3U   /**< Channel 3 */
#define ALD_DMA_CH_4 0x4U   /**< Channel 4 */
#define ALD_DMA_CH_5 0x5U   /**< Channel 5 */
#define ALD_DMA_CH_6 0x6U   /**< Channel 6 */
/**
  * @}
  */

/**
  * @brief DMA handle structure definition
  */
typedef struct {
    DMA_TypeDef *perh;               /**< DMA registers base address */
    ald_dma_config_t config;             /**< Channel configure structure. @ref dma_config_t */
    void (*cplt_tc_cbk)(void *arg);  /**< DMA transfers complete callback */
    void (*cplt_ht_cbk)(void *arg);  /**< DMA transfers half complete callback */
    void *cplt_tc_arg;               /**< The parameter of cplt_tc_cbk() */
    void *cplt_ht_arg;               /**< The parameter of cplt_ht_cbk() */
} ald_dma_handle_t;

/**
  * @}
  */

/**
  * @defgroup DMA_Private_Macros DMA Private Macros
  * @{
  */
#define IS_DMA_MSEL_TYPE(x) ((x) <= ALD_DMA_MSEL_BS16T)
#define IS_DMA_MSIGSEL_TYPE(x)  ((x) <= ALD_DMA_MSIGSEL_EXTI_15)
#define IS_DMA_DATAINC_TYPE(x)  (((x) == ALD_DMA_DATA_INC_DISABLE)     || \
                                 ((x) == ALD_DMA_DATA_INC_ENABLE))
#define IS_DMA_DATASIZE_TYPE(x)  (((x) == ALD_DMA_DATA_SIZE_BYTE)     || \
                                  ((x) == ALD_DMA_DATA_SIZE_HALFWORD) || \
                                  ((x) == ALD_DMA_DATA_SIZE_WORD))
#define IS_DMA_ARBITERCONFIG_TYPE(x)  (((x) == ALD_DMA_R_POWER_1)   || \
                                       ((x) == ALD_DMA_R_POWER_2)   || \
                                       ((x) == ALD_DMA_R_POWER_4)   || \
                                       ((x) == ALD_DMA_R_POWER_8)   || \
                                       ((x) == ALD_DMA_R_POWER_16)  || \
                                       ((x) == ALD_DMA_R_POWER_32)  || \
                                       ((x) == ALD_DMA_R_POWER_64)  || \
                                       ((x) == ALD_DMA_R_POWER_128) || \
                                       ((x) == ALD_DMA_R_POWER_256) || \
                                       ((x) == ALD_DMA_R_POWER_512) || \
                                       ((x) == ALD_DMA_R_POWER_1024))
#define IS_DMA_PRIORITY_TYPE(x)  (((x) == ALD_DMA_LOW_PRIORITY)     || \
                                  ((x) == ALD_DMA_MEDIUM_PRIORITY) || \
                                  ((x) == ALD_DMA_HIGH_PRIORUTY) || \
                                  ((x) == ALD_DMA_HIGHEST_PRIORITY))
#define IS_DMA_IT_TYPE(x)  (((x) == ALD_DMA_IT_FLAG_TC)     || \
                                  ((x) == ALD_DMA_IT_FLAG_HT))
#define IS_DMA(x)       ((x) == DMA)
#define IS_DMA_CHANNEL(x)   ((x) <= ALD_DMA_CH_6)
#define IS_DMA_DATA_SIZE(x) ((x) <= 65535)
/**
  * @}
  */

/**
  * @addtogroup DMA_Public_Functions
  * @{
  */

/** @addtogroup DMA_Public_Functions_Group1
  * @{
  */
/* Initialization functions */
extern void ald_dma_config_base(ald_dma_config_t *config);
extern void ald_dma_config_basic(ald_dma_handle_t *hperh);
extern void ald_dma_config_basic_easy(void *src, void *dst, uint16_t size, ald_dma_msel_t msel,
        ald_dma_msigsel_t msigsel, uint8_t channel, void (*cbk)(void *arg));
extern void ald_dma_irq_handler(void);
extern void ald_dma_reset(void);
extern void ald_dma_init(void);
extern void ald_dma_config_struct(ald_dma_config_t *p);
/**
  * @}
  */


/** @addtogroup DMA_Public_Functions_Group2
  * @{
  */
/* DMA control functions */
extern void ald_dma_channel_config(uint8_t channel, type_func_t state);
void ald_dma_interrupt_config(uint8_t channel, ald_dma_it_flag_t it, type_func_t state);
extern it_status_t ald_dma_get_it_status(uint8_t channel, ald_dma_it_flag_t it);
extern flag_status_t ald_dma_get_flag_status(uint8_t channel, ald_dma_it_flag_t it);
extern void ald_dma_clear_flag_status(uint8_t channel, ald_dma_it_flag_t it);
/**
  * @}
  */

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*__ALD_DMA_H__ */
