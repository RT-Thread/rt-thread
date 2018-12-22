/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define __LITTLE_ENDIAN

#ifndef POLLING_AMD_DQ6
#define POLLING_AMD_DQ7
#endif

#include <stdio.h>
#include <string.h>
#include "cfi_flash.h"

/* Global variable */
flash_info_t flash_info[CFG_MAX_FLASH_BANKS];

/* Static variable */
static uint32_t bank_base[CFG_MAX_FLASH_BANKS];
static const uint32_t offset_multiply[9][5] = {
/* chip width = 0 (dummy), 1 (8-bit), 2 (16-bit), 3 (dummy), 4(32-bit) */
    {0, 0, 0, 0, 0},            /* dummy */
    {0, 1, 0, 0, 0},            /* port width = 1 (8-bit) */
    {0, 4, 2, 0, 0},            /* port width = 2 (16-bit) */
    {0, 0, 0, 0, 0},            /* dummy */
    {0, 8, 4, 0, 4},            /* port width = 4 (32-bit) */
    {0, 0, 0, 0, 0},            /* 5, dummy */
    {0, 0, 0, 0, 0},            /* 6, dummy */
    {0, 0, 0, 0, 0},            /* 7, dummy */
    {0, 16, 8, 0, 8},           /* port width = 8 (64-bit) */
};

/* Static function */
static uint32_t get_timer(uint32_t base)
{
    static uint32_t timer_counter = 0;

    if (base == 0)
        timer_counter = 0;
    else
        timer_counter++;

    return timer_counter;
}

static uint8_t *flash_make_addr(flash_info_t * info, int32_t sect, uint32_t offset)
{
    return ((uint8_t *) (info->start[sect] +
                         (offset * offset_multiply[info->portwidth][info->chipwidth])));
}

static uint8_t flash_read_uint8_t(flash_info_t * info, uint32_t offset)
{
    uint8_t *cp;

    cp = flash_make_addr(info, 0, offset);
#if defined(__LITTLE_ENDIAN)
    return (cp[0]);
#else
    return (cp[info->portwidth - 1]);
#endif
}

static uint16_t flash_read_uint16_t(flash_info_t * info, int32_t sect, uint32_t offset)
{
    uint8_t *addr;
    uint16_t retval;

    addr = flash_make_addr(info, sect, offset);

#if defined(__LITTLE_ENDIAN)
    retval = ((addr[(info->portwidth)] << 8) | addr[0]);
#else
    retval = (uint16_t) ((addr[(2 * info->portwidth) - 1] << 8) | addr[info->portwidth - 1]);
#endif

    return retval;
}

static uint32_t flash_read_long(flash_info_t * info, int32_t sect, uint32_t offset)
{
    uint8_t *addr;
    uint32_t retval;

    addr = flash_make_addr(info, sect, offset);

#if defined(__LITTLE_ENDIAN)
    retval = (addr[0] << 16) | (addr[(info->portwidth)] << 24) |
        (addr[(2 * info->portwidth)]) | (addr[(3 * info->portwidth)] << 8);
#else
    retval = (uint32_t) (addr[(2 * info->portwidth) - 1] << 24) |
        (addr[(info->portwidth) - 1] << 16) |
        (addr[(4 * info->portwidth) - 1] << 8) | addr[(3 * info->portwidth) - 1];
#endif
    return retval;
}

static flash_info_t *flash_get_info(uint32_t base)
{
    int32_t i;
    flash_info_t *info;

    for (i = 0; i < CFG_MAX_FLASH_BANKS; i++) {
        info = &flash_info[i];
        if (info->size && info->start[0] <= base && base <= info->start[0] + info->size - 1)
            break;
    }

    return i == CFG_MAX_FLASH_BANKS ? 0 : info;
}

static void flash_make_cmd(flash_info_t * info, uint8_t cmd, void *cmdbuf)
{
    int32_t i;

#if defined(__LITTLE_ENDIAN)
    uint16_t stmpw;
#endif
    uint8_t *cp = (uint8_t *) cmdbuf;
    if (info->chipwidth < FLASH_CFI_BY32) {
        for (i = 0; i < info->portwidth; i++)
            *cp++ = ((i + 1) % info->chipwidth) ? '\0' : cmd;
    } else {
        uint16_t *ccp = (uint16_t *) cmdbuf;
        uint16_t cmd_16 = cmd + cmd * 256;
        for (i = 0; i < info->portwidth; i = i + 2)
            *ccp++ = ((i + 2) % info->chipwidth) ? '\0' : cmd_16;
    }
#if defined(__LITTLE_ENDIAN)
    switch (info->portwidth) {
    case FLASH_CFI_8BIT:
        break;
    case FLASH_CFI_16BIT:
        stmpw = *(uint16_t *) cmdbuf;
        *(uint16_t *) cmdbuf = __swab16(stmpw);
        break;

    default:
        printf("WARNING: flash_make_cmd: unsuppported LittleEndian mode\n");
        break;
    }
#endif
}

static void flash_add_byte(flash_info_t * info, cfiword_t * cword, uint8_t c)
{
#if defined(__LITTLE_ENDIAN)
    unsigned short w;
#endif

    switch (info->portwidth) {
    case FLASH_CFI_8BIT:
        cword->c = c;
        break;
    case FLASH_CFI_16BIT:
#if defined(__LITTLE_ENDIAN)
        w = c;
        w <<= 8;
        cword->w = (cword->w >> 8) | w;
#else
        cword->w = (cword->w << 8) | c;
#endif
        break;
    }
}

static int32_t find_sector(flash_info_t * info, uint32_t addr)
{
    int32_t sector;

    for (sector = info->sector_count - 1; sector >= 0; sector--) {
        if (addr >= info->start[sector])
            break;
    }
    return sector;
}

static void flash_write_cmd(flash_info_t * info, int32_t sect, uint32_t offset, uint8_t cmd)
{

    cfiptr_t addr;
    cfiword_t cword;

    addr.cp = flash_make_addr(info, sect, offset);
    flash_make_cmd(info, cmd, &cword);
    switch (info->portwidth) {
    case FLASH_CFI_8BIT:
        *addr.cp = cword.c;
        break;
    case FLASH_CFI_16BIT:
        *addr.wp = cword.w;
        break;
    }
}

static void flash_unlock_seq(flash_info_t * info, int32_t sect)
{
    flash_write_cmd(info, sect, AMD_ADDR_START, AMD_CMD_UNLOCK_START);
    flash_write_cmd(info, sect, AMD_ADDR_ACK, AMD_CMD_UNLOCK_ACK);
}

static int32_t flash_isequal(flash_info_t * info, cfiptr_t cptr, uint8_t cmd)
{
    cfiword_t cword;
    int32_t retval;

    flash_make_cmd(info, cmd, &cword);

    switch (info->portwidth) {
    case FLASH_CFI_8BIT:
        retval = (cptr.cp[0] == cword.c);
        break;
    case FLASH_CFI_16BIT:
        retval = (cptr.wp[0] == cword.w);
        break;

    default:
        retval = 0;
        break;
    }
    return retval;
}

static int32_t flash_isset(flash_info_t * info, cfiptr_t cptr, uint8_t cmd)
{
    cfiword_t cword;
    int32_t retval = 0;

    flash_make_cmd(info, cmd, &cword);
    switch (info->portwidth) {
    case FLASH_CFI_8BIT:
        retval = ((cptr.cp[0] & cword.c) == cword.c);
        break;
    case FLASH_CFI_16BIT:
        retval = ((cptr.wp[0] & cword.w) == cword.w);
        break;
    }
    return retval;
}

#ifdef POLLING_AMD_DQ7
static int32_t Data_Polling_Check(flash_info_t * info, cfiptr_t cptr, cfiword_t * cword)
{
    uint8_t read_data = 0, polling_data = 0;

    switch (info->portwidth) {
    case FLASH_CFI_8BIT:
        polling_data = cword->c;
        break;
    case FLASH_CFI_16BIT:
        polling_data = (uint8_t) (cword->w & 0xff);
        break;
    default:
        printf("Error in function %s\n", __FUNCTION__);
    }
    do {
        switch (info->portwidth) {
        case FLASH_CFI_8BIT:
            read_data = cptr.cp[0];
            break;
        case FLASH_CFI_16BIT:
            read_data = (uint8_t) (cptr.wp[0] & 0xff);
            break;
        }
        if ((read_data & AMD_DQ7) == (polling_data & AMD_DQ7))
            break;
    } while ((read_data & AMD_DQ5) != (uint8_t) AMD_DQ5);
    switch (info->portwidth) {
    case FLASH_CFI_8BIT:
        read_data = cptr.cp[0];
        break;
    case FLASH_CFI_16BIT:
        read_data = (uint8_t) (cptr.wp[0] & 0xff);
        break;
    }

    if ((read_data & AMD_DQ7) != (polling_data & AMD_DQ7))
        return ERR_TIMOUT;
    else
        return ERR_OK;
}
#endif

static int32_t flash_toggle(flash_info_t * info, cfiptr_t cptr, uint8_t cmd)
{
    cfiword_t cword;
    int32_t retval;

    flash_make_cmd(info, cmd, &cword);
    switch (info->portwidth) {
    case FLASH_CFI_8BIT:
        retval = ((cptr.cp[0] & cword.c) != (cptr.cp[0] & cword.c));
        break;
    case FLASH_CFI_16BIT:
        retval = ((cptr.wp[0] & cword.w) != (cptr.wp[0] & cword.w));
        break;
    default:
        retval = 0;
        break;
    }
    return retval;
}

static int32_t flash_is_busy(flash_info_t * info, cfiptr_t cptr, cfiword_t * cword)
{
    int32_t retval;

    switch (info->vendor) {
    case CFI_CMDSET_INTEL_STANDARD:
    case CFI_CMDSET_INTEL_EXTENDED:
        retval = !flash_isset(info, cptr, FLASH_STATUS_DONE);
        break;
    case CFI_CMDSET_AMD_STANDARD:
    case CFI_CMDSET_AMD_EXTENDED:
#ifdef POLLING_AMD_DQ7
        retval = Data_Polling_Check(info, cptr, cword); /* data polling for D7 */
#else
        retval = flash_toggle(info, cptr, AMD_STATUS_TOGGLE);
#endif
        break;
    default:
        retval = 0;
    }
    return retval;
}

static int32_t flash_time_out(flash_info_t * info, cfiptr_t cptr)
{
    int32_t retval;

    switch (info->vendor) {
    case CFI_CMDSET_AMD_STANDARD:
    case CFI_CMDSET_AMD_EXTENDED:
        retval = flash_isset(info, cptr, AMD_STATUS_TIMEOUT);
        break;
    default:
        retval = 0;
    }
    return retval;
}

static int32_t flash_status_check_orig(flash_info_t * info, cfiptr_t cptr, cfiword_t * cword,
                                   uint32_t tout, char *prompt)
{
    uint32_t start;

    /* Wait for command completion */
    start = get_timer(0);

    while (flash_is_busy(info, cptr, cword)) {
        if ((flash_time_out(info, cptr)) || ((get_timer(start)) > tout * CFG_HZ)) {
            if (flash_is_busy(info, cptr, cword)) {
                printf("Flash %s timeout at address %x data %x\n",
                       prompt, (uint32_t) cptr.cp, cword->l);
                flash_write_cmd(info, 0, 0, info->cmd_reset);
                return ERR_TIMOUT;
            }
        }
    }

    return ERR_OK;
}

static int32_t flash_status_check(flash_info_t * info, cfiptr_t cptr, cfiword_t * cword, uint32_t tout,
                              char *prompt)
{
    int32_t rc = 0;
    int32_t ready = 0;
    int32_t retry;
    uint16_t data, lastdata;

    retry = ERASE_POLL_LIMIT;

    lastdata = cptr.wp[0];

    while (!ready && retry-- >= 0) {
        data = *cptr.wp;
        if ((data & 0xFFFF) == (lastdata & 0xFFFF)) {   /* test to see if bit6 is NOT toggling */
            ready = 1;
        } else {
            if (data & 0x0020) {
                lastdata = *cptr.wp;
                data = *cptr.wp;
                if ((data & 0xFFFF) != (lastdata & 0xFFFF)) {   /* test to see if bit6 is toggling */
                    rc = 1;
                }
            }
        }
        lastdata = data;
    }
    if (rc || ready == 0) {
        printf("Error wait for flash ready, status = 0x%04x\r\n", data);
        rc = 1;
    }
    return rc;
}

static int32_t flash_full_status_check(flash_info_t * info, cfiptr_t cptr, cfiword_t * cword,
                                   uint32_t tout, char *prompt)
{
    int32_t retcode;

    retcode = flash_status_check(info, cptr, cword, tout, prompt);
    switch (info->vendor) {
    case CFI_CMDSET_INTEL_EXTENDED:
    case CFI_CMDSET_INTEL_STANDARD:
        if ((retcode != ERR_OK)
            && !flash_isequal(info, cptr, FLASH_STATUS_DONE)) {
            retcode = ERR_INVAL;
            printf("Flash %s error at address %8x\n", prompt, (uint32_t) cptr.cp);
            if (flash_isset(info, cptr, FLASH_STATUS_ECLBS | FLASH_STATUS_PSLBS)) {
                printf("Command Sequence Error.\n");
            } else if (flash_isset(info, cptr, FLASH_STATUS_ECLBS)) {
                printf("Block Erase Error.\n");
                retcode = ERR_NOT_ERASED;
            } else if (flash_isset(info, cptr, FLASH_STATUS_PSLBS)) {
                printf("Locking Error\n");
            }
            if (flash_isset(info, cptr, FLASH_STATUS_DPS)) {
                printf("Block locked.\n");
                retcode = ERR_PROTECTED;
            }
            if (flash_isset(info, cptr, FLASH_STATUS_VPENS))
                printf("Vpp Low Error.\n");
        }
        break;
    case CFI_CMDSET_AMD_STANDARD:
    case CFI_CMDSET_AMD_EXTENDED:
        if (retcode != ERR_OK)
            printf("\nError flash status \n");
        break;
    default:
        break;
    }
    flash_write_cmd(info, 0, 0, info->cmd_reset);
    return retcode;
}

static int32_t flash_detect_cfi(flash_info_t * info)
{
    cfiptr_t cptr1, cptr2, cptr3;

    for (info->portwidth = FLASH_CFI_8BIT;
         info->portwidth <= FLASH_CFI_16BIT; info->portwidth <<= 1) {
        for (info->chipwidth = FLASH_CFI_BY8;
             info->chipwidth <= info->portwidth; info->chipwidth <<= 1) {
            cptr1.cp = flash_make_addr(info, 0, FLASH_OFFSET_CFI_RESP);
            cptr2.cp = flash_make_addr(info, 0, FLASH_OFFSET_CFI_RESP + 1);
            cptr3.cp = flash_make_addr(info, 0, FLASH_OFFSET_CFI_RESP + 2);
            flash_write_cmd(info, 0, FLASH_OFFSET_CFI, FLASH_CMD_CFI);
            if (flash_isequal(info, cptr1, 'Q')
                && flash_isequal(info, cptr2, 'R')
                && flash_isequal(info, cptr3, 'Y')) {
                info->interface = flash_read_uint16_t(info, 0, FLASH_OFFSET_INTERFACE);
                return 1;
            }
        }
    }
    printf("Error: CFI flah not found\n");
    return 0;
}

static uint32_t flash_get_size(uint32_t base, int32_t banknum)
{
    flash_info_t *info = &flash_info[banknum];
    int32_t i, j;
    int32_t sect_cnt;
    uint32_t sector;
    uint32_t tmp;
    int32_t size_ratio;
    uint8_t num_erase_regions;
    int32_t erase_region_size;
    int32_t erase_region_count;
    cfiptr_t cptr;

    info->start[0] = base;

    if (flash_detect_cfi(info)) {
        info->vendor = flash_read_uint16_t(info, 0, FLASH_OFFSET_PRIMARY_VENDOR);
        switch (info->vendor) {
        case CFI_CMDSET_INTEL_STANDARD:
        case CFI_CMDSET_INTEL_EXTENDED:
        default:
            info->cmd_reset = FLASH_CMD_RESET;
            break;
        case CFI_CMDSET_AMD_STANDARD:
        case CFI_CMDSET_AMD_EXTENDED:
            info->cmd_reset = AMD_CMD_RESET;
            break;
        }

        size_ratio = info->portwidth / info->chipwidth;
        if ((info->interface == FLASH_CFI_X8X16)
            && (info->chipwidth == FLASH_CFI_BY8)) {
            size_ratio >>= 1;
        }
        num_erase_regions = flash_read_uint8_t(info, FLASH_OFFSET_NUM_ERASE_REGIONS);
        sect_cnt = 0;
        sector = base;
        for (i = 0; i < num_erase_regions; i++) {
            if (i > NUM_ERASE_REGIONS) {
                printf("%d erase regions found, only %d used\n",
                       num_erase_regions, NUM_ERASE_REGIONS);
                break;
            }
            tmp = flash_read_long(info, 0, FLASH_OFFSET_ERASE_REGIONS + i * 4);
            erase_region_size = (tmp & 0xffff) ? ((tmp & 0xffff) * 256) : 128;
            tmp >>= 16;
            erase_region_count = (tmp & 0xffff) + 1;
            for (j = 0; j < erase_region_count; j++) {
                info->start[sect_cnt] = sector;
                sector += (erase_region_size * size_ratio);

                switch (info->vendor) {
                case CFI_CMDSET_INTEL_EXTENDED:
                case CFI_CMDSET_INTEL_STANDARD:
                    cptr.cp = flash_make_addr(info, sect_cnt, FLASH_OFFSET_PROTECT);
                    info->protect[sect_cnt] = flash_isset(info, cptr, FLASH_STATUS_PROTECT);
                    break;
                default:
                    info->protect[sect_cnt] = 0;    /* default: not protected */
                }

                sect_cnt++;
            }
        }

        info->sector_count = sect_cnt;
        /* multiply the size by the number of chips */
        info->size = (1 << flash_read_uint8_t(info, FLASH_OFFSET_SIZE)) * size_ratio;
        info->buffer_size = (1 << flash_read_uint16_t(info, 0, FLASH_OFFSET_BUFFER_SIZE));
        tmp = 1 << flash_read_uint8_t(info, FLASH_OFFSET_ETOUT);
        info->erase_blk_tout = (tmp * (1 << flash_read_uint8_t(info, FLASH_OFFSET_EMAX_TOUT)));

        info->erase_chip_tout = info->erase_blk_tout * info->sector_count;
        tmp = 1 << flash_read_uint8_t(info, FLASH_OFFSET_WBTOUT);
        info->buffer_write_tout = (tmp * (1 << flash_read_uint8_t(info, FLASH_OFFSET_WBMAX_TOUT)));
        tmp = 1 << flash_read_uint8_t(info, FLASH_OFFSET_WTOUT);
        info->write_tout = (tmp * (1 << flash_read_uint8_t(info, FLASH_OFFSET_WMAX_TOUT))) / 1000;
        info->flash_id = FLASH_MAN_CFI;
        if ((info->interface == FLASH_CFI_X8X16) && (info->chipwidth == FLASH_CFI_BY8)) {
            info->portwidth >>= 1;
        }
    } else {
        info->portwidth = 1;
        info->chipwidth = 1;
    }

    flash_write_cmd(info, 0, 0, info->cmd_reset);
    return (info->size);
}

static int32_t flash_write_cfiword(flash_info_t * info, uint32_t dest, cfiword_t * cword)
{

    cfiptr_t ctladdr;
    cfiptr_t cptr;
    int32_t flag, retcode;

    ctladdr.cp = flash_make_addr(info, 0, 0);
    cptr.cp = (uint8_t *) dest;

    /* Check if Flash is (sufficiently) erased */
    switch (info->portwidth) {
    case FLASH_CFI_8BIT:
        flag = ((cptr.cp[0] & cword->c) == cword->c);
        break;
    case FLASH_CFI_16BIT:
        flag = ((cptr.wp[0] & cword->w) == cword->w);
        break;
    default:
        return 2;
    }
    if (!flag)
        return 2;

    switch (info->vendor) {
    case CFI_CMDSET_INTEL_EXTENDED:
    case CFI_CMDSET_INTEL_STANDARD:
        flash_write_cmd(info, 0, 0, FLASH_CMD_CLEAR_STATUS);
        flash_write_cmd(info, 0, 0, FLASH_CMD_WRITE);
        break;
    case CFI_CMDSET_AMD_EXTENDED:
    case CFI_CMDSET_AMD_STANDARD:
        flash_unlock_seq(info, 0);
        flash_write_cmd(info, 0, AMD_ADDR_START, AMD_CMD_WRITE);
        break;
    }

    switch (info->portwidth) {
    case FLASH_CFI_8BIT:
        cptr.cp[0] = cword->c;
        break;
    case FLASH_CFI_16BIT:
        cptr.wp[0] = cword->w;
        break;
    }

    retcode = flash_full_status_check(info, cptr, cword, info->write_tout, "write");
    return retcode;
}

#ifdef CFG_FLASH_USE_BUFFER_WRITE

static int32_t flash_write_cfibuffer(flash_info_t * info, uint32_t dest, uint8_t * cp, int32_t len)
{
    int32_t sector;
    int32_t cnt;
    int32_t retcode;
    cfiptr_t src;
    cfiptr_t dst;
    cfiword_t cword;

    switch (info->vendor) {
    case CFI_CMDSET_INTEL_STANDARD:
    case CFI_CMDSET_INTEL_EXTENDED:
        cword.c = 0xff;
        src.cp = cp;
        dst.cp = (uint8_t *) dest;
        sector = find_sector(info, dest);
        flash_write_cmd(info, sector, 0, FLASH_CMD_CLEAR_STATUS);
        flash_write_cmd(info, sector, 0, FLASH_CMD_WRITE_TO_BUFFER);
        if ((retcode =
             flash_status_check(info, dst, &cword, info->buffer_write_tout,
                                "write to buffer")) == ERR_OK) {
            /* reduce the number of loops by the width of the port */
            switch (info->portwidth) {
            case FLASH_CFI_8BIT:
                cnt = len;
                break;
            case FLASH_CFI_16BIT:
                cnt = len >> 1;
                break;

            default:
                return ERR_INVAL;
                break;
            }
            flash_write_cmd(info, sector, 0, (uint8_t) cnt - 1);
            while (cnt-- > 0) {
                switch (info->portwidth) {
                case FLASH_CFI_8BIT:
                    *dst.cp++ = *src.cp++;
                    break;

                case FLASH_CFI_16BIT:
                    *dst.wp++ = *src.wp++;
                    break;

                default:
                    return ERR_INVAL;
                    break;
                }
            }
            flash_write_cmd(info, sector, 0, FLASH_CMD_WRITE_BUFFER_CONFIRM);
            cword.c = 0xff;
            dst.cp = (uint8_t *) ((uint32_t) dst.cp - info->portwidth);
            retcode =
                flash_full_status_check(info, dst, &cword, info->buffer_write_tout, "buffer write");
        }
        return retcode;

    case CFI_CMDSET_AMD_STANDARD:
    case CFI_CMDSET_AMD_EXTENDED:
        src.cp = cp;
        dst.cp = (uint8_t *) dest;
        sector = find_sector(info, dest);

        flash_unlock_seq(info, 0);
        flash_write_cmd(info, sector, 0, AMD_CMD_WRITE_TO_BUFFER);

        switch (info->portwidth) {
        case FLASH_CFI_8BIT:
            cnt = len;
            flash_write_cmd(info, sector, 0, (uint8_t) cnt - 1);
            while (cnt-- > 0)
                *dst.cp++ = *src.cp++;
            break;
        case FLASH_CFI_16BIT:
            cnt = len >> 1;
            flash_write_cmd(info, sector, 0, (uint8_t) cnt - 1);
            while (cnt-- > 0)
                *dst.wp++ = *src.wp++;
            break;
        default:
            return ERR_INVAL;
        }

        flash_write_cmd(info, sector, 0, AMD_CMD_WRITE_BUFFER_CONFIRM);
        cword.c = 0xff;
        dst.cp -= info->portwidth;
        retcode =
            flash_full_status_check(info, dst, &cword, info->buffer_write_tout, "buffer write");
        return retcode;

    default:
        printf("Unknown Command Set\n");
        return ERR_INVAL;
    }
}
#endif

/* Global function */

void flash_reset(uint32_t flash_base_address)
{
    //reg16_write((flash_base_address+0xAAA), 0xAA);
    //reg16_write((flash_base_address+0x554), 0x55);
    reg16_write((flash_base_address + 0x000), 0xF0);
}

uint32_t flash_init(uint32_t flash_base_addr)
{
    uint32_t size = 0;
    int32_t i;

    bank_base[0] = flash_base_addr;
    for (i = 0; i < CFG_MAX_FLASH_BANKS; ++i) {
        flash_info[i].flash_id = FLASH_UNKNOWN;
        size += flash_info[i].size = flash_get_size(bank_base[i], i);
        if (flash_info[i].flash_id == FLASH_UNKNOWN) {
            printf("## Unknown FLASH on Bank %d - Size = 0x%x = %d MB\n",
                   i, flash_info[i].size, flash_info[i].size << 20);
        }
    }

    /* Monitor protection ON by default */
#ifdef    CFG_MONITOR_BASE
    if (CFG_MONITOR_BASE >= flash_base_addr)
        flash_protect(FLAG_PROTECT_SET,
                      CFG_MONITOR_BASE,
                      CFG_MONITOR_BASE + monitor_flash_len - 1, flash_get_info(CFG_MONITOR_BASE));
#endif

    /* Environment protection ON by default */
#ifdef CFG_ENV_IS_IN_FLASH
    flash_protect(FLAG_PROTECT_SET,
                  CFG_ENV_ADDR, CFG_ENV_ADDR + CFG_ENV_SECT_SIZE - 1, flash_get_info(CFG_ENV_ADDR));
#endif

    /* Redundant environment protection ON by default */
#ifdef CFG_ENV_ADDR_REDUND
    flash_protect(FLAG_PROTECT_SET,
                  CFG_ENV_ADDR_REDUND,
                  CFG_ENV_ADDR_REDUND + CFG_ENV_SIZE_REDUND - 1,
                  flash_get_info(CFG_ENV_ADDR_REDUND));
#endif
    return (size);
}

int32_t flash_erase(flash_info_t * info, int32_t s_first, int32_t s_last)
{
    int32_t rcode = 0;
    int32_t prot;
    cfiword_t cword;
    cfiptr_t cptr;
    int32_t sect;

    cword.c = 0xff;

    if (info->flash_id != FLASH_MAN_CFI) {
        printf("Can't erase unknown flash type - aborted\n");
        return 1;
    }
    if ((s_first < 0) || (s_first > s_last)) {
        printf("- no sectors to erase\n");
        return 1;
    }

    prot = 0;
    for (sect = s_first; sect <= s_last; ++sect) {
        if (info->protect[sect]) {
            prot++;
        }
    }
    if (prot) {
        printf("- Warning: %d protected sectors will not be erased!\n", prot);
        return 1;
    }

    if (s_first == 0 && s_last == (info->sector_count - 1)
        && (info->vendor == CFI_CMDSET_AMD_STANDARD || info->vendor == CFI_CMDSET_AMD_EXTENDED)) {
        // Erase chip       
        sect = s_first;
        flash_unlock_seq(info, sect);
        flash_write_cmd(info, sect, AMD_ADDR_ERASE_START, AMD_CMD_ERASE_START);
        flash_unlock_seq(info, sect);
        flash_write_cmd(info, sect, AMD_ADDR_ERASE_START, AMD_CMD_ERASE_CHIP);
        cptr.cp = flash_make_addr(info, sect, 0);
        if (flash_full_status_check(info, cptr, &cword, info->erase_chip_tout, "chip erase"))
            rcode = 1;
    } else {
        for (sect = s_first; sect <= s_last; sect++) {
            if (info->protect[sect] == 0) { /* not protected */
                switch (info->vendor) {
                case CFI_CMDSET_INTEL_STANDARD:
                case CFI_CMDSET_INTEL_EXTENDED:
                    flash_write_cmd(info, sect, 0, FLASH_CMD_CLEAR_STATUS);
                    flash_write_cmd(info, sect, 0, FLASH_CMD_BLOCK_ERASE);
                    flash_write_cmd(info, sect, 0, FLASH_CMD_ERASE_CONFIRM);
                    break;
                case CFI_CMDSET_AMD_STANDARD:
                case CFI_CMDSET_AMD_EXTENDED:
                    flash_unlock_seq(info, sect);
                    flash_write_cmd(info, sect, AMD_ADDR_ERASE_START, AMD_CMD_ERASE_START);
                    flash_unlock_seq(info, sect);
                    flash_write_cmd(info, sect, 0, AMD_CMD_ERASE_SECTOR);
                    break;
                default:
                    printf("Unkown flash vendor %d\n", info->vendor);
                    break;
                }
                cptr.cp = flash_make_addr(info, sect, 0);
                if (flash_full_status_check
                    (info, cptr, &cword, info->erase_blk_tout, "sector erase")) {
                    rcode = 1;
                } else {
                    printf(".");
                    if (!(sect % 30) && sect > 0)
                        printf("\n");
                }
            }
        }
    }
    return rcode;
}

void flash_print_info(flash_info_t * info)
{
    int32_t i;

    if (info->flash_id != FLASH_MAN_CFI) {
        printf("missing or unknown FLASH type\n");
        return;
    }

    printf("CFI compatible FLASH (%d port width with %d chip width)\n",
           (info->portwidth << 3), (info->chipwidth << 3));
    printf("Command set is ");
    switch (info->vendor) {
    case CFI_CMDSET_INTEL_EXTENDED:
        printf("Intel/Sharp extended\n");
        break;
    case CFI_CMDSET_AMD_STANDARD:
        printf("AMD/Fujitsu standard. ");
#ifdef POLLING_AMD_DQ7
        printf("Driver is polling DQ7 for status checking.\n");
#else
        printf("Driver is polling DQ6 for status checking.\n");
#endif
        break;
    case CFI_CMDSET_INTEL_STANDARD:
        printf("Intel/Sharp standard\n");
        break;
    case CFI_CMDSET_AMD_EXTENDED:
        printf("AMD/Fujitsu extended\n");
#ifdef POLLING_AMD_DQ7
        printf("Driver is polling DQ7 for status checking.\n");
#else
        printf("Driver is polling DQ6 for status checking.\n");
#endif
        break;
    case CFI_CMDSET_MITSU_STANDARD:
        printf("Mitsubishi standard\n");
        break;
    case CFI_CMDSET_MITSU_EXTENDED:
        printf("Mitsubishi extendend\n");
        break;
    default:
        printf("Not defined\n");
        break;
    }

    for (i = 0; i < info->sector_count; ++i) {
#ifdef CFG_FLASH_EMPTY_INFO
        int32_t k;
        int32_t size;
        int32_t erased;
        uint32_t *flash;

        /* Check if whole sector is erased */
        if (i != (info->sector_count - 1))
            size = info->start[i + 1] - info->start[i];
        else
            size = info->start[0] + info->size - info->start[i];
        erased = 1;
        flash = (uint32_t *) info->start[i];
        size = size >> 2;       /* divide by 4 for longword access */
        for (k = 0; k < size; k++) {
            if (*flash++ != 0xffffffff) {
                erased = 0;
                break;
            }
        }

        if ((i % 5) == 0)
            printf("\n");
        /* print empty and read-only info */
        printf(" %8X%s%s", info->start[i], erased ? " E" : "  ", info->protect[i] ? "RO " : "   ");
#else
        if ((i % 5) == 0)
            printf("\n   ");
        printf(" %8x%s", info->start[i], info->protect[i] ? " (RO)  " : "     ");
#endif
    }
    printf("\n");
    return;
}

int32_t write_buff(flash_info_t * info, uint8_t * src, uint32_t addr, uint32_t cnt)
{
    uint32_t wp;
    uint32_t cp;
    int32_t aln;
    cfiword_t cword;
    int32_t i, rc;
    int32_t byte_idx;

#ifdef CFG_FLASH_USE_BUFFER_WRITE
    int32_t buffered_size;
#endif
    /* get lower aligned address */
    wp = (addr & ~(info->portwidth - 1));

    for (byte_idx = 0; byte_idx < info->portwidth; byte_idx++) {
        if (*(uint8_t *) wp != (uint8_t) 0xff) {
            printf("Error write_buff():Flash is not erased on the address 0x%8x, read 0x%8x\n", wp,
                   *(uint8_t *) wp);
            return 1;
        }
    }

    /* handle unaligned start */
    if ((aln = addr - wp) != 0) {
        cword.l = 0;
        cp = wp;
        for (i = 0; i < aln; ++i, ++cp) {
            flash_add_byte(info, &cword, (*(uint8_t *) cp));
        }

        for (; (i < info->portwidth) && (cnt > 0); i++) {
            flash_add_byte(info, &cword, *src++);
            cnt--;
            cp++;
        }
        for (; (cnt == 0) && (i < info->portwidth); ++i, ++cp)
            flash_add_byte(info, &cword, (*(uint8_t *) cp));
        if ((rc = flash_write_cfiword(info, wp, &cword)) != 0)
            return rc;
        wp = cp;
    }

    /* handle the aligned part */
#ifdef CFG_FLASH_USE_BUFFER_WRITE
    buffered_size = (info->portwidth / info->chipwidth);
    buffered_size *= info->buffer_size;
    while (cnt >= info->portwidth) {
        /* prohibit buffer write when buffer_size is 1 */
        if (info->buffer_size == 1 || cnt == info->portwidth) {
            cword.l = 0;
            for (i = 0; i < info->portwidth; i++)
                flash_add_byte(info, &cword, *src++);
            if ((rc = flash_write_cfiword(info, wp, &cword)) != 0)
                return rc;
            wp += info->portwidth;
            cnt -= info->portwidth;
            continue;
        }

        /* write buffer until next buffered_size aligned boundary */
        i = buffered_size - (wp % buffered_size);
        if (i > cnt)
            i = cnt;
        if ((rc = flash_write_cfibuffer(info, wp, src, i)) != ERR_OK)
            return rc;
        i -= i & (info->portwidth - 1);
        wp += i;
        src += i;
        cnt -= i;
        if (!(cnt % 0x40000) && cnt > 0) {
            printf(".");
        }
    }
#else
    while (cnt >= info->portwidth) {
        cword.l = 0;
        for (i = 0; i < info->portwidth; i++) {
            flash_add_byte(info, &cword, *src++);
        }
        if ((rc = flash_write_cfiword(info, wp, cword)) != 0)
            return rc;
        wp += info->portwidth;
        cnt -= info->portwidth;
        for (byte_idx = 0; byte_idx < info->portwidth; byte_idx++) {
            if (*(uint8_t *) wp != (uint8_t) 0xff) {
                printf("Error:Flash is not erased on the address 0x%8x, read 0x%8x\n", wp,
                       *(uint8_t *) wp);
                return 1;
            }
        }
    }
#endif /* CFG_FLASH_USE_BUFFER_WRITE */
    if (cnt == 0) {
        return (0);
    }

    /* handle unaligned tail bytes */
    cword.l = 0;
    for (i = 0, cp = wp; (i < info->portwidth) && (cnt > 0); ++i, ++cp) {
        flash_add_byte(info, &cword, *src++);
        --cnt;
    }
    for (; i < info->portwidth; ++i, ++cp) {
        flash_add_byte(info, &cword, (*(uint8_t *) cp));
    }

    return flash_write_cfiword(info, wp, &cword);
}

#ifdef CFG_FLASH_PROTECTION

int32_t flash_real_protect(flash_info_t * info, int32_t sector, int32_t prot)
{
    int32_t retcode = 0;
    cfiword_t cword;
    cfiptr_t cptr;

    flash_write_cmd(info, sector, 0, FLASH_CMD_CLEAR_STATUS);
    flash_write_cmd(info, sector, 0, FLASH_CMD_PROTECT);
    if (prot)
        flash_write_cmd(info, sector, 0, FLASH_CMD_PROTECT_SET);
    else
        flash_write_cmd(info, sector, 0, FLASH_CMD_PROTECT_CLEAR);

    cptr.cp = flash_make_addr(info, sector, 0);
    cword.c = 0xff;

    if ((retcode =
         flash_full_status_check(info, cptr, &cword, info->erase_blk_tout,
                                 prot ? "protect" : "unprotect")) == 0) {

        info->protect[sector] = prot;
        if (prot == 0) {
            int32_t i;

            for (i = 0; i < info->sector_count; i++) {
                if (info->protect[i])
                    flash_real_protect(info, i, 1);
            }
        }
    }
    return retcode;
}

void flash_read_user_serial(flash_info_t * info, void *buffer, int32_t offset, int32_t len)
{
    uint8_t *src, *dst = buffer;

    src = flash_make_addr(info, 0, FLASH_OFFSET_USER_PROTECTION);
    flash_write_cmd(info, 0, 0, FLASH_CMD_READ_ID);
    memcpy(dst, src + offset, len);
    flash_write_cmd(info, 0, 0, info->cmd_reset);
}

void flash_read_factory_serial(flash_info_t * info, void *buffer, int32_t offset, int32_t len)
{
    uint8_t *src;

    src = flash_make_addr(info, 0, FLASH_OFFSET_INTEL_PROTECTION);
    flash_write_cmd(info, 0, 0, FLASH_CMD_READ_ID);
    memcpy(buffer, src + offset, len);
    flash_write_cmd(info, 0, 0, info->cmd_reset);
}

#endif
