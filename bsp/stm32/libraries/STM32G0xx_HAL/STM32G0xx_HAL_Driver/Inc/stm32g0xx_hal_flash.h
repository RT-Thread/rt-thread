/**
  ******************************************************************************
  * @file    stm32g0xx_hal_flash.h
  * @author  MCD Application Team
  * @brief   Header file of FLASH HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32G0xx_HAL_FLASH_H
#define STM32G0xx_HAL_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal_def.h"

/** @addtogroup STM32G0xx_HAL_Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup FLASH_Exported_Types FLASH Exported Types
  * @{
  */

/**
  * @brief  FLASH Erase structure definition
  */
typedef struct
{
  uint32_t TypeErase;   /*!< Mass erase or page erase.
                             This parameter can be a value of @ref FLASH_Type_Erase */
  uint32_t Banks;       /*!< Select bank to erase.
                             This parameter must be a value of @ref FLASH_Banks
                             (FLASH_BANK_BOTH should be used only for mass erase) */
  uint32_t Page;        /*!< Initial Flash page to erase when page erase is enabled
                             This parameter must be a value between 0 and (FLASH_PAGE_NB - 1) */
  uint32_t NbPages;     /*!< Number of pages to be erased.
                             This parameter must be a value between 1 and (FLASH_PAGE_NB - value of initial page)*/
} FLASH_EraseInitTypeDef;

/**
  * @brief  FLASH Option Bytes Program structure definition
  */
typedef struct
{
  uint32_t OptionType;        /*!< Option byte to be configured.
                                   This parameter can be a combination of the values of @ref FLASH_OB_Type */
  uint32_t WRPArea;           /*!< Write protection area to be programmed (used for OPTIONBYTE_WRP).
                                   Only one WRP area could be programmed at the same time.
                                   This parameter can be value of @ref FLASH_OB_WRP_Area */
  uint32_t WRPStartOffset;    /*!< Write protection start offset (used for OPTIONBYTE_WRP).
                                   This parameter must be a value between 0 and [FLASH_PAGE_NB - 1]*/
  uint32_t WRPEndOffset;      /*!< Write protection end offset (used for OPTIONBYTE_WRP).
                                   This parameter must be a value between WRPStartOffset and [FLASH_PAGE_NB - 1] */
  uint32_t RDPLevel;          /*!< Set the read protection level (used for OPTIONBYTE_RDP).
                                   This parameter can be a value of @ref FLASH_OB_Read_Protection */
  uint32_t USERType;          /*!< User option byte(s) to be configured (used for OPTIONBYTE_USER).
                                   This parameter can be a combination of @ref FLASH_OB_USER_Type */
  uint32_t USERConfig;        /*!< Value of the user option byte (used for OPTIONBYTE_USER).
                                   This parameter can be a combination of
                                   @ref FLASH_OB_USER_BOR_ENABLE(*),
                                   @ref FLASH_OB_USER_BOR_LEVEL(*),
                                   @ref FLASH_OB_USER_RESET_CONFIG(*),
                                   @ref FLASH_OB_USER_nRST_STOP,
                                   @ref FLASH_OB_USER_nRST_STANDBY,
                                   @ref FLASH_OB_USER_nRST_SHUTDOWN(*),
                                   @ref FLASH_OB_USER_IWDG_SW,
                                   @ref FLASH_OB_USER_IWDG_STOP,
                                   @ref FLASH_OB_USER_IWDG_STANDBY,
                                   @ref FLASH_OB_USER_WWDG_SW,
                                   @ref FLASH_OB_USER_SRAM_PARITY,
                                   @ref FLASH_OB_USER_BANK_SWAP(*),
                                   @ref FLASH_OB_USER_DUAL_BANK(*),
                                   @ref FLASH_OB_USER_nBOOT_SEL,
                                   @ref FLASH_OB_USER_nBOOT1,
                                   @ref FLASH_OB_USER_nBOOT0,
                                   @ref FLASH_OB_USER_INPUT_RESET_HOLDER(*)
                                   @note (*) availability depends on devices */
#if defined(FLASH_PCROP_SUPPORT)
  uint32_t PCROPConfig;       /*!< Configuration of the PCROP (used for OPTIONBYTE_PCROP).
                                   This parameter must be a combination of @ref FLASH_OB_PCROP_ZONE
                                   and @ref FLASH_OB_PCROP_RDP. Note that once set, Pcrop erase on RDP level 1 regression
                                   (PCROP_RDP bit) can not be reset. It will be reset by mass erase */
  uint32_t PCROP1AStartAddr;  /*!< PCROP Start address (used for OPTIONBYTE_PCROP). It represents first address of start block
                                   to protect. Make sure this parameter is multiple of PCROP granularity: 512 Bytes.*/
  uint32_t PCROP1AEndAddr;    /*!< PCROP End address (used for OPTIONBYTE_PCROP). It represents first address of end block
                                   to protect. Make sure this parameter is multiple of PCROP granularity: 512 Bytes.*/
  uint32_t PCROP1BStartAddr;  /*!< PCROP Start address (used for OPTIONBYTE_PCROP). It represents first address of start block
                                   to protect. Make sure this parameter is multiple of PCROP granularity: 512 Bytes.*/
  uint32_t PCROP1BEndAddr;    /*!< PCROP End address (used for OPTIONBYTE_PCROP). It represents first address of end block
                                   to protect. Make sure this parameter is multiple of PCROP granularity: 512 Bytes.*/
#if defined(FLASH_DBANK_SUPPORT)
  uint32_t PCROP2AStartAddr;  /*!< PCROP Start address (used for OPTIONBYTE_PCROP). It represents first address of start block
                                   to protect. Make sure this parameter is multiple of PCROP granularity: 512 Bytes.*/
  uint32_t PCROP2AEndAddr;    /*!< PCROP End address (used for OPTIONBYTE_PCROP). It represents first address of end block
                                   to protect. Make sure this parameter is multiple of PCROP granularity: 512 Bytes.*/
  uint32_t PCROP2BStartAddr;  /*!< PCROP Start address (used for OPTIONBYTE_PCROP). It represents first address of start block
                                   to protect. Make sure this parameter is multiple of PCROP granularity: 512 Bytes.*/
  uint32_t PCROP2BEndAddr;    /*!< PCROP End address (used for OPTIONBYTE_PCROP). It represents first address of end block
                                   to protect. Make sure this parameter is multiple of PCROP granularity: 512 Bytes.*/
#endif /* FLASH_DBANK_SUPPORT */
#endif /* FLASH_PCROP_SUPPORT */
#if defined(FLASH_SECURABLE_MEMORY_SUPPORT)
  uint32_t BootEntryPoint;    /*!< Allow to force a unique boot entry point to Flash or system Flash */
  uint32_t SecSize;           /*!< This parameter defines securable memory area width in number of pages starting from Flash base address.
                                   This parameter must be a value between [0] and [FLASH_PAGE_NB],
                                   [0] meaning no secure area defined, [1] meaning first page only protected, etc... */
#if defined(FLASH_DBANK_SUPPORT)
  uint32_t SecSize2;           /*!< This parameter defines securable memory area width in number of pages starting from 2nd Bank start address.
                                   This parameter must be a value between [0] and [FLASH_PAGE_NB],
                                   [0] meaning no secure area defined, [1] meaning first page only protected, etc... */
#endif /* FLASH_SECURABLE_MEMORY_SUPPORT */
#endif /* FLASH_DBANK_SUPPORT */
} FLASH_OBProgramInitTypeDef;

/**
  * @brief  FLASH handle Structure definition
  */
typedef struct
{
  HAL_LockTypeDef   Lock;              /* FLASH locking object */
  uint32_t          ErrorCode;         /* FLASH error code */
  uint32_t          ProcedureOnGoing;  /* Internal variable to indicate which procedure is ongoing or not in IT context */
  uint32_t          Address;           /* Internal variable to save address selected for program in IT context */
  uint32_t          Banks;             /* Internal variable to save current bank selected during erase in IT context */
  uint32_t          Page;              /* Internal variable to define the current page which is erasing in IT context */
  uint32_t          NbPagesToErase;    /* Internal variable to save the remaining pages to erase in IT context */
} FLASH_ProcessTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup FLASH_Exported_Constants FLASH Exported Constants
  * @{
  */
/** @defgroup FLASH_Keys FLASH Keys
  * @{
  */
#define FLASH_KEY1                      0x45670123U   /*!< Flash key1 */
#define FLASH_KEY2                      0xCDEF89ABU   /*!< Flash key2: used with FLASH_KEY1
                                                           to unlock the FLASH registers access */
#define FLASH_OPTKEY1                   0x08192A3BU   /*!< Flash option byte key1 */
#define FLASH_OPTKEY2                   0x4C5D6E7FU   /*!< Flash option byte key2: used with FLASH_OPTKEY1
                                                           to allow option bytes operations */
/**
  * @}
  */

/** @defgroup FLASH_Latency FLASH Latency
  * @{
  */
#define FLASH_LATENCY_0                 0x00000000UL        /*!< FLASH Zero wait state */
#define FLASH_LATENCY_1                 FLASH_ACR_LATENCY_0 /*!< FLASH One wait state */
#define FLASH_LATENCY_2                 FLASH_ACR_LATENCY_1 /*!< FLASH Two wait states */
/**
  * @}
  */

/** @defgroup FLASH_Flags FLASH Flags Definition
  * @{
  */
#define FLASH_FLAG_EOP                  ((FLASH_FLAG_SR_ID << FLASH_FLAG_REG_POS) | FLASH_SR_EOP_Pos)         /*!< FLASH End of operation flag */
#define FLASH_FLAG_OPERR                ((FLASH_FLAG_SR_ID << FLASH_FLAG_REG_POS) | FLASH_SR_OPERR_Pos)       /*!< FLASH Operation error flag */
#define FLASH_FLAG_PROGERR              ((FLASH_FLAG_SR_ID << FLASH_FLAG_REG_POS) | FLASH_SR_PROGERR_Pos)     /*!< FLASH Programming error flag */
#define FLASH_FLAG_WRPERR               ((FLASH_FLAG_SR_ID << FLASH_FLAG_REG_POS) | FLASH_SR_WRPERR_Pos)      /*!< FLASH Write protection error flag */
#define FLASH_FLAG_PGAERR               ((FLASH_FLAG_SR_ID << FLASH_FLAG_REG_POS) | FLASH_SR_PGAERR_Pos)      /*!< FLASH Programming alignment error flag */
#define FLASH_FLAG_SIZERR               ((FLASH_FLAG_SR_ID << FLASH_FLAG_REG_POS) | FLASH_SR_SIZERR_Pos)      /*!< FLASH Size error flag  */
#define FLASH_FLAG_PGSERR               ((FLASH_FLAG_SR_ID << FLASH_FLAG_REG_POS) | FLASH_SR_PGSERR_Pos)      /*!< FLASH Programming sequence error flag */
#define FLASH_FLAG_MISERR               ((FLASH_FLAG_SR_ID << FLASH_FLAG_REG_POS) | FLASH_SR_MISERR_Pos)      /*!< FLASH Fast programming data miss error flag */
#define FLASH_FLAG_FASTERR              ((FLASH_FLAG_SR_ID << FLASH_FLAG_REG_POS) | FLASH_SR_FASTERR_Pos)     /*!< FLASH Fast programming error flag */
#if defined(FLASH_PCROP_SUPPORT)
#define FLASH_FLAG_RDERR                ((FLASH_FLAG_SR_ID << FLASH_FLAG_REG_POS) | FLASH_SR_RDERR_Pos)       /*!< FLASH PCROP read error flag */
#endif /* FLASH_PCROP_SUPPORT */
#define FLASH_FLAG_OPTVERR              ((FLASH_FLAG_SR_ID << FLASH_FLAG_REG_POS) | FLASH_SR_OPTVERR_Pos)     /*!< FLASH Option validity error flag */
#define FLASH_FLAG_BSY1                 ((FLASH_FLAG_SR_ID << FLASH_FLAG_REG_POS) | FLASH_SR_BSY1_Pos)        /*!< FLASH Operation Busy flag for Bank 1 */
#if defined(FLASH_DBANK_SUPPORT)
#define FLASH_FLAG_BSY2                  ((FLASH_FLAG_SR_ID << FLASH_FLAG_REG_POS) | FLASH_SR_BSY2_Pos)       /*!< FLASH Operation Busy flag for Bank 2 */
#endif /* FLASH_DBANK_SUPPORT */
#define FLASH_FLAG_BSY                  FLASH_FLAG_BSY1                                                       /*!< FLASH Operation Busy flag - legacy name for single bank */
#define FLASH_FLAG_CFGBSY               ((FLASH_FLAG_SR_ID << FLASH_FLAG_REG_POS) | FLASH_SR_CFGBSY_Pos)      /*!< FLASH Configuration Busy flag */
#if defined(FLASH_DBANK_SUPPORT)
#define FLASH_FLAG_PESD                 ((FLASH_FLAG_SR_ID << FLASH_FLAG_REG_POS) | FLASH_SR_PESD_Pos)        /*!< FLASH Programming/erase operation suspended */
#endif /* FLASH_DBANK_SUPPORT */
#define FLASH_FLAG_ECCC1                ((FLASH_FLAG_ECCR1_ID << FLASH_FLAG_REG_POS) | FLASH_ECCR_ECCC_Pos)   /*!< FLASH ECC correction on bank 1 */
#define FLASH_FLAG_ECCD1                ((FLASH_FLAG_ECCR1_ID << FLASH_FLAG_REG_POS) | FLASH_ECCR_ECCD_Pos)   /*!< FLASH ECC detection on bank 1 */
#if defined(FLASH_DBANK_SUPPORT)
#define FLASH_FLAG_ECCC2                ((FLASH_FLAG_ECCR2_ID << FLASH_FLAG_REG_POS) | FLASH_ECC2R_ECCC_Pos)  /*!< FLASH ECC correction on bank 2 */
#define FLASH_FLAG_ECCD2                ((FLASH_FLAG_ECCR2_ID << FLASH_FLAG_REG_POS) | FLASH_ECC2R_ECCD_Pos)  /*!< FLASH ECC detection on bank 2 */
#endif /* FLASH_DBANK_SUPPORT */
#define FLASH_FLAG_ECCC                 FLASH_FLAG_ECCC1   /*!< FLASH ECC correction - legacy name for single bank */
#define FLASH_FLAG_ECCD                 FLASH_FLAG_ECCD1   /*!< FLASH ECC detection - legacy name for single bank */
/**
  * @}
  */

/** @defgroup FLASH_Interrupt_definition FLASH Interrupts Definition
  * @brief FLASH Interrupt definition
  * @{
  */
#define FLASH_IT_EOP                    ((FLASH_FLAG_CR_ID << FLASH_FLAG_REG_POS) | FLASH_CR_EOPIE_Pos)         /*!< End of FLASH Operation Interrupt source */
#define FLASH_IT_OPERR                  ((FLASH_FLAG_CR_ID << FLASH_FLAG_REG_POS) | FLASH_CR_ERRIE_Pos)         /*!< Error Interrupt source */
#if defined(FLASH_PCROP_SUPPORT)
#define FLASH_IT_RDERR                  ((FLASH_FLAG_CR_ID << FLASH_FLAG_REG_POS) | FLASH_CR_RDERRIE_Pos)       /*!< PCROP Read Error Interrupt source*/
#endif /* FLASH_PCROP_SUPPORT */
#define FLASH_IT_ECCC1                  ((FLASH_FLAG_ECCR1_ID << FLASH_FLAG_REG_POS) | FLASH_ECCR_ECCCIE_Pos)   /*!< ECC Correction on Bank 1 Interrupt source */
#if defined(FLASH_DBANK_SUPPORT)
#define FLASH_IT_ECCC2                  ((FLASH_FLAG_ECCR2_ID << FLASH_FLAG_REG_POS) | FLASH_ECC2R_ECCCIE_Pos)  /*!< ECC Correction on Bank 2 Interrupt source */
#endif /* FLASH_DBANK_SUPPORT */
#define FLASH_IT_ECCC                   FLASH_IT_ECCC1                                                          /*!< ECC Correction - legacy name for single bank */
/**
  * @}
  */

/** @defgroup FLASH_Error FLASH Error
  * @{
  */
#define HAL_FLASH_ERROR_NONE            0x00000000U
#define HAL_FLASH_ERROR_OP              FLASH_SR_EOP
#define HAL_FLASH_ERROR_PROG            FLASH_SR_PROGERR
#define HAL_FLASH_ERROR_WRP             FLASH_SR_WRPERR
#define HAL_FLASH_ERROR_PGA             FLASH_SR_PGAERR
#define HAL_FLASH_ERROR_SIZ             FLASH_SR_SIZERR
#define HAL_FLASH_ERROR_PGS             FLASH_SR_PGSERR
#define HAL_FLASH_ERROR_MIS             FLASH_SR_MISERR
#define HAL_FLASH_ERROR_FAST            FLASH_SR_FASTERR
#if defined(FLASH_PCROP_SUPPORT)
#define HAL_FLASH_ERROR_RD              FLASH_SR_RDERR
#endif /* FLASH_PCROP_SUPPORT */
#define HAL_FLASH_ERROR_OPTV            FLASH_SR_OPTVERR
#define HAL_FLASH_ERROR_ECCD            FLASH_ECCR_ECCD
/**
  * @}
  */

/** @defgroup FLASH_Type_Erase FLASH Erase Type
  * @{
  */
#define FLASH_TYPEERASE_PAGES           FLASH_CR_PER    /*!< Pages erase only */
#define FLASH_TYPEERASE_MASS            FLASH_CR_MER1   /*!< Flash mass erase activation */
/**
  * @}
  */

/** @defgroup FLASH_Banks FLASH Banks
  * @{
  */
#define FLASH_BANK_1                    FLASH_CR_MER1   /*!< Bank 1 */
#if defined(FLASH_DBANK_SUPPORT)
#define FLASH_BANK_2                    FLASH_CR_MER2   /*!< Bank 2 */
#endif /* FLASH_DBANK_SUPPORT */
/**
  * @}
  */


/** @defgroup FLASH_Type_Program FLASH Program Type
  * @{
  */
#define FLASH_TYPEPROGRAM_DOUBLEWORD    FLASH_CR_PG     /*!< Program a double-word (64-bit) at a specified address */
#define FLASH_TYPEPROGRAM_FAST          FLASH_CR_FSTPG  /*!< Fast program a 32 row double-word (64-bit) at a specified address */
/**
  * @}
  */

/** @defgroup FLASH_OB_Type FLASH Option Bytes Type
  * @{
  */
#define OPTIONBYTE_WRP                  0x00000001U  /*!< WRP option byte configuration */
#define OPTIONBYTE_RDP                  0x00000002U  /*!< RDP option byte configuration */
#define OPTIONBYTE_USER                 0x00000004U  /*!< USER option byte configuration */
#if defined(FLASH_PCROP_SUPPORT)
#define OPTIONBYTE_PCROP                0x00000008U  /*!< PCROP option byte configuration */
#endif /* FLASH_PCROP_SUPPORT */
#if defined(FLASH_SECURABLE_MEMORY_SUPPORT)
#define OPTIONBYTE_SEC                  0x00000010U  /*!< SEC option byte configuration */
#endif /* FLASH_SECURABLE_MEMORY_SUPPORT */

#if defined(FLASH_PCROP_SUPPORT) && defined(FLASH_SECURABLE_MEMORY_SUPPORT)
#define OPTIONBYTE_ALL                  (OPTIONBYTE_WRP   | OPTIONBYTE_RDP | OPTIONBYTE_USER | \
                                         OPTIONBYTE_PCROP | OPTIONBYTE_SEC)                   /*!< All option byte configuration */
#else
#define OPTIONBYTE_ALL                  (OPTIONBYTE_WRP   | OPTIONBYTE_RDP | OPTIONBYTE_USER) /*!< All option byte configuration */
#endif /* FLASH_PCROP_SUPPORT && FLASH_SECURABLE_MEMORY_SUPPORT */
/**
  * @}
  */

/** @defgroup FLASH_OB_WRP_Area FLASH WRP Area
  * @{
  */
#define OB_WRPAREA_ZONE_A               0x00000001U  /*!< Flash Zone A */
#define OB_WRPAREA_ZONE_B               0x00000002U  /*!< Flash Zone B */
#if defined(FLASH_DBANK_SUPPORT)
#define OB_WRPAREA_ZONE2_A              0x00000004U  /*!< Flash Bank 2 Zone A */
#define OB_WRPAREA_ZONE2_B              0x00000008U  /*!< Flash Bank 2 Zone B */
#endif /* FLASH_DBANK_SUPPORT */
/**
  * @}
  */

/** @defgroup FLASH_OB_Read_Protection FLASH Option Bytes Read Protection
  * @{
  */
#define OB_RDP_LEVEL_0                  0x000000AAU
#define OB_RDP_LEVEL_1                  0x000000BBU
#define OB_RDP_LEVEL_2                  0x000000CCU  /*!< Warning: When enabling read protection level 2
                                                          it is no more possible to go back to level 1 or 0 */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_Type FLASH Option Bytes User Type
  * @{
  */
#if defined(PWR_BOR_SUPPORT)
#define OB_USER_BOR_EN                  FLASH_OPTR_BOR_EN                           /*!< BOR reset enable */
#define OB_USER_BOR_LEV                 (FLASH_OPTR_BORF_LEV | FLASH_OPTR_BORR_LEV) /*!< BOR reset Level */
#endif /* PWR_BOR_SUPPORT */
#define OB_USER_nRST_STOP               FLASH_OPTR_nRST_STOP                        /*!< Reset generated when entering the stop mode */
#define OB_USER_nRST_STDBY              FLASH_OPTR_nRST_STDBY                       /*!< Reset generated when entering the standby mode */
#if defined(PWR_SHDW_SUPPORT)
#define OB_USER_nRST_SHDW               FLASH_OPTR_nRST_SHDW                        /*!< Reset generated when entering the shutdown mode */
#endif /* PWR_SHDW_SUPPORT */
#define OB_USER_IWDG_SW                 FLASH_OPTR_IWDG_SW                          /*!< Independent watchdog selection */
#define OB_USER_IWDG_STOP               FLASH_OPTR_IWDG_STOP                        /*!< Independent watchdog counter freeze in stop mode */
#define OB_USER_IWDG_STDBY              FLASH_OPTR_IWDG_STDBY                       /*!< Independent watchdog counter freeze in standby mode */
#define OB_USER_WWDG_SW                 FLASH_OPTR_WWDG_SW                          /*!< Window watchdog selection */
#if defined(FLASH_DBANK_SUPPORT)
#define OB_USER_BANK_SWAP               FLASH_OPTR_nSWAP_BANK                       /*!< Swap bank memory addresses */
#define OB_USER_DUAL_BANK               FLASH_OPTR_DUAL_BANK                        /*!< Select single or dual bank (depending of device memory size) */
#endif /* FLASH_DBANK_SUPPORT */
#define OB_USER_RAM_PARITY_CHECK        FLASH_OPTR_RAM_PARITY_CHECK                 /*!< Sram parity check control */
#define OB_USER_nBOOT_SEL               FLASH_OPTR_nBOOT_SEL                        /*!< Boot Selection */
#define OB_USER_nBOOT1                  FLASH_OPTR_nBOOT1                           /*!< nBoot1 configuration */
#define OB_USER_nBOOT0                  FLASH_OPTR_nBOOT0                           /*!< nBoot0 configuration */
#if defined(GPIO_NRST_CONFIG_SUPPORT)
#define OB_USER_NRST_MODE               FLASH_OPTR_NRST_MODE                        /*!< Reset pin configuration */
#endif /* GPIO_NRST_CONFIG_SUPPORT */
#if defined(FLASH_OPTR_IRHEN)
#define OB_USER_INPUT_RESET_HOLDER      FLASH_OPTR_IRHEN                            /*!< Internal reset holder enable */
#endif /* FLASH_OPTR_IRHEN */

#if defined(FLASH_DBANK_SUPPORT)
#if defined(PWR_BOR_SUPPORT) && defined(PWR_SHDW_SUPPORT) && defined(GPIO_NRST_CONFIG_SUPPORT)
#define OB_USER_ALL                     (OB_USER_BOR_EN           | OB_USER_BOR_LEV    | OB_USER_nRST_STOP | \
                                         OB_USER_nRST_STDBY       | OB_USER_nRST_SHDW  | OB_USER_IWDG_SW   | \
                                         OB_USER_IWDG_STOP        | OB_USER_IWDG_STDBY | OB_USER_WWDG_SW   | \
                                         OB_USER_BANK_SWAP        | OB_USER_DUAL_BANK                      | \
                                         OB_USER_RAM_PARITY_CHECK | OB_USER_nBOOT_SEL  | OB_USER_nBOOT1    | \
                                         OB_USER_nBOOT0           | OB_USER_NRST_MODE  | OB_USER_INPUT_RESET_HOLDER)   /*!< all option bits */
#else
#define OB_USER_ALL                     (                                                OB_USER_nRST_STOP | \
    OB_USER_nRST_STDBY                            | OB_USER_IWDG_SW   | \
    OB_USER_IWDG_STOP        | OB_USER_IWDG_STDBY | OB_USER_WWDG_SW   | \
    OB_USER_BANK_SWAP        | OB_USER_DUAL_BANK                      | \
    OB_USER_RAM_PARITY_CHECK | OB_USER_nBOOT_SEL  | OB_USER_nBOOT1    | \
    OB_USER_nBOOT0)                                                               /*!< all option bits */
#endif /* PWR_BOR_SUPPORT && PWR_SHDW_SUPPORT && GPIO_NRST_CONFIG_SUPPORT */
#else
#if defined(PWR_BOR_SUPPORT) && defined(PWR_SHDW_SUPPORT) && defined(GPIO_NRST_CONFIG_SUPPORT)
#define OB_USER_ALL                     (OB_USER_BOR_EN           | OB_USER_BOR_LEV    | OB_USER_nRST_STOP | \
                                         OB_USER_nRST_STDBY       | OB_USER_nRST_SHDW  | OB_USER_IWDG_SW   | \
                                         OB_USER_IWDG_STOP        | OB_USER_IWDG_STDBY | OB_USER_WWDG_SW   | \
                                         OB_USER_RAM_PARITY_CHECK | OB_USER_nBOOT_SEL  | OB_USER_nBOOT1    | \
                                         OB_USER_nBOOT0           | OB_USER_NRST_MODE  | OB_USER_INPUT_RESET_HOLDER)   /*!< all option bits */
#else
#define OB_USER_ALL                     (                                                OB_USER_nRST_STOP | \
    OB_USER_nRST_STDBY                            | OB_USER_IWDG_SW   | \
    OB_USER_IWDG_STOP        | OB_USER_IWDG_STDBY | OB_USER_WWDG_SW   | \
    OB_USER_RAM_PARITY_CHECK | OB_USER_nBOOT_SEL  | OB_USER_nBOOT1    | \
    OB_USER_nBOOT0)                                                               /*!< all option bits */
#endif /* PWR_BOR_SUPPORT && PWR_SHDW_SUPPORT && GPIO_NRST_CONFIG_SUPPORT */
#endif /* FLASH_DBANK_SUPPORT */
/**
  * @}
  */

#if defined(PWR_BOR_SUPPORT)
/** @defgroup FLASH_OB_USER_BOR_ENABLE FLASH Option Bytes User BOR enable
  * @{
  */
#define OB_BOR_DISABLE                  0x00000000U        /*!< BOR Reset set to default */
#define OB_BOR_ENABLE                   FLASH_OPTR_BOR_EN  /*!< Use option byte to define BOR thresholds */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_BOR_LEVEL FLASH Option Bytes User BOR Level
  * @{
  */
#define OB_BOR_LEVEL_FALLING_0          0x00000000U                                     /*!< BOR falling level 1 with threshold around 2.0V */
#define OB_BOR_LEVEL_FALLING_1          FLASH_OPTR_BORF_LEV_0                           /*!< BOR falling level 2 with threshold around 2.2V */
#define OB_BOR_LEVEL_FALLING_2          FLASH_OPTR_BORF_LEV_1                           /*!< BOR falling level 3 with threshold around 2.5V */
#define OB_BOR_LEVEL_FALLING_3          (FLASH_OPTR_BORF_LEV_0 | FLASH_OPTR_BORF_LEV_1) /*!< BOR falling level 4 with threshold around 2.8V */
#define OB_BOR_LEVEL_RISING_0           0x00000000U                                     /*!< BOR rising level 1 with threshold around 2.1V */
#define OB_BOR_LEVEL_RISING_1           FLASH_OPTR_BORR_LEV_0                           /*!< BOR rising level 2 with threshold around 2.3V */
#define OB_BOR_LEVEL_RISING_2           FLASH_OPTR_BORR_LEV_1                           /*!< BOR rising level 3 with threshold around 2.6V */
#define OB_BOR_LEVEL_RISING_3           (FLASH_OPTR_BORR_LEV_0 | FLASH_OPTR_BORR_LEV_1) /*!< BOR rising level 4 with threshold around 2.9V */
/**
  * @}
  */
#endif /* PWR_BOR_SUPPORT */

/** @defgroup FLASH_OB_USER_nRST_STOP FLASH Option Bytes User Reset On Stop
  * @{
  */
#define OB_STOP_RST                     0x00000000U           /*!< Reset generated when entering the stop mode */
#define OB_STOP_NORST                   FLASH_OPTR_nRST_STOP  /*!< No reset generated when entering the stop mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_nRST_STANDBY FLASH Option Bytes User Reset On Standby
  * @{
  */
#define OB_STANDBY_RST                  0x00000000U           /*!< Reset generated when entering the standby mode */
#define OB_STANDBY_NORST                FLASH_OPTR_nRST_STDBY /*!< No reset generated when entering the standby mode */
/**
  * @}
  */

#if defined(PWR_SHDW_SUPPORT)
/** @defgroup FLASH_OB_USER_nRST_SHUTDOWN FLASH Option Bytes User Reset On Shutdown
  * @{
  */
#define OB_SHUTDOWN_RST                 0x00000000U           /*!< Reset generated when entering the shutdown mode */
#define OB_SHUTDOWN_NORST               FLASH_OPTR_nRST_SHDW  /*!< No reset generated when entering the shutdown mode */
/**
  * @}
  */
#endif /* PWR_SHDW_SUPPORT */

/** @defgroup FLASH_OB_USER_IWDG_SW FLASH Option Bytes User IWDG Type
  * @{
  */
#define OB_IWDG_HW                      0x00000000U           /*!< Hardware independent watchdog */
#define OB_IWDG_SW                      FLASH_OPTR_IWDG_SW    /*!< Software independent watchdog */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IWDG_STOP FLASH Option Bytes User IWDG Mode On Stop
  * @{
  */
#define OB_IWDG_STOP_FREEZE             0x00000000U           /*!< Independent watchdog counter is frozen in Stop mode */
#define OB_IWDG_STOP_RUN                FLASH_OPTR_IWDG_STOP  /*!< Independent watchdog counter is running in Stop mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IWDG_STANDBY FLASH Option Bytes User IWDG Mode On Standby
  * @{
  */
#define OB_IWDG_STDBY_FREEZE            0x00000000U           /*!< Independent watchdog counter is frozen in Standby mode */
#define OB_IWDG_STDBY_RUN               FLASH_OPTR_IWDG_STDBY /*!< Independent watchdog counter is running in Standby mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_WWDG_SW FLASH Option Bytes User WWDG Type
  * @{
  */
#define OB_WWDG_HW                      0x00000000U           /*!< Hardware window watchdog */
#define OB_WWDG_SW                      FLASH_OPTR_WWDG_SW    /*!< Software window watchdog */
/**
  * @}
  */

#if defined(FLASH_DBANK_SUPPORT)
/** @defgroup FLASH_OB_USER_BANK_SWAP FLASH Option Bytes User bank swap Type
  * @{
  */
#define OB_USER_DUALBANK_SWAP_ENABLE    0x00000000U            /*!< Enable bank swap */
#define OB_USER_DUALBANK_SWAP_DISABLE   FLASH_OPTR_nSWAP_BANK  /*!< Disable bank swap */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_DUAL_BANK FLASH Option Bytes User dual bank enable Type
  * @{
  */
#define OB_USER_DUALBANK_DISABLE        0x00000000U           /*!< Disable dual bank */
#define OB_USER_DUALBANK_ENABLE         FLASH_OPTR_DUAL_BANK  /*!< Enable dual bank */
/**
  * @}
  */
#endif /* FLASH_DBANK_SUPPORT */

/** @defgroup FLASH_OB_USER_SRAM_PARITY FLASH Option Bytes User SRAM parity
  * @{
  */
#define OB_SRAM_PARITY_ENABLE           0x00000000U                  /*!< Sram parity enable */
#define OB_SRAM_PARITY_DISABLE          FLASH_OPTR_RAM_PARITY_CHECK  /*!< Sram parity disable */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_nBOOT_SEL FLASH Option Bytes User Boot0 Selection
  * @{
  */
#define OB_BOOT0_FROM_PIN               0x00000000U             /*!< BOOT0 signal is defined by PA14/BOOT0 pin value */
#define OB_BOOT0_FROM_OB                FLASH_OPTR_nBOOT_SEL    /*!< BOOT0 signal is defined by nBOOT0 option bit */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_nBOOT1 FLASH Option Bytes User BOOT1 Type
  * @{
  */
#define OB_BOOT1_SRAM                   0x00000000U           /*!< Embedded SRAM is selected as boot space (if nBOOT0=0 or BOOT0_pin=1) */
#define OB_BOOT1_SYSTEM                 FLASH_OPTR_nBOOT1     /*!< System memory is selected as boot space (if nBOOT0=0 or BOOT0_pin=1) */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_nBOOT0 FLASH Option Bytes User nBOOT0 option bit
  * @{
  */
#define OB_nBOOT0_RESET                 0x00000000U           /*!< nBOOT0 = 0 */
#define OB_nBOOT0_SET                   FLASH_OPTR_nBOOT0     /*!< nBOOT0 = 1 */
/**
  * @}
  */

#if defined(GPIO_NRST_CONFIG_SUPPORT)
/** @defgroup FLASH_OB_USER_RESET_CONFIG FLASH Option Bytes User reset config bit
  * @{
  */
#define OB_RESET_MODE_INPUT_ONLY        FLASH_OPTR_NRST_MODE_0  /*!< Reset pin is in Reset input mode only */
#define OB_RESET_MODE_GPIO              FLASH_OPTR_NRST_MODE_1  /*!< Reset pin is in GPIO mode mode only */
#define OB_RESET_MODE_INPUT_OUTPUT      FLASH_OPTR_NRST_MODE    /*!< Reset pin is in reset input and output mode */
/**
  * @}
  */
#endif /* GPIO_NRST_CONFIG_SUPPORT */

#if defined(FLASH_OPTR_IRHEN)
/** @defgroup FLASH_OB_USER_INPUT_RESET_HOLDER FLASH Option Bytes User input reset holder bit
  * @{
  */
#define OB_IRH_ENABLE                   0x00000000U           /*!< Internal Reset handler enable */
#define OB_IRH_DISABLE                  FLASH_OPTR_IRHEN      /*!< Internal Reset handler disable */
/**
  * @}
  */
#endif /* FLASH_OPTR_IRHEN */

#if defined(FLASH_PCROP_SUPPORT)
/** @defgroup FLASH_OB_PCROP_ZONE FLASH Option Bytes PCROP ZONE
  * @{
  */
#define OB_PCROP_ZONE_A                 0x00000001U /*!< PCROP Zone A */
#define OB_PCROP_ZONE_B                 0x00000002U /*!< PCROP Zone B */
#if defined(FLASH_DBANK_SUPPORT)
#define OB_PCROP_ZONE2_A                0x00000004U /*!< PCROP Bank 2 Zone A */
#define OB_PCROP_ZONE2_B                0x00000008U /*!< PCROP Bank 2 Zone B */
#endif /* FLASH_DBANK_SUPPORT */
/**
  * @}
  */

/** @defgroup FLASH_OB_PCROP_RDP FLASH Option Bytes PCROP On RDP Level Type
  * @{
  */
#define OB_PCROP_RDP_NOT_ERASE          0x00000000U               /*!< PCROP area is not erased when the RDP level
                                                                       is decreased from Level 1 to Level 0 */
#define OB_PCROP_RDP_ERASE              FLASH_PCROP1AER_PCROP_RDP /*!< PCROP area is erased when the RDP level is
                                                                       decreased from Level 1 to Level 0 (full mass erase).
                                                                       Once this bit is set only, it will be reset by mass erase */
/**
  * @}
  */
#endif /* FLASH_PCROP_SUPPORT */

#if defined(FLASH_SECURABLE_MEMORY_SUPPORT)
/** @defgroup FLASH_OB_SEC_BOOT_LOCK FLASH Option Bytes Secure boot lock
  * @{
  */
#define OB_BOOT_ENTRY_FORCED_NONE        0x00000000U               /*!< Boot entry is free */
#define OB_BOOT_ENTRY_FORCED_FLASH       FLASH_SECR_BOOT_LOCK      /*!< Boot entry is forced to Flash or System Flash */
/**
  * @}
  */
#endif /* FLASH_SECURABLE_MEMORY_SUPPORT */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup FLASH_Exported_Macros FLASH Exported Macros
  *  @brief macros to control FLASH features
  *  @{
  */

/**
  * @brief  Set the FLASH Latency.
  * @param  __LATENCY__ FLASH Latency
  *         This parameter can be one of the following values :
  *     @arg @ref FLASH_LATENCY_0 FLASH Zero wait state
  *     @arg @ref FLASH_LATENCY_1 FLASH One wait state
  *     @arg @ref FLASH_LATENCY_2 FLASH Two wait states
  * @retval None
  */
#define __HAL_FLASH_SET_LATENCY(__LATENCY__)    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (__LATENCY__))

/**
  * @brief  Get the FLASH Latency.
  * @retval FLASH Latency
  *         Returned value can be one of the following values :
  *     @arg @ref FLASH_LATENCY_0 FLASH Zero wait state
  *     @arg @ref FLASH_LATENCY_1 FLASH One wait state
  *     @arg @ref FLASH_LATENCY_2 FLASH Two wait states
  */
#define __HAL_FLASH_GET_LATENCY()               READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY)

/**
  * @brief  Enable the FLASH prefetch buffer.
  * @retval None
  */
#define __HAL_FLASH_PREFETCH_BUFFER_ENABLE()    SET_BIT(FLASH->ACR, FLASH_ACR_PRFTEN)

/**
  * @brief  Disable the FLASH prefetch buffer.
  * @retval None
  */
#define __HAL_FLASH_PREFETCH_BUFFER_DISABLE()   CLEAR_BIT(FLASH->ACR, FLASH_ACR_PRFTEN)

/**
  * @brief  Enable the FLASH instruction cache.
  * @retval none
  */
#define __HAL_FLASH_INSTRUCTION_CACHE_ENABLE()  SET_BIT(FLASH->ACR, FLASH_ACR_ICEN)

/**
  * @brief  Disable the FLASH instruction cache.
  * @retval none
  */
#define __HAL_FLASH_INSTRUCTION_CACHE_DISABLE() CLEAR_BIT(FLASH->ACR, FLASH_ACR_ICEN)

/**
  * @brief  Reset the FLASH instruction Cache.
  * @note   This function must be used only when the Instruction Cache is disabled.
  * @retval None
  */
#define __HAL_FLASH_INSTRUCTION_CACHE_RESET()   do { SET_BIT(FLASH->ACR, FLASH_ACR_ICRST);   \
                                                     CLEAR_BIT(FLASH->ACR, FLASH_ACR_ICRST); \
                                                   } while (0U)
/**
  * @}
  */

/** @defgroup FLASH_Interrupt FLASH Interrupts Macros
  *  @brief macros to handle FLASH interrupts
  * @{
  */

/**
  * @brief  Enable the specified FLASH interrupt.
  * @param  __INTERRUPT__ FLASH interrupt
  *         This parameter can be one of the following values :
  *     @arg @ref FLASH_IT_EOP End of FLASH Operation Interrupt
  *     @arg @ref FLASH_IT_OPERR Error Interrupt
  *     @arg @ref FLASH_IT_RDERR PCROP Read Error Interrupt(*)
  *     @arg @ref FLASH_IT_ECCC1 ECC Correction Interrupt on bank 1
  *     @arg @ref FLASH_IT_ECCC2 ECC Correction Interrupt on bank 2(*)
  *     @arg @ref FLASH_IT_ECCC ECC Correction Interrupt - legacy name for single bank
  * @note (*) availability depends on devices
  * @retval none
  */
#if defined(FLASH_DBANK_SUPPORT)
#define __HAL_FLASH_ENABLE_IT(__INTERRUPT__)    do { if(((__INTERRUPT__) & (FLASH_FLAG_CR_ID << FLASH_FLAG_REG_POS)) != 0U) { SET_BIT(FLASH->CR, (1uL << ((__INTERRUPT__) & 0x1Fu))); }             \
                                                     else if(((__INTERRUPT__) & (FLASH_FLAG_ECCR1_ID << FLASH_FLAG_REG_POS)) != 0U) { SET_BIT(FLASH->ECCR, (1uL << ((__INTERRUPT__) & 0x1Fu))); }   \
                                                     else if(((__INTERRUPT__) & (FLASH_FLAG_ECCR2_ID << FLASH_FLAG_REG_POS)) != 0U) { SET_BIT(FLASH->ECC2R, (1uL << ((__INTERRUPT__) & 0x1Fu))); }  \
                                                   } while(0U)
#else
#define __HAL_FLASH_ENABLE_IT(__INTERRUPT__)    do { if(((__INTERRUPT__) & (FLASH_FLAG_CR_ID << FLASH_FLAG_REG_POS)) != 0U) { SET_BIT(FLASH->CR, (1uL << ((__INTERRUPT__) & 0x1Fu))); }             \
                                                     else if(((__INTERRUPT__) & (FLASH_FLAG_ECCR1_ID << FLASH_FLAG_REG_POS)) != 0U) { SET_BIT(FLASH->ECCR, (1uL << ((__INTERRUPT__) & 0x1Fu))); }   \
                                                   } while(0U)
#endif /* FLASH_DBANK_SUPPORT */

/**
  * @brief  Disable the specified FLASH interrupt.
  * @param  __INTERRUPT__ FLASH interrupt
  *         This parameter can be one of the following values :
  *     @arg @ref FLASH_IT_EOP End of FLASH Operation Interrupt
  *     @arg @ref FLASH_IT_OPERR Error Interrupt
  *     @arg @ref FLASH_IT_RDERR PCROP Read Error Interrupt(*)
  *     @arg @ref FLASH_IT_ECCC1 ECC Correction Interrupt on bank 1
  *     @arg @ref FLASH_IT_ECCC2 ECC Correction Interrupt on bank 2(*)
  *     @arg @ref FLASH_IT_ECCC ECC Correction Interrupt - legacy name for single bank
  * @note (*) availability depends on devices
  * @retval none
  */
#if defined(FLASH_DBANK_SUPPORT)
#define __HAL_FLASH_DISABLE_IT(__INTERRUPT__)   do { if(((__INTERRUPT__) & (FLASH_FLAG_CR_ID << FLASH_FLAG_REG_POS)) != 0U) { CLEAR_BIT(FLASH->CR, (1uL << ((__INTERRUPT__) & 0x1Fu))); }             \
                                                     else if(((__INTERRUPT__) & (FLASH_FLAG_ECCR1_ID << FLASH_FLAG_REG_POS)) != 0U) { CLEAR_BIT(FLASH->ECCR, (1uL << ((__INTERRUPT__) & 0x1Fu))); }   \
                                                     else if(((__INTERRUPT__) & (FLASH_FLAG_ECCR2_ID << FLASH_FLAG_REG_POS)) != 0U) { CLEAR_BIT(FLASH->ECC2R, (1uL << ((__INTERRUPT__) & 0x1Fu))); }  \
                                                   } while(0U)
#else
#define __HAL_FLASH_DISABLE_IT(__INTERRUPT__)   do { if(((__INTERRUPT__) & (FLASH_FLAG_CR_ID << FLASH_FLAG_REG_POS)) != 0U) { CLEAR_BIT(FLASH->CR, (1uL << ((__INTERRUPT__) & 0x1Fu))); }             \
                                                     else if(((__INTERRUPT__) & (FLASH_FLAG_ECCR1_ID << FLASH_FLAG_REG_POS)) != 0U) { CLEAR_BIT(FLASH->ECCR, (1uL << ((__INTERRUPT__) & 0x1Fu))); }   \
                                                   } while(0U)
#endif /* FLASH_DBANK_SUPPORT */

/**
  * @brief  Check whether the specified FLASH flag is set or not.
  * @param  __FLAG__ specifies the FLASH flag to check.
  *         This parameter can be one of the following values :
  *     @arg @ref FLASH_FLAG_EOP FLASH End of Operation flag
  *     @arg @ref FLASH_FLAG_OPERR FLASH Operation error flag
  *     @arg @ref FLASH_FLAG_PROGERR FLASH Programming error flag
  *     @arg @ref FLASH_FLAG_WRPERR FLASH Write protection error flag
  *     @arg @ref FLASH_FLAG_PGAERR FLASH Programming alignment error flag
  *     @arg @ref FLASH_FLAG_SIZERR FLASH Size error flag
  *     @arg @ref FLASH_FLAG_PGSERR FLASH Programming sequence error flag
  *     @arg @ref FLASH_FLAG_MISERR FLASH Fast programming data miss error flag
  *     @arg @ref FLASH_FLAG_FASTERR FLASH Fast programming error flag
  *     @arg @ref FLASH_FLAG_RDERR FLASH PCROP read  error flag(*)
  *     @arg @ref FLASH_FLAG_OPTVERR FLASH Option validity error flag
  *     @arg @ref FLASH_FLAG_BSY1 FLASH bank 1 write/erase operations in progress flag
  *     @arg @ref FLASH_FLAG_BSY2 FLASH bank 2 write/erase operations in progress flag(*)
  *     @arg @ref FLASH_FLAG_BSY FLASH write/erase operations in progress flag  - legacy name for single bank
  *     @arg @ref FLASH_FLAG_CFGBSY FLASH configuration is busy : program or erase setting are used.
  *     @arg @ref FLASH_FLAG_ECCC1 FLASH one ECC error has been detected and corrected
  *     @arg @ref FLASH_FLAG_ECCD1 FLASH two ECC errors have been detected on bank 1
  *     @arg @ref FLASH_FLAG_ECCC2 FLASH one ECC error has been detected and corrected on bank 2(*)
  *     @arg @ref FLASH_FLAG_ECCD2 FLASH two ECC errors have been detected on bank 2(*)
  *     @arg @ref FLASH_FLAG_ECCC FLASH one ECC error has been detected and corrected - legacy name for single bank
  *     @arg @ref FLASH_FLAG_ECCD FLASH two ECC errors have been detected - legacy name for single bank
  * @note (*) availability depends on devices
  * @retval The state of FLASH_FLAG (SET or RESET).
  */
#if defined(FLASH_DBANK_SUPPORT)
#define __HAL_FLASH_GET_FLAG(__FLAG__)          ((((__FLAG__) & (FLASH_FLAG_SR_ID << FLASH_FLAG_REG_POS)) != 0U) ?             \
                                                 (READ_BIT(FLASH->SR, (1uL << ((__FLAG__) & 0x1Fu))) != 0x00u) :        \
                                                 ((((__FLAG__) & (FLASH_FLAG_ECCR1_ID << FLASH_FLAG_REG_POS)) != 0U) ? \
                                                  (READ_BIT(FLASH->ECCR, (1uL << ((__FLAG__) & 0x1Fu))) != 0x00u) :      \
                                                  (READ_BIT(FLASH->ECC2R, (1uL << ((__FLAG__) & 0x1Fu))) != 0x00u)))
#else
#define __HAL_FLASH_GET_FLAG(__FLAG__)          ((((__FLAG__) & (FLASH_FLAG_SR_ID << FLASH_FLAG_REG_POS)) != 0U) ?   \
                                                 (READ_BIT(FLASH->SR, (1uL << ((__FLAG__) & 0x1Fu))) != 0x00u) : \
                                                 (READ_BIT(FLASH->ECCR, (1uL << ((__FLAG__) & 0x1Fu))) != 0x00u))
#endif /* FLASH_DBANK_SUPPORT */

/**
  * @brief  Clear the FLASH pending flags.
  * @param  __FLAG__ specifies the FLASH flags to clear.
  *         This parameter can be one of the following values :
  *     @arg @ref FLASH_FLAG_EOP FLASH End of Operation flag
  *     @arg @ref FLASH_FLAG_OPERR FLASH Operation error flag
  *     @arg @ref FLASH_FLAG_PROGERR FLASH Programming error flag
  *     @arg @ref FLASH_FLAG_WRPERR FLASH Write protection error flag
  *     @arg @ref FLASH_FLAG_PGAERR FLASH Programming alignment error flag
  *     @arg @ref FLASH_FLAG_SIZERR FLASH Size error flag
  *     @arg @ref FLASH_FLAG_PGSERR FLASH Programming sequence error flag
  *     @arg @ref FLASH_FLAG_MISERR FLASH Fast programming data miss error flag
  *     @arg @ref FLASH_FLAG_FASTERR FLASH Fast programming error flag
  *     @arg @ref FLASH_FLAG_RDERR FLASH PCROP read  error flag
  *     @arg @ref FLASH_FLAG_OPTVERR FLASH Option validity error flag
  *     @arg @ref FLASH_FLAG_ECCC1 FLASH one ECC error has been detected and corrected
  *     @arg @ref FLASH_FLAG_ECCD1 FLASH two ECC errors have been detected on bank 1
  *     @arg @ref FLASH_FLAG_ECCC2 FLASH one ECC error has been detected and corrected on bank 2(*)
  *     @arg @ref FLASH_FLAG_ECCD2 FLASH two ECC errors have been detected on bank 2(*)
  *     @arg @ref FLASH_FLAG_ECCC FLASH one ECC error has been detected and corrected - legacy name for single bank
  *     @arg @ref FLASH_FLAG_ECCD FLASH two ECC errors have been detected - legacy name for single bank
  * @note (*) availability depends on devices
  * @retval None
  */
#if defined(FLASH_DBANK_SUPPORT)
#define __HAL_FLASH_CLEAR_FLAG(__FLAG__)        do { if(((__FLAG__) & (FLASH_FLAG_SR_ID << FLASH_FLAG_REG_POS)) != 0U)         { FLASH->SR = (1uL << ((__FLAG__) & 0x1Fu)); }    \
                                                     else if(((__FLAG__) & (FLASH_FLAG_ECCR1_ID << FLASH_FLAG_REG_POS)) != 0U) { FLASH->ECCR = (1uL << ((__FLAG__) & 0x1Fu)); }  \
                                                     else if(((__FLAG__) & (FLASH_FLAG_ECCR2_ID << FLASH_FLAG_REG_POS)) != 0U) { FLASH->ECC2R = (1uL << ((__FLAG__) & 0x1Fu)); }  \
                                                   } while(0U)
#else
#define __HAL_FLASH_CLEAR_FLAG(__FLAG__)        do { if(((__FLAG__) & (FLASH_FLAG_SR_ID << FLASH_FLAG_REG_POS)) != 0U)         { FLASH->SR = (1uL << ((__FLAG__) & 0x1Fu)); }    \
                                                     else if(((__FLAG__) & (FLASH_FLAG_ECCR1_ID << FLASH_FLAG_REG_POS)) != 0U) { FLASH->ECCR = (1uL << ((__FLAG__) & 0x1Fu)); }  \
                                                   } while(0U)
#endif /* FLASH_DBANK_SUPPORT */
/**
  * @}
  */

/* Include FLASH HAL Extended module */
#include "stm32g0xx_hal_flash_ex.h"
/* Exported variables --------------------------------------------------------*/
/** @defgroup FLASH_Exported_Variables FLASH Exported Variables
  * @{
  */
extern FLASH_ProcessTypeDef pFlash;
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup FLASH_Exported_Functions
  * @{
  */

/* Program operation functions  ***********************************************/
/** @addtogroup FLASH_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef  HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data);
HAL_StatusTypeDef  HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint64_t Data);
/* FLASH IRQ handler method */
void               HAL_FLASH_IRQHandler(void);
/* Callbacks in non blocking modes */
void               HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue);
void               HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue);
/**
  * @}
  */

/* Peripheral Control functions  **********************************************/
/** @addtogroup FLASH_Exported_Functions_Group2
  * @{
  */
HAL_StatusTypeDef  HAL_FLASH_Unlock(void);
HAL_StatusTypeDef  HAL_FLASH_Lock(void);
/* Option bytes control */
HAL_StatusTypeDef  HAL_FLASH_OB_Unlock(void);
HAL_StatusTypeDef  HAL_FLASH_OB_Lock(void);
HAL_StatusTypeDef  HAL_FLASH_OB_Launch(void);
/**
  * @}
  */

/* Peripheral State functions  ************************************************/
/** @addtogroup FLASH_Exported_Functions_Group3
  * @{
  */
uint32_t HAL_FLASH_GetError(void);
/**
  * @}
  */

/**
  * @}
  */

/* Private types --------------------------------------------------------*/
/** @defgroup FLASH_Private_types FLASH Private Types
  * @{
  */
HAL_StatusTypeDef  FLASH_WaitForLastOperation(uint32_t Timeout);
/**
  * @}
  */

/* Private constants --------------------------------------------------------*/
/** @defgroup FLASH_Private_Constants FLASH Private Constants
  * @{
  */
#define FLASH_SIZE_DATA_REGISTER        FLASHSIZE_BASE

#if defined(FLASH_DBANK_SUPPORT)
#define OB_DUAL_BANK_BASE               (FLASH_R_BASE + 0x20U)               /*!< Not use cmsis FLASH alias to avoid iar warning about volatile reading sequence */
#define FLASH_SALES_TYPE_Pos            (24U)
#define FLASH_SALES_TYPE                (0x3UL << FLASH_SALES_TYPE_Pos)     /*!< 0x000001E0 */
#define FLASH_SALES_TYPE_0              (0x1UL << FLASH_SALES_TYPE_Pos)     /*!< 0x01000000 */
#define FLASH_SALES_TYPE_1              (0x2UL << FLASH_SALES_TYPE_Pos)     /*!< 0x02000000 */
#define FLASH_SALES_VALUE               ((*((uint32_t *)PACKAGE_BASE)) & (FLASH_SALES_TYPE))
#define OB_DUAL_BANK_VALUE              ((*((uint32_t *)OB_DUAL_BANK_BASE)) & (FLASH_OPTR_DUAL_BANK))
#define FLASH_BANK_NB                   (((FLASH_SALES_VALUE == 0U)\
                                          || ((FLASH_SALES_VALUE == FLASH_SALES_TYPE_0) && (OB_DUAL_BANK_VALUE == 0U)))?1U:2U)
#define FLASH_BANK_SIZE                 ((FLASH_BANK_NB==1U)?(FLASH_SIZE):(FLASH_SIZE >> 1U)) /*!< FLASH Bank Size. Divided by 2 if 2 Banks */
#else /* FLASH_DBANK_SUPPORT */
#define FLASH_BANK_SIZE                 (FLASH_SIZE)   /*!< FLASH Bank Size */
#endif /* FLASH_DBANK_SUPPORT */

#define FLASH_PAGE_SIZE                 0x00000800U    /*!< FLASH Page Size, 2 KBytes */
#define FLASH_PAGE_NB                   (FLASH_BANK_SIZE/FLASH_PAGE_SIZE) /* Number of pages per bank */
#define FLASH_TIMEOUT_VALUE             1000U          /*!< FLASH Execution Timeout, 1 s */
#define FLASH_TYPENONE                  0x00000000U    /*!< No programming Procedure On Going */

#if defined(FLASH_PCROP_SUPPORT)
#define FLASH_SR_ERRORS                 (FLASH_SR_OPERR  | FLASH_SR_PROGERR | FLASH_SR_WRPERR | \
                                         FLASH_SR_PGAERR | FLASH_SR_SIZERR  | FLASH_SR_PGSERR |  \
                                         FLASH_SR_MISERR | FLASH_SR_FASTERR | FLASH_SR_RDERR |   \
                                         FLASH_SR_OPTVERR) /*!< All SR error flags */
#else
#define FLASH_SR_ERRORS                 (FLASH_SR_OPERR  | FLASH_SR_PROGERR | FLASH_SR_WRPERR | \
                                         FLASH_SR_PGAERR | FLASH_SR_SIZERR  | FLASH_SR_PGSERR |  \
                                         FLASH_SR_MISERR | FLASH_SR_FASTERR |                    \
                                         FLASH_SR_OPTVERR) /*!< All SR error flags */
#endif /* FLASH_PCROP_SUPPORT */

#if defined(FLASH_DBANK_SUPPORT)
#define FLASH_SR_CLEAR                  (FLASH_SR_ERRORS | FLASH_SR_EOP | FLASH_SR_PESD)
#else
#define FLASH_SR_CLEAR                  (FLASH_SR_ERRORS | FLASH_SR_EOP)
#endif /* FLASH_DBANK_SUPPORT */

/* Internal defines for HAL macro usage */
#define FLASH_FLAG_REG_POS              16u
#define FLASH_FLAG_SR_ID                1u
#define FLASH_FLAG_CR_ID                2u
#define FLASH_FLAG_ECCR1_ID             4u
#define FLASH_FLAG_ECCR2_ID             8u

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup FLASH_Private_Macros FLASH Private Macros
  *  @{
  */
#define IS_FLASH_MAIN_MEM_ADDRESS(__ADDRESS__)         (((__ADDRESS__) >= (FLASH_BASE))\
                                                        && ((__ADDRESS__) <= (FLASH_BASE + FLASH_SIZE - 1UL)))

#define IS_FLASH_MAIN_FIRSTHALF_MEM_ADDRESS(__ADDRESS__)  (((__ADDRESS__) >= (FLASH_BASE))\
                                                           && ((__ADDRESS__) <= (FLASH_BASE + FLASH_BANK_SIZE - 1UL)))
#if defined(FLASH_DBANK_SUPPORT)
#define IS_FLASH_MAIN_SECONDHALF_MEM_ADDRESS(__ADDRESS__) (((__ADDRESS__) >= (FLASH_BASE + FLASH_BANK_SIZE))\
                                                           && ((__ADDRESS__) <= (FLASH_BASE + FLASH_SIZE - 1UL)))
#endif /* FLASH_DBANK_SUPPORT */

#define IS_FLASH_PROGRAM_MAIN_MEM_ADDRESS(__ADDRESS__) (((__ADDRESS__) >= (FLASH_BASE))\
                                                        && ((__ADDRESS__) <= (FLASH_BASE + FLASH_SIZE - 8UL)))

#define IS_FLASH_PROGRAM_OTP_ADDRESS(__ADDRESS__)      (((__ADDRESS__) >= 0x1FFF7000U)\
                                                        && ((__ADDRESS__) <= (0x1FFF7400U - 8UL)))

#define IS_FLASH_PROGRAM_ADDRESS(__ADDRESS__)          ((IS_FLASH_PROGRAM_MAIN_MEM_ADDRESS(__ADDRESS__))\
                                                        || (IS_FLASH_PROGRAM_OTP_ADDRESS(__ADDRESS__)))

#define IS_FLASH_FAST_PROGRAM_ADDRESS(__ADDRESS__)     (((__ADDRESS__) >= (FLASH_BASE))\
                                                        && ((__ADDRESS__) <= (FLASH_BASE + FLASH_SIZE - 256UL)))

#define IS_FLASH_PAGE(__PAGE__)                        ((__PAGE__) < FLASH_PAGE_NB)

#if defined(FLASH_DBANK_SUPPORT)
#define IS_FLASH_BANK(__BANK__)                       \
  ((FLASH_BANK_NB == 2U) ?                         \
   (((__BANK__) == FLASH_BANK_1)  ||               \
    ((__BANK__) == FLASH_BANK_2)  ||                \
    ((__BANK__) == (FLASH_BANK_2 | FLASH_BANK_1))): \
   ((__BANK__) == FLASH_BANK_1))
#else
#define IS_FLASH_BANK(__BANK__)                        ((__BANK__) == FLASH_BANK_1)
#endif /* FLASH_DBANK_SUPPORT */

#define IS_FLASH_TYPEERASE(__VALUE__)                  (((__VALUE__) == FLASH_TYPEERASE_PAGES) || \
                                                        ((__VALUE__) == FLASH_TYPEERASE_MASS))

#define IS_FLASH_TYPEPROGRAM(__VALUE__)                (((__VALUE__) == FLASH_TYPEPROGRAM_DOUBLEWORD) || \
                                                        ((__VALUE__) == FLASH_TYPEPROGRAM_FAST))

#define IS_OPTIONBYTE(__VALUE__)                       ((((__VALUE__) & OPTIONBYTE_ALL) != 0x00U) && \
                                                        (((__VALUE__) & ~OPTIONBYTE_ALL) == 0x00U))

#if defined(FLASH_DBANK_SUPPORT)
#define IS_OB_WRPAREA(__VALUE__)                                                     \
  ((FLASH_BANK_NB == 2U) ?                                                        \
   (((__VALUE__) == OB_WRPAREA_ZONE_A) || ((__VALUE__) == OB_WRPAREA_ZONE_B) ||   \
    ((__VALUE__) == OB_WRPAREA_ZONE2_A) || ((__VALUE__) == OB_WRPAREA_ZONE2_B)) :  \
   (((__VALUE__) == OB_WRPAREA_ZONE_A) || ((__VALUE__) == OB_WRPAREA_ZONE_B)))
#else
#define IS_OB_WRPAREA(__VALUE__)                       (((__VALUE__) == OB_WRPAREA_ZONE_A)\
                                                        || ((__VALUE__) == OB_WRPAREA_ZONE_B))
#endif /* FLASH_DBANK_SUPPORT */

#define IS_OB_RDP_LEVEL(__LEVEL__)                     (((__LEVEL__) == OB_RDP_LEVEL_0)   ||\
                                                        ((__LEVEL__) == OB_RDP_LEVEL_1)   ||\
                                                        ((__LEVEL__) == OB_RDP_LEVEL_2))

#define IS_OB_USER_TYPE(__TYPE__)                      ((((__TYPE__) & OB_USER_ALL) != 0x00U) && \
                                                        (((__TYPE__) & ~OB_USER_ALL) == 0x00U))

#define IS_OB_USER_CONFIG(__TYPE__,__CONFIG__)         ((~(__TYPE__) & (__CONFIG__)) == 0x00U)

#if defined(FLASH_PCROP_SUPPORT)
#if defined(FLASH_DBANK_SUPPORT)
#define IS_OB_PCROP_CONFIG(__CONFIG__)                                                           \
  ((FLASH_BANK_NB == 2U) ?                                                                    \
   (((__CONFIG__) & ~(OB_PCROP_ZONE_A | OB_PCROP_ZONE_B |                                     \
                      OB_PCROP_ZONE2_A | OB_PCROP_ZONE2_B | OB_PCROP_RDP_ERASE)) == 0x00U):   \
   (((__CONFIG__) & ~(OB_PCROP_ZONE_A | OB_PCROP_ZONE_B | OB_PCROP_RDP_ERASE)) == 0x00U))
#else
#define IS_OB_PCROP_CONFIG(__CONFIG__)                 (((__CONFIG__)\
                                                         & ~(OB_PCROP_ZONE_A | OB_PCROP_ZONE_B | OB_PCROP_RDP_ERASE)) == 0x00U)
#endif /* FLASH_DBANK_SUPPORT */
#endif /* FLASH_PCROP_SUPPORT */

#if defined(FLASH_SECURABLE_MEMORY_SUPPORT)
#define IS_OB_SEC_BOOT_LOCK(__VALUE__)                 (((__VALUE__) == OB_BOOT_ENTRY_FORCED_NONE)\
                                                        || ((__VALUE__) == OB_BOOT_ENTRY_FORCED_FLASH))

#define IS_OB_SEC_SIZE(__VALUE__)                      ((__VALUE__) < (FLASH_PAGE_NB + 1U))
#endif /* FLASH_SECURABLE_MEMORY_SUPPORT */

#define IS_FLASH_LATENCY(__LATENCY__)                  (((__LATENCY__) == FLASH_LATENCY_0) || \
                                                        ((__LATENCY__) == FLASH_LATENCY_1) || \
                                                        ((__LATENCY__) == FLASH_LATENCY_2))
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
#endif

#endif /* STM32G0xx_HAL_FLASH_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
