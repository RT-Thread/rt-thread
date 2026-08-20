/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-08-11     ox-horse         first version
 */

#ifndef __SD_HOST_H__
#define __SD_HOST_H__

#include "board.h"

/* SD card product name length united as bytes. */
#define SD_PRODUCT_NAME_BYTES (5U)

/* SD card CID register */
typedef struct
{
    uint8_t manufacturerID;                     /* Manufacturer ID [127:120] */
    uint16_t applicationID;                     /* OEM/Application ID [119:104] */
    uint8_t productName[SD_PRODUCT_NAME_BYTES]; /* Product name [103:64] */
    uint8_t productVersion;                     /* Product revision [63:56] */
    uint32_t productSerialNumber;               /* Product serial number [55:24] */
    uint16_t manufacturerData;                  /* Manufacturing date [19:8] */
} sd_cid;

/* SD card CSD register */
typedef struct
{
    uint8_t csdStructure;        /* CSD structure [127:126] */
    uint8_t dataReadAccessTime1; /* Data read access-time-1 [119:112] */
    uint8_t dataReadAccessTime2; /* Data read access-time-2 in clock cycles (NSAC*100) [111:104] */
    uint8_t transferSpeed;       /* Maximum data transfer rate [103:96] */
    uint16_t cardCommandClass;   /* Card command classes [95:84] */
    uint8_t readBlockLength;     /* Maximum read data block length [83:80] */
    uint16_t flags;              /* Flags in _sd_csd_flag */
    uint32_t deviceSize;         /* Device size [73:62] */
    /* Following fields from 'readCurrentVddMin' to 'deviceSizeMultiplier' exist in CSD version 1 */
    uint8_t readCurrentVddMin;    /* Maximum read current at VDD min [61:59] */
    uint8_t readCurrentVddMax;    /* Maximum read current at VDD max [58:56] */
    uint8_t writeCurrentVddMin;   /* Maximum write current at VDD min [55:53] */
    uint8_t writeCurrentVddMax;   /* Maximum write current at VDD max [52:50] */
    uint8_t deviceSizeMultiplier; /* Device size multiplier [49:47] */

    uint8_t eraseSectorSize;       /* Erase sector size [45:39] */
    uint8_t writeProtectGroupSize; /* Write protect group size [38:32] */
    uint8_t writeSpeedFactor;      /* Write speed factor [28:26] */
    uint8_t writeBlockLength;      /* Maximum write data block length [25:22] */
    uint8_t fileFormat;            /* File format [11:10] */
} sd_csd_t;

/* SD card SCR register */
typedef struct _sd_scr
{
    uint8_t scrStructure;             /* SCR Structure [63:60] */
    uint8_t sdSpecification;          /* SD memory card specification version [59:56] */
    uint16_t flags;                   /* SCR flags in _sd_scr_flag */
    uint8_t sdSecurity;               /* Security specification supported [54:52] */
    uint8_t sdBusWidths;              /* Data bus widths supported [51:48] */
    uint8_t commandSupport;           /* Command support bits [33:32] 33-support CMD23, 32-support cmd20*/
    uint32_t reservedForManufacturer; /* reserved for manufacturer usage [31:0] */
} sd_scr_t;

/* Record information of card */
typedef struct
{
    uint32_t flags;         /* sd card Flags */
    uint32_t busy;          /* busy status */
    uint32_t ocr;           /* Raw OCR content,, only 24bit avalible for SDIO card */
    sd_cid cid;           /* CID */
    uint32_t rca;           /* Relative address of the card */
    sd_csd_t csd;           /* CSD */
    uint32_t blockCount;    /* Card total block number */
    uint32_t blockSize;     /* Card block size */
    sd_scr_t scr;           /* SCR */
    uint32_t version;       /* Card version */
//    sd_status_t stat;       /* sd 512 bit status */
} sd_card_info;


/* card bus width */
typedef enum
{
    SDMMC_BusWidth1Bit = 0U, /* card bus 1 width */
    SDMMC_BusWidth4Bit = 1U, /* card bus 4 width */
    SDMMC_BusWidth8Bit = 2U, /* card bus 8 width */
} sd_bus_width_t;

/* dma mode */
typedef enum
{
    SDMMC_NODMA = 0U,  /* no use dma */
    SDMMC_SDMA = 1U,   /* use sdma */
    SDMMC_ADMA = 2U,   /* use adma */
} sd_dma_t;

/* card operation voltage */
typedef enum
{
    SD_OperationVoltageNone = 0U, /* indicate current voltage setting is not setting by suser*/
    SD_OperationVoltage330V = 1U, /* card operation voltage around 3.3v */
    SD_OperationVoltage300V = 2U, /* card operation voltage around 3.0v */
    SD_OperationVoltage180V = 3U, /* card operation voltage around 1.8v */
} sd_operation_voltage_t;

/* SD card communication method and speed */
typedef struct
{
    uint32_t busClock_Hz;     /* SD bus clock frequency united in Hz */
    sd_bus_width_t busWidth; /* set DATA bus width */
    SD_ModeConfig mode;         /* work mode */
    sd_dma_t dma;           /* dma mode */
    sd_operation_voltage_t operationVoltageflag; /* card current operation voltage */
} sd_card_workmode;

/* SD card state
 * Define the card structure including the necessary fields to identify and describe the card.
 */
typedef struct
{
    SDHOST_Module *SDHOSTx; /* Host device */
    SDMMC_Module *SDMMCx;   /* SDMMC */
    SDMMC_CMD command;
    sd_card_info sd_card_information;
    sd_card_workmode card_workmode;
    SDHOST_TMODE_struct tMode;
} sd_card_t;

#ifdef __cplusplus
}
#endif

#endif /* __SD_HOST_H__ */
