/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_smbus.h"

static uint8_t hpm_smbus_pec_crc8(uint8_t *data, uint32_t len);


hpm_stat_t hpm_smbus_master_write_byte(I2C_Type *ptr, uint8_t slave_address, uint8_t data)
{
    hpm_stat_t stat;
    uint8_t buf[3];
    /* addr + rw bit*/
    buf[0] = slave_address << 1;
    buf[1] = data;
    buf[2] = hpm_smbus_pec_crc8(buf, 2);
    stat = i2c_master_write(ptr, (const uint16_t)slave_address, &buf[1], sizeof(buf) - 1);
    return stat;
}

hpm_stat_t hpm_smbus_master_read_byte(I2C_Type *ptr, uint8_t slave_address, uint8_t *data)
{
    uint8_t buf[3];
    hpm_stat_t stat;
    uint8_t pec;
    /* addr + rw bit*/
    buf[0] = (slave_address << 1);
    stat = i2c_master_read(ptr, (const uint16_t)slave_address, &buf[1], sizeof(buf) - 1);
    if (stat == status_success) {
        pec = hpm_smbus_pec_crc8(buf, sizeof(buf) - 1);
        if (pec == buf[2]) {
            *data = buf[1];
        } else {
            stat = status_fail;
        }
    }
    return stat;
}

hpm_stat_t hpm_smbus_master_write_byte_in_command(I2C_Type *ptr, uint8_t slave_address, uint8_t command, uint8_t data)
{
    hpm_stat_t stat;
    uint8_t buf[4];
    /* addr + rw bit*/
    buf[0] = slave_address << 1;
    buf[1] = command;
    buf[2] = data;
    buf[3] = hpm_smbus_pec_crc8(buf, sizeof(buf) - 1);
    stat = i2c_master_write(ptr, (const uint16_t)slave_address, &buf[1], sizeof(buf) - 1);
    return stat;
}

hpm_stat_t hpm_smbus_master_write_word_in_command(I2C_Type *ptr, uint8_t slave_address, uint8_t command, uint16_t data)
{
    hpm_stat_t stat;
    uint8_t pec;
    uint8_t buf[5];
    /* addr + rw bit*/
    buf[0] = slave_address << 1;
    buf[1] = command;
    *(uint16_t *)(&buf[2]) = data;
    buf[4] = hpm_smbus_pec_crc8(buf, sizeof(buf) - 1);
    stat = i2c_master_write(ptr, (const uint16_t)slave_address, &buf[1], sizeof(buf) - 1);
    return stat;
}

hpm_stat_t hpm_smbus_master_read_byte_in_command(I2C_Type *ptr, uint8_t slave_address, uint8_t command, uint8_t *data)
{
    hpm_stat_t stat;
    uint8_t pec;
    uint8_t buf[5];
    /* addr + rw bit*/
    buf[0] = (slave_address << 1);
    buf[1] = command;
    /* write command code in smbus spec*/
    stat = i2c_master_seq_transmit(ptr, (const uint16_t)slave_address, &command, sizeof(uint8_t), i2c_frist_frame);
    if (stat == status_success) {
        /* read */
        buf[2] = (slave_address << 1) | 0x01;
        /* now change dir,restart, read the byte */
        stat = i2c_master_seq_receive(ptr, (const uint16_t)slave_address, &buf[3], 1, i2c_frist_frame);
        /* read the pec */
        stat = i2c_master_seq_receive(ptr, (const uint16_t)slave_address, &buf[4], 1, i2c_last_frame);
        if (stat == status_success) {
            pec = hpm_smbus_pec_crc8(buf, sizeof(buf) - 1);
            if (pec == buf[4]) {
                *data = buf[3];
            } else {
                stat = status_fail;
            }
        }
    }
    return stat;
}

hpm_stat_t hpm_smbus_master_read_word_in_command(I2C_Type *ptr, uint8_t slave_address, uint8_t command, uint16_t *data)
{
    hpm_stat_t stat;
    uint8_t pec;
    uint8_t buf[6];
    /* addr + rw bit*/
    buf[0] = (slave_address << 1);
    buf[1] = command;
    /* write command code in smbus spec*/
    stat = i2c_master_seq_transmit(ptr, (const uint16_t)slave_address, &command, sizeof(uint8_t), i2c_frist_frame);
    if (stat == status_success) {
        /* read */
        buf[2] = (slave_address << 1) | 0x01;
        /* now change dir,restart, read the word (16 bits)*/
        stat = i2c_master_seq_receive(ptr, (const uint16_t)slave_address, &buf[3], 2, i2c_frist_frame);
        /* read the pec */
        stat = i2c_master_seq_receive(ptr, (const uint16_t)slave_address, &buf[5], 1, i2c_last_frame);
        if (stat == status_success) {
            pec = hpm_smbus_pec_crc8(buf, sizeof(buf) - 1);
            if (pec == buf[5]) {
                *data = *(uint16_t *)(&buf[3]);
            } else {
                stat = status_fail;
            }
        }
    }
    return stat;
}

hpm_stat_t hpm_smbus_master_write_block_in_command(I2C_Type *ptr, uint8_t slave_address, uint8_t command, uint8_t *data, uint32_t size)
{
    hpm_stat_t stat;
    uint8_t pec;
    uint8_t buf[I2C_SOC_TRANSFER_COUNT_MAX];
    uint16_t buf_size;
    /* frame included addr, command, data, and pec */
    assert(size > 0 && size <= (I2C_SOC_TRANSFER_COUNT_MAX - 3));
    /* addr + rw bit*/
    buf[0] = slave_address << 1;
    buf[1] = command;
    buf[2] = size;
    memcpy(&buf[3], data, size);
    buf[size + 3] = hpm_smbus_pec_crc8(buf, size + 3);
    buf_size = size + 4;
    stat = i2c_master_write(ptr, (const uint16_t)slave_address, buf, buf_size);
    return stat;
}

hpm_stat_t hpm_smbus_master_read_block_in_command(I2C_Type *ptr, uint8_t slave_address, uint8_t command, uint8_t *data, uint32_t size)
{
    hpm_stat_t stat;
    uint8_t pec;
    uint8_t buf[I2C_SOC_TRANSFER_COUNT_MAX];
    uint16_t buf_size;
    /* frame included addr, command, data, and pec */
    assert(size > 0 && size <= (I2C_SOC_TRANSFER_COUNT_MAX - 3));
    /* addr + rw bit*/
    buf[0] = (slave_address << 1);
    buf[1] = command;
    /* write command code in smbus spec*/
    stat = i2c_master_seq_transmit(ptr, (const uint16_t)slave_address, &command, sizeof(uint8_t), i2c_frist_frame);
    /* read */
    buf[2] = (slave_address << 1) | 0x01;
    if (stat == status_success) {
        /* now change dir,restart, read the block count*/
        stat = i2c_master_seq_receive(ptr, (const uint16_t)slave_address, &buf[3], 1, i2c_frist_frame);
        /* read data*/
        stat = i2c_master_seq_receive(ptr, (const uint16_t)slave_address, &buf[4], size, i2c_next_frame);
        /* read pec */
        stat = i2c_master_seq_receive(ptr, (const uint16_t)slave_address, &buf[size + 4], 1, i2c_last_frame);
        if (stat == status_success) {
            pec = hpm_smbus_pec_crc8(buf, sizeof(buf) - 1);
            if (pec == buf[size + 4]) {
                memcpy(data, &buf[4], size);
            } else {
                stat = status_fail;
            }
        }
    }
    return stat;
}

hpm_stat_t hpm_smbus_master_write(I2C_Type *ptr, uint8_t slave_address, uint8_t *data, uint32_t size)
{
    hpm_stat_t stat;
    uint8_t pec;
    uint8_t buf[I2C_SOC_TRANSFER_COUNT_MAX];
    uint16_t buf_size;
    /* frame included addr, data, and pec */
    assert(size > 0 && size <= (I2C_SOC_TRANSFER_COUNT_MAX - 1));
    /* addr + rw bit*/
    buf[0] = (slave_address << 1) | 0x01;
    memcpy(&buf[1], data, size);
    buf[size + 1] = hpm_smbus_pec_crc8(buf, size + 1);
    buf_size = size + 1;
    stat = i2c_master_write(ptr, (const uint16_t)slave_address, &buf[1], buf_size);
    return stat;
}

hpm_stat_t hpm_smbus_master_read(I2C_Type *ptr, uint8_t slave_address, uint8_t *data, uint32_t size)
{
    hpm_stat_t stat;
    uint8_t pec;
    uint8_t buf[I2C_SOC_TRANSFER_COUNT_MAX];
    uint16_t buf_size;
    /* frame included addr, data, and pec */
    assert(size > 0 && size <= (I2C_SOC_TRANSFER_COUNT_MAX - 2));
    buf[0] = (slave_address << 1);
    stat = i2c_master_read(ptr, slave_address, &buf[1], size + 1);
    if (stat == status_success) {
        pec = hpm_smbus_pec_crc8(buf, size + 1);
        if (pec == buf[size + 1]) {
            memcpy(data, &buf[1], size);
        } else {
            stat = status_fail;
        }
    }
    return stat;
}

hpm_stat_t hpm_smbus_slave_write(I2C_Type *ptr, uint8_t *data, uint32_t size)
{
    hpm_stat_t stat;
    uint8_t pec;
    uint8_t buf[I2C_SOC_TRANSFER_COUNT_MAX];
    uint16_t buf_size;
    uint8_t slave_address;
    /* frame included addr, data, and pec */
    assert(size > 0 && size <= (I2C_SOC_TRANSFER_COUNT_MAX - 1));
    slave_address = ptr->ADDR;
    /* addr + rw bit*/
    buf[0] = (slave_address << 1);
    memcpy(&buf[1], data, size);
    buf[size + 1] = hpm_smbus_pec_crc8(buf, size + 1);
    buf_size = size + 1;
    stat = i2c_slave_write(ptr, &buf[1], buf_size);
    return stat;
}

hpm_stat_t hpm_smbus_slave_read(I2C_Type *ptr, uint8_t *data, uint32_t size)
{
    hpm_stat_t stat;
    uint8_t pec;
    uint8_t buf[I2C_SOC_TRANSFER_COUNT_MAX];
    uint16_t buf_size;
    uint8_t slave_address;
    /* frame included addr, data, and pec */
    assert(size > 0 && size <= (I2C_SOC_TRANSFER_COUNT_MAX - 2));
    /* addr + rw bit*/
    slave_address = ptr->ADDR;
    buf[0] = (slave_address << 1) | 0x01;
    stat = i2c_slave_read(ptr, &buf[1], size + 1);
    if (stat == status_success) {
        pec = hpm_smbus_pec_crc8(buf, size + 1);
        if (pec == buf[size + 1]) {
            memcpy(data, &buf[1], size);
        } else {
            stat = status_fail;
        }
    }
    return stat;
}

static uint8_t hpm_smbus_pec_crc8(uint8_t *data, uint32_t len)
{
    /* The PEC is a CRC-8 error-checking byte, calculated on all the message bytes (including addresses and read/write bits) */
    uint32_t i;
    uint8_t crc = 0x00;
    while (len--) {
        crc ^= *data++;
        for (i = 0; i < 8; i++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ 0x07;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

