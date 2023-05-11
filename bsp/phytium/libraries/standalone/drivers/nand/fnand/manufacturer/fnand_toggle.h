/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fnand_toggle.h
 * Date: 2022-07-05 20:00:45
 * LastEditTime: 2022-07-05 20:00:45
 * Description:  This file is for toggle nand
 *
 * Modify History:
 *  Ver   Who  Date   Changes
 * ----- ------  -------- --------------------------------------
 * 1.0   huanghe    2022/05/10    first release
 */

#ifndef DRIVERS_NAND_FNAND_TOGGLE_H
#define DRIVERS_NAND_FNAND_TOGGLE_H


#include "ftypes.h"
#include "fnand.h"


#ifdef __cplusplus
extern "C"
{
#endif


/*
 * Mandatory commands
 */

#define TOGGLE_CMD_READ1 0x00
#define TOGGLE_CMD_READ2 0x30

#define TOGGLE_CMD_CHANGE_READ_COLUMN1 0x05 /* TOGGLE Change Read \
                      Column command (1st                         \
cycle) */
#define TOGGLE_CMD_CHANGE_READ_COLUMN2 0xE0 /* TOGGLE Change Read \
                      Column command (2nd                         \
cycle) */
#define TOGGLE_CMD_BLOCK_ERASE1 0x60        /* TOGGLE Block Erase \
(1st cycle) */
#define TOGGLE_CMD_BLOCK_ERASE2 0xD0        /* TOGGLE Block Erase \
(2nd cycle) */
#define TOGGLE_CMD_READ_STATUS 0x70         /* TOGGLE Read status \
command */
#define TOGGLE_CMD_PAGE_PROG1 0x80          /* TOGGLE Page Program \
                          command (1st cycle)                      \
*/
#define TOGGLE_CMD_PAGE_PROG2 0x10          /* TOGGLE Page Program \
                          command (2nd cycle)                      \
*/
#define TOGGLE_CMD_CHANGE_WRITE_COLUMN 0x85 /* TOGGLE Change Write \
Column command */
#define TOGGLE_CMD_READ_ID 0x90             /* TOGGLE Read ID \
command */
#define TOGGLE_CMD_READ_PARAM_PAGE 0xEC     /* TOGGLE Read \
                          Parameter Page                   \
command */
#define TOGGLE_CMD_RESET 0xFF               /* TOGGLE Reset \
command */

#define TOGGLE_END_CMD_NONE 0xfff /* No End command */


struct jedec_ecc_info
{
    u8 ecc_bits;
    u8 codeword_size;
    u16 bb_per_lun;
    u16 block_endurance;
    u8 reserved[2];
} __attribute__((packed));

struct ToggleNandGeometry
{
    u8 sig[4];          /* Parameter page signature */
    u16 revision;       /* Revision number */
    u16 features;       /* Features supported */
    u8 opt_cmd[3];      /* Optional commands supported */
    u16 sec_cmd;
    u8 num_of_param_pages;
    u8 reserved0[18];

    /* manufacturer information block */
    char manufacturer[12];  /* Device manufacturer */
    char model[20];         /* Device model */
    u8 jedec_id[6];         /* JEDEC manufacturer ID */
    u8 reserved1[10];

    /* memory organization block */
    u32 byte_per_page;      /* Number of data bytes per page */
    u16 spare_bytes_per_page; /* Number of spare bytes per page */
    u8 reserved2[6];          /*  */
    u32 pages_per_block;      /* Number of pages per block */
    u32 blocks_per_lun;       /* Number of blocks per logical unit */
    u8 lun_count;             /* Number of logical unit */
    u8 addr_cycles;
    u8 bits_per_cell;
    u8 programs_per_page;
    u8 multi_plane_addr;
    u8 multi_plane_op_attr;
    u8 reserved3[38];

    /* electrical parameter block */
    u16 async_sdr_speed_grade;
    u16 toggle_ddr_speed_grade;
    u16 sync_ddr_speed_grade;
    u8 async_sdr_features;
    u8 toggle_ddr_features;
    u8 sync_ddr_features;
    u16 t_prog;
    u16 t_bers;
    u16 t_r;
    u16 t_r_multi_plane;
    u16 t_ccs;
    u16 io_pin_capacitance_typ;
    u16 input_pin_capacitance_typ;
    u16 clk_pin_capacitance_typ;
    u8 driver_strength_support;
    u16 t_adl;
    u8 reserved4[36];

    /* ECC and endurance block */
    u8 guaranteed_good_blocks;
    u16 guaranteed_block_endurance;
    struct jedec_ecc_info ecc_info[4];
    u8 reserved5[29];

    /* reserved */
    u8 reserved6[148];

    /* vendor */
    u16 vendor_rev_num;
    u8 reserved7[88];

    /* CRC for Parameter Page */
    u16 crc;

} __attribute__((__packed__));


#ifdef __cplusplus
}
#endif

#endif // !


