/*
 * Copyright (C) 2017 ALLWINNERTECH TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of ALLWINNERTECH TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "stdint.h"
#include "sys/param.h"
#include "sys/endian.h"


#include "hal_sdhost.h"
#include "sdmmc.h"
#include "sdio.h"


#include "_sd_define.h"
#include "_core.h"
#include "_sdio.h"

#ifdef CONFIG_USE_SDIO

//inline int mmc_io_rw_direct(struct mmc_card *card, int32_t write, uint32_t fn, uint32_t addr, uint8_t in, uint8_t *out);


#define SDIO_MIN(a, b)          MIN(a, b)


/*
 * Calculate the maximum byte mode transfer size
 */
static inline unsigned int sdio_max_byte_size(struct sdio_func *func)
{
    unsigned mval = func->card->host->max_blk_size;

    //if (mmc_blksz_for_byte_mode(func->card))
    //  mval = min(mval, func->cur_blksize);
    //else
        mval = SDIO_MIN(mval, func->max_blksize);

    //if (mmc_card_broken_byte_mode_512(func->card))
        return SDIO_MIN(mval, 511u);

    return SDIO_MIN(mval, 512u); /* maximum size for byte mode */
}



#ifdef CONFIG_SDIO_USE_FUNS
static int32_t cistpl_vers_1(struct mmc_card *card, struct sdio_func *func,
             const unsigned char *buf, uint32_t size)
{
    uint32_t i, nr_strings;
    char **buffer, *string;

    /* Find all null-terminated (including zero length) strings in
       the TPLLV1_INFO field. Trailing garbage is ignored. */
    buf += 2;
    size -= 2;

    nr_strings = 0;
    for (i = 0; i < size; i++) {
        if (buf[i] == 0xff)
            break;
        if (buf[i] == 0)
            nr_strings++;
    }
    if (nr_strings == 0)
        return 0;

    size = i;

    buffer = HAL_Malloc(sizeof(char *) * nr_strings + size);
    SDC_Memset(buffer, 0, sizeof(char *) * nr_strings + size);
    if (!buffer)
        return -1;

    string = (char*)(buffer + nr_strings);

    for (i = 0; i < nr_strings; i++) {
        buffer[i] = string;
        strcpy(string, (char *)buf);
        string += strlen(string) + 1;
        buf += strlen((char *)buf) + 1;
    }

    if (func) {
        func->num_info = nr_strings;
        func->info = (const char**)buffer;
    } else {
        card->num_info = nr_strings;
        card->info = (const int8_t **)buffer;
    }

    return 0;
}

static int32_t cistpl_manfid(struct mmc_card *card, struct sdio_func *func,
             const unsigned char *buf, unsigned size)
{
    uint32_t vendor, device;

    /* TPLMID_MANF */
    vendor = buf[0] | (buf[1] << 8);

    /* TPLMID_CARD */
    device = buf[2] | (buf[3] << 8);

    if (func) {
        func->vendor = vendor;
        func->device = device;
    } else {
        card->cis.vendor = vendor;
        card->cis.device = device;
    }

    return 0;
}

static const unsigned char speed_val[16] =
    { 0, 10, 12, 13, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 70, 80 };
static const uint32_t speed_unit[8] =
    { 10000, 100000, 1000000, 10000000, 0, 0, 0, 0 };


typedef int32_t (tpl_parse_t)(struct mmc_card *, struct sdio_func *, const unsigned char *, unsigned);

struct cis_tpl {
    unsigned char code;
    unsigned char min_size;
    tpl_parse_t *parse;
};

static int32_t cis_tpl_parse(struct mmc_card *card, struct sdio_func *func,
             const char *tpl_descr,
             const struct cis_tpl *tpl, int32_t tpl_count,
             uint8_t code, const uint8_t *buf, uint32_t size)
{
    int32_t i, ret = 0;

    /* look for a matching code in the table */
    for (i = 0; i < tpl_count; i++, tpl++) {
        if (tpl->code == code)
            break;
    }
    if (i < tpl_count) {
        if (size >= tpl->min_size) {
            if (tpl->parse)
                ret = tpl->parse(card, func, buf, size);
            else
                ret = 0; /* known tuple, not parsed */
        } else {
            /* invalid tuple */
            ret = -1;
        }
        if (ret) {
            SD_LOGW("%s: bad %s tuple 0x%02x (%u bytes)\n",
                   __func__, tpl_descr, (unsigned int)code, (unsigned int)size);
        }
    } else {
        /* warn about unknown tuples */
        SD_LOGW("%s: queuing unknown CIS tuple 0x%02x (%u bytes)\n",
            __func__, (unsigned int)code, (unsigned int)size);
    }

    return ret;
}

static int32_t cistpl_funce_common(struct mmc_card *card, struct sdio_func *func,
                   const unsigned char *buf, unsigned size)
{
    /* Only valid for the common CIS (function 0) */
    if (func)
        return -1;

    /* TPLFE_FN0_BLK_SIZE */
    card->cis.blksize = buf[1] | (buf[2] << 8);

    /* TPLFE_MAX_TRAN_SPEED */
    card->cis.max_dtr = speed_val[(buf[3] >> 3) & 15] *
                speed_unit[buf[3] & 7];

    return 0;
}

static int32_t cistpl_funce_func(struct mmc_card *card, struct sdio_func *func,
                 const unsigned char *buf, uint32_t size)
{
    uint32_t vsn;
    uint32_t min_size;

    /* Only valid for the individual function's CIS (1-7) */
    if (!func)
        return -1;

    /*
     * This tuple has a different length depending on the SDIO spec
     * version.
     */
    vsn = func->card->cccr.sdio_vsn;
    min_size = (vsn == SDIO_SDIO_REV_1_00) ? 28 : 42;

    if (size < min_size)
        return -1;

    /* TPLFE_MAX_BLK_SIZE */
    func->max_blksize = buf[12] | (buf[13] << 8);

    /* TPLFE_ENABLE_TIMEOUT_VAL, present in ver 1.1 and above */
#ifdef CONFIG_MMC_ERASE
    if (vsn > SDIO_SDIO_REV_1_00)
        func->enable_timeout = (buf[28] | (buf[29] << 8)) * 10;
    else
        func->enable_timeout = jiffies_to_msecs(HZ);
#endif

    return 0;
}

/*
 * Known TPLFE_TYPEs table for CISTPL_FUNCE tuples.
 *
 * Note that, unlike PCMCIA, CISTPL_FUNCE tuples are not parsed depending
 * on the TPLFID_FUNCTION value of the previous CISTPL_FUNCID as on SDIO
 * TPLFID_FUNCTION is always hardcoded to 0x0C.
 */
static const struct cis_tpl cis_tpl_funce_list[] = {
    {   (unsigned char)0x00,    (unsigned char)4,   (tpl_parse_t *)cistpl_funce_common      },
    {   (unsigned char)0x01,    (unsigned char)0,   (tpl_parse_t *)cistpl_funce_func        },
    {   (unsigned char)0x04,    (unsigned char)(1+1+6), NULL/* CISTPL_FUNCE_LAN_NODE_ID */  },
};

static int32_t cistpl_funce(struct mmc_card *card, struct sdio_func *func,
            const unsigned char *buf, unsigned size)
{
    if (size < 1)
        return -1;

    return cis_tpl_parse(card, func, "CISTPL_FUNCE",
                 cis_tpl_funce_list,
                 HAL_ARRAY_SIZE(cis_tpl_funce_list),
                 buf[0], buf, size);
}

/* Known TPL_CODEs table for CIS tuples */
static const struct cis_tpl cis_tpl_list[] = {
    {   0x15,   3,  (tpl_parse_t *)cistpl_vers_1        },
    {   0x20,   4,  (tpl_parse_t *)cistpl_manfid        },
    {   0x21,   2,  NULL/* cistpl_funcid */ },
    {   0x22,   0,  (tpl_parse_t *)cistpl_funce     },
};

static int32_t sdio_read_cis(struct mmc_card *card, struct sdio_func *func)
{
    int32_t ret;
    struct sdio_func_tuple *this, **prev;
    uint32_t i, ptr = 0;

    /*
     * Note that this works for the common CIS (function number 0) as
     * well as a function's CIS * since SDIO_CCCR_CIS and SDIO_FBR_CIS
     * have the same offset.
     */
    for (i = 0; i < 3; i++) {
        uint8_t x, fn;

        if (func)
            fn = func->num;
        else
            fn = 0;

        ret = mmc_io_rw_direct(card, 0, FN0, SDIO_FBR_BASE(fn) + SDIO_FBR_CIS + i, 0, &x);
        if (ret)
            return ret;
        ptr |= x << (i * 8);
    }

    if (func)
        prev = &func->tuples;
    else
        prev = &card->tuples;

    if (*prev) {
        SD_LOGE("%s,%d no prev found\n", __func__, __LINE__);
        return -1;
    }

    do {
        uint8_t tpl_code, tpl_link;

        ret = mmc_io_rw_direct(card, 0, FN0, ptr++, 0, &tpl_code);
        if (ret)
            break;

        /* 0xff means we're done */
        if (tpl_code == 0xff)
            break;

        /* null entries have no link field or data */
        if (tpl_code == 0x00)
            continue;

        ret = mmc_io_rw_direct(card, 0, FN0, ptr++, 0, &tpl_link);
        if (ret)
            break;

        /* a size of 0xff also means we're done */
        if (tpl_link == 0xff)
            break;

        this = HAL_Malloc(sizeof(*this) + tpl_link);
        if (!this)
            return -1;

        for (i = 0; i < tpl_link; i++) {
            ret = mmc_io_rw_direct(card, 0, FN0, ptr + i, 0, &this->data[i]);
            if (ret)
                break;
        }
        if (ret) {
            HAL_Free(this);
            break;
        }

        /* Try to parse the CIS tuple */
        ret = cis_tpl_parse(card, func, "CIS",
                            cis_tpl_list, HAL_ARRAY_SIZE(cis_tpl_list),
                            tpl_code, this->data, tpl_link);
        if (ret == -1) {
            /*
             * The tuple is unknown or known but not parsed.
             * Queue the tuple for the function driver.
             */
            this->next = NULL;
            this->code = tpl_code;
            this->size = tpl_link;
            *prev = this;
            prev = &this->next;

            /* keep on analyzing tuples */
            ret = 0;
        } else {
            /*
             * We don't need the tuple anymore if it was
             * successfully parsed by the SDIO core or if it is
             * not going to be queued for a driver.
             */
            HAL_Free(this);
        }

        ptr += tpl_link;
    } while (!ret);

    /*
     * Link in all unknown tuples found in the common CIS so that
     * drivers don't have to go digging in two places.
     */
    if (func)
        *prev = card->tuples;

    return ret;
}

int32_t sdio_read_common_cis(struct mmc_card *card)
{
    return sdio_read_cis(card, NULL);
}

void sdio_free_common_cis(struct mmc_card *card)
{
    struct sdio_func_tuple *tuple, *victim;

    tuple = card->tuples;

    while (tuple) {
        victim = tuple;
        tuple = tuple->next;
        HAL_Free(victim);
    }

    card->tuples = NULL;
}

void sdio_free_func_cis(struct sdio_func *func)
{
    struct sdio_func_tuple *tuple, *victim;

    tuple = func->tuples;

    while (tuple && tuple != func->card->tuples) {
        victim = tuple;
        tuple = tuple->next;
        HAL_Free(victim);
    }

    func->tuples = NULL;
}

int sdio_read_func_cis(struct sdio_func *func)
{
    int ret;

    ret = sdio_read_cis(func->card, func);
    if (ret)
        return ret;

    /*
     * Since we've linked to tuples in the card structure,
     * we must make sure we have a reference to it.
     */
//  get_device(&func->card->dev);

    /*
     * Vendor/device id is optional for function CIS, so
     * copy it from the card structure as needed.
     */
    if (func->vendor == 0) {
        func->vendor = func->card->cis.vendor;
        func->device = func->card->cis.device;
    }

    return 0;
}

static int32_t sdio_read_fbr(struct sdio_func *func)
{
    int32_t ret;
    unsigned char data;

    //if (mmc_card_nonstd_func_interface(func->card)) {
    //  func->class = SDIO_CLASS_NONE;
    //  return 0;
    //}

    ret = mmc_io_rw_direct(func->card, 0, FN0,
        SDIO_FBR_BASE(func->num) + SDIO_FBR_STD_IF, 0, &data);
    if (ret)
        goto out;

    data &= 0x0f;

    if (data == 0x0f) {
        ret = mmc_io_rw_direct(func->card, 0, FN0,
            SDIO_FBR_BASE(func->num) + SDIO_FBR_STD_IF_EXT, 0, &data);
        if (ret)
            goto out;
    }

    func->class = data;

out:
    return ret;
}
#endif

static int32_t mmc_send_io_op_cond(struct mmc_card *card, uint32_t ocr, uint32_t *rocr)
{
    struct mmc_command cmd = {0};
    uint32_t i, err = 0;

    cmd.opcode = SD_IO_SEND_OP_COND;
    cmd.arg = ocr;
    cmd.flags = MMC_RSP_SPI_R4 | MMC_RSP_R4 | MMC_CMD_BCR;

    for (i = 1000; i; i--) {
        err = mmc_wait_for_cmd(card->host, &cmd);
        if (err)
            break;

        /* if we're just probing, do a single pass */
        if (ocr == 0)
            break;

        /* otherwise wait until reset completes */
        if (cmd.resp[0] & MMC_CARD_BUSY)
            break;
        err = -1;
        mmc_mdelay(1);
    }

    if (rocr)
        *rocr = cmd.resp[0];

    return err;
}

int32_t
mmc_io_rw_direct_host(struct mmc_host *host, int32_t write, uint32_t fn,
                      uint32_t addr, uint8_t in, uint8_t *out)
{
    struct mmc_command cmd = {0};
    int32_t err;
    uint32_t temp;

    if (!host) {
        SD_LOGE_RAW(ROM_ERR_MASK, "%s,%d no host exist!\n", __func__, __LINE__);
        return -1;
    }
    if (fn > 7) {
        SDC_LOGE("%s,%d wrong fn:%ld!\n", __func__, __LINE__, HAL_PR_SZ_L(fn));
        return -1;
    }

    SDC_LOGD("%s,fun %ld, raw %d ,addr %lx,wrte data %x\n", write?"Write":"Read", HAL_PR_SZ_L(fn), (write && out)?1:0, HAL_PR_SZ_L(addr), in);

    /* sanity check */
    if (addr & ~0x1FFFF)
        return -1;

    cmd.opcode = SD_IO_RW_DIRECT;
    cmd.arg = write ? 0x80000000 : 0x00000000;
    cmd.arg |= fn << 28;
    cmd.arg |= (write && out) ? 0x08000000 : 0x00000000;
    cmd.arg |= addr << 9;
    cmd.arg |= in;
    cmd.flags = MMC_RSP_SPI_R5 | MMC_RSP_R5 | MMC_CMD_AC;

    err = mmc_wait_for_cmd(host, &cmd);
    if (err)
        return err;

    temp = cmd.resp[0];
    if (temp & 0xcf00) {
        SDC_LOGE("CMD52 %s Operation Error:%s%s%s%s%s !\n",
             write           ? "wirte"  : "read",
             temp&0x8000     ? " CMDCRCErr"   : "",
             temp&0x4000     ? " ILLEGALCmd"  : "",
             temp&0x800      ? " GenERR" : "",
             temp&0x200      ? " FucNumErr"   : "",
             temp&0x100      ? " ArgOutRange" : "");
    }

    if (cmd.resp[0] & R5_ERROR)
        return -1;
    if (cmd.resp[0] & R5_FUNCTION_NUMBER)
        return -1;
    if (cmd.resp[0] & R5_OUT_OF_RANGE)
        return -1;

    if (out) {
        *out = cmd.resp[0] & 0xFF;
    }

    return 0;
}

int mmc_io_rw_direct(struct mmc_card *card, int32_t write, uint32_t fn, uint32_t addr, uint8_t in, uint8_t *out)
{
    if (!card) {
        SD_LOGE_RAW(ROM_ERR_MASK, "%s,%d no card exist!\n", __func__, __LINE__);
        return -1;
    }
    return mmc_io_rw_direct_host(card->host, write, fn, addr, in, out);
}

/**
 *  SDIO Spec: CMD53 is 48 bit long. read or write multiple I/O registers with a
 *    single command
 *  ----------------------------------------------------------------------------
 *  S|D|CMDIND|R|FUN|BLOCK MODE|OP CODE|REGISTER ADDRESS|BYTE/BLOCK COUNT|CRC7|E
 *  ----------------------------------------------------------------------------
 *  @ret : RET_OK, RET_FAIL
 */
 int32_t
mmc_io_rw_extended(struct mmc_card *card, uint8_t write, uint8_t fn, uint32_t addr, uint32_t incr_addr,
               const void *buf, uint32_t blocks, uint32_t blksz)
{
    struct mmc_request mrq;
    struct mmc_command cmd = {0};
    struct mmc_data data = {0};
    struct scatterlist sg = {0};
    int32_t ret;

    if (fn > 7) {
        SD_LOGE("%s,%d err fn:%d\n", __func__, __LINE__, fn);
        return -1;
    }
    SDC_WARN_ON(blksz == 0);

    /* sanity check */
    if (addr & ~0x1FFFF)
        return -1;

    cmd.opcode = SD_IO_RW_EXTENDED;                         /* cmd53 --index */
    cmd.arg = write ? 0x80000000 : 0x00000000;              /* write/read --flag */
    cmd.arg |= fn << 28;                                    /* function number */
    cmd.arg |= incr_addr ? 0x04000000 : 0x00000000;         /* incrementing address */
    cmd.arg |= addr << 9;

    if (blocks == 0 )
        cmd.arg |= (blksz == 512) ? 0 : blksz;          /* byte mode */
    else
        cmd.arg |= 0x08000000| blocks;                  /* block mode */

    cmd.flags = MMC_RSP_SPI_R5 | MMC_RSP_R5 | MMC_CMD_ADTC;
    data.blksz = blksz;

    data.blocks = blocks ? blocks : 1;
    data.flags = write ? MMC_DATA_WRITE : MMC_DATA_READ;
    data.sg = &sg;
    data.sg_len = 1;

    sg.buffer = (void *)buf;
    sg.len = data.blksz * data.blocks;

    mrq.cmd = &cmd;
    mrq.data = &data;

    SD_LOGD("starting %s CMD%ld add %lx,arg 0x%08lx flags %lx\n", write?"Write":"Read", HAL_PR_SZ_L(cmd.opcode), HAL_PR_SZ_L(addr), HAL_PR_SZ_L(cmd.arg), HAL_PR_SZ_L(cmd.flags));
    SD_LOGD("blksz %ld blocks %ld flags %lx\n", HAL_PR_SZ_L(data.blksz), HAL_PR_SZ_L(data.blocks), HAL_PR_SZ_L(data.flags));
    ret = mmc_wait_for_req(card->host, &mrq);
    if (ret) {
        SD_LOGE("SDC write operation failed\n");
    }
    if (cmd.resp[0] & R5_ERROR)
        return -1;
    if (cmd.resp[0] & R5_FUNCTION_NUMBER)
        return -1;
    if (cmd.resp[0] & R5_OUT_OF_RANGE)
        return -1;
//  printf("%s,%d,%x\n", __FUNCTION__,__LINE__, sg.buffer);

    return ret;
}

/**
 *  read/write IO memory in Block/Stream mode with fixed/increaming address
 *    This will split an arbitrarily sized data transfer into several IO_RW_EXTENDED commands.
 *  @func_num: function number
 *  @write: IOMEM_WR:write, IOMEM_RD:read
 *  @addr: address of register read from or write to
 *  @incr_addr: 1: in, 0: not, used for fifio
 *  @buf: pointer to data buffer
 *  @size: block counter(block mode)/byte counter(byte mode)
 *  @ret: RET_OK, RET_FAIL
 */
static int32_t
sdio_io_rw_ext_helper(struct mmc_card *card, uint8_t func_num, int32_t write, uint32_t addr,
                      uint32_t incr_addr, uint8_t *buf, uint32_t size)
{
    uint32_t remainder = size;
    int32_t ret = -1;
    uint32_t blocks;
    int32_t fn_bsize;
    uint8_t *buf_tmp = buf;

    /* Do the bulk of the transfer using block mode (if supported). */
    //if (func->card->cccr.multi_block && (size > sdio_max_byte_size(func))) {
    fn_bsize = card->fn_bsize[func_num];
    /* Do the bulk of the transfer using block mode (if supported). */
    while (remainder >= fn_bsize) {
        blocks = remainder / fn_bsize;
        size = blocks * fn_bsize;

        ret = mmc_io_rw_extended(card, write, func_num, addr, incr_addr, buf, blocks, fn_bsize);
        if (ret) {
            SD_LOGE("%s,%d %s IO%x [%lx] SZ:%ld Err:%ld !!\n", __func__, __LINE__,
                      write?"W":"R", func_num, HAL_PR_SZ_L(addr), HAL_PR_SZ_L(size), HAL_PR_SZ_L(ret));
            return ret;
        }
        remainder -= size;
        buf += size;
        if (incr_addr)
            addr += size;
    }

    /* Write the remainder using byte mode. */
    while (remainder > 0) {
        size = SDIO_MIN(remainder, 512);

        ret = mmc_io_rw_extended(card, write, func_num, addr, incr_addr, buf, 0, size);
        if (ret) {
            SD_LOGE("%s,%d %s IO%x [%lx] SZ:%ld Err:%ld !!\n", __func__, __LINE__,
                      write?"W":"R", func_num, HAL_PR_SZ_L(addr), HAL_PR_SZ_L(size), HAL_PR_SZ_L(ret));
            return ret;
        }
        remainder -= size;
        buf += size;
        if (incr_addr)
            addr += size;
    }

//  printf("%s,%d,%x %x,%x\n", __FUNCTION__,__LINE__, buf_tmp,(uint32_t)buf_tmp, (uint32_t)buf);
    return ret;
}

/**
 *  sdio_readb - read a single byte from a SDIO function
 *  @func_num: SDIO function to access
 *  @addr: address to read
 *  @err_ret: optional status value from transfer
 *
 *  Reads a single byte from the address space of a given SDIO
 *  function. If there is a problem reading the address, 0xff
 *  is returned and @err_ret will contain the error code.
 */
uint8_t sdio_readb(struct mmc_card *card, uint32_t func_num, uint32_t addr, int32_t *err_ret)
{
    int32_t ret;
    uint8_t val;

    if (err_ret)
        *err_ret = 0;

    ret = mmc_io_rw_direct_host(card->host, 0, func_num, addr, 0, &val);
    if (ret) {
        if (err_ret)
            *err_ret = ret;
        return 0xFF;
    }

    return val;
}

/**
 *  sdio_writeb - write a single byte to a SDIO function
 *  @func_num: SDIO function to access
 *  @b: byte to write
 *  @addr: address to write to
 *  @err_ret: optional status value from transfer
 *
 *  Writes a single byte to the address space of a given SDIO
 *  function. @err_ret will contain the status of the actual
 *  transfer.
 */
void sdio_writeb(struct mmc_card *card, uint32_t func_num, const uint8_t b, uint32_t addr, int32_t *err_ret)
{
    int32_t ret;

    ret = mmc_io_rw_direct_host(card->host, 1, func_num, addr, b, NULL);
    if (err_ret)
        *err_ret = ret;
}



/**
 *  sdio_readw - read a 16 bit integer from a SDIO function
 *  @func: SDIO function to access
 *  @addr: address to read
 *  @err_ret: optional status value from transfer
 *
 *  Reads a 16 bit integer from the address space of a given SDIO
 *  function. If there is a problem reading the address, 0xffff
 *  is returned and @err_ret will contain the error code.
 */
uint16_t sdio_readw(struct sdio_func *func, unsigned int addr, int *err_ret)
{
    int ret;

    if (err_ret)
        *err_ret = 0;

    ret = sdio_memcpy_fromio(func->card, func->num,func->tmpbuf, addr, 2);
    if (ret) {
        if (err_ret)
            *err_ret = ret;
        return 0xFFFF;
    }

    //return le16_to_cpup((__le16 *)func->tmpbuf);
    return le16toh( *((uint16_t *)func->tmpbuf));
}
//EXPORT_SYMBOL_GPL(sdio_readw);

/**
 *  sdio_writew - write a 16 bit integer to a SDIO function
 *  @func: SDIO function to access
 *  @b: integer to write
 *  @addr: address to write to
 *  @err_ret: optional status value from transfer
 *
 *  Writes a 16 bit integer to the address space of a given SDIO
 *  function. @err_ret will contain the status of the actual
 *  transfer.
 */
void sdio_writew(struct sdio_func *func, uint16_t b, unsigned int addr, int *err_ret)
{
    int ret;

    //*(__le16 *)func->tmpbuf = cpu_to_le16(b);
    *(int16_t *)func->tmpbuf = cpu_to_le16(b);

    ret = sdio_memcpy_toio(func->card, func->num, addr, func->tmpbuf, 2);
    if (err_ret)
        *err_ret = ret;
}
//EXPORT_SYMBOL_GPL(sdio_writew);

/**
 *  sdio_readl - read a 32 bit integer from a SDIO function
 *  @func: SDIO function to access
 *  @addr: address to read
 *  @err_ret: optional status value from transfer
 *
 *  Reads a 32 bit integer from the address space of a given SDIO
 *  function. If there is a problem reading the address,
 *  0xffffffff is returned and @err_ret will contain the error
 *  code.
 */
uint32_t sdio_readl(struct sdio_func *func, unsigned int addr, int *err_ret)
{
    int ret;

    if (err_ret)
        *err_ret = 0;

    ret = sdio_memcpy_fromio(func->card, func->num,func->tmpbuf, addr, 4);
    if (ret) {
        if (err_ret)
            *err_ret = ret;
        return 0xFFFFFFFF;
    }
    //return le32_to_cpup((__le32 *)func->tmpbuf);
    return le32toh(*((uint32_t *)func->tmpbuf));
}
//EXPORT_SYMBOL_GPL(sdio_readl);

/**
 *  sdio_writel - write a 32 bit integer to a SDIO function
 *  @func: SDIO function to access
 *  @b: integer to write
 *  @addr: address to write to
 *  @err_ret: optional status value from transfer
 *
 *  Writes a 32 bit integer to the address space of a given SDIO
 *  function. @err_ret will contain the status of the actual
 *  transfer.
 */
void sdio_writel(struct sdio_func *func, uint32_t b, unsigned int addr, int *err_ret)
{
    int ret;

    //*(__le32 *)func->tmpbuf = cpu_to_le32(b);
    *(int32_t *)func->tmpbuf = cpu_to_le32(b);

    ret = sdio_memcpy_toio(func->card, func->num, addr, func->tmpbuf, 4);
    if (err_ret)
        *err_ret = ret;
}
//EXPORT_SYMBOL_GPL(sdio_writel);




/**
 *  sdio_enable_func - enables a SDIO function for usage
 *  @func: SDIO function to enable
 *
 *  Powers up and activates a SDIO function so that register
 *  access is possible.
 */
int32_t sdio_enable_func(struct mmc_card *card, uint32_t func_num)
{
    uint8_t dat;

    mmc_io_rw_direct_host(card->host, 0, FN0, SDIO_CCCR_IOEx, 0, &dat);

    dat |= (1 << func_num); /* keep the value of other FN's IO enb state */
    mmc_io_rw_direct_host(card->host, 1, FN0, SDIO_CCCR_IOEx, dat, &dat);

    if (!(dat & (1 << func_num))) {
        SD_LOGE("%s,%d IO%ld Enable failed !!\n", __func__, __LINE__, HAL_PR_SZ_L(func_num));
        return -1;
    }

    SD_LOGD("IO%ld is enabled !!\n", HAL_PR_SZ_L(func_num));

    mmc_io_rw_direct_host(card->host, 0, FN0, SDIO_CCCR_IORx, 0, &dat);

    if (!(dat & (1 << func_num))) {
        SD_LOGD("%s,%d IO%ld is not ready !!\n", __func__, __LINE__, HAL_PR_SZ_L(func_num));
        return -1;
    }

    SD_LOGD("IO%ld is ready !!\n", HAL_PR_SZ_L(func_num));

    return 0;
}

/**
 *  Disable IOx's Function.
 *  @io_num: 1~7
 */
int32_t sdio_disable_func(struct mmc_card *card, uint32_t func_num)
{
    uint8_t dat;

    mmc_io_rw_direct_host(card->host, 0, FN0, SDIO_CCCR_IOEx, 0, &dat);

    dat &= ~(1 << func_num); /* keep the value of other FN's IO enb state */
    mmc_io_rw_direct_host(card->host, 1, FN0, SDIO_CCCR_IOEx, dat, &dat);

    if (dat & (1 << func_num)) {
        SD_LOGE("%s,%d IO%ld Disable failed !!\n", __func__, __LINE__, HAL_PR_SZ_L(func_num));
        return -1;
    }

    SD_LOGD("IO%ld is Disabled !!\n", HAL_PR_SZ_L(func_num));

    return 0;
}

int32_t sdio_set_block_size(struct mmc_card *card, uint32_t fn_num, uint32_t blksz)
{
    int32_t ret;

#if 0
    if ((blksz == 0) || card->fn_bsize[fn_num] == blksz) {
        SD_LOGW("block size has beed set to %d !!\n", blksz);
        return -1;
    }
#endif
    if ((blksz == 0)) {
        SD_LOGW("block size has beed set to %ld !!\n", HAL_PR_SZ_L(blksz));
        return -1;
    }



    /* sdio block size set in FN0 CCIA */
    sdio_writeb(card, FN0, blksz & 0xff, SDIO_FBR_BASE(fn_num) + SDIO_FBR_BLKSIZE, &ret);
    if (ret)
        return ret;
    sdio_writeb(card, FN0, (blksz >> 8) & 0xff, SDIO_FBR_BASE(fn_num) + SDIO_FBR_BLKSIZE + 1, &ret);
    if (ret)
        return ret;

    card->fn_bsize[fn_num] = blksz;

    SD_LOGD("sdio FN%ld set block size to %ld\n", HAL_PR_SZ_L(fn_num), HAL_PR_SZ_L(blksz));
    return 0;
}

/*
 * Test if the card supports high-speed mode and, if so, switch to it.
 */
static int32_t mmc_sdio_switch_hs(struct mmc_card *card, uint32_t enable)
{
    int32_t ret;
    uint8_t speed;

    if (!(card->host->caps & MMC_CAP_SD_HIGHSPEED))
        return 0;

    if (!card->cccr.high_speed)
        return 0;

    ret = mmc_io_rw_direct(card, 0, FN0, SDIO_CCCR_SPEED, 0, &speed);
    if (ret)
        return ret;

    if (!(speed & SDIO_SPEED_SHS)) {
        SD_LOGE("%s not support high speed mode!\n", __func__);
        return -1;
    }

    if (enable) {
        speed |= SDIO_SPEED_EHS;
    } else {
        speed &= ~SDIO_SPEED_EHS;
    }

    ret = mmc_io_rw_direct(card, 1, FN0, SDIO_CCCR_SPEED, speed, NULL);
    if(ret)
        return ret;

    return 1;
}

uint32_t mmc_sdio_get_max_clock(struct mmc_card *card)
{
    unsigned max_dtr;

    if (mmc_card_highspeed(card)) {
        /*
         * The SDIO specification doesn't mention how
         * the CIS transfer speed register relates to
         * high-speed, but it seems that 50 MHz is
         * mandatory.
         */
        max_dtr = 50000000;
    } else {
        max_dtr = card->cis.max_dtr;
    }

#ifdef CONFIG_USE_SDIO_COMBO
    if (card->type == MMC_TYPE_SD_COMBO)
        max_dtr = min(max_dtr, mmc_sd_get_max_clock(card));
#endif

    return max_dtr;
}

#ifdef CONFIG_SDIO_USE_FUNS
/*
 * Allocate and initialise a new SDIO function structure.
 */
struct sdio_func *sdio_alloc_func(struct mmc_card *card)
{
    struct sdio_func *func;

    func = HAL_Malloc(sizeof(struct sdio_func));
    if (!func)
        return NULL;

    SDC_Memset(func, 0, sizeof(struct sdio_func));

    func->card = card;

    return func;
}
/*
 * Register a new SDIO function with the driver model.
 */
int32_t sdio_add_func(struct sdio_func *func, uint32_t id)
{
//  fprintf(func->name, "%s:%d", id, func->num);

    sdio_func_set_present(func);

    return 0;
}

/*
 * Unregister a SDIO function with the driver model, and
 * (eventually) free it.
 * This function can be called through error paths where sdio_add_func() was
 * never executed (because a failure occurred at an earlier point).
 */
void sdio_remove_func(struct sdio_func *func)
{
    if (!sdio_func_present(func))
        return;
}

static int32_t sdio_init_func(struct mmc_card *card, uint32_t fn)
{
    int32_t ret;
    struct sdio_func *func;

    if (fn > SDIO_MAX_FUNCS) {
        SD_LOGE("%s,%d wrong fn:%ld!\n", __func__, __LINE__, HAL_PR_SZ_L(fn));
        return -1;
    }

    func = sdio_alloc_func(card);
    if (!func)
        return -1;

    func->num = fn;

    if (!(card->quirks & MMC_QUIRK_NONSTD_SDIO)) {
        ret = sdio_read_fbr(func);
        if (ret)
            goto fail;

        ret = sdio_read_func_cis(func);
        if (ret)
            goto fail;
    } else {
        func->vendor = func->card->cis.vendor;
        func->device = func->card->cis.device;
        func->max_blksize = func->card->cis.blksize;
    }

    card->sdio_func[fn - 1] = func;
    printf("func address %p\n",func);
    return 0;

fail:
    /*
     * It is okay to remove the function here even though we hold
     * the host lock as we haven't registered the device yet.
     */
    sdio_remove_func(func);
    return ret;
}

/*
 * Host is being removed. Free up the current card.
 */
int mmc_sdio_remove(struct mmc_host *host)
{
    int i;

    if (!host) {
        SD_LOGE_RAW(ROM_ERR_MASK, "%s,%d no host exist!\n", __func__, __LINE__);
        return -1;
    }
    if (!host->card) {
        SDC_LOGE("%s,%d no card exist!\n", __func__, __LINE__);
        return -1;
    }

    for (i = 0;i < host->card->sdio_funcs;i++) {
        if (host->card->sdio_func[i]) {
            sdio_remove_func(host->card->sdio_func[i]);
            host->card->sdio_func[i] = NULL;
        }
    }

    //mmc_remove_card(host->card); /* do nothing */
    host->card = NULL;
    return 0;
}

#endif

static int32_t sdio_read_cccr(struct mmc_card *card, uint32_t ocr)
{
    int32_t ret;
    int32_t cccr_vsn;
    int32_t uhs = ocr & R4_18V_PRESENT;
    uint8_t data;
    uint8_t speed;

    SDC_Memset(&card->cccr, 0, sizeof(struct sdio_cccr));

    ret = mmc_io_rw_direct(card, 0, FN0, SDIO_CCCR_CCCR, 0, &data);
    if (ret)
        goto out;

    cccr_vsn = data & 0x0f;

    if (cccr_vsn > SDIO_CCCR_REV_3_00) {
        SD_LOGW("%s: unrecognised CCCR structure version %ld\n",
                __func__, HAL_PR_SZ_L(cccr_vsn));
        return -1;
    }

    card->cccr.sdio_vsn = (data & 0xf0) >> 4;

    ret = mmc_io_rw_direct(card, 0, FN0, SDIO_CCCR_CAPS, 0, &data);
    if (ret)
        goto out;

    if (data & SDIO_CCCR_CAP_SMB)
        card->cccr.multi_block = 1;
    if (data & SDIO_CCCR_CAP_LSC)
        card->cccr.low_speed = 1;
    if (data & SDIO_CCCR_CAP_4BLS)
        card->cccr.wide_bus = 1;

    if (cccr_vsn >= SDIO_CCCR_REV_1_10) {
        ret = mmc_io_rw_direct(card, 0, FN0, SDIO_CCCR_POWER, 0, &data);
        if (ret)
            goto out;

        if (data & SDIO_POWER_SMPC)
            card->cccr.high_power = 1;
    }

    if (cccr_vsn >= SDIO_CCCR_REV_1_20) {
        ret = mmc_io_rw_direct(card, 0, FN0, SDIO_CCCR_SPEED, 0, &speed);
        if (ret)
            goto out;

        card->scr.sda_spec3 = 0;
        card->sw_caps.sd3_bus_mode = 0;
        card->sw_caps.sd3_drv_type = 0;
        if (cccr_vsn >= SDIO_CCCR_REV_3_00 && uhs) {
            card->scr.sda_spec3 = 1;
            ret = mmc_io_rw_direct(card, 0, FN0, SDIO_CCCR_UHS, 0, &data);
            if (ret)
                goto out;

            if (card->host->caps &
                (MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 |
                 MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR104 |
                 MMC_CAP_UHS_DDR50)) {
                if (data & SDIO_UHS_DDR50)
                    card->sw_caps.sd3_bus_mode |= SD_MODE_UHS_DDR50;

                if (data & SDIO_UHS_SDR50)
                    card->sw_caps.sd3_bus_mode |= SD_MODE_UHS_SDR50;

                if (data & SDIO_UHS_SDR104)
                    card->sw_caps.sd3_bus_mode |= SD_MODE_UHS_SDR104;
            }

            ret = mmc_io_rw_direct(card, 0, FN0, SDIO_CCCR_DRIVE_STRENGTH, 0, &data);
            if (ret)
                goto out;

            if (data & SDIO_DRIVE_SDTA)
                card->sw_caps.sd3_drv_type |= SD_DRIVER_TYPE_A;
            if (data & SDIO_DRIVE_SDTC)
                card->sw_caps.sd3_drv_type |= SD_DRIVER_TYPE_C;
            if (data & SDIO_DRIVE_SDTD)
                card->sw_caps.sd3_drv_type |= SD_DRIVER_TYPE_D;
        }

        /* if no uhs mode ensure we check for high speed */
        if (!card->sw_caps.sd3_bus_mode) {
            if (speed & SDIO_SPEED_SHS) {
                card->cccr.high_speed = 1;
                card->sw_caps.hs_max_dtr = 50000000;
            } else {
                card->cccr.high_speed = 0;
                card->sw_caps.hs_max_dtr = 25000000;
            }
        }
    }

out:
    SD_LOGD("%s high_speed:%d sda_spec3:%d sd3_drv_type:%lx sd3_bus_mode:%lx\n",
             __func__, card->cccr.high_speed, card->scr.sda_spec3,
            HAL_PR_SZ_L(card->sw_caps.sd3_drv_type), HAL_PR_SZ_L(card->sw_caps.sd3_bus_mode));
    return ret;
}

static int32_t sdio_enable_wide(struct mmc_card *card)
{
    int32_t ret;
    uint8_t ctrl;

    if (!(card->host->caps & MMC_CAP_4_BIT_DATA))
        return 0;

    if (card->cccr.low_speed && !card->cccr.wide_bus)
        return 0;

    ret = mmc_io_rw_direct(card, 0, FN0, SDIO_CCCR_IF, 0, &ctrl);
    if (ret)
        return ret;

    ctrl |= SDIO_BUS_WIDTH_4BIT;

    ret = mmc_io_rw_direct(card, 1, FN0, SDIO_CCCR_IF, ctrl, NULL);

    if (!ret && card->type == MMC_TYPE_SDIO)
        card->bus_width = MMC_BUS_WIDTH_4;

    return ret;
}

/*
 * If desired, disconnect the pull-up resistor on CD/DAT[3] (pin 1)
 * of the card. This may be required on certain setups of boards,
 * controllers and embedded sdio device which do not need the card's
 * pull-up. As a result, card detection is disabled and power is saved.
 */
static int32_t sdio_disable_cd(struct mmc_card *card)
{
    int32_t ret;
    uint8_t ctrl;

    if (!mmc_card_disable_cd(card))
        return 0;

    ret = mmc_io_rw_direct(card, 0, FN0, SDIO_CCCR_IF, 0, &ctrl);
    if (ret)
        return ret;

    ctrl |= SDIO_BUS_CD_DISABLE;

    return mmc_io_rw_direct(card, 1, FN0, SDIO_CCCR_IF, ctrl, NULL);
}

/*
 * Devices that remain active during a system suspend are
 * put back into 1-bit mode. called by mmc_sdio_suspend(host).
 */
#ifdef CONFIG_SD_PM
static int32_t sdio_disable_wide(struct mmc_card *card)
{
    int32_t ret;
    uint8_t ctrl;

    if (!(card->host->caps & MMC_CAP_4_BIT_DATA))
        return 0;

    if (card->cccr.low_speed && !card->cccr.wide_bus)
        return 0;

    ret = mmc_io_rw_direct(card, 0, FN0, SDIO_CCCR_IF, 0, &ctrl);
    if (ret)
        return ret;

    if (!(ctrl & SDIO_BUS_WIDTH_4BIT))
        return 0;

    ctrl &= ~SDIO_BUS_WIDTH_4BIT;
    ctrl |= SDIO_BUS_ASYNC_INT;

    ret = mmc_io_rw_direct(card, 1, FN0, SDIO_CCCR_IF, ctrl, NULL);
    if (ret)
        return ret;

    HAL_SDC_Set_BusWidth(card->host, MMC_BUS_WIDTH_1);

    return 0;
}
#endif

static int32_t sdio_enable_4bit_bus(struct mmc_card *card)
{
    int32_t err = 0;

    if (card->type == MMC_TYPE_SDIO)
        return sdio_enable_wide(card);

#ifdef CONFIG_USE_SDIO_COMBO
    if ((card->host->caps & MMC_CAP_4_BIT_DATA) &&
        (card->scr.bus_widths & SD_SCR_BUS_WIDTH_4)) {
        err = mmc_app_set_bus_width(card, MMC_BUS_WIDTH_4);
        if (err)
            return err;
    } else
        return 0;

    err = sdio_enable_wide(card);
    if (err <= 0)
        mmc_app_set_bus_width(card, MMC_BUS_WIDTH_1);
#endif

    return err;
}

/*
 * Enable SDIO/combo card's high-speed mode. Return 0/1 if [not]supported.
 */
static int32_t sdio_enable_hs(struct mmc_card *card)
{
    int32_t ret;

    ret = mmc_sdio_switch_hs(card, 1);
    if (ret <= 0 || card->type == MMC_TYPE_SDIO)
        return ret;

#ifdef CONFIG_USE_SDIO_COMBO
    ret = mmc_sd_switch_hs(card);
    if (ret <= 0)
        mmc_sdio_switch_hs(card, 0);
#endif

    return ret;
}

/*----------------------------------------------------------------------------------------------*\
    Function   : This function gets the CIS adress present on the SDIO card
    Argumennt : pointer to controller structure
    Return    : 0, -1
\*----------------------------------------------------------------------------------------------*/
/*
static uint32_t sdio_get_cisptr(struct mmc_card *card)
{
    uint32_t fn;
    uint8_t dat;

    for (fn=0; fn<=card->io_num; fn++) {
        sdio_ioreg_read(card, FN0, FN_CIS_POINTER_0_REG(fn), &dat);
        card->cisptr[fn] = dat;
        sdio_ioreg_read(card, FN0, FN_CIS_POINTER_1_REG(fn), &dat);
        card->cisptr[fn] |= (uint32_t)dat << 8;
        sdio_ioreg_read(card, FN0, FN_CIS_POINTER_2_REG(fn), &dat);
        card->cisptr[fn] |= (uint32_t)dat << 16;

        SD_LOGD("Card CIS Addr = %x, fn = %d\n", card->cisptr[fn], fn);
    }

    return 0;
}
*/
#if 0
/*--------------------------------------------------------------*\
    @function : uint32_t sdio_read_cisinfo(uint8_t* buf)
    @brief    : this function read CIS infomation of card
    @arguments: buf - pointer to data buffer
    @return   : 0, -1
\*--------------------------------------------------------------*/
int32_t sdio_read_cisinfo(struct mmc_card *card, uint8_t* buf)
{
    uint32_t i;
    int32_t ret=0;

    /* Read the Tuple Data */
    for (i = 0; i < SIZE_OF_TUPLE; i++) {
        ret = sdio_ioreg_read(card, FN0, card->cisptr[FN0]+i, buf+i);
        if (ret==-1)
            return ret;
    }
    return ret;
}

/*--------------------------------------------------------------*\
    @function : uint32_t sdio_read_manfid(uint32_t func_num)
    @brief    : this function read Manufacturer identification of card
    @arguments: func_num - pointer to data buffer
    @return   : 0, -1
\*--------------------------------------------------------------*/
int32_t sdio_read_manfid(struct mmc_card *card, uint32_t func_num)
{
    uint32_t offset = 0;
    uint32_t manfid, card_id;
    int32_t ret=0;
    uint8_t tuple, link, datah, datal;

    do {
        ret = sdio_ioreg_read(card, func_num, card->cisptr[func_num]+offset, &tuple);
        if (ret == -1)
            return ret;

        if (tuple == CISTPL_MANFID) {
            offset += 2;

            ret = sdio_ioreg_read(card, func_num, card->cisptr[func_num]+offset, &datal);
            if (ret == -1)
                return ret;
            offset++;

            ret = sdio_ioreg_read(card, func_num, card->cisptr[func_num]+offset, &datah);
            if (ret == -1)
                return ret;
            manfid = (uint32_t)datal | (uint32_t)datah << 8;
            offset++;

            ret = sdio_ioreg_read(card, func_num, card->cisptr[func_num]+offset, &datal);
            if (ret == -1)
                return ret;
            offset++;

            ret = sdio_ioreg_read(card, func_num, card->cisptr[func_num]+offset, &datah);
            if (ret == -1)
                return ret;
            card_id = (uint32_t)datal | (uint32_t)datah << 8;

            card->manfid = (card_id<<16)|manfid;

            SD_LOGD("Card id = %08x manfid = %08x\n", card_id, manfid);
            return manfid;
        }

        ret = sdio_ioreg_read(card, func_num, card->cisptr[func_num]+offset+1, &link);
        if (ret == -1)
            return ret;

        offset += link + 2;

    } while(tuple != CISTPL_END);

    return 0;
}

int32_t sdio_get_vendor_id(struct mmc_card *card)
{
    return (sdio_read_manfid(card, FN0));
}
#endif

int
sdio_memcpy_fromio(struct mmc_card *card, unsigned int func_num, void *dst, unsigned int addr, int count)
{
    return sdio_io_rw_ext_helper(card, func_num, 0, addr, 1, dst, count);
}

int
sdio_memcpy_toio(struct mmc_card *card, unsigned int func_num, unsigned int addr, const void *src, int count)
{
    return sdio_io_rw_ext_helper(card, func_num, 1, addr, 1, (uint8_t *)src, count);
}

#ifdef CONFIG_SDIO_IRQ_SUPPORT
#if 0
/*-----------------------------------*\
    Read IOx's Interrupt Pending
    Argument: io_num - 1~7
    Return: 1-pending, 0-not pending
\*-----------------------------------*/
int32_t sdio_intx_pend_rd(struct mmc_card *card, uint32_t io_num)
{
    uint8_t dat;

    //func_num uses default value 0
    mmc_io_rw_direct_host(card->host, 0, FN0, INT_PENDING_REG, 0, &dat);

    if (dat & INT(io_num)) {
        SD_LOGE("IO%x Interrupt is pending !!\n", io_num);
        return 0;
    }
    SD_LOGD("IO%x Interrupt is not pending !!\n", io_num);

    return -1;
}

/*  IOx's Abort *\
\*  io_num: 1~7 */
int32_t sdio_iox_abort(struct mmc_card *card, uint32_t io_num)
{
    mmc_io_rw_direct_host(card->host, 0, FN0, IO_ABORT_REG, AS(io_num), NULL);

    return 0;
}

/**
 *  sdio_claim_irq - claim the IRQ for a SDIO function
 *  @func: SDIO function
 *  @handler: IRQ handler callback
 *
 *  Claim and activate the IRQ for the given SDIO function. The provided
 *  handler will be called when that IRQ is asserted.  The host is always
 *  claimed already when the handler is called so the handler must not
 *  call sdio_claim_host() nor sdio_release_host().
 */
int sdio_claim_irq(struct mmc_card *card, unsigned int func_num, sdio_irq_handler_t *handler)
{
    int32_t ret;
    uint8_t reg;

    if (!card) {
        SD_LOGE_RAW(ROM_ERR_MASK, "%s,%d\n", __func__, __LINE__);
        return -1;
    }

    SD_LOGN("SDIO: Enabling IRQ for %d...\n", func_num);

    if (card->irq_handler) {
        SD_LOGE("SDIO: IRQ for %d already in use.\n", func_num);
        return -EBUSY;
    }

    reg = sdio_readb(card, FN0, SDIO_CCCR_IENx, &ret);
    if (ret)
        return ret;
    reg |= 1 << func_num;

    reg |= 1; /* Master interrupt enable */

    sdio_writeb(card, FN0, reg, SDIO_CCCR_IENx, &ret);
    if (ret)
        return ret;

    card->irq_handler = handler;

    return ret;
}

/**
 *  sdio_release_irq - release the IRQ for a SDIO function
 *  @func: SDIO function
 *
 *  Disable and release the IRQ for the given SDIO function.
 */
int sdio_release_irq(struct mmc_card *card, unsigned int func_num)
{
    int ret;
    uint8_t reg;

    if (!card) {
        SD_LOGE_RAW(ROM_ERR_MASK, "%s,%d\n", __func__, __LINE__);
        return -1;
    }

    SD_LOGN("SDIO: Disabling IRQ for %d...\n", func_num);

    if (card->irq_handler)
        card->irq_handler = NULL;

    reg = sdio_readb(card, FN0, SDIO_CCCR_IENx, &ret);
    if (ret)
        return ret;

    reg &= ~(1 << func_num);

    /* Disable master interrupt with the last function interrupt */
    if (!(reg & 0xFE))
        reg = 0;

    sdio_writeb(card, FN0, reg, SDIO_CCCR_IENx, &ret);
    if (ret)
        return ret;

    return 0;
}
#endif
#endif

/*
 * Fetch CID from card.
 */
#ifdef CONFIG_USE_SDIO_COMBO
int32_t mmc_sd_get_cid(struct mmc_host *host, uint32_t ocr, uint32_t *cid, uint32_t *rocr)
{
    int32_t err;

    /*
     * Since we're changing the OCR value, we seem to
     * need to tell some cards to go back to the idle
     * state.  We wait 1ms to give cards time to
     * respond.
     */
    mmc_go_idle(host);

    /*
     * If SD_SEND_IF_COND indicates an SD 2.0
     * compliant card and we should set bit 30
     * of the ocr to indicate that we can handle
     * block-addressed SDHC cards.
     */
    err = mmc_send_if_cond(host, ocr);
    if (!err)
        ocr |= SD_OCR_CCS;

    /*
     * If the host supports one of UHS-I modes, request the card
     * to switch to 1.8V signaling level.
     */
    if (host->caps & (MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 |
        MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR104 | MMC_CAP_UHS_DDR50))
        ocr |= SD_OCR_S18R;

    /* If the host can supply more than 150mA, XPC should be set to 1. */
    if (host->caps & (MMC_CAP_SET_XPC_330 | MMC_CAP_SET_XPC_300 |
        MMC_CAP_SET_XPC_180))
        ocr |= SD_OCR_XPC;

try_again:
    err = mmc_send_app_op_cond(host, ocr, rocr);
    if (err)
        return err;

    /*
     * In case CCS and S18A in the response is set, start Signal Voltage
     * Switch procedure. SPI mode doesn't support CMD11.
     */
    if (rocr && ((*rocr & 0x41000000) == 0x41000000)) {
        err = mmc_set_signal_voltage(host, MMC_SIGNAL_VOLTAGE_180, true);
        if (err) {
            ocr &= ~SD_OCR_S18R;
            goto try_again;
        }
    }

    err = mmc_all_send_cid(host, cid);

    return err;
}
#endif

/*--------------------------------------------------------------*\
    @function : uint32_t sdio_enumerate(uint32_t smc_no)
    @brief    : this function enumerates and initializes SDIO card
    @arguments: smc_no - number of the smc channel selected
    @return   : 0, -1
\*--------------------------------------------------------------*/
int32_t mmc_sdio_init_card(struct mmc_card *card)
{
    int32_t err;
    //struct mmc_host *host = card->host;

    /* The initialization should be done at 3.3 V I/O voltage. */
    //mmc_set_signal_voltage();

    err = mmc_send_io_op_cond(card, card->ocr.ocr & 0xFF8000, &card->ocr.ocr);
    if (err)
        return err;

#ifdef CONFIG_USE_SDIO_COMBO
    if ((card->ocr.ocr & R4_MEMORY_PRESENT) &&
        mmc_sd_get_cid(host, host->ocr & card->ocr.ocr, card->raw_cid, NULL) == 0) {
        card->type = MMC_TYPE_SD_COMBO;
        SD_LOGW("SDIO Combo Card(With I/O & Memory) !!\n");

        /* if with memory in it, allocate memory space for storing memory portion information */
        //card->mem_info_p = (SDMMCInfo *)HAL_Malloc(sizeof(SDMMCInfo));

        /* relative operations for memory portion */
    } else
#endif
    {
        card->type = MMC_TYPE_SDIO;
        SD_LOGD("Standard SDIO Card with IO portion only !!\n");
    }

    /*
     * If the host and card support UHS-I mode request the card
     * to switch to 1.8V signaling level.  No 1.8v signalling if
     * UHS mode is not enabled to maintain compatibilty and some
     * systems that claim 1.8v signalling in fact do not support
     * it.
     */
#ifdef SD_SUPPORT_VERSION3
    if ((card->ocr.ocr & R4_18V_PRESENT) &&
        (card->host->caps & (MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 |
                             MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR104 |
                             MMC_CAP_UHS_DDR50))) {
        err = mmc_set_signal_voltage(card->host, MMC_SIGNAL_VOLTAGE_180, true);
        if (err) {
            card->ocr.ocr &= ~R4_18V_PRESENT;
            card->host->ocr &= ~R4_18V_PRESENT;
        }
        err = 0;
    } else {
        card->ocr.ocr &= ~R4_18V_PRESENT;
        card->host->ocr &= ~R4_18V_PRESENT;
    }
#endif

    /* CMD3, Ask the card to publish a new Relative Card Address (RCA) */
    err = mmc_send_relative_addr(card->host, &card->rca);
    if (err) {
        SD_LOGW("SD public RCA failed\n");
        return err;
    }
    SD_LOGD("Card RCA %lx\n", HAL_PR_SZ_L(card->rca));
    HAL_SDC_Update_Clk(card->host, 25000000);

    /*
     * Read CSD, before selecting the card
     */
#ifdef CONFIG_USE_SDIO_COMBO
    if (card->type == MMC_TYPE_SD_COMBO) {
        err = mmc_sd_get_csd(host, card);
        if (err)
            return err;

        mmc_decode_cid(card);
    }
#endif

    /* CMD7, Select card, as all following commands rely on that. */
    err = mmc_select_card(card, 1);
    if (err) {
        SD_LOGE("Card Select Error!!\n");
        return -1;
    }

#ifdef CONFIG_USE_MMC_QUIRK
    if (card->quirks & MMC_QUIRK_NONSTD_SDIO) {
        /*
         * This is non-standard SDIO device, meaning it doesn't
         * have any CIA (Common I/O area) registers present.
         * It's host's responsibility to fill cccr and cis
         * structures in init_card().
         */
        mmc_set_clock(host, card->cis.max_dtr);

        if (card->cccr.high_speed) {
            mmc_card_set_highspeed(card);
            mmc_set_timing(card->host, MMC_TIMING_SD_HS);
        }

        goto finish;
    }
#endif

    /*
     * Read the common registers.
     */
    err = sdio_read_cccr(card, card->ocr.ocr);
    if (err)
        goto remove;

    /*
     * Read the common CIS tuples.
     */
#ifdef CONFIG_SDIO_USE_FUNS
    err = sdio_read_common_cis(card);
    if (err)
        goto remove;
#endif

#ifdef CONFIG_USE_MMC_QUIRK
    mmc_fixup_device(card, NULL);
#endif

    /*
     * If needed, disconnect card detection pull-up resistor.
     */
    err = sdio_disable_cd(card);
    if (err)
        goto remove;

    /* Initialization sequence for UHS-I cards */
    /* Only if card supports 1.8v and UHS signaling */
#ifdef SD_SUPPORT_VERSION3
    if ((card->ocr.ocr & R4_18V_PRESENT) && card->sw_caps.sd3_bus_mode) {
        err = mmc_sdio_init_uhs_card(card);
        if (err)
            goto remove;

        /* Card is an ultra-high-speed card */
        mmc_card_set_uhs(card);
    } else
#endif
    {
        /*
         * Switch to high-speed (if supported).
         */
        err = sdio_enable_hs(card);
        if (err > 0) {
            mmc_card_set_highspeed(card);
            SD_LOGN("sdio highspeed \n");
        } else if (err)
            goto remove;

        /*
         * Change to the card's maximum speed.
         */
        HAL_SDC_Update_Clk(card->host, mmc_sdio_get_max_clock(card));

        /*
         * Switch to wider bus (if supported).
         */
        err = sdio_enable_4bit_bus(card);
        if (!err) {
            /* sd Host Controller Register SDXC_REG_WIDTH */
            HAL_SDC_Set_BusWidth(card->host, MMC_BUS_WIDTH_4);
            SD_LOGN("%s bus width type:%d\n", __func__, MMC_BUS_WIDTH_4);
        } else if (err)
            goto remove;
    }


#ifdef CONFIG_USE_MMC_QUIRK
finish:
#endif
    card->host->card = card;
    return 0;

remove:
    card->host->card = NULL;
#ifdef CONFIG_SDIO_USE_FUNS
    sdio_free_func_cis((struct sdio_func *)card->sdio_func);
    sdio_free_common_cis(card);
#endif

    return err;
}

uint32_t sdio_reset(struct mmc_host *host)
{
    int32_t ret;
    uint8_t abort;

    /* SDIO Simplified Specification V2.0, 4.4 Reset for SDIO */

    ret = mmc_io_rw_direct_host(host, 0, 0, SDIO_CCCR_ABORT, 0, &abort);
    if (ret)
        abort = 0x08;
    else
        abort |= 0x08;

    ret = mmc_io_rw_direct_host(host, 1, 0, SDIO_CCCR_ABORT, abort, NULL);

    return ret;
}

/**
 *  sdio_set_host_pm_flags - set wanted host power management capabilities
 *  @func: SDIO function attached to host
 *
 *  Set a capability bitmask corresponding to wanted host controller
 *  power management features for the upcoming suspend state.
 *  This must be called, if needed, each time the suspend method of
 *  the function driver is called, and must contain only bits that
 *  were returned by sdio_get_host_pm_caps().
 *  The host doesn't need to be claimed, nor the function active,
 *  for this information to be set.
 */
static int32_t sdio_set_host_pm_flags(sdio_t *card, uint32_t flags)
{
#ifdef CONFIG_SD_PM
    struct mmc_host *host = card->host;

    if (flags & ~host->pm_caps)
        return -1;

    /* function suspend methods are serialized, hence no lock needed */
    host->pm_flags |= flags;
#endif
    return 0;
}

int32_t sdio_pm(sdio_t *card, int32_t suspend)
{
    int32_t ret = 0;

    if (suspend) {
        /* Notify SDIO that ALLWINNERTECH will remain powered during suspend */
        ret = sdio_set_host_pm_flags(card, MMC_PM_KEEP_POWER);
        if (ret)
            SD_LOGE("Error setting SDIO pm flags: %ld\n", HAL_PR_SZ_L(ret));
    }

    return ret;
}

#ifdef CONFIG_SD_PM
/*
 * SDIO suspend.  We need to suspend all functions separately.
 * Therefore all registered functions must have drivers with suspend
 * and resume methods.  Failing that we simply remove the whole card.
 */
static int mmc_sdio_suspend(struct mmc_host *host)
{
    int32_t i, err = 0;
    struct mmc_card *card;

    card = host->card;
    card->suspend = 1;

#ifdef CONFIG_SDIO_USE_FUNS
    for (i = 0; i < host->card->sdio_funcs; i++) {
        struct sdio_func *func = host->card->sdio_func[i];
        if (func && sdio_func_present(func) && func->dev.driver) {
            err = sdio_bus_pm_suspend(&func->dev);
            sdio_disable_func(host->card, FN1);
            if (err)
                break;
        }
    }
    while (err && --i >= 0) {
        struct sdio_func *func = host->card->sdio_func[i];
        if (func && sdio_func_present(func) && func->dev.driver) {
            sdio_bus_pm_resume(&func->dev);
        }
    }
#else
    (void)i;
#endif
    if (mmc_card_keep_power(host) && mmc_card_wake_sdio_irq(host)) {
        mmc_claim_host(host);
        sdio_disable_wide(host->card);
        mmc_release_host(host);
    }

    return err;
}

int mmc_sdio_resume(struct mmc_host *host)
{
    int32_t i, err = 0;
    struct mmc_card *card;

    if (!host) {
        SDC_LOGE_RAW(ROM_ERR_MASK, "%s,%d no host exist!\n", __func__, __LINE__);
        return -1;
    }
    if (!host->card) {
        SDC_LOGE("%s,%d no card exist!\n", __func__, __LINE__);
        return -1;
    }

    card = host->card;

    /* Basic card reinitialization. */
    mmc_claim_host(host);

    /* No need to reinitialize powered-resumed nonremovable cards */
    if (!mmc_card_keep_power(host)) {
        err = mmc_sdio_init_card(host->card);
    } else if (mmc_card_wake_sdio_irq(host)) {
        /* We may have switched to 1-bit mode during suspend */
        err = sdio_enable_4bit_bus(host->card);
        if (!err) {
            HAL_SDC_Set_BusWidth(host->card->host, MMC_BUS_WIDTH_4);
            SDC_LOGN("%s bus width type:%d\n", __func__, MMC_BUS_WIDTH_4);
            err = 0;
        }
    }

#ifdef CONFIG_SDIO_IRQ_SUPPORT
    if (!err && host->sdio_irqs)
        wake_up_process(host->sdio_irq_thread);
#endif
    mmc_release_host(host);

#ifdef CONFIG_SDIO_USE_FUNS
    /*
     * If the card looked to be the same as before suspending, then
     * we proceed to resume all card functions.  If one of them returns
     * an error then we simply return that error to the core and the
     * card will be redetected as new.  It is the responsibility of
     * the function driver to perform further tests with the extra
     * knowledge it has of the card to confirm the card is indeed the
     * same as before suspending (same MAC address for network cards,
     * etc.) and return an error otherwise.
     */
    for (i = 0; !err && i < host->card->sdio_funcs; i++) {
        struct sdio_func *func = host->card->sdio_func[i];
        if (func && sdio_func_present(func) && func->dev.driver) {
            err = sdio_bus_pm_resume(&func->dev);
            sdio_enable_func(host->card, FN1);
        }
    }
#else
    (void)i;
#endif

    card->suspend = 0;

    return err;
}

static const struct mmc_bus_ops sdio_bus_ops = {
    .suspend = mmc_sdio_suspend,
    .resume = mmc_sdio_resume,
};
#endif

/*
 * Starting point for SDIO card init.
 */
int mmc_attach_sdio(struct mmc_card *card, struct mmc_host *host)
{
    int err = -1;
    int32_t funcs;
    int i;

    if (!host) {
        SD_LOGE("%s,%d no host exist!\n", __func__, __LINE__);
        return -1;
    }

    /* CMD5 arg=0; get card support Voltage */
    err = mmc_send_io_op_cond(card, 0, &card->ocr.ocr);
    if (err)
        return err;
    SD_LOGD("card ocr:%lx\n", HAL_PR_SZ_L(card->ocr.ocr));

    /*
     * Sanity check the voltages that the card claims to
     * support.
     */
    if (card->ocr.ocr & 0x7F) {
        SD_LOGW("card claims to support voltages below the defined range."
                "These will be ignored.\n");
        card->ocr.ocr &= ~0x7F;
    }

    /* Detect and init the card. */
    err = mmc_sdio_init_card(card);
    if (err)
        return err;


    funcs = (card->ocr.ocr >> 28) & 0x7;

    SD_LOGD("Number of I/O Functions: %02lx\n", HAL_PR_SZ_L(funcs));

    /*
     * Initialize (but don't add) all present functions.
     */
#ifdef CONFIG_SDIO_USE_FUNS
    card->sdio_funcs = 0;

//  for (int i = 0; i < card->io_num; i++, card->sdio_funcs++) {
//  for (int i = 0; i < funcs; i++, card->sdio_funcs++) {
    for (i = 0; i < funcs; i++, card->sdio_funcs++) {
        err = sdio_init_func(host->card, i + 1);
        if (err)
            goto remove;
    }
#endif

    /*
     * First add the card to the driver model...
     */
    mmc_release_host(host);

    if(host->caps&MMC_CAP_SDIO_IRQ){
        int ret =  OS_SemaphoreCreateBinary(&host->sdio_irq_signal);
        SDC_BUG_ON(ret!=OS_OK);
    }
    mmc_add_card(host->card);

    /*
     * ...then the SDIO functions.
     */
#ifdef CONFIG_SDIO_USE_FUNS
//  for (int i = 0; i < funcs; i++) {
    for (i = 0; i < funcs; i++) {
        err = sdio_add_func(host->card->sdio_func[i], i);
        if (err)
            goto remove_added;
    }
#else
    (void)funcs;
#endif

    card->fn_bsize[1] = 512;

    mmc_claim_host(host);

#ifdef CONFIG_SD_PM
    if (!card->suspend) {
        mmc_attach_bus(host, &sdio_bus_ops);
    }
#endif

    return 0;

#ifdef CONFIG_SDIO_USE_FUNS
remove_added:
    /* Remove without lock if the device has been added. */
    mmc_sdio_remove(host);
#endif
    card->host->card = NULL;
    mmc_claim_host(host);

#ifdef CONFIG_SDIO_USE_FUNS
remove:
    /* And with lock if it hasn't been added. */
    mmc_release_host(host);
    if (host->card) {
        mmc_sdio_remove(host);
        card->host->card = NULL;
    }
    mmc_claim_host(host);
#else
    card->host->card = NULL;
#endif

    SD_LOGE("%s: error %d whilst initialising SDIO card\n", __func__, err);

    return err;
}

void mmc_deattach_sdio(struct mmc_card *card, struct mmc_host *host)
{
    if (!card) {
        SD_LOGE_RAW(ROM_ERR_MASK, "%s,%d\n", __func__, __LINE__);
        return ;
    }

#ifdef CONFIG_SD_PM
    if (!card->suspend) {
        mmc_detach_bus(card->host);
    }
#endif
    if(host->caps&MMC_CAP_SDIO_IRQ){
        int ret =  OS_SemaphoreDelete(&host->sdio_irq_signal);
        SDC_BUG_ON(ret!=OS_OK);
    }

}

/**
 *  sdio_align_size - pads a transfer size to a more optimal value
 *  @card: SDIO card
 *  @sz: original transfer size
 *
 *  Pads the original data size with a number of extra bytes in
 *  order to avoid controller bugs and/or performance hits
 *  (e.g. some controllers revert to PIO for certain sizes).
 *
 *  If possible, it will also adjust the size so that it can be
 *  handled in just a single request.
 *
 *  Returns the improved size, which might be unmodified.
 */
//unsigned int sdio_align_size(struct mmc_card *card, unsigned int sz)
unsigned int sdio_align_size(struct sdio_func *func, unsigned int sz)
{
#ifdef CONFIG_SDIO_USE_FUNS
    unsigned int orig_sz;
    unsigned int blk_sz, byte_sz;
    unsigned chunk_sz;

    orig_sz = sz;
#endif

    /* Do a first check with the controller, in case it
     * wants to increase the size up to a point where it
     * might need more than one block.
     */
    //sz = mmc_align_data_size(card, sz);
    sz = mmc_align_data_size(func->card, sz);

#ifdef CONFIG_SDIO_USE_FUNS
    /*
     * If we can still do this with just a byte transfer, then
     * we're done.
     */
    if (sz <= sdio_max_byte_size(func))
        return sz;

    if (func->card->cccr.multi_block) {
        /*
         * Check if the transfer is already block aligned
         */
        if ((sz % func->cur_blksize) == 0) {
            return sz;
        }

            /*
             * Realign it so that it can be done with one request,
             * and recheck if the controller still likes it.
             */
            blk_sz = ((sz + func->cur_blksize - 1) /
                func->cur_blksize) * func->cur_blksize;
            blk_sz = mmc_align_data_size(func->card, blk_sz);

            /*
             * This value is only good if it is still just
             * one request.
             */
            if ((blk_sz % func->cur_blksize) == 0)
                return blk_sz;

            /*
             * We failed to do one request, but at least try to
             * pad the remainder properly.
             */
            byte_sz = mmc_align_data_size(func->card,
                    sz % func->cur_blksize);
            if (byte_sz <= sdio_max_byte_size(func)) {
                blk_sz = sz / func->cur_blksize;
                return blk_sz * func->cur_blksize + byte_sz;
            }
        } else {
            /*
             * We need multiple requests, so first check that the
             * controller can handle the chunk size;
             */
            chunk_sz = mmc_align_data_size(func->card,
                    sdio_max_byte_size(func));
            if (chunk_sz == sdio_max_byte_size(func)) {
                /*
                 * Fix up the size of the remainder (if any)
                 */
                byte_sz = orig_sz % chunk_sz;
                if (byte_sz) {
                    byte_sz = mmc_align_data_size(func->card,
                            byte_sz);
                }

                return (orig_sz / chunk_sz) * chunk_sz + byte_sz;
            }
        }

    /* The controller is simply incapable of transferring the size
     * we want in decent manner, so just return the original size.
     */
    return orig_sz;
#endif

    return sz;
}

#ifdef SDIO_EXCLUSIVE_HOST
/**
 *  sdio_claim_host - exclusively claim a bus for a certain SDIO function
 *  @card: SDIO that will be accessed
 *
 *  Claim a bus for a set of operations. The SDIO function given
 *  is used to figure out which bus is relevant.
 */
void sdio_claim_host(struct mmc_card *card)
{
    HAL_SDC_Claim_Host(card->host);
}

/**
 *  sdio_release_host - release a bus for a certain SDIO function
 *  @card: SDIO that was accessed
 *
 *  Release a bus, allowing others to claim the bus for their
 *  operations.
 */
void sdio_release_host(struct mmc_card *card)
{
    HAL_SDC_Release_Host(card->host);
}
#endif

#endif /* CONFIG_USE_SDIO */
