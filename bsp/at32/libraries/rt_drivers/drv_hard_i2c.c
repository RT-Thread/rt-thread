/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-31     shelton      first version
 */

#include "drv_common.h"
#include "drv_hard_i2c.h"
#include "drv_config.h"
#include <string.h>

#if defined(BSP_USING_HARD_I2C1) || defined(BSP_USING_HARD_I2C2) || \
    defined(BSP_USING_HARD_I2C3)

//#define DRV_DEBUG
#define LOG_TAG             "drv.hwi2c"
#include <drv_log.h>

enum
{
#ifdef BSP_USING_HARD_I2C1
    I2C1_INDEX,
#endif
#ifdef BSP_USING_HARD_I2C2
    I2C2_INDEX,
#endif
#ifdef BSP_USING_HARD_I2C3
    I2C3_INDEX,
#endif
};

static struct at32_i2c_handle i2c_handle[] = {
#ifdef BSP_USING_HARD_I2C1
    I2C1_CONFIG,
#endif

#ifdef BSP_USING_HARD_I2C2
    I2C2_CONFIG,
#endif

#ifdef BSP_USING_HARD_I2C3
    I2C3_CONFIG,
#endif
};

static struct at32_i2c i2cs[sizeof(i2c_handle) / sizeof(i2c_handle[0])] = {0};

/* private rt-thread i2c ops function */
static rt_ssize_t master_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num);
static struct rt_i2c_bus_device_ops at32_i2c_ops =
{
    master_xfer,
    RT_NULL,
    RT_NULL
};

static rt_err_t at32_i2c_configure(struct rt_i2c_bus_device *bus)
{
    RT_ASSERT(RT_NULL != bus);
    struct at32_i2c *instance = rt_container_of(bus, struct at32_i2c, i2c_bus);

    at32_msp_i2c_init(instance->handle->i2c_x);

#if defined (SOC_SERIES_AT32F403A) || defined (SOC_SERIES_AT32F407)  || \
    defined (SOC_SERIES_AT32F413)  || defined (SOC_SERIES_AT32F415)  || \
    defined (SOC_SERIES_AT32F421)  || defined (SOC_SERIES_AT32A403A)
    i2c_init(instance->handle->i2c_x, I2C_FSMODE_DUTY_2_1, instance->handle->timing);
#endif
#if defined (SOC_SERIES_AT32F402)  || defined (SOC_SERIES_AT32F405) || \
    defined (SOC_SERIES_AT32F423)  || defined (SOC_SERIES_AT32F425) || \
    defined (SOC_SERIES_AT32F435)  || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32A423)  || defined (SOC_SERIES_AT32M412) || \
    defined (SOC_SERIES_AT32M416)
    i2c_init(instance->handle->i2c_x, 0x0F, instance->handle->timing);
#endif
    i2c_own_address1_set(instance->handle->i2c_x, I2C_ADDRESS_MODE_7BIT, HWI2C_OWN_ADDRESS);

    nvic_irq_enable(instance->handle->ev_irqn, 0, 0);
    nvic_irq_enable(instance->handle->er_irqn, 0, 0);

    i2c_enable(instance->handle->i2c_x, TRUE);

    return RT_EOK;
}

static void i2c_dma_config(struct at32_i2c_handle *handle, rt_uint8_t *buffer, rt_uint32_t size)
{
    struct dma_config *dma = RT_NULL;

    if(handle->comm.mode == I2C_DMA_MA_TX)
    {
        dma = handle->dma_tx;
#if defined (SOC_SERIES_AT32F403A) || defined (SOC_SERIES_AT32F407)  || \
    defined (SOC_SERIES_AT32F413)  || defined (SOC_SERIES_AT32F415)  || \
    defined (SOC_SERIES_AT32F421)  || defined (SOC_SERIES_AT32A403A)
        dma->dma_channel->paddr = (rt_uint32_t)&(handle->i2c_x->dt);
#endif
#if defined (SOC_SERIES_AT32F402)  || defined (SOC_SERIES_AT32F405) || \
    defined (SOC_SERIES_AT32F423)  || defined (SOC_SERIES_AT32F425) || \
    defined (SOC_SERIES_AT32F435)  || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32A423)  || defined (SOC_SERIES_AT32M412) || \
    defined (SOC_SERIES_AT32M416)
        dma->dma_channel->paddr = (rt_uint32_t)&(handle->i2c_x->txdt);
#endif
    }
    else if(handle->comm.mode == I2C_DMA_MA_RX)
    {
        dma = handle->dma_rx;
#if defined (SOC_SERIES_AT32F403A) || defined (SOC_SERIES_AT32F407)  || \
    defined (SOC_SERIES_AT32F413)  || defined (SOC_SERIES_AT32F415)  || \
    defined (SOC_SERIES_AT32F421)  || defined (SOC_SERIES_AT32A403A)
        dma->dma_channel->paddr = (rt_uint32_t)&(handle->i2c_x->dt);
#endif
#if defined (SOC_SERIES_AT32F402)  || defined (SOC_SERIES_AT32F405) || \
    defined (SOC_SERIES_AT32F423)  || defined (SOC_SERIES_AT32F425) || \
    defined (SOC_SERIES_AT32F435)  || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32A423)  || defined (SOC_SERIES_AT32M412) || \
    defined (SOC_SERIES_AT32M416)
        dma->dma_channel->paddr = (rt_uint32_t)&(handle->i2c_x->rxdt);
#endif
    }

    dma->dma_channel->dtcnt = size;
    dma->dma_channel->maddr = (rt_uint32_t)buffer;

    /* enable transmit complete interrupt */
    dma_interrupt_enable(dma->dma_channel, DMA_FDT_INT, TRUE);

    /* mark dma flag */
    dma->dma_done = RT_FALSE;
    /* enable dma channel */
    dma_channel_enable(dma->dma_channel, TRUE);
}

#if defined (SOC_SERIES_AT32F402)  || defined (SOC_SERIES_AT32F405) || \
    defined (SOC_SERIES_AT32F423)  || defined (SOC_SERIES_AT32F425) || \
    defined (SOC_SERIES_AT32F435)  || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32A423)  || defined (SOC_SERIES_AT32M412) || \
    defined (SOC_SERIES_AT32M416)
void i2c_refresh_txdt_register(i2c_type *i2c_x)
{
    /* clear tdis flag */
    if (i2c_flag_get(i2c_x, I2C_TDIS_FLAG) != RESET)
    {
        i2c_x->txdt = 0x00;
    }
    /* refresh txdt register*/
    if (i2c_flag_get(i2c_x, I2C_TDBE_FLAG) == RESET)
    {
        i2c_x->sts_bit.tdbe = 1;
    }
}

void i2c_reset_ctrl2_register(i2c_type *i2c_x)
{
    i2c_x->ctrl2_bit.saddr = 0;
    i2c_x->ctrl2_bit.readh10 = 0;
    i2c_x->ctrl2_bit.cnt = 0;
    i2c_x->ctrl2_bit.rlden = 0;
    i2c_x->ctrl2_bit.dir = 0;
}
#endif

i2c_status_type i2c_wait_end(struct at32_i2c_handle *handle, uint32_t timeout)
{
    while(handle->comm.status != I2C_END)
    {
        /* check timeout */
        if((timeout--) == 0)
        {
            return I2C_ERR_TIMEOUT;
        }
    }

    if(handle->comm.error_code != I2C_OK)
    {
        return handle->comm.error_code;
    }
    else
    {
        return I2C_OK;
    }
}

i2c_status_type i2c_wait_flag(struct at32_i2c_handle *handle, uint32_t flag, uint32_t event_check, uint32_t timeout)
{
    if(flag == I2C_BUSYF_FLAG)
    {
        while(i2c_flag_get(handle->i2c_x, flag) != RESET)
        {
            /* check timeout */
            if((timeout--) == 0)
            {
                handle->comm.error_code = I2C_ERR_TIMEOUT;

                return I2C_ERR_TIMEOUT;
            }
        }
    }
    else
    {
        while(i2c_flag_get(handle->i2c_x, flag) == RESET)
        {
            /* check the ack fail flag */
            if(event_check & I2C_EVENT_CHECK_ACKFAIL)
            {
                if(i2c_flag_get(handle->i2c_x, I2C_ACKFAIL_FLAG) != RESET)
                {
#if defined (SOC_SERIES_AT32F403A) || defined (SOC_SERIES_AT32F407)  || \
    defined (SOC_SERIES_AT32F413)  || defined (SOC_SERIES_AT32F415)  || \
    defined (SOC_SERIES_AT32F421)  || defined (SOC_SERIES_AT32A403A)
                    /* generate stop condtion */
                    i2c_stop_generate(handle->i2c_x);
#endif
                    /* clear ack fail flag */
                    i2c_flag_clear(handle->i2c_x, I2C_ACKFAIL_FLAG);

                    handle->comm.error_code = I2C_ERR_ACKFAIL;

                    return I2C_ERR_ACKFAIL;
                }
            }

            /* check the stop flag */
            if(event_check & I2C_EVENT_CHECK_STOP)
            {
                if(i2c_flag_get(handle->i2c_x, I2C_STOPF_FLAG) != RESET)
                {
                    /* clear stop flag */
                    i2c_flag_clear(handle->i2c_x, I2C_STOPF_FLAG);
#if defined (SOC_SERIES_AT32F402)  || defined (SOC_SERIES_AT32F405) || \
    defined (SOC_SERIES_AT32F423)  || defined (SOC_SERIES_AT32F425) || \
    defined (SOC_SERIES_AT32F435)  || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32A423)  || defined (SOC_SERIES_AT32M412) || \
    defined (SOC_SERIES_AT32M416)
                    i2c_reset_ctrl2_register(handle->i2c_x);
#endif
                    handle->comm.error_code = I2C_ERR_STOP;

                    return I2C_ERR_STOP;
                }
            }

            /* check timeout */
            if((timeout--) == 0)
            {
                handle->comm.error_code = I2C_ERR_TIMEOUT;

                return I2C_ERR_TIMEOUT;
            }
        }
    }

    return I2C_OK;
}

#if defined (SOC_SERIES_AT32F403A) || defined (SOC_SERIES_AT32F407)  || \
    defined (SOC_SERIES_AT32F413)  || defined (SOC_SERIES_AT32F415)  || \
    defined (SOC_SERIES_AT32F421)  || defined (SOC_SERIES_AT32A403A)
i2c_status_type i2c_master_write_addr(struct at32_i2c_handle *handle, uint16_t address, uint32_t timeout)
{
    /* generate start condtion */
    i2c_start_generate(handle->i2c_x);

    /* wait for the start flag to be set */
    if(i2c_wait_flag(handle, I2C_STARTF_FLAG, I2C_EVENT_CHECK_NONE, timeout) != I2C_OK)
    {
        handle->comm.error_code = I2C_ERR_START;

        return I2C_ERR_START;
    }

    if(handle->i2c_x->oaddr1_bit.addr1mode == I2C_ADDRESS_MODE_7BIT)
    {
        /* send slave address */
        i2c_7bit_address_send(handle->i2c_x, address, I2C_DIRECTION_TRANSMIT);
    }
    else
    {
        /* send slave 10-bit address header */
        i2c_data_send(handle->i2c_x, (uint8_t)((address & 0x0300) >> 7) | 0xF0);

        /* wait for the addrh flag to be set */
        if(i2c_wait_flag(handle, I2C_ADDRHF_FLAG, I2C_EVENT_CHECK_ACKFAIL, timeout) != I2C_OK)
        {
            handle->comm.error_code = I2C_ERR_ADDR10;

            return I2C_ERR_ADDR10;
        }

        /* send slave address */
        i2c_data_send(handle->i2c_x, (uint8_t)(address & 0x00FF));
    }

    /* wait for the addr7 flag to be set */
    if(i2c_wait_flag(handle, I2C_ADDR7F_FLAG, I2C_EVENT_CHECK_ACKFAIL, timeout) != I2C_OK)
    {
        handle->comm.error_code = I2C_ERR_ADDR;

        return I2C_ERR_ADDR;
    }

    return I2C_OK;
}

i2c_status_type i2c_master_read_addr(struct at32_i2c_handle *handle, uint16_t address, uint32_t timeout)
{
    /* enable ack */
    i2c_ack_enable(handle->i2c_x, TRUE);

    /* generate start condtion */
    i2c_start_generate(handle->i2c_x);

    /* wait for the start flag to be set */
    if(i2c_wait_flag(handle, I2C_STARTF_FLAG, I2C_EVENT_CHECK_NONE, timeout) != I2C_OK)
    {
        handle->comm.error_code = I2C_ERR_START;

        return I2C_ERR_START;
    }

    if(handle->i2c_x->oaddr1_bit.addr1mode == I2C_ADDRESS_MODE_7BIT)
    {
        /* send slave address */
        i2c_7bit_address_send(handle->i2c_x, address, I2C_DIRECTION_RECEIVE);
    }
    else
    {
        /* send slave 10-bit address header */
        i2c_data_send(handle->i2c_x, (uint8_t)((address & 0x0300) >> 7) | 0xF0);

        /* wait for the addrh flag to be set */
        if(i2c_wait_flag(handle, I2C_ADDRHF_FLAG, I2C_EVENT_CHECK_ACKFAIL, timeout) != I2C_OK)
        {
            handle->comm.error_code = I2C_ERR_ADDR10;

            return I2C_ERR_ADDR10;
        }

        /* send slave address */
        i2c_data_send(handle->i2c_x, (uint8_t)(address & 0x00FF));

        /* wait for the addr7 flag to be set */
        if(i2c_wait_flag(handle, I2C_ADDR7F_FLAG, I2C_EVENT_CHECK_ACKFAIL, timeout) != I2C_OK)
        {
            handle->comm.error_code = I2C_ERR_ADDR;

            return I2C_ERR_ADDR;
        }

        /* clear addr flag */
        i2c_flag_clear(handle->i2c_x, I2C_ADDR7F_FLAG);

        /* generate restart condtion */
        i2c_start_generate(handle->i2c_x);

        /* wait for the start flag to be set */
        if(i2c_wait_flag(handle, I2C_STARTF_FLAG, I2C_EVENT_CHECK_NONE, timeout) != I2C_OK)
        {
            handle->comm.error_code = I2C_ERR_START;

            return I2C_ERR_START;
        }

        /* send slave 10-bit address header */
        i2c_data_send(handle->i2c_x, (uint8_t)((address & 0x0300) >> 7) | 0xF1);
    }

    /* wait for the addr7 flag to be set */
    if(i2c_wait_flag(handle, I2C_ADDR7F_FLAG, I2C_EVENT_CHECK_ACKFAIL, timeout) != I2C_OK)
    {
        handle->comm.error_code = I2C_ERR_ADDR;

        return I2C_ERR_ADDR;
    }

    return I2C_OK;
}

i2c_status_type i2c_master_transmit_int(struct at32_i2c_handle *handle, uint16_t address, uint8_t *pdata, uint16_t size, uint32_t timeout)
{
    /* initialization parameters */
    handle->comm.mode = I2C_INT_MA_TX;
    handle->comm.status = I2C_START;

    handle->comm.pbuff = pdata;
    handle->comm.pcount = size;

    handle->comm.timeout = timeout;
    handle->comm.error_code = I2C_OK;

    /* wait for the busy flag to be reset */
    if(i2c_wait_flag(handle, I2C_BUSYF_FLAG, I2C_EVENT_CHECK_NONE, timeout) != I2C_OK)
    {
        return I2C_ERR_STEP_1;
    }

    /* ack acts on the current byte */
    i2c_master_receive_ack_set(handle->i2c_x, I2C_MASTER_ACK_CURRENT);

    /* send slave address */
    if(i2c_master_write_addr(handle, address, timeout) != I2C_OK)
    {
        /* generate stop condtion */
        i2c_stop_generate(handle->i2c_x);

        return I2C_ERR_STEP_2;
    }

    /* clear addr flag */
    i2c_flag_clear(handle->i2c_x, I2C_ADDR7F_FLAG);

    /* enable interrupt */
    i2c_interrupt_enable(handle->i2c_x, I2C_EVT_INT | I2C_DATA_INT | I2C_ERR_INT, TRUE);

    return I2C_OK;
}

i2c_status_type i2c_master_receive_int(struct at32_i2c_handle *handle, uint16_t address, uint8_t *pdata, uint16_t size, uint32_t timeout)
{
    /* initialization parameters */
    handle->comm.mode = I2C_INT_MA_RX;
    handle->comm.status = I2C_START;

    handle->comm.pbuff = pdata;
    handle->comm.pcount = size;

    handle->comm.timeout = timeout;
    handle->comm.error_code = I2C_OK;

    /* wait for the busy flag to be reset */
    if(i2c_wait_flag(handle, I2C_BUSYF_FLAG, I2C_EVENT_CHECK_NONE, timeout) != I2C_OK)
    {
        return I2C_ERR_STEP_1;
    }

    /* ack acts on the current byte */
    i2c_master_receive_ack_set(handle->i2c_x, I2C_MASTER_ACK_CURRENT);

    /* enable ack */
    i2c_ack_enable(handle->i2c_x, TRUE);

    /* send slave address */
    if(i2c_master_read_addr(handle, address, timeout) != I2C_OK)
    {
        /* generate stop condtion */
        i2c_stop_generate(handle->i2c_x);

        return I2C_ERR_STEP_2;
    }

    if(handle->comm.pcount == 1)
    {
        /* disable ack */
        i2c_ack_enable(handle->i2c_x, FALSE);

        /* clear addr flag */
        i2c_flag_clear(handle->i2c_x, I2C_ADDR7F_FLAG);

        /* generate stop condtion */
        i2c_stop_generate(handle->i2c_x);
    }
    else if(handle->comm.pcount == 2)
    {
        /* ack acts on the next byte */
        i2c_master_receive_ack_set(handle->i2c_x, I2C_MASTER_ACK_NEXT);

        /* clear addr flag */
        i2c_flag_clear(handle->i2c_x, I2C_ADDR7F_FLAG);

        /* disable ack */
        i2c_ack_enable(handle->i2c_x, FALSE);
    }
    else
    {
        /* enable ack */
        i2c_ack_enable(handle->i2c_x, TRUE);

        /* clear addr flag */
        i2c_flag_clear(handle->i2c_x, I2C_ADDR7F_FLAG);
    }

    /* enable interrupt */
    i2c_interrupt_enable(handle->i2c_x, I2C_EVT_INT | I2C_DATA_INT | I2C_ERR_INT, TRUE);

    return I2C_OK;
}

i2c_status_type i2c_master_transmit_dma(struct at32_i2c_handle *handle, uint16_t address, uint8_t *pdata, uint16_t size, uint32_t timeout)
{
    /* initialization parameters */
    handle->comm.mode = I2C_DMA_MA_TX;
    handle->comm.status = I2C_START;

    handle->comm.pbuff = pdata;
    handle->comm.pcount = size;

    handle->comm.timeout = timeout;
    handle->comm.error_code = I2C_OK;

    /* wait for the busy flag to be reset */
    if(i2c_wait_flag(handle, I2C_BUSYF_FLAG, I2C_EVENT_CHECK_NONE, timeout) != I2C_OK)
    {
        return I2C_ERR_STEP_1;
    }

    /* ack acts on the current byte */
    i2c_master_receive_ack_set(handle->i2c_x, I2C_MASTER_ACK_CURRENT);

    /* disable dma request */
    i2c_dma_enable(handle->i2c_x, FALSE);

    /* configure the dma channel */
    i2c_dma_config(handle, pdata, size);

    /* send slave address */
    if(i2c_master_write_addr(handle, address, timeout) != I2C_OK)
    {
        /* generate stop condtion */
        i2c_stop_generate(handle->i2c_x);

        return I2C_ERR_STEP_2;
    }

    /* clear addr flag */
    i2c_flag_clear(handle->i2c_x, I2C_ADDR7F_FLAG);

    /* enable dma request */
    i2c_dma_enable(handle->i2c_x, TRUE);

    return I2C_OK;
}

i2c_status_type i2c_master_receive_dma(struct at32_i2c_handle *handle, uint16_t address, uint8_t *pdata, uint16_t size, uint32_t timeout)
{
    /* initialization parameters */
    handle->comm.mode = I2C_DMA_MA_RX;
    handle->comm.status = I2C_START;

    handle->comm.pbuff = pdata;
    handle->comm.pcount = size;

    handle->comm.timeout = timeout;
    handle->comm.error_code = I2C_OK;

    /* wait for the busy flag to be reset */
    if(i2c_wait_flag(handle, I2C_BUSYF_FLAG, I2C_EVENT_CHECK_NONE, timeout) != I2C_OK)
    {
        return I2C_ERR_STEP_1;
    }

    /* ack acts on the current byte */
    i2c_master_receive_ack_set(handle->i2c_x, I2C_MASTER_ACK_CURRENT);

    /* enable ack */
    i2c_ack_enable(handle->i2c_x, TRUE);

    /* disable dma request */
    i2c_dma_enable(handle->i2c_x, FALSE);

    /* configure the dma channel */
    i2c_dma_config(handle, pdata, size);

    /* send slave address */
    if(i2c_master_read_addr(handle, address, timeout) != I2C_OK)
    {
        /* generate stop condtion */
        i2c_stop_generate(handle->i2c_x);

        return I2C_ERR_STEP_2;
    }

    if(size == 1)
    {
        /* clear addr flag */
        i2c_flag_clear(handle->i2c_x, I2C_ADDR7F_FLAG);

        /* disable ack */
        i2c_ack_enable(handle->i2c_x, FALSE);

        /* generate stop condtion */
        i2c_stop_generate(handle->i2c_x);

        /* enable dma request */
        i2c_dma_enable(handle->i2c_x, TRUE);
    }
    else
    {
        /* enable dma end transfer */
        i2c_dma_end_transfer_set(handle->i2c_x, TRUE);

        /* enable dma request */
        i2c_dma_enable(handle->i2c_x, TRUE);

        /* clear addr flag */
        i2c_flag_clear(handle->i2c_x, I2C_ADDR7F_FLAG);
    }

    return I2C_OK;
}


void i2c_master_tx_isr_int(struct at32_i2c_handle *handle)
{
    /* step 1: transfer data */
    if(i2c_flag_get(handle->i2c_x, I2C_TDBE_FLAG) != RESET)
    {
        if(handle->comm.pcount == 0)
        {
            rt_completion_done(&handle->completion);

            /* transfer complete */
            handle->comm.status = I2C_END;

            /* disable interrupt */
            i2c_interrupt_enable(handle->i2c_x, I2C_EVT_INT | I2C_DATA_INT | I2C_ERR_INT, FALSE);

            /* generate stop condtion */
            i2c_stop_generate(handle->i2c_x);
        }
        else
        {
            /* write data */
            i2c_data_send(handle->i2c_x, *handle->comm.pbuff++);
            handle->comm.pcount--;
        }
    }
}

void i2c_master_rx_isr_int(struct at32_i2c_handle *handle)
{
    if(i2c_flag_get(handle->i2c_x, I2C_TDC_FLAG) != RESET)
    {
        if(handle->comm.pcount == 3)
        {
            /* disable ack */
            i2c_ack_enable(handle->i2c_x, FALSE);

            /* read data */
            (*handle->comm.pbuff++) = i2c_data_receive(handle->i2c_x);
            handle->comm.pcount--;
        }
        else if(handle->comm.pcount == 2)
        {
            /* generate stop condtion */
            i2c_stop_generate(handle->i2c_x);

            /* read data */
            (*handle->comm.pbuff++) = i2c_data_receive(handle->i2c_x);
            handle->comm.pcount--;

            /* read data */
            (*handle->comm.pbuff++) = i2c_data_receive(handle->i2c_x);
            handle->comm.pcount--;

            /* transfer complete */
            rt_completion_done(&handle->completion);
            handle->comm.status = I2C_END;

            /* disable interrupt */
            i2c_interrupt_enable(handle->i2c_x, I2C_EVT_INT | I2C_DATA_INT | I2C_ERR_INT, FALSE);
        }
        else
        {
            /* read data */
            (*handle->comm.pbuff++) = i2c_data_receive(handle->i2c_x);
            handle->comm.pcount--;
        }
    }
    else if(i2c_flag_get(handle->i2c_x, I2C_RDBF_FLAG) != RESET)
    {
        if(handle->comm.pcount > 3)
        {
            /* read data */
            (*handle->comm.pbuff++) = i2c_data_receive(handle->i2c_x);
            handle->comm.pcount--;
        }
        else if((handle->comm.pcount == 3) || (handle->comm.pcount == 2))
        {
            /* disable rdbf interrupt */
            i2c_interrupt_enable(handle->i2c_x, I2C_DATA_INT, FALSE);
        }
        else
        {
            /* read data */
            (*handle->comm.pbuff++) = i2c_data_receive(handle->i2c_x);
            handle->comm.pcount--;

            /* transfer complete */
            rt_completion_done(&handle->completion);
            handle->comm.status = I2C_END;

            /* disable interrupt */
            i2c_interrupt_enable(handle->i2c_x, I2C_EVT_INT | I2C_DATA_INT | I2C_ERR_INT, FALSE);
        }
    }
}

void i2c_master_tx_isr_dma(struct at32_i2c_handle *handle)
{
    /* tdc interrupt */
    if(i2c_flag_get(handle->i2c_x, I2C_TDC_FLAG) != RESET)
    {
        rt_completion_done(&handle->completion);

        /* generate stop condtion */
        i2c_stop_generate(handle->i2c_x);

        /* disable evt interrupt */
        i2c_interrupt_enable(handle->i2c_x, I2C_EVT_INT, FALSE);

        /* transfer complete */
        handle->comm.status = I2C_END;
    }
}

void i2c_evt_isr(struct at32_i2c_handle *handle)
{
    switch(handle->comm.mode)
    {
        case I2C_INT_MA_TX:
            i2c_master_tx_isr_int(handle);
            break;
        case I2C_INT_MA_RX:
            i2c_master_rx_isr_int(handle);
            break;
        case I2C_DMA_MA_TX:
            i2c_master_tx_isr_dma(handle);
            break;
        default:
            break;
    }
}
#endif

#if defined (SOC_SERIES_AT32F402)  || defined (SOC_SERIES_AT32F405) || \
    defined (SOC_SERIES_AT32F423)  || defined (SOC_SERIES_AT32F425) || \
    defined (SOC_SERIES_AT32F435)  || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32A423)  || defined (SOC_SERIES_AT32M412) || \
    defined (SOC_SERIES_AT32M416)
void i2c_start_transfer(struct at32_i2c_handle *handle, uint16_t address, i2c_start_mode_type start)
{
    if (handle->comm.pcount > MAX_TRANSFER_CNT)
    {
        handle->comm.psize = MAX_TRANSFER_CNT;

        i2c_transmit_set(handle->i2c_x, address, handle->comm.psize, I2C_RELOAD_MODE, start);
    }
    else
    {
        handle->comm.psize = handle->comm.pcount;

        i2c_transmit_set(handle->i2c_x, address, handle->comm.psize, I2C_AUTO_STOP_MODE, start);
    }
}

void i2c_start_transfer_dma(struct at32_i2c_handle *handle, uint16_t address, i2c_start_mode_type start)
{
    if (handle->comm.pcount > MAX_TRANSFER_CNT)
    {
        handle->comm.psize = MAX_TRANSFER_CNT;

        /* config dma */
        i2c_dma_config(handle, handle->comm.pbuff, handle->comm.psize);

        i2c_transmit_set(handle->i2c_x, address, handle->comm.psize, I2C_RELOAD_MODE, start);
    }
    else
    {
        handle->comm.psize = handle->comm.pcount;

        /* config dma */
        i2c_dma_config(handle, handle->comm.pbuff, handle->comm.psize);

        i2c_transmit_set(handle->i2c_x, address, handle->comm.psize, I2C_AUTO_STOP_MODE, start);
    }
}

i2c_status_type i2c_master_transmit_int(struct at32_i2c_handle *handle, uint16_t address, uint8_t *pdata, uint16_t size, uint32_t timeout)
{
    /* initialization parameters */
    handle->comm.mode = I2C_INT_MA_TX;
    handle->comm.status = I2C_START;

    handle->comm.pbuff = pdata;
    handle->comm.pcount = size;

    handle->comm.error_code = I2C_OK;

    /* wait for the busy flag to be reset */
    if (i2c_wait_flag(handle, I2C_BUSYF_FLAG, I2C_EVENT_CHECK_NONE, timeout) != I2C_OK)
    {
        return I2C_ERR_STEP_1;
    }

    /* start transfer */
    i2c_start_transfer(handle, address, I2C_GEN_START_WRITE);

    /* enable interrupt */
    i2c_interrupt_enable(handle->i2c_x, I2C_ERR_INT | I2C_TDC_INT | I2C_STOP_INT | I2C_ACKFIAL_INT | I2C_TD_INT, TRUE);

    return I2C_OK;
}

i2c_status_type i2c_master_receive_int(struct at32_i2c_handle *handle, uint16_t address, uint8_t *pdata, uint16_t size, uint32_t timeout)
{
    /* initialization parameters */
    handle->comm.mode = I2C_INT_MA_RX;
    handle->comm.status = I2C_START;

    handle->comm.pbuff = pdata;
    handle->comm.pcount = size;

    handle->comm.error_code = I2C_OK;

    /* wait for the busy flag to be reset */
    if (i2c_wait_flag(handle, I2C_BUSYF_FLAG, I2C_EVENT_CHECK_NONE, timeout) != I2C_OK)
    {
        return I2C_ERR_STEP_1;
    }

    /* start transfer */
    i2c_start_transfer(handle, address, I2C_GEN_START_READ);

    /* enable interrupt */
    i2c_interrupt_enable(handle->i2c_x, I2C_ERR_INT | I2C_TDC_INT | I2C_STOP_INT | I2C_ACKFIAL_INT | I2C_RD_INT, TRUE);

    return I2C_OK;
}

i2c_status_type i2c_master_transmit_dma(struct at32_i2c_handle *handle, uint16_t address, uint8_t *pdata, uint16_t size, uint32_t timeout)
{
    /* initialization parameters */
    handle->comm.mode = I2C_DMA_MA_TX;
    handle->comm.status = I2C_START;

    handle->comm.pbuff = pdata;
    handle->comm.pcount = size;

    handle->comm.error_code = I2C_OK;

    /* wait for the busy flag to be reset */
    if(i2c_wait_flag(handle, I2C_BUSYF_FLAG, I2C_EVENT_CHECK_NONE, timeout) != I2C_OK)
    {
        return I2C_ERR_STEP_1;
    }

    /* disable dma request */
    i2c_dma_enable(handle->i2c_x, I2C_DMA_REQUEST_TX, FALSE);

    /* start transfer */
    i2c_start_transfer_dma(handle, address, I2C_GEN_START_WRITE);

    /* enable i2c interrupt */
    i2c_interrupt_enable(handle->i2c_x, I2C_ERR_INT | I2C_ACKFIAL_INT, TRUE);

    /* enable dma request */
    i2c_dma_enable(handle->i2c_x, I2C_DMA_REQUEST_TX, TRUE);

    return I2C_OK;
}

i2c_status_type i2c_master_receive_dma(struct at32_i2c_handle *handle, uint16_t address, uint8_t *pdata, uint16_t size, uint32_t timeout)
{
    /* initialization parameters */
    handle->comm.mode   = I2C_DMA_MA_RX;
    handle->comm.status = I2C_START;

    handle->comm.pbuff  = pdata;
    handle->comm.pcount = size;

    handle->comm.error_code = I2C_OK;

    /* wait for the busy flag to be reset */
    if(i2c_wait_flag(handle, I2C_BUSYF_FLAG, I2C_EVENT_CHECK_NONE, timeout) != I2C_OK)
    {
        return I2C_ERR_STEP_1;
    }

    /* disable dma request */
    i2c_dma_enable(handle->i2c_x, I2C_DMA_REQUEST_RX, FALSE);

    /* start transfer */
    i2c_start_transfer_dma(handle, address, I2C_GEN_START_READ);

    /* enable i2c interrupt */
    i2c_interrupt_enable(handle->i2c_x, I2C_ERR_INT | I2C_ACKFIAL_INT, TRUE);

    /* enable dma request */
    i2c_dma_enable(handle->i2c_x, I2C_DMA_REQUEST_RX, TRUE);

    return I2C_OK;
}

void i2c_master_isr_int(struct at32_i2c_handle *handle)
{
    if (i2c_flag_get(handle->i2c_x, I2C_ACKFAIL_FLAG) != RESET)
    {
        /* clear ackfail flag */
        i2c_flag_clear(handle->i2c_x, I2C_ACKFAIL_FLAG);

        /* refresh tx register */
        i2c_refresh_txdt_register(handle->i2c_x);

        if(handle->comm.pcount != 0)
        {
            handle->comm.error_code = I2C_ERR_ACKFAIL;
        }
    }
    else if (i2c_flag_get(handle->i2c_x, I2C_TDIS_FLAG) != RESET)
    {
        /* send data */
        i2c_data_send(handle->i2c_x, *handle->comm.pbuff++);
        handle->comm.pcount--;
        handle->comm.psize--;
    }
    else if (i2c_flag_get(handle->i2c_x, I2C_TCRLD_FLAG) != RESET)
    {
        if ((handle->comm.psize == 0) && (handle->comm.pcount != 0))
        {
            /* continue transfer */
            i2c_start_transfer(handle, i2c_transfer_addr_get(handle->i2c_x), I2C_WITHOUT_START);
        }
    }
    else if (i2c_flag_get(handle->i2c_x, I2C_RDBF_FLAG) != RESET)
    {
        /* read data */
        (*handle->comm.pbuff++) = i2c_data_receive(handle->i2c_x);
        handle->comm.pcount--;
        handle->comm.psize--;
    }
    else if (i2c_flag_get(handle->i2c_x, I2C_TDC_FLAG) != RESET)
    {
        if (handle->comm.pcount == 0)
        {
            if (handle->i2c_x->ctrl2_bit.astopen == 0)
            {
                /* generate stop condtion */
                i2c_stop_generate(handle->i2c_x);
            }
        }
    }
    else if (i2c_flag_get(handle->i2c_x, I2C_STOPF_FLAG) != RESET)
    {
        /* clear stop flag */
        i2c_flag_clear(handle->i2c_x, I2C_STOPF_FLAG);

        /* reset ctrl2 register */
        i2c_reset_ctrl2_register(handle->i2c_x);

        if (i2c_flag_get(handle->i2c_x, I2C_ACKFAIL_FLAG) != RESET)
        {
            /* clear ackfail flag */
            i2c_flag_clear(handle->i2c_x, I2C_ACKFAIL_FLAG);
        }

        /* refresh tx dt register */
        i2c_refresh_txdt_register(handle->i2c_x);

        /* disable interrupts */
        i2c_interrupt_enable(handle->i2c_x, I2C_ERR_INT | I2C_TDC_INT | I2C_STOP_INT | I2C_ACKFIAL_INT | I2C_TD_INT | I2C_RD_INT, FALSE);

        /* transfer complete */
        handle->comm.status = I2C_END;
        rt_completion_done(&handle->completion);
    }
}

void i2c_master_isr_dma(struct at32_i2c_handle *handle)
{
    if (i2c_flag_get(handle->i2c_x, I2C_ACKFAIL_FLAG) != RESET)
    {
        /* clear ackfail flag */
        i2c_flag_clear(handle->i2c_x, I2C_ACKFAIL_FLAG);

        /* enable stop interrupt to wait for stop generate stop */
        i2c_interrupt_enable(handle->i2c_x, I2C_STOP_INT, TRUE);

        /* refresh tx dt register */
        i2c_refresh_txdt_register(handle->i2c_x);

        if(handle->comm.pcount != 0)
        {
          handle->comm.error_code = I2C_ERR_ACKFAIL;
        }
    }
    else if (i2c_flag_get(handle->i2c_x, I2C_TCRLD_FLAG) != RESET)
    {
        /* disable tdc interrupt */
        i2c_interrupt_enable(handle->i2c_x, I2C_TDC_INT, FALSE);

        if (handle->comm.pcount != 0)
        {
            /* continue transfer */
            i2c_start_transfer(handle, i2c_transfer_addr_get(handle->i2c_x), I2C_WITHOUT_START);

            /* enable dma request */
            if(handle->comm.mode == I2C_DMA_MA_TX)
                i2c_dma_enable(handle->i2c_x, I2C_DMA_REQUEST_TX, TRUE);
            else if(handle->comm.mode == I2C_DMA_MA_RX)
                i2c_dma_enable(handle->i2c_x, I2C_DMA_REQUEST_RX, TRUE);
        }
    }
    else if (i2c_flag_get(handle->i2c_x, I2C_STOPF_FLAG) != RESET)
    {
        /* clear stop flag */
        i2c_flag_clear(handle->i2c_x, I2C_STOPF_FLAG);

        /* reset ctrl2 register */
        i2c_reset_ctrl2_register(handle->i2c_x);

        if (i2c_flag_get(handle->i2c_x, I2C_ACKFAIL_FLAG) != RESET)
        {
            /* clear ackfail flag */
            i2c_flag_clear(handle->i2c_x, I2C_ACKFAIL_FLAG);
        }

        /* refresh tx dt register */
        i2c_refresh_txdt_register(handle->i2c_x);

        /* disable interrupts */
        i2c_interrupt_enable(handle->i2c_x, I2C_ERR_INT | I2C_TDC_INT | I2C_STOP_INT | I2C_ACKFIAL_INT | I2C_TD_INT | I2C_RD_INT, FALSE);

        /* transfer complete */
        handle->comm.status = I2C_END;
        rt_completion_done(&handle->completion);
    }
}

void i2c_evt_isr(struct at32_i2c_handle *handle)
{
    switch(handle->comm.mode)
    {
        case I2C_INT_MA_TX:
        case I2C_INT_MA_RX:
            i2c_master_isr_int(handle);
            break;
        case I2C_DMA_MA_TX:
        case I2C_DMA_MA_RX:
            i2c_master_isr_dma(handle);
            break;
        default:
            break;
    }
}
#endif

static rt_ssize_t master_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    /* for dma may more stability */
#define DMA_TRANS_MIN_LEN 2 /* only buffer length >= DMA_TRANS_MIN_LEN will use DMA mode */
#define TRANS_TIMEOUT_PERSEC 8 /* per ms will trans nums bytes */

    rt_int32_t i, ret;
    struct rt_i2c_msg *msg = msgs;
    struct rt_completion *completion;
    rt_uint32_t timeout;
    if (num == 0)
    {
        return 0;
    }
    RT_ASSERT((msgs != RT_NULL) && (bus != RT_NULL));
    struct at32_i2c *instance = rt_container_of(bus, struct at32_i2c, i2c_bus);
    completion = &instance->handle->completion;

    LOG_D("xfer start %d mags", num);
    for (i = 0; i < (num - 1); i++)
    {
        msg = &msgs[i];
        LOG_D("xfer msgs[%d] addr=0x%2x buf=0x%x len= 0x%x flags= 0x%x", i, msg->addr, msg->buf, msg->len, msg->flags);
        timeout = msg->len / TRANS_TIMEOUT_PERSEC + 2;

        if (msg->flags & RT_I2C_RD)
        {
            if ((instance->handle->i2c_dma_flag & RT_DEVICE_FLAG_DMA_RX) && (msg->len >= DMA_TRANS_MIN_LEN))
            {
                ret = i2c_master_receive_dma(instance->handle, (msg->addr <<  1) , msg->buf, msg->len, 0xFFFFFFFF);
            }
            else
            {
                ret = i2c_master_receive_int(instance->handle, (msg->addr << 1) , msg->buf, msg->len, 0xFFFFFFFF);
            }
            if (ret != RT_EOK)
            {
                LOG_E("[%s:%d]i2c read error(%d)!\n", __func__, __LINE__, ret);
                goto out;
            }
            if (rt_completion_wait(completion, timeout) != RT_EOK)
            {
                LOG_D("receive time out");
                goto out;
            }
        }
        else
        {
            if ((instance->handle->i2c_dma_flag & RT_DEVICE_FLAG_DMA_TX) && (msg->len >= DMA_TRANS_MIN_LEN))
            {
                ret = i2c_master_transmit_dma(instance->handle, (msg->addr << 1)  , msg->buf, msg->len, 0xFFFFFFFF);
            }
            else
            {
                ret = i2c_master_transmit_int(instance->handle, (msg->addr << 1)  , msg->buf, msg->len, 0xFFFFFFFF);
            }
            if (ret != RT_EOK)
            {
                LOG_D("[%s:%d]i2c write error(%d)!\n", __func__, __LINE__, ret);
                goto out;
            }
            if (rt_completion_wait(completion, timeout) != RT_EOK)
            {
                LOG_D("transmit time out");
                goto out;
            }
        }
    }
    /* last msg */
    msg = &msgs[i];
    timeout = msg->len / TRANS_TIMEOUT_PERSEC + 2;

    LOG_D("xfer last msgs[%d] addr=0x%2x buf= 0x%x len= 0x%x flags = 0x%x", i, msg->addr, msg->buf, msg->len, msg->flags);
    if (msg->flags & RT_I2C_RD)
    {
        if ((instance->handle->i2c_dma_flag & RT_DEVICE_FLAG_DMA_RX) && (msg->len >= DMA_TRANS_MIN_LEN))
        {
            ret = i2c_master_receive_dma(instance->handle, (msg->addr << 1), msg->buf, msg->len, 0xFFFFFFFF);
        }
        else
        {
            ret = i2c_master_receive_int(instance->handle, (msg->addr << 1), msg->buf, msg->len, 0xFFFFFFFF);
        }
        if (ret != RT_EOK)
        {
            LOG_D("[%s:%d]i2c read error(%d)!\n", __func__, __LINE__, ret);
            goto out;
        }
        if (rt_completion_wait(completion, timeout) != RT_EOK)
        {
            LOG_D("receive time out");
            goto out;
        }
    }
    else
    {
        if ((instance->handle->i2c_dma_flag & RT_DEVICE_FLAG_DMA_TX) && (msg->len >= DMA_TRANS_MIN_LEN))
        {
            ret = i2c_master_transmit_dma(instance->handle, (msg->addr << 1), msg->buf, msg->len, 0xFFFFFFFF);
        }
        else
        {
            ret = i2c_master_transmit_int(instance->handle, (msg->addr << 1), msg->buf, msg->len, 0xFFFFFFFF);
        }
        if (ret != RT_EOK)
        {
            LOG_D("[%s:%d]i2c write error(%d)!\n", __func__, __LINE__, ret);
            goto out;
        }
        if (rt_completion_wait(completion, timeout) != RT_EOK)
        {
            LOG_D("transmit time out");
            goto out;
        }
    }
    ret = num;
    LOG_D("xfer end %d mags\r\n", num);
    return ret;

out:
    if(instance->handle->comm.error_code == I2C_ERR_ACKFAIL)
    {
        LOG_D("i2c nack error now stoped");
    }
    if(instance->handle->comm.error_code == I2C_ERR_INTERRUPT)
    {
        LOG_D("i2c bus error now stoped");
        ret = i - 1;
    }
    /* generate stop */
    i2c_stop_generate(instance->handle->i2c_x);
    return ret;
}

static void _dma_base_channel_check(struct at32_i2c *instance)
{
    dma_channel_type *rx_channel = instance->handle->dma_rx->dma_channel;
    dma_channel_type *tx_channel = instance->handle->dma_tx->dma_channel;

    if(instance->handle->i2c_dma_flag & RT_DEVICE_FLAG_DMA_RX)
    {
        instance->handle->dma_rx->dma_done = RT_TRUE;
        instance->handle->dma_rx->dma_x = (dma_type *)((rt_uint32_t)rx_channel & ~0xFF);
        instance->handle->dma_rx->channel_index = ((((rt_uint32_t)rx_channel & 0xFF) - 8) / 0x14) + 1;
    }

    if(instance->handle->i2c_dma_flag & RT_DEVICE_FLAG_DMA_TX)
    {
        instance->handle->dma_tx->dma_done = RT_TRUE;
        instance->handle->dma_tx->dma_x = (dma_type *)((rt_uint32_t)tx_channel & ~0xFF);
        instance->handle->dma_tx->channel_index = ((((rt_uint32_t)tx_channel & 0xFF) - 8) / 0x14) + 1;
    }
}

static void at32_i2c_dma_init(struct at32_i2c *instance)
{
    dma_init_type dma_init_struct;

    /* search dma base and channel index */
    _dma_base_channel_check(instance);

    /* config dma channel */
    dma_default_para_init(&dma_init_struct);
    dma_init_struct.peripheral_inc_enable = FALSE;
    dma_init_struct.memory_inc_enable = TRUE;
    dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
    dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
    dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
    dma_init_struct.loop_mode_enable = FALSE;

    if (instance->handle->i2c_dma_flag & RT_DEVICE_FLAG_DMA_RX)
    {
        crm_periph_clock_enable(instance->handle->dma_rx->dma_clock, TRUE);
        dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;

        dma_reset(instance->handle->dma_rx->dma_channel);
        dma_init(instance->handle->dma_rx->dma_channel, &dma_init_struct);
#if defined (SOC_SERIES_AT32F425)
        dma_flexible_config(instance->handle->dma_rx->dma_x, instance->handle->dma_rx->flex_channel, \
                           (dma_flexible_request_type)instance->handle->dma_rx->request_id);
#endif
#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32F423) || defined (SOC_SERIES_AT32F402) || \
    defined (SOC_SERIES_AT32F405) || defined (SOC_SERIES_AT32A423) || \
    defined (SOC_SERIES_AT32M412) || defined (SOC_SERIES_AT32M416)
        dmamux_enable(instance->handle->dma_rx->dma_x, TRUE);
        dmamux_init(instance->handle->dma_rx->dmamux_channel, (dmamux_requst_id_sel_type)instance->handle->dma_rx->request_id);
#endif
        /* dma irq should set in dma rx mode */
        nvic_irq_enable(instance->handle->dma_rx->dma_irqn, 0, 1);
    }

    if (instance->handle->i2c_dma_flag & RT_DEVICE_FLAG_DMA_TX)
    {
        crm_periph_clock_enable(instance->handle->dma_tx->dma_clock, TRUE);
        dma_init_struct.direction = DMA_DIR_MEMORY_TO_PERIPHERAL;

        dma_reset(instance->handle->dma_tx->dma_channel);
        dma_init(instance->handle->dma_tx->dma_channel, &dma_init_struct);
#if defined (SOC_SERIES_AT32F425)
        dma_flexible_config(instance->handle->dma_tx->dma_x, instance->handle->dma_tx->flex_channel, \
                           (dma_flexible_request_type)instance->handle->dma_tx->request_id);
#endif
#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32F423) || defined (SOC_SERIES_AT32F402) || \
    defined (SOC_SERIES_AT32F405) || defined (SOC_SERIES_AT32A423) || \
    defined (SOC_SERIES_AT32M412) || defined (SOC_SERIES_AT32M416)
        dmamux_enable(instance->handle->dma_tx->dma_x, TRUE);
        dmamux_init(instance->handle->dma_tx->dmamux_channel, (dmamux_requst_id_sel_type)instance->handle->dma_tx->request_id);
#endif
        /* dma irq should set in dma tx mode */
        nvic_irq_enable(instance->handle->dma_tx->dma_irqn, 0, 1);
    }
}

void i2c_err_isr(struct at32_i2c_handle *handle)
{
    /* buserr */
    if(i2c_flag_get(handle->i2c_x, I2C_BUSERR_FLAG) != RESET)
    {
        i2c_flag_clear(handle->i2c_x, I2C_BUSERR_FLAG);

        handle->comm.error_code = I2C_ERR_INTERRUPT;
    }

    /* arlost */
    if(i2c_flag_get(handle->i2c_x, I2C_ARLOST_FLAG) != RESET)
    {
        i2c_flag_clear(handle->i2c_x, I2C_ARLOST_FLAG);

        handle->comm.error_code = I2C_ERR_INTERRUPT;
    }

#if defined (SOC_SERIES_AT32F403A) || defined (SOC_SERIES_AT32F407)  || \
    defined (SOC_SERIES_AT32F413)  || defined (SOC_SERIES_AT32F415)  || \
    defined (SOC_SERIES_AT32F421)  || defined (SOC_SERIES_AT32A403A)
    /* ackfail */
    if(i2c_flag_get(handle->i2c_x, I2C_ACKFAIL_FLAG) != RESET)
    {
        i2c_flag_clear(handle->i2c_x, I2C_ACKFAIL_FLAG);

        switch(handle->comm.mode)
        {
            case I2C_DMA_SLA_TX:
                /* disable ack */
                i2c_ack_enable(handle->i2c_x, FALSE);

                /* disable evt interrupt */
                i2c_interrupt_enable(handle->i2c_x, I2C_EVT_INT, FALSE);

                /* transfer complete */
                handle->comm.status = I2C_END;
                break;
            default:
                handle->comm.error_code = I2C_ERR_INTERRUPT;
                break;
        }
    }
#endif

    /* ouf */
    if(i2c_flag_get(handle->i2c_x, I2C_OUF_FLAG) != RESET)
    {
        i2c_flag_clear(handle->i2c_x, I2C_OUF_FLAG);

        handle->comm.error_code = I2C_ERR_INTERRUPT;
    }

    /* pecerr */
    if(i2c_flag_get(handle->i2c_x, I2C_PECERR_FLAG) != RESET)
    {
        i2c_flag_clear(handle->i2c_x, I2C_PECERR_FLAG);

        handle->comm.error_code = I2C_ERR_INTERRUPT;
    }

    /* tmout */
    if(i2c_flag_get(handle->i2c_x, I2C_TMOUT_FLAG) != RESET)
    {
        i2c_flag_clear(handle->i2c_x, I2C_TMOUT_FLAG);

        handle->comm.error_code = I2C_ERR_INTERRUPT;
    }

    /* alertf */
    if(i2c_flag_get(handle->i2c_x, I2C_ALERTF_FLAG) != RESET)
    {
        i2c_flag_clear(handle->i2c_x, I2C_ALERTF_FLAG);

        handle->comm.error_code = I2C_ERR_INTERRUPT;
    }

    /* disable all interrupts */
    i2c_interrupt_enable(handle->i2c_x, I2C_ERR_INT, FALSE);
}

void i2c_dma_isr(struct at32_i2c_handle *handle)
{
    volatile rt_uint32_t reg_sts = 0, index = 0;
    struct dma_config *dma = RT_NULL;

    if(handle->comm.mode == I2C_DMA_MA_TX)
    {
        dma = handle->dma_tx;
    }
    else if(handle->comm.mode == I2C_DMA_MA_RX)
    {
        dma = handle->dma_rx;
    }

    reg_sts = dma->dma_x->sts;
    index = dma->channel_index;

    /* transfer complete */
    if((reg_sts & (DMA_FDT_FLAG << (4 * (index - 1)))) != RESET)
    {
        /* clear dma flag */
        dma->dma_x->clr |= (rt_uint32_t)((DMA_FDT_FLAG << (4 * (index - 1))) | \
                                         (DMA_HDT_FLAG << (4 * (index - 1))));
        /* disable the transfer complete interrupt */
        dma_interrupt_enable(dma->dma_channel, DMA_FDT_INT, FALSE);
        /* mark done */
        dma->dma_done = RT_TRUE;
#if defined (SOC_SERIES_AT32F403A) || defined (SOC_SERIES_AT32F407)  || \
    defined (SOC_SERIES_AT32F413)  || defined (SOC_SERIES_AT32F415)  || \
    defined (SOC_SERIES_AT32F421)  || defined (SOC_SERIES_AT32A403A)
        /* disable dma request */
        i2c_dma_enable(handle->i2c_x, FALSE);
#endif
#if defined (SOC_SERIES_AT32F402)  || defined (SOC_SERIES_AT32F405) || \
    defined (SOC_SERIES_AT32F423)  || defined (SOC_SERIES_AT32F425) || \
    defined (SOC_SERIES_AT32F435)  || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32A423)  || defined (SOC_SERIES_AT32M412) || \
    defined (SOC_SERIES_AT32M416)
        /* disable dma request */
        if(handle->comm.mode == I2C_DMA_MA_TX)
            i2c_dma_enable(handle->i2c_x, I2C_DMA_REQUEST_TX, FALSE);
        else if(handle->comm.mode == I2C_DMA_MA_RX)
            i2c_dma_enable(handle->i2c_x, I2C_DMA_REQUEST_RX, FALSE);
#endif
        /* disable dma channel */
        dma_channel_enable(dma->dma_channel, FALSE);

        switch(handle->comm.mode)
        {
#if defined (SOC_SERIES_AT32F403A) || defined (SOC_SERIES_AT32F407)  || \
    defined (SOC_SERIES_AT32F413)  || defined (SOC_SERIES_AT32F415)  || \
    defined (SOC_SERIES_AT32F421)  || defined (SOC_SERIES_AT32A403A)
            case I2C_DMA_MA_TX:
                /* enable tdc interrupt, generate stop condition in tdc interrupt */
                handle->comm.pcount = 0;
                i2c_interrupt_enable(handle->i2c_x, I2C_EVT_INT, TRUE);
                break;
            case I2C_DMA_MA_RX:
                /* clear ackfail flag  */
                i2c_flag_clear(handle->i2c_x, I2C_ACKFAIL_FLAG);
                handle->comm.pcount = 0;
                /* generate stop condtion */
                i2c_stop_generate(handle->i2c_x);

                /* transfer complete */
                rt_completion_done(&handle->completion);
                handle->comm.status = I2C_END;
                break;
            default:
                break;
#endif
#if defined (SOC_SERIES_AT32F402)  || defined (SOC_SERIES_AT32F405) || \
    defined (SOC_SERIES_AT32F423)  || defined (SOC_SERIES_AT32F425) || \
    defined (SOC_SERIES_AT32F435)  || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32A423)  || defined (SOC_SERIES_AT32M412) || \
    defined (SOC_SERIES_AT32M416)
            case I2C_DMA_MA_TX:
            case I2C_DMA_MA_RX:
            {
                /* update the number of transfers */
                handle->comm.pcount -= handle->comm.psize;

                /* transfer complete */
                if (handle->comm.pcount == 0)
                {
                    /* enable stop interrupt */
                    i2c_interrupt_enable(handle->i2c_x, I2C_STOP_INT, TRUE);
                }
                /* the transfer has not been completed */
                else
                {
                    /* update the buffer pointer of transfers */
                    handle->comm.pbuff += handle->comm.psize;

                    /* set the number to be transferred */
                    if (handle->comm.pcount > MAX_TRANSFER_CNT)
                    {
                        handle->comm.psize = MAX_TRANSFER_CNT;
                    }
                    else
                    {
                        handle->comm.psize = handle->comm.pcount;
                    }

                    /* config dma channel, continue to transfer data */
                    i2c_dma_config(handle, handle->comm.pbuff, handle->comm.psize);

                    /* enable tdc interrupt */
                    i2c_interrupt_enable(handle->i2c_x, I2C_TDC_INT, TRUE);
                }
            }
                break;
            default:
                break;
#endif
        }
    }
}

#ifdef BSP_USING_HARD_I2C1
void I2C1_EVT_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    i2c_evt_isr(i2cs[I2C1_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}

void I2C1_ERR_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    i2c_err_isr(i2cs[I2C1_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(BSP_I2C1_RX_USING_DMA)
void I2C1_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    i2c_dma_isr(i2cs[I2C1_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_I2C1_RX_USING_DMA) */
#if defined(BSP_I2C1_TX_USING_DMA)
void I2C1_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    i2c_dma_isr(i2cs[I2C1_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_I2C1_TX_USING_DMA) */
#endif
#ifdef BSP_USING_HARD_I2C2
void I2C2_EVT_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    i2c_evt_isr(i2cs[I2C2_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}

void I2C2_ERR_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    i2c_err_isr(i2cs[I2C2_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(BSP_I2C2_RX_USING_DMA)
void I2C2_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    i2c_dma_isr(i2cs[I2C2_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_I2C2_RX_USING_DMA) */
#if defined(BSP_I2C2_TX_USING_DMA)
void I2C2_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    i2c_dma_isr(i2cs[I2C2_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_I2C2_TX_USING_DMA) */
#endif
#ifdef BSP_USING_HARD_I2C3
void I2C3_EVT_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    i2c_evt_isr(i2cs[I2C3_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}

void I2C3_ERR_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    i2c_err_isr(i2cs[I2C3_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(BSP_I2C3_RX_USING_DMA)
void I2C3_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    i2c_dma_isr(i2cs[I2C3_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_I2C3_RX_USING_DMA) */
#if defined(BSP_I2C3_TX_USING_DMA)
void I2C3_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    i2c_dma_isr(i2cs[I2C3_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_I2C3_TX_USING_DMA) */
#endif

#if defined (SOC_SERIES_AT32F421) || defined (SOC_SERIES_AT32F425)
void I2C1_TX_RX_DMA_IRQHandler(void)
{
#if defined(BSP_USING_HARD_I2C1) && defined(BSP_I2C1_TX_USING_DMA)
    I2C1_TX_DMA_IRQHandler();
#endif

#if defined(BSP_USING_HARD_I2C1) && defined(BSP_I2C1_RX_USING_DMA)
    I2C1_RX_DMA_IRQHandler();
#endif
}

void I2C2_TX_RX_DMA_IRQHandler(void)
{
#if defined(BSP_USING_HARD_I2C2) && defined(BSP_I2C2_TX_USING_DMA)
    I2C2_TX_DMA_IRQHandler();
#endif

#if defined(BSP_USING_HARD_I2C2) && defined(BSP_I2C2_RX_USING_DMA)
    I2C2_RX_DMA_IRQHandler();
#endif
}
#endif

static void at32_i2c_get_dma_config(void)
{
#ifdef BSP_USING_HARD_I2C1
    i2c_handle[I2C1_INDEX].i2c_dma_flag = 0;
#ifdef BSP_I2C1_RX_USING_DMA
    i2c_handle[I2C1_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config i2c1_dma_rx = I2C1_RX_DMA_CONFIG;
    i2c_handle[I2C1_INDEX].dma_rx = &i2c1_dma_rx;
#endif
#ifdef BSP_I2C1_TX_USING_DMA
    i2c_handle[I2C1_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config i2c1_dma_tx = I2C1_TX_DMA_CONFIG;
    i2c_handle[I2C1_INDEX].dma_tx = &i2c1_dma_tx;
#endif
#endif

#ifdef BSP_USING_HARD_I2C2
    i2c_handle[I2C2_INDEX].i2c_dma_flag = 0;
#ifdef BSP_I2C2_RX_USING_DMA
    i2c_handle[I2C2_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config i2c2_dma_rx = I2C2_RX_DMA_CONFIG;
    i2c_handle[I2C2_INDEX].dma_rx = &i2c2_dma_rx;
#endif
#ifdef BSP_I2C2_TX_USING_DMA
    i2c_handle[I2C2_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config i2c2_dma_tx = I2C2_TX_DMA_CONFIG;
    i2c_handle[I2C2_INDEX].dma_tx = &i2c2_dma_tx;
#endif
#endif

#ifdef BSP_USING_HARD_I2C3
    i2c_handle[I2C3_INDEX].i2c_dma_flag = 0;
#ifdef BSP_I2C3_RX_USING_DMA
    i2c_handle[I2C3_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config i2c3_dma_rx = I2C3_RX_DMA_CONFIG;
    i2c_handle[I2C3_INDEX].dma_rx = &i2c3_dma_rx;
#endif
#ifdef BSP_I2C3_TX_USING_DMA
    i2c_handle[I2C3_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config i2c3_dma_tx = I2C3_TX_DMA_CONFIG;
    i2c_handle[I2C3_INDEX].dma_tx = &i2c3_dma_tx;
#endif
#endif
}

int rt_hw_hwi2c_init(void)
{
    int i;
    rt_err_t result;
    rt_size_t obj_num = sizeof(i2c_handle) / sizeof(i2c_handle[0]);

    at32_i2c_get_dma_config();

    for (i = 0; i < obj_num; i++)
    {
        i2cs[i].handle = &i2c_handle[i];
        i2cs[i].i2c_bus.ops = &at32_i2c_ops;

        if(i2cs[i].handle->i2c_dma_flag & (RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX))
        {
            at32_i2c_dma_init(&i2cs[i]);
        }
        rt_completion_init(&i2cs[i].handle->completion);
        at32_i2c_configure(&(i2cs[i].i2c_bus));
        result = rt_i2c_bus_device_register(&(i2cs[i].i2c_bus), i2cs[i].handle->i2c_name);
    }

    return result;
}

INIT_BOARD_EXPORT(rt_hw_hwi2c_init);

#endif
