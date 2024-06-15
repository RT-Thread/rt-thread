/*
 * Copyright (c) 2021-2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_common.h"
#include "hpm_crc_drv.h"

void crc_get_default_channel_config(crc_channel_config_t *cfg)
{
    cfg->preset = crc_preset_crc32;
    cfg->poly = 0x4C11DB7ul;
    cfg->init = 0xFFFFFFFul;
    cfg->in_byte_order = crc_in_byte_order_lsb;
    cfg->refout = crc_refout_true;
    cfg->refin = crc_refin_true;
    cfg->poly_width = CRC_POLY_WIDTH_32;
    cfg->xorout = 0xFFFFFFF;
}

hpm_stat_t crc_setup_channel_config(CRC_Type *ptr, uint32_t ch_index,
                            crc_channel_config_t *cfg)
{
    ptr->CHN[ch_index].PRE_SET = cfg->preset;

    if (!ptr->CHN[ch_index].PRE_SET) {
        ptr->CHN[ch_index].POLY = cfg->poly;
        ptr->CHN[ch_index].INIT_DATA = cfg->init;
        ptr->CHN[ch_index].XOROUT = cfg->xorout;
        ptr->CHN[ch_index].MISC_SETTING = CRC_CHN_MISC_SETTING_REV_OUT_SET(cfg->refout) |
                                        CRC_CHN_MISC_SETTING_REV_IN_SET(cfg->refin) |
                                        CRC_CHN_MISC_SETTING_POLY_WIDTH_SET(cfg->poly_width);
    }

    ptr->CHN[ch_index].MISC_SETTING |= CRC_CHN_MISC_SETTING_BYTE_REV_SET(cfg->in_byte_order);
    return status_success;
}

void crc_calc_block_bytes(CRC_Type *ptr, uint32_t ch_index, uint8_t *pbuffer, uint32_t length)
{
    uint32_t addr = (uint32_t)&ptr->CHN[ch_index].DATA;

    for (uint32_t i = 0; i < length; i++) {
        CRC_REG_WRITE8(addr, pbuffer[i]);
    }
}

void crc_calc_block_half_words(CRC_Type *ptr, uint32_t ch_index, uint16_t *pbuffer, uint32_t length)
{
    uint32_t addr = (uint32_t)&ptr->CHN[ch_index].DATA;

    for (uint32_t i = 0; i < length; i++) {
        CRC_REG_WRITE16(addr, pbuffer[i]);
    }
}

void crc_calc_block_words(CRC_Type *ptr, uint32_t ch_index, uint32_t *pbuffer, uint32_t length)
{
    uint32_t addr = (uint32_t)&ptr->CHN[ch_index].DATA;

    for (uint32_t i = 0; i < length; i++) {
        CRC_REG_WRITE32(addr, pbuffer[i]);
    }
}

void crc_calc_large_block_fast(CRC_Type *ptr, uint32_t ch_index, uint8_t *pbuffer, uint32_t length)
{
    if (length < 16) {
        crc_calc_block_bytes(ptr, ch_index, pbuffer, length);
        return;
    }

    uint32_t addr = (uint32_t)&ptr->CHN[ch_index].DATA;
    uint32_t start_byte_addr = (uint32_t)pbuffer;
    uint32_t start_byte_len = 4ul - (start_byte_addr & 0x03ul);
    uint32_t word_addr = start_byte_addr + start_byte_len;
    uint32_t word_len = (length - start_byte_len) & (~0x03ul);
    uint32_t end_byte_addr = word_addr + word_len;
    uint32_t end_byte_len = (length - start_byte_len - word_len);

    for (uint32_t i = 0; i < start_byte_len; i++) {
        CRC_REG_WRITE8(addr, *(volatile uint8_t *)(start_byte_addr + i));
    }

    for (uint32_t i = 0; i < word_len; i += 4) {
        CRC_REG_WRITE32(addr, *(volatile uint32_t *)(word_addr + i));
    }

    for (uint32_t i = 0; i < end_byte_len; i++) {
        CRC_REG_WRITE8(addr, *(volatile uint8_t *)(end_byte_addr + i));
    }
}

