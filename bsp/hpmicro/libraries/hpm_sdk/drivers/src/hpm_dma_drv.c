/*
 * Copyright (c) 2021 - 2022 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_dma_drv.h"

hpm_stat_t dma_setup_channel(DMA_Type *ptr, uint32_t ch_num, dma_channel_config_t *ch)
{
    uint32_t tmp;
    if ((ch->dst_width > DMA_SOC_TRANSFER_WIDTH_MAX(ptr))
            || (ch->src_width > DMA_SOC_TRANSFER_WIDTH_MAX(ptr))) {
        return status_invalid_argument;
    }
    if ((ch->size_in_byte & ((1 << ch->dst_width) - 1))
     || (ch->src_addr & ((1 << ch->src_width) - 1))
     || (ch->src_addr & (((1 << ch->src_width) << ch->src_burst_size) - 1))
     || (ch->dst_addr & ((1 << ch->dst_width) - 1))
     || (ch->dst_addr & (((1 << ch->dst_width) << ch->src_burst_size) - 1))
     || ((1 << ch->src_width) & ((1 << ch->dst_width) - 1))
     || (((1 << ch->src_width) << ch->src_burst_size) & ((1 << ch->dst_width) - 1))
     || ((ch->linked_ptr & 0x7))) {
        return status_dma_alignment_error;
    }
    ptr->CHCTRL[ch_num].SRCADDR = DMA_CHCTRL_SRCADDR_SRCADDRL_SET(ch->src_addr);
    ptr->CHCTRL[ch_num].DSTADDR = DMA_CHCTRL_DSTADDR_DSTADDRL_SET(ch->dst_addr);
    ptr->CHCTRL[ch_num].TRANSIZE = DMA_CHCTRL_TRANSIZE_TRANSIZE_SET(ch->size_in_byte >> ch->src_width);
    ptr->CHCTRL[ch_num].LLPOINTER = DMA_CHCTRL_LLPOINTER_LLPOINTERL_SET(ch->linked_ptr >> 3);

#if DMA_SUPPORT_64BIT_ADDR
    ptr->CHCTRL[ch_num].SRCADDRH = DMA_CHCTRL_SRCADDRH_SRCADDRH_SET(ch->src_addr_high);
    ptr->CHCTRL[ch_num].DSTADDRH = DMA_CHCTRL_DSTADDRH_DSTADDRH_SET(ch->dst_addr_high);
    ptr->CHCTRL[ch_num].LLPOINTERH = DMA_CHCTRL_LLPOINTERH_LLPOINTERH_SET(ch->linked_ptr_high);
#endif

    ptr->INTSTATUS = (DMA_INTSTATUS_TC_SET(1) | DMA_INTSTATUS_ABORT_SET(1) | DMA_INTSTATUS_ERROR_SET(1)) << ch_num;
    tmp = DMA_CHCTRL_CTRL_SRCBUSINFIDX_SET(0)
        | DMA_CHCTRL_CTRL_DSTBUSINFIDX_SET(0)
        | DMA_CHCTRL_CTRL_PRIORITY_SET(ch->priority)
        | DMA_CHCTRL_CTRL_SRCBURSTSIZE_SET(ch->src_burst_size)
        | DMA_CHCTRL_CTRL_SRCWIDTH_SET(ch->src_width)
        | DMA_CHCTRL_CTRL_DSTWIDTH_SET(ch->dst_width)
        | DMA_CHCTRL_CTRL_SRCMODE_SET(ch->src_mode)
        | DMA_CHCTRL_CTRL_DSTMODE_SET(ch->dst_mode)
        | DMA_CHCTRL_CTRL_SRCADDRCTRL_SET(ch->src_addr_ctrl)
        | DMA_CHCTRL_CTRL_DSTADDRCTRL_SET(ch->dst_addr_ctrl)
        | DMA_CHCTRL_CTRL_SRCREQSEL_SET(ch_num)
        | DMA_CHCTRL_CTRL_DSTREQSEL_SET(ch_num)
        | ch->interrupt_mask
        | DMA_CHCTRL_CTRL_ENABLE_MASK;
    ptr->CHCTRL[ch_num].CTRL = tmp;
    if ((ptr->CHEN == 0) || !(ptr->CHEN & 1 << ch_num)) {
        return status_fail;
    }

    return status_success;
}


void dma_default_channel_config(DMA_Type *ptr, dma_channel_config_t *ch)
{
    ch->priority = 0;
    ch->src_mode = DMA_HANDSHAKE_MODE_NORMAL;
    ch->dst_mode = DMA_HANDSHAKE_MODE_NORMAL;
    ch->src_burst_size = DMA_NUM_TRANSFER_PER_BURST_1T;
    ch->src_addr_ctrl = DMA_ADDRESS_CONTROL_INCREMENT;
    ch->dst_addr_ctrl = DMA_ADDRESS_CONTROL_INCREMENT;
    ch->interrupt_mask = DMA_INTERRUPT_MASK_NONE;
    ch->linked_ptr= 0;
#if DMA_SUPPORT_64BIT_ADDR
    ch->linked_ptr_high = 0;
#endif
}

hpm_stat_t dma_start_memcpy(DMA_Type *ptr, uint8_t ch_num,
                               uint32_t dst, uint32_t src,
                               uint32_t size, uint32_t burst_len_in_byte)
{
    hpm_stat_t stat = status_success;
    uint32_t width, count;
    int32_t burst_size;
    dma_channel_config_t config = {0};
    dma_default_channel_config(ptr, &config);

    /* burst size checking (1-byte burst length will cause heavy overhead */
    if (!burst_len_in_byte || burst_len_in_byte == 1 || burst_len_in_byte > size
        || burst_len_in_byte >
            ((1 << DMA_SOC_TRANSFER_WIDTH_MAX(ptr)) << DMA_SOC_TRANSFER_PER_BURST_MAX(ptr))) {
        return status_invalid_argument;
    }

    count = count_set_bits(burst_len_in_byte);
    if ((count > 1) || (burst_len_in_byte & 0x1)) {
        /* dma only supports 2^n bytes as burst size */
        return status_invalid_argument;
    }

    if ((size & (burst_len_in_byte - 1))
            || (dst & (burst_len_in_byte - 1))
            || (src & (burst_len_in_byte - 1))) {
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
    stat = dma_setup_channel(ptr, ch_num, &config);
    if (stat != status_success) {
        return stat;
    }

    return stat;
}

hpm_stat_t dma_setup_handshake(DMA_Type *ptr,  dma_handshake_config_t *pconfig)
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

    if (pconfig->ch_index > DMA_SOC_CHANNEL_NUM) {
        return status_invalid_argument;
    }

    /*  In DMA handshake case, source width and destination width must be BYTE. */
    config.src_width = DMA_TRANSFER_WIDTH_BYTE;
    config.dst_width = DMA_TRANSFER_WIDTH_BYTE;
    config.src_addr = pconfig->src;
    config.dst_addr = pconfig->dst;
    config.size_in_byte = pconfig->size_in_byte;
     /*  In DMA handshake case, source burst size must be 1 transfer, that is 0. */
    config.src_burst_size = 0;
    stat = dma_setup_channel(ptr, pconfig->ch_index, &config);
    if (stat != status_success) {
        return stat;
    }
    return stat;
}
