/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-16     shelton      first version
 */

#include <rtdevice.h>
#include "drv_common.h"
#include "drv_qspi.h"

#ifdef BSP_USING_QSPI
#if !defined(BSP_USING_QSPI1) && !defined(BSP_USING_QSPI2)
#error "Please define at least one BSP_USING_QSPIx"
#endif

#define POSITION_VAL(VAL)               (__CLZ(__RBIT(VAL)))
#define QSPI_FIFO_DEPTH                 (32 * 4)

#define DRV_DEBUG
#define LOG_TAG                         "drv.qspi"
#include <drv_log.h>

struct at32_hw_spi_cs
{
    rt_uint16_t pin;
};

struct at32_qspi_bus
{
    struct rt_spi_bus qspi_device;

    qspi_type *qspi_x;
    char *bus_name;
};

enum
{
#ifdef BSP_USING_QSPI1
    QSPI1_INDEX,
#endif
#ifdef BSP_USING_QSPI2
    QSPI2_INDEX,
#endif
};

static struct at32_qspi_bus at32_qspi_obj[] =
{
#ifdef BSP_USING_QSPI1
    QSPI1_BUS_CONFIG,
#endif

#ifdef BSP_USING_QSPI2
    QSPI2_BUS_CONFIG,
#endif
};

static int at32_qspi_init(struct rt_qspi_device *device, struct rt_qspi_configuration *qspi_cfg)
{
    int result = RT_EOK;
    unsigned int i = 0;
    crm_clocks_freq_type clocks;
    rt_uint8_t qspi_div_tab[] = {2, 4, 6, 8, 3, 5, 10, 12};

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(qspi_cfg != RT_NULL);

    struct rt_spi_configuration *cfg = &qspi_cfg->parent;
    struct at32_qspi_bus *qspi_bus = device->parent.bus->parent.user_data;

    at32_msp_qspi_init(qspi_bus->qspi_x);

    /* switch to cmd port */
    qspi_xip_enable(qspi_bus->qspi_x, FALSE);

    /* get clocks and config qspi clock div */
    crm_clocks_freq_get(&clocks);

    while (cfg->max_hz < clocks.ahb_freq / qspi_div_tab[i])
    {
        i++;
        if (i == 8)
        {
            LOG_E("qspi init failed, qspi frequency(%d) is too low.", cfg->max_hz);
            return -RT_ERROR;
        }
    }
    /* set qspi sclk */
    qspi_clk_division_set(qspi_bus->qspi_x, (qspi_clk_div_type)i);

    if (!(cfg->mode & RT_SPI_CPOL))
    {
        /* qspi mode0 */
        qspi_sck_mode_set(qspi_bus->qspi_x, QSPI_SCK_MODE_0);
    }
    else
    {
        /* qspi mode3 */
        qspi_sck_mode_set(qspi_bus->qspi_x, QSPI_SCK_MODE_3);
    }

    /* flash size */
    qspi_bus->qspi_x->fsize = POSITION_VAL(qspi_cfg->medium_size) - 1;

    return result;
}

static void qspi_send_cmd(struct at32_qspi_bus *qspi_bus, struct rt_qspi_message *message, rt_bool_t dir)
{
    qspi_cmd_type cmd;

    RT_ASSERT(qspi_bus != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    /* set qspi cmd struct */
    cmd.instruction_code = message->instruction.content;
    cmd.address_code = message->address.content;
    cmd.second_dummy_cycle_num = message->dummy_cycles;

    /* address length */
    if (message->address.size == 0)
    {
        cmd.address_length = QSPI_CMD_ADRLEN_0_BYTE;
    }
    else if (message->address.size == 8)
    {
        cmd.address_length = QSPI_CMD_ADRLEN_1_BYTE;
    }
    else if (message->address.size == 16)
    {
        cmd.address_length = QSPI_CMD_ADRLEN_2_BYTE;
    }
    else if (message->address.size == 24)
    {
        cmd.address_length = QSPI_CMD_ADRLEN_3_BYTE;
    }
    else if (message->address.size == 32)
    {
        cmd.address_length = QSPI_CMD_ADRLEN_4_BYTE;
    }

    /* instruction length */
    if (message->instruction.qspi_lines == 0)
    {
        cmd.instruction_length = QSPI_CMD_INSLEN_0_BYTE;
    }
    else
    {
        cmd.instruction_length = QSPI_CMD_INSLEN_1_BYTE;
    }

    /* operate mode */
    switch(message->instruction.qspi_lines)
    {
        case 0:
        case 1:
        {
            switch(message->address.qspi_lines)
            {
                case 0:
                case 1:
                {
                    switch(message->qspi_data_lines)
                    {
                        case 1:
                        {
                            cmd.operation_mode = QSPI_OPERATE_MODE_111;
                            break;
                        }
                        case 2:
                        {
                            cmd.operation_mode = QSPI_OPERATE_MODE_112;
                            break;
                        }
                        case 4:
                        {
                            cmd.operation_mode = QSPI_OPERATE_MODE_114;
                            break;
                        }
                        default:
                        {
                            cmd.operation_mode = QSPI_OPERATE_MODE_111;
                            break;
                        }
                    }
                    break;
                }
                case 2:
                {
                    cmd.operation_mode = QSPI_OPERATE_MODE_122;
                    break;
                }
                case 4:
                {
                    cmd.operation_mode = QSPI_OPERATE_MODE_144;
                    break;
                }
            }
            break;
        }
        case 2:
        {
            cmd.operation_mode = QSPI_OPERATE_MODE_222;
            break;
        }
        case 4:
        {
            cmd.operation_mode = QSPI_OPERATE_MODE_444;
            break;
        }
        default:
        {
            cmd.operation_mode = QSPI_OPERATE_MODE_111;
            break;
        }
    }

    cmd.pe_mode_enable = FALSE;
    cmd.pe_mode_operate_code = 0;
    cmd.read_status_enable = FALSE;
    cmd.read_status_config = QSPI_RSTSC_SW_ONCE;

    if(dir == 1)
    {
        cmd.write_data_enable = TRUE;
    }
    else
    {
        cmd.write_data_enable = FALSE;
    }

    cmd.data_counter = message->parent.length;

    qspi_cmd_operation_kick(qspi_bus->qspi_x, &cmd);

    /* no date need to be processed, wait command completed. */
    if(cmd.data_counter == 0)
    {
        while(qspi_flag_get(qspi_bus->qspi_x, QSPI_CMDSTS_FLAG) == RESET);
        qspi_flag_clear(qspi_bus->qspi_x, QSPI_CMDSTS_FLAG);
    }
}

static error_status qspi_data_transmit(struct at32_qspi_bus *qspi_bus, rt_uint8_t* buf, rt_uint32_t length, rt_uint32_t timeout)
{
    rt_uint32_t index = 0, ticks = 0, len = length;

    for(index = 0; index < len; index++)
    {
        /* wait fifo ready */
        ticks = 0;
        while((qspi_flag_get(qspi_bus->qspi_x, QSPI_TXFIFORDY_FLAG) == RESET) && (ticks <= timeout))
        {
            ticks ++;
        }
        if(ticks >= timeout)
        {
            return ERROR;
        }

        /* write data */
        qspi_byte_write(qspi_bus->qspi_x, *buf++);
    }

    /* wait command completed. */
    ticks = 0;
    while((qspi_flag_get(qspi_bus->qspi_x, QSPI_CMDSTS_FLAG) == RESET) && (ticks <= timeout))
    {
        ticks++;
    }
    if(ticks >= timeout)
    {
        return ERROR;
    }
    /* clear cmdsts flag */
    qspi_flag_clear(qspi_bus->qspi_x, QSPI_CMDSTS_FLAG);

    return SUCCESS;
}

static error_status qspi_data_receive(struct at32_qspi_bus *qspi_bus, rt_uint8_t* buf, rt_uint32_t length, rt_uint32_t timeout)
{
    rt_uint32_t index = 0, ticks = 0, len = 0;

    do
    {
        if(length >= QSPI_FIFO_DEPTH)
        {
            len = QSPI_FIFO_DEPTH;
        }
        else
        {
            len = length;
        }

        /* wait fifo ready */
        ticks = 0;
        while((qspi_flag_get(qspi_bus->qspi_x, QSPI_RXFIFORDY_FLAG) == RESET) && (ticks <= timeout))
        {
            ticks ++;
        }
        if(ticks >= timeout)
        {
            return ERROR;
        }

        /* read data */
        for(index = 0; index < len; index++)
        {
            *buf++ = qspi_byte_read(qspi_bus->qspi_x);
        }

        length -= len;
    } while(length);

    /* wait command completed. */
    ticks = 0;
    while((qspi_flag_get(qspi_bus->qspi_x, QSPI_CMDSTS_FLAG) == RESET) && (ticks <= timeout))
    {
        ticks++;
    }
    if(ticks >= timeout)
    {
        return ERROR;
    }
    /* clear cmdsts flag */
    qspi_flag_clear(qspi_bus->qspi_x, QSPI_CMDSTS_FLAG);

    return SUCCESS;
}

static rt_uint32_t qspi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    rt_size_t len = 0;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);

    struct rt_qspi_message *qspi_message = (struct rt_qspi_message *)message;
    struct at32_qspi_bus *qspi_bus = device->bus->parent.user_data;
#ifdef BSP_QSPI_USING_SOFTCS
    struct at32_hw_spi_cs *cs = device->parent.user_data;
#endif

    const rt_uint8_t *sndb = message->send_buf;
    rt_uint8_t *rcvb = message->recv_buf;
    rt_int32_t length = message->length;

#ifdef BSP_QSPI_USING_SOFTCS
    if (message->cs_take)
    {
        rt_pin_write(cs->pin, 0);
    }
#endif

    /* send data */
    if (sndb)
    {
        /* dir == 1, send */
        qspi_send_cmd(qspi_bus, qspi_message, 1);

        if (qspi_message->parent.length != 0)
        {
            if(qspi_data_transmit(qspi_bus, (rt_uint8_t *)sndb, length, 0xFFFF) == SUCCESS)
            {
                len = length;
            }
            else
            {
                LOG_E("qspi send data failed!");
                goto __exit;
            }
        }
        else
        {
            len = 1;
        }
    }
    /* recv data */
    else if (rcvb)
    {
        /* dir == 0, recv */
        qspi_send_cmd(qspi_bus, qspi_message, 0);

        if(qspi_data_receive(qspi_bus, (rt_uint8_t *)rcvb, length, 0xFFFF) == SUCCESS)
        {
            len = length;
        }
        else
        {
            LOG_E("qspi recv data failed!");
            goto __exit;
        }
    }

__exit:
#ifdef BSP_QSPI_USING_SOFTCS
    if (message->cs_release)
    {
        rt_pin_write(cs->pin, 1);
    }
#endif
    return len;
}

static rt_err_t qspi_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    struct rt_qspi_device *qspi_device = (struct rt_qspi_device *)device;
    return at32_qspi_init(qspi_device, &qspi_device->config);
}

static const struct rt_spi_ops at32_qspi_ops =
{
    .configure = qspi_configure,
    .xfer = qspi_xfer,
};

/**
  * @brief  this function attach device to qspi bus.
  * @param  device_name      qspi device name
  * @param  pin              qspi cs pin number
  * @param  data_line_width  qspi data lines width, such as 1, 2, 4
  * @param  enter_qspi_mode  callback function that lets flash enter qspi mode
  * @param  exit_qspi_mode   callback function that lets flash exit qspi mode
  * @retval 0 : success
  *        -1 : failed
  */
rt_err_t at32_qspi_bus_attach_device(const char *bus_name, const char *device_name, rt_uint32_t pin, rt_uint8_t data_line_width, void (*enter_qspi_mode)(), void (*exit_qspi_mode)())
{
    struct rt_qspi_device *qspi_device = RT_NULL;
    struct at32_hw_spi_cs *cs_pin = RT_NULL;
    rt_err_t result = RT_EOK;

    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);
    RT_ASSERT(data_line_width == 1 || data_line_width == 2 || data_line_width == 4);

    qspi_device = (struct rt_qspi_device *)rt_malloc(sizeof(struct rt_qspi_device));
    if (qspi_device == RT_NULL)
    {
        LOG_E("no memory, qspi bus attach device failed!");
        result = -RT_ENOMEM;
        goto __exit;
    }
    cs_pin = (struct at32_hw_spi_cs *)rt_malloc(sizeof(struct at32_hw_spi_cs));
    if (qspi_device == RT_NULL)
    {
        LOG_E("no memory, qspi bus attach device failed!");
        result = -RT_ENOMEM;
        goto __exit;
    }

    qspi_device->enter_qspi_mode = enter_qspi_mode;
    qspi_device->exit_qspi_mode = exit_qspi_mode;
    qspi_device->config.qspi_dl_width = data_line_width;

    cs_pin->pin = pin;
#ifdef BSP_QSPI_USING_SOFTCS
    rt_pin_mode(pin, PIN_MODE_OUTPUT);
    rt_pin_write(pin, 1);
#endif

    result = rt_spi_bus_attach_device(&qspi_device->parent, device_name, bus_name, (void *)cs_pin);

__exit:
    if (result != RT_EOK)
    {
        if (qspi_device)
        {
            rt_free(qspi_device);
        }

        if (cs_pin)
        {
            rt_free(cs_pin);
        }
    }

    return  result;
}

static int rt_hw_qspi_bus_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for(i = 0; i < sizeof(at32_qspi_obj) / sizeof(at32_qspi_obj[0]); i++)
    {
        at32_qspi_obj[i].qspi_device.parent.user_data = &at32_qspi_obj[i];

        if(rt_qspi_bus_register(&at32_qspi_obj[i].qspi_device, at32_qspi_obj[i].bus_name, &at32_qspi_ops) == RT_EOK)
        {
            LOG_D("%s register success", at32_qspi_obj[i].bus_name);
        }
        else
        {
            LOG_D("%s register failed", at32_qspi_obj[i].bus_name);
            result = -RT_ERROR;
        }
    }

    return result;
}

INIT_BOARD_EXPORT(rt_hw_qspi_bus_init);

#endif /* BSP_USING_QSPI */
