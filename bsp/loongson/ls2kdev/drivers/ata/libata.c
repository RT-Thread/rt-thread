/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-19     lizhirui     porting to ls2k
 */

#include <rtthread.h>
#include <ata_interface.h>
#include <libata.h>

u64 ata_id_n_sectors(u16 *id)
{
    if (ata_id_has_lba(id)) {
        if (ata_id_has_lba48(id))
            return ata_id_u64(id, ATA_ID_LBA48_SECTORS);
        else
            return ata_id_u32(id, ATA_ID_LBA_SECTORS);
    } else {
        return 0;
    }
}

u32 ata_dev_classify(u32 sig)
{
    u8 lbam, lbah;

    lbam = (sig >> 16) & 0xff;
    lbah = (sig >> 24) & 0xff;

    if (((lbam == 0) && (lbah == 0)) ||
        ((lbam == 0x3c) && (lbah == 0xc3)))
        return ATA_DEV_ATA;

    if ((lbam == 0x14) && (lbah == 0xeb))
        return ATA_DEV_ATAPI;

    if ((lbam == 0x69) && (lbah == 0x96))
        return ATA_DEV_PMP;

    return ATA_DEV_UNKNOWN;
}

static void ata_id_string(const u16 *id, unsigned char *s,
             unsigned int ofs, unsigned int len)
{
    unsigned int c;

    while (len > 0) {
        c = id[ofs] >> 8;
        *s = c;
        s++;

        c = id[ofs] & 0xff;
        *s = c;
        s++;

        ofs++;
        len -= 2;
    }
}

void ata_id_c_string(const u16 *id, unsigned char *s,
             unsigned int ofs, unsigned int len)
{
    unsigned char *p;

    ata_id_string(id, s, ofs, len - 1);

    p = s + strnlen((char *)s, len - 1);
    while (p > s && p[-1] == ' ')
        p--;
    *p = '\0';
}

void ata_dump_id(u16 *id)
{
    unsigned char serial[ATA_ID_SERNO_LEN + 1];
    unsigned char firmware[ATA_ID_FW_REV_LEN + 1];
    unsigned char product[ATA_ID_PROD_LEN + 1];
    u64 n_sectors;

    /* Serial number */
    ata_id_c_string(id, serial, ATA_ID_SERNO, sizeof(serial));
    printf("S/N: %s\n\r", serial);

    /* Firmware version */
    ata_id_c_string(id, firmware, ATA_ID_FW_REV, sizeof(firmware));
    printf("Firmware version: %s\n\r", firmware);

    /* Product model */
    ata_id_c_string(id, product, ATA_ID_PROD, sizeof(product));
    printf("Product model number: %s\n\r", product);

    /* Total sectors of device  */
    n_sectors = ata_id_n_sectors(id);
    printf("Capablity: %lld sectors\n\r", n_sectors);

    printf ("id[49]: capabilities = 0x%04x\n"
        "id[53]: field valid = 0x%04x\n"
        "id[63]: mwdma = 0x%04x\n"
        "id[64]: pio = 0x%04x\n"
        "id[75]: queue depth = 0x%04x\n",
        id[49],
        id[53],
        id[63],
        id[64],
        id[75]);

    printf ("id[76]: sata capablity = 0x%04x\n"
        "id[78]: sata features supported = 0x%04x\n"
        "id[79]: sata features enable = 0x%04x\n",
        id[76],
        id[78],
        id[79]);

    printf ("id[80]: major version = 0x%04x\n"
        "id[81]: minor version = 0x%04x\n"
        "id[82]: command set supported 1 = 0x%04x\n"
        "id[83]: command set supported 2 = 0x%04x\n"
        "id[84]: command set extension = 0x%04x\n",
        id[80],
        id[81],
        id[82],
        id[83],
        id[84]);
    printf ("id[85]: command set enable 1 = 0x%04x\n"
        "id[86]: command set enable 2 = 0x%04x\n"
        "id[87]: command set default = 0x%04x\n"
        "id[88]: udma = 0x%04x\n"
        "id[93]: hardware reset result = 0x%04x\n",
        id[85],
        id[86],
        id[87],
        id[88],
        id[93]);
}

void ata_swap_buf_le16(u16 *buf, unsigned int buf_words)
{
    unsigned int i;

    for (i = 0; i < buf_words; i++)
    {
        buf[i] = le16_to_cpu(buf[i]);
    }
}
