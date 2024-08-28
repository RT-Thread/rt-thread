/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_dmav2_drv.h"

void dma_default_channel_config(DMAV2_Type *ptr, dma_channel_config_t *ch)
{
    (void) ptr;
    ch->en_infiniteloop = false;
    ch->handshake_opt = DMA_HANDSHAKE_OPT_ONE_BURST;
    ch->burst_opt = DMA_SRC_BURST_OPT_STANDAND_SIZE;
    ch->priority = DMA_CHANNEL_PRIORITY_LOW;
    ch->src_mode = DMA_HANDSHAKE_MODE_NORMAL;
    ch->dst_mode = DMA_HANDSHAKE_MODE_NORMAL;
    ch->src_burst_size = DMA_NUM_TRANSFER_PER_BURST_1T;
    ch->src_addr_ctrl = DMA_ADDRESS_CONTROL_INCREMENT;
    ch->dst_addr_ctrl = DMA_ADDRESS_CONTROL_INCREMENT;
    ch->interrupt_mask = DMA_INTERRUPT_MASK_HALF_TC; /* disable half complete interrupt to keep align with dma */
    ch->linked_ptr = 0;
#if defined(HPM_IP_FEATURE_DMAV2_BURST_IN_FIXED_TRANS) && (HPM_IP_FEATURE_DMAV2_BURST_IN_FIXED_TRANS == 1)
    ch->en_src_burst_in_fixed_trans = false;
    ch->en_dst_burst_in_fixed_trans = false;
#endif
#if defined(HPM_IP_FEATURE_DMAV2_BYTE_ORDER_SWAP) && (HPM_IP_FEATURE_DMAV2_BYTE_ORDER_SWAP == 1)
    ch->swap_mode = DMA_SWAP_MODE_TABLE;
    ch->swap_table = 0;
#endif
}

hpm_stat_t dma_setup_channel(DMAV2_Type *ptr, uint8_t ch_num, dma_channel_config_t *ch, bool start_transfer)
{
    uint32_t tmp;

    if ((ch->dst_width > DMA_SOC_TRANSFER_WIDTH_MAX(ptr))
     || (ch->src_width > DMA_SOC_TRANSFER_WIDTH_MAX(ptr))
     || (ch_num >= DMA_SOC_CHANNEL_NUM)
     || (ch->en_infiniteloop && (ch->linked_ptr != 0))
     || ((ch->dst_mode == DMA_HANDSHAKE_MODE_HANDSHAKE) && (ch->src_mode == DMA_HANDSHAKE_MODE_HANDSHAKE))) {
        return status_invalid_argument;
    }

    if ((ch->size_in_byte & ((1 << ch->dst_width) - 1))
     || (ch->src_addr & ((1 << ch->src_width) - 1))
     || (ch->dst_addr & ((1 << ch->dst_width) - 1))
     || ((1 << ch->src_width) & ((1 << ch->dst_width) - 1))
     || ((ch->linked_ptr & 0x7))) {
        return status_dma_alignment_error;
    }

    ptr->CHCTRL[ch_num].SRCADDR = DMAV2_CHCTRL_SRCADDR_SRCADDRL_SET(ch->src_addr);
    ptr->CHCTRL[ch_num].DSTADDR = DMAV2_CHCTRL_DSTADDR_DSTADDRL_SET(ch->dst_addr);
    ptr->CHCTRL[ch_num].TRANSIZE = DMAV2_CHCTRL_TRANSIZE_TRANSIZE_SET(ch->size_in_byte >> ch->src_width);
    ptr->CHCTRL[ch_num].LLPOINTER = DMAV2_CHCTRL_LLPOINTER_LLPOINTERL_SET(ch->linked_ptr >> DMAV2_CHCTRL_LLPOINTER_LLPOINTERL_SHIFT);
    ptr->CHCTRL[ch_num].CHANREQCTRL = DMAV2_CHCTRL_CHANREQCTRL_SRCREQSEL_SET(ch_num) | DMAV2_CHCTRL_CHANREQCTRL_DSTREQSEL_SET(ch_num);
#if defined(HPM_IP_FEATURE_DMAV2_BYTE_ORDER_SWAP) && (HPM_IP_FEATURE_DMAV2_BYTE_ORDER_SWAP == 1)
    ptr->CHCTRL[ch_num].SWAPTABLE = ch->swap_table;
#endif

    dma_clear_transfer_status(ptr, ch_num);
    tmp = DMAV2_CHCTRL_CTRL_INFINITELOOP_SET(ch->en_infiniteloop)
        | DMAV2_CHCTRL_CTRL_HANDSHAKEOPT_SET(ch->handshake_opt)
        | DMAV2_CHCTRL_CTRL_BURSTOPT_SET(ch->burst_opt)
        | DMAV2_CHCTRL_CTRL_PRIORITY_SET(ch->priority)
        | DMAV2_CHCTRL_CTRL_SRCBURSTSIZE_SET(ch->src_burst_size)
        | DMAV2_CHCTRL_CTRL_SRCWIDTH_SET(ch->src_width)
        | DMAV2_CHCTRL_CTRL_DSTWIDTH_SET(ch->dst_width)
        | DMAV2_CHCTRL_CTRL_SRCMODE_SET(ch->src_mode)
        | DMAV2_CHCTRL_CTRL_DSTMODE_SET(ch->dst_mode)
        | DMAV2_CHCTRL_CTRL_SRCADDRCTRL_SET(ch->src_addr_ctrl)
        | DMAV2_CHCTRL_CTRL_DSTADDRCTRL_SET(ch->dst_addr_ctrl)
#if defined(HPM_IP_FEATURE_DMAV2_BURST_IN_FIXED_TRANS) && (HPM_IP_FEATURE_DMAV2_BURST_IN_FIXED_TRANS == 1)
        | DMAV2_CHCTRL_CTRL_SRC_FIXBURST_SET(ch->en_src_burst_in_fixed_trans)
        | DMAV2_CHCTRL_CTRL_DST_FIXBURST_SET(ch->en_dst_burst_in_fixed_trans)
#endif
#if defined(HPM_IP_FEATURE_DMAV2_BYTE_ORDER_SWAP) && (HPM_IP_FEATURE_DMAV2_BYTE_ORDER_SWAP == 1)
        | DMAV2_CHCTRL_CTRL_SWAP_CTL_SET(ch->swap_mode)
#endif
        | ch->interrupt_mask;

    if (start_transfer) {
        tmp |= DMAV2_CHCTRL_CTRL_ENABLE_MASK;
    }
    ptr->CHCTRL[ch_num].CTRL = tmp;

    return status_success;
}

hpm_stat_t dma_config_linked_descriptor(DMAV2_Type *ptr, dma_linked_descriptor_t *descriptor, uint8_t ch_num, dma_channel_config_t *config)
{
    (void) ptr;
    uint32_t tmp;

    if ((config->dst_width > DMA_SOC_TRANSFER_WIDTH_MAX(ptr))
     || (config->src_width > DMA_SOC_TRANSFER_WIDTH_MAX(ptr))
     || (ch_num >= DMA_SOC_CHANNEL_NUM)
     || (config->en_infiniteloop)
     || ((config->dst_mode == DMA_HANDSHAKE_MODE_HANDSHAKE) && (config->src_mode == DMA_HANDSHAKE_MODE_HANDSHAKE))) {
        return status_invalid_argument;
    }

    if ((config->size_in_byte & ((1 << config->dst_width) - 1))
     || (config->src_addr & ((1 << config->src_width) - 1))
     || (config->dst_addr & ((1 << config->dst_width) - 1))
     || ((1 << config->src_width) & ((1 << config->dst_width) - 1))
     || ((config->linked_ptr & 0x7))) {
        return status_dma_alignment_error;
    }

    descriptor->src_addr = DMAV2_CHCTRL_SRCADDR_SRCADDRL_SET(config->src_addr);
    descriptor->dst_addr = DMAV2_CHCTRL_DSTADDR_DSTADDRL_SET(config->dst_addr);
    descriptor->trans_size = DMAV2_CHCTRL_TRANSIZE_TRANSIZE_SET(config->size_in_byte >> config->src_width);
    descriptor->linked_ptr = DMAV2_CHCTRL_LLPOINTER_LLPOINTERL_SET(config->linked_ptr >> DMAV2_CHCTRL_LLPOINTER_LLPOINTERL_SHIFT);
    descriptor->req_ctrl = DMAV2_CHCTRL_CHANREQCTRL_SRCREQSEL_SET(ch_num) | DMAV2_CHCTRL_CHANREQCTRL_DSTREQSEL_SET(ch_num);
#if defined(HPM_IP_FEATURE_DMAV2_BYTE_ORDER_SWAP) && (HPM_IP_FEATURE_DMAV2_BYTE_ORDER_SWAP == 1)
    descriptor->swap_table = config->swap_table;
#endif

    tmp = DMAV2_CHCTRL_CTRL_INFINITELOOP_SET(false)
        | DMAV2_CHCTRL_CTRL_HANDSHAKEOPT_SET(config->handshake_opt)
        | DMAV2_CHCTRL_CTRL_BURSTOPT_SET(config->burst_opt)
        | DMAV2_CHCTRL_CTRL_PRIORITY_SET(config->priority)
        | DMAV2_CHCTRL_CTRL_SRCBURSTSIZE_SET(config->src_burst_size)
        | DMAV2_CHCTRL_CTRL_SRCWIDTH_SET(config->src_width)
        | DMAV2_CHCTRL_CTRL_DSTWIDTH_SET(config->dst_width)
        | DMAV2_CHCTRL_CTRL_SRCMODE_SET(config->src_mode)
        | DMAV2_CHCTRL_CTRL_DSTMODE_SET(config->dst_mode)
        | DMAV2_CHCTRL_CTRL_SRCADDRCTRL_SET(config->src_addr_ctrl)
        | DMAV2_CHCTRL_CTRL_DSTADDRCTRL_SET(config->dst_addr_ctrl)
#if defined(HPM_IP_FEATURE_DMAV2_BURST_IN_FIXED_TRANS) && (HPM_IP_FEATURE_DMAV2_BURST_IN_FIXED_TRANS == 1)
        | DMAV2_CHCTRL_CTRL_SRC_FIXBURST_SET(config->en_src_burst_in_fixed_trans)
        | DMAV2_CHCTRL_CTRL_DST_FIXBURST_SET(config->en_dst_burst_in_fixed_trans)
#endif
#if defined(HPM_IP_FEATURE_DMAV2_BYTE_ORDER_SWAP) && (HPM_IP_FEATURE_DMAV2_BYTE_ORDER_SWAP == 1)
        | DMAV2_CHCTRL_CTRL_SWAP_CTL_SET(config->swap_mode)
#endif
        | config->interrupt_mask
        | DMAV2_CHCTRL_CTRL_ENABLE_MASK;
    descriptor->ctrl = tmp;

    return status_success;
}

hpm_stat_t dma_start_memcpy(DMAV2_Type *ptr, uint8_t ch_num,
                               uint32_t dst, uint32_t src,
                               uint32_t size, uint32_t burst_len_in_byte)
{
    hpm_stat_t stat = status_success;
    uint32_t width, count;
    uint32_t burst_size;
    dma_channel_config_t config = {0};
    dma_default_channel_config(ptr, &config);

    /* burst size checking (1-byte burst length will cause heavy overhead */
    if (!burst_len_in_byte || burst_len_in_byte == 1 || burst_len_in_byte > size
        || burst_len_in_byte >
            (uint32_t) ((1 << DMA_SOC_TRANSFER_WIDTH_MAX(ptr)) << DMA_SOC_TRANSFER_PER_BURST_MAX(ptr))) {
        return status_invalid_argument;
    }

    count = count_set_bits(burst_len_in_byte);
    if ((count > 1) || (burst_len_in_byte & 0x1)) {
        /* dma only supports 2^n bytes as burst size */
        return status_invalid_argument;
    }

    if ((size & (burst_len_in_byte - 1))) {
        return status_dma_alignment_error;
    }
    burst_size = get_first_set_bit_from_lsb(burst_len_in_byte);

    config.src_width = DMA_TRANSFER_WIDTH_HALF_WORD;
    config.dst_width = DMA_TRANSFER_WIDTH_HALF_WORD;
    for (width = DMA_SOC_TRANSFER_WIDTH_MAX(ptr); width > DMA_TRANSFER_WIDTH_HALF_WORD; width--) {
        if (!(burst_len_in_byte & ((1 << width) - 1))
            && !(dst & ((1 << width) - 1))
            && !(src & ((1 << width) - 1))
            && !(size & ((1 << width) - 1))) {
            config.src_width = width;
            config.dst_width = width;
            break;
        }
    }

    burst_size -= config.src_width;
    do {
        if (!(src & (((1 << config.src_width) << burst_size) - 1))) {
            break;
        }
        burst_size--;
    } while (burst_size > 0);

    config.src_addr = src;
    config.dst_addr = dst;
    config.size_in_byte = size;

    config.src_burst_size = burst_size;
    stat = dma_setup_channel(ptr, ch_num, &config, true);
    if (stat != status_success) {
        return stat;
    }

    return stat;
}

void dma_default_handshake_config(DMAV2_Type *ptr, dma_handshake_config_t *config)
{
    (void) ptr;
    memset(config, 0, sizeof(dma_handshake_config_t));
    config->en_infiniteloop = false;
    config->interrupt_mask = DMA_INTERRUPT_MASK_HALF_TC;
}

hpm_stat_t dma_setup_handshake(DMAV2_Type *ptr,  dma_handshake_config_t *pconfig, bool start_transfer)
{
    hpm_stat_t stat = status_success;
    dma_channel_config_t config = {0};
    dma_default_channel_config(ptr, &config);

    if (true == pconfig->dst_fixed) {
        config.dst_addr_ctrl = DMA_ADDRESS_CONTROL_FIXED;
        config.dst_mode = DMA_HANDSHAKE_MODE_HANDSHAKE;
    }
    if (true == pconfig->src_fixed) {
        config.src_addr_ctrl = DMA_ADDRESS_CONTROL_FIXED;
        config.src_mode = DMA_HANDSHAKE_MODE_HANDSHAKE;
    }

    if (pconfig->ch_index >= DMA_SOC_CHANNEL_NUM) {
        return status_invalid_argument;
    }

    config.en_infiniteloop = pconfig->en_infiniteloop;
    config.interrupt_mask = pconfig->interrupt_mask;
    config.src_width = pconfig->data_width;
    config.dst_width = pconfig->data_width;
    config.src_addr = pconfig->src;
    config.dst_addr = pconfig->dst;
    config.size_in_byte = pconfig->size_in_byte;
    /*  In DMA handshake case, source burst size must be 1 transfer, that is 0. */
    config.src_burst_size = 0;
    stat = dma_setup_channel(ptr, pconfig->ch_index, &config, start_transfer);
    if (stat != status_success) {
        return stat;
    }
    return stat;
}
