/**
  ******************************************************************************
  * @file    stm32l5xx_hal_flash.h
  * @author  MCD Application Team
  * @brief   Header file of FLASH HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#ifndef STM32L5xx_HAL_FLASH_H
#define STM32L5xx_HAL_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l5xx_hal_def.h"

/** @addtogroup STM32L5xx_HAL_Driver
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
  uint32_t Page;        /*!< Initial Flash page to erase when page erase is disabled
                             This parameter must be a value between 0 and (max number of pages in the bank - 1)
                             (eg : 127 for 512kB dual bank) */
  uint32_t NbPages;     /*!< Number of pages to be erased.
                             This parameter must be a value between 1 and (max number of pages in the bank - value of initial page)*/
} FLASH_EraseInitTypeDef;

/**
  * @brief  FLASH Option Bytes Program structure definition
  */
typedef struct
{
  uint32_t OptionType;       /*!< Option byte to be configured.
                                  This parameter can be a combination of the values of @ref FLASH_OB_Type */
  uint32_t WRPArea;          /*!< Write protection area to be programmed (used for OPTIONBYTE_WRP).
                                  Only one WRP area could be programmed at the same time.
                                  This parameter can be value of @ref FLASH_OB_WRP_Area */
  uint32_t WRPStartOffset;   /*!< Write protection start offset (used for OPTIONBYTE_WRP).
                                  This parameter must be a value between 0 and (max number of pages in the bank - 1)
                                  (eg : 127 for 512kB dual bank) */
  uint32_t WRPEndOffset;     /*!< Write protection end offset (used for OPTIONBYTE_WRP).
                                  This parameter must be a value between WRPStartOffset and (max number of pages in the bank - 1) */
  uint32_t RDPLevel;         /*!< Set the read protection level.. (used for OPTIONBYTE_RDP).
                                  This parameter can be a value of @ref FLASH_OB_Read_Protection */
  uint32_t USERType;         /*!< User option byte(s) to be configured (used for OPTIONBYTE_USER).
                                  This parameter can be a combination of @ref FLASH_OB_USER_Type */
  uint32_t USERConfig;       /*!< Value of the user option byte (used for OPTIONBYTE_USER).
                                  This parameter can be a combination of @ref FLASH_OB_USER_BOR_LEVEL,
                                  @ref FLASH_OB_USER_nRST_STOP, @ref FLASH_OB_USER_nRST_STANDBY,
                                  @ref FLASH_OB_USER_nRST_SHUTDOWN, @ref FLASH_OB_USER_IWDG_SW,
                                  @ref FLASH_OB_USER_IWDG_STOP, @ref FLASH_OB_USER_IWDG_STANDBY,
                                  @ref FLASH_OB_USER_WWDG_SW, @ref FLASH_OB_USER_SWAP_BANK,
								  @ref FLASH_OB_USER_DUALBANK, @ref FLASH_OB_USER_DBANK,
                                  @ref FLASH_OB_USER_SRAM2_PAR, @ref FLASH_OB_USER_SRAM2_RST,
                                  @ref FLASH_OB_USER_nSWBOOT0, @ref FLASH_OB_USER_nBOOT0,
                                  @ref FLASH_OB_USER_PA15_PUPEN and @ref FLASH_OB_USER_TZEN */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  uint32_t WMSecConfig;      /*!< Configuration of the Watermark-based Secure Area (used for OPTIONBYTE_WMSEC).
                                  This parameter must be a value of @ref FLASH_OB_WMSEC */
  uint32_t WMSecStartPage;   /*!< Start page of secure area (used for OPTIONBYTE_WMSEC).
                                  This parameter must be a value between 0 and (max number of pages in the bank - 1) */
  uint32_t WMSecEndPage;     /*!< End page of secure area (used for OPTIONBYTE_WMSEC).
                                  This parameter must be a value between WMSecStartPage and (max number of pages in the bank - 1) */
  uint32_t WMHDPEndPage;     /*!< End page of the secure hide protection (used for OPTIONBYTE_WMSEC).
                                  This parameter must be a value between WMSecStartPage and WMPCROPStartPage
                                  (if PCROP area activated) or WMSecEndPage */
  uint32_t BootLock;           /*!< Configuration of the boot lock (used for OPTIONBYTE_BOOT_LOCK).
                                  This parameter must be a value of @ref FLASH_OB_BOOT_LOCK */
#endif
  uint32_t BootAddrConfig;   /*!< Configuration of the Boot address (used for OPTIONBYTE_BOOTADDR).
                                  This parameter must be a value of @ref FLASH_OB_BOOTADDR */
  uint32_t BootAddr;         /*!< Boot address (used for OPTIONBYTE_BOOTADDR).
                                  This parameter must be a value between 0x0 and 0xFFFFFF00 */
} FLASH_OBProgramInitTypeDef;

/**
  * @brief  FLASH handle Structure definition
  */
typedef struct
{
  HAL_LockTypeDef        Lock;              /*!< FLASH locking object */
  uint32_t               ErrorCode;         /*!< FLASH error code */
  uint32_t               ProcedureOnGoing;  /*!< Internal variable to indicate which procedure is ongoing or not in IT context */
  uint32_t               Address;           /*!< Internal variable to save address selected for program in IT context */
  uint32_t               Bank;              /*!< Internal variable to save current bank selected during erase in IT context */
  uint32_t               Page;              /*!< Internal variable to define the current page which is being erased in IT context */
  uint32_t               NbPagesToErase;    /*!< Internal variable to save the remaining pages to erase in IT context */
}FLASH_ProcessTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup FLASH_Exported_Constants FLASH Exported Constants
  * @{
  */

/** @defgroup FLASH_Flags FLASH Flags Definition
  * @{
  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define FLASH_FLAG_EOP       FLASH_SECSR_SECEOP                   /*!< FLASH End of operation flag */
#define FLASH_FLAG_OPERR     FLASH_SECSR_SECOPERR                 /*!< FLASH Operation error flag */
#define FLASH_FLAG_PROGERR   FLASH_SECSR_SECPROGERR               /*!< FLASH Programming error flag */
#define FLASH_FLAG_WRPERR    FLASH_SECSR_SECWRPERR                /*!< FLASH Write protection error flag */
#define FLASH_FLAG_PGAERR    FLASH_SECSR_SECPGAERR                /*!< FLASH Programming alignment error flag */
#define FLASH_FLAG_SIZERR    FLASH_SECSR_SECSIZERR                /*!< FLASH Size error flag */
#define FLASH_FLAG_PGSERR    FLASH_SECSR_SECPGSERR                /*!< FLASH Programming sequence error flag */
#define FLASH_FLAG_OPTWERR   FLASH_NSSR_OPTWERR                   /*!< FLASH Option modification error flag  */
#define FLASH_FLAG_BSY       FLASH_SECSR_SECBSY                   /*!< FLASH Busy flag */
#define FLASH_FLAG_ECCC      (FLASH_ECCR_ECCC | FLASH_ECCR_ECCC2) /*!< FLASH ECC correction */
#define FLASH_FLAG_ECCD      (FLASH_ECCR_ECCD | FLASH_ECCR_ECCD2) /*!< FLASH ECC detection */

#define FLASH_FLAG_SR_ERRORS    (FLASH_FLAG_OPERR  | FLASH_FLAG_PROGERR | FLASH_FLAG_WRPERR | \
                                 FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR  | FLASH_FLAG_PGSERR)         /*!< Flash all flags from Status Register */
#define FLASH_FLAG_ECCR_ERRORS  (FLASH_FLAG_ECCD | FLASH_FLAG_ECCC)                                  /*!< Flash all flags from ECC Register */
#define FLASH_FLAG_ALL_ERRORS   (FLASH_FLAG_SR_ERRORS | FLASH_FLAG_OPTWERR | FLASH_FLAG_ECCR_ERRORS) /*!< Flash all flags */
#else
#define FLASH_FLAG_EOP       FLASH_NSSR_NSEOP                     /*!< FLASH End of operation flag */
#define FLASH_FLAG_OPERR     FLASH_NSSR_NSOPERR                   /*!< FLASH Operation error flag */
#define FLASH_FLAG_PROGERR   FLASH_NSSR_NSPROGERR                 /*!< FLASH Programming error flag */
#define FLASH_FLAG_WRPERR    FLASH_NSSR_NSWRPERR                  /*!< FLASH Write protection error flag */
#define FLASH_FLAG_PGAERR    FLASH_NSSR_NSPGAERR                  /*!< FLASH Programming alignment error flag */
#define FLASH_FLAG_SIZERR    FLASH_NSSR_NSSIZERR                  /*!< FLASH Size error flag  */
#define FLASH_FLAG_PGSERR    FLASH_NSSR_NSPGSERR                  /*!< FLASH Programming sequence error flag */
#define FLASH_FLAG_OPTWERR   FLASH_NSSR_OPTWERR                   /*!< FLASH Option modification error flag  */
#define FLASH_FLAG_BSY       FLASH_NSSR_NSBSY                     /*!< FLASH Busy flag */
#define FLASH_FLAG_ECCC      (FLASH_ECCR_ECCC | FLASH_ECCR_ECCC2) /*!< FLASH ECC correction */
#define FLASH_FLAG_ECCD      (FLASH_ECCR_ECCD | FLASH_ECCR_ECCD2) /*!< FLASH ECC detection */

#define FLASH_FLAG_SR_ERRORS    (FLASH_FLAG_OPERR  | FLASH_FLAG_PROGERR | FLASH_FLAG_WRPERR  | \
                                 FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR  | FLASH_FLAG_PGSERR  | \
                                 FLASH_FLAG_OPTWERR)                            /*!< Flash all flags from Status Register */
#define FLASH_FLAG_ECCR_ERRORS  (FLASH_FLAG_ECCD | FLASH_FLAG_ECCC)             /*!< Flash all flags from ECC Register */
#define FLASH_FLAG_ALL_ERRORS   (FLASH_FLAG_SR_ERRORS | FLASH_FLAG_ECCR_ERRORS) /*!< Flash all flags */
#endif
/**
  * @}
  */

/** @defgroup FLASH_Interrupt_definition FLASH Interrupts Definition
  * @brief FLASH Interrupt definition
  * @{
  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define FLASH_IT_EOP     FLASH_SECCR_SECEOPIE     /*!< End of FLASH Operation Interrupt source */
#define FLASH_IT_OPERR   FLASH_SECCR_SECERRIE     /*!< Error Interrupt source */
#define FLASH_IT_ECCC    (FLASH_ECCR_ECCIE >> 24) /*!< ECC Correction Interrupt source */
#else
#define FLASH_IT_EOP     FLASH_NSCR_NSEOPIE       /*!< End of FLASH Operation Interrupt source */
#define FLASH_IT_OPERR   FLASH_NSCR_NSERRIE       /*!< Error Interrupt source */
#define FLASH_IT_ECCC    (FLASH_ECCR_ECCIE >> 24) /*!< ECC Correction Interrupt source */
#endif
/**
  * @}
  */

/** @defgroup FLASH_Error FLASH Error
  * @{
  */
#define HAL_FLASH_ERROR_NONE   0x00000000U        /*!< Flash no error */
#define HAL_FLASH_ERROR_OP     FLASH_FLAG_OPERR   /*!< Flash operation error */
#define HAL_FLASH_ERROR_PROG   FLASH_FLAG_PROGERR /*!< Flash programming error */
#define HAL_FLASH_ERROR_WRP    FLASH_FLAG_WRPERR  /*!< Flash write protection error */
#define HAL_FLASH_ERROR_PGA    FLASH_FLAG_PGAERR  /*!< Flash programming alignment error */
#define HAL_FLASH_ERROR_SIZ    FLASH_FLAG_SIZERR  /*!< Flash size error */
#define HAL_FLASH_ERROR_PGS    FLASH_FLAG_PGSERR  /*!< Flash programming sequence error */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#else
#define HAL_FLASH_ERROR_OPTW   FLASH_FLAG_OPTWERR /*!< Flash option modification error */
#endif
#define HAL_FLASH_ERROR_ECCC   FLASH_FLAG_ECCC    /*!< Flash ECC correction error */
#define HAL_FLASH_ERROR_ECCD   FLASH_FLAG_ECCD    /*!< Flash ECC detection error */
/**
  * @}
  */

/** @defgroup FLASH_Type_Erase FLASH Erase Type
  * @{
  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define FLASH_TYPEERASE_PAGES        FLASH_SECCR_SECPER                                                /*!<Secure pages erase only*/
#define FLASH_TYPEERASE_PAGES_NS     (FLASH_NSCR_NSPER    | FLASH_NON_SECURE_MASK)                     /*!<Non-secure pages erase only*/
#define FLASH_TYPEERASE_MASSERASE    (FLASH_SECCR_SECMER1 | FLASH_SECCR_SECMER2)                       /*!<Secure flash mass erase activation*/
#define FLASH_TYPEERASE_MASSERASE_NS (FLASH_NSCR_NSMER1   | FLASH_NSCR_NSMER2 | FLASH_NON_SECURE_MASK) /*!<Non-secure flash mass erase activation*/
#else
#define FLASH_TYPEERASE_PAGES       FLASH_NSCR_NSPER                            /*!<Pages erase only*/
#define FLASH_TYPEERASE_MASSERASE   (FLASH_NSCR_NSMER1 | FLASH_NSCR_NSMER2)     /*!<Flash mass erase activation*/
#endif
/**
  * @}
  */

/** @defgroup FLASH_Banks FLASH Banks
  * @{
  */
#define FLASH_BANK_1      0x00000001U                   /*!< Bank 1   */
#define FLASH_BANK_2      0x00000002U                   /*!< Bank 2   */
#define FLASH_BANK_BOTH   (FLASH_BANK_1 | FLASH_BANK_2) /*!< Bank1 and Bank2  */
/**
  * @}
  */

/** @defgroup FLASH_Type_Program FLASH Program Type
  * @{
  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define FLASH_TYPEPROGRAM_DOUBLEWORD    FLASH_SECCR_SECPG                         /*!<Program a double-word (64-bit) at a specified secure address.*/
#define FLASH_TYPEPROGRAM_DOUBLEWORD_NS (FLASH_NSCR_NSPG | FLASH_NON_SECURE_MASK) /*!<Program a double-word (64-bit) at a specified non-secure address.*/
#else
#define FLASH_TYPEPROGRAM_DOUBLEWORD    FLASH_NSCR_NSPG                           /*!<Program a double-word (64-bit) at a specified address.*/
#endif
/**
  * @}
  */

/** @defgroup FLASH_OB_Type FLASH Option Bytes Type
  * @{
  */
#define OPTIONBYTE_WRP        0x00000001U /*!< WRP option byte configuration */
#define OPTIONBYTE_RDP        0x00000002U /*!< RDP option byte configuration */
#define OPTIONBYTE_USER       0x00000004U /*!< USER option byte configuration */
#define OPTIONBYTE_BOOTADDR   0x00000008U /*!< Boot address option byte configuration */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define OPTIONBYTE_WMSEC      0x00000010U /*!< Watermark-based secure area option byte configuration */
#define OPTIONBYTE_BOOT_LOCK  0x00000020U /*!< Boot lock option byte configuration */
#endif
/**
  * @}
  */

/** @defgroup FLASH_OB_WRP_Area FLASH WRP Area
  * @{
  */
#define OB_WRPAREA_BANK1_AREAA   0x00000001U /*!< Flash Bank 1 Area A */
#define OB_WRPAREA_BANK1_AREAB   0x00000002U /*!< Flash Bank 1 Area B */
#define OB_WRPAREA_BANK2_AREAA   0x00000004U /*!< Flash Bank 2 Area A */
#define OB_WRPAREA_BANK2_AREAB   0x00000008U /*!< Flash Bank 2 Area B */
/**
  * @}
  */

/** @defgroup FLASH_OB_Read_Protection FLASH Option Bytes Read Protection
  * @{
  */
#define OB_RDP_LEVEL_0   ((uint32_t)0xAA) /*!< RDP level 0 code */
#define OB_RDP_LEVEL_0_5 ((uint32_t)0x55) /*!< RDP level 0.5 code */
#define OB_RDP_LEVEL_1   ((uint32_t)0xBB) /*!< RDP level 1 code */
#define OB_RDP_LEVEL_2   ((uint32_t)0xCC) /*!< RDP level 2 code.
                                               Warning: When enabling read protection level 2
                                               it's no more possible to go back to level 1 or 0. */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_Type FLASH Option Bytes User Type
  * @{
  */
#define OB_USER_BOR_LEV      0x00000001U /*!< BOR reset Level */
#define OB_USER_nRST_STOP    0x00000002U /*!< Reset generated when entering the stop mode */
#define OB_USER_nRST_STDBY   0x00000004U /*!< Reset generated when entering the standby mode */
#define OB_USER_nRST_SHDW    0x00000008U /*!< Reset generated when entering the shutdown mode */
#define OB_USER_IWDG_SW      0x00000010U /*!< Independent watchdog selection */
#define OB_USER_IWDG_STOP    0x00000020U /*!< Independent watchdog counter freeze in stop mode */
#define OB_USER_IWDG_STDBY   0x00000040U /*!< Independent watchdog counter freeze in standby mode */
#define OB_USER_WWDG_SW      0x00000080U /*!< Window watchdog selection */
#define OB_USER_SWAP_BANK    0x00000100U /*!< Swap banks */
#define OB_USER_DUALBANK     0x00000200U /*!< Dual-Bank on 256kB Flash memory devices */
#define OB_USER_DBANK        0x00000400U /*!< Single bank with 128-bits data or two banks with 64-bits data */
#define OB_USER_SRAM2_PE     0x00000800U /*!< SRAM2 parity error enable */
#define OB_USER_SRAM2_RST    0x00001000U /*!< SRAM2 Erase when system reset */
#define OB_USER_nSWBOOT0     0x00002000U /*!< Software BOOT0 */
#define OB_USER_nBOOT0       0x00004000U /*!< nBOOT0 option bit */
#define OB_USER_PA15_PUPEN   0x00008000U /*!< PA15 pull-up enable option bit */
#define OB_USER_TZEN         0x00010000U /*!< Global TrustZone enable */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_BOR_LEVEL FLASH Option Bytes User BOR Level
  * @{
  */
#define OB_BOR_LEVEL_0   FLASH_OPTR_BOR_LEV_0 /*!< Reset level threshold is around 1.7V */
#define OB_BOR_LEVEL_1   FLASH_OPTR_BOR_LEV_1 /*!< Reset level threshold is around 2.0V */
#define OB_BOR_LEVEL_2   FLASH_OPTR_BOR_LEV_2 /*!< Reset level threshold is around 2.2V */
#define OB_BOR_LEVEL_3   FLASH_OPTR_BOR_LEV_3 /*!< Reset level threshold is around 2.5V */
#define OB_BOR_LEVEL_4   FLASH_OPTR_BOR_LEV_4 /*!< Reset level threshold is around 2.8V */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_nRST_STOP FLASH Option Bytes User Reset On Stop
  * @{
  */
#define OB_STOP_RST     0x00000000U          /*!< Reset generated when entering the stop mode */
#define OB_STOP_NORST   FLASH_OPTR_nRST_STOP /*!< No reset generated when entering the stop mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_nRST_STANDBY FLASH Option Bytes User Reset On Standby
  * @{
  */
#define OB_STANDBY_RST     0x00000000U           /*!< Reset generated when entering the standby mode */
#define OB_STANDBY_NORST   FLASH_OPTR_nRST_STDBY /*!< No reset generated when entering the standby mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_nRST_SHUTDOWN FLASH Option Bytes User Reset On Shutdown
  * @{
  */
#define OB_SHUTDOWN_RST     0x00000000U          /*!< Reset generated when entering the shutdown mode */
#define OB_SHUTDOWN_NORST   FLASH_OPTR_nRST_SHDW /*!< No reset generated when entering the shutdown mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IWDG_SW FLASH Option Bytes User IWDG Type
  * @{
  */
#define OB_IWDG_HW   0x00000000U        /*!< Hardware independent watchdog */
#define OB_IWDG_SW   FLASH_OPTR_IWDG_SW /*!< Software independent watchdog */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IWDG_STOP FLASH Option Bytes User IWDG Mode On Stop
  * @{
  */
#define OB_IWDG_STOP_FREEZE   0x00000000U          /*!< Independent watchdog counter is frozen in Stop mode */
#define OB_IWDG_STOP_RUN      FLASH_OPTR_IWDG_STOP /*!< Independent watchdog counter is running in Stop mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IWDG_STANDBY FLASH Option Bytes User IWDG Mode On Standby
  * @{
  */
#define OB_IWDG_STDBY_FREEZE   0x00000000U           /*!< Independent watchdog counter is frozen in Standby mode */
#define OB_IWDG_STDBY_RUN      FLASH_OPTR_IWDG_STDBY /*!< Independent watchdog counter is running in Standby mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_WWDG_SW FLASH Option Bytes User WWDG Type
  * @{
  */
#define OB_WWDG_HW   0x00000000U        /*!< Hardware window watchdog */
#define OB_WWDG_SW   FLASH_OPTR_WWDG_SW /*!< Software window watchdog */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_SWAP_BANK FLASH Option Bytes User Swap banks
  * @{
  */
#define OB_SWAP_BANK_DISABLE   0x00000000U          /*!< Bank 1 is located at AHB address 0x0, Bank 2 is located at 0x40000 */
#define OB_SWAP_BANK_ENABLE    FLASH_OPTR_SWAP_BANK /*!< Bank 1 is located at AHB address 0x40000, Bank 2 is located at 0x0 */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_DUALBANK FLASH Option Bytes User Dual-bank Type
  * @{
  */
#define OB_DUALBANK_SINGLE   0x00000000U       /*!< 256 kB Single-bank Flash */
#define OB_DUALBANK_DUAL     FLASH_OPTR_DB256K /*!< 256 kB Dual-bank Flash */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_DBANK FLASH Option Bytes User DBANK Type
  * @{
  */
#define OB_DBANK_128_BITS   0x00000000U      /*!< Single-bank with 128-bits data */
#define OB_DBANK_64_BITS    FLASH_OPTR_DBANK /*!< Dual-bank with 64-bits data */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_SRAM2_PAR FLASH Option Bytes User SRAM2 Parity error enable
  * @{
  */
#define OB_SRAM2_PARITY_ENABLE    0x00000000U         /*!< SRAM2 parity error generation enable */
#define OB_SRAM2_PARITY_DISABLE   FLASH_OPTR_SRAM2_PE /*!< SRAM2 parity check disable */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_SRAM2_RST FLASH Option Bytes User SRAM2 Erase On Reset Type
  * @{
  */
#define OB_SRAM2_RST_ERASE       0x00000000U          /*!< SRAM2 erased when a system reset occurs */
#define OB_SRAM2_RST_NOT_ERASE   FLASH_OPTR_SRAM2_RST /*!< SRAM2 is not erased when a system reset occurs */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_nSWBOOT0 FLASH Option Bytes User Software BOOT0
  * @{
  */
#define OB_BOOT0_FROM_OB    0x00000000U         /*!< BOOT0 taken from the option bit nBOOT0 */
#define OB_BOOT0_FROM_PIN   FLASH_OPTR_nSWBOOT0 /*!< BOOT0 taken from BOOT0 pin */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_nBOOT0 FLASH Option Bytes User nBOOT0 option bit
  * @{
  */
#define OB_nBOOT0_RESET   0x00000000U       /*!< nBOOT0 = 0 */
#define OB_nBOOT0_SET     FLASH_OPTR_nBOOT0 /*!< nBOOT0 = 1 */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_PA15_PUPEN FLASH Option Bytes User PA15 pull-up enable option bit
  * @{
  */
#define OB_PA15_PUP_DISABLE   0x00000000U           /*!< USB power delivery dead-battery enabled/ TDI pull-up deactivated */
#define OB_PA15_PUP_ENABLE    FLASH_OPTR_PA15_PUPEN /*!< USB power delivery dead-battery disabled/ TDI pull-up activated */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_TZEN FLASH Option Bytes User Global TrustZone
  * @{
  */
#define OB_TZEN_DISABLE   0x00000000U     /*!< no TrustZone */
#define OB_TZEN_ENABLE    FLASH_OPTR_TZEN /*!< TrustZone */
/**
  * @}
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/** @defgroup FLASH_OB_BOOT_LOCK FLASH Option Bytes Boot Lock
  * @{
  */
#define OB_BOOT_LOCK_DISABLE   0x00000000U                  /*!< Boot lock disable */
#define OB_BOOT_LOCK_ENABLE    FLASH_SECBOOTADD0R_BOOT_LOCK /*!< Boot lock enable */
/**
  * @}
  */

/** @defgroup FLASH_OB_WMSEC FLASH Option Bytes Watermarked-based security configuration
  * @{
  */
#define OB_WMSEC_AREA1                 FLASH_BANK_1 /*!< Watermarked-based security area for bank 1 */
#define OB_WMSEC_AREA2                 FLASH_BANK_2 /*!< Watermarked-based security area for bank 2 */

#define OB_WMSEC_SECURE_AREA_CONFIG    0x00000010U  /*!< Configure Watermarked-based security area       */
#define OB_WMSEC_HDP_AREA_CONFIG       0x00000020U  /*!< Configure Watermarked-based secure hide area    */
#define OB_WMSEC_HDP_AREA_ENABLE       0x00000080U  /*!< Enable Watermarked-based secure hide area       */
#define OB_WMSEC_HDP_AREA_DISABLE      0x00000100U  /*!< Disable Watermarked-based secure hide area      */
/**
  * @}
  */
#endif

/** @defgroup FLASH_OB_BOOTADDR FLASH Option Bytes Boot address
  * @{
  */
#define OB_BOOTADDR_NS0      0x00000001U   /*!< Non-secure boot address 0 */
#define OB_BOOTADDR_NS1      0x00000002U   /*!< Non-secure boot address 1 */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define OB_BOOTADDR_SEC0     0x00000004U   /*!< Secure boot address 0 */
#endif
/**
  * @}
  */

/** @defgroup FLASH_Latency FLASH Latency
  * @{
  */
#define FLASH_LATENCY_0    FLASH_ACR_LATENCY_0WS  /*!< FLASH Zero wait state */
#define FLASH_LATENCY_1    FLASH_ACR_LATENCY_1WS  /*!< FLASH One wait state */
#define FLASH_LATENCY_2    FLASH_ACR_LATENCY_2WS  /*!< FLASH Two wait states */
#define FLASH_LATENCY_3    FLASH_ACR_LATENCY_3WS  /*!< FLASH Three wait states */
#define FLASH_LATENCY_4    FLASH_ACR_LATENCY_4WS  /*!< FLASH Four wait states */
#define FLASH_LATENCY_5    FLASH_ACR_LATENCY_5WS  /*!< FLASH Five wait state */
#define FLASH_LATENCY_6    FLASH_ACR_LATENCY_6WS  /*!< FLASH Six wait state */
#define FLASH_LATENCY_7    FLASH_ACR_LATENCY_7WS  /*!< FLASH Seven wait states */
#define FLASH_LATENCY_8    FLASH_ACR_LATENCY_8WS  /*!< FLASH Eight wait states */
#define FLASH_LATENCY_9    FLASH_ACR_LATENCY_9WS  /*!< FLASH Nine wait states */
#define FLASH_LATENCY_10   FLASH_ACR_LATENCY_10WS /*!< FLASH Ten wait state */
#define FLASH_LATENCY_11   FLASH_ACR_LATENCY_11WS /*!< FLASH Eleven wait state */
#define FLASH_LATENCY_12   FLASH_ACR_LATENCY_12WS /*!< FLASH Twelve wait states */
#define FLASH_LATENCY_13   FLASH_ACR_LATENCY_13WS /*!< FLASH Thirteen wait states */
#define FLASH_LATENCY_14   FLASH_ACR_LATENCY_14WS /*!< FLASH Fourteen wait states */
#define FLASH_LATENCY_15   FLASH_ACR_LATENCY_15WS /*!< FLASH Fifteen wait states */
/**
  * @}
  */

/** @defgroup FLASH_Keys FLASH Keys
  * @{
  */
#define FLASH_KEY1   0x45670123U /*!< Flash key1 */
#define FLASH_KEY2   0xCDEF89ABU /*!< Flash key2: used with FLASH_KEY1
                                      to unlock the FLASH registers access */

#define FLASH_PDKEY1   0x04152637U /*!< Flash power down key1 */
#define FLASH_PDKEY2   0xFAFBFCFDU /*!< Flash power down key2: used with FLASH_PDKEY1
                                        to unlock the RUN_PD bit in FLASH_ACR */

#define FLASH_OPTKEY1   0x08192A3BU /*!< Flash option byte key1 */
#define FLASH_OPTKEY2   0x4C5D6E7FU /*!< Flash option byte key2: used with FLASH_OPTKEY1
                                         to allow option bytes operations */

#define FLASH_LVEKEY1   0xF4F5F6F7U /*!< Flash LVE key1 */
#define FLASH_LVEKEY2   0x0A1B2C3DU /*!< Flash LVE key2: used with FLASH_LVEKEY1
                                         to unblock the LVEN bit in FLASH_ACR */
/**
  * @}
  */

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
  * @param  __LATENCY__ FLASH Latency.
  *         This parameter can be one of the following values :
  *     @arg FLASH_LATENCY_0: FLASH Zero wait state
  *     @arg FLASH_LATENCY_1: FLASH One wait state
  *     @arg FLASH_LATENCY_2: FLASH Two wait states
  *     @arg FLASH_LATENCY_3: FLASH Three wait states
  *     @arg FLASH_LATENCY_4: FLASH Four wait states
  *     @arg FLASH_LATENCY_5: FLASH Five wait states
  *     @arg FLASH_LATENCY_6: FLASH Six wait states
  *     @arg FLASH_LATENCY_7: FLASH Seven wait states
  *     @arg FLASH_LATENCY_8: FLASH Eight wait states
  *     @arg FLASH_LATENCY_9: FLASH Nine wait states
  *     @arg FLASH_LATENCY_10: FLASH Ten wait states
  *     @arg FLASH_LATENCY_11: FLASH Eleven wait states
  *     @arg FLASH_LATENCY_12: FLASH Twelve wait states
  *     @arg FLASH_LATENCY_13: FLASH Thirteen wait states
  *     @arg FLASH_LATENCY_14: FLASH Fourteen wait states
  *     @arg FLASH_LATENCY_15: FLASH Fifteen wait states
  * @retval None
  */
#define __HAL_FLASH_SET_LATENCY(__LATENCY__)   (MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (__LATENCY__)))

/**
  * @brief  Get the FLASH Latency.
  * @retval FLASH Latency
  *         This parameter can be one of the following values :
  *     @arg FLASH_LATENCY_0: FLASH Zero wait state
  *     @arg FLASH_LATENCY_1: FLASH One wait state
  *     @arg FLASH_LATENCY_2: FLASH Two wait states
  *     @arg FLASH_LATENCY_3: FLASH Three wait states
  *     @arg FLASH_LATENCY_4: FLASH Four wait states
  *     @arg FLASH_LATENCY_5: FLASH Five wait states
  *     @arg FLASH_LATENCY_6: FLASH Six wait states
  *     @arg FLASH_LATENCY_7: FLASH Seven wait states
  *     @arg FLASH_LATENCY_8: FLASH Eight wait states
  *     @arg FLASH_LATENCY_9: FLASH Nine wait states
  *     @arg FLASH_LATENCY_10: FLASH Ten wait states
  *     @arg FLASH_LATENCY_11: FLASH Eleven wait states
  *     @arg FLASH_LATENCY_12: FLASH Twelve wait states
  *     @arg FLASH_LATENCY_13: FLASH Thirteen wait states
  *     @arg FLASH_LATENCY_14: FLASH Fourteen wait states
  *     @arg FLASH_LATENCY_15: FLASH Fifteen wait states
  */
#define __HAL_FLASH_GET_LATENCY()   READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY)

/**
  * @brief  Enable the FLASH power down during Low-power run mode.
  * @retval None
  * @note   Writing this bit to 0, automatically the keys are
  *         lost and a new unlock sequence is necessary to re-write it to 1.
  */
#define __HAL_FLASH_POWER_DOWN_ENABLE()         do { WRITE_REG(FLASH->PDKEYR, FLASH_PDKEY1); \
                                                     WRITE_REG(FLASH->PDKEYR, FLASH_PDKEY2); \
                                                     SET_BIT(FLASH->ACR, FLASH_ACR_RUN_PD);  \
                                                   } while (0)

/**
  * @brief  Disable the FLASH power down during Low-power run mode.
  * @retval None
  * @note   Writing this bit to 1, automatically the keys are
  *         loss and a new unlock sequence is necessary to re-write it to 0.
  */
#define __HAL_FLASH_POWER_DOWN_DISABLE()        do { WRITE_REG(FLASH->PDKEYR, FLASH_PDKEY1);  \
                                                     WRITE_REG(FLASH->PDKEYR, FLASH_PDKEY2);  \
                                                     CLEAR_BIT(FLASH->ACR, FLASH_ACR_RUN_PD); \
                                                   } while (0)

/**
  * @brief  Enable the FLASH power down during Low-Power sleep mode
  * @retval None
  */
#define __HAL_FLASH_SLEEP_POWERDOWN_ENABLE()    SET_BIT(FLASH->ACR, FLASH_ACR_SLEEP_PD)

/**
  * @brief  Disable the FLASH power down during Low-Power sleep mode
  * @retval None
  */
#define __HAL_FLASH_SLEEP_POWERDOWN_DISABLE()   CLEAR_BIT(FLASH->ACR, FLASH_ACR_SLEEP_PD)

/**
  * @}
  */

/** @defgroup FLASH_Interrupt FLASH Interrupts Macros
 *  @brief macros to handle FLASH interrupts
 * @{
 */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Enable secure FLASH interrupts from the secure world.
  * @param  __INTERRUPT__ FLASH interrupt.
  *         This parameter can be any combination of the following values:
  *     @arg FLASH_IT_EOP: End of FLASH Operation Interrupt
  *     @arg FLASH_IT_OPERR: Error Interrupt
  *     @arg FLASH_IT_ECCC: ECC Correction Interrupt
  * @retval None
  */
/* Enable secure FLASH interrupts from the secure world */
#define __HAL_FLASH_ENABLE_IT(__INTERRUPT__)    do { if(((__INTERRUPT__) & FLASH_IT_ECCC) != 0U) { SET_BIT(FLASH->ECCR, FLASH_ECCR_ECCIE); }\
                                                     if(((__INTERRUPT__) & (~FLASH_IT_ECCC)) != 0U) { SET_BIT(FLASH->SECCR, ((__INTERRUPT__) & (~FLASH_IT_ECCC))); }\
                                                   } while(0)
/**
  * @brief  Enable non-secure FLASH interrupts from the secure world.
  * @param  __INTERRUPT__ FLASH interrupt.
  *         This parameter can be any combination of the following values:
  *     @arg FLASH_IT_EOP: End of FLASH Operation Interrupt
  *     @arg FLASH_IT_OPERR: Error Interrupt
  *     @arg FLASH_IT_ECCC: ECC Correction Interrupt
  * @retval None
  */
#define __HAL_FLASH_ENABLE_IT_NS(__INTERRUPT__) do { if(((__INTERRUPT__) & FLASH_IT_ECCC) != 0U) { SET_BIT(FLASH->ECCR, FLASH_ECCR_ECCIE); }\
                                                     if(((__INTERRUPT__) & (~FLASH_IT_ECCC)) != 0U) { SET_BIT(FLASH->NSCR, ((__INTERRUPT__) & (~FLASH_IT_ECCC))); }\
                                                   } while(0)
#else
/**
  * @brief  Enable non-secure FLASH interrupts from the non-secure world.
  * @param  __INTERRUPT__ FLASH interrupt.
  *         This parameter can be any combination of the following values:
  *     @arg FLASH_IT_EOP: End of FLASH Operation Interrupt
  *     @arg FLASH_IT_OPERR: Error Interrupt
  *     @arg FLASH_IT_ECCC: ECC Correction Interrupt
  * @retval None
  */
#define __HAL_FLASH_ENABLE_IT(__INTERRUPT__)    do { if(((__INTERRUPT__) & FLASH_IT_ECCC) != 0U) { SET_BIT(FLASH->ECCR, FLASH_ECCR_ECCIE); }\
                                                     if(((__INTERRUPT__) & (~FLASH_IT_ECCC)) != 0U) { SET_BIT(FLASH->NSCR, ((__INTERRUPT__) & (~FLASH_IT_ECCC))); }\
                                                   } while(0)
#endif /* __ARM_FEATURE_CMSE */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Disable secure FLASH interrupts from the secure world.
  * @param  __INTERRUPT__ FLASH interrupt.
  *         This parameter can be any combination of the following values:
  *     @arg FLASH_IT_EOP: End of FLASH Operation Interrupt
  *     @arg FLASH_IT_OPERR: Error Interrupt
  *     @arg FLASH_IT_ECCC: ECC Correction Interrupt
  * @retval None
  */
#define __HAL_FLASH_DISABLE_IT(__INTERRUPT__)    do { if(((__INTERRUPT__) & FLASH_IT_ECCC) != 0U) { CLEAR_BIT(FLASH->ECCR, FLASH_ECCR_ECCIE); }\
                                                      if(((__INTERRUPT__) & (~FLASH_IT_ECCC)) != 0U) { CLEAR_BIT(FLASH->SECCR, ((__INTERRUPT__) & (~FLASH_IT_ECCC))); }\
                                                    } while(0)
/**
  * @brief  Disable non-secure FLASH interrupts from the secure world.
  * @param  __INTERRUPT__ FLASH interrupt.
  *         This parameter can be any combination of the following values:
  *     @arg FLASH_IT_EOP: End of FLASH Operation Interrupt
  *     @arg FLASH_IT_OPERR: Error Interrupt
  *     @arg FLASH_IT_ECCC: ECC Correction Interrupt
  * @retval None
  */
#define __HAL_FLASH_DISABLE_IT_NS(__INTERRUPT__) do { if(((__INTERRUPT__) & FLASH_IT_ECCC) != 0U) { CLEAR_BIT(FLASH->ECCR, FLASH_ECCR_ECCIE); }\
                                                      if(((__INTERRUPT__) & (~FLASH_IT_ECCC)) != 0U) { CLEAR_BIT(FLASH->NSCR, ((__INTERRUPT__) & (~FLASH_IT_ECCC))); }\
                                                    } while(0)
#else
/**
  * @brief  Disable non-secure FLASH interrupts from the non-secure world.
  * @param  __INTERRUPT__ FLASH interrupt.
  *         This parameter can be any combination of the following values:
  *     @arg FLASH_IT_EOP: End of FLASH Operation Interrupt
  *     @arg FLASH_IT_OPERR: Error Interrupt
  *     @arg FLASH_IT_ECCC: ECC Correction Interrupt
  * @retval None
  */
#define __HAL_FLASH_DISABLE_IT(__INTERRUPT__)    do { if(((__INTERRUPT__) & FLASH_IT_ECCC) != 0U) { CLEAR_BIT(FLASH->ECCR, FLASH_ECCR_ECCIE); }\
                                                      if(((__INTERRUPT__) & (~FLASH_IT_ECCC)) != 0U) { CLEAR_BIT(FLASH->NSCR, ((__INTERRUPT__) & (~FLASH_IT_ECCC))); }\
                                                    } while(0)
#endif /* __ARM_FEATURE_CMSE */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Check whether the specified secure FLASH flags from the secure world is set or not.
  * @param  __FLAG__ specifies the FLASH flag to check.
  *   This parameter can be one of the following values:
  *     @arg FLASH_FLAG_EOP: FLASH End of Operation flag
  *     @arg FLASH_FLAG_OPERR: FLASH Operation error flag
  *     @arg FLASH_FLAG_PROGERR: FLASH Programming error flag
  *     @arg FLASH_FLAG_WRPERR: FLASH Write protection error flag
  *     @arg FLASH_FLAG_PGAERR: FLASH Programming alignment error flag
  *     @arg FLASH_FLAG_SIZERR: FLASH Size error flag
  *     @arg FLASH_FLAG_PGSERR: FLASH Programming sequence error flag
  *     @arg FLASH_FLAG_OPTWERR: FLASH Option modification error flag
  *     @arg FLASH_FLAG_BSY: FLASH write/erase operations in progress flag
  *     @arg FLASH_FLAG_ECCC: FLASH one ECC error has been detected and corrected
  *     @arg FLASH_FLAG_ECCD: FLASH two ECC errors have been detected
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
#define __HAL_FLASH_GET_FLAG(__FLAG__)          ((((__FLAG__) & FLASH_FLAG_ECCR_ERRORS) != 0U) ? \
                                                 (READ_BIT(FLASH->ECCR, (__FLAG__)) == (__FLAG__)) : \
                                                 ((((__FLAG__) & (FLASH_FLAG_OPTWERR)) != 0U) ? \
                                                  (READ_BIT(FLASH->NSSR, (__FLAG__)) == (__FLAG__)) : \
                                                  (READ_BIT(FLASH->SECSR, (__FLAG__)) == (__FLAG__))))
/**
  * @brief  Check whether the specified non-secure FLASH flags from the secure world is set or not.
  * @param  __FLAG__ specifies the FLASH flag to check.
  *   This parameter can be one of the following values:
  *     @arg FLASH_FLAG_EOP: FLASH End of Operation flag
  *     @arg FLASH_FLAG_OPERR: FLASH Operation error flag
  *     @arg FLASH_FLAG_PROGERR: FLASH Programming error flag
  *     @arg FLASH_FLAG_WRPERR: FLASH Write protection error flag
  *     @arg FLASH_FLAG_PGAERR: FLASH Programming alignment error flag
  *     @arg FLASH_FLAG_SIZERR: FLASH Size error flag
  *     @arg FLASH_FLAG_PGSERR: FLASH Programming sequence error flag
  *     @arg FLASH_FLAG_OPTWERR: FLASH Option modification error flag
  *     @arg FLASH_FLAG_BSY: FLASH write/erase operations in progress flag
  *     @arg FLASH_FLAG_ECCC: FLASH one ECC error has been detected and corrected
  *     @arg FLASH_FLAG_ECCD: FLASH two ECC errors have been detected
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
#define __HAL_FLASH_GET_FLAG_NS(__FLAG__)       ((((__FLAG__) & FLASH_FLAG_ECCR_ERRORS) != 0U) ? \
                                                 (READ_BIT(FLASH->ECCR, (__FLAG__)) == (__FLAG__)) : \
                                                 (READ_BIT(FLASH->NSSR, (__FLAG__)) == (__FLAG__)))
#else
/**
  * @brief  Check whether the specified non-secure FLASH flags from the non-secure world is set or not.
  * @param  __FLAG__ specifies the FLASH flag to check.
  *   This parameter can be one of the following values:
  *     @arg FLASH_FLAG_EOP: FLASH End of Operation flag
  *     @arg FLASH_FLAG_OPERR: FLASH Operation error flag
  *     @arg FLASH_FLAG_PROGERR: FLASH Programming error flag
  *     @arg FLASH_FLAG_WRPERR: FLASH Write protection error flag
  *     @arg FLASH_FLAG_PGAERR: FLASH Programming alignment error flag
  *     @arg FLASH_FLAG_SIZERR: FLASH Size error flag
  *     @arg FLASH_FLAG_PGSERR: FLASH Programming sequence error flag
  *     @arg FLASH_FLAG_OPTWERR: FLASH Option modification error flag
  *     @arg FLASH_FLAG_BSY: FLASH write/erase operations in progress flag
  *     @arg FLASH_FLAG_ECCC: FLASH one ECC error has been detected and corrected
  *     @arg FLASH_FLAG_ECCD: FLASH two ECC errors have been detected
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
#define __HAL_FLASH_GET_FLAG(__FLAG__)          ((((__FLAG__) & FLASH_FLAG_ECCR_ERRORS) != 0U) ? \
                                                 (READ_BIT(FLASH->ECCR, (__FLAG__)) == (__FLAG__)) : \
                                                 (READ_BIT(FLASH->NSSR, (__FLAG__)) == (__FLAG__)))
#endif /* __ARM_FEATURE_CMSE */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Clear secure FLASH flags from the secure world.
  * @param  __FLAG__ specifies the FLASH flags to clear.
  *   This parameter can be any combination of the following values:
  *     @arg FLASH_FLAG_EOP: FLASH End of Operation flag
  *     @arg FLASH_FLAG_OPERR: FLASH Operation error flag
  *     @arg FLASH_FLAG_PROGERR: FLASH Programming error flag
  *     @arg FLASH_FLAG_WRPERR: FLASH Write protection error flag
  *     @arg FLASH_FLAG_PGAERR: FLASH Programming alignment error flag
  *     @arg FLASH_FLAG_SIZERR: FLASH Size error flag
  *     @arg FLASH_FLAG_PGSERR: FLASH Programming sequence error flag
  *     @arg FLASH_FLAG_OPTWERR: FLASH Option modification error flag (Only in non-secure)
  *     @arg FLASH_FLAG_ECCC: FLASH one ECC error has been detected and corrected
  *     @arg FLASH_FLAG_ECCD: FLASH two ECC errors have been detected
  *     @arg FLASH_FLAG_ALL_ERRORS: FLASH All errors flags
  * @retval None
  */
#define __HAL_FLASH_CLEAR_FLAG(__FLAG__)        do { if(((__FLAG__) & FLASH_FLAG_ECCR_ERRORS) != 0U) { SET_BIT(FLASH->ECCR, ((__FLAG__) & FLASH_FLAG_ECCR_ERRORS)); }\
                                                     if(((__FLAG__) & FLASH_FLAG_OPTWERR) != 0U) { SET_BIT(FLASH->NSSR, ((__FLAG__) & (FLASH_FLAG_OPTWERR))); }\
                                                     if(((__FLAG__) & ~(FLASH_FLAG_ECCR_ERRORS | FLASH_FLAG_OPTWERR)) != 0U) { WRITE_REG(FLASH->SECSR, ((__FLAG__) & ~(FLASH_FLAG_ECCR_ERRORS | FLASH_FLAG_OPTWERR))); } \
                                                   } while(0)
/**
  * @brief  Clear non-secure FLASH flags from the secure world.
  * @param  __FLAG__ specifies the FLASH flags to clear.
  *   This parameter can be any combination of the following values:
  *     @arg FLASH_FLAG_EOP: FLASH End of Operation flag
  *     @arg FLASH_FLAG_OPERR: FLASH Operation error flag
  *     @arg FLASH_FLAG_PROGERR: FLASH Programming error flag
  *     @arg FLASH_FLAG_WRPERR: FLASH Write protection error flag
  *     @arg FLASH_FLAG_PGAERR: FLASH Programming alignment error flag
  *     @arg FLASH_FLAG_SIZERR: FLASH Size error flag
  *     @arg FLASH_FLAG_PGSERR: FLASH Programming sequence error flag
  *     @arg FLASH_FLAG_OPTWERR: FLASH Option modification error flag (Only in non-secure)
  *     @arg FLASH_FLAG_ECCC: FLASH one ECC error has been detected and corrected
  *     @arg FLASH_FLAG_ECCD: FLASH two ECC errors have been detected
  *     @arg FLASH_FLAG_ALL_ERRORS: FLASH All errors flags
  * @retval None
  */
#define __HAL_FLASH_CLEAR_FLAG_NS(__FLAG__)     do { if(((__FLAG__) & FLASH_FLAG_ECCR_ERRORS) != 0U) { SET_BIT(FLASH->ECCR, ((__FLAG__) & FLASH_FLAG_ECCR_ERRORS)); }\
                                                     if(((__FLAG__) & ~(FLASH_FLAG_ECCR_ERRORS)) != 0U) { WRITE_REG(FLASH->NSSR, ((__FLAG__) & ~(FLASH_FLAG_ECCR_ERRORS))); }\
                                                   } while(0)
#else
/**
  * @brief  Clear non-secure FLASH flags from the non-secure world.
  * @param  __FLAG__ specifies the FLASH flags to clear.
  *   This parameter can be any combination of the following values:
  *     @arg FLASH_FLAG_EOP: FLASH End of Operation flag
  *     @arg FLASH_FLAG_OPERR: FLASH Operation error flag
  *     @arg FLASH_FLAG_PROGERR: FLASH Programming error flag
  *     @arg FLASH_FLAG_WRPERR: FLASH Write protection error flag
  *     @arg FLASH_FLAG_PGAERR: FLASH Programming alignment error flag
  *     @arg FLASH_FLAG_SIZERR: FLASH Size error flag
  *     @arg FLASH_FLAG_PGSERR: FLASH Programming sequence error flag
  *     @arg FLASH_FLAG_OPTWERR: FLASH Option modification error flag (Only in non-secure)
  *     @arg FLASH_FLAG_ECCC: FLASH one ECC error has been detected and corrected
  *     @arg FLASH_FLAG_ECCD: FLASH two ECC errors have been detected
  *     @arg FLASH_FLAG_ALL_ERRORS: FLASH All errors flags
  * @retval None
  */
#define __HAL_FLASH_CLEAR_FLAG(__FLAG__)        do { if(((__FLAG__) & FLASH_FLAG_ECCR_ERRORS) != 0U) { SET_BIT(FLASH->ECCR, ((__FLAG__) & FLASH_FLAG_ECCR_ERRORS)); }\
                                                     if(((__FLAG__) & ~(FLASH_FLAG_ECCR_ERRORS)) != 0U) { WRITE_REG(FLASH->NSSR, ((__FLAG__) & ~(FLASH_FLAG_ECCR_ERRORS))); }\
                                                   } while(0)
#endif /* __ARM_FEATURE_CMSE */
/**
  * @}
  */

/* Include FLASH HAL Extended module */
#include "stm32l5xx_hal_flash_ex.h"
#include "stm32l5xx_hal_flash_ramfunc.h"

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

/* Private variables ---------------------------------------------------------*/
/** @addtogroup FLASH_Private_Variables FLASH Private Variables
 * @{
 */
extern FLASH_ProcessTypeDef pFlash;
/**
  * @}
  */

/* Private function ----------------------------------------------------------*/
/** @addtogroup FLASH_Private_Functions FLASH Private Functions
 * @{
 */
HAL_StatusTypeDef FLASH_WaitForLastOperation(uint32_t Timeout);
/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup FLASH_Private_Constants FLASH Private Constants
  * @{
  */
#define FLASH_BANK_SIZE          (FLASH_SIZE >> 1)

#define FLASH_PAGE_SIZE          0x00000800U
#define FLASH_PAGE_SIZE_128_BITS 0x00001000U

#define FLASH_PAGE_NB            (FLASH_SIZE / FLASH_PAGE_SIZE)
#define FLASH_PAGE_NB_PER_BANK   (FLASH_BANK_SIZE / FLASH_PAGE_SIZE)
#define FLASH_PAGE_NB_128_BITS   (FLASH_SIZE / FLASH_PAGE_SIZE_128_BITS)

#define FLASH_TIMEOUT_VALUE      1000u /* 1 s */

#define FLASH_NON_SECURE_MASK    0x80000000U
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup FLASH_Private_Macros FLASH Private Macros
 *  @{
 */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_FLASH_TYPEERASE(VALUE)          (((VALUE) == FLASH_TYPEERASE_PAGES)     || \
                                            ((VALUE) == FLASH_TYPEERASE_PAGES_NS)  || \
                                            ((VALUE) == FLASH_TYPEERASE_MASSERASE) || \
                                            ((VALUE) == FLASH_TYPEERASE_MASSERASE_NS))
#else
#define IS_FLASH_TYPEERASE(VALUE)          (((VALUE) == FLASH_TYPEERASE_PAGES) || \
                                            ((VALUE) == FLASH_TYPEERASE_MASSERASE))
#endif

#define IS_FLASH_BANK(BANK)                (((BANK) == FLASH_BANK_1)  || \
                                            ((BANK) == FLASH_BANK_2)  || \
                                            ((BANK) == FLASH_BANK_BOTH))

#define IS_FLASH_BANK_EXCLUSIVE(BANK)      (((BANK) == FLASH_BANK_1)  || \
                                            ((BANK) == FLASH_BANK_2))

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_FLASH_TYPEPROGRAM(VALUE)        (((VALUE) == FLASH_TYPEPROGRAM_DOUBLEWORD) || \
                                            ((VALUE) == FLASH_TYPEPROGRAM_DOUBLEWORD_NS))
#else
#define IS_FLASH_TYPEPROGRAM(VALUE)        ((VALUE) == FLASH_TYPEPROGRAM_DOUBLEWORD)
#endif

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_FLASH_MAIN_MEM_ADDRESS(ADDRESS) ((((ADDRESS) >= FLASH_BASE)    && ((ADDRESS) < (FLASH_BASE+FLASH_SIZE))) || \
                                            (((ADDRESS) >= FLASH_BASE_NS) && ((ADDRESS) < (FLASH_BASE_NS+FLASH_SIZE))))
#else
#define IS_FLASH_MAIN_MEM_ADDRESS(ADDRESS) (((ADDRESS) >= FLASH_BASE) && ((ADDRESS) < (FLASH_BASE+FLASH_SIZE)))
#endif

#define IS_FLASH_OTP_ADDRESS(ADDRESS)      (((ADDRESS) >= OTP_BASE) && ((ADDRESS) < (OTP_BASE+OTP_SIZE)))

#define IS_FLASH_PROGRAM_ADDRESS(ADDRESS)  ((IS_FLASH_MAIN_MEM_ADDRESS(ADDRESS)) || (IS_FLASH_OTP_ADDRESS(ADDRESS)))

#define IS_FLASH_PAGE(PAGE)                ((PAGE) < 128U)

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_OPTIONBYTE(VALUE)               (((VALUE) <= (OPTIONBYTE_WRP   | OPTIONBYTE_RDP       | OPTIONBYTE_USER | \
                                                         OPTIONBYTE_WMSEC | OPTIONBYTE_BOOT_LOCK | OPTIONBYTE_BOOTADDR)))
#else
#define IS_OPTIONBYTE(VALUE)               (((VALUE) <= (OPTIONBYTE_WRP   | OPTIONBYTE_RDP   | OPTIONBYTE_USER | \
                                                         OPTIONBYTE_BOOTADDR)))
#endif

#define IS_OB_WRPAREA(VALUE)               (((VALUE) == OB_WRPAREA_BANK1_AREAA) || ((VALUE) == OB_WRPAREA_BANK1_AREAB) || \
                                            ((VALUE) == OB_WRPAREA_BANK2_AREAA) || ((VALUE) == OB_WRPAREA_BANK2_AREAB))

#define IS_OB_RDP_LEVEL(LEVEL)             (((LEVEL) == OB_RDP_LEVEL_0)   ||\
                                            ((LEVEL) == OB_RDP_LEVEL_0_5) ||\
                                            ((LEVEL) == OB_RDP_LEVEL_1)   ||\
                                            ((LEVEL) == OB_RDP_LEVEL_2))

#define IS_OB_USER_TYPE(TYPE)              (((TYPE) <= (uint32_t)0x1FFFFU) && ((TYPE) != 0U))

#define IS_OB_USER_BOR_LEVEL(LEVEL)        (((LEVEL) == OB_BOR_LEVEL_0) || ((LEVEL) == OB_BOR_LEVEL_1) || \
                                            ((LEVEL) == OB_BOR_LEVEL_2) || ((LEVEL) == OB_BOR_LEVEL_3) || \
                                            ((LEVEL) == OB_BOR_LEVEL_4))

#define IS_OB_USER_STOP(VALUE)             (((VALUE) == OB_STOP_RST) || ((VALUE) == OB_STOP_NORST))

#define IS_OB_USER_STANDBY(VALUE)          (((VALUE) == OB_STANDBY_RST) || ((VALUE) == OB_STANDBY_NORST))

#define IS_OB_USER_SHUTDOWN(VALUE)         (((VALUE) == OB_SHUTDOWN_RST) || ((VALUE) == OB_SHUTDOWN_NORST))

#define IS_OB_USER_IWDG(VALUE)             (((VALUE) == OB_IWDG_HW) || ((VALUE) == OB_IWDG_SW))

#define IS_OB_USER_IWDG_STOP(VALUE)        (((VALUE) == OB_IWDG_STOP_FREEZE) || ((VALUE) == OB_IWDG_STOP_RUN))

#define IS_OB_USER_IWDG_STDBY(VALUE)       (((VALUE) == OB_IWDG_STDBY_FREEZE) || ((VALUE) == OB_IWDG_STDBY_RUN))

#define IS_OB_USER_WWDG(VALUE)             (((VALUE) == OB_WWDG_HW) || ((VALUE) == OB_WWDG_SW))

#define IS_OB_USER_SWAP_BANK(VALUE)        (((VALUE) == OB_SWAP_BANK_DISABLE) || ((VALUE) == OB_SWAP_BANK_ENABLE))

#define IS_OB_USER_DUALBANK(VALUE)         (((VALUE) == OB_DUALBANK_SINGLE) || ((VALUE) == OB_DUALBANK_DUAL))

#define IS_OB_USER_DBANK(VALUE)            (((VALUE) == OB_DBANK_128_BITS) || ((VALUE) == OB_DBANK_64_BITS))

#define IS_OB_USER_SRAM2_PARITY(VALUE)     (((VALUE) == OB_SRAM2_PARITY_ENABLE) || ((VALUE) == OB_SRAM2_PARITY_DISABLE))

#define IS_OB_USER_SRAM2_RST(VALUE)        (((VALUE) == OB_SRAM2_RST_ERASE) || ((VALUE) == OB_SRAM2_RST_NOT_ERASE))

#define IS_OB_USER_SWBOOT0(VALUE)          (((VALUE) == OB_BOOT0_FROM_OB) || ((VALUE) == OB_BOOT0_FROM_PIN))

#define IS_OB_USER_BOOT0(VALUE)            (((VALUE) == OB_nBOOT0_RESET) || ((VALUE) == OB_nBOOT0_SET))

#define IS_OB_USER_PA15_PUPEN(VALUE)       (((VALUE) == OB_PA15_PUP_DISABLE) || ((VALUE) == OB_PA15_PUP_ENABLE))

#define IS_OB_USER_TZEN(VALUE)             (((VALUE) == OB_TZEN_DISABLE) || ((VALUE) == OB_TZEN_ENABLE))

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_OB_BOOT_LOCK(VALUE)             (((VALUE) == OB_BOOT_LOCK_DISABLE) || ((VALUE) == OB_BOOT_LOCK_ENABLE))

#define IS_OB_WMSEC_CONFIG(CFG)            ((((CFG) & 0x1B3U) != 0U) && (((CFG) & 0x3U) != 0U) && (((CFG) & 0xFFFFFE4CU) == 0U))

#define IS_OB_WMSEC_AREA_EXCLUSIVE(WMSEC)  (((((WMSEC) & OB_WMSEC_AREA1) != 0U) && (((WMSEC) & OB_WMSEC_AREA2) == 0U)) || \
                                            ((((WMSEC) & OB_WMSEC_AREA2) != 0U) && (((WMSEC) & OB_WMSEC_AREA1) == 0U)))
#endif

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_OB_BOOTADDR_CONFIG(CFG)         (((CFG) == OB_BOOTADDR_NS0) || ((CFG) == OB_BOOTADDR_NS1) || \
                                            ((CFG) == OB_BOOTADDR_SEC0))
#else
#define IS_OB_BOOTADDR_CONFIG(CFG)         (((CFG) == OB_BOOTADDR_NS0) || ((CFG) == OB_BOOTADDR_NS1))
#endif

#define IS_FLASH_LATENCY(LATENCY)          (((LATENCY) == FLASH_LATENCY_0) || ((LATENCY) == FLASH_LATENCY_1) || \
                                            ((LATENCY) == FLASH_LATENCY_2) || ((LATENCY) == FLASH_LATENCY_3) || \
                                            ((LATENCY) == FLASH_LATENCY_4) || ((LATENCY) == FLASH_LATENCY_5) || \
                                            ((LATENCY) == FLASH_LATENCY_6) || ((LATENCY) == FLASH_LATENCY_7) || \
                                            ((LATENCY) == FLASH_LATENCY_8) || ((LATENCY) == FLASH_LATENCY_9) || \
                                            ((LATENCY) == FLASH_LATENCY_10) || ((LATENCY) == FLASH_LATENCY_11) || \
                                            ((LATENCY) == FLASH_LATENCY_12) || ((LATENCY) == FLASH_LATENCY_13) || \
                                            ((LATENCY) == FLASH_LATENCY_14) || ((LATENCY) == FLASH_LATENCY_15))

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_FLASH_SECURE_OPERATION()        ((pFlash.ProcedureOnGoing & FLASH_NON_SECURE_MASK) == 0U)
#else
#define IS_FLASH_SECURE_OPERATION()        (0U)
#endif /* __ARM_FEATURE_CMSE */
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

#endif /* STM32L5xx_HAL_FLASH_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
