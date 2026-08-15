/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#ifndef __ROCKCHIP_I2S_TDM_H__
#define __ROCKCHIP_I2S_TDM_H__

#include <rtthread.h>
#include <rtdevice.h>

/* I2S register offsets */
#define I2S_TXCR            0x0000
#define I2S_RXCR            0x0004
#define I2S_CKR             0x0008
#define I2S_TXFIFOLR        0x000c
#define I2S_DMACR           0x0010
#define I2S_INTCR           0x0014
#define I2S_INTSR           0x0018
#define I2S_XFER            0x001c
#define I2S_CLR             0x0020
#define I2S_TXDR            0x0024
#define I2S_RXDR            0x0028
#define I2S_CLKDIV          0x0038

#define I2S_TXCR_VDW(x)     (((x) - 1) << 0)
#define I2S_TXCR_VDW_MASK   (0x1f << 0)
#define I2S_TXCR_CSR(x)     ((x) << 15)
#define I2S_TXCR_CSR_MASK   (3 << 15)
#define I2S_TXCR_IBM_NORMAL (0 << 9)
#define I2S_TXCR_TFS_I2S    (0 << 5)

#define I2S_CKR_TRCM_TXONLY (1 << 28)
#define I2S_CKR_TRCM_MASK   (3 << 28)
#define I2S_CKR_MSS_MASTER  (0 << 27)
#define I2S_CKR_MSS_MASK    (1 << 27)
#define I2S_CKR_CKP_NORMAL  (0 << 26)
#define I2S_CKR_TLP_NORMAL  (0 << 24)
#define I2S_CKR_RLP_NORMAL  (0 << 25)
#define I2S_CKR_TSD(x)      (((x) - 1) << 0)
#define I2S_CKR_TSD_MASK    (0xff << 0)

#define I2S_CLKDIV_TXM(x)   (((x) - 1) << 0)
#define I2S_CLKDIV_TXM_MASK (0xff << 0)

#define I2S_CHN_2           (0 << 15)

#define I2S_DMACR_TDE_ENABLE (1 << 8)
#define I2S_DMACR_TDE_MASK   (1 << 8)
#define I2S_DMACR_TDL(x)    ((x) << 0)
#define I2S_DMACR_TDL_MASK  (0x1f << 0)

#define I2S_XFER_TXS_START  (1 << 0)
#define I2S_XFER_TXS_STOP   (0 << 0)
#define I2S_XFER_TXS_MASK   (1 << 0)
#define I2S_XFER_RXS_START  (1 << 1)
#define I2S_XFER_RXS_STOP   (0 << 1)
#define I2S_XFER_RXS_MASK   (1 << 1)

#define I2S_CLR_TXC         RT_BIT(0)

#define I2S_FIFOLR_TFL0_MASK 0x3f

#define RK3568_I2S1_GRF_REG     0x504
#define RK3568_I2S1_CLK_TXONLY  ((1 << (5 + 16)) | (1 << 5))

#define I2S_DEFAULT_FRAME_WIDTH  64

struct rockchip_i2s_config
{
    rt_uint32_t samplerate;
    rt_uint16_t channels;
    rt_uint16_t samplebits;
    rt_uint32_t mclk_fs;
};

struct rockchip_i2s_tdm;

rt_err_t rockchip_i2s_tdm_hw_params(struct rockchip_i2s_tdm *i2s,
        const struct rockchip_i2s_config *cfg);
rt_err_t rockchip_i2s_tdm_start(struct rockchip_i2s_tdm *i2s);
rt_err_t rockchip_i2s_tdm_stop(struct rockchip_i2s_tdm *i2s);
rt_ssize_t rockchip_i2s_tdm_push(struct rockchip_i2s_tdm *i2s,
        const rt_uint8_t *buf, rt_size_t size);
struct rockchip_i2s_tdm *rockchip_i2s_tdm_find(struct rt_ofw_node *np);

#ifdef RT_USING_DMA
struct rt_dma_chan *rockchip_i2s_tdm_get_dma_tx(struct rockchip_i2s_tdm *i2s);
rt_ubase_t rockchip_i2s_tdm_txdr_phys(struct rockchip_i2s_tdm *i2s);
rt_err_t rockchip_i2s_tdm_dma_enable(struct rockchip_i2s_tdm *i2s);
rt_err_t rockchip_i2s_tdm_dma_disable(struct rockchip_i2s_tdm *i2s);
#endif

#endif /* __ROCKCHIP_I2S_TDM_H__ */
