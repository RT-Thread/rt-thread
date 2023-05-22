/**
  ******************************************************************************
  * @file    bflb_emac.c
  * @version V1.0
  * @date    2022-09-27
  * @brief   This file is the low hardware abstraction layer file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2022 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#include "bflb_emac.h"
#include "bflb_clock.h"
#include "bflb_l1c.h"
#include "hardware/emac_reg.h"

/* private definition */
// #define TAG                   "EMAC_BD: "
#define EMAC_TX_COMMON_FLAGS (EMAC_BD_TX_RD_MASK | EMAC_BD_TX_IRQ_MASK | EMAC_BD_TX_PAD_MASK | EMAC_BD_TX_CRC_MASK | EMAC_BD_TX_EOF_MASK)
#define EMAC_RX_COMMON_FLAGS ((ETH_MAX_PACKET_SIZE << 16) | EMAC_BD_RX_IRQ_MASK)

/**
 *  @brief Note: Always write DWORD1 (buffer addr) first then DWORD0 for racing concern.
 */
struct bflb_emac_bd_desc_s {
    uint32_t C_S_L;  /*!< Buffer Descriptors(BD) control,status,length */
    uint32_t Buffer; /*!< BD buffer address */
};

/**
 * @brief emac handle type definition
 * @param bd             Tx descriptor header pointer
 * @param tx_index_emac  TX index: EMAC
 * @param tx_index_cpu   TX index: CPU/SW
 * @param tx_buff_limit  TX index max
 * @param rsv0           rsv0
 * @param rx_index_emac  RX index: EMAC
 * @param rx_index_cpu   RX index: CPU/SW
 * @param rx_buff_limit  RX index max
 * @param rsv1           rsv1
 *
 */
struct bflb_emac_handle_s {
    struct bflb_emac_bd_desc_s *bd;
    uint8_t tx_index_emac;
    uint8_t tx_index_cpu;
    uint8_t tx_buff_limit;
    uint8_t rsv0;
    uint8_t rx_index_emac;
    uint8_t rx_index_cpu;
    uint8_t rx_buff_limit;
    uint8_t rsv1;
};

static struct bflb_emac_handle_s eth_handle;
static struct bflb_emac_handle_s *thiz = NULL;

/**
 *
 * @brief get emac current active buffer describe index
 * @param dev
 * @param bdt @ref emac buffer descriptors type define
 * @return uint32_t
 *
 */
uint32_t bflb_emac_bd_get_cur_active(struct bflb_device_s *dev, uint8_t bdt)
{
    uint32_t bd = 0;
    uint32_t reg_base;
    reg_base = dev->reg_base;

    bd = getreg32(reg_base + EMAC_TX_BD_NUM_OFFSET);

    if (bdt == EMAC_BD_TYPE_TX) {
        bd &= EMAC_TXBDPTR_MASK;
        bd >>= EMAC_TXBDPTR_SHIFT;
    }

    if (bdt == EMAC_BD_TYPE_RX) {
        bd &= EMAC_RXBDPTR_MASK;
        bd >>= EMAC_RXBDPTR_SHIFT;
    }

    return bd;
}
/**
 * @brief
 *
 * @param index
 *
 */
void bflb_emac_bd_rx_enqueue(uint32_t index)
{
    thiz->rx_index_emac = index;
}

/**
 * @brief
 *
 * @param index
 *
 */
void bflb_emac_bd_rx_on_err(uint32_t index)
{
    /* handle error */
    if (thiz->bd[index].C_S_L & EMAC_BD_RX_OR_MASK) {
        printf("EMAC RX OR Error at %s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & EMAC_BD_RX_RE_MASK) {
        printf("MAC RX RE Error at %s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & EMAC_BD_RX_DN_MASK) {
        printf("MAC RX DN Error at %s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & EMAC_BD_RX_TL_MASK) {
        printf("MAC RX TL Error at %s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & EMAC_BD_RX_CRC_MASK) {
        printf("MAC RX CRC Error at %s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & EMAC_BD_RX_LC_MASK) {
        printf("MAC RX LC Error at %s:%d\r\n", __func__, __LINE__);
    }

    thiz->bd[index].C_S_L &= ~0xff;
    /* RX BD is ready for RX */
    thiz->bd[index].C_S_L |= EMAC_BD_RX_E_MASK;
}

/**
 * @brief this func will be called in ISR
 *
 * @param index
 *
 */
void bflb_emac_bd_tx_dequeue(uint32_t index)
{
    struct bflb_emac_bd_desc_s *DMADesc;

    thiz->tx_index_emac = index;
    DMADesc = &thiz->bd[thiz->tx_index_emac];
    /* release this tx BD to SW (HW will do this) */
    DMADesc->C_S_L &= ~EMAC_BD_TX_RD_MASK;
}

/**
 * @brief
 *
 * @param index
 * @return int
 */
void bflb_emac_bd_tx_on_err(uint32_t index)
{
    /* handle error */
    if (thiz->bd[index].C_S_L & EMAC_BD_TX_UR_MASK) {
        printf("%s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & EMAC_BD_TX_RTRY_MASK) {
        printf("%s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & EMAC_BD_TX_RL_MASK) {
        printf("%s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & EMAC_BD_TX_LC_MASK) {
        printf("%s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & EMAC_BD_TX_DF_MASK) {
        printf("%s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & EMAC_BD_TX_CS_MASK) {
        printf("%s:%d\r\n", __func__, __LINE__);
    }

    thiz->bd[index].C_S_L &= ~0xff;
}
/**
 * @brief
 *
 * @param none
 * @return int
 */
int emac_bd_fragment_support(void)
{
#if defined(BL616) || defined(BL808)
    return 1;
#elif defined(BL702)
    return 0;
#elif defined(BL628)
    return 1;
#endif
}
/**
 * @brief
 *
 * @param flags
 * @param len
 * @param data_in
 * @return int
 */
int bflb_emac_bd_tx_enqueue(uint32_t flags, uint32_t len, const uint8_t *data_in)
{
    uint32_t err = 0;
    struct bflb_emac_bd_desc_s *DMADesc;
    uint32_t tx_flags = EMAC_TX_COMMON_FLAGS;
    DMADesc = &thiz->bd[thiz->tx_index_cpu];

    if (flags & EMAC_FRAGMENT_PACKET) {
        /* Fragment packet, clear EOF */
        tx_flags &= ~EMAC_BD_TX_EOF_MASK;
    }

    if (DMADesc->C_S_L & EMAC_BD_TX_RD_MASK) {
        /* no free BD, lost sync with DMA TX? */
        err = 4;
        //printf(TAG"%s:%d\n", __func__, __LINE__);
    } else {
#if defined(BL616)
        __ASM volatile("fence");
#endif
        // printf("tx q flags:%d,len:%d,data:0x%x\r\n", flags, len, data_in);
        if (flags & EMAC_NOCOPY_PACKET) {
            DMADesc->Buffer = (uint32_t)(uintptr_t)data_in;
        } else {
            // memcpy((void *)(uintptr_t)(DMADesc->Buffer), data_in, len);
            arch_memcpy_fast((void *)(uintptr_t)(DMADesc->Buffer), data_in, len);
        }

#ifdef EMAC_DO_FLUSH_DATA
#if defined(BL616)
        bflb_l1c_dcache_invalidate_range((void *)DMADesc->Buffer, len);
#endif
#endif
        DMADesc->C_S_L = tx_flags | (len << EMAC_BD_TX_LEN_SHIFT);

        /* move to next TX BD */
        if ((++thiz->tx_index_cpu) > thiz->tx_buff_limit) {
            /* the last BD */
            DMADesc->C_S_L |= EMAC_BD_TX_WR_MASK;
            /* wrap back */
            thiz->tx_index_cpu = 0;
        }
    }

    return err;
}

/**
 * @brief
 *
 * @param flags
 * @param len
 * @param data_out
 * @return int
 */
int bflb_emac_bd_rx_dequeue(uint32_t flags, uint32_t *len, uint8_t *data_out)
{
    uint32_t err = 0;
    struct bflb_emac_bd_desc_s *DMADesc;

    DMADesc = &thiz->bd[thiz->rx_index_cpu];

    if (DMADesc->C_S_L & EMAC_BD_RX_E_MASK) {
        /* current RX BD is empty */
        err = 4;
        *len = 0;
    } else {
        *len = (thiz->bd[thiz->rx_index_cpu].C_S_L & EMAC_BD_RX_LEN_MASK) >> EMAC_BD_RX_LEN_SHIFT;
#ifdef EMAC_DO_FLUSH_DATA
#if defined(BL616)
        bflb_l1c_dcache_invalidate_range((void *)DMADesc->Buffer, *len);
#endif
#endif
        if (data_out) {
            // memcpy(data_out, (const void *)(uintptr_t)DMADesc->Buffer, *len);
            arch_memcpy_fast(data_out, (const void *)(uintptr_t)DMADesc->Buffer, *len);
        }

        /* RX BD can be used for another receive */
        DMADesc->C_S_L |= EMAC_BD_RX_E_MASK;

        /* move to next RX BD */
        if ((++thiz->rx_index_cpu) > thiz->rx_buff_limit) {
            /* the last BD */
            DMADesc->C_S_L |= EMAC_BD_RX_WR_MASK;
            /* wrap back */
            thiz->rx_index_cpu = thiz->tx_buff_limit + 1;
        }
    }

    return err;
}

/**
 * @brief bflb emac init
 *
 * @param dev
 * @param config
 *
 */
void bflb_emac_init(struct bflb_device_s *dev, const struct bflb_emac_config_s *config)
{
    uint32_t reg_base;
    uint32_t reg_val;

#if defined(BL616) || defined(BL808)
#define GLB_EMAC_CLK_OUT_ADDRESS (0x20000390)
#define GLB_UNGATE_CFG2_ADDRESS  (0x20000588)

    /* GLB select inside clock or Not */
    reg_val = getreg32(GLB_EMAC_CLK_OUT_ADDRESS);
    if (config->inside_clk == EMAC_CLK_USE_INTERNAL) {
        reg_val |= (1 << 5);
        reg_val |= (1 << 6);
        reg_val &= ~(1 << 7);
        reg_val |= (1 << 10);
    } else {
        reg_val &= ~(1 << 5);
        reg_val &= ~(1 << 6);
        reg_val &= ~(1 << 7);
    }
    putreg32(reg_val, GLB_EMAC_CLK_OUT_ADDRESS);

    /* ungate emac clock */
    reg_val = getreg32(GLB_UNGATE_CFG2_ADDRESS);
    reg_val |= (1 << 23);
    putreg32(reg_val, GLB_UNGATE_CFG2_ADDRESS);
#elif defined(BL702)
    /* enable audio clock and GLB select inside clock or Not */
// #define PDS_AUDIO_PLL_EN_ADDRESS (0x4000E41C)
#define GLB_UNGATE_CFG1_ADDRESS (0x40000024)
#define GLB_CLOCK_CFG3_ADDRESS  (0x4000000C)

    // reg_val = getreg32(PDS_AUDIO_PLL_EN_ADDRESS);
    // reg_val |= (1 << 7);
    // putreg32(reg_val, PDS_AUDIO_PLL_EN_ADDRESS);

    reg_val = getreg32(GLB_CLOCK_CFG3_ADDRESS);
    if (config->inside_clk == EMAC_CLK_USE_INTERNAL) {
        reg_val |= (1 << 5);
    } else {
        reg_val &= ~(1 << 5);
    }
    putreg32(reg_val, GLB_CLOCK_CFG3_ADDRESS);

    /* ungate emac clock */
    reg_val = getreg32(GLB_UNGATE_CFG1_ADDRESS);
    reg_val |= (1 << 0x0d);
    putreg32(reg_val, GLB_UNGATE_CFG1_ADDRESS);
#endif

    reg_base = dev->reg_base;
    /* set mac defualt config , enable rmii and other*/
    reg_val = getreg32(reg_base + EMAC_MODE_OFFSET);
    reg_val |= (EMAC_RMII_EN);
    reg_val |= (EMAC_PRO);
    reg_val |= (EMAC_BRO);
    reg_val &= ~(EMAC_NOPRE);
    reg_val |= (EMAC_PAD);
    reg_val |= (EMAC_CRCEN);
    reg_val &= ~(EMAC_HUGEN);
    reg_val |= (EMAC_RECSMALL);
    reg_val |= (EMAC_IFG);
    putreg32(reg_val, reg_base + EMAC_MODE_OFFSET);

    /* set inter frame gap defualt value */
    reg_val = getreg32(reg_base + EMAC_IPGT_OFFSET);
    reg_val &= ~(EMAC_IPGT_MASK);
    reg_val |= (0x18) << EMAC_IPGT_SHIFT;
    putreg32(reg_val, reg_base + EMAC_IPGT_OFFSET);

    /* set MII interface */
    reg_val = getreg32(reg_base + EMAC_MIIMODE_OFFSET);
    reg_val |= EMAC_MIINOPRE;
    reg_val &= ~(EMAC_CLKDIV_MASK);
    reg_val |= (config->mii_clk_div) << EMAC_CLKDIV_SHIFT;
    putreg32(reg_val, reg_base + EMAC_MIIMODE_OFFSET);

    /* set collision */
    reg_val = getreg32(reg_base + EMAC_COLLCONFIG_OFFSET);
    reg_val &= ~(EMAC_MAXFL_MASK | EMAC_COLLVALID_MASK);
    reg_val |= (0xf) << EMAC_MAXFL_SHIFT;
    reg_val |= (0x10) << EMAC_COLLVALID_SHIFT;
    putreg32(reg_val, reg_base + EMAC_COLLCONFIG_OFFSET);

    /* set frame length */
    reg_val = getreg32(reg_base + EMAC_PACKETLEN_OFFSET);
    reg_val &= ~(EMAC_MINFL_MASK | EMAC_MAXFL_MASK);
    reg_val |= (config->min_frame_len) << EMAC_MINFL_SHIFT;
    reg_val |= (config->max_frame_len) << EMAC_MAXFL_SHIFT;
    putreg32(reg_val, reg_base + EMAC_PACKETLEN_OFFSET);

    /* set emac address */
    reg_val = getreg32(reg_base + EMAC_MAC_ADDR0_OFFSET);
    reg_val &= ~(EMAC_MAC_B2_MASK | EMAC_MAC_B3_MASK | EMAC_MAC_B4_MASK | EMAC_MAC_B5_MASK);
    reg_val |= (config->mac_addr[5]) << EMAC_MAC_B5_SHIFT;
    reg_val |= (config->mac_addr[4]) << EMAC_MAC_B4_SHIFT;
    reg_val |= (config->mac_addr[3]) << EMAC_MAC_B3_SHIFT;
    reg_val |= (config->mac_addr[2]) << EMAC_MAC_B2_SHIFT;
    putreg32(reg_val, reg_base + EMAC_MAC_ADDR0_OFFSET);
    reg_val = getreg32(reg_base + EMAC_MAC_ADDR1_OFFSET);
    reg_val &= ~(EMAC_MAC_B0_MASK | EMAC_MAC_B1_MASK);
    reg_val |= (config->mac_addr[1]) << EMAC_MAC_B1_SHIFT;
    reg_val |= (config->mac_addr[0]) << EMAC_MAC_B0_SHIFT;
    putreg32(reg_val, reg_base + EMAC_MAC_ADDR1_OFFSET);
}

/**
 * @brief bflb emac deinit
 *
 * @param dev
 *
 */
void bflb_emac_deinit(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t reg_val;

    reg_base = dev->reg_base;

    reg_val = getreg32(reg_base + EMAC_MODE_OFFSET);
    reg_val &= ~(EMAC_TX_EN | EMAC_RX_EN);
    putreg32(reg_val, reg_base + EMAC_MODE_OFFSET);
}

/**
 * @brief bflb emac interrupt enable
 *
 * @param dev
 * @param flag
 * @param enable
 *
 */
void bflb_emac_int_enable(struct bflb_device_s *dev, uint32_t flag, bool enable)
{
    uint32_t reg_base;
    uint32_t reg_val_mask; // reg_val_en;

    reg_base = dev->reg_base;
    reg_val_mask = getreg32(reg_base + EMAC_INT_MASK_OFFSET);
    if (enable) {
        reg_val_mask &= ~(flag);
    } else {
        reg_val_mask |= (flag);
    }
    putreg32(reg_val_mask, reg_base + EMAC_INT_MASK_OFFSET);
};

/**
 * @brief bflb emac interrupt clear
 *
 * @param dev
 * @param flag
 *
 */
void bflb_emac_int_clear(struct bflb_device_s *dev, uint32_t flag)
{
    putreg32(flag, dev->reg_base + EMAC_INT_SOURCE_OFFSET);
}

/**
 * @brief bflb emac get interrupt status
 *
 * @param dev
 * @return uint32_t
 */
uint32_t bflb_emac_get_int_status(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t reg_sts_val, reg_mask_val;

    reg_base = dev->reg_base;
    reg_sts_val = getreg32(reg_base + EMAC_INT_SOURCE_OFFSET);
    reg_mask_val = getreg32(reg_base + EMAC_INT_MASK_OFFSET);

    return (reg_sts_val & (~reg_mask_val));
}

/**
 * @brief emac dma description list init
 *
 * @param reg_base
 * @param handle
 * @param tx_buff
 * @param tx_buff_cnt
 * @param rx_buff
 * @param rx_buff_cnt
 *
 */
static void emac_dma_desc_list_init(uint32_t reg_base, struct bflb_emac_handle_s *handle, uint8_t *tx_buff, uint32_t tx_buff_cnt, uint8_t *rx_buff, uint32_t rx_buff_cnt)
{
    uint32_t i = 0;

    /* Set the Ethernet handler env */
    handle->bd = (struct bflb_emac_bd_desc_s *)(uintptr_t)(reg_base + EMAC_DMA_DESC_OFFSET);
    handle->tx_index_emac = 0;
    handle->tx_index_cpu = 0;
    handle->tx_buff_limit = tx_buff_cnt - 1;
    /* The receive descriptors' address starts right after the last transmit BD. */
    handle->rx_index_emac = tx_buff_cnt;
    handle->rx_index_cpu = tx_buff_cnt;
    handle->rx_buff_limit = tx_buff_cnt + rx_buff_cnt - 1;

    /* Fill each DMARxDesc descriptor with the right values */
    for (i = 0; i < tx_buff_cnt; i++) {
        /* Get the pointer on the ith member of the Tx Desc list */
        handle->bd[i].Buffer = (NULL == tx_buff) ? 0 : (uint32_t)(uintptr_t)(tx_buff + (ETH_MAX_PACKET_SIZE * i));
        handle->bd[i].C_S_L = 0;
    }

    /* For the last TX DMA Descriptor, it should be wrap back */
    handle->bd[handle->tx_buff_limit].C_S_L |= EMAC_BD_TX_WR_MASK;

    for (i = tx_buff_cnt; i < (tx_buff_cnt + rx_buff_cnt); i++) {
        /* Get the pointer on the ith member of the Rx Desc list */
        handle->bd[i].Buffer = (NULL == rx_buff) ? 0 : (uint32_t)(uintptr_t)(rx_buff + (ETH_MAX_PACKET_SIZE * (i - tx_buff_cnt)));
        handle->bd[i].C_S_L = (ETH_MAX_PACKET_SIZE << 16) | EMAC_BD_RX_IRQ_MASK | EMAC_BD_RX_E_MASK;
    }

    /* For the last RX DMA Descriptor, it should be wrap back */
    handle->bd[handle->rx_buff_limit].C_S_L |= EMAC_BD_RX_WR_MASK;

    /* For the TX DMA Descriptor, it will wrap to 0 according to EMAC_TX_BD_NUM*/
    putreg32(tx_buff_cnt, reg_base + EMAC_TX_BD_NUM_OFFSET);
}

/**
 * @brief emac buffer description init
 *
 * @param eth_tx_buff
 * @param tx_buf_count
 * @param eth_rx_buff
 * @param rx_buf_count
 *
 */
void bflb_emac_bd_init(struct bflb_device_s *dev, uint8_t *eth_tx_buff, uint8_t tx_buf_count, uint8_t *eth_rx_buff, uint8_t rx_buf_count)
{
    thiz = &eth_handle;
    uint32_t reg_base;
    reg_base = dev->reg_base;
    /* init the BDs in emac with buffer address */
    emac_dma_desc_list_init(reg_base, thiz, (uint8_t *)eth_tx_buff, tx_buf_count, (uint8_t *)eth_rx_buff, rx_buf_count);
}

/**
 * @brief bflb emac phy register read
 *
 * @param dev
 * @param phy_reg
 * @param phy_reg_val
 * @return int
 *
 */
int bflb_emac_phy_reg_read(struct bflb_device_s *dev, uint16_t phy_reg, uint16_t *phy_reg_val)
{
    uint32_t reg_val;

    /* Set Register Address */
    reg_val = getreg32(dev->reg_base + EMAC_MIIADDRESS_OFFSET);
    reg_val &= ~(EMAC_RGAD_MASK);
    reg_val |= ((uint32_t)phy_reg << EMAC_RGAD_SHIFT);
    putreg32(reg_val, dev->reg_base + EMAC_MIIADDRESS_OFFSET);

    /* Trigger read */
    reg_val = getreg32(dev->reg_base + EMAC_MIICOMMAND_OFFSET);
    reg_val |= (EMAC_RSTAT);
    putreg32(reg_val, dev->reg_base + EMAC_MIICOMMAND_OFFSET);

    __ASM volatile("nop");
    __ASM volatile("nop");
    __ASM volatile("nop");
    __ASM volatile("nop");

    do {
        reg_val = getreg32(dev->reg_base + EMAC_MIISTATUS_OFFSET);
        bflb_mtimer_delay_us(16);
    } while ((reg_val & (EMAC_MIIM_BUSY)) != 0);

    *phy_reg_val = getreg32(dev->reg_base + EMAC_MIIRX_DATA_OFFSET);

    return 0;
}

/**
 * @brief bflb emac phy register write
 *
 * @param dev
 * @param phy_reg
 * @param phy_reg_val
 * @return int
 *
 */
int bflb_emac_phy_reg_write(struct bflb_device_s *dev, uint16_t phy_reg, uint16_t phy_reg_val)
{
    uint32_t reg_val;

    /* Set Register Address */
    reg_val = getreg32(dev->reg_base + EMAC_MIIADDRESS_OFFSET);
    reg_val &= ~(EMAC_RGAD_MASK);
    reg_val |= ((uint32_t)phy_reg << EMAC_RGAD_SHIFT);
    putreg32(reg_val, dev->reg_base + EMAC_MIIADDRESS_OFFSET);

    /* Set Write data */
    putreg32(phy_reg_val, dev->reg_base + EMAC_MIITX_DATA_OFFSET);

    /* Trigger write */
    reg_val = getreg32(dev->reg_base + EMAC_MIICOMMAND_OFFSET);
    reg_val |= (EMAC_WCTRLDATA);
    putreg32(reg_val, dev->reg_base + EMAC_MIICOMMAND_OFFSET);

    __ASM volatile("nop");
    __ASM volatile("nop");
    __ASM volatile("nop");
    __ASM volatile("nop");

    do {
        reg_val = getreg32(dev->reg_base + EMAC_MIISTATUS_OFFSET);
        bflb_mtimer_delay_us(16);
    } while ((reg_val & (EMAC_MIIM_BUSY)) != 0);

    return 0;
}

/**
 * @brief bflb emac feature control
 *
 * @param dev
 * @param cmd
 * @param arg
 * @return int
 *
 */
int bflb_emac_feature_control(struct bflb_device_s *dev, int cmd, size_t arg)
{
    int ret = 0;
    uint32_t reg_val;
    uint32_t reg_base;

    reg_base = dev->reg_base;
    switch (cmd) {
        case EMAC_CMD_NO_PREAMBLE_MODE:
            reg_val = getreg32(reg_base + EMAC_MODE_OFFSET);
            if (arg) {
                reg_val |= EMAC_NOPRE;
            } else {
                reg_val &= ~(EMAC_NOPRE);
            }
            putreg32(reg_val, reg_base + EMAC_MODE_OFFSET);
            break;

        case EMAC_CMD_EN_PROMISCUOUS:
            reg_val = getreg32(reg_base + EMAC_MODE_OFFSET);
            if (arg) {
                reg_val |= EMAC_PRO;
            } else {
                reg_val &= ~(EMAC_PRO);
            }
            putreg32(reg_val, reg_base + EMAC_MODE_OFFSET);
            break;

        case EMAC_CMD_FRAME_GAP_CHECK:
            reg_val = getreg32(reg_base + EMAC_MODE_OFFSET);
            if (arg) {
                reg_val |= EMAC_IFG;
            } else {
                reg_val &= ~(EMAC_IFG);
            }
            putreg32(reg_val, reg_base + EMAC_MODE_OFFSET);
            break;

        case EMAC_CMD_FULL_DUPLEX:
            reg_val = getreg32(reg_base + EMAC_MODE_OFFSET);
            if (arg) {
                reg_val |= EMAC_FULLD;
            } else {
                reg_val &= ~(EMAC_FULLD);
            }
            putreg32(reg_val, reg_base + EMAC_MODE_OFFSET);
            break;

        case EMAC_CMD_EN_TX_CRC_FIELD:
            reg_val = getreg32(reg_base + EMAC_MODE_OFFSET);
            if (arg) {
                reg_val |= EMAC_CRCEN;
            } else {
                reg_val &= ~(EMAC_CRCEN);
            }
            putreg32(reg_val, reg_base + EMAC_MODE_OFFSET);
            break;

        case EMAC_CMD_RECV_HUGE_FRAMES:
            reg_val = getreg32(reg_base + EMAC_MODE_OFFSET);
            if (arg) {
                reg_val |= EMAC_HUGEN;
            } else {
                reg_val &= ~(EMAC_HUGEN);
            }
            putreg32(reg_val, reg_base + EMAC_MODE_OFFSET);
            break;

        case EMAC_CMD_EN_AUTO_PADDING:
            reg_val = getreg32(reg_base + EMAC_MODE_OFFSET);
            if (arg) {
                reg_val |= EMAC_PAD;
            } else {
                reg_val &= ~(EMAC_PAD);
            }
            putreg32(reg_val, reg_base + EMAC_MODE_OFFSET);
            break;

        case EMAC_CMD_RECV_SMALL_FRAME:
            reg_val = getreg32(reg_base + EMAC_MODE_OFFSET);
            if (arg) {
                reg_val |= EMAC_RECSMALL;
            } else {
                reg_val &= ~(EMAC_RECSMALL);
            }
            putreg32(reg_val, reg_base + EMAC_MODE_OFFSET);
            break;

        case EMAC_CMD_SET_PHY_ADDRESS:
            reg_val = getreg32(reg_base + EMAC_MIIADDRESS_OFFSET);
            reg_val &= ~(EMAC_FIAD_MASK);
            reg_val |= (uint32_t)(arg << EMAC_FIAD_SHIFT);
            putreg32(reg_val, reg_base + EMAC_MIIADDRESS_OFFSET);
            break;

        case EMAC_CMD_SET_MAXRET:
            reg_val = getreg32(reg_base + EMAC_COLLCONFIG_OFFSET);
            reg_val &= ~(EMAC_MAXFL_MASK);
            reg_val |= (arg) << EMAC_MAXFL_SHIFT;
            putreg32(reg_val, reg_base + EMAC_COLLCONFIG_OFFSET);
            break;

        case EMAC_CMD_SET_COLLVALID:
            reg_val = getreg32(reg_base + EMAC_COLLCONFIG_OFFSET);
            reg_val &= ~(EMAC_COLLVALID_MASK);
            reg_val |= (arg) << EMAC_COLLVALID_SHIFT;
            putreg32(reg_val, reg_base + EMAC_COLLCONFIG_OFFSET);
            break;

        case EMAC_CMD_SET_PACKET_GAP:
            reg_val = getreg32(reg_base + EMAC_IPGT_OFFSET);
            reg_val &= ~(EMAC_IPGT_MASK);
            reg_val |= (arg) << EMAC_IPGT_SHIFT;
            putreg32(reg_val, reg_base + EMAC_IPGT_OFFSET);
            break;

        default:
            ret = -EPERM;
            break;
    }
    return ret;
}

/**
 * @brief bflb emac stop
 *
 * @param dev
 *
 */
void bflb_emac_stop(struct bflb_device_s *dev)
{
    /* disable emac */
    uint32_t reg_val;

    reg_val = getreg32(dev->reg_base + EMAC_MODE_OFFSET);
    reg_val &= ~(EMAC_TX_EN | EMAC_RX_EN);
    putreg32(reg_val, dev->reg_base + EMAC_MODE_OFFSET);
}

/**
 * @brief bflb emac start
 *
 * @param dev
 *
 */
void bflb_emac_start(struct bflb_device_s *dev)
{
    /* enable emac */
    uint32_t reg_val;

    reg_val = getreg32(dev->reg_base + EMAC_MODE_OFFSET);
    reg_val |= (EMAC_TX_EN | EMAC_RX_EN);
    putreg32(reg_val, dev->reg_base + EMAC_MODE_OFFSET);
}

/**
 * @brief bflb emac start tx
 *
 * @param dev
 *
 */
void bflb_emac_start_tx(struct bflb_device_s *dev)
{
    uint32_t reg_val;

    reg_val = getreg32(dev->reg_base + EMAC_MODE_OFFSET);
    reg_val |= (EMAC_TX_EN);
    putreg32(reg_val, dev->reg_base + EMAC_MODE_OFFSET);
}

/**
 * @brief bflb emac stop tx
 *
 * @param dev
 *
 */
void bflb_emac_stop_tx(struct bflb_device_s *dev)
{
    uint32_t reg_val;

    reg_val = getreg32(dev->reg_base + EMAC_MODE_OFFSET);
    reg_val &= ~(EMAC_TX_EN);
    putreg32(reg_val, dev->reg_base + EMAC_MODE_OFFSET);
}

/**
 * @brief bflb emac start rx
 *
 * @param dev
 *
 */
void bflb_emac_start_rx(struct bflb_device_s *dev)
{
    uint32_t reg_val;

    reg_val = getreg32(dev->reg_base + EMAC_MODE_OFFSET);
    reg_val |= (EMAC_RX_EN);
    putreg32(reg_val, dev->reg_base + EMAC_MODE_OFFSET);
}

/**
 * @brief bflb emac stop rx
 *
 * @param dev
 *
 */
void bflb_emac_stop_rx(struct bflb_device_s *dev)
{
    uint32_t reg_val;

    reg_val = getreg32(dev->reg_base + EMAC_MODE_OFFSET);
    reg_val &= ~(EMAC_RX_EN);
    putreg32(reg_val, dev->reg_base + EMAC_MODE_OFFSET);
}
