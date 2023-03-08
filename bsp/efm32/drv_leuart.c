/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2011-12-09   onelife     Initial creation for EFM32
 * 2011-12-27   onelife     Utilize "LEUART_PRESENT" and "LEUART_COUNT"
 */

/***************************************************************************//**
 * @addtogroup efm32
 * @{
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "hdl_interrupt.h"
#include "drv_leuart.h"

#if (defined(RT_USING_LEUART0) || defined(RT_USING_LEUART1))
 #if !defined(LEUART_PRESENT)
 #error "LEUART module is not available"
 #endif
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#ifdef RT_LEUART_DEBUG
#define leuart_debug(format,args...)        rt_kprintf(format, ##args)
#else
#define leuart_debug(format,args...)
#endif

/* Private variables ---------------------------------------------------------*/
#if defined(RT_USING_LEUART0)
 #if (RT_USING_LEUART0 >= EFM32_LEUART_LOCATION_COUNT)
    #error "Wrong location number"
 #endif
    struct rt_device leuart0_device;
    static struct rt_semaphore leuart0_lock;
#endif

#if defined(RT_USING_LEUART1)
 #if (LEUART_COUNT <= 1)
 #error "Wrong unit number"
 #endif
 #if (RT_USING_LEUART1 >= EFM32_LEUART_LOCATION_COUNT)
    #error "Wrong location number"
 #endif
    struct rt_device leuart1_device;
    static struct rt_semaphore leuart1_lock;
#endif

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/***************************************************************************//**
 * @brief
 *   Initialize LEUART device
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
static rt_err_t rt_leuart_init (rt_device_t dev)
{
    struct efm32_leuart_device_t *leuart;

    leuart = (struct efm32_leuart_device_t *)(dev->user_data);

    if (!(dev->flag & RT_DEVICE_FLAG_ACTIVATED))
    {
        if (dev->flag & RT_DEVICE_FLAG_DMA_TX)
        {
            struct efm32_leuart_dma_mode_t *dma_tx;

            dma_tx = (struct efm32_leuart_dma_mode_t *)(leuart->tx_mode);

            leuart->state |= LEUART_STATE_RX_BUSY;
        }

        if (dev->flag & RT_DEVICE_FLAG_INT_RX)
        {
            struct efm32_leuart_int_mode_t *int_rx;

            int_rx = (struct efm32_leuart_int_mode_t *)(leuart->rx_mode);

            int_rx->data_ptr = RT_NULL;
        }

        /* Enable LEUART */
        LEUART_Enable(leuart->leuart_device, leuartEnable);

        dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
    }

    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *   Open LEUART device
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
static rt_err_t rt_leuart_open(rt_device_t dev, rt_uint16_t oflag)
{
    RT_ASSERT(dev != RT_NULL);

    struct efm32_leuart_device_t    *leuart;

    leuart = (struct efm32_leuart_device_t *)(dev->user_data);

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        IRQn_Type                   rxIrq;

        //if (leuart->state & LEUART_STATE_CONSOLE)
        {   /* Allocate new RX buffer */
            struct efm32_leuart_int_mode_t  *int_mode;

            int_mode = (struct efm32_leuart_int_mode_t *)(leuart->rx_mode);

            if ((int_mode->data_ptr = rt_malloc(LEUART_RX_BUFFER_SIZE)) == RT_NULL)
            {
                leuart_debug("LEUART%d err: no mem for RX BUF\n", leuart->unit);
                return -RT_ENOMEM;
            }
            rt_memset(int_mode->data_ptr, 0, LEUART_RX_BUFFER_SIZE);
            int_mode->data_size = LEUART_RX_BUFFER_SIZE;
            int_mode->read_index = 0;
            int_mode->save_index = 0;
        }

        /* Enable RX interrupt */
        leuart->leuart_device->IEN  = LEUART_IEN_RXDATAV;

        /* Enable IRQ */
        switch (leuart->unit)
        {
        case 0:
            rxIrq   = LEUART0_IRQn;
            break;
#if (LEUART_COUNT > 1)
        case 1:
            rxIrq   = LEUART1_IRQn;
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
    leuart->leuart_device->IFC      = _LEUART_IFC_MASK;

    if ((dev->flag & RT_DEVICE_FLAG_DMA_TX) && (oflag != RT_DEVICE_OFLAG_RDONLY))
    {
        /* DMA IRQ is enabled by DMA_Init() */
        NVIC_SetPriority(DMA_IRQn, EFM32_IRQ_PRI_DEFAULT);
    }

    leuart->counter++;
    leuart_debug("LEUART%d: Open with flag %x\n", leuart->unit, oflag);
    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *   Close LEUART device
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
static rt_err_t rt_leuart_close(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);

    struct efm32_leuart_device_t    *leuart;

    leuart = (struct efm32_leuart_device_t *)(dev->user_data);

    if (--leuart->counter == 0)
    {
        if (dev->flag & RT_DEVICE_FLAG_INT_RX)
        {
            struct efm32_leuart_int_mode_t *int_rx;

            int_rx = (struct efm32_leuart_int_mode_t *)leuart->rx_mode;

            rt_free(int_rx->data_ptr);
            int_rx->data_ptr = RT_NULL;
        }
    }

    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *   Read from LEUART device
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
 *   Number of read bytes
 ******************************************************************************/
static rt_ssize_t rt_leuart_read (
    rt_device_t     dev,
    rt_off_t        pos,
    void            *buffer,
    rt_size_t       size)
{
    struct efm32_leuart_device_t *leuart;
    rt_uint8_t  *ptr;
    rt_err_t    err_code;
    rt_size_t   read_len;

    leuart = (struct efm32_leuart_device_t *)(dev->user_data);

    /* Lock device */
    if (rt_hw_interrupt_check())
    {
        err_code = rt_sem_take(leuart->lock, RT_WAITING_NO);
    }
    else
    {
        err_code = rt_sem_take(leuart->lock, RT_WAITING_FOREVER);
    }
    if (err_code != RT_EOK)
    {
        rt_set_errno(err_code);
        return 0;
    }

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        ptr = buffer;

        /* interrupt mode Rx */
        while (size)
        {
            rt_base_t level;
            struct efm32_leuart_int_mode_t *int_rx;

            int_rx = (struct efm32_leuart_int_mode_t *)\
                (((struct efm32_leuart_device_t *)(dev->user_data))->rx_mode);

            /* disable interrupt */
            level = rt_hw_interrupt_disable();

            if (int_rx->read_index != int_rx->save_index)
            {
                /* read a character */
                *ptr++ = int_rx->data_ptr[int_rx->read_index];
                size--;

                /* move to next position */
                int_rx->read_index ++;
                if (int_rx->read_index >= LEUART_RX_BUFFER_SIZE)
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
        LEUART_TypeDef *leuart_device;

        leuart = (struct efm32_leuart_device_t *)(dev->user_data);
        leuart_device = ((struct efm32_leuart_device_t *)(dev->user_data))->leuart_device;
        ptr = buffer;

        /* polling mode */
        while ((rt_uint32_t)ptr - (rt_uint32_t)buffer < size)
        {
            while (leuart_device->STATUS & LEUART_STATUS_RXDATAV)
            {
                *ptr = leuart_device->RXDATA & 0xff;
                ptr ++;
            }
        }

        read_len = size;
    }

    /* Unlock device */
    rt_sem_release(leuart->lock);

    /* set error code */
    rt_set_errno(err_code);
    return read_len;
}

/***************************************************************************//**
 * @brief
 *   Write to LEUART device
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
static rt_ssize_t rt_leuart_write (
    rt_device_t     dev,
    rt_off_t        pos,
    const void*     buffer,
    rt_size_t       size)
{
    rt_err_t                        err_code;
    rt_size_t                       write_size;
    struct efm32_leuart_device_t*   leuart;

    write_size = 0;
    leuart = (struct efm32_leuart_device_t*)(dev->user_data);

    /* Lock device */
    if (rt_hw_interrupt_check())
    {
        err_code = rt_sem_take(leuart->lock, RT_WAITING_NO);
    }
    else
    {
        err_code = rt_sem_take(leuart->lock, RT_WAITING_FOREVER);
    }
    if (err_code != RT_EOK)
    {
        rt_set_errno(err_code);
        return 0;
    }

    if ((dev->flag & RT_DEVICE_FLAG_DMA_TX) && (size > 2))
    {   /* DMA mode Tx */
        struct efm32_leuart_dma_mode_t *dma_tx;

        if (dev->flag & RT_DEVICE_FLAG_STREAM)
        {
            if (*((rt_uint8_t *)buffer + size - 1) == '\n')
            {
                *((rt_uint8_t *)buffer + size - 1) = '\r';
                *((rt_uint8_t *)buffer + size++) = '\n';
                *((rt_uint8_t *)buffer + size) = 0;
            }
        }

        dma_tx = (struct efm32_leuart_dma_mode_t *)(leuart->tx_mode);
        dma_tx->data_ptr = (rt_uint32_t *)buffer;
        dma_tx->data_size = size;

        leuart->state |= LEUART_STATE_TX_BUSY;

        DMA_ActivateBasic(
            dma_tx->dma_channel,
            true,
            false,
            (void *)&(leuart->leuart_device->TXDATA),
            (void *)buffer,
            (rt_uint32_t)(size - 1));

        /* Wait, otherwise the TX buffer is overwrite */
//      if (leuart->state & LEUART_STATE_CONSOLE)
//      {
            while(leuart->state & LEUART_STATE_TX_BUSY);
//      }
//      else
//      {
//          while(leuart->state & LEUART_STATE_TX_BUSY)
//          {
//              rt_thread_sleep(LEUART_WAIT_TIME_TX);
//          }
//      }
// TODO: This function blocks the process
        write_size = size;
    }
    else
    {   /* polling mode */
        rt_uint8_t *ptr = (rt_uint8_t *)buffer;

        if (dev->flag & RT_DEVICE_FLAG_STREAM)
        {
            /* stream mode */
            while (size)
            {
                if (*ptr == '\n')
                {
                    while (!(leuart->leuart_device->STATUS & LEUART_STATUS_TXBL));
                    leuart->leuart_device->TXDATA = '\r';
                }

                while (!(leuart->leuart_device->STATUS & LEUART_STATUS_TXBL));
                leuart->leuart_device->TXDATA = (rt_uint32_t)*ptr;
                ++ptr; --size;
            }
        }
        else
        {
            /* write data directly */
            while (size)
            {
                while (!(leuart->leuart_device->STATUS & LEUART_STATUS_TXBL));
                leuart->leuart_device->TXDATA = (rt_uint32_t)*ptr;
                ++ptr; --size;
            }
        }

        write_size = (rt_size_t)ptr - (rt_size_t)buffer;
    }

    /* Unlock device */
    rt_sem_release(leuart->lock);

    /* set error code */
    rt_set_errno(err_code);
    return write_size;
}

/***************************************************************************//**
* @brief
*   Configure LEUART device
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
static rt_err_t rt_leuart_control (
    rt_device_t     dev,
    rt_uint8_t      cmd,
    void            *args)
{
    RT_ASSERT(dev != RT_NULL);

    rt_err_t    err_code;
    struct efm32_leuart_device_t *leuart;

    leuart = (struct efm32_leuart_device_t *)(dev->user_data);

    /* Lock device */
    if (rt_hw_interrupt_check())
    {
        err_code = rt_sem_take(leuart->lock, RT_WAITING_NO);
    }
    else
    {
        err_code = rt_sem_take(leuart->lock, RT_WAITING_FOREVER);
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
        LEUART_Enable(leuart->leuart_device, leuartDisable);
        break;

    case RT_DEVICE_CTRL_RESUME:
        /* Resume device */
        dev->flag &= ~RT_DEVICE_FLAG_SUSPENDED;
        LEUART_Enable(leuart->leuart_device, leuartEnable);
        break;

    case RT_DEVICE_CTRL_LEUART_RBUFFER:
        /* Set RX buffer */
        {
            struct efm32_leuart_int_mode_t *int_rx;
            rt_uint8_t size;

            int_rx = (struct efm32_leuart_int_mode_t *)(leuart->rx_mode);
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
                        leuart_debug("LEUART%d err: no mem for RX BUF\n", leuart->unit);
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
                    leuart_debug("LEUART%d err: no mem for RX BUF\n", leuart->unit);
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
    rt_sem_release(leuart->lock);

    return err_code;
}

/***************************************************************************//**
 * @brief
 *  LEUART RX data valid interrupt handler
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *  Pointer to device descriptor
 ******************************************************************************/
void rt_hw_leuart_rx_isr(rt_device_t dev)
{
    struct efm32_leuart_device_t    *leuart;
    struct efm32_leuart_int_mode_t  *int_rx;
    rt_uint32_t                     flag;

    /* interrupt mode receive */
    RT_ASSERT(dev->flag & RT_DEVICE_FLAG_INT_RX);

    leuart = (struct efm32_leuart_device_t *)(dev->user_data);
    int_rx = (struct efm32_leuart_int_mode_t *)(leuart->rx_mode);

    RT_ASSERT(int_rx->data_ptr != RT_NULL);

    /* Set status */
    leuart->state |= LEUART_STATE_RX_BUSY;

    /* save into rx buffer */
    while (leuart->leuart_device->STATUS & LEUART_STATUS_RXDATAV)
    {
        rt_base_t level;

        /* disable interrupt */
        level = rt_hw_interrupt_disable();

        /* save character */
        int_rx->data_ptr[int_rx->save_index] = \
            (rt_uint8_t)(leuart->leuart_device->RXDATA & 0xFFUL);
        int_rx->save_index ++;
        if (int_rx->save_index >= LEUART_RX_BUFFER_SIZE)
            int_rx->save_index = 0;

        /* if the next position is read index, discard this 'read char' */
        if (int_rx->save_index == int_rx->read_index)
        {
            int_rx->read_index ++;
            if (int_rx->read_index >= LEUART_RX_BUFFER_SIZE)
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
            LEUART_RX_BUFFER_SIZE - int_rx->read_index + int_rx->save_index : \
            int_rx->save_index - int_rx->read_index;

        dev->rx_indicate(dev, rx_length);
    }
}

/***************************************************************************//**
 * @brief
 *  DMA for LEUART TX interrupt handler
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *  Pointer to device descriptor
 ******************************************************************************/
void rt_hw_leuart_dma_tx_isr(rt_device_t dev)
{
    /* DMA mode receive */
    struct efm32_leuart_device_t    *leuart;
    struct efm32_leuart_dma_mode_t  *dma_tx;

    RT_ASSERT(dev->flag & RT_DEVICE_FLAG_DMA_TX);

    leuart = (struct efm32_leuart_device_t *)(dev->user_data);
    dma_tx = (struct efm32_leuart_dma_mode_t *)(leuart->tx_mode);

    /* invoke call to notify tx complete */
    if (dev->tx_complete != RT_NULL)
    {
        dev->tx_complete(dev, dma_tx->data_ptr);
    }

    /* Set status */
    leuart->state &= ~(rt_uint32_t)LEUART_STATE_TX_BUSY;
}

/***************************************************************************//**
* @brief
*   Register LEUART device
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
* @param[in] leuart
*   Pointer to LEUART device descriptor
*
* @return
*   Error code
******************************************************************************/
rt_err_t rt_hw_leuart_register(
    rt_device_t     device,
    const char      *name,
    rt_uint32_t     flag,
    struct efm32_leuart_device_t *leuart)
{
    RT_ASSERT(device != RT_NULL);

    if ((flag & RT_DEVICE_FLAG_DMA_RX) ||
        (flag & RT_DEVICE_FLAG_INT_TX))
    {
        RT_ASSERT(0);
    }

    device->type        = RT_Device_Class_Char;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->init        = rt_leuart_init;
    device->open        = rt_leuart_open;
    device->close       = rt_leuart_close;
    device->read        = rt_leuart_read;
    device->write       = rt_leuart_write;
    device->control     = rt_leuart_control;
    device->user_data   = leuart;

    /* register a character device */
    return rt_device_register(device, name, RT_DEVICE_FLAG_RDWR | flag);
}

/***************************************************************************//**
* @brief
*   Initialize the specified LEUART unit
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
*   Pointer to LEUART device
******************************************************************************/
static struct efm32_leuart_device_t *rt_hw_leuart_unit_init(
    rt_device_t device,
    rt_uint8_t  unitNumber,
    rt_uint8_t  location,
    rt_uint32_t flag,
    rt_uint32_t dmaChannel,
    rt_uint8_t  config)
{
    struct efm32_leuart_device_t    *leuart;
    struct efm32_leuart_dma_mode_t  *dma_mode;
    DMA_CB_TypeDef                  *callback;
    CMU_Clock_TypeDef               leuartClock;
    rt_uint32_t                     txDmaSelect;
    GPIO_Port_TypeDef               port_tx, port_rx, port_clk, port_cs;
    rt_uint32_t                     pin_tx, pin_rx, pin_clk, pin_cs;
    LEUART_Init_TypeDef             init = LEUART_INIT_DEFAULT;
    efm32_irq_hook_init_t           hook;

    do
    {
        /* Allocate device */
        leuart = rt_malloc(sizeof(struct efm32_leuart_device_t));
        if (leuart == RT_NULL)
        {
            leuart_debug("LEUART%d err: no mem\n", unitNumber);
            break;
        }
        leuart->counter = 0;
        leuart->unit    = unitNumber;
        leuart->state   = config;
        leuart->tx_mode = RT_NULL;
        leuart->rx_mode = RT_NULL;

        /* Allocate TX */
        dma_mode = RT_NULL;
        if (flag & RT_DEVICE_FLAG_DMA_TX)
        {
            leuart->tx_mode = dma_mode = rt_malloc(sizeof(struct efm32_leuart_dma_mode_t));
            if (dma_mode == RT_NULL)
            {
                leuart_debug("LEUART%d err: no mem for DMA TX\n", unitNumber);
                break;
            }
            dma_mode->dma_channel = dmaChannel;
        }

        /* Allocate RX */
        if (flag & RT_DEVICE_FLAG_INT_RX)
        {
            leuart->rx_mode = rt_malloc(sizeof(struct efm32_leuart_int_mode_t));
            if (leuart->rx_mode == RT_NULL)
            {
                leuart_debug("LEUART%d err: no mem for INT RX\n, unitNumber");
                break;
            }
        }

        /* Initialization */
        if (unitNumber >= LEUART_COUNT)
        {
            break;
        }
        switch (unitNumber)
        {
        case 0:
            leuart->leuart_device    = LEUART0;
            leuartClock             = (CMU_Clock_TypeDef)cmuClock_LEUART0;
            txDmaSelect             = DMAREQ_LEUART0_TXBL;
            port_tx                 = AF_LEUART0_TX_PORT(location);
            pin_tx                  = AF_LEUART0_TX_PIN(location);
            port_rx                 = AF_LEUART0_RX_PORT(location);
            pin_rx                  = AF_LEUART0_RX_PIN(location);
            break;
#if (LEUART_COUNT > 1)
        case 1:
            leuart->leuart_device    = LEUART1;
            leuartClock             = (CMU_Clock_TypeDef)cmuClock_LEUART1;
            txDmaSelect             = DMAREQ_LEUART1_TXBL;
            port_tx                 = AF_LEUART1_TX_PORT(location);
            pin_tx                  = AF_LEUART1_TX_PIN(location);
            port_rx                 = AF_LEUART1_RX_PORT(location);
            pin_rx                  = AF_LEUART1_RX_PIN(location);
            break;
#endif
        default:
            break;
        }

        /* Do not prescale clock */
        CMU_ClockDivSet(leuartClock, cmuClkDiv_1);

        /* Enable LEUART clock */
        CMU_ClockEnable(leuartClock, true);

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

        /* Config interrupt and NVIC */
        if (flag & RT_DEVICE_FLAG_INT_RX)
        {
            hook.type       = efm32_irq_type_leuart;
            hook.unit       = unitNumber;
            hook.cbFunc     = rt_hw_leuart_rx_isr;
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
            hook.cbFunc         = rt_hw_leuart_dma_tx_isr;
            hook.userPtr        = device;
            efm32_irq_hook_register(&hook);

            callback = (DMA_CB_TypeDef *)rt_malloc(sizeof(DMA_CB_TypeDef));
            if (callback == RT_NULL)
            {
                leuart_debug("LEUART%d err: no mem for callback\n", unitNumber);
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

        /* Init specified LEUART unit */
        LEUART_Init(leuart->leuart_device, &init);

        /* Enable RX and TX pins and set location */
        leuart->leuart_device->ROUTE = LEUART_ROUTE_RXPEN | LEUART_ROUTE_TXPEN | \
                        (location << _LEUART_ROUTE_LOCATION_SHIFT);

        /* Clear RX/TX buffers */
        leuart->leuart_device->CMD = LEUART_CMD_CLEARRX | LEUART_CMD_CLEARTX;

        return leuart;
    } while(0);

    if (leuart->rx_mode)
    {
        rt_free(leuart->rx_mode);
    }
    if (leuart->tx_mode)
    {
        rt_free(leuart->tx_mode);
    }
    if (leuart)
    {
        rt_free(leuart);
    }
    if (callback)
    {
        rt_free(leuart);
    }

    leuart_debug("LEUART%d err: init failed!\n", unitNumber);
    return RT_NULL;
}

/***************************************************************************//**
* @brief
*   Initialize all LEUART module related hardware and register LEUART device to
* kernel
*
* @details
*
* @note
******************************************************************************/
void rt_hw_leuart_init(void)
{
    struct efm32_leuart_device_t    *leuart;
    rt_uint32_t                     flag;
    rt_uint8_t                      config;

    do
    {
#ifdef RT_USING_LEUART0
        config = 0;
        flag = RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX;

 #if (RT_CONSOLE_DEVICE == EFM_LEUART0)
        config |= LEUART_STATE_CONSOLE;
        flag |= RT_DEVICE_FLAG_STREAM;
 #endif

 #ifdef RT_LEUART0_USING_DMA
        RT_ASSERT(RT_LEUART0_USING_DMA < DMA_CHAN_COUNT);
        flag |= RT_DEVICE_FLAG_DMA_TX;
 #else
       #define RT_LEUART0_USING_DMA EFM32_NO_DMA
 #endif

        /* Initialize and Register leuart0 */
        if ((leuart = rt_hw_leuart_unit_init(
            &leuart0_device,
            0,
            RT_USING_LEUART0,
            flag,
            RT_LEUART0_USING_DMA,
            config)) != RT_NULL)
        {
            rt_hw_leuart_register(&leuart0_device, RT_LEUART0_NAME, flag, leuart);
        }
        else
        {
            break;
        }
        /* Initialize lock for leuart0 */
        leuart->lock = &leuart0_lock;
        if (rt_sem_init(leuart->lock, RT_LEUART0_NAME, 1, RT_IPC_FLAG_FIFO) != RT_EOK)
        {
            break;
        }
#endif

#if ((LEUART_COUNT > 1) && defined(RT_USING_LEUART1))
        config = 0;
        flag = RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX;

 #if (RT_CONSOLE_DEVICE == EFM_LEUART1)
        config |= LEUART_STATE_CONSOLE;
        flag |= RT_DEVICE_FLAG_STREAM;
 #endif

 #ifdef RT_LEUART1_USING_DMA
        RT_ASSERT(RT_LEUART1_USING_DMA < DMA_CHAN_COUNT);
        flag |= RT_DEVICE_FLAG_DMA_TX;
 #else
       #define RT_LEUART1_USING_DMA EFM32_NO_DMA
 #endif

        /* Initialize and Register leuart1 */
        if ((leuart = rt_hw_leuart_unit_init(
            &leuart1_device,
            1,
            RT_USING_LEUART1,
            flag,
            RT_LEUART1_USING_DMA,
            config)) != RT_NULL)
        {
            rt_hw_leuart_register(&leuart1_device, RT_LEUART1_NAME, flag, leuart);
        }
        else
        {
            break;
        }
        /* Initialize lock for leuart1 */
        leuart->lock = &leuart1_lock;
        if (rt_sem_init(leuart->lock, RT_LEUART1_NAME, 1, RT_IPC_FLAG_FIFO) != RT_EOK)
        {
            break;
        }
#endif

        leuart_debug("LEUART: H/W init OK!\n");
        return;
    } while (0);

    rt_kprintf("LEUART: H/W init failed!\n");
}

#endif /* (defined(RT_USING_LEUART0) || defined(RT_USING_LEUART1)) */
/***************************************************************************//**
 * @}
 ******************************************************************************/
