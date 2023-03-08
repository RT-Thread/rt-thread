/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2010-12-22   onelife     Initial creation for EFM32
 * 2011-01-17   onelife     Merge with serial.c
 * 2011-05-06   onelife     Add sync mode (SPI) support
 * 2011-06-14   onelife     Fix a bug of TX by DMA
 * 2011-06-16   onelife     Modify init function for EFM32 library v2.0.0
 *  upgrading
 * 2011-07-07   onelife     Modify write function to avoid sleep in ISR
 * 2011-07-26   onelife     Add lock (semaphore) to prevent simultaneously
 *  access
 * 2011-11-29   onelife     Modify init function for EFM32 library v2.2.2
 *  upgrading
 * 2011-12-09   onelife     Add giant gecko support
 * 2011-12-09   onelife     Add UART module support
 * 2011-12-20   onelife     Add 9-bit SPI mode support
 * 2011-12-20   onelife     Change SPI write format (same as SPI read)
 * 2011-12-20   onelife     Change USART status format
 * 2011-12-27   onelife     Utilize "USART_PRESENT", "USART_COUNT",
 *                            "UART_PRESENT" and "UART_COUNT"
 * 2012-05-16   onelife     Fix a bug in rt_hw_usart_init()
 */

/***************************************************************************//**
 * @addtogroup efm32
 * @{
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "hdl_interrupt.h"
#include "drv_usart.h"

#if (defined(RT_USING_USART0) || defined(RT_USING_USART1) || \
    defined(RT_USING_USART2) || defined(RT_USING_UART0) || \
    defined(RT_USING_UART1))
 #if ((defined(RT_USING_USART0) || defined(RT_USING_USART1) || \
    defined(RT_USING_USART2)) && !defined(USART_PRESENT))
 #error "USART module is not available"
 #endif
 #if ((defined(RT_USING_UART0) || defined(RT_USING_UART1)) && \
    !defined(UART_PRESENT))
 #error "UART module is not available"
 #endif
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#ifdef RT_USART_DEBUG
#define usart_debug(format,args...)         rt_kprintf(format, ##args)
#else
#define usart_debug(format,args...)
#endif

/* Private variables ---------------------------------------------------------*/
#ifdef RT_USING_USART0
 #if (RT_USING_USART0 >= EFM32_USART_LOCATION_COUNT)
    #error "Wrong location number"
 #endif
    struct rt_device usart0_device;
    static struct rt_semaphore usart0_lock;
#endif

#ifdef RT_USING_USART1
 #if (USART_COUNT <= 1)
    #error "Wrong unit number"
 #endif
 #if (RT_USING_USART1 >= EFM32_USART_LOCATION_COUNT)
    #error "Wrong location number"
 #endif
    struct rt_device usart1_device;
    static struct rt_semaphore usart1_lock;
#endif

#ifdef RT_USING_USART2
 #if (USART_COUNT <= 2)
    #error "Wrong unit number"
 #endif
 #if (RT_USING_USART2 >= EFM32_USART_LOCATION_COUNT)
    #error "Wrong location number"
 #endif
    struct rt_device usart2_device;
    static struct rt_semaphore usart2_lock;
#endif

#ifdef RT_USING_UART0
 #if (RT_USING_UART0 >= EFM32_UART_LOCATION_COUNT)
    #error "Wrong location number"
 #endif
    struct rt_device uart0_device;
    static struct rt_semaphore uart0_lock;
#endif

#ifdef RT_USING_UART1
 #if (UART_COUNT <= 1)
    #error "Wrong unit number"
 #endif
 #if (RT_USING_UART1 >= EFM32_UART_LOCATION_COUNT)
    #error "Wrong location number"
 #endif
    struct rt_device uart1_device;
    static struct rt_semaphore uart1_lock;
#endif

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/***************************************************************************//**
 * @brief
 *   Initialize USART device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @return
 *   Error code
 ******************************************************************************/
static rt_err_t rt_usart_init (rt_device_t dev)
{
    struct efm32_usart_device_t *usart;

    usart = (struct efm32_usart_device_t *)(dev->user_data);

    if (!(dev->flag & RT_DEVICE_FLAG_ACTIVATED))
    {
        if (dev->flag & RT_DEVICE_FLAG_DMA_TX)
        {
            struct efm32_usart_dma_mode_t *dma_tx;

            dma_tx = (struct efm32_usart_dma_mode_t *)(usart->tx_mode);

            usart->state |= USART_STATE_RX_BUSY;
        }

        if (dev->flag & RT_DEVICE_FLAG_INT_RX)
        {
            struct efm32_usart_int_mode_t *int_rx;

            int_rx = (struct efm32_usart_int_mode_t *)(usart->rx_mode);

            int_rx->data_ptr = RT_NULL;
        }

        /* Enable USART */
        USART_Enable(usart->usart_device, usartEnable);

        dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
    }

    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *   Open USART device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @param[in] oflag
 *   Device open flag
 *
 * @return
 *   Error code
 ******************************************************************************/
static rt_err_t rt_usart_open(rt_device_t dev, rt_uint16_t oflag)
{
    RT_ASSERT(dev != RT_NULL);

    struct efm32_usart_device_t *usart;

    usart = (struct efm32_usart_device_t *)(dev->user_data);

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        IRQn_Type                   rxIrq;

        //if (usart->state & USART_STATE_CONSOLE)
        {   /* Allocate new RX buffer */
            struct efm32_usart_int_mode_t   *int_mode;

            int_mode = (struct efm32_usart_int_mode_t *)(usart->rx_mode);

            if ((int_mode->data_ptr = rt_malloc(USART_RX_BUFFER_SIZE)) == RT_NULL)
            {
                usart_debug("USART%d err: no mem for RX BUF\n", usart->unit);
                return -RT_ENOMEM;
            }
            rt_memset(int_mode->data_ptr, 0, USART_RX_BUFFER_SIZE);
            int_mode->data_size = USART_RX_BUFFER_SIZE;
            int_mode->read_index = 0;
            int_mode->save_index = 0;
        }

        /* Enable RX interrupt */
#if defined(UART_PRESENT)
        if (usart->state & USART_STATE_ASYNC_ONLY)
        {
            usart->usart_device->IEN    = UART_IEN_RXDATAV;
        }
        else
#endif
        {
            usart->usart_device->IEN    = USART_IEN_RXDATAV;
        }

        /* Enable IRQ */
        switch (usart->unit)
        {
        case 0:
#if defined(UART_PRESENT)
            if (usart->state & USART_STATE_ASYNC_ONLY)
            {
                rxIrq   = UART0_RX_IRQn;
            }
            else
#endif
            {
                rxIrq   = USART0_RX_IRQn;
            }
            break;
#if ((defined(USART_PRESENT) && (USART_COUNT > 1)) || \
    (defined(UART_PRESENT) && (UART_COUNT > 1)))
        case 1:
 #if (defined(UART_PRESENT) && (UART_COUNT > 1))
            if (usart->state & USART_STATE_ASYNC_ONLY)
            {
                rxIrq   = UART1_RX_IRQn;
            }
            else
 #endif
            {
                rxIrq   = USART1_RX_IRQn;
            }
            break;
#endif
#if ((defined(USART_PRESENT) && (USART_COUNT > 2)) || \
    (defined(UART_PRESENT) && (UART_COUNT > 2)))
        case 2:
 #if (defined(UART_PRESENT) && (UART_COUNT > 2))
            if (usart->state & USART_STATE_ASYNC_ONLY)
            {
                rxIrq   = UART2_RX_IRQn;
            }
            else
 #endif
            {
                rxIrq   = USART2_RX_IRQn;
            }
            break;
#endif
        }
        if (oflag != RT_DEVICE_OFLAG_WRONLY)
        {
            NVIC_ClearPendingIRQ(rxIrq);
            NVIC_SetPriority(rxIrq, EFM32_IRQ_PRI_DEFAULT);
            NVIC_EnableIRQ(rxIrq);
        }
    }

    /* Clear Flag */
#if defined(UART_PRESENT)
    if (usart->state & USART_STATE_ASYNC_ONLY)
    {
        usart->usart_device->IFC    = _UART_IFC_MASK;
    }
    else
#endif
    {
        usart->usart_device->IFC    = _USART_IFC_MASK;
    }

    if ((dev->flag & RT_DEVICE_FLAG_DMA_TX) && (oflag != RT_DEVICE_OFLAG_RDONLY))
    {
        /* DMA IRQ is enabled by DMA_Init() */
        NVIC_SetPriority(DMA_IRQn, EFM32_IRQ_PRI_DEFAULT);
    }

    usart->counter++;
    usart_debug("USART%d: Open with flag %x\n", usart->unit, oflag);
    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *   Close USART device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @return
 *   Error code
 ******************************************************************************/
static rt_err_t rt_usart_close(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);

    struct efm32_usart_device_t *usart;

    usart = (struct efm32_usart_device_t *)(dev->user_data);

    if (--usart->counter == 0)
    {
        if (dev->flag & RT_DEVICE_FLAG_INT_RX)
        {
            struct efm32_usart_int_mode_t *int_rx;

            int_rx = (struct efm32_usart_int_mode_t *)usart->rx_mode;

            rt_free(int_rx->data_ptr);
            int_rx->data_ptr = RT_NULL;
        }
    }

    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *  Read from USART device
 *
 * @details
 *
 * @note
 *  9-bit SPI mode and SPI slave mode is untested
 *
 * @param[in] dev
 *  Pointer to device descriptor
 *
 * @param[in] pos
 *  Offset
 *
 * @param[in] buffer
 *  Poniter to the buffer
 *
 * @param[in] size
 *  Buffer size in byte
 *
 * @return
 *  Number of read bytes
 ******************************************************************************/
static rt_ssize_t rt_usart_read (
    rt_device_t     dev,
    rt_off_t        pos,
    void            *buffer,
    rt_size_t       size)
{
    rt_err_t    err_code;
    struct efm32_usart_device_t *usart;
    rt_size_t   read_len, len;
    rt_uint8_t  *ptr;
    rt_uint32_t rx_flag, tx_flag, b8_flag;

    usart = (struct efm32_usart_device_t *)(dev->user_data);
#if defined(UART_PRESENT)
    if (usart->state & USART_STATE_ASYNC_ONLY)
    {
        rx_flag = UART_STATUS_RXDATAV;
        tx_flag = UART_STATUS_TXBL;
        b8_flag = UART_CTRL_BIT8DV;
    }
    else
#endif
    {
        rx_flag = USART_STATUS_RXDATAV;
        tx_flag = USART_STATUS_TXBL;
        b8_flag = USART_CTRL_BIT8DV;
    }

    /* Lock device */
    if (rt_hw_interrupt_check())
    {
        err_code = rt_sem_take(usart->lock, RT_WAITING_NO);
    }
    else
    {
        err_code = rt_sem_take(usart->lock, RT_WAITING_FOREVER);
    }
    if (err_code != RT_EOK)
    {
        rt_set_errno(err_code);
        return 0;
    }

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        len = size;
        ptr = buffer;
        /* interrupt mode Rx */
        while (len)
        {
            rt_base_t level;
            struct efm32_usart_int_mode_t *int_rx;

            int_rx = (struct efm32_usart_int_mode_t *)\
                (((struct efm32_usart_device_t *)(dev->user_data))->rx_mode);

            /* disable interrupt */
            level = rt_hw_interrupt_disable();

            if (int_rx->read_index != int_rx->save_index)
            {
                /* read a character */
                *ptr++ = int_rx->data_ptr[int_rx->read_index];
                len--;

                /* move to next position */
                int_rx->read_index ++;
                if (int_rx->read_index >= USART_RX_BUFFER_SIZE)
                {
                    int_rx->read_index = 0;
                }
            }
            else
            {
                /* set error code */
                err_code = -RT_EEMPTY;

                /* enable interrupt */
                rt_hw_interrupt_enable(level);
                break;
            }

            /* enable interrupt */
            rt_hw_interrupt_enable(level);
        }

        read_len = (rt_uint32_t)ptr - (rt_uint32_t)buffer;
    }
    else
    {
        if (usart->state & USART_STATE_SYNC)
        {
            /* SPI read */
            rt_uint8_t inst_len = *((rt_uint8_t *)buffer);
            rt_uint8_t *inst_ptr = (rt_uint8_t *)(buffer + 1);
            rt_uint8_t *rx_buf = *((rt_uint8_t **)(buffer + inst_len + 1));
            rt_off_t i;

            ptr = inst_ptr;
            len = inst_len;
            /* Write instructions */
            if (len)
            {
                if (usart->state & USART_STATE_9BIT)
                {
                    usart->usart_device->CTRL &= ~b8_flag;
                }
                while (len)
                {
                    while (!(usart->usart_device->STATUS & tx_flag));
                    usart->usart_device->TXDATA = (rt_uint32_t)*(ptr++);
                    len--;
                }
                if (usart->state & USART_STATE_9BIT)
                {
                    usart->usart_device->CTRL |= b8_flag;
                }
            }

            /* Flushing RX */
            usart->usart_device->CMD = USART_CMD_CLEARRX;
            /* Skip some bytes if necessary */
            for (i = 0; i < pos; i++)
            {
                /* dummy write */
                while (!(usart->usart_device->STATUS & tx_flag));
                usart->usart_device->TXDATA = (rt_uint32_t)0xff;
                /* dummy read */
                while (!(usart->usart_device->STATUS & rx_flag));
                *((rt_uint32_t *)0x00) = usart->usart_device->RXDATA;
            }

            ptr = rx_buf;
            len = size;
            /* Read data */
            while (len)
            {
                /* dummy write */
                while (!(usart->usart_device->STATUS & tx_flag));
                usart->usart_device->TXDATA = (rt_uint32_t)0xff;
                /* read a byte of data */
                while (!(usart->usart_device->STATUS & rx_flag));
                *(ptr++) = usart->usart_device->RXDATA & 0xff;
                len--;
            }
        }
        else
        {
            ptr = buffer;
            len = size;
            /* polling mode */
            while (len)
            {
                while (usart->usart_device->STATUS & rx_flag)
                {
                    *(ptr++) = usart->usart_device->RXDATA & 0xff;
                }
                len--;
            }
        }

        read_len = size - len;
    }

    /* Unlock device */
    rt_sem_release(usart->lock);

    /* set error code */
    rt_set_errno(err_code);

    return read_len;
}

/***************************************************************************//**
 * @brief
 *   Write to USART device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @param[in] pos
 *   Offset
 *
 * @param[in] buffer
 *   Poniter to the buffer
 *
 * @param[in] size
 *   Buffer size in byte
 *
 * @return
 *   Number of written bytes
 ******************************************************************************/
static rt_ssize_t rt_usart_write (
    rt_device_t     dev,
    rt_off_t        pos,
    const void*     buffer,
    rt_size_t       size)
{
    rt_err_t err_code;
    struct efm32_usart_device_t* usart = (struct efm32_usart_device_t*)(dev->user_data);
    rt_size_t   read_len, len;
    rt_uint8_t  *ptr;
    rt_size_t   write_size = 0;
    rt_uint32_t tx_flag, b8_flag;

#if defined(UART_PRESENT)
    if (usart->state & USART_STATE_ASYNC_ONLY)
    {
        tx_flag = UART_STATUS_TXBL;
        b8_flag = UART_CTRL_BIT8DV;
    }
    else
#endif
    {
        tx_flag = USART_STATUS_TXBL;
        b8_flag = USART_CTRL_BIT8DV;
    }

    /* Lock device */
    if (rt_hw_interrupt_check())
    {
        err_code = rt_sem_take(usart->lock, RT_WAITING_NO);
    }
    else
    {
        err_code = rt_sem_take(usart->lock, RT_WAITING_FOREVER);
    }
    if (err_code != RT_EOK)
    {
        rt_set_errno(err_code);
        return 0;
    }

    if (usart->state & USART_STATE_SYNC)
    {   /* SPI write */
        rt_uint8_t inst_len     = *((rt_uint8_t *)buffer);
        rt_uint8_t *inst_ptr    = (rt_uint8_t *)(buffer + 1);
        rt_uint8_t *tx_buf      = *((rt_uint8_t **)(buffer + inst_len + 1));

        ptr = inst_ptr;
        len = inst_len;
        /* Write instructions */
        if (len)
        {
            if (usart->state & USART_STATE_9BIT)
            {
                usart->usart_device->CTRL &= ~b8_flag;
            }
            if ((dev->flag & RT_DEVICE_FLAG_DMA_TX) && (len > 2))
            {   /* DMA mode Tx */
                struct efm32_usart_dma_mode_t *dma_tx;

                usart_debug("USART: DMA TX INS (%d)\n", len);
                dma_tx = (struct efm32_usart_dma_mode_t *)(usart->tx_mode);
                dma_tx->data_ptr = (rt_uint32_t *)ptr;
                dma_tx->data_size = len;

                usart->state |= USART_STATE_TX_BUSY;
                DMA_ActivateBasic(
                    dma_tx->dma_channel,
                    true,
                    false,
                    (void *)&(usart->usart_device->TXDATA),
                    (void *)ptr,
                    (rt_uint32_t)(len - 1));
                /* Wait, otherwise the TX buffer is overwrite */
                // TODO: This function blocks the process => goto low power mode?
        //      if (usart->state & USART_STATE_CONSOLE)
        //      {
                    while(usart->state & USART_STATE_TX_BUSY);
        //      }
        //      else
        //      {
        //          while(usart->state & USART_STATE_TX_BUSY)
        //          {
        //              rt_thread_sleep(USART_WAIT_TIME_TX);
        //          }
        //      }
            }
            else
            {   /* polling mode */
                usart_debug("USART: Polling TX INS (%d)\n", len);
                while (len)
                {
                    while (!(usart->usart_device->STATUS & tx_flag));
                    usart->usart_device->TXDATA = (rt_uint32_t)*(ptr++);
                    len--;
                }
            }
            if (usart->state & USART_STATE_9BIT)
            {
                usart->usart_device->CTRL |= b8_flag;
            }
        }

        ptr = tx_buf;
    }
    else
    {
        ptr = (rt_uint8_t *)buffer;
    }

    len = size;
    /* Write data */
    if (dev->flag & RT_DEVICE_FLAG_STREAM)
    {
        if (*(ptr + len - 1) == '\n')
        {
            *(ptr + len - 1) = '\r';
            *(ptr + len++) = '\n';
            *(ptr + len) = 0;
        }
    }
    if ((dev->flag & RT_DEVICE_FLAG_DMA_TX) && (len > 2))
    {   /* DMA mode Tx */
        struct efm32_usart_dma_mode_t *dma_tx;

        usart_debug("USART: DMA TX data (%d)\n", len);
        dma_tx = (struct efm32_usart_dma_mode_t *)(usart->tx_mode);
        dma_tx->data_ptr = (rt_uint32_t *)ptr;
        dma_tx->data_size = len;

        usart->state |= USART_STATE_TX_BUSY;
        DMA_ActivateBasic(
            dma_tx->dma_channel,
            true,
            false,
            (void *)&(usart->usart_device->TXDATA),
            (void *)ptr,
            (rt_uint32_t)(len - 1));

        /* Wait, otherwise the TX buffer is overwrite */
        // TODO: This function blocks the process => goto low power mode?
//      if (usart->state & USART_STATE_CONSOLE)
//      {
            while(usart->state & USART_STATE_TX_BUSY);
//      }
//      else
//      {
//          while(usart->state & USART_STATE_TX_BUSY)
//          {
//              rt_thread_sleep(USART_WAIT_TIME_TX);
//          }
//      }
        write_size = size;
    }
    else
    {   /* polling mode */
        usart_debug("USART: Polling TX data (%d)\n", len);
        while (len)
        {
            while (!(usart->usart_device->STATUS & tx_flag));
            usart->usart_device->TXDATA = (rt_uint32_t)*(ptr++);
            len--;
        }

        write_size = size - len;
    }

    /* Unlock device */
    rt_sem_release(usart->lock);

    /* set error code */
    rt_set_errno(err_code);

    return write_size;
}

/***************************************************************************//**
* @brief
*   Configure USART device
*
* @details
*
* @note
*
* @param[in] dev
*   Pointer to device descriptor
*
* @param[in] cmd
*   IIC control command
*
* @param[in] args
*   Arguments
*
* @return
*   Error code
******************************************************************************/
static rt_err_t rt_usart_control (
    rt_device_t     dev,
    rt_uint8_t      cmd,
    void            *args)
{
    RT_ASSERT(dev != RT_NULL);

    rt_err_t    err_code;
    struct efm32_usart_device_t *usart;

    usart = (struct efm32_usart_device_t *)(dev->user_data);

    /* Lock device */
    if (rt_hw_interrupt_check())
    {
        err_code = rt_sem_take(usart->lock, RT_WAITING_NO);
    }
    else
    {
        err_code = rt_sem_take(usart->lock, RT_WAITING_FOREVER);
    }
    if (err_code != RT_EOK)
    {
        return err_code;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SUSPEND:
        /* Suspend device */
        dev->flag |= RT_DEVICE_FLAG_SUSPENDED;
        USART_Enable(usart->usart_device, usartDisable);
        break;

    case RT_DEVICE_CTRL_RESUME:
        /* Resume device */
        dev->flag &= ~RT_DEVICE_FLAG_SUSPENDED;
        USART_Enable(usart->usart_device, usartEnable);
        break;

    case RT_DEVICE_CTRL_USART_RBUFFER:
        /* Set RX buffer */
        {
            struct efm32_usart_int_mode_t *int_rx;
            rt_uint8_t size;

            int_rx = (struct efm32_usart_int_mode_t *)(usart->rx_mode);
            size = (rt_uint8_t)((rt_uint32_t)args & 0xFFUL);

            /* Free previous RX buffer */
            if (int_rx->data_ptr != RT_NULL)
            {
                if (size == 0)
                {   /* Free RX buffer */
                    rt_free(int_rx->data_ptr);
                    int_rx->data_ptr = RT_NULL;
                }
                else if (size != int_rx->data_size)
                {
                    /* Re-allocate RX buffer */
                    if ((int_rx->data_ptr = rt_realloc(int_rx->data_ptr, size)) \
                        == RT_NULL)
                    {
                        usart_debug("USART%d err: no mem for RX BUF\n", usart->unit);
                        err_code = -RT_ENOMEM;
                        break;
                    }
                    // TODO: Is the following line necessary?
                    //rt_memset(int_rx->data_ptr, 0, size);
                }
            }
            else
            {
                /* Allocate new RX buffer */
                if ((int_rx->data_ptr = rt_malloc(size)) == RT_NULL)
                {
                    usart_debug("USART%d err: no mem for RX BUF\n", usart->unit);
                    err_code = -RT_ENOMEM;
                    break;
                }
            }
            int_rx->data_size = size;
            int_rx->read_index = 0;
            int_rx->save_index = 0;
        }
        break;

    }

    /* Unlock device */
    rt_sem_release(usart->lock);

    return err_code;
}

/***************************************************************************//**
 * @brief
 *  USART RX data valid interrupt handler
 *
 * @details
 *
 * @note
 *  9-bit SPI mode has not implemented yet and SPI slave mode is untested
 *
 * @param[in] dev
 *  Pointer to device descriptor
 ******************************************************************************/
void rt_hw_usart_rx_isr(rt_device_t dev)
{
    struct efm32_usart_device_t     *usart;
    struct efm32_usart_int_mode_t   *int_rx;
    rt_uint32_t                     flag;

    /* interrupt mode receive */
    RT_ASSERT(dev->flag & RT_DEVICE_FLAG_INT_RX);
    usart = (struct efm32_usart_device_t *)(dev->user_data);
    int_rx = (struct efm32_usart_int_mode_t *)(usart->rx_mode);
    RT_ASSERT(int_rx->data_ptr != RT_NULL);
#if defined(UART_PRESENT)
    if (usart->state & USART_STATE_ASYNC_ONLY)
    {
        flag = UART_STATUS_RXDATAV;
    }
    else
#endif
    {
        flag = USART_STATUS_RXDATAV;
    }

    /* Set status */
    usart->state |= USART_STATE_RX_BUSY;

    /* save into rx buffer */
    while (usart->usart_device->STATUS & flag)
    {
        rt_base_t level;

        /* disable interrupt */
        level = rt_hw_interrupt_disable();

        /* save character */
        int_rx->data_ptr[int_rx->save_index] = \
            (rt_uint8_t)(usart->usart_device->RXDATA & 0xFFUL);
        int_rx->save_index ++;
        if (int_rx->save_index >= USART_RX_BUFFER_SIZE)
            int_rx->save_index = 0;

        /* if the next position is read index, discard this 'read char' */
        if (int_rx->save_index == int_rx->read_index)
        {
            int_rx->read_index ++;
            if (int_rx->read_index >= USART_RX_BUFFER_SIZE)
            {
                int_rx->read_index = 0;
            }
        }

        /* enable interrupt */
        rt_hw_interrupt_enable(level);
    }

    /* invoke callback */
    if (dev->rx_indicate != RT_NULL)
    {
        rt_size_t rx_length;

        /* get rx length */
        rx_length = int_rx->read_index > int_rx->save_index ?
            USART_RX_BUFFER_SIZE - int_rx->read_index + int_rx->save_index : \
            int_rx->save_index - int_rx->read_index;

        dev->rx_indicate(dev, rx_length);
    }
}

/***************************************************************************//**
 * @brief
 *  DMA for USART TX interrupt handler
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *  Pointer to device descriptor
 ******************************************************************************/
void rt_hw_usart_dma_tx_isr(rt_device_t dev)
{
    /* DMA mode receive */
    struct efm32_usart_device_t     *usart;
    struct efm32_usart_dma_mode_t   *dma_tx;

    RT_ASSERT(dev->flag & RT_DEVICE_FLAG_DMA_TX);

    usart = (struct efm32_usart_device_t *)(dev->user_data);
    dma_tx = (struct efm32_usart_dma_mode_t *)(usart->tx_mode);

    /* invoke call to notify tx complete */
    if (dev->tx_complete != RT_NULL)
    {
        dev->tx_complete(dev, dma_tx->data_ptr);
    }

    /* Set status */
    usart->state &= ~(rt_uint32_t)USART_STATE_TX_BUSY;
}

/***************************************************************************//**
* @brief
*   Register USART device
*
* @details
*
* @note
*
* @param[in] device
*   Pointer to device descriptor
*
* @param[in] name
*   Device name
*
* @param[in] flag
*   Configuration flags
*
* @param[in] usart
*   Pointer to USART device descriptor
*
* @return
*   Error code
******************************************************************************/
rt_err_t rt_hw_usart_register(
    rt_device_t     device,
    const char      *name,
    rt_uint32_t     flag,
    struct efm32_usart_device_t *usart)
{
    RT_ASSERT(device != RT_NULL);

    if ((flag & RT_DEVICE_FLAG_DMA_RX) ||
        (flag & RT_DEVICE_FLAG_INT_TX))
    {
        RT_ASSERT(0);
    }

    if (usart->state & USART_STATE_SYNC)
    {
        device->type    = RT_Device_Class_SPIBUS;
    }
    else
    {
        device->type    = RT_Device_Class_Char;
    }
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->init        = rt_usart_init;
    device->open        = rt_usart_open;
    device->close       = rt_usart_close;
    device->read        = rt_usart_read;
    device->write       = rt_usart_write;
    device->control     = rt_usart_control;
    device->user_data   = usart;

    /* register a character device */
    return rt_device_register(device, name, RT_DEVICE_FLAG_RDWR | flag);
}

/***************************************************************************//**
* @brief
*   Initialize the specified USART unit
*
* @details
*
* @note
*
* @param[in] device
*   Pointer to device descriptor
*
* @param[in] unitNumber
*   Unit number
*
* @param[in] location
*   Pin location number
*
* @param[in] flag
*   Configuration flag
*
* @param[in] dmaChannel
*   DMA channel number for TX
*
* @param[in] console
*   Indicate if using as console
*
* @return
*   Pointer to USART device
******************************************************************************/
static struct efm32_usart_device_t *rt_hw_usart_unit_init(
    rt_device_t device,
    rt_uint8_t  unitNumber,
    rt_uint8_t  location,
    rt_uint32_t flag,
    rt_uint32_t dmaChannel,
    rt_uint8_t  config)
{
    struct efm32_usart_device_t     *usart;
    struct efm32_usart_dma_mode_t   *dma_mode;
    DMA_CB_TypeDef                  *callback;
    CMU_Clock_TypeDef               usartClock;
    rt_uint32_t                     txDmaSelect;
    GPIO_Port_TypeDef               port_tx, port_rx, port_clk, port_cs;
    rt_uint32_t                     pin_tx, pin_rx, pin_clk, pin_cs;
    efm32_irq_hook_init_t           hook;

    do
    {
        /* Allocate device */
        usart = rt_malloc(sizeof(struct efm32_usart_device_t));
        if (usart == RT_NULL)
        {
            usart_debug("USART%d err: no mem\n", usart->unit);
            break;
        }
        usart->counter  = 0;
        usart->unit     = unitNumber;
        usart->state    = config;
        usart->tx_mode  = RT_NULL;
        usart->rx_mode  = RT_NULL;

        /* Allocate TX */
        dma_mode = RT_NULL;
        if (flag & RT_DEVICE_FLAG_DMA_TX)
        {
            usart->tx_mode = dma_mode = rt_malloc(sizeof(struct efm32_usart_dma_mode_t));
            if (dma_mode == RT_NULL)
            {
                usart_debug("USART%d err: no mem for DMA TX\n", usart->unit);
                break;
            }
            dma_mode->dma_channel = dmaChannel;
        }

        /* Allocate RX */
        if (flag & RT_DEVICE_FLAG_INT_RX)
        {
            usart->rx_mode = rt_malloc(sizeof(struct efm32_usart_int_mode_t));
            if (usart->rx_mode == RT_NULL)
            {
                usart_debug("USART%d err: no mem for INT RX\n", usart->unit);
                break;
            }
        }

        /* Initialization */
#if defined(UART_PRESENT)
        if ((!(config & USART_STATE_ASYNC_ONLY) && (unitNumber >= USART_COUNT)) || \
            ((config & USART_STATE_ASYNC_ONLY) && (unitNumber >= UART_COUNT)))
#else
        if (unitNumber >= USART_COUNT)
#endif
        {
            break;
        }
        switch (unitNumber)
        {
        case 0:
#if defined(UART_PRESENT)
            if (config & USART_STATE_ASYNC_ONLY)
            {
                usart->usart_device = UART0;
                usartClock          = (CMU_Clock_TypeDef)cmuClock_UART0;
                txDmaSelect         = DMAREQ_UART0_TXBL;
                port_tx             = AF_UART0_TX_PORT(location);
                pin_tx              = AF_UART0_TX_PIN(location);
                port_rx             = AF_UART0_RX_PORT(location);
                pin_rx              = AF_UART0_RX_PIN(location);
            }
            else
 #endif
            {
                usart->usart_device = USART0;
                usartClock          = (CMU_Clock_TypeDef)cmuClock_USART0;
                txDmaSelect         = DMAREQ_USART0_TXBL;
                port_tx             = AF_USART0_TX_PORT(location);
                pin_tx              = AF_USART0_TX_PIN(location);
                port_rx             = AF_USART0_RX_PORT(location);
                pin_rx              = AF_USART0_RX_PIN(location);
                port_clk            = AF_USART0_CLK_PORT(location);
                pin_clk             = AF_USART0_CLK_PIN(location);
                port_cs             = AF_USART0_CS_PORT(location);
                pin_cs              = AF_USART0_CS_PIN(location);
            }
            break;
#if ((defined(USART_PRESENT) && (USART_COUNT > 1)) || \
    (defined(UART_PRESENT) && (UART_COUNT > 1)))
        case 1:
 #if (defined(UART_PRESENT) && (UART_COUNT > 1))
            if (config & USART_STATE_ASYNC_ONLY)
            {
                usart->usart_device = UART1;
                usartClock          = (CMU_Clock_TypeDef)cmuClock_UART1;
                txDmaSelect         = DMAREQ_UART1_TXBL;
                port_tx             = AF_UART1_TX_PORT(location);
                pin_tx              = AF_UART1_TX_PIN(location);
                port_rx             = AF_UART1_RX_PORT(location);
                pin_rx              = AF_UART1_RX_PIN(location);
            }
            else
 #endif
            {
                usart->usart_device = USART1;
                usartClock          = (CMU_Clock_TypeDef)cmuClock_USART1;
                txDmaSelect         = DMAREQ_USART1_TXBL;
                port_tx             = AF_USART1_TX_PORT(location);
                pin_tx              = AF_USART1_TX_PIN(location);
                port_rx             = AF_USART1_RX_PORT(location);
                pin_rx              = AF_USART1_RX_PIN(location);
                port_clk            = AF_USART1_CLK_PORT(location);
                pin_clk             = AF_USART1_CLK_PIN(location);
                port_cs             = AF_USART1_CS_PORT(location);
                pin_cs              = AF_USART1_CS_PIN(location);
            }
            break;
#endif
#if ((defined(USART_PRESENT) && (USART_COUNT > 2)) || \
    (defined(UART_PRESENT) && (UART_COUNT > 2)))
        case 2:
 #if (defined(UART_PRESENT) && (UART_COUNT > 2))
            if (config & USART_STATE_ASYNC_ONLY)
            {
                usart->usart_device = UART2;
                usartClock          = (CMU_Clock_TypeDef)cmuClock_UART2;
                txDmaSelect         = DMAREQ_UART2_TXBL;
                port_tx             = AF_UART2_TX_PORT(location);
                pin_tx              = AF_UART2_TX_PIN(location);
                port_rx             = AF_UART2_RX_PORT(location);
                pin_rx              = AF_UART2_RX_PIN(location);
            }
            else
 #endif
            {
                usart->usart_device = USART2;
                usartClock          = (CMU_Clock_TypeDef)cmuClock_USART2;
                txDmaSelect         = DMAREQ_USART2_TXBL;
                port_tx             = AF_USART2_TX_PORT(location);
                pin_tx              = AF_USART2_TX_PIN(location);
                port_rx             = AF_USART2_RX_PORT(location);
                pin_rx              = AF_USART2_RX_PIN(location);
                port_clk            = AF_USART2_CLK_PORT(location);
                pin_clk             = AF_USART2_CLK_PIN(location);
                port_cs             = AF_USART2_CS_PORT(location);
                pin_cs              = AF_USART2_CS_PIN(location);
            }
            break;
#endif
        default:
            break;
        }

        /* Enable USART clock */
        CMU_ClockEnable(usartClock, true);

        /* Config GPIO */
        GPIO_PinModeSet(
            port_tx,
            pin_tx,
            gpioModePushPull,
            0);
        GPIO_PinModeSet(
            port_rx,
            pin_rx,
            gpioModeInputPull,
            1);
        if (config & USART_STATE_SYNC)
        {
            GPIO_PinModeSet(
                port_clk,
                pin_clk,
                gpioModePushPull,
                0);
        }
        if (config & USART_STATE_AUTOCS)
        {
            GPIO_PinModeSet(
                port_cs,
                pin_cs,
                gpioModePushPull,
                1);
        }

        /* Config interrupt and NVIC */
        if (flag & RT_DEVICE_FLAG_INT_RX)
        {
            hook.type       = efm32_irq_type_usart;
            hook.unit       = unitNumber * 2 + 1;
#if defined(UART_PRESENT)
            if (config & USART_STATE_ASYNC_ONLY)
            {
                hook.unit += USART_COUNT * 2;
            }
#endif
            hook.cbFunc     = rt_hw_usart_rx_isr;
            hook.userPtr    = device;
            efm32_irq_hook_register(&hook);
        }

        /* Config DMA */
        if (flag & RT_DEVICE_FLAG_DMA_TX)
        {
            DMA_CfgChannel_TypeDef  chnlCfg;
            DMA_CfgDescr_TypeDef    descrCfg;

            hook.type           = efm32_irq_type_dma;
            hook.unit           = dmaChannel;
            hook.cbFunc         = rt_hw_usart_dma_tx_isr;
            hook.userPtr        = device;
            efm32_irq_hook_register(&hook);

            callback = (DMA_CB_TypeDef *)rt_malloc(sizeof(DMA_CB_TypeDef));
            if (callback == RT_NULL)
            {
                usart_debug("USART%d err: no mem for callback\n", usart->unit);
                break;
            }
            callback->cbFunc    = DMA_IRQHandler_All;
            callback->userPtr   = RT_NULL;
            callback->primary   = 0;

            /* Setting up DMA channel */
            chnlCfg.highPri     = false;    /* Can't use with peripherals */
            chnlCfg.enableInt   = true;     /* Interrupt for callback function */
            chnlCfg.select      = txDmaSelect;
            chnlCfg.cb          = callback;
            DMA_CfgChannel(dmaChannel, &chnlCfg);

            /* Setting up DMA channel descriptor */
            descrCfg.dstInc     = dmaDataIncNone;
            descrCfg.srcInc     = dmaDataInc1;
            descrCfg.size       = dmaDataSize1;
            descrCfg.arbRate    = dmaArbitrate1;
            descrCfg.hprot      = 0;
            DMA_CfgDescr(dmaChannel, true, &descrCfg);
        }

        /* Init specified USART unit */
        if (config & USART_STATE_SYNC)
        {
            USART_InitSync_TypeDef init_sync = USART_INITSYNC_DEFAULT;

            init_sync.enable        = usartEnable;
            init_sync.refFreq       = 0;
            init_sync.baudrate      = SPI_BAUDRATE;
            if (config & USART_STATE_9BIT)
            {
                init_sync.databits  = usartDatabits9;
            }
            else
            {
                init_sync.databits  = usartDatabits8;
            }
            if (config & USART_STATE_MASTER)
            {
                init_sync.master    = true;
            }
            else
            {
                init_sync.master    = false;
            }
            init_sync.msbf          = true;

            switch (USART_CLK_MODE_GET(config))
            {
            case 0:
                init_sync.clockMode = usartClockMode0;
                break;
            case 1:
                init_sync.clockMode = usartClockMode1;
                break;
            case 2:
                init_sync.clockMode = usartClockMode2;
                break;
            case 3:
                init_sync.clockMode = usartClockMode3;
                break;
            }
            USART_InitSync(usart->usart_device, &init_sync);
        }
        else
        {
            USART_InitAsync_TypeDef init_async = USART_INITASYNC_DEFAULT;

            init_async.enable       = usartEnable;
            init_async.refFreq      = 0;
            init_async.baudrate     = UART_BAUDRATE;
            init_async.oversampling = USART_CTRL_OVS_X4;
            init_async.databits     = USART_FRAME_DATABITS_EIGHT;
            init_async.parity       = USART_FRAME_PARITY_NONE;
            init_async.stopbits     = USART_FRAME_STOPBITS_ONE;
            USART_InitAsync(usart->usart_device, &init_async);
        }

        /* Enable RX and TX pins and set location */
        usart->usart_device->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN | \
                        (location << _USART_ROUTE_LOCATION_SHIFT);
        if (config & USART_STATE_SYNC)
        {
            usart->usart_device->ROUTE |= USART_ROUTE_CLKPEN;
        }
        if (config & USART_STATE_AUTOCS)
        {
            usart->usart_device->ROUTE |= USART_ROUTE_CSPEN;
            if (config & USART_STATE_MASTER)
            {
                usart->usart_device->CTRL |= USART_CTRL_AUTOCS;
            }
        }

        /* Clear RX/TX buffers */
        usart->usart_device->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;

        return usart;
    } while(0);

    if (usart->rx_mode)
    {
        rt_free(usart->rx_mode);
    }
    if (usart->tx_mode)
    {
        rt_free(usart->tx_mode);
    }
    if (usart)
    {
        rt_free(usart);
    }
    if (callback)
    {
        rt_free(callback);
    }

#if defined(UART_PRESENT)
    if (config & USART_STATE_ASYNC_ONLY)
    {
        usart_debug("UART%d err: init failed!\n", unitNumber);
    }
    else
#endif
    {
        usart_debug("USART%d err: init failed!\n", unitNumber);
    }
    return RT_NULL;
}

/***************************************************************************//**
* @brief
*   Initialize all USART module related hardware and register USART device to
* kernel
*
* @details
*
* @note
******************************************************************************/
void rt_hw_usart_init(void)
{
    struct efm32_usart_device_t *usart;
    rt_uint32_t                 flag;
    rt_uint8_t                  config;

    do
    {
#if (defined(USART_PRESENT) && defined(RT_USING_USART0))
        config = 0x00;
        flag = RT_DEVICE_FLAG_RDWR;

 #ifdef RT_USART0_SYNC_MODE
        config |= USART_STATE_SYNC;
        config |= (RT_USART0_SYNC_MODE & SYNC_SETTING_MASK) << SYNC_SETTING_SHIFT;
  #if (!((RT_USART0_SYNC_MODE << SYNC_SETTING_SHIFT) & USART_STATE_MASTER))
         flag |= RT_DEVICE_FLAG_INT_RX;
  #endif
 #else
         flag |= RT_DEVICE_FLAG_INT_RX;
 #endif

 #if (RT_CONSOLE_DEVICE == EFM_USART0)
        config |= USART_STATE_CONSOLE;
        flag |= RT_DEVICE_FLAG_STREAM;
 #endif

 #ifdef RT_USART0_USING_DMA
        RT_ASSERT(RT_USART0_USING_DMA < DMA_CHAN_COUNT);
        flag |= RT_DEVICE_FLAG_DMA_TX;
 #else
       #define RT_USART0_USING_DMA EFM32_NO_DMA
 #endif

        /* Initialize and Register usart0 */
        if ((usart = rt_hw_usart_unit_init(
            &usart0_device,
            0,
            RT_USING_USART0,
            flag,
            RT_USART0_USING_DMA,
            config)) != RT_NULL)
        {
            rt_hw_usart_register(&usart0_device, RT_USART0_NAME, flag, usart);
        }
        else
        {
            break;
        }
        /* Initialize lock for usart0 */
        usart->lock = &usart0_lock;
        if (rt_sem_init(usart->lock, RT_USART0_NAME, 1, RT_IPC_FLAG_FIFO) != RT_EOK)
        {
            break;
        }
#endif

#if (defined(USART_PRESENT) && (USART_COUNT > 1) && defined(RT_USING_USART1))
        config = 0x00;
        flag = RT_DEVICE_FLAG_RDWR;

 #ifdef RT_USART1_SYNC_MODE
         config |= USART_STATE_SYNC;
         config |= (RT_USART1_SYNC_MODE & SYNC_SETTING_MASK) << SYNC_SETTING_SHIFT;
  #if (!((RT_USART1_SYNC_MODE << SYNC_SETTING_SHIFT) & USART_STATE_MASTER))
         flag |= RT_DEVICE_FLAG_INT_RX;
  #endif
 #else
         flag |= RT_DEVICE_FLAG_INT_RX;
 #endif

 #if (RT_CONSOLE_DEVICE == EFM_USART1)
        config |= USART_STATE_CONSOLE;
        flag |= RT_DEVICE_FLAG_STREAM;
 #endif

 #ifdef RT_USART1_USING_DMA
        RT_ASSERT(RT_USART1_USING_DMA < DMA_CHAN_COUNT);
        flag |= RT_DEVICE_FLAG_DMA_TX;
 #else

       #define RT_USART1_USING_DMA EFM32_NO_DMA
 #endif

        /* Initialize and Register usart1 */
        if ((usart = rt_hw_usart_unit_init(
            &usart1_device,
            1,
            RT_USING_USART1,
            flag,
            RT_USART1_USING_DMA,
            config)) != RT_NULL)
        {
            rt_hw_usart_register(&usart1_device, RT_USART1_NAME, flag, usart);
        }
        else
        {
            break;
        }
        /* Initialize lock for usart1 */
        usart->lock = &usart1_lock;
        if (rt_sem_init(usart->lock, RT_USART1_NAME, 1, RT_IPC_FLAG_FIFO) != RT_EOK)
        {
            break;
        }
#endif

#if (defined(USART_PRESENT) && (USART_COUNT > 2) && defined(RT_USING_USART2))
        config = 0x00;
        flag = RT_DEVICE_FLAG_RDWR;

 #ifdef RT_USART2_SYNC_MODE
         config |= USART_STATE_SYNC;
         config |= (RT_USART2_SYNC_MODE & SYNC_SETTING_MASK) << SYNC_SETTING_SHIFT;
  #if (!((RT_USART2_SYNC_MODE << SYNC_SETTING_SHIFT) & USART_STATE_MASTER))
        flag |= RT_DEVICE_FLAG_INT_RX;
  #endif
 #else
        flag |= RT_DEVICE_FLAG_INT_RX;
 #endif

#if (RT_CONSOLE_DEVICE == EFM_USART2)
        config |= USART_STATE_CONSOLE;
        flag |= RT_DEVICE_FLAG_STREAM;
#endif

 #ifdef RT_USART2_USING_DMA
        RT_ASSERT(RT_USART2_USING_DMA < DMA_CHAN_COUNT);
        flag |= RT_DEVICE_FLAG_DMA_TX;

 #else

       #define RT_USART2_USING_DMA EFM32_NO_DMA
 #endif

        /* Initialize and Register usart2 */
        if ((usart = rt_hw_usart_unit_init(
            &usart2_device,
            2,
            RT_USING_USART2,
            flag,
            RT_USART2_USING_DMA,
            config)) != RT_NULL)
        {
            rt_hw_usart_register(&usart2_device, RT_USART2_NAME, flag, usart);
        }
        else
        {
            break;
        }
        /* Initialize lock for usart2 */
        usart->lock = &usart2_lock;
        if (rt_sem_init(usart->lock, RT_USART2_NAME, 1, RT_IPC_FLAG_FIFO) != RT_EOK)
        {
            break;
        }
#endif

#if (defined(UART_PRESENT) && defined(RT_USING_UART0))
        config = USART_STATE_ASYNC_ONLY;
        flag = RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX;

 #if (RT_CONSOLE_DEVICE == EFM_UART0)
        config |= USART_STATE_CONSOLE;
        flag |= RT_DEVICE_FLAG_STREAM;
 #endif

 #ifdef RT_UART0_USING_DMA
        RT_ASSERT(RT_UART0_USING_DMA < DMA_CHAN_COUNT);
        flag |= RT_DEVICE_FLAG_DMA_TX;
 #else
       #define RT_UART0_USING_DMA EFM32_NO_DMA
 #endif

        /* Initialize and Register uart0 */
        if ((usart = rt_hw_usart_unit_init(
            &uart0_device,
            0,
            RT_USING_UART0,
            flag,
            RT_UART0_USING_DMA,
            config)) != RT_NULL)
        {
            rt_hw_usart_register(&uart0_device, RT_UART0_NAME, flag, usart);
        }
        else
        {
            break;
        }
        /* Initialize lock for uart0 */
        usart->lock = &uart0_lock;
        if (rt_sem_init(usart->lock, RT_UART0_NAME, 1, RT_IPC_FLAG_FIFO) != RT_EOK)
        {
            break;
        }
#endif

#if (defined(UART_PRESENT) && (UART_COUNT > 1) && defined(RT_USING_UART1))
        config = USART_STATE_ASYNC_ONLY;
        flag = RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX;

 #if (RT_CONSOLE_DEVICE == EFM_UART1)
        config |= USART_STATE_CONSOLE;
        flag |= RT_DEVICE_FLAG_STREAM;
 #endif

 #ifdef RT_UART1_USING_DMA
        RT_ASSERT(RT_UART1_USING_DMA < DMA_CHAN_COUNT);
        flag |= RT_DEVICE_FLAG_DMA_TX;
 #else
       #define RT_UART1_USING_DMA EFM32_NO_DMA
 #endif

        /* Initialize and Register uart1 */
        if ((usart = rt_hw_usart_unit_init(
            &uart1_device,
            1,
            RT_USING_UART1,
            flag,
            RT_UART1_USING_DMA,
            config)) != RT_NULL)
        {
            rt_hw_usart_register(&uart1_device, RT_UART1_NAME, flag, usart);
        }
        else
        {
            break;
        }
        /* Initialize lock for uart1 */
        usart->lock = &uart1_lock;
        if (rt_sem_init(usart->lock, RT_UART1_NAME, 1, RT_IPC_FLAG_FIFO) != RT_EOK)
        {
            break;
        }
#endif

        usart_debug("USART: H/W init OK!\n");
        return;
    } while (0);

    rt_kprintf("USART: H/W init failed!\n");
}

#endif /* (defined(RT_USING_USART0) || defined(RT_USING_USART1) || \
    defined(RT_USING_USART2) || defined(RT_USING_UART0) || \
    defined(RT_USING_UART1)) */
/***************************************************************************//**
 * @}
 ******************************************************************************/
