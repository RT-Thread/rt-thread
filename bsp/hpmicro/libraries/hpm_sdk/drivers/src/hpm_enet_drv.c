/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*---------------------------------------------------------------------
 * Includes
 *---------------------------------------------------------------------
 */
#include "hpm_enet_drv.h"
#include "hpm_enet_soc_drv.h"

/*---------------------------------------------------------------------
 * Internal API
 *---------------------------------------------------------------------
 */
static void enet_mode_init(ENET_Type *ptr, uint32_t intr)
{
    /* receive and transmit store and forward */
    ptr->DMA_OP_MODE |= ENET_DMA_OP_MODE_RSF_MASK | ENET_DMA_OP_MODE_TSF_MASK;

    /* enalbe hardware flow control */
    ptr->DMA_OP_MODE |= ENET_DMA_OP_MODE_EFC_MASK;

    /* enable error frame and undersized good frame forwarding */
    ptr->DMA_OP_MODE |= ENET_DMA_OP_MODE_FEF_MASK;

    /* disable osf mode */
    ptr->DMA_OP_MODE &= ~ENET_DMA_OP_MODE_OSF_MASK;

    ptr->DMA_INTR_EN |= intr;

    while (ENET_DMA_BUS_STATUS_AXIRDSTS_GET(ptr->DMA_BUS_STATUS) || ENET_DMA_BUS_STATUS_AXWHSTS_GET(ptr->DMA_BUS_STATUS)) {
    }

    /* start the receive and transmit dma */
    ptr->DMA_OP_MODE |= ENET_DMA_OP_MODE_ST_MASK | ENET_DMA_OP_MODE_SR_MASK;
}

static int enet_dma_init(ENET_Type *ptr, enet_desc_t *desc, uint32_t intr, uint8_t pbl)
{
    /* generate software reset */
    ptr->DMA_BUS_MODE |= ENET_DMA_BUS_MODE_SWR_MASK;

    /* wait for the completion of reset process */
    while (ENET_DMA_BUS_MODE_SWR_GET(ptr->DMA_BUS_MODE)) {
    }

    /* initialize bus mode register */
    ptr->DMA_BUS_MODE |= ENET_DMA_BUS_MODE_AAL_MASK;

    ptr->DMA_BUS_MODE &= ~ENET_DMA_BUS_MODE_FB_MASK;

    /* enable pblx8 mode */
    ptr->DMA_BUS_MODE |= ENET_DMA_BUS_MODE_PBLX8_MASK;

    /* set programmable burst length */
    ptr->DMA_BUS_MODE &= ~ENET_DMA_BUS_MODE_PBL_MASK;
    ptr->DMA_BUS_MODE |= ENET_DMA_BUS_MODE_PBL_SET(pbl);

    /* disable separate pbl */
    ptr->DMA_BUS_MODE &= ~ENET_DMA_BUS_MODE_USP_MASK;

    /* descriptor length */
#if ENET_SOC_ALT_EHD_DES_LEN == ENET_SOC_ALT_EHD_DES_MIN_LEN
    ptr->DMA_BUS_MODE &= ~ENET_DMA_BUS_MODE_ATDS_MASK;
#elif ENET_SOC_ALT_EHD_DES_LEN == ENET_SOC_ALT_EHD_DES_MAX_LEN
    ptr->DMA_BUS_MODE |= ENET_DMA_BUS_MODE_ATDS_MASK;
    #endif

    /* set the maximum enabled burst length */
    if (ENET_DMA_BUS_MODE_FB_GET(ptr->DMA_BUS_MODE) == 0) {
        ptr->DMA_AXI_MODE |= ENET_DMA_AXI_MODE_BLEN4_MASK | ENET_DMA_AXI_MODE_BLEN8_MASK | ENET_DMA_AXI_MODE_BLEN16_MASK;
    } else {
        /* TODO: set BLENX_MASK */
    }

    /* initialize Tx descriptors list: chain mode */
    enet_dma_tx_desc_chain_init(ptr, desc);

    /* initialize Rx descriptors list: Chain Mode  */
    enet_dma_rx_desc_chain_init(ptr, desc);

    enet_mode_init(ptr, intr);

    enet_dma_flush(ptr);

    return true;
}

static int enet_mac_init(ENET_Type *ptr, enet_mac_config_t *config, enet_inf_type_t inf_type)
{
    for (int i = 0; i < config->valid_max_count; i++) {
        if (i == 0) {
            ptr->MAC_ADDR_0_HIGH &= ~ENET_MAC_ADDR_0_HIGH_ADDRHI_MASK;
            ptr->MAC_ADDR_0_LOW  &= ~ENET_MAC_ADDR_0_LOW_ADDRLO_MASK;
            ptr->MAC_ADDR_0_HIGH |= ENET_MAC_ADDR_0_HIGH_ADDRHI_SET(config->mac_addr_high[i]);
            ptr->MAC_ADDR_0_LOW  |= ENET_MAC_ADDR_0_LOW_ADDRLO_SET(config->mac_addr_low[i]);
        } else {
            ptr->MAC_ADDR[i-1].HIGH &= ~ENET_MAC_ADDR_HIGH_ADDRHI_MASK;
            ptr->MAC_ADDR[i-1].LOW  &= ~ENET_MAC_ADDR_LOW_ADDRLO_MASK;
            ptr->MAC_ADDR[i-1].HIGH |= ENET_MAC_ADDR_HIGH_AE_MASK | ENET_MAC_ADDR_HIGH_ADDRHI_SET(config->mac_addr_high[i]);
            ptr->MAC_ADDR[i-1].LOW  |= ENET_MAC_ADDR_LOW_ADDRLO_SET(config->mac_addr_low[i]);
        }
    }

    /* set the appropriate filters for the incoming frames */
    ptr->MACFF |= ENET_MACFF_RA_SET(1);      /* receive all */

    /* replace the content of the mac address 0 in the sa field of all transmitted frames */
    ptr->MACCFG &= ~ENET_MACCFG_SARC_MASK;
    ptr->MACCFG |= ENET_MACCFG_SARC_SET(config->sarc);

    ptr->MACCFG |= ENET_MACCFG_PS_MASK | ENET_MACCFG_FES_MASK;

    if (inf_type == enet_inf_rgmii) {
        ptr->MACCFG &= ~ENET_MACCFG_PS_MASK;
    } else if (inf_type == enet_inf_rmii) {
        ptr->MACCFG |= ENET_MACCFG_PS_MASK | ENET_MACCFG_FES_MASK;
    }
#if defined(HPM_IP_FEATURE_ENET_HAS_MII_MODE) && HPM_IP_FEATURE_ENET_HAS_MII_MODE
    else if (inf_type == enet_inf_mii) {
        ptr->MACCFG |= ENET_MACCFG_PS_MASK | ENET_MACCFG_FES_MASK;
    }
#endif
    else {
        return status_invalid_argument;
    }

    ptr->MACCFG |= ENET_MACCFG_DM_MASK;

    if (ENET_MACCFG_DM_GET(ptr->MACCFG) == 0) {
        ptr->MACCFG |= ENET_MACCFG_IFG_SET(4);
    } else {
        ptr->MACCFG |= ENET_MACCFG_IFG_SET(2);
    }


    /* enable transmitter enable and receiver */
    ptr->MACCFG |= ENET_MACCFG_TE_MASK | ENET_MACCFG_RE_MASK;

    return true;
}

static void enet_mask_interrupt_event(ENET_Type *ptr, uint32_t mask)
{
    /* mask the specified interrupts */
    ptr->INTR_MASK |= mask;
}

/*---------------------------------------------------------------------
 * Driver API
 *---------------------------------------------------------------------
 */
uint32_t enet_get_interrupt_status(ENET_Type *ptr)
{
    return ptr->INTR_STATUS;
}

void enet_mask_mmc_rx_interrupt_event(ENET_Type *ptr, uint32_t mask)
{
    ptr->MMC_INTR_MASK_RX |= mask;
}

uint32_t enet_get_mmc_rx_interrupt_status(ENET_Type *ptr)
{
    return ptr->MMC_INTR_RX;
}

void enet_mask_mmc_tx_interrupt_event(ENET_Type *ptr, uint32_t mask)
{
    ptr->MMC_INTR_MASK_TX |= mask;
}

uint32_t enet_get_mmc_tx_interrupt_status(ENET_Type *ptr)
{
    return ptr->MMC_INTR_TX;
}

void enet_dma_flush(ENET_Type *ptr)
{
    /* flush DMA transmit FIFO */
    ptr->DMA_OP_MODE |= ENET_DMA_OP_MODE_FTF_MASK;
    while (ENET_DMA_OP_MODE_FTF_GET(ptr->DMA_OP_MODE)) {

    }
}

void enet_write_phy(ENET_Type *ptr, uint32_t phy_addr, uint32_t addr, uint32_t data)
{
    /* set data to be written */
    ptr->GMII_DATA = ENET_GMII_DATA_GD_SET(data);

    /* set phy address , register address, write operation and busy flag */
    ptr->GMII_ADDR = ENET_GMII_ADDR_PA_SET(phy_addr)
                   | ENET_GMII_ADDR_GR_SET(addr)
                   | ENET_GMII_ADDR_CR_SET(enet_csr_150m_to_250m_mdc_csr_div_102)
                   | ENET_GMII_ADDR_GW_SET(enet_phy_op_write)
                   | ENET_GMII_ADDR_GB_SET(enet_gmii_busy);

    /* wait until the write operation is completed */
    while (ENET_GMII_ADDR_GB_GET(ptr->GMII_ADDR)) {
    }
}

uint16_t enet_read_phy(ENET_Type *ptr, uint32_t phy_addr, uint32_t addr)
{
    /* set phy address, register address, read operation and busy flag */
    ptr->GMII_ADDR = ENET_GMII_ADDR_PA_SET(phy_addr)
                   | ENET_GMII_ADDR_GR_SET(addr)
                   | ENET_GMII_ADDR_CR_SET(enet_csr_150m_to_250m_mdc_csr_div_102)
                   | ENET_GMII_ADDR_GW_SET(enet_phy_op_read)
                   | ENET_GMII_ADDR_GB_SET(enet_gmii_busy);

    /* wait until the write operation is completed */
    while (ENET_GMII_ADDR_GB_GET(ptr->GMII_ADDR)) {
    }

    /* read and return data */
    return (uint16_t)ENET_GMII_DATA_GD_GET(ptr->GMII_DATA);
}

void enet_set_line_speed(ENET_Type *ptr, enet_line_speed_t speed)
{
    ptr->MACCFG &= ~(ENET_MACCFG_PS_MASK | ENET_MACCFG_FES_MASK);
    ptr->MACCFG |= speed << ENET_MACCFG_FES_SHIFT;
}

void enet_set_duplex_mode(ENET_Type *ptr, enet_duplex_mode_t mode)
{
    ptr->MACCFG &= ~ENET_MACCFG_DM_MASK;
    ptr->MACCFG |= ENET_MACCFG_DM_SET(mode);
}

hpm_stat_t enet_controller_init(ENET_Type *ptr, enet_inf_type_t inf_type, enet_desc_t *desc, enet_mac_config_t *config, enet_int_config_t *int_config)
{
    /* select an interface */
    enet_intf_selection(ptr, inf_type);

    /* initialize DMA */
    enet_dma_init(ptr, desc, int_config->int_enable, config->dma_pbl);

    /* initialize MAC */
    enet_mac_init(ptr, config, inf_type);

    /* mask the specified interrupts */
    enet_mask_interrupt_event(ptr, int_config->int_mask);

    /* mask the mmc rx interrupts */
    enet_mask_mmc_rx_interrupt_event(ptr, int_config->mmc_intr_mask_rx);

    /* mask the mmc tx interrupts */
    enet_mask_mmc_tx_interrupt_event(ptr, int_config->mmc_intr_mask_tx);

    return status_success;
}

/*****************************************************************************
 *                           DMA API
 ****************************************************************************/
void enet_rx_resume(ENET_Type *ptr)
{
    if (ENET_DMA_STATUS_RU_GET(ptr->DMA_STATUS)) {
        ptr->DMA_STATUS = ENET_DMA_STATUS_RU_MASK;
        ptr->DMA_RX_POLL_DEMAND = 1;
    }
}

uint32_t enet_check_received_frame(enet_rx_desc_t **parent_rx_desc_list_cur, enet_rx_frame_info_t *rx_frame_info)
{
    enet_rx_desc_t *rx_desc_list_cur = *parent_rx_desc_list_cur;

    /* check if the last segment */
    if ((rx_desc_list_cur->rdes0_bm.own == 0) &&
        (rx_desc_list_cur->rdes0_bm.ls == 1)) {
        rx_frame_info->seg_count++;
        if (rx_frame_info->seg_count == 1) {
            rx_frame_info->fs_rx_desc = rx_desc_list_cur;
        }
        rx_frame_info->ls_rx_desc = rx_desc_list_cur;
        return 1;
    }
    /* check if the first segment */
    else if ((rx_desc_list_cur->rdes0_bm.own == 0) &&
             (rx_desc_list_cur->rdes0_bm.fs == 1) &&
             (rx_desc_list_cur->rdes0_bm.ls == 0)) {
        rx_frame_info->fs_rx_desc = rx_desc_list_cur;
        rx_frame_info->ls_rx_desc = NULL;
        rx_frame_info->seg_count = 1;
        rx_desc_list_cur = (enet_rx_desc_t *)rx_desc_list_cur->rdes3_bm.next_desc;
        *parent_rx_desc_list_cur = rx_desc_list_cur;
    }

    /* check if intermediate segments */
    else if ((rx_desc_list_cur->rdes0_bm.own == 0) &&
             (rx_desc_list_cur->rdes0_bm.fs == 0) &&
             (rx_desc_list_cur->rdes0_bm.ls == 0)) {
        rx_frame_info->seg_count++;
        rx_desc_list_cur = (enet_rx_desc_t *)(rx_desc_list_cur->rdes3_bm.next_desc);
        *parent_rx_desc_list_cur = rx_desc_list_cur;
    }

    return 0;
}

enet_frame_t enet_get_received_frame(enet_rx_desc_t **parent_rx_desc_list_cur, enet_rx_frame_info_t *rx_frame_info)
{
    uint32_t frame_length = 0;
    enet_frame_t frame = {0, 0, 0};
    enet_rx_desc_t *rx_desc_list_cur = *parent_rx_desc_list_cur;

    /* get the frame length of the received packet: substruct 4 bytes of the CRC */
    frame_length = rx_desc_list_cur->rdes0_bm.fl - 4;
    frame.length = frame_length;

    /* get the address of the first frame descriptor and the buffer start address */
    frame.rx_desc = rx_frame_info->fs_rx_desc;
    frame.buffer = rx_frame_info->fs_rx_desc->rdes2_bm.buffer1;

    /* update the Ethernet dma global Rx descriptor with next Rx descriptor */
    /* chained mode */
    /* selects the next dma Rx descriptor list for next buffer to read */
    rx_desc_list_cur = (enet_rx_desc_t *)(rx_desc_list_cur->rdes3_bm.next_desc);
    *parent_rx_desc_list_cur = rx_desc_list_cur;

    return frame;
}

enet_frame_t enet_get_received_frame_interrupt(enet_rx_desc_t **parent_rx_desc_list_cur, enet_rx_frame_info_t *rx_frame_info, uint32_t rx_desc_count)
{
    enet_frame_t frame = {0, 0, 0};
    uint32_t desc_scan_counter = 0;
    enet_rx_desc_t *rx_desc_list_cur = *parent_rx_desc_list_cur;

    /* scan descriptors owned by CPU */
    while ((rx_desc_list_cur->rdes0_bm.own == 0) &&
        (desc_scan_counter < rx_desc_count)) {

        desc_scan_counter++;

        /* check if first segment in frame */
        if ((rx_desc_list_cur->rdes0_bm.fs == 1) &&
            (rx_desc_list_cur->rdes0_bm.ls == 0)) {
            rx_frame_info->fs_rx_desc = rx_desc_list_cur;
            rx_frame_info->seg_count = 1;
            rx_desc_list_cur = (enet_rx_desc_t *)(rx_desc_list_cur->rdes3_bm.next_desc);
            *parent_rx_desc_list_cur = rx_desc_list_cur;
        }

        /* check if intermediate segment */
        else if ((rx_desc_list_cur->rdes0_bm.ls == 0) &&
                 (rx_desc_list_cur->rdes0_bm.fs == 0)) {
            rx_frame_info->seg_count++;
            rx_desc_list_cur = (enet_rx_desc_t *)(rx_desc_list_cur->rdes3_bm.next_desc);
            *parent_rx_desc_list_cur = rx_desc_list_cur;
        }

        /* should be last segment */
        else {
            /* last segment */
            rx_frame_info->ls_rx_desc = rx_desc_list_cur;

            rx_frame_info->seg_count++;

            /* first segment is last segment */
            if (rx_frame_info->seg_count == 1) {
                rx_frame_info->fs_rx_desc = rx_desc_list_cur;
            }

            /* get the frame length of the received packet: substruct 4 bytes of the crc */
            frame.length = rx_desc_list_cur->rdes0_bm.fl - 4;

            /* get the address of the buffer start address */
            /* check if more than one segment in the frame */
            if (rx_frame_info->seg_count > 1) {
                frame.buffer = rx_frame_info->fs_rx_desc->rdes2_bm.buffer1;
            } else {
                frame.buffer = rx_desc_list_cur->rdes2_bm.buffer1;
            }

            frame.rx_desc = rx_frame_info->fs_rx_desc;

            rx_desc_list_cur = (enet_rx_desc_t *)(rx_desc_list_cur->rdes3_bm.next_desc);
            *parent_rx_desc_list_cur = rx_desc_list_cur;

            return frame;
        }
    }

    return frame;
}

void enet_get_default_tx_control_config(ENET_Type *ptr, enet_tx_control_config_t *config)
{
    (void) ptr;
    config->enable_ioc  = false;
    config->disable_crc = true;
    config->disable_pad = false;
    config->enable_ttse = false;
    config->enable_crcr = true;
    config->cic         = enet_cic_ip_pseudoheader;
    config->vlic        = enet_vlic_disable;
    config->saic        = enet_saic_disable;
}

void enet_get_default_interrupt_config(ENET_Type *ptr, enet_int_config_t *config)
{
    (void) ptr;

    config->int_enable = enet_normal_int_sum_en    /* Enable normal interrupt summary */
                       | enet_receive_int_en;      /* Enable receive interrupt */

    config->int_mask = enet_rgsmii_int_mask        /* Disable RGSMII interrupt */
                     | enet_lpi_int_mask;          /* Disable LPI interrupt */

    config->mmc_intr_mask_rx = 0x03ffffff;         /* Disable all mmc rx interrupt events */
    config->mmc_intr_mask_tx = 0x03ffffff;         /* Disable all mmc tx interrupt events */
}

uint32_t enet_prepare_tx_desc_with_ts_record(ENET_Type *ptr,
                                             enet_tx_desc_t **parent_tx_desc_list_cur,
                                             enet_tx_control_config_t *config,
                                             uint16_t frame_length, uint16_t tx_buff_size,
                                             enet_ptp_ts_system_t *timestamp)
{
    uint32_t buf_count = 0, size = 0, i = 0;
    uint32_t retry_cnt = ENET_RETRY_CNT;
    enet_tx_desc_t *dma_tx_desc;
    enet_tx_desc_t *tx_desc_list_cur = *parent_tx_desc_list_cur;

    if (tx_buff_size == 0) {
        return ENET_ERROR;
    }
    /* check if the descriptor is owned by the Ethernet DMA (when set) or CPU (when reset) */

    dma_tx_desc = tx_desc_list_cur;

    if (frame_length > tx_buff_size) {
        buf_count = frame_length / tx_buff_size;
        if (frame_length % tx_buff_size) {
            buf_count++;
        }
    } else {
        buf_count = 1;
    }

    if (buf_count == 1) {
        /*set the last and the first segment */
        dma_tx_desc->tdes0_bm.own  = 0;
        dma_tx_desc->tdes0_bm.fs   = 1;
        dma_tx_desc->tdes0_bm.ls   = 1;
        dma_tx_desc->tdes0_bm.ic   = config->enable_ioc;
        dma_tx_desc->tdes0_bm.dc   = config->disable_crc;
        dma_tx_desc->tdes0_bm.dp   = config->disable_pad;
        dma_tx_desc->tdes0_bm.crcr = config->enable_crcr;
        dma_tx_desc->tdes0_bm.cic  = config->cic;
        dma_tx_desc->tdes0_bm.vlic = config->vlic;
        dma_tx_desc->tdes0_bm.ttse = config->enable_ttse;
        dma_tx_desc->tdes1_bm.saic = config->saic;
        /* set the frame size */
        dma_tx_desc->tdes1_bm.tbs1 = (frame_length & ENET_DMATxDesc_TBS1);
        /* set own bit of the Tx descriptor status: gives the buffer back to Ethernet DMA */
        dma_tx_desc->tdes0 |= 1 << 31;
        ptr->DMA_TX_POLL_DEMAND = 1;

        if (dma_tx_desc->tdes0_bm.ttse == true) {
            do {

            } while (dma_tx_desc->tdes0_bm.own == 1 && retry_cnt-- > 0);

            if (retry_cnt == 0) {
                return ENET_ERROR;
            }

            timestamp->sec  = dma_tx_desc->tdes7_bm.ttsh;
            timestamp->nsec = dma_tx_desc->tdes6_bm.ttsl;
        }

        dma_tx_desc = (enet_tx_desc_t *)(dma_tx_desc->tdes3_bm.next_desc);
    } else {
        for (i = 0; i < buf_count; i++) {
            /* get the next available tx descriptor */
            dma_tx_desc = (enet_tx_desc_t *)(dma_tx_desc->tdes3_bm.next_desc);

            /* clear first and last segment bits */
            dma_tx_desc->tdes0_bm.fs = 0;
            dma_tx_desc->tdes0_bm.ls = 0;

            if (i == 0) {
                /* setting the first segment bit */
                dma_tx_desc->tdes0_bm.fs = 1;
                dma_tx_desc->tdes0_bm.dc   = config->disable_crc;
                dma_tx_desc->tdes0_bm.dp   = config->disable_pad;
                dma_tx_desc->tdes0_bm.crcr = config->enable_crcr;
                dma_tx_desc->tdes0_bm.cic  = config->cic;
                dma_tx_desc->tdes0_bm.vlic = config->vlic;
                dma_tx_desc->tdes0_bm.ttse = config->enable_ttse;
                dma_tx_desc->tdes1_bm.saic = config->saic;

                if (dma_tx_desc->tdes0_bm.ttse == true) {
                    do {

                    } while (dma_tx_desc->tdes0_bm.own == 1 && retry_cnt-- > 0);

                    if (retry_cnt == 0) {
                        return ENET_ERROR;
                    }

                    timestamp->sec  = dma_tx_desc->tdes7_bm.ttsh;
                    timestamp->nsec = dma_tx_desc->tdes6_bm.ttsl;
                }
            }

            /* set the buffer 1 size */
            dma_tx_desc->tdes1_bm.tbs1 = (tx_buff_size & ENET_DMATxDesc_TBS1);

            if (i == (buf_count - 1)) {
                /* set the last segment bit */
                dma_tx_desc->tdes0_bm.ls = 1;
                dma_tx_desc->tdes0_bm.ic   = config->enable_ioc;
                size = frame_length - (buf_count - 1) * tx_buff_size;
                dma_tx_desc->tdes1_bm.tbs1 = (size & ENET_DMATxDesc_TBS1);

                /* set own bit of the Tx descriptor status: gives the buffer back to Ethernet DMA */
                dma_tx_desc->tdes0 |= 1 << 31;
                ptr->DMA_TX_POLL_DEMAND = 1;
            }
        }
    }

    tx_desc_list_cur = dma_tx_desc;
    *parent_tx_desc_list_cur = tx_desc_list_cur;

    return ENET_SUCCESS;
}

uint32_t enet_prepare_tx_desc(ENET_Type *ptr, enet_tx_desc_t **parent_tx_desc_list_cur, enet_tx_control_config_t *config, uint16_t frame_length, uint16_t tx_buff_size)
{
    uint32_t buf_count = 0, size = 0, i = 0;
    enet_tx_desc_t *dma_tx_desc;
    enet_tx_desc_t *tx_desc_list_cur = *parent_tx_desc_list_cur;

    if (tx_buff_size == 0) {
        return ENET_ERROR;
    }
    /* check if the descriptor is owned by the Ethernet DMA (when set) or CPU (when reset) */
    dma_tx_desc = tx_desc_list_cur;
    if (frame_length > tx_buff_size) {
        buf_count = frame_length / tx_buff_size;
        if (frame_length % tx_buff_size) {
            buf_count++;
        }
    } else {
        buf_count = 1;
    }

    if (buf_count == 1) {
        /*set the last and the first segment */
        dma_tx_desc->tdes0_bm.own  = 0;
        dma_tx_desc->tdes0_bm.fs   = 1;
        dma_tx_desc->tdes0_bm.ls   = 1;
        dma_tx_desc->tdes0_bm.ic   = config->enable_ioc;
        dma_tx_desc->tdes0_bm.dc   = config->disable_crc;
        dma_tx_desc->tdes0_bm.dp   = config->disable_pad;
        dma_tx_desc->tdes0_bm.crcr = config->enable_crcr;
        dma_tx_desc->tdes0_bm.cic  = config->cic;
        dma_tx_desc->tdes0_bm.vlic = config->vlic;
        dma_tx_desc->tdes1_bm.saic = config->saic;
        /* set the frame size */
        dma_tx_desc->tdes1_bm.tbs1 = (frame_length & ENET_DMATxDesc_TBS1);
        /* set own bit of the Tx descriptor status: gives the buffer back to Ethernet DMA */
        dma_tx_desc->tdes0 |= 1 << 31;
        ptr->DMA_TX_POLL_DEMAND = 1;

        dma_tx_desc = (enet_tx_desc_t *)(dma_tx_desc->tdes3_bm.next_desc);
    } else {
        for (i = 0; i < buf_count; i++) {
            /* clear first and last segment bits */
            dma_tx_desc->tdes0_bm.fs = 0;
            dma_tx_desc->tdes0_bm.ls = 0;

            if (i == 0) {
                /* setting the first segment bit */
                dma_tx_desc->tdes0_bm.fs = 1;
                dma_tx_desc->tdes0_bm.dc   = config->disable_crc;
                dma_tx_desc->tdes0_bm.dp   = config->disable_pad;
                dma_tx_desc->tdes0_bm.crcr = config->enable_crcr;
                dma_tx_desc->tdes0_bm.cic  = config->cic;
                dma_tx_desc->tdes0_bm.vlic = config->vlic;
                dma_tx_desc->tdes1_bm.saic = config->saic;
            }

            /* set the buffer 1 size */
            dma_tx_desc->tdes1_bm.tbs1 = (tx_buff_size & ENET_DMATxDesc_TBS1);

            if (i == (buf_count - 1)) {
                /* set the last segment bit */
                dma_tx_desc->tdes0_bm.ls = 1;
                dma_tx_desc->tdes0_bm.ic   = config->enable_ioc;
                size = frame_length - (buf_count - 1) * tx_buff_size;
                dma_tx_desc->tdes1_bm.tbs1 = (size & ENET_DMATxDesc_TBS1);

                /* set own bit of the Tx descriptor status: gives the buffer back to Ethernet DMA */
                dma_tx_desc->tdes0 |= 1 << 31;
                ptr->DMA_TX_POLL_DEMAND = 1;
            }

            dma_tx_desc = (enet_tx_desc_t *)(dma_tx_desc->tdes3_bm.next_desc);
        }
    }

    tx_desc_list_cur = dma_tx_desc;
    *parent_tx_desc_list_cur = tx_desc_list_cur;

    return ENET_SUCCESS;
}

uint32_t enet_prepare_transmission_descriptors(ENET_Type *ptr, enet_tx_desc_t **parent_tx_desc_list_cur, uint16_t frame_length, uint16_t tx_buff_size)
{
    uint32_t buf_count = 0, size = 0, i = 0;
    enet_tx_desc_t *dma_tx_desc;
    enet_tx_desc_t  *tx_desc_list_cur = *parent_tx_desc_list_cur;

    if (tx_buff_size == 0) {
        return ENET_ERROR;
    }
    /* check if the descriptor is owned by the Ethernet DMA (when set) or CPU (when reset) */
    dma_tx_desc = tx_desc_list_cur;
    if (frame_length > tx_buff_size) {
        buf_count = frame_length / tx_buff_size;
        if (frame_length % tx_buff_size) {
            buf_count++;
        }
    } else {
        buf_count = 1;
    }

    if (buf_count == 1) {
        /*set the last and the first segment */
        dma_tx_desc->tdes0_bm.own = 0;
        dma_tx_desc->tdes0_bm.ic = 0;
        dma_tx_desc->tdes0_bm.fs = 1;
        dma_tx_desc->tdes0_bm.ls = 1;
        dma_tx_desc->tdes0_bm.dc = 1;
        dma_tx_desc->tdes0_bm.dp = 0;
        dma_tx_desc->tdes0_bm.crcr = 1;
        dma_tx_desc->tdes0_bm.cic = 3;
        dma_tx_desc->tdes1_bm.saic = 2;

        /* set the frame size */
        dma_tx_desc->tdes1_bm.tbs1 = (frame_length & ENET_DMATxDesc_TBS1);
        /* set own bit of the Tx descriptor status: gives the buffer back to Ethernet DMA */
        dma_tx_desc->tdes0 |= 1 << 31;
        ptr->DMA_TX_POLL_DEMAND = 1;

        dma_tx_desc = (enet_tx_desc_t *)(dma_tx_desc->tdes3_bm.next_desc);
    } else {
        for (i = 0; i < buf_count; i++) {
            /* clear first and last segment bits */
            dma_tx_desc->tdes0_bm.fs = 0;
            dma_tx_desc->tdes0_bm.ls = 0;

            if (i == 0) {
                /* setting the first segment bit */
                dma_tx_desc->tdes0_bm.fs = 1;
            }

            /* set the buffer 1 size */
            dma_tx_desc->tdes1_bm.tbs1 = (tx_buff_size & ENET_DMATxDesc_TBS1);

            if (i == (buf_count - 1)) {
                /* set the last segment bit */
                dma_tx_desc->tdes0_bm.ls = 1;
                size = frame_length - (buf_count - 1) * tx_buff_size;
                dma_tx_desc->tdes1_bm.tbs1 = (size & ENET_DMATxDesc_TBS1);

                /* set own bit of the Tx descriptor status: gives the buffer back to Ethernet DMA */
                dma_tx_desc->tdes0 |= 1 << 31;
                ptr->DMA_TX_POLL_DEMAND = 1;
            }

            dma_tx_desc = (enet_tx_desc_t *)(dma_tx_desc->tdes3_bm.next_desc);
        }
    }

    tx_desc_list_cur = dma_tx_desc;
    *parent_tx_desc_list_cur = tx_desc_list_cur;

    return ENET_SUCCESS;
}

void enet_dma_tx_desc_chain_init(ENET_Type *ptr, enet_desc_t *desc)
{
    uint32_t i = 0;
    enet_tx_desc_t *dma_tx_desc;

    /* set the tx_desc_list_cur pointer with the first one of the dma_tx_desc_tab list */
    desc->tx_desc_list_cur = desc->tx_desc_list_head;

    /* fill each dma_tx_desc descriptor with the right values */
    for (i = 0; i < desc->tx_buff_cfg.count; i++) {

        /* get the pointer on the ith member of the Tx desc list */
        dma_tx_desc = desc->tx_desc_list_head + i;

        /* set second address chained bit */
        dma_tx_desc->tdes0_bm.tch = 1;

        /* set buffer 1 address pointer */
        dma_tx_desc->tdes2_bm.buffer1 = (uint32_t)(&((uint8_t *)desc->tx_buff_cfg.buffer)[i * desc->tx_buff_cfg.size]);

        /* link all Tx descriptors */
        if (i < desc->tx_buff_cfg.count - 1) {
            /* set next descriptor address register with the next descriptor base address */
            dma_tx_desc->tdes3_bm.next_desc = (uint32_t)(desc->tx_desc_list_head + i + 1);
        } else {
            /* for last descriptor, set next descriptor address register equal to the first descriptor base address */
            dma_tx_desc->tdes3_bm.next_desc = (uint32_t)desc->tx_desc_list_head;
        }
    }

    /* set transmit descriptor list address register */
    ptr->DMA_TX_DESC_LIST_ADDR = (uint32_t)desc->tx_desc_list_head;
}

void enet_dma_rx_desc_chain_init(ENET_Type *ptr,  enet_desc_t *desc)
{
    uint32_t i = 0;
    enet_rx_desc_t *dma_rx_desc;

    /* set the rx_desc_list_cur pointer with the first one of the dma_rx_desc_tab list */
    desc->rx_desc_list_cur = desc->rx_desc_list_head;
    /* fill each dma_rx_desc descriptor with the right values */
    for (i = 0; i < desc->rx_buff_cfg.count; i++) {
        /* get the pointer on the ith member of the Rx desc list */
        dma_rx_desc = desc->rx_desc_list_head + i;
        /* set own bit of the rx descriptor status */
        dma_rx_desc->rdes0_bm.own = 1;

        /* set buffer 1 size and second address chained bit */
        dma_rx_desc->rdes1_bm.rch = 1;
        dma_rx_desc->rdes1_bm.rbs1 = desc->rx_buff_cfg.size;

        /* set buffer 1 address pointer */
        dma_rx_desc->rdes2_bm.buffer1 = (uint32_t)(&((uint8_t *)desc->rx_buff_cfg.buffer)[i * desc->rx_buff_cfg.size]);

        /* link all Rx descriptors */
        if (i < desc->rx_buff_cfg.count - 1) {
            /* set next descriptor address register with next descriptor base address */
            dma_rx_desc->rdes3_bm.next_desc = (uint32_t)(desc->rx_desc_list_head + i + 1);
        } else {
            /* for last descriptor, set next descriptor address register equal to the first descriptor base address */
            dma_rx_desc->rdes3_bm.next_desc = (uint32_t)desc->rx_desc_list_head;
        }
    }
    /* set receive descriptor list address register */
    ptr->DMA_RX_DESC_LIST_ADDR = (uint32_t)desc->rx_desc_list_head;
}

void enet_timestamp_enable(ENET_Type *ptr, bool enable)
{
    /* enable the timestamp */
    ptr->TS_CTRL &= ~ENET_TS_CTRL_TSENA_MASK;
    ptr->TS_CTRL |= ENET_TS_CTRL_TSENA_SET(enable);
}

void enet_set_subsecond_increment(ENET_Type *ptr, uint8_t ssinc)
{
    ptr->SUB_SEC_INCR &= ~ENET_SUB_SEC_INCR_SSINC_MASK;
    ptr->SUB_SEC_INCR |= ENET_SUB_SEC_INCR_SSINC_SET(ssinc);
}

void enet_set_ptp_timestamp(ENET_Type *ptr, enet_ptp_ts_update_t *timestamp)
{
    ptr->SYST_SEC_UPD = timestamp->sec;
    ptr->SYST_NSEC_UPD = timestamp->nsec;
    ptr->TS_CTRL |= ENET_TS_CTRL_TSINIT_MASK;

    while (ENET_TS_CTRL_TSINIT_GET(ptr->TS_CTRL) == 1) {

    }
}

void enet_get_ptp_timestamp(ENET_Type *ptr, enet_ptp_ts_system_t *timestamp)
{
    timestamp->sec = ptr->SYST_SEC;
    timestamp->nsec = ptr->SYST_NSEC;
}

void enet_update_ptp_timeoffset(ENET_Type *ptr, enet_ptp_ts_update_t *timeoffset)
{
    /* write the offset (positive or negative ) in the timestamp update high and low registers */
    ptr->SYST_SEC_UPD = ENET_SYST_SEC_UPD_TSS_SET(timeoffset->sec);
    ptr->SYST_NSEC_UPD = ENET_SYST_NSEC_UPD_ADDSUB_SET(timeoffset->sign) | ENET_SYST_NSEC_UPD_TSSS_SET(timeoffset->nsec);

    /* update the timestamp */
    ptr->TS_CTRL |= ENET_TS_CTRL_TSUPDT_MASK;

    /* wait for the updating to finish */
    while (ENET_TS_CTRL_TSUPDT_GET(ptr->TS_CTRL)) {

    }
}

void enet_adjust_ptp_time_freq(ENET_Type *ptr, int32_t adj)
{
    ptr->TS_ADDEND = (uint32_t)((int64_t)adj * ENET_ADJ_FREQ_BASE_ADDEND / (ENET_ONE_SEC_IN_NANOSEC - adj) + ENET_ADJ_FREQ_BASE_ADDEND);

    ptr->TS_CTRL |= ENET_TS_CTRL_TSADDREG_MASK;

    while (ENET_TS_CTRL_TSADDREG_GET(ptr->TS_CTRL)) {

    }
}

void enet_set_ptp_version(ENET_Type *ptr, enet_ptp_version_t ptp_ver)
{
    ptr->TS_CTRL &= ~ENET_TS_CTRL_TSVER2ENA_MASK;
    ptr->TS_CTRL |= ENET_TS_CTRL_TSVER2ENA_SET(ptp_ver);
}

hpm_stat_t enet_enable_ptp_frame_type(ENET_Type *ptr, enet_ptp_frame_type_t ptp_frame_type, bool enable)
{
    hpm_stat_t stat = status_success;

    if (ptp_frame_type == enet_ptp_frame_ipv4) {
        ptr->TS_CTRL &= ~ENET_TS_CTRL_TSIPV4ENA_MASK;
        ptr->TS_CTRL |= ENET_TS_CTRL_TSIPV4ENA_SET(enable);
    } else if (ptp_frame_type == enet_ptp_frame_ipv6) {
        ptr->TS_CTRL &= ~ENET_TS_CTRL_TSIPV6ENA_MASK;
        ptr->TS_CTRL |= ENET_TS_CTRL_TSIPV6ENA_SET(enable);
    } else if (ptp_frame_type == enet_ptp_frame_ethernet) {
        ptr->TS_CTRL &= ~ENET_TS_CTRL_TSIPENA_MASK;
        ptr->TS_CTRL |= ENET_TS_CTRL_TSIPENA_SET(enable);
    } else {
        return status_invalid_argument;
    }

    return stat;
}

void enet_set_snapshot_ptp_message_type(ENET_Type *ptr, enet_ts_ss_ptp_msg_t ts_ss_ptp_msg)
{
    /* set ptp message type for snapshots */
    ptr->TS_CTRL &= ~ENET_TS_CTRL_SNAPTYPSEL_MASK;
    ptr->TS_CTRL &= ~ENET_TS_CTRL_TSMSTRENA_MASK;
    ptr->TS_CTRL &= ~ENET_TS_CTRL_TSEVNTENA_MASK;
    ptr->TS_CTRL |= ts_ss_ptp_msg << ENET_TS_CTRL_TSEVNTENA_SHIFT;
}

void enet_init_ptp(ENET_Type *ptr, enet_ptp_config_t *config)
{
    enet_mask_interrupt_event(ptr, ENET_INTR_STATUS_TSIS_MASK);

    /* select the resolution of nanosecond */
    ptr->TS_CTRL &= ~ENET_TS_CTRL_TSCTRLSSR_MASK;
    ptr->TS_CTRL |= ENET_TS_CTRL_TSCTRLSSR_SET(config->timestamp_rollover_mode);

    /* enable timestamping */
    ptr->TS_CTRL |= ENET_TS_CTRL_TSENALL_MASK | ENET_TS_CTRL_TSENA_MASK;

    /* set sub-second increment */
    ptr->SUB_SEC_INCR &= ~ENET_SUB_SEC_INCR_SSINC_MASK;
    ptr->SUB_SEC_INCR |= ENET_SUB_SEC_INCR_SSINC_SET(config->ssinc);

    if (config->update_method == enet_ptp_time_fine_update) {
        /* set the addend */
        ptr->TS_ADDEND = config->addend;

        /* update the addend */
        ptr->TS_CTRL |= ENET_TS_CTRL_TSADDREG_MASK;

        /* poll the status of updating the addend */
        while (ENET_TS_CTRL_TSADDREG_GET(ptr->TS_CTRL)) {

        }

        /* fine update */
        ptr->TS_CTRL |= ENET_TS_CTRL_TSCFUPDT_MASK;
    } else {
        /* coarse update */
        ptr->TS_CTRL &= ~ENET_TS_CTRL_TSCFUPDT_MASK;
    }
}

void enet_set_pps0_control_output(ENET_Type *ptr, enet_pps_ctrl_t freq)
{
    ptr->PPS_CTRL &= ~ENET_PPS_CTRL_PPSEN0_MASK;
    ptr->PPS_CTRL |= ENET_PPS_CTRL_PPSCTRLCMD0_SET(freq);
}

hpm_stat_t enet_set_ppsx_command(ENET_Type *ptr, enet_pps_cmd_t cmd, enet_pps_idx_t idx)
{
    if (idx >= ENET_SOC_PPS_MAX_COUNT) {
        return status_invalid_argument;
    }

    /* Wait the last command to complete */
    while (ptr->PPS_CTRL & (ENET_PPS_CMD_MASK << ((idx + 1) << ENET_PPS_CMD_OFS_FAC))) {

    }

    /* Set the specified pps output with a specified command */
    ptr->PPS_CTRL |= cmd << ((idx + 1) << ENET_PPS_CMD_OFS_FAC);

    return status_success;
}

hpm_stat_t enet_set_ppsx_config(ENET_Type *ptr, enet_pps_cmd_config_t *cmd_cfg, enet_pps_idx_t idx)
{
    if (idx >= ENET_SOC_PPS_MAX_COUNT) {
        return status_invalid_argument;
    }

    /* Set the interval and width for PPSx */
    if (idx == enet_pps_0) {
        ptr->PPS0_INTERVAL = cmd_cfg->pps_interval - 1;
        ptr->PPS0_WIDTH    = cmd_cfg->pps_width - 1;
    } else {
        ptr->PPS[idx].INTERVAL = cmd_cfg->pps_interval - 1;
        ptr->PPS[idx].WIDTH    = cmd_cfg->pps_width - 1;
    }

    /* Set the target timestamp */
    if (idx == enet_pps_0) {
        ptr->TGTTM_SEC  = cmd_cfg->target_sec;
        ptr->TGTTM_NSEC = cmd_cfg->target_nsec;
    } else {
        ptr->PPS[idx].TGTTM_SEC  = cmd_cfg->target_sec;
        ptr->PPS[idx].TGTTM_NSEC = cmd_cfg->target_nsec;
    }

    /* Set PPS0 as the command function */
    if (idx == enet_pps_0) {
        ptr->PPS_CTRL |= ENET_PPS_CTRL_PPSEN0_MASK;
    }

#if ENET_SOC_PPS1_EN
    if (idx == enet_pps_1) {
        ptr->PPS_CTRL |= ENET_PPS_CTRL_PPSEN1_MASK;
    }
#endif

    /* Wait the last command to complete */
    while (ptr->PPS_CTRL & (ENET_PPS_CMD_MASK << ((idx + 1) << ENET_PPS_CMD_OFS_FAC))) {

    }

    /* Initialize with the No Command */
    ptr->PPS_CTRL &= ~(ENET_PPS_CMD_MASK << ((idx + 1) << ENET_PPS_CMD_OFS_FAC));

    return status_success;
}
