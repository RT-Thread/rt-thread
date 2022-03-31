/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-19     lizhirui     porting to ls2k
 */

#ifndef __FIS_H__
#define __FIS_H__
/*
* Register - Host to Device FIS
*/
typedef struct sata_fis_h2d
{
    u8 fis_type;
    u8 pm_port_c;
    u8 command;
    u8 features;
    u8 lba_low;
    u8 lba_mid;
    u8 lba_high;
    u8 device;
    u8 lba_low_exp;
    u8 lba_mid_exp;
    u8 lba_high_exp;
    u8 features_exp;
    u8 sector_count;
    u8 sector_count_exp;
    u8 res1;
    u8 control;
    u8 res2[4];
} __attribute__((packed)) sata_fis_h2d_t;

/*
* Register - Host to Device FIS for read/write FPDMA queued
*/
typedef struct sata_fis_h2d_ncq
{
    u8 fis_type;
    u8 pm_port_c;
    u8 command;
    u8 sector_count_low;
    u8 lba_low;
    u8 lba_mid;
    u8 lba_high;
    u8 device;
    u8 lba_low_exp;
    u8 lba_mid_exp;
    u8 lba_high_exp;
    u8 sector_count_high;
    u8 tag;
    u8 res1;
    u8 res2;
    u8 control;
    u8 res3[4];
} __attribute__((packed)) sata_fis_h2d_ncq_t;

/*
* Register - Device to Host FIS
*/
typedef struct sata_fis_d2h
{
    u8 fis_type;
    u8 pm_port_i;
    u8 status;
    u8 error;
    u8 lba_low;
    u8 lba_mid;
    u8 lba_high;
    u8 device;
    u8 lba_low_exp;
    u8 lba_mid_exp;
    u8 lba_high_exp;
    u8 res1;
    u8 sector_count;
    u8 sector_count_exp;
    u8 res2[2];
    u8 res3[4];
} __attribute__((packed)) sata_fis_d2h_t;

/*
* DMA Setup - Device to Host or Host to Device FIS
*/
typedef struct sata_fis_dma_setup
{
    u8 fis_type;
    u8 pm_port_dir_int_act;
    u8 res1;
    u8 res2;
    u32 dma_buffer_id_low;
    u32 dma_buffer_id_high;
    u32 res3;
    u32 dma_buffer_offset;
    u32 dma_transfer_count;
    u32 res4;
} __attribute__((packed)) sata_fis_dma_setup_t;

/*
* PIO Setup - Device to Host FIS
*/
typedef struct sata_fis_pio_setup
{
    u8 fis_type;
    u8 pm_port_dir_int;
    u8 status;
    u8 error;
    u8 lba_low;
    u8 lba_mid;
    u8 lba_high;
    u8 res1;
    u8 lba_low_exp;
    u8 lba_mid_exp;
    u8 lba_high_exp;
    u8 res2;
    u8 sector_count;
    u8 sector_count_exp;
    u8 res3;
    u8 e_status;
    u16 transfer_count;
    u16 res4;
} __attribute__((packed)) sata_fis_pio_setup_t;

/*
* Data - Host to Device or Device to Host FIS
*/
typedef struct sata_fis_data
{
    u8 fis_type;
    u8 pm_port;
    u8 res1;
    u8 res2;
    u32 data[2048];
} __attribute__((packed)) sata_fis_data_t;

/* fis_type - SATA FIS type
 */
enum sata_fis_type
{
    SATA_FIS_TYPE_REGISTER_H2D = 0x27,
    SATA_FIS_TYPE_REGISTER_D2H = 0x34,
    SATA_FIS_TYPE_DMA_ACT_D2H = 0x39,
    SATA_FIS_TYPE_DMA_SETUP_BI = 0x41,
    SATA_FIS_TYPE_DATA_BI = 0x46,
    SATA_FIS_TYPE_BIST_ACT_BI = 0x58,
    SATA_FIS_TYPE_PIO_SETUP_D2H = 0x5F,
    SATA_FIS_TYPE_SET_DEVICE_BITS_D2H = 0xA1,
};

#endif /* __FIS_H__ */
