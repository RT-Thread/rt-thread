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

#ifndef _DRIVER_CHIP_SDMMC_SDIO_H_
#define _DRIVER_CHIP_SDMMC_SDIO_H_

#include "card.h"

#ifdef __cplusplus
extern "C" {
#endif

#undef readl
#undef writel

#ifndef printk
#define printk  rt_kprintf
#endif

#define readl hal_readl
#define writel hal_writel

#ifdef CONFIG_USE_SDIO
/*
 * SDIO function CIS tuple (unknown to the core)
 */
struct sdio_func_tuple {
    struct sdio_func_tuple *next;
    unsigned char code;
    unsigned char size;
    unsigned char data[0];
};

//#define SDIO_DEBUG

#define SDIO_EXCLUSIVE_HOST

/* SDIO commands                         type  argument     response */
#define SD_IO_SEND_OP_COND              5       /* bcr  [23:0] OCR         R4  */
#define SD_IO_RW_DIRECT                 52      /* ac   [31:0] See below   R5  */
#define SD_IO_RW_EXTENDED               53      /* adtc [31:0] See below   R5  */

/*
 * SD_IO_RW_DIRECT argument format:
 *
 *      [31] R/W flag
 *      [30:28] Function number
 *      [27] RAW flag
 *      [25:9] Register address
 *      [7:0] Data
 */

/*
 * SD_IO_RW_EXTENDED argument format:
 *
 *      [31] R/W flag
 *      [30:28] Function number
 *      [27] Block mode
 *      [26] Increment address
 *      [25:9] Register address
 *      [8:0] Byte/block count
 */

#define R4_18V_PRESENT                  (1<<24)
#define R4_MEMORY_PRESENT               (1 << 27)

//#define CONFIG_SDIO_IRQ_SUPPORT

/*
  SDIO status in R5
  Type
    e : error bit
    s : status bit
    r : detected and set for the actual command response
    x : detected and set during command execution. the host must poll
            the card by sending status command in order to read these bits.
  Clear condition
    a : according to the card state
    b : always related to the previous command. Reception of
            a valid command will clear it (with a delay of one command)
    c : clear by read
 */

#define R5_COM_CRC_ERROR                (1 << 15)       /* er, b */
#define R5_ILLEGAL_COMMAND              (1 << 14)       /* er, b */
#define R5_ERROR                        (1 << 11)       /* erx, c */
#define R5_FUNCTION_NUMBER              (1 << 9)        /* er, c */
#define R5_OUT_OF_RANGE                 (1 << 8)        /* er, c */
#define R5_STATUS(x)                    (x & 0xCB00)
#define R5_IO_CURRENT_STATE(x)          ((x & 0x3000) >> 12) /* s, b */

/*
 * Card Common Control Registers (CCCR)
 */

#define SDIO_CCCR_CCCR                  0x00

#define SDIO_CCCR_REV_1_00              0       /* CCCR/FBR Version 1.00 */
#define SDIO_CCCR_REV_1_10              1       /* CCCR/FBR Version 1.10 */
#define SDIO_CCCR_REV_1_20              2       /* CCCR/FBR Version 1.20 */
#define  SDIO_CCCR_REV_3_00             3       /* CCCR/FBR Version 3.00 */

#define SDIO_SDIO_REV_1_00              0       /* SDIO Spec Version 1.00 */
#define SDIO_SDIO_REV_1_10              1       /* SDIO Spec Version 1.10 */
#define SDIO_SDIO_REV_1_20              2       /* SDIO Spec Version 1.20 */
#define SDIO_SDIO_REV_2_00              3       /* SDIO Spec Version 2.00 */
#define SDIO_SDIO_REV_3_00              4       /* SDIO Spec Version 3.00 */

#define SDIO_CCCR_SD                    0x01

#define SDIO_SD_REV_1_01                0       /* SD Physical Spec Version 1.01 */
#define SDIO_SD_REV_1_10                1       /* SD Physical Spec Version 1.10 */
#define SDIO_SD_REV_2_00                2       /* SD Physical Spec Version 2.00 */
#define SDIO_SD_REV_3_00                3       /* SD Physical Spev Version 3.00 */

#define SDIO_CCCR_IOEx                  0x02
#define SDIO_CCCR_IORx                  0x03
#define SDIO_CCCR_IENx                  0x04    /* Function/Master Interrupt Enable */
#define SDIO_CCCR_INTx                  0x05    /* Function Interrupt Pending */
#define SDIO_CCCR_ABORT                 0x06    /* function abort/card reset */
#define SDIO_CCCR_IF                    0x07    /* bus interface controls */

#define SDIO_BUS_WIDTH_1BIT             0x00
#define SDIO_BUS_WIDTH_4BIT             0x02
#define SDIO_BUS_ECSI                   0x20    /* Enable continuous SPI interrupt */
#define SDIO_BUS_SCSI                   0x40    /* Support continuous SPI interrupt */

#define SDIO_BUS_ASYNC_INT              0x20

#define SDIO_BUS_CD_DISABLE             0x80    /* disable pull-up on DAT3 (pin 1) */

#define SDIO_CCCR_CAPS                  0x08

#define SDIO_CCCR_CAP_SDC               0x01    /* can do CMD52 while data transfer */
#define SDIO_CCCR_CAP_SMB               0x02    /* can do multi-block xfers (CMD53) */
#define SDIO_CCCR_CAP_SRW               0x04    /* supports read-wait protocol */
#define SDIO_CCCR_CAP_SBS               0x08    /* supports suspend/resume */
#define SDIO_CCCR_CAP_S4MI              0x10    /* interrupt during 4-bit CMD53 */
#define SDIO_CCCR_CAP_E4MI              0x20    /* enable ints during 4-bit CMD53 */
#define SDIO_CCCR_CAP_LSC               0x40    /* low speed card */
#define SDIO_CCCR_CAP_4BLS              0x80    /* 4 bit low speed card */

#define SDIO_CCCR_CIS                   0x09    /* common CIS pointer (3 bytes) */

/* Following 4 regs are valid only if SBS is set */
#define SDIO_CCCR_SUSPEND               0x0c
#define SDIO_CCCR_SELx                  0x0d
#define SDIO_CCCR_EXECx                 0x0e
#define SDIO_CCCR_READYx                0x0f

#define SDIO_CCCR_BLKSIZE               0x10

#define SDIO_CCCR_POWER                 0x12

#define SDIO_POWER_SMPC                 0x01    /* Supports Master Power Control */
#define SDIO_POWER_EMPC                 0x02    /* Enable Master Power Control */

#define SDIO_CCCR_SPEED                 0x13

#define SDIO_SPEED_SHS                  0x01    /* Supports High-Speed mode */
#define SDIO_SPEED_BSS_SHIFT            1
#define SDIO_SPEED_BSS_MASK             (7<<SDIO_SPEED_BSS_SHIFT)
#define SDIO_SPEED_SDR12                (0<<SDIO_SPEED_BSS_SHIFT)
#define SDIO_SPEED_SDR25                (1<<SDIO_SPEED_BSS_SHIFT)
#define SDIO_SPEED_SDR50                (2<<SDIO_SPEED_BSS_SHIFT)
#define SDIO_SPEED_SDR104               (3<<SDIO_SPEED_BSS_SHIFT)
#define SDIO_SPEED_DDR50                (4<<SDIO_SPEED_BSS_SHIFT)
#define SDIO_SPEED_EHS                  SDIO_SPEED_SDR25    /* Enable High-Speed */

#define SDIO_CCCR_UHS                   0x14
#define SDIO_UHS_SDR50                  0x01
#define SDIO_UHS_SDR104                 0x02
#define SDIO_UHS_DDR50                  0x04

#define SDIO_CCCR_DRIVE_STRENGTH        0x15
#define SDIO_SDTx_MASK                  0x07
#define SDIO_DRIVE_SDTA                 (1<<0)
#define SDIO_DRIVE_SDTC                 (1<<1)
#define SDIO_DRIVE_SDTD                 (1<<2)
#define SDIO_DRIVE_DTSx_MASK            0x03
#define SDIO_DRIVE_DTSx_SHIFT           4
#define SDIO_DTSx_SET_TYPE_B            (0 << SDIO_DRIVE_DTSx_SHIFT)
#define SDIO_DTSx_SET_TYPE_A            (1 << SDIO_DRIVE_DTSx_SHIFT)
#define SDIO_DTSx_SET_TYPE_C            (2 << SDIO_DRIVE_DTSx_SHIFT)
#define SDIO_DTSx_SET_TYPE_D            (3 << SDIO_DRIVE_DTSx_SHIFT)

/*
 * Function Basic Registers (FBR)
 */
#define SDIO_FBR_BASE(f)                ((f) * 0x100) /* base of function f's FBRs */

#define SDIO_FBR_STD_IF                 0x00

#define SDIO_FBR_SUPPORTS_CSA           0x40    /* supports Code Storage Area */
#define SDIO_FBR_ENABLE_CSA             0x80    /* enable Code Storage Area */

#define SDIO_FBR_STD_IF_EXT             0x01
#define SDIO_FBR_POWER                  0x02
#define SDIO_FBR_POWER_SPS              0x01    /* Supports Power Selection */
#define SDIO_FBR_POWER_EPS              0x02    /* Enable (low) Power Selection */
#define SDIO_FBR_CIS                    0x09    /* CIS pointer (3 bytes) */
#define SDIO_FBR_CSA                    0x0C    /* CSA pointer (3 bytes) */
#define SDIO_FBR_CSA_DATA               0x0F
#define SDIO_FBR_BLKSIZE                0x10    /* block size (2 bytes) */

/* Misc. helper definitions */
#define FN(x)                           (x)
#define FN0                             FN(0)
#define FN1                             FN(1)
#define FN2                             FN(2)
#define FN3                             FN(3)
#define FN4                             FN(4)
#define FN5                             FN(5)
#define FN6                             FN(6)
#define FN7                             FN(7)

struct mmc_card;

typedef struct mmc_card sdio_t;

/**
 *  sdio_readb - read a single byte from a SDIO function
 *  @card: SDIO to access
 *  @addr: address to read
 *  @err_ret: optional status value from transfer
 *
 *  Reads a single byte from the address space of a given SDIO
 *  function. If there is a problem reading the address, 0xff
 *  is returned and @err_ret will contain the error code.
 */
extern uint8_t
sdio_readb(struct mmc_card *card, uint32_t func_num, uint32_t addr,
           int32_t *err_ret);

/**
 *  sdio_writeb - write a single byte to a SDIO function
 *  @card: SDIO to access
 *  @b: byte to write
 *  @addr: address to write to
 *  @err_ret: optional status value from transfer
 *
 *  Writes a single byte to the address space of a given SDIO
 *  function. @err_ret will contain the status of the actual
 *  transfer.
 */
extern void
sdio_writeb(struct mmc_card *card, uint32_t func_num, const uint8_t b,
            uint32_t addr, int32_t  *err_ret);

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
extern uint16_t sdio_readw(struct sdio_func *func, unsigned int addr, int *err_ret);
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
extern void sdio_writew(struct sdio_func *func, uint16_t b, unsigned int addr, int *err_ret);
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
extern uint32_t sdio_readl(struct sdio_func *func, unsigned int addr, int *err_ret);
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
extern void sdio_writel(struct sdio_func *func, uint32_t b, unsigned int addr, int *err_ret);

/**
 *  memcpy_fromio - read a chunk of memory from a SDIO function
 *  @dst: buffer to store the data
 *  @addr: address to begin reading from
 *  @count: number of bytes to read
 *
 *  Reads from the address space of a given SDIO function. Return
 *  value indicates if the transfer succeeded or not.
 */
extern int
sdio_memcpy_fromio(struct mmc_card *card, unsigned int func_num, void *dst,
                   unsigned int addr, int count);

/**
 *  memcpy_toio - write a chunk of memory to a SDIO function
 *  @addr: address to start writing to
 *  @src: buffer that contains the data to write
 *  @count: number of bytes to write
 *
 *  Writes to the address space of a given SDIO function. Return
 *  value indicates if the transfer succeeded or not.
 */
extern int
sdio_memcpy_toio(struct mmc_card *card, unsigned int func_num, unsigned int addr,
                 const void *src, int count);

/**
 *    sdio_claim_irq - claim the IRQ for a SDIO function
 *    @card: SDIO card
 *    @func_num: function num
 *    @handler: IRQ handler callback
 *
 *    Claim and activate the IRQ for the given SDIO function. The provided
 *    handler will be called when that IRQ is asserted.  The host is always
 *    claimed already when the handler is called so the handler must not
 *    call sdio_claim_host() nor sdio_release_host().
 */
//extern int sdio_claim_irq(struct mmc_card *card, unsigned int func_num,
//                          sdio_irq_handler_t *handler);
extern int sdio_claim_irq(struct sdio_func *func, sdio_irq_handler_t *handler);

/**
 *    sdio_release_irq - release the IRQ for a SDIO function
 *    @card: SDIO card
 *    @func_num: function num
 *
 *    Disable and release the IRQ for the given SDIO function.
 */
//extern int sdio_release_irq(struct mmc_card *card, unsigned int func_num);
extern int sdio_release_irq(struct sdio_func *func);

/**
 *  sdio_align_size - pads a transfer size to a more optimal value
 *  @func: SDIO function
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
//unsigned int sdio_align_size(struct mmc_card *card, unsigned int sz);
unsigned int sdio_align_size(struct sdio_func *func, unsigned int sz);

/**
 *  claim_host - exclusively claim a bus for a certain SDIO function
 *  @func: SDIO function that will be accessed
 *
 *  Claim a bus for a set of operations. The SDIO function given
 *  is used to figure out which bus is relevant.
 */
#ifdef SDIO_EXCLUSIVE_HOST
extern void sdio_claim_host(struct mmc_card *card);
#else
static inline void sdio_claim_host(struct mmc_card *card) {
#ifdef SDIO_DEBUG
    if (card->_bus_refs)
        BUG_ON(1); /* check when need debug */
    card->_bus_refs++;
#endif
}
#endif

/**
 *  release_host - release a bus for a certain SDIO function
 *  @func: SDIO function that was accessed
 *
 *  Release a bus, allowing others to claim the bus for their
 *  operations.
 */
#ifdef SDIO_EXCLUSIVE_HOST
extern void sdio_release_host(struct mmc_card *card);
#else
static inline void sdio_release_host(struct mmc_card *card) {
#ifdef SDIO_DEBUG
    card->_bus_refs--;
    if (card->_bus_refs)
        BUG_ON(1); /* check when need debug */
#endif
}
#endif

static inline void sdio_lock(struct mmc_card *card) {
    sdio_claim_host(card);
}

static inline void sdio_unlock(struct mmc_card *card) {
    sdio_release_host(card);
}

extern int32_t sdio_set_block_size(struct mmc_card *card, uint32_t fn_num,
                               uint32_t blksz);
extern int32_t sdio_enable_func(struct mmc_card *card, uint32_t func_num);
extern int32_t sdio_disable_func(struct mmc_card *card, uint32_t func_num);
extern int32_t sdio_pm(sdio_t *card, int32_t suspend);

extern void sdio_test(void);
extern int mmc_io_rw_direct(struct mmc_card *card, int32_t write, uint32_t fn, uint32_t addr, uint8_t in, uint8_t *out);

extern struct sdio_func ** get_mmc_card_func(uint8_t card_id);

#endif /* CONFIG_USE_SDIO */

#ifdef __cplusplus
}
#endif

#endif /* _DRIVER_CHIP_SDMMC_SDIO_H_ */
