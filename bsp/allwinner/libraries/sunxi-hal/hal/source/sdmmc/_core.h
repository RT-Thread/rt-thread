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

#ifndef _ROM_DRIVER_CHIP_SDMMC__CORE_H_
#define _ROM_DRIVER_CHIP_SDMMC__CORE_H_

//#include "rom_debug.h"
#include "rom_debug.h"

#include "card.h"

#ifdef CONFIG_USE_SDIO
#include "sdio.h"
#endif
#include "sdmmc.h"

#include "_sdhost.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mmc_data {
    uint32_t blksz;     /* data block size */
    uint32_t blocks;    /* number of blocks */
    uint32_t flags;

#define MMC_DATA_WRITE          (1 << 8)
#define MMC_DATA_READ           (1 << 9)
#define MMC_DATA_STREAM         (1 << 10)

    uint32_t                bytes_xfered;
    uint32_t                sg_len;         /* size of scatter list */
    struct scatterlist      *sg;            /* I/O scatter list */
};

struct mmc_command {
    uint32_t opcode;
    uint32_t arg;
    uint32_t resp[4];
    uint32_t flags;                         /* expected response type */
    /* data transfer */
    volatile uint32_t stop        :1,
                      boot        :1,
                      vol_switch  :1;

#define MMC_RSP_MASK            (0x1f << 0)
#define MMC_RSP_PRESENT         (1 << 0)
#define MMC_RSP_136             (1 << 1)        /* 136 bit response */
#define MMC_RSP_CRC             (1 << 2)        /* expect valid crc */
#define MMC_RSP_BUSY            (1 << 3)        /* card may send busy */
#define MMC_RSP_OPCODE          (1 << 4)        /* response contains opcode */

#define MMC_CMD_MASK            (3 << 5)        /* non-SPI command type */
#define MMC_CMD_AC              (0 << 5)        /* addressed comamnd without data transfer */
#define MMC_CMD_ADTC            (1 << 5)        /* addressed command with data transfer */
#define MMC_CMD_BC              (2 << 5)        /* broadcast command without response */
#define MMC_CMD_BCR             (3 << 5)        /* broadcast command with response */

#define MMC_RSP_SPI_S1          (1 << 7)        /* one status byte */
#define MMC_RSP_SPI_S2          (1 << 8)        /* second byte */
#define MMC_RSP_SPI_B4          (1 << 9)        /* four data bytes */
#define MMC_RSP_SPI_BUSY        (1 << 10)       /* card may send busy */

/* These are the native response types, and correspond to valid bit
 * patterns of the above flags.  One additional valid pattern
 * is all zeros, which means we don't expect a response.
 */
#define MMC_RSP_NONE            (0)
#define MMC_RSP_R1              (MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R1B             (MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE|MMC_RSP_BUSY)
#define MMC_RSP_R2              (MMC_RSP_PRESENT|MMC_RSP_136|MMC_RSP_CRC)
#define MMC_RSP_R3              (MMC_RSP_PRESENT)
#define MMC_RSP_R4              (MMC_RSP_PRESENT)
#define MMC_RSP_R5              (MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R6              (MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R7              (MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)

#define mmc_resp_type(cmd)      ((cmd)->flags & MMC_RSP_MASK)

/*
 * These are the SPI response types for MMC, SD, and SDIO cards.
 * Commands return R1, with maybe more info.  Zero is an error type;
 * callers must always provide the appropriate MMC_RSP_SPI_Rx flags.
 */
#define MMC_RSP_SPI_R1          (MMC_RSP_SPI_S1)
#define MMC_RSP_SPI_R1B         (MMC_RSP_SPI_S1|MMC_RSP_SPI_BUSY)
#define MMC_RSP_SPI_R2          (MMC_RSP_SPI_S1|MMC_RSP_SPI_S2)
#define MMC_RSP_SPI_R3          (MMC_RSP_SPI_S1|MMC_RSP_SPI_B4)
#define MMC_RSP_SPI_R4          (MMC_RSP_SPI_S1|MMC_RSP_SPI_B4)
#define MMC_RSP_SPI_R5          (MMC_RSP_SPI_S1|MMC_RSP_SPI_S2)
#define MMC_RSP_SPI_R7          (MMC_RSP_SPI_S1|MMC_RSP_SPI_B4)

/* These are the command types. */
#define mmc_cmd_type(cmd)       ((cmd)->flags & MMC_CMD_MASK)

#if ((defined CONFIG_USE_SD) || (defined CONFIG_USE_MMC))
    uint32_t retries;               /* max number of retries */

    /* Standard errno values are used for errors, but some have specific
     * meaning in the MMC layer:
     *
     * ETIMEDOUT    Card took too long to respond
     * EILSEQ       Basic format problem with the received or sent data
     *              (e.g. CRC check failed, incorrect opcode in response
     *              or bad end bit)
     * EINVAL       Request cannot be performed because of restrictions
     *              in hardware and/or the driver
     * ENOMEDIUM    Host can determine that the slot is empty and is
     *              actively failing requests
     */
    uint32_t erase_timeout;         /* in milliseconds */
#endif

    struct mmc_data         *data;          /* data segment associated with cmd */
};

struct mmc_request {
    //struct mmc_command    *sbc;           /* SET_BLOCK_COUNT for multiblock */
    struct mmc_command      *cmd;
    struct mmc_data         *data;
    //struct mmc_command    *stop;

    //struct completion     completion;
    //void                  (*done)(struct mmc_request *); /* completion function */
};

#define UNSTUFF_BITS(resp,start,size)                                   \
    ({                                                              \
        const int32_t __size = size;                            \
        const uint32_t __mask = (__size < 32 ? 1 << __size : 0) - 1;    \
        const int32_t __off = 3 - ((start) / 32);                       \
        const int32_t __shft = (start) & 31;                    \
        uint32_t __res;                                         \
                                                                \
        __res = resp[__off] >> __shft;                          \
        if (__size + __shft > 32)                               \
            __res |= resp[__off-1] << ((32 - __shft) % 32); \
        __res & __mask;                                         \
    })

#ifdef CONFIG_USE_MMC_QUIRK

#define SDIO_ANY_ID (~0)

/*
 *  The world is not perfect and supplies us with broken mmc/sdio devices.
 *  For at least some of these bugs we need a work-around.
 */

struct mmc_fixup {
    /* CID-specific fields. */
    const char *name;

    /* Valid revision range */
    uint64_t rev_start, rev_end;

    int32_t manfid;
    int16_t oemid;

    /* SDIO-specfic fields. You can use SDIO_ANY_ID here of course */
    uint16_t cis_vendor, cis_device;

    void (*vendor_fixup)(struct mmc_card *card, int32_t data);
    int32_t data;
};

#define CID_MANFID_ANY (-1u)
#define CID_OEMID_ANY ((unsigned short) -1)
#define CID_NAME_ANY (NULL)

#define END_FIXUP { 0 }

#define _FIXUP_EXT(_name, _manfid, _oemid, _rev_start, _rev_end,    \
           _cis_vendor, _cis_device,                \
           _fixup, _data)                   \
    {                          \
        .name = (_name),               \
        .manfid = (_manfid),               \
        .oemid = (_oemid),             \
        .rev_start = (_rev_start),         \
        .rev_end = (_rev_end),             \
        .cis_vendor = (_cis_vendor),           \
        .cis_device = (_cis_device),           \
        .vendor_fixup = (_fixup),          \
        .data = (_data),               \
     }

#define SDIO_FIXUP(_vendor, _device, _fixup, _data) \
    _FIXUP_EXT(CID_NAME_ANY, CID_MANFID_ANY,    \
            CID_OEMID_ANY, 0, -1ull,        \
           _vendor, _device,            \
           _fixup, _data)           \

#define cid_rev(hwrev, fwrev, year, month)  \
    (((uint64_t) hwrev) << 40 |          \
     ((uint64_t) fwrev) << 32 |          \
     ((uint64_t) year) << 16 |           \
     ((uint64_t) month))

#define cid_rev_card(card)        \
    cid_rev(card->cid.hwrev,      \
            card->cid.fwrev,      \
            card->cid.year,   \
            card->cid.month)

/*
 * This hook just adds a quirk for all sdio devices
 */
static void add_quirk_for_sdio_devices(struct mmc_card *card, int32_t data)
{
    if (mmc_card_sdio(card))
        card->quirks |= data;
}

static inline void add_quirk(struct mmc_card *card, int32_t data)
{
    card->quirks |= data;
}

static inline void remove_quirk(struct mmc_card *card, int32_t data)
{
    card->quirks &= ~data;
}

/*
 * Quirk add/remove for MMC products.
 */

static inline void add_quirk_mmc(struct mmc_card *card, int data)
{
    if (mmc_card_mmc(card))
        card->quirks |= data;
}

static inline void remove_quirk_mmc(struct mmc_card *card,
                           int data)
{
    if (mmc_card_mmc(card))
        card->quirks &= ~data;
}

/*
 * Quirk add/remove for SD products.
 */

static inline void add_quirk_sd(struct mmc_card *card, int data)
{
    if (mmc_card_sd(card))
        card->quirks |= data;
}

static inline void remove_quirk_sd(struct mmc_card *card,
                           int data)
{
    if (mmc_card_sd(card))
        card->quirks &= ~data;
}

static inline int mmc_card_lenient_fn0(const struct mmc_card *c)
{
    return c->quirks & MMC_QUIRK_LENIENT_FN0;
}

static inline int mmc_blksz_for_byte_mode(const struct mmc_card *c)
{
    return c->quirks & MMC_QUIRK_BLKSZ_FOR_BYTE_MODE;
}

/*
static inline int mmc_card_disable_cd(const struct mmc_card *c)
{
    return c->quirks & MMC_QUIRK_DISABLE_CD;
}
*/

static inline int mmc_card_nonstd_func_interface(const struct mmc_card *c)
{
    return c->quirks & MMC_QUIRK_NONSTD_FUNC_IF;
}

static inline int mmc_card_broken_byte_mode_512(const struct mmc_card *c)
{
    return c->quirks & MMC_QUIRK_BROKEN_BYTE_MODE_512;
}

static inline int mmc_card_long_read_time(const struct mmc_card *c)
{
    return c->quirks & MMC_QUIRK_LONG_READ_TIME;
}

#endif

void mmc_attach_bus(struct mmc_host *host, const struct mmc_bus_ops *ops);
void mmc_detach_bus(struct mmc_host *host);

extern int32_t mmc_align_data_size(struct mmc_card *card, uint32_t sz);
extern int32_t mmc_send_status(struct mmc_card *card, uint32_t *status);
extern int32_t mmc_sd_switch(struct mmc_card *card, uint8_t mode, uint8_t group,
                             uint16_t value, uint8_t *resp);
extern void mmc_enumerate_card_info(struct mmc_card *card);
extern int32_t mmc_switch_to_high_speed(struct mmc_card *card);
extern int32_t __sdmmc_block_rw(struct mmc_card *card, uint32_t blk_num, uint32_t blk_cnt,
                                uint32_t sg_len, struct scatterlist *sg, int write);
extern int32_t mmc_sd_switch_hs(struct mmc_card *card);
extern int32_t mmc_app_set_bus_width(struct mmc_card *card, uint32_t width);
extern int32_t mmc_wait_for_cmd(struct mmc_host *host, struct mmc_command *cmd);
extern int32_t mmc_wait_for_req(struct mmc_host *host, struct mmc_request *mrq);
//#ifndef __CONFIG_ROM
extern int32_t mmc_attach_sd(struct mmc_card *card, struct mmc_host *host);
extern void mmc_deattach_sd(struct mmc_card *card, struct mmc_host *host);
//#endif
extern int32_t mmc_select_card(struct mmc_card *card, uint32_t select);
extern int32_t mmc_all_send_cid(struct mmc_host *host, uint32_t *cid);
extern int32_t mmc_send_relative_addr(struct mmc_host *host, uint32_t *rca);
extern void mmc_add_card(struct mmc_card *card);
#ifdef CONFIG_USE_MMC_QUIRK
extern void mmc_fixup_device(struct mmc_card *card, const struct mmc_fixup *table);
#endif

static inline int mmc_card_disable_cd(const struct mmc_card *c)
{
#ifdef CONFIG_USE_MMC_QUIRK
    return c->quirks & MMC_QUIRK_DISABLE_CD;
#else
    return 0;
#endif
}

/**
 * @brief Exclusively claim a host.
 * @note Claim a host for a set of operations.
 * @param host:
 *        @host->mmc host to claim.
 * @retval  None.
 */
static inline void mmc_claim_host(struct mmc_host *host)
{
    HAL_SDC_Claim_Host(host);
}

/**
 * @brief Release a host.
 * @note Release a MMC host, allowing others to claim the host for their operations.
 * @param host:
 *        @host->mmc host to release.
 * @retval  None.
 */
static inline void mmc_release_host(struct mmc_host *host)
{
    HAL_SDC_Release_Host(host);
}

#ifdef __cplusplus
}
#endif

#endif /* _ROM_DRIVER_CHIP_SDMMC__CORE_H_ */
