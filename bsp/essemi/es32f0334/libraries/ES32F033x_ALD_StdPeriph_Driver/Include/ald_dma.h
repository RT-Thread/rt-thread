/**
  *********************************************************************************
  *
  * @file    ald_dma.h
  * @brief   DMA module Library.
  *
  * @version V1.0
  * @date    09 Nov 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
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
#define DMA_CH_COUNT	6
#define DMA_ERR		31
/**
  * @}
  */

/**
  * @defgroup DMA_Public_Types DMA Public Types
  * @{
  */

/**
  * @brief Input source to DMA channel
  * @note  ES32F065x:
  *          AD16C4T0--TIMER0
  *          GP16C4T0--TIMER6
  *          GP16C2T0--TIMER2
  *          GP16C2T1--TIMER3
  *          BS16T0----TIMER1
  *          BS16T1----TIMER4
  *          BS16T2----TIMER5
  *          BS16T3----TIMER7
  *
  *        ES32F033x:
  *        ES32F093x:
  *          GP16C4T0--TIMER0
  *          GP16C4T1--TIMER6
  *          GP16C2T0--TIMER2
  *          GP16C2T1--TIMER3
  *          BS16T0----TIMER1
  *          BS16T1----TIMER4
  *          BS16T2----TIMER5
  *          BS16T3----TIMER7
  */
typedef enum
{
    DMA_MSEL_NONE    = 0x0,		/**< NONE */
    DMA_MSEL_GPIO    = 0x1,		/**< GPIO */
    DMA_MSEL_CRYPT   = 0x2,		/**< CRYPT */
    DMA_MSEL_ACMP    = 0x3,		/**< ACMP */
    DMA_MSEL_DAC0    = 0x4,		/**< DAC0 */
    DMA_MSEL_ADC0    = 0x6,		/**< ADC0 */
    DMA_MSEL_CRC     = 0x7,		/**< CRC */
    DMA_MSEL_UART0   = 0x8,		/**< UART0 */
    DMA_MSEL_UART1   = 0x9,		/**< UART1 */
    DMA_MSEL_UART2   = 0xA,		/**< UART2 */
    DMA_MSEL_UART3   = 0xB,		/**< UART3 */
    DMA_MSEL_USART0  = 0xC,		/**< USART0 */
    DMA_MSEL_USART1  = 0xD,		/**< USART1 */
    DMA_MSEL_SPI0    = 0xE,		/**< SPI0 */
    DMA_MSEL_SPI1    = 0xF,		/**< SPI1 */
    DMA_MSEL_I2C0    = 0x10,	/**< I2C0 */
    DMA_MSEL_I2C1    = 0x11,	/**< I2C1 */
    DMA_MSEL_TIMER0  = 0x12,	/**< TIMER0 */
    DMA_MSEL_TIMER1  = 0x13,	/**< TIMER1 */
    DMA_MSEL_TIMER2  = 0x14,	/**< TIMER2 */
    DMA_MSEL_TIMER3  = 0x15,	/**< TIMER3 */
    DMA_MSEL_RTC     = 0x16,	/**< RTC */
    DMA_MSEL_LPTIM0  = 0x17,	/**< LPTIM0 */
    DMA_MSEL_LPUART0 = 0x18,	/**< LPUART0 */
    DMA_MSEL_DMA     = 0x19,	/**< DMA */
    DMA_MSEL_SPI2    = 0x1A,	/**< SPI2 */
    DMA_MSEL_TIMER4  = 0x1B,	/**< TIMER4 */
    DMA_MSEL_TIMER5  = 0x1C,	/**< TIMER5 */
    DMA_MSEL_TIMER6  = 0x1D,	/**< TIMER6 */
    DMA_MSEL_TIMER7  = 0x1E,	/**< TIMER7 */
    DMA_MSEL_ADC1    = 0x1F,	/**< ADC1 */
    DMA_MSEL_PIS     = 0x20,	/**< PIS */
    DMA_MSEL_TRNG    = 0x21,	/**< TRNG */
} dma_msel_t;

/**
  * @brief Input signal to DMA channel
  */
typedef enum
{
    DMA_MSIGSEL_NONE           = 0x0,	/**< NONE */
    DMA_MSIGSEL_EXTI_0         = 0x0,	/**< External interrupt 0 */
    DMA_MSIGSEL_EXTI_1         = 0x1,	/**< External interrupt 1 */
    DMA_MSIGSEL_EXTI_2         = 0x2,	/**< External interrupt 2 */
    DMA_MSIGSEL_EXTI_3         = 0x3,	/**< External interrupt 3 */
    DMA_MSIGSEL_EXTI_4         = 0x4,	/**< External interrupt 4 */
    DMA_MSIGSEL_EXTI_5         = 0x5,	/**< External interrupt 5 */
    DMA_MSIGSEL_EXTI_6         = 0x6,	/**< External interrupt 6 */
    DMA_MSIGSEL_EXTI_7         = 0x7,	/**< External interrupt 7 */
    DMA_MSIGSEL_EXTI_8         = 0x8,	/**< External interrupt 8 */
    DMA_MSIGSEL_EXTI_9         = 0x9,	/**< External interrupt 9 */
    DMA_MSIGSEL_EXTI_10        = 0xA,	/**< External interrupt 10 */
    DMA_MSIGSEL_EXTI_11        = 0xB,	/**< External interrupt 11 */
    DMA_MSIGSEL_EXTI_12        = 0xC,	/**< External interrupt 12 */
    DMA_MSIGSEL_EXTI_13        = 0xD,	/**< External interrupt 13 */
    DMA_MSIGSEL_EXTI_14        = 0xE,	/**< External interrupt 14 */
    DMA_MSIGSEL_EXTI_15        = 0xF,	/**< External interrupt 15 */
    DMA_MSIGSEL_CRYPT_WRITE    = 0x0,	/**< CRYPT write mode */
    DMA_MSIGSEL_CRYPT_READ     = 0x1,	/**< CRYPT read mode */
    DMA_MSIGSEL_CALC_WRITE     = 0x0,	/**< CALC write mode */
    DMA_MSIGSEL_CALC_READ      = 0x1,	/**< CALC read mode */
    DMA_MSIGSEL_DAC0_CH0       = 0x0,	/**< DAC0 channel 0 complete */
    DMA_MSIGSEL_DAC0_CH1       = 0x1,	/**< DAC0 channel 1 complete */
    DMA_MSIGSEL_ADC       	   = 0x0,	/**< ADC mode */
    DMA_MSIGSEL_UART_TXEMPTY   = 0x0,	/**< UART transmit */
    DMA_MSIGSEL_UART_RNR       = 0x1,	/**< UART receive */
    DMA_MSIGSEL_USART_RNR      = 0x0,	/**< USART reveive */
    DMA_MSIGSEL_USART_TXEMPTY  = 0x1,	/**< USART transmit */
    DMA_MSIGSEL_SPI_RNR        = 0x0,	/**< SPI receive */
    DMA_MSIGSEL_SPI_TXEMPTY    = 0x1,	/**< SPI transmit */
    DMA_MSIGSEL_I2C_RNR        = 0x0,	/**< I2C receive */
    DMA_MSIGSEL_I2C_TXEMPTY    = 0x1,	/**< I2C transmit */
    DMA_MSIGSEL_TIMER_CH1      = 0x0,	/**< TIM channal 1 */
    DMA_MSIGSEL_TIMER_CH2      = 0x1,	/**< TIM channal 2 */
    DMA_MSIGSEL_TIMER_CH3      = 0x2,	/**< TIM channal 3 */
    DMA_MSIGSEL_TIMER_CH4      = 0x3,	/**< TIM channal 4 */
    DMA_MSIGSEL_TIMER_TRI      = 0x4,	/**< TIM trigger */
    DMA_MSIGSEL_TIMER_COMP     = 0x5,	/**< TIM compare */
    DMA_MSIGSEL_TIMER_UPDATE   = 0x6,	/**< TIM update */
    DMA_MSIGSEL_LPUART_RNR     = 0x0,	/**< LPUART receive */
    DMA_MSIGSEL_LPUART_TXEMPTY = 0x1,	/**< LPUART transmit */
    DMA_MSIGSEL_PIS_CH0        = 0x0,	/**< PIS channal 0 */
    DMA_MSIGSEL_PIS_CH1        = 0x1,	/**< PIS channal 1 */
    DMA_MSIGSEL_PIS_CH2        = 0x2,	/**< PIS channal 2 */
    DMA_MSIGSEL_PIS_CH3        = 0x3,	/**< PIS channal 3 */
    DMA_MSIGSEL_PIS_CH4        = 0x4,	/**< PIS channal 4 */
    DMA_MSIGSEL_PIS_CH5        = 0x5,	/**< PIS channal 5 */
    DMA_MSIGSEL_PIS_CH6        = 0x6,	/**< PIS channal 6 */
    DMA_MSIGSEL_PIS_CH7        = 0x7,	/**< PIS channal 7 */
    DMA_MSIGSEL_PIS_CH8        = 0x8,	/**< PIS channal 8 */
    DMA_MSIGSEL_PIS_CH9        = 0x9,	/**< PIS channal 9 */
    DMA_MSIGSEL_PIS_CH10       = 0xA,	/**< PIS channal 10 */
    DMA_MSIGSEL_PIS_CH11       = 0xB,	/**< PIS channal 11 */
    DMA_MSIGSEL_PIS_CH12       = 0xC,	/**< PIS channal 12 */
    DMA_MSIGSEL_PIS_CH13       = 0xD,	/**< PIS channal 13 */
    DMA_MSIGSEL_PIS_CH14       = 0xE,	/**< PIS channal 14 */
    DMA_MSIGSEL_PIS_CH15       = 0xF,	/**< PIS channal 15 */
} dma_msigsel_t;

/**
  * @brief DMA Descriptor control type
  */
typedef union
{
    struct
    {
        uint32_t cycle_ctrl    : 3;	/**< DMA operating mode @ref dma_cycle_ctrl_t */
        uint32_t next_useburst : 1;	/**< Uses the alternate data structure when complete a DMA cycle */
        uint32_t n_minus_1     : 10;	/**< Represent the total number of DMA transfers that DMA cycle contains. */
        uint32_t R_power       : 4;	/**< Control how many DMA transfers can occur before re-arbitrates. @ref dma_arbiter_config_t */
        uint32_t src_prot_ctrl : 3;	/**< Control the state of HPROT when reads the source data. */
        uint32_t dst_prot_ctrl : 3;	/**< Control the state of HPROT when writes the destination data */
        uint32_t src_size      : 2;	/**< Source data size @ref dma_data_size_t */
        uint32_t src_inc       : 2;	/**< Control the source address increment. @ref dma_data_inc_t */
        uint32_t dst_size      : 2;	/**< Destination data size. @ref dma_data_size_t */
        uint32_t dst_inc       : 2;	/**< Destination address increment. @ref dma_data_inc_t */
    };
    uint32_t word;
} dma_ctrl_t;

/**
  * @brief Channel control data structure
  */
typedef struct
{
    void *src;		/**< Source data end pointer */
    void *dst;		/**< Destination data end pointer */
    dma_ctrl_t ctrl;	/**< Control data configuration @ref dma_ctrl_t */
    uint32_t use;		/**< Reserve for user */
} dma_descriptor_t;

/**
  * @brief data increment
  */
typedef enum
{
    DMA_DATA_INC_BYTE     = 0x0,	/**< Address increment by byte */
    DMA_DATA_INC_HALFWORD = 0x1,	/**< Address increment by halfword */
    DMA_DATA_INC_WORD     = 0x2,	/**< Address increment by word */
    DMA_DATA_INC_NONE     = 0x3,	/**< No increment */
} dma_data_inc_t;

/**
  * @brief Data size
  */
typedef enum
{
    DMA_DATA_SIZE_BYTE     = 0x0,	/**< Byte */
    DMA_DATA_SIZE_HALFWORD = 0x1,	/**< Halfword */
    DMA_DATA_SIZE_WORD     = 0x2,	/**< Word */
} dma_data_size_t;

/**
  * @brief The operating mode of the DMA cycle
  */
typedef enum
{
    DMA_CYCLE_CTRL_NONE               = 0x0,	/**< Stop */
    DMA_CYCLE_CTRL_BASIC              = 0x1,	/**< Basic */
    DMA_CYCLE_CTRL_AUTO               = 0x2,	/**< Auto-request */
    DMA_CYCLE_CTRL_PINGPONG           = 0x3,	/**< Ping-pong */
    DMA_CYCLE_CTRL_MEM_SCATTER_GATHER = 0x4,	/**< Memory scatter/gather */
    DMA_CYCLE_CTRL_PER_SCATTER_GATHER = 0x6,	/**< Peripheral scatter/gather */
} dma_cycle_ctrl_t;

/**
  * @brief Control how many DMA transfers can occur
  *        before the controller re-arbitrates
  */
typedef enum
{
    DMA_R_POWER_1    = 0x0,		/**< Arbitrates after each DMA transfer */
    DMA_R_POWER_2    = 0x1,		/**< Arbitrates after 2 DMA transfer */
    DMA_R_POWER_4    = 0x2,		/**< Arbitrates after 4 DMA transfer */
    DMA_R_POWER_8    = 0x3,		/**< Arbitrates after 8 DMA transfer */
    DMA_R_POWER_16   = 0x4,		/**< Arbitrates after 16 DMA transfer */
    DMA_R_POWER_32   = 0x5,		/**< Arbitrates after 32 DMA transfer */
    DMA_R_POWER_64   = 0x6,		/**< Arbitrates after 64 DMA transfer */
    DMA_R_POWER_128  = 0x7,		/**< Arbitrates after 128 DMA transfer */
    DMA_R_POWER_256  = 0x8,		/**< Arbitrates after 256 DMA transfer */
    DMA_R_POWER_512  = 0x9,		/**< Arbitrates after 512 DMA transfer */
    DMA_R_POWER_1024 = 0xA,		/**< Arbitrates after 1024 DMA transfer */
} dma_arbiter_config_t;

/**
  * @brief Callback function pointer and param
  */
typedef struct
{
    void (*cplt_cbk)(void *arg);	/**< DMA transfers complete callback */
    void (*err_cbk)(void *arg);	/**< DMA occurs error callback */
    void *cplt_arg;			/**< The parameter of cplt_cbk() */
    void *err_arg;			/**< The parameter of err_cbk() */
} dma_call_back_t;

/**
  * @brief DMA channal configure structure
  */
typedef struct
{
    void *src;			/**< Source data begin pointer */
    void *dst;			/**< Destination data begin pointer */
    uint16_t size;			/**< The total number of DMA transfers that DMA cycle contains */
    dma_data_size_t data_width;	/**< Data width, @ref dma_data_size_t */
    dma_data_inc_t src_inc;		/**< Source increment type. @ref dma_data_inc_t */
    dma_data_inc_t dst_inc;		/**< Destination increment type. @ref dma_data_inc_t */
    dma_arbiter_config_t R_power;	/**< Control how many DMA transfers can occur before re-arbitrates. @ref dma_arbiter_config_t */
    type_func_t primary;		/**< Use primary descriptor or alternate descriptor */
    type_func_t burst;		/**< Uses the alternate data structure when complete a DMA cycle */
    type_func_t high_prio;		/**< High priority or default priority */
    type_func_t iterrupt;		/**< Enable/disable interrupt */
    dma_msel_t msel;		/**< Input source to DMA channel @ref dma_msel_t */
    dma_msigsel_t msigsel;		/**< Input signal to DMA channel @ref dma_msigsel_t */
    uint8_t channel;		/**< Channel index */
} dma_config_t;

/**
  * @brief DMA handle structure definition
  */
typedef struct
{
    DMA_TypeDef *perh;		/**< DMA registers base address */
    dma_config_t config;		/**< Channel configure structure. @ref dma_config_t */
    void (*cplt_cbk)(void *arg);	/**< DMA transfers complete callback */
    void (*err_cbk)(void *arg);	/**< DMA bus occurs error callback */
    void *cplt_arg;			/**< The parameter of cplt_cbk() */
    void *err_arg;			/**< The parameter of err_cbk() */
} dma_handle_t;
/**
  * @}
  */

/**
  * @defgroup DMA_Private_Macros DMA Private Macros
  * @{
  */
#define IS_DMA_MSEL_TYPE(x)	((x) <= DMA_MSEL_TRNG)
#define IS_DMA_MSIGSEL_TYPE(x)	((x) <= 0xF)
#define IS_DMA_DATAINC_TYPE(x)  (((x) == DMA_DATA_INC_BYTE)     || \
                                 ((x) == DMA_DATA_INC_HALFWORD) || \
                                 ((x) == DMA_DATA_INC_WORD)     || \
                                 ((x) == DMA_DATA_INC_NONE))
#define IS_DMA_DATASIZE_TYPE(x)  (((x) == DMA_DATA_SIZE_BYTE)     || \
                                  ((x) == DMA_DATA_SIZE_HALFWORD) || \
                                  ((x) == DMA_DATA_SIZE_WORD))
#define IS_CYCLECTRL_TYPE(x)  (((x) == DMA_CYCLE_CTRL_NONE)               || \
                               ((x) == DMA_CYCLE_CTRL_BASIC)              || \
                               ((x) == DMA_CYCLE_CTRL_AUTO)               || \
                               ((x) == DMA_CYCLE_CTRL_PINGPONG)           || \
                               ((x) == DMA_CYCLE_CTRL_MEM_SCATTER_GATHER) || \
                               ((x) == DMA_CYCLE_CTRL_PER_SCATTER_GATHER))
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
#define IS_DMA_CHANNEL(x)	((x) <= 5)
#define IS_DMA_DATA_SIZE(x)	((x) <= 1024)
#define IS_DMA_IT_TYPE(x)	(((x) <= 5) || ((x) == 31))
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
void ald_dma_irq_handler(void);
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
