/**
  ******************************************************************************
  * @file    tae32g58xx_ll_eflash.h
  * @author  MCD Application Team
  * @brief   Header file for EFLASH LL module
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32G58XX_LL_EFLASH_H_
#define _TAE32G58XX_LL_EFLASH_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup EFLASH_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup EFLASH_LL_Exported_Constants EFLASH LL Exported Constants
  * @brief    EFLASH LL Exported Constants
  * @{
  */

/*
 * @brief EFLASH Sector Size and Sector Number Definition
 */
#define EFLASH_SECTOR_SIZE_256_S        (8192U)     /*!< EFLASH 256K Single Bank Sector Size Definition     */
#define EFLASH_SECTOR_NUM_256_S         (32U)       /*!< EFLASH 256K Single Bank Sector Number Definition   */

#define EFLASH_SECTOR_SIZE_256_D        (4096U)     /*!< EFLASH 256K Double Bank Sector Size Definition     */
#define EFLASH_SECTOR_NUM_256_D         (64U)       /*!< EFLASH 256K Double Bank Sector Number Definition   */

#define EFLASH_SECTOR_SIZE_128          (4096U)     /*!< EFLASH 128K Bank Sector Size Definition            */
#define EFLASH_SECTOR_NUM_128           (32U)       /*!< EFLASH 128K Bank Sector Number Definition          */


/**
  * @brief EFLASH Program Size in a single programming operation, in byte Unit
  */
#define EFLASH_PROG_SINGLE_SIZE         (8U)

/*
 * @brief EFLASH Program address mask Definition
 */
#define EFLASH_PROG_ADDRESS_MASK        (0x00FFFFFFU)

/*
 * @brief EFLASH Default Timeout Definition, 300ms
 */
#define EFLASH_DEFAULT_TIMEOUT          (300U)

/**
  * @brief EFLASH Write Protect Control Unit, 2 Sectors
  */
#define EFLASH_WRITE_PROTECT_UNIT       (2U)


/*
 * @brief EFLASH Program/Erase unlock KEY1
 */
#define EFLASH_PROG_ERASE_KEY1          (0x3facU)

/*
 * @brief EFLASH Program/Erase unlock KEY2
 * @note  Used with KEY1 to unlock the EFLASH Program/Erase features
 */
#define EFLASH_PROG_ERASE_KEY2          (0x87e4U)

/*
 * @brief EFLASH Read/Write Protection / Option Data unlock Operation KEY1
 */
#define EFLASH_RW_PROTECT_OPT_DAT_KEY1  (0x124AU)

/*
 * @brief EFLASH Read/Write Protection / Option Data unlock Operation KEY2
 * @note  Used with KEY1 to unlock the operation of EFLASH Read/Write Protection Register
 */
#define EFLASH_RW_PROTECT_OPT_DAT_KEY2  (0xbc7fU)

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup EFLASH_LL_Exported_Macros EFLASH LL Exported Macros
  * @brief    EFLASH LL Exported Macros
  * @{
  */

/**
  * @brief  Program/Erase Lock
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_ProgErase_Lock(__EFLASH__)          SET_BIT((__EFLASH__)->CR, FLASH_CR_LCK_Msk)

/**
  * @brief  Judge Program/Erase is Lock or Unlock
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 Program/Erase is Unlock
  * @retval 1 Program/Erase is Lock
  */
#define __LL_EFLASH_IsProgEraseLock(__EFLASH__)         READ_BIT_SHIFT((__EFLASH__)->CR, FLASH_CR_LCK_Msk, FLASH_CR_LCK_Pos)

/**
  * @brief  FLASH nBits ECC NMI Interrupt Enable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_NBitsEccNmi_INT_En(__EFLASH__)      SET_BIT((__EFLASH__)->CR, FLASH_CR_NMIE_Msk)

/**
  * @brief  FLASH nBits ECC NMI Interrupt Disable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_NBitsEccNmi_INT_Dis(__EFLASH__)     CLEAR_BIT((__EFLASH__)->CR, FLASH_CR_NMIE_Msk)

/**
  * @brief  Judge is nBits ECC NMI Interrupt Enable or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 ECC NMI Interrupt is Disable
  * @retval 1 ECC NMI Interrupt is Enable
  */
#define __LL_EFLASH_IsNBitsEccNmiIntEn(__EFLASH__)      READ_BIT_SHIFT((__EFLASH__)->CR, FLASH_CR_NMIE_Msk, FLASH_CR_NMIE_Pos)


/**
  * @brief  Error Interrupt Enable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_Err_INT_En(__EFLASH__)              SET_BIT((__EFLASH__)->CR, FLASH_CR_EIE_Msk)

/**
  * @brief  Error Interrupt Disable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_Err_INT_Dis(__EFLASH__)             CLEAR_BIT((__EFLASH__)->CR, FLASH_CR_EIE_Msk)

/**
  * @brief  Judge is Error Interrupt Enable or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 Error Interrupt is Disable
  * @retval 1 Error Interrupt is Enable
  */
#define __LL_EFLASH_IsErrIntEn(__EFLASH__)              READ_BIT_SHIFT((__EFLASH__)->CR, FLASH_CR_EIE_Msk, FLASH_CR_EIE_Pos)

/**
  * @brief  Launch Enable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_Launch_En(__EFLASH__)               SET_BIT((__EFLASH__)->CR, FLASH_CR_FLE_Msk)

/**
  * @brief  EFLASH D BUS Prefetch feature Enable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @note   Prefetch feature should not be enabled when CPU frequency is lower than 40MHz
  * @return None
  */
#define __LL_EFLASH_DBusPrefetch_En(__EFLASH__)         SET_BIT((__EFLASH__)->CR, FLASH_CR_DPE_Msk)

/**
  * @brief  EFLASH D BUS Prefetch feature Disable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_DBusPrefetch_Dis(__EFLASH__)        CLEAR_BIT((__EFLASH__)->CR, FLASH_CR_DPE_Msk)

/**
  * @brief  Judge is EFLASH D BUS Prefetch feature Enable or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 EFLASH D BUS Prefetch feature is Disable
  * @retval 1 EFLASH D BUS Prefetch feature is Enable
  */
#define __LL_EFLASH_IsDBusPrefetchEn(__EFLASH__)        READ_BIT_SHIFT((__EFLASH__)->CR, FLASH_CR_DPE_Msk, FLASH_CR_DPE_Pos)

/**
  * @brief  EFLASH I BUS Prefetch feature Enable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @note   Prefetch feature should not be enabled when CPU frequency is lower than 40MHz
  * @return None
  */
#define __LL_EFLASH_IBusPrefetch_En(__EFLASH__)         SET_BIT((__EFLASH__)->CR, FLASH_CR_IPE_Msk)

/**
  * @brief  EFLASH I BUS Prefetch feature Disable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_IBusPrefetch_Dis(__EFLASH__)        CLEAR_BIT((__EFLASH__)->CR, FLASH_CR_IPE_Msk)

/**
  * @brief  Judge is EFLASH I BUS Prefetch feature Enable or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 EFLASH I BUS Prefetch feature is Disable
  * @retval 1 EFLASH I BUS Prefetch feature is Enable
  */
#define __LL_EFLASH_IsIBusPrefetchEn(__EFLASH__)        READ_BIT_SHIFT((__EFLASH__)->CR, FLASH_CR_IPE_Msk, FLASH_CR_IPE_Pos)

/**
  * @brief  Flash Cache Refresh
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_CacheRefresh(__EFLASH__)            SET_BIT((__EFLASH__)->CR, FLASH_CR_CRS_Msk)

/**
  * @brief  Erase Start
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_EraseStart(__EFLASH__)              SET_BIT((__EFLASH__)->CR, FLASH_CR_ES_Msk)

/**
  * @brief  Judge is Erase Operation Done or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 Erase Operation isn't Done
  * @retval 1 Erase Operation is Done
  */
#define __LL_EFLASH_IsEraseOptDone(__EFLASH__)          (!READ_BIT_SHIFT((__EFLASH__)->CR, FLASH_CR_ES_Msk, FLASH_CR_ES_Pos))

/**
  * @brief  Program Start
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_ProgramStart(__EFLASH__)            SET_BIT((__EFLASH__)->CR, FLASH_CR_PS_Msk)

/**
  * @brief  Judge is Program Operation Done or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 Program Operation isn't Done
  * @retval 1 Program Operation is Done
  */
#define __LL_EFLASH_IsProgramOptDone(__EFLASH__)        (!READ_BIT_SHIFT((__EFLASH__)->CR, FLASH_CR_PS_Msk, FLASH_CR_PS_Pos))


/**
  * @brief  Wakeup/Standby Unlock
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_WakeupStdby_Unlock(__EFLASH__)      SET_BIT((__EFLASH__)->LPR, FLASH_LPR_LCK_Msk)

/**
  * @brief  Wakeup/Standby Lock
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_WakeupStdby_Lock(__EFLASH__)        CLEAR_BIT((__EFLASH__)->LPR, FLASH_LPR_LCK_Msk)

/**
  * @brief  Judge Wakeup/Standby is Lock or Unlock
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 Wakeup/Standby is Lock
  * @retval 1 Wakeup/Standby is Unlock
  */
#define __LL_EFLASH_IsWakeupStdbyUnlock(__EFLASH__)     READ_BIT_SHIFT((__EFLASH__)->LPR, FLASH_LPR_LCK_Msk, FLASH_LPR_LCK_Pos)

/**
  * @brief  Bank0 Lowpower Enable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_Bank0LowPower_En(__EFLASH__)        SET_BIT((__EFLASH__)->LPR, BIT(2))

/**
  * @brief  Bank0 Lowpower Disable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_Bank0LowPower_Dis(__EFLASH__)       CLEAR_BIT((__EFLASH__)->LPR, BIT(2))

/**
  * @brief  Bank1 Lowpower Enable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_Bank1LowPower_En(__EFLASH__)        SET_BIT((__EFLASH__)->LPR, BIT(3))

/**
  * @brief  Bank1 Lowpower Disable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_Bank1LowPower_Dis(__EFLASH__)       CLEAR_BIT((__EFLASH__)->LPR, BIT(3))

/**
  * @brief  Wakeup Start
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_WakeupStart(__EFLASH__)             SET_BIT((__EFLASH__)->LPR, FLASH_LPR_LW_Msk)

/**
  * @brief  Judge is Wakeup Operation Done or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 Wakeup Operation isn't Done
  * @retval 1 Wakeup Operation is Done
  */
#define __LL_EFLASH_IsWakeupOptDone(__EFLASH__)         (!READ_BIT_SHIFT((__EFLASH__)->LPR, FLASH_LPR_LW_Msk, FLASH_LPR_LW_Pos))

/**
  * @brief  Standby Start
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_StdbyStart(__EFLASH__)              SET_BIT((__EFLASH__)->LPR, FLASH_LPR_LS_Msk)

/**
  * @brief  Judge is Standby Operation Done or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 Standby Operation isn't Done
  * @retval 1 Standby Operation is Done
  */
#define __LL_EFLASH_IsStdbyOptDone(__EFLASH__)          (!READ_BIT_SHIFT((__EFLASH__)->LPR, FLASH_LPR_LS_Msk, FLASH_LPR_LS_Pos))


/**
  * @brief  Judge is Program/Erase & Low Power & Read/Write Protect & Option Data Operation Done or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 Program/Erase & Low Power & Read/Write Protect & Option Data Operation isn't Done
  * @retval 1 Program/Erase & Low Power & Read/Write Protect & Option Data Operation is Done
  */
#define __LL_EFLASH_IsIdle(__EFLASH__)                  (!READ_BIT_SHIFT((__EFLASH__)->SR, FLASH_SR_BST_Msk, FLASH_SR_BST_Pos))

/**
  * @brief  Bank Map Status Get
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 Bank 0
  * @retval 1 Bank 1
  */
#define __LL_EFLASH_BankMapSta_Get(__EFLASH__)          READ_BIT_SHIFT((__EFLASH__)->SR, FLASH_SR_BMS_Msk, FLASH_SR_BMS_Pos)

/**
  * @brief  Judge is Read/Write Protect / Option Data Operation Error Status or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 isn't Read/Write Protect / Option Data Operation Error Status
  * @retval 1 is Read/Write Protect / Option Data Operation Error Status
  */
#define __LL_EFLASH_IsRwProtOptDatErrSta(__EFLASH__)    READ_BIT_SHIFT((__EFLASH__)->SR, FLASH_SR_OPE_Msk, FLASH_SR_OPE_Pos)

/**
  * @brief  Read/Write Protect / Option Data Operation Error Status Clear
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_RwProtOptDatErrSta_Clr(__EFLASH__)  WRITE_REG((__EFLASH__)->SR, FLASH_SR_OPE_Msk)

/**
  * @brief  Judge is Program/Erase Operation Error Status or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 isn't Program/Erase Operation Error Status
  * @retval 1 is Program/Erase Operation Error Status
  */
#define __LL_EFLASH_IsPrgEraseOptErrSta(__EFLASH__)     READ_BIT_SHIFT((__EFLASH__)->SR, FLASH_SR_PES_Msk, FLASH_SR_PES_Pos)

/**
  * @brief  Program/Erase Operation Error Status Clear
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_PrgEraseOptErrSta_Clr(__EFLASH__)   WRITE_REG((__EFLASH__)->SR, FLASH_SR_PES_Msk)

/**
  * @brief  Judge is Program Error Status or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 isn't Program Error Status
  * @retval 1 is Program Error Status
  */
#define __LL_EFLASH_IsPrgErrSta(__EFLASH__)             READ_BIT_SHIFT((__EFLASH__)->SR, FLASH_SR_PGE_Msk, FLASH_SR_PGE_Pos)

/**
  * @brief  Program Error Status Clear
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_PrgErrSta_Clr(__EFLASH__)           WRITE_REG((__EFLASH__)->SR, FLASH_SR_PGE_Msk)

/**
  * @brief  Option Bank Map Status Get
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 Bank 0
  * @retval 1 Bank 1
  */
#define __LL_EFLASH_OptBankMapSta_Get(__EFLASH__)       READ_BIT_SHIFT((__EFLASH__)->SR, FLASH_SR_BM_Msk, FLASH_SR_BM_Pos)

/**
  * @brief  Work Mode Status Get
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 Empty Status
  * @retval 1 Normal Status
  */
#define __LL_EFLASH_WorkModeSta_Get(__EFLASH__)         READ_BIT_SHIFT((__EFLASH__)->SR, FLASH_SR_WM_Msk, FLASH_SR_WM_Pos)

/**
  * @brief  Judge is Double Bit Error Pending or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 isn't Double Bit Error Pending
  * @retval 1 is Double Bit Error Pending
  */
#define __LL_EFLASH_IsDblBitErrPnd(__EFLASH__)          READ_BIT_SHIFT((__EFLASH__)->SR, FLASH_SR_DBC_Msk, FLASH_SR_DBC_Pos)

/**
  * @brief  Double Bit Error Pending Clear
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_DblBitErrPnd_Clr(__EFLASH__)        WRITE_REG((__EFLASH__)->SR, FLASH_SR_DBC_Msk)

/**
  * @brief  Judge is Single Bit Error Pending or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 isn't Single Bit Error Pending
  * @retval 1 is Single Bit Error Pending
  */
#define __LL_EFLASH_IsSingleBitErrPnd(__EFLASH__)       READ_BIT_SHIFT((__EFLASH__)->SR, FLASH_SR_SBC_Msk, FLASH_SR_SBC_Pos)

/**
  * @brief  Single Bit Error Pending Clear
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_SingleBitErrPnd_Clr(__EFLASH__)     WRITE_REG((__EFLASH__)->SR, FLASH_SR_SBC_Msk)

/**
  * @brief  Judge is Read/Write Protect / Option Data Operation Done or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 Read/Write Protect / Option Data Operation isn't Done
  * @retval 1 Read/Write Protect / Option Data Operation is Done
  */
#define __LL_EFLASH_IsRwProtOptDatOptDone(__EFLASH__)     (!READ_BIT_SHIFT((__EFLASH__)->SR, FLASH_SR_BSY_Msk, FLASH_SR_BSY_Pos))

/**
  * @brief  Judge is Illegal Operation Error Pending or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 isn't Illegal Operation Error Pending
  * @retval 1 is Illegal Operation Error Pending
  */
#define __LL_EFLASH_IsIllegalOptErr(__EFLASH__)         READ_BIT_SHIFT((__EFLASH__)->SR, FLASH_SR_IOS_Msk, FLASH_SR_IOS_Pos)

/**
  * @brief  Illegal Operation Error Pending Clear
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_IllegalOptErr_Clr(__EFLASH__)       WRITE_REG((__EFLASH__)->SR, FLASH_SR_IOS_Msk)

/**
  * @brief  Judge is Write Protect Error Pending or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 isn't Write Protect Error Pending
  * @retval 1 is Write Protect Error Pending
  */
#define __LL_EFLASH_IsWriteProtErr(__EFLASH__)          READ_BIT_SHIFT((__EFLASH__)->SR, FLASH_SR_WPS_Msk, FLASH_SR_WPS_Pos)

/**
  * @brief  Write Protect Error Pending Clear
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_WriteProtErr_Clr(__EFLASH__)        WRITE_REG((__EFLASH__)->SR, FLASH_SR_WPS_Msk)

/**
  * @brief  Judge is Operation Error Pending or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 isn't Operation Error Pending
  * @retval 1 is Operation Error Pending
  */
#define __LL_EFLASH_IsOptErr(__EFLASH__)                READ_BIT_SHIFT((__EFLASH__)->SR, FLASH_SR_OES_Msk, FLASH_SR_OES_Pos)

/**
  * @brief  Operation Error Pending Clear
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_OptErr_Clr(__EFLASH__)              WRITE_REG((__EFLASH__)->SR, FLASH_SR_OES_Msk)

/**
  * @brief  Judge has Any Extended Error Pending or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 hasn't Any Error Pending
  * @retval 1 has Any Error Pending
  */
#define __LL_EFLASH_IsAnyExError(__EFLASH__)              \
        READ_BIT_SHIFT((__EFLASH__)->SR, FLASH_SR_OPE_Msk | FLASH_SR_PES_Msk | FLASH_SR_PGE_Msk, FLASH_SR_OES_Pos)

/**
  * @brief  Judge has Any Error Pending or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 hasn't Any Error Pending
  * @retval 1 has Any Error Pending
  */
#define __LL_EFLASH_IsAnyError(__EFLASH__)              \
        READ_BIT_SHIFT((__EFLASH__)->SR, FLASH_SR_IOS_Msk | FLASH_SR_WPS_Msk | FLASH_SR_OES_Msk, FLASH_SR_OES_Pos)

/**
  * @brief  All Extended Error Pending Clear
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_AllExErr_Clr(__EFLASH__)            \
        WRITE_REG((__EFLASH__)->SR, FLASH_SR_OPE_Msk | FLASH_SR_PES_Msk | FLASH_SR_PGE_Msk)

/**
  * @brief  All Error Pending Clear
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_AllErr_Clr(__EFLASH__)              \
        WRITE_REG((__EFLASH__)->SR, FLASH_SR_IOS_Msk | FLASH_SR_WPS_Msk | FLASH_SR_OES_Msk)

/**
  * @brief  All Interrupt Pending Get
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return All Interrupt Pending
  */
#define __LL_EFLASH_AllIntPnd_Get(__EFLASH__)           READ_REG((__EFLASH__)->SR)


/**
  * @brief  Program Data 0 Set
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @param  dat Program Data 0
  * @return None
  */
#define __LL_EFLASH_ProgData0_Set(__EFLASH__, dat)      WRITE_REG((__EFLASH__)->PDR0, dat)


/**
  * @brief  Program Data 1 Set
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @param  dat Program Data 1
  * @return None
  */
#define __LL_EFLASH_ProgData1_Set(__EFLASH__, dat)      WRITE_REG((__EFLASH__)->PDR1, dat)


/**
  * @brief  Erase Mode Set
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @param  mode Erase Mode @ref EFLASH_EraseModeETypeDef
  * @return None
  */
#define __LL_EFLASH_EraseMode_Set(__EFLASH__, mode)     \
        MODIFY_REG((__EFLASH__)->PAR, FLASH_PAR_EM_Msk, (((mode) & 0x3UL) << FLASH_PAR_EM_Pos))

/**
  * @brief  Erase Sector Number Set
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @param  num Erase Sector Number
  * @return None
  */
#define __LL_EFLASH_EraseSectorNum_Set(__EFLASH__, num) \
        MODIFY_REG((__EFLASH__)->PAR, FLASH_PAR_PA_Msk, (((num) & 0x3fUL) << FLASH_PAR_PA_Pos))

/**
  * @brief  Erase Sector Number Get
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return Erase Sector Number
  */
#define __LL_EFLASH_EraseSectorNum_Get(__EFLASH__)      \
        READ_BIT_SHIFT((__EFLASH__)->PAR, FLASH_PAR_PA_Msk, FLASH_PAR_PA_Pos)

/**
  * @brief  Program Address Set
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @param  addr Program Address
  * @return None
  */
#define __LL_EFLASH_ProgAddr_Set(__EFLASH__, addr)      \
        MODIFY_REG((__EFLASH__)->PAR, FLASH_PAR_PA_Msk, (((addr) & 0x7ffffUL) << FLASH_PAR_PA_Pos))


/**
  * @brief  Read/Write Protect / Option Data Lock
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_RwProtOptDat_Lock(__EFLASH__)       SET_BIT((__EFLASH__)->KR, FLASH_KR_PLK_Msk)

/**
  * @brief  Judge Read/Write Protect / Option Data is Lock or Unlock
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 Read/Write Protect / Option Data is Unlock
  * @retval 1 Read/Write Protect / Option Data is Lock
  */
#define __LL_EFLASH_IsRwProtOptDatLock(__EFLASH__)      (!READ_BIT_SHIFT((__EFLASH__)->KR, FLASH_KR_PLK_Msk, FLASH_KR_PLK_Pos))

/**
  * @brief  Key Set
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @param  key Key
  * @return None
  */
#define __LL_EFLASH_Key_Set(__EFLASH__, key)            \
        MODIFY_REG((__EFLASH__)->KR, FLASH_KR_KEY_Msk, (((key) & 0xffffUL) << FLASH_KR_KEY_Pos))


/**
  * @brief  Read Protect Register Value Set
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @param  val Read Protect Register Value
  * @return None
  */
#define __LL_EFLASH_ReadProtReg_Set(__EFLASH__, val)    WRITE_REG((__EFLASH__)->RPR, ((val) & 0xffUL))


/**
  * @brief  Write Protect Register Value Set
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @param  val Write Protect Register Value
  * @return None
  */
#define __LL_EFLASH_WriteProtReg_Set(__EFLASH__, val)   WRITE_REG((__EFLASH__)->WPR, val & 0xffffffffUL)

/**
  * @brief  Write Protect Area Enable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @param  area Write Protect Area @ref EFLASH_WriteProtAreaETypeDef
  * @return None
  */
#define __LL_EFLASH_WriteProtArea_En(__EFLASH__, area)  CLEAR_BIT((__EFLASH__)->WPR, area & 0xffffffffUL)

/**
  * @brief  Write Protect Register Value Read
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return Write Protect Register Value
  */
#define __LL_EFLASH_WriteProtArea_Read(__EFLASH__)      READ_REG((__EFLASH__)->WPR)

/**
  * @brief  Write Protect Area Disable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @param  area Write Protect Area  @ref EFLASH_WriteProtAreaETypeDef
  * @return None
  */
#define __LL_EFLASH_WriteProtArea_Dis(__EFLASH__, area) SET_BIT((__EFLASH__)->WPR, area)


/**
  * @brief  Bank Address Mapping Set
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @param  bank Bank Address Mapping bank @ref EFLASH_BankAddrMapETypeDef
  * @return None
  */
#define __LL_EFLASH_BankAddrMap(__EFLASH__, bank)       \
        MODIFY_REG((__EFLASH__)->OPDR, FLASH_OPDR_MAP_Msk, (((bank) & 0xfUL) << FLASH_OPDR_MAP_Pos))

/**
  * @brief  Bank Address Mapping Get
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0xA   Bank1 Mapping
  * @retval Other Bank0 Mapping
  */
#define __LL_EFLASH_BankAddrMap_Get(__EFLASH__)            READ_BIT_SHIFT((__EFLASH__)->OPDR, FLASH_OPDR_MAP_Msk, FLASH_OPDR_MAP_Pos)

/**
  * @brief  Bank Mode Config
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @param  mode Bank mode
  * @return None
  */
#define __LL_EFLASH_BankMode_Cfg(__EFLASH__, mode)      \
        MODIFY_REG((__EFLASH__)->OPDR, FLASH_OPDR_BMD_Msk, (((mode) & 0xfUL) << FLASH_OPDR_BMD_Pos))

/**
  * @brief  Bank Mode Get
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0xA   Bank mode Double
  * @retval Other Bank mode Single
  */
#define __LL_EFLASH_BankMode_Get(__EFLASH__)            READ_BIT_SHIFT((__EFLASH__)->OPDR, FLASH_OPDR_BMD_Msk, FLASH_OPDR_BMD_Pos)

/**
  * @brief  WWDG Enable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_WWDG_En(__EFLASH__)                 \
        MODIFY_REG((__EFLASH__)->OPDR, FLASH_OPDR_WWEN_Msk, 0xaUL << FLASH_OPDR_WWEN_Pos)

/**
  * @brief  WWDG Disable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_WWDG_Dis(__EFLASH__)                \
        MODIFY_REG((__EFLASH__)->OPDR, FLASH_OPDR_WWEN_Msk, 0xfUL << FLASH_OPDR_WWEN_Pos)

/**
  * @brief  Judge is WWDG Enable or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 WWDG is Disable
  * @retval 1 WWDG is Enable
  */
#define __LL_EFLASH_Is_WWDGEn(__EFLASH__)               \
        (READ_BIT_SHIFT((__EFLASH__)->OPDR, FLASH_OPDR_WWEN_Msk, FLASH_OPDR_WWEN_Pos) == 0xa)

/**
  * @brief  IWDG Enable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_IWDG_En(__EFLASH__)                 \
        MODIFY_REG((__EFLASH__)->OPDR, FLASH_OPDR_IWEN_Msk, 0xaUL << FLASH_OPDR_IWEN_Pos)

/**
  * @brief  IWDG Disable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_IWDG_Dis(__EFLASH__)                \
        MODIFY_REG((__EFLASH__)->OPDR, FLASH_OPDR_IWEN_Msk, 0xfUL << FLASH_OPDR_IWEN_Pos)

/**
  * @brief  Judge is IWDG Enable or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 IWDG is Disable
  * @retval 1 IWDG is Enable
  */
#define __LL_EFLASH_Is_IWDGEn(__EFLASH__)               \
        (READ_BIT_SHIFT((__EFLASH__)->OPDR, FLASH_OPDR_IWEN_Msk, FLASH_OPDR_IWEN_Pos) == 0xa)

/**
  * @brief  Power On ECC Bypass Enable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_PowerOnECCBypass_En(__EFLASH__)     \
        MODIFY_REG((__EFLASH__)->OPDR, FLASH_OPDR_EBP_Msk, 0xfUL << FLASH_OPDR_EBP_Pos)

/**
  * @brief  Power On ECC Bypass Disable
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_PowerOnECCBypass_Dis(__EFLASH__)    \
        MODIFY_REG((__EFLASH__)->OPDR, FLASH_OPDR_EBP_Msk, 0xaUL << FLASH_OPDR_EBP_Pos)

/**
  * @brief  Judge is Power On ECC Bypass Enable or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 Power On ECC Bypass is Disable
  * @retval 1 Power On ECC Bypass is Enable
  */
#define __LL_EFLASH_Is_PowerOnECCBypassEn(__EFLASH__)   \
        (!(READ_BIT_SHIFT((__EFLASH__)->OPDR, FLASH_OPDR_EBP_Msk, FLASH_OPDR_EBP_Pos) == 0xa))

/**
  * @brief  BOR Voltage Limit Config
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @param  vol BOR Voltage Limit @ref EFLASH_BORVolLimitETypeDef
  * @return None
  */
#define __LL_EFLASH_BORVolLimit_Cfg(__EFLASH__, vol)    \
        MODIFY_REG((__EFLASH__)->OPDR, FLASH_OPDR_BORLV_Msk, (((vol) & 0x3UL) << FLASH_OPDR_BORLV_Pos))

/**
  * @brief  BOR Voltage Limit Read
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return BOR Voltage Limit
  */
#define __LL_EFLASH_BORVolLimit_Read(__EFLASH__)         \
        READ_BIT_SHIFT((__EFLASH__)->OPDR, FLASH_OPDR_BORLV_Msk, FLASH_OPDR_BORLV_Pos)

/**
  * @brief  Boot Selection Set
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @param  sel Boot Selection @ref EFLASH_BootSelETypeDef
  * @return None
  */
#define __LL_EFLASH_BootSel_Set(__EFLASH__, sel)        \
        MODIFY_REG((__EFLASH__)->OPDR, FLASH_OPDR_BSEL_Msk, (((sel) & 0x7UL) << FLASH_OPDR_BSEL_Pos))

/**
  * @brief  Boot Selection Read
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return Boot Selection
  */
#define __LL_EFLASH_BootSel_Read(__EFLASH__)            \
        READ_BIT_SHIFT((__EFLASH__)->OPDR, FLASH_OPDR_BSEL_Msk, FLASH_OPDR_BSEL_Pos)

/**
  * @brief  Boot Lock
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_Boot_Lock(__EFLASH__)               \
        MODIFY_REG((__EFLASH__)->OPDR, FLASH_OPDR_BLK_Msk, 0xaUL << FLASH_OPDR_BLK_Pos)

/**
  * @brief  Judge is Boot Lock or not
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @retval 0 Boot is Unlock
  * @retval 1 Boot is Lock
  */
#define __LL_EFLASH_Is_BootLock(__EFLASH__)             \
        (READ_BIT_SHIFT((__EFLASH__)->OPDR, FLASH_OPDR_BLK_Msk, FLASH_OPDR_BLK_Pos) == 0xa)

/**
  * @brief  Boot Unlock
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return None
  */
#define __LL_EFLASH_Boot_Unlock(__EFLASH__)             \
        MODIFY_REG((__EFLASH__)->OPDR, FLASH_OPDR_BLK_Msk, 0xfUL << FLASH_OPDR_BLK_Pos)

/**
  * @brief  OPDR Read
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return OPDR
  */
#define __LL_EFLASH_OPDR_Read(__EFLASH__)               READ_REG((__EFLASH__)->OPDR)

/**
  * @brief  ECC 1Bit Address Get
  * @note   Single Bank, align address by 128bit. Double Bank, align address by 64bit.
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return ECC Error Address for one bit
  */
#define __LL_EFLASH_OneBitECCErrAddr_Get(__EFLASH__)      READ_BIT_SHIFT((__EFLASH__)->EAR0, FLASH_EAR0_EAD1_Msk, FLASH_EAR0_EAD1_Pos)

/**
  * @brief  ECC nBit Address Get
  * @note   Single Bank, align address by 128bit. Double Bank, align address by 64bit.
  * @param  __EFLASH__ Specifies EFLASH peripheral
  * @return ECC Error Address for multi-bit
  */
#define __LL_EFLASH_MultiBitECCErrAddr_Get(__EFLASH__)    READ_BIT_SHIFT((__EFLASH__)->EAR1, FLASH_EAR1_EADn_Msk, FLASH_EAR1_EADn_Pos)

/**
  * @brief  Judge EFLASH program address or size is align 8bytes or not
  * @param  n program address or size to judge
  * @retval 0 EFLASH program address or size isn't align 8bytes
  * @retval 1 EFLASH program address or size is align 8bytes
  */
#define __LL_EFLASH_IsProgAddrOrSizeAlign8Bytes(n)      (!((n) % 8))

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup EFLASH_LL_Exported_Types EFLASH LL Exported Types
  * @brief    EFLASH LL Exported Types
  * @{
  */

/**
  * @brief EFLASH Operation definition
  */
typedef enum {
    EFLASH_OPT_PROG,                        /*!< EFLASH Operation Program       */
    EFLASH_OPT_ERASE,                       /*!< EFLASH Operation Erase         */
    EFLASH_OPT_STDBY,                       /*!< EFLASH Operation Standby       */
    EFLASH_OPT_WAKEUP,                      /*!< EFLASH Operation Wakeup        */
    EFLASH_OPT_RW_PROT,                     /*!< EFLASH Operation RW Protect    */
    EFLASH_OPT_OPT_DAT,                     /*!< EFLASH Operation Option Data   */
} EFLASH_OptETypeDef;

/**
  * @brief EFLASH Read Protection Level Definition
  * @note When set read protection to level 2, it's no more possible to go back to level 1 or 0
  */
typedef enum {
    EFLASH_READ_PROT_LVL_0 = 0xAA,          /*!< EFLASH Read Protection Level 0 */
    EFLASH_READ_PROT_LVL_1 = 0xFF,          /*!< EFLASH Read Protection Level 1 */
    EFLASH_READ_PROT_LVL_2 = 0xCC,          /*!< EFLASH Read Protection Level 2 */
} EFLASH_ReadProtLvlETypeDef;

/**
  * @brief EFLASH Write Protect Area definition
  * @note  Each area control 2 sectors
  */
typedef enum {
    EFLASH_WRITE_PROT_AREA_1   = BIT(0),                /*!< EFLASH Write Protection Area 1     */
    EFLASH_WRITE_PROT_AREA_2   = BIT(1),                /*!< EFLASH Write Protection Area 2     */
    EFLASH_WRITE_PROT_AREA_3   = BIT(2),                /*!< EFLASH Write Protection Area 3     */
    EFLASH_WRITE_PROT_AREA_4   = BIT(3),                /*!< EFLASH Write Protection Area 4     */
    EFLASH_WRITE_PROT_AREA_5   = BIT(4),                /*!< EFLASH Write Protection Area 5     */
    EFLASH_WRITE_PROT_AREA_6   = BIT(5),                /*!< EFLASH Write Protection Area 6     */
    EFLASH_WRITE_PROT_AREA_7   = BIT(6),                /*!< EFLASH Write Protection Area 7     */
    EFLASH_WRITE_PROT_AREA_8   = BIT(7),                /*!< EFLASH Write Protection Area 8     */
    EFLASH_WRITE_PROT_AREA_9   = BIT(8),                /*!< EFLASH Write Protection Area 9     */
    EFLASH_WRITE_PROT_AREA_10  = BIT(9),                /*!< EFLASH Write Protection Area 10    */
    EFLASH_WRITE_PROT_AREA_11  = BIT(10),               /*!< EFLASH Write Protection Area 11    */
    EFLASH_WRITE_PROT_AREA_12  = BIT(11),               /*!< EFLASH Write Protection Area 12    */
    EFLASH_WRITE_PROT_AREA_13  = BIT(12),               /*!< EFLASH Write Protection Area 13    */
    EFLASH_WRITE_PROT_AREA_14  = BIT(13),               /*!< EFLASH Write Protection Area 14    */
    EFLASH_WRITE_PROT_AREA_15  = BIT(14),               /*!< EFLASH Write Protection Area 15    */
    EFLASH_WRITE_PROT_AREA_16  = BIT(15),               /*!< EFLASH Write Protection Area 16    */
    EFLASH_WRITE_PROT_AREA_17  = BIT(16),               /*!< EFLASH Write Protection Area 17    */
    EFLASH_WRITE_PROT_AREA_18  = BIT(17),               /*!< EFLASH Write Protection Area 18    */
    EFLASH_WRITE_PROT_AREA_19  = BIT(18),               /*!< EFLASH Write Protection Area 19    */
    EFLASH_WRITE_PROT_AREA_20  = BIT(19),               /*!< EFLASH Write Protection Area 20    */
    EFLASH_WRITE_PROT_AREA_21  = BIT(20),               /*!< EFLASH Write Protection Area 21    */
    EFLASH_WRITE_PROT_AREA_22  = BIT(21),               /*!< EFLASH Write Protection Area 22    */
    EFLASH_WRITE_PROT_AREA_23  = BIT(22),               /*!< EFLASH Write Protection Area 23    */
    EFLASH_WRITE_PROT_AREA_24  = BIT(23),               /*!< EFLASH Write Protection Area 24    */
    EFLASH_WRITE_PROT_AREA_25  = BIT(24),               /*!< EFLASH Write Protection Area 25    */
    EFLASH_WRITE_PROT_AREA_26  = BIT(25),               /*!< EFLASH Write Protection Area 26    */
    EFLASH_WRITE_PROT_AREA_27  = BIT(26),               /*!< EFLASH Write Protection Area 27    */
    EFLASH_WRITE_PROT_AREA_28  = BIT(27),               /*!< EFLASH Write Protection Area 28    */
    EFLASH_WRITE_PROT_AREA_29  = BIT(28),               /*!< EFLASH Write Protection Area 29    */
    EFLASH_WRITE_PROT_AREA_30  = BIT(29),               /*!< EFLASH Write Protection Area 30    */
    EFLASH_WRITE_PROT_AREA_31  = BIT(30),               /*!< EFLASH Write Protection Area 31    */
    EFLASH_WRITE_PROT_AREA_32  = (int32_t)(BIT(31)),    /*!< EFLASH Write Protection Area 32    */
    EFLASH_WRITE_PROT_AREA_ALL = (int32_t)0xFFFFFFFF,   /*!< EFLASH Write Protection Area ALL   */
    EFLASH_WRITE_PROT_AREA_Msk = (int32_t)0xFFFFFFFF,   /*!< EFLASH Write Protection Area Mask  */
} EFLASH_WriteProtAreaETypeDef;

/**
  * @brief EFLASH Erase Mode Definition
  */
typedef enum {
    EFLASH_ERASE_MODE_SECTOR = 0,           /*!< Erase Mode Sector  */
    EFLASH_ERASE_MODE_BANK0,                /*!< Erase Mode Bank0   */
    EFLASH_ERASE_MODE_BANK1,                /*!< Erase Mode Bank1   */
    EFLASH_ERASE_MODE_CHIP,                 /*!< Erase Mode Chip    */
} EFLASH_EraseModeETypeDef;

/**
  * @brief EFLASH Bank Address Mapping Definition
  */
typedef enum {
    EFLASH_BANK_ADDR_MAP_BANK0 = 0xF,       /*!< Bank Address Mapping Bank 0    */
    EFLASH_BANK_ADDR_MAP_BANK1 = 0xA,       /*!< Bank Address Mapping Bank 1    */
} EFLASH_BankAddrMapETypeDef;

/**
  * @brief EFLASH Bank Mode Definition
  * @note  Only Valid in 256K Mode
  */
typedef enum {
    EFLASH_BANK_MODE_SINGLE = 0xF,          /*!< Bank Mode Single   */
    EFLASH_BANK_MODE_DOUBLE = 0xA,          /*!< Bank Mode Double   */
} EFLASH_BankModeETypeDef;

/**
  * @brief EFLASH BOR Voltage Limit Definition
  */
typedef enum {
    EFLASH_BOR_VOL_LIMIT_2V4 = 0,      /*!< BOR Voltage Limit 2.4V  */
    EFLASH_BOR_VOL_LIMIT_2V55,         /*!< BOR Voltage Limit 2.55V */
    EFLASH_BOR_VOL_LIMIT_2V7,          /*!< BOR Voltage Limit 2.7V  */
    EFLASH_BOR_VOL_LIMIT_2V85,         /*!< BOR Voltage Limit 2.85V */
} EFLASH_BORVolLimitETypeDef;

/**
  * @brief EFLASH Boot Selection Definition
  */
typedef enum {
    EFLASH_BOOT_SEL_0 = 0,                  /*!< Boot Selection 0   */
    EFLASH_BOOT_SEL_1,                      /*!< Boot Selection 1   */
    EFLASH_BOOT_SEL_2,                      /*!< Boot Selection 2   */
    EFLASH_BOOT_SEL_3,                      /*!< Boot Selection 3   */
    EFLASH_BOOT_SEL_4,                      /*!< Boot Selection 4   */
    EFLASH_BOOT_SEL_5,                      /*!< Boot Selection 5   */
    EFLASH_BOOT_SEL_6,                      /*!< Boot Selection 6   */
    EFLASH_BOOT_SEL_7,                      /*!< Boot Selection 7   */
} EFLASH_BootSelETypeDef;

/**
  * @brief EFLASH User Option Operation Definition
  */
typedef enum {
    EFLASH_USER_OPT_BOOT_LOCK_CFG,          /*!< Boot Lock Config       */
    EFLASH_USER_OPT_BOOT_SEL,               /*!< Boot Selection         */
    EFLASH_USER_OPT_BOR_VOL_LMT_CFG,        /*!< BOR Vol Limit Config   */
    EFLASH_USER_OPT_PWRON_ECC_BYPASS,       /*!< Power On ECC Bypass    */
    EFLASH_USER_OPT_IWDG_EN,                /*!< IWDG Enable            */
    EFLASH_USER_OPT_WWDG_EN,                /*!< WWDG Enable            */
    EFLASH_USER_OPT_BANK_MODE_CFG,          /*!< Bank Mode Config       */
    EFLASH_USER_OPT_BANK_MAP_CFG,           /*!< Bank Mapping Config    */
} EFLASH_UserOptETypeDef;


/**
  * @brief EFLASH User Config
  */
typedef struct __EFLASH_UserCfgTypeDef {
    bool iwdg_en;                           /*!< IWDG Enable                    */
    bool wwdg_en;                           /*!< WWDG Enable                    */
    bool boot_lock_en;                      /*!< Boot Lock Enable               */
    bool pwron_ecc_bypass_en;               /*!< Power On ECC Bypass Enable     */

    EFLASH_BootSelETypeDef     boot_sel;    /*!< Boot Selection                 */
    EFLASH_BankModeETypeDef    bank_mode;   /*!< Bank Mode(Only Valid in 256K)  */
    EFLASH_BankAddrMapETypeDef bank_map;    /*!< Bank Address Mapping           */
    EFLASH_BORVolLimitETypeDef bor_vol_lmt; /*!< BOR Voltage Limit              */
} EFLASH_UserCfgTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup EFLASH_LL_Exported_Functions
  * @{
  */

/** @addtogroup EFLASH_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_EFLASH_ReadProtLvlCfg(EFLASH_TypeDef *Instance, EFLASH_ReadProtLvlETypeDef level);
LL_StatusETypeDef LL_EFLASH_WriteProtCfg(EFLASH_TypeDef *Instance, EFLASH_WriteProtAreaETypeDef area, bool write_prot_en);
LL_StatusETypeDef LL_EFLASH_OptDatUserCfg(EFLASH_TypeDef *Instance, EFLASH_UserCfgTypeDef *cfg);
LL_StatusETypeDef LL_EFLASH_UserOptCfg(EFLASH_TypeDef *Instance, EFLASH_UserOptETypeDef user_opt, uint32_t opt_param);

LL_StatusETypeDef LL_EFLASH_BankMapCfg(EFLASH_TypeDef *Instance, EFLASH_BankAddrMapETypeDef bank_map);
LL_StatusETypeDef LL_EFLASH_BankModeCfg(EFLASH_TypeDef *Instance, EFLASH_BankModeETypeDef bank_mode);
LL_StatusETypeDef LL_EFLASH_BootSelCfg(EFLASH_TypeDef *Instance, EFLASH_BootSelETypeDef boot_sel);
LL_StatusETypeDef LL_EFLASH_BORVolLimitCfg(EFLASH_TypeDef *Instance, EFLASH_BORVolLimitETypeDef bor_vol_lmt);
/**
  * @}
  */


/** @addtogroup EFLASH_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_EFLASH_WaitForBusyState(EFLASH_TypeDef *Instance, uint32_t timeout);
LL_StatusETypeDef LL_EFLASH_WaitForLastOptCplt(EFLASH_TypeDef *Instance, EFLASH_OptETypeDef last_opt, uint32_t timeout);
/**
  * @}
  */


/** @addtogroup EFLASH_LL_Exported_Functions_Group3
  * @{
  */
uint32_t LL_EFLASH_ChipSize_Get(EFLASH_TypeDef *Instance);
uint32_t LL_EFLASH_SectorSize_Get(EFLASH_TypeDef *Instance);
uint32_t LL_EFLASH_SectorNums_Get(EFLASH_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup EFLASH_LL_Exported_Functions_Group4
  * @{
  */
uint32_t LL_EFLASH_Program(EFLASH_TypeDef *Instance, uint32_t addr, uint8_t *buf, uint32_t size);
uint32_t LL_EFLASH_EraseMultiSector(EFLASH_TypeDef *Instance, uint32_t sector_start, uint32_t num);
LL_StatusETypeDef LL_EFLASH_EraseSector(EFLASH_TypeDef *Instance, uint32_t sector_num);
LL_StatusETypeDef LL_EFLASH_EraseChip(EFLASH_TypeDef *Instance);
LL_StatusETypeDef LL_EFLASH_EraseBank0(EFLASH_TypeDef *Instance);
LL_StatusETypeDef LL_EFLASH_EraseBank1(EFLASH_TypeDef *Instance);
uint32_t LL_EFLASH_Verify(EFLASH_TypeDef *Instance, uint32_t addr, uint8_t *buf, uint32_t size);
/**
  * @}
  */


/** @addtogroup EFLASH_LL_Exported_Functions_Lock
  * @{
  */
LL_StatusETypeDef LL_EFLASH_ProgErase_Unlock(EFLASH_TypeDef *Instance);
LL_StatusETypeDef LL_EFLASH_ProgErase_Lock(EFLASH_TypeDef *Instance);
LL_StatusETypeDef LL_EFLASH_RWProtOptDat_Unlock(EFLASH_TypeDef *Instance);
LL_StatusETypeDef LL_EFLASH_RWProtOptDat_Lock(EFLASH_TypeDef *Instance);
void LL_FLASH_ReadWriteProt_Launch(EFLASH_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup EFLASH_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_EFLASH_IRQHandler(EFLASH_TypeDef *Instance);

void LL_EFLASH_OptErrCallback(EFLASH_TypeDef *Instance);
void LL_EFLASH_WriteProtErrCallback(EFLASH_TypeDef *Instance);
void LL_EFLASH_IllegalOptErrCallback(EFLASH_TypeDef *Instance);
void LL_EFLASH_SingleBitErrCallback(EFLASH_TypeDef *Instance);
/**
  * @}
  */

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_EFLASH_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

