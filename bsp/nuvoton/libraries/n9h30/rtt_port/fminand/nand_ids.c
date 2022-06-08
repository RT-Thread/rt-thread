/*
 *  Copyright (C) 2002 Thomas Gleixner (tglx@linutronix.de)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
//#include <common.h>
#include <rtthread.h>
#include "linux/mtd/nand.h"
#include "linux/sizes.h"

#define LP_OPTIONS NAND_SAMSUNG_LP_OPTIONS
#define LP_OPTIONS16 (LP_OPTIONS | NAND_BUSWIDTH_16)

#define SP_OPTIONS NAND_NEED_READRDY
#define SP_OPTIONS16 (SP_OPTIONS | NAND_BUSWIDTH_16)

/*
 * The chip ID list:
 *    name, device ID, page size, chip size in MiB, eraseblock size, options
 *
 * If page size and eraseblock size are 0, the sizes are taken from the
 * extended chip ID.
 */
struct nand_flash_dev nand_flash_ids[] =
{
#ifdef CONFIG_MTD_NAND_MUSEUM_IDS
    LEGACY_ID_NAND("NAND 1MiB 5V 8-bit",    0x6e, 1, SZ_4K, SP_OPTIONS),
    LEGACY_ID_NAND("NAND 2MiB 5V 8-bit",    0x64, 2, SZ_4K, SP_OPTIONS),
    LEGACY_ID_NAND("NAND 1MiB 3,3V 8-bit",  0xe8, 1, SZ_4K, SP_OPTIONS),
    LEGACY_ID_NAND("NAND 1MiB 3,3V 8-bit",  0xec, 1, SZ_4K, SP_OPTIONS),
    LEGACY_ID_NAND("NAND 2MiB 3,3V 8-bit",  0xea, 2, SZ_4K, SP_OPTIONS),
    LEGACY_ID_NAND("NAND 4MiB 3,3V 8-bit",  0xd5, 4, SZ_8K, SP_OPTIONS),

    LEGACY_ID_NAND("NAND 8MiB 3,3V 8-bit",  0xe6, 8, SZ_8K, SP_OPTIONS),
#endif
    /*
     * Some incompatible NAND chips share device ID's and so must be
     * listed by full ID. We list them first so that we can easily identify
     * the most specific match.
     */
    {
        "TC58NVG0S3E 1G 3.3V 8-bit",
        {0x98, 0xd1, 0x90, 0x15, 0x76, 0x14, 0x01, 0x00},
        SZ_2K, SZ_128, SZ_128K, 0, 8, 64, {1, SZ_512}, 2
    },
    {
        "TC58NVG2S0F 4G 3.3V 8-bit",
        {0x98, 0xdc, 0x90, 0x26, 0x76, 0x15, 0x01, 0x08},
        SZ_4K, SZ_512, SZ_256K, 0, 8, 224, {4, SZ_512}, 2
    },
    {
        "TC58NVG3S0F 8G 3.3V 8-bit",
        {0x98, 0xd3, 0x90, 0x26, 0x76, 0x15, 0x02, 0x08},
        SZ_4K, SZ_1K, SZ_256K, 0, 8, 232, {4, SZ_512}, 2
    },
    {
        "TC58NVG5D2 32G 3.3V 8-bit",
        {0x98, 0xd7, 0x94, 0x32, 0x76, 0x56, 0x09, 0x00},
        SZ_8K, SZ_4K, SZ_1M, 0, 8, 640, {40, SZ_1K}, 2
    },
    {
        "TC58NVG6D2 64G 3.3V 8-bit",
        {0x98, 0xde, 0x94, 0x82, 0x76, 0x56, 0x04, 0x20},
        SZ_8K, SZ_8K, SZ_2M, 0, 8, 640, {40, SZ_1K}, 2
    },
    {
        "SDTNRGAMA 64G 3.3V 8-bit",
        {0x45, 0xde, 0x94, 0x93, 0x76, 0x50, 0x00, 0x00},
        SZ_16K, SZ_8K, SZ_4M, 0, 6, 1280, {40, SZ_1K}, 2
    },
    {
        "H27UCG8T2ATR-BC 64G 3.3V 8-bit",
        {0xad, 0xde, 0x94, 0xda, 0x74, 0xc4, 0x00, 0x00},
        SZ_8K, SZ_8K, SZ_2M, NAND_NEED_SCRAMBLING, 6, 640,
        {40, SZ_1K}, 4
    },
    {
        "H27QCG8T2E5RBCF 64G 3.3V 8-bit",
        {0xad, 0xde, 0x14, 0xa7, 0x42, 0x4a, 0x00, 0x00},
        SZ_16K, SZ_8K, SZ_4M, NAND_NEED_SCRAMBLING, 6, 1664,
        {56, SZ_1K}, 1
    },

    {"NAND 4MiB 5V 8-bit", {0, 0x6B, 0, 0, 0, 0, 0, 0,}, 512, 4, SZ_8K, SP_OPTIONS, 0},
    {"NAND 4MiB 3,3V 8-bit", {0, 0xE3}, 512, 4, SZ_8K, SP_OPTIONS},
    {"NAND 4MiB 3,3V 8-bit", {0, 0xE5}, 512, 4, SZ_8K, SP_OPTIONS},
    {"NAND 8MiB 3,3V 8-bit", {0, 0xD6}, 512, 8, SZ_8K, SP_OPTIONS},
    {"NAND 8MiB 3,3V 8-bit", {0, 0xE6}, 512, 8, SZ_8K, SP_OPTIONS},

    {"NAND 16MiB 1,8V 8-bit", {0, 0x33}, 512, 16, SZ_16K, SP_OPTIONS},
    {"NAND 16MiB 3,3V 8-bit", {0, 0x73}, 512, 16, SZ_16K, SP_OPTIONS},
    {"NAND 16MiB 1,8V 16-bit", {0, 0x43}, 512, 16, SZ_16K, SP_OPTIONS16},
    {"NAND 16MiB 3,3V 16-bit", {0, 0x53}, 512, 16, SZ_16K, SP_OPTIONS16},

    {"NAND 32MiB 1,8V 8-bit", {0, 0x35}, 512, 32, SZ_16K, SP_OPTIONS},
    {"NAND 32MiB 3,3V 8-bit", {0, 0x75}, 512, 32, SZ_16K, SP_OPTIONS},
    {"NAND 32MiB 1,8V 16-bit", {0, 0x45}, 512, 32, SZ_16K, SP_OPTIONS16},
    {"NAND 32MiB 3,3V 16-bit", {0, 0x55}, 512, 32, SZ_16K, SP_OPTIONS16},

    {"NAND 64MiB 1,8V 8-bit", {0, 0x36}, 512, 64, SZ_16K, SP_OPTIONS},
    {"NAND 64MiB 3,3V 8-bit", {0, 0x76}, 512, 64, SZ_16K, SP_OPTIONS},
    {"NAND 64MiB 1,8V 16-bit", {0, 0x46}, 512, 64, SZ_16K, SP_OPTIONS16},
    {"NAND 64MiB 3,3V 16-bit", {0, 0x56}, 512, 64, SZ_16K, SP_OPTIONS16},

    {"NAND 128MiB 1,8V 8-bit", {0, 0x78}, 512, 128, SZ_16K, SP_OPTIONS},
    {"NAND 128MiB 1,8V 8-bit", {0, 0x39}, 512, 128, SZ_16K, SP_OPTIONS},
    {"NAND 128MiB 3,3V 8-bit", {0, 0x79}, 512, 128, SZ_16K, SP_OPTIONS},
    {"NAND 128MiB 1,8V 16-bit", {0, 0x72}, 512, 128, SZ_16K, SP_OPTIONS16},
    {"NAND 128MiB 1,8V 16-bit", {0, 0x49}, 512, 128, SZ_16K, SP_OPTIONS16},
    {"NAND 128MiB 3,3V 16-bit", {0, 0x74}, 512, 128, SZ_16K, SP_OPTIONS16},
    {"NAND 128MiB 3,3V 16-bit", {0, 0x59}, 512, 128, SZ_16K, SP_OPTIONS16},

    {"NAND 256MiB 3,3V 8-bit", {0, 0x71}, 512, 256, SZ_16K, SP_OPTIONS},

    /*
     * These are the new chips with large page size. Their page size and
     * eraseblock size are determined from the extended ID bytes.
     */

    /* 512 Megabit */
    {"NAND 64MiB 1,8V 8-bit", {0, 0xA2}, 0, 64, 0, LP_OPTIONS, 0},
    {"NAND 64MiB 1,8V 8-bit", {0, 0xA0}, 0, 64, 0, LP_OPTIONS, 0},
    {"NAND 64MiB 3,3V 8-bit", {0, 0xF2}, 0, 64, 0, LP_OPTIONS, 0},
    {"NAND 64MiB 3,3V 8-bit", {0, 0xD0}, 0, 64, 0, LP_OPTIONS, 0},
    {"NAND 64MiB 3,3V 8-bit", {0, 0xF0}, 0, 64, 0, LP_OPTIONS, 0},
    {"NAND 64MiB 1,8V 16-bit", {0, 0xB2}, 0, 64, 0, LP_OPTIONS16, 0},
    {"NAND 64MiB 1,8V 16-bit", {0, 0xB0}, 0, 64, 0, LP_OPTIONS16, 0},
    {"NAND 64MiB 3,3V 16-bit", {0, 0xC2}, 0, 64, 0, LP_OPTIONS16, 0},
    {"NAND 64MiB 3,3V 16-bit", {0, 0xC0}, 0, 64, 0, LP_OPTIONS16, 0},

    /* 1 Gigabit */
    {"NAND 128MiB 1,8V 8-bit", {0, 0xA1}, 0, 128, 0, LP_OPTIONS, 0},
    {"NAND 128MiB 3,3V 8-bit", {0, 0xF1}, 0, 128, 0, LP_OPTIONS, 0},
    {"NAND 128MiB 3,3V 8-bit", {0, 0xD1}, 0, 128, 0, LP_OPTIONS, 0},
    {"NAND 128MiB 1,8V 16-bit", {0, 0xB1}, 0, 128, 0, LP_OPTIONS16, 0},
    {"NAND 128MiB 3,3V 16-bit", {0, 0xC1}, 0, 128, 0, LP_OPTIONS16, 0},
    {"NAND 128MiB 1,8V 16-bit", {0, 0xAD}, 0, 128, 0, LP_OPTIONS16, 0},

    /* 2 Gigabit */
    {"NAND 256MiB 1,8V 8-bit", {0, 0xAA}, 0, 256, 0, LP_OPTIONS, 0},
    {"NAND 256MiB 3,3V 8-bit", {0, 0xDA}, 0, 256, 0, LP_OPTIONS, 0},
    {"NAND 256MiB 1,8V 16-bit", {0, 0xBA}, 0, 256, 0, LP_OPTIONS16, 0},
    {"NAND 256MiB 3,3V 16-bit", {0, 0xCA}, 0, 256, 0, LP_OPTIONS16, 0},

    /* 4 Gigabit */
    {"NAND 512MiB 1,8V 8-bit", {0, 0xAC}, 0, 512, 0, LP_OPTIONS, 0},
    {"NAND 512MiB 3,3V 8-bit", {0, 0xDC}, 0, 512, 0, LP_OPTIONS, 0},
    {"NAND 512MiB 1,8V 16-bit", {0, 0xBC}, 0, 512, 0, LP_OPTIONS16, 0},
    {"NAND 512MiB 3,3V 16-bit", {0, 0xCC}, 0, 512, 0, LP_OPTIONS16, 0},

    /* 8 Gigabit */
    {"NAND 1GiB 1,8V 8-bit", {0, 0xA3}, 0, 1024, 0, LP_OPTIONS, 0},
    {"NAND 1GiB 3,3V 8-bit", {0, 0xD3}, 0, 1024, 0, LP_OPTIONS, 0},
    {"NAND 1GiB 1,8V 16-bit", {0, 0xB3}, 0, 1024, 0, LP_OPTIONS16, 0},
    {"NAND 1GiB 3,3V 16-bit", {0, 0xC3}, 0, 1024, 0, LP_OPTIONS16, 0},

    /* 16 Gigabit */
    {"NAND 2GiB 1,8V 8-bit", {0, 0xA5}, 0, 2048, 0, LP_OPTIONS, 0},
    {"NAND 2GiB 3,3V 8-bit", {0, 0xD5}, 0, 2048, 0, LP_OPTIONS, 0},
    {"NAND 2GiB 1,8V 16-bit", {0, 0xB5}, 0, 2048, 0, LP_OPTIONS16, 0},
    {"NAND 2GiB 3,3V 16-bit", {0, 0xC5}, 0, 2048, 0, LP_OPTIONS16, 0},

    /* 32 Gigabit */
    {"NAND 4GiB 1,8V 8-bit", {0, 0xA7}, 0, 4096, 0, LP_OPTIONS, 0},
    {"NAND 4GiB 3,3V 8-bit", {0, 0xD7}, 0, 4096, 0, LP_OPTIONS, 0},
    {"NAND 4GiB 1,8V 16-bit", {0, 0xB7}, 0, 4096, 0, LP_OPTIONS16, 0},
    {"NAND 4GiB 3,3V 16-bit", {0, 0xC7}, 0, 4096, 0, LP_OPTIONS16, 0},

    /* 64 Gigabit */
    {"NAND 8GiB 1,8V 8-bit", {0, 0xAE}, 0, 8192, 0, LP_OPTIONS, 0},
    {"NAND 8GiB 3,3V 8-bit", {0, 0xDE}, 0, 8192, 0, LP_OPTIONS, 0},
    {"NAND 8GiB 1,8V 16-bit", {0, 0xBE}, 0, 8192, 0, LP_OPTIONS16, 0},
    {"NAND 8GiB 3,3V 16-bit", {0, 0xCE}, 0, 8192, 0, LP_OPTIONS16, 0},

    /* 128 Gigabit */
    {"NAND 16GiB 1,8V 8-bit", {0, 0x1A}, 0, 16384, 0, LP_OPTIONS, 0},
    {"NAND 16GiB 3,3V 8-bit", {0, 0x3A}, 0, 16384, 0, LP_OPTIONS, 0},
    {"NAND 16GiB 1,8V 16-bit", {0, 0x2A}, 0, 16384, 0, LP_OPTIONS16, 0},
    {"NAND 16GiB 3,3V 16-bit", {0, 0x4A}, 0, 16384, 0, LP_OPTIONS16, 0},

    /* 256 Gigabit */
    {"NAND 32GiB 1,8V 8-bit", {0, 0x1C}, 0, 32768, 0, LP_OPTIONS, 0},
    {"NAND 32GiB 3,3V 8-bit", {0, 0x3C}, 0, 32768, 0, LP_OPTIONS, 0},
    {"NAND 32GiB 1,8V 16-bit", {0, 0x2C}, 0, 32768, 0, LP_OPTIONS16, 0},
    {"NAND 32GiB 3,3V 16-bit", {0, 0x4C}, 0, 32768, 0, LP_OPTIONS16, 0},

    /* 512 Gigabit */
    {"NAND 64GiB 1,8V 8-bit", {0, 0x1E}, 0, 65536, 0, LP_OPTIONS, 0},
    {"NAND 64GiB 3,3V 8-bit", {0, 0x3E}, 0, 65536, 0, LP_OPTIONS, 0},
    {"NAND 64GiB 1,8V 16-bit", {0, 0x2E}, 0, 65536, 0, LP_OPTIONS16, 0},
    {"NAND 64GiB 3,3V 16-bit", {0, 0x4E}, 0, 65536, 0, LP_OPTIONS16, 0},

    {NULL}
};

/* Manufacturer IDs */
struct nand_manufacturers nand_manuf_ids[] =
{
    {NAND_MFR_TOSHIBA, "Toshiba"},
    {NAND_MFR_SAMSUNG, "Samsung"},
    {NAND_MFR_FUJITSU, "Fujitsu"},
    {NAND_MFR_NATIONAL, "National"},
    {NAND_MFR_RENESAS, "Renesas"},
    {NAND_MFR_STMICRO, "ST Micro"},
    {NAND_MFR_HYNIX, "Hynix"},
    {NAND_MFR_MICRON, "Micron"},
    {NAND_MFR_AMD, "AMD/Spansion"},
    {NAND_MFR_MACRONIX, "Macronix"},
    {NAND_MFR_EON, "Eon"},
    {NAND_MFR_SANDISK, "SanDisk"},
    {NAND_MFR_INTEL, "Intel"},
    {NAND_MFR_ATO, "ATO"},
    {0x0, "Unknown"}
};

EXPORT_SYMBOL(nand_manuf_ids);
EXPORT_SYMBOL(nand_flash_ids);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Thomas Gleixner <tglx@linutronix.de>");
MODULE_DESCRIPTION("Nand device & manufacturer IDs");
