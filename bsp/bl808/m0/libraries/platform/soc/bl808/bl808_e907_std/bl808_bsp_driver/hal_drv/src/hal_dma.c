/**
 * *****************************************************************************
 * @file hal_dma.c
 * @version 0.1
 * @date 2021-03-01
 * @brief
 * *****************************************************************************
 * @attention
 *
 *  <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
 *
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *    1. Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright notice,
 *       this list of conditions and the following disclaimer in the documentation
 *       and/or other materials provided with the distribution.
 *    3. Neither the name of Bouffalo Lab nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * *****************************************************************************
 */
#include "hal_dma.h"
#include "bl808_dma.h"

#define DMA_CHANNEL_BASE(id_base, ch) ((id_base) + DMA_CHANNEL_OFFSET + (ch)*0x100)

__UNUSED__ static const uint32_t dma_channel_base[][8] = {
    {
        DMA_CHANNEL_BASE(DMA0_BASE, 0),
        DMA_CHANNEL_BASE(DMA0_BASE, 1),
        DMA_CHANNEL_BASE(DMA0_BASE, 2),
        DMA_CHANNEL_BASE(DMA0_BASE, 3),
        DMA_CHANNEL_BASE(DMA0_BASE, 4),
        DMA_CHANNEL_BASE(DMA0_BASE, 5),
        DMA_CHANNEL_BASE(DMA0_BASE, 6),
        DMA_CHANNEL_BASE(DMA0_BASE, 7),
    },
    {
        DMA_CHANNEL_BASE(DMA1_BASE, 0),
        DMA_CHANNEL_BASE(DMA1_BASE, 1),
        DMA_CHANNEL_BASE(DMA1_BASE, 2),
        DMA_CHANNEL_BASE(DMA1_BASE, 3),
        DMA_CHANNEL_BASE(DMA1_BASE, 4),
        DMA_CHANNEL_BASE(DMA1_BASE, 5),
        DMA_CHANNEL_BASE(DMA1_BASE, 6),
        DMA_CHANNEL_BASE(DMA1_BASE, 7),
    },
    {
        DMA_CHANNEL_BASE(DMA2_BASE, 0),
        DMA_CHANNEL_BASE(DMA2_BASE, 1),
        DMA_CHANNEL_BASE(DMA2_BASE, 2),
        DMA_CHANNEL_BASE(DMA2_BASE, 3),
        DMA_CHANNEL_BASE(DMA2_BASE, 4),
        DMA_CHANNEL_BASE(DMA2_BASE, 5),
        DMA_CHANNEL_BASE(DMA2_BASE, 6),
        DMA_CHANNEL_BASE(DMA2_BASE, 7),
    }

};

void DMA0_IRQ(void);
void DMA1_IRQ(void);
void (*p_dma2_chn_irq[])(void);

dma_device_t dmax_device[DMA_MAX_INDEX] = {
#ifdef BSP_USING_DMA0_CH0
    DMA0_CH0_CONFIG,
#endif
#ifdef BSP_USING_DMA0_CH1
    DMA0_CH1_CONFIG,
#endif
#ifdef BSP_USING_DMA0_CH2
    DMA0_CH2_CONFIG,
#endif
#ifdef BSP_USING_DMA0_CH3
    DMA0_CH3_CONFIG,
#endif
#ifdef BSP_USING_DMA0_CH4
    DMA0_CH4_CONFIG,
#endif
#ifdef BSP_USING_DMA0_CH5
    DMA0_CH5_CONFIG,
#endif
#ifdef BSP_USING_DMA0_CH6
    DMA0_CH6_CONFIG,
#endif
#ifdef BSP_USING_DMA0_CH7
    DMA0_CH7_CONFIG,
#endif
#ifdef BSP_USING_DMA1_CH0
    DMA1_CH0_CONFIG,
#endif
#ifdef BSP_USING_DMA1_CH1
    DMA1_CH1_CONFIG,
#endif
#ifdef BSP_USING_DMA1_CH2
    DMA1_CH2_CONFIG,
#endif
#ifdef BSP_USING_DMA1_CH3
    DMA1_CH3_CONFIG,
#endif
#ifdef BSP_USING_DMA1_CH4
    DMA1_CH4_CONFIG,
#endif
#ifdef BSP_USING_DMA1_CH5
    DMA1_CH5_CONFIG,
#endif
#ifdef BSP_USING_DMA1_CH6
    DMA1_CH6_CONFIG,
#endif
#ifdef BSP_USING_DMA1_CH7
    DMA1_CH7_CONFIG,
#endif
#ifdef BSP_USING_DMA2_CH0
    DMA2_CH0_CONFIG,
#endif
#ifdef BSP_USING_DMA2_CH1
    DMA2_CH1_CONFIG,
#endif
#ifdef BSP_USING_DMA2_CH2
    DMA2_CH2_CONFIG,
#endif
#ifdef BSP_USING_DMA2_CH3
    DMA2_CH3_CONFIG,
#endif
#ifdef BSP_USING_DMA2_CH4
    DMA2_CH4_CONFIG,
#endif
#ifdef BSP_USING_DMA2_CH5
    DMA2_CH5_CONFIG,
#endif
#ifdef BSP_USING_DMA2_CH6
    DMA2_CH6_CONFIG,
#endif
#ifdef BSP_USING_DMA2_CH7
    DMA2_CH7_CONFIG,
#endif
};
/**
 * @brief
 *
 * @param dev
 * @param oflag
 * @return int
 */
int dma_open(struct device *dev, uint16_t oflag)
{
#ifdef BSP_USING_DMA
    dma_device_t *dma_device = (dma_device_t *)dev;
    DMA_Channel_Cfg_Type chCfg = { 0 };

    /* Disable all interrupt */
    DMA_IntMask(dma_device->id, dma_device->ch, DMA_INT_ALL, MASK);

    /* disable cpu dma interrupt*/
    switch (dma_device->id)
    {
    case 0:
        CPU_Interrupt_Disable(DMA0_ALL_IRQn);
        break;
    case 1:
        CPU_Interrupt_Disable(DMA1_ALL_IRQn);
        break;
    case 2:
        CPU_Interrupt_Disable(DMA2_INT0_IRQn + dma_device->ch);
        break;

    default:
        return 1;
    }

    DMA_Disable(dma_device->id);

    DMA_Channel_Disable(dma_device->id, dma_device->ch);

    chCfg.ch = dma_device->ch;
    chCfg.dir = dma_device->direction;
    chCfg.srcPeriph = dma_device->src_req;
    chCfg.dstPeriph = dma_device->dst_req;
    chCfg.srcAddrInc = dma_device->src_addr_inc;
    chCfg.destAddrInc = dma_device->dst_addr_inc;
    chCfg.srcBurstSize = dma_device->src_burst_size;
    chCfg.dstBurstSize = dma_device->dst_burst_size;
    chCfg.srcTransfWidth = dma_device->src_width;
    chCfg.dstTransfWidth = dma_device->dst_width;
    DMA_Channel_Init(dma_device->id, &chCfg);

    DMA_Enable(dma_device->id);
    if (dma_device->id == 0) {
        Interrupt_Handler_Register(DMA0_ALL_IRQn, DMA0_IRQ);
        /* Enable dma interrupt*/
        CPU_Interrupt_Enable(DMA0_ALL_IRQn);
    } else if (dma_device->id == 1) {
        Interrupt_Handler_Register(DMA1_ALL_IRQn, DMA1_IRQ);
        /* Enable dma interrupt*/
        CPU_Interrupt_Enable(DMA1_ALL_IRQn);
    } else if(dma_device->id == 2) {
        Interrupt_Handler_Register(DMA2_INT0_IRQn + dma_device->ch, p_dma2_chn_irq[dma_device->ch]);
        /* Enable dma interrupt*/
        CPU_Interrupt_Enable(DMA2_INT0_IRQn + dma_device->ch);
    }
#endif
    return 0;
}
/**
 * @brief
 *
 * @param dev
 * @param cmd
 * @param args
 * @return int
 */
int dma_control(struct device *dev, int cmd, void *args)
{
#ifdef BSP_USING_DMA
    dma_device_t *dma_device = (dma_device_t *)dev;

    switch (cmd) {
        case DEVICE_CTRL_SET_INT:
            DMA_IntMask(dma_device->id, dma_device->ch, DMA_INT_TCOMPLETED, UNMASK);
            DMA_IntMask(dma_device->id, dma_device->ch, DMA_INT_ERR, UNMASK);
            break;

        case DEVICE_CTRL_CLR_INT:
            /* Dma interrupt configuration */
            DMA_IntMask(dma_device->id, dma_device->ch, DMA_INT_TCOMPLETED, MASK);
            DMA_IntMask(dma_device->id, dma_device->ch, DMA_INT_ERR, MASK);
            break;

        case DEVICE_CTRL_GET_INT:
            break;

        case DEVICE_CTRL_CONFIG:
            break;

        case DEVICE_CTRL_DMA_CHANNEL_UPDATE:
            DMA_LLI_Update(dma_device->id, dma_device->ch, (uint32_t)(uintptr_t)args);
            break;

        case DEVICE_CTRL_DMA_CHANNEL_GET_STATUS:
            return DMA_Channel_Is_Busy(dma_device->id, dma_device->ch);

        case DEVICE_CTRL_DMA_CHANNEL_START:
            DMA_Channel_Enable(dma_device->id, dma_device->ch);
            break;

        case DEVICE_CTRL_DMA_CHANNEL_STOP:
            DMA_Channel_Disable(dma_device->id, dma_device->ch);
            break;
        case DEVICE_CTRL_DMA_CONFIG_SI: {
            uint32_t tmpVal = BL_RD_REG(dma_channel_base[dma_device->id][dma_device->ch], DMA_CONTROL);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA_SI, ((uint32_t)(uintptr_t)args) & 0x01);
            BL_WR_REG(dma_channel_base[dma_device->id][dma_device->ch], DMA_CONTROL, tmpVal);

        } break;
        case DEVICE_CTRL_DMA_CONFIG_DI: {
            uint32_t tmpVal = BL_RD_REG(dma_channel_base[dma_device->id][dma_device->ch], DMA_CONTROL);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA_DI, ((uint32_t)(uintptr_t)args) & 0x01);
            BL_WR_REG(dma_channel_base[dma_device->id][dma_device->ch], DMA_CONTROL, tmpVal);

        } break;
        default:
            break;
    }
#endif
    return 0;
}
/**
 * @brief
 *
 * @param dev
 * @return int
 */
int dma_close(struct device *dev)
{
#ifdef BSP_USING_DMA
    dma_device_t *dma_device = (dma_device_t *)dev;
    DMA_Channel_Cfg_Type chCfg = { 0 };
    chCfg.ch = dma_device->ch;

    DMA_Channel_Disable(dma_device->id, dma_device->ch);
    DMA_Channel_Init(dma_device->id, &chCfg);
#endif
    return 0;
}

int dma_register(enum dma_index_type index, const char *name)
{
#ifdef BSP_USING_DMA
    struct device *dev;

    if (DMA_MAX_INDEX == 0) {
        return -DEVICE_EINVAL;
    }

    dev = &(dmax_device[index].parent);

    dev->open = dma_open;
    dev->close = dma_close;
    dev->control = dma_control;
    // dev->write = dma_write;
    // dev->read = dma_read;

    dev->type = DEVICE_CLASS_DMA;
    dev->handle = NULL;

     return device_register(dev, name);
#else
    return 0;
#endif
}
/**
 * @brief
 *
 * @param dev
 * @param src_addr
 * @param dst_addr
 * @param transfer_size
 * @return int
 */
int dma_reload(struct device *dev, uint32_t src_addr, uint32_t dst_addr, uint32_t transfer_size)
{
#ifdef BSP_USING_DMA
    uint32_t malloc_count;
    uint32_t remain_len;
    uint32_t actual_transfer_len = 0;
    uint32_t actual_transfer_offset = 0;
    dma_control_data_t dma_ctrl_cfg;

    dma_device_t *dma_device = (dma_device_t *)dev;

    DMA_Channel_Disable(dma_device->id, dma_device->ch);

    if (transfer_size == 0) {
        return 0;
    }

    switch (dma_device->src_width) {
        case DMA_TRANSFER_WIDTH_8BIT:
            actual_transfer_offset = 4064;
            actual_transfer_len = transfer_size;
            break;
        case DMA_TRANSFER_WIDTH_16BIT:
            if (transfer_size % 2) {
                return -1;
            }
            actual_transfer_offset = 4064 << 1;
            actual_transfer_len = transfer_size >> 1;
            break;
        case DMA_TRANSFER_WIDTH_32BIT:
            if (transfer_size % 4) {
                return -1;
            }
            actual_transfer_offset = 4064 << 2;
            actual_transfer_len = transfer_size >> 2;
            break;

        default:
            return -3;
            break;
    }

    dma_ctrl_cfg = (dma_control_data_t)(BL_RD_REG(dma_channel_base[dma_device->id][dma_device->ch], DMA_CONTROL));

    malloc_count = actual_transfer_len / 4064 + 1;
    remain_len = actual_transfer_len % 4064;

    /* The maximum transfer capacity of the last node is 4095 */
    if(malloc_count > 1 && remain_len < (4095 - 4064)){
        malloc_count --;
        remain_len += 4064;
    }

    dma_device->lli_cfg = (dma_lli_ctrl_t *)realloc(dma_device->lli_cfg, sizeof(dma_lli_ctrl_t) * malloc_count);

    if (dma_device->lli_cfg) {
        dma_ctrl_cfg.bits.TransferSize = 4064;
        dma_ctrl_cfg.bits.I = 0;
        /*transfer_size will be integer multiple of 4064*n or 4064*2*n or 4064*4*n,(n>0) */
        for (uint32_t i = 0; i < malloc_count; i++) {
            dma_device->lli_cfg[i].src_addr = src_addr;
            dma_device->lli_cfg[i].dst_addr = dst_addr;
            dma_device->lli_cfg[i].nextlli = 0;

            if (dma_ctrl_cfg.bits.SI) {
                src_addr += actual_transfer_offset;
            }

            if (dma_ctrl_cfg.bits.DI) {
                dst_addr += actual_transfer_offset;
            }

            if (i == malloc_count - 1) {
                dma_ctrl_cfg.bits.TransferSize = remain_len;
                dma_ctrl_cfg.bits.I = 1;

                if (dma_device->transfer_mode == DMA_LLI_CYCLE_MODE) {
                    dma_device->lli_cfg[i].nextlli = (uint32_t)(uintptr_t)&dma_device->lli_cfg[0];
                }
            }

            if (i) {
                dma_device->lli_cfg[i - 1].nextlli = (uint32_t)(uintptr_t)&dma_device->lli_cfg[i];
            }

            dma_device->lli_cfg[i].cfg = dma_ctrl_cfg;
        }
        /* clean cache, DMA does not pass through the cache */
        csi_dcache_clean_range((void*)(dma_device->lli_cfg), sizeof(dma_lli_ctrl_t) * malloc_count);

        BL_WR_REG(dma_channel_base[dma_device->id][dma_device->ch], DMA_SRCADDR, dma_device->lli_cfg[0].src_addr);
        BL_WR_REG(dma_channel_base[dma_device->id][dma_device->ch], DMA_DSTADDR, dma_device->lli_cfg[0].dst_addr);
        BL_WR_REG(dma_channel_base[dma_device->id][dma_device->ch], DMA_LLI, dma_device->lli_cfg[0].nextlli);
        BL_WR_REG(dma_channel_base[dma_device->id][dma_device->ch], DMA_CONTROL, dma_device->lli_cfg[0].cfg.WORD);
    } else {
        return -2;
    }
#endif
    return 0;
}

/**
 * @brief
 *
 * @param handle
 */
void dma_channel_isr(dma_device_t *handle)
{
#ifdef BSP_USING_DMA
    uint32_t tmpVal;
    uint32_t intClr;
    const uint32_t dmaAddr[] = { DMA0_BASE, DMA1_BASE, DMA2_BASE };

    /* Get DMA register */
    uint32_t DMAChs = dmaAddr[handle->id];

    if (!handle->parent.callback) {
        return;
    }

    tmpVal = BL_RD_REG(DMAChs, DMA_INTTCSTATUS);
    if ((BL_GET_REG_BITS_VAL(tmpVal, DMA_INTTCSTATUS) & (1 << handle->ch)) != 0) {
        /* Clear interrupt */
        tmpVal = BL_RD_REG(DMAChs, DMA_INTTCCLEAR);
        intClr = BL_GET_REG_BITS_VAL(tmpVal, DMA_INTTCCLEAR);
        intClr |= (1 << handle->ch);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA_INTTCCLEAR, intClr);
        BL_WR_REG(DMAChs, DMA_INTTCCLEAR, tmpVal);
        handle->parent.callback(&handle->parent, NULL, 0, DMA_INT_TCOMPLETED);
    }

    tmpVal = BL_RD_REG(DMAChs, DMA_INTERRORSTATUS);
    if ((BL_GET_REG_BITS_VAL(tmpVal, DMA_INTERRORSTATUS) & (1 << handle->ch)) != 0) {
        /*Clear interrupt */
        tmpVal = BL_RD_REG(DMAChs, DMA_INTERRCLR);
        intClr = BL_GET_REG_BITS_VAL(tmpVal, DMA_INTERRCLR);
        intClr |= (1 << handle->ch);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA_INTERRCLR, intClr);
        BL_WR_REG(DMAChs, DMA_INTERRCLR, tmpVal);
        handle->parent.callback(&handle->parent, NULL, 0, DMA_INT_ERR);
    }
#endif
}

/**
 * @brief
 *
 */
void DMA0_IRQ(void)
{
    for (uint8_t i = 0; i < DMA_MAX_INDEX; i++) {
        if (dmax_device[i].id == 0) {
            dma_channel_isr(&dmax_device[i]);
        }
    }
}

/**
 * @brief
 *
 */
void DMA1_IRQ(void)
{
    for (uint8_t i = 0; i < DMA_MAX_INDEX; i++) {
        if (dmax_device[i].id == 1) {
            dma_channel_isr(&dmax_device[i]);
        }
    }
}

/**
 * @brief
 *
 */
void dma2_common_irq(uint8_t ch)
{
    for (uint8_t i = 0; i < DMA_MAX_INDEX; i++) {
        if (dmax_device[i].id == 2 && dmax_device[i].ch == ch) {
            dma_channel_isr(&dmax_device[i]);
        }
    }
}

/**
 * @brief
 *
 */
void DMA2_CH0_IRQ(void)
{
    dma2_common_irq(0);
}

void DMA2_CH1_IRQ(void)
{
    dma2_common_irq(1);
}

void DMA2_CH2_IRQ(void)
{
    dma2_common_irq(2);
}

void DMA2_CH3_IRQ(void)
{
    dma2_common_irq(3);
}

void DMA2_CH4_IRQ(void)
{
    dma2_common_irq(4);
}

void DMA2_CH5_IRQ(void)
{
    dma2_common_irq(5);
}

void DMA2_CH6_IRQ(void)
{
    dma2_common_irq(6);
}

void DMA2_CH7_IRQ(void)
{
    dma2_common_irq(7);
}

void (*p_dma2_chn_irq[])(void) = {DMA2_CH0_IRQ, DMA2_CH1_IRQ, DMA2_CH2_IRQ, DMA2_CH3_IRQ, DMA2_CH4_IRQ, DMA2_CH5_IRQ, DMA2_CH6_IRQ, DMA2_CH7_IRQ};
