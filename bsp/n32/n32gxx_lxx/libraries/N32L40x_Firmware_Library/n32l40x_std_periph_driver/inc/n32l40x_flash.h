/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32l40x_flash.h
 * @author Nations
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32L40X_FLASH_H__
#define __N32L40X_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32l40x.h"

/** @addtogroup n32l40x_StdPeriph_Driver
 * @{
 */

/** @addtogroup FLASH
 * @{
 */

/** @addtogroup FLASH_Exported_Types
 * @{
 */

/**
 * @brief  FLASH Status
 */

typedef enum
{
    FLASH_BUSY = 1,
    FLASH_RESERVED,
    FLASH_ERR_PG,
    FLASH_ERR_PV,
    FLASH_ERR_WRP,
    FLASH_COMPL,
    FLASH_ERR_EV,
    FLASH_ERR_RDP2,
    FLASH_ERR_ADD,
    FLASH_TIMEOUT
} FLASH_STS;

/**
 * @brief  FLASH_SMPSEL
 */

typedef enum
{
    FLASH_SMP1 = 0,
    FLASH_SMP2
} FLASH_SMPSEL;

/**
 * @brief  FLASH_HSICLOCK
 */

typedef enum
{
    FLASH_HSICLOCK_ENABLE = 0,
    FLASH_HSICLOCK_DISABLE
} FLASH_HSICLOCK;

/**
 * @}
 */

/** @addtogroup FLASH_Exported_Constants
 * @{
 */

/** @addtogroup Flash_Latency
 * @{
 */

#define FLASH_LATENCY_0 ((uint32_t)0x00000000) /*!< FLASH Zero Latency cycle */
#define FLASH_LATENCY_1 ((uint32_t)0x00000001) /*!< FLASH One Latency cycle */
#define FLASH_LATENCY_2 ((uint32_t)0x00000002) /*!< FLASH Two Latency cycles */
#define FLASH_LATENCY_3 ((uint32_t)0x00000003) /*!< FLASH Three Latency cycles */
#define IS_FLASH_LATENCY(LATENCY)                                                                                      \
    (((LATENCY) == FLASH_LATENCY_0) || ((LATENCY) == FLASH_LATENCY_1) || ((LATENCY) == FLASH_LATENCY_2)                \
     || ((LATENCY) == FLASH_LATENCY_3))
/**
 * @}
 */

/** @addtogroup Prefetch_Buffer_Enable_Disable
 * @{
 */

#define FLASH_PrefetchBuf_EN              ((uint32_t)0x00000010) /*!< FLASH Prefetch Buffer Enable */
#define FLASH_PrefetchBuf_DIS             ((uint32_t)0x00000000) /*!< FLASH Prefetch Buffer Disable */
#define IS_FLASH_PREFETCHBUF_STATE(STATE) (((STATE) == FLASH_PrefetchBuf_EN) || ((STATE) == FLASH_PrefetchBuf_DIS))
/**
 * @}
 */

/** @addtogroup iCache_Enable_Disable
 * @{
 */

#define FLASH_iCache_EN              ((uint32_t)0x00000080) /*!< FLASH iCache Enable */
#define FLASH_iCache_DIS             ((uint32_t)0x00000000) /*!< FLASH iCache Disable */
#define IS_FLASH_ICACHE_STATE(STATE) (((STATE) == FLASH_iCache_EN) || ((STATE) == FLASH_iCache_DIS))
/**
 * @}
 */

/** @addtogroup Low Voltage Mode
 * @{
 */

#define FLASH_LVM_EN              ((uint32_t)0x00000200) /*!< FLASH Low Voltage Mode Enable */
#define FLASH_LVM_DIS             ((uint32_t)0x00000000) /*!< FLASH Low Voltage Mode Disable */
#define IS_FLASH_LVM(STATE)       (((STATE) == FLASH_LVM_EN) || ((STATE) == FLASH_LVM_DIS))
/**
 * @}
 */

/** @addtogroup FLASH Sleep Mode
 * @{
 */

#define FLASH_SLM_EN              ((uint32_t)0x00000800) /*!< FLASH Sleep Mode Enable */
#define FLASH_SLM_DIS             ((uint32_t)0x00000000) /*!< FLASH Sleep Mode Disable */
#define IS_FLASH_SLM(STATE)       (((STATE) == FLASH_SLM_EN) || ((STATE) == FLASH_SLM_DIS))
/**
 * @}
 */

/** @addtogroup SMPSEL_SMP1_SMP2
 * @{
 */

#define FLASH_SMPSEL_SMP1            ((uint32_t)0x00000000) /*!< FLASH SMPSEL SMP1 */
#define FLASH_SMPSEL_SMP2            ((uint32_t)0x00000100) /*!< FLASH SMPSEL SMP2 */
#define IS_FLASH_SMPSEL_STATE(STATE) (((STATE) == FLASH_SMPSEL_SMP1) || ((STATE) == FLASH_SMPSEL_SMP2))
/**
 * @}
 */

/* Values to be used with n32l40x devices */
#define FLASH_WRP_Pages0to1                                                                                           \
    ((uint32_t)0x00000001) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 0 to 1 */
#define FLASH_WRP_Pages2to3                                                                                           \
    ((uint32_t)0x00000002) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 2 to 3 */
#define FLASH_WRP_Pages4to5                                                                                           \
    ((uint32_t)0x00000004) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 4 to 5 */
#define FLASH_WRP_Pages6to7                                                                                           \
    ((uint32_t)0x00000008) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 6 to 7 */
#define FLASH_WRP_Pages8to9                                                                                           \
    ((uint32_t)0x00000010) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 8 to 9 */
#define FLASH_WRP_Pages10to11                                                                                         \
    ((uint32_t)0x00000020) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 10 to 11 */
#define FLASH_WRP_Pages12to13                                                                                         \
    ((uint32_t)0x00000040) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 12 to 13 */
#define FLASH_WRP_Pages14to15                                                                                         \
    ((uint32_t)0x00000080) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 14 to 15 */
#define FLASH_WRP_Pages16to17                                                                                         \
    ((uint32_t)0x00000100) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 16 to 17 */
#define FLASH_WRP_Pages18to19                                                                                         \
    ((uint32_t)0x00000200) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 18 to 19 */
#define FLASH_WRP_Pages20to21                                                                                         \
    ((uint32_t)0x00000400) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 20 to 21 */
#define FLASH_WRP_Pages22to23                                                                                         \
    ((uint32_t)0x00000800) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 22 to 23 */
#define FLASH_WRP_Pages24to25                                                                                         \
    ((uint32_t)0x00001000) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 24 to 25 */
#define FLASH_WRP_Pages26to27                                                                                         \
    ((uint32_t)0x00002000) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 26 to 27 */
#define FLASH_WRP_Pages28to29                                                                                         \
    ((uint32_t)0x00004000) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 28 to 29 */
#define FLASH_WRP_Pages30to31                                                                                         \
    ((uint32_t)0x00008000) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 30 to 31 */
#define FLASH_WRP_Pages32to33                                                                                         \
    ((uint32_t)0x00010000) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 32 to 33 */
#define FLASH_WRP_Pages34to35                                                                                         \
    ((uint32_t)0x00020000) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 34 to 35 */
#define FLASH_WRP_Pages36to37                                                                                         \
    ((uint32_t)0x00040000) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 36 to 37 */
#define FLASH_WRP_Pages38to39                                                                                         \
    ((uint32_t)0x00080000) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 38 to 39 */
#define FLASH_WRP_Pages40to41                                                                                         \
    ((uint32_t)0x00100000) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 40 to 41 */
#define FLASH_WRP_Pages42to43                                                                                         \
    ((uint32_t)0x00200000) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 42 to 43 */
#define FLASH_WRP_Pages44to45                                                                                         \
    ((uint32_t)0x00400000) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 44 to 45 */
#define FLASH_WRP_Pages46to47                                                                                         \
    ((uint32_t)0x00800000) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 46 to 47 */
#define FLASH_WRP_Pages48to49                                                                                         \
    ((uint32_t)0x01000000) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 48 to 49 */
#define FLASH_WRP_Pages50to51                                                                                         \
    ((uint32_t)0x02000000) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 50 to 51 */
#define FLASH_WRP_Pages52to53                                                                                         \
    ((uint32_t)0x04000000) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 52 to 53 */
#define FLASH_WRP_Pages54to55                                                                                         \
    ((uint32_t)0x08000000) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 54 to 55 */
#define FLASH_WRP_Pages56to57                                                                                         \
    ((uint32_t)0x10000000) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 56 to 57 */
#define FLASH_WRP_Pages58to59                                                                                         \
    ((uint32_t)0x20000000) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 58 to 59 */
#define FLASH_WRP_Pages60to61                                                                                         \
    ((uint32_t)0x40000000) /*!< n32l40x devices:                                                                       \
                                  Write protection of page 60 to 61 */
#define FLASH_WRP_Pages62to63                                                                                        \
    ((uint32_t)0x80000000) /*!< n32l40x devices:
                                  Write protection of page 62 to 63 */

#define FLASH_WRP_AllPages ((uint32_t)0xFFFFFFFF) /*!< Write protection of all Pages */

#define IS_FLASH_WRP_PAGE(PAGE) (1)//(((PAGE) <= FLASH_WRP_AllPages))

#define IS_FLASH_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && ((ADDRESS) < 0x0801FFFF))

#define IS_OB_DATA_ADDRESS(ADDRESS) ((ADDRESS) == 0x1FFFF804)

/**
 * @}
 */

/** @addtogroup Option_Bytes_RDP1
 * @{
 */

#define OB_RDP1_ENABLE            ((uint8_t)0x00) /*!< Enable RDP1 */
#define OB_RDP1_DISABLE           ((uint8_t)0xA5) /*!< DISABLE RDP1 */
#define IS_OB_RDP1_SOURCE(SOURCE) (((SOURCE) == OB_RDP1_ENABLE) || ((SOURCE) == OB_RDP1_DISABLE))

/**
 * @}
 */

/** @addtogroup Option_Bytes_IWatchdog
 * @{
 */

#define OB_IWDG_SW                ((uint8_t)0x01) /*!< Software IWDG selected */
#define OB_IWDG_HW                ((uint8_t)0x00) /*!< Hardware IWDG selected */
#define IS_OB_IWDG_SOURCE(SOURCE) (((SOURCE) == OB_IWDG_SW) || ((SOURCE) == OB_IWDG_HW))

/**
 * @}
 */

/** @addtogroup Option_Bytes_nRST_STOP
 * @{
 */

#define OB_STOP2_NORST             ((uint8_t)0x02) /*!< No reset generated when entering in STOP */
#define OB_STOP2_RST               ((uint8_t)0x00) /*!< Reset generated when entering in STOP */
#define IS_OB_STOP2_SOURCE(SOURCE) (((SOURCE) == OB_STOP2_NORST) || ((SOURCE) == OB_STOP2_RST))

/**
 * @}
 */

/** @addtogroup Option_Bytes_nRST_STDBY
 * @{
 */

#define OB_STDBY_NORST             ((uint8_t)0x04) /*!< No reset generated when entering in STANDBY */
#define OB_STDBY_RST               ((uint8_t)0x00) /*!< Reset generated when entering in STANDBY */
#define IS_OB_STDBY_SOURCE(SOURCE) (((SOURCE) == OB_STDBY_NORST) || ((SOURCE) == OB_STDBY_RST))

/**
 * @}
 */

/** @addtogroup Option_Bytes_nRST_PD
 * @{
 */

#define OB_PD_NORST                ((uint8_t)0x08) /*!< No reset generated when entering in PowerDown */
#define OB_PD_RST                  ((uint8_t)0x00) /*!< Reset generated when entering in PowerDown */
#define IS_OB_PD_SOURCE(SOURCE)    (((SOURCE) == OB_PD_NORST) || ((SOURCE) == OB_PD_RST))

/**
 * @}
 */

/** @addtogroup Option_Bytes_RDP2
 * @{
 */

#define OB_RDP2_ENABLE            ((uint8_t)0x33) /*!< Enable RDP2 */
#define OB_RDP2_DISABLE           ((uint8_t)0x00) /*!< Disable RDP2 */
#define IS_OB_RDP2_SOURCE(SOURCE) (((SOURCE) == OB_RDP2_ENABLE) || ((SOURCE) == OB_RDP2_DISABLE))

/**
 * @}
 */

/** @addtogroup Option_Bytes_nBOOT0
 * @{
 */

#define OB2_NBOOT0_SET                ((uint8_t)0x01) /*!< Set nBOOT0 */
#define OB2_NBOOT0_CLR                ((uint8_t)0x00) /*!< Clear nBOOT0 */
#define IS_OB2_NBOOT0_SOURCE(SOURCE)  (((SOURCE) == OB2_NBOOT0_SET) || ((SOURCE) == OB2_NBOOT0_CLR))

/**
 * @}
 */

/** @addtogroup Option_Bytes_nBOOT1
 * @{
 */

#define OB2_NBOOT1_SET                ((uint8_t)0x02) /*!< Set nBOOT1 */
#define OB2_NBOOT1_CLR                ((uint8_t)0x00) /*!< Clear nBOOT1 */
#define IS_OB2_NBOOT1_SOURCE(SOURCE)  (((SOURCE) == OB2_NBOOT1_SET) || ((SOURCE) == OB2_NBOOT1_CLR))

/**
 * @}
 */

/** @addtogroup Option_Bytes_nSWBOOT0
 * @{
 */

#define OB2_NSWBOOT0_SET                ((uint8_t)0x04) /*!< Set nSWBOOT0 */
#define OB2_NSWBOOT0_CLR                ((uint8_t)0x00) /*!< Clear nSWBOOT0 */
#define IS_OB2_NSWBOOT0_SOURCE(SOURCE)  (((SOURCE) == OB2_NSWBOOT0_SET) || ((SOURCE) == OB2_NSWBOOT0_CLR))

/**
 * @}
 */

/** @addtogroup Option_Bytes_BOR_LEV
 * @{
 */

#define OB2_BOR_LEV0                    ((uint8_t)0x00) /*!< BOR_LEV[2:0] L0 */
#define OB2_BOR_LEV1                    ((uint8_t)0x10) /*!< BOR_LEV[2:0] L1 */
#define OB2_BOR_LEV2                    ((uint8_t)0x20) /*!< BOR_LEV[2:0] L2 */
#define OB2_BOR_LEV3                    ((uint8_t)0x30) /*!< BOR_LEV[2:0] L3 */
#define OB2_BOR_LEV4                    ((uint8_t)0x40) /*!< BOR_LEV[2:0] L4 */
#define OB2_BOR_LEV5                    ((uint8_t)0x50) /*!< BOR_LEV[2:0] L5 */
#define OB2_BOR_LEV6                    ((uint8_t)0x60) /*!< BOR_LEV[2:0] L6 */
#define OB2_BOR_LEV7                    ((uint8_t)0x70) /*!< BOR_LEV[2:0] L7 */
#define IS_OB2_BOR_LEV_SOURCE(SOURCE)   (((SOURCE) == OB2_BOR_LEV0) || ((SOURCE) == OB2_BOR_LEV1)  \
                                     || ((SOURCE) == OB2_BOR_LEV2) || ((SOURCE) == OB2_BOR_LEV3)  \
                                     || ((SOURCE) == OB2_BOR_LEV4) || ((SOURCE) == OB2_BOR_LEV5)  \
                                     || ((SOURCE) == OB2_BOR_LEV6) || ((SOURCE) == OB2_BOR_LEV7))


/**
 * @}
 */
/** @addtogroup FLASH_Interrupts
 * @{
 */
#define FLASH_INT_ERRIE    ((uint32_t)0x00000400) /*!< PGERR WRPERR ERROR error interrupt source */
#define FLASH_INT_FERR     ((uint32_t)0x00000800) /*!< EVERR PVERR interrupt source */
#define FLASH_INT_EOP      ((uint32_t)0x00001000) /*!< End of FLASH Operation Interrupt source */

#define IS_FLASH_INT(IT) ((((IT) & (uint32_t)0xFFFFE3FF) == 0x00000000) && (((IT) != 0x00000000)))

/**
 * @}
 */

/** @addtogroup FLASH_Flags
 * @{
 */
#define FLASH_FLAG_BUSY     ((uint32_t)0x00000001) /*!< FLASH Busy flag */
#define FLASH_FLAG_PGERR    ((uint32_t)0x00000004) /*!< FLASH Program error flag */
#define FLASH_FLAG_PVERR    ((uint32_t)0x00000008) /*!< FLASH Program Verify ERROR flag after program */
#define FLASH_FLAG_WRPERR   ((uint32_t)0x00000010) /*!< FLASH Write protected error flag */
#define FLASH_FLAG_EOP      ((uint32_t)0x00000020) /*!< FLASH End of Operation flag */
#define FLASH_FLAG_EVERR    ((uint32_t)0x00000040) /*!< FLASH Erase Verify ERROR flag after page erase */
#define FLASH_FLAG_OBERR    ((uint32_t)0x00000001) /*!< FLASH Option Byte error flag */

#define IS_FLASH_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFFF83) == 0x00000000) && ((FLAG) != 0x00000000))
#define IS_FLASH_GET_FLAG(FLAG)                                                                                       \
       (((FLAG) == FLASH_FLAG_BUSY)   || ((FLAG) == FLASH_FLAG_PGERR) || ((FLAG) == FLASH_FLAG_PVERR)                 \
     || ((FLAG) == FLASH_FLAG_WRPERR) || ((FLAG) == FLASH_FLAG_EOP)   || ((FLAG) == FLASH_FLAG_EVERR)                 \
     || ((FLAG) == FLASH_FLAG_OBERR))

/**
 * @}
 */

/** @addtogroup FLASH_STS_CLRFLAG
 * @{
 */
#define FLASH_STS_CLRFLAG   (FLASH_FLAG_PGERR | FLASH_FLAG_PVERR | FLASH_FLAG_WRPERR | FLASH_FLAG_EOP |FLASH_FLAG_EVERR)

/**
 * @}
 */

/** @addtogroup FLASH_Exported_Functions
 * @{
 */

/*------------ Functions used for n32l40x devices -----*/
void FLASH_SetLatency(uint32_t FLASH_Latency);
void FLASH_PrefetchBufSet(uint32_t FLASH_PrefetchBuf);
void FLASH_iCacheRST(void);
void FLASH_iCacheCmd(uint32_t FLASH_iCache);
void FLASH_LowVoltageModeCmd(uint32_t FLASH_LVM);
FlagStatus FLASH_GetLowVoltageModeSTS(void);
void FLASH_FLASHSleepModeCmd(uint32_t FLASH_SLM);
FlagStatus FLASH_GetFLASHSleepModeSTS(void);
FLASH_HSICLOCK FLASH_ClockInit(void);
void FLASH_Unlock(void);
void FLASH_Lock(void);
FLASH_STS FLASH_EraseOnePage(uint32_t Page_Address);
FLASH_STS FLASH_MassErase(void);
FLASH_STS FLASH_EraseOB(void);
FLASH_STS FLASH_ProgramWord(uint32_t Address, uint32_t Data);
FLASH_STS FLASH_ProgramOBData(uint32_t Address, uint32_t Data);
FLASH_STS FLASH_EnWriteProtection(uint32_t FLASH_Pages);
FLASH_STS FLASH_ReadOutProtectionL1(FunctionalState Cmd);
FLASH_STS FLASH_ReadOutProtectionL2_ENABLE(void);
FLASH_STS FLASH_ConfigALLOptionByte(uint8_t OB_RDP1,    uint8_t OB_IWDG,    uint8_t OB_STOP2,
                                    uint8_t OB_STDBY,   uint8_t OB_PD,      uint8_t OB_Data0,
                                    uint8_t OB_Data1,   uint32_t WRP_Pages, uint8_t OB_RDP2,
                                    uint8_t OB2_nBOOT0, uint8_t OB2_nBOOT1, uint8_t OB2_nSWBOOT0,
                                    uint8_t OB2_BOR_LEV);
FLASH_STS FLASH_ConfigUserOB(uint8_t OB_IWDG, uint8_t OB_STOP2, uint8_t OB_STDBY, uint8_t OB_PD);
FLASH_STS FLASH_ConfigUserOB2(uint8_t OB2_nBOOT0, uint8_t OB2_nBOOT1, uint8_t OB2_nSWBOOT0, uint8_t OB2_BOR_LEV);
uint32_t FLASH_GetUserOB(void);
uint32_t FLASH_GetWriteProtectionOB(void);
FlagStatus FLASH_GetReadOutProtectionSTS(void);
FlagStatus FLASH_GetReadOutProtectionL2STS(void);
FlagStatus FLASH_GetPrefetchBufSTS(void);
void FLASH_SetSMPSELStatus(uint32_t FLASH_smpsel);
FLASH_SMPSEL FLASH_GetSMPSELStatus(void);
void FLASH_INTConfig(uint32_t FLASH_INT, FunctionalState Cmd);
FlagStatus FLASH_GetFlagSTS(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_STS FLASH_GetSTS(void);
FLASH_STS FLASH_WaitForLastOpt(uint32_t Timeout);

#ifdef __cplusplus
}
#endif

#endif /* __N32L40X_FLASH_H__ */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
