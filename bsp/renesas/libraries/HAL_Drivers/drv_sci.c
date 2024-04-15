/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-24     Vandoul      first version
 * 2023-09-27     Vandoul      add sci uart
 */

#include "drv_sci.h"

#ifdef BSP_USING_SCI

//#define DRV_DEBUG
#define DBG_TAG              "drv.sci"
#ifdef DRV_DEBUG
    #define DBG_LVL               DBG_LOG
#else
    #define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */
#include <rtdbg.h>

#ifdef R_SCI_B_SPI_H
    #define R_SCI_SPI_Write             R_SCI_B_SPI_Write
    #define R_SCI_SPI_Read              R_SCI_B_SPI_Read
    #define R_SCI_SPI_WriteRead         R_SCI_B_SPI_WriteRead
    #define R_SCI_SPI_Open              R_SCI_B_SPI_Open
    #define R_SCI_SPI_Close             R_SCI_B_SPI_Close
    #define R_SCI_SPI_CallbackSet       R_SCI_B_SPI_CallbackSet
#endif

enum
{
#ifdef        BSP_USING_SCI0
    RA_SCI_INDEX0,
#endif
#ifdef        BSP_USING_SCI1
    RA_SCI_INDEX1,
#endif
#ifdef        BSP_USING_SCI2
    RA_SCI_INDEX2,
#endif
#ifdef        BSP_USING_SCI3
    RA_SCI_INDEX3,
#endif
#ifdef        BSP_USING_SCI4
    RA_SCI_INDEX4,
#endif
#ifdef        BSP_USING_SCI5
    RA_SCI_INDEX5,
#endif
#ifdef        BSP_USING_SCI6
    RA_SCI_INDEX6,
#endif
#ifdef        BSP_USING_SCI7
    RA_SCI_INDEX7,
#endif
#ifdef        BSP_USING_SCI8
    RA_SCI_INDEX8,
#endif
#ifdef        BSP_USING_SCI9
    RA_SCI_INDEX9,
#endif
    RA_SCI_INDEX_MAX,
};

struct ra_sci_param
{
    const char  bus_name[RT_NAME_MAX];
    const void  *sci_ctrl;
    const void  *sci_cfg;
    const void  *ops;
};

#ifdef RT_USING_I2C
    rt_weak const struct rt_i2c_bus_device_ops sci_ops_i2c;
#endif
#ifdef RT_USING_SPI
    rt_weak const struct rt_spi_ops            sci_ops_spi;
#endif
#ifdef RT_USING_SERIAL
    rt_weak const struct rt_uart_ops           sci_ops_uart;
#endif

struct ra_sci_object
{
    union
    {
#ifdef RT_USING_SPI
        struct
        {
            struct rt_spi_bus           sbus;
            struct rt_spi_configuration *spi_cfg;
        };
#endif
#ifdef RT_USING_I2C
        struct
        {
            struct rt_i2c_bus_device    ibus;
        };
#endif
#ifdef RT_USING_SERIAL
        struct
        {
            struct rt_serial_device     ubus;
        };
#endif
    };
    const struct ra_sci_param *param;
    struct rt_event event;
};

#define _TO_STR(_a)                 #_a
#define CONCAT3STR(_a,_b,_c)        _TO_STR(_a##_b##_c)

#define RA_SCI_EVENT_ABORTED        1
#define RA_SCI_EVENT_RX_COMPLETE    2
#define RA_SCI_EVENT_TX_COMPLETE    4
#define RA_SCI_EVENT_ERROR          8
#define RA_SCI_EVENT_ALL            15

/**
 * Bus name format: sci[x][y], where x=0~9 and y=s/i/u
 * Example:
 * - sci_spi:  sci0s
 * - sci_i2c:  sci0i
 * - sci_uart: sci0u
 */
#define RA_SCI_HANDLE_ITEM(idx,type,id)    {.bus_name=CONCAT3STR(sci,idx,id),.sci_ctrl=&g_sci##idx##_ctrl,.sci_cfg=&g_sci##idx##_cfg,.ops=&sci_ops_##type}

const static struct ra_sci_param sci_param[] =
{
#ifdef        BSP_USING_SCI0
#ifdef        BSP_USING_SCI0_SPI
    RA_SCI_HANDLE_ITEM(0, spi, s),
#elif defined(BSP_USING_SCI0_I2C)
    RA_SCI_HANDLE_ITEM(0, i2c, i),
#elif defined(BSP_USING_SCI0_UART)
    RA_SCI_HANDLE_ITEM(0, uart, u),
#endif
#endif

#ifdef        BSP_USING_SCI1
#ifdef        BSP_USING_SCI1_SPI
    RA_SCI_HANDLE_ITEM(1, spi, s),
#elif defined(BSP_USING_SCI1_I2C)
    RA_SCI_HANDLE_ITEM(1, i2c, i),
#elif defined(BSP_USING_SCI1_UART)
    RA_SCI_HANDLE_ITEM(1, uart, u),
#endif
#endif

#ifdef        BSP_USING_SCI2
#ifdef        BSP_USING_SCI2_SPI
    RA_SCI_HANDLE_ITEM(2, spi, s),
#elif defined(BSP_USING_SCI2_I2C)
    RA_SCI_HANDLE_ITEM(2, i2c, i),
#elif defined(BSP_USING_SCI2_UART)
    RA_SCI_HANDLE_ITEM(2, uart, u),
#endif
#endif

#ifdef        BSP_USING_SCI3
#ifdef        BSP_USING_SCI3_SPI
    RA_SCI_HANDLE_ITEM(3, spi, s),
#elif defined(BSP_USING_SCI3_I2C)
    RA_SCI_HANDLE_ITEM(3, i2c, i),
#elif defined(BSP_USING_SCI3_UART)
    RA_SCI_HANDLE_ITEM(3, uart, u),
#endif
#endif

#ifdef        BSP_USING_SCI4
#ifdef        BSP_USING_SCI4_SPI
    RA_SCI_HANDLE_ITEM(4, spi, s),
#elif defined(BSP_USING_SCI4_I2C)
    RA_SCI_HANDLE_ITEM(4, i2c, i),
#elif defined(BSP_USING_SCI4_UART)
    RA_SCI_HANDLE_ITEM(4, uart, u),
#endif
#endif

#ifdef        BSP_USING_SCI5
#ifdef        BSP_USING_SCI5_SPI
    RA_SCI_HANDLE_ITEM(5, spi, s),
#elif defined(BSP_USING_SCI5_I2C)
    RA_SCI_HANDLE_ITEM(5, i2c, i),
#elif defined(BSP_USING_SCI5_UART)
    RA_SCI_HANDLE_ITEM(5, uart, u),
#endif
#endif

#ifdef        BSP_USING_SCI6
#ifdef        BSP_USING_SCI6_SPI
    RA_SCI_HANDLE_ITEM(6, spi, s),
#elif defined(BSP_USING_SCI6_I2C)
    RA_SCI_HANDLE_ITEM(6, i2c, i),
#elif defined(BSP_USING_SCI6_UART)
    RA_SCI_HANDLE_ITEM(6, uart, u),
#endif
#endif

#ifdef        BSP_USING_SCI7
#ifdef        BSP_USING_SCI7_SPI
    RA_SCI_HANDLE_ITEM(7, spi, s),
#elif defined(BSP_USING_SCI7_I2C)
    RA_SCI_HANDLE_ITEM(7, i2c, i),
#elif defined(BSP_USING_SCI7_UART)
    RA_SCI_HANDLE_ITEM(7, uart, u),
#endif
#endif

#ifdef        BSP_USING_SCI8
#ifdef        BSP_USING_SCI8_SPI
    RA_SCI_HANDLE_ITEM(8, spi, s),
#elif defined(BSP_USING_SCI8_I2C)
    RA_SCI_HANDLE_ITEM(8, i2c, i),
#elif defined(BSP_USING_SCI8_UART)
    RA_SCI_HANDLE_ITEM(8, uart, u),
#endif
#endif

#ifdef        BSP_USING_SCI9
#ifdef        BSP_USING_SCI9_SPI
    RA_SCI_HANDLE_ITEM(9, spi, s),
#elif defined(BSP_USING_SCI9_I2C)
    RA_SCI_HANDLE_ITEM(9, i2c, i),
#elif defined(BSP_USING_SCI9_UART)
    RA_SCI_HANDLE_ITEM(9, uart, u),
#endif
#endif
};

static struct ra_sci_object sci_obj[RA_SCI_INDEX_MAX];
rt_used static rt_err_t ra_wait_complete(struct ra_sci_object *obj)
{
    rt_uint32_t event = 0;
    if (RT_EOK != rt_event_recv(&obj->event, RA_SCI_EVENT_ALL, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, (rt_int32_t)rt_tick_from_millisecond(400), &event))
    {
        return -RT_ETIMEOUT;
    }
    if ((event & (RA_SCI_EVENT_ABORTED | RA_SCI_EVENT_ERROR)) == 0)
    {
        return RT_EOK;
    }

    return -RT_ERROR;
}
/**
 * @brief SCI UART
 * @defgroup SCI_UART
 * @{
 */
#ifdef BSP_USING_SCIn_UART
const static int uart_buff_size[][2] =
{
#ifdef        BSP_USING_SCI0_UART
    {BSP_SCI0_UART_RX_BUFSIZE, BSP_SCI0_UART_TX_BUFSIZE},
#endif
#ifdef        BSP_USING_SCI1_UART
    {BSP_SCI1_UART_RX_BUFSIZE, BSP_SCI1_UART_TX_BUFSIZE},
#endif
#ifdef        BSP_USING_SCI2_UART
    {BSP_SCI2_UART_RX_BUFSIZE, BSP_SCI2_UART_TX_BUFSIZE},
#endif
#ifdef        BSP_USING_SCI3_UART
    {BSP_SCI3_UART_RX_BUFSIZE, BSP_SCI3_UART_TX_BUFSIZE},
#endif
#ifdef        BSP_USING_SCI4_UART
    {BSP_SCI4_UART_RX_BUFSIZE, BSP_SCI4_UART_TX_BUFSIZE},
#endif
#ifdef        BSP_USING_SCI5_UART
    {BSP_SCI5_UART_RX_BUFSIZE, BSP_SCI5_UART_TX_BUFSIZE},
#endif
#ifdef        BSP_USING_SCI6_UART
    {BSP_SCI6_UART_RX_BUFSIZE, BSP_SCI6_UART_TX_BUFSIZE},
#endif
#ifdef        BSP_USING_SCI7_UART
    {BSP_SCI7_UART_RX_BUFSIZE, BSP_SCI7_UART_TX_BUFSIZE},
#endif
#ifdef        BSP_USING_SCI8_UART
    {BSP_SCI8_UART_RX_BUFSIZE, BSP_SCI8_UART_TX_BUFSIZE},
#endif
#ifdef        BSP_USING_SCI9_UART
    {BSP_SCI9_UART_RX_BUFSIZE, BSP_SCI9_UART_TX_BUFSIZE},
#endif
    {0, 0},
};

void sci_uart_irq_callback(uart_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (NULL != p_args)
    {
        struct ra_sci_object *obj = (struct ra_sci_object *)p_args->p_context;
        RT_ASSERT(obj != RT_NULL);

        if (UART_EVENT_RX_CHAR == p_args->event)
        {
            struct rt_serial_device *serial = &obj->ubus;
            struct rt_serial_rx_fifo *rx_fifo;
            rx_fifo = (struct rt_serial_rx_fifo *) serial->serial_rx;
            RT_ASSERT(rx_fifo != RT_NULL);

            rt_ringbuffer_putchar(&(rx_fifo->rb), (rt_uint8_t)p_args->data);

            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        }
    }
    rt_interrupt_leave();
}

static rt_err_t ra_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct ra_sci_object *obj;
    const struct ra_sci_param *param;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    fsp_err_t err = FSP_SUCCESS;

    obj = rt_container_of(serial, struct ra_sci_object, ubus);
    param = obj->param;
    RT_ASSERT(param != RT_NULL);

    err = R_SCI_UART_Open((uart_ctrl_t *const)param->sci_ctrl, (uart_cfg_t *const)param->sci_cfg);
    if (FSP_SUCCESS != err)
    {
        return -RT_ERROR;
    }

    err = R_SCI_UART_CallbackSet((uart_ctrl_t *const)param->sci_ctrl, sci_uart_irq_callback, obj, NULL);
    if (FSP_SUCCESS != err)
    {
        //LOG_W("R_SCI_UART_CallbackSet API failed,%d", err);
    }

    return RT_EOK;
}

static rt_err_t ra_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    return RT_EOK;
}

static int ra_uart_putc(struct rt_serial_device *serial, char c)
{
    struct ra_sci_object *obj;
    const struct ra_sci_param *param;
    RT_ASSERT(serial != RT_NULL);

    obj = rt_container_of(serial, struct ra_sci_object, ubus);
    param = obj->param;
    RT_ASSERT(param != RT_NULL);

    sci_uart_instance_ctrl_t *p_ctrl = (sci_uart_instance_ctrl_t *)param->sci_ctrl;

    p_ctrl->p_reg->TDR = c;
    while ((p_ctrl->p_reg->SSR_b.TEND) == 0);

    return RT_EOK;
}

static int ra_uart_getc(struct rt_serial_device *serial)
{
    return RT_EOK;
}

static rt_ssize_t ra_uart_transmit(struct rt_serial_device     *serial,
                                   rt_uint8_t           *buf,
                                   rt_size_t             size,
                                   rt_uint32_t           tx_flag)
{
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    return 0;
}

const struct rt_uart_ops sci_ops_uart =
{
    .configure = ra_uart_configure,
    .control = ra_uart_control,
    .putc = ra_uart_putc,
    .getc = ra_uart_getc,
    .transmit = ra_uart_transmit,
};
#else
void sci_uart_irq_callback(uart_callback_args_t *p_args)
{
}
#endif
/**
 * @}
 */

/**
 * @brief SCI I2C
 * @defgroup SCI_I2C
 * @{
 */
#ifdef BSP_USING_SCIn_I2C
void sci_i2c_irq_callback(i2c_master_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (NULL != p_args)
    {
        /* capture callback event for validating the i2c transfer event*/
        struct ra_sci_object *obj = (struct ra_sci_object *)p_args->p_context;
        uint32_t event = 0;
        RT_ASSERT(obj != RT_NULL);
        switch (p_args->event)
        {
        case I2C_MASTER_EVENT_ABORTED:
            event |= RA_SCI_EVENT_ABORTED;
            break;
        case I2C_MASTER_EVENT_RX_COMPLETE:
            event |= RA_SCI_EVENT_RX_COMPLETE;
            break;
        case I2C_MASTER_EVENT_TX_COMPLETE:
            event |= RA_SCI_EVENT_TX_COMPLETE;
            break;
        }
        rt_event_send(&obj->event, event);
        LOG_D("event:%x", p_args->event);
    }
    rt_interrupt_leave();
    LOG_D("p_args:%p", p_args);
}

static rt_ssize_t ra_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                  struct rt_i2c_msg msgs[],
                                  rt_uint32_t num)
{
    rt_size_t i;
    RT_ASSERT(bus != RT_NULL);
    struct ra_sci_object *obj = rt_container_of(bus, struct ra_sci_object, ibus);
    const struct ra_sci_param *param = obj->param;
    i2c_master_ctrl_t *master_ctrl = (i2c_master_ctrl_t *)param->sci_ctrl;
    int err = FSP_SUCCESS;
    bool restart = false;

    for (i = 0; i < num; i++)
    {
        struct rt_i2c_msg *msg = &msgs[i];
        if (msg->flags & RT_I2C_NO_STOP)
        {
            restart = true;
        }
        else
        {
            restart = false;
        }
        if (msg->flags & RT_I2C_ADDR_10BIT)
        {
            //LOG_E("10Bit not support");
            //break;
#ifdef SOC_SERIES_R7FA8M85
            R_SCI_B_I2C_SlaveAddressSet(master_ctrl, msg->addr, I2C_MASTER_ADDR_MODE_10BIT);
#else
            R_SCI_I2C_SlaveAddressSet(master_ctrl, msg->addr, I2C_MASTER_ADDR_MODE_10BIT);
#endif
        }
        else
        {
            //master_ctrl->slave = msg->addr;
#ifdef SOC_SERIES_R7FA8M85
            R_SCI_B_I2C_SlaveAddressSet(master_ctrl, msg->addr, I2C_MASTER_ADDR_MODE_7BIT);
#else
            R_SCI_I2C_SlaveAddressSet(master_ctrl, msg->addr, I2C_MASTER_ADDR_MODE_7BIT);
#endif
        }

        if (msg->flags & RT_I2C_RD)
        {
#ifdef SOC_SERIES_R7FA8M85
            err = R_SCI_B_I2C_Read(master_ctrl, msg->buf, msg->len, restart);
#else
            err = R_SCI_I2C_Read(master_ctrl, msg->buf, msg->len, restart);
#endif
        }
        else
        {
#ifdef SOC_SERIES_R7FA8M85
            err = R_SCI_B_I2C_Write(master_ctrl, msg->buf, msg->len, restart);
#else
            err = R_SCI_I2C_Write(master_ctrl, msg->buf, msg->len, restart);
#endif
        }
        if (FSP_SUCCESS == err)
        {
            /* handle error */
            err = ra_wait_complete(obj);
            if (RT_EOK != err)
            {
                //LOG_E("POWER_CTL reg I2C write failed,%d,%d", err, i);
                break;
            }
        }
        /* handle error */
        else
        {
            /* Write API returns itself is not successful */
            LOG_E("R_IIC_MASTER_Write/Read API failed,%d", i);
            break;
        }
    }
    return (rt_ssize_t)i;
}

const struct rt_i2c_bus_device_ops sci_ops_i2c =
{
    .master_xfer        = ra_i2c_mst_xfer,
    .slave_xfer         = RT_NULL,
    .i2c_bus_control    = RT_NULL
};
#endif
/**
 * @}
 */

/**
 * @brief SCI SPI
 * @defgroup SCI_SPI
 * @{
 */
#ifdef BSP_USING_SCIn_SPI
void sci_spi_irq_callback(spi_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (NULL != p_args)
    {
        /* capture callback event for validating the i2c transfer event*/
        struct ra_sci_object *obj = (struct ra_sci_object *)p_args->p_context;
        uint32_t event = 0;
        switch (p_args->event)
        {
        case SPI_EVENT_ERR_MODE_FAULT   :
        case SPI_EVENT_ERR_READ_OVERFLOW:
        case SPI_EVENT_ERR_PARITY       :
        case SPI_EVENT_ERR_OVERRUN      :
        case SPI_EVENT_ERR_FRAMING      :
        case SPI_EVENT_ERR_MODE_UNDERRUN:
            event |= RA_SCI_EVENT_ERROR;
            break;
        case SPI_EVENT_TRANSFER_ABORTED :
            event |= RA_SCI_EVENT_ABORTED;
            break;
        case SPI_EVENT_TRANSFER_COMPLETE:
            event |= RA_SCI_EVENT_TX_COMPLETE;
            break;
        }
        rt_event_send(&obj->event, event);
        LOG_D("event:%x", p_args->event);
    }
    rt_interrupt_leave();
    LOG_D("p_args:%p", p_args);
}

static spi_bit_width_t ra_width_shift(rt_uint8_t data_width)
{
    spi_bit_width_t bit_width = SPI_BIT_WIDTH_8_BITS;
    if (data_width == 1)
        bit_width = SPI_BIT_WIDTH_8_BITS;
    else if (data_width == 2)
        bit_width = SPI_BIT_WIDTH_16_BITS;
    else if (data_width == 4)
        bit_width = SPI_BIT_WIDTH_32_BITS;

    return bit_width;
}

static rt_err_t ra_write_message(struct rt_spi_device *device, const void *send_buf, const rt_size_t len)
{
    RT_ASSERT(device != NULL);
    RT_ASSERT(send_buf != NULL);
    RT_ASSERT(len > 0);
    rt_err_t err = RT_EOK;
    struct ra_sci_object *obj =  rt_container_of(device->bus, struct ra_sci_object, sbus);
    const struct ra_sci_param *param = obj->param;

    spi_bit_width_t bit_width = ra_width_shift(obj->spi_cfg->data_width);
    /**< send msessage */
    err = R_SCI_SPI_Write((spi_ctrl_t *)param->sci_ctrl, send_buf, len, bit_width);
    if (RT_EOK != err)
    {
        LOG_E("%s write failed. %d", param->bus_name, err);
        return -RT_ERROR;
    }
    /* Wait for SPI_EVENT_TRANSFER_COMPLETE callback event. */
    ra_wait_complete(obj);
    return len;
}

static rt_err_t ra_read_message(struct rt_spi_device *device, void *recv_buf, const rt_size_t len)
{
    RT_ASSERT(device != NULL);
    RT_ASSERT(recv_buf != NULL);
    RT_ASSERT(len > 0);
    rt_err_t err = RT_EOK;
    struct ra_sci_object *obj =  rt_container_of(device->bus, struct ra_sci_object, sbus);
    const struct ra_sci_param *param = obj->param;

    spi_bit_width_t bit_width = ra_width_shift(obj->spi_cfg->data_width);
    /**< receive message */
    err = R_SCI_SPI_Read((spi_ctrl_t *)param->sci_ctrl, recv_buf, len, bit_width);
    if (RT_EOK != err)
    {
        LOG_E("%s write failed. %d", param->bus_name, err);
        return -RT_ERROR;
    }
    /* Wait for SPI_EVENT_TRANSFER_COMPLETE callback event. */
    ra_wait_complete(obj);
    return len;
}

static rt_err_t ra_write_read_message(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);
    RT_ASSERT(message->length > 0);
    rt_err_t err = RT_EOK;
    struct ra_sci_object *obj =  rt_container_of(device->bus, struct ra_sci_object, sbus);
    const struct ra_sci_param *param = obj->param;

    spi_bit_width_t bit_width = ra_width_shift(obj->spi_cfg->data_width);
    /**< write and receive message */
    err = R_SCI_SPI_WriteRead((spi_ctrl_t *)param->sci_ctrl, message->send_buf, message->recv_buf, message->length, bit_width);
    if (RT_EOK != err)
    {
        LOG_E("%s write and read failed. %d", param->bus_name, err);
        return -RT_ERROR;
    }

    /* Wait for SPI_EVENT_TRANSFER_COMPLETE callback event. */
    ra_wait_complete(obj);
    return message->length;
}

/**< init spi TODO : MSB does not support modification */
static rt_err_t ra_hw_spi_configure(struct rt_spi_device *device,
                                    struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != NULL);
    RT_ASSERT(configuration != NULL);
    rt_err_t err = RT_EOK;

    struct ra_sci_object *obj =  rt_container_of(device->bus, struct ra_sci_object, sbus);
    const struct ra_sci_param *param = obj->param;
    const spi_cfg_t *cfg = (const spi_cfg_t *)param->sci_cfg;

    /**< data_width : 1 -> 8 bits , 2 -> 16 bits, 4 -> 32 bits, default 32 bits*/
    rt_uint8_t data_width = configuration->data_width / 8;
    RT_ASSERT(data_width == 1 || data_width == 2 || data_width == 4);
    configuration->data_width = configuration->data_width / 8;
    obj->spi_cfg = configuration;

#ifdef R_SCI_B_SPI_H
    sci_b_spi_extended_cfg_t spi_cfg = *(sci_b_spi_extended_cfg_t *)cfg->p_extend;
#else
    sci_spi_extended_cfg_t *spi_cfg = (sci_spi_extended_cfg_t *)cfg->p_extend;
#endif

    /**< Configure Select Line */
    rt_pin_write(device->cs_pin, PIN_HIGH);

    /**< config bitrate */
#ifdef R_SCI_B_SPI_H
    R_SCI_B_SPI_CalculateBitrate(obj->spi_cfg->max_hz, SCI_B_SPI_SOURCE_CLOCK_PCLK, &spi_cfg.clk_div);
#else
    R_SCI_SPI_CalculateBitrate(obj->spi_cfg->max_hz, &spi_cfg->clk_div, false);
#endif

    /**< init */
    err = R_SCI_SPI_Open((spi_ctrl_t *)param->sci_ctrl, cfg);
    /* handle error */
    if (err == FSP_ERR_IN_USE)
    {
        R_SCI_SPI_Close((spi_ctrl_t *)param->sci_ctrl);
        err = R_SCI_SPI_Open((spi_ctrl_t *)param->sci_ctrl, cfg);
    }
    if (RT_EOK != err)
    {
        LOG_E("%s init failed. %d", param->bus_name, err);
        return -RT_ERROR;
    }
    err = R_SCI_SPI_CallbackSet((spi_ctrl_t *)param->sci_ctrl, sci_spi_irq_callback, obj, NULL);
    if (FSP_SUCCESS != err)
    {
        LOG_E("R_SCI_I2C_CallbackSet API failed,%d", err);
    }
    return RT_EOK;
}

static rt_ssize_t ra_spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    rt_err_t err = RT_EOK;

    if (message->cs_take && !(device->config.mode & RT_SPI_NO_CS) && (device->cs_pin != PIN_NONE))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
            rt_pin_write(device->cs_pin, PIN_HIGH);
        else
            rt_pin_write(device->cs_pin, PIN_LOW);
    }

    if (message->length > 0)
    {
        if (message->send_buf == RT_NULL && message->recv_buf != RT_NULL)
        {
            /**< receive message */
            err = ra_read_message(device, (void *)message->recv_buf, (const rt_size_t)message->length);
        }
        else if (message->send_buf != RT_NULL && message->recv_buf == RT_NULL)
        {
            /**< send message */
            err = ra_write_message(device, (const void *)message->send_buf, (const rt_size_t)message->length);
        }
        else if (message->send_buf != RT_NULL && message->recv_buf != RT_NULL)
        {
            /**< send and receive message */
            err =  ra_write_read_message(device, message);
        }
    }

    if (message->cs_release && !(device->config.mode & RT_SPI_NO_CS) && (device->cs_pin != PIN_NONE))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
            rt_pin_write(device->cs_pin, PIN_LOW);
        else
            rt_pin_write(device->cs_pin, PIN_HIGH);
    }
    return err;
}

const struct rt_spi_ops sci_ops_spi =
{
    .configure = ra_hw_spi_configure,
    .xfer = ra_spixfer,
};
#endif
/**
 * @}
 */

static int ra_hw_sci_init(void)
{
    int bufsz_idx = 0;
    for (rt_uint8_t idx = 0; idx < RA_SCI_INDEX_MAX; idx++)
    {
        struct ra_sci_object *obj = &sci_obj[idx];
        const struct ra_sci_param *param = &sci_param[idx];
        obj->param = param;
        rt_err_t err;
#ifdef BSP_USING_SCIn_SPI
        if ((uint32_t)param->ops == (uint32_t)&sci_ops_spi)
        {
            /**< register spi bus */
            err = rt_spi_bus_register(&obj->sbus, param->bus_name, param->ops);
            if (RT_EOK != err)
            {
                LOG_E("bus %s register failed. %d", param->bus_name, err);
                return -RT_ERROR;
            }
        }
        else
#endif
#ifdef BSP_USING_SCIn_I2C
            if ((uint32_t)param->ops == (uint32_t)&sci_ops_i2c)
            {
                obj->ibus.ops = param->ops;
                obj->ibus.priv = 0;
                /* opening IIC master module */
#ifdef SOC_SERIES_R7FA8M85
                err = R_SCI_B_I2C_Open((i2c_master_ctrl_t *)param->sci_ctrl, param->sci_cfg);
#else
                err = R_SCI_I2C_Open((i2c_master_ctrl_t *)param->sci_ctrl, param->sci_cfg);
#endif
                if (err != FSP_SUCCESS)
                {
                    LOG_E("R_IIC_MASTER_Open API failed,%d", err);
                    continue;
                }
#ifdef SOC_SERIES_R7FA8M85
                err = R_SCI_B_I2C_CallbackSet((i2c_master_ctrl_t *)param->sci_ctrl, sci_i2c_irq_callback, obj, NULL);
#else
                err = R_SCI_I2C_CallbackSet((i2c_master_ctrl_t *)param->sci_ctrl, sci_i2c_irq_callback, obj, NULL);
#endif
                /* handle error */
                if (FSP_SUCCESS != err)
                {
                    LOG_E("R_SCI_I2C_CallbackSet API failed,%d", err);
                    continue;
                }

                err = rt_i2c_bus_device_register(&obj->ibus, param->bus_name);
                if (RT_EOK != err)
                {
                    LOG_E("i2c bus %s register failed,%d", param->bus_name, err);
                    continue;
                }
            }
            else
#endif
#ifdef BSP_USING_SCIn_UART
                if ((uint32_t)param->ops == (uint32_t)&sci_ops_uart)
                {
                    if (rt_device_find(param->bus_name) != RT_NULL)
                    {
                        continue;
                    }
                    struct rt_serial_device *serial = &obj->ubus;
                    obj->ubus.ops = param->ops;
                    serial->config.rx_bufsz = uart_buff_size[bufsz_idx][0];
                    serial->config.tx_bufsz = uart_buff_size[bufsz_idx][1];
                    bufsz_idx ++;
                    err = rt_hw_serial_register(serial, param->bus_name, RT_DEVICE_FLAG_RDWR, RT_NULL);
                    if (RT_EOK != err)
                    {
                        LOG_E("uart %s register failed,%d", param->bus_name, err);
                        continue;
                    }
                }
#endif
        {
        }
        if (RT_EOK != rt_event_init(&obj->event, param->bus_name, RT_IPC_FLAG_PRIO))
        {
            LOG_E("sci event init fail!");
            return -RT_ERROR;
        }
    }

    return RT_EOK;
}
INIT_BOARD_EXPORT(ra_hw_sci_init);

#ifdef BSP_USING_SCIn_UART
rt_weak int rt_hw_usart_init(void)
{
    int bufsz_idx = 0;
    for (rt_uint8_t idx = 0; idx < RA_SCI_INDEX_MAX; idx++)
    {
        struct ra_sci_object *obj = &sci_obj[idx];
        const struct ra_sci_param *param = &sci_param[idx];
        obj->param = param;
        rt_err_t err;
        if ((uint32_t)param->ops == (uint32_t)&sci_ops_uart)
        {
            if (rt_device_find(param->bus_name) != RT_NULL)
            {
                continue;
            }
            struct rt_serial_device *serial = &obj->ubus;
            obj->ubus.ops = param->ops;
            serial->config.rx_bufsz = uart_buff_size[bufsz_idx][0];
            serial->config.tx_bufsz = uart_buff_size[bufsz_idx][1];
            bufsz_idx ++;
            err = rt_hw_serial_register(serial, param->bus_name, RT_DEVICE_FLAG_RDWR, RT_NULL);
            if (RT_EOK != err)
            {
                continue;
            }
            if (RT_EOK != rt_event_init(&obj->event, param->bus_name, RT_IPC_FLAG_PRIO))
            {
                return -RT_ERROR;
            }
        }
    }
    return RT_EOK;
}
#endif

/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
#ifdef BSP_USING_SCIn_SPI
rt_err_t rt_hw_sci_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;

    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);

    result = rt_spi_bus_attach_device_cspin(spi_device, device_name, bus_name, cs_pin, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("%s attach to %s faild, %d\n", device_name, bus_name, result);
    }

    LOG_D("%s attach to %s done", device_name, bus_name);

    return result;
}
#endif
#endif /* BSP_USING_SCI */
