/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2010-12-22   onelife     Initial creation for EFM32
 * 2011-06-27   onelife     Fix a bug when using compiler optimization
 * 2011-07-26   onelife     Add lock (semaphore) to prevent simultaneously
 *  access
 * 2011-12-09   onelife     Add giant gecko support
 * 2011-12-09   onelife     Add UART module support
 * 2011-12-20   onelife     Change USART status format
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
struct efm32_usart_int_mode_t
{
    rt_uint8_t          *data_ptr;
    rt_uint8_t          data_size;
    rt_uint32_t         read_index, save_index;
};

struct efm32_usart_dma_mode_t
{
    /* DMA Channel */
    rt_uint32_t         dma_channel;

    /* buffer info */
    rt_uint32_t         *data_ptr;
    rt_uint8_t          data_size;
};

struct efm32_usart_device_t
{
    /* Counter */
    rt_uint32_t         counter;
    /* Lock */
    struct rt_semaphore *lock;
    /* Unit number */
    rt_uint8_t          unit;
    /* State */
    volatile rt_uint8_t state;
    /*  Pointer to USART device structure */
    USART_TypeDef       *usart_device;
    /* Pointer to RX structure */
    void                *rx_mode;
    /* Pointer to TX structure */
    void                *tx_mode;
};

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define USART_WAIT_TIME_TX          (RT_TICK_PER_SECOND / 100 * 3)

#define USART_STATE_CONSOLE         (1 << 0)
#define USART_STATE_TX_BUSY         (1 << 1)
#define USART_STATE_RX_BUSY         (1 << 2)
#if defined(UART_PRESENT)
#define USART_STATE_ASYNC_ONLY      (1 << 3)
#endif
#define USART_STATE_SYNC            (1 << 4)
#define USART_STATE_MASTER          (1 << 5)
#define USART_STATE_AUTOCS          (1 << 6)
#define USART_STATE_9BIT            (1 << 7)
#define USART_CLK_MODE_GET(state)   ((state >> 8) & 0x03)

#define SYNC_SETTING_MASK           (0x1F)
#define SYNC_SETTING_SHIFT          (5)

/* Exported functions ------------------------------------------------------- */
void rt_hw_usart_init(void);

#endif /* __DRV_USART_H__ */
