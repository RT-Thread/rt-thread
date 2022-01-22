/*
 * This file is part of the Serial Flash Universal Driver Library.
 *
 * Copyright (c) 2016, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: Analyze the SFDP (Serial Flash Discoverable Parameters) which from JESD216/A/B (V1.X) standard.
 *           JESD216  (V1.0) document: http://www.jedec.org/sites/default/files/docs/JESD216.pdf
 *           JESD216A (V1.5) document: http://www.jedec.org/sites/default/files/docs/JESD216A.pdf
 *           JESD216B (V1.6) document: http://www.jedec.org/sites/default/files/docs/JESD216B.pdf
 *
 * Created on: 2016-05-26
 */

#include "../inc/sfud.h"

/**
 * JEDEC Standard JESD216 Terms and definitions:
 *
 * DWORD: Four consecutive 8-bit bytes used as the basic 32-bit building block for headers and parameter tables.
 *
 * Sector: The minimum granularity - size and alignment - of an area that can be erased in the data array
 * of a flash memory device. Different areas within the address range of the data array may have a different
 * minimum erase granularity (sector size).
 */

#ifdef SFUD_USING_SFDP

/* support maximum SFDP major revision by driver */
#define SUPPORT_MAX_SFDP_MAJOR_REV                  1
/* the JEDEC basic flash parameter table length is 9 DWORDs (288-bit) on JESD216 (V1.0) initial release standard */
#define BASIC_TABLE_LEN                             9
/* the smallest eraser in SFDP eraser table */
#define SMALLEST_ERASER_INDEX                       0
/**
 *  SFDP parameter header structure
 */
typedef struct {
    uint8_t id;                                  /**< Parameter ID LSB */
    uint8_t minor_rev;                           /**< Parameter minor revision */
    uint8_t major_rev;                           /**< Parameter major revision */
    uint8_t len;                                 /**< Parameter table length(in double words) */
    uint32_t ptp;                                /**< Parameter table 24bit pointer (byte address) */
} sfdp_para_header;

static sfud_err read_sfdp_data(const sfud_flash *flash, uint32_t addr, uint8_t *read_buf, size_t size);
static bool read_sfdp_header(sfud_flash *flash);
static bool read_basic_header(const sfud_flash *flash, sfdp_para_header *basic_header);
static bool read_basic_table(sfud_flash *flash, sfdp_para_header *basic_header);

/* ../port/sfup_port.c */
extern void sfud_log_debug(const char *file, const long line, const char *format, ...);
extern void sfud_log_info(const char *format, ...);

/**
 * Read SFDP parameter information
 *
 * @param flash flash device
 *
 * @return true: read OK
 */
bool sfud_read_sfdp(sfud_flash *flash) {
    SFUD_ASSERT(flash);

    /* JEDEC basic flash parameter header */
    sfdp_para_header basic_header;
    if (read_sfdp_header(flash) && read_basic_header(flash, &basic_header)) {
        return read_basic_table(flash, &basic_header);
    } else {
        SFUD_INFO("Warning: Read SFDP parameter header information failed. The %s is not support JEDEC SFDP.", flash->name);
        return false;
    }
}

/**
 * Read SFDP parameter header
 *
 * @param flash flash device
 *
 * @return true: read OK
 */
static bool read_sfdp_header(sfud_flash *flash) {
    sfud_sfdp *sfdp = &flash->sfdp;
    /* The SFDP header is located at address 000000h of the SFDP data structure.
     * It identifies the SFDP Signature, the number of parameter headers, and the SFDP revision numbers. */
    /* sfdp parameter header address */
    uint32_t header_addr = 0;
    /* each parameter header being 2 DWORDs (64-bit) */
    uint8_t header[2 * 4] = { 0 };

    SFUD_ASSERT(flash);

    sfdp->available = false;
    /* read SFDP header */
    if (read_sfdp_data(flash, header_addr, header, sizeof(header)) != SFUD_SUCCESS) {
        SFUD_INFO("Error: Can't read SFDP header.");
        return false;
    }
    /* check SFDP header */
    if (!(header[0] == 'S' &&
          header[1] == 'F' &&
          header[2] == 'D' &&
          header[3] == 'P')) {
        SFUD_DEBUG("Error: Check SFDP signature error. It's must be 50444653h('S' 'F' 'D' 'P').");
        return false;
    }
    sfdp->minor_rev = header[4];
    sfdp->major_rev = header[5];
    if (sfdp->major_rev > SUPPORT_MAX_SFDP_MAJOR_REV) {
        SFUD_INFO("Error: This reversion(V%d.%d) SFDP is not supported.", sfdp->major_rev, sfdp->minor_rev);
        return false;
    }
    SFUD_DEBUG("Check SFDP header is OK. The reversion is V%d.%d, NPN is %d.", sfdp->major_rev, sfdp->minor_rev,
            header[6]);

    return true;
}

/**
 * Read JEDEC basic parameter header
 *
 * @param flash flash device
 *
 * @return true: read OK
 */
static bool read_basic_header(const sfud_flash *flash, sfdp_para_header *basic_header) {
    /* The basic parameter header is mandatory, is defined by this standard, and starts at byte offset 08h. */
    uint32_t header_addr = 8;
    /* each parameter header being 2 DWORDs (64-bit) */
    uint8_t header[2 * 4] = { 0 };

    SFUD_ASSERT(flash);
    SFUD_ASSERT(basic_header);

    /* read JEDEC basic flash parameter header */
    if (read_sfdp_data(flash, header_addr, header, sizeof(header)) != SFUD_SUCCESS) {
        SFUD_INFO("Error: Can't read JEDEC basic flash parameter header.");
        return false;
    }
    basic_header->id        = header[0];
    basic_header->minor_rev = header[1];
    basic_header->major_rev = header[2];
    basic_header->len       = header[3];
    basic_header->ptp       = (long)header[4] | (long)header[5] << 8 | (long)header[6] << 16;
    /* check JEDEC basic flash parameter header */
    if (basic_header->major_rev > SUPPORT_MAX_SFDP_MAJOR_REV) {
        SFUD_INFO("Error: This reversion(V%d.%d) JEDEC basic flash parameter header is not supported.",
                basic_header->major_rev, basic_header->minor_rev);
        return false;
    }
    if (basic_header->len < BASIC_TABLE_LEN) {
        SFUD_INFO("Error: The JEDEC basic flash parameter table length (now is %d) error.", basic_header->len);
        return false;
    }
    SFUD_DEBUG("Check JEDEC basic flash parameter header is OK. The table id is %d, reversion is V%d.%d,"
            " length is %d, parameter table pointer is 0x%06lX.", basic_header->id, basic_header->major_rev,
            basic_header->minor_rev, basic_header->len, basic_header->ptp);

    return true;
}

/**
 * Read JEDEC basic parameter table
 *
 * @param flash flash device
 *
 * @return true: read OK
 */
static bool read_basic_table(sfud_flash *flash, sfdp_para_header *basic_header) {
    sfud_sfdp *sfdp = &flash->sfdp;
    /* parameter table address */
    uint32_t table_addr = basic_header->ptp;
    /* parameter table */
    uint8_t table[BASIC_TABLE_LEN * 4] = { 0 }, i, j;

    SFUD_ASSERT(flash);
    SFUD_ASSERT(basic_header);

    /* read JEDEC basic flash parameter table */
    if (read_sfdp_data(flash, table_addr, table, sizeof(table)) != SFUD_SUCCESS) {
        SFUD_INFO("Warning: Can't read JEDEC basic flash parameter table.");
        return false;
    }
    /* print JEDEC basic flash parameter table info */
    SFUD_DEBUG("JEDEC basic flash parameter table info:");
    SFUD_DEBUG("MSB-LSB  3    2    1    0");
    for (i = 0; i < BASIC_TABLE_LEN; i++) {
        SFUD_DEBUG("[%04d] 0x%02X 0x%02X 0x%02X 0x%02X", i + 1, table[i * 4 + 3], table[i * 4 + 2], table[i * 4 + 1],
                table[i * 4]);
    }

    /* get block/sector 4 KB erase supported and command */
    sfdp->erase_4k_cmd = table[1];
    switch (table[0] & 0x03) {
    case 1:
        sfdp->erase_4k = true;
        SFUD_DEBUG("4 KB Erase is supported throughout the device. Command is 0x%02X.", sfdp->erase_4k_cmd);
        break;
    case 3:
        sfdp->erase_4k = false;
        SFUD_DEBUG("Uniform 4 KB erase is unavailable for this device.");
        break;
    default:
        SFUD_INFO("Error: Uniform 4 KB erase supported information error.");
        return false;
    }
    /* get write granularity */
    //TODO 目前为 1.0 所提供的方式，后期支持 V1.5 及以上的方式读取 page size
    switch ((table[0] & (0x01 << 2)) >> 2) {
    case 0:
        sfdp->write_gran = 1;
        SFUD_DEBUG("Write granularity is 1 byte.");
        break;
    case 1:
        sfdp->write_gran = 256;
        SFUD_DEBUG("Write granularity is 64 bytes or larger.");
        break;
    }
    /* volatile status register block protect bits */
    switch ((table[0] & (0x01 << 3)) >> 3) {
    case 0:
        /* Block Protect bits in device's status register are solely non-volatile or may be
         * programmed either as volatile using the 50h instruction for write enable or non-volatile
         * using the 06h instruction for write enable.
         */
        sfdp->sr_is_non_vola = true;
        SFUD_DEBUG("Target flash status register is non-volatile.");
        break;
    case 1:
        /* block protect bits in device's status register are solely volatile. */
        sfdp->sr_is_non_vola = false;
        SFUD_DEBUG("Block Protect bits in device's status register are solely volatile.");
        /* write enable instruction select for writing to volatile status register */
        switch ((table[0] & (0x01 << 4)) >> 4) {
        case 0:
            sfdp->vola_sr_we_cmd = SFUD_VOLATILE_SR_WRITE_ENABLE;
            SFUD_DEBUG("Flash device requires instruction 50h as the write enable prior "
                    "to performing a volatile write to the status register.");
            break;
        case 1:
            sfdp->vola_sr_we_cmd = SFUD_CMD_WRITE_ENABLE;
            SFUD_DEBUG("Flash device requires instruction 06h as the write enable prior "
                    "to performing a volatile write to the status register.");
            break;
        }
        break;
    }
    /* get address bytes, number of bytes used in addressing flash array read, write and erase. */
    switch ((table[2] & (0x03 << 1)) >> 1) {
    case 0:
        sfdp->addr_3_byte = true;
        sfdp->addr_4_byte = false;
        SFUD_DEBUG("3-Byte only addressing.");
        break;
    case 1:
        sfdp->addr_3_byte = true;
        sfdp->addr_4_byte = true;
        SFUD_DEBUG("3- or 4-Byte addressing.");
        break;
    case 2:
        sfdp->addr_3_byte = false;
        sfdp->addr_4_byte = true;
        SFUD_DEBUG("4-Byte only addressing.");
        break;
    default:
        sfdp->addr_3_byte = false;
        sfdp->addr_4_byte = false;
        SFUD_INFO("Error: Read address bytes error!");
        return false;
    }
    /* get flash memory capacity */
    uint32_t table2_temp = ((long)table[7] << 24) | ((long)table[6] << 16) | ((long)table[5] << 8) | (long)table[4];
    switch ((table[7] & (0x01 << 7)) >> 7) {
    case 0:
        sfdp->capacity = 1 + (table2_temp >> 3);
        break;
    case 1:
        table2_temp &= 0x7FFFFFFF;
        if (table2_temp > sizeof(sfdp->capacity) * 8 + 3) {
            sfdp->capacity = 0;
            SFUD_INFO("Error: The flash capacity is grater than 32 Gb/ 4 GB! Not Supported.");
            return false;
        }
        sfdp->capacity = 1L << (table2_temp - 3);
        break;
    }
    SFUD_DEBUG("Capacity is %ld Bytes.", sfdp->capacity);
    /* get erase size and erase command  */
    for (i = 0, j = 0; i < SFUD_SFDP_ERASE_TYPE_MAX_NUM; i++) {
        if (table[28 + 2 * i] != 0x00) {
            sfdp->eraser[j].size = 1L << table[28 + 2 * i];
            sfdp->eraser[j].cmd = table[28 + 2 * i + 1];
            SFUD_DEBUG("Flash device supports %ldKB block erase. Command is 0x%02X.", sfdp->eraser[j].size / 1024,
                    sfdp->eraser[j].cmd);
            j++;
        }
    }
    /* sort the eraser size from small to large */
    for (i = 0, j = 0; i < SFUD_SFDP_ERASE_TYPE_MAX_NUM; i++) {
        if (sfdp->eraser[i].size) {
            for (j = i + 1; j < SFUD_SFDP_ERASE_TYPE_MAX_NUM; j++) {
                if (sfdp->eraser[j].size != 0 && sfdp->eraser[i].size > sfdp->eraser[j].size) {
                    /* swap the small eraser */
                    uint32_t temp_size = sfdp->eraser[i].size;
                    uint8_t temp_cmd = sfdp->eraser[i].cmd;
                    sfdp->eraser[i].size = sfdp->eraser[j].size;
                    sfdp->eraser[i].cmd = sfdp->eraser[j].cmd;
                    sfdp->eraser[j].size = temp_size;
                    sfdp->eraser[j].cmd = temp_cmd;
                }
            }
        }
    }

    sfdp->available = true;
    return true;
}

static sfud_err read_sfdp_data(const sfud_flash *flash, uint32_t addr, uint8_t *read_buf, size_t size) {
    uint8_t cmd[] = {
            SFUD_CMD_READ_SFDP_REGISTER,
            (addr >> 16) & 0xFF,
            (addr >> 8) & 0xFF,
            (addr >> 0) & 0xFF,
            SFUD_DUMMY_DATA,
    };

    SFUD_ASSERT(flash);
    SFUD_ASSERT(addr < 1L << 24);
    SFUD_ASSERT(read_buf);
    SFUD_ASSERT(flash->spi.wr);

    return flash->spi.wr(&flash->spi, cmd, sizeof(cmd), read_buf, size);
}

/**
 * get the most suitable eraser for erase process from SFDP parameter
 *
 * @param flash flash device
 * @param addr start address
 * @param erase_size will be erased size
 *
 * @return the eraser index of SFDP eraser table  @see sfud_sfdp.eraser[]
 */
size_t sfud_sfdp_get_suitable_eraser(const sfud_flash *flash, uint32_t addr, size_t erase_size) {
    size_t index = SMALLEST_ERASER_INDEX, i;
    /* only used when flash supported SFDP */
    SFUD_ASSERT(flash->sfdp.available);
    /* the address isn't align by smallest eraser's size, then use the smallest eraser */
    if (addr % flash->sfdp.eraser[SMALLEST_ERASER_INDEX].size) {
        return SMALLEST_ERASER_INDEX;
    }
    /* Find the suitable eraser.
     * The largest size eraser is at the end of eraser table.
     * In order to decrease erase command counts, so the find process is from the end of eraser table. */
    for (i = SFUD_SFDP_ERASE_TYPE_MAX_NUM - 1;; i--) {
        if ((flash->sfdp.eraser[i].size != 0) && (erase_size >= flash->sfdp.eraser[i].size)
                && (addr % flash->sfdp.eraser[i].size == 0)) {
            index = i;
            break;
        }
        if (i == SMALLEST_ERASER_INDEX) {
            break;
        }
    }
    return index;
}

#endif /* SFUD_USING_SFDP */
