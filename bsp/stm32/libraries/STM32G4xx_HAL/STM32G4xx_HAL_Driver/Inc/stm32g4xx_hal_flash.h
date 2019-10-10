/**
  ******************************************************************************
  * @file    stm32g4xx_hal_flash.h
  * @author  MCD Application Team
  * @brief   Header file of FLASH HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 STMicroelectronics</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32G4xx_HAL_FLASH_H
#define STM32G4xx_HAL_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal_def.h"

/** @addtogroup STM32G4xx_HAL_Driver
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
  uint32_t Page;        /*!< Initial Flash page to erase when page erase is disabled.
                             This parameter must be a value between 0 and (max number of pages in the bank - 1)
                             (eg : 127 for 512KB dual bank) */
  uint32_t NbPages;     /*!< Number of pages to be erased.
                             This parameter must be a value between 1 and (max number of pages in the bank - value of initial page)*/
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
                                This parameter must be a value between WRPStartOffset and (max number of pages in the bank - 1) */
  uint32_t RDPLevel;       /*!< Set the read protection level.. (used for OPTIONBYTE_RDP).
                                This parameter can be a value of @ref FLASH_OB_Read_Protection */
  uint32_t USERType;       /*!< User option byte(s) to be configured (used for OPTIONBYTE_USER).
                                This parameter can be a combination of @ref FLASH_OB_USER_Type */
  uint32_t USERConfig;     /*!< Value of the user option byte (used for OPTIONBYTE_USER).
                                This parameter can be a combination of @ref FLASH_OB_USER_BOR_LEVEL,
                                @ref FLASH_OB_USER_nRST_STOP, @ref FLASH_OB_USER_nRST_STANDBY,
                                @ref FLASH_OB_USER_nRST_SHUTDOWN, @ref FLASH_OB_USER_IWDG_SW,
                                @ref FLASH_OB_USER_IWDG_STOP, @ref FLASH_OB_USER_IWDG_STANDBY,
                                @ref FLASH_OB_USER_WWDG_SW, @ref FLASH_OB_USER_BFB2 (*),
                                @ref FLASH_OB_USER_nBOOT1, @ref FLASH_OB_USER_SRAM_PE,
                                @ref FLASH_OB_USER_CCMSRAM_RST
                                @note (*) availability depends on devices */
  uint32_t PCROPConfig;    /*!< Configuration of the PCROP (used for OPTIONBYTE_PCROP).
                                This parameter must be a combination of @ref FLASH_Banks (except FLASH_BANK_BOTH)
                                and @ref FLASH_OB_PCROP_RDP */
  uint32_t PCROPStartAddr; /*!< PCROP Start address (used for OPTIONBYTE_PCROP).
                                This parameter must be a value between begin and end of bank
                                => Be careful of the bank swapping for the address */
  uint32_t PCROPEndAddr;   /*!< PCROP End address (used for OPTIONBYTE_PCROP).
                                This parameter must be a value between PCROP Start address and end of bank */
  uint32_t BootEntryPoint; /*!< Set the Boot Lock (used for OPTIONBYTE_BOOT_LOCK).
                                This parameter can be a value of @ref FLASH_OB_Boot_Lock */
  uint32_t SecBank;        /*!< Bank of securable memory area to be programmed (used for OPTIONBYTE_SEC).
                                Only one securable memory area could be programmed at the same time.
                                This parameter can be one of the following values:
                                FLASH_BANK_1: Securable memory area to be programmed in bank 1
                                FLASH_BANK_2: Securable memory area to be programmed in bank 2 (*)
                                @note (*) availability depends on devices */
  uint32_t SecSize;        /*!< Size of securable memory area to be programmed (used for OPTIONBYTE_SEC),
                                in number of pages. Securable memory area is starting from first page of the bank.
                                Only one securable memory could be programmed at the same time.
                                This parameter must be a value between 0 and (max number of pages in the bank - 1) */
} FLASH_OBProgramInitTypeDef;

/**
  * @brief  FLASH Procedure structure definition
  */
typedef enum
{
  FLASH_PROC_NONE = 0,
  FLASH_PROC_PAGE_ERASE,
  FLASH_PROC_MASS_ERASE,
  FLASH_PROC_PROGRAM,
  FLASH_PROC_PROGRAM_LAST
} FLASH_ProcedureTypeDef;

/**
  * @brief  FLASH Cache structure definition
  */
typedef enum
{
  FLASH_CACHE_DISABLED = 0,
  FLASH_CACHE_ICACHE_ENABLED,
  FLASH_CACHE_DCACHE_ENABLED,
  FLASH_CACHE_ICACHE_DCACHE_ENABLED
} FLASH_CacheTypeDef;

/**
  * @brief  FLASH handle Structure definition
  */
typedef struct
{
  HAL_LockTypeDef             Lock;              /* FLASH locking object */
  __IO uint32_t               ErrorCode;         /* FLASH error code */
  __IO FLASH_ProcedureTypeDef ProcedureOnGoing;  /* Internal variable to indicate which procedure is ongoing or not in IT context */
  __IO uint32_t               Address;           /* Internal variable to save address selected for program in IT context */
  __IO uint32_t               Bank;              /* Internal variable to save current bank selected during erase in IT context */
  __IO uint32_t               Page;              /* Internal variable to define the current page which is erasing in IT context */
  __IO uint32_t               NbPagesToErase;    /* Internal variable to save the remaining pages to erase in IT context */
  __IO FLASH_CacheTypeDef     CacheToReactivate; /* Internal variable to indicate which caches should be reactivated */
} FLASH_ProcessTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup FLASH_Exported_Constants FLASH Exported Constants
  * @{
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
#define HAL_FLASH_ERROR_MIS       FLASH_FLAG_MISERR
#define HAL_FLASH_ERROR_FAST      FLASH_FLAG_FASTERR
#define HAL_FLASH_ERROR_RD        FLASH_FLAG_RDERR
#define HAL_FLASH_ERROR_OPTV      FLASH_FLAG_OPTVERR
#define HAL_FLASH_ERROR_ECCC      FLASH_FLAG_ECCC
#define HAL_FLASH_ERROR_ECCD      FLASH_FLAG_ECCD
#if defined (FLASH_OPTR_DBANK)
#define HAL_FLASH_ERROR_ECCC2     FLASH_FLAG_ECCC2
#define HAL_FLASH_ERROR_ECCD2     FLASH_FLAG_ECCD2
#endif
/**
  * @}
  */

/** @defgroup FLASH_Type_Erase FLASH Erase Type
  * @{
  */
#define FLASH_TYPEERASE_PAGES     0x00U                    /*!<Pages erase only*/
#define FLASH_TYPEERASE_MASSERASE 0x01U                    /*!<Flash mass erase activation*/
/**
  * @}
  */

/** @defgroup FLASH_Banks FLASH Banks
  * @{
  */
#define FLASH_BANK_1              0x00000001U              /*!< Bank 1   */
#if defined (FLASH_OPTR_DBANK)
#define FLASH_BANK_2              0x00000002U              /*!< Bank 2   */
#define FLASH_BANK_BOTH           (FLASH_BANK_1 | FLASH_BANK_2) /*!< Bank1 and Bank2  */
#else
#define FLASH_BANK_BOTH           FLASH_BANK_1             /*!< Bank 1   */
#endif
/**
  * @}
  */


/** @defgroup FLASH_Type_Program FLASH Program Type
  * @{
  */
#define FLASH_TYPEPROGRAM_DOUBLEWORD    0x00U              /*!< Program a double-word (64-bit) at a specified address.*/
#define FLASH_TYPEPROGRAM_FAST          0x01U              /*!< Fast program a 32 row double-word (64-bit) at a specified address.
                                                                And another 32 row double-word (64-bit) will be programmed */
#define FLASH_TYPEPROGRAM_FAST_AND_LAST 0x02U              /*!< Fast program a 32 row double-word (64-bit) at a specified address.
                                                                And this is the last 32 row double-word (64-bit) programmed */
/**
  * @}
  */

/** @defgroup FLASH_OB_Type FLASH Option Bytes Type
  * @{
  */
#define OPTIONBYTE_WRP            0x01U                    /*!< WRP option byte configuration */
#define OPTIONBYTE_RDP            0x02U                    /*!< RDP option byte configuration */
#define OPTIONBYTE_USER           0x04U                    /*!< USER option byte configuration */
#define OPTIONBYTE_PCROP          0x08U                    /*!< PCROP option byte configuration */
#define OPTIONBYTE_BOOT_LOCK      0x10U                    /*!< Boot lock option byte configuration */
#define OPTIONBYTE_SEC            0x20U                    /*!< Securable memory option byte configuration */
/**
  * @}
  */

/** @defgroup FLASH_OB_WRP_Area FLASH WRP Area
  * @{
  */
#define OB_WRPAREA_BANK1_AREAA    0x00U                    /*!< Flash Bank 1 Area A */
#define OB_WRPAREA_BANK1_AREAB    0x01U                    /*!< Flash Bank 1 Area B */
#if defined (FLASH_OPTR_DBANK)
#define OB_WRPAREA_BANK2_AREAA    0x02U                    /*!< Flash Bank 2 Area A */
#define OB_WRPAREA_BANK2_AREAB    0x04U                    /*!< Flash Bank 2 Area B */
#endif
/**
  * @}
  */

/** @defgroup FLASH_OB_Boot_Lock FLASH Boot Lock
  * @{
  */
#define OB_BOOT_LOCK_DISABLE      0x00000000U              /*!< Boot Lock Disable */
#define OB_BOOT_LOCK_ENABLE       FLASH_SEC1R_BOOT_LOCK    /*!< Boot Lock Enable */
/**
  * @}
  */

/** @defgroup FLASH_OB_Read_Protection FLASH Option Bytes Read Protection
  * @{
  */
#define OB_RDP_LEVEL_0            0xAAU
#define OB_RDP_LEVEL_1            0xBBU
#define OB_RDP_LEVEL_2            0xCCU                    /*!< Warning: When enabling read protection level 2 
                                                                it's no more possible to go back to level 1 or 0 */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_Type FLASH Option Bytes User Type
  * @{
  */
#define OB_USER_BOR_LEV           0x00000001U              /*!< BOR reset Level */
#define OB_USER_nRST_STOP         0x00000002U              /*!< Reset generated when entering the stop mode */
#define OB_USER_nRST_STDBY        0x00000004U              /*!< Reset generated when entering the standby mode */
#define OB_USER_IWDG_SW           0x00000008U              /*!< Independent watchdog selection */
#define OB_USER_IWDG_STOP         0x00000010U              /*!< Independent watchdog counter freeze in stop mode */
#define OB_USER_IWDG_STDBY        0x00000020U              /*!< Independent watchdog counter freeze in standby mode */
#define OB_USER_WWDG_SW           0x00000040U              /*!< Window watchdog selection */
#if defined (FLASH_OPTR_DBANK)
#define OB_USER_BFB2              0x00000080U              /*!< Dual-bank boot */
#define OB_USER_DBANK             0x00000100U              /*!< Single bank with 128-bits data or two banks with 64-bits data */
#endif
#define OB_USER_nBOOT1            0x00000200U              /*!< Boot configuration */
#define OB_USER_SRAM_PE           0x00000400U              /*!< SRAM parity check enable (first 32kB of SRAM1 + CCM SRAM) */
#define OB_USER_CCMSRAM_RST       0x00000800U              /*!< CCMSRAM Erase when system reset */
#define OB_USER_nRST_SHDW         0x00001000U              /*!< Reset generated when entering the shutdown mode */
#define OB_USER_nSWBOOT0          0x00002000U              /*!< Software BOOT0 */
#define OB_USER_nBOOT0            0x00004000U              /*!< nBOOT0 option bit */
#define OB_USER_NRST_MODE         0x00008000U              /*!< Reset pin configuration */
#define OB_USER_IRHEN             0x00010000U              /*!< Internal Reset Holder enable */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_BOR_LEVEL FLASH Option Bytes User BOR Level
  * @{
  */
#define OB_BOR_LEVEL_0            FLASH_OPTR_BOR_LEV_0     /*!< Reset level threshold is around 1.7V */
#define OB_BOR_LEVEL_1            FLASH_OPTR_BOR_LEV_1     /*!< Reset level threshold is around 2.0V */
#define OB_BOR_LEVEL_2            FLASH_OPTR_BOR_LEV_2     /*!< Reset level threshold is around 2.2V */
#define OB_BOR_LEVEL_3            FLASH_OPTR_BOR_LEV_3     /*!< Reset level threshold is around 2.5V */
#define OB_BOR_LEVEL_4            FLASH_OPTR_BOR_LEV_4     /*!< Reset level threshold is around 2.8V */
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
#define OB_IWDG_STOP_FREEZE       0x00000000U              /*!< Independent watchdog counter is frozen in Stop mode */
#define OB_IWDG_STOP_RUN          FLASH_OPTR_IWDG_STOP     /*!< Independent watchdog counter is running in Stop mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IWDG_STANDBY FLASH Option Bytes User IWDG Mode On Standby
  * @{
  */
#define OB_IWDG_STDBY_FREEZE      0x00000000U              /*!< Independent watchdog counter is frozen in Standby mode */
#define OB_IWDG_STDBY_RUN         FLASH_OPTR_IWDG_STDBY    /*!< Independent watchdog counter is running in Standby mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_WWDG_SW FLASH Option Bytes User WWDG Type
  * @{
  */
#define OB_WWDG_HW                0x00000000U              /*!< Hardware window watchdog */
#define OB_WWDG_SW                FLASH_OPTR_WWDG_SW       /*!< Software window watchdog */
/**
  * @}
  */

#if defined (FLASH_OPTR_DBANK)
/** @defgroup FLASH_OB_USER_BFB2 FLASH Option Bytes User BFB2 Mode
  * @{
  */
#define OB_BFB2_DISABLE           0x00000000U              /*!< Dual-bank boot disable */
#define OB_BFB2_ENABLE            FLASH_OPTR_BFB2          /*!< Dual-bank boot enable */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_DBANK FLASH Option Bytes User DBANK Type
  * @{
  */
#define OB_DBANK_128_BITS         0x00000000U              /*!< Single-bank with 128-bits data */
#define OB_DBANK_64_BITS          FLASH_OPTR_DBANK         /*!< Dual-bank with 64-bits data */
/**
  * @}
  */
#endif

/** @defgroup FLASH_OB_USER_nBOOT1 FLASH Option Bytes User BOOT1 Type
  * @{
  */
#define OB_BOOT1_SRAM             0x00000000U              /*!< Embedded SRAM1 is selected as boot space (if BOOT0=1) */
#define OB_BOOT1_SYSTEM           FLASH_OPTR_nBOOT1        /*!< System memory is selected as boot space (if BOOT0=1) */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_SRAM_PE FLASH Option Bytes User SRAM Parity Check Type
  * @{
  */
#define OB_SRAM_PARITY_ENABLE     0x00000000U              /*!< SRAM parity check enable (first 32kB of SRAM1 + CCM SRAM) */
#define OB_SRAM_PARITY_DISABLE    FLASH_OPTR_SRAM_PE       /*!< SRAM parity check disable (first 32kB of SRAM1 + CCM SRAM) */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_CCMSRAM_RST FLASH Option Bytes User CCMSRAM Erase On Reset Type
  * @{
  */
#define OB_CCMSRAM_RST_ERASE      0x00000000U              /*!< CCMSRAM erased when a system reset occurs */
#define OB_CCMSRAM_RST_NOT_ERASE  FLASH_OPTR_CCMSRAM_RST   /*!< CCMSRAM is not erased when a system reset occurs */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_nSWBOOT0 FLASH Option Bytes User Software BOOT0
  * @{
  */
#define OB_BOOT0_FROM_OB          0x00000000U              /*!< BOOT0 taken from the option bit nBOOT0 */
#define OB_BOOT0_FROM_PIN         FLASH_OPTR_nSWBOOT0      /*!< BOOT0 taken from PB8/BOOT0 pin */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_nBOOT0 FLASH Option Bytes User nBOOT0 option bit
  * @{
  */
#define OB_nBOOT0_RESET           0x00000000U              /*!< nBOOT0 = 0 */
#define OB_nBOOT0_SET             FLASH_OPTR_nBOOT0        /*!< nBOOT0 = 1 */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_NRST_MODE FLASH Option Bytes User NRST mode bit
  * @{
  */
#define OB_NRST_MODE_INPUT_ONLY   FLASH_OPTR_NRST_MODE_0   /*!< Reset pin is in Reset input mode only */
#define OB_NRST_MODE_GPIO         FLASH_OPTR_NRST_MODE_1   /*!< Reset pin is in GPIO mode only */
#define OB_NRST_MODE_INPUT_OUTPUT FLASH_OPTR_NRST_MODE     /*!< Reset pin is in reset input and output mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_INTERNAL_RESET_HOLDER FLASH Option Bytes User internal reset holder bit
  * @{
  */
#define OB_IRH_DISABLE            0x00000000U              /*!< Internal Reset holder disable */
#define OB_IRH_ENABLE             FLASH_OPTR_IRHEN         /*!< Internal Reset holder enable */
/**
  * @}
  */

/** @defgroup FLASH_OB_PCROP_RDP FLASH Option Bytes PCROP On RDP Level Type
  * @{
  */
#define OB_PCROP_RDP_NOT_ERASE    0x00000000U              /*!< PCROP area is not erased when the RDP level 
                                                                is decreased from Level 1 to Level 0 */
#define OB_PCROP_RDP_ERASE        FLASH_PCROP1ER_PCROP_RDP /*!< PCROP area is erased when the RDP level is 
                                                                decreased from Level 1 to Level 0 (full mass erase) */
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
#define FLASH_KEY1                0x45670123U              /*!< Flash key1 */
#define FLASH_KEY2                0xCDEF89ABU              /*!< Flash key2: used with FLASH_KEY1 
                                                                to unlock the FLASH registers access */

#define FLASH_PDKEY1              0x04152637U              /*!< Flash power down key1 */
#define FLASH_PDKEY2              0xFAFBFCFDU              /*!< Flash power down key2: used with FLASH_PDKEY1 
                                                                to unlock the RUN_PD bit in FLASH_ACR */

#define FLASH_OPTKEY1             0x08192A3BU              /*!< Flash option byte key1 */
#define FLASH_OPTKEY2             0x4C5D6E7FU              /*!< Flash option byte key2: used with FLASH_OPTKEY1 
                                                                to allow option bytes operations */
/**
  * @}
  */

/** @defgroup FLASH_Flags FLASH Flags Definition
  * @{
  */
#define FLASH_FLAG_EOP            FLASH_SR_EOP             /*!< FLASH End of operation flag */
#define FLASH_FLAG_OPERR          FLASH_SR_OPERR           /*!< FLASH Operation error flag */
#define FLASH_FLAG_PROGERR        FLASH_SR_PROGERR         /*!< FLASH Programming error flag */
#define FLASH_FLAG_WRPERR         FLASH_SR_WRPERR          /*!< FLASH Write protection error flag */
#define FLASH_FLAG_PGAERR         FLASH_SR_PGAERR          /*!< FLASH Programming alignment error flag */
#define FLASH_FLAG_SIZERR         FLASH_SR_SIZERR          /*!< FLASH Size error flag  */
#define FLASH_FLAG_PGSERR         FLASH_SR_PGSERR          /*!< FLASH Programming sequence error flag */
#define FLASH_FLAG_MISERR         FLASH_SR_MISERR          /*!< FLASH Fast programming data miss error flag */
#define FLASH_FLAG_FASTERR        FLASH_SR_FASTERR         /*!< FLASH Fast programming error flag */
#define FLASH_FLAG_RDERR          FLASH_SR_RDERR           /*!< FLASH PCROP read error flag */
#define FLASH_FLAG_OPTVERR        FLASH_SR_OPTVERR         /*!< FLASH Option validity error flag  */
#define FLASH_FLAG_BSY            FLASH_SR_BSY             /*!< FLASH Busy flag */
#define FLASH_FLAG_ECCC           FLASH_ECCR_ECCC          /*!< FLASH ECC correction in 64 LSB bits */
#define FLASH_FLAG_ECCD           FLASH_ECCR_ECCD          /*!< FLASH ECC detection in 64 LSB bits */
#if defined (FLASH_OPTR_DBANK)
#define FLASH_FLAG_ECCC2          FLASH_ECCR_ECCC2         /*!< FLASH ECC correction in 64 MSB bits (mode 128 bits only) */
#define FLASH_FLAG_ECCD2          FLASH_ECCR_ECCD2         /*!< FLASH ECC detection in 64 MSB bits (mode 128 bits only) */
#endif

#define FLASH_FLAG_SR_ERRORS      (FLASH_FLAG_OPERR   | FLASH_FLAG_PROGERR | FLASH_FLAG_WRPERR | \
                                   FLASH_FLAG_PGAERR  | FLASH_FLAG_SIZERR  | FLASH_FLAG_PGSERR | \
                                   FLASH_FLAG_MISERR  | FLASH_FLAG_FASTERR | FLASH_FLAG_RDERR  | \
                                   FLASH_FLAG_OPTVERR)
#if defined (FLASH_OPTR_DBANK)
#define FLASH_FLAG_ECCR_ERRORS    (FLASH_FLAG_ECCC    | FLASH_FLAG_ECCD    | FLASH_FLAG_ECCC2  | FLASH_FLAG_ECCD2)
#else
#define FLASH_FLAG_ECCR_ERRORS    (FLASH_FLAG_ECCC    | FLASH_FLAG_ECCD)
#endif
#define FLASH_FLAG_ALL_ERRORS     (FLASH_FLAG_SR_ERRORS | FLASH_FLAG_ECCR_ERRORS)
/**
  * @}
  */

/** @defgroup FLASH_Interrupt_definition FLASH Interrupts Definition
  * @brief FLASH Interrupt definition
  * @{
  */
#define FLASH_IT_EOP              FLASH_CR_EOPIE           /*!< End of FLASH Operation Interrupt source */
#define FLASH_IT_OPERR            FLASH_CR_ERRIE           /*!< Error Interrupt source */
#define FLASH_IT_RDERR            FLASH_CR_RDERRIE         /*!< PCROP Read Error Interrupt source*/
#define FLASH_IT_ECCC            (FLASH_ECCR_ECCIE >> 24U) /*!< ECC Correction Interrupt source */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup FLASH_Exported_Macros FLASH Exported Macros
  * @brief macros to control FLASH features
  * @{
  */

/**
  * @brief  Set the FLASH Latency.
  * @param  __LATENCY__ FLASH Latency.
  *         This parameter can be one of the following values :
  *           @arg FLASH_LATENCY_0: FLASH Zero wait state
  *           @arg FLASH_LATENCY_1: FLASH One wait state
  *           @arg FLASH_LATENCY_2: FLASH Two wait states
  *           @arg FLASH_LATENCY_3: FLASH Three wait states
  *           @arg FLASH_LATENCY_4: FLASH Four wait states
  *           @arg FLASH_LATENCY_5: FLASH Five wait states
  *           @arg FLASH_LATENCY_6: FLASH Six wait states
  *           @arg FLASH_LATENCY_7: FLASH Seven wait states
  * @retval None
  */
#define __HAL_FLASH_SET_LATENCY(__LATENCY__)    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (__LATENCY__))

/**
  * @brief  Get the FLASH Latency.
  * @retval FLASH_Latency.
  *         This parameter can be one of the following values :
  *           @arg FLASH_LATENCY_0: FLASH Zero wait state
  *           @arg FLASH_LATENCY_1: FLASH One wait state
  *           @arg FLASH_LATENCY_2: FLASH Two wait states
  *           @arg FLASH_LATENCY_3: FLASH Three wait states
  *           @arg FLASH_LATENCY_4: FLASH Four wait states
  *           @arg FLASH_LATENCY_5: FLASH Five wait states
  *           @arg FLASH_LATENCY_6: FLASH Six wait states
  *           @arg FLASH_LATENCY_7: FLASH Seven wait states
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
  * @brief  Enable the FLASH data cache.
  * @retval none
  */
#define __HAL_FLASH_DATA_CACHE_ENABLE()         SET_BIT(FLASH->ACR, FLASH_ACR_DCEN)

/**
  * @brief  Disable the FLASH data cache.
  * @retval none
  */
#define __HAL_FLASH_DATA_CACHE_DISABLE()        CLEAR_BIT(FLASH->ACR, FLASH_ACR_DCEN)

/**
  * @brief  Reset the FLASH instruction Cache.
  * @note   This function must be used only when the Instruction Cache is disabled.
  * @retval None
  */
#define __HAL_FLASH_INSTRUCTION_CACHE_RESET()   do { SET_BIT(FLASH->ACR, FLASH_ACR_ICRST);   \
                                                     CLEAR_BIT(FLASH->ACR, FLASH_ACR_ICRST); \
                                                   } while (0)

/**
  * @brief  Reset the FLASH data Cache.
  * @note   This function must be used only when the data Cache is disabled.
  * @retval None
  */
#define __HAL_FLASH_DATA_CACHE_RESET()          do { SET_BIT(FLASH->ACR, FLASH_ACR_DCRST);   \
                                                     CLEAR_BIT(FLASH->ACR, FLASH_ACR_DCRST); \
                                                   } while (0)

/**
  * @brief  Enable the FLASH power down during Low-power run mode.
  * @note   Writing this bit to 1, automatically the keys are
  *         lost and a new unlock sequence is necessary to re-write it to 0.
  */
#define __HAL_FLASH_POWER_DOWN_ENABLE()         do { WRITE_REG(FLASH->PDKEYR, FLASH_PDKEY1); \
                                                     WRITE_REG(FLASH->PDKEYR, FLASH_PDKEY2); \
                                                     SET_BIT(FLASH->ACR, FLASH_ACR_RUN_PD);   \
                                                   } while (0)

/**
  * @brief  Disable the FLASH power down during Low-power run mode.
  * @note   Writing this bit to 0, automatically the keys are
  *         lost and a new unlock sequence is necessary to re-write it to 1.
  */
#define __HAL_FLASH_POWER_DOWN_DISABLE()        do { WRITE_REG(FLASH->PDKEYR, FLASH_PDKEY1); \
                                                     WRITE_REG(FLASH->PDKEYR, FLASH_PDKEY2); \
                                                     CLEAR_BIT(FLASH->ACR, FLASH_ACR_RUN_PD); \
                                                   } while (0)

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
  *     @arg FLASH_IT_RDERR: PCROP Read Error Interrupt
  *     @arg FLASH_IT_ECCC: ECC Correction Interrupt
  * @retval none
  */
#define __HAL_FLASH_ENABLE_IT(__INTERRUPT__)    do { if(((__INTERRUPT__) & FLASH_IT_ECCC) != 0U) { SET_BIT(FLASH->ECCR, FLASH_ECCR_ECCIE); }\
                                                     if(((__INTERRUPT__) & (~FLASH_IT_ECCC)) != 0U) { SET_BIT(FLASH->CR, ((__INTERRUPT__) & (~FLASH_IT_ECCC))); }\
                                                   } while (0)

/**
  * @brief  Disable the specified FLASH interrupt.
  * @param  __INTERRUPT__ FLASH interrupt
  *         This parameter can be any combination of the following values:
  *     @arg FLASH_IT_EOP: End of FLASH Operation Interrupt
  *     @arg FLASH_IT_OPERR: Error Interrupt
  *     @arg FLASH_IT_RDERR: PCROP Read Error Interrupt
  *     @arg FLASH_IT_ECCC: ECC Correction Interrupt
  * @retval none
  */
#define __HAL_FLASH_DISABLE_IT(__INTERRUPT__)   do { if(((__INTERRUPT__) & FLASH_IT_ECCC) != 0U) { CLEAR_BIT(FLASH->ECCR, FLASH_ECCR_ECCIE); }\
                                                     if(((__INTERRUPT__) & (~FLASH_IT_ECCC)) != 0U) { CLEAR_BIT(FLASH->CR, ((__INTERRUPT__) & (~FLASH_IT_ECCC))); }\
                                                   } while (0)

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
  *     @arg FLASH_FLAG_MISERR: FLASH Fast programming data miss error flag
  *     @arg FLASH_FLAG_FASTERR: FLASH Fast programming error flag
  *     @arg FLASH_FLAG_RDERR: FLASH PCROP read  error flag
  *     @arg FLASH_FLAG_OPTVERR: FLASH Option validity error flag
  *     @arg FLASH_FLAG_BSY: FLASH write/erase operations in progress flag
  *     @arg FLASH_FLAG_ECCC: FLASH one ECC error has been detected and corrected in 64 LSB bits
  *     @arg FLASH_FLAG_ECCD: FLASH two ECC errors have been detected in 64 LSB bits
  *     @arg FLASH_FLAG_ECCC2(*): FLASH one ECC error has been detected and corrected in 64 MSB bits (mode 128 bits only)
  *     @arg FLASH_FLAG_ECCD2(*): FLASH two ECC errors have been detected in 64 MSB bits (mode 128 bits only)
  * @note  (*) availability depends on devices
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
#define __HAL_FLASH_GET_FLAG(__FLAG__)          ((((__FLAG__) & FLASH_FLAG_ECCR_ERRORS) != 0U) ? \
                                                 (READ_BIT(FLASH->ECCR, (__FLAG__)) == (__FLAG__)) : \
                                                 (READ_BIT(FLASH->SR,   (__FLAG__)) == (__FLAG__)))

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
  *     @arg FLASH_FLAG_MISERR: FLASH Fast programming data miss error flag
  *     @arg FLASH_FLAG_FASTERR: FLASH Fast programming error flag
  *     @arg FLASH_FLAG_RDERR: FLASH PCROP read  error flag
  *     @arg FLASH_FLAG_OPTVERR: FLASH Option validity error flag
  *     @arg FLASH_FLAG_ECCC: FLASH one ECC error has been detected and corrected in 64 LSB bits
  *     @arg FLASH_FLAG_ECCD: FLASH two ECC errors have been detected in 64 LSB bits
  *     @arg FLASH_FLAG_ECCC2(*): FLASH one ECC error has been detected and corrected in 64 MSB bits (mode 128 bits only)
  *     @arg FLASH_FLAG_ECCD2(*): FLASH two ECC errors have been detected in 64 MSB bits (mode 128 bits only)
  *     @arg FLASH_FLAG_SR_ERRORS: FLASH All SR errors flags
  *     @arg FLASH_FLAG_ECCR_ERRORS: FLASH All ECCR errors flags
  * @note  (*) availability depends on devices
  * @retval None
  */
#define __HAL_FLASH_CLEAR_FLAG(__FLAG__)        do { if(((__FLAG__) & FLASH_FLAG_ECCR_ERRORS) != 0U) { SET_BIT(FLASH->ECCR, ((__FLAG__) & FLASH_FLAG_ECCR_ERRORS)); }\
                                                     if(((__FLAG__) & ~(FLASH_FLAG_ECCR_ERRORS)) != 0U) { WRITE_REG(FLASH->SR, ((__FLAG__) & ~(FLASH_FLAG_ECCR_ERRORS))); }\
                                                   } while (0)
/**
  * @}
  */

/* Include FLASH HAL Extended module */
#include "stm32g4xx_hal_flash_ex.h"
#include "stm32g4xx_hal_flash_ramfunc.h"

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

/** @addtogroup FLASH_Private_Functions
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

#if defined (FLASH_OPTR_DBANK)
#define FLASH_SIZE                      ((((*((uint16_t *)FLASH_SIZE_DATA_REGISTER)) == 0xFFFFU)) ? (0x200UL << 10U) : \
                                        (((*((uint32_t *)FLASH_SIZE_DATA_REGISTER)) & 0xFFFFUL) << 10U))
#define FLASH_BANK_SIZE                 (FLASH_SIZE >> 1)
#define FLASH_PAGE_NB                   128U
#define FLASH_PAGE_SIZE_128_BITS        0x1000U /* 4 KB */
#else
#define FLASH_SIZE                      ((((*((uint16_t *)FLASH_SIZE_DATA_REGISTER)) == 0xFFFFU)) ? (0x80UL << 10U) : \
                                        (((*((uint32_t *)FLASH_SIZE_DATA_REGISTER)) & 0xFFFFUL) << 10U))
#define FLASH_BANK_SIZE                 (FLASH_SIZE)
#define FLASH_PAGE_NB                   64U
#endif

#define FLASH_PAGE_SIZE                 0x800U  /* 2 KB */

#define FLASH_TIMEOUT_VALUE             1000U   /* 1 s  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup FLASH_Private_Macros FLASH Private Macros
  *  @{
  */

#define IS_FLASH_TYPEERASE(VALUE)          (((VALUE) == FLASH_TYPEERASE_PAGES) || \
                                            ((VALUE) == FLASH_TYPEERASE_MASSERASE))

#if defined (FLASH_OPTR_DBANK)
#define IS_FLASH_BANK(BANK)                (((BANK) == FLASH_BANK_1)  || \
                                            ((BANK) == FLASH_BANK_2)  || \
                                            ((BANK) == FLASH_BANK_BOTH))

#define IS_FLASH_BANK_EXCLUSIVE(BANK)      (((BANK) == FLASH_BANK_1)  || \
                                            ((BANK) == FLASH_BANK_2))
#else
#define IS_FLASH_BANK(BANK)                ((BANK) == FLASH_BANK_1)

#define IS_FLASH_BANK_EXCLUSIVE(BANK)      ((BANK) == FLASH_BANK_1)
#endif

#define IS_FLASH_TYPEPROGRAM(VALUE)        (((VALUE) == FLASH_TYPEPROGRAM_DOUBLEWORD) || \
                                            ((VALUE) == FLASH_TYPEPROGRAM_FAST) || \
                                            ((VALUE) == FLASH_TYPEPROGRAM_FAST_AND_LAST))

#define IS_FLASH_MAIN_MEM_ADDRESS(ADDRESS) (((ADDRESS) >= FLASH_BASE) && ((ADDRESS) < (FLASH_BASE+FLASH_SIZE)))

#define IS_FLASH_OTP_ADDRESS(ADDRESS)      (((ADDRESS) >= 0x1FFF7000U) && ((ADDRESS) <= 0x1FFF73FFU))

#define IS_FLASH_PROGRAM_ADDRESS(ADDRESS)  (IS_FLASH_MAIN_MEM_ADDRESS(ADDRESS) || IS_FLASH_OTP_ADDRESS(ADDRESS))

#define IS_FLASH_PAGE(PAGE)                ((PAGE) < FLASH_PAGE_NB)

#define IS_OPTIONBYTE(VALUE)               (((VALUE) <= (OPTIONBYTE_WRP | OPTIONBYTE_RDP | OPTIONBYTE_USER | OPTIONBYTE_PCROP | \
                                            OPTIONBYTE_BOOT_LOCK | OPTIONBYTE_SEC)))

#if defined (FLASH_OPTR_DBANK)
#define IS_OB_WRPAREA(VALUE)               (((VALUE) == OB_WRPAREA_BANK1_AREAA) || ((VALUE) == OB_WRPAREA_BANK1_AREAB) || \
                                            ((VALUE) == OB_WRPAREA_BANK2_AREAA) || ((VALUE) == OB_WRPAREA_BANK2_AREAB))
#else
#define IS_OB_WRPAREA(VALUE)               (((VALUE) == OB_WRPAREA_BANK1_AREAA) || ((VALUE) == OB_WRPAREA_BANK1_AREAB))
#endif

#define IS_OB_BOOT_LOCK(VALUE)             (((VALUE) == OB_BOOT_LOCK_ENABLE) || ((VALUE) == OB_BOOT_LOCK_DISABLE))

#define IS_OB_RDP_LEVEL(LEVEL)             (((LEVEL) == OB_RDP_LEVEL_0) ||\
                                            ((LEVEL) == OB_RDP_LEVEL_1) ||\
                                            ((LEVEL) == OB_RDP_LEVEL_2))

#define IS_OB_USER_TYPE(TYPE)              (((TYPE) <= 0x1FFFFU) && ((TYPE) != 0U))

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

#if defined (FLASH_OPTR_DBANK)
#define IS_OB_USER_BFB2(VALUE)             (((VALUE) == OB_BFB2_DISABLE) || ((VALUE) == OB_BFB2_ENABLE))

#define IS_OB_USER_DBANK(VALUE)            (((VALUE) == OB_DBANK_128_BITS) || ((VALUE) == OB_DBANK_64_BITS))
#endif

#define IS_OB_USER_BOOT1(VALUE)            (((VALUE) == OB_BOOT1_SRAM) || ((VALUE) == OB_BOOT1_SYSTEM))

#define IS_OB_USER_SRAM_PARITY(VALUE)      (((VALUE) == OB_SRAM_PARITY_ENABLE) || ((VALUE) == OB_SRAM_PARITY_DISABLE))

#define IS_OB_USER_CCMSRAM_RST(VALUE)      (((VALUE) == OB_CCMSRAM_RST_ERASE) || ((VALUE) == OB_CCMSRAM_RST_NOT_ERASE))

#define IS_OB_USER_SWBOOT0(VALUE)          (((VALUE) == OB_BOOT0_FROM_OB) || ((VALUE) == OB_BOOT0_FROM_PIN))

#define IS_OB_USER_BOOT0(VALUE)            (((VALUE) == OB_nBOOT0_RESET) || ((VALUE) == OB_nBOOT0_SET))

#define IS_OB_USER_NRST_MODE(VALUE)        (((VALUE) == OB_NRST_MODE_GPIO) || ((VALUE) == OB_NRST_MODE_INPUT_ONLY) || \
                                            ((VALUE) == OB_NRST_MODE_INPUT_OUTPUT))

#define IS_OB_USER_IRHEN(VALUE)            (((VALUE) == OB_IRH_ENABLE) || ((VALUE) == OB_IRH_DISABLE))

#define IS_OB_PCROP_RDP(VALUE)             (((VALUE) == OB_PCROP_RDP_NOT_ERASE) || ((VALUE) == OB_PCROP_RDP_ERASE))

#define IS_OB_SECMEM_SIZE(VALUE)           ((VALUE) <= FLASH_PAGE_NB)

#define IS_FLASH_LATENCY(LATENCY)          (((LATENCY) == FLASH_LATENCY_0) || ((LATENCY) == FLASH_LATENCY_1) || \
                                            ((LATENCY) == FLASH_LATENCY_2) || ((LATENCY) == FLASH_LATENCY_3) || \
                                            ((LATENCY) == FLASH_LATENCY_4) || ((LATENCY) == FLASH_LATENCY_5) || \
                                            ((LATENCY) == FLASH_LATENCY_6) || ((LATENCY) == FLASH_LATENCY_7) || \
                                            ((LATENCY) == FLASH_LATENCY_8) || ((LATENCY) == FLASH_LATENCY_9) || \
                                            ((LATENCY) == FLASH_LATENCY_10) || ((LATENCY) == FLASH_LATENCY_11) || \
                                            ((LATENCY) == FLASH_LATENCY_12) || ((LATENCY) == FLASH_LATENCY_13) || \
                                            ((LATENCY) == FLASH_LATENCY_14) || ((LATENCY) == FLASH_LATENCY_15))
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

#endif /* STM32G4xx_HAL_FLASH_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
