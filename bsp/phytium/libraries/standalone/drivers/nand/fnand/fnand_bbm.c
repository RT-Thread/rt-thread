/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
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
 * FilePath: fnand_bbm.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:56:12
 * Description:  This file implements the bad block management (BBM) functionality.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/05/10    first release
 */


#include "fnand_bbm.h"
#include "fnand.h"
#include "fparameters.h"

#include <string.h>
#include "fdebug.h"
#define FNAND_BBM_DEBUG_TAG "FNAND_BBM"
#define FNAND_BBM_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FNAND_BBM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FNAND_BBM_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FNAND_BBM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FNAND_BBM_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FNAND_BBM_DEBUG_TAG, format, ##__VA_ARGS__)

static FError FNandWriteBbt(FNand *instance_p,
                            FNandBbtDesc *desc_p,
                            FNandBbtDesc *mirror_desc_p,
                            u32 chip_addr);

/**
 * @name: FNandInitBbtDesc
 * @msg:  This function initializes the Bad Block Table(BBT) descriptors with a
 * predefined pattern for searching Bad Block Table(BBT) in flash.
 * @param {FNand} *instance_p is the pointer to the FNand instance.
 * @return {*}
 * @note:
 */
void FNandInitBbtDesc(FNand *instance_p)
{
    u32 i;
    int index;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);

    for (i = 0; i < FNAND_CONNECT_MAX_NUM; i++)
    {
        /*
        * Initialize primary Bad Block Table(BBT)
        */
        instance_p->bbt_manager[i].bbt_desc.page_offset = FNAND_BBT_DESC_PAGE_OFFSET;
        instance_p->bbt_manager[i].bbt_desc.sig_offset = FNAND_BBT_DESC_SIG_OFFSET;
        instance_p->bbt_manager[i].bbt_desc.ver_offset = FNAND_BBT_DESC_VER_OFFSET;
        instance_p->bbt_manager[i].bbt_desc.max_blocks = FNAND_BBT_DESC_MAX_BLOCKS;
        instance_p->bbt_manager[i].bbt_desc.sig_length = FNAND_BBT_DESC_SIG_LEN;
        strcpy(&instance_p->bbt_manager[i].bbt_desc.signature[0], "Bbt0");
        instance_p->bbt_manager[i].bbt_desc.version = 0;
        instance_p->bbt_manager[i].bbt_desc.valid = 0;
        /*
        * Initialize mirror Bad Block Table(BBT)
        */
        instance_p->bbt_manager[i].bbt_mirror_desc.page_offset = FNAND_BBT_DESC_PAGE_OFFSET;
        instance_p->bbt_manager[i].bbt_mirror_desc.sig_offset = FNAND_BBT_DESC_SIG_OFFSET;
        instance_p->bbt_manager[i].bbt_mirror_desc.ver_offset = FNAND_BBT_DESC_VER_OFFSET;
        instance_p->bbt_manager[i].bbt_mirror_desc.sig_length = FNAND_BBT_DESC_SIG_LEN;
        instance_p->bbt_manager[i].bbt_mirror_desc.max_blocks = FNAND_BBT_DESC_MAX_BLOCKS;
        strcpy(&instance_p->bbt_manager[i].bbt_mirror_desc.signature[0], "1tbB");
        instance_p->bbt_manager[i].bbt_mirror_desc.version = 0;
        instance_p->bbt_manager[i].bbt_mirror_desc.valid = 0;

        /*
        * Initialize Bad block search pattern structure
        */
        if (instance_p->nand_geometry[i].bytes_per_page > 512)
        {
            /* For flash page size > 512 bytes */
            instance_p->bbt_manager[i].bb_pattern.options = FNAND_BBT_SCAN_2ND_PAGE;
            instance_p->bbt_manager[i].bb_pattern.offset =
                FNAND_BB_PATTERN_OFFSET_LARGE_PAGE;
            instance_p->bbt_manager[i].bb_pattern.length =
                FNAND_BB_PATTERN_LENGTH_LARGE_PAGE;
        }
        else
        {
            instance_p->bbt_manager[i].bb_pattern.options = FNAND_BBT_SCAN_2ND_PAGE;
            instance_p->bbt_manager[i].bb_pattern.offset =
                FNAND_BB_PATTERN_OFFSET_SMALL_PAGE;
            instance_p->bbt_manager[i].bb_pattern.length =
                FNAND_BB_PATTERN_LENGTH_SMALL_PAGE;
        }
        for (index = 0; index < FNAND_BB_PATTERN_LENGTH_LARGE_PAGE; index++)
        {
            instance_p->bbt_manager[i].bb_pattern.pattern[index] = FNAND_BB_PATTERN;
        }
    }
}

/**
 * @name: FNandConvertBbt
 * @msg:  Convert bitmask read in flash to information stored in RAM
 * @return {*}
 * @note:
 * @param {FNand} *instance_p is the pointer to the FNand instance.
 * @param {u8} *buf is buffer to store the bitmask
 * @param {u32} chip_addr is chip address
 */
static void FNandConvertBbt(FNand *instance_p, u8 *buf, u32 chip_addr)
{
    u32 block_offset;
    u32 block_shift;
    u32 data;
    u8 block_type;
    u32 block_index;
    u32 bbtlen = instance_p->nand_geometry[chip_addr].num_blocks >>
                 FNAND_BBT_BLOCK_SHIFT;

    for (block_offset = 0; block_offset < bbtlen; block_offset++)
    {
        data = buf[block_offset];

        /*
        * Clear the RAM based Bad Block Table(BBT) contents
        */
        instance_p->bbt_manager[chip_addr].bbt[block_offset] = 0x0;

        /*
        * Loop through the every 4 blocks in the bitmap
        */
        for (block_index = 0; block_index < FNAND_BBT_ENTRY_NUM_BLOCKS;
             block_index++)
        {
            block_shift = FNAND_BBTBLOCKSHIFT(block_index);
            block_type = (data >> block_shift) &
                         FNAND_BLOCK_TYPE_MASK;
            switch (block_type)
            {
                case FNAND_FLASH_BLOCK_FACTORY_BAD:
                    /* Factory bad block */
                    instance_p->bbt_manager[chip_addr].bbt[block_offset] |=
                        FNAND_BLOCK_FACTORY_BAD << block_shift;
                    break;
                case FNAND_FLASH_BLOCK_RESERVED:
                    /* Reserved block */
                    instance_p->bbt_manager[chip_addr].bbt[block_offset] |=
                        FNAND_BLOCK_RESERVED << block_shift;
                    break;
                case FNAND_FLASH_BLOCK_BAD:
                    /* Bad block due to wear */
                    instance_p->bbt_manager[chip_addr].bbt[block_offset] |=
                        FNAND_BLOCK_BAD << block_shift;
                    break;
                default:
                    /* Good block */
                    /* The BBT entry already defaults to
                            * zero */
                    break;
            }
        }
    }
}

static FError FNandUpdateBbt(FNand *instance_p, u32 chip_addr)
{
    FError ret;
    u8 version;

    /*
    * Update the version number
    */
    version = instance_p->bbt_manager[chip_addr].bbt_desc.version;
    instance_p->bbt_manager[chip_addr].bbt_desc.version = (version + 1) % 256;
    version = instance_p->bbt_manager[chip_addr].bbt_mirror_desc.version;
    instance_p->bbt_manager[chip_addr].bbt_mirror_desc.version = (version + 1) % 256;

    /*
    * Update the primary Bad Block Table(BBT) in flash
    */
    ret = FNandWriteBbt(instance_p,
                        &instance_p->bbt_manager[chip_addr].bbt_desc,
                        &instance_p->bbt_manager[chip_addr].bbt_mirror_desc, chip_addr);
    if (ret != FT_SUCCESS)
    {
        return ret;
    }

    /*
    * Update the mirrored Bad Block Table(BBT) in flash
    */
    ret = FNandWriteBbt(instance_p,
                        &instance_p->bbt_manager[chip_addr].bbt_mirror_desc,
                        &instance_p->bbt_manager[chip_addr].bbt_desc, chip_addr);
    if (ret != FT_SUCCESS)
    {
        return ret;
    }

    return FT_SUCCESS;
}

static FError FNandMarkBbt(FNand *instance_p,
                           FNandBbtDesc *desc_p,
                           u32 chip_addr)
{

    u32 block_index;
    u32 block_offset;
    u8 block_shift;
    u8 old_val;
    u8 new_val;
    FError ret;
    u32 updatebbt = 0;
    u32 index;

    /*
     * Mark the last four blocks as Reserved
     */
    block_index = instance_p->nand_geometry[chip_addr].num_blocks - desc_p->max_blocks;

    for (index = 0; index < desc_p->max_blocks; index++, block_index++)
    {
        block_offset = block_index >> FNAND_BBT_BLOCK_SHIFT;
        block_shift = FNAND_BBTBLOCKSHIFT(block_index);
        old_val = instance_p->bbt_manager[chip_addr].bbt[block_offset];
        new_val = old_val | (FNAND_BLOCK_RESERVED << block_shift);
        instance_p->bbt_manager[chip_addr].bbt[block_offset] = new_val;

        if (old_val != new_val)
        {
            updatebbt = 1;
        }
    }

    /*
     * Update the BBT to flash
     */
    if (updatebbt)
    {
        ret = FNandUpdateBbt(instance_p, chip_addr);
        if (ret != FT_SUCCESS)
        {
            return ret;
        }
    }
    return FT_SUCCESS;
}

static FError FNandWriteBbt(FNand *instance_p,
                            FNandBbtDesc *desc_p,
                            FNandBbtDesc *mirror_desc_p,
                            u32 chip_addr)
{
    u64 offset;
    u32 block = instance_p->nand_geometry[chip_addr].num_blocks - 1;
    u8 buf[FNAND_MAX_BLOCKS >> FNAND_BBT_BLOCK_SHIFT];
    u8 sparebuf[FNAND_MAX_SPARE_SIZE];
    u8 mask[4] = {0x00, 0x01, 0x02, 0x03};
    u8 Data;
    u32 block_offset;
    u32 block_shift;
    FError ret;
    u32 block_index;
    u32 index;
    u8 block_type;
    u32 bbtlen = instance_p->nand_geometry[chip_addr].num_blocks >>
                 FNAND_BBT_BLOCK_SHIFT;
    FNAND_BBM_DEBUG_I("FNandWriteBbt bbtlen is %d", bbtlen);

    /*
     * Find a valid block to write the Bad Block Table(BBT)
     */
    if (!desc_p->valid)
    {
        for (index = 0; index < desc_p->max_blocks; index++)
        {
            block = (block - index);
            block_offset = block >> FNAND_BBT_BLOCK_SHIFT;
            block_shift = FNAND_BBTBLOCKSHIFT(block);
            block_type = (instance_p->bbt_manager[chip_addr].bbt[block_offset] >>
                          block_shift) &
                         FNAND_BLOCK_TYPE_MASK;
            switch (block_type)
            {
                case FNAND_BLOCK_BAD:
                case FNAND_BLOCK_FACTORY_BAD:
                    continue;
                default:
                    /* Good Block */
                    break;
            }
            desc_p->page_offset = block *
                                  instance_p->nand_geometry[chip_addr].pages_per_block;
            if (desc_p->page_offset != mirror_desc_p->page_offset)
            {
                /* Free block found */
                desc_p->valid = 1;
                break;
            }
        }

        /*
         * Block not found for writing Bad Block Table(BBT)
         */
        if (index >= desc_p->max_blocks)
        {
            return FNAND_VALUE_FAILURE;
        }
    }
    else
    {
        block = desc_p->page_offset / instance_p->nand_geometry[chip_addr].pages_per_block;
    }

    /*
     * Convert the memory based BBT to flash based table
     */
    memset(buf, 0xff, bbtlen);

    /*
     * Loop through the number of blocks
     */
    for (block_offset = 0; block_offset < bbtlen; block_offset++)
    {
        Data = instance_p->bbt_manager[chip_addr].bbt[block_offset];
        /*
         * Calculate the bit mask for 4 blocks at a time in loop
         */
        for (block_index = 0; block_index < FNAND_BBT_ENTRY_NUM_BLOCKS;
             block_index++)
        {
            block_shift = FNAND_BBTBLOCKSHIFT(block_index);
            buf[block_offset] &= ~(mask[Data &
                                        FNAND_BLOCK_TYPE_MASK]
                                   << block_shift);
            Data >>= FNAND_BBT_BLOCK_SHIFT;
        }

    }

    /*
     * Write the Bad Block Table(BBT) to flash
     */
    ret = FNandEraseBlock(instance_p, block, chip_addr);
    if (ret != FT_SUCCESS)
    {
        return ret;
    }

    /*
     * Write the signature and version in the spare data area
     */
    memset(sparebuf, 0xff, instance_p->nand_geometry[chip_addr].spare_bytes_per_page);
    memcpy(sparebuf + desc_p->sig_offset, &desc_p->signature[0],
           desc_p->sig_length);
    memcpy(sparebuf + desc_p->ver_offset, &desc_p->version, 1);

    /*
     * Write the BBT to page offset
     */
    FNandWritePage(instance_p, desc_p->page_offset, &buf[0], 0, bbtlen, sparebuf, 0, sizeof(sparebuf), chip_addr);
    if (ret != FT_SUCCESS)
    {
        return ret;
    }
    return FT_SUCCESS;
}

static void FNandCreateBbt(FNand *instance_p, u32 chip_addr)
{
    u32 block_index;
    u32 page_index;
    u32 length;
    u32 block_offset;
    u32 block_shift;
    u32 num_pages;
    u32 page;
    u8 buf[FNAND_MAX_SPARE_SIZE];
    u32 bbt_len = instance_p->nand_geometry[chip_addr].num_blocks >>
                  FNAND_BBT_BLOCK_SHIFT;
    FError ret;
    /*
     * Number of pages to search for bad block pattern
     */
    if (instance_p->bbt_manager[chip_addr].bb_pattern.options & FNAND_BBT_SCAN_2ND_PAGE)
    {
        num_pages = 2;
    }
    else
    {
        num_pages = 1;
    }

    /*
     * Zero the RAM based Bad Block Table(BBT) entries
     */
    memset(&instance_p->bbt_manager[chip_addr].bbt[0], 0, bbt_len);

    /*
     * Scan all the blocks for factory marked bad blocks
     */
    for (block_index = 0; block_index <
         instance_p->nand_geometry[chip_addr].num_blocks;
         block_index++)
    {
        /*
         * Block offset in Bad Block Table(BBT) entry
         */
        block_offset = block_index >> FNAND_BBT_BLOCK_SHIFT;
        /*
         * Block shift value in the byte
         */
        block_shift = FNAND_BBTBLOCKSHIFT(block_index);
        page = block_index * instance_p->nand_geometry[chip_addr].pages_per_block;

        /*
         * Search for the bad block pattern
         */
        for (page_index = 0; page_index < num_pages; page_index++)
        {
            ret = FNandReadPageOOb(instance_p, page + page_index, buf, 0, sizeof(buf), chip_addr);
            if (ret != FT_SUCCESS)
            {
                FNAND_BBM_DEBUG_E("%s FNandReadPageOOb is error", __func__);
                /* Marking as bad block */
                instance_p->bbt_manager[chip_addr].bbt[block_offset] |=
                    (FNAND_BLOCK_FACTORY_BAD << block_shift);
                break;
            }

            /*
             * Read the spare bytes to check for bad block
             * pattern
             */
            for (length = 0; length <
                 instance_p->bbt_manager[chip_addr].bb_pattern.length;
                 length++)
            {
                if (buf[instance_p->bbt_manager[chip_addr].bb_pattern.offset + length] !=
                    instance_p->bbt_manager[chip_addr].bb_pattern.pattern[length])
                {
                    /* Bad block found */
                    instance_p->bbt_manager[chip_addr].bbt[block_offset] |=
                        (FNAND_BLOCK_FACTORY_BAD << block_shift);
                    FNAND_BBM_DEBUG_E("Bad block found block is %d", page + page_index);
                    break;
                }
            }
        }
    }
}

FError FNandSearchBbt(FNand *instance_p, FNandBbtDesc *desc, u32 chip_addr)
{
    u32 start_block;
    u32 sig_offset;
    u32 ver_offset;
    u32 max_blocks;
    u32 pageoff;
    u32 sig_length;
    u8 buf[FNAND_MAX_SPARE_SIZE];
    u32 block;
    u32 offset;
    FError ret;

    start_block = instance_p->nand_geometry[chip_addr].num_blocks - 1; /* start block is last block start */
    sig_offset = desc->sig_offset;
    ver_offset = desc->ver_offset;
    max_blocks = desc->max_blocks;
    sig_length = desc->sig_length;
    FNAND_BBM_DEBUG_I("FNandSearchBbt starts at 0x%x", start_block);
    FNAND_BBM_DEBUG_I("Pages_per_block starts at %d", instance_p->nand_geometry[chip_addr].pages_per_block);
    for (block = 0; block < max_blocks; block++)
    {
        pageoff = (start_block - block) *
                  instance_p->nand_geometry[chip_addr].pages_per_block;
        FNAND_BBM_DEBUG_I("Block 0x%x", block);
        FNAND_BBM_DEBUG_I("%s, Pageoff is 0x%x", __func__, pageoff);
        ret = FNandReadPageOOb(instance_p, pageoff, buf, 0, sizeof(buf), chip_addr);
        if (ret != FT_SUCCESS)
        {
            continue;
        }

        /*
         * Check the Bad Block Table(BBT) signature
         */
        for (offset = 0; offset < sig_length; offset++)
        {
            if (buf[offset + sig_offset] != desc->signature[offset])
            {
                break; /* Check the next blocks */
            }
        }
        if (offset >= sig_length)
        {
            /*
             * Bad Block Table(BBT) found
             */
            desc->page_offset = pageoff;
            desc->version = buf[ver_offset];
            desc->valid = 1;
            return FT_SUCCESS;
        }
    }
    /*
     * Bad Block Table(BBT) not found
     */
    return FNAND_VALUE_ERROR;
}

/**
 * @name:
 * @msg:
 * @return {*}
 * @note:
 * @param {FNand} *instance_p
 * @param {u32} chip_addr
 */
FError FNandReadBbt(FNand *instance_p, u32 chip_addr)
{
    u64 offset;
    u8 buf[FNAND_MAX_BLOCKS >> FNAND_BBT_BLOCK_SHIFT];
    FError status1;
    FError status2;
    FError ret;
    u32 bbtlen;


    FNandBbtDesc *desc_p = &instance_p->bbt_manager[chip_addr].bbt_desc;
    FNandBbtDesc *mirror_desc_p = &instance_p->bbt_manager[chip_addr].bbt_mirror_desc;

    bbtlen = instance_p->nand_geometry[chip_addr].num_blocks >> FNAND_BBT_BLOCK_SHIFT; /* 根据nand 介质信息获取的总块数，除以4 的含义为每字节存储4个块信息 */
    FNAND_BBM_DEBUG_I("FNandReadBbt ,bbtlen is %d", bbtlen);

    status1 = FNandSearchBbt(instance_p, desc_p, chip_addr);
    status2 = FNandSearchBbt(instance_p, mirror_desc_p, chip_addr);

    if ((status1 != FT_SUCCESS) && (status2 != FT_SUCCESS))
    {
        FNAND_BBM_DEBUG_E("FNandReadBbt error status1 %x, status2 %x", status1, status2);
        return FNAND_VALUE_FAILURE;
    }

    /*
     * Bad Block Table found
     */

    if (desc_p->valid && mirror_desc_p->valid)
    {
        if (desc_p->version > mirror_desc_p->version)
        {
            /*
            * Valid BBT & Mirror BBT found
            */
            FNAND_BBM_DEBUG_I("The desc_p->version > mirror_desc_p->version is not null , the page_offset is %d", desc_p->page_offset);
            ret = FNandReadPage(instance_p, desc_p->page_offset, buf, 0, bbtlen, NULL, 0, 0, chip_addr);
            if (ret != FT_SUCCESS)
            {
                FNAND_BBM_DEBUG_I("The desc_p->version > mirror_desc_p->version is not null , the FNandReadPage is error 0x%x", ret);
                return ret;
            }
            /*
             * Convert flash BBT to memory based BBT
            */
            FNandConvertBbt(instance_p, &buf[0], chip_addr);
            mirror_desc_p->version = desc_p->version;

            /*
             * Write the BBT to Mirror BBT location in flash
             */
            ret = FNandWriteBbt(instance_p, mirror_desc_p,
                                desc_p, chip_addr);
            if (ret != FT_SUCCESS)
            {
                return ret;
            }
        }
        else if (desc_p->version < mirror_desc_p->version)
        {
            FNAND_BBM_DEBUG_I("desc_p->version < mirror_desc_p->version is not null, the page_offset is %d", mirror_desc_p->page_offset);
            ret = FNandReadPage(instance_p, mirror_desc_p->page_offset, buf, 0, bbtlen, NULL, 0, 0, chip_addr);
            if (ret != FT_SUCCESS)
            {
                FNAND_BBM_DEBUG_I("desc_p->version < mirror_desc_p->version is not null, the FNandReadPage is error 0x%x", ret);
                return ret;
            }
            /*
             * Convert flash BBT to memory based BBT
             */
            FNandConvertBbt(instance_p, &buf[0], chip_addr);
            desc_p->version = mirror_desc_p->version;

            /*
             * Write the BBT to Mirror BBT location in flash
             */
            ret = FNandWriteBbt(instance_p, desc_p,
                                mirror_desc_p, chip_addr);
            if (ret != FT_SUCCESS)
            {
                return ret;
            }
        }
        else
        {
            /* Both are up-to-date */
            FNAND_BBM_DEBUG_I("Both are up-to-date, the page_offset is %d", desc_p->page_offset);

            ret = FNandReadPage(instance_p, desc_p->page_offset, buf, 0, bbtlen, NULL, 0, 0, chip_addr);
            if (ret != FT_SUCCESS)
            {
                FNAND_BBM_DEBUG_I("Both are up-to-date, the FNandReadPage is error 0x%x", ret);
                return ret;
            }

            /*
             * Convert flash BBT to memory based BBT
            */
            FNandConvertBbt(instance_p, &buf[0], chip_addr);
        }
    }
    else if (desc_p->valid)
    {
        /*
        * Valid Primary BBT found
        */

        FNAND_BBM_DEBUG_I("Valid Primary BBT found is %d", desc_p->page_offset);

        ret = FNandReadPage(instance_p, desc_p->page_offset, buf, 0, bbtlen, NULL, 0, 0, chip_addr);
        if (ret != FT_SUCCESS)
        {
            FNAND_BBM_DEBUG_I("Valid Primary BBT found is error 0x%x", ret);
            return ret;
        }


        /*
            * Convert flash BBT to memory based BBT
        */
        FNandConvertBbt(instance_p, &buf[0], chip_addr);
        desc_p->version = mirror_desc_p->version;

        /*
        * Write the BBT to Mirror BBT location in flash
        */
        ret = FNandWriteBbt(instance_p, mirror_desc_p,
                            desc_p, chip_addr);
        if (ret != FT_SUCCESS)
        {
            return ret;
        }
    }
    else
    {
        /*
         * Valid Mirror BBT found
         */

        FNAND_BBM_DEBUG_I("Valid Mirror BBT found is %d", mirror_desc_p->page_offset);

        ret = FNandReadPage(instance_p, mirror_desc_p->page_offset, buf, 0, bbtlen, NULL, 0, 0, chip_addr);
        if (ret != FT_SUCCESS)
        {
            FNAND_BBM_DEBUG_I("Valid Mirror BBT found is error 0x%x", ret);
            return ret;
        }

        /*
        * Convert flash BBT to memory based BBT
        */
        FNandConvertBbt(instance_p, &buf[0], chip_addr);
        desc_p->version = mirror_desc_p->version;

        /*
        * Write the BBT to Mirror BBT location in flash
        */
        ret = FNandWriteBbt(instance_p, desc_p,
                            mirror_desc_p, chip_addr);
        if (ret != FT_SUCCESS)
        {
            return ret;
        }
    }
    return FT_SUCCESS;
}



static void FNandBbtDumpDebug(FNand *instance_p)
{
    int i;
    FNAND_BBM_DEBUG_W("/********************* Master bbt descriptor **********************/");

    FNAND_BBM_DEBUG_I("page_offset 0x%x", instance_p->bbt_manager[0].bbt_desc.page_offset);  /* Page offset where BBT resides */
    FNAND_BBM_DEBUG_I("sig_offset 0x%x", instance_p->bbt_manager[0].bbt_desc.sig_offset);   /* Signature offset in Spare area */
    FNAND_BBM_DEBUG_I("ver_offset 0x%x", instance_p->bbt_manager[0].bbt_desc.ver_offset);   /* Offset of BBT version */
    FNAND_BBM_DEBUG_I("sig_length 0x%x", instance_p->bbt_manager[0].bbt_desc.sig_length);   /* Length of the signature */
    FNAND_BBM_DEBUG_I("max_blocks 0x%x", instance_p->bbt_manager[0].bbt_desc.max_blocks);   /* Max blocks to search for BBT */
    for (i = 0; i < 4; i++)
    {
        FNAND_BBM_DEBUG_I("Signature[%d] %c", i, instance_p->bbt_manager[0].bbt_desc.signature[i]);
    }
    FNAND_BBM_DEBUG_I("version 0x%x", instance_p->bbt_manager[0].bbt_desc.version);       /* BBT version */
    FNAND_BBM_DEBUG_I("valid 0x%x", instance_p->bbt_manager[0].bbt_desc.valid);        /* BBT descriptor is valid or not */

    FNAND_BBM_DEBUG_W("/********************* Mirror bbt descriptor **********************/");
    FNAND_BBM_DEBUG_I("page_offset 0x%x", instance_p->bbt_manager[0].bbt_mirror_desc.page_offset);  /* Page offset where BBT resides */
    FNAND_BBM_DEBUG_I("sig_offset 0x%x", instance_p->bbt_manager[0].bbt_mirror_desc.sig_offset);   /* Signature offset in Spare area */
    FNAND_BBM_DEBUG_I("ver_offset 0x%x", instance_p->bbt_manager[0].bbt_mirror_desc.ver_offset);   /* Offset of BBT version */
    FNAND_BBM_DEBUG_I("sig_length 0x%x", instance_p->bbt_manager[0].bbt_mirror_desc.sig_length);   /* Length of the signature */
    FNAND_BBM_DEBUG_I("max_blocks 0x%x", instance_p->bbt_manager[0].bbt_mirror_desc.max_blocks);   /* Max blocks to search for BBT */
    for (i = 0; i < 4; i++)
    {
        FNAND_BBM_DEBUG_I("signature[%d] %c", i, instance_p->bbt_manager[0].bbt_mirror_desc.signature[i]);
    }
    FNAND_BBM_DEBUG_I("version 0x%x", instance_p->bbt_manager[0].bbt_mirror_desc.version);       /* BBT version */
    FNAND_BBM_DEBUG_I("valid 0x%x", instance_p->bbt_manager[0].bbt_mirror_desc.valid);        /* BBT descriptor is valid or not */


    FNAND_BBM_DEBUG_W("/********************* Bbt info **********************/");
    FtDumpHexWord((const u32 *)instance_p->bbt_manager[0].bbt, instance_p->nand_geometry[0].num_blocks >>
                  FNAND_BBT_BLOCK_SHIFT);
}

/**
 * @name: FNandScanBbt
 * @msg:  This function reads the Bad Block Table(BBT) if present in flash.
 * @note:
 * @param {FNand} *instance_p is the pointer to the FNand instance.
 * @param {u32} chip_addr is chip address
 * @return {FError}
 */
FError FNandScanBbt(FNand *instance_p, u32 chip_addr)
{
    FError ret;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);

    if (FNandReadBbt(instance_p, chip_addr) != FT_SUCCESS)
    {
        /*
        * Create memory based Bad Block Table(BBT)
        */
        FNandCreateBbt(instance_p, chip_addr);

        /*
        * Write the Bad Block Table(BBT) to the flash
        */
        ret = FNandWriteBbt(instance_p,
                            &instance_p->bbt_manager[chip_addr].bbt_desc,
                            &instance_p->bbt_manager[chip_addr].bbt_mirror_desc, chip_addr);
        if (ret != FT_SUCCESS)
        {
            return ret;
        }

        /*
        * Write the Mirror Bad Block Table(BBT) to the flash
        */
        ret = FNandWriteBbt(instance_p,
                            &instance_p->bbt_manager[chip_addr].bbt_mirror_desc,
                            &instance_p->bbt_manager[chip_addr].bbt_desc, chip_addr);
        if (ret != FT_SUCCESS)
        {
            return ret;
        }

        /*
        * Mark the blocks containing Bad Block Table(BBT) as Reserved
        */
        FNandMarkBbt(instance_p, &instance_p->bbt_manager[chip_addr].bbt_desc, chip_addr);
        FNandMarkBbt(instance_p, &instance_p->bbt_manager[chip_addr].bbt_mirror_desc, chip_addr);

        FNAND_BBM_DEBUG_I("New bbt is ready");

        FNandBbtDumpDebug(instance_p) ;

    }
    else
    {
        FNAND_BBM_DEBUG_I("Old bbt is valid");
        FNandBbtDumpDebug(instance_p) ;
    }

    return FT_SUCCESS;
}


/**
 * @name:  FNandIsBlockBad
 * @msg:   This function checks whether a block is bad or not.
 * @note:
 * @param {FNand} *instance_p is the pointer to the FNand instance.
 * @param {u32} block is the fnand flash block number
 * @param {u32} chip_addr is chip address
 * @return {FError}  FT_SUCCESS if block is bad
 */
FError FNandIsBlockBad(FNand *instance_p, u32 block, u32 chip_addr)
{
    u8 data;
    u8 block_shift;
    u8 BlockType;
    u32 BlockOffset;

    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT_MSG(block < instance_p->nand_geometry[chip_addr].num_blocks, "block is %d,num_blocks is %d", block, instance_p->nand_geometry[chip_addr].num_blocks);

    BlockOffset = block >> FNAND_BBT_BLOCK_SHIFT;
    block_shift = FNAND_BBTBLOCKSHIFT(block);
    data = instance_p->bbt_manager[chip_addr].bbt[BlockOffset]; /* Block information in BBT */
    BlockType = (data >> block_shift) & FNAND_BLOCK_TYPE_MASK;

    if (BlockType != FNAND_BLOCK_GOOD)
    {
        return FT_SUCCESS;
    }
    else
    {
        return FNAND_VALUE_FAILURE;
    }
}



/**
 * @name: FNandMarkBlockBad
 * @msg:  This function marks a block as bad in the RAM based Bad Block Table(BBT).
 * @note:
 * @param {FNand} *instance_p is the pointer to the FNand instance.
 * @param {u32} block is the fnand flash block number
 * @param {u32} chip_addr is chip address
 * @return {*} FT_SUCCESS if successful
 */
FError FNandMarkBlockBad(FNand *instance_p, u32 block, u32 chip_addr)
{
    u8 data;
    u8 block_shift;
    u32 block_offset;
    u8 oldval;
    u8 newval;
    u32 Status;

    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(block < instance_p->nand_geometry[chip_addr].num_blocks);

    block_offset = block >> FNAND_BBT_BLOCK_SHIFT;
    block_shift = FNAND_BBTBLOCKSHIFT(block);
    data = instance_p->bbt_manager[chip_addr].bbt[block_offset]; /* Block information in BBT */

    /*
     * Mark the block as bad in the RAM based Bad Block Table
     */
    oldval = data;
    data &= ~(FNAND_BLOCK_TYPE_MASK << block_shift);
    data |= (FNAND_BLOCK_BAD << block_shift);
    newval = data;
    instance_p->bbt_manager[chip_addr].bbt[block_offset] = data;

    /*
     * Update the Bad Block Table(BBT) in flash
     */
    if (oldval != newval)
    {
        Status = FNandUpdateBbt(instance_p, chip_addr);
        if (Status != FT_SUCCESS)
        {
            return Status;
        }
    }
    return FT_SUCCESS;
}