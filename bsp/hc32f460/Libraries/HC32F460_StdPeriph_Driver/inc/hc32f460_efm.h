/*****************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_efm.h
 **
 ** A detailed description is available at
 ** @link EfmGroup EFM description @endlink
 **
 **   - 2018-10-29  CDT  First version for Device Driver Library of EFM.
 **
 ******************************************************************************/
#ifndef __HC32F460_EFM_H__
#define __HC32F460_EFM_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

#if (DDL_EFM_ENABLE == DDL_ON)

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup EfmGroup Embedded Flash Management unit(EFM)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief  The flash status.
 **
 ******************************************************************************/
typedef enum en_efm_flash_status
{
    FlashReady                  = 1u,   ///< The flash ready flag.
    FlashRWErr                  = 2u,   ///< The flash read/write error flag.
    FlashEOP                    = 3u,   ///< The flash end of operation flag.
    FlashPgMissMatch            = 4u,   ///< The flash program miss match flag.
    FlashPgSizeErr              = 5u,   ///< The flash program size error flag.
    FlashPgareaPErr             = 6u,   ///< The flash program protect area error flag.
    FlashWRPErr                 = 7u,   ///< The flash write protect error flag.
}en_efm_flash_status_t;

/**
 *******************************************************************************
 ** \brief  The flash read mode.
 **
 ******************************************************************************/
typedef enum en_efm_read_md
{
    NormalRead                  = 0u,   ///< The flash normal read mode.
    UltraPowerRead              = 1u,   ///< The flash ultra power read mode.
}en_efm_read_md_t;

/**
 *******************************************************************************
 ** \brief  The flash interrupt select.
 **
 ******************************************************************************/
typedef enum en_efm_int_sel
{
    PgmErsErrInt                = 0u,   ///< The flash program / erase error interrupt.
    EndPgmInt                   = 1u,   ///< The flash end of program interrupt.
    ColErrInt                   = 2u,   ///< The flash read collided error interrupt.
}en_efm_int_sel_t;

/**
 *******************************************************************************
 ** \brief  The bus state while flash program & erase.
 **
 ******************************************************************************/
typedef enum en_efm_bus_sta
{
    BusBusy                     = 0u,   ///< The bus busy while flash program & erase.
    BusRelease                  = 1u,   ///< The bus release while flash program & erase.
}en_efm_bus_sta_t;

/**
 *******************************************************************************
 ** \brief  Structure of windows protect address.
 **
 ** \note   None.
 **
 ******************************************************************************/
typedef struct stc_efm_win_protect_addr
{
    uint32_t            StartAddr;      ///< The protect start address.
    uint32_t            EndAddr;        ///< The protect end address.
}stc_efm_win_protect_addr_t;

/**
 *******************************************************************************
 ** \brief  Structure of unique ID.
 **
 ** \note   None.
 **
 ******************************************************************************/
typedef struct stc_efm_unique_id
{
    uint32_t            uniqueID1;      ///< unique ID 1.
    uint32_t            uniqueID2;      ///< unique ID 2.
    uint32_t            uniqueID3;      ///< unique ID 3.
}stc_efm_unique_id_t;
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
 /* Flach latency cycle (0~15) */
#define EFM_LATENCY_0                   (0ul)
#define EFM_LATENCY_1                   (1ul)
#define EFM_LATENCY_2                   (2ul)
#define EFM_LATENCY_3                   (3ul)
#define EFM_LATENCY_4                   (4ul)
#define EFM_LATENCY_5                   (5ul)
#define EFM_LATENCY_6                   (6ul)
#define EFM_LATENCY_7                   (7ul)
#define EFM_LATENCY_8                   (8ul)
#define EFM_LATENCY_9                   (9ul)
#define EFM_LATENCY_10                  (10ul)
#define EFM_LATENCY_11                  (11ul)
#define EFM_LATENCY_12                  (12ul)
#define EFM_LATENCY_13                  (13ul)
#define EFM_LATENCY_14                  (14ul)
#define EFM_LATENCY_15                  (15ul)

/* Flash flag */
#define EFM_FLAG_WRPERR                 (0x00000001ul)
#define EFM_FLAG_PEPRTERR               (0x00000002ul)
#define EFM_FLAG_PGSZERR                (0x00000004ul)
#define EFM_FLAG_PGMISMTCH              (0x00000008ul)
#define EFM_FLAG_EOP                    (0x00000010ul)
#define EFM_FLAG_COLERR                 (0x00000020ul)
#define EFM_FLAG_RDY                    (0x00000100ul)

/* Flash operate mode */
#define EFM_MODE_READONLY               (0ul)
#define EFM_MODE_SINGLEPROGRAM          (1ul)
#define EFM_MODE_SINGLEPROGRAMRB        (2ul)
#define EFM_MODE_SEQUENCEPROGRAM        (3ul)
#define EFM_MODE_SECTORERASE            (4ul)
#define EFM_MODE_CHIPERASE              (5ul)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
void EFM_Unlock(void);
void EFM_Lock(void);

void EFM_FlashCmd(en_functional_state_t enNewState);
void EFM_SetLatency(uint32_t u32Latency);
void EFM_InstructionCacheCmd(en_functional_state_t enNewState);
void EFM_DataCacheRstCmd(en_functional_state_t enNewState);
void EFM_SetReadMode(en_efm_read_md_t enReadMD);
void EFM_ErasePgmCmd(en_functional_state_t enNewState);
en_result_t EFM_SetErasePgmMode(uint32_t u32Mode);
void EFM_InterruptCmd(en_efm_int_sel_t enInt, en_functional_state_t enNewState);

en_flag_status_t EFM_GetFlagStatus(uint32_t u32flag);
en_flag_status_t EFM_GetSwitchStatus(void);
void EFM_ClearFlag(uint32_t u32flag);
en_efm_flash_status_t EFM_GetStatus(void);
void EFM_SetBusState(en_efm_bus_sta_t enState);

void EFM_SetWinProtectAddr(stc_efm_win_protect_addr_t stcAddr);

en_result_t EFM_SingleProgram(uint32_t u32Addr, uint32_t u32Data);
en_result_t EFM_SingleProgramRB(uint32_t u32Addr, uint32_t u32Data);
en_result_t EFM_SequenceProgram(uint32_t u32Addr, uint32_t u32Len, void *pBuf);
en_result_t EFM_SectorErase(uint32_t u32Addr);
en_result_t EFM_MassErase(uint32_t u32Addr);

en_result_t EFM_OtpLock(uint32_t u32Addr);
stc_efm_unique_id_t EFM_ReadUID(void);


//@} // EfmGroup

#ifdef __cplusplus
}
#endif

#endif /* DDL_EFM_ENABLE */

#endif /* __HC32F460_EFM_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

