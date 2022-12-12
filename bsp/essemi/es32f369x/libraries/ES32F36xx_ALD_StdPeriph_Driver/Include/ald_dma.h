/**
  *********************************************************************************
  *
  * @file    ald_dma.h
  * @brief   DMA module Library.
  *
  * @version V1.0
  * @date    09 Nov 2019
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          09 Nov 2019     AE Team         The first version
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
#endif

#include "utils.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup DMA
  * @{
  */

/**
  * @defgroup DMA_Public_Macros DMA Public Macros
  * @{
  */
#define DMA_CH_COUNT	12U
#define DMA_ERR		31U
/**
  * @}
  */

/**
  * @defgroup DMA_Public_Types DMA Public Types
  * @{
  */

/**
  * @brief Input source to DMA channel
  * @verbatim
      In this module, for the convenience of code maintenance,
      TIMERx is used to indicate the sequence of the timer peripheral.
      Different product series TIMERx represent different meanings:
      1. For ES32F36xx series:
      TIMER0 ----> AD16C4T0
      TIMER1 ----> AD16C4T1
      TIMER2 ----> GP32C4T0
      TIMER3 ----> GP32C4T1
      TIMER4 ----> BS16T0
      TIMER5 ----> BS16T1
      TIMER6 ----> GP16C4T0
      TIMER7 ----> GP16C4T1

      2. For ES32F393x/ES32F336x/ES32F392x series:
      TIMER0 ----> GP16C4T0
      TIMER1 ----> GP16C4T1
      TIMER2 ----> GP32C4T0
      TIMER3 ----> GP32C4T1
      TIMER4 ----> BS16T0
      TIMER5 ----> BS16T1
      TIMER6 ----> GP16C4T2
      TIMER7 ----> GP16C4T3
    @endverbatim
  */
typedef enum {
	DMA_MSEL_NONE    = 0x0U,	/**< NONE */
	DMA_MSEL_GPIO    = 0x1U,	/**< GPIO */
	DMA_MSEL_CRYPT   = 0x2U,	/**< CRYPT */
	DMA_MSEL_DAC0    = 0x4U,	/**< DAC0 */
	DMA_MSEL_ADC0    = 0x6U,	/**< ADC0 */
	DMA_MSEL_CRC     = 0x7U,	/**< CRC */
	DMA_MSEL_UART0   = 0x8U,	/**< UART0 */
	DMA_MSEL_UART1   = 0x9U,	/**< UART1 */
	DMA_MSEL_UART2   = 0xAU,	/**< UART2 */
	DMA_MSEL_UART3   = 0xBU,	/**< UART3 */
	DMA_MSEL_UART4   = 0xCU,	/**< UART4 */
	DMA_MSEL_UART5   = 0xDU,	/**< UART5 */
	DMA_MSEL_SPI0    = 0xEU,	/**< SPI0 */
	DMA_MSEL_SPI1    = 0xFU,	/**< SPI1 */
	DMA_MSEL_I2C0    = 0x10U,	/**< I2C0 */
	DMA_MSEL_I2C1    = 0x11U,	/**< I2C1 */
	DMA_MSEL_TIMER0  = 0x12U,	/**< TIMER0 */
	DMA_MSEL_TIMER1  = 0x13U,	/**< TIMER1 */
	DMA_MSEL_TIMER2  = 0x14U,	/**< TIMER2 */
	DMA_MSEL_TIMER3  = 0x15U,	/**< TIMER3 */
	DMA_MSEL_LPUART0 = 0x18U,	/**< LPUART0 */
	DMA_MSEL_SPI2    = 0x1AU,	/**< SPI2 */
	DMA_MSEL_TIMER4  = 0x1BU,	/**< TIMER4 */
	DMA_MSEL_TIMER5  = 0x1CU,	/**< TIMER5 */
	DMA_MSEL_TIMER6  = 0x1DU,	/**< TIMER6 */
	DMA_MSEL_TIMER7  = 0x1EU,	/**< TIMER7 */
	DMA_MSEL_ADC1    = 0x1FU,	/**< ADC1 */
	DMA_MSEL_PIS     = 0x20U,	/**< PIS */
	DMA_MSEL_TRNG    = 0x21U,	/**< TRNG */
	DMA_MSEL_QSPI    = 0x22U,	/**< QSPI */
	DMA_MSEL_USB     = 0x23U,	/**< USB */
} dma_msel_t;

/**
  * @brief Input signal to DMA channel
  */
typedef enum {
	DMA_MSIGSEL_NONE           = 0x0U,	/**< NONE */
	DMA_MSIGSEL_EXTI_0         = 0x0U,	/**< External interrupt 0 */
	DMA_MSIGSEL_EXTI_1         = 0x1U,	/**< External interrupt 1 */
	DMA_MSIGSEL_EXTI_2         = 0x2U,	/**< External interrupt 2 */
	DMA_MSIGSEL_EXTI_3         = 0x3U,	/**< External interrupt 3 */
	DMA_MSIGSEL_EXTI_4         = 0x4U,	/**< External interrupt 4 */
	DMA_MSIGSEL_EXTI_5         = 0x5U,	/**< External interrupt 5 */
	DMA_MSIGSEL_EXTI_6         = 0x6U,	/**< External interrupt 6 */
	DMA_MSIGSEL_EXTI_7         = 0x7U,	/**< External interrupt 7 */
	DMA_MSIGSEL_EXTI_8         = 0x8U,	/**< External interrupt 8 */
	DMA_MSIGSEL_EXTI_9         = 0x9U,	/**< External interrupt 9 */
	DMA_MSIGSEL_EXTI_10        = 0xAU,	/**< External interrupt 10 */
	DMA_MSIGSEL_EXTI_11        = 0xBU,	/**< External interrupt 11 */
	DMA_MSIGSEL_EXTI_12        = 0xCU,	/**< External interrupt 12 */
	DMA_MSIGSEL_EXTI_13        = 0xDU,	/**< External interrupt 13 */
	DMA_MSIGSEL_EXTI_14        = 0xEU,	/**< External interrupt 14 */
	DMA_MSIGSEL_EXTI_15        = 0xFU,	/**< External interrupt 15 */
	DMA_MSIGSEL_CRYPT_WRITE    = 0x0U,	/**< CRYPT write mode */
	DMA_MSIGSEL_CRYPT_READ     = 0x1U,	/**< CRYPT read mode */
	DMA_MSIGSEL_DAC0_CH0       = 0x0U,	/**< DAC0 channel 0 complete */
	DMA_MSIGSEL_DAC0_CH1       = 0x1U,	/**< DAC0 channel 1 complete */
	DMA_MSIGSEL_ADC       	   = 0x0U,	/**< ADC mode */
	DMA_MSIGSEL_UART_TXEMPTY   = 0x0U,	/**< UART0/UART1/UART2/UART3 transmit */
	DMA_MSIGSEL_UART_RNR       = 0x1U,	/**< UART0/UART1/UART2/UART3 receive */
	DMA_MSIGSEL_UART45_RNR     = 0x0U,	/**< UART4/UART5 reveive */
	DMA_MSIGSEL_UART45_TXEMPTY = 0x1U,	/**< UART4/UART5 transmit */
	DMA_MSIGSEL_SPI_RNR        = 0x0U,	/**< SPI receive */
	DMA_MSIGSEL_SPI_TXEMPTY    = 0x1U,	/**< SPI transmit */
	DMA_MSIGSEL_I2C_RNR        = 0x0U,	/**< I2C receive */
	DMA_MSIGSEL_I2C_TXEMPTY    = 0x1U,	/**< I2C transmit */
	DMA_MSIGSEL_TIMER_CH1      = 0x0U,	/**< TIM channal 1 */
	DMA_MSIGSEL_TIMER_CH2      = 0x1U,	/**< TIM channal 2 */
	DMA_MSIGSEL_TIMER_CH3      = 0x2U,	/**< TIM channal 3 */
	DMA_MSIGSEL_TIMER_CH4      = 0x3U,	/**< TIM channal 4 */
	DMA_MSIGSEL_TIMER_TRI      = 0x4U,	/**< TIM trigger */
	DMA_MSIGSEL_TIMER_COMP     = 0x5U,	/**< TIM compare */
	DMA_MSIGSEL_TIMER_UPDATE   = 0x6U,	/**< TIM update */
	DMA_MSIGSEL_LPUART_RNR     = 0x0U,	/**< LPUART receive */
	DMA_MSIGSEL_LPUART_TXEMPTY = 0x1U,	/**< LPUART transmit */
	DMA_MSIGSEL_PIS_CH0        = 0x0U,	/**< PIS channal 0 */
	DMA_MSIGSEL_PIS_CH1        = 0x1U,	/**< PIS channal 1 */
	DMA_MSIGSEL_PIS_CH2        = 0x2U,	/**< PIS channal 2 */
	DMA_MSIGSEL_PIS_CH3        = 0x3U,	/**< PIS channal 3 */
	DMA_MSIGSEL_PIS_CH4        = 0x4U,	/**< PIS channal 4 */
	DMA_MSIGSEL_PIS_CH5        = 0x5U,	/**< PIS channal 5 */
	DMA_MSIGSEL_PIS_CH6        = 0x6U,	/**< PIS channal 6 */
	DMA_MSIGSEL_PIS_CH7        = 0x7U,	/**< PIS channal 7 */
	DMA_MSIGSEL_PIS_CH8        = 0x8U,	/**< PIS channal 8 */
	DMA_MSIGSEL_PIS_CH9        = 0x9U,	/**< PIS channal 9 */
	DMA_MSIGSEL_PIS_CH10       = 0xAU,	/**< PIS channal 10 */
	DMA_MSIGSEL_PIS_CH11       = 0xBU,	/**< PIS channal 11 */
	DMA_MSIGSEL_PIS_CH12       = 0xCU,	/**< PIS channal 12 */
	DMA_MSIGSEL_PIS_CH13       = 0xDU,	/**< PIS channal 13 */
	DMA_MSIGSEL_PIS_CH14       = 0xEU,	/**< PIS channal 14 */
	DMA_MSIGSEL_PIS_CH15       = 0xFU,	/**< PIS channal 15 */
	DMA_MSIGSEL_QSPI_WRITE     = 0x0U,	/**< QSPI Write */
	DMA_MSIGSEL_QSPI_READ      = 0x1U,	/**< QSPI Read */
	DMA_MSIGSEL_EP_TX1         = 0x0U,	/**< USB TX Endport 0 */
	DMA_MSIGSEL_EP_TX2         = 0x1U,	/**< USB TX Endport 1 */
	DMA_MSIGSEL_EP_TX3         = 0x2U,	/**< USB TX Endport 2 */
	DMA_MSIGSEL_EP_TX4         = 0x3U,	/**< USB TX Endport 3 */
	DMA_MSIGSEL_EP_TX5         = 0x4U,	/**< USB TX Endport 4 */
	DMA_MSIGSEL_EP_RX1         = 0x8U,	/**< USB RX Endport 0 */
	DMA_MSIGSEL_EP_RX2         = 0x9U,	/**< USB RX Endport 1 */
	DMA_MSIGSEL_EP_RX3         = 0xAU,	/**< USB RX Endport 2 */
	DMA_MSIGSEL_EP_RX4         = 0xBU,	/**< USB RX Endport 3 */
	DMA_MSIGSEL_EP_RX5         = 0xCU,	/**< USB RX Endport 4 */	
} dma_msigsel_t;

/**
  * @brief DMA Descriptor control type
  */
typedef union {
	struct {
		uint32_t cycle_ctrl    :3;	/**< DMA operating mode @ref dma_cycle_ctrl_t */
		uint32_t next_useburst :1;	/**< Uses the alternate data structure when complete a DMA cycle */
		uint32_t n_minus_1     :10;	/**< Represent the total number of DMA transfers that DMA cycle contains. */
		uint32_t R_power       :4;	/**< Control how many DMA transfers can occur before re-arbitrates. @ref dma_arbiter_config_t */
		uint32_t src_prot_ctrl :3;	/**< Control the state of HPROT when reads the source data. */
		uint32_t dst_prot_ctrl :3;	/**< Control the state of HPROT when writes the destination data */
		uint32_t src_size      :2;	/**< Source data size @ref dma_data_size_t */
		uint32_t src_inc       :2;	/**< Control the source address increment. @ref dma_data_inc_t */
		uint32_t dst_size      :2;	/**< Destination data size. @ref dma_data_size_t */
		uint32_t dst_inc       :2;	/**< Destination address increment. @ref dma_data_inc_t */
	};
	uint32_t word;
} dma_ctrl_t;

/**
  * @brief Channel control data structure
  */
typedef struct {
	void *src;		/**< Source data end pointer */
	void *dst;		/**< Destination data end pointer */
	dma_ctrl_t ctrl;	/**< Control data configuration @ref dma_ctrl_t */
	uint32_t use;		/**< Reserve for user */
} dma_descriptor_t;

/**
  * @brief data increment
  */
typedef enum {
	DMA_DATA_INC_BYTE     = 0x0U,	/**< Address increment by byte */
	DMA_DATA_INC_HALFWORD = 0x1U,	/**< Address increment by halfword */
	DMA_DATA_INC_WORD     = 0x2U,	/**< Address increment by word */
	DMA_DATA_INC_NONE     = 0x3U,	/**< No increment */
} dma_data_inc_t;

/**
  * @brief Data size
  */
typedef enum {
	DMA_DATA_SIZE_BYTE     = 0x0U,	/**< Byte */
	DMA_DATA_SIZE_HALFWORD = 0x1U,	/**< Halfword */
	DMA_DATA_SIZE_WORD     = 0x2U,	/**< Word */
} dma_data_size_t;

/**
  * @brief The operating mode of the DMA cycle
  */
typedef enum {
	DMA_CYCLE_CTRL_NONE             = 0x0U,	/**< Stop */
	DMA_CYCLE_CTRL_BASIC            = 0x1U,	/**< Basic */
	DMA_CYCLE_CTRL_AUTO             = 0x2U,	/**< Auto-request */
	DMA_CYCLE_CTRL_PINGPONG         = 0x3U,	/**< Ping-pong */
	DMA_CYCLE_CTRL_MEM_SG_PRIMARY   = 0x4U,	/**< Memory scatter-gather using the primary structure */
	DMA_CYCLE_CTRL_MEM_SG_ALTERNATE = 0x5U,	/**< Memory scatter-gather using the alternate structure */
	DMA_CYCLE_CTRL_PER_SG_PRIMARY   = 0x6U,	/**< Peripheral scatter-gather using the primary structure */
	DMA_CYCLE_CTRL_PER_SG_ALTERNATE = 0x7U,	/**< Peripheral scatter-gather using the alternate structure */
} dma_cycle_ctrl_t;

/**
  * @brief Control how many DMA transfers can occur
  *        before the controller re-arbitrates
  */
typedef enum {
	DMA_R_POWER_1    = 0x0U,	/**< Arbitrates after each DMA transfer */
	DMA_R_POWER_2    = 0x1U,	/**< Arbitrates after 2 DMA transfer */
	DMA_R_POWER_4    = 0x2U,	/**< Arbitrates after 4 DMA transfer */
	DMA_R_POWER_8    = 0x3U,	/**< Arbitrates after 8 DMA transfer */
	DMA_R_POWER_16   = 0x4U,	/**< Arbitrates after 16 DMA transfer */
	DMA_R_POWER_32   = 0x5U,	/**< Arbitrates after 32 DMA transfer */
	DMA_R_POWER_64   = 0x6U,	/**< Arbitrates after 64 DMA transfer */
	DMA_R_POWER_128  = 0x7U,	/**< Arbitrates after 128 DMA transfer */
	DMA_R_POWER_256  = 0x8U,	/**< Arbitrates after 256 DMA transfer */
	DMA_R_POWER_512  = 0x9U,	/**< Arbitrates after 512 DMA transfer */
	DMA_R_POWER_1024 = 0xAU,	/**< Arbitrates after 1024 DMA transfer */
} dma_arbiter_config_t;

/**
  * @brief Callback function pointer and param
  */
typedef struct {
	void (*cplt_cbk)(void *arg);	/**< DMA transfers complete callback */
	void (*err_cbk)(void* arg);	/**< DMA occurs error callback */
	void *cplt_arg;			/**< The parameter of cplt_cbk() */
	void *err_arg;			/**< The parameter of err_cbk() */
} dma_call_back_t;

/**
  * @brief DMA channal configure structure
  */
typedef struct {
	void *src;			/**< Source data begin pointer */
	void *dst;			/**< Destination data begin pointer */
	uint16_t size;			/**< The total number of DMA transfers that DMA cycle contains */
	dma_data_size_t data_width;	/**< Data width, @ref dma_data_size_t */
	dma_data_inc_t src_inc;		/**< Source increment type. @ref dma_data_inc_t */
	dma_data_inc_t dst_inc;		/**< Destination increment type. @ref dma_data_inc_t */
	dma_arbiter_config_t R_power;	/**< Control how many DMA transfers can occur before re-arbitrates. @ref dma_arbiter_config_t */
	type_func_t primary;		/**< Use primary descriptor or alternate descriptor */
	type_func_t burst;		/**< Enable/Disable the useburst setting for this channel */
	type_func_t high_prio;		/**< High priority or default priority */
	type_func_t interrupt;		/**< Enable/disable interrupt */
	dma_msel_t msel;		/**< Input source to DMA channel @ref dma_msel_t */
	dma_msigsel_t msigsel;		/**< Input signal to DMA channel @ref dma_msigsel_t */
	uint8_t channel;		/**< Channel index */
} dma_config_t;

/**
  * @brief DMA handle structure definition
  */
typedef struct {
	DMA_TypeDef *perh;		/**< DMA registers base address */
	dma_config_t config;		/**< Channel configure structure. @ref dma_config_t */
	void (*cplt_cbk)(void *arg);	/**< DMA transfers complete callback */
	void (*err_cbk)(void *arg);	/**< DMA bus occurs error callback */
	void *cplt_arg;			/**< The parameter of cplt_cbk() */
	void *err_arg;			/**< The parameter of err_cbk() */
} dma_handle_t;

/**
  * @brief Descriptor complete state
  */
typedef enum {
	DMA_DESCP_CPLT_PRI = 0x0U,	/**< Primary descriptor has been completed */
	DMA_DESCP_CPLT_ALT = 0x1U,	/**< Alternate descriptor has been completed */
	DMA_DESCP_CPLT_ALL = 0x2U,	/**< Both primary and alternate descriptors have been completed */
} dma_descrp_cplt_t;
/**
  * @}
  */

/**
  * @defgroup DMA_Private_Macros DMA Private Macros
  * @{
  */
#define IS_DMA_MSEL_TYPE(x)	((x) <= DMA_MSEL_USB)
#define IS_DMA_MSIGSEL_TYPE(x)	((x) <= 0xF)
#define IS_DMA_DATAINC_TYPE(x)  (((x) == DMA_DATA_INC_BYTE)     || \
                                 ((x) == DMA_DATA_INC_HALFWORD) || \
                                 ((x) == DMA_DATA_INC_WORD)     || \
                                 ((x) == DMA_DATA_INC_NONE))
#define IS_DMA_DATASIZE_TYPE(x)  (((x) == DMA_DATA_SIZE_BYTE)     || \
                                  ((x) == DMA_DATA_SIZE_HALFWORD) || \
                                  ((x) == DMA_DATA_SIZE_WORD))
#define IS_CYCLECTRL_TYPE(x)  (((x) == DMA_CYCLE_CTRL_NONE)             || \
                               ((x) == DMA_CYCLE_CTRL_BASIC)            || \
                               ((x) == DMA_CYCLE_CTRL_AUTO)             || \
                               ((x) == DMA_CYCLE_CTRL_PINGPONG)         || \
                               ((x) == DMA_CYCLE_CTRL_MEM_SG_PRIMARY)   || \
                               ((x) == DMA_CYCLE_CTRL_MEM_SG_ALTERNATE) || \
                               ((x) == DMA_CYCLE_CTRL_PER_SG_PRIMARY)   || \
                               ((x) == DMA_CYCLE_CTRL_PER_SG_ALTERNATE))
#define IS_DMA_ARBITERCONFIG_TYPE(x)  (((x) == DMA_R_POWER_1)   || \
                                       ((x) == DMA_R_POWER_2)   || \
                                       ((x) == DMA_R_POWER_4)   || \
                                       ((x) == DMA_R_POWER_8)   || \
                                       ((x) == DMA_R_POWER_16)  || \
                                       ((x) == DMA_R_POWER_32)  || \
                                       ((x) == DMA_R_POWER_64)  || \
                                       ((x) == DMA_R_POWER_128) || \
                                       ((x) == DMA_R_POWER_256) || \
                                       ((x) == DMA_R_POWER_512) || \
                                       ((x) == DMA_R_POWER_1024))
#define IS_DMA(x)		((x) == DMA0)
#define IS_DMA_CHANNEL(x)	((x) <= 11)
#define IS_DMA_DATA_SIZE(x)	((x) <= 1024)
#define IS_DMA_IT_TYPE(x)	(((x) <= 11) || ((x) == 31))
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
extern void ald_dma_reset(DMA_TypeDef *DMAx);
extern void ald_dma_init(DMA_TypeDef *DMAx);
extern void ald_dma_config_struct(dma_config_t *p);
extern void ald_dma_config_sg_alt_desc(dma_descriptor_t *desc, dma_config_t *config, uint8_t memory);
/**
  * @}
  */


/** @addtogroup DMA_Public_Functions_Group2
  * @{
  */
/* Configure DMA channel functions */
extern void ald_dma_config_auto(dma_handle_t *hperh);
extern void ald_dma_restart_auto(dma_handle_t *hperh, void *src, void *dst, uint16_t size);
extern void ald_dma_config_auto_easy(DMA_TypeDef *DMAx, void *src, void *dst,
                                        uint16_t size, uint8_t channel, void (*cbk)(void *arg));
extern void ald_dma_config_basic(dma_handle_t *hperh);
extern void ald_dma_restart_basic(dma_handle_t *hperh, void *src, void *dst, uint16_t size);
extern void ald_dma_config_basic_easy(DMA_TypeDef *DMAx, void *src, void *dst, uint16_t size, dma_msel_t msel,
                                 dma_msigsel_t msigsel, uint8_t channel, void (*cbk)(void *arg));
extern void ald_dma_config_ping_pong(DMA_TypeDef *DMAx, dma_config_t *config,
                                       uint8_t first, void (*cbk)(void *arg));
extern void ald_dma_config_sg_mem(DMA_TypeDef *DMAx, dma_descriptor_t *desc,
                                       uint32_t nr, uint8_t channel, void (*cbk)(void *arg));
extern void ald_dma_config_sg_per(DMA_TypeDef *DMAx, dma_descriptor_t *desc, uint32_t nr, uint8_t burst,
                    dma_msel_t msel, dma_msigsel_t msigsel, uint8_t channel, void (*cbk)(void *arg));
/**
  * @}
  */

/** @addtogroup DMA_Public_Functions_Group3
  * @{
  */
/* DMA control functions */
extern void ald_dma_channel_config(DMA_TypeDef *DMAx, uint8_t channel, type_func_t state);
extern void ald_dma_interrupt_config(DMA_TypeDef *DMAx, uint8_t channel, type_func_t state);
extern it_status_t ald_dma_get_it_status(DMA_TypeDef *DMAx, uint8_t channel);
extern flag_status_t ald_dma_get_flag_status(DMA_TypeDef *DMAx, uint8_t channel);
extern void ald_dma_clear_flag_status(DMA_TypeDef *DMAx, uint8_t channel);
extern dma_descrp_cplt_t ald_dma_descriptor_cplt_get(DMA_TypeDef *DMAx, uint8_t channel);
extern void ald_dma_irq_handler(void);
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
#endif

#endif	/*__ALD_DMA_H__ */
