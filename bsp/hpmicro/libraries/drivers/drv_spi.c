/*
 * Copyright (c) 2021-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2022-02-01   HPMicro     First version
 * 2023-02-15   HPMicro     Add DMA support
 * 2023-07-14   HPMicro     Manage the DMA buffer alignment in driver
 * 2023-12-14   HPMicro     change state blocking wait to interrupt semaphore wait for DMA
 * 2024-06-10   HPMicro     Add the SPI pin settings
 * 2025-03-17   HPMicro     Improve SPI driver,support SPI/DSPI/QSPI
 * 2025-07-14   HPMicro     Check CS pin in xfer API
 * 2025-08-05   HPMicro     Optimized cache alignment handling for DMA transfers
 */
#include <rtthread.h>

#ifdef BSP_USING_SPI
#include <rtdevice.h>
#include "board.h"
#include "drv_spi.h"
#include "hpm_spi_drv.h"
#include "hpm_sysctl_drv.h"
#include "hpm_dma_mgr.h"
#include "hpm_dmamux_drv.h"

#include "hpm_l1c_drv.h"
#include "hpm_clock_drv.h"
#define DBG_TAG    "drv.spi"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#if defined(BSP_USING_SPI0)
#ifndef BSP_SPI0_USING_QUAD_IO
#ifndef BSP_SPI0_USING_DUAL_IO
#ifndef BSP_SPI0_USING_SINGLE_IO
#define BSP_SPI0_USING_SINGLE_IO
#endif
#endif
#endif
#endif

#if defined(BSP_USING_SPI1)
#ifndef BSP_SPI1_USING_QUAD_IO
#ifndef BSP_SPI1_USING_DUAL_IO
#ifndef BSP_SPI1_USING_SINGLE_IO
#define BSP_SPI1_USING_SINGLE_IO
#endif
#endif
#endif
#endif

#if defined(BSP_USING_SPI2)
#ifndef BSP_SPI2_USING_QUAD_IO
#ifndef BSP_SPI2_USING_DUAL_IO
#ifndef BSP_SPI2_USING_SINGLE_IO
#define BSP_SPI2_USING_SINGLE_IO
#endif
#endif
#endif
#endif

#if defined(BSP_USING_SPI3)
#ifndef BSP_SPI3_USING_QUAD_IO
#ifndef BSP_SPI3_USING_DUAL_IO
#ifndef BSP_SPI3_USING_SINGLE_IO
#define BSP_SPI3_USING_SINGLE_IO
#endif
#endif
#endif
#endif

#if defined(BSP_USING_SPI4)
#ifndef BSP_SPI4_USING_QUAD_IO
#ifndef BSP_SPI4_USING_DUAL_IO
#ifndef BSP_SPI4_USING_SINGLE_IO
#define BSP_SPI4_USING_SINGLE_IO
#endif
#endif
#endif
#endif

#if defined(BSP_USING_SPI5)
#ifndef BSP_SPI5_USING_QUAD_IO
#ifndef BSP_SPI5_USING_DUAL_IO
#ifndef BSP_SPI5_USING_SINGLE_IO
#define BSP_SPI5_USING_SINGLE_IO
#endif
#endif
#endif
#endif

#if defined(BSP_USING_SPI6)
#ifndef BSP_SPI6_USING_QUAD_IO
#ifndef BSP_SPI6_USING_DUAL_IO
#ifndef BSP_SPI6_USING_SINGLE_IO
#define BSP_SPI6_USING_SINGLE_IO
#endif
#endif
#endif
#endif

#if defined(BSP_USING_SPI7)
#ifndef BSP_SPI7_USING_QUAD_IO
#ifndef BSP_SPI7_USING_DUAL_IO
#ifndef BSP_SPI7_USING_SINGLE_IO
#define BSP_SPI7_USING_SINGLE_IO
#endif
#endif
#endif
#endif


struct hpm_spi
{
    uint32_t instance;
    char *bus_name;
    SPI_Type *spi_base;
    clock_name_t clk_name;
    spi_data_phase_format_t spi_io_mode;
    spi_control_config_t control_config;
    struct rt_spi_bus spi_bus;
    rt_sem_t xfer_sem;
    rt_bool_t enable_dma;
    rt_uint8_t tx_dmamux;
    rt_uint8_t rx_dmamux;
    dma_resource_t tx_dma;
    dma_resource_t rx_dma;
    rt_uint8_t spi_irq;
    rt_uint8_t spi_irq_priority;
    rt_sem_t spi_xfer_done_sem;
    rt_sem_t txdma_xfer_done_sem;
    rt_sem_t rxdma_xfer_done_sem;
    void (*spi_pins_init)(SPI_Type *spi_base);
};

typedef struct {
    rt_uint8_t *raw_alloc_tx_buf;
    rt_uint8_t *raw_alloc_rx_buf;
    rt_uint8_t *aligned_tx_buf;
    rt_uint8_t *aligned_rx_buf;
    rt_uint32_t aligned_size;
} spi_dma_buf_ctx_t;

static rt_err_t hpm_spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg);
static rt_ssize_t hpm_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *msg);

static struct hpm_spi hpm_spis[] =
{
#if defined(BSP_USING_SPI0)
    {
#if defined(BSP_SPI0_USING_SINGLE_IO)
        .bus_name = "spi0",
        .spi_io_mode = spi_single_io_mode,
#endif
#if defined(BSP_SPI0_USING_DUAL_IO)
        .bus_name = "dspi0",
        .spi_io_mode = spi_dual_io_mode,
#endif
#if defined(BSP_SPI0_USING_QUAD_IO)
        .bus_name = "qspi0",
        .spi_io_mode = spi_quad_io_mode,
#endif
        .spi_base = HPM_SPI0,
        .clk_name = clock_spi0,
#if defined(BSP_SPI0_USING_DMA)
        .enable_dma = RT_TRUE,
#endif
        .tx_dmamux = HPM_DMA_SRC_SPI0_TX,
        .rx_dmamux = HPM_DMA_SRC_SPI0_RX,
        .spi_irq   = IRQn_SPI0,
#if defined(BSP_SPI0_IRQ_PRIORITY)
        .spi_irq_priority = BSP_SPI0_IRQ_PRIORITY,
#else
        .spi_irq_priority = 1,
#endif
#if !defined BSP_SPI0_USING_HARD_CS
        .spi_pins_init = init_spi_pins_with_gpio_as_cs,
#else
        .spi_pins_init = init_spi_pins,
#endif
    },
#endif
#if defined(BSP_USING_SPI1)
    {
#if defined(BSP_SPI1_USING_SINGLE_IO)
        .bus_name = "spi1",
        .spi_io_mode = spi_single_io_mode,
#endif
#if defined(BSP_SPI1_USING_DUAL_IO)
        .bus_name = "dspi1",
        .spi_io_mode = spi_dual_io_mode,
#endif
#if defined(BSP_SPI1_USING_QUAD_IO)
        .bus_name = "qspi1",
        .spi_io_mode = spi_quad_io_mode,
#endif
        .spi_base = HPM_SPI1,
        .clk_name = clock_spi1,
#if defined(BSP_SPI1_USING_DMA)
        .enable_dma = RT_TRUE,
#endif
        .tx_dmamux = HPM_DMA_SRC_SPI1_TX,
        .rx_dmamux = HPM_DMA_SRC_SPI1_RX,
        .spi_irq   = IRQn_SPI1,
#if defined(BSP_SPI1_IRQ_PRIORITY)
       .spi_irq_priority = BSP_SPI1_IRQ_PRIORITY,
#else
       .spi_irq_priority = 1,
#endif
#if !defined BSP_SPI1_USING_HARD_CS
        .spi_pins_init = init_spi_pins_with_gpio_as_cs,
#else
        .spi_pins_init = init_spi_pins,
#endif
    },
#endif
#if defined(BSP_USING_SPI2)
    {
#if defined(BSP_SPI2_USING_SINGLE_IO)
        .bus_name = "spi2",
        .spi_io_mode = spi_single_io_mode,
#endif
#if defined(BSP_SPI2_USING_DUAL_IO)
        .bus_name = "dspi2",
        .spi_io_mode = spi_dual_io_mode,
#endif
#if defined(BSP_SPI2_USING_QUAD_IO)
        .bus_name = "qspi2",
        .spi_io_mode = spi_quad_io_mode,
#endif
        .spi_base = HPM_SPI2,
        .clk_name = clock_spi2,
#if defined(BSP_SPI2_USING_DMA)
        .enable_dma = RT_TRUE,
#endif
        .tx_dmamux = HPM_DMA_SRC_SPI2_TX,
        .rx_dmamux = HPM_DMA_SRC_SPI2_RX,
        .spi_irq   = IRQn_SPI2,
#if defined(BSP_SPI2_IRQ_PRIORITY)
      .spi_irq_priority = BSP_SPI2_IRQ_PRIORITY,
#else
      .spi_irq_priority = 1,
#endif
#if !defined BSP_SPI2_USING_HARD_CS
        .spi_pins_init = init_spi_pins_with_gpio_as_cs,
#else
        .spi_pins_init = init_spi_pins,
#endif
    },
#endif
#if defined(BSP_USING_SPI3)
    {
#if defined(BSP_SPI3_USING_SINGLE_IO)
        .bus_name = "spi3",
        .spi_io_mode = spi_single_io_mode,
#endif
#if defined(BSP_SPI3_USING_DUAL_IO)
        .bus_name = "dspi3",
        .spi_io_mode = spi_dual_io_mode,
#endif
#if defined(BSP_SPI3_USING_QUAD_IO)
        .bus_name = "qspi3",
        .spi_io_mode = spi_quad_io_mode,
#endif
        .spi_base = HPM_SPI3,
        .clk_name = clock_spi3,
#if defined(BSP_SPI3_USING_DMA)
        .enable_dma = RT_TRUE,
#endif
        .tx_dmamux = HPM_DMA_SRC_SPI3_TX,
        .rx_dmamux = HPM_DMA_SRC_SPI3_RX,
        .spi_irq   = IRQn_SPI3,
#if defined(BSP_SPI3_IRQ_PRIORITY)
        .spi_irq_priority = BSP_SPI3_IRQ_PRIORITY,
#else
        .spi_irq_priority = 1,
#endif
#if !defined BSP_SPI3_USING_HARD_CS
        .spi_pins_init = init_spi_pins_with_gpio_as_cs,
#else
        .spi_pins_init = init_spi_pins,
#endif
    },
#endif
#if defined(BSP_USING_SPI4)
    {
#if defined(BSP_SPI4_USING_SINGLE_IO)
        .bus_name = "spi4",
        .spi_io_mode = spi_single_io_mode,
#endif
#if defined(BSP_SPI4_USING_DUAL_IO)
        .bus_name = "dspi4",
        .spi_io_mode = spi_dual_io_mode,
#endif
#if defined(BSP_SPI4_USING_QUAD_IO)
        .bus_name = "qspi4",
        .spi_io_mode = spi_quad_io_mode,
#endif
        .spi_base = HPM_SPI4,
        .clk_name = clock_spi4,
#if defined(BSP_SPI4_USING_DMA)
        .enable_dma = RT_TRUE,
#endif
        .tx_dmamux = HPM_DMA_SRC_SPI4_TX,
        .rx_dmamux = HPM_DMA_SRC_SPI4_RX,
        .spi_irq   = IRQn_SPI4,
#if defined(BSP_SPI4_IRQ_PRIORITY)
       .spi_irq_priority = BSP_SPI4_IRQ_PRIORITY,
#else
       .spi_irq_priority = 1,
#endif
#if !defined BSP_SPI4_USING_HARD_CS
        .spi_pins_init = init_spi_pins_with_gpio_as_cs,
#else
        .spi_pins_init = init_spi_pins,
#endif
    },
#endif
#if defined(BSP_USING_SPI5)
    {
#if defined(BSP_SPI5_USING_SINGLE_IO)
        .bus_name = "spi5",
        .spi_io_mode = spi_single_io_mode,
#endif
#if defined(BSP_SPI5_USING_DUAL_IO)
        .bus_name = "dspi5",
        .spi_io_mode = spi_dual_io_mode,
#endif
#if defined(BSP_SPI5_USING_QUAD_IO)
        .bus_name = "qspi5",
        .spi_io_mode = spi_quad_io_mode,
#endif
        .spi_base = HPM_SPI5,
        .clk_name = clock_spi5,
#if defined(BSP_SPI5_USING_DMA)
        .enable_dma = RT_TRUE,
#endif
        .tx_dmamux = HPM_DMA_SRC_SPI5_TX,
        .rx_dmamux = HPM_DMA_SRC_SPI5_RX,
        .spi_irq   = IRQn_SPI5,
#if defined(BSP_SPI5_IRQ_PRIORITY)
        .spi_irq_priority = BSP_SPI5_IRQ_PRIORITY,
#else
        .spi_irq_priority = 1,
#endif
#if !defined BSP_SPI5_USING_HARD_CS
        .spi_pins_init = init_spi_pins_with_gpio_as_cs,
#else
        .spi_pins_init = init_spi_pins,
#endif
    },
#endif
#if defined(BSP_USING_SPI6)
    {
#if defined(BSP_SPI6_USING_SINGLE_IO)
        .bus_name = "spi6",
        .spi_io_mode = spi_single_io_mode,
#endif
#if defined(BSP_SPI6_USING_DUAL_IO)
        .bus_name = "dspi6",
        .spi_io_mode = spi_dual_io_mode,
#endif
#if defined(BSP_SPI6_USING_QUAD_IO)
        .bus_name = "qspi6",
        .spi_io_mode = spi_quad_io_mode,
#endif
        .spi_base = HPM_SPI6,
        .clk_name = clock_spi6,
#if defined(BSP_SPI6_USING_DMA)
        .enable_dma = RT_TRUE,
#endif
        .tx_dmamux = HPM_DMA_SRC_SPI6_TX,
        .rx_dmamux = HPM_DMA_SRC_SPI6_RX,
        .spi_irq   = IRQn_SPI6,
#if defined(BSP_SPI6_IRQ_PRIORITY)
        .spi_irq_priority = BSP_SPI6_IRQ_PRIORITY,
#else
        .spi_irq_priority = 1,
#endif
#if !defined BSP_SPI6_USING_HARD_CS
        .spi_pins_init = init_spi_pins_with_gpio_as_cs,
#else
        .spi_pins_init = init_spi_pins,
#endif
    },
#endif
#if defined(BSP_USING_SPI7)
    {
#if defined(BSP_SPI7_USING_SINGLE_IO)
        .bus_name = "spi7",
        .spi_io_mode = spi_single_io_mode,
#endif
#if defined(BSP_SPI7_USING_DUAL_IO)
        .bus_name = "dspi7",
        .spi_io_mode = spi_dual_io_mode,
#endif
#if defined(BSP_SPI7_USING_QUAD_IO)
        .bus_name = "qspi7",
        .spi_io_mode = spi_quad_io_mode,
#endif
        .spi_base = HPM_SPI7,
        .clk_name = clock_spi7,
#if defined(BSP_SPI7_USING_DMA)
        .enable_dma = RT_TRUE,
#endif
        .tx_dmamux = HPM_DMA_SRC_SPI7_TX,
        .rx_dmamux = HPM_DMA_SRC_SPI7_RX,
        .spi_irq   = IRQn_SPI7,
#if defined(BSP_SPI7_IRQ_PRIORITY)
        .spi_irq_priority = BSP_SPI7_IRQ_PRIORITY,
#else
        .spi_irq_priority = 1,
#endif
#if !defined BSP_SPI7_USING_HARD_CS
        .spi_pins_init = init_spi_pins_with_gpio_as_cs,
#else
        .spi_pins_init = init_spi_pins,
#endif
    },
#endif
};
static struct rt_spi_ops hpm_spi_ops =
{
    .configure = hpm_spi_configure,
    .xfer = hpm_spi_xfer,
};

static inline void handle_spi_isr(SPI_Type *ptr)
{
    volatile uint32_t irq_status;
    RT_ASSERT(ptr != RT_NULL);
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    irq_status = spi_get_interrupt_status(ptr);
    if (irq_status & spi_end_int)
    {
        spi_clear_interrupt_status(ptr, spi_end_int);
        for (uint32_t i = 0; i < sizeof(hpm_spis) / sizeof(hpm_spis[0]); i++)
        {
            if (hpm_spis[i].spi_base == ptr)
            {
                rt_sem_release(hpm_spis[i].spi_xfer_done_sem);
                break;
            }
        }
    }
    rt_hw_interrupt_enable(level);
}

#if defined(BSP_USING_SPI0)
SDK_DECLARE_EXT_ISR_M(IRQn_SPI0, spi0_isr);
void spi0_isr(void)
{
    handle_spi_isr(HPM_SPI0);
}
#endif

#if defined(BSP_USING_SPI1)
SDK_DECLARE_EXT_ISR_M(IRQn_SPI1, spi1_isr);
void spi1_isr(void)
{
    handle_spi_isr(HPM_SPI1);
}
#endif

#if defined(BSP_USING_SPI2)
SDK_DECLARE_EXT_ISR_M(IRQn_SPI2, spi2_isr);
void spi2_isr(void)
{
    handle_spi_isr(HPM_SPI2);
}
#endif

#if defined(BSP_USING_SPI3)
SDK_DECLARE_EXT_ISR_M(IRQn_SPI3, spi3_isr);
void spi3_isr(void)
{
    handle_spi_isr(HPM_SPI3);
}
#endif

#if defined(BSP_USING_SPI4)
SDK_DECLARE_EXT_ISR_M(IRQn_SPI4, spi4_isr);
void spi4_isr(void)
{
    handle_spi_isr(HPM_SPI4);
}
#endif

#if defined(BSP_USING_SPI5)
SDK_DECLARE_EXT_ISR_M(IRQn_SPI5, spi5_isr);
void spi5_isr(void)
{
    handle_spi_isr(HPM_SPI5);
}
#endif

#if defined(BSP_USING_SPI6)
SDK_DECLARE_EXT_ISR_M(IRQn_SPI6, spi6_isr);
void spi6_isr(void)
{
    handle_spi_isr(HPM_SPI6);
}
#endif

#if defined(BSP_USING_SPI7)
SDK_DECLARE_EXT_ISR_M(IRQn_SPI7, spi7_isr);
void spi7_isr(void)
{
    handle_spi_isr(HPM_SPI7);
}
#endif

void spi_dma_channel_tc_callback(DMA_Type *ptr, uint32_t channel, void *user_data)
{
    struct hpm_spi *spi = (struct hpm_spi *)user_data;
    RT_ASSERT(spi != RT_NULL);
    RT_ASSERT(ptr != RT_NULL);
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    if ((spi->tx_dma.base == ptr) && spi->tx_dma.channel == channel)
    {
        dma_mgr_disable_chn_irq(&spi->tx_dma, DMA_MGR_INTERRUPT_MASK_TC);
        rt_sem_release(spi->txdma_xfer_done_sem);
    }
    if ((spi->rx_dma.base == ptr) && spi->rx_dma.channel == channel)
    {
        dma_mgr_disable_chn_irq(&spi->rx_dma, DMA_MGR_INTERRUPT_MASK_TC);
        rt_sem_release(spi->rxdma_xfer_done_sem);
    }
    rt_hw_interrupt_enable(level);
}

static rt_err_t hpm_spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg)
{
    spi_timing_config_t timing_config = { 0 };
    spi_format_config_t format_config = { 0 };
    struct hpm_spi *spi = RT_NULL;
    hpm_stat_t stat = status_success;
    spi = (struct hpm_spi *)(device->bus->parent.user_data);
    RT_ASSERT(spi != RT_NULL);
    /* hpm spi data width support 1 ~ 32 */
    RT_ASSERT((cfg->data_width > 0) && (cfg->data_width <= 32));

    spi->spi_pins_init(spi->spi_base);
    struct rt_spi_configuration *spi_cfg = cfg;

    if (spi_cfg->mode & RT_SPI_SLAVE) {
        spi_slave_get_default_format_config(&format_config);
        spi_slave_get_default_control_config(&spi->control_config);
        spi->control_config.slave_config.slave_data_only = true;
    } else {
        spi_master_get_default_timing_config(&timing_config);
        spi_master_get_default_format_config(&format_config);
        spi_master_get_default_control_config(&spi->control_config);
        timing_config.master_config.cs2sclk = spi_cs2sclk_half_sclk_1;
        timing_config.master_config.csht = spi_csht_half_sclk_1;
        timing_config.master_config.clk_src_freq_in_hz = board_init_spi_clock(spi->spi_base);
        if (spi_cfg->max_hz > timing_config.master_config.clk_src_freq_in_hz) {
            spi_cfg->max_hz = timing_config.master_config.clk_src_freq_in_hz;
        }
        timing_config.master_config.sclk_freq_in_hz = spi_cfg->max_hz;
        stat = spi_master_timing_init(spi->spi_base, &timing_config);
        LOG_D("spi clock frequency = %d, spi sclk frequency = %d", timing_config.master_config.clk_src_freq_in_hz, timing_config.master_config.sclk_freq_in_hz);
        if (stat != status_success) {
            LOG_E("spi clock frequency = %d, spi sclk frequency = %d \n", timing_config.master_config.clk_src_freq_in_hz, timing_config.master_config.sclk_freq_in_hz);
            LOG_E("set spi master sclk frequency fail, SPI_freq / spi_sclk must be an integer multiple and the ratio must be an even number.");
            return -RT_EINVAL;
        }
    }

    format_config.common_config.data_len_in_bits = cfg->data_width;
    format_config.common_config.cpha = (cfg->mode & RT_SPI_CPHA) ? spi_sclk_sampling_even_clk_edges : spi_sclk_sampling_odd_clk_edges;
    format_config.common_config.cpol = (cfg->mode & RT_SPI_CPOL) ? spi_sclk_high_idle : spi_sclk_low_idle;
    format_config.common_config.lsb  = (cfg->mode & RT_SPI_MSB) ? false : true;
    format_config.common_config.mosi_bidir = cfg->mode & RT_SPI_3WIRE ? true : false;
    spi_format_init(spi->spi_base, &format_config);


    spi->control_config.master_config.addr_enable = false;
    spi->control_config.master_config.cmd_enable = false;
    spi->control_config.master_config.token_enable = false;
    spi->control_config.common_config.trans_mode = spi_trans_write_read_together;

    return RT_EOK;
}


static rt_err_t hpm_spi_check_params(struct rt_spi_device *device, struct rt_spi_message *msg)
{
    struct rt_spi_message *spi_msg = (struct rt_spi_message *)msg;

#ifdef RT_USING_QSPI
    struct rt_qspi_message *qspi_msg = (struct rt_qspi_message *)msg;
    struct rt_qspi_device *qspi_dev = (struct rt_qspi_device *)device;
    struct rt_qspi_configuration *qspi_cfg = (struct rt_qspi_configuration *)&qspi_dev->config;
#endif

    if ((device->config.mode == RT_SPI_SLAVE) && (msg->length > SPI_SOC_TRANSFER_COUNT_MAX)) {
        LOG_E("spi SPI transfer cannot exceed %d bytes for slave\n", SPI_SOC_TRANSFER_COUNT_MAX);
        return -RT_EINVAL;
    }

    if ((device->config.mode == RT_SPI_SLAVE) && ((msg->recv_buf == RT_NULL) || (msg->send_buf == RT_NULL)))
    {
        LOG_E("spi only support read write toggther mode for slave\n");
        return -RT_EINVAL;
    }
#ifdef RT_USING_QSPI
    if (device->bus->mode == RT_SPI_BUS_MODE_QSPI) {
        if ((device->config.mode & RT_SPI_MASTER) == RT_SPI_MASTER) {
            if (qspi_msg->instruction.qspi_lines > 1) {
                LOG_E("dspi/qspi only support single instruction(command) phase for master\n");
                return -RT_EINVAL;
            }
        }

        if (((device->config.mode  & RT_SPI_MASTER) == RT_SPI_MASTER) && ((msg->recv_buf != RT_NULL) && (msg->send_buf != RT_NULL)) &&
            (qspi_msg->dummy_cycles > 0)) {
            LOG_E("dspi/qspi only not support dummy phase on read write toggther mode for master\n");
            return -RT_EINVAL;
        }

        if (qspi_msg->address.size != 0) {
            if (((qspi_msg->address.size != 8) && (qspi_msg->address.size != 16) && (qspi_msg->address.size != 24) && (qspi_msg->address.size != 32))) {
                LOG_E("dspi/qspi only support address phase size 8/16/24/32 for master\n");
                return -RT_EINVAL;
            }
        }

        if (qspi_msg->address.qspi_lines != 0) {
            if ((qspi_msg->address.qspi_lines != 1) && (qspi_msg->address.qspi_lines != 2) && (qspi_msg->address.qspi_lines != 4)) {
                LOG_E("dspi/qspi only support address phase qspi lines 1/2/4 for master\n");
                return -RT_EINVAL;
            }
        }

        if (qspi_msg->alternate_bytes.size != 0) {
            LOG_E("dspi/qspi not support alternate phase size 0 for master\n");
            return -RT_EINVAL;
        }

        if (qspi_cfg->qspi_dl_width != 0) {
            switch (qspi_cfg->qspi_dl_width)
            {
            case 1:
                if (qspi_msg->dummy_cycles != 0) {
                    if ((qspi_msg->dummy_cycles > (4 * 8))) {
                        LOG_E("spi only support dummy phase cycles < 32 for master\n");
                        return -RT_EINVAL;
                    }
                    if ((qspi_msg->dummy_cycles != 0) && (qspi_msg->dummy_cycles % 8)) {
                        LOG_E("The number of cycles should be an integer multiple of 8 for spi master\n");
                        return -RT_EINVAL;
                    }
                }
                break;
            case 2:
                if (qspi_msg->dummy_cycles != 0) {
                    if (qspi_msg->dummy_cycles > (4 * 4)) {
                        LOG_E("dspi only support dummy phase cycles < 16 for master\n");
                        return -RT_EINVAL;
                    }
                    if (qspi_msg->dummy_cycles % 4) {
                        LOG_E("The number of cycles should be an integer multiple of 4 for spi master\n");
                        return -RT_EINVAL;
                    }
                }
                break;
            case 4:
                if (qspi_msg->dummy_cycles != 0) {
                    if (qspi_msg->dummy_cycles > (4 * 2)) {
                        LOG_E("qspi only support dummy phase cycles < 8 for master\n");
                        return -RT_EINVAL;
                    }
                    if (qspi_msg->dummy_cycles % 2) {
                        LOG_E("The number of cycles should be an integer multiple of 2 for spi master\n");
                        return -RT_EINVAL;
                    }
                }
                break;
            default:
                LOG_E("spi only support data phase qspi lines 1/2/4 for master\n");
                return -RT_EINVAL;
            }
        }
    }
#endif
    return RT_EOK;
}

bool hpm_qspi_parse_phase_message(struct rt_spi_device *device, struct rt_qspi_message *msg,
                                        spi_control_config_t *control_config, rt_uint8_t *cmd, rt_uint32_t *addr)
{
    rt_uint8_t dummy_bytes = 0;
    bool need_dummy = RT_FALSE;
    struct hpm_spi *spi = (struct hpm_spi *)(device->bus->parent.user_data);
#ifdef RT_USING_QSPI
    struct rt_qspi_message *qspi_msg = (struct rt_qspi_message *)msg;
    struct rt_qspi_device *qspi_dev = (struct rt_qspi_device *)device;
    struct rt_qspi_configuration *qspi_cfg = (struct rt_qspi_configuration *)&qspi_dev->config;
    if ((device->bus->mode == RT_SPI_BUS_MODE_QSPI) && ((device->config.mode & RT_SPI_MASTER) == RT_SPI_MASTER)) {
        if (msg->instruction.qspi_lines == 1) {
            (*cmd) = msg->instruction.content;
            control_config->master_config.cmd_enable = RT_TRUE;
        } else {
            control_config->master_config.cmd_enable = RT_FALSE;
        }
        if (msg->address.qspi_lines != 0) {
            control_config->master_config.addr_enable = RT_TRUE;
            switch (msg->address.qspi_lines) {
            case 1:
                control_config->master_config.addr_phase_fmt = spi_address_phase_format_single_io_mode;
                break;
            case 2:
            case 4:
                control_config->master_config.addr_phase_fmt = spi_address_phase_format_dualquad_io_mode;
                break;
            default:
                break;
            }
        } else {
            control_config->master_config.addr_enable = RT_FALSE;
        }
        if (msg->address.size != 0) {
            (*addr) = msg->address.content;
            control_config->master_config.addr_enable = RT_TRUE;
            switch (msg->address.size) {
                case 8:
                    spi_set_address_len(spi->spi_base, addrlen_8bit);
                    break;
                case 16:
                    spi_set_address_len(spi->spi_base, addrlen_16bit);
                    break;
                case 24:
                    spi_set_address_len(spi->spi_base, addrlen_24bit);
                    break;
                case 32:
                    spi_set_address_len(spi->spi_base, addrlen_32bit);
                    break;
                default:
                    break;
            }
        } else {
            control_config->master_config.addr_enable = RT_FALSE;
        }
        if (msg->dummy_cycles == 0) {
            need_dummy = RT_FALSE;
        } else {
            need_dummy = RT_TRUE;
            switch (msg->qspi_data_lines)
            {
                case 1:
                    dummy_bytes = (msg->dummy_cycles + 7) / 8;
                    break;
                case 2:
                    dummy_bytes = (msg->dummy_cycles + 3) / 4;
                    break;
                case 4:
                    dummy_bytes = (msg->dummy_cycles + 1) / 2;
                    break;
                default:
                    break;
            }
        }
        if (dummy_bytes != 0) {
            switch (dummy_bytes)
            {
                case 1:
                    control_config->common_config.dummy_cnt = spi_dummy_count_1;
                    break;
                case 2:
                    control_config->common_config.dummy_cnt = spi_dummy_count_2;
                    break;
                case 3:
                    control_config->common_config.dummy_cnt = spi_dummy_count_3;
                    break;
                case 4:
                    control_config->common_config.dummy_cnt = spi_dummy_count_4;
                    break;
                default:
                    break;
            }
        }
        if (qspi_cfg->qspi_dl_width == 1) {
            if (msg->qspi_data_lines == 1) {
                spi->control_config.common_config.data_phase_fmt = spi_single_io_mode;
            } else {
                LOG_E("msg data_lines must be 1  when qspi_dl_width is 1, but msg data_lines is %d\n", msg->qspi_data_lines);
            }
        } else if (qspi_cfg->qspi_dl_width == 2) {
            if (msg->qspi_data_lines == 1) {
                spi->control_config.common_config.data_phase_fmt = spi_dual_io_mode;
            } else if (msg->qspi_data_lines == 2) {
                spi->control_config.common_config.data_phase_fmt = spi_quad_io_mode;
            } else {
                LOG_E("msg data_lines must be 1 or 2 when qspi_dl_width is 2, but msg data_lines is %d\n", msg->qspi_data_lines);
            }
        } else if (qspi_cfg->qspi_dl_width == 4) {
            if (msg->qspi_data_lines == 1) {
                spi->control_config.common_config.data_phase_fmt = spi_single_io_mode;
            } else if (msg->qspi_data_lines == 2) {
                spi->control_config.common_config.data_phase_fmt = spi_dual_io_mode;
            } else if (msg->qspi_data_lines == 4) {
                spi->control_config.common_config.data_phase_fmt = spi_quad_io_mode;
            } else {
                spi->control_config.common_config.data_phase_fmt = spi_single_io_mode;
            }
        } else {
            spi->control_config.common_config.data_phase_fmt = spi_single_io_mode;
        }
    }
#endif
    return need_dummy;
}
static rt_ssize_t hpm_spi_send_no_data(SPI_Type *ptr, spi_control_config_t *config, uint8_t *cmd, uint32_t *addr,  struct rt_qspi_message *qspi_msg)
{
    rt_ssize_t actual_len = 0;
    hpm_stat_t spi_stat = status_success;
    if (config->master_config.cmd_enable == true || config->master_config.addr_enable == true) {
        config->common_config.trans_mode = spi_trans_no_data;
        spi_stat = spi_transfer(ptr, config, cmd, addr, NULL, 0, NULL, 0);
        if (spi_stat != status_success) {
            actual_len = -RT_EIO;
        } else {
            if (qspi_msg->instruction.qspi_lines > 0) {
                actual_len++;
            }
            if (qspi_msg->address.size > 0) {
                switch (qspi_msg->address.size)
                {
                case 8:
                    actual_len++;
                    break;
                case 16:
                    actual_len += 2;
                    break;
                case 24:
                    actual_len += 3;
                    break;
                case 32:
                    actual_len += 4;
                    break;
                default:
                    break;
                }
            }
        }
    }
    return actual_len;
}
static rt_ssize_t hpm_spi_xfer_polling(struct rt_spi_device *device, struct rt_spi_message *msg)
{
    struct hpm_spi *spi = (struct hpm_spi *) (device->bus->parent.user_data);
    rt_ssize_t actual_len = 0;
    hpm_stat_t spi_stat = status_success;
    struct rt_spi_message *_msg = (struct rt_spi_message *)msg;
    struct rt_spi_message *spi_msg = (struct rt_spi_message *)_msg;
#ifdef RT_USING_QSPI
    struct rt_qspi_message *qspi_msg = RT_NULL;
#endif
    rt_uint32_t remaining_size = _msg->length;
    rt_uint32_t transfer_len;
    rt_uint8_t *tx_buf = (rt_uint8_t*) _msg->send_buf;
    rt_uint8_t *rx_buf = (rt_uint8_t*) _msg->recv_buf;
    rt_uint8_t cmd = 0;
    rt_uint32_t addr = 0;
    rt_uint32_t index = 0;
    bool need_dummy = RT_FALSE;
    RT_ASSERT(spi != RT_NULL);

    spi->control_config.common_config.tx_dma_enable = false;
    spi->control_config.common_config.rx_dma_enable = false;
    if (device->config.mode == RT_SPI_SLAVE) {
#if 0
        spi_slave_enable_data_only(spi->spi_base);
        spi_set_transfer_mode(spi->spi_base, spi_trans_write_read_together);
#endif
        LOG_E("Spi slave does not support polling transmission\n");
        return -RT_EINVAL;
    }
    while (_msg != RT_NULL) {
        tx_buf = (rt_uint8_t*) _msg->send_buf;
        rx_buf = (rt_uint8_t*) _msg->recv_buf;
        index = 0;
        if (hpm_spi_check_params(device, _msg) != RT_EOK) {
            return -RT_EINVAL;
        }
#ifdef RT_USING_QSPI
        qspi_msg = (struct rt_qspi_message *)_msg;
        need_dummy = hpm_qspi_parse_phase_message(device, qspi_msg, &spi->control_config, &cmd, &addr);
        remaining_size = _msg->length;
        if (remaining_size == 0) {
            actual_len = hpm_spi_send_no_data(spi->spi_base, &spi->control_config, &cmd, &addr,  qspi_msg);
        }
#endif
        while (remaining_size > 0) {
            transfer_len = MIN(SPI_SOC_TRANSFER_COUNT_MAX, remaining_size);
            /* Next sub-packet: Disable CMD and ADDR phase for the following packet */
            if (index > 0) {
                spi->control_config.master_config.cmd_enable = RT_FALSE;
                spi->control_config.master_config.addr_enable = RT_FALSE;
            }
            if ((_msg->send_buf != NULL) && (_msg->recv_buf != NULL)) {
                spi->control_config.common_config.trans_mode = spi_trans_write_read_together;
                spi_stat = spi_transfer(spi->spi_base, &spi->control_config, &cmd, &addr, tx_buf, transfer_len, rx_buf, transfer_len);
            }
            else if (_msg->send_buf != NULL) {
                if ((need_dummy == RT_TRUE) && (index == 0)) {
                    spi->control_config.common_config.trans_mode = spi_trans_dummy_write;
                } else {
                    spi->control_config.common_config.trans_mode = spi_trans_write_only;
                }
                spi_stat = spi_transfer(spi->spi_base, &spi->control_config, &cmd, &addr, (uint8_t*) tx_buf, transfer_len, NULL, 0);
            }
            else if (_msg->recv_buf != NULL){
                if ((need_dummy == RT_TRUE) && (index == 0)) {
                    spi->control_config.common_config.trans_mode = spi_trans_dummy_read;
                } else {
                    spi->control_config.common_config.trans_mode = spi_trans_read_only;
                }
                spi_stat = spi_transfer(spi->spi_base, &spi->control_config, &cmd, &addr, NULL, 0, rx_buf, transfer_len);
            }
            if (spi_stat != status_success) {
                actual_len = -RT_EIO;
                break;
            }
            if (tx_buf != NULL) {
                tx_buf += transfer_len;
            }
            if (rx_buf != NULL) {
                rx_buf += transfer_len;
            }
            remaining_size -= transfer_len;
            actual_len += transfer_len;
            index++;
        }
        _msg = _msg->next;
    }
    return actual_len;
}

static hpm_stat_t hpm_spi_tx_dma_config(struct rt_spi_device *device, uint8_t *buff, uint32_t size)
{
    hpm_stat_t stat = status_success;
    uint8_t transfer_width;
    uint32_t buf_addr;
    struct hpm_spi *spi = (struct hpm_spi *)(device->bus->parent.user_data);
    uint8_t data_len_in_bytes = spi_get_data_length_in_bytes(spi->spi_base);
    dma_resource_t *resource = &spi->tx_dma;
    uint32_t core_id = read_csr(CSR_MHARTID);
    if (data_len_in_bytes > 2) {
        data_len_in_bytes = 4; /* must be 4 aglin */
        /* word */
        transfer_width = DMA_MGR_TRANSFER_WIDTH_WORD;
    } else {
        /* byte or half_word*/
        transfer_width = data_len_in_bytes - 1;
    }
    if (size > (SPI_SOC_TRANSFER_COUNT_MAX * data_len_in_bytes)) {
        return status_invalid_argument;
    }
    buf_addr = core_local_mem_to_sys_address(core_id, (uint32_t)buff);
    HPM_CHECK_RET(dma_mgr_set_chn_src_addr(resource, buf_addr));
    HPM_CHECK_RET(dma_mgr_set_chn_dst_width(resource, transfer_width));
    HPM_CHECK_RET(dma_mgr_set_chn_src_width(resource, transfer_width));
    HPM_CHECK_RET(dma_mgr_set_chn_transize(resource, size / data_len_in_bytes));
    return stat;
}

static hpm_stat_t hpm_spi_tx_dma_start(struct rt_spi_device *device)
{
    hpm_stat_t stat = status_success;
    struct hpm_spi *spi = (struct hpm_spi *)(device->bus->parent.user_data);
    dma_resource_t *resource = &spi->tx_dma;
    HPM_CHECK_RET(dma_mgr_enable_channel(resource));
    return stat;
}


static hpm_stat_t hpm_spi_rx_dma_config(struct rt_spi_device *device, uint8_t *buff, uint32_t size)
{
    hpm_stat_t stat = status_success;
    uint8_t transfer_width;
    uint32_t buf_addr;
    uint32_t core_id = read_csr(CSR_MHARTID);
    struct hpm_spi *spi = (struct hpm_spi *)(device->bus->parent.user_data);
    uint8_t data_len_in_bytes = spi_get_data_length_in_bytes(spi->spi_base);
    dma_resource_t *resource = &spi->rx_dma;
    if (data_len_in_bytes > 2) {
        data_len_in_bytes = 4; /* must be 4 aglin */
        /* word */
        transfer_width = DMA_MGR_TRANSFER_WIDTH_WORD;
    } else {
        /* byte or half_word*/
        transfer_width = data_len_in_bytes - 1;
    }
    if (size > (SPI_SOC_TRANSFER_COUNT_MAX * data_len_in_bytes)) {
        return status_invalid_argument;
    }
    buf_addr = core_local_mem_to_sys_address(core_id, (uint32_t)buff);
    HPM_CHECK_RET(dma_mgr_set_chn_dst_addr(resource, buf_addr));
    HPM_CHECK_RET(dma_mgr_set_chn_src_width(resource, transfer_width));
    HPM_CHECK_RET(dma_mgr_set_chn_dst_width(resource, transfer_width));
    HPM_CHECK_RET(dma_mgr_set_chn_transize(resource, size / data_len_in_bytes));
    HPM_CHECK_RET(dma_mgr_enable_channel(resource));
    return stat;
}

static hpm_stat_t hpm_spi_rx_dma_start(struct rt_spi_device *device)
{
    hpm_stat_t stat = status_success;
    struct hpm_spi *spi = (struct hpm_spi *)(device->bus->parent.user_data);
    dma_resource_t *resource = &spi->rx_dma;
    HPM_CHECK_RET(dma_mgr_enable_channel(resource));
    return stat;
}

static void hpm_spi_transfer_data_cache_handle(struct rt_spi_message *msg, spi_dma_buf_ctx_t *ctx, rt_uint32_t len)
{
    rt_uint32_t transfer_len;
    rt_uint8_t *tx_buf = RT_NULL;
    rt_uint8_t *rx_buf = RT_NULL;
    uint32_t aligned_start = 0;
    uint32_t aligned_end = 0;
    uint32_t aligned_size = 0;
    if (msg->send_buf != RT_NULL) {
        if (l1c_dc_is_enabled() == true) {
            if (((rt_uint32_t)msg->send_buf % HPM_L1C_CACHELINE_SIZE) || (len % HPM_L1C_CACHELINE_SIZE)) {
                ctx->aligned_size = (len + HPM_L1C_CACHELINE_SIZE - 1U) & ~(HPM_L1C_CACHELINE_SIZE - 1U);
                ctx->raw_alloc_tx_buf = (rt_uint8_t*)rt_malloc_align(ctx->aligned_size, HPM_L1C_CACHELINE_SIZE);
                RT_ASSERT(ctx->raw_alloc_tx_buf != RT_NULL);
                ctx->aligned_tx_buf = ctx->raw_alloc_tx_buf;
                rt_memcpy(ctx->aligned_tx_buf, msg->send_buf, len);
                l1c_dc_flush((uint32_t) (ctx->aligned_tx_buf), ctx->aligned_size);
            } else {
                ctx->aligned_tx_buf = (uint8_t*) msg->send_buf;
                aligned_start = HPM_L1C_CACHELINE_ALIGN_DOWN((uint32_t)(ctx->aligned_tx_buf));
                aligned_end = HPM_L1C_CACHELINE_ALIGN_UP((uint32_t)(ctx->aligned_tx_buf) + msg->length);
                aligned_size = aligned_end - aligned_start;
                ctx->aligned_size = aligned_size;
                l1c_dc_writeback(aligned_start, aligned_size);
            }
        } else {
            ctx->aligned_tx_buf = (uint8_t*) msg->send_buf;
            ctx->aligned_size = len;
        }

    }
    if (msg->recv_buf != RT_NULL) {
        if (l1c_dc_is_enabled() == true) {
            if (((rt_uint32_t)msg->recv_buf % HPM_L1C_CACHELINE_SIZE) || (len % HPM_L1C_CACHELINE_SIZE)) {
                ctx->aligned_size = (len + HPM_L1C_CACHELINE_SIZE - 1U) & ~(HPM_L1C_CACHELINE_SIZE - 1U);
                ctx->raw_alloc_rx_buf = (uint8_t*)rt_malloc_align(ctx->aligned_size, HPM_L1C_CACHELINE_SIZE);
                RT_ASSERT(ctx->raw_alloc_rx_buf != RT_NULL);
                ctx->aligned_rx_buf = ctx->raw_alloc_rx_buf;
                l1c_dc_invalidate((uint32_t)(ctx->aligned_rx_buf), ctx->aligned_size);
            } else {
                ctx->aligned_rx_buf = (uint8_t*)msg->recv_buf;
                ctx->aligned_size = len;
            }
        } else {
            ctx->aligned_rx_buf = (uint8_t*) msg->recv_buf;
            ctx->aligned_size = len;
        }
    }
}

static hpm_stat_t hpm_spi_transmit_use_fifo(struct rt_spi_device *device, struct rt_spi_message *msg, rt_uint32_t *remaining_size,
                                                rt_uint8_t *cmd, rt_uint32_t *addr, bool *need_dummy, rt_ssize_t *actual_len)
{
    hpm_stat_t stat = status_fail;
    struct hpm_spi *spi = (struct hpm_spi *)(device->bus->parent.user_data);
    if (((*remaining_size) <= SPI_SOC_FIFO_DEPTH) && ((device->config.mode & RT_SPI_MASTER) == RT_SPI_MASTER)
    && (msg->send_buf != NULL) && (msg->recv_buf == NULL)) {
        spi_enable_interrupt(spi->spi_base, spi_end_int);
        if ((*need_dummy) == RT_TRUE) {
            spi->control_config.common_config.trans_mode = spi_trans_dummy_write;
        } else {
            spi->control_config.common_config.trans_mode = spi_trans_write_only;
        }
        stat = spi_control_init(spi->spi_base, &spi->control_config, (*remaining_size), 0);
        if (stat != status_success) {
            return stat;
        }
        uint8_t data_len_in_bytes = spi_get_data_length_in_bytes(spi->spi_base);
        if (msg->send_buf != NULL) {
            for (uint8_t j = 0; j < (*remaining_size); j++) {
                switch (data_len_in_bytes) {
                case 1:
                    spi->spi_base->DATA = *(uint8_t *)msg->send_buf;
                    break;
                case 2:
                    spi->spi_base->DATA = *(uint16_t *)msg->send_buf;
                    break;
                default:
                    spi->spi_base->DATA = *(uint32_t *)msg->send_buf;
                    break;
                }
                msg->send_buf += data_len_in_bytes;
                (*actual_len) += data_len_in_bytes;
            }
        }
        spi->spi_base->ADDR = SPI_ADDR_ADDR_SET(*addr);
        spi->spi_base->CMD = SPI_CMD_CMD_SET(*cmd);
        rt_sem_take(spi->spi_xfer_done_sem, RT_WAITING_FOREVER);
    }
    return stat;
}

static rt_ssize_t hpm_spi_xfer_dma(struct rt_spi_device *device, struct rt_spi_message *msg)
{
    spi_dma_buf_ctx_t dma_buf_ctx = {0};
    rt_uint8_t cmd = 0;
    rt_uint32_t addr = 0, aligned_len = 0;
    rt_uint32_t remaining_size = msg->length;
    rt_uint32_t transfer_len;
    rt_uint8_t *tx_buf = RT_NULL;
    rt_uint8_t *rx_buf = RT_NULL;
    uint32_t aligned_start = 0;
    uint32_t aligned_end = 0;
    uint32_t aligned_size = 0;
    rt_ssize_t actual_len = 0;
    bool need_dummy = RT_FALSE;
    hpm_stat_t stat = status_success;
    rt_uint32_t index;
    struct rt_spi_message *_msg = (struct rt_spi_message *)msg;
    struct rt_spi_message *spi_msg = (struct rt_spi_message *)_msg;
#ifdef RT_USING_QSPI
    struct rt_qspi_message *qspi_msg = RT_NULL;
#endif
    struct hpm_spi *spi = (struct hpm_spi *)(device->bus->parent.user_data);
    spi_enable_interrupt(spi->spi_base, spi_end_int);
    while (_msg != RT_NULL) {
        index = 0;
        if (hpm_spi_check_params(device, _msg) != RT_EOK) {
            return -RT_EINVAL;
        }
        remaining_size = _msg->length;
#ifdef RT_USING_QSPI
        qspi_msg = (struct rt_qspi_message *)_msg;
        need_dummy = hpm_qspi_parse_phase_message(device, qspi_msg, &spi->control_config, &cmd, &addr);
        if (remaining_size == 0) {
            actual_len = hpm_spi_send_no_data(spi->spi_base, &spi->control_config, &cmd, &addr,  qspi_msg);
        } else
#endif
        {
            if (remaining_size > 0) {
                /* If the length is less than SPI_SOC_FIFO_DEPTH, use fifo mode to transmit data */
                stat = hpm_spi_transmit_use_fifo(device, _msg, &remaining_size, &cmd, &addr, &need_dummy, &actual_len);
                if (stat == status_success) {
                    _msg = _msg->next;
                    continue;
                }
                hpm_spi_transfer_data_cache_handle(_msg, &dma_buf_ctx, msg->length);
                tx_buf = dma_buf_ctx.aligned_tx_buf;
                rx_buf = dma_buf_ctx.aligned_rx_buf;
                dma_mgr_disable_chn_irq(&spi->rx_dma, DMA_MGR_INTERRUPT_MASK_TC);
                dma_mgr_disable_chn_irq(&spi->tx_dma, DMA_MGR_INTERRUPT_MASK_TC);
            }
        }
        while (remaining_size > 0) {
            transfer_len = MIN(SPI_SOC_TRANSFER_COUNT_MAX, remaining_size);
            /* Next sub-packet: Disable CMD and ADDR phase for the following packet */
            if (index > 0) {
                spi->control_config.master_config.cmd_enable = RT_FALSE;
                spi->control_config.master_config.addr_enable = RT_FALSE;
            }
            if (_msg->send_buf != NULL && _msg->recv_buf != NULL) {
                dma_mgr_enable_chn_irq(&spi->rx_dma, DMA_MGR_INTERRUPT_MASK_TC);
                dma_mgr_enable_chn_irq(&spi->tx_dma, DMA_MGR_INTERRUPT_MASK_TC);
                spi->control_config.common_config.tx_dma_enable = RT_TRUE;
                spi->control_config.common_config.rx_dma_enable = RT_TRUE;
                spi->control_config.common_config.trans_mode = spi_trans_write_read_together;
                /* for spi_trans_write_read_together mode, the operation sequence is recommended as follows: */
                /* first: config rx dma transfer and start rx dma */
                stat = hpm_spi_rx_dma_config(device, rx_buf, transfer_len);
                if (stat != status_success) {
                    break;
                }
                stat = hpm_spi_rx_dma_start(device);
                if (stat != status_success) {
                    break;
                }
                /* second: config tx dma transfer */
                stat = hpm_spi_tx_dma_config(device, tx_buf, transfer_len);
                if (stat != status_success) {
                    break;
                }
                /* third: config spi */
                stat = spi_control_init(spi->spi_base, &spi->control_config, transfer_len, transfer_len);
                if (stat != status_success) {
                    break;
                }
                /* fourth: set spi address and enable spi rx /tx dma */
                spi_write_address(spi->spi_base, spi_master_mode, &spi->control_config, &addr);
                spi_enable_rx_dma(spi->spi_base);
#if defined(HPM_IP_FEATURE_SPI_DMA_TX_REQ_AFTER_CMD_FO_MASTER) && (HPM_IP_FEATURE_SPI_DMA_TX_REQ_AFTER_CMD_FO_MASTER == 1)
                spi_master_enable_tx_dma_request_after_cmd_write(spi->spi_base);
#endif
                spi_enable_tx_dma(spi->spi_base);
                /* fifth: start tx dma */
                stat = hpm_spi_tx_dma_start(device);
                if (stat != status_success) {
                    break;
                }
                /* sixth: Write the command, which marks the beginning of an SPI transfer */
                spi_write_command(spi->spi_base, spi_master_mode, &spi->control_config, &cmd);
                /* to ensure complete transmission, check both SPI transfer completion and DMA transfer completion */
                rt_sem_take(spi->spi_xfer_done_sem, RT_WAITING_FOREVER);
                rt_sem_take(spi->txdma_xfer_done_sem, RT_WAITING_FOREVER);
                rt_sem_take(spi->rxdma_xfer_done_sem, RT_WAITING_FOREVER);
            } else if (_msg->send_buf != NULL) {
                dma_mgr_enable_chn_irq(&spi->tx_dma, DMA_MGR_INTERRUPT_MASK_TC);
                spi->control_config.common_config.tx_dma_enable = RT_TRUE;
                spi->control_config.common_config.rx_dma_enable = RT_FALSE;
                if ((need_dummy == RT_TRUE) && (index == 0)) {
                    spi->control_config.common_config.trans_mode = spi_trans_dummy_write;
                } else {
                    spi->control_config.common_config.trans_mode = spi_trans_write_only;
                }
                stat = spi_setup_dma_transfer(spi->spi_base, &spi->control_config, &cmd, &addr, transfer_len, RT_NULL);
                if (stat != status_success) {
                    break;
                }
                stat = hpm_spi_tx_dma_config(device, tx_buf, transfer_len);
                if (stat != status_success) {
                    break;
                }
                stat = hpm_spi_tx_dma_start(device);
                if (stat != status_success) {
                    break;
                }
                /* to ensure complete transmission, check both SPI transfer completion and DMA transfer completion */
                rt_sem_take(spi->spi_xfer_done_sem, RT_WAITING_FOREVER);
                rt_sem_take(spi->txdma_xfer_done_sem, RT_WAITING_FOREVER);
            } else if (_msg->recv_buf != NULL) {
                dma_mgr_enable_chn_irq(&spi->rx_dma, DMA_MGR_INTERRUPT_MASK_TC);
                spi->control_config.common_config.tx_dma_enable = RT_FALSE;
                spi->control_config.common_config.rx_dma_enable = RT_TRUE;
                if ((need_dummy == RT_TRUE) && (index == 0)) {
                    spi->control_config.common_config.trans_mode = spi_trans_dummy_read;
                } else {
                    spi->control_config.common_config.trans_mode = spi_trans_read_only;
                }
                stat = hpm_spi_rx_dma_config(device, rx_buf, transfer_len);
                if (stat != status_success) {
                    break;
                }
                stat = hpm_spi_rx_dma_start(device);
                if (stat != status_success) {
                    break;
                }
                stat = spi_setup_dma_transfer(spi->spi_base, &spi->control_config, &cmd, &addr, RT_NULL, transfer_len);
                if (stat != status_success) {
                    break;
                }
                /* to ensure complete transmission, check both SPI transfer completion and DMA transfer completion */
                rt_sem_take(spi->spi_xfer_done_sem, RT_WAITING_FOREVER);
                rt_sem_take(spi->rxdma_xfer_done_sem, RT_WAITING_FOREVER);
            }
            if (tx_buf != NULL) {
                tx_buf += transfer_len;
            }
            if (rx_buf != NULL) {
                rx_buf += transfer_len;
            }
            remaining_size -= transfer_len;
            actual_len += transfer_len;
            index++;
        }
        if (l1c_dc_is_enabled() && (_msg->length > 0)) {
            if (((rt_uint32_t)msg->send_buf % HPM_L1C_CACHELINE_SIZE) || (_msg->length % HPM_L1C_CACHELINE_SIZE)) {
                if (dma_buf_ctx.aligned_tx_buf != RT_NULL) {
                    rt_free_align(dma_buf_ctx.raw_alloc_tx_buf);
                    dma_buf_ctx.raw_alloc_tx_buf = RT_NULL;
                    dma_buf_ctx.aligned_tx_buf = RT_NULL;
                }
            }
            if ((l1c_dc_is_enabled() == true) && (_msg->recv_buf != RT_NULL) && (dma_buf_ctx.aligned_rx_buf != RT_NULL)) {
                l1c_dc_invalidate((uint32_t) dma_buf_ctx.aligned_rx_buf, dma_buf_ctx.aligned_size);
                if (((rt_uint32_t)msg->recv_buf % HPM_L1C_CACHELINE_SIZE) || (_msg->length % HPM_L1C_CACHELINE_SIZE)) {
                    rt_memcpy(_msg->recv_buf, dma_buf_ctx.aligned_rx_buf, _msg->length);
                    rt_free_align(dma_buf_ctx.raw_alloc_rx_buf);
                    dma_buf_ctx.raw_alloc_rx_buf = RT_NULL;
                    dma_buf_ctx.aligned_rx_buf = RT_NULL;
                }
            }
        }
        if (stat != status_success) {
            actual_len = -RT_EIO;
            break;
        }
        _msg = _msg->next;
    }
    spi_disable_interrupt(spi->spi_base, spi_end_int);
    return actual_len;
}

static rt_ssize_t hpm_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *msg)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(msg != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    rt_ssize_t len;

    cs_ctrl_callback_t cs_pin_control = (cs_ctrl_callback_t) device->parent.user_data;

    struct hpm_spi *spi = (struct hpm_spi *) (device->bus->parent.user_data);

    hpm_stat_t spi_stat = status_success;
    if (device->cs_pin == PIN_NONE) {
        if ((cs_pin_control != NULL) && msg->cs_take) {
            cs_pin_control(SPI_CS_TAKE);
        }
    } else {
        if (msg->cs_take && !(device->config.mode & RT_SPI_NO_CS)) {
            if (device->config.mode & RT_SPI_CS_HIGH) {
                rt_pin_write(device->cs_pin, PIN_HIGH);
            } else {
                rt_pin_write(device->cs_pin, PIN_LOW);
            }
        }

    }

    if (spi->enable_dma) {
        len = hpm_spi_xfer_dma(device,  msg);
    } else {
        len = hpm_spi_xfer_polling(device,  msg);
    }

    if (device->cs_pin == PIN_NONE) {
        if ((cs_pin_control != NULL) && msg->cs_release) {
            cs_pin_control(SPI_CS_RELEASE);
        }
    } else {
        if (msg->cs_release && !(device->config.mode & RT_SPI_NO_CS)) {
            if (device->config.mode & RT_SPI_CS_HIGH) {
                rt_pin_write(device->cs_pin, PIN_LOW);
            } else {
                rt_pin_write(device->cs_pin, PIN_HIGH);
            }
        }
    }
    return len;
}

#ifdef RT_USING_QSPI
void enter_qspi_mode(struct rt_qspi_device *device)
{
    (void)device;
}

void exit_qspi_mode(struct rt_qspi_device *device)
{
    (void)device;
}

#endif

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, cs_ctrl_callback_t callback)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
#ifdef RT_USING_QSPI
    struct rt_qspi_device *qspi_dev;
    qspi_dev = (struct rt_qspi_device *) rt_malloc(sizeof(struct rt_qspi_device));
    qspi_dev->enter_qspi_mode = enter_qspi_mode;
    qspi_dev->exit_qspi_mode = exit_qspi_mode;
    RT_ASSERT(qspi_dev != RT_NULL);
    result = rt_spi_bus_attach_device(&qspi_dev->parent, device_name, bus_name, (void*)callback);
    RT_ASSERT(result == RT_EOK);
    struct hpm_spi *spi = RT_NULL;
    spi = (struct hpm_spi *)(qspi_dev->parent.bus->parent.user_data);
    switch (spi->spi_io_mode) {
        case spi_single_io_mode:
            qspi_dev->config.qspi_dl_width = 1;
            break;
        case spi_dual_io_mode:
            qspi_dev->config.qspi_dl_width = 2;
            break;
        case spi_quad_io_mode:
            qspi_dev->config.qspi_dl_width = 4;
            break;
        default:
            qspi_dev->config.qspi_dl_width = 1;
            break;
    }

#else
    struct rt_spi_device *spi_device;
    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *) rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void*)callback);
    RT_ASSERT(result == RT_EOK);
#endif
    return result;
}


int rt_hw_spi_init(void)
{

    rt_err_t ret = RT_EOK;
    hpm_stat_t stat;
    dma_mgr_chn_conf_t chg_config;
    for (uint32_t i = 0; i < sizeof(hpm_spis) / sizeof(hpm_spis[0]); i++)
    {
        struct hpm_spi *spi = &hpm_spis[i];
        spi->spi_bus.parent.user_data = spi;
        clock_add_to_group(spi->clk_name, BOARD_RUNNING_CORE & 0x1);
        if (spi->enable_dma)
        {
            dma_mgr_get_default_chn_config(&chg_config);
            chg_config.src_width = DMA_MGR_TRANSFER_WIDTH_BYTE;
            chg_config.dst_width = DMA_MGR_TRANSFER_WIDTH_BYTE;
            /* spi tx dma config */
            stat = dma_mgr_request_resource(&spi->tx_dma);
            if (stat != status_success)
            {
                LOG_E("[spi%d]tx dma request resource failed\n", i);
                return -RT_ERROR;
            }
            chg_config.src_mode = DMA_MGR_HANDSHAKE_MODE_NORMAL;
            chg_config.src_addr_ctrl = DMA_MGR_ADDRESS_CONTROL_INCREMENT;
            chg_config.dst_mode = DMA_MGR_HANDSHAKE_MODE_HANDSHAKE;
            chg_config.dst_addr_ctrl = DMA_MGR_ADDRESS_CONTROL_FIXED;
            chg_config.dst_addr = (uint32_t)&spi->spi_base->DATA;
            chg_config.en_dmamux = true;
            chg_config.dmamux_src = spi->tx_dmamux;
            dma_mgr_setup_channel(&spi->tx_dma, &chg_config);
            dma_mgr_install_chn_tc_callback(&spi->tx_dma, spi_dma_channel_tc_callback, (void *)&hpm_spis[i]);
            /* spi rx dma config */
            stat = dma_mgr_request_resource(&spi->rx_dma);
            if (stat != status_success) {
                LOG_E("[spi%d]rx dma request resource failed\n", i);
                return -RT_ERROR;
            }
            chg_config.src_mode = DMA_MGR_HANDSHAKE_MODE_HANDSHAKE;
            chg_config.src_addr_ctrl = DMA_MGR_ADDRESS_CONTROL_FIXED;
            chg_config.src_addr = (uint32_t)&spi->spi_base->DATA;
            chg_config.dst_mode = DMA_MGR_HANDSHAKE_MODE_NORMAL;
            chg_config.dst_addr_ctrl = DMA_MGR_ADDRESS_CONTROL_INCREMENT;
            chg_config.en_dmamux = true;
            chg_config.dmamux_src = spi->rx_dmamux;
            dma_mgr_setup_channel(&spi->rx_dma, &chg_config);
            dma_mgr_install_chn_tc_callback(&spi->rx_dma, spi_dma_channel_tc_callback, (void *)&hpm_spis[i]);

            intc_m_enable_irq_with_priority(hpm_spis[i].spi_irq, hpm_spis[i].spi_irq_priority);
            dma_mgr_enable_dma_irq_with_priority(&spi->tx_dma, 1);
            dma_mgr_enable_dma_irq_with_priority(&spi->rx_dma, 1);
        }
#ifdef RT_USING_QSPI
        ret = rt_qspi_bus_register(&spi->spi_bus, spi->bus_name, &hpm_spi_ops);
#else
        ret = rt_spi_bus_register(&spi->spi_bus, spi->bus_name, &hpm_spi_ops);
#endif
        if (ret != RT_EOK)
        {
            break;
        }

        char sem_name[RT_NAME_MAX];
        rt_sprintf(sem_name, "%s_s", hpm_spis[i].bus_name);
        hpm_spis[i].xfer_sem = rt_sem_create(sem_name, 0, RT_IPC_FLAG_PRIO);
        if (hpm_spis[i].xfer_sem == RT_NULL)
        {
            ret = RT_ENOMEM;
            break;
        }

        rt_sprintf(sem_name, "%s_ds", hpm_spis[i].bus_name);
        hpm_spis[i].spi_xfer_done_sem = rt_sem_create(sem_name, 0, RT_IPC_FLAG_PRIO);
        if (hpm_spis[i].spi_xfer_done_sem == RT_NULL)
        {
            ret = RT_ENOMEM;
            break;
        }

        rt_sprintf(sem_name, "%s_rds", hpm_spis[i].bus_name);
        hpm_spis[i].rxdma_xfer_done_sem = rt_sem_create(sem_name, 0, RT_IPC_FLAG_PRIO);
        if (hpm_spis[i].rxdma_xfer_done_sem == RT_NULL)
        {
            ret = RT_ENOMEM;
            break;
        }

        rt_sprintf(sem_name, "%s_tds", hpm_spis[i].bus_name);
        hpm_spis[i].txdma_xfer_done_sem = rt_sem_create(sem_name, 0, RT_IPC_FLAG_PRIO);
        if (hpm_spis[i].txdma_xfer_done_sem == RT_NULL)
        {
            ret = RT_ENOMEM;
            break;
        }
    }

    return ret;
}

INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif /*BSP_USING_SPI*/
