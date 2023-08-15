/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_sccb.h"

hpm_stat_t sccb_master_init(sccb_type sccb)
{
    /*TODO*/
    return status_success;
}

uint8_t sccb_master_scan(sccb_type sccb)
{
    for (uint8_t addr = 0x01, rxdata; addr < 0xff; addr++) {
        if (i2c_master_read(sccb, addr, &rxdata, 1) == status_success) {
            return addr;
        }
    }
    return 0;
}

hpm_stat_t sccb_master_gencall(sccb_type sccb, uint8_t cmd)
{
    uint8_t reg_data = 0;
    return i2c_master_address_write(sccb, 0x00, &cmd, 1, &reg_data, 1);
}

hpm_stat_t sccb_master_readb(sccb_type sccb, uint8_t slv_addr, uint8_t reg_addr, uint8_t *reg_data)
{
    return i2c_master_address_read(sccb, (uint16_t)slv_addr, (uint8_t *)&reg_addr, 1, reg_data, 1);
}

hpm_stat_t sccb_master_writeb(sccb_type sccb, uint8_t slv_addr, uint8_t reg_addr, uint8_t reg_data)
{
    return i2c_master_address_write(sccb, (uint16_t)slv_addr, (uint8_t *)&reg_addr, 1, (uint8_t *)&reg_data, 1);
}

hpm_stat_t sccb_master_readb2(sccb_type sccb, uint8_t slv_addr, uint16_t reg_addr, uint8_t *reg_data)
{
    uint8_t r[2];
    r[0] = reg_addr >> 8;
    r[1] = reg_addr & 0xFF;
    return i2c_master_address_read(sccb, (uint16_t)slv_addr, r, sizeof(r), reg_data, 1);
}

hpm_stat_t sccb_master_writeb2(sccb_type sccb, uint8_t slv_addr, uint16_t reg_addr, uint8_t reg_data)
{
    int ret = 0;
    uint8_t r[2];
    r[0] = reg_addr >> 8;
    r[1] = reg_addr & 0xFF;
    return i2c_master_address_write(sccb, (uint16_t)slv_addr, r, sizeof(r), (uint8_t *)&reg_data, 1);
}

hpm_stat_t sccb_master_readw(sccb_type sccb, uint8_t slv_addr, uint8_t reg_addr, uint16_t *reg_data)
{
    hpm_stat_t ret = status_success;
    ret = i2c_master_address_read(sccb, (uint16_t)slv_addr, (uint8_t *)&reg_addr,
                                1, (uint8_t *)reg_data, 2);
    if (ret == status_success) {
        *reg_data = (*reg_data >> 8) | (*reg_data << 8);
    }
    return ret;
}

hpm_stat_t sccb_master_writew(sccb_type sccb, uint8_t slv_addr, uint8_t reg_addr, uint16_t reg_data)
{
    reg_data = (reg_data >> 8) | (reg_data << 8);
    return i2c_master_address_write(sccb, (uint16_t)slv_addr, (uint8_t *)&reg_addr, 1, (uint8_t *)&reg_data, 2);
}

hpm_stat_t sccb_master_readw2(sccb_type sccb, uint8_t slv_addr, uint16_t reg_addr, uint16_t *reg_data)
{
    hpm_stat_t ret = status_success;
    ret = i2c_master_address_read(sccb, (uint16_t)slv_addr, (uint8_t *)&reg_addr,
                                2, (uint8_t *)reg_data, 2);
    if (ret == status_success) {
        *reg_data = (*reg_data >> 8) | (*reg_data << 8);
    }
    return ret;
}

hpm_stat_t sccb_master_writew2(sccb_type sccb, uint8_t slv_addr, uint16_t reg_addr, uint16_t reg_data)
{
    int ret = 0;
    reg_data = (reg_data >> 8) | (reg_data << 8);
    return i2c_master_address_write(sccb, (uint16_t)slv_addr,
                                    (uint8_t *)&reg_addr, 2,
                                    (uint8_t *)&reg_data, 2);
}

hpm_stat_t sccb_master_read_bytes(sccb_type sccb, uint8_t slv_addr, uint8_t *buf, const uint32_t len, uint8_t flags)
{
    return i2c_master_read(sccb, (uint16_t)slv_addr, buf, len);
}

hpm_stat_t cambus_write_bytes(sccb_type sccb, uint8_t slv_addr, uint8_t *buf, const uint32_t len, uint8_t flags)
{
    int ret = 0;
    hpm_stat_t sta = status_success;
    int _len = len;
    int remain = 0;
    int offset = 0;
    while (_len > 0) {
        remain = (_len > 100) ? 100 : _len;
        sta = i2c_master_write(sccb, (uint16_t)slv_addr, &buf[offset], remain);
        if (sta != status_success) {
            return status_fail;
        }
        offset += remain;
        _len -= remain;
    }
    return sta;
}
