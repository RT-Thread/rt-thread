/**
  ******************************************************************************
  * @file    stm32u5xx_hal_flash.h
  * @author  MCD Application Team
  * @brief   Header file of FLASH HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5xx_HAL_FLASH_H
#define STM32U5xx_HAL_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
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
                             (eg : 127 for 2MB dual bank) */
  uint32_t NbPages;     /*!< Number of pages to be erased. This parameter must be a value between 1 and
                             (max number of pages in the bank - value of initial page)*/
} FLASH_EraseInitTypeDef;

/**
  * @brief  FLASH Option Bytes Program structure definition
  */
typedef struct
{
  uint32_t OptionType;     /*!< Option byte to be configured.
                                This parameter can be a combination of the values of @ref FLASH_OB_Type */
  uint32_t WRPArea;        /*!< Write protection area to be programmed (used for OPTIONBYTE_WRP).
                                Only one WRP area could be programmed at the same time.
                                This parameter can be value of @ref FLASH_OB_WRP_Area */
  uint32_t WRPStartOffset; /*!< Write protection start offset (used for OPTIONBYTE_WRP).
                                This parameter must be a value between 0 and (max number of pages in the bank - 1) */
  uint32_t WRPEndOffset;   /*!< Write protection end offset (used for OPTIONBYTE_WRP).
                                This parameter must be a value between WRPStartOffset
                                and (max number of pages in the bank - 1) */
  FunctionalState WRPLock; /*!< Write protection lock (used for OPTIONBYTE_WRP).
                                This parameter can be set to ENABLE or DISABLE */
  uint32_t RDPLevel;       /*!< Set the read protection level (used for OPTIONBYTE_RDP).
                                This parameter can be a value of @ref FLASH_OB_Read_Protection */
  uint32_t USERType;       /*!< User option byte(s) to be configured (used for OPTIONBYTE_USER).
                                This parameter can be a combination of @ref FLASH_OB_USER_Type */
  uint32_t USERConfig;     /*!< Value of the user option byte (used for OPTIONBYTE_USER).
                                This parameter can be a combination of @ref FLASH_OB_USER_BOR_LEVEL,
                                @ref FLASH_OB_USER_nRST_STOP, @ref FLASH_OB_USER_nRST_STANDBY,
                                @ref FLASH_OB_USER_nRST_SHUTDOWN, @ref FLASH_OB_USER_SRAM134_RST,
                                @ref FLASH_OB_USER_IWDG_SW, @ref FLASH_OB_USER_IWDG_STOP,
                                @ref FLASH_OB_USER_IWDG_STANDBY, @ref FLASH_OB_USER_WWDG_SW,
                                @ref FLASH_OB_USER_SWAP_BANK, @ref FLASH_OB_USER_DUALBANK,
                                @ref FLASH_OB_USER_BKPRAM_RST, @ref FLASH_OB_USER_SRAM3_ECC,
                                @ref FLASH_OB_USER_SRAM2_ECC, @ref FLASH_OB_USER_SRAM2_RST,
                                @ref FLASH_OB_USER_nSWBOOT0, @ref FLASH_OB_USER_nBOOT0,
                                @ref FLASH_OB_USER_PA15_PUPEN, @ref FLASH_OB_USER_IO_VDD_HSLV,
                                @ref FLASH_OB_USER_IO_VDDIO2_HSLV, @ref FLASH_OB_USER_TZEN */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  uint32_t WMSecConfig;      /*!< Configuration of the Watermark-based Secure Area (used for OPTIONBYTE_WMSEC).
                                  This parameter must be a value of @ref FLASH_OB_WMSEC */
  uint32_t WMSecStartPage;   /*!< Start page of secure area (used for OPTIONBYTE_WMSEC).
                                  This parameter must be a value between 0 and (max number of pages in the bank - 1) */
  uint32_t WMSecEndPage;     /*!< End page of secure area (used for OPTIONBYTE_WMSEC). This parameter must be a value
                                  between WMSecStartPage and (max number of pages in the bank - 1) */
  uint32_t WMHDPEndPage;     /*!< End page of the secure hide protection (used for OPTIONBYTE_WMSEC).
                                  This parameter must be a value between WMSecStartPage and WMSecEndPage */
  uint32_t BootLock;         /*!< Configuration of the boot lock (used for OPTIONBYTE_BOOT_LOCK).
                                  This parameter must be a value of @ref FLASH_OB_BOOT_LOCK */
#endif /* __ARM_FEATURE_CMSE */
  uint32_t BootAddrConfig;   /*!< Configuration of the Boot address (used for OPTIONBYTE_BOOTADDR).
                                  This parameter must be a value of @ref FLASH_OB_BOOTADDR */
  uint32_t BootAddr;         /*!< Boot address (used for OPTIONBYTE_BOOTADDR).
                                  This parameter must be a value between 0x0 and 0xFFFFFF00 */
  uint32_t RDPKeyType;       /*!< Configuration of the RDP OEM keys (used for OPTIONBYTE_RDPKEY).
                                  This parameter can be a value of @ref FLASH_OB_RDP_Key_Type */
  uint32_t RDPKey1;          /*!< Value of the RDP OEM key 1 (used for OPTIONBYTE_RDPKEY) */
  uint32_t RDPKey2;          /*!< Value of the RDP OEM key 2 (used for OPTIONBYTE_RDPKEY) */
} FLASH_OBProgramInitTypeDef;

/**
  * @brief  FLASH handle Structure definition
  */
typedef struct
{
  HAL_LockTypeDef        Lock;              /* FLASH locking object */
  uint32_t               ErrorCode;         /* FLASH error code */
  uint32_t               ProcedureOnGoing;  /* Internal variable to indicate which procedure is ongoing
                                               or not in IT context */
  uint32_t               Address;           /* Internal variable to save address selected for program
                                               in IT context */
  uint32_t               Bank;              /* Internal variable to save current bank selected during erase
                                               in IT context */
  uint32_t               Page;              /* Internal variable to define the current page which is being erased
                                               in IT context */
  uint32_t               NbPagesToErase;    /* Internal variable to save the remaining pages to erase in IT context */
} FLASH_ProcessTypeDef;

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
#define FLASH_FLAG_EOP       FLASH_SECSR_EOP                      /*!< FLASH End of operation flag */
#define FLASH_FLAG_OPERR     FLASH_SECSR_OPERR                    /*!< FLASH Operation error flag */
#define FLASH_FLAG_PROGERR   FLASH_SECSR_PROGERR                  /*!< FLASH Programming error flag */
#define FLASH_FLAG_WRPERR    FLASH_SECSR_WRPERR                   /*!< FLASH Write protection error flag */
#define FLASH_FLAG_PGAERR    FLASH_SECSR_PGAERR                   /*!< FLASH Programming alignment error flag */
#define FLASH_FLAG_SIZERR    FLASH_SECSR_SIZERR                   /*!< FLASH Size error flag */
#define FLASH_FLAG_PGSERR    FLASH_SECSR_PGSERR                   /*!< FLASH Programming sequence error flag */
#define FLASH_FLAG_OPTWERR   FLASH_NSSR_OPTWERR                   /*!< FLASH Option modification error flag  */
#define FLASH_FLAG_BSY       FLASH_SECSR_BSY                      /*!< FLASH Busy flag */
#define FLASH_FLAG_WDW       FLASH_SECSR_WDW                      /*!< FLASH Wait Data to Write flag */
#define FLASH_FLAG_ECCC      FLASH_ECCR_ECCC                      /*!< FLASH ECC correction */
#define FLASH_FLAG_ECCD      FLASH_ECCR_ECCD                      /*!< FLASH ECC detection */

#define FLASH_FLAG_SR_ERRORS    (FLASH_FLAG_OPERR     | FLASH_FLAG_PROGERR | FLASH_FLAG_WRPERR | \
                                 FLASH_FLAG_PGAERR    | FLASH_FLAG_SIZERR  | FLASH_FLAG_PGSERR)
#define FLASH_FLAG_ECCR_ERRORS  (FLASH_FLAG_ECCC      | FLASH_FLAG_ECCD)
#define FLASH_FLAG_ALL_ERRORS   (FLASH_FLAG_SR_ERRORS | FLASH_FLAG_OPTWERR | FLASH_FLAG_ECCR_ERRORS)
#else
#define FLASH_FLAG_EOP       FLASH_NSSR_EOP                       /*!< FLASH End of operation flag */
#define FLASH_FLAG_OPERR     FLASH_NSSR_OPERR                     /*!< FLASH Operation error flag */
#define FLASH_FLAG_PROGERR   FLASH_NSSR_PROGERR                   /*!< FLASH Programming error flag */
#define FLASH_FLAG_WRPERR    FLASH_NSSR_WRPERR                    /*!< FLASH Write protection error flag */
#define FLASH_FLAG_PGAERR    FLASH_NSSR_PGAERR                    /*!< FLASH Programming alignment error flag */
#define FLASH_FLAG_SIZERR    FLASH_NSSR_SIZERR                    /*!< FLASH Size error flag  */
#define FLASH_FLAG_PGSERR    FLASH_NSSR_PGSERR                    /*!< FLASH Programming sequence error flag */
#define FLASH_FLAG_OPTWERR   FLASH_NSSR_OPTWERR                   /*!< FLASH Option modification error flag  */
#define FLASH_FLAG_BSY       FLASH_NSSR_BSY                       /*!< FLASH Busy flag */
#define FLASH_FLAG_WDW       FLASH_NSSR_WDW                       /*!< FLASH Wait Data to Write flag */
#define FLASH_FLAG_ECCC      FLASH_ECCR_ECCC                      /*!< FLASH ECC correction */
#define FLASH_FLAG_ECCD      FLASH_ECCR_ECCD                      /*!< FLASH ECC detection */

#define FLASH_FLAG_SR_ERRORS    (FLASH_FLAG_OPERR     | FLASH_FLAG_PROGERR | FLASH_FLAG_WRPERR  | \
                                 FLASH_FLAG_PGAERR    | FLASH_FLAG_SIZERR  | FLASH_FLAG_PGSERR  | \
                                 FLASH_FLAG_OPTWERR)
#define FLASH_FLAG_ECCR_ERRORS  (FLASH_FLAG_ECCC      | FLASH_FLAG_ECCD)
#define FLASH_FLAG_ALL_ERRORS   (FLASH_FLAG_SR_ERRORS | FLASH_FLAG_ECCR_ERRORS)
#endif /* __ARM_FEATURE_CMSE */
/**
  * @}
  */

/** @defgroup FLASH_Interrupt_definition FLASH Interrupts Definition
  * @brief FLASH Interrupt definition
  * @{
  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define FLASH_IT_EOP     FLASH_SECCR_EOPIE        /*!< End of FLASH Operation Interrupt source */
#define FLASH_IT_OPERR   FLASH_SECCR_ERRIE        /*!< Error Interrupt source */
#define FLASH_IT_ECCC    (FLASH_ECCR_ECCIE >> 24) /*!< ECC Correction Interrupt source */
#else
#define FLASH_IT_EOP     FLASH_NSCR_EOPIE         /*!< End of FLASH Operation Interrupt source */
#define FLASH_IT_OPERR   FLASH_NSCR_ERRIE         /*!< Error Interrupt source */
#define FLASH_IT_ECCC    (FLASH_ECCR_ECCIE >> 24) /*!< ECC Correction Interrupt source */
#endif /* __ARM_FEATURE_CMSE */
/**
  * @}
  */

/** @defgroup FLASH_Error FLASH Error
  * @{
  */
#define HAL_FLASH_ERROR_NONE      0x00000000U
#define HAL_FLASH_ERROR_OP        FLASH_FLAG_OPERR
#define HAL_FLASH_ERROR_PROG      FLASH_FLAG_PROGERR
#define HAL_FLASH_ERROR_WRP       FLASH_FLAG_WRPERR
#define HAL_FLASH_ERROR_PGA       FLASH_FLAG_PGAERR
#define HAL_FLASH_ERROR_SIZ       FLASH_FLAG_SIZERR
#define HAL_FLASH_ERROR_PGS       FLASH_FLAG_PGSERR
#define HAL_FLASH_ERROR_OPTW      FLASH_FLAG_OPTWERR
#define HAL_FLASH_ERROR_ECCC      FLASH_FLAG_ECCC
#define HAL_FLASH_ERROR_ECCD      FLASH_FLAG_ECCD
/**
  * @}
  */

/** @defgroup FLASH_Type_Erase FLASH Erase Type
  * @{
  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define FLASH_TYPEERASE_PAGES        FLASH_SECCR_PER                                 /*!< Secure pages erase 
                                                                                          activation */
#define FLASH_TYPEERASE_PAGES_NS     (FLASH_NSCR_PER   | FLASH_NON_SECURE_MASK)      /*!< Non-secure pages erase
                                                                                          activation */
#define FLASH_TYPEERASE_MASSERASE    (FLASH_SECCR_MER1 | FLASH_SECCR_MER2)           /*!< Secure flash mass erase
                                                                                          activation */
#define FLASH_TYPEERASE_MASSERASE_NS (FLASH_NSCR_MER1  | FLASH_NSCR_MER2 | FLASH_NON_SECURE_MASK) /*!< Non-secure flash
                                                                                          mass erase activation */
#else
#define FLASH_TYPEERASE_PAGES        FLASH_NSCR_PER                                  /*!< Pages erase activation */
#define FLASH_TYPEERASE_MASSERASE    (FLASH_NSCR_MER1 | FLASH_NSCR_MER2)             /*!< Flash mass erase activation */
#endif /* __ARM_FEATURE_CMSE */
/**
  * @}
  */

/** @defgroup FLASH_Banks FLASH Banks
  * @{
  */
#define FLASH_BANK_1              0x00000001U                       /*!< Bank 1   */
#define FLASH_BANK_2              0x00000002U                       /*!< Bank 2   */
#define FLASH_BANK_BOTH           (FLASH_BANK_1 | FLASH_BANK_2)     /*!< Bank1 and Bank2  */
/**
  * @}
  */

/** @defgroup FLASH_Type_Program FLASH Program Type
  * @{
  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define FLASH_TYPEPROGRAM_QUADWORD    FLASH_SECCR_PG                          /*!< Program a quad-word (128-bit)
                                                                                   at a specified secure address */
#define FLASH_TYPEPROGRAM_QUADWORD_NS (FLASH_NSCR_PG | FLASH_NON_SECURE_MASK) /*!< Program a quad-word (128-bit)
                                                                                   at a specified non-secure address */
#define FLASH_TYPEPROGRAM_BURST       (FLASH_SECCR_PG | FLASH_SECCR_BWR)      /*!< Program a burst (8xquad-word)
                                                                                   at a specified secure address */
#define FLASH_TYPEPROGRAM_BURST_NS    (FLASH_NSCR_PG | FLASH_NSCR_BWR | FLASH_NON_SECURE_MASK) /*!< Program a burst
(8xquad-word) at a specified non-secure address */
#else
#define FLASH_TYPEPROGRAM_QUADWORD   FLASH_NSCR_PG                    /*!<Program a quad-word (128-bit)
                                                                          at a specified address */
#define FLASH_TYPEPROGRAM_BURST      (FLASH_NSCR_PG | FLASH_NSCR_BWR) /*!<Program a burst (8xquad-word)
                                                                          at a specified address */
#endif /* __ARM_FEATURE_CMSE */
/**
  * @}
  */

/** @defgroup FLASH_OB_Type FLASH Option Bytes Type
  * @{
  */
#define OPTIONBYTE_WRP            0x00000001U   /*!< WRP option byte configuration */
#define OPTIONBYTE_RDP            0x00000002U   /*!< RDP option byte configuration */
#define OPTIONBYTE_USER           0x00000004U   /*!< USER option byte configuration */
#define OPTIONBYTE_BOOTADDR       0x00000008U   /*!< Boot address option byte configuration */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define OPTIONBYTE_WMSEC          0x00000010U   /*!< Watermark-based secure area option byte configuration */
#define OPTIONBYTE_BOOT_LOCK      0x00000020U   /*!< Boot lock option byte configuration */
#endif /* __ARM_FEATURE_CMSE */
#define OPTIONBYTE_RDPKEY         0x00000040U   /*!< RDP Key option byte configuration */
/**
  * @}
  */

/** @defgroup FLASH_OB_WRP_Area FLASH WRP Area
  * @{
  */
#define OB_WRPAREA_BANK1_AREAA    0x01U  /*!< Flash Bank 1 Area A */
#define OB_WRPAREA_BANK1_AREAB    0x02U  /*!< Flash Bank 1 Area B */
#define OB_WRPAREA_BANK2_AREAA    0x04U  /*!< Flash Bank 2 Area A */
#define OB_WRPAREA_BANK2_AREAB    0x08U  /*!< Flash Bank 2 Area B */
/**
  * @}
  */

/** @defgroup FLASH_OB_Read_Protection FLASH Option Bytes Read Protection
  * @{
  */
#define OB_RDP_LEVEL_0            0xAAU
#define OB_RDP_LEVEL_0_5          0x55U
#define OB_RDP_LEVEL_1            0xBBU
#define OB_RDP_LEVEL_2            0xCCU
/**
  * @}
  */

/** @defgroup FLASH_OB_RDP_Key_Type FLASH Option Bytes Read Protection Key Type
  * @{
  */
#define OB_RDP_KEY_OEM1           0x01U  /*!< OEM1 key */
#define OB_RDP_KEY_OEM2           0x02U  /*!< OEM2 key */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_Type FLASH Option Bytes User Type
  * @{
  */
#define OB_USER_BOR_LEV           0x00000001U     /*!< BOR reset Level */
#define OB_USER_NRST_STOP         0x00000002U     /*!< Reset generated when entering the stop mode */
#define OB_USER_NRST_STDBY        0x00000004U     /*!< Reset generated when entering the standby mode */
#define OB_USER_NRST_SHDW         0x00000008U     /*!< Reset generated when entering the shutdown mode */
#define OB_USER_SRAM134_RST       0x00000010U     /*!< SRAM1, SRAM3 and SRAM4 erase upon system reset */
#define OB_USER_IWDG_SW           0x00000020U     /*!< Independent watchdog selection */
#define OB_USER_IWDG_STOP         0x00000040U     /*!< Independent watchdog counter freeze in stop mode */
#define OB_USER_IWDG_STDBY        0x00000080U     /*!< Independent watchdog counter freeze in standby mode */
#define OB_USER_WWDG_SW           0x00000100U     /*!< Window watchdog selection */
#define OB_USER_SWAP_BANK         0x00000200U     /*!< Swap banks */
#define OB_USER_DUALBANK          0x00000400U     /*!< Dual-Bank on 1MB/512kB Flash memory devices */
#define OB_USER_BKPRAM_ECC        0x00000800U     /*!< Backup RAM ECC detection and correction enable */
#define OB_USER_SRAM3_ECC         0x00001000U     /*!< SRAM3 ECC detection and correction enable */
#define OB_USER_SRAM2_ECC         0x00002000U     /*!< SRAM2 ECC detection and correction enable */
#define OB_USER_SRAM2_RST         0x00004000U     /*!< SRAM2 Erase when system reset */
#define OB_USER_NSWBOOT0          0x00008000U     /*!< Software BOOT0 */
#define OB_USER_NBOOT0            0x00010000U     /*!< nBOOT0 option bit */
#define OB_USER_PA15_PUPEN        0x00020000U     /*!< PA15 pull-up enable option bit */
#define OB_USER_IO_VDD_HSLV       0x00040000U     /*!< High speed IO at low voltage configuration bit */
#define OB_USER_IO_VDDIO2_HSLV    0x00080000U     /*!< High speed IO at low VDDIO2 voltage configuration bit */
#define OB_USER_TZEN              0x00100000U     /*!< Global TrustZone security enable */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_BOR_LEVEL FLASH Option Bytes User BOR Level
  * @{
  */
#define OB_BOR_LEVEL_0            0x00000000U                                   /*!< Reset level threshold
                                                                                     is around 1.7V */
#define OB_BOR_LEVEL_1            FLASH_OPTR_BOR_LEV_0                          /*!< Reset level threshold
                                                                                     is around 2.0V */
#define OB_BOR_LEVEL_2            FLASH_OPTR_BOR_LEV_1                          /*!< Reset level threshold
                                                                                     is around 2.2V */
#define OB_BOR_LEVEL_3            (FLASH_OPTR_BOR_LEV_1 | FLASH_OPTR_BOR_LEV_0) /*!< Reset level threshold
                                                                                     is around 2.5V */
#define OB_BOR_LEVEL_4            FLASH_OPTR_BOR_LEV_2                          /*!< Reset level threshold
                                                                                     is around 2.8V */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_nRST_STOP FLASH Option Bytes User Reset On Stop
  * @{
  */
#define OB_STOP_RST               0x00000000U              /*!< Reset generated when entering the stop mode */
#define OB_STOP_NORST             FLASH_OPTR_nRST_STOP     /*!< No reset generated when entering the stop mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_nRST_STANDBY FLASH Option Bytes User Reset On Standby
  * @{
  */
#define OB_STANDBY_RST            0x00000000U              /*!< Reset generated when entering the standby mode */
#define OB_STANDBY_NORST          FLASH_OPTR_nRST_STDBY    /*!< No reset generated when entering the standby mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_nRST_SHUTDOWN FLASH Option Bytes User Reset On Shutdown
  * @{
  */
#define OB_SHUTDOWN_RST           0x00000000U              /*!< Reset generated when entering the shutdown mode */
#define OB_SHUTDOWN_NORST         FLASH_OPTR_nRST_SHDW     /*!< No reset generated when entering the shutdown mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_SRAM134_RST FLASH Option Bytes User SRAM134 Erase On Reset Type
  * @{
  */
#define OB_SRAM134_RST_ERASE      0x00000000U            /*!< SRAM1, SRAM3 and SRAM4 erased
                                                              when a system reset occurs */
#define OB_SRAM134_RST_NOT_ERASE  FLASH_OPTR_SRAM134_RST /*!< SRAM1, SRAM3 and SRAM4 are not erased
                                                              when a system reset occurs */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IWDG_SW FLASH Option Bytes User IWDG Type
  * @{
  */
#define OB_IWDG_HW                0x00000000U              /*!< Hardware independent watchdog */
#define OB_IWDG_SW                FLASH_OPTR_IWDG_SW       /*!< Software independent watchdog */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IWDG_STOP FLASH Option Bytes User IWDG Mode On Stop
  * @{
  */
#define OB_IWDG_STOP_FREEZE       0x00000000U            /*!< Independent watchdog counter is frozen in Stop mode */
#define OB_IWDG_STOP_RUN          FLASH_OPTR_IWDG_STOP   /*!< Independent watchdog counter is running in Stop mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IWDG_STANDBY FLASH Option Bytes User IWDG Mode On Standby
  * @{
  */
#define OB_IWDG_STDBY_FREEZE      0x00000000U            /*!< Independent watchdog counter is frozen in Standby mode */
#define OB_IWDG_STDBY_RUN         FLASH_OPTR_IWDG_STDBY  /*!< Independent watchdog counter is running in Standby mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_WWDG_SW FLASH Option Bytes User WWDG Type
  * @{
  */
#define OB_WWDG_HW                0x00000000U            /*!< Hardware window watchdog */
#define OB_WWDG_SW                FLASH_OPTR_WWDG_SW     /*!< Software window watchdog */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_SWAP_BANK FLASH Option Bytes User Swap banks
  * @{
  */
#define OB_SWAP_BANK_DISABLE      0x00000000U          /*!< Bank 1 is located at address offset 0x0,
                                                            Bank 2 is located at 0x100000 */
#define OB_SWAP_BANK_ENABLE       FLASH_OPTR_SWAP_BANK /*!< Bank 1 is located at address offset 0x100000,
                                                            Bank 2 is located at 0x0 */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_DUALBANK FLASH Option Bytes User Dual-bank Type
  * @{
  */
#define OB_DUALBANK_SINGLE        0x00000000U         /*!< 1MB/512KB Single-bank Flash */
#define OB_DUALBANK_DUAL          FLASH_OPTR_DUALBANK /*!< 1MB/512KB Dual-bank Flash */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_BKPRAM_RST FLASH Option Bytes User BKPRAM ECC check
  * @{
  */
#define OB_BKPRAM_ECC_ENABLE      0x00000000U           /*!< BKPRAM ECC check enable */
#define OB_BKPRAM_ECC_DISABLE     FLASH_OPTR_BKPRAM_ECC /*!< BKPRAM ECC check disable */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_SRAM3_ECC FLASH Option Bytes User SRAM3 ECC check
  * @{
  */
#define OB_SRAM3_ECC_ENABLE       0x00000000U          /*!< SRAM3 ECC check enable */
#define OB_SRAM3_ECC_DISABLE      FLASH_OPTR_SRAM3_ECC /*!< SRAM3 ECC check disable */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_SRAM2_ECC FLASH Option Bytes User SRAM2 ECC check
  * @{
  */
#define OB_SRAM2_ECC_ENABLE    0x00000000U              /*!< SRAM2 ECC check enable */
#define OB_SRAM2_ECC_DISABLE   FLASH_OPTR_SRAM2_ECC     /*!< SRAM2 ECC check disable */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_SRAM2_RST FLASH Option Bytes User SRAM2 Erase On Reset Type
  * @{
  */
#define OB_SRAM2_RST_ERASE        0x00000000U            /*!< SRAM2 erased when a system reset occurs */
#define OB_SRAM2_RST_NOT_ERASE    FLASH_OPTR_SRAM2_RST   /*!< SRAM2 is not erased when a system reset occurs */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_nSWBOOT0 FLASH Option Bytes User Software BOOT0
  * @{
  */
#define OB_BOOT0_FROM_OB          0x00000000U              /*!< BOOT0 taken from the option bit nBOOT0 */
#define OB_BOOT0_FROM_PIN         FLASH_OPTR_nSWBOOT0      /*!< BOOT0 taken from BOOT0 pin */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_nBOOT0 FLASH Option Bytes User nBOOT0 option bit
  * @{
  */
#define OB_NBOOT0_RESET           0x00000000U              /*!< nBOOT0 = 0 */
#define OB_NBOOT0_SET             FLASH_OPTR_nBOOT0        /*!< nBOOT0 = 1 */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_PA15_PUPEN FLASH Option Bytes User PA15 pull-up enable option bit
  * @{
  */
#define OB_PA15_PUP_DISABLE       0x00000000U           /*!< USB power delivery dead-battery
                                                             enabled / TDI pull-up deactivated */
#define OB_PA15_PUP_ENABLE        FLASH_OPTR_PA15_PUPEN /*!< USB power delivery dead-battery
                                                             disabled / TDI pull-up activated */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IO_VDD_HSLV FLASH Option Bytes User High speed IO at low voltage configuration bit
  * @{
  */
#define OB_IO_VDD_HSLV_DISABLE    0x00000000U            /*!< High-speed IO at low VDD voltage feature disabled
                                                              (VDD can exceed 2.5 V) */
#define OB_IO_VDD_HSLV_ENABLE     FLASH_OPTR_IO_VDD_HSLV /*!< High-speed IO at low VDD voltage feature enabled
                                                              (VDD remains below 2.5 V) */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IO_VDDIO2_HSLV FLASH Option Bytes User High speed IO at low VDDIO2 voltage configuration bit
  * @{
  */
#define OB_IO_VDDIO2_HSLV_DISABLE 0x00000000U               /*!< High-speed IO at low VDDIO2 voltage feature disabled
                                                                 (VDDIO2 can exceed 2.5 V) */
#define OB_IO_VDDIO2_HSLV_ENABLE  FLASH_OPTR_IO_VDDIO2_HSLV /*!< High-speed IO at low VDDIO2 voltage feature enabled
                                                                 (VDDIO2 remains below 2.5 V) */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_TZEN FLASH Option Bytes User Global TrustZone
  * @{
  */
#define OB_TZEN_DISABLE   0x00000000U     /*!< Global TrustZone security disabled */
#define OB_TZEN_ENABLE    FLASH_OPTR_TZEN /*!< Global TrustZone security enabled */
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
#endif /* __ARM_FEATURE_CMSE */

/** @defgroup FLASH_OB_BOOTADDR FLASH Option Bytes Boot address
  * @{
  */
#define OB_BOOTADDR_NS0      0x00000001U   /*!< Non-secure boot address 0 */
#define OB_BOOTADDR_NS1      0x00000002U   /*!< Non-secure boot address 1 */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define OB_BOOTADDR_SEC0     0x00000004U   /*!< Secure boot address 0 */
#endif /* __ARM_FEATURE_CMSE */
/**
  * @}
  */

/** @defgroup FLASH_Latency FLASH Latency
  * @{
  */
#define FLASH_LATENCY_0           FLASH_ACR_LATENCY_0WS    /*!< FLASH Zero wait state */
#define FLASH_LATENCY_1           FLASH_ACR_LATENCY_1WS    /*!< FLASH One wait state */
#define FLASH_LATENCY_2           FLASH_ACR_LATENCY_2WS    /*!< FLASH Two wait states */
#define FLASH_LATENCY_3           FLASH_ACR_LATENCY_3WS    /*!< FLASH Three wait states */
#define FLASH_LATENCY_4           FLASH_ACR_LATENCY_4WS    /*!< FLASH Four wait states */
#define FLASH_LATENCY_5           FLASH_ACR_LATENCY_5WS    /*!< FLASH Five wait state */
#define FLASH_LATENCY_6           FLASH_ACR_LATENCY_6WS    /*!< FLASH Six wait state */
#define FLASH_LATENCY_7           FLASH_ACR_LATENCY_7WS    /*!< FLASH Seven wait states */
#define FLASH_LATENCY_8           FLASH_ACR_LATENCY_8WS    /*!< FLASH Eight wait states */
#define FLASH_LATENCY_9           FLASH_ACR_LATENCY_9WS    /*!< FLASH Nine wait states */
#define FLASH_LATENCY_10          FLASH_ACR_LATENCY_10WS   /*!< FLASH Ten wait state */
#define FLASH_LATENCY_11          FLASH_ACR_LATENCY_11WS   /*!< FLASH Eleven wait state */
#define FLASH_LATENCY_12          FLASH_ACR_LATENCY_12WS   /*!< FLASH Twelve wait states */
#define FLASH_LATENCY_13          FLASH_ACR_LATENCY_13WS   /*!< FLASH Thirteen wait states */
#define FLASH_LATENCY_14          FLASH_ACR_LATENCY_14WS   /*!< FLASH Fourteen wait states */
#define FLASH_LATENCY_15          FLASH_ACR_LATENCY_15WS   /*!< FLASH Fifteen wait states */
/**
  * @}
  */

/** @defgroup FLASH_Keys FLASH Keys
  * @{
  */
#define FLASH_KEY1                0x45670123U /*!< Flash key1 */
#define FLASH_KEY2                0xCDEF89ABU /*!< Flash key2: used with FLASH_KEY1
                                                   to unlock the FLASH registers access */

#define FLASH_PDKEY1_1            0x04152637U /*!< Flash Bank 1 power down key1 */
#define FLASH_PDKEY1_2            0xFAFBFCFDU /*!< Flash Bank 1 power down key2: used with FLASH_PDKEY1_1
                                                   to unlock the PDREQ1 bit in FLASH_ACR */

#define FLASH_PDKEY2_1            0x40516273U /*!< Flash Bank 2 power down key1 */
#define FLASH_PDKEY2_2            0xAFBFCFDFU /*!< Flash Bank 2 power down key2: used with FLASH_PDKEY2_1
                                                   to unlock the PDREQ2 bit in FLASH_ACR */

#define FLASH_OPTKEY1             0x08192A3BU /*!< Flash option byte key1 */
#define FLASH_OPTKEY2             0x4C5D6E7FU /*!< Flash option byte key2: used with FLASH_OPTKEY1
                                                   to allow option bytes operations */
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
  * @param  __LATENCY__ FLASH Latency
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
#define __HAL_FLASH_SET_LATENCY(__LATENCY__)    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (__LATENCY__))

/**
  * @brief  Get the FLASH Latency.
  * @retval FLASH Latency
  *         This return value can be one of the following values :
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
  * @brief  Enable the FLASH power down during Low-Power sleep mode
  * @retval none
  */
#define __HAL_FLASH_SLEEP_POWERDOWN_ENABLE()    SET_BIT(FLASH->ACR, FLASH_ACR_SLEEP_PD)

/**
  * @brief  Disable the FLASH power down during Low-Power sleep mode
  * @retval none
  */
#define __HAL_FLASH_SLEEP_POWERDOWN_DISABLE()   CLEAR_BIT(FLASH->ACR, FLASH_ACR_SLEEP_PD)

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
  *         This parameter can be any combination of the following values:
  *     @arg FLASH_IT_EOP: End of FLASH Operation Interrupt
  *     @arg FLASH_IT_OPERR: Error Interrupt
  *     @arg FLASH_IT_ECCC: ECC Correction Interrupt
  * @retval none
  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/* Enable secure FLASH interrupts from the secure world */
#define __HAL_FLASH_ENABLE_IT(__INTERRUPT__)    do { if(((__INTERRUPT__) & FLASH_IT_ECCC) != 0U) \
                                                      { SET_BIT(FLASH->ECCR, FLASH_ECCR_ECCIE); } \
                                                     if(((__INTERRUPT__) & (~FLASH_IT_ECCC)) != 0U) \
                                                      { SET_BIT(FLASH->SECCR, ((__INTERRUPT__) & (~FLASH_IT_ECCC))); }\
                                                   } while(0)
/* Enable non-secure FLASH interrupts from the secure world */
#define __HAL_FLASH_ENABLE_IT_NS(__INTERRUPT__) do { if(((__INTERRUPT__) & FLASH_IT_ECCC) != 0U) \
                                                      { SET_BIT(FLASH->ECCR, FLASH_ECCR_ECCIE); } \
                                                     if(((__INTERRUPT__) & (~FLASH_IT_ECCC)) != 0U) \
                                                      { SET_BIT(FLASH->NSCR, ((__INTERRUPT__) & (~FLASH_IT_ECCC))); }\
                                                   } while(0)
#else
/* Enable non-secure FLASH interrupts from the non-secure world */
#define __HAL_FLASH_ENABLE_IT(__INTERRUPT__)    do { if(((__INTERRUPT__) & FLASH_IT_ECCC) != 0U) \
                                                      { SET_BIT(FLASH->ECCR, FLASH_ECCR_ECCIE); } \
                                                     if(((__INTERRUPT__) & (~FLASH_IT_ECCC)) != 0U) \
                                                      { SET_BIT(FLASH->NSCR, ((__INTERRUPT__) & (~FLASH_IT_ECCC))); }\
                                                   } while(0)
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Disable the specified FLASH interrupt.
  * @param  __INTERRUPT__ FLASH interrupt
  *         This parameter can be any combination of the following values:
  *     @arg FLASH_IT_EOP: End of FLASH Operation Interrupt
  *     @arg FLASH_IT_OPERR: Error Interrupt
  *     @arg FLASH_IT_ECCC: ECC Correction Interrupt
  * @retval none
  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/* Disable secure FLASH interrupts from the secure world */
#define __HAL_FLASH_DISABLE_IT(__INTERRUPT__)   do { if(((__INTERRUPT__) & FLASH_IT_ECCC) != 0U) \
                                                      { CLEAR_BIT(FLASH->ECCR, FLASH_ECCR_ECCIE); } \
                                                     if(((__INTERRUPT__) & (~FLASH_IT_ECCC)) != 0U) \
                                                      { CLEAR_BIT(FLASH->SECCR, ((__INTERRUPT__) & (~FLASH_IT_ECCC)));}\
                                                   } while(0)
/* Disable non-secure FLASH interrupts from the secure world */
#define __HAL_FLASH_DISABLE_IT_NS(__INTERRUPT__) do { if(((__INTERRUPT__) & FLASH_IT_ECCC) != 0U) \
                                                       { CLEAR_BIT(FLASH->ECCR, FLASH_ECCR_ECCIE); } \
                                                      if(((__INTERRUPT__) & (~FLASH_IT_ECCC)) != 0U) \
                                                       { CLEAR_BIT(FLASH->NSCR, ((__INTERRUPT__) & \
                                                                                 (~FLASH_IT_ECCC))); }\
                                                    } while(0)
#else
/* Disable non-secure FLASH interrupts from the non-secure world */
#define __HAL_FLASH_DISABLE_IT(__INTERRUPT__)   do { if(((__INTERRUPT__) & FLASH_IT_ECCC) != 0U) \
                                                     { CLEAR_BIT(FLASH->ECCR, FLASH_ECCR_ECCIE); }\
                                                     if(((__INTERRUPT__) & (~FLASH_IT_ECCC)) != 0U) \
                                                     { CLEAR_BIT(FLASH->NSCR, ((__INTERRUPT__) & (~FLASH_IT_ECCC))); }\
                                                   } while(0)
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Check whether the specified FLASH flag is set or not.
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
  *     @arg FLASH_FLAG_WDW: FLASH Wait Data to Write flag
  *     @arg FLASH_FLAG_ECCC: FLASH one ECC error has been detected and corrected
  *     @arg FLASH_FLAG_ECCD: FLASH two ECC errors have been detected
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/* Get secure FLASH flags from the secure world */
#define __HAL_FLASH_GET_FLAG(__FLAG__)          ((((__FLAG__) & (FLASH_FLAG_ECCC | FLASH_FLAG_ECCD)) != 0U) ? \
                                                 (READ_BIT(FLASH->ECCR, (__FLAG__)) == (__FLAG__))  : \
                                                 ((((__FLAG__) & (FLASH_FLAG_OPTWERR)) != 0U) ? \
                                                  (READ_BIT(FLASH->NSSR, (__FLAG__)) == (__FLAG__)) : \
                                                  (READ_BIT(FLASH->SECSR, (__FLAG__)) == (__FLAG__))))
/* Get non-secure FLASH flags from the secure world */
#define __HAL_FLASH_GET_FLAG_NS(__FLAG__)       ((((__FLAG__) & (FLASH_FLAG_ECCC | FLASH_FLAG_ECCD)) != 0U) ? \
                                                 (READ_BIT(FLASH->ECCR, (__FLAG__)) == (__FLAG__))  : \
                                                 (READ_BIT(FLASH->NSSR, (__FLAG__)) == (__FLAG__)))
#else
/* Get non-secure FLASH flags from the non-secure world */
#define __HAL_FLASH_GET_FLAG(__FLAG__)          ((((__FLAG__) & (FLASH_FLAG_ECCC | FLASH_FLAG_ECCD)) != 0U) ? \
                                                 (READ_BIT(FLASH->ECCR, (__FLAG__)) == (__FLAG__))  : \
                                                 (READ_BIT(FLASH->NSSR, (__FLAG__)) == (__FLAG__)))
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Clear the FLASH's pending flags.
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
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/* Clear secure FLASH flags from the secure world */
#define __HAL_FLASH_CLEAR_FLAG(__FLAG__)        do { if(((__FLAG__) & FLASH_FLAG_ECCR_ERRORS) != 0U) \
                                                      { SET_BIT(FLASH->ECCR, ((__FLAG__) & FLASH_FLAG_ECCR_ERRORS)); }\
                                                     if(((__FLAG__) & FLASH_FLAG_OPTWERR) != 0U) \
                                                      { SET_BIT(FLASH->NSSR, ((__FLAG__) & (FLASH_FLAG_OPTWERR))); }\
                                                     if(((__FLAG__) & ~(FLASH_FLAG_ECCR_ERRORS | \
                                                        FLASH_FLAG_OPTWERR)) != 0U) \
                                                     { WRITE_REG(FLASH->SECSR, ((__FLAG__) & \
                                                     ~(FLASH_FLAG_ECCR_ERRORS | FLASH_FLAG_OPTWERR))); }\
                                                   } while(0)
/* Clear non-secure FLASH flags from the secure world */
#define __HAL_FLASH_CLEAR_FLAG_NS(__FLAG__)     do { if(((__FLAG__) & FLASH_FLAG_ECCR_ERRORS) != 0U) \
                                                      { SET_BIT(FLASH->ECCR, ((__FLAG__) & FLASH_FLAG_ECCR_ERRORS)); }\
                                                     if(((__FLAG__) & ~(FLASH_FLAG_ECCR_ERRORS)) != 0U) \
                                                       { WRITE_REG(FLASH->NSSR, ((__FLAG__) & \
                                                                                ~(FLASH_FLAG_ECCR_ERRORS))); }\
                                                   } while(0)
#else
/* Clear non-secure FLASH flags from the non-secure world */
#define __HAL_FLASH_CLEAR_FLAG(__FLAG__)        do { if(((__FLAG__) & FLASH_FLAG_ECCR_ERRORS) != 0U) \
                                                    { SET_BIT(FLASH->ECCR, ((__FLAG__) & FLASH_FLAG_ECCR_ERRORS)); }\
                                                     if(((__FLAG__) & ~(FLASH_FLAG_ECCR_ERRORS)) != 0U) \
                                                       { WRITE_REG(FLASH->NSSR, ((__FLAG__) & \
                                                                                ~(FLASH_FLAG_ECCR_ERRORS))); }\
                                                   } while(0)
#endif /* __ARM_FEATURE_CMSE */
/**
  * @}
  */

/* Include FLASH HAL Extended module */
#include "stm32u5xx_hal_flash_ex.h"


/* Exported functions --------------------------------------------------------*/
/** @addtogroup FLASH_Exported_Functions
  * @{
  */

/* Program operation functions  ***********************************************/
/** @addtogroup FLASH_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef  HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint32_t DataAddress);
HAL_StatusTypeDef  HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint32_t DataAddress);
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

/* Private constants --------------------------------------------------------*/
/** @defgroup FLASH_Private_Constants FLASH Private Constants
  * @{
  */

#define FLASH_TIMEOUT_VALUE             1000U   /* 1 s */

#define FLASH_NON_SECURE_MASK           0x80000000U

#define FLASH_NB_WORDS_IN_BURST         32

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
#endif /* __ARM_FEATURE_CMSE */

#define IS_FLASH_BANK(BANK)                (((BANK) == FLASH_BANK_1)  || \
                                            ((BANK) == FLASH_BANK_2)  || \
                                            ((BANK) == FLASH_BANK_BOTH))

#define IS_FLASH_BANK_EXCLUSIVE(BANK)      (((BANK) == FLASH_BANK_1)  || \
                                            ((BANK) == FLASH_BANK_2))

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_FLASH_TYPEPROGRAM(VALUE)        (((VALUE) == FLASH_TYPEPROGRAM_QUADWORD)    || \
                                            ((VALUE) == FLASH_TYPEPROGRAM_QUADWORD_NS) || \
                                            ((VALUE) == FLASH_TYPEPROGRAM_BURST)       || \
                                            ((VALUE) == FLASH_TYPEPROGRAM_BURST_NS))
#else
#define IS_FLASH_TYPEPROGRAM(VALUE)        (((VALUE) == FLASH_TYPEPROGRAM_QUADWORD) || \
                                            ((VALUE) == FLASH_TYPEPROGRAM_BURST))
#endif /* __ARM_FEATURE_CMSE */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_FLASH_MAIN_MEM_ADDRESS(ADDRESS) ((((ADDRESS) >= FLASH_BASE)    && ((ADDRESS) < (FLASH_BASE+FLASH_SIZE))) || \
                                            (((ADDRESS) >= FLASH_BASE_NS) && ((ADDRESS) < (FLASH_BASE_NS+FLASH_SIZE))))
#else
#define IS_FLASH_MAIN_MEM_ADDRESS(ADDRESS) (((ADDRESS) >= FLASH_BASE)     && ((ADDRESS) < (FLASH_BASE+FLASH_SIZE)))
#endif /* __ARM_FEATURE_CMSE */

#define IS_FLASH_OTP_ADDRESS(ADDRESS)      (((ADDRESS) >= FLASH_OTP_BASE)\
                                            && ((ADDRESS) < (FLASH_OTP_BASE + FLASH_OTP_SIZE)))

#define IS_FLASH_PROGRAM_ADDRESS(ADDRESS)  ((IS_FLASH_MAIN_MEM_ADDRESS(ADDRESS)) || (IS_FLASH_OTP_ADDRESS(ADDRESS)))

#define IS_FLASH_PAGE(PAGE)                ((PAGE) < FLASH_PAGE_NB)

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_OPTIONBYTE(VALUE)            (((VALUE) <= (OPTIONBYTE_WRP   | OPTIONBYTE_RDP       | OPTIONBYTE_USER     | \
                                                      OPTIONBYTE_WMSEC | OPTIONBYTE_BOOT_LOCK | OPTIONBYTE_BOOTADDR | \
                                                      OPTIONBYTE_RDPKEY)))
#else
#define IS_OPTIONBYTE(VALUE)               (((VALUE) <= (OPTIONBYTE_WRP   | OPTIONBYTE_RDP   | OPTIONBYTE_USER | \
                                                         OPTIONBYTE_BOOTADDR | OPTIONBYTE_RDPKEY)))
#endif /* __ARM_FEATURE_CMSE */

#define IS_OB_WRPAREA(VALUE)           (((VALUE) == OB_WRPAREA_BANK1_AREAA) || ((VALUE) == OB_WRPAREA_BANK1_AREAB) || \
                                        ((VALUE) == OB_WRPAREA_BANK2_AREAA) || ((VALUE) == OB_WRPAREA_BANK2_AREAB))

#define IS_OB_RDP_LEVEL(LEVEL)             (((LEVEL) == OB_RDP_LEVEL_0)   ||\
                                            ((LEVEL) == OB_RDP_LEVEL_0_5) ||\
                                            ((LEVEL) == OB_RDP_LEVEL_1)   ||\
                                            ((LEVEL) == OB_RDP_LEVEL_2))

#define IS_OB_USER_TYPE(TYPE)              (((TYPE) <= 0x1FFFFFU) && ((TYPE) != 0U))

#define IS_OB_USER_BOR_LEVEL(LEVEL)        (((LEVEL) == OB_BOR_LEVEL_0) || ((LEVEL) == OB_BOR_LEVEL_1) || \
                                            ((LEVEL) == OB_BOR_LEVEL_2) || ((LEVEL) == OB_BOR_LEVEL_3) || \
                                            ((LEVEL) == OB_BOR_LEVEL_4))

#define IS_OB_USER_STOP(VALUE)             (((VALUE) == OB_STOP_RST) || ((VALUE) == OB_STOP_NORST))

#define IS_OB_USER_STANDBY(VALUE)          (((VALUE) == OB_STANDBY_RST) || ((VALUE) == OB_STANDBY_NORST))

#define IS_OB_USER_SHUTDOWN(VALUE)         (((VALUE) == OB_SHUTDOWN_RST) || ((VALUE) == OB_SHUTDOWN_NORST))

#define IS_OB_USER_SRAM134_RST(VALUE)      (((VALUE) == OB_SRAM134_RST_ERASE) || ((VALUE) == OB_SRAM134_RST_NOT_ERASE))

#define IS_OB_USER_IWDG(VALUE)             (((VALUE) == OB_IWDG_HW) || ((VALUE) == OB_IWDG_SW))

#define IS_OB_USER_IWDG_STOP(VALUE)        (((VALUE) == OB_IWDG_STOP_FREEZE) || ((VALUE) == OB_IWDG_STOP_RUN))

#define IS_OB_USER_IWDG_STDBY(VALUE)       (((VALUE) == OB_IWDG_STDBY_FREEZE) || ((VALUE) == OB_IWDG_STDBY_RUN))

#define IS_OB_USER_WWDG(VALUE)             (((VALUE) == OB_WWDG_HW) || ((VALUE) == OB_WWDG_SW))

#define IS_OB_USER_SWAP_BANK(VALUE)        (((VALUE) == OB_SWAP_BANK_DISABLE) || ((VALUE) == OB_SWAP_BANK_ENABLE))

#define IS_OB_USER_DUALBANK(VALUE)         (((VALUE) == OB_DUALBANK_SINGLE) || ((VALUE) == OB_DUALBANK_DUAL))

#define IS_OB_USER_BKPRAM_ECC(VALUE)       (((VALUE) == OB_BKPRAM_ECC_ENABLE) || ((VALUE) == OB_BKPRAM_ECC_DISABLE))

#define IS_OB_USER_SRAM3_ECC(VALUE)        (((VALUE) == OB_SRAM3_ECC_ENABLE) || ((VALUE) == OB_SRAM3_ECC_DISABLE))

#define IS_OB_USER_SRAM2_ECC(VALUE)        (((VALUE) == OB_SRAM2_ECC_ENABLE) || ((VALUE) == OB_SRAM2_ECC_DISABLE))

#define IS_OB_USER_SRAM2_RST(VALUE)        (((VALUE) == OB_SRAM2_RST_ERASE) || ((VALUE) == OB_SRAM2_RST_NOT_ERASE))

#define IS_OB_USER_SWBOOT0(VALUE)          (((VALUE) == OB_BOOT0_FROM_OB) || ((VALUE) == OB_BOOT0_FROM_PIN))

#define IS_OB_USER_BOOT0(VALUE)            (((VALUE) == OB_NBOOT0_RESET) || ((VALUE) == OB_NBOOT0_SET))

#define IS_OB_USER_PA15_PUPEN(VALUE)       (((VALUE) == OB_PA15_PUP_DISABLE) || ((VALUE) == OB_PA15_PUP_ENABLE))

#define IS_OB_USER_IO_VDD_HSLV(VALUE)      (((VALUE) == OB_IO_VDD_HSLV_DISABLE) || ((VALUE) == OB_IO_VDD_HSLV_ENABLE))

#define IS_OB_USER_IO_VDDIO2_HSLV(VALUE)   (((VALUE) == OB_IO_VDDIO2_HSLV_DISABLE)\
                                            || ((VALUE) == OB_IO_VDDIO2_HSLV_ENABLE))

#define IS_OB_USER_TZEN(VALUE)             (((VALUE) == OB_TZEN_DISABLE) || ((VALUE) == OB_TZEN_ENABLE))

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_OB_BOOT_LOCK(VALUE)             (((VALUE) == OB_BOOT_LOCK_DISABLE) || ((VALUE) == OB_BOOT_LOCK_ENABLE))

#define IS_OB_WMSEC_CONFIG(CFG)            ((((CFG) & 0x7F3U) != 0U) && \
                                            (((CFG) & 0x3U) != 0U) && (((CFG) & 0xFFFFF80CU) == 0U))

#define IS_OB_WMSEC_AREA_EXCLUSIVE(WMSEC)  (((((WMSEC) & OB_WMSEC_AREA1) != 0U) &&  \
                                             (((WMSEC) & OB_WMSEC_AREA2) == 0U)) || \
                                            ((((WMSEC) & OB_WMSEC_AREA2) != 0U) &&  \
                                             (((WMSEC) & OB_WMSEC_AREA1) == 0U)))
#endif /* __ARM_FEATURE_CMSE */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_OB_BOOTADDR_CONFIG(CFG)         (((CFG) == OB_BOOTADDR_NS0) || ((CFG) == OB_BOOTADDR_NS1) || \
                                            ((CFG) == OB_BOOTADDR_SEC0))
#else
#define IS_OB_BOOTADDR_CONFIG(CFG)         (((CFG) == OB_BOOTADDR_NS0) || ((CFG) == OB_BOOTADDR_NS1))
#endif /* __ARM_FEATURE_CMSE */

#define IS_FLASH_LATENCY(LATENCY)          (((LATENCY) == FLASH_LATENCY_0)  || ((LATENCY) == FLASH_LATENCY_1) || \
                                            ((LATENCY) == FLASH_LATENCY_2)  || ((LATENCY) == FLASH_LATENCY_3) || \
                                            ((LATENCY) == FLASH_LATENCY_4)  || ((LATENCY) == FLASH_LATENCY_5) || \
                                            ((LATENCY) == FLASH_LATENCY_6)  || ((LATENCY) == FLASH_LATENCY_7) || \
                                            ((LATENCY) == FLASH_LATENCY_8)  || ((LATENCY) == FLASH_LATENCY_9) || \
                                            ((LATENCY) == FLASH_LATENCY_10) || ((LATENCY) == FLASH_LATENCY_11) || \
                                            ((LATENCY) == FLASH_LATENCY_12) || ((LATENCY) == FLASH_LATENCY_13) || \
                                            ((LATENCY) == FLASH_LATENCY_14) || ((LATENCY) == FLASH_LATENCY_15))

#define IS_OB_RDP_KEY_TYPE(TYPE)           (((TYPE) == OB_RDP_KEY_OEM1) || \
                                            ((TYPE) == OB_RDP_KEY_OEM2))

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_FLASH_SECURE_OPERATION()        ((pFlash.ProcedureOnGoing & FLASH_NON_SECURE_MASK) == 0U)
#else
#define IS_FLASH_SECURE_OPERATION()        (0U)
#endif /* __ARM_FEATURE_CMSE */
/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @addtogroup FLASH_Private_Functions FLASH Private Functions
  * @{
  */
HAL_StatusTypeDef FLASH_WaitForLastOperation(uint32_t Timeout);
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

#endif /* STM32U5xx_HAL_FLASH_H */

