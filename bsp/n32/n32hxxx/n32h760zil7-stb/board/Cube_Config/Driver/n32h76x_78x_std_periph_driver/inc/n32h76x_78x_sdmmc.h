/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_sdmmc.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H76X_78X_SDMMC_H__
#define __N32H76X_78X_SDMMC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h76x_78x.h"


/** Function declaration **/

/** SDMMC Init Structure Definition **/
typedef struct
{
    uint32_t MaxBlockLen;     /* Maximum Block Length supported by the Core/Device */
    uint32_t SDBaseCLKFreq;   /* xin_clk, Base Clock Frequency for SD Clock */
    uint32_t TimeOutUnit;     /* the unit of base clock frequency used to detect Data Timeout Error */
    uint32_t TuningCNT;       /* the number of delay taps that are supported for tuning the rxclk_in */
    uint32_t WKUPSignalMode;  /* Wakeup Signal Generation Mode */
    uint32_t SPIBlockMode;    /* SPI Block Mode */
    uint32_t SPIMode;         /* SPI Mode Support */
    uint32_t DDR50;           /* DDR50 Support */
    uint32_t SDR104;          /* SDR104 Support */
    uint32_t SDR50;           /* SDR50 Support */
    uint32_t SlotType;        /* Slot Type */
    uint32_t AsyncInt;        /* Asynchronous Interrupt Support */
    uint32_t Suspend_Resume;  /* Suspend/Resume Support */
    uint32_t SDMA;            /* SDMA Support */
    uint32_t HS;              /* High Speed Support */
    uint32_t ADMA2;           /* ADMA2 Support */
    uint32_t Embedded_8bit;   /* 8-bit Support for Embedded Device */
    uint32_t UseTuningSDR50;  /* Use Tuning for SDR50 */
    uint32_t DSSDCLKFreq;     /* SDCLK Frequency Select Value for Default Speed */
    uint32_t INITSDCLKFreq;   /* SDCLK Frequency Select Value for Initialization */
    uint32_t SDR12SDCLKFreq;  /* SDCLK Frequency Select Value for SDR12 */
    uint32_t HSSDCLKFreq;     /* SDCLK Frequency Select Value for High Speed */
    uint32_t SDR50SDCLKFreq;  /* SDCLK Frequency Select Value for SDR50 */
    uint32_t SDR25SDCLKFreq;  /* SDCLK Frequency Select Value for SDR25 */
    uint32_t SDR104SDCLKFreq; /* SDCLK Frequency Select Value for SDR104 */
    uint32_t DDR50SDCLKFreq;  /* SDCLK Frequency Select Value for DDR50 */
} SDMMC_WrapperType;

/** SDHSOT capability Structure Definition **/
typedef struct
{
    uint32_t MaxBlockLen;     /* Maximum Block Length supported by the Core/Device */
    uint32_t SDBaseCLKFreq;   /* xin_clk, Base Clock Frequency for SD Clock */
    uint32_t TimeOutUnit;     /* the unit of base clock frequency used to detect Data Timeout Error */
    uint32_t SPIBlockMode;    /* SPI Block Mode */
    uint32_t SPIMode;         /* SPI Mode Support */
    uint32_t DDR50;           /* DDR50 Support */
    uint32_t SDR104;          /* SDR104 Support */
    uint32_t SDR50;           /* SDR50 Support */
    uint32_t SlotType;        /* Slot Type */
    uint32_t AsyncInt;        /* Asynchronous Interrupt Support */
    uint32_t Suspend_Resume;  /* Suspend/Resume Support */
    uint32_t SDMA;            /* SDMA Support */
    uint32_t HS;              /* High Speed Support */
    uint32_t ADMA2;           /* ADMA2 Support */
    uint32_t Embedded_8bit;   /* 8-bit Support for Embedded Device */
    uint32_t UseTuningSDR50;  /* Use Tuning for SDR50 */
} SDHOST_capability;

/** SDHSOT preset value Structure Definition **/
typedef struct
{
    uint32_t DSSDCLKFreq;     /* SDCLK Frequency Select Value for Default Speed */
    uint32_t INITSDCLKFreq;   /* SDCLK Frequency Select Value for Initialization */
    uint32_t SDR12SDCLKFreq;  /* SDCLK Frequency Select Value for SDR12 */
    uint32_t HSSDCLKFreq;     /* SDCLK Frequency Select Value for High Speed */
    uint32_t SDR50SDCLKFreq;  /* SDCLK Frequency Select Value for SDR50 */
    uint32_t SDR25SDCLKFreq;  /* SDCLK Frequency Select Value for SDR25 */
    uint32_t SDR104SDCLKFreq; /* SDCLK Frequency Select Value for SDR104 */
    uint32_t DDR50SDCLKFreq;  /* SDCLK Frequency Select Value for DDR50 */
} SDHOST_presetvalue;


/** SDMMC Status **/
typedef enum
{
    SDMMC_BusyTransferring = 1,             /* Transfer is on-going. */
    SDMMC_PrepareAdmaDescriptorFailed,      /* Set DMA descriptor failed. */
    SDMMC_SendCommandFailed,                /* Send command failed. */
    SDMMC_TransferDataFailed,               /* Transfer data failed. */
    SDMMC_DMADataAddrNotAlign,              /* Data address not aligned. */
    SDMMC_ReTuningRequest,                  /* Re-tuning request. */
    SDMMC_TuningError,                      /* Tuning error. */
    SDMMC_NotSupport,                       /* Not support. */
    SDMMC_TransferDataComplete,             /* Transfer data complete. */
    SDMMC_SendCommandSuccess,               /* Transfer command complete. */
    SDMMC_TransferDMAComplete,              /* Transfer DMA complete. */
    SDMMC_SUCCESS,                          /* The code execution flow is normal. */
    SDMMC_ERROR,                            /* Code execution flow exception. */
    SDMMC_OutOfRange                        /* Out of range access. */
} SDMMC_STS;

/* SDMMC transfer flags */
typedef enum
{
    SDMMC_CommandOnly        = 1U,  /* transfer command only */
    SDMMC_CommandAndTxData   = 2U,  /* transfer command and transmit data */
    SDMMC_CommandAndRxData   = 4U,  /* transfer command and receive data */
    SDMMC_DataWithAutoCmd12  = 8U,  /* transfer data with auto cmd12 enabled */
    SDMMC_DataWithAutoCmd23  = 16U, /* transfer data with auto cmd23 enabled */
    SDMMC_BootData           = 32U, /* transfer boot data */
    SDMMC_BootDataContinuous = 64U, /* transfer boot data continuous */
} SDMMC_TRANSFlAG;

/* Data transfer direction. */
typedef enum
{
    SDMMC_TransferDirSend    = 0U, /* transfer direction send. */
    SDMMC_TransferDirReceive = SDHOST_TMODE_DATDIR, /* transfer direction receive. */
} SDMMC_TRANSDIR;


/* The command type */
typedef enum
{
    CARD_CommandTypeNormal  = 0U, /* Normal command */
    CARD_CommandTypeSuspend = 1U, /* Suspend command */
    CARD_CommandTypeResume  = 2U, /* Resume command */
    CARD_CommandTypeAbort   = 3U, /* Abort command */
    CARD_CommandTypeEmpty   = 4U, /* Empty command */
} SDMMC_CardCMDType;

/* The command response type.
 * Defines the command response type from card to host controller.
 */
typedef enum
{
    CARD_ResponseTypeNone = 0U, /* Response type: none */
    CARD_ResponseTypeR1   = 1U, /* Response type: R1 */
    CARD_ResponseTypeR1b  = 2U, /* Response type: R1b */
    CARD_ResponseTypeR2   = 3U, /* Response type: R2 */
    CARD_ResponseTypeR3   = 4U, /* Response type: R3 */
    CARD_ResponseTypeR4   = 5U, /* Response type: R4 */
    CARD_ResponseTypeR5   = 6U, /* Response type: R5 */
    CARD_ResponseTypeR5b  = 7U, /* Response type: R5b */
    CARD_ResponseTypeR6   = 8U, /* Response type: R6 */
    CARD_ResponseTypeR7   = 9U, /* Response type: R7 */
} SDMMC_CardRspType;


/* Since every write operation to the TMODE register triggers the issuance of a CMD, 
   this struct is used to store some of the status bits of the TMODE register, 
   which are then written to the TMODE register collectively when issuing a CMD. */
typedef struct
{
    uint32_t DMAE;            /* DMA Enable. */
    uint32_t BCNTE;           /* Block Count Enable. */
    uint32_t ACMDE;           /* Auto CMD Enable. */
    uint32_t DATDIR;          /* Data Transfer Direction Select. */
    uint32_t BLKSEL;          /* Multi / Single Block Select. */
} SDHOST_TMODE_struct;

/* Card command descriptor. Defines card command-related attribute. */
typedef struct
{
    uint32_t index;                          /* Command index. */
    uint32_t argument;                       /* Command argument. */
    SDMMC_CardCMDType type;                  /* Command type. */
    SDMMC_CardRspType responseType;          /* Command response type. */
    uint32_t response[4U];                   /* Response for this command. */
    uint32_t responseErrorFlags;             /* Response error flag, which need to check the command reponse. */
    uint32_t flags;                          /* Cmd flags. */
} SDMMC_CMD;

/* Card data descriptor.
 *
 * Defines a structure to contain data-related attribute. The 'enableIgnoreError' is used when upper card
 * driver wants to ignore the error event to read/write all the data and not to stop read/write immediately when an
 * error event happens. For example, bus testing procedure for MMC card.
 */
typedef struct
{
    uint32_t AutoCommand12_23; /* Enable auto CMD12/CMD23. */
    FunctionalState enableIgnoreError;   /* Enable to ignore error event to read/write all the data. */
    uint8_t dataType;         /* this is used to distinguish the normal/tuning/boot data. */
    uint32_t blockSize;       /* Block size. */
    uint32_t blockCount;      /* Block count. */
    uint32_t *rxData;         /* Buffer to save data read. */
    const uint32_t *txData;   /* Data buffer to write. */
} SDMMC_DATA;

/* Transfer state. */
typedef struct
{
    SDMMC_DATA data;       /* Data to transfer. */
    SDMMC_CMD command;     /* Command to send. */
} SDMMC_Transfer;

/* Data structure to configure the MMC boot feature. */
typedef struct
{
    uint32_t ackTimeoutCount;      /* Timeout value for the boot ACK. */
    uint32_t bootMode;             /* Boot mode selection. */
    uint32_t blockCount;           /* Block count */
    uint32_t blockSize;            /* Block size. */
    uint32_t BootAck;              /* Enable or disable boot ACK. */
} SDHOST_boot_config;

/* DMA mode */
typedef enum
{
    DmaModeSimple = 0UL, /* SDMA  is selected. */
    DmaModeAdma2  = SDHOST_CTRL1_DMASEL_1, /* ADMA2 is selected. */
} SDHOST_DMAMODE;

/* ADMA configuration. */
typedef struct
{
    SDHOST_DMAMODE dmaMode; /* DMA mode. */
    uint32_t *admaTable;     /* ADMA table address, can't be null if transfer way is ADMA2. */
    uint32_t admaTableWords; /* ADMA table length united as words, can't be 0 if transfer way is ADMA2. */
} SDHOST_ADMAconfig;


/* Defines the ADMA2 descriptor structure. */
typedef struct
{
    uint32_t attribute;      /* The control and status field. */
    const uint32_t *address; /* The address field. */
} SDHOST_ADMA2_descriptor;

/* SDHOST Present status flag. */
enum
{
    SDHOST_CommandInhibitFlag      = SDHOST_PRESTS_CMDINHC,  /* Command inhibit. */
    SDHOST_DataInhibitFlag         = SDHOST_PRESTS_CMDINHD, /* Data inhibit. */
    SDHOST_DataLineActiveFlag      = SDHOST_PRESTS_DLACT,   /* Data line active. */
    SDHOST_ReTuningRequestFlag     = SDHOST_PRESTS_RETUNREQ, /* Re-tuning request flag */
    SDHOST_WriteTransferActiveFlag = SDHOST_PRESTS_WTRANACT,   /* Write transfer active. */
    SDHOST_ReadTransferActiveFlag  = SDHOST_PRESTS_RTRANACT,   /* Read transfer active. */
    SDHOST_BufferWriteEnableFlag   = SDHOST_PRESTS_BUFW,  /* Buffer write enable. */
    SDHOST_BufferReadEnableFlag    = SDHOST_PRESTS_BUFR,  /* Buffer read enable. */
    SDHOST_CardInsertedFlag        = SDHOST_PRESTS_CINS, /* Card inserted. */
    SDHOST_CardStateStableFlag     = SDHOST_PRESTS_CSTSL, /* Card State Stable. */
    SDHOST_CardDetectPinFlag       = SDHOST_PRESTS_SDCDL, /* Card Detect Pin Level. */
    SDHOST_CardWPSwitchPinFlag     = SDHOST_PRESTS_SDCDL, /* Write Protect Switch Pin Level. */
    
    SDHOST_CommandLineLevelFlag    = SDHOST_PRESTS_CMDL,  /* Command line signal level. */
    SDHOST_Data0LineLevelFlag = SDHOST_PRESTS_DATLL_0,        /* Data0 line signal level. */
    SDHOST_Data1LineLevelFlag = SDHOST_PRESTS_DATLL_1,        /* Data1 line signal level. */
    SDHOST_Data2LineLevelFlag = SDHOST_PRESTS_DATLL_2,        /* Data2 line signal level. */
    SDHOST_Data3LineLevelFlag = SDHOST_PRESTS_DATLL_3,        /* Data3 line signal level. */
    SDHOST_Data4LineLevelFlag = SDHOST_PRESTS_DATLH_0,        /* Data4 line signal level. */
    SDHOST_Data5LineLevelFlag = SDHOST_PRESTS_DATLH_1,        /* Data5 line signal level. */
    SDHOST_Data6LineLevelFlag = SDHOST_PRESTS_DATLH_2,        /* Data6 line signal level. */
    SDHOST_Data7LineLevelFlag = SDHOST_PRESTS_DATLH_3,        /* Data7 line signal level. */
};


/* SDHOST interrupt status flag */
enum
{
    SDHOST_CommandCompleteFlag  = SDHOST_INTSTS_CMDC,       /* Command complete. */
    SDHOST_DataCompleteFlag     = SDHOST_INTSTS_TC,         /* Data complete. */
    SDHOST_BlockGapEventFlag    = SDHOST_INTSTS_BLKGAPE,    /* Block gap event. */
    SDHOST_DmaCompleteFlag      = SDHOST_INTSTS_DMAINT,     /* DMA interrupt. */
    SDHOST_BufferWriteReadyFlag = SDHOST_INTSTS_BUFWRDY,    /* Buffer write ready. */
    SDHOST_BufferReadReadyFlag  = SDHOST_INTSTS_BUFRRDY,    /* Buffer read ready. */
    SDHOST_CardInsertionFlag    = SDHOST_INTSTS_CINS,       /* Card inserted. */
    SDHOST_CardRemovalFlag      = SDHOST_INTSTS_CRMV,       /* Card removed. */
    SDHOST_CardInterruptFlag    = SDHOST_INTSTS_CINT,       /* Card interrupt. */
    SDHOST_ReTuningEventFlag    = SDHOST_INTSTS_RETUNE,     /* Re-Tuning event */
    SDHOST_BootACKRcvFlag       = SDHOST_INTSTS_BOOTACKR,   /* BOOT ACK receive */
    SDHOST_BootTerminateFlag    = SDHOST_INTSTS_BOOTTER,    /* Boot terminate */
    SDHOST_AllErrorFlag         = SDHOST_INTSTS_ALLERR,     /* Sum of all error flags below */
    SDHOST_CommandTimeoutFlag     = SDHOST_INTSTS_CTERR,    /* Command timeout error. */
    SDHOST_CommandCrcErrorFlag    = SDHOST_INTSTS_CCRCERR,  /* Command CRC error. */
    SDHOST_CommandEndBitErrorFlag = SDHOST_INTSTS_CENDBERR, /* Command end bit error. */
    SDHOST_CommandIndexErrorFlag  = SDHOST_INTSTS_CINXERR,  /* Command index error. */
    SDHOST_DataTimeoutFlag        = SDHOST_INTSTS_DTERR,    /* Data timeout error. */
    SDHOST_DataCrcErrorFlag       = SDHOST_INTSTS_DCRCERR,  /* Data CRC error. */
    SDHOST_DataEndBitErrorFlag    = SDHOST_INTSTS_DENDERR,  /* Data end bit error. */
    SDHOST_AutoCommand12ErrorFlag = SDHOST_INTSTS_ACMDERR,  /* Auto CMD12 error. */
    SDHOST_DmaErrorFlag           = SDHOST_INTSTS_ADMAERR,  /* ADMA error. */
    SDHOST_TargetResErrorFlag     = SDHOST_INTSTS_TRGRERR,  /* Target Response error. */

    SDHOST_CommandErrorFlag = (SDHOST_CommandTimeoutFlag | SDHOST_CommandCrcErrorFlag | SDHOST_CommandEndBitErrorFlag |
                               SDHOST_CommandIndexErrorFlag), /* Command error */
    SDHOST_DataErrorFlag    = (SDHOST_DataTimeoutFlag | SDHOST_DataCrcErrorFlag | SDHOST_DataEndBitErrorFlag |
                               SDHOST_AutoCommand12ErrorFlag),                                        /* Data error */
    SDHOST_ErrorFlag        = (SDHOST_CommandErrorFlag | SDHOST_DataErrorFlag | SDHOST_DmaErrorFlag | 
                               SDHOST_TargetResErrorFlag), /* All other error */

    SDHOST_DataFlag = (SDHOST_DataCompleteFlag | SDHOST_BufferWriteReadyFlag | SDHOST_BufferReadReadyFlag |
                       SDHOST_DataErrorFlag), /* Data interrupts */

    SDHOST_DataDMAFlag = (SDHOST_DataCompleteFlag | SDHOST_DataErrorFlag | SDHOST_DmaErrorFlag), /* Data interrupts */

    SDHOST_CommandFlag      = (SDHOST_CommandErrorFlag | SDHOST_CommandCompleteFlag), /* Command interrupts */
    SDHOST_CardDetectFlag   = (SDHOST_CardInsertionFlag | SDHOST_CardRemovalFlag),    /* Card detection interrupts */
    SDHOST_AllInterruptFlags =
        (SDHOST_BlockGapEventFlag | SDHOST_CardInterruptFlag | SDHOST_CommandFlag | SDHOST_DataFlag | SDHOST_ErrorFlag |
         SDHOST_ReTuningEventFlag | SDHOST_DmaCompleteFlag | SDHOST_BootTerminateFlag | SDHOST_BootACKRcvFlag | SDHOST_CardDetectFlag), /* All flags mask */
};

/* Auto CMD12 error status flag. */
enum
{
    SDHOST_AutoCommand12NotExecutedFlag = SDHOST_CTRLSTS_ACMD12NE,    /* Not executed error. */
    SDHOST_AutoCommand12TimeoutFlag     = SDHOST_CTRLSTS_ACMDTE,      /* Timeout error. */
    SDHOST_AutoCommand12EndBitErrorFlag = SDHOST_CTRLSTS_ACMDEBE,     /* End bit error. */
    SDHOST_AutoCommand12CrcErrorFlag    = SDHOST_CTRLSTS_ACMDCRCE,    /* CRC error. */
    SDHOST_AutoCommand12IndexErrorFlag  = SDHOST_CTRLSTS_ACMDINXE,    /* Index error. */
    SDHOST_AutoCommand12NotIssuedFlag   = SDHOST_CTRLSTS_ACMD12E,     /* Not issued error. */
};

/* ADMA error status flag. */
enum
{
    SDHOST_AdmaLenghMismatchFlag       = SDHOST_ADMAESTS_ADMALME,    /* ADMA Length Mismatch Error. */
};


/* AutoCommand12_23 type. */
enum
{
    NoAutoCommand        = 0U, /* No Auto command. */
    AutoCommand23        = 1U, /* AutoCommand23 enable. */
    AutoCommand12        = 2U, /* AutoCommand12 enable. */
};

/* Tansfer data type definition. */
enum
{
    SDHOST_TransferDataNormal        = 0U, /* Transfer normal read/write data. */
    SDHOST_TransferDataTuning        = 1U, /* Transfer tuning data. */
    SDHOST_TransferDataBoot          = 2U, /* Transfer boot data. */
    SDHOST_TransferDataBootcontinous = 3U, /* Transfer boot data continuously. */
};

/** SDMMC timeout constant define **/
#define SDMMC_TIMEOUT_VALUE         (600000U)    /*10ms*/

/* Software Reset for DAT/CMD/ALL Line */
#define SDHOST_SOFTWARE_DATALINE  (SDHOST_CTRL2_SWRSTDL)    /* Software Reset for DAT Line */
#define SDHOST_SOFTWARE_CMDLINE   (SDHOST_CTRL2_SWRSTCL)    /* Software Reset for CMD Line */
#define SDHOST_SOFTWARE_ALLLINE   (SDHOST_CTRL2_SWRSTALL)   /* Software Reset for ALL Line */

/* Maximum Block Length supported by the Core/Device */
#define SDMMC_MAXBLOCKLEN_512B            ((uint32_t)0x00000000U)          /* 512 Bytes */
#define SDMMC_MAXBLOCKLEN_1024B           (SDMMC_CFG1_MBL_0)     /* 1024 Bytes */
#define SDMMC_MAXBLOCKLEN_2048B           (SDMMC_CFG1_MBL_1)     /* 2048 Bytes */

/* the unit of base clock frequency used to detect Data Timeout Error */
#define SDMMC_TIMEOUTCLKUNIT_KHZ          ((uint32_t)0x00000000U)          /* KHz */
#define SDMMC_TIMEOUTCLKUNIT_MHZ          (SDMMC_CFG1_TCLKU)     /* MHz */

/* Wakeup Signal Generation Mode */
#define SDMMC_SYNCWKUP           ((uint32_t)0x00000000U)         /* wakeup event are syncrhonized with controller clock (xin_clk). */
#define SDMMC_ASYNCWKUP          (SDMMC_CFG1_WSGM)     /* wakeup event are async with xin_clk */

/* SPI Block Mode */
#define SDMMC_TIMEOUTCLKUNIT_KHZ          ((uint32_t)0x00000000U)          /* KHz */
#define SDMMC_TIMEOUTCLKUNIT_MHZ          (SDMMC_CFG1_TCLKU)     /* MHz */

/* SPI Block Mode Support */
#define SDMMC_SPIBLOCKMODESUPPORT         (SDMMC_CFG2_SPIBMOD)    /* SPI Block Mode support */
#define SDMMC_SPIBLOCKMODEUNSUPPORT       ((uint32_t)0x00000000U)           /* SPI Block Mode not support */

/* SPI Mode Support */
#define SDMMC_SPIMODESUPPORT         (SDMMC_CFG2_SPIMOD)    /* SPI Mode support */
#define SDMMC_SPIMODEUNSUPPORT       ((uint32_t)0x00000000U)          /* SPI Mode not support */

/* DDR50 Mode Support */
#define SDMMC_DDR50SUPPORT         (SDMMC_CFG2_DDR50)     /* DDR50 support */
#define SDMMC_DDR50UNSUPPORT       ((uint32_t)0x00000000U)          /* DDR50 not support */

/* SDR104 Mode Support */
#define SDMMC_SDR104SUPPORT         (SDMMC_CFG2_SDR104)    /* SDR104 support */
#define SDMMC_SDR104UNSUPPORT       ((uint32_t)0x00000000U)          /* SDR104 not support */

/* SDR50 Mode Support */
#define SDMMC_SDR50SUPPORT         (SDMMC_CFG2_SDR50)     /* SDR50 support */
#define SDMMC_SDR50UNSUPPORT       ((uint32_t)0x00000000U)          /* SDR50 not support */

/* Slot Type */
#define SDMMC_SDTYPE          ((uint32_t)0x00000000U)             /* SD/SDIO Device */
#define SDMMC_EMMCTYPE        (SDMMC_CFG2_STYP_0)        /* emmc Device */

/* Asynchronous Interrupt Support */
#define SDMMC_ASYNCINTSUPPORT         (SDMMC_CFG2_ASYNCINT)            /* Asynchronous Interrupt Support */
#define SDMMC_ASYNCINTUNSUPPORT       ((uint32_t)0x00000000U)          /* Asynchronous Interrupt not Support */

/* Suspend/Resume Support */
#define SDMMC_SUSRESSUPPORT         (SDMMC_CFG2_SRS)            /* Suspend/Resume Support  */
#define SDMMC_SUSRESUNSUPPORT       ((uint32_t)0x00000000U)     /* Suspend/Resume not Support */

/* SDMA Support */
#define SDMMC_SDMASUPPORT         (SDMMC_CFG2_SDMA)            /* SDMA Support  */
#define SDMMC_SDMAUNSUPPORT       ((uint32_t)0x00000000U)      /* SDMA not Support */

/* High Speed Support */
#define SDMMC_HSSUPPORT         (SDMMC_CFG2_HS)            /* High Speed Support  */
#define SDMMC_HSUNSUPPORT       ((uint32_t)0x00000000U)      /* High Speed not Support */

/* ADMA2 Support */
#define SDMMC_ADMA2SUPPORT         (SDMMC_CFG2_ADMA2)            /* ADMA2 Support  */
#define SDMMC_ADMA2UNSUPPORT       ((uint32_t)0x00000000U)    /* ADMA2 not Support */

/* 8-bit Support for Embedded Device */
#define SDMMC_EMBEDDEDSUPPORT         (SDMMC_CFG2_EMBUS)            /* 8-bit Support for Embedded Device  */
#define SDMMC_EMBEDDEDUNSUPPORT       ((uint32_t)0x00000000U)    /* 8-bit not Support for Embedded Device */

/* Use Tuning for SDR50 */
#define SDMMC_SDR50TUNING         (SDMMC_CFG3_UTFSDR50)      /* Use Tuning for SDR50  */
#define SDMMC_SDR50UNTUNING       ((uint32_t)0x00000000U)    /* Not use Tuning for SDR50 */

/* Manual tuning sdclk output */
#define SDMMC_MANUALTUNOUT_EN         (SDMMC_DLYCTRL_OTDE)      /* Output tap Delay Enable  */
#define SDMMC_MANUALTUNOUT_DELAYMASK  (SDMMC_DLYCTRL_OTDS)      /* Output Tap Delay Select */

/* Manual tuning rclk input */
#define SDMMC_MANUALTUNGATE_EN       (SDMMC_DLYCTRL_ITCW)      /* Input Tap Change Window  */
#define SDMMC_MANUALTUNIN_EN         (SDMMC_DLYCTRL_ITDE)      /* Input tap Delay Enable  */
#define SDMMC_MANUALTUNIN_DELAYMASK  (SDMMC_DLYCTRL_ITDS)      /* Input Tap Delay Select */

/* Sampling Clock Select */
#define SDHOST_SAMPCLKSEL             (SDHOST_CTRLSTS_SCS)      /* Sampling Clock Select  */
#define SDHOST_AUTOTUNE               (SDHOST_CTRLSTS_ETUN)     /* Execute Tuning  */


/** SDMMC CFG1 register bit offset define **/
#define SDMMC_CFG1_BCLKF_OFFSET             (REG_BIT14_OFFSET )  /* Base Clock Frequency for SD Clock */
#define SDMMC_CFG1_TCNT_OFFSET              (REG_BIT1_OFFSET )   /* Tuning Count */

/** SDMMC PVxCTRL register bit offset define **/
#define SDMMC_PV0CTRL_CLKFS_OFFSET             (REG_BIT13_OFFSET )  /* SDCLK Frequency Select Value */

/**********        SDHOST register                     ***********/
/* Maximum block count can be set one time */
#define SDHOST_MAX_BLOCK_COUNT  (SDHOST_BLKCFG_CNT >> REG_BIT16_OFFSET)
#define SDHOST_BLOCK_COUNT_OFFSET (REG_BIT16_OFFSET )

/* SDHOST TMODE register */
#define SDHOST_TMODE_DMADISABLE          ((uint32_t)0x00000000U )  /* DMA Disable */
#define SDHOST_TMODE_DMAENABLE           (SDHOST_TMODE_DMAE )      /* DMA Enable  */

#define SDHOST_TMODE_BLOCKCNTDISABLE     ((uint32_t)0x00000000U )  /* DMA Disable */
#define SDHOST_TMODE_BLOCKCNTENABLE      (SDHOST_TMODE_BLOCKCNTE ) /* DMA Enable  */

#define SDHOST_TMODE_NOACMDEN            ((uint32_t)0x00000000U)   /* No Auto CMD enable */
#define SDHOST_TMODE_AC12EN              (SDHOST_TMODE_AUTOCMDE_0) /* Auto CMD12 enable */
#define SDHOST_TMODE_AC23EN              (SDHOST_TMODE_AUTOCMDE_1) /* Auto CMD23 enable */

#define SDHOST_TMODE_DATDIR_WRITE        ((uint32_t)0x00000000U )  /* Data Transfer Direction Select write */
#define SDHOST_TMODE_DATDIR_READ         (SDHOST_TMODE_DATDIR )    /* Data Transfer Direction Select read  */

#define SDHOST_TMODE_SINGLEBLK           ((uint32_t)0x00000000 )   /* Single Block Select  */
#define SDHOST_TMODE_MULTIBLK            (SDHOST_TMODE_BLKSEL )    /* Multi Block Select */


/* Transfer flag mask. */
enum
{
    SDHOST_EnableDmaFlag = SDHOST_TMODE_DMAE, /* Enable DMA. */

    SDHOST_CommandTypeSuspendFlag = SDHOST_TMODE_TYPE_0, /* Suspend command. */
    SDHOST_CommandTypeResumeFlag  = SDHOST_TMODE_TYPE_1, /* Resume command. */
    SDHOST_CommandTypeAbortFlag   = SDHOST_TMODE_TYPE, /* Abort command. */

    SDHOST_EnableBlockCountFlag    = SDHOST_TMODE_BLOCKCNTE,   /* Enable block count. */
    SDHOST_EnableAutoCommand12Flag = SDHOST_TMODE_AUTOCMDE_0, /* Enable auto CMD12. */
    SDHOST_DataReadFlag            = SDHOST_TMODE_DATDIR, /* Enable data read. */
    SDHOST_MultipleBlockFlag       = SDHOST_TMODE_BLKSEL, /* Multiple block data read/write. */
    SDHOST_EnableAutoCommand23Flag = SDHOST_TMODE_AUTOCMDE_1, /* Enable auto CMD23. */

    SDHOST_ResponseLength136Flag    = SDHOST_TMODE_RTYPESEL_0, /* 136-bit response length. */
    SDHOST_ResponseLength48Flag     = SDHOST_TMODE_RTYPESEL_1, /* 48-bit response length. */
    SDHOST_ResponseLength48BusyFlag = SDHOST_TMODE_RTYPESEL, /* 48-bit response length with busy status. */

    SDHOST_EnableCrcCheckFlag   = SDHOST_TMODE_CRCCK, /* Enable CRC check. */
    SDHOST_EnableIndexCheckFlag = SDHOST_TMODE_INDEXCK, /* Enable index check. */
    SDHOST_DataPresentFlag      = SDHOST_TMODE_DPRESEL, /* Data present flag. */
};

#define SDHOST_CMD_INDEX_OFFSET             (REG_BIT24_OFFSET )  /* CMD index */

#define SDHOST_BOOTDUMMY    ((uint32_t)0x5555AAAAU)  /* dummy data */

/* SDHOST capability register */
#define SDHOST_CAP0_SLOTTYPE_MASK             (SDHOST_CAP0STS_STYP )  /* Slot Type */
#define SDHOST_CAP0_SLOTTYPE_OFFSET           (REG_BIT30_OFFSET )     /* Slot Type */

#define SDHOST_CAP0_ASYNCINT_MASK             (SDHOST_CAP0STS_ASYNCINT )  /* Asynchronous Interrupt Support */
#define SDHOST_CAP0_ASYNCINT_OFFSET           (REG_BIT29_OFFSET )  /* Asynchronous Interrupt Support */

#define SDHOST_CAP0_VS33_MASK             (SDHOST_CAP0STS_VS33 )  /* Voltage Support 3.3V */
#define SDHOST_CAP0_VS33_OFFSET           (REG_BIT24_OFFSET )  /* Voltage Support 3.3V */

#define SDHOST_CAP0_SRS_MASK             (SDHOST_CAP0STS_SRS )  /* Suspend / Resume Support */
#define SDHOST_CAP0_SRS_OFFSET           (REG_BIT23_OFFSET )  /* Suspend / Resume Support */

#define SDHOST_CAP0_SDMA_MASK             (SDHOST_CAP0STS_SDMA )  /* SDMA Support */
#define SDHOST_CAP0_SDMA_OFFSET           (REG_BIT22_OFFSET )  /* SDMA Support */

#define SDHOST_CAP0_HS_MASK             (SDHOST_CAP0STS_HS )  /* High Speed Support */
#define SDHOST_CAP0_HS_OFFSET           (REG_BIT21_OFFSET )  /* High Speed Support */

#define SDHOST_CAP0_ADMA2_MASK             (SDHOST_CAP0STS_ADMA2 )  /* ADMA2 Support */
#define SDHOST_CAP0_ADMA2_OFFSET           (REG_BIT19_OFFSET )  /* ADMA2 Support */

#define SDHOST_CAP0_EMBUS_MASK             (SDHOST_CAP0STS_EMBUS )  /* Extended Media Bus Support */
#define SDHOST_CAP0_EMBUS_OFFSET           (REG_BIT18_OFFSET )  /* Extended Media Bus Support */

#define SDHOST_CAP0_MBL_MASK             (SDHOST_CAP0STS_MBL )  /* Max Block Length */
#define SDHOST_CAP0_MBL_OFFSET           (REG_BIT16_OFFSET )  /* Max Block Length */

#define SDHOST_CAP0_BCLKF_MASK             (SDHOST_CAP0STS_BCLKF )  /* Base Clock Frequency for SD Clock */
#define SDHOST_CAP0_BCLKF_OFFSET           (REG_BIT8_OFFSET )  /* Base Clock Frequency for SD Clock */

#define SDHOST_CAP0_TCLKU_MASK             (SDHOST_CAP0STS_TCLKU )  /* Timeout Clock Unit */
#define SDHOST_CAP0_TCLKU_OFFSET           (REG_BIT7_OFFSET )  /* Timeout Clock Unit */

#define SDHOST_CAP1_SPIBMOD_MASK             (SDHOST_CAP1STS_SPIBMOD )  /* SPI block mode */
#define SDHOST_CAP1_SPIBMOD_OFFSET           (REG_BIT25_OFFSET )  /* SPI block mode */

#define SDHOST_CAP1_SPIMOD_MASK             (SDHOST_CAP1STS_SPIMOD )  /* SPI mode */
#define SDHOST_CAP1_SPIMOD_OFFSET           (REG_BIT24_OFFSET )  /* SPI mode */

#define SDHOST_CAP1_UTFSDR50_MASK             (SDHOST_CAP1STS_UTFSDR50 )  /* Use Tuning for SDR50 */
#define SDHOST_CAP1_UTFSDR50_OFFSET           (REG_BIT13_OFFSET )  /* Use Tuning for SDR50 */

#define SDHOST_CAP1_DDR50_MASK             (SDHOST_CAP1STS_DDR50 )  /* DDR50 Support */
#define SDHOST_CAP1_DDR50_OFFSET           (REG_BIT2_OFFSET )  /* DDR50 Support */

#define SDHOST_CAP1_SDR104_MASK             (SDHOST_CAP1STS_SDR104 )  /* SDR104 Support */
#define SDHOST_CAP1_SDR104_OFFSET           (REG_BIT1_OFFSET )  /* SDR104 Support */

#define SDHOST_CAP1_SDR50_MASK             (SDHOST_CAP1STS_SDR50 )  /* SDR50 Support */

/* SDHOST preset value register */
#define SDHOST_PV0_DSCLKFS_MASK             (SDHOST_PV0STS_CLKFS_DS )  /* SDCLK Frequency Select Value for Default Speed */
#define SDHOST_PV0_DSCLKFS_OFFSET           (REG_BIT16_OFFSET )  /* SDCLK Frequency Select Value for Default Speed */

#define SDHOST_PV0_INITCLKFS_MASK             (SDHOST_PV0STS_CLKFS_INIT )  /* SDCLK Frequency Select Value for Initialization */

#define SDHOST_PV1_SDR12CLKFS_MASK             (SDHOST_PV1STS_CLKFS_SDR12 )  /* SDCLK Frequency Select Value for SDR12*/
#define SDHOST_PV1_SDR12CLKFS_OFFSET           (REG_BIT16_OFFSET )  /* SDCLK Frequency Select Value for SDR12 */

#define SDHOST_PV1_HSCLKFS_MASK             (SDHOST_PV1STS_CLKFS_HS )  /* SDCLK Frequency Select Value for High Speed */

#define SDHOST_PV2_SDR50CLKFS_MASK             (SDHOST_PV2STS_CLKFS_SDR50 )  /* SDCLK Frequency Select Value for SDR50*/
#define SDHOST_PV2_SDR50CLKFS_OFFSET           (REG_BIT16_OFFSET )  /* SDCLK Frequency Select Value for SDR50 */

#define SDHOST_PV2_SDR25CLKFS_MASK             (SDHOST_PV2STS_CLKFS_SDR25 )  /* SDCLK Frequency Select Value for SDR25 */

#define SDHOST_PV3_DDR50CLKFS_MASK             (SDHOST_PV3STS_CLKFS_DDR50 )  /* SDCLK Frequency Select Value for DDR50*/
#define SDHOST_PV3_DDR50CLKFS_OFFSET           (REG_BIT16_OFFSET )  /* SDCLK Frequency Select Value for DDR50 */

#define SDHOST_PV3_SDR104CLKFS_MASK             (SDHOST_PV3STS_CLKFS_SDR104 )  /* SDCLK Frequency Select Value for SDR104 */

/* boot config */
#define SDHOST_BOOTMODENORMAL             ((uint32_t)0x00000000U )   /* Normal boot */
#define SDHOST_BOOTMODEALIERNATIVE        (SDHOST_CTRL1_BOOTINALT )  /* Alternative boot */

#define SDHOST_BOOTNOACKCHECK             ((uint32_t)0x00000000U )   /* Boot Ack Not Check */
#define SDHOST_BOOTACKCHECK               (SDHOST_CTRL1_BOOTACKC )  /* Boot Ack Check */


/* ADMA2 Descriptor */
/* The alignment size for ADDRESS field in ADMA2's descriptor. */
#define SDHOST_ADMA2_ADDRESS_ALIGN (4U)
/* The alignment size for LENGTH filed in ADMA2's descriptor. */
#define SDHOST_ADMA2_LENGTH_ALIGN (4U)

/* ADMA2 descriptor table:
 * |----------------|---------------|-------------|--------------------------|
 * | Address field  |     Length    | Reserved    |         Attribute        |
 * |----------------|---------------|-------------|--------------------------|
 * |63            32|31           16|15         06|05  |04  |03|02 |01 |00   |
 * |----------------|---------------|-------------|----|----|--|---|---|-----|
 * | 32-bit address | 16-bit length | 0000000000  |Act2|Act1| 0|Int|End|Valid|
 * |----------------|---------------|-------------|----|----|--|---|---|-----|
 *
 * ADMA2 action table:
 * | Act2 | Act1 |     Comment     | Operation                                                         |
 * |------|------|-----------------|-------------------------------------------------------------------|
 * |   0  |   0  | No op           | Don't care                                                        |
 * |------|------|-----------------|-------------------------------------------------------------------|
 * |   0  |   1  | Reserved        | Read this line and go to next one                                 |
 * |------|------|-----------------|-------------------------------------------------------------------|
 * |   1  |   0  | Transfer data   | Transfer data with address and length set in this descriptor line |
 * |------|------|-----------------|-------------------------------------------------------------------|
 * |   1  |   1  | Link descriptor | Link to another descriptor                                        |
 * |------|------|-----------------|-------------------------------------------------------------------|
 */
/**********************************tables below are created only for Doxygen***********************************/
/* The bit shift for LENGTH field in ADMA2's descriptor.
 *
 * <table>
 * <caption>ADMA2 descriptor table</caption>
 * <tr><th>Address field    <th>Length         <th>Reserved     <th colspan="6">Attribute
 * <tr><td>63 32            <td>31 16          <td>15 06        <td>05   <td>04   <td>03  <td>02  <td>01  <td>00
 * <tr><td>32-bit address   <td>16-bit length  <td>0000000000   <td>Act2 <td>Act1 <td>0   <td>Int <td>End <td>Valid
 *</table>
 *
 * <table>
 * <caption>ADMA2 action</caption>
 * <tr><th>Act2   <th>Act1   <th>Comment          <th>Operation
 * <tr><td> 0     <td>0      <td>No op            <td>Don't care
 * <tr><td> 0     <td>1      <td> Reserved        <td> Read this line and go to next one
 * <tr><td> 1     <td>0      <td>Transfer data    <td>Transfer data with address and length set in this descriptor line
 * <tr><td> 1     <td>1      <td>Link descriptor  <td>Link to another descriptor
 * </table>
 */
#define SDHOST_ADMA2_DESCRIPTOR_LENGTH_SHIFT (16U)
/* The bit mask for LENGTH field in ADMA2's descriptor. */
#define SDHOST_ADMA2_DESCRIPTOR_LENGTH_MASK (0xFFFFU)
/* The maximum value of LENGTH field in ADMA2's descriptor. */
#define SDHOST_ADMA2_DESCRIPTOR_MAX_LENGTH_PER_ENTRY (SDHOST_ADMA2_DESCRIPTOR_LENGTH_MASK - 3U)

/* ADMA2 descriptor control and status mask. */
enum
{
    SDHOST_Adma2DescriptorValidFlag     = (1U << 0U), /* Valid flag. */
    SDHOST_Adma2DescriptorEndFlag       = (1U << 1U), /* End flag. */
    SDHOST_Adma2DescriptorInterruptFlag = (1U << 2U), /* Interrupt flag. */
    SDHOST_Adma2DescriptorActivity1Flag = (1U << 4U), /* Activity 1 mask. */
    SDHOST_Adma2DescriptorActivity2Flag = (1U << 5U), /* Activity 2 mask. */

    SDHOST_Adma2DescriptorTypeNop      = (SDHOST_Adma2DescriptorValidFlag), /* No operation. */
    SDHOST_Adma2DescriptorTypeReserved = (SDHOST_Adma2DescriptorActivity1Flag | SDHOST_Adma2DescriptorValidFlag),
    /* Reserved. */
    SDHOST_Adma2DescriptorTypeTransfer = (SDHOST_Adma2DescriptorActivity2Flag | SDHOST_Adma2DescriptorValidFlag),
    /* Transfer type. */
    SDHOST_Adma2DescriptorTypeLink = (SDHOST_Adma2DescriptorActivity1Flag | SDHOST_Adma2DescriptorActivity2Flag |
                                      SDHOST_Adma2DescriptorValidFlag), /* Link type. */
};

/* ADMA descriptor configuration flag. */
enum
{
    SDHOST_AdmaDescriptorSingleFlag = 0U,
    /* Try to finish the transfer in a single ADMA descriptor. If transfer size is bigger than one
       ADMA descriptor's ability, new another descriptor for data transfer. */
    SDHOST_AdmaDescriptorMultipleFlag = 1U, 
    /* Create multiple ADMA descriptors within the ADMA table, this is used for
         mmc boot mode specifically, which need to modify the ADMA descriptor on the fly, 
         so the flag should be used combining with stop at block gap feature. */
};


/* Data transfer width. */
typedef enum
{
    SDHOST_DataBusWidth1Bit = 0U, /* 1-bit mode */
    SDHOST_DataBusWidth4Bit = 1U, /* 4-bit mode */
    SDHOST_DataBusWidth8Bit = 2U, /* 8-bit mode */
} SDHOST_BusWidth;

/* Wakeup event. */
enum
{
    SDHOST_WakeupEventOnCardInt    = SDHOST_CTRL1_INTWKUP, /* Wakeup on card interrupt. */
    SDHOST_WakeupEventOnCardInsert = SDHOST_CTRL1_INSTWKUP, /* Wakeup on card insertion. */
    SDHOST_WakeupEventOnCardRemove = SDHOST_CTRL1_RMVWKUP,  /* Wakeup on card removal. */
    SDHOST_WakeupEventsAll =
        (SDHOST_WakeupEventOnCardInt | SDHOST_WakeupEventOnCardInsert | SDHOST_WakeupEventOnCardRemove),
    /* All wakeup events */
};

/* SDIO control flag. */
enum
{
    SDHOST_StopAtBlockGapFlag      = SDHOST_CTRL1_SABGREQ,   /* Stop at block gap. */
    SDHOST_ReadWaitControlFlag     = SDHOST_CTRL1_RWAITCTRL, /* Read wait control. */
    SDHOST_InterruptAtBlockGapFlag = SDHOST_CTRL1_INTATBG,   /* Interrupt at block gap. */
};


/* Force event bit position. */
enum
{
    SDHOST_ForceEventAutoCommand12NotExecuted = SDHOST_STSFE_ACMD12NE, /* Auto CMD12 not executed error. */
    SDHOST_ForceEventAutoCommand12Timeout    = SDHOST_STSFE_ACMDTE,  /* Auto CMD12 timeout error. */
    SDHOST_ForceEventAutoCommand12CrcError   = SDHOST_STSFE_ACMDCRCE,   /* Auto CMD12 CRC error. */
    SDHOST_ForceEventAutoCommandEndBitError  = SDHOST_STSFE_ACMDEBE,  /* Auto CMD end bit error. */
    SDHOST_ForceEventAutoCommand12IndexError = SDHOST_STSFE_ACMDINXE,   /* Auto CMD12 index error. */
    SDHOST_ForceEventAutoCommand12NotIssued = SDHOST_STSFE_ACMD12E, /* Auto CMD12 not issued error. */
    SDHOST_ForceEventCommandTimeout         = SDHOST_STSFE_CTE,      /* Command timeout error. */
    SDHOST_ForceEventCommandCrcError        = SDHOST_STSFE_CCRCE,       /* Command CRC error. */
    SDHOST_ForceEventCommandEndBitError     = SDHOST_STSFE_CEBE,      /* Command end bit error. */
    SDHOST_ForceEventCommandIndexError      = SDHOST_STSFE_CINXE,       /* Command index error. */
    SDHOST_ForceEventDataTimeout            = SDHOST_STSFE_DTE,      /* Data timeout error. */
    SDHOST_ForceEventDataCrcError           = SDHOST_STSFE_DCRCE,       /* Data CRC error. */
    SDHOST_ForceEventDataEndBitError        = SDHOST_STSFE_DEBE,      /* Data end bit error. */
    SDHOST_ForceEventAutoCommand12Error     = SDHOST_STSFE_ACMDE,     /* Auto CMD12 error. */
    SDHOST_ForceEventAdmaError              = SDHOST_STSFE_ADMAE,      /* Adma error. */
};


/* Host SDMA Buffer Size. */
typedef enum
{
    SDHOST_SDMABUFFERSIZE_4KB    = ((uint32_t)0x00000000U),               /* Detect A11. */
    SDHOST_SDMABUFFERSIZE_8KB    = SDHOST_BLKCFG_HDBS_0,      /* Detect A12. */
    SDHOST_SDMABUFFERSIZE_16KB   = SDHOST_BLKCFG_HDBS_1,      /* Detect A13. */
    SDHOST_SDMABUFFERSIZE_32KB   = SDHOST_BLKCFG_HDBS_0 | SDHOST_BLKCFG_HDBS_1,    /* Detect A14. */
    SDHOST_SDMABUFFERSIZE_64KB   = SDHOST_BLKCFG_HDBS_2,      /* Detect A15. */
    SDHOST_SDMABUFFERSIZE_128KB  = SDHOST_BLKCFG_HDBS_2 | SDHOST_BLKCFG_HDBS_0,    /* Detect A16. */
    SDHOST_SDMABUFFERSIZE_256KB  = SDHOST_BLKCFG_HDBS_2 | SDHOST_BLKCFG_HDBS_1,    /* Detect A17. */
    SDHOST_SDMABUFFERSIZE_512KB  = SDHOST_BLKCFG_HDBS,       /* NDetect A18. */
}SDHOST_SDMA_Buffer_Size;

/* card work mode */
typedef enum
{
    SDMMC_DS = 0U,     /* Default Speed */
    SDMMC_HS = 1U,     /* High Speed */
    SDMMC_SDR12 = 2U,  /* SDR12 */
    SDMMC_SDR25 = 3U,  /* SDR25 */
    SDMMC_SDR50 = 4U,  /* SDR50 */
    SDMMC_SDR104 = 5U, /* SDR104 */
    SDMMC_DDR50 = 6U,  /* DDR50 */
    SDMMC_SPI   = 7U,  /* SPI mode */
}SD_ModeConfig;

/* Card detect signal source and test level */
#define SDMMC_CARDDETECT_NORMAL           ((uint32_t)0x00000000U) /* Select SDCD # (normal use)*/
#define SDMMC_CARDDETECT_TEST             (SDHOST_CTRL1_CDSD)     /* Select card detection test level */

#define SDMMC_CARDTESTLEVEL_LOW           ((uint32_t)0x00000000U) /* low level */
#define SDMMC_CARDTESTLEVEL_HIGH          (SDHOST_CTRL1_CDTL)     /* high level  */


/* Private function */
static SDMMC_STS SDMMC_TransferConfig(SDHOST_Module* SDHOSTx, uint32_t transferFlags, uint32_t blockSize, uint32_t blockCount,SDHOST_TMODE_struct *TMODE_struct);
static SDMMC_STS SDMMC_ReceiveCommandResponse(SDHOST_Module* SDHOSTx, SDMMC_CMD *command);
static uint32_t SDMMC_ReadDataPort(SDHOST_Module* SDHOSTx, SDMMC_DATA *data, uint32_t transferredWords);
static ErrorStatus SDMMC_ReadByDataPortBlocking(SDHOST_Module* SDHOSTx, SDMMC_DATA *data);
static uint32_t SDMMC_WriteDataPort(SDHOST_Module* SDHOSTx, SDMMC_DATA *data, uint32_t transferredWords);
static ErrorStatus SDMMC_WriteByDataPortBlocking(SDHOST_Module* SDHOSTx, SDMMC_DATA *data);
SDMMC_STS SDMMC_WaitCommandDone(SDHOST_Module* SDHOSTx, SDMMC_CMD *command, FunctionalState pollingCmdDone);
static SDMMC_STS SDMMC_TransferDataBlocking(SDHOST_Module* SDHOSTx, SDMMC_DATA *data, FunctionalState DMACmd);
void SDMMC_WriteData(SDHOST_Module* SDHOSTx, uint32_t data);
uint32_t SDMMC_ReadData(SDHOST_Module* SDHOSTx);


/* Public function */
void SDMMC_DeInit(SDMMC_Module* SDMMCx);
ErrorStatus SDMMC_WrapperConfig(SDMMC_Module* SDMMCx, SDMMC_WrapperType *SDMMC_WrapperParam);
void SDMMC_StructWrapperInit(SDMMC_WrapperType *SDMMC_WrapperStruct);
ErrorStatus SDMMC_SoftWareReset(SDHOST_Module* SDHOSTx, uint32_t LineMask);
void SDMMC_SendCommand(SDHOST_Module* SDHOSTx, SDMMC_CMD *command,const SDHOST_TMODE_struct *TMODE_struct);
void SDMMC_GetCapability(SDHOST_Module* SDHOSTx, SDHOST_capability *capability);
void SDMMC_GetPresetvalue(SDHOST_Module* SDHOSTx, SDHOST_presetvalue *presetvalue);
void SDMMC_EnableSDCLK(SDHOST_Module* SDHOSTx, FunctionalState Cmd);
SDMMC_STS SDMMC_WaitSDCLKStable(SDHOST_Module* SDHOSTx);
SDMMC_STS SDMMC_SetSdClock(SDHOST_Module* SDHOSTx, FunctionalState PresetCmd, uint32_t SDClock_KHz);
void SDMMC_ConfigemmcBoot(SDHOST_Module* SDHOSTx, const SDHOST_boot_config *config);
static SDMMC_STS SDMMC_ConfigInternalDma(SDHOST_Module* SDHOSTx, SDHOST_ADMAconfig *dmaConfig, const uint32_t *dataAddr, 
                                  FunctionalState enAutoCmd23,SDHOST_TMODE_struct *TMODE_struct);
static SDMMC_STS SDMMC_SetAdmaTableConfig(SDHOST_Module* SDHOSTx,SDHOST_ADMAconfig *dmaConfig,
                                  SDMMC_DATA *dataConfig, SDHOST_TMODE_struct *TMODE_struct);
SDMMC_STS SDMMC_TransferBlocking(SDHOST_Module* SDHOSTx, SDHOST_ADMAconfig *dmaConfig, SDMMC_Transfer *transfer,SDHOST_TMODE_struct *TMODE_struct);                                  
void SDMMC_EnableManualTuningOut(SDMMC_Module* SDMMCx, uint32_t delay,FunctionalState cmd);
void SDMMC_EnableManualTuningIN(SDMMC_Module* SDMMCx, uint32_t delay,FunctionalState cmd);
void SDMMC_FixedSampleClock(SDHOST_Module* SDHOSTx);
void SDMMC_EnableAutoTuning(SDHOST_Module* SDHOSTx, FunctionalState cmd);
void SDMMC_ConfigInt(SDHOST_Module* SDHOSTx, uint32_t SDHOST_Flag, FunctionalState Cmd);
void SDMMC_EnableFlagStatus(SDHOST_Module* SDHOSTx, uint32_t SDHOST_Flag, FunctionalState Cmd);
FlagStatus SDMMC_GetEnableFlagStatus(SDHOST_Module* SDHOSTx, uint32_t SDHOST_Flag);
FlagStatus SDMMC_GetFlagStatus(SDHOST_Module* SDHOSTx, uint32_t SDHOST_Flag);
void SDMMC_ClrFlag(SDHOST_Module* SDHOSTx, uint32_t SDHOST_Flag);
void SDMMC_EnableForceEvent(SDHOST_Module* SDHOSTx, uint32_t SDHOST_Flag, FunctionalState Cmd);
FlagStatus SDMMC_GetPresentFlagStatus(SDHOST_Module* SDHOSTx, uint32_t SDHOST_PreFlag);
FlagStatus SDMMC_GetACMDErrorStatusFlag(SDHOST_Module* SDHOSTx, uint32_t SDHOST_ACMDFlag);
FlagStatus SDMMC_GetADMAErrorStatusFlag(SDHOST_Module* SDHOSTx, uint32_t SDHOST_ADMAFlag);
void SDMMC_EnableHWReset(SDHOST_Module* SDHOSTx, FunctionalState Cmd);
void SDMMC_ConfigWorkMode(SDHOST_Module* SDHOSTx, SD_ModeConfig mode);
void SDMMC_ConfigBusWidth(SDHOST_Module* SDHOSTx, SDHOST_BusWidth Width);
void SDMMC_EnableWakeupEvent(SDHOST_Module* SDHOSTx,uint32_t Wakeupevent, FunctionalState Cmd);
void SDMMC_EnableSdioControl(SDHOST_Module* SDHOSTx,uint32_t Sdioflag, FunctionalState Cmd);
void SDMMC_EnableContinueRequest(SDHOST_Module* SDHOSTx);
void SDMMC_EnableMmcBoot(SDHOST_Module* SDHOSTx, FunctionalState Cmd);
void SDMMC_EnableVolSwitch(SDHOST_Module* SDHOSTx, FunctionalState Cmd);
void SDMMC_EnablePower(SDHOST_Module* SDHOSTx, FunctionalState Cmd);
void SDMMC_ConfigSDMABufferSize(SDHOST_Module* SDHOSTx, SDHOST_SDMA_Buffer_Size Size);
void SDMMC_TModeStructInit(SDHOST_TMODE_struct *TMODE_struct);
void SDMMC_ConfigCardDetectSignal(SDHOST_Module* SDHOSTx, uint32_t Signalsource, uint32_t Signallevel);
void SDMMC_EnableLED(SDHOST_Module* SDHOSTx, FunctionalState Cmd);
void SDMMC_EnableAsyncInt(SDHOST_Module* SDHOSTx, FunctionalState Cmd);
void SDMMC_ConfigDATATimeoutValue(SDHOST_Module* SDHOSTx, uint32_t Count);


#ifdef __cplusplus
}
#endif

#endif /* __N32H76X_78X_SDMMC_H__ */


