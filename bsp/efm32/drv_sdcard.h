/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-05-13   onelife     Initial creation for using EFM32 USART module
 * 2011-07-07   onelife     Modify initialization function to return error code
 */

#ifndef __DEV_SDCARD_H__
#define __DEV_SDCARD_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define EFM32_SDCLK_LOW         (100000)
#if defined(EFM32_GXXX_DK)
#define EFM32_SDCLK_HIGH        (16000000)
#elif defined(EFM32GG_DK3750)
#define EFM32_SDCLK_HIGH        (19000000)
#endif

#if (EFM32_SDCLK_HIGH > (EFM32_HFXO_FREQUENCY/2))
#error "EFM32 SPI clock should not be more than (EFM32_HFXO_FREQUENCY/2)"
#endif

#define SD_SPEED_LOW            (0)
#define SD_SPEED_HIGH           (1)
#define SD_WAIT_PERIOD          (RT_TICK_PER_SECOND)

#define SD_SECTOR_SIZE_SHIFT    (9)
#define SD_SECTOR_SIZE          (1 << SD_SECTOR_SIZE_SHIFT)
#define SD_BLOCK_SIZE_CSD       (16)
#define SD_BLOCK_SIZE_CID       (16)
#define SD_BLOCK_SIZE_OCR       (4)
#define SD_BLOCK_SIZE_SDSTAT    (64)

/* Card type definitions (CardType) */
#define CT_MMC                  (0x01)
#define CT_SD1                  (0x02)
#define CT_SD2                  (0x04)
#define CT_SDC                  (CT_SD1|CT_SD2)
#define CT_BLOCK                (0x08)

/* Definitions for MMC/SDC command */
#define CMD0                    (0)         /* GO_IDLE_STATE */
#define CMD1                    (1)         /* SEND_OP_COND */
#define ACMD41                  (41|0x80)   /* SEND_OP_COND (SDC) */
#define CMD8                    (8)         /* SEND_IF_COND */
#define CMD9                    (9)         /* SEND_CSD */
#define CMD10                   (10)        /* SEND_CID */
#define CMD12                   (12)        /* STOP_TRANSMISSION */
#define ACMD13                  (13|0x80)   /* SD_STATUS (SDC) */
#define CMD16                   (16)        /* SET_BLOCKLEN */
#define CMD17                   (17)        /* READ_SINGLE_BLOCK */
#define CMD18                   (18)        /* READ_MULTIPLE_BLOCK */
#define CMD23                   (23)        /* SET_BLOCK_COUNT */
#define ACMD23                  (23|0x80)   /* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24                   (24)        /* WRITE_BLOCK */
#define CMD25                   (25)        /* WRITE_MULTIPLE_BLOCK */
#define CMD41                   (41)        /* SEND_OP_COND (ACMD) */
#define CMD55                   (55)        /* APP_CMD */
#define CMD58                   (58)        /* READ_OCR */

/* Exported functions ------------------------------------------------------- */
rt_err_t efm_spiSd_init(void);
void efm_spiSd_deinit(void);

#endif /* __DEV_SDCARD_H__ */
