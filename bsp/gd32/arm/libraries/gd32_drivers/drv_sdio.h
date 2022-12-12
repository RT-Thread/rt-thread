/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-20     jiezhi320    the first version
 */

#ifndef __SDCARD_H_
#define __SDCARD_H_

#include <board.h>

#if defined SOC_SERIES_GD32F10x
#include "gd32f10x_sdio.h"
#include "gd32f10x_dma.h"
#elif defined SOC_SERIES_GD32F20x
#include "gd32f20x_sdio.h"
#include "gd32f20x_dma.h"
#elif defined SOC_SERIES_GD32F30x
#include "gd32f30x_sdio.h"
#include "gd32f30x_dma.h"
#elif defined SOC_SERIES_GD32F4xx
#include "gd32f4xx_sdio.h"
#include "gd32f4xx_dma.h"
#endif

#define SDIO_PERI_CLOCK            RCU_SDIO
#define SDIO_GPIO_CLK              RCU_GPIOC
#define SDIO_GPIO_CMD              RCU_GPIOD
#define SDIO_GPIO_D0               RCU_GPIOC
#define SDIO_GPIO_D1               RCU_GPIOC
#define SDIO_GPIO_D2               RCU_GPIOC
#define SDIO_GPIO_D3               RCU_GPIOC

#define SDIO_CLK_PORT              GPIOC
#define SDIO_CLK_PIN               GPIO_PIN_12
#define SDIO_CMD_PORT              GPIOD
#define SDIO_CMD_PIN               GPIO_PIN_2
#define SDIO_D0_PORT               GPIOC
#define SDIO_D0_PIN                GPIO_PIN_8
#define SDIO_D1_PORT               GPIOC
#define SDIO_D1_PIN                GPIO_PIN_9
#define SDIO_D2_PORT               GPIOC
#define SDIO_D2_PIN                GPIO_PIN_10
#define SDIO_D3_PORT               GPIOC
#define SDIO_D3_PIN                GPIO_PIN_11

#define SDIO_DMA                   DMA1
#define SDIO_DMA_CLOCK             RCU_DMA1
#define SDIO_DMA_CHANNEL           DMA_CH3
#define SDIO_DMA_IRQ               DMA1_Channel3_IRQn
#define SDIO_DMA_IRQ_HANDLER       DMA1_Channel3_IRQHandler


/* SD memory card bus commands index */
#define SD_CMD_GO_IDLE_STATE                  ((uint8_t)0)   /* CMD0, GO_IDLE_STATE */
#define SD_CMD_ALL_SEND_CID                   ((uint8_t)2)   /* CMD2, ALL_SEND_CID */
#define SD_CMD_SEND_RELATIVE_ADDR             ((uint8_t)3)   /* CMD3, SEND_RELATIVE_ADDR */
#define SD_CMD_SET_DSR                        ((uint8_t)4)   /* CMD4, SET_DSR */
#define SD_CMD_SWITCH_FUNC                    ((uint8_t)6)   /* CMD6, SWITCH_FUNC */
#define SD_CMD_SELECT_DESELECT_CARD           ((uint8_t)7)   /* CMD7, SELECT_DESELECT_CARD */
#define SD_CMD_SEND_IF_COND                   ((uint8_t)8)   /* CMD8, SEND_IF_COND */
#define SD_CMD_SEND_CSD                       ((uint8_t)9)   /* CMD9, SEND_CSD */
#define SD_CMD_SEND_CID                       ((uint8_t)10)  /* CMD10, SEND_CID */
#define SD_CMD_STOP_TRANSMISSION              ((uint8_t)12)  /* CMD12, STOP_TRANSMISSION */
#define SD_CMD_SEND_STATUS                    ((uint8_t)13)  /* CMD13, SEND_STATUS */
#define SD_CMD_GO_INACTIVE_STATE              ((uint8_t)15)  /* CMD15, GO_INACTIVE_STATE */
#define SD_CMD_SET_BLOCKLEN                   ((uint8_t)16)  /* CMD16, SET_BLOCKLEN */
#define SD_CMD_READ_SINGLE_BLOCK              ((uint8_t)17)  /* CMD17, READ_SINGLE_BLOCK */
#define SD_CMD_READ_MULTIPLE_BLOCK            ((uint8_t)18)  /* CMD18, READ_MULTIPLE_BLOCK */
#define SD_CMD_WRITE_BLOCK                    ((uint8_t)24)  /* CMD24, WRITE_BLOCK */
#define SD_CMD_WRITE_MULTIPLE_BLOCK           ((uint8_t)25)  /* CMD25, WRITE_MULTIPLE_BLOCK */
#define SD_CMD_PROG_CSD                       ((uint8_t)27)  /* CMD27, PROG_CSD */
#define SD_CMD_SET_WRITE_PROT                 ((uint8_t)28)  /* CMD28, SET_WRITE_PROT */
#define SD_CMD_CLR_WRITE_PROT                 ((uint8_t)29)  /* CMD29, CLR_WRITE_PROT */
#define SD_CMD_SEND_WRITE_PROT                ((uint8_t)30)  /* CMD30, SEND_WRITE_PROT */
#define SD_CMD_ERASE_WR_BLK_START             ((uint8_t)32)  /* CMD32, ERASE_WR_BLK_START */
#define SD_CMD_ERASE_WR_BLK_END               ((uint8_t)33)  /* CMD33, ERASE_WR_BLK_END */
#define SD_CMD_ERASE                          ((uint8_t)38)  /* CMD38, ERASE */
#define SD_CMD_LOCK_UNLOCK                    ((uint8_t)42)  /* CMD42, LOCK_UNLOCK */
#define SD_CMD_APP_CMD                        ((uint8_t)55)  /* CMD55, APP_CMD */
#define SD_CMD_GEN_CMD                        ((uint8_t)56)  /* CMD56, GEN_CMD */

/* SD memory card application specific commands index */
#define SD_APPCMD_SET_BUS_WIDTH               ((uint8_t)6)   /* ACMD6, SET_BUS_WIDTH */
#define SD_APPCMD_SD_STATUS                   ((uint8_t)13)  /* ACMD13, SD_STATUS */
#define SD_APPCMD_SEND_NUM_WR_BLOCKS          ((uint8_t)22)  /* ACMD22, SEND_NUM_WR_BLOCKS */
#define SD_APPCMD_SET_WR_BLK_ERASE_COUNT      ((uint8_t)23)  /* ACMD23, SET_WR_BLK_ERASE_COUNT */
#define SD_APPCMD_SD_SEND_OP_COND             ((uint8_t)41)  /* ACMD41, SD_SEND_OP_COND */
#define SD_APPCMD_SET_CLR_CARD_DETECT         ((uint8_t)42)  /* ACMD42, SET_CLR_CARD_DETECT */
#define SD_APPCMD_SEND_SCR                    ((uint8_t)51)  /* ACMD51, SEND_SCR */

/* card command class */
#define SD_CCC_SWITCH                          BIT(10)       /* class 10 */
#define SD_CCC_IO_MODE                         BIT(9)        /* class 9 */
#define SD_CCC_APPLICATION_SPECIFIC            BIT(8)        /* class 8 */
#define SD_CCC_LOCK_CARD                       BIT(7)        /* class 7 */
#define SD_CCC_WRITE_PROTECTION                BIT(6)        /* class 6 */
#define SD_CCC_ERASE                           BIT(5)        /* class 5 */
#define SD_CCC_BLOCK_WRITE                     BIT(4)        /* class 4 */
#define SD_CCC_BLOCK_READ                      BIT(2)        /* class 2 */
#define SD_CCC_BASIC                           BIT(0)        /* class 0 */

/* SD card data transmission mode */
#define SD_DMA_MODE                           ((uint32_t)0x00000000) /* DMA mode */
#define SD_POLLING_MODE                       ((uint32_t)0x00000001) /* polling mode */

/* lock unlock status */
#define SD_LOCK                               ((uint8_t)0x05)        /* lock the SD card */
#define SD_UNLOCK                             ((uint8_t)0x02)        /* unlock the SD card */

/* supported memory cards types */
typedef enum
{
    SDIO_STD_CAPACITY_SD_CARD_V1_1 = 0,   /* standard capacity SD card version 1.1 */
    SDIO_STD_CAPACITY_SD_CARD_V2_0,       /* standard capacity SD card version 2.0 */
    SDIO_HIGH_CAPACITY_SD_CARD,           /* high capacity SD card */
    SDIO_SECURE_DIGITAL_IO_CARD,          /* secure digital IO card */
    SDIO_SECURE_DIGITAL_IO_COMBO_CARD,    /* secure digital IO combo card */
    SDIO_MULTIMEDIA_CARD,                 /* multimedia card */
    SDIO_HIGH_CAPACITY_MULTIMEDIA_CARD,   /* high capacity multimedia card */
    SDIO_HIGH_SPEED_MULTIMEDIA_CARD       /* high speed multimedia card */
}sdio_card_type_enum;

/* card identification (CID) register */
typedef struct
{
    __IO uint8_t mid;                     /* manufacturer ID */
    __IO uint16_t oid;                    /* OEM/application ID */
    __IO uint32_t pnm0;                   /* product name */
    __IO uint8_t pnm1;                    /* product name */
    __IO uint8_t prv;                     /* product revision */
    __IO uint32_t psn;                    /* product serial number */
    __IO uint16_t mdt;                    /* manufacturing date */
    __IO uint8_t cid_crc;                 /* CID CRC7 checksum */
}sd_cid_struct;

/* CSD register (CSD version 1.0 and 2.0) */
typedef struct
{
    __IO uint8_t csd_struct;              /* CSD struct */
    __IO uint8_t taac;                    /* data read access-time */
    __IO uint8_t nsac;                    /* data read access-time in CLK cycles */
    __IO uint8_t tran_speed;              /* max. data transfer rate */
    __IO uint16_t ccc;                    /* card command classes */
    __IO uint8_t read_bl_len;             /* max. read data block length */
    __IO uint8_t read_bl_partial;         /* partial blocks for read allowed */
    __IO uint8_t write_blk_misalign;      /* write block misalignment */
    __IO uint8_t read_blk_misalign;       /* read block misalignment */
    __IO uint8_t dsp_imp;                 /* DSR implemented */
    __IO uint32_t c_size;                 /* device size, 12 bits in CSD version 1.0, 22 bits in CSD version 2.0 */
    __IO uint8_t vdd_r_curr_min;          /* max. read current @VDD min, CSD version 1.0 */
    __IO uint8_t vdd_r_curr_max;          /* max. read current @VDD max, CSD version 1.0 */
    __IO uint8_t vdd_w_curr_min;          /* max. write current @VDD min, CSD version 1.0 */
    __IO uint8_t vdd_w_curr_max;          /* max. write current @VDD max, CSD version 1.0 */
    __IO uint8_t c_size_mult;             /* device size multiplier, CSD version 1.0 */
    __IO uint8_t erase_blk_en;            /* erase single block enable */
    __IO uint8_t sector_size;             /* erase sector size */
    __IO uint8_t wp_grp_size;             /* write protect group size */
    __IO uint8_t wp_grp_enable;           /* write protect group enable */
    __IO uint8_t r2w_factor;              /* write speed factor */
    __IO uint8_t write_bl_len;            /* max. write data block length */
    __IO uint8_t write_bl_partial;        /* partial blocks for write allowed */
    __IO uint8_t file_format_grp;         /* file format group */
    __IO uint8_t copy_flag;               /* copy flag (OTP) */
    __IO uint8_t perm_write_protect;      /* permanent write protection */
    __IO uint8_t tmp_write_protect;       /* temporary write protection */
    __IO uint8_t file_format;             /* file format */
    __IO uint8_t csd_crc;                 /* CSD CRC checksum */
}sd_csd_struct;

/* information of card */
typedef struct
{
    sd_cid_struct card_cid;               /* CID register */
    sd_csd_struct card_csd;               /* CSD register */
    sdio_card_type_enum card_type;        /* card tpye */
    uint32_t card_capacity;               /* card capacity */
    uint32_t card_blocksize;              /* card block size */
    uint16_t card_rca;                    /* card relative card address */
}sd_card_info_struct;

/* SD error flags */
typedef enum
{
    SD_OUT_OF_RANGE = 0,                  /* command's argument was out of range */
    SD_ADDRESS_ERROR,                     /* misaligned address which did not match the block length */
    SD_BLOCK_LEN_ERROR,                   /* transferred block length is not allowed for the card or the number of transferred bytes does not match the block length */
    SD_ERASE_SEQ_ERROR,                   /* an error in the sequence of erase command occurs */
    SD_ERASE_PARAM,                       /* an invalid selection of write-blocks for erase occurred */
    SD_WP_VIOLATION,                      /* attempt to program a write protect block or permanent write protected card */
    SD_LOCK_UNLOCK_FAILED,                /* sequence or password error has been detected in lock/unlock card command */
    SD_COM_CRC_ERROR,                     /* CRC check of the previous command failed */
    SD_ILLEGAL_COMMAND,                   /* command not legal for the card state */
    SD_CARD_ECC_FAILED,                   /* card internal ECC was applied but failed to correct the data */
    SD_CC_ERROR,                          /* internal card controller error */
    SD_GENERAL_UNKNOWN_ERROR,             /* general or unknown error occurred during the operation */
    SD_CSD_OVERWRITE,                     /* read only section of the CSD does not match the card content or an attempt to reverse the copy or permanent WP bits was made */
    SD_WP_ERASE_SKIP,                     /* only partial address space was erased or the temporary or permanent write protected card was erased */
    SD_CARD_ECC_DISABLED,                 /* command has been executed without using internal ECC */
    SD_ERASE_RESET,                       /* erase sequence was cleared before executing because an out of erase sequence command was received */
    SD_AKE_SEQ_ERROR,                     /* error in the sequence of the authentication process */

    SD_CMD_CRC_ERROR,                     /* command response received (CRC check failed) */
    SD_DATA_CRC_ERROR,                    /* data block sent/received (CRC check failed) */
    SD_CMD_RESP_TIMEOUT,                  /* command response timeout */
    SD_DATA_TIMEOUT,                      /* data timeout */
    SD_TX_UNDERRUN_ERROR,                 /* transmit FIFO underrun error occurs */
    SD_RX_OVERRUN_ERROR,                  /* received FIFO overrun error occurs */
    SD_START_BIT_ERROR,                   /* start bit error in the bus */

    SD_VOLTRANGE_INVALID,                 /* the voltage range is invalid */
    SD_PARAMETER_INVALID,                 /* the parameter is invalid */
    SD_OPERATION_IMPROPER,                /* the operation is improper */
    SD_FUNCTION_UNSUPPORTED,              /* the function is unsupported */
    SD_ERROR,                             /* an error occurred */
    SD_OK                                 /* no error occurred */
}sd_error_enum;

typedef enum
{
  SD_NO_TRANSFER = 0,                     /* no data transfer is acting */
  SD_TRANSFER_IN_PROGRESS                 /* data transfer is in progress */
}sd_transfer_state_enum;


/* function declarations */
/* initialize the SD card and make it in standby state */
sd_error_enum sd_init(void);
/* initialize the card and get CID and CSD of the card */
sd_error_enum sd_card_init(void);
/* configure the clock and the work voltage, and get the card type */
sd_error_enum sd_power_on(void);
/* close the power of SDIO */
sd_error_enum sd_power_off(void);

/* configure the bus mode */
sd_error_enum sd_bus_mode_config(uint32_t busmode);
/* configure the mode of transmission */
sd_error_enum sd_transfer_mode_config(uint32_t txmode);

/* read a block data into a buffer from the specified address of a card */
sd_error_enum sd_block_read(uint32_t *preadbuffer, uint32_t readaddr, uint16_t blocksize);
/* read multiple blocks data into a buffer from the specified address of a card */
sd_error_enum sd_multiblocks_read(uint32_t *preadbuffer, uint32_t readaddr, uint16_t blocksize, uint32_t blocksnumber);
/* write a block data to the specified address of a card */
sd_error_enum sd_block_write(uint32_t *pwritebuffer, uint32_t writeaddr, uint16_t blocksize);
/* write multiple blocks data to the specified address of a card */
sd_error_enum sd_multiblocks_write(uint32_t *pwritebuffer, uint32_t writeaddr, uint16_t blocksize, uint32_t blocksnumber);
/* erase a continuous area of a card */
sd_error_enum sd_erase(uint32_t startaddr, uint32_t endaddr);
/* process all the interrupts which the corresponding flags are set */
sd_error_enum sd_interrupts_process(void);

/* select or deselect a card */
sd_error_enum sd_card_select_deselect(uint16_t cardrca);
/* get the card status whose response format R1 contains a 32-bit field */
sd_error_enum sd_cardstatus_get(uint32_t *pcardstatus);
/* get the SD status, the size of the SD status is one data block of 512 bit */
sd_error_enum sd_sdstatus_get(uint32_t *psdstatus);
/* stop an ongoing data transfer */
sd_error_enum sd_transfer_stop(void);
/* lock or unlock a card */
sd_error_enum sd_lock_unlock(uint8_t lockstate);

/* get the data transfer state */
sd_transfer_state_enum sd_transfer_state_get(void);
/* get SD card capacity(KB) */
uint32_t sd_card_capacity_get(void);
/* get the detailed information of the SD card based on received CID and CSD */
sd_error_enum sd_card_information_get(sd_card_info_struct *pcardinfo);

#endif /* __SDCARD_H_ */


