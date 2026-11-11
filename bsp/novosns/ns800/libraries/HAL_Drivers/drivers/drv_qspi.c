/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2026-05-17     lugl              first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "qspi.h"
#include "board.h"

#ifdef RT_USING_QSPI

/*===========================================================================
 * GPIO initialization
 *===========================================================================*/
static void qspi_pin_init(void)
{
    GPIO_setPinConfig(GPIO_15_QSPI_NCS);
    GPIO_setAnalogMode(GPIO_15, GPIO_ANALOG_DISABLED);
    GPIO_setPadConfig(GPIO_15, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(GPIO_15, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(GPIO_16_QSPI_D0);
    GPIO_setAnalogMode(GPIO_16, GPIO_ANALOG_DISABLED);
    GPIO_setPadConfig(GPIO_16, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(GPIO_16, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(GPIO_16, GPIO_DIR_MODE_OUT);

    GPIO_setPinConfig(GPIO_17_QSPI_D1);
    GPIO_setAnalogMode(GPIO_17, GPIO_ANALOG_DISABLED);
    GPIO_setPadConfig(GPIO_17, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(GPIO_17, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(GPIO_17, GPIO_DIR_MODE_IN);

    GPIO_setPinConfig(GPIO_18_QSPI_D2);
    GPIO_setAnalogMode(GPIO_18, GPIO_ANALOG_DISABLED);
    GPIO_setPadConfig(GPIO_18, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(GPIO_18, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(GPIO_18, GPIO_DIR_MODE_IN);

    GPIO_setPinConfig(GPIO_20_QSPI_D3);
    GPIO_setAnalogMode(GPIO_20, GPIO_ANALOG_DISABLED);
    GPIO_setPadConfig(GPIO_20, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(GPIO_20, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(GPIO_20, GPIO_DIR_MODE_IN);

    GPIO_setPinConfig(GPIO_21_QSPI_SCLK);
    GPIO_setAnalogMode(GPIO_21, GPIO_ANALOG_DISABLED);
    GPIO_setPadConfig(GPIO_21, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(GPIO_21, GPIO_QUAL_ASYNC);
}

/*===========================================================================
 * QSPI clock & controller initialization
 *===========================================================================*/
static void qspi_clock_enable(void)
{
    RCC_unlockRccRegister();
    RCC_enableQspiClock();
    RCC_resetQspiModule();
    RCC_releaseQspiModule();
    RCC_lockRccRegister();
}

static void qspi_controller_init(void)
{
    QSPI_open(EXTENDED_SPI_PROTOCOL,
              HLCK_DIV_48,
              ADDRESS_3_BYTES,
              DEFAULT_DUMMY_CYCLE,
              HIGH_LVL_4_QSCK,
              FAST_READ_QUAD_IN_OUT);
}

/*===========================================================================
 * RT-Thread QSPI device interface
 *===========================================================================*/
static struct rt_spi_bus qspi_bus;
static struct rt_qspi_device qspi_dev;
static struct rt_qspi_configuration qspi_cfg;

static rt_err_t qspi_configure(struct rt_spi_device *device,
                               struct rt_spi_configuration *cfg)
{
    device->config = *cfg;
    return RT_EOK;
}

static rt_ssize_t qspi_xfer(struct rt_spi_device *device,
                            struct rt_spi_message *message)
{
    struct rt_qspi_message *qspi_msg = rt_container_of(message, struct rt_qspi_message, parent);
    uint8_t *send_buf = (uint8_t *)message->send_buf;
    uint8_t *recv_buf = (uint8_t *)message->recv_buf;
    uint32_t send_len = (send_buf != NULL) ? message->length : 0;
    uint32_t recv_len = (recv_buf != NULL) ? message->length : 0;

    /* Build command buffer (instruction + address + dummy) */
    uint8_t cmd_buf[260];
    uint8_t *ptr = cmd_buf;

    if (qspi_msg->instruction.content)
        *ptr++ = qspi_msg->instruction.content;

    if (qspi_msg->address.size)
    {
        uint32_t addr = qspi_msg->address.content;
        uint8_t addr_bytes = qspi_msg->address.size / 8;
        for (uint8_t i = addr_bytes; i > 0; i--)
            *ptr++ = (addr >> (8*(i-1))) & 0xFF;
    }

    if (qspi_msg->dummy_cycles)
    {
        uint8_t dummy_bytes = qspi_msg->dummy_cycles / 8;
        for (uint8_t i = 0; i < dummy_bytes; i++)
            *ptr++ = 0xFF;
    }

    uint32_t cmd_len = ptr - cmd_buf;

    /* Execute transfer using direct API */
    if (send_len && recv_len)
    {
        /* Half-duplex not supported in this driver */
        return 0;
    }

    if (send_len)
    {
        /* Append send data to command buffer */
        if (cmd_len + send_len <= sizeof(cmd_buf))
        {
            rt_memcpy(ptr, send_buf, send_len);
            QSPI_writeDirect(cmd_buf, cmd_len + send_len, 0);
        } else {
            /* Not enough buffer, split into two writes? Not needed for normal use */
            return 0;
        }
    } else if (recv_len)
    {
        /* Write command, keep CS active, then read data */
        QSPI_writeDirect(cmd_buf, cmd_len, 1);
        QSPI_readDirect(recv_buf, recv_len);
    } else {
        /* No data phase, just send command */
        QSPI_writeDirect(cmd_buf, cmd_len, 0);
    }

    return message->length;
}

static const struct rt_spi_ops qspi_ops = {
    .configure = qspi_configure,
    .xfer = qspi_xfer,
};

/*===========================================================================
 * Initialization
 *===========================================================================*/
int rt_hw_qspi_init(void)
{
    rt_kprintf("Initializing QSPI...\n");
    qspi_clock_enable();
    qspi_pin_init();
    qspi_controller_init();

    qspi_cfg.parent.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;
    qspi_cfg.parent.max_hz = 25000000;
    qspi_cfg.parent.data_width = 8;
    qspi_cfg.medium_size = 0x1000000;
    qspi_cfg.ddr_mode = 0;
    qspi_cfg.qspi_dl_width = 0;

    rt_qspi_bus_register(&qspi_bus, "qspi0", &qspi_ops);

    qspi_dev.parent.bus = &qspi_bus;
    qspi_dev.parent.config = qspi_cfg.parent;
    qspi_dev.config = qspi_cfg;
    rt_spi_bus_attach_device(&qspi_dev.parent, "qspi_dev", "qspi0", NULL);

    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_qspi_init);

#endif

