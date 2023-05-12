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
 * FilePath: fnand_toshiba.c
 * Date: 2022-07-06 08:32:43
 * LastEditTime: 2022-07-06 08:32:44
 * Description:  This file is for toshiba nand
 *
 * Modify History:
 *  Ver   Who  Date   Changes
 * ----- ------  -------- --------------------------------------
 * 1.0   huanghe    2022/05/10    first release
 */


#include "fnand.h"
#include "fnand_id.h"
#include "fnand_ecc.h"
#include "fdebug.h"
#include "sdkconfig.h"


#define FNAND_T_NAND_DEBUG_TAG "FNAND_T_NAND"
#define CONFIG_FNAND_T_NAND_DEBUG_EN
// #define CONFIG_FNAND_T_NAND_DEBUG_EN
#ifdef CONFIG_FNAND_T_NAND_DEBUG_EN
    #define FNAND_T_NAND_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FNAND_T_NAND_DEBUG_TAG, format, ##__VA_ARGS__)
    #define FNAND_T_NAND_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FNAND_T_NAND_DEBUG_TAG, format, ##__VA_ARGS__)
    #define FNAND_T_NAND_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FNAND_T_NAND_DEBUG_TAG, format, ##__VA_ARGS__)
    #define FNAND_T_NAND_DEBUG_D(format, ...) FT_DEBUG_PRINT_D(FNAND_T_NAND_DEBUG_TAG, format, ##__VA_ARGS__)
#else
    #define FNAND_T_NAND_DEBUG_I(format, ...)
    #define FNAND_T_NAND_DEBUG_W(format, ...)
    #define FNAND_T_NAND_DEBUG_E(format, ...)
    #define FNAND_T_NAND_DEBUG_D(format, ...)
#endif

static FError TC58NVM9S3ETAI0_CHECK(FNand *instance_p, FNandId *id_p, u32 chip_addr)
{
    FNandNandGeometry *geometry_p = &instance_p->nand_geometry[chip_addr];

    if (((id_p->data[3] & 0x3) == 1)) /*  */
    {
        FNAND_T_NAND_DEBUG_I("TC58NVM9S3ETAI0 is checked") ;
        geometry_p->bytes_per_page = 2048;
        geometry_p->spare_bytes_per_page =  64;
        geometry_p->pages_per_block = 64;
        geometry_p->blocks_per_lun = 512;
        geometry_p->num_lun = 1;
        geometry_p->num_pages = (geometry_p->num_lun *
                                 geometry_p->blocks_per_lun *
                                 geometry_p->pages_per_block);
        geometry_p->num_blocks = (geometry_p->num_lun * geometry_p->blocks_per_lun);
        geometry_p->block_size = (geometry_p->pages_per_block * geometry_p->bytes_per_page);
        geometry_p->device_size = (geometry_p->num_blocks * geometry_p->block_size * geometry_p->bytes_per_page);
        geometry_p->rowaddr_cycles = 3;
        geometry_p->coladdr_cycles = 2 ;
        geometry_p->hw_ecc_length =  FNandGetEccTotalLength(geometry_p->bytes_per_page, instance_p->config.ecc_strength);
        geometry_p->ecc_offset = geometry_p->spare_bytes_per_page - geometry_p->hw_ecc_length;
        geometry_p->hw_ecc_steps = geometry_p->bytes_per_page  / instance_p->config.ecc_step_size ;
        geometry_p->ecc_step_size = instance_p->config.ecc_step_size;
        FNAND_T_NAND_DEBUG_D("bytes_per_page %d ", geometry_p->bytes_per_page);               /* Bytes per page */
        FNAND_T_NAND_DEBUG_D("spare_bytes_per_page %d ", geometry_p->spare_bytes_per_page) ;  /* Size of spare area in bytes */
        FNAND_T_NAND_DEBUG_D("pages_per_block %d ", geometry_p->pages_per_block) ;        /* Pages per block */
        FNAND_T_NAND_DEBUG_D("blocks_per_lun %d ", geometry_p->blocks_per_lun) ;         /* Bocks per LUN */
        FNAND_T_NAND_DEBUG_D("num_lun %d ", geometry_p->num_lun) ;                /* Total number of LUN */
        FNAND_T_NAND_DEBUG_D("num_pages %d ", geometry_p->num_pages) ;              /* Total number of pages in device */
        FNAND_T_NAND_DEBUG_D("num_blocks %d ", geometry_p->num_blocks) ;             /* Total number of blocks in device */
        FNAND_T_NAND_DEBUG_D("block_size %d ", geometry_p->block_size) ;             /* Size of a block in bytes */
        FNAND_T_NAND_DEBUG_D("device_size %d ", geometry_p->device_size) ;            /* Total device size in bytes */
        FNAND_T_NAND_DEBUG_D("rowaddr_cycles %d ", geometry_p->rowaddr_cycles) ;          /* Row address cycles */
        FNAND_T_NAND_DEBUG_D("coladdr_cycles %d ", geometry_p->coladdr_cycles) ;          /* Column address cycles */
        FNAND_T_NAND_DEBUG_D("hw_ecc_length %d ", geometry_p->hw_ecc_length) ;          /* 产生硬件ecc校验参数的个数 */
        FNAND_T_NAND_DEBUG_D("ecc_offset %d ", geometry_p->ecc_offset) ;          /* obb存放硬件ecc校验参数页位置的偏移 */
        FNAND_T_NAND_DEBUG_D("hw_ecc_steps %d ", geometry_p->hw_ecc_steps) ;          /* number of ECC steps per page */
        FNAND_T_NAND_DEBUG_D("ecc_step_size %d ", geometry_p->ecc_step_size) ;       /* 进行读写操作时，单次ecc 的步骤的跨度 */
    }
    else
    {
        FNAND_T_NAND_DEBUG_E("TC58NVM9S3ETAI0_CHECK error");
        return FNAND_ERR_NOT_MATCH;
    }

    return FT_SUCCESS;
}

FError toshiba_nand_decode_id(FNand *instance_p, FNandId *id_p, u32 chip_addr)
{

    switch (id_p->data[1])
    {
        case 0xf0:
            return TC58NVM9S3ETAI0_CHECK(instance_p, id_p, chip_addr) ;
            break;
        default:
            FNAND_T_NAND_DEBUG_E("Driver not supported 0x%x device", id_p->data[1]) ;
            return FNAND_ERR_NOT_MATCH;
    }
}

const struct FNandManuFacturerOps toshiba_ops = {.detect = toshiba_nand_decode_id};
