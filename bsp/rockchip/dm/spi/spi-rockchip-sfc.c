/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include "dev_spi_dm.h"

#define DBG_TAG "spi.rockchip.sfc"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <mmu.h>
#include <cpuport.h>

/* System control */
#define SFC_CTRL                        0x0
#define  SFC_CTRL_PHASE_SEL_NEGETIVE    RT_BIT(1)
#define  SFC_CTRL_CMD_BITS_SHIFT        8
#define  SFC_CTRL_ADDR_BITS_SHIFT       10
#define  SFC_CTRL_DATA_BITS_SHIFT       12

/* Interrupt mask */
#define SFC_IMR                         0x4
#define  SFC_IMR_RX_FULL                RT_BIT(0)
#define  SFC_IMR_RX_UFLOW               RT_BIT(1)
#define  SFC_IMR_TX_OFLOW               RT_BIT(2)
#define  SFC_IMR_TX_EMPTY               RT_BIT(3)
#define  SFC_IMR_TRAN_FINISH            RT_BIT(4)
#define  SFC_IMR_BUS_ERR                RT_BIT(5)
#define  SFC_IMR_NSPI_ERR               RT_BIT(6)
#define  SFC_IMR_DMA                    RT_BIT(7)

/* Interrupt clear */
#define SFC_ICLR                        0x8
#define  SFC_ICLR_RX_FULL               RT_BIT(0)
#define  SFC_ICLR_RX_UFLOW              RT_BIT(1)
#define  SFC_ICLR_TX_OFLOW              RT_BIT(2)
#define  SFC_ICLR_TX_EMPTY              RT_BIT(3)
#define  SFC_ICLR_TRAN_FINISH           RT_BIT(4)
#define  SFC_ICLR_BUS_ERR               RT_BIT(5)
#define  SFC_ICLR_NSPI_ERR              RT_BIT(6)
#define  SFC_ICLR_DMA                   RT_BIT(7)

/* FIFO threshold level */
#define SFC_FTLR                        0xc
#define  SFC_FTLR_TX_SHIFT              0
#define  SFC_FTLR_TX_MASK               0x1f
#define  SFC_FTLR_RX_SHIFT              8
#define  SFC_FTLR_RX_MASK               0x1f

/* Reset FSM and FIFO */
#define SFC_RCVR                        0x10
#define  SFC_RCVR_RESET                 RT_BIT(0)

/* Enhanced mode */
#define SFC_AX                          0x14

/* Address Bit number */
#define SFC_ABIT                        0x18

/* Interrupt status */
#define SFC_ISR                         0x1c
#define  SFC_ISR_RX_FULL_SHIFT          RT_BIT(0)
#define  SFC_ISR_RX_UFLOW_SHIFT         RT_BIT(1)
#define  SFC_ISR_TX_OFLOW_SHIFT         RT_BIT(2)
#define  SFC_ISR_TX_EMPTY_SHIFT         RT_BIT(3)
#define  SFC_ISR_TX_FINISH_SHIFT        RT_BIT(4)
#define  SFC_ISR_BUS_ERR_SHIFT          RT_BIT(5)
#define  SFC_ISR_NSPI_ERR_SHIFT         RT_BIT(6)
#define  SFC_ISR_DMA_SHIFT              RT_BIT(7)

/* FIFO status */
#define SFC_FSR                         0x20
#define  SFC_FSR_TX_IS_FULL             RT_BIT(0)
#define  SFC_FSR_TX_IS_EMPTY            RT_BIT(1)
#define  SFC_FSR_RX_IS_EMPTY            RT_BIT(2)
#define  SFC_FSR_RX_IS_FULL             RT_BIT(3)
#define  SFC_FSR_TXLV_MASK              RT_GENMASK(12, 8)
#define  SFC_FSR_TXLV_SHIFT             8
#define  SFC_FSR_RXLV_MASK              RT_GENMASK(20, 16)
#define  SFC_FSR_RXLV_SHIFT             16

/* FSM status */
#define SFC_SR                          0x24
#define  SFC_SR_IS_IDLE                 0x0
#define  SFC_SR_IS_BUSY                 0x1

/* Raw interrupt status */
#define SFC_RISR                        0x28
#define  SFC_RISR_RX_FULL               RT_BIT(0)
#define  SFC_RISR_RX_UNDERFLOW          RT_BIT(1)
#define  SFC_RISR_TX_OVERFLOW           RT_BIT(2)
#define  SFC_RISR_TX_EMPTY              RT_BIT(3)
#define  SFC_RISR_TRAN_FINISH           RT_BIT(4)
#define  SFC_RISR_BUS_ERR               RT_BIT(5)
#define  SFC_RISR_NSPI_ERR              RT_BIT(6)
#define  SFC_RISR_DMA                   RT_BIT(7)

/* Version */
#define SFC_VER                         0x2c
#define  SFC_VER_3                      0x3
#define  SFC_VER_4                      0x4
#define  SFC_VER_5                      0x5
#define  SFC_VER_6                      0x6

/* Delay line controller resiter */
#define SFC_DLL_CTRL0                   0x3c
#define SFC_DLL_CTRL0_SCLK_SMP_DLL      RT_BIT(15)
#define SFC_DLL_CTRL0_DLL_MAX_VER4      0xffU
#define SFC_DLL_CTRL0_DLL_MAX_VER5      0x1ffU

/* Master trigger */
#define SFC_DMA_TRIGGER                 0x80
#define SFC_DMA_TRIGGER_START           1

/* Src or Dst addr for master */
#define SFC_DMA_ADDR                    0x84

/* Length control register extension 32GB */
#define SFC_LEN_CTRL                    0x88
#define SFC_LEN_CTRL_TRB_SEL            1
#define SFC_LEN_EXT                     0x8c

/* Command */
#define SFC_CMD                         0x100
#define  SFC_CMD_IDX_SHIFT              0
#define  SFC_CMD_DUMMY_SHIFT            8
#define  SFC_CMD_DIR_SHIFT              12
#define  SFC_CMD_DIR_RD                 0
#define  SFC_CMD_DIR_WR                 1
#define  SFC_CMD_ADDR_SHIFT             14
#define  SFC_CMD_ADDR_0BITS             0
#define  SFC_CMD_ADDR_24BITS            1
#define  SFC_CMD_ADDR_32BITS            2
#define  SFC_CMD_ADDR_XBITS             3
#define  SFC_CMD_TRAN_BYTES_SHIFT       16
#define  SFC_CMD_CS_SHIFT               30

/* Address */
#define SFC_ADDR                        0x104

/* Data */
#define SFC_DATA                        0x108

/* The controller and documentation reports that it supports up to 4 CS
 * devices (0-3), however I have only been able to test a single CS (CS 0)
 * due to the configuration of my device.
 */
#define SFC_MAX_CHIPSELECT_NUM          4

/* The SFC can transfer max 16KB - 1 at one time
 * we set it to 15.5KB here for alignment.
 */
#define SFC_MAX_IOSIZE_VER3             (512 * 31)
#define SFC_MAX_IOSIZE_VER4             (0xffffffffU)

/* DMA is only enabled for large data transmission */
#define SFC_DMA_TRANS_THRETHOLD         0x40

/* Maximum clock values from datasheet suggest keeping clock value under
 * 150MHz. No minimum or average value is suggested.
 */
#define SFC_MAX_SPEED                   (150 * 1000 * 1000)
#define SFC_DLL_THRESHOLD_RATE          (50 * 1000 * 1000)

#define SFC_DLL_TRANING_STEP            10  /* Training step */
#define SFC_DLL_TRANING_VALID_WINDOW    80  /* Valid DLL winbow */

#define ROCKCHIP_AUTOSUSPEND_DELAY      2000

struct rockchip_sfc
{
    struct rt_spi_bus parent;
    struct rt_platform_device *pdev;

    struct rt_clk *clk;
    struct rt_clk *hclk;

    int irq;
    void *regs;

    void *dma_buffer;
    rt_ubase_t dma_buffer_phy;
    rt_bool_t use_dma;

    rt_uint32_t frequency;
    rt_uint32_t max_speed_hz;
    rt_uint32_t max_iosize;
    rt_uint32_t dll_cells;
    rt_uint16_t version;

    struct rt_completion done;
};

#define raw_to_rockchip_sfc(raw) rt_container_of(raw, struct rockchip_sfc, parent)

rt_inline rt_uint32_t rockchip_sfc_readl(struct rockchip_sfc *rk_sfc, int offset)
{
    return HWREG32(rk_sfc->regs + offset);
}

rt_inline void rockchip_sfc_writel(struct rockchip_sfc *rk_sfc, int offset, rt_uint32_t value)
{
    HWREG32(rk_sfc->regs + offset) = value;
}

static rt_err_t rockchip_sfc_poll(struct rockchip_sfc *rk_sfc, int offset,
        rt_uint32_t flag, rt_bool_t is_set,
        rt_uint32_t delay_us, rt_int32_t timeout_us)
{
    if (!delay_us)
    {
        delay_us = 1;
    }

    for (; timeout_us > 0; timeout_us -= delay_us)
    {
        if (is_set)
        {
            if (rockchip_sfc_readl(rk_sfc, offset) & flag)
            {
                return RT_EOK;
            }
        }
        else
        {
            if (!(rockchip_sfc_readl(rk_sfc, offset) & flag))
            {
                return RT_EOK;
            }
        }

        rt_hw_us_delay(delay_us);
        rt_hw_cpu_relax();
    }

    return -RT_ETIMEOUT;
}

static rt_err_t rockchip_sfc_reset(struct rockchip_sfc *rk_sfc)
{
    rt_err_t err;

    rockchip_sfc_writel(rk_sfc, SFC_RCVR, SFC_RCVR_RESET);

    err = rockchip_sfc_poll(rk_sfc, SFC_RCVR, SFC_RCVR_RESET, RT_FALSE,
            20, 1000000L);

    if (err)
    {
        LOG_E("SFC reset never finished");
    }

    /* Still need to clear the masked interrupt from RISR */
    rockchip_sfc_writel(rk_sfc, SFC_ICLR, 0xffffffff);

    return err;
}

static rt_uint16_t rockchip_sfc_get_version(struct rockchip_sfc *rk_sfc)
{
    return (rt_uint16_t)(rockchip_sfc_readl(rk_sfc, SFC_VER) & 0xffff);
}

static rt_uint32_t rockchip_sfc_get_max_iosize(struct rockchip_sfc *rk_sfc)
{
    return SFC_MAX_IOSIZE_VER3;
}

static rt_uint32_t rockchip_sfc_get_max_dll_cells(struct rockchip_sfc *rk_sfc)
{
    switch (rockchip_sfc_get_version(rk_sfc))
    {
    case SFC_VER_6:
    case SFC_VER_5:
        return SFC_DLL_CTRL0_DLL_MAX_VER5;

    case SFC_VER_4:
        return SFC_DLL_CTRL0_DLL_MAX_VER4;

    default:
        return 0;
    }
}

static void rockchip_sfc_set_delay_lines(struct rockchip_sfc *rk_sfc,
        rt_uint16_t cells)
{
    rt_uint32_t val = 0;
    rt_uint16_t cell_max = (rt_uint16_t)rockchip_sfc_get_max_dll_cells(rk_sfc);

    if (cells > cell_max)
    {
        cells = cell_max;
    }

    if (cells)
    {
        val = SFC_DLL_CTRL0_SCLK_SMP_DLL | cells;
    }

    rockchip_sfc_writel(rk_sfc, SFC_DLL_CTRL0, val);
}

static void rockchip_sfc_irq_unmask(struct rockchip_sfc *rk_sfc, rt_uint32_t mask)
{
    /* Enable transfer complete interrupt */
    rockchip_sfc_writel(rk_sfc, SFC_IMR,
            rockchip_sfc_readl(rk_sfc, SFC_IMR) & (~mask));
}

static void rockchip_sfc_irq_mask(struct rockchip_sfc *rk_sfc, rt_uint32_t mask)
{
    /* Disable transfer finish interrupt */
    rockchip_sfc_writel(rk_sfc, SFC_IMR,
            rockchip_sfc_readl(rk_sfc, SFC_IMR) | mask);
}

static rt_err_t rockchip_sfc_init(struct rockchip_sfc *rk_sfc)
{
    rockchip_sfc_writel(rk_sfc, SFC_CTRL, 0);
    rockchip_sfc_writel(rk_sfc, SFC_ICLR, 0xffffffff);

    rockchip_sfc_irq_mask(rk_sfc, 0xFFFFFFFF);

    if (rockchip_sfc_get_version(rk_sfc) >= SFC_VER_4)
    {
        rockchip_sfc_writel(rk_sfc, SFC_LEN_CTRL, SFC_LEN_CTRL_TRB_SEL);
    }

    return RT_EOK;
}

static rt_ssize_t rockchip_sfc_wait_txfifo_ready(struct rockchip_sfc *rk_sfc,
        rt_uint32_t timeout_us)
{
    if (rockchip_sfc_poll(rk_sfc, SFC_FSR, SFC_FSR_TXLV_MASK, RT_TRUE, 0, timeout_us))
    {
        LOG_D("Wait tx fifo timeout");

        return -RT_ETIMEOUT;
    }

    return (rockchip_sfc_readl(rk_sfc, SFC_FSR) & SFC_FSR_TXLV_MASK) >> SFC_FSR_TXLV_SHIFT;
}

static rt_ssize_t rockchip_sfc_wait_rxfifo_ready(struct rockchip_sfc *rk_sfc,
        rt_uint32_t timeout_us)
{
    if (rockchip_sfc_poll(rk_sfc, SFC_FSR, SFC_FSR_RXLV_MASK, RT_TRUE, 0, timeout_us))
    {
        LOG_D("Wait rx fifo timeout");

        return -RT_ETIMEOUT;
    }

    return (rockchip_sfc_readl(rk_sfc, SFC_FSR) & SFC_FSR_RXLV_MASK) >> SFC_FSR_RXLV_SHIFT;
}

static rt_ssize_t rockchip_sfc_write_fifo(struct rockchip_sfc *rk_sfc,
        const rt_uint8_t *buf, int len)
{
    int tx_level;
    rt_uint8_t bytes = len & 0x3;
    rt_uint32_t dwords, write_words, tmp = 0;

    dwords = len >> 2;
    while (dwords)
    {
        if ((tx_level = rockchip_sfc_wait_txfifo_ready(rk_sfc, 1000)) < 0)
        {
            return tx_level;
        }

        write_words = rt_min_t(rt_uint32_t, tx_level, dwords);

        for (int i = 0; i < write_words; ++i)
        {
            rockchip_sfc_writel(rk_sfc, SFC_DATA, ((rt_uint32_t *)buf)[i]);
        }

        buf += write_words << 2;
        dwords -= write_words;
    }

    /* write the rest non word aligned bytes */
    if (bytes)
    {
        if ((tx_level = rockchip_sfc_wait_txfifo_ready(rk_sfc, 1000)) < 0)
        {
            return tx_level;
        }

        rt_memcpy(&tmp, buf, bytes);
        rockchip_sfc_writel(rk_sfc, SFC_DATA, tmp);
    }

    return len;
}

static rt_ssize_t rockchip_sfc_read_fifo(struct rockchip_sfc *rk_sfc,
        rt_uint8_t *buf, int len)
{
    int rx_level;
    rt_uint8_t bytes = len & 0x3;
    rt_uint32_t dwords, read_words, tmp = 0;

    /* word aligned access only */
    dwords = len >> 2;
    while (dwords)
    {
        if ((rx_level = rockchip_sfc_wait_rxfifo_ready(rk_sfc, 1000)) < 0)
        {
            return rx_level;
        }

        read_words = rt_min_t(rt_uint32_t, rx_level, dwords);

        for (int i = 0; i < read_words; ++i)
        {
            ((rt_uint32_t *)buf)[i] = rockchip_sfc_readl(rk_sfc, SFC_DATA);
        }

        buf += read_words << 2;
        dwords -= read_words;
    }

    /* read the rest non word aligned bytes */
    if (bytes)
    {
        if ((rx_level = rockchip_sfc_wait_rxfifo_ready(rk_sfc, 1000)) < 0)
        {
            return rx_level;
        }

        tmp = rockchip_sfc_readl(rk_sfc, SFC_DATA);
        rt_memcpy(buf, &tmp, bytes);
    }

    return len;
}

static rt_size_t rockchip_sfc_fifo_transfer_dma(struct rockchip_sfc *rk_sfc,
        rt_ubase_t dma_buf, rt_size_t len)
{
    rockchip_sfc_writel(rk_sfc, SFC_ICLR, 0xffffffff);
    rockchip_sfc_writel(rk_sfc, SFC_DMA_ADDR, (rt_uint32_t)dma_buf);
    rockchip_sfc_writel(rk_sfc, SFC_DMA_TRIGGER, SFC_DMA_TRIGGER_START);

    return len;
}

static rt_ssize_t rockchip_sfc_xfer_data_poll(struct rockchip_sfc *rk_sfc,
        struct rt_spi_message *xfer)
{
    if (xfer->send_buf)
    {
        return rockchip_sfc_write_fifo(rk_sfc, xfer->send_buf, xfer->length);
    }
    else if (xfer->recv_buf)
    {
        return rockchip_sfc_read_fifo(rk_sfc, xfer->recv_buf, xfer->length);
    }

    return -RT_EINVAL;
}

static rt_ssize_t rockchip_sfc_xfer_data_dma(struct rockchip_sfc *rk_sfc,
        struct rt_spi_message *xfer)
{
    rt_ssize_t res = -RT_EINVAL, len = xfer->length;

    if (xfer->send_buf)
    {
        rt_memcpy(rk_sfc->dma_buffer, xfer->send_buf, len);

        res = rockchip_sfc_fifo_transfer_dma(rk_sfc, rk_sfc->dma_buffer_phy, len);

        if (rt_completion_wait(&rk_sfc->done, rt_tick_from_millisecond(2000)))
        {
            LOG_E("DMA wait for %s transfer finish timeout", "tx");
            res = -RT_ETIMEOUT;

            goto _out_irq;
        }
    }

    if (xfer->recv_buf)
    {
        res = rockchip_sfc_fifo_transfer_dma(rk_sfc, rk_sfc->dma_buffer_phy, len);

        if (rt_completion_wait(&rk_sfc->done, rt_tick_from_millisecond(2000)))
        {
            LOG_E("DMA wait for %s transfer finish timeout", "rx");
            res = -RT_ETIMEOUT;
        }
    }

_out_irq:
    rockchip_sfc_irq_mask(rk_sfc, SFC_IMR_DMA);

    if (res > 0 && xfer->recv_buf)
    {
        rt_memcpy(xfer->recv_buf, rk_sfc->dma_buffer, len);
    }

    return res;
}

static rt_err_t rockchip_sfc_xfer_done(struct rockchip_sfc *rk_sfc,
        rt_uint32_t timeout_us)
{
    if (rockchip_sfc_poll(rk_sfc, SFC_SR, SFC_SR_IS_BUSY, RT_FALSE,
            20, timeout_us))
    {
        LOG_E("Wait sfc idle timeout");
        rockchip_sfc_reset(rk_sfc);

        return -RT_EIO;
    }

    return RT_EOK;
}

static rt_err_t rockchip_sfc_xfer_setup(struct rockchip_sfc *rk_sfc,
        struct rt_spi_device *spi_dev, struct rt_qspi_message *qspi_xfer)
{
    rt_uint32_t ctrl = 0, cmd = 0;
    rt_ssize_t len = qspi_xfer->parent.length;

    /* instruction */
    cmd = qspi_xfer->instruction.content;
    ctrl |= (qspi_xfer->instruction.qspi_lines >> 1) << SFC_CTRL_CMD_BITS_SHIFT;

    /* address */
    if (qspi_xfer->address.size)
    {
        if (qspi_xfer->address.size == 4)
        {
            cmd |= SFC_CMD_ADDR_32BITS << SFC_CMD_ADDR_SHIFT;
        }
        else if (qspi_xfer->address.size == 3)
        {
            cmd |= SFC_CMD_ADDR_24BITS << SFC_CMD_ADDR_SHIFT;
        }
        else
        {
            cmd |= SFC_CMD_ADDR_XBITS << SFC_CMD_ADDR_SHIFT;
            rockchip_sfc_writel(rk_sfc, SFC_ABIT, qspi_xfer->address.size * 8 - 1);
        }

        ctrl |= ((qspi_xfer->address.qspi_lines >> 1) << SFC_CTRL_ADDR_BITS_SHIFT);
    }

    /* data */
    if (rk_sfc->version >= SFC_VER_4)
    {
        /* Clear it if no data to transfer */
        rockchip_sfc_writel(rk_sfc, SFC_LEN_EXT, len);
    }
    else
    {
        cmd |= len << SFC_CMD_TRAN_BYTES_SHIFT;
    }
    if (len)
    {
        if (qspi_xfer->parent.send_buf)
        {
            cmd |= SFC_CMD_DIR_WR << SFC_CMD_DIR_SHIFT;
        }

        ctrl |= ((qspi_xfer->qspi_data_lines >> 1) << SFC_CTRL_DATA_BITS_SHIFT);
    }
    if (!len && qspi_xfer->address.size)
    {
        cmd |= SFC_CMD_DIR_WR << SFC_CMD_DIR_SHIFT;
    }

    /* controller */
    ctrl |= SFC_CTRL_PHASE_SEL_NEGETIVE;
    cmd |= spi_dev->chip_select[0] << SFC_CMD_CS_SHIFT;

    rockchip_sfc_writel(rk_sfc, SFC_CTRL, ctrl);
    rockchip_sfc_writel(rk_sfc, SFC_CMD, cmd);

    if (qspi_xfer->address.size)
    {
        rockchip_sfc_writel(rk_sfc, SFC_ADDR, qspi_xfer->address.content);
    }

    return RT_EOK;
}

static void rockchip_sfc_adjust_op_work(struct rt_qspi_message *qspi_xfer)
{
    if (qspi_xfer->alternate_bytes.size && !qspi_xfer->address.size)
    {
        /*
         * SFC not support output DUMMY cycles right after CMD cycles, so
         * treat it as ADDR cycles.
         */
        qspi_xfer->address.size = qspi_xfer->alternate_bytes.size;
        qspi_xfer->address.qspi_lines = qspi_xfer->alternate_bytes.qspi_lines;
        qspi_xfer->address.content = 0xffffffff;

        qspi_xfer->alternate_bytes.size = 0;
    }
}

static rt_err_t rockchip_sfc_exec_op_bypass(struct rockchip_sfc *rk_sfc,
        struct rt_spi_device *spi_dev, struct rt_qspi_message *qspi_xfer)
{
    rt_uint32_t res, len;

    len = rt_min_t(rt_uint32_t, qspi_xfer->parent.length, rk_sfc->max_iosize);

    rockchip_sfc_adjust_op_work(qspi_xfer);
    rockchip_sfc_xfer_setup(rk_sfc, spi_dev, qspi_xfer);
    res = rockchip_sfc_xfer_data_poll(rk_sfc, &qspi_xfer->parent);

    if (res != len)
    {
        LOG_E("xfer data failed ret %d", res);

        return -RT_EIO;
    }

    return rockchip_sfc_xfer_done(rk_sfc, 100000);
}

static void rockchip_sfc_delay_lines_tuning(struct rockchip_sfc *rk_sfc,
        struct rt_spi_device *spi_dev)
{
    rt_uint8_t id[3], id_temp[3];
    rt_bool_t dll_valid = RT_FALSE;
    rt_uint16_t right, left = 0, step = SFC_DLL_TRANING_STEP;
    rt_uint16_t cell_max = (rt_uint16_t)rockchip_sfc_get_max_dll_cells(rk_sfc);
    struct rt_qspi_message qspi_xfer = {};
    struct rt_spi_message *xfer = &qspi_xfer.parent;

    rt_clk_set_rate(rk_sfc->clk, SFC_DLL_THRESHOLD_RATE);

    qspi_xfer.instruction.content = 0x9f;
    qspi_xfer.qspi_data_lines = 1;

    xfer->recv_buf = &id;
    xfer->length = sizeof(id);
    xfer->cs_take = 1;
    xfer->cs_release = 1;
    rockchip_sfc_exec_op_bypass(rk_sfc, spi_dev, &qspi_xfer);

    if ((0xff == id[0] && 0xff == id[1]) || (0x00 == id[0] && 0x00 == id[1]))
    {
        rt_clk_set_rate(rk_sfc->clk, rk_sfc->max_speed_hz);

        return;
    }

    rt_clk_set_rate(rk_sfc->clk, rk_sfc->max_speed_hz);
    xfer->recv_buf = &id_temp;
    xfer->length = sizeof(id_temp);

    for (right = 0; right <= cell_max; right += step)
    {
        int res;

        rockchip_sfc_set_delay_lines(rk_sfc, right);
        rockchip_sfc_exec_op_bypass(rk_sfc, spi_dev, &qspi_xfer);

        res = rt_memcmp(&id, &id_temp, sizeof(id));

        if (dll_valid && res)
        {
            right -= step;
            break;
        }

        if (!dll_valid && !res)
        {
            left = right;
        }

        if (!res)
        {
            dll_valid = RT_TRUE;
        }

        /* Add cell_max to loop */
        if (right == cell_max)
        {
            break;
        }
        if (right + step > cell_max)
        {
            right = cell_max - step;
        }
    }

    if (dll_valid && (right - left) >= SFC_DLL_TRANING_VALID_WINDOW)
    {
        if (left == 0 && right < cell_max)
        {
            rk_sfc->dll_cells = left + (right - left) * 2 / 5;
        }
        else
        {
            rk_sfc->dll_cells = left + (right - left) / 2;
        }
    }
    else
    {
        rk_sfc->dll_cells = 0;
    }

    if (rk_sfc->dll_cells)
    {
        rockchip_sfc_set_delay_lines(rk_sfc, (rt_uint16_t)rk_sfc->dll_cells);
    }
    else
    {
        LOG_E("%d %d dll training failed in %dMHz, reduce the frequency",
                left, right, rk_sfc->max_speed_hz);

        rockchip_sfc_set_delay_lines(rk_sfc, 0);
        rt_clk_set_rate(rk_sfc->clk, SFC_DLL_THRESHOLD_RATE);
        rk_sfc->max_speed_hz = rt_clk_get_rate(rk_sfc->clk);
    }
}

static rt_err_t rockchip_sfc_configure(struct rt_spi_device *device,
        struct rt_spi_configuration *conf)
{
    rt_err_t err;
    struct rockchip_sfc *rk_sfc = raw_to_rockchip_sfc(device->bus);

    if (conf->max_hz != rk_sfc->frequency)
    {
        if ((err = rt_clk_set_rate(rk_sfc->clk, rk_sfc->max_speed_hz)))
        {
            return err;
        }

        rk_sfc->frequency = rk_sfc->max_speed_hz;

        if (rockchip_sfc_get_version(rk_sfc) >= SFC_VER_4)
        {
            if (rt_clk_get_rate(rk_sfc->clk) > SFC_DLL_THRESHOLD_RATE)
            {
                rockchip_sfc_delay_lines_tuning(rk_sfc, device);
            }
            else
            {
                rockchip_sfc_set_delay_lines(rk_sfc, 0);
            }
        }
    }

    return RT_EOK;
}

static rt_ssize_t rockchip_sfc_xfer(struct rt_spi_device *device,
        struct rt_spi_message *xfer)
{
    rt_err_t err;
    rt_ssize_t res, len = xfer->length;
    struct rockchip_sfc *rk_sfc = raw_to_rockchip_sfc(device->bus);
    struct rt_qspi_message *qspi_xfer = rt_container_of(xfer, struct rt_qspi_message, parent);

    rockchip_sfc_adjust_op_work(qspi_xfer);
    rockchip_sfc_xfer_setup(rk_sfc, device, qspi_xfer);

    if (qspi_xfer->alternate_bytes.size > 0)
    {
        rt_uint8_t buf[4];
        rt_size_t size = qspi_xfer->alternate_bytes.size / 8;

        rt_memcpy(buf, &qspi_xfer->alternate_bytes.content, size);
        rockchip_sfc_write_fifo(rk_sfc, buf, size);
    }

    if (len > 0)
    {
        if (rk_sfc->use_dma && len >= SFC_DMA_TRANS_THRETHOLD && !(len & 0x3))
        {
            rockchip_sfc_irq_unmask(rk_sfc, SFC_IMR_DMA);
            res = rockchip_sfc_xfer_data_dma(rk_sfc, xfer);
        }
        else
        {
            res = rockchip_sfc_xfer_data_poll(rk_sfc, xfer);
        }

        if (res != len)
        {
            LOG_E("xfer data failed");
            return -RT_EIO;
        }
    }

    if ((err = rockchip_sfc_xfer_done(rk_sfc, 100000)))
    {
        res = err;
    }

    return res;
}

static const struct rt_spi_ops rockchip_sfc_ops =
{
    .configure = rockchip_sfc_configure,
    .xfer = rockchip_sfc_xfer,
};

static void rockchip_sfc_isr(int irqno, void *param)
{
    rt_uint32_t isr;
    struct rockchip_sfc *rk_sfc = param;

    isr = rockchip_sfc_readl(rk_sfc, SFC_RISR);
    /* Clear interrupt */
    rockchip_sfc_writel(rk_sfc, SFC_ICLR, isr);

    if (isr & SFC_RISR_DMA)
    {
        rt_completion_done(&rk_sfc->done);
    }
}

static void rockchip_sfc_free(struct rockchip_sfc *rk_sfc)
{
    if (rk_sfc->regs)
    {
        rt_iounmap(rk_sfc->regs);
    }

    if (!rt_is_err_or_null(rk_sfc->clk))
    {
        rt_clk_put(rk_sfc->clk);
    }

    if (!rt_is_err_or_null(rk_sfc->hclk))
    {
        rt_clk_put(rk_sfc->hclk);
    }

    if (rk_sfc->dma_buffer)
    {
        rt_dma_free_coherent(&rk_sfc->pdev->parent,
                SFC_MAX_IOSIZE_VER3, rk_sfc->dma_buffer, rk_sfc->dma_buffer_phy);
    }

    rt_free(rk_sfc);
}

static rt_err_t rockchip_sfc_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *bus_name;
    struct rt_device *dev = &pdev->parent;
    struct rockchip_sfc *rk_sfc = rt_calloc(1, sizeof(*rk_sfc));

    if (!rk_sfc)
    {
        return -RT_ENOMEM;
    }

    rk_sfc->pdev = pdev;
    rk_sfc->regs = rt_dm_dev_iomap(dev, 0);

    if (!rk_sfc->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rk_sfc->clk = rt_clk_get_by_name(dev, "clk_sfc");

    if (rt_is_err(rk_sfc->clk))
    {
        err = rt_ptr_err(rk_sfc->clk);
        goto _fail;
    }

    rk_sfc->hclk = rt_clk_get_by_name(dev, "hclk_sfc");

    if (rt_is_err(rk_sfc->hclk))
    {
        err = rt_ptr_err(rk_sfc->hclk);
        goto _fail;
    }

    rk_sfc->irq = rt_dm_dev_get_irq(dev, 0);

    if (rk_sfc->irq < 0)
    {
        err = rk_sfc->irq;
        goto _fail;
    }

    rk_sfc->use_dma = !rt_dm_dev_prop_read_bool(dev, "rockchip,sfc-no-dma");

    if (rk_sfc->use_dma)
    {
        rk_sfc->dma_buffer = rt_dma_alloc_coherent(dev,
                SFC_MAX_IOSIZE_VER3, &rk_sfc->dma_buffer_phy);

        if (!rk_sfc->dma_buffer)
        {
            err = -RT_ENOMEM;
            LOG_E("Could not alloc DMA memory witch cache");

            goto _fail;
        }
    }

    if ((err = rt_clk_prepare_enable(rk_sfc->hclk)))
    {
        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(rk_sfc->clk)))
    {
        goto _fail;
    }

#ifdef RT_USING_OFW
    if (rt_ofw_bootargs_select("rockchip.thunder_boot", 0))
    {
        if (rockchip_sfc_poll(rk_sfc, SFC_SR, SFC_SR_IS_BUSY, RT_FALSE, 10, 500000))
        {
            LOG_E("Wait for SFC idle timeout");
        }
    }
#endif

    if ((err = rockchip_sfc_init(rk_sfc)))
    {
        goto _fail;
    }

    rk_sfc->max_iosize = rockchip_sfc_get_max_iosize(rk_sfc);
    rk_sfc->version = rockchip_sfc_get_version(rk_sfc);

    rk_sfc->max_speed_hz = SFC_MAX_SPEED;
    rk_sfc->parent.num_chipselect = SFC_MAX_CHIPSELECT_NUM;
    rt_completion_init(&rk_sfc->done);

    dev->user_data = rk_sfc;

    rk_sfc->parent.parent.ofw_node = dev->ofw_node;

    rt_dm_dev_set_name_auto(&rk_sfc->parent.parent, "qspi");
    bus_name = rt_dm_dev_get_name(&rk_sfc->parent.parent);

    rt_hw_interrupt_install(rk_sfc->irq, rockchip_sfc_isr, rk_sfc, bus_name);
    rt_hw_interrupt_umask(rk_sfc->irq);

    if ((err = rt_qspi_bus_register(&rk_sfc->parent, bus_name, &rockchip_sfc_ops)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    rockchip_sfc_free(rk_sfc);

    return err;
}

static rt_err_t rockchip_sfc_remove(struct rt_platform_device *pdev)
{
    struct rockchip_sfc *rk_sfc = pdev->parent.user_data;

    rt_hw_interrupt_mask(rk_sfc->irq);
    rt_pic_detach_irq(rk_sfc->irq, rk_sfc);

    rt_device_unregister(&rk_sfc->parent.parent);

    rockchip_sfc_free(rk_sfc);

    return RT_EOK;
}

static const struct rt_ofw_node_id rockchip_sfc_ofw_ids[] =
{
    { .compatible = "rockchip,sfc", },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_sfc_driver =
{
    .name = "rockchip-sfc",
    .ids = rockchip_sfc_ofw_ids,

    .probe = rockchip_sfc_probe,
    .remove = rockchip_sfc_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rockchip_sfc_driver);
