/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2011-12-09   onelife     Initial creation for EFM32
 */

#ifndef __DRV_LEUSART_H__
#define __DRV_LEUSART_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
struct efm32_leuart_int_mode_t
{
    rt_uint8_t          *data_ptr;
    rt_uint8_t          data_size;
    rt_uint32_t         read_index, save_index;
};

struct efm32_leuart_dma_mode_t
{
    /* DMA Channel */
    rt_uint32_t         dma_channel;

    /* buffer info */
    rt_uint32_t         *data_ptr;
    rt_uint8_t          data_size;
};

struct efm32_leuart_device_t
{
    /* Counter */
    rt_uint32_t         counter;
    /* Lock */
    struct rt_semaphore *lock;
    /* Unit number */
    rt_uint8_t          unit;
    /* State */
    volatile rt_uint8_t state;
    /*  Pointer to LEUART device structure */
    LEUART_TypeDef      *leuart_device;
    /* Pointer to RX structure */
    void                *rx_mode;
    /* Pointer to TX structure */
    void                *tx_mode;
};

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define LEUART_WAIT_TIME_TX     (RT_TICK_PER_SECOND / 100 * 3)

#define LEUART_STATE_CONSOLE    (1 << 0)
#define LEUART_STATE_SYNC       (1 << 1)
#define LEUART_STATE_MASTER     (1 << 2)
#define LEUART_STATE_AUTOCS     (1 << 3)
#define LEUART_STATE_TX_BUSY    (1 << 4)
#define LEUART_STATE_RX_BUSY    (1 << 5)


/* Exported functions ------------------------------------------------------- */
void rt_hw_leuart_init(void);

#endif /* __DRV_LEUSART_H__ */

