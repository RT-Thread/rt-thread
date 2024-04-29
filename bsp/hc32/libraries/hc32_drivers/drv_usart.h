/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtthread.h>
#include "rtdevice.h"
#include "drv_irq.h"
#include "drv_dma.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
struct hc32_uart_irq_config
{
    struct hc32_irq_config irq_config;
    func_ptr_t             irq_callback;
};

/* HC32 config Rx timeout */
struct hc32_uart_rxto
{
    CM_TMR0_TypeDef             *TMR0_Instance;
    rt_uint32_t                 channel;
    rt_uint32_t                 clock;
    rt_size_t                   timeout_bits;
#if defined (HC32F460) || defined (HC32F4A0)
    struct hc32_irq_config      irq_config;
    func_ptr_t                  irq_callback;
#endif
};

/* HC32 config uart class */
struct hc32_uart_config
{
    const char                  *name;
    CM_USART_TypeDef            *Instance;
    rt_uint32_t                 clock;
#if defined (HC32F460) || defined (HC32F4A0)
    struct hc32_uart_irq_config rxerr_irq;
    struct hc32_uart_irq_config rx_irq;
    struct hc32_uart_irq_config tx_irq;
#elif defined (HC32F448) || defined (HC32F472)
    IRQn_Type                   irq_num;
    en_int_src_t                rxerr_int_src;
    en_int_src_t                tx_int_src;
    en_int_src_t                rx_int_src;
#ifdef RT_SERIAL_USING_DMA
    en_int_src_t                rxto_int_src;
#endif
#endif

#ifdef RT_SERIAL_USING_DMA
    struct hc32_uart_rxto       *rx_timeout;
    stc_dma_llp_descriptor_t    llp_desc[2U];
    struct dma_config           *dma_rx;
    struct hc32_uart_irq_config *tc_irq;
    struct dma_config           *dma_tx;
#endif
};

/* HC32 uart driver class */
struct hc32_uart
{
    struct hc32_uart_config *config;
#ifdef RT_SERIAL_USING_DMA
    rt_size_t               dma_rx_remaining_cnt;
#endif
    rt_uint16_t             uart_dma_flag;
    struct rt_serial_device serial;
};

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
int rt_hw_usart_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_USART_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
