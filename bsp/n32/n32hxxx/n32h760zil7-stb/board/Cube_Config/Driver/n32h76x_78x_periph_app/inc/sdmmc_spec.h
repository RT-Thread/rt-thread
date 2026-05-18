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
 * @file sdmmc_spec.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __SDMMC_SPEC_H__
#define __SDMMC_SPEC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define swap_uint32( val) (((val << 24) & 0xff000000) | ((val << 8) & 0x00ff0000) | ((val >> 8) & 0x0000ff00) | ((val >> 24) & 0x000000ff))
/* mask convert  */
#define SDMMC_MASK(bit) (1UL << (bit))

/* SD/mmccard status */
typedef enum
{
    Status_Success = 1,    /* Generic status for Success */
    Status_Fail,           /* Generic status for Fail */
    Status_PollingCardIdleFailed, /* polling mmccard idle status failed */
    Status_CardStatusIdle, /* mmccard idle */
    Status_CardStatusBusy, /* mmccard busy */
    Status_CardOutOfRange, /* Out of range access. */
    Status_CardNotSupportYet, /* Haven't supported. */
    Status_CardSwitchFailed, /* Switch command failed */
}Status_card;

/* Card status bit in R1 */
enum
{
    SDMMC_R1OutOfRangeFlag                  = 31, /* Out of range status bit */
    SDMMC_R1AddressErrorFlag                = 30, /* Address error status bit */
    SDMMC_R1BlockLengthErrorFlag            = 29, /* Block length error status bit */
    SDMMC_R1EraseSequenceErrorFlag          = 28, /* Erase sequence error status bit */
    SDMMC_R1EraseParameterErrorFlag         = 27, /* Erase parameter error status bit */
    SDMMC_R1WriteProtectViolationFlag       = 26, /* Write protection violation status bit */
    SDMMC_R1CardIsLockedFlag                = 25, /* Card locked status bit */
    SDMMC_R1LockUnlockFailedFlag            = 24, /* lock/unlock error status bit */
    SDMMC_R1CommandCrcErrorFlag             = 23, /* CRC error status bit */
    SDMMC_R1IllegalCommandFlag              = 22, /* Illegal command status bit */
    SDMMC_R1CardEccFailedFlag               = 21, /* Card ecc error status bit */
    SDMMC_R1CardControllerErrorFlag         = 20, /* Internal card controller error status bit */
    SDMMC_R1ErrorFlag                       = 19, /* A general or an unknown error status bit */
    SDMMC_R1CidCsdOverwriteFlag             = 16, /* Cid/csd overwrite status bit */
    SDMMC_R1WriteProtectEraseSkipFlag       = 15, /* Write protection erase skip status bit */
    SDMMC_R1CardEccDisabledFlag             = 14, /* Card ecc disabled status bit */
    SDMMC_R1EraseResetFlag                  = 13, /* Erase reset status bit */
    SDMMC_R1ReadyForDataFlag                = 8,  /* Ready for data status bit */
    SDMMC_R1SwitchErrorFlag                 = 7,  /* Switch error status bit */
    SDMMC_R1ApplicationCommandFlag          = 5,  /* Application command enabled status bit */
    SDMMC_R1AuthenticationSequenceErrorFlag = 3,  /* error in the sequence of authentication process */
};

/* R1: current state */
#define SDMMC_R1_CURRENT_STATE(x) (((x)&0x00001E00U) >> 9U)

/* CURRENT_STATE filed in R1 */
typedef enum
{
    SDMMC_R1StateIdle        = 0U, /* R1: current state: idle */
    SDMMC_R1StateReady       = 1U, /* R1: current state: ready */
    SDMMC_R1StateIdentify    = 2U, /* R1: current state: identification */
    SDMMC_R1StateStandby     = 3U, /* R1: current state: standby */
    SDMMC_R1StateTransfer    = 4U, /* R1: current state: transfer */
    SDMMC_R1StateSendData    = 5U, /* R1: current state: sending data */
    SDMMC_R1StateReceiveData = 6U, /* R1: current state: receiving data */
    SDMMC_R1StateProgram     = 7U, /* R1: current state: programming */
    SDMMC_R1StateDisconnect  = 8U, /* R1: current state: disconnect */
} sdmmc_r1_current_state_t;

/* MMC card Extended CSD fix version(EXT_CSD_REV in Extended CSD) */
enum
{
    MMC_ExtendedCsdRevision10 = 0U, /* Revision 1.0 */
    MMC_ExtendedCsdRevision11 = 1U, /* Revision 1.1 */
    MMC_ExtendedCsdRevision12 = 2U, /* Revision 1.2 */
    MMC_ExtendedCsdRevision13 = 3U, /* Revision 1.3 MMC4.3*/
    MMC_ExtendedCsdRevision14 = 4U, /* Revision 1.4 obsolete*/
    MMC_ExtendedCsdRevision15 = 5U, /* Revision 1.5 MMC4.41*/
    MMC_ExtendedCsdRevision16 = 6U, /* Revision 1.6 MMC4.5*/
    MMC_ExtendedCsdRevision17 = 7U, /* Revision 1.7 MMC5.0 */
};

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

/* MMC card product name length united as bytes. */
#define MMC_PRODUCT_NAME_BYTES (6U)
/* MMC card CID register. */
typedef struct
{
    uint8_t manufacturerID;                      /* Manufacturer ID */
    uint16_t applicationID;                      /* OEM/Application ID */
    uint8_t productName[MMC_PRODUCT_NAME_BYTES]; /* Product name */
    uint8_t productVersion;                      /* Product revision */
    uint32_t productSerialNumber;                /* Product serial number */
    uint8_t manufacturerData;                    /* Manufacturing date */
} mmc_cid;

/* SD card CSD register flags */
enum
{
    SD_CsdReadBlockPartialFlag         = (1U << 0U),  /* Partial blocks for read allowed [79:79] */
    SD_CsdWriteBlockMisalignFlag       = (1U << 1U),  /* Write block misalignment [78:78] */
    SD_CsdReadBlockMisalignFlag        = (1U << 2U),  /* Read block misalignment [77:77] */
    SD_CsdDsrImplementedFlag           = (1U << 3U),  /* DSR implemented [76:76] */
    SD_CsdEraseBlockEnabledFlag        = (1U << 4U),  /* Erase single block enabled [46:46] */
    SD_CsdWriteProtectGroupEnabledFlag = (1U << 5U),  /* Write protect group enabled [31:31] */
    SD_CsdWriteBlockPartialFlag        = (1U << 6U),  /* Partial blocks for write allowed [21:21] */
    SD_CsdFileFormatGroupFlag          = (1U << 7U),  /* File format group [15:15] */
    SD_CsdCopyFlag                     = (1U << 8U),  /* Copy flag [14:14] */
    SD_CsdPermanentWriteProtectFlag    = (1U << 9U),  /* Permanent write protection [13:13] */
    SD_CsdTemporaryWriteProtectFlag    = (1U << 10U), /* Temporary write protection [12:12] */
};

/* MMC card CSD register flags */
enum
{
    MMC_CsdReadBlockPartialFlag         = (1U << 0U),  /* Partial blocks for read allowed */
    MMC_CsdWriteBlockMisalignFlag       = (1U << 1U),  /* Write block misalignment */
    MMC_CsdReadBlockMisalignFlag        = (1U << 2U),  /* Read block misalignment */
    MMC_CsdDsrImplementedFlag           = (1U << 3U),  /* DSR implemented */
    MMC_CsdWriteProtectGroupEnabledFlag = (1U << 4U),  /* Write protect group enabled */
    MMC_CsdWriteBlockPartialFlag        = (1U << 5U),  /* Partial blocks for write allowed */
    MMC_ContentProtectApplicationFlag   = (1U << 6U),  /* Content protect application */
    MMC_CsdFileFormatGroupFlag          = (1U << 7U),  /* File format group */
    MMC_CsdCopyFlag                     = (1U << 8U),  /* Copy flag */
    MMC_CsdPermanentWriteProtectFlag    = (1U << 9U),  /* Permanent write protection */
    MMC_CsdTemporaryWriteProtectFlag    = (1U << 10U), /* Temporary write protection */
};

/* SD/MMC mmccard common commands */
typedef enum
{
    SDMMC_GoIdleState        = 0U,  /* Go Idle State */
    SDMMC_AllSendCid         = 2U,  /* All Send CID */
    SDMMC_SetDsr             = 4U,  /* Set DSR */
    SDMMC_SelectCard         = 7U,  /* Select mmccard */
    SDMMC_SendCsd            = 9U,  /* Send CSD */
    SDMMC_SendCid            = 10U, /* Send CID */
    SDMMC_StopTransmission   = 12U, /* Stop Transmission */
    SDMMC_SendStatus         = 13U, /* Send Status */
    SDMMC_GoInactiveState    = 15U, /* Go Inactive State */
    SDMMC_SetBlockLength     = 16U, /* Set Block Length */
    SDMMC_ReadSingleBlock    = 17U, /* Read Single Block */
    SDMMC_ReadMultipleBlock  = 18U, /* Read Multiple Block */
    SDMMC_SetBlockCount      = 23U, /* Set Block Count */
    SDMMC_WriteSingleBlock   = 24U, /* Write Single Block */
    SDMMC_WriteMultipleBlock = 25U, /* Write Multiple Block */
    SDMMC_ProgramCsd         = 27U, /* Program CSD */
    SDMMC_SetWriteProtect    = 28U, /* Set Write Protect */
    SDMMC_ClearWriteProtect  = 29U, /* Clear Write Protect */
    SDMMC_SendWriteProtect   = 30U, /* Send Write Protect */
    SDMMC_Erase              = 38U, /* Erase */
    SDMMC_LockUnlock         = 42U, /* Lock Unlock */
    SDMMC_ApplicationCommand = 55U, /* Send Application Command */
    SDMMC_GeneralCommand     = 56U, /* General Purpose Command */
    SDMMC_ReadOcr            = 58U, /* Read OCR */
} sdmmc_command_t;

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

/* MMC card CSD register. */
typedef struct _mmc_csd
{
    uint8_t csdStructureVersion;        /* CSD structure [127:126] */
    uint8_t systemSpecificationVersion; /* System specification version [125:122] */
    uint8_t dataReadAccessTime1;        /* Data read access-time 1 [119:112] */
    uint8_t dataReadAccessTime2;        /* Data read access-time 2 in CLOCK cycles (NSAC*100) [111:104] */
    uint8_t transferSpeed;              /* Max. bus clock frequency [103:96] */
    uint16_t cardCommandClass;          /* card command classes [95:84] */
    uint8_t readBlockLength;            /* Max. read data block length [83:80] */
    uint16_t flags;                     /* Contain flags in _mmc_csd_flag */
    uint16_t deviceSize;                /* Device size [73:62] */
    uint8_t readCurrentVddMin;          /* Max. read current @ VDD min [61:59] */
    uint8_t readCurrentVddMax;          /* Max. read current @ VDD max [58:56] */
    uint8_t writeCurrentVddMin;         /* Max. write current @ VDD min [55:53] */
    uint8_t writeCurrentVddMax;         /* Max. write current @ VDD max [52:50] */
    uint8_t deviceSizeMultiplier;       /* Device size multiplier [49:47] */
    uint8_t eraseGroupSize;             /* Erase group size [46:42] */
    uint8_t eraseGroupSizeMultiplier;   /* Erase group size multiplier [41:37] */
    uint8_t writeProtectGroupSize;      /* Write protect group size [36:32] */
    uint8_t defaultEcc;                 /* Manufacturer default ECC [30:29] */
    uint8_t writeSpeedFactor;           /* Write speed factor [28:26] */
    uint8_t maxWriteBlockLength;        /* Max. write data block length [25:22] */
    uint8_t fileFormat;                 /* File format [11:10] */
    uint8_t eccCode;                    /* ECC code [9:8] */
} mmc_csd_t;

/* SD card SCR register flags */
enum
{
    SD_ScrDataStatusAfterErase = (1U << 0U), /* Data status after erases [55:55] */
    SD_ScrSdSpecification3     = (1U << 1U), /* Specification version 3.00 or higher [47:47]*/
};

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


/*  MMC card Extended CSD register (unit: byte). */
typedef struct _mmc_extended_csd
{
    /*uint8_t SecureRemoveType;*/             /* secure removal type[16]*/
    /*uint8_t enProductStateAware;*/          /* product state awareness enablement[17]*/
    /*uint32_t maxPreLoadDataSize;*/          /* max preload data size[21-18]*/
    /*uint32_t preLoadDataSize;*/             /* pre-load data size[25-22]*/
    /*uint8_t ffuStatus;*/                    /* FFU status [26]*/
    /*uint8_t modeOperationCode;*/            /* mode operation code[29]*/
    /*uint8_t modeConfig;*/                   /* mode config [30]*/
    uint8_t cacheCtrl;                        /* control to turn on/off cache[33]*/
    /*uint8_t pwroffNotify;*/                 /* power off notification[34]*/
    /*uint8_t packedCmdFailIndex;*/           /* packed cmd fail index [35]*/
    /*uint8_t packedCmdStatus;*/              /* packed cmd status[36]*/
    /*uint32_t contextConfig[4U];*/           /* context configuration[51-37]*/
    /*uint16_t extPartitionAttr;*/            /* extended partitions attribut[53-52]*/
    /*uint16_t exceptEventStatus;*/           /* exception events status[55-54]*/
    /*uint16_t exceptEventControl;*/          /* exception events control[57-56]*/
    /*uint8_t toReleaseAddressedGroup;*/      /* number of group to be released[58]*/
    /*uint8_t class6CmdCtrl;*/                /* class 6 command control[59]*/
    /*uint8_t intTimeoutEmu;*/                /* 1st initiallization after disabling sector size emu[60]*/
    /*uint8_t sectorSize;*/                   /* sector size[61] */
    /*uint8_t sectorSizeEmu;*/                /* sector size emulation[62]*/
    /*uint8_t nativeSectorSize;*/             /* native sector size[63]*/
    /*uint8_t periodWakeup;*/                 /* period wakeup [131]*/
    /*uint8_t tCASESupport;*/                 /* package case temperature is controlled[132]*/
    /*uint8_t productionStateAware;*/         /* production state awareness[133]*/
    /*uint32_t enhanceUsrDataStartAddr;*/     /* enhanced user data start addr [139-136]*/
    /*uint32_t enhanceUsrDataSize;*/          /* enhanced user data area size[142-140]*/
    /*uint32_t generalPartitionSize[3];*/     /* general purpose partition size[154-143]*/
    uint8_t partitionAttribute;               /* partition attribute [156]*/
    /*uint32_t maxEnhanceAreaSize;*/          /* max enhance area size [159-157]*/
    /*uint8_t hpiManagementEn;*/              /* HPI management [161]*/
    /*uint8_t writeReliabilityParameter;*/    /* write reliability parameter register[166] */
    /*uint8_t writeReliabilitySet;*/          /* write reliability setting register[167] */
    /*uint8_t rpmbSizeMult;*/                 /* RPMB size multi [168]*/
    /*uint8_t fwConfig;*/                     /* FW configuration[169]*/
    uint8_t userWP;                           /* user write protect register[171] */
    uint8_t bootPartitionWP;                  /* boot write protect register[173]*/
    uint8_t bootWPStatus;                     /* boot write protect status register[174]*/
    uint8_t highDensityEraseGroupDefinition;  /* High-density erase group definition [175] */
    uint8_t bootDataBusConditions;            /* Boot bus conditions [177] */
    uint8_t bootConfigProtect;                /* Boot config protection [178]*/
    uint8_t partitionConfig;                  /* Boot configuration [179] */
    uint8_t eraseMemoryContent;               /* Erased memory content [181] */
    uint8_t dataBusWidth;                     /* Data bus width mode [183] */
    uint8_t highSpeedTiming;                  /* High-speed interface timing [185] */
    uint8_t powerClass;                       /* Power class [187] */
    uint8_t commandSetRevision;               /* Command set revision [189] */
    uint8_t commandSet;                       /* Command set [191] */
    uint8_t extendecCsdVersion;               /* Extended CSD revision [192] */
    uint8_t csdStructureVersion;              /* CSD structure version [194] */
    uint8_t cardType;                         /* Card Type [196] */
    uint8_t ioDriverStrength;                 /* IO driver strength [197] */
    /*uint8_t OutofInterruptBusyTiming;*/     /* out of interrupt busy timing [198] */
    uint8_t partitionSwitchTimeout;           /* partition switch timing [199] */
    uint8_t powerClass52MHz195V;              /* Power Class for 52MHz @ 1.95V [200] */
    uint8_t powerClass26MHz195V;              /* Power Class for 26MHz @ 1.95V [201] */
    uint8_t powerClass52MHz360V;              /* Power Class for 52MHz @ 3.6V [202] */
    uint8_t powerClass26MHz360V;              /* Power Class for 26MHz @ 3.6V [203] */
    uint8_t minimumReadPerformance4Bit26MHz;  /* Minimum Read Performance for 4bit at 26MHz [205] */
    uint8_t minimumWritePerformance4Bit26MHz; /* Minimum Write Performance for 4bit at 26MHz [206] */
    uint8_t minimumReadPerformance8Bit26MHz4Bit52MHz;
    /* Minimum read Performance for 8bit at 26MHz/4bit @52MHz [207] */
    uint8_t minimumWritePerformance8Bit26MHz4Bit52MHz;
    /* Minimum Write Performance for 8bit at 26MHz/4bit @52MHz [208] */
    uint8_t minimumReadPerformance8Bit52MHz;   /* Minimum Read Performance for 8bit at 52MHz [209] */
    uint8_t minimumWritePerformance8Bit52MHz;  /* Minimum Write Performance for 8bit at 52MHz [210] */
    uint32_t sectorCount;                      /* Sector Count [215:212] */
    /*uint8_t sleepNotificationTimeout;*/      /* sleep notification timeout [216]*/
    uint8_t sleepAwakeTimeout;                 /* Sleep/awake timeout [217] */
    /*uint8_t productionStateAwareTimeout;*/   /* Production state awareness timeout [218]*/
    uint8_t sleepCurrentVCCQ;                  /* Sleep current (VCCQ) [219] */
    uint8_t sleepCurrentVCC;                   /* Sleep current (VCC) [220] */
    uint8_t highCapacityWriteProtectGroupSize; /* High-capacity write protect group size [221] */
    uint8_t reliableWriteSectorCount;          /* Reliable write sector count [222] */
    uint8_t highCapacityEraseTimeout;          /* High-capacity erase timeout [223] */
    uint8_t highCapacityEraseUnitSize;         /* High-capacity erase unit size [224] */
    uint8_t accessSize;                        /* Access size [225] */
    /*uint8_t secureTrimMultiplier;*/          /* secure trim multiplier[229]*/
    /*uint8_t secureEraseMultiplier;*/         /* secure erase multiplier[230]*/
    /*uint8_t secureFeatureSupport;*/          /* secure feature support[231]*/
    /*uint32_t trimMultiplier;*/               /* trim multiplier[232]*/
    uint8_t minReadPerformance8bitAt52MHZDDR;  /* Minimum read performance for 8bit at DDR 52MHZ[234]*/
    uint8_t minWritePerformance8bitAt52MHZDDR; /* Minimum write performance for 8bit at DDR 52MHZ[235]*/
    uint8_t powerClass200MHZVCCQ130VVCC360V;   /* power class for 200MHZ, at VCCQ= 1.3V,VCC=3.6V[236]*/
    uint8_t powerClass200MHZVCCQ195VVCC360V;   /* power class for 200MHZ, at VCCQ= 1.95V,VCC=3.6V[237]*/
    uint8_t powerClass52MHZDDR195V;            /* power class for 52MHZ,DDR at Vcc 1.95V[238]*/
    uint8_t powerClass52MHZDDR360V;            /* power class for 52MHZ,DDR at Vcc 3.6V[239]*/
    /*uint8_t iniTimeoutAP;*/                  /* 1st initialization time after partitioning[241]*/
    /*uint32_t correctPrgSectorNum;*/          /* correct prg sectors number[245-242]*/
    /*uint8_t bkOpsStatus;*/                   /* background operations status[246]*/
    /*uint8_t powerOffNotifyTimeout;*/         /* power off notification timeout[247]*/
    uint32_t genericCMD6Timeout;               /* generic CMD6 timeout[248]*/
    uint32_t cacheSize;                        /* cache size[252-249]*/
    uint8_t powerClass200MHZDDR360V;           /* power class for 200MHZ, DDR at VCC=2.6V[253]*/
    /*uint32_t fwVer[2U];*/                    /* fw VERSION [261-254]*/
    /*uint16_t deviceVer;*/                    /* device version[263-262]*/
    /*uint8_t optimalTrimSize;*/               /* optimal trim size[264]*/
    /*uint8_t optimalWriteSize;*/              /* optimal write size[265]*/
    /*uint8_t optimalReadSize;*/               /* optimal read size[266]*/
    /*uint8_t preEolInfo;*/                    /* pre EOL information[267]*/
    /*uint8_t deviceLifeTimeEstimationA;*/     /* device life time estimation typeA[268]*/
    /*uint8_t deviceLifeTimeEstimationB;*/     /* device life time estimation typeB[269]*/
    /*uint32_t correctPrgFWSectorNum;*/        /* number of FW sectors correctly programmed[305-302]*/
    /*uint32_t ffuArg;*/                       /* FFU argument[490-487]*/
    /*uint8_t operationCodeTimeout;*/          /* operation code timeout[491]*/
    /*uint8_t supportMode;*/                   /* support mode [493]*/
    uint8_t extPartitionSupport;               /* extended partition attribute support[494]*/
    /*uint8_t largeUnitSize;*/                 /* large unit size[495]*/
    /*uint8_t contextManageCap;*/              /* context management capability[496]*/
    /*uint8_t tagResourceSize;*/               /* tag resource size[497]*/
    /*uint8_t tagUnitSize;*/                   /* tag unit size[498]*/
    /*uint8_t maxPackedWriteCmd;*/             /* max packed write cmd[500]*/
    /*uint8_t maxPackedReadCmd;*/              /* max packed read cmd[501]*/
    /*uint8_t hpiFeature;*/                    /* HPI feature[503]*/
    uint8_t supportedCommandSet;               /* Supported Command Sets [504] */
    /*uint8_t extSecurityCmdError;*/           /* extended security commands error[505]*/
} mmc_extended_csd_t;


/* MMC card command set(COMMAND_SET in Extended CSD) */
typedef enum
{
    MMC_CommandSetStandard = 0U, /*MMC Standard MMC */
    MMC_CommandSet1        = 1U, /*MMC Command set 1 */
    MMC_CommandSet2        = 2U, /*MMC Command set 2 */
    MMC_CommandSet3        = 3U, /*MMC Command set 3 */
    MMC_CommandSet4        = 4U, /*MMC Command set 4 */
} mmc_command_set_t;

/* Extended CSD register access mode(Access mode in CMD6). */
typedef enum
{
    MMC_ExtendedCsdAccessModeCommandSet = 0U, /* MMC Command set related setting */
    MMC_ExtendedCsdAccessModeSetBits    = 1U, /* MMC Set bits in specific byte in Extended CSD  */
    MMC_ExtendedCsdAccessModeClearBits  = 2U, /* MMC Clear bits in specific byte in Extended CSD */
    MMC_ExtendedCsdAccessModeWriteBits  = 3U, /* MMC Write a value to specific byte in Extended CSD */
} mmc_extended_csd_access_mode_t;

/* EXT CSD byte index */
typedef enum
{
    MMC_ExtendedCsdIndexFlushCache           = 32U,  /* flush cache */
    MMC_ExtendedCsdIndexCacheControl         = 33U,  /* cache control */
    MMC_ExtendedCsdIndexBootPartitionWP      = 173U, /* Boot partition write protect */
    MMC_ExtendedCsdIndexEraseGroupDefinition = 175U, /* Erase Group Def */
    MMC_ExtendedCsdIndexBootBusConditions    = 177U, /* Boot Bus conditions */
    MMC_ExtendedCsdIndexBootConfigWP         = 178U, /* Boot config write protect */
    MMC_ExtendedCsdIndexPartitionConfig      = 179U, /* Partition Config, before BOOT_CONFIG */
    MMC_ExtendedCsdIndexBusWidth             = 183U, /* Bus Width */
    MMC_ExtendedCsdIndexHighSpeedTiming      = 185U, /* High-speed Timing */
    MMC_ExtendedCsdIndexPowerClass           = 187U, /* Power Class */
    MMC_ExtendedCsdIndexCommandSet           = 191U, /* Command Set */
} mmc_extended_csd_index_t;

/* mmc driver strength */
enum
{
    MMC_DriverStrength0 = 0U, /* Driver type0 ,nominal impedance 50ohm */
    MMC_DriverStrength1 = 1U, /* Driver type1 ,nominal impedance 33ohm */
    MMC_DriverStrength2 = 2U, /* Driver type2 ,nominal impedance 66ohm */
    MMC_DriverStrength3 = 3U, /* Driver type3 ,nominal impedance 100ohm */
    MMC_DriverStrength4 = 4U, /* Driver type4 ,nominal impedance 40ohm */
};

/* The bit shift for COMMAND SET field in SWITCH command. */
#define MMC_SWITCH_COMMAND_SET_SHIFT (0U)
/* The bit mask for COMMAND set field in SWITCH command. */
#define MMC_SWITCH_COMMAND_SET_MASK (0x00000007U)
/* The bit shift for VALUE field in SWITCH command */
#define MMC_SWITCH_VALUE_SHIFT (8U)
/* The bit mask for VALUE field in SWITCH command */
#define MMC_SWITCH_VALUE_MASK (0x0000FF00U)
/* The bit shift for BYTE INDEX field in SWITCH command */
#define MMC_SWITCH_BYTE_INDEX_SHIFT (16U)
/* The bit mask for BYTE INDEX field in SWITCH command */
#define MMC_SWITCH_BYTE_INDEX_MASK (0x00FF0000U)
/* The bit shift for ACCESS MODE field in SWITCH command */
#define MMC_SWITCH_ACCESS_MODE_SHIFT (24U)
/* The bit mask for ACCESS MODE field in SWITCH command */
#define MMC_SWTICH_ACCESS_MODE_MASK (0x03000000U)

/* Default block size */
#define FSL_SDMMC_DEFAULT_BLOCK_SIZE (512U)

/* MMC Extended CSD configuration. */
typedef struct
{
    mmc_command_set_t commandSet;              /* MMC Command set */
    uint8_t ByteValue;                         /* MMC The value to set */
    uint8_t ByteIndex;                         /* MMC The byte index in Extended CSD(mmc_extended_csd_index_t) */
    mmc_extended_csd_access_mode_t accessMode; /* MMC Access mode */
} mmc_extended_csd_config_t;

/* SD card command class */
enum
{
    SD_CommandClassBasic               = (1U << 0U),  /* Card command class 0 */
    SD_CommandClassBlockRead           = (1U << 2U),  /* Card command class 2 */
    SD_CommandClassBlockWrite          = (1U << 4U),  /* Card command class 4 */
    SD_CommandClassErase               = (1U << 5U),  /* Card command class 5 */
    SD_CommandClassWriteProtect        = (1U << 6U),  /* Card command class 6 */
    SD_CommandClassLockCard            = (1U << 7U),  /* Card command class 7 */
    SD_CommandClassApplicationSpecific = (1U << 8U),  /* Card command class 8 */
    SD_CommandClassInputOutputMode     = (1U << 9U),  /* Card command class 9 */
    SD_CommandClassSwitch              = (1U << 10U), /* Card command class 10 */
};

/* SD card specification version number */
enum
{
    SD_SpecificationVersion1_0 = (1U << 0U), /* SD card version 1.0-1.01 */
    SD_SpecificationVersion1_1 = (1U << 1U), /* SD card version 1.10 */
    SD_SpecificationVersion2_0 = (1U << 2U), /* SD card version 2.00 */
    SD_SpecificationVersion3_0 = (1U << 3U), /* SD card version 3.0 */
};
/* dma mode */
typedef enum
{
    SDMMC_NODMA = 0U,  /* no use dma */
    SDMMC_SDMA = 1U,   /* use sdma */
    SDMMC_ADMA = 2U,   /* use adma */
}sdmmc_dma_t;
/* SD card flags */
enum
{
    SD_SupportHighCapacityFlag     = (1U << 1U), /* Support high capacity */
    SD_Support4BitWidthFlag        = (1U << 2U), /* Support 4-bit data width */
    SD_SupportSdhcFlag             = (1U << 3U), /* Card is SDHC */
    SD_SupportSdxcFlag             = (1U << 4U), /* Card is SDXC */
    SD_SupportVoltage180v          = (1U << 5U), /* card support 1.8v voltage*/
    SD_SupportSetBlockCountCmd     = (1U << 6U), /* card support cmd23 flag*/
    SD_SupportSpeedClassControlCmd = (1U << 7U), /* card support speed class control flag */
};
/* SD card individual commands */
typedef enum
{
    SD_SendRelativeAddress    = 3U,  /* Send Relative Address */
    SD_Switch                 = 6U,  /* Switch Function */
    SD_SendInterfaceCondition = 8U,  /* Send Interface Condition */
    SD_VoltageSwitch          = 11U, /* Voltage Switch */
    SD_SpeedClassControl      = 20U, /* Speed Class control */
    SD_EraseWriteBlockStart   = 32U, /* Write Block Start */
    SD_EraseWriteBlockEnd     = 33U, /* Write Block End */
    SD_SendTuningBlock        = 19U, /* Send Tuning Block */
} sd_command_t;
#ifdef __cplusplus
}
#endif

#endif /* __SDMMC_SPEC_H__ */

