/*
 * @brief LPC18xx/43xx SD/SDIO driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __SDMMC_18XX_43XX_H_
#define __SDMMC_18XX_43XX_H_

#include "chip.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup SDMMC_18XX_43XX CHIP: LPC18xx/43xx SD/SDIO driver
 * @ingroup CHIP_18XX_43XX_Drivers
 * @{
 */

/* SD/MMC commands - this matrix shows the command, response types, and
   supported card type for that command.
   Command                 Number Resp  SD  MMC
   ----------------------- ------ ----- --- ---
   Reset (go idle)         CMD0   NA    x   x
   Send op condition       CMD1   R3        x
   All send CID            CMD2   R2    x   x
   Send relative address   CMD3   R1        x
   Send relative address   CMD3   R6    x
   Program DSR             CMD4   NA        x
   Select/deselect card    CMD7   R1b       x
   Select/deselect card    CMD7   R1    x
   Send CSD                CMD9   R2    x   x
   Send CID                CMD10  R2    x   x
   Read data until stop    CMD11  R1    x   x
   Stop transmission       CMD12  R1/b  x   x
   Send status             CMD13  R1    x   x
   Go inactive state       CMD15  NA    x   x
   Set block length        CMD16  R1    x   x
   Read single block       CMD17  R1    x   x
   Read multiple blocks    CMD18  R1    x   x
   Write data until stop   CMD20  R1        x
   Setblock count          CMD23  R1        x
   Write single block      CMD24  R1    x   x
   Write multiple blocks   CMD25  R1    x   x
   Program CID             CMD26  R1        x
   Program CSD             CMD27  R1    x   x
   Set write protection    CMD28  R1b   x   x
   Clear write protection  CMD29  R1b   x   x
   Send write protection   CMD30  R1    x   x
   Erase block start       CMD32  R1    x
   Erase block end         CMD33  R1    x
   Erase block start       CMD35  R1        x
   Erase block end         CMD36  R1        x
   Erase blocks            CMD38  R1b       x
   Fast IO                 CMD39  R4        x
   Go IRQ state            CMD40  R5        x
   Lock/unlock             CMD42  R1b       x
   Application command     CMD55  R1        x
   General command         CMD56  R1b       x

 *** SD card application commands - these must be preceded with ***
 *** MMC CMD55 application specific command first               ***
   Set bus width           ACMD6  R1    x
   Send SD status          ACMD13 R1    x
   Send number WR blocks   ACMD22 R1    x
   Set WR block erase cnt  ACMD23 R1    x
   Send op condition       ACMD41 R3    x
   Set clear card detect   ACMD42 R1    x
   Send CSR                ACMD51 R1    x */

/** @brief  SD/MMC command enumeration value.
 */
typedef enum {
	SDMMC_IDLE,				/*!<  Put card in idle mode */
	MMC_SENDOP_COND,		/*!<  Send operating condition */
	SDMMC_ALL_SEND_CID,		/*!<  All cards send CID */
	SDMMC_SRA,				/*!<  Set relative address */
	MMC_PROGRAM_DSR,		/*!<  Program DSR */
	SDMMC_SELECT_CARD,		/*!< Select card */
	SDMMC_SEND_CSD,			/*!< Send CSD data */
	SDMMC_SEND_CID,			/*!< Send CID register data (with rel. addr) */
	SDMMC_READ_UNTIL_STOP,	/*!< Read data until stop */
	SDMMC_STOP_XFER,		/*!< Stop current transmission */
	SDMMC_SSTAT,			/*!< Send status */
	SDMMC_INACTIVE,			/*!< Put card in inactive state */
	SDMMC_SET_BLEN,			/*!< Set block transfer length */
	SDMMC_READ_SINGLE,		/*!< Read single block */
	SDMMC_READ_MULTIPLE,	/*!< Read multiple blocks */
	SDMMC_WRITE_UNTIL_STOP,	/*!< Write data until stop */
	SDMMC_SET_BLOCK_COUNT,	/*!< Set block count */
	SDMMC_WRITE_SINGLE,		/*!< Write single block */
	SDMMC_WRITE_MULTIPLE,	/*!< Write multiple blocks */
	MMC_PROGRAM_CID,		/*!< Program CID */
	SDMMC_PROGRAM_CSD,		/*!< Program CSD */
	SDMMC_SET_WR_PROT,		/*!< Set write protection */
	SDMMC_CLEAR_WR_PROT,	/*!< Clear write protection */
	SDMMC_SEND_WR_PROT,		/*!< Send write protection */
	SD_ERASE_BLOCK_START,	/*!< Set starting erase block */
	SD_ERASE_BLOCK_END,		/*!< Set ending erase block */
	MMC_ERASE_BLOCK_START,	/*!< Set starting erase block */
	MMC_ERASE_BLOCK_END,	/*!< Set ending erase block */
	MMC_ERASE_BLOCKS,		/*!< Erase blocks */
	MMC_FAST_IO,			/*!< Fast IO */
	MMC_GO_IRQ_STATE,		/*!< Go into IRQ state */
	MMC_LOCK_UNLOCK,		/*!< Lock/unlock */
	SDMMC_APP_CMD,			/*!< Application specific command */
	SDMMC_GEN_CMD,			/*!< General purpose command */
	SDMMC_INVALID_CMD		/*!< Invalid SDMMC command */
} SDMMC_COMMAND_T;

/** @brief  SDMMC application specific commands for SD cards only - these
   must be preceded by the SDMMC CMD55 to work correctly.
 */
typedef enum {
	SD_SET_BUS_WIDTH,		/*!< Set the SD bus width */
	SD_SEND_STATUS,			/*!< Send the SD card status */
	SD_SEND_WR_BLOCKS,		/*!< Send the number of written clocks */
	SD_SET_ERASE_COUNT,		/*!< Set the number of blocks to pre-erase */
	SD_SENDOP_COND,			/*!< Send the OCR register (init) */
	SD_CLEAR_CARD_DET,		/*!< Set or clear the 50K detect pullup */
	SD_SEND_SCR,			/*!< Send the SD configuration register */
	SD_INVALID_APP_CMD		/*!< Invalid SD application command */
} SD_APP_CMD_T;

/** @brief  Possible SDMMC response types
 */
typedef enum {
	SDMMC_RESPONSE_R1,		/*!< Typical status */
	SDMMC_RESPONSE_R1B,		/*!< Typical status with busy */
	SDMMC_RESPONSE_R2,		/*!< CID/CSD registers (CMD2 and CMD10) */
	SDMMC_RESPONSE_R3,		/*!< OCR register (CMD1, ACMD41) */
	SDMMC_RESPONSE_R4,		/*!< Fast IO response word */
	SDMMC_RESPONSE_R5,		/*!< Go IRQ state response word */
	SDMMC_RESPONSE_R6,		/*!< Published RCA response */
	SDMMC_RESPONSE_NONE		/*!< No response expected */
} SDMMC_RESPONSE_T;

/** @brief  Possible SDMMC card state types
 */
typedef enum {
	SDMMC_IDLE_ST = 0,	/*!< Idle state */
	SDMMC_READY_ST,		/*!< Ready state */
	SDMMC_IDENT_ST,		/*!< Identification State */
	SDMMC_STBY_ST,		/*!< standby state */
	SDMMC_TRAN_ST,		/*!< transfer state */
	SDMMC_DATA_ST,		/*!< Sending-data State */
	SDMMC_RCV_ST,		/*!< Receive-data State */
	SDMMC_PRG_ST,		/*!< Programming State */
	SDMMC_DIS_ST		/*!< Disconnect State */
} SDMMC_STATE_T;

/* Standard MMC commands (3.1)           type  argument     response */
/* class 1 */
#define MMC_GO_IDLE_STATE         0		/* bc                          */
#define MMC_SEND_OP_COND          1		/* bcr  [31:0]  OCR        R3  */
#define MMC_ALL_SEND_CID          2		/* bcr                     R2  */
#define MMC_SET_RELATIVE_ADDR     3		/* ac   [31:16] RCA        R1  */
#define MMC_SET_DSR               4		/* bc   [31:16] RCA            */
#define MMC_SELECT_CARD           7		/* ac   [31:16] RCA        R1  */
#define MMC_SEND_EXT_CSD          8		/* bc                      R1  */
#define MMC_SEND_CSD              9		/* ac   [31:16] RCA        R2  */
#define MMC_SEND_CID             10		/* ac   [31:16] RCA        R2  */
#define MMC_STOP_TRANSMISSION    12		/* ac                      R1b */
#define MMC_SEND_STATUS          13		/* ac   [31:16] RCA        R1  */
#define MMC_GO_INACTIVE_STATE    15		/* ac   [31:16] RCA            */

/* class 2 */
#define MMC_SET_BLOCKLEN         16		/* ac   [31:0]  block len  R1  */
#define MMC_READ_SINGLE_BLOCK    17		/* adtc [31:0]  data addr  R1  */
#define MMC_READ_MULTIPLE_BLOCK  18		/* adtc [31:0]  data addr  R1  */

/* class 3 */
#define MMC_WRITE_DAT_UNTIL_STOP 20		/* adtc [31:0]  data addr  R1  */

/* class 4 */
#define MMC_SET_BLOCK_COUNT      23		/* adtc [31:0]  data addr  R1  */
#define MMC_WRITE_BLOCK          24		/* adtc [31:0]  data addr  R1  */
#define MMC_WRITE_MULTIPLE_BLOCK 25		/* adtc                    R1  */
#define MMC_PROGRAM_CID          26		/* adtc                    R1  */
#define MMC_PROGRAM_CSD          27		/* adtc                    R1  */

/* class 6 */
#define MMC_SET_WRITE_PROT       28		/* ac   [31:0]  data addr  R1b */
#define MMC_CLR_WRITE_PROT       29		/* ac   [31:0]  data addr  R1b */
#define MMC_SEND_WRITE_PROT      30		/* adtc [31:0]  wpdata addr R1  */

/* class 5 */
#define MMC_ERASE_GROUP_START    35		/* ac   [31:0]  data addr  R1  */
#define MMC_ERASE_GROUP_END      36		/* ac   [31:0]  data addr  R1  */
#define MMC_ERASE                37		/* ac                      R1b */

/* class 9 */
#define MMC_FAST_IO              39		/* ac   <Complex>          R4  */
#define MMC_GO_IRQ_STATE         40		/* bcr                     R5  */

/* class 7 */
#define MMC_LOCK_UNLOCK          42		/* adtc                    R1b */

/* class 8 */
#define MMC_APP_CMD              55		/* ac   [31:16] RCA        R1  */
#define MMC_GEN_CMD              56		/* adtc [0]     RD/WR      R1b */

/* SD commands                           type  argument     response */
/* class 8 */
/* This is basically the same command as for MMC with some quirks. */
#define SD_SEND_RELATIVE_ADDR     3		/* ac                      R6  */
#define SD_CMD8                   8		/* bcr  [31:0]  OCR        R3  */

/* Application commands */
#define SD_APP_SET_BUS_WIDTH      6		/* ac   [1:0]   bus width  R1   */
#define SD_APP_OP_COND           41		/* bcr  [31:0]  OCR        R1 (R4)  */
#define SD_APP_SEND_SCR          51		/* adtc                    R1   */

/*
   MMC status in R1
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

#define R1_OUT_OF_RANGE         (1UL << 31)		/* er, c */
#define R1_ADDRESS_ERROR        (1 << 30)	/* erx, c */
#define R1_BLOCK_LEN_ERROR      (1 << 29)	/* er, c */
#define R1_ERASE_SEQ_ERROR      (1 << 28)	/* er, c */
#define R1_ERASE_PARAM          (1 << 27)	/* ex, c */
#define R1_WP_VIOLATION         (1 << 26)	/* erx, c */
#define R1_CARD_IS_LOCKED       (1 << 25)	/* sx, a */
#define R1_LOCK_UNLOCK_FAILED   (1 << 24)	/* erx, c */
#define R1_COM_CRC_ERROR        (1 << 23)	/* er, b */
#define R1_ILLEGAL_COMMAND      (1 << 22)	/* er, b */
#define R1_CARD_ECC_FAILED      (1 << 21)	/* ex, c */
#define R1_CC_ERROR             (1 << 20)	/* erx, c */
#define R1_ERROR                (1 << 19)	/* erx, c */
#define R1_UNDERRUN             (1 << 18)	/* ex, c */
#define R1_OVERRUN              (1 << 17)	/* ex, c */
#define R1_CID_CSD_OVERWRITE    (1 << 16)	/* erx, c, CID/CSD overwrite */
#define R1_WP_ERASE_SKIP        (1 << 15)	/* sx, c */
#define R1_CARD_ECC_DISABLED    (1 << 14)	/* sx, a */
#define R1_ERASE_RESET          (1 << 13)	/* sr, c */
#define R1_STATUS(x)            (x & 0xFFFFE000)
#define R1_CURRENT_STATE(x)     ((x & 0x00001E00) >> 9)	/* sx, b (4 bits) */
#define R1_READY_FOR_DATA       (1 << 8)/* sx, a */
#define R1_APP_CMD              (1 << 5)/* sr, c */

#define OCR_ALL_READY           (1UL << 31)		/* Card Power up status bit */
#define OCR_HC_CCS              (1 << 30)	/* High capacity card */
#define OCR_VOLTAGE_RANGE_MSK   0x00ff8000

#define SD_SEND_IF_ARG          0x000001AA
#define SD_SEND_IF_ECHO_MSK     0x000000FF
#define SD_SEND_IF_RESP         0x000000AA

#define CMD_MASK_RESP       (0x3UL << 28)
#define CMD_RESP(r)         (((r) & 0x3) << 28)
#define CMD_RESP_R0         (0 << 28)
#define CMD_RESP_R1         (1 << 28)
#define CMD_RESP_R2         (2 << 28)
#define CMD_RESP_R3         (3 << 28)
#define CMD_BIT_AUTO_STOP   (1 << 24)
#define CMD_BIT_APP         (1 << 23)
#define CMD_BIT_INIT        (1 << 22)
#define CMD_BIT_BUSY        (1 << 21)
#define CMD_BIT_LS          (1 << 20)	/* Low speed, used during acquire */
#define CMD_BIT_DATA        (1 << 19)
#define CMD_BIT_WRITE       (1 << 18)
#define CMD_BIT_STREAM      (1 << 17)
#define CMD_MASK_CMD        (0xff)
#define CMD_SHIFT_CMD       (0)

#define CMD(c, r)        ( ((c) &  CMD_MASK_CMD) | CMD_RESP((r)) )

#define CMD_IDLE            CMD(MMC_GO_IDLE_STATE, 0) | CMD_BIT_LS    | CMD_BIT_INIT
#define CMD_SD_OP_COND      CMD(SD_APP_OP_COND, 1)      | CMD_BIT_LS | CMD_BIT_APP
#define CMD_SD_SEND_IF_COND CMD(SD_CMD8, 1)      | CMD_BIT_LS
#define CMD_MMC_OP_COND     CMD(MMC_SEND_OP_COND, 3)    | CMD_BIT_LS | CMD_BIT_INIT
#define CMD_ALL_SEND_CID    CMD(MMC_ALL_SEND_CID, 2)    | CMD_BIT_LS
#define CMD_MMC_SET_RCA     CMD(MMC_SET_RELATIVE_ADDR, 1) | CMD_BIT_LS
#define CMD_SD_SEND_RCA     CMD(SD_SEND_RELATIVE_ADDR, 1) | CMD_BIT_LS
#define CMD_SEND_CSD        CMD(MMC_SEND_CSD, 2) | CMD_BIT_LS
#define CMD_SEND_EXT_CSD    CMD(MMC_SEND_EXT_CSD, 1) | CMD_BIT_LS | CMD_BIT_DATA
#define CMD_DESELECT_CARD   CMD(MMC_SELECT_CARD, 0)
#define CMD_SELECT_CARD     CMD(MMC_SELECT_CARD, 1)
#define CMD_SET_BLOCKLEN    CMD(MMC_SET_BLOCKLEN, 1)
#define CMD_SEND_STATUS     CMD(MMC_SEND_STATUS, 1)
#define CMD_READ_SINGLE     CMD(MMC_READ_SINGLE_BLOCK, 1) | CMD_BIT_DATA
#define CMD_READ_MULTIPLE   CMD(MMC_READ_MULTIPLE_BLOCK, 1) | CMD_BIT_DATA | CMD_BIT_AUTO_STOP
#define CMD_SD_SET_WIDTH    CMD(SD_APP_SET_BUS_WIDTH, 1) | CMD_BIT_APP
#define CMD_STOP            CMD(MMC_STOP_TRANSMISSION, 1) | CMD_BIT_BUSY
#define CMD_WRITE_SINGLE    CMD(MMC_WRITE_BLOCK, 1) | CMD_BIT_DATA | CMD_BIT_WRITE
#define CMD_WRITE_MULTIPLE  CMD(MMC_WRITE_MULTIPLE_BLOCK, 1) | CMD_BIT_DATA | CMD_BIT_WRITE | CMD_BIT_AUTO_STOP

/** @brief card type defines
 */
#define CARD_TYPE_SD    (1 << 0)
#define CARD_TYPE_4BIT  (1 << 1)
#define CARD_TYPE_8BIT  (1 << 2)
#define CARD_TYPE_HC    (OCR_HC_CCS)/*!< high capacity card > 2GB */

#define MMC_SECTOR_SIZE 512

/** @brief Setup options for the SDIO driver
 */
#define US_TIMEOUT            1000000		/*!< give 1 atleast 1 sec for the card to respond */
#define MS_ACQUIRE_DELAY      (10)			/*!< inter-command acquire oper condition delay in msec*/
#define INIT_OP_RETRIES       50			/*!< initial OP_COND retries */
#define SET_OP_RETRIES        1000			/*!< set OP_COND retries */
#define SDIO_BUS_WIDTH        4				/*!< Max bus width supported */
#define SD_MMC_ENUM_CLOCK       400000		/*!< Typical enumeration clock rate */
#define MMC_MAX_CLOCK           20000000	/*!< Max MMC clock rate */
#define MMC_LOW_BUS_MAX_CLOCK   26000000	/*!< Type 0 MMC card max clock rate */
#define MMC_HIGH_BUS_MAX_CLOCK  52000000	/*!< Type 1 MMC card max clock rate */
#define SD_MAX_CLOCK            25000000	/*!< Max SD clock rate */

/* Function prototype for event setup function */
typedef void (*MCI_EVSETUP_FUNC_T)(uint32_t);

/* Function prototype for wait (for IRQ) function */
typedef uint32_t (*MCI_WAIT_CB_FUNC_T)(void);

/* Function prototype for milliSecond delay function */
typedef void (*MCI_MSDELAY_FUNC_T)(uint32_t);

/* Card specific setup data */
typedef struct _mci_card_struct {
	uint32_t response[4];						/*!< Most recent response */
	uint32_t cid[4];							/*!< CID of acquired card  */
	uint32_t csd[4];							/*!< CSD of acquired card */
	uint32_t ext_csd[512 / 4];
	uint32_t card_type;
	uint32_t rca;								/*!< Relative address assigned to card */
	uint32_t speed;
	uint32_t block_len;							/*!< Card sector size*/
	uint32_t device_size;
	uint32_t blocknr;
	uint32_t clk_rate;
	sdif_device sdif_dev;
	MCI_EVSETUP_FUNC_T evsetup_cb;
	MCI_WAIT_CB_FUNC_T waitfunc_cb;
	MCI_MSDELAY_FUNC_T msdelay_func;
} mci_card_struct;

/**
 * @brief	Detect if an SD card is inserted
 * @return	Returns 0 if a card is detected, otherwise 1
 * Detect if an SD card is inserted
 * (uses SD_CD pin, returns 0 on card detect)
 */
STATIC INLINE int32_t Chip_SDMMC_CardNDetect(void)
{
	return IP_SDMMC_CardNDetect(LPC_SDMMC);
}

/**
 * @brief	Detect if write protect is enabled
 * @return	Returns 1 if card is write protected, otherwise 0
 * Detect if write protect is enabled
 * (uses SD_WP pin, returns 1 if card is write protected)
 */
STATIC INLINE int32_t Chip_CardWpOn(void)
{
	return IP_SDMMC_CardWpOn(LPC_SDMMC);
}

/**
 * @brief	Initializes the MCI card controller
 * @return	None
 */
STATIC INLINE void Chip_SDMMC_Init(void)
{
	IP_SDMMC_Init(LPC_SDMMC);
}

/**
 * @brief	Enable or disable slot power
 * @param	enable	: !0 to enable, or 0 to disable
 * @return	None
 * Enable or disable slot power, !0 = enable slot power
 * (Uses SD_POW pin, set to high or low based on enable parameter state)
 */
STATIC INLINE void Chip_SDMMC_PowerOnOff(int32_t enable)
{
	IP_SDMMC_PowerOnOff(LPC_SDMMC, enable);
}

/**
 * @brief	Sets the SD interface interrupt mask
 * @param	iVal	: Interrupts to enable, Or'ed values MCI_INT_*
 * @return	None
 */
STATIC INLINE void Chip_SDMMC_SetIntMask(uint32_t iVal)
{
	IP_SDMMC_SetIntMask(LPC_SDMMC, iVal);
}

/**
 * @brief	Returns the current SD status, clears pending ints, and disables all ints
 * @return	Current pending interrupt status of Or'ed values MCI_INT_*
 */
uint32_t Chip_SDMMC_GetIntStatus(void);

/**
 * @brief	Get card's current state (idle, transfer, program, etc.)
 * @return	Current SD card transfer state
 */
int32_t Chip_SDMMC_GetState(void);

/**
 * @brief	Function to enumerate the SD/MMC/SDHC/MMC+ cards
 * @param	pcardinfo	: Pointer to pre-allocated card info structure
 * @return	1 if a card is acquired, otherwise 0
 */
uint32_t Chip_SDMMC_Acquire(mci_card_struct *pcardinfo);

/**
 * @brief	Get the device size of SD/MMC card (after enumeration)
 * @return	Card size (capacity)
 */
int32_t Chip_SDMMC_GetDeviceSize(void);

/**
 * @brief	Performs the read of data from the SD/MMC card
 * @param	buffer		: Pointer to data buffer to copy to
 * @param	start_block	: Start block number
 * @param	num_blocks	: Number of block to read
 * @return	Bytes read, or 0 on error
 */
int32_t Chip_SDMMC_ReadBlocks(void *buffer, int32_t start_block, int32_t num_blocks);

/**
 * @brief	Performs write of data to the SD/MMC card
 * @param	buffer		: Pointer to data buffer to copy to
 * @param	start_block	: Start block number
 * @param	num_blocks	: Number of block to write
 * @return	Number of bytes actually written, or 0 on error
 */
int32_t Chip_SDMMC_WriteBlocks(void *buffer, int32_t start_block, int32_t num_blocks);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SDMMC_18XX_43XX_H_ */
