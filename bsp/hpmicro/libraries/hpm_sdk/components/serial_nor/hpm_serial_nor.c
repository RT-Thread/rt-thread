/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_serial_nor.h"
#include "hpm_clock_drv.h"

#ifndef SERIALNOR_CMD_PAGE_PROGRAM_1_1_4_3B
#define SERIALNOR_CMD_PAGE_PROGRAM_1_1_4_3B      (0x32U)
#endif

#ifndef SERIALNOR_CMD_READ_SDR_1_2_2_4B
#define SERIALNOR_CMD_READ_SDR_1_2_2_4B           (0xBCU)
#endif

#ifndef SERIALNOR_CMD_READ_SDR_1_2_2_3B
#define SERIALNOR_CMD_READ_SDR_1_2_2_3B           (0xBBU)
#endif

#ifndef SERIALNOR_CMD_READ_SDR_1_1_2_3B
#define SERIALNOR_CMD_READ_SDR_1_1_2_3B           (0x3BU)
#endif

#ifndef SERIALNOR_CMD_READ_SDR_1_1_2_4B
#define SERIALNOR_CMD_READ_SDR_1_1_2_4B           (0x3CU)
#endif

#ifndef SERIALNOR_CMD_WRITE_STATUS_REG3
#define SERIALNOR_CMD_WRITE_STATUS_REG3           (0x11U)
#endif

#ifndef SERIALNOR_CMD_READ_STATUS_REG3
#define SERIALNOR_CMD_READ_STATUS_REG3            (0x15U)
#endif

#ifndef kSERIALNOR_CMD_WRITE_STATUS_REG2_VIA_0X31
#define kSERIALNOR_CMD_WRITE_STATUS_REG2_VIA_0X31  (0x31U)
#endif


#ifndef kSERIALNOR_CMD_READ_STATUS_REG2_VIA_0X31
#define kSERIALNOR_CMD_READ_STATUS_REG2_VIA_0X31   (0x35U)
#endif


#define MAX_24BIT_ADDRESSING_SIZE               ((1UL << 24))
#define MAX_24BIT_ADDR_SIZE_IN_KBYTES           ((1UL << 24) / SIZE_1KB)

#define SPI_READ_SFDP_FREQUENCY                  (10000000U)

/**
 * @brief QE bit enable sequence option
 */
typedef enum {
    spi_nor_quad_en_auto_or_ignore = 0U,                        /**< Auto enable or ignore */
    spi_nor_quad_en_set_bit6_in_status_reg1 = 1U,               /**< QE bit is at bit6 in Status register 1 */
    spi_nor_quad_en_set_bit1_in_status_reg2 = 2U,               /**< QE bit is at bit1 in Status register 2 register 2 */
    spi_nor_quad_en_set_bit7_in_status_reg2 = 3U,               /**< QE bit is at bit7 in Status register 2 */
    spi_nor_quad_en_set_bi1_in_status_reg2_via_0x31_cmd = 4U,   /**< QE bit is in status register 2 and configured by CMD 0x31 */
} spi_nor_quad_enable_seq_t;

static hpm_stat_t hpm_serial_nor_read_sfdp_info(hpm_serial_nor_t *flash, jedec_info_table_t *tbl, bool address_shift_enable);
static hpm_stat_t hpm_spi_get_read_para(hpm_serial_nor_t *flash, jedec_info_table_t *jedec_info);
static hpm_stat_t hpm_spi_get_program_para(hpm_serial_nor_t *flash, jedec_info_table_t *jedec_info);
static hpm_stat_t hpm_spi_nor_read_sfdp(hpm_serial_nor_t *flash, uint32_t addr,
                                        uint32_t *buffer, uint32_t bytes);
static hpm_stat_t hpm_spi_nor_set_command(hpm_serial_nor_t *flash, uint8_t cmd);
static hpm_stat_t get_page_sector_block_size_from_sfdp(hpm_serial_nor_info_t *config, jedec_info_table_t *tbl);
static hpm_stat_t hpm_spi_nor_read_status_register(hpm_serial_nor_t *flash, uint8_t *reg_data, uint8_t status_reg);
static hpm_stat_t hpm_spi_nor_write_status_register(hpm_serial_nor_t *flash, uint8_t reg_data, uint8_t status_reg);
static hpm_stat_t prepare_quad_mode_enable_sequence(hpm_serial_nor_t *flash, jedec_info_table_t *jedec_info);

__attribute__((weak)) void hpm_spi_nor_udelay(uint32_t us)
{
    clock_cpu_delay_us(us);
}

static hpm_stat_t hpm_spi_get_read_para(hpm_serial_nor_t *flash, jedec_info_table_t *jedec_info)
{
    uint32_t address_bits;
    uint32_t dummy_cycles = 0;
    uint8_t mode_cycles = 0;
    uint8_t dummy_count = 0;
    jedec_flash_param_table_t *param_tbl = &jedec_info->flash_param_tbl;
    jedec_4byte_addressing_inst_table_t *flash_4b_tbl = &jedec_info->flash_4b_inst_tbl;
    flash->nor_read_para.data_phase_format = quad_io_mode;
    flash->nor_read_para.addr_phase_format = single_io_mode;
    flash->nor_read_para.data_dummy_count = 1;
    address_bits = (flash->flash_info.size_in_kbytes > MAX_24BIT_ADDR_SIZE_IN_KBYTES) ? 32U : 24U;
    if (address_bits == 32) {
        flash->nor_read_para.addr_bit = flash_addrlen_32bit;
    } else {
        flash->nor_read_para.addr_bit = flash_addrlen_24bit;
    }

    if (flash->host.host_param.flags & SERIAL_NOR_HOST_SUPPORT_QUAD_IO_MODE) {
        if (address_bits == 24U) {
            if (param_tbl->misc.supports_1_4_4_fast_read != 0U) {
                flash->nor_read_para.read_cmd = param_tbl->read_1_4_info.inst_1_4_4_read;
            } else if (param_tbl->misc.support_1_1_4_fast_read != 0U) {
                flash->nor_read_para.read_cmd = param_tbl->read_1_4_info.inst_1_1_4_read;
            } else {
                flash->nor_read_para.read_cmd = SERIALNOR_CMD_BASICREAD_3B;
                dummy_cycles = 0;
                mode_cycles = 0;
            }
        } else {
            if (jedec_info->has_4b_addressing_inst_table) {
                if (flash_4b_tbl->cmd_4byte_support_info.support_1_4_4_fast_read != 0U) {
                    flash->nor_read_para.read_cmd = SERIALNOR_CMD_READ_SDR_1_4_4_4B;
                    flash->nor_read_para.addr_phase_format = quad_io_mode;
                } else if (flash_4b_tbl->cmd_4byte_support_info.support_1_1_4_fast_read != 0U) {
                    flash->nor_read_para.read_cmd = SERIALNOR_CMD_READ_SDR_1_1_4_4B;
                } else {
                    flash->nor_read_para.read_cmd = SERIALNOR_CMD_BASICREAD_4B;
                    dummy_cycles = 0;
                    mode_cycles = 0;
                }
            } else if (param_tbl->misc.supports_1_4_4_fast_read != 0U) { /* For device that is only compliant with JESD216 */
                flash->nor_read_para.read_cmd = SERIALNOR_CMD_READ_SDR_1_4_4_4B;
            } else if (param_tbl->misc.support_1_1_4_fast_read != 0U) {
                flash->nor_read_para.read_cmd = SERIALNOR_CMD_READ_SDR_1_1_4_4B;
            } else {
                flash->nor_read_para.read_cmd = SERIALNOR_CMD_BASICREAD_4B;
                dummy_cycles = 0;
                mode_cycles = 0;
            }
        }
    } else if (flash->host.host_param.flags & SERIAL_NOR_HOST_SUPPORT_DUAL_IO_MODE) {
        if (address_bits == 24U) {
            if (param_tbl->misc.support_1_2_2_fast_read != 0U) {
                flash->nor_read_para.read_cmd = param_tbl->read_1_2_info.inst_1_2_2_read;
                flash->nor_read_para.data_phase_format = dual_io_mode;
            } else if (param_tbl->misc.support_1_1_2_fast_read != 0U) {
                flash->nor_read_para.read_cmd = param_tbl->read_1_2_info.inst_1_1_2_read;
            } else {
                flash->nor_read_para.read_cmd = SERIALNOR_CMD_BASICREAD_3B;
                dummy_cycles = 0;
                mode_cycles = 0;
            }
        } else {
            if (jedec_info->has_4b_addressing_inst_table) {
                if (flash_4b_tbl->cmd_4byte_support_info.support_1_2_2_fast_read != 0U) {
                    flash->nor_read_para.read_cmd = SERIALNOR_CMD_READ_SDR_1_2_2_4B;
                    flash->nor_read_para.data_phase_format = dual_io_mode;
                } else if (flash_4b_tbl->cmd_4byte_support_info.support_1_1_2_fast_read != 0U) {
                    flash->nor_read_para.read_cmd = SERIALNOR_CMD_READ_SDR_1_1_2_4B;
                    flash->nor_read_para.data_phase_format = dual_io_mode;
                } else {
                    flash->nor_read_para.data_phase_format = single_io_mode;
                    flash->nor_read_para.read_cmd = SERIALNOR_CMD_BASICREAD_4B;
                    dummy_cycles = 0;
                    mode_cycles = 0;
                }
            } else if (param_tbl->misc.support_1_2_2_fast_read != 0U) { /* For device that is only compliant with JESD216 */
                flash->nor_read_para.read_cmd = SERIALNOR_CMD_READ_SDR_1_2_2_4B;
                flash->nor_read_para.data_phase_format = dual_io_mode;
            } else if (param_tbl->misc.support_1_1_2_fast_read != 0U) {
                flash->nor_read_para.read_cmd = SERIALNOR_CMD_READ_SDR_1_1_2_4B;
                flash->nor_read_para.data_phase_format = dual_io_mode;
            } else {
                flash->nor_read_para.data_phase_format = single_io_mode;
                flash->nor_read_para.read_cmd = SERIALNOR_CMD_BASICREAD_4B;
                dummy_cycles = 0;
                mode_cycles = 0;
            }
        }

    } else {
        flash->nor_read_para.read_cmd = (address_bits == 32U) ? SERIALNOR_CMD_BASICREAD_4B : SERIALNOR_CMD_BASICREAD_3B;
        flash->nor_read_para.data_phase_format = single_io_mode;
        flash->nor_read_para.data_dummy_count = 0;
        dummy_cycles = 0;
        mode_cycles = 0;
    }

    /* Determine Read command based on SFDP */
    if (flash->host.host_param.flags & SERIAL_NOR_HOST_SUPPORT_QUAD_IO_MODE) {
        if (param_tbl->misc.supports_1_4_4_fast_read != 0U) {
            flash->nor_read_para.addr_phase_format = quad_io_mode;
            mode_cycles = param_tbl->read_1_4_info.mode_clocks_1_4_4_read;
            dummy_cycles = param_tbl->read_1_4_info.dummy_clocks_1_4_4_read;
        } else if (param_tbl->misc.support_1_1_4_fast_read != 0U) {
            mode_cycles = param_tbl->read_1_4_info.mode_clocks_1_1_4_read;
            dummy_cycles = param_tbl->read_1_4_info.dummy_clocks_1_1_4_read;
        } else {
            /* Reserved for future use */
        }
    } else if (flash->host.host_param.flags & SERIAL_NOR_HOST_SUPPORT_DUAL_IO_MODE) {
        if (param_tbl->misc.support_1_2_2_fast_read != 0U) {
            flash->nor_read_para.addr_phase_format = dual_io_mode;
            mode_cycles = param_tbl->read_1_2_info.mode_clocks_1_2_2_read;
            dummy_cycles = param_tbl->read_1_2_info.dummy_clocks_1_2_2_read;
        } else if (param_tbl->misc.support_1_1_2_fast_read != 0U) {
            flash->nor_read_para.addr_phase_format = single_io_mode;
            mode_cycles = param_tbl->read_1_2_info.mode_clocks_1_1_2_read;
            dummy_cycles = param_tbl->read_1_2_info.dummy_clocks_1_1_2_read;
        } else {
            /* Reserved for future use */
        }
    }

    if ((dummy_cycles) && (!(flash->host.host_param.flags & SERIAL_NOR_HOST_SUPPORT_SINGLE_IO_MODE))) {
        if (flash->host.host_param.flags & SERIAL_NOR_HOST_SUPPORT_DUAL_IO_MODE) {
            dummy_count = ((dummy_cycles + mode_cycles) / 4);
        } else {
            dummy_count = ((dummy_cycles + mode_cycles) / 2);
        }
        /* SPI is only support 4 dummy count*/
        if (dummy_count > 5) {
            flash->nor_read_para.data_phase_format = single_io_mode;
            flash->nor_read_para.addr_phase_format = single_io_mode;
            flash->nor_read_para.read_cmd = (address_bits == 32U) ? SERIALNOR_CMD_BASICREAD_4B : SERIALNOR_CMD_BASICREAD_3B;
        } else {
            flash->nor_read_para.data_dummy_count = dummy_count;
        }
    }
    return status_success;
}

static hpm_stat_t hpm_spi_get_program_para(hpm_serial_nor_t *flash, jedec_info_table_t *jedec_info)
{
    jedec_4byte_addressing_inst_table_t *flash_4b_tbl;
    flash_4b_tbl = &jedec_info->flash_4b_inst_tbl;
    flash->nor_program_para.has_4b_addressing_inst_table = jedec_info->has_4b_addressing_inst_table;
    flash->nor_program_para.support_1_1_4_page_program = flash_4b_tbl->cmd_4byte_support_info.support_1_1_4_page_program;
    flash->nor_program_para.support_1_4_4_page_program = flash_4b_tbl->cmd_4byte_support_info.support_1_4_4_page_program;
    return status_success;
}

static hpm_stat_t hpm_spi_nor_read_sfdp(hpm_serial_nor_t *flash, uint32_t addr, uint32_t *buffer, uint32_t bytes)
{
    hpm_serial_nor_transfer_seq_t command_seq = {0};
    command_seq.use_dma = false;
    command_seq.cmd_phase.cmd = SERIAL_FLASH_READ_SFDP;
    command_seq.addr_phase.addr = addr;
    command_seq.addr_phase.enable = true;
    command_seq.addr_phase.addr_bit = flash_addrlen_24bit;
    command_seq.addr_phase.addr_io_mode = single_io_mode;
    command_seq.dummy_phase.dummy_count = 1;
    command_seq.data_phase.direction = read_direction;
    command_seq.data_phase.data_io_mode = single_io_mode;
    command_seq.data_phase.buf = (uint8_t *)buffer;
    command_seq.data_phase.len = bytes;
    return flash->host.host_ops.transfer(flash->host.host_ops.user_data, &command_seq);
}

static hpm_stat_t hpm_spi_nor_set_command(hpm_serial_nor_t *flash, uint8_t cmd)
{
    hpm_serial_nor_transfer_seq_t command_seq = {0};
    command_seq.use_dma = false;
    command_seq.cmd_phase.cmd = cmd;
    return flash->host.host_ops.transfer(flash->host.host_ops.user_data, &command_seq);
}

static hpm_stat_t get_page_sector_block_size_from_sfdp(hpm_serial_nor_info_t *config, jedec_info_table_t *tbl)
{
    hpm_stat_t status = status_invalid_argument;
    jedec_flash_param_table_t *param_tbl = &tbl->flash_param_tbl;
    jedec_4byte_addressing_inst_table_t *flash_4b_tbl = &tbl->flash_4b_inst_tbl;

    /* Calculate Flash Size */
    uint32_t flash_size;
    uint32_t flash_density = tbl->flash_param_tbl.flash_density;
    uint32_t page_size;
    uint32_t sector_size = 0xFFFFFFUL;
    uint32_t block_size = 0U;
    uint32_t block_erase_type = 0U;
    uint32_t sector_erase_type = 0U;

    if (IS_HPM_BIT_SET(flash_density, 31)) {
        /* Flash size >= 4G bits */
        flash_size = 1UL << ((flash_density & ~(1UL << 0x1F)) - 3U);
    } else {
        /* Flash size < 4G bits */
        flash_size = (flash_density + 1U) >> 3;
    }

    do {
        HPM_BREAK_IF(flash_size < 1U);
        config->size_in_kbytes = flash_size / SIZE_1KB;
        /* Calculate Page size */
        if (tbl->flash_param_tbl_size < SFDP_BASIC_PROTOCOL_TABLE_SIZE_REVA) {
            config->page_size = 256U;
        } else {
            page_size = 1UL << (param_tbl->chip_erase_progrm_info.page_size);
            config->page_size = (page_size == (1UL << 15)) ? 256U : page_size;
        }
        /* Calculate Sector Size */
        for (uint32_t index = 0; index < 4U; index++) {
            if (param_tbl->erase_info[index].size != 0U) {
                uint32_t current_erase_size = 1UL << param_tbl->erase_info[index].size;
                if (current_erase_size < SIZE_1KB) {
                    continue;
                }
                if (current_erase_size < sector_size) {
                    sector_size = current_erase_size;
                    sector_erase_type = index;
                }
                if ((current_erase_size > block_size) && (current_erase_size < (1024U * 1024U))) {
                    block_size = current_erase_size;
                    block_erase_type = index;
                }
            }
        }

        config->sector_size_kbytes = sector_size / SIZE_1KB;

        config->block_size_kbytes = block_size / SIZE_1KB;

        if (flash_size > MAX_24BIT_ADDRESSING_SIZE) {
            if (tbl->has_4b_addressing_inst_table) {
                config->sector_erase_cmd = flash_4b_tbl->erase_inst_info.erase_inst[sector_erase_type];
                config->block_erase_cmd = flash_4b_tbl->erase_inst_info.erase_inst[block_erase_type];
            } else {
                switch (param_tbl->erase_info[sector_erase_type].inst) {
                case SERIALNOR_CMD_SE4K_3B:
                    config->sector_erase_cmd = SERIALNOR_CMD_SE4K_4B;
                    break;
                case SERIALNOR_CMD_SE64K_3B:
                    config->sector_erase_cmd = SERIALNOR_CMD_SE64K_4B;
                    break;
                default:
                    /* Reserved for future use */
                    break;
                }
                switch (param_tbl->erase_info[block_erase_type].inst) {
                case SERIALNOR_CMD_SE4K_3B:
                    config->block_erase_cmd = SERIALNOR_CMD_SE4K_4B;
                    break;
                case SERIALNOR_CMD_SE64K_3B:
                    config->block_erase_cmd = SERIALNOR_CMD_SE64K_4B;
                    break;
                default:
                    /* Reserved for future use */
                    break;
                }
            }
        } else {
            config->sector_erase_cmd = param_tbl->erase_info[sector_erase_type].inst;
            config->block_erase_cmd = param_tbl->erase_info[block_erase_type].inst;
        }

        status = status_success;

    } while (false);

    return status;
}

static hpm_stat_t hpm_spi_nor_read_status_register(hpm_serial_nor_t *flash, uint8_t *reg_data, uint8_t status_reg)
{
    hpm_serial_nor_transfer_seq_t command_seq = {0};
    command_seq.use_dma = false;
    command_seq.cmd_phase.cmd = status_reg;
    command_seq.data_phase.direction = read_direction;
    command_seq.data_phase.buf = reg_data;
    command_seq.data_phase.data_io_mode = single_io_mode;
    command_seq.data_phase.len = sizeof(uint8_t);
    return flash->host.host_ops.transfer(flash->host.host_ops.user_data, &command_seq);
}

static hpm_stat_t hpm_spi_nor_write_status_register(hpm_serial_nor_t *flash, uint8_t reg_data, uint8_t status_reg)
{
    hpm_stat_t stat;
    hpm_serial_nor_transfer_seq_t command_seq = {0};
    stat = status_spi_nor_flash_is_busy;
    while (stat == status_spi_nor_flash_is_busy) {
        stat = hpm_serial_nor_is_busy(flash);
        if ((stat != status_success) && (stat != status_spi_nor_flash_is_busy)) {
            return stat;
        } else {
            if (stat == status_success) {
                break;
            } else {
                if (stat == status_success) {
                    break;
                } else {
                    hpm_spi_nor_udelay(1);
                }
            }
        }
    }

    stat = hpm_serial_nor_write_enable(flash);
    if (stat != status_success) {
        return stat;
    }
    command_seq.use_dma = false;
    command_seq.cmd_phase.cmd = status_reg;
    command_seq.data_phase.direction = write_direction;
    command_seq.data_phase.buf = (uint8_t *)&reg_data;
    command_seq.data_phase.data_io_mode = single_io_mode;
    command_seq.data_phase.len = sizeof(uint8_t);
    return flash->host.host_ops.transfer(flash->host.host_ops.user_data, &command_seq);
}

static hpm_stat_t prepare_quad_mode_enable_sequence(hpm_serial_nor_t *flash, jedec_info_table_t *jedec_info)
{
    hpm_stat_t status = status_success;
    uint8_t status_val = 0;
    uint8_t read_status_reg = 0;
    uint8_t write_status_reg = 0;
    /* See JESD216B 6.4.18 for more details. */
    do {
        /* Enter Quad mode */
        spi_nor_quad_enable_seq_t enter_quad_mode_option = spi_nor_quad_en_auto_or_ignore;
        /* Ideally, we only need one condition here, however, for some Flash devices that actually support JESD216A
         *  before the standard is publicly released, the JESD minor revision is still the initial version. That is why
         *  we use two conditions to handle below logic.
         */
        if ((jedec_info->standard_version >= SFDP_VERSION_MINOR_A) ||
            (jedec_info->flash_param_tbl_size >= SFDP_BASIC_PROTOCOL_TABLE_SIZE_REVA)) {
            switch (jedec_info->flash_param_tbl.mode_4_4_info.quad_enable_requirement) {
            case 1:
            case 4:
            case 5:
                enter_quad_mode_option = spi_nor_quad_en_set_bit1_in_status_reg2;
                break;
            case 6:
                enter_quad_mode_option = spi_nor_quad_en_set_bi1_in_status_reg2_via_0x31_cmd;
                break;
            case 2:
                enter_quad_mode_option = spi_nor_quad_en_set_bit6_in_status_reg1;
                break;
            case 3:
                enter_quad_mode_option = spi_nor_quad_en_set_bit7_in_status_reg2;
                break;
            default:
                enter_quad_mode_option = spi_nor_quad_en_auto_or_ignore;
                flash->flash_info.en_dev_mode_cfg = 0;
                break;
            }
        } else {
            /* Device does not have a QE bit. Device detects 1-1-4 and 1-4-4 reads based on instruction */
            enter_quad_mode_option = spi_nor_quad_en_auto_or_ignore;
            status = status_spi_nor_flash_not_qe_bit_in_sfdp;
        }
        /* Retrieve the read status command */
        if (enter_quad_mode_option != spi_nor_quad_en_auto_or_ignore) {

            switch (enter_quad_mode_option) {
            case spi_nor_quad_en_set_bit1_in_status_reg2:
            case spi_nor_quad_en_set_bi1_in_status_reg2_via_0x31_cmd:
                read_status_reg = kSERIALNOR_CMD_READ_STATUS_REG2_VIA_0X31;
                break;
            case spi_nor_quad_en_set_bit6_in_status_reg1:
                read_status_reg = SERIALNOR_CMD_READ_STATUS_REG1;
                break;
            case spi_nor_quad_en_set_bit7_in_status_reg2:
                read_status_reg = SERIALNOR_CMD_READ_STATUS_REG2;
                break;
            default:
                /* Reserved for future use */
                break;
            }
            status = hpm_spi_nor_read_status_register(flash, &status_val, read_status_reg);
            HPM_BREAK_IF(status != status_success);

            /* Do modify-after-read status and then create Quad mode Enable sequence
             * Enable QE bit only if it is not enabled.
             */
            flash->flash_info.en_dev_mode_cfg = 0;
            switch (enter_quad_mode_option) {
            case spi_nor_quad_en_set_bit6_in_status_reg1:
                if (!IS_HPM_BIT_SET(status_val, 6)) {
                    write_status_reg = SERIALNOR_CMD_WRITE_STATUS_REG1;
                    status_val &= (uint8_t) ~0x3cU; /* Clear Block protection */
                    status_val |= HPM_BITSMASK(1U, 6);
                    status = hpm_spi_nor_write_status_register(flash, status_val, write_status_reg);
                    HPM_BREAK_IF(status != status_success);
                    flash->flash_info.en_dev_mode_cfg = 1U;
                }
                break;
            case spi_nor_quad_en_set_bit1_in_status_reg2:
                if (!IS_HPM_BIT_SET(status_val, 1)) {
                    write_status_reg = SERIALNOR_CMD_WRITE_STATUS_REG1;
                    status_val |= HPM_BITSMASK(1U, 1);
                    /* QE bit will be programmed after status1 register, so need to left shit 8 bit */
                    status_val <<= 8;
                    status = hpm_spi_nor_write_status_register(flash, status_val, write_status_reg);
                    HPM_BREAK_IF(status != status_success);
                    flash->flash_info.en_dev_mode_cfg = 1U;
                }
                break;
            case spi_nor_quad_en_set_bi1_in_status_reg2_via_0x31_cmd:
                if (!IS_HPM_BIT_SET(status_val, 1)) {
                    write_status_reg = kSERIALNOR_CMD_WRITE_STATUS_REG2_VIA_0X31;
                    status_val |= HPM_BITSMASK(1U, 1);
                    status = hpm_spi_nor_write_status_register(flash, status_val, write_status_reg);
                    HPM_BREAK_IF(status != status_success);
                    flash->flash_info.en_dev_mode_cfg = 1U;
                }
                break;
            case spi_nor_quad_en_set_bit7_in_status_reg2:
                if (!IS_HPM_BIT_SET(status_val, 7)) {
                    write_status_reg = SERIALNOR_CMD_WRITE_STATUS_REG2;
                    status_val |= HPM_BITSMASK(1U, 7);
                    status = hpm_spi_nor_write_status_register(flash, status_val, write_status_reg);
                    HPM_BREAK_IF(status != status_success);
                    flash->flash_info.en_dev_mode_cfg = 1U;
                }
                break;
            default:
                flash->flash_info.en_dev_mode_cfg = 0U;
                break;
            }
        }
    } while (false);

    return status;
}

static hpm_stat_t hpm_serial_nor_read_sfdp_info(hpm_serial_nor_t *flash, jedec_info_table_t *tbl, bool address_shift_enable)
{
    hpm_stat_t status = status_spi_nor_sfdp_not_found;
    do {
        sfdp_header_t sfdp_header;
        uint32_t address;
        uint32_t parameter_header_number;
        uint32_t max_hdr_count;
        uint32_t parameter_id;
        uint32_t table_size;

        status = hpm_spi_nor_read_sfdp(flash, 0, &sfdp_header.words[0], sizeof(sfdp_header));
        HPM_BREAK_IF(status != status_success);

        if (sfdp_header.signature != SFDP_SIGNATURE) {
            status = status_spi_nor_sfdp_not_found;
            break;
        }

        parameter_header_number = (uint32_t) sfdp_header.param_hdr_num + 1U;

        sfdp_parameter_header_t sfdp_param_hdrs[10];
        (void) memset(&sfdp_param_hdrs, 0, sizeof(sfdp_param_hdrs));
        max_hdr_count = parameter_header_number > 10U ? 10U : parameter_header_number;
        address = 0x08U;
        if (address_shift_enable) {
            address <<= 8;
        }
        status = hpm_spi_nor_read_sfdp(flash, address, &sfdp_param_hdrs[0].words[0],
                                   max_hdr_count * sizeof(sfdp_parameter_header_t));
        HPM_BREAK_IF(status != status_success);

        (void) memset(tbl, 0, sizeof(*tbl));

        /* Save the standard version for later use. */
        tbl->standard_version = sfdp_header.minor_rev;

        for (uint32_t i = 0; i < max_hdr_count; i++) {
            parameter_id = sfdp_param_hdrs[i].parameter_id_lsb + ((uint32_t) sfdp_param_hdrs[i].parameter_id_msb << 8);

            if ((parameter_id == PARAMETER_ID_BASIC_SPIPROTOCOL) ||
                (parameter_id == PARAMETER_ID_4BYTEADDRESS_INSTRUCTION_TABLE) ||
                (parameter_id == PARAMETER_ID_CMDSEQ_CHANGE_TO_OCTAL_DDR) ||
                (parameter_id == PARAMETER_ID_XSPIPROFILE1_0) || (parameter_id == PARAMETER_ID_STACTRLCFGREGMAP)) {
                address = 0;
                for (int32_t index = 2; index >= 0; index--) {
                    address <<= 8;
                    address |= sfdp_param_hdrs[i].parameter_table_pointer[index];
                }
                table_size = (uint32_t) sfdp_param_hdrs[i].table_length_in_32bit * sizeof(uint32_t);

                if (address_shift_enable) {
                    address <<= 8;
                }

                if (parameter_id == PARAMETER_ID_BASIC_SPIPROTOCOL) {
                    /* Limit table size to the max supported standard */
                    if (table_size > sizeof(jedec_flash_param_table_t)) {
                        table_size = sizeof(jedec_flash_param_table_t);
                    }
                    status = hpm_spi_nor_read_sfdp(flash, address, &tbl->flash_param_tbl.words[0], table_size);
                    HPM_BREAK_IF(status != status_success);

                    tbl->flash_param_tbl_size = table_size;
                } else if (parameter_id == PARAMETER_ID_4BYTEADDRESS_INSTRUCTION_TABLE) {
                    status = hpm_spi_nor_read_sfdp(flash, address, &tbl->flash_4b_inst_tbl.words[0], table_size);
                    HPM_BREAK_IF(status != status_success);

                    tbl->has_4b_addressing_inst_table = true;
                } else if (parameter_id == PARAMETER_ID_CMDSEQ_CHANGE_TO_OCTAL_DDR) {
                    status = hpm_spi_nor_read_sfdp(flash, address, &tbl->otcal_ddr_mode_enable_sequence.words[0],
                                               sizeof(jedec_cmd_sequence_change_to_octal_mode_t));
                    HPM_BREAK_IF(status != status_success);

                    tbl->has_otcal_ddr_mode_enable_sequence_table = true;
                } else if (parameter_id == PARAMETER_ID_XSPIPROFILE1_0) {
                    status = hpm_spi_nor_read_sfdp(flash, address, &tbl->profile1_0_table.words[0],
                                               sizeof(jedec_x_spi_profile1_0_table_t));
                    HPM_BREAK_IF(status != status_success);

                    tbl->has_spi_profile1_0_table = true;
                } else if (parameter_id == PARAMETER_ID_STACTRLCFGREGMAP) {
                    status = hpm_spi_nor_read_sfdp(flash, address, &tbl->sccr_map.words[0],
                                               sizeof(jedec_status_control_configuration_reg_map_t));
                    HPM_BREAK_IF(status != status_success);

                    tbl->has_sccr_map = true;
                } else {
                    /* Reserved for future use */
                }
            } else {
                /* Unsupported parameter type, ignore */
            }
        }

    } while (false);

    return status;
}

hpm_stat_t hpm_serial_nor_is_busy(hpm_serial_nor_t *flash)
{
    uint8_t sr = 0;
    hpm_stat_t stat;
    if (flash == NULL) {
        return status_invalid_argument;
    }
    stat = hpm_spi_nor_read_status_register(flash, &sr, SERIALNOR_CMD_READ_STATUS_REG1);
    if (stat != status_success) {
        return stat;
    }
    return (sr & 0b1) ? status_spi_nor_flash_is_busy : status_success;
}

hpm_stat_t hpm_serial_nor_write_enable(hpm_serial_nor_t *flash)
{
    hpm_stat_t stat;
    uint8_t cmd;
    if (flash == NULL) {
        return status_invalid_argument;
    }
    cmd = SERIALNOR_CMD_WRITEENABLE;
    stat = hpm_spi_nor_set_command(flash, cmd);
    if (stat != status_success) {
        return stat;
    }
    hpm_spi_nor_udelay(1);
    return stat;
}

hpm_stat_t hpm_serial_nor_erase_chip(hpm_serial_nor_t *flash)
{
    hpm_stat_t stat;
    uint8_t cmd;
    if (flash == NULL) {
        return status_invalid_argument;
    }
    stat = status_spi_nor_flash_is_busy;
    while (stat == status_spi_nor_flash_is_busy) {
        stat = hpm_serial_nor_is_busy(flash);
        if ((stat != status_success) && (stat != status_spi_nor_flash_is_busy)) {
            return stat;
        } else {
            if (stat == status_success) {
                break;
            } else {
                hpm_spi_nor_udelay(1);
            }
        }
    }

    stat = hpm_serial_nor_write_enable(flash);
    if (stat != status_success) {
        return stat;
    }

    cmd = SERIALNOR_CMD_CHIPERASE;
    stat = hpm_spi_nor_set_command(flash, cmd);
    if (stat != status_success) {
        return stat;
    }

    stat = status_spi_nor_flash_is_busy;
    while (stat == status_spi_nor_flash_is_busy) {
        stat = hpm_serial_nor_is_busy(flash);
        if ((stat != status_success) && (stat != status_spi_nor_flash_is_busy)) {
            return stat;
        } else {
            if (stat == status_success) {
                break;
            } else {
                hpm_spi_nor_udelay(1);
            }
        }
    }
    return stat;
}

hpm_stat_t hpm_serial_nor_erase_block_blocking(hpm_serial_nor_t *flash, uint32_t block_addr)
{
    hpm_stat_t stat;
    uint8_t cmd;
    uint32_t addr;
    hpm_serial_nor_transfer_seq_t command_seq = {0};

    if (flash == NULL) {
        return status_invalid_argument;
    }

    stat = status_spi_nor_flash_is_busy;
    while (stat == status_spi_nor_flash_is_busy) {
        stat = hpm_serial_nor_is_busy(flash);
        if ((stat != status_success) && (stat != status_spi_nor_flash_is_busy)) {
            return stat;
        } else {
            if (stat == status_success) {
                break;
            } else {
                hpm_spi_nor_udelay(1);
            }
        }
    }

    stat = hpm_serial_nor_write_enable(flash);
    if (stat != status_success) {
        return stat;
    }
    cmd = flash->flash_info.block_erase_cmd;
    addr = (flash->flash_info.size_in_kbytes > MAX_24BIT_ADDR_SIZE_IN_KBYTES) ? 32U : 24U;
    if (addr == 32) {
        command_seq.addr_phase.addr_bit = flash_addrlen_32bit;
    } else {
        command_seq.addr_phase.addr_bit = flash_addrlen_24bit;
    }
    command_seq.addr_phase.enable = true;
    command_seq.cmd_phase.cmd = cmd;
    command_seq.addr_phase.addr = block_addr;
    command_seq.addr_phase.addr_io_mode = single_io_mode;
    command_seq.dummy_phase.dummy_count = 0;
    command_seq.use_dma = false;
    stat = flash->host.host_ops.transfer(flash->host.host_ops.user_data, &command_seq);

    if (stat != status_success) {
        return stat;
    }
    stat = status_spi_nor_flash_is_busy;
    while (stat == status_spi_nor_flash_is_busy) {
        stat = hpm_serial_nor_is_busy(flash);
        if ((stat != status_success) && (stat != status_spi_nor_flash_is_busy)) {
            return stat;
        } else {
            if (stat == status_success) {
                break;
            } else {
                hpm_spi_nor_udelay(1);
            }
        }
    }
    return stat;
}

hpm_stat_t hpm_serial_nor_erase_sector_blocking(hpm_serial_nor_t *flash, uint32_t sector_addr)
{
    hpm_stat_t stat;
    uint32_t addr;
    hpm_serial_nor_transfer_seq_t command_seq = {0};
    if (flash == NULL) {
        return status_invalid_argument;
    }

    stat = status_spi_nor_flash_is_busy;
    while (stat == status_spi_nor_flash_is_busy) {
        stat = hpm_serial_nor_is_busy(flash);
        if ((stat != status_success) && (stat != status_spi_nor_flash_is_busy)) {
            return stat;
        } else {
            if (stat == status_success) {
                break;
            } else {
                hpm_spi_nor_udelay(1);
            }
        }
    }

    stat = hpm_serial_nor_write_enable(flash);
    if (stat != status_success) {
        return stat;
    }

    addr = (flash->flash_info.size_in_kbytes > MAX_24BIT_ADDR_SIZE_IN_KBYTES) ? 32U : 24U;
    command_seq.cmd_phase.cmd = flash->flash_info.sector_erase_cmd;
    if (addr == 32) {
        command_seq.addr_phase.addr_bit = flash_addrlen_32bit;
    } else {
        command_seq.addr_phase.addr_bit = flash_addrlen_24bit;
    }
    command_seq.addr_phase.enable = true;
    command_seq.addr_phase.addr = sector_addr;
    command_seq.addr_phase.addr_io_mode = single_io_mode;
    command_seq.use_dma = false;
    stat = flash->host.host_ops.transfer(flash->host.host_ops.user_data, &command_seq);
    if (stat != status_success) {
        return stat;
    }

    stat = status_spi_nor_flash_is_busy;
    while (stat == status_spi_nor_flash_is_busy) {
        stat = hpm_serial_nor_is_busy(flash);
        if ((stat != status_success) && (stat != status_spi_nor_flash_is_busy)) {
            return stat;
        } else {
            if (stat == status_success) {
                break;
            } else {
                hpm_spi_nor_udelay(1);
            }
        }
    }
    return stat;
}

hpm_stat_t hpm_serial_nor_erase_block_noblocking(hpm_serial_nor_t *flash, uint32_t block_addr)
{
    hpm_stat_t stat;
    uint32_t addr;
    hpm_serial_nor_transfer_seq_t command_seq = {0};

    if (flash == NULL) {
        return status_invalid_argument;
    }

    stat = hpm_serial_nor_write_enable(flash);
    if (stat != status_success) {
        return stat;
    }

    addr = (flash->flash_info.size_in_kbytes > MAX_24BIT_ADDR_SIZE_IN_KBYTES) ? 32U : 24U;
    if (addr == 32) {
        command_seq.addr_phase.addr_bit = flash_addrlen_32bit;
    } else {
        command_seq.addr_phase.addr_bit = flash_addrlen_24bit;
    }
    command_seq.addr_phase.enable = true;
    command_seq.addr_phase.addr = block_addr;
    command_seq.addr_phase.addr_io_mode = single_io_mode;
    command_seq.cmd_phase.cmd = flash->flash_info.block_erase_cmd;
    command_seq.use_dma = false;
    stat = flash->host.host_ops.transfer(flash->host.host_ops.user_data, &command_seq);
    if (stat != status_success) {
        return stat;
    }
    return stat;
}

hpm_stat_t hpm_serial_nor_erase_sector_noblocking(hpm_serial_nor_t *flash, uint32_t sector_addr)
{
    hpm_stat_t stat;
    uint32_t addr;
    hpm_serial_nor_transfer_seq_t command_seq = {0};

    if (flash == NULL) {
        return status_invalid_argument;
    }

    stat = hpm_serial_nor_write_enable(flash);
    if (stat != status_success) {
        return stat;
    }

    addr = (flash->flash_info.size_in_kbytes > MAX_24BIT_ADDR_SIZE_IN_KBYTES) ? 32U : 24U;
    if (addr == 32) {
        command_seq.addr_phase.addr_bit = flash_addrlen_32bit;
    } else {
        command_seq.addr_phase.addr_bit = flash_addrlen_24bit;
    }
    command_seq.addr_phase.enable = true;
    command_seq.addr_phase.addr = sector_addr;
    command_seq.addr_phase.addr_io_mode = single_io_mode;
    command_seq.cmd_phase.cmd = flash->flash_info.sector_erase_cmd;
    command_seq.use_dma = false;
    stat = flash->host.host_ops.transfer(flash->host.host_ops.user_data, &command_seq);
    if (stat != status_success) {
        return stat;
    }

    return stat;
}

hpm_stat_t hpm_serial_nor_erase_blocking(hpm_serial_nor_t *flash, uint32_t start, uint32_t length)
{
    hpm_stat_t status = status_invalid_argument;
    uint32_t sector_size;
    uint32_t block_size;
    uint32_t aligned_start;
    uint32_t aligned_len;
    uint32_t remaining_len;
    if (flash == NULL) {
        return status_invalid_argument;
    }
    do {
        sector_size = flash->flash_info.sector_size_kbytes * 1024U;
        block_size = flash->flash_info.block_size_kbytes * 1024U;
        aligned_start = HPM_ALIGN_DOWN(start, sector_size);
        aligned_len = HPM_ALIGN_UP(start + length, sector_size) - aligned_start;

        /* If erase address is not block aligned */
        remaining_len = aligned_len;
        while (remaining_len > 0U) {
            if ((aligned_start % block_size != 0U) || (remaining_len < block_size)) {
                status = hpm_serial_nor_erase_sector_blocking(flash, aligned_start);
                HPM_BREAK_IF(status != status_success);
                aligned_start += sector_size;
                remaining_len -= sector_size;
            } else {
                status = hpm_serial_nor_erase_block_blocking(flash, aligned_start);
                HPM_BREAK_IF(status != status_success);
                aligned_start += block_size;
                remaining_len -= block_size;
            }
        }
    } while (false);
    return status;
}

hpm_stat_t hpm_serial_nor_program_blocking(hpm_serial_nor_t *flash, uint8_t *buf, uint32_t data_len, uint32_t address)
{
    hpm_stat_t stat = status_success;
    uint32_t program_size = 0;
    uint32_t offset_in_page;
    uint32_t remaining_page_size;
    uint8_t *src_8;
    uint32_t address_bits;
    uint32_t offset;
    hpm_serial_nor_transfer_seq_t command_seq = {0};

    if ((buf == NULL) || (data_len == 0) || (flash == NULL)) {
        return status_invalid_argument;
    }

    command_seq.addr_phase.addr_io_mode = single_io_mode;
    command_seq.data_phase.data_io_mode = quad_io_mode;
    do {
        HPM_BREAK_IF(data_len > (flash->flash_info.size_in_kbytes * SIZE_1KB));

        stat = status_spi_nor_flash_is_busy;
        while (stat == status_spi_nor_flash_is_busy) {
            stat = hpm_serial_nor_is_busy(flash);
            if ((stat != status_success) && (stat != status_spi_nor_flash_is_busy)) {
                return stat;
            } else {
                if (stat == status_success) {
                    break;
                } else {
                    hpm_spi_nor_udelay(1);
                }
            }
        }

        offset_in_page = address % flash->flash_info.page_size;
        remaining_page_size = flash->flash_info.page_size - offset_in_page;
        address_bits = (flash->flash_info.size_in_kbytes > MAX_24BIT_ADDR_SIZE_IN_KBYTES) ? 32U : 24U;
        if (address_bits == 32) {
            command_seq.addr_phase.addr_bit = flash_addrlen_32bit;
            if ((flash->host.host_param.flags & SERIAL_NOR_HOST_SUPPORT_QUAD_IO_MODE) && (flash->nor_program_para.has_4b_addressing_inst_table)) {
                if (flash->nor_program_para.support_1_4_4_page_program == true) {
                    flash->nor_program_para.page_program_cmd = SERIALNOR_CMD_PAGEPROGRAM_1_4_4_4B;
                    command_seq.addr_phase.addr_io_mode = dual_io_mode;
                } else if (flash->nor_program_para.support_1_1_4_page_program == true) {
                    flash->nor_program_para.page_program_cmd = SERIALNOR_CMD_PAGEPROGRAM_1_1_4_4B;
                } else {
                    /* 1_1_1_page_program */
                    flash->nor_program_para.page_program_cmd = SERIALNOR_CMD_PAGEPROGRAM_1_1_1_4B;
                    command_seq.data_phase.data_io_mode = single_io_mode;
                }
            } else { /* Only consider 1-1-1 Program */
                flash->nor_program_para.page_program_cmd = SERIALNOR_CMD_PAGEPROGRAM_1_1_1_4B;
                command_seq.data_phase.data_io_mode = single_io_mode;
            }
        } else {
            command_seq.addr_phase.addr_bit = flash_addrlen_24bit;
            flash->nor_program_para.page_program_cmd = (flash->host.host_param.flags & SERIAL_NOR_HOST_SUPPORT_QUAD_IO_MODE) ?
                                                SERIALNOR_CMD_PAGE_PROGRAM_1_1_4_3B : SERIALNOR_CMD_PAGEPROGRAM_1_1_1_3B;

            command_seq.data_phase.data_io_mode = (flash->host.host_param.flags & SERIAL_NOR_HOST_SUPPORT_QUAD_IO_MODE) ?
                                                quad_io_mode : single_io_mode;
        }
        command_seq.cmd_phase.cmd = flash->nor_program_para.page_program_cmd;
        command_seq.data_phase.direction = write_direction;
        command_seq.use_dma = true;
        command_seq.addr_phase.enable = true;
        while (data_len > 0) {
            /* Send page program command */
            program_size = MIN(data_len, remaining_page_size);
            /* Ensure the address doesn't across page boundary */
            offset = address % flash->flash_info.page_size;
            HPM_BREAK_IF((offset + program_size) > flash->flash_info.page_size);
            stat = hpm_serial_nor_write_enable(flash);
            if (stat != status_success) {
                return stat;
            }
            command_seq.addr_phase.addr = address;
            command_seq.data_phase.buf = buf;
            command_seq.data_phase.len = program_size;
            stat = flash->host.host_ops.transfer(flash->host.host_ops.user_data, &command_seq);

            HPM_BREAK_IF(stat != status_success);
            stat = status_spi_nor_flash_is_busy;
            while (stat == status_spi_nor_flash_is_busy) {
                stat = hpm_serial_nor_is_busy(flash);
                if ((stat != status_success) && (stat != status_spi_nor_flash_is_busy)) {
                    return stat;
                } else {
                    if (stat == status_success) {
                        break;
                    } else {
                        if (stat == status_success) {
                            break;
                        } else {
                            hpm_spi_nor_udelay(1);
                        }
                    }
                }
            }
            /* Get the new address and length for next iteration */
            address += program_size;
            data_len -= program_size;
            remaining_page_size = flash->flash_info.page_size;
            src_8 = (uint8_t *) buf + program_size;
            buf = (uint8_t *) src_8;
        }
    } while (false);
    return stat;
}

hpm_stat_t hpm_serial_nor_page_program_noblocking(hpm_serial_nor_t *flash, uint8_t *buf, uint32_t data_len, uint32_t address)
{
    hpm_stat_t stat = status_success;
    uint32_t program_size = 0;
    uint32_t offset_in_page;
    uint32_t remaining_page_size;
    uint32_t address_bits;
    hpm_serial_nor_transfer_seq_t command_seq = {0};

    if ((buf == NULL) || (data_len == 0) || (flash == NULL)) {
        return status_invalid_argument;
    }

    command_seq.addr_phase.addr_io_mode = single_io_mode;
    command_seq.data_phase.data_io_mode = quad_io_mode;
    offset_in_page = address % flash->flash_info.page_size;
    remaining_page_size = flash->flash_info.page_size - offset_in_page;
    program_size = MIN(data_len, remaining_page_size);
    if ((data_len > flash->flash_info.page_size) ||
        ((offset_in_page + program_size) > flash->flash_info.page_size)) {
        return status_invalid_argument;
    }

    do {
        offset_in_page = address % flash->flash_info.page_size;
        remaining_page_size = flash->flash_info.page_size - offset_in_page;
        address_bits = (flash->flash_info.size_in_kbytes > MAX_24BIT_ADDR_SIZE_IN_KBYTES) ? 32U : 24U;
        if (address_bits == 32) {
            command_seq.addr_phase.addr_bit = flash_addrlen_32bit;
            if ((flash->host.host_param.flags & SERIAL_NOR_HOST_SUPPORT_QUAD_IO_MODE) && (flash->nor_program_para.has_4b_addressing_inst_table)) {
                if (flash->nor_program_para.support_1_4_4_page_program > 0U) {
                    flash->nor_program_para.page_program_cmd = SERIALNOR_CMD_PAGEPROGRAM_1_4_4_4B;
                    command_seq.addr_phase.addr_io_mode = dual_io_mode;
                } else if (flash->nor_program_para.support_1_1_4_page_program > 0U) {
                    flash->nor_program_para.page_program_cmd = SERIALNOR_CMD_PAGEPROGRAM_1_1_4_4B;
                } else {
                    /* 1_1_1_page_program */
                    flash->nor_program_para.page_program_cmd = SERIALNOR_CMD_PAGEPROGRAM_1_1_1_4B;
                    command_seq.data_phase.data_io_mode = single_io_mode;
                }
            } else { /* Only consider 1-1-1 Program */
                flash->nor_program_para.page_program_cmd = SERIALNOR_CMD_PAGEPROGRAM_1_1_1_4B;
                command_seq.data_phase.data_io_mode = single_io_mode;
            }
        } else {
            command_seq.addr_phase.addr_bit = flash_addrlen_24bit;
            flash->nor_program_para.page_program_cmd = (flash->host.host_param.flags & SERIAL_NOR_HOST_SUPPORT_QUAD_IO_MODE) ?
                                                SERIALNOR_CMD_PAGE_PROGRAM_1_1_4_3B : SERIALNOR_CMD_PAGEPROGRAM_1_1_1_3B;

            command_seq.data_phase.data_io_mode = (flash->host.host_param.flags & SERIAL_NOR_HOST_SUPPORT_QUAD_IO_MODE) ?
                                                quad_io_mode : single_io_mode;
        }
        command_seq.cmd_phase.cmd = flash->nor_program_para.page_program_cmd;
        stat = hpm_serial_nor_write_enable(flash);
        if (stat != status_success) {
            return stat;
        }
        command_seq.use_dma = true;
        command_seq.addr_phase.addr = address;
        command_seq.data_phase.buf = buf;
        command_seq.data_phase.len = program_size;
        command_seq.data_phase.direction = write_direction;
        command_seq.addr_phase.enable = true;
        stat = flash->host.host_ops.transfer(flash->host.host_ops.user_data, &command_seq);
        HPM_BREAK_IF(stat != status_success);
    } while (false);

    return stat;
}

hpm_stat_t hpm_serial_nor_read(hpm_serial_nor_t *flash, uint8_t *buf, uint16_t data_len, uint32_t address)
{
    hpm_stat_t stat;
    hpm_serial_nor_transfer_seq_t command_seq = {0};
    uint32_t read_start = address;

    if ((buf == NULL) || (data_len == 0) || (flash == NULL)) {
        return status_invalid_argument;
    }

    command_seq.addr_phase.addr = read_start;
    command_seq.addr_phase.addr_bit = flash->nor_read_para.addr_bit;
    command_seq.addr_phase.addr_io_mode = flash->nor_read_para.addr_phase_format;
    command_seq.dummy_phase.dummy_count  = flash->nor_read_para.data_dummy_count;
    command_seq.data_phase.data_io_mode = flash->nor_read_para.data_phase_format;
    command_seq.data_phase.buf = buf;
    command_seq.data_phase.len = data_len;
    command_seq.cmd_phase.cmd = flash->nor_read_para.read_cmd;
    command_seq.data_phase.direction = read_direction;
    command_seq.use_dma = true;
    command_seq.addr_phase.enable = true;
    stat = flash->host.host_ops.transfer(flash->host.host_ops.user_data, &command_seq);
    return stat;
}


hpm_stat_t hpm_serial_nor_init(hpm_serial_nor_t *flash, hpm_serial_nor_info_t *info)
{
    jedec_info_table_t jedec_info;
    hpm_stat_t stat;
    if (flash == NULL) {
        return status_invalid_argument;
    }
    if (flash->host.host_param.flags & SERIAL_NOR_HOST_SUPPORT_SPI_INTERFACE) {
        serial_nor_host_ops_use_spi(flash);
    } else {
        /* Reserved for use by other interfaces */
    }
    flash->host.host_ops.user_data = &flash->host;
    flash->host.host_ops.init(flash->host.host_ops.user_data);
    /* in order to ensure read sfdp parameter are correct, spi frequency must be less than 50M, and here,default value is 20M */
    flash->host.host_ops.set_frequency(flash->host.host_ops.user_data, SPI_READ_SFDP_FREQUENCY);
    stat = hpm_serial_nor_read_sfdp_info(flash, &jedec_info, false);
    if (stat != status_success) {
        return stat;
    }
    flash->host.host_ops.set_frequency(flash->host.host_ops.user_data, flash->host.host_param.param.frequency);
    get_page_sector_block_size_from_sfdp(&flash->flash_info, &jedec_info);
    memcpy(info, &flash->flash_info, sizeof(hpm_serial_nor_info_t));
    if (flash->host.host_param.flags & SERIAL_NOR_HOST_SUPPORT_QUAD_IO_MODE) {
        stat = prepare_quad_mode_enable_sequence(flash, &jedec_info);
        flash->flash_info.sfdp_version = jedec_info.standard_version;
        info->sfdp_version = jedec_info.standard_version;
        if (stat != status_success) {
            flash->host.host_param.flags &= ~SERIAL_NOR_HOST_SUPPORT_QUAD_IO_MODE | SERIAL_NOR_HOST_SUPPORT_SINGLE_IO_MODE;
        }
    }
    hpm_spi_get_read_para(flash, &jedec_info);
    hpm_spi_get_program_para(flash, &jedec_info);
    return stat;
}

hpm_stat_t hpm_serial_nor_get_info(hpm_serial_nor_t *flash, hpm_serial_nor_info_t *info)
{
    if (flash == NULL) {
        return status_invalid_argument;
    }
    memcpy(info, &flash->flash_info, sizeof(hpm_serial_nor_info_t));
    return status_success;
}