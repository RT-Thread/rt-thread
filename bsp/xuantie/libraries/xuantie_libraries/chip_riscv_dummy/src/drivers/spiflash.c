 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     spiflash.c
 * @brief
 * @version
 * @date     2020-03-18
 ******************************************************************************/
#include <string.h>
#include <drv/spiflash.h>
#include <drv/irq.h>
#include <drv/tick.h>

/* FLASH command set */
#define FLASH_CMD_WRITE_STATUS       0x01U
#define FLASH_CMD_READ_STATUS1       0x05U
#define FLASH_CMD_READ_STATUS2       0x35U
#define FLASH_CMD_WRITE_ENABLE       0x06U
#define FLASH_CMD_READ_JEDEC_ID      0x9FU
#define FLASH_CMD_SECTOR_ERASE       0x20U
#define FLASH_CMD_CHIP_ERASE         0x60U
#define FLASH_CMD_PAGE_PROGRAM       0x02U
#define FLASH_CMD_READ_DATA          0x03U
#define FLASH_CMD_SECTOR_ERASE       0x20U
#define FALSH_CMD_POWER_DOWN         0xB9U
#define FALSH_CMD_RELEASE_POWER_DOWN 0xABU


/* FLASH operation parameters */
#define FLASH_DEFUALT_OPERATION_TIMEOUT 100000U

#define FLASH_STATUS_BP_Pos               2U
#define FLASH_STATUS_TB_Pos(bp_bits)     (bp_bits + FLASH_STATUS_BP_Pos)

#define FLASH_STATUS_BP_Msk(bp_bits, bp_msk) \
    while(bp_bits--){                     \
        bp_msk <<= 1U;                    \
        bp_msk |= 1U;                     \
    };                                    \
    bp_msk <<= FLASH_STATUS_BP_Pos;

#define FLASH_STATUS_TB_Msk(bp_bits)     (0x1U << FLASH_STATUS_TB_Pos(bp_bits))

#define SPIFLASH_BASE               0x18000000UL

typedef enum {
    FLASH_ADDR_24,                        ///< 24bit address
    FLASH_ADDR_32,                        ///< 32bit address
} csi_spiflash_addr_mode_t;

typedef struct csi_spiflash_param {

    char      *flash_name;       ///< name string of spiflash
    uint32_t   flash_id;         ///< JEDEC ID  = manufature ID <<16 | device ID (ID15~ID0)
    csi_spiflash_addr_mode_t addr_mode; ///< flash addr mode(24bit or 32 bit)
    uint32_t   flash_size;              ///< flash chip size
    uint32_t   sector_size;             ///< sector size
    uint32_t   page_size;               ///< page size for read or program
    uint32_t   has_lock: 1;             ///< whether flash support lock function
    uint32_t   region:  2;              ///< spiflash lock region type, pls /ref csi_spiflash_lock_region_t
    uint32_t   bp_bits: 4;              ///< how many block protect bits to protect flash
    uint32_t   base_protect_size;       ///< smallest protect size
    uint32_t   qe_pos;                  ///< qe bit position
} csi_spiflash_param_t;

extern csi_error_t spiflash_config_data_line(csi_spiflash_t *spiflash, csi_spiflash_data_line_t line);

static int32_t flash_wait_ready(csi_spiflash_t *spiflash)
{
    uint32_t addr, addr_size, size;
    uint32_t time_start;
    uint8_t  cmd;
    uint8_t  status;
    int32_t  ret = CSI_TIMEOUT;
    int32_t  check;

    time_start = csi_tick_get_ms();
    cmd        = FLASH_CMD_READ_STATUS1;
    addr       = 0U;
    addr_size  = 0U;
    size       = 1U;

    while ((csi_tick_get_ms() - time_start) < FLASH_DEFUALT_OPERATION_TIMEOUT) {
        check = spiflash->spi_receive(spiflash, cmd, addr, addr_size, &status, size);

        if ((check == ( int32_t ) size) && ((status & 0x01U) == 0U)) {
            ret = CSI_OK;
            break;
        }
    }

    return ret;
}

static int32_t spiflash_page_write(csi_spiflash_t *spiflash, uint32_t start_addr, void *data, uint32_t size)
{
    csi_spiflash_param_t *param;
    uint32_t addr, addr_size, data_size;
    uint8_t  cmd;
    int32_t  ret   = 0;
    uint32_t count = 0U;

    do {

        cmd       = FLASH_CMD_WRITE_ENABLE;
        addr      = 0U;
        addr_size = 0U;
        data_size = 0U;
        param     = (csi_spiflash_param_t *)spiflash->flash_prv_info;
        ret = spiflash->spi_send(spiflash, cmd, addr, addr_size, NULL, data_size);

        if (ret < 0) {
            break;
        }

        ret = flash_wait_ready(spiflash);

        if (ret < 0) {
            break;
        }

        cmd       = FLASH_CMD_PAGE_PROGRAM;
        addr      = start_addr;

        if (param->addr_mode == FLASH_ADDR_32) {
            addr_size = 4U;
        } else if (param->addr_mode == FLASH_ADDR_24) {
            addr_size = 3U;
        }

        data_size = size;
        ret = spiflash->spi_send(spiflash, cmd, addr, addr_size, data, data_size);

        if(ret < 0){
            break;
        }
        else {
            count = ( uint32_t )ret;
        }

        ret = flash_wait_ready(spiflash);
    } while (0);

    if( ret >= 0 ) {
        ret = ( int32_t )count;
    }

    return ret;
}

csi_error_t csi_spiflash_get_flash_info(csi_spiflash_t *spiflash, csi_spiflash_info_t *flash_info)
{
    CSI_PARAM_CHK(spiflash, CSI_ERROR);
    CSI_PARAM_CHK(flash_info, CSI_ERROR);

    csi_spiflash_param_t *param;
    csi_error_t  ret = CSI_OK;

    param = (csi_spiflash_param_t *)spiflash->flash_prv_info;

    if (param == NULL) {
        ret = CSI_ERROR;
    } else {
        flash_info->flash_name  = param->flash_name;
        flash_info->flash_id    = param->flash_id;
        flash_info->flash_size  = param->flash_size;
        flash_info->sector_size = param->sector_size;
        flash_info->page_size   = param->page_size;
        flash_info->xip_addr    = SPIFLASH_BASE;
    }

    return ret;
}


int32_t csi_spiflash_read(csi_spiflash_t *spiflash, uint32_t offset, void *data, uint32_t size)
{
    CSI_PARAM_CHK(spiflash, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);

    uint32_t addr, addr_size;
    uint8_t  cmd;
    int32_t  ret;

    cmd       = FLASH_CMD_READ_DATA;
    addr      = offset;
    addr_size = 3U;
    ret = spiflash->spi_receive(spiflash, cmd, addr, addr_size, data, size);

    return ret;
}


int32_t csi_spiflash_program(csi_spiflash_t *spiflash, uint32_t offset, const void *data, uint32_t size)
{
    CSI_PARAM_CHK(spiflash, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);

    int ret = 0;
    uint32_t end_addr, current_size, current_addr, count = 0U;
    uint8_t *program_data;
    csi_spiflash_param_t *param;

    program_data = (uint8_t *)data;
    param        = (csi_spiflash_param_t *)spiflash->flash_prv_info;

    /* calculation of the size between the write address and the end of the page */
    current_size = param->page_size - (offset % param->page_size);

    /* check if the size of the data is less than the remaining place in the page */
    if (current_size > size) {
        current_size = size;
    }

    /* initialize the adress variables */
    current_addr = offset;
    end_addr = offset + size;

    /* perform the write page by page */
    do {
        ret = spiflash_page_write(spiflash, current_addr, (void *)program_data, current_size);

        if (ret < 0) {
            break;
        }
        else{
            count += ( uint32_t )ret;
        }

        /* update the address and size variables for next page programming */
        current_addr += current_size;
        program_data += current_size;
        current_size = ((current_addr + param->page_size) > end_addr) ? (end_addr - current_addr) : param->page_size;
    } while (current_addr < end_addr);

    if( ret >= 0 ){
        ret = ( int32_t )count;
    }

    return ret;
}

csi_error_t csi_spiflash_erase(csi_spiflash_t *spiflash, uint32_t offset, uint32_t size)
{
    CSI_PARAM_CHK(spiflash, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);

    csi_spiflash_param_t *param;
    int32_t     ret = 0;
    uint32_t    addr, addr_size, data_size;
    uint8_t     cmd;

    param = (csi_spiflash_param_t *)spiflash->flash_prv_info;

    do{
        if (size % param->sector_size) {
            ret = CSI_ERROR;
            break;
        } else if (offset % param->sector_size) {
            ret = CSI_ERROR;
            break;
        }

        if (( offset == 0U ) && ( size == param->flash_size )){ /* chip erase */
            ret = spiflash->spi_send(spiflash, FLASH_CMD_WRITE_ENABLE, 0U, 0U, NULL, 0U);

            if (ret < 0) {
                break;
            }

            ret = flash_wait_ready(spiflash);

            if (ret < 0) {
                break;
            }

            ret = spiflash->spi_send(spiflash, FLASH_CMD_CHIP_ERASE, 0U, 0U, NULL, 0U);

            if (ret < 0) {
                break;
            }

            ret = flash_wait_ready(spiflash);

            if (ret < 0) {
                break;
            }
        }
        else{ /* sector erase */
            addr      = offset;

            do {
                ret = spiflash->spi_send(spiflash, FLASH_CMD_WRITE_ENABLE, 0U, 0U, NULL, 0U);

                if (ret < 0) {
                    break;
                }

                ret = flash_wait_ready(spiflash);

                if (ret < 0) {
                    break;
                }

                cmd       = FLASH_CMD_SECTOR_ERASE;
                addr_size = 3U;
                data_size = 0U;
                ret = spiflash->spi_send(spiflash, cmd, addr, addr_size, NULL, data_size);

                if (ret < 0) {
                    break;
                }

                ret = flash_wait_ready(spiflash);

                if (ret < 0) {
                    break;
                }

                addr += param->sector_size;
            } while (addr < (offset + size));
        }
    } while(0);

    return ( csi_error_t )ret;
}

csi_error_t csi_spiflash_read_reg(csi_spiflash_t *spiflash, uint8_t cmd_code, uint8_t *data, uint32_t size)
{
    CSI_PARAM_CHK(spiflash, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);

    int ret = 0;
    uint32_t addr, addr_size, data_size;
    uint8_t  cmd;

    cmd       = cmd_code;
    addr      = 0U;
    addr_size = 0U;
    data_size = size;
    ret = spiflash->spi_receive(spiflash, cmd, addr, addr_size, data, data_size);

    if (ret >= 0) {
        ret = CSI_OK;
    }

    return ( csi_error_t )ret;
}

csi_error_t csi_spiflash_write_reg(csi_spiflash_t *spiflash, uint8_t cmd_code, uint8_t *data, uint32_t size)
{
    CSI_PARAM_CHK(spiflash, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);

    uint32_t addr, addr_size, data_size;
    uint8_t  cmd;
    int  ret ;

    do {

        ret = spiflash->spi_send(spiflash, FLASH_CMD_WRITE_ENABLE, 0U, 0U, NULL, 0U);

        if (ret < 0) {
            ret = CSI_ERROR;
            break;
        }

        ret = flash_wait_ready(spiflash);

        if (ret < 0) {
            ret = CSI_ERROR;
            break;
        }

        cmd       = cmd_code;
        addr      = 0U;
        addr_size = 0U;
        data_size = size;
        ret = spiflash->spi_send(spiflash, cmd, addr, addr_size, data, data_size);

        if (ret < 0) {
            ret = CSI_ERROR;
            break;
        }

        ret = flash_wait_ready(spiflash);

        if (ret < 0) {
            ret = CSI_ERROR;
            break;
        }
    } while (0);

    return ( csi_error_t )ret;
}

static int is_top_protect_region(csi_spiflash_t *spiflash, uint32_t offset, uint32_t size)
{
    int i = 0;
    uint32_t start_addr, end_addr;
    uint32_t lock_start_addr, lock_end_addr;
    csi_spiflash_param_t *param;

    param      = (csi_spiflash_param_t *)spiflash->flash_prv_info;
    start_addr = offset;
    end_addr   = ( offset + size ) - 1U;

    /* Cheak whether protect region is belong to top protect region */
    lock_start_addr = param->flash_size - param->base_protect_size;
    lock_end_addr   = param->flash_size - 1U;

    do {
        i++;

        if ((start_addr == lock_start_addr) && (end_addr == lock_end_addr)) {
            break;
        }

        lock_start_addr = param->flash_size - (param->base_protect_size << i);
    } while (lock_start_addr >= (param->flash_size / 2U));

    if(lock_start_addr < (param->flash_size / 2U))
    {
        i = -1;
    }
    return i;
}

static int is_button_protect_region(csi_spiflash_t *spiflash, uint32_t offset, uint32_t size)
{
    int i = 0;
    uint32_t start_addr, end_addr;
    uint32_t lock_start_addr, lock_end_addr;
    csi_spiflash_param_t *param;

    param      = (csi_spiflash_param_t *)spiflash->flash_prv_info;
    start_addr = offset;
    end_addr   = ( offset + size ) - 1U;

    /* Cheak whether protect region is belong to button protect region */
    lock_start_addr = 0U;
    lock_end_addr   = param->base_protect_size;

    do {
        i++;

        if ((start_addr == lock_start_addr) && (end_addr == (lock_end_addr - 1U))) {
            break;
        }

        lock_end_addr = (param->base_protect_size << i);
    } while (lock_end_addr <= (param->flash_size / 2U));

    if(lock_end_addr > (param->flash_size / 2U)){
        i = -1;
    }

    return i;
}

static int spiflash_location_validate(csi_spiflash_t *spiflash, uint32_t offset, uint32_t size)
{
    csi_spiflash_param_t *param;
    int ret = -1;

    param = (csi_spiflash_param_t *)spiflash->flash_prv_info;

    if (is_top_protect_region(spiflash, offset, size) != -1) {
        ret = 0;
    } else if (is_button_protect_region(spiflash, offset, size) != -1) {
        ret = 0;
    } else if ((offset == 0U) && (size == param->flash_size)) {
        ret = 0;
    }

    return ret;
}


static int calculate_bp(csi_spiflash_t *spiflash, uint32_t offset, uint32_t size)
{
    int      bp = 0;
    int      tb = 0;
    int      ret;
    uint32_t bp_bits;
    csi_spiflash_param_t *param;

    param = (csi_spiflash_param_t *)spiflash->flash_prv_info;

    if ((ret = is_top_protect_region(spiflash, offset, size)) != -1) {
        bp  = ret;
        tb  = 0;
        ret = bp | (tb <<  ( int )param->bp_bits);
    } else if ((ret = is_button_protect_region(spiflash, offset, size)) != -1) {
        bp  = ret;
        tb  = 1;
        ret = bp | (tb << ( int )param->bp_bits);
    } else if ((offset == 0U) && (size == param->flash_size)) {
        bp_bits = param->bp_bits;

        while (bp_bits--) {
            bp <<= 1;
            bp |= 1;
        }

        ret = bp;
    } else {
        ret = -1;
    }

    return ret;
}

csi_error_t csi_spiflash_lock(csi_spiflash_t *spiflash, uint32_t offset, uint32_t size)
{
    CSI_PARAM_CHK(spiflash, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);

    int ret;
    uint8_t  bp;

    do {

        ret = spiflash_location_validate(spiflash, offset, size);

        if (ret == -1) {
            break;
        }

        ret = calculate_bp(spiflash, offset, size);

        if (ret == -1) {
            break;
        }

        bp = ( uint8_t )ret << FLASH_STATUS_BP_Pos;
        ret = csi_spiflash_write_reg(spiflash, FLASH_CMD_WRITE_STATUS, &bp, 1U);
    } while (0);

    return ( csi_error_t )ret;
}

csi_error_t csi_spiflash_unlock(csi_spiflash_t *spiflash, uint32_t offset, uint32_t size)
{
    CSI_PARAM_CHK(spiflash, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);

    int32_t  ret = 0;
    uint8_t  data;
    uint8_t  bp_msk  = 0U;
    uint8_t  bp_bits;
    csi_spiflash_param_t *param;

    param = (csi_spiflash_param_t *)spiflash->flash_prv_info;

    do {

        if (spiflash_location_validate(spiflash, offset, size) == -1) {
            ret = CSI_ERROR;
        } else if (csi_spiflash_is_locked(spiflash, offset, size)) {

            /* Calculate bp msk and tb msk */
            bp_bits = param->bp_bits;
            FLASH_STATUS_BP_Msk(bp_bits, bp_msk);
            bp_bits = param->bp_bits;
            bp_msk |= FLASH_STATUS_TB_Msk(bp_bits);

            /* Clear bp bits and tb bits */
            ret = spiflash->spi_receive(spiflash, FLASH_CMD_READ_STATUS1, 0U, 0U, &data, 1U);

            if (ret < 0) {
                ret = CSI_ERROR;
                break;
            }

            data &= ~bp_msk;
            ret = spiflash->spi_send(spiflash, FLASH_CMD_WRITE_ENABLE, 0U, 0U, NULL, 0U);

            if (ret < 0) {
                ret = CSI_ERROR;
                break;
            }

            ret = flash_wait_ready(spiflash);

            if (ret < 0) {
                ret = CSI_ERROR;
                break;
            }

            ret = csi_spiflash_write_reg(spiflash, FLASH_CMD_WRITE_STATUS, &data, 1U);
        }
    } while (0);

    return ( csi_error_t )ret;
}


int csi_spiflash_is_locked(csi_spiflash_t *spiflash, uint32_t offset, uint32_t size)
{
    CSI_PARAM_CHK(spiflash, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);

    int ret;
    uint8_t  bp;
    uint8_t  status;
    uint8_t  bp_msk  = 0U;
    uint8_t  bp_bits;
    csi_spiflash_param_t *param;

    do {
        param = (csi_spiflash_param_t *)spiflash->flash_prv_info;
        ret = spiflash_location_validate(spiflash, offset, size);

        if (ret == -1) {
            ret = 0;
            break;
        }

        /* Calculate bp value */
        ret = calculate_bp(spiflash, offset, size);

        if (ret == -1) {
            ret = 0;
            break;
        }

        bp = ( uint8_t )ret << FLASH_STATUS_BP_Pos;

        ret = spiflash->spi_receive(spiflash, FLASH_CMD_READ_STATUS1, 0U, 0U, &status, 1U);
        if (ret < 0) {
            ret = CSI_ERROR;
            break;
        }

        /* Calculate bp msk and tb msk */
        bp_bits = param->bp_bits;
        FLASH_STATUS_BP_Msk(bp_bits, bp_msk);
        bp_bits = param->bp_bits;
        bp_msk |= FLASH_STATUS_TB_Msk(bp_bits);

        if ((status & bp_msk) == (bp & bp_msk)) {
            ret = 1;
        } else {
            ret = 0;
        }
    } while (0);

    return ret;
}

csi_error_t csi_spiflash_config_data_line(csi_spiflash_t *spiflash, csi_spiflash_data_line_t line)
{
    CSI_PARAM_CHK(spiflash, CSI_ERROR);

    int32_t ret = 0;
    csi_spiflash_param_t *param;
    void *temp;
    uint8_t status[2];

    param = (csi_spiflash_param_t *)spiflash->flash_prv_info;
    temp = status;

    do {

        /* config spiflash periphrial data line */
        switch (line) {
            case SPIFLASH_DATA_1_LINE:
                break;

            case SPIFLASH_DATA_2_LINES:
            case SPIFLASH_DATA_4_LINES:

                ret = spiflash->spi_receive(spiflash, FLASH_CMD_READ_STATUS1, 0U, 0U, &status[0], 1U);

                if (ret < 0) {
                    ret = CSI_ERROR;
                    break;
                }

                ret = spiflash->spi_receive(spiflash, FLASH_CMD_READ_STATUS2, 0U, 0U, &status[1], 1U);

                if (ret < 0) {
                    ret = CSI_ERROR;
                    break;
                }

                if(param->qe_pos == 1U){
                    // Used to adapte GDxxx series SPIFLASH
                    status[1] |= ((uint8_t)0x1U << param->qe_pos);
                    ret = csi_spiflash_write_reg(spiflash, 0x31U, &status[1], 1U);
                } else {
                    *(uint16_t *) temp |= ((uint16_t)0x1U << param->qe_pos);
                    ret = csi_spiflash_write_reg(spiflash, 0x01U, status, 2U);
                }

                break;

            default:
                ret = CSI_ERROR;
                break;
        }

        if(ret == 0){
            /* config bus data line*/
            ret = spiflash_config_data_line(spiflash, line);
        }
    } while (0);

    return ( csi_error_t )ret;
}

uint32_t csi_spiflash_frequence(csi_spiflash_t *spiflash, uint32_t hz)
{
    CSI_PARAM_CHK(spiflash, 0U);

    return csi_qspi_frequence(&spiflash->spi_qspi.qspi, hz);
}

void csi_spiflash_power_down(csi_spiflash_t *spiflash)
{
    uint32_t addr, addr_size, data_size;
    uint8_t  cmd;

    cmd       = FLASH_CMD_WRITE_ENABLE;
    addr      = 0U;
    addr_size = 0U;
    data_size = 0U;
    spiflash->spi_send(spiflash, cmd, addr, addr_size, NULL, data_size);
    flash_wait_ready(spiflash);

    cmd       = FALSH_CMD_POWER_DOWN;
    addr      = 0U;
    addr_size = 0U;
    data_size = 0U;
    spiflash->spi_send(spiflash, cmd, addr, addr_size, NULL, data_size);
}

csi_error_t csi_spiflash_release_power_down(csi_spiflash_t *spiflash)
{
    uint32_t addr, addr_size, data_size;
    uint8_t  cmd;

    cmd       = FALSH_CMD_RELEASE_POWER_DOWN;
    addr      = 0U;
    addr_size = 0U;
    data_size = 0U;
    spiflash->spi_send(spiflash, cmd, addr, addr_size, NULL, data_size);
    return ( csi_error_t )flash_wait_ready(spiflash);
}
#if 0
ATTRIBUTE_DATA void drv_spiflash_continues_read_mode(csi_spiflash_t *spiflash, bool enable)
{
    csi_qspi_t *qspi =&spiflash->spi_qspi.qspi;
    cd_qspi_regs_t *qspi_base = (cd_qspi_regs_t *)HANDLE_REG_BASE(qspi);

    if(enable) {
        cd_qspi_config_mode_byte(qspi_base, 0x20U);
        cd_qspi_enter_xip_mode(qspi_base);
    } else {
        // exit continues read mode
        cd_qspi_config_mode_byte(qspi_base, 0U);
        cd_qspi_exit_xip_mode(qspi_base);
        for(uint32_t i = 0U; i < 300U; i++){
            *(volatile uint32_t *)SPIFLASH_BASE;
        }
    }
}
#endif
