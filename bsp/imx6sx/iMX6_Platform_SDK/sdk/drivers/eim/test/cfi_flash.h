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

#ifndef _FLASH_H_
#define _FLASH_H_

#include "sdk.h"

#define flash_print printf

#define OK  0
#define ERR 1

#define CFG_FLASH_CFI
#define CFG_FLASH_CFI_DRIVER
#define CFG_FLASH_USE_BUFFER_WRITE

#define CFG_HZ		1000
#define CFG_MAX_FLASH_BANKS	1
#define CFG_MAX_FLASH_SECT	512*2

#define FLASH_CFI_8BIT		0x01
#define FLASH_CFI_16BIT		0x02
#define FLASH_CFI_BY8		0x01
#define FLASH_CFI_BY16		0x02
#define FLASH_CFI_BY32		0x04
#define CFI_FLASH_SHIFT_WIDTH	3
#define FLASH_CFI_X8		0x00
#define FLASH_CFI_X16		0x01
#define FLASH_CFI_X8X16		0x02

#define FLASH_UNKNOWN   0xFFFF

#define CFI_FLASH_SHIFT_WIDTH	3

#define ERR_OK				0
#define ERR_TIMOUT			1
#define ERR_NOT_ERASED			2
#define ERR_PROTECTED			4
#define ERR_INVAL			8
#define ERR_ALIGN			16
#define ERR_UNKNOWN_FLASH_VENDOR	32
#define ERR_UNKNOWN_FLASH_TYPE		64
#define ERR_PROG_ERROR			128

#define FLAG_PROTECT_SET	0x01
#define FLAG_PROTECT_CLEAR	0x02

/* commands */
#define FLASH_CMD_CFI			0x98
#define FLASH_CMD_READ_ID		0x90
#define FLASH_CMD_RESET			0xff
#define FLASH_CMD_BLOCK_ERASE		0x20
#define FLASH_CMD_ERASE_CONFIRM		0xD0
#define FLASH_CMD_WRITE			0x40
#define FLASH_CMD_PROTECT		0x60
#define FLASH_CMD_PROTECT_SET		0x01
#define FLASH_CMD_PROTECT_CLEAR		0xD0
#define FLASH_CMD_CLEAR_STATUS		0x50
#define FLASH_CMD_WRITE_TO_BUFFER	0xE8
#define FLASH_CMD_WRITE_BUFFER_CONFIRM	0xD0

#define FLASH_STATUS_DONE		0x80
#define FLASH_STATUS_ESS		0x40
#define FLASH_STATUS_ECLBS		0x20
#define FLASH_STATUS_PSLBS		0x10
#define FLASH_STATUS_VPENS		0x08
#define FLASH_STATUS_PSS		0x04
#define FLASH_STATUS_DPS		0x02
#define FLASH_STATUS_R			0x01
#define FLASH_STATUS_PROTECT		0x01

#define AMD_CMD_RESET			0xF0
#define AMD_CMD_WRITE			0xA0
#define AMD_CMD_ERASE_START		0x80
#define AMD_CMD_ERASE_SECTOR		0x30
#define AMD_CMD_ERASE_CHIP  		0x10
#define AMD_CMD_UNLOCK_START		0xAA
#define AMD_CMD_UNLOCK_ACK		0x55

#define AMD_CMD_WRITE_TO_BUFFER 	 0x25
#define AMD_CMD_WRITE_BUFFER_CONFIRM 0x29

#define AMD_DQ7				0x80
#define AMD_DQ5				0x20
#define AMD_STATUS_TIMEOUT		0x20

#define AMD_STATUS_TOGGLE		0x40
#define AMD_STATUS_ERROR		0x20

#define AMD_ADDR_ERASE_START	0x555
#define AMD_ADDR_START			0x555
#define AMD_ADDR_ACK			0x2AA

#define FLASH_OFFSET_CFI		0x55
#define FLASH_OFFSET_CFI_RESP		0x10
#define FLASH_OFFSET_PRIMARY_VENDOR	0x13
#define FLASH_OFFSET_WTOUT		0x1F
#define FLASH_OFFSET_WBTOUT		0x20
#define FLASH_OFFSET_ETOUT		0x21
#define FLASH_OFFSET_CETOUT		0x22
#define FLASH_OFFSET_WMAX_TOUT		0x23
#define FLASH_OFFSET_WBMAX_TOUT		0x24
#define FLASH_OFFSET_EMAX_TOUT		0x25
#define FLASH_OFFSET_CEMAX_TOUT		0x26
#define FLASH_OFFSET_SIZE		0x27
#define FLASH_OFFSET_INTERFACE		0x28
#define FLASH_OFFSET_BUFFER_SIZE	0x2A
#define FLASH_OFFSET_NUM_ERASE_REGIONS	0x2C
#define FLASH_OFFSET_ERASE_REGIONS	0x2D
#define FLASH_OFFSET_PROTECT		0x02
#define FLASH_OFFSET_USER_PROTECTION	0x85
#define FLASH_OFFSET_INTEL_PROTECTION	0x81

#define FLASH_MAN_CFI			0x01000000

#define CFI_CMDSET_NONE		    0
#define CFI_CMDSET_INTEL_EXTENDED   1
#define CFI_CMDSET_AMD_STANDARD	    2
#define CFI_CMDSET_INTEL_STANDARD   3
#define CFI_CMDSET_AMD_EXTENDED	    4
#define CFI_CMDSET_MITSU_STANDARD   256
#define CFI_CMDSET_MITSU_EXTENDED   257
#define CFI_CMDSET_SST		    258

#define ERASE_POLL_LIMIT	0x60000000

#define __swab16(x) \
    ((((x) & 0xFF) << 8) | (((x) >> 8) & 0xFF))

#define __swab32(x)         \
   ((((x) & 0xff) << 24)   |  \
    (((x) & 0xff00) <<  8) |  \
    (((x) >> 8) & 0xff00)  |  \
    (((x) >> 24) & 0xff))

#ifdef CFG_FLASH_CFI_AMD_RESET  /* needed for STM_ID_29W320DB on UC100 */
# undef  FLASH_CMD_RESET
# define FLASH_CMD_RESET                AMD_CMD_RESET   /* use AMD-Reset instead */
#endif

typedef union {
    uint8_t c;
    uint16_t w;
    uint32_t l;
} cfiword_t;

typedef union {
    uint8_t *cp;
    uint16_t *wp;
    uint32_t *lp;
} cfiptr_t;

#define NUM_ERASE_REGIONS 4

typedef struct {
    uint32_t size;              /* total bank size in bytes */
    uint32_t flash_id;          /* combined device & manufacturer code */
    uint32_t start[CFG_MAX_FLASH_SECT]; /* physical sector start addresses */
    uint32_t erase_blk_tout;    /* maximum block erase timeout */
    uint32_t erase_chip_tout;   /* maximum block erase timeout */
    uint32_t write_tout;        /* maximum write timeout */
    uint32_t buffer_write_tout; /* maximum buffer write timeout */
    uint16_t vendor;            /* the primary vendor id */
    uint16_t cmd_reset;         /* Vendor specific reset command */
    uint16_t interface;         /* used for x8/x16 adjustments */
    uint16_t sector_count;      /* number of erase units */
    uint16_t buffer_size;       /* number of bytes in write buffer */
    uint8_t portwidth;          /* the width of the port */
    uint8_t chipwidth;          /* the width of the chip */
    uint8_t protect[CFG_MAX_FLASH_SECT];    /* sector protection status */
} flash_info_t;

/* Drivers */
extern uint32_t flash_init(uint32_t);
extern void flash_reset(uint32_t);
extern int32_t flash_erase(flash_info_t *, int32_t, int32_t);
extern void flash_print_info(flash_info_t *);
extern void flash_read_user_serial(flash_info_t *, void *, int32_t, int32_t);
extern void flash_read_factory_serial(flash_info_t *, void *, int32_t, int32_t);

/* APIs */
extern void flash_perror(int32_t);
extern int32_t flash_sects_erase(int32_t *, int32_t *);
extern int32_t flash_sects_protect(int32_t, int32_t *, int32_t *);
extern int32_t flash_write(uint8_t *, uint32_t, uint32_t);
extern void flash_protect(int32_t, uint32_t, uint32_t, flash_info_t *);
extern int32_t flash_fill_sect_ranges(uint32_t, uint32_t, int32_t *, int32_t *, int32_t *);

#endif
