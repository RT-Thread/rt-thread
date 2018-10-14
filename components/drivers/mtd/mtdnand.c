/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2018-09-10     heyuanjie87   first version
 */

#include <rtdevice.h>

#define MTDTONAND(x)    ((rt_nand_t*)(x))
#define NOTALIGNED(x)   ((x & (chip->page_size - 1)) != 0)
#ifndef min
#define min(a,b) (a>b? b:a)
#endif

static uint8_t *nand_fill_oob(rt_nand_t *chip, uint8_t *oob, size_t len, struct mtd_io_desc *desc)
{
    rt_memset(chip->oob_poi, 0xff, chip->oobsize);

    switch (desc->mode)
    {
    case MTD_OPM_PLACE_OOB:
    case MTD_OPM_RAW:
        rt_memcpy(chip->oob_poi + desc->ooboffs, oob, len);
        return oob + len;

    case MTD_OPM_AUTO_OOB:
    {
        const struct mtd_oob_region *free = chip->freelayout;
        uint32_t boffs;
        size_t bytes;

        bytes = min(len, free->length);
        boffs = free->offset;

        rt_memcpy(chip->oob_poi + boffs, oob, bytes);
        oob += bytes;

        return oob;
    }
    }

    return NULL;
}

static uint8_t *nand_transfer_oob(rt_nand_t *chip, uint8_t *oob, struct mtd_io_desc *desc, size_t len)
{
    switch (desc->mode)
    {
    case MTD_OPM_PLACE_OOB:
    case MTD_OPM_RAW:
        rt_memcpy(oob, chip->oob_poi + desc->ooboffs, len);
        return oob + len;

    case MTD_OPM_AUTO_OOB:
    {
        struct mtd_oob_region *free = (struct mtd_oob_region *)chip->freelayout;
        uint32_t boffs = 0, roffs = desc->ooboffs;
        size_t bytes = 0;

        for (; free->length && len; free++, len -= bytes)
        {
            /* Read request not from offset 0? */
            if (roffs)
            {
                if (roffs >= free->length)
                {
                    roffs -= free->length;
                    continue;
                }
                boffs = free->offset + roffs;
                bytes = min(len, (free->length - roffs));
                roffs = 0;
            }
            else
            {
                bytes = min(len, free->length);
                boffs = free->offset;
            }

            rt_memcpy(oob, chip->oob_poi + boffs, bytes);
            oob += bytes;
        }

        return oob;
    }
    }

    return NULL;
}

static int nand_read_page_raw(rt_nand_t *chip, uint8_t *buf, int oob_required, int page)
{
    chip->ops->read_buf(chip, buf, chip->page_size);

    if (oob_required)
        chip->ops->read_buf(chip, chip->oob_poi, chip->oobsize);

    return 0;
}

static int nand_write_page_raw(rt_nand_t *chip, const uint8_t *buf, int oob_required, int page)
{
    chip->ops->write_buf(chip, buf, chip->page_size);

    if (oob_required)
        chip->ops->write_buf(chip, chip->oob_poi, chip->oobsize);

    return 0;
}

static int nand_write_page_hwecc(rt_nand_t *chip, const uint8_t *buf, int oob_required, int page)
{
    uint16_t i;
    uint16_t stepsize = chip->ecc.stepsize;
    uint16_t eccbytes = chip->ecc.bytes;
    uint16_t eccsteps = chip->ecc._step;
    uint16_t eccpos = chip->ecc.layout->offset;
    uint8_t *ecc_calc = chip->buffers.ecccalc;
    const uint8_t *p = buf;

    for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += stepsize)
    {
        chip->ops->cmdfunc(chip, NAND_CMD_ECC_EN, 0, 0);
        chip->ops->write_buf(chip, p, stepsize);
        chip->ecc.calculate(chip, p, &ecc_calc[i]);
        chip->ops->cmdfunc(chip, NAND_CMD_ECC_DIS, 0, 0);
    }

    rt_memcpy(&chip->oob_poi[eccpos], ecc_calc, chip->ecc.layout->length);

    chip->ops->write_buf(chip, chip->oob_poi, chip->oobsize);

    return 0;
}

static int nand_read_page_hwecc(rt_nand_t *chip, uint8_t *buf, int oob_required, int page)
{
    uint16_t i;
    uint16_t eccsize = chip->ecc.stepsize;
    uint16_t eccbytes = chip->ecc.bytes;
    uint16_t eccsteps = chip->ecc._step;
    uint16_t eccpos = chip->ecc.layout->offset;
    uint8_t *p = buf;
    uint8_t *ecc_calc = chip->buffers.ecccalc;
    uint8_t *ecc_code = chip->buffers.ecccode;
    int ret = 0;

    for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize)
    {
        chip->ops->cmdfunc(chip, NAND_CMD_ECC_EN, 0, 0);
        chip->ops->read_buf(chip, p, eccsize);
        chip->ecc.calculate(chip, p, &ecc_calc[i]);
        chip->ops->cmdfunc(chip, NAND_CMD_ECC_DIS, 0, 0);
    }

    chip->ops->read_buf(chip, chip->oob_poi, chip->oobsize);
    rt_memcpy(ecc_code, &chip->oob_poi[eccpos], chip->ecc.layout->length);

    eccsteps = chip->ecc._step;
    p = buf;

    for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize)
    {
        int stat;

        stat = chip->ecc.correct(chip, p, &ecc_code[i], &ecc_calc[i]);
        if (stat != 0)
            ret = -1;
    }

    return ret;
}

static int nand_write_page(rt_nand_t *chip, const uint8_t *buf,
    int oob_required, int page, int raw)
{
    int status;

    chip->ops->cmdfunc(chip, NAND_CMD_PAGE_WR0, page, 0x00);

    if (raw)
    {
        nand_write_page_raw(chip, buf, oob_required, page);
    }
    else
    {
        chip->write_page(chip, buf, oob_required, page);
    }

    status = chip->ops->cmdfunc(chip, NAND_CMD_PAGE_WR1, -1, -1);

    return status;
}

static int nand_do_read_desc(rt_nand_t *chip, loff_t from, struct mtd_io_desc *desc)
{
    int page, bytes;
    char oob_required;
    char ecc_fail = 0;
    int ret = 0;
    uint32_t readlen = desc->datlen;
    uint16_t oobreadlen = desc->ooblen;
    uint16_t max_oobsize = desc->mode == MTD_OPM_AUTO_OOB ?
        chip->freelayout->length : chip->oobsize;

    uint8_t *oob, *buf, *notalign = 0;

    /* Reject reads, which are not page aligned */
    if (NOTALIGNED(from))
    {
        return -EINVAL;
    }

    buf = desc->datbuf;
    if (NOTALIGNED(desc->datlen) && !chip->pagebuf)
    {
        chip->pagebuf = rt_malloc(chip->page_size);
         if (!chip->pagebuf)
             return -ENOMEM;
    }

    page = (int)(from / chip->page_size);

    oob = desc->oobbuf;
    oob_required = oob ? 1 : 0;

    while (1)
    {
        bytes = min(chip->page_size, readlen);

        chip->ops->cmdfunc(chip, NAND_CMD_PAGE_RD, page, 0x00);
        if (NOTALIGNED(bytes))
        {
            notalign = buf;
            buf = chip->pagebuf;
        }
        /*
        * Now read the page into the buffer.  Absent an error,
        * the read methods return max bitflips per ecc step.
        */
        if (desc->mode == MTD_OPM_RAW)
        {
            ret = nand_read_page_raw(chip, buf, oob_required, page);
        }
        else
        {
            ret = chip->read_page(chip, buf, oob_required, page);
        }

        if (ret != 0)
        {
            ret = -EBADMSG;
            break;
        }

        if (oob)
        {
            int toread = min(oobreadlen, max_oobsize);

            if (toread)
            {
                oob = nand_transfer_oob(chip, oob, desc, toread);
                oobreadlen -= toread;
            }
        }

        if (notalign)
        {
            rt_memcpy(notalign, buf, bytes);
        }

        buf += bytes;
        readlen -= bytes;

        if (!readlen)
            break;

        page++;
    }

    desc->datretlen = desc->datlen - (size_t)readlen;
    if (oob)
        desc->oobretlen = desc->ooblen - oobreadlen;

    return ret;
}

/*
 * write with ECC
 *
*/
static int nand_do_write_desc(rt_nand_t *chip, loff_t to, struct mtd_io_desc *desc)
{
    int page;
    uint16_t writelen = desc->datlen;
    uint16_t oob_required = desc->oobbuf ? 1 : 0;
    uint16_t oobwritelen = desc->ooblen;
    uint16_t oobmaxlen = desc->mode == MTD_OPM_AUTO_OOB ?
        chip->freelayout->length : chip->oobsize;

    uint8_t *oob = desc->oobbuf;
    uint8_t *buf = desc->datbuf;
    int ret;

    if (!writelen)
        return 0;

    /* Reject writes, which are not page aligned */
    if (NOTALIGNED(to))
    {
        return -EINVAL;
    }

    page = (int)(to / chip->page_size);

    /* Don't allow multipage oob writes with offset */
    if (oob && desc->ooboffs && (desc->ooboffs + desc->ooblen > oobmaxlen))
    {
        ret = -EINVAL;
        goto err_out;
    }

    if (NOTALIGNED(desc->datlen) && !chip->pagebuf)
    {
        chip->pagebuf = rt_malloc(chip->page_size);
        if (!chip->pagebuf)
            return -ENOMEM;
    }

    while (1)
    {
        uint16_t bytes = min(chip->page_size, writelen);

        if (oob)
        {
            size_t len = min(oobwritelen, oobmaxlen);
            oob = nand_fill_oob(chip, oob, len, desc);
            oobwritelen -= len;
        }
        else
        {
            /* We still need to erase leftover OOB data */
            rt_memset(chip->oob_poi, 0xff, chip->oobsize);
        }

        if (NOTALIGNED(bytes))
        {
            uint8_t *dbtmp = buf;
            buf = chip->pagebuf;
            rt_memset(&buf[bytes], 0xff, chip->page_size - bytes);
            rt_memcpy(buf, dbtmp, bytes);
        }
        ret = nand_write_page(chip, buf, oob_required, page, (desc->mode == MTD_OPM_RAW));
        if (ret)
            break;

        writelen -= bytes;
        if (!writelen)
            break;

        buf += bytes;
        page++;
    }

    desc->datretlen = desc->datlen - writelen;
    if (oob)
        desc->oobretlen = desc->ooblen;

err_out:

    return ret;
}

static int nand_read_oob_std(rt_nand_t *chip, int page)
{
    chip->ops->cmdfunc(chip, NAND_CMD_PAGE_RD, page, chip->page_size);
    chip->ops->read_buf(chip, chip->oob_poi, chip->oobsize);

    return 0;
}

/*
 * read one page of OOB
*/
static int nand_only_read_oob(rt_nand_t *chip, loff_t from, struct mtd_io_desc *desc)
{
    int page;
    int readlen = desc->ooblen;
    int len;
    uint8_t *buf = desc->oobbuf;
    int ret = 0;

    if (desc->mode == MTD_OPM_AUTO_OOB)
        len = chip->freelayout->length;
    else
        len = chip->oobsize;

    if (desc->ooboffs >= len) //attempt to start read outside oob
    {
        return -EINVAL;
    }

    page = (int)(from / chip->page_size);

    ret = nand_read_oob_std(chip, page);
    if (ret == 0)
    {
        len = min(len, readlen);
        buf = nand_transfer_oob(chip, buf, desc, len);
        desc->oobretlen = len;
    }

    return ret;
}

static int nand_write_oob_std(rt_nand_t *chip, int page)
{
    int status;

    chip->ops->cmdfunc(chip, NAND_CMD_PAGE_WR0, page, chip->page_size);
    chip->ops->write_buf(chip, chip->oob_poi, chip->oobsize);
    /* Send command to program the OOB data */
    status = chip->ops->cmdfunc(chip, NAND_CMD_PAGE_WR1, -1, -1);

    return status & NAND_STATUS_FAIL ? -EIO : 0;
}

static int nand_only_write_oob(rt_nand_t *chip, loff_t to, struct mtd_io_desc *desc)
{
    int page, ret, len;

    if (desc->mode == MTD_OPM_AUTO_OOB)
        len = chip->freelayout->length;
    else
        len = chip->oobsize;

    /* Do not allow write past end of page */
    if ((desc->ooboffs + desc->ooblen) > len)
    {
        return -EINVAL;
    }

    if (desc->ooblen == 0)
    {
        return -EINVAL;
    }

    /* get page */
    page = (int)(to / chip->page_size);

    nand_fill_oob(chip, desc->oobbuf, desc->ooblen, desc);

    ret = nand_write_oob_std(chip, page);
    if (ret == 0)
        desc->oobretlen = len;

    return ret;
}

static int nand_erase(rt_mtd_t *mtd, loff_t addr, size_t size)
{
    rt_nand_t *chip;
    int status;
    int page;
    uint32_t blksize;

    chip = MTDTONAND(mtd);
    blksize = mtd->block_size;
    page = addr / chip->page_size;

    while (size >= blksize)
    {
        status = chip->ops->cmdfunc(chip, NAND_CMD_BLK_ERASE, page, 0);
        if (status & NAND_STATUS_FAIL)
        {
            break;
        }
        size -= blksize;
        page += chip->pages_pb;
    }

    return size;
}

static int nand_read(rt_mtd_t *mtd, loff_t from, struct mtd_io_desc *desc)
{
    int ret = -ENOTSUP;
    rt_nand_t *chip;

    chip = MTDTONAND(mtd);

    switch (desc->mode)
    {
    case MTD_OPM_PLACE_OOB:
    case MTD_OPM_AUTO_OOB:
    case MTD_OPM_RAW:
        break;

    default:
        goto out;
    }

    if (!desc->datbuf || !desc->datlen)
        ret = nand_only_read_oob(chip, from, desc);
    else
        ret = nand_do_read_desc(chip, from, desc);

out:

    return ret;
}

static int nand_write(rt_mtd_t *mtd, loff_t to, struct mtd_io_desc *desc)
{
    int ret = -ENOTSUP;
    rt_nand_t *chip;

    chip = MTDTONAND(mtd);

    switch (desc->mode)
    {
    case MTD_OPM_PLACE_OOB:
    case MTD_OPM_AUTO_OOB:
    case MTD_OPM_RAW:
        break;

    default:
        goto out;
    }

    if (!desc->datbuf || !desc->datlen)
        ret = nand_only_write_oob(chip, to, desc);
    else
        ret = nand_do_write_desc(chip, to, desc);

out:

    return ret;
}

static int nand_block_isbad(rt_mtd_t *mtd, uint32_t blk)
{
    int ret;
    rt_nand_t *chip = MTDTONAND(mtd);

    if (chip->ops->isbad)
    {
        ret = chip->ops->isbad(chip, blk);
    }
    else
    {
        int page;

        page = blk * chip->pages_pb;
        nand_read_oob_std(chip, page);
        ret = chip->oob_poi[0] != 0xFF;
    }

    return ret;
}

static int nand_block_markbad(rt_mtd_t *mtd, uint32_t blk)
{
    int ret;
    rt_nand_t *chip;

    chip = MTDTONAND(mtd);

    if (chip->ops->markbad)
    {
        ret = chip->ops->markbad(chip, blk);
    }
    else
    {
        int page;

        page = blk * chip->pages_pb;
        rt_memset(chip->oob_poi, 0xff, chip->oobsize);
        chip->oob_poi[0] = 0;
        ret = nand_write_oob_std(chip, page);
    }

    return ret;
}

static const struct mtd_ops _ops =
{
    nand_erase,
    nand_read,
    nand_write,
    nand_block_isbad,
    nand_block_markbad,
};

int rt_mtd_nand_init(rt_nand_t *nand, int blk_size, int page_size, int oob_size)
{
    uint8_t *buf;

    buf = rt_malloc(oob_size * 3);
    if (buf == RT_NULL)
        return -ENOMEM;

    nand->oob_poi = buf;
    buf += oob_size;
    nand->buffers.ecccalc = buf;
    buf += oob_size;
    nand->buffers.ecccode = buf;
    nand->pagebuf = 0; /* alloc when unaligen access */

    nand->pages_pb = blk_size / page_size;
    nand->ecc._step = page_size / nand->ecc.stepsize;
    nand->page_size = page_size;
    nand->oobsize = oob_size;

    nand->parent.type = MTD_TYPE_NAND;
    nand->parent.ops = &_ops;
    nand->parent.sector_size = page_size;
    nand->parent.block_size = blk_size;
    nand->parent.oob_size = oob_size;

    switch (nand->ecc.mode)
    {
    case NAND_ECCM_NONE:
    {
        nand->read_page = nand_read_page_raw;
        nand->write_page = nand_write_page_raw;
    }break;
    case NAND_ECCM_HW:
    {
        nand->read_page = nand_read_page_hwecc;
        nand->write_page = nand_write_page_hwecc;
    }break;
    default:
    {
        rt_free(buf);
        return -1;
    }
    }

    return 0;
}
