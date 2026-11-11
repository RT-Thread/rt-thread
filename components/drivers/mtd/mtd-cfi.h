/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __MTD_CFI_H__
#define __MTD_CFI_H__

#include <rtthread.h>

/* Values for the width of the port */
#define FLASH_CFI_8BIT                  0x01
#define FLASH_CFI_16BIT                 0x02
#define FLASH_CFI_32BIT                 0x04
#define FLASH_CFI_64BIT                 0x08
/* Values for the width of the chip */
#define FLASH_CFI_BY8                   0x01
#define FLASH_CFI_BY16                  0x02
#define FLASH_CFI_BY32                  0x04
#define FLASH_CFI_BY64                  0x08
/* Values for the flash device interface */
#define FLASH_CFI_X8                    0x00
#define FLASH_CFI_X16                   0x01
#define FLASH_CFI_X8X16                 0x02
#define FLASH_CFI_X16X32                0x05

/* Convert between bit value and numeric value */
#define FLASH_CFI_SHIFT_WIDTH           3

#define FLASH_CMD_CFI                   0x98
#define FLASH_CMD_READ_ID               0x90
#define FLASH_CMD_RESET                 0xff
#define FLASH_CMD_BLOCK_ERASE           0x20
#define FLASH_CMD_ERASE_CONFIRM         0xd0
#define FLASH_CMD_WRITE                 0x40
#define FLASH_CMD_PROTECT               0x60
#define FLASH_CMD_SETUP                 0x60
#define FLASH_CMD_SET_CR_CONFIRM        0x03
#define FLASH_CMD_PROTECT_SET           0x01
#define FLASH_CMD_PROTECT_CLEAR         0xd0
#define FLASH_CMD_CLEAR_STATUS          0x50
#define FLASH_CMD_READ_STATUS           0x70
#define FLASH_CMD_WRITE_TO_BUFFER       0xe8
#define FLASH_CMD_WRITE_BUFFER_PROG     0xe9
#define FLASH_CMD_WRITE_BUFFER_CONFIRM  0xd0

#define FLASH_STATUS_DONE               0x80
#define FLASH_STATUS_ESS                0x40
#define FLASH_STATUS_ECLBS              0x20
#define FLASH_STATUS_PSLBS              0x10
#define FLASH_STATUS_VPENS              0x08
#define FLASH_STATUS_PSS                0x04
#define FLASH_STATUS_DPS                0x02
#define FLASH_STATUS_R                  0x01
#define FLASH_STATUS_PROTECT            0x01

#define FLASH_CONTINUATION_CODE         0x7f

#define FLASH_OFFSET_MANUFACTURER_ID    0x00
#define FLASH_OFFSET_DEVICE_ID          0x01
#define FLASH_OFFSET_LOWER_SW_BITS      0x0c
#define FLASH_OFFSET_DEVICE_ID2         0x0e
#define FLASH_OFFSET_DEVICE_ID3         0x0f
#define FLASH_OFFSET_CFI                0x55
#define FLASH_OFFSET_CFI_ALT            0x555
#define FLASH_OFFSET_CFI_RESP           0x10    /* "QRY" */
#define FLASH_OFFSET_PRIMARY_VENDOR     0x13    /* Primary OEM command set */
#define FLASH_OFFSET_EXT_QUERY_T_P_ADDR 0x15    /* Extended query table primary address */
#define FLASH_OFFSET_WTOUT              0x1f
#define FLASH_OFFSET_WBTOUT             0x20
#define FLASH_OFFSET_ETOUT              0x21
#define FLASH_OFFSET_CETOUT             0x22
#define FLASH_OFFSET_WMAX_TOUT          0x23
#define FLASH_OFFSET_WBMAX_TOUT         0x24
#define FLASH_OFFSET_EMAX_TOUT          0x25
#define FLASH_OFFSET_CEMAX_TOUT         0x26
#define FLASH_OFFSET_SIZE               0x27    /* 2^N bytes */
#define FLASH_OFFSET_INTERFACE          0x28
#define FLASH_OFFSET_BUFFER_SIZE        0x2a
#define FLASH_OFFSET_NUM_ERASE_REGIONS  0x2c
#define FLASH_OFFSET_ERASE_REGIONS      0x2d
#define FLASH_OFFSET_PROTECT            0x02
#define FLASH_OFFSET_USER_PROTECTION    0x85
#define FLASH_OFFSET_INTEL_PROTECTION   0x81

#define CFI_CMDSET_NONE                 0
#define CFI_CMDSET_INTEL_EXTENDED       1
#define CFI_CMDSET_AMD_STANDARD         2
#define CFI_CMDSET_INTEL_STANDARD       3
#define CFI_CMDSET_AMD_EXTENDED         4
#define CFI_CMDSET_MITSU_STANDARD       256
#define CFI_CMDSET_MITSU_EXTENDED       257
#define CFI_CMDSET_SST                  258
#define CFI_CMDSET_INTEL_PROG_REGIONS   512

#define AMD_CMD_RESET                   0xf0
#define AMD_CMD_WRITE                   0xa0
#define AMD_CMD_ERASE_START             0x80
#define AMD_CMD_ERASE_SECTOR            0x30
#define AMD_CMD_UNLOCK_START            0xaa
#define AMD_CMD_UNLOCK_ACK              0x55
#define AMD_CMD_WRITE_TO_BUFFER         0x25
#define AMD_CMD_WRITE_BUFFER_CONFIRM    0x29
#define AMD_CMD_SET_PPB_ENTRY           0xc0
#define AMD_CMD_SET_PPB_EXIT_BC1        0x90
#define AMD_CMD_SET_PPB_EXIT_BC2        0x00
#define AMD_CMD_PPB_UNLOCK_BC1          0x80
#define AMD_CMD_PPB_UNLOCK_BC2          0x30
#define AMD_CMD_PPB_LOCK_BC1            0xa0
#define AMD_CMD_PPB_LOCK_BC2            0x00

#define AMD_STATUS_TOGGLE               0x40
#define AMD_STATUS_ERROR                0x20

#define ATM_CMD_UNLOCK_SECT             0x70
#define ATM_CMD_SOFTLOCK_START          0x80
#define ATM_CMD_LOCK_SECT               0x40

union cfi_word
{
    rt_uint8_t w8;
    rt_uint16_t w16;
    rt_uint32_t w32;
    rt_uint64_t w64;
};

#ifndef CFI_FLASH_SECT_MAX
#define CFI_FLASH_SECT_MAX              512
#endif

#ifndef CFI_QUERY_ERASE_REGIONS_MAX
#define CFI_QUERY_ERASE_REGIONS_MAX     CFI_FLASH_SECT_MAX
#endif

rt_packed(struct cfi_query
{
    rt_uint8_t query[3];            /* "Q" "R" "Y" */
    rt_uint16_t primary_id;         /* Unaligned */
    rt_uint16_t primary_address;    /* Unaligned */
    rt_uint16_t alternate_id;       /* Unaligned */
    rt_uint16_t alternate_address;  /* Unaligned */
    rt_uint8_t vcc_min;
    rt_uint8_t vcc_max;
    rt_uint8_t vpp_min;
    rt_uint8_t vpp_max;
    rt_uint8_t word_write_timeout_type;
    rt_uint8_t buf_write_timeout_type;
    rt_uint8_t block_erase_timeout_type;
    rt_uint8_t chip_erase_timeout_type;
    rt_uint8_t word_write_timeout_max;
    rt_uint8_t buf_write_timeout_max;
    rt_uint8_t block_erase_timeout_max;
    rt_uint8_t chip_erase_timeout_max;
    rt_uint8_t dev_size;
    rt_uint16_t interface_desc;     /* Aligned */
    rt_uint16_t max_buf_write_size; /* Aligned */
    rt_uint8_t num_erase_regions;
    rt_uint32_t erase_region_info[CFI_QUERY_ERASE_REGIONS_MAX]; /* Unaligned */
});

#endif /* __MTD_CFI_H__ */
