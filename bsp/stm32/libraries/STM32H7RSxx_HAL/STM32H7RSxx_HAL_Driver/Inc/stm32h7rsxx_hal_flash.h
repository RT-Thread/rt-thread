/**
  ******************************************************************************
  * @file    stm32h7rsxx_hal_flash.h
  * @author  MCD Application Team
  * @brief   Header file of FLASH HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7RSxx_HAL_FLASH_H
#define STM32H7RSxx_HAL_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal_def.h"

/** @addtogroup STM32H7RSxx_HAL_Driver
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
  uint32_t Sector;      /*!< Initial Flash sector to erase when sector erase is enabled
                             This parameter must be a value between 0 and (max number of sector - 1)
                             (eg : 15 for 128KB single bank) */
  uint32_t NbSectors;   /*!< Number of sectors to be erased.
                             This parameter must be a value between 1 and
                             (max number of sectors - value of initial page)*/
} FLASH_EraseInitTypeDef;

/**
  * @brief  FLASH Option Bytes Program structure definition
  */
#define FLASH_KEY_DATA_NB_REG (8U)  /*!< 8 Key data registers  */

typedef struct
{
  uint32_t OptionType;                  /*!< Option byte to be configured.
                                             This parameter can be a combination of the values of @ref FLASH_OB_TYPE */
  uint32_t WRPState;                    /*!< Write protection activation or deactivation (used for OPTIONBYTE_WRP).
                                             This parameter can be value of @ref FLASH_OB_WRP_STATE */
  uint32_t WRPSector;                   /*!< Specifies the sector(s) to be write protected (used for OPTIONBYTE_WRP).
                                             The value of this parameter depend on device used within the same series */
  uint32_t USERType;                    /*!< User option byte(s) to be configured (used for OPTIONBYTE_USER).
                                             This parameter can be a combination of @ref FLASH_OB_USER_TYPE */
  uint32_t USERConfig1;                 /*!< Value of the user option byte (used for OPTIONBYTE_USER).
                                             This parameter can be a combination of @ref FLASH_OB_USER_BOR_LEV,
                                             @ref FLASH_OB_USER_IWDG_SW, @ref FLASH_OB_USER_nRST_STOP,
                                             @ref FLASH_OB_USER_nRST_STDBY, @ref FLASH_OB_USER_XSPI1_HSLV,
                                             @ref FLASH_OB_USER_XSPI2_HSLV, @ref FLASH_OB_USER_IWDG_STOP,
                                             @ref FLASH_OB_USER_IWDG_STANDBY, @ref FLASH_OB_USER_VDDIO_HSLV */
  uint32_t USERConfig2;                 /*!< Value of the user option byte (used for OPTIONBYTE_USER).
                                             This parameter can be a combination of @ref FLASH_OB_USER_ITCM_AXI_SHARE,
                                             @ref FLASH_OB_USER_DTCM_AXI_SHARE, @ref FLASH_OB_USER_ECC_ON_SRAM,
                                             @ref FLASH_OB_USER_I2C_NI3C */
  uint32_t HDPStartPage;                /*!< Start address that contains the first 256-byte block of HDP area (used for OPTIONBYTE_HDP).
                                             This parameter must be a value between 0 or 0xFFF */
  uint32_t HDPEndPage;                  /*!< End address that contains the last 256-byte block of HDP area (used for OPTIONBYTE_HDP).
                                             This parameter must be a value between 0 or 0xFFF */
  uint32_t NVState;                     /*!< Value of the non-volatile state (used for OPTIONBYTE_NV).
                                             This parameter must be a value of @ref FLASH_OB_NVSTATE */
  uint32_t ROTConfig;                   /*!< Value of the RoT status (only used for read configuration).
                                             This parameter can be a combination of @ref FLASH_OB_ROT_OEM_PROVD,
                                             @ref FLASH_OB_ROT_DBG_AUTH, @ref FLASH_OB_ROT_IROT_SELECT */
  uint32_t EPOCH;                       /*!< Value of the epoch (only used for read configuration).
                                             This parameter must be a value between 0x0 and 0xFFFFFF */
} FLASH_OBProgramInitTypeDef;

/**
  * @brief  FLASH handle Structure definition
  */
typedef struct
{
  HAL_LockTypeDef        Lock;              /* FLASH locking object */
  uint32_t               ErrorCode;         /* FLASH error code */
  uint32_t               ProcedureOnGoing;  /* Internal variable to indicate which procedure is ongoing or not in IT
                                               context */
  uint32_t               Address;           /* Internal variable to save address selected for program in IT context */
  uint32_t               Sector;            /* Internal variable to define the current sector which is being erased in
                                               IT context */
  uint32_t               NbSectorsToErase;  /* Internal variable to save the remaining sectors to erase in IT context */
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
#define FLASH_FLAG_EOP               FLASH_ISR_EOPF        /*!< FLASH End of program flag */
#define FLASH_FLAG_WRPERR            FLASH_ISR_WRPERRF     /*!< FLASH Write protection error flag */
#define FLASH_FLAG_PGSERR            FLASH_ISR_PGSERRF     /*!< FLASH Programming sequence error flag */
#define FLASH_FLAG_STRBERR           FLASH_ISR_STRBERRF    /*!< FLASH Strobe error flag */
#define FLASH_FLAG_OBLERR            FLASH_ISR_OBLERRF     /*!< FLASH Option byte loading error flag */
#define FLASH_FLAG_INCERR            FLASH_ISR_INCERRF     /*!< FLASH Inconsistency error flag */
#define FLASH_FLAG_RDSERR            FLASH_ISR_RDSERRF     /*!< FLASH Read security error flag */
#define FLASH_FLAG_SNECCERR          FLASH_ISR_SNECCERRF   /*!< FLASH ECC single error flag */
#define FLASH_FLAG_DBECCERR          FLASH_ISR_DBECCERRF   /*!< FLASH ECC double error flag */
#define FLASH_FLAG_CRCEND            FLASH_ISR_CRCENDF     /*!< FLASH CRC end of calculation flag */
#define FLASH_FLAG_CRCERR            FLASH_ISR_CRCRDERRF   /*!< FLASH CRC error flag  */
#define FLASH_FLAG_KVERR             FLASH_OPTISR_KVEF     /*!< FLASH Key valid error flag */
#define FLASH_FLAG_KTERR             FLASH_OPTISR_KTEF     /*!< FLASH Key transfer error flag */
#define FLASH_FLAG_OPTERR            FLASH_OPTISR_OPTERRF  /*!< FLASH Options byte change error flag */

#define FLASH_FLAG_ISR_ERRORS        (FLASH_FLAG_WRPERR     | FLASH_FLAG_PGSERR   | FLASH_FLAG_STRBERR | \
                                      FLASH_FLAG_OBLERR     | FLASH_FLAG_INCERR   | FLASH_FLAG_RDSERR  | \
                                      FLASH_FLAG_CRCERR)
#define FLASH_FLAG_ECC_ERRORS        (FLASH_FLAG_SNECCERR   | FLASH_FLAG_DBECCERR)
#define FLASH_FLAG_OPTISR_ERRORS     (FLASH_FLAG_KVERR      | FLASH_FLAG_KTERR      | FLASH_FLAG_OPTERR)
#define FLASH_FLAG_ALL_ERRORS        (FLASH_FLAG_ISR_ERRORS | FLASH_FLAG_ECC_ERRORS | FLASH_FLAG_OPTISR_ERRORS)

#define FLASH_FLAG_ISR_FLAGS         (FLASH_FLAG_ISR_ERRORS | FLASH_FLAG_ECC_ERRORS | FLASH_FLAG_EOP)
/**
  * @}
  */

/** @defgroup FLASH_Interrupt_definition FLASH Interrupts Definition
  * @brief FLASH Interrupt definition
  * @{
  */
#define FLASH_IT_EOP                 FLASH_IER_EOPIE       /*!< End of program interrupt source */
#define FLASH_IT_WRPERR              FLASH_IER_WRPERRIE    /*!< FLASH Write protection error interrupt source */
#define FLASH_IT_PGSERR              FLASH_IER_PGSERRIE    /*!< FLASH Programming sequence error interrupt source */
#define FLASH_IT_STRBERR             FLASH_IER_STRBERRIE   /*!< FLASH Strobe error interrupt source */
#define FLASH_IT_OBLERR              FLASH_IER_OBLERRIE    /*!< FLASH Option byte loading error interrupt source */
#define FLASH_IT_INCERR              FLASH_IER_INCERRIE    /*!< FLASH Inconsistency error interrupt source */
#define FLASH_IT_RDSERR              FLASH_IER_RDSERRIE    /*!< FLASH Read security error interrupt source */
#define FLASH_IT_SNECCERR            FLASH_IER_SNECCERRIE  /*!< FLASH ECC single error interrupt source */
#define FLASH_IT_DBECCERR            FLASH_IER_DBECCERRIE  /*!< FLASH ECC double error interrupt source */
#define FLASH_IT_CRCEND              FLASH_IER_CRCENDIE    /*!< FLASH CRC end of calculation interrupt source */
#define FLASH_IT_CRCERR              FLASH_IER_CRCRDERRIE  /*!< FLASH CRC error interrupt source  */
#define FLASH_IT_KVERR               FLASH_OPTCR_KVEIE     /*!< FLASH Key valid error interrupt source */
#define FLASH_IT_KTERR               FLASH_OPTCR_KTEIE     /*!< FLASH Key transfer error interrupt source */
#define FLASH_IT_OPTERR              FLASH_OPTCR_OPTERRIE  /*!< FLASH Options byte change error interrupt source */

#define FLASH_IT_IER                 (FLASH_IT_EOP    | FLASH_IT_WRPERR | FLASH_IT_PGSERR   | FLASH_IT_STRBERR  | \
                                      FLASH_IT_OBLERR | FLASH_IT_INCERR | FLASH_IT_RDSERR | FLASH_IT_SNECCERR | \
                                      FLASH_IT_DBECCERR | FLASH_IT_CRCEND | FLASH_IT_CRCERR)
#define FLASH_IT_OPTCR               (FLASH_IT_KVERR  | FLASH_IT_KTERR    | FLASH_IT_OPTERR)
/**
  * @}
  */

/** @defgroup FLASH_Error FLASH Error
  * @{
  */
#define HAL_FLASH_ERROR_NONE         0x00000000U
#define HAL_FLASH_ERROR_WRP          FLASH_FLAG_WRPERR
#define HAL_FLASH_ERROR_PGS          FLASH_FLAG_PGSERR
#define HAL_FLASH_ERROR_STRB         FLASH_FLAG_STRBERR
#define HAL_FLASH_ERROR_OBL          FLASH_FLAG_OBLERR
#define HAL_FLASH_ERROR_INC          FLASH_FLAG_INCERR
#define HAL_FLASH_ERROR_RDS          FLASH_FLAG_RDSERR
#define HAL_FLASH_ERROR_SNECC        FLASH_FLAG_SNECCERR
#define HAL_FLASH_ERROR_DBECC        FLASH_FLAG_DBECCERR
#define HAL_FLASH_ERROR_CRC          FLASH_FLAG_CRCERR
#define HAL_FLASH_ERROR_KV           FLASH_FLAG_KVERR
#define HAL_FLASH_ERROR_KT           FLASH_FLAG_KTERR
#define HAL_FLASH_ERROR_OPT          FLASH_FLAG_OPTERR
/**
  * @}
  */

/** @defgroup FLASH_Type_Erase FLASH Erase Type
  * @{
  */
#define FLASH_TYPEERASE_SECTORS      FLASH_CR_SER  /*!< Sectors erase activation */
#define FLASH_TYPEERASE_MASSERASE    FLASH_CR_BER  /*!< Flash mass erase activation */
/**
  * @}
  */

/** @defgroup FLASH_Type_Program FLASH Program Type
  * @{
  */
#define FLASH_TYPEPROGRAM_BYTE         (FLASH_CR_PG | FLASH_CR_FW)                             /*!< Program a byte (8-bit) at a specified address */
#define FLASH_TYPEPROGRAM_HALFWORD     (FLASH_HALFWORD_MASK   | FLASH_CR_PG | FLASH_CR_FW)     /*!< Program a half-word (16-bit) at a specified address */
#define FLASH_TYPEPROGRAM_WORD         (FLASH_WORD_MASK       | FLASH_CR_PG | FLASH_CR_FW)     /*!< Program a word (32-bit) at a specified address */
#define FLASH_TYPEPROGRAM_DOUBLEWORD   (FLASH_DOUBLEWORD_MASK | FLASH_CR_PG | FLASH_CR_FW)     /*!< Program a double-word (64-bit) at a specified address */
#define FLASH_TYPEPROGRAM_QUADWORD     (FLASH_CR_PG)                                           /*!< Program a quad-word (128-bit) at a specified address */
#define FLASH_TYPEPROGRAM_OTP_HALFWORD (FLASH_HALFWORD_MASK   | FLASH_CR_PG_OTP | FLASH_CR_FW) /*!< Program a half-word (16-bit) at a OTP address */
#define FLASH_TYPEPROGRAM_OTP_WORD     (FLASH_WORD_MASK       | FLASH_CR_PG_OTP | FLASH_CR_FW) /*!< Program a word (32-bit) at a OTP address */
/**
  * @}
  */

/** @defgroup FLASH_OB_TYPE FLASH Option Bytes Type
  * @{
  */
#define OPTIONBYTE_WRP               0x00000001U   /*!< WRP option byte configuration */
#define OPTIONBYTE_USER              0x00000002U   /*!< User option byte configuration */
#define OPTIONBYTE_HDP               0x00000004U   /*!< HDP option byte configuration */
#define OPTIONBYTE_NV                0x00000008U   /*!< Non-Volatile State option byte configuration */
/**
  * @}
  */

/** @defgroup FLASH_OB_WRP_STATE FLASH Option Bytes WRP State
  * @{
  */
#define OB_WRPSTATE_DISABLE          0x00000000U  /*!< Disable the write protection of the desired sectors */
#define OB_WRPSTATE_ENABLE           0x00000001U  /*!< Enable the write protection of the desired sectors */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_TYPE FLASH Option Bytes User Type
  * @{
  */
#define OB_USER_BOR_LEV              0x00000001U     /*!< Brownout level */
#define OB_USER_IWDG_SW              0x00000002U     /*!< IWDG control mode */
#define OB_USER_NRST_STOP            0x00000004U     /*!< Stop entry reset */
#define OB_USER_NRST_STDBY           0x00000008U     /*!< Standby entry reset */
#define OB_USER_XSPI1_HSLV           0x00000010U     /*!< XSPI1 High-speed at low voltage */
#define OB_USER_XSPI2_HSLV           0x00000020U     /*!< XSPI2 High-speed at low voltage */
#define OB_USER_IWDG_STOP            0x00000040U     /*!< IWDG Stop mode freeze */
#define OB_USER_IWDG_STDBY           0x00000080U     /*!< IWDG Standby mode freeze */
#define OB_USER_VDDIO_HSLV           0x00000100U     /*!< I/O High-speed at low voltage */
#define OB_USER_ITCM_AXI_SHARE       0x00000200U     /*!< ITCM AXI share */
#define OB_USER_DTCM_AXI_SHARE       0x00000400U     /*!< DTCM AXI share */
#define OB_USER_SRAM_ECC             0x00000800U     /*!< ECC on SRAM */
#define OB_USER_I2C_NI3C             0x00001000U     /*!< I2C Not I3C */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_BOR_LEV FLASH Option Bytes User BOR Level
  * @{
  */
#define OB_BOR_LEVEL_0               0x00000000U                /*!< BOR OFF, POR/PDR reset threshold level is applied */
#define OB_BOR_LEVEL_1               FLASH_OBW1SRP_BOR_LEVEL_0  /*!< BOR Level 1, the threshold level is low (around 2.1 V) */
#define OB_BOR_LEVEL_2               FLASH_OBW1SRP_BOR_LEVEL_1  /*!< BOR Level 2, the threshold level is medium (around 2.4 V) */
#define OB_BOR_LEVEL_3               FLASH_OBW1SRP_BOR_LEVEL    /*!< BOR Level 3, the threshold level is high (around 2.7 V) */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IWDG_SW FLASH Option Bytes User IWDG control mode
  * @{
  */
#define OB_IWDG_HW                   0x00000000U             /*!< IWDG watchdog is controlled by hardware */
#define OB_IWDG_SW                   FLASH_OBW1SRP_IWDG_HW   /*!< IWDG watchdog is controlled by software */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_nRST_STOP FLASH Option Bytes User stop entry reset
  * @{
  */
#define OB_STOP_RST                  0x00000000U                 /*!< Reset generated when entering stop mode */
#define OB_STOP_NORST                FLASH_OBW1SRP_NRST_STOP     /*!< No reset generated when entering stop mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_nRST_STDBY FLASH Option Bytes User standby entry reset
  * @{
  */
#define OB_STANDBY_RST               0x00000000U                 /*!< Reset generated when entering standby mode */
#define OB_STANDBY_NORST             FLASH_OBW1SRP_NRST_STBY     /*!< No reset generated when entering standby mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_XSPI1_HSLV FLASH Option Bytes User XSPI 1 High-Speed at Low-Voltage
  * @{
  */
#define OB_XSPI1_HSLV_DISABLE        0x00000000U               /*!< I/O speed optimization at low-voltage disabled */
#define OB_XSPI1_HSLV_ENABLE         FLASH_OBW1SRP_XSPI1_HSLV  /*!< I/O speed optimization at low-voltage feature allowed */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_XSPI2_HSLV FLASH Option Bytes User XSPI 2 High-Speed at Low-Voltage
  * @{
  */
#define OB_XSPI2_HSLV_DISABLE        0x00000000U               /*!< I/O speed optimization at low-voltage disabled */
#define OB_XSPI2_HSLV_ENABLE         FLASH_OBW1SRP_XSPI2_HSLV  /*!< I/O speed optimization at low-voltage feature allowed */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IWDG_STOP FLASH Option Bytes User IWDG Stop Mode Freeze
  * @{
  */
#define OB_IWDG_STOP_FREEZE          0x00000000U                 /*!< Independent watchdog frozen in Stop mode */
#define OB_IWDG_STOP_RUN             FLASH_OBW1SRP_IWDG_FZ_STOP  /*!< Independent watchdog running in Stop mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IWDG_STANDBY FLASH Option Bytes User IWDG Standby Mode Freeze
  * @{
  */
#define OB_IWDG_STDBY_FREEZE         0x00000000U                 /*!< Independent watchdog frozen in Standby mode */
#define OB_IWDG_STDBY_RUN            FLASH_OBW1SRP_IWDG_FZ_STBY  /*!< Independent watchdog running in Standby mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_VDDIO_HSLV FLASH Option Bytes User I/O High-Speed at Low-Voltage
  * @{
  */
#define OB_VDDIO_HSLV_DISABLE        0x00000000U               /*!< I/O speed optimization at low-voltage disabled */
#define OB_VDDIO_HSLV_ENABLE         FLASH_OBW1SRP_VDDIO_HSLV  /*!< I/O speed optimization at low-voltage feature allowed */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_ITCM_AXI_SHARE FLASH Option Bytes User ITCM AXI share
  * @{
  */
#define OB_ITCM_AXI_SHARE_0          0x00000000U
#define OB_ITCM_AXI_SHARE_1          FLASH_OBW2SRP_ITCM_AXI_SHARE_0
#define OB_ITCM_AXI_SHARE_2          FLASH_OBW2SRP_ITCM_AXI_SHARE_1
#define OB_ITCM_AXI_SHARE_3          (FLASH_OBW2SRP_ITCM_AXI_SHARE_0 | FLASH_OBW2SRP_ITCM_AXI_SHARE_1)
#define OB_ITCM_AXI_SHARE_4          FLASH_OBW2SRP_ITCM_AXI_SHARE_2
#define OB_ITCM_AXI_SHARE_5          (FLASH_OBW2SRP_ITCM_AXI_SHARE_2 | FLASH_OBW2SRP_ITCM_AXI_SHARE_0)
#define OB_ITCM_AXI_SHARE_6          (FLASH_OBW2SRP_ITCM_AXI_SHARE_2 | FLASH_OBW2SRP_ITCM_AXI_SHARE_1)
#define OB_ITCM_AXI_SHARE_7          FLASH_OBW2SRP_ITCM_AXI_SHARE
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_DTCM_AXI_SHARE FLASH Option Bytes User DTCM AXI share
  * @{
  */
#define OB_DTCM_AXI_SHARE_0          0x00000000U
#define OB_DTCM_AXI_SHARE_1          FLASH_OBW2SRP_DTCM_AXI_SHARE_0
#define OB_DTCM_AXI_SHARE_2          FLASH_OBW2SRP_DTCM_AXI_SHARE_1
#define OB_DTCM_AXI_SHARE_3          (FLASH_OBW2SRP_DTCM_AXI_SHARE_0 | FLASH_OBW2SRP_DTCM_AXI_SHARE_1)
#define OB_DTCM_AXI_SHARE_4          FLASH_OBW2SRP_DTCM_AXI_SHARE_2
#define OB_DTCM_AXI_SHARE_5          (FLASH_OBW2SRP_DTCM_AXI_SHARE_2 | FLASH_OBW2SRP_DTCM_AXI_SHARE_0)
#define OB_DTCM_AXI_SHARE_6          (FLASH_OBW2SRP_DTCM_AXI_SHARE_2 | FLASH_OBW2SRP_DTCM_AXI_SHARE_1)
#define OB_DTCM_AXI_SHARE_7          FLASH_OBW2SRP_DTCM_AXI_SHARE
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_ECC_ON_SRAM FLASH Option Bytes User ECC on sRAM
  * @{
  */
#define OB_AXISRAM_ECC_DISABLE       0x00000000U                /*!< AXISRAM ECC check disable */
#define OB_AXISRAM_ECC_ENABLE        FLASH_OBW2SRP_ECC_ON_SRAM  /*!< AXISRAM ECC check enable */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_I2C_NI3C FLASH Option Bytes User I2C Not I3C
  * @{
  */
#define OB_I2C_NI3C_I2C              FLASH_OBW2SRP_I2C_NI3C
#define OB_I2C_NI3C_I3C              0x00000000U
/**
  * @}
  */

/** @defgroup FLASH_OB_NVSTATE FLASH Option Bytes Non-volatile state
  * @{
  */
#define OB_NVSTATE_OPEN              (uint8_t)0xB4
#define OB_NVSTATE_CLOSE             (uint8_t)0x51
/**
  * @}
  */

/** @defgroup FLASH_OB_ROT_OEM_PROVD FLASH Option Bytes Root-Of-Trust OEM Provisioned state
  * @{
  */
#define OB_OEM_PROVD_ENABLE          (0xB4UL << FLASH_ROTSR_OEM_PROVD_Pos) /*!< Device is in OEM provisioned state */
#define OB_OEM_PROVD_DEFAULT         (0x6AUL << FLASH_ROTSR_OEM_PROVD_Pos) /*!< Device is not in OEM provisioned state (default value)*/
/**
  * @}
  */

/** @defgroup FLASH_OB_ROT_DBG_AUTH FLASH Option Bytes Root-Of-Trust Debug authentication method
  * @{
  */
#define OB_DBG_AUTH_LOCKED           (0xB4UL << FLASH_ROTSR_DBG_AUTH_Pos) /*!< Locked device (no debug allowed) */
#define OB_DBG_AUTH_ECDSA_SIGN       (0x51UL << FLASH_ROTSR_DBG_AUTH_Pos) /*!< Authentication method using ECDSA signature (NISTP256) */
#define OB_DBG_AUTH_PASSWORD         (0x8AUL << FLASH_ROTSR_DBG_AUTH_Pos) /*!< Authentication method using password */
#define OB_DBG_AUTH_DEFAULT          (0xFFUL << FLASH_ROTSR_DBG_AUTH_Pos) /*!< No authentication method selected (default value) */
/**
  * @}
  */

/** @defgroup FLASH_OB_ROT_IROT_SELECT FLASH Option Bytes iRoT selection
  * @{
  */
#define OB_IROT_SELECTION_ST         (0xB4UL << FLASH_ROTSR_IROT_SELECT_Pos) /*!< ST iRoT is selected at boot */
#define OB_IROT_SELECTION_OEM        (0x6AUL << FLASH_ROTSR_IROT_SELECT_Pos) /*!< OEM iRoT is selected at boot */
/**
  * @}
  */

/** @defgroup FLASH_Latency FLASH Latency
  * @{
  */
#define FLASH_LATENCY_0        0U                                                                                       /*!< FLASH Zero wait state      */
#define FLASH_LATENCY_1        FLASH_ACR_LATENCY_0                                                                      /*!< FLASH One wait state       */
#define FLASH_LATENCY_2        (FLASH_ACR_LATENCY_1 | FLASH_ACR_WRHIGHFREQ_0)                                           /*!< FLASH Two wait states      */
#define FLASH_LATENCY_3        (FLASH_ACR_LATENCY_1 | FLASH_ACR_LATENCY_0 | FLASH_ACR_WRHIGHFREQ_0)                     /*!< FLASH Three wait states    */
#define FLASH_LATENCY_4        (FLASH_ACR_LATENCY_2 | FLASH_ACR_WRHIGHFREQ_1)                                           /*!< FLASH Four wait states     */
#define FLASH_LATENCY_5        (FLASH_ACR_LATENCY_2 | FLASH_ACR_LATENCY_0 | FLASH_ACR_WRHIGHFREQ_1)                     /*!< FLASH Five wait states     */
#define FLASH_LATENCY_6        (FLASH_ACR_LATENCY_2 | FLASH_ACR_LATENCY_1 | FLASH_ACR_WRHIGHFREQ)                       /*!< FLASH Six wait state       */
#define FLASH_LATENCY_7        (FLASH_ACR_LATENCY_2 | FLASH_ACR_LATENCY_1 | FLASH_ACR_LATENCY_0 | FLASH_ACR_WRHIGHFREQ) /*!< FLASH Seven wait states    */
#define FLASH_LATENCY_8        (FLASH_ACR_LATENCY_3 | FLASH_ACR_WRHIGHFREQ)                                             /*!< FLASH Eight wait states    */
#define FLASH_LATENCY_9        (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_0 | FLASH_ACR_WRHIGHFREQ)                       /*!< FLASH Nine wait states     */
#define FLASH_LATENCY_10       (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_1 | FLASH_ACR_WRHIGHFREQ)                       /*!< FLASH Ten wait states      */
#define FLASH_LATENCY_11       (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_1 | FLASH_ACR_LATENCY_0 | FLASH_ACR_WRHIGHFREQ) /*!< FLASH Eleven wait states   */
#define FLASH_LATENCY_12       (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_2 | FLASH_ACR_WRHIGHFREQ)                       /*!< FLASH Twelve wait states   */
#define FLASH_LATENCY_13       (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_2 | FLASH_ACR_LATENCY_0 | FLASH_ACR_WRHIGHFREQ) /*!< FLASH Thirteen wait states */
#define FLASH_LATENCY_14       (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_2 | FLASH_ACR_LATENCY_1 | FLASH_ACR_WRHIGHFREQ) /*!< FLASH Fourteen wait states */
#define FLASH_LATENCY_15       (FLASH_ACR_LATENCY   | FLASH_ACR_WRHIGHFREQ)                                               /*!< FLASH Fifteen wait states  */
/**
  * @}
  */

/** @defgroup FLASH_Keys FLASH Keys
  * @{
  */
#define FLASH_KEY1                   0x45670123U /*!< Flash key1 */
#define FLASH_KEY2                   0xCDEF89ABU /*!< Flash key2: used with FLASH_KEY1
                                                      to unlock the FLASH registers access */

#define FLASH_OPTKEY1                0x08192A3BU /*!< Flash option byte key1 */
#define FLASH_OPTKEY2                0x4C5D6E7FU /*!< Flash option byte key2: used with FLASH_OPTKEY1
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
#define __HAL_FLASH_SET_LATENCY(__LATENCY__) MODIFY_REG(FLASH->ACR, (FLASH_ACR_LATENCY |\
                                                                     FLASH_ACR_WRHIGHFREQ), (__LATENCY__))

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
#define __HAL_FLASH_GET_LATENCY() READ_BIT(FLASH->ACR, (FLASH_ACR_LATENCY | FLASH_ACR_WRHIGHFREQ))

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
  *     @arg FLASH_IT_EOP: End of program interrupt
  *     @arg FLASH_IT_WRPERR: Write protection error interrupt
  *     @arg FLASH_IT_PGSERR: Programming sequence error interrupt
  *     @arg FLASH_IT_STRBERR: Strobe error interrupt
  *     @arg FLASH_IT_OBLERR: Option byte loading error interrupt
  *     @arg FLASH_IT_INCERR: Inconsistency error interrupt
  *     @arg FLASH_IT_RDSERR: Read security error interrupt
  *     @arg FLASH_IT_SNECCERR: ECC single error interrupt
  *     @arg FLASH_IT_DBECCERR: ECC double error interrupt
  *     @arg FLASH_IT_CRCEND: CRC end of calculation interrupt
  *     @arg FLASH_IT_CRCERR: CRC error interrupt
  *     @arg FLASH_IT_KVERR: Key valid error interrupt
  *     @arg FLASH_IT_KTERR: Key transfer error interrupt
  *     @arg FLASH_IT_OPTERR: Options byte change error interrupt
  * @retval none
  */
#define __HAL_FLASH_ENABLE_IT(__INTERRUPT__) do { if(((__INTERRUPT__) & FLASH_IT_IER) != 0U)\
                                                  { SET_BIT(FLASH->IER, ((__INTERRUPT__) & FLASH_IT_IER)); }\
                                                  if(((__INTERRUPT__) & FLASH_IT_OPTCR) != 0U)\
                                                  { SET_BIT(FLASH->OPTCR, ((__INTERRUPT__) & FLASH_IT_OPTCR)); }\
                                                } while(0)

/**
  * @brief  Disable the specified FLASH interrupt.
  * @param  __INTERRUPT__ FLASH interrupt
  *         This parameter can be any combination of the following values:
  *     @arg FLASH_IT_EOP: End of program interrupt
  *     @arg FLASH_IT_WRPERR: Write protection error interrupt
  *     @arg FLASH_IT_PGSERR: Programming sequence error interrupt
  *     @arg FLASH_IT_STRBERR: Strobe error interrupt
  *     @arg FLASH_IT_OBLERR: Option byte loading error interrupt
  *     @arg FLASH_IT_INCERR: Inconsistency error interrupt
  *     @arg FLASH_IT_RDSERR: Read security error interrupt
  *     @arg FLASH_IT_SNECCERR: ECC single error interrupt
  *     @arg FLASH_IT_DBECCERR: ECC double error interrupt
  *     @arg FLASH_IT_CRCEND: CRC end of calculation interrupt
  *     @arg FLASH_IT_CRCERR: CRC error interrupt
  *     @arg FLASH_IT_KVERR: Key valid error interrupt
  *     @arg FLASH_IT_KTERR: Key transfer error interrupt
  *     @arg FLASH_IT_OPTERR: Options byte change error interrupt
  * @retval none
  */
#define __HAL_FLASH_DISABLE_IT(__INTERRUPT__) do { if(((__INTERRUPT__) & FLASH_IT_IER) != 0U)\
                                                   { CLEAR_BIT(FLASH->IER, ((__INTERRUPT__) & FLASH_IT_IER)); }\
                                                   if(((__INTERRUPT__) & FLASH_IT_OPTCR) != 0U)\
                                                   { CLEAR_BIT(FLASH->OPTCR, ((__INTERRUPT__) & FLASH_IT_OPTCR)); }\
                                                 } while(0)

/**
  * @brief  Check whether the specified FLASH flag is set or not.
  * @param  __FLAG__ specifies the FLASH flag to check.
  *   This parameter can be one of the following values:
  *     @arg FLASH_FLAG_EOP: FLASH End of program flag
  *     @arg FLASH_FLAG_WRPERR: FLASH Write protection error flag
  *     @arg FLASH_FLAG_PGSERR: FLASH Programming sequence error flag
  *     @arg FLASH_FLAG_STRBERR: FLASH Strobe error flag
  *     @arg FLASH_FLAG_OBLERR: FLASH Option byte loading error flag
  *     @arg FLASH_FLAG_INCERR: FLASH Inconsistency error flag
  *     @arg FLASH_FLAG_RDSERR: FLASH Read security error flag
  *     @arg FLASH_FLAG_SNECCERR: FLASH ECC single error flag
  *     @arg FLASH_FLAG_DBECCERR: FLASH ECC double error flag
  *     @arg FLASH_FLAG_CRCEND: FLASH CRC end of calculation flag
  *     @arg FLASH_FLAG_CRCERR: FLASH CRC error flag
  *     @arg FLASH_FLAG_KVERR: FLASH Key valid error flag
  *     @arg FLASH_FLAG_KTERR: FLASH Key transfer error flag
  *     @arg FLASH_FLAG_OPTERR: FLASH Options byte change error flag
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
#define __HAL_FLASH_GET_FLAG(__FLAG__) ((((__FLAG__) & FLASH_FLAG_OPTISR_ERRORS) != 0U) ? \
                                        (READ_BIT(FLASH->OPTISR, (__FLAG__)) == (__FLAG__)) : \
                                        (READ_BIT(FLASH->ISR, (__FLAG__)) == (__FLAG__)))

/**
  * @brief  Clear the FLASH's pending flags.
  * @param  __FLAG__ specifies the FLASH flags to clear.
  *   This parameter can be any combination of the following values:
  *     @arg FLASH_FLAG_EOP: FLASH End of program flag
  *     @arg FLASH_FLAG_WRPERR: FLASH Write protection error flag
  *     @arg FLASH_FLAG_PGSERR: FLASH Programming sequence error flag
  *     @arg FLASH_FLAG_STRBERR: FLASH Strobe error flag
  *     @arg FLASH_FLAG_OBLERR: FLASH Option byte loading error flag
  *     @arg FLASH_FLAG_INCERR: FLASH Inconsistency error flag
  *     @arg FLASH_FLAG_RDSERR: FLASH Read security error flag
  *     @arg FLASH_FLAG_SNECCERR: FLASH ECC single error flag
  *     @arg FLASH_FLAG_DBECCERR: FLASH ECC double error flag
  *     @arg FLASH_FLAG_CRCEND: FLASH CRC end of calculation flag
  *     @arg FLASH_FLAG_CRCERR: FLASH CRC error flag
  *     @arg FLASH_FLAG_KVERR: FLASH Key valid error flag
  *     @arg FLASH_FLAG_KTERR: FLASH Key transfer error flag
  *     @arg FLASH_FLAG_OPTERR: FLASH Options byte change error flag
  * @retval None
  */
#define __HAL_FLASH_CLEAR_FLAG(__FLAG__) do { if(((__FLAG__) & FLASH_FLAG_OPTISR_ERRORS) != 0U)\
                                              { WRITE_REG(FLASH->OPTICR, ((__FLAG__) & FLASH_FLAG_OPTISR_ERRORS)); }\
                                              if(((__FLAG__) & FLASH_FLAG_ISR_FLAGS) != 0U)\
                                              { WRITE_REG(FLASH->ICR, ((__FLAG__) & FLASH_FLAG_ISR_FLAGS)); }\
                                            } while(0)
/**
  * @}
  */

/* Include FLASH HAL Extended module */
#include "stm32h7rsxx_hal_flash_ex.h"


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
#define FLASH_BANK_SIZE                 FLASH_SIZE

#define FLASH_SECTOR_NB                 8U

#define FLASH_SECTOR_SIZE               0x2000UL  /* 8 KB */

#define FLASH_HDP_BLOCK_NB              0x100U

#define FLASH_TIMEOUT_VALUE             1000U   /* 1 s */

#define FLASH_BYTE_MASK                 0x00000000U
#define FLASH_HALFWORD_MASK             0x40000000U
#define FLASH_WORD_MASK                 0x80000000U
#define FLASH_DOUBLEWORD_MASK           0xC0000000U
#define FLASH_WORD_SIZE_MASK            FLASH_DOUBLEWORD_MASK
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup FLASH_Private_Macros FLASH Private Macros
  *  @{
  */
#define IS_FLASH_TYPEERASE(VALUE)          (((VALUE) == FLASH_TYPEERASE_SECTORS) ||\
                                            ((VALUE) == FLASH_TYPEERASE_MASSERASE))

#define IS_FLASH_TYPEPROGRAM(VALUE)        (((VALUE) == FLASH_TYPEPROGRAM_BYTE)         ||\
                                            ((VALUE) == FLASH_TYPEPROGRAM_HALFWORD)     ||\
                                            ((VALUE) == FLASH_TYPEPROGRAM_WORD)         ||\
                                            ((VALUE) == FLASH_TYPEPROGRAM_DOUBLEWORD)   ||\
                                            ((VALUE) == FLASH_TYPEPROGRAM_QUADWORD)     ||\
                                            ((VALUE) == FLASH_TYPEPROGRAM_OTP_HALFWORD) ||\
                                            ((VALUE) == FLASH_TYPEPROGRAM_OTP_WORD))

#define IS_FLASH_MAIN_MEM_ADDRESS(ADDRESS) (((ADDRESS) >= FLASH_BASE) && ((ADDRESS) < (FLASH_BASE+FLASH_SIZE)))

#define IS_FLASH_OTP_ADDRESS(ADDRESS)      (((ADDRESS) >= OTP_AREA_BASE) && ((ADDRESS) < (OTP_AREA_BASE + OTP_SIZE)))

#define IS_FLASH_PROGRAM_ADDRESS(ADDRESS)  ((IS_FLASH_MAIN_MEM_ADDRESS(ADDRESS)) || (IS_FLASH_OTP_ADDRESS(ADDRESS)))

#define IS_FLASH_SECTOR(SECTOR)            ((SECTOR) < FLASH_SECTOR_NB)

#define IS_OPTIONBYTE(VALUE)               (((VALUE) <= (OPTIONBYTE_WRP |\
                                                         OPTIONBYTE_USER | OPTIONBYTE_HDP | OPTIONBYTE_NV)))

#define IS_OB_WRPSTATE(VALUE)              (((VALUE) == OB_WRPSTATE_DISABLE) || ((VALUE) == OB_WRPSTATE_ENABLE))

#define IS_OB_USER_TYPE(TYPE)              (((TYPE) <= 0x1FFFU) && ((TYPE) != 0U))

#define IS_OB_USER_BOR_LEVEL(LEVEL)        (((LEVEL) == OB_BOR_LEVEL_0) || ((LEVEL) == OB_BOR_LEVEL_1) || \
                                            ((LEVEL) == OB_BOR_LEVEL_2) || ((LEVEL) == OB_BOR_LEVEL_3))

#define IS_OB_USER_IWDG(VALUE)             (((VALUE) == OB_IWDG_HW) || ((VALUE) == OB_IWDG_SW))

#define IS_OB_USER_STOP(VALUE)             (((VALUE) == OB_STOP_RST) || ((VALUE) == OB_STOP_NORST))

#define IS_OB_USER_STANDBY(VALUE)          (((VALUE) == OB_STANDBY_RST) || ((VALUE) == OB_STANDBY_NORST))

#define IS_OB_USER_XSPI1_HSLV(VALUE)       (((VALUE) == OB_XSPI1_HSLV_DISABLE) || ((VALUE) == OB_XSPI1_HSLV_ENABLE))

#define IS_OB_USER_XSPI2_HSLV(VALUE)       (((VALUE) == OB_XSPI2_HSLV_DISABLE) || ((VALUE) == OB_XSPI2_HSLV_ENABLE))

#define IS_OB_USER_IWDG_STOP(VALUE)        (((VALUE) == OB_IWDG_STOP_FREEZE) || ((VALUE) == OB_IWDG_STOP_RUN))

#define IS_OB_USER_IWDG_STDBY(VALUE)       (((VALUE) == OB_IWDG_STDBY_FREEZE) || ((VALUE) == OB_IWDG_STDBY_RUN))

#define IS_OB_USER_VDDIO_HSLV(VALUE)       (((VALUE) == OB_VDDIO_HSLV_DISABLE) || ((VALUE) == OB_VDDIO_HSLV_ENABLE))

#define IS_OB_USER_ITCM_AXI_SHARE(VALUE)   (((VALUE) == OB_ITCM_AXI_SHARE_0) || ((VALUE) == OB_ITCM_AXI_SHARE_1) || \
                                            ((VALUE) == OB_ITCM_AXI_SHARE_2) || ((VALUE) == OB_ITCM_AXI_SHARE_3) || \
                                            ((VALUE) == OB_ITCM_AXI_SHARE_4) || ((VALUE) == OB_ITCM_AXI_SHARE_5) || \
                                            ((VALUE) == OB_ITCM_AXI_SHARE_6) || ((VALUE) == OB_ITCM_AXI_SHARE_7))

#define IS_OB_USER_DTCM_AXI_SHARE(VALUE)   (((VALUE) == OB_DTCM_AXI_SHARE_0) || ((VALUE) == OB_DTCM_AXI_SHARE_1) || \
                                            ((VALUE) == OB_DTCM_AXI_SHARE_2) || ((VALUE) == OB_DTCM_AXI_SHARE_3) || \
                                            ((VALUE) == OB_DTCM_AXI_SHARE_4) || ((VALUE) == OB_DTCM_AXI_SHARE_5) || \
                                            ((VALUE) == OB_DTCM_AXI_SHARE_6) || ((VALUE) == OB_DTCM_AXI_SHARE_7))

#define IS_OB_USER_AXISRAM_ECC(VALUE)      (((VALUE) == OB_AXISRAM_ECC_ENABLE) || ((VALUE) == OB_AXISRAM_ECC_DISABLE))

#define IS_OB_USER_I2C_NI3C(VALUE)         (((VALUE) == OB_I2C_NI3C_I2C) || ((VALUE) == OB_I2C_NI3C_I3C))

#define IS_OB_HDP_PAGE(PAGE)               ((PAGE) < FLASH_HDP_BLOCK_NB)

#define IS_OB_NVSTATE(VALUE)               (((VALUE) == OB_NVSTATE_OPEN) || ((VALUE) ==OB_NVSTATE_CLOSE))

#define IS_OB_ROT_TYPE(VALUE)              ((VALUE) <= 0x7U)

#define IS_OB_OEM_PROVD(VALUE)             ((VALUE) <= 0x000000FFU)

#define IS_OB_DBG_AUTH(VALUE)              ((VALUE) <= 0x0000FF00U)

#define IS_OB_IROT_SELECT(VALUE)           ((VALUE) <= 0xFF000000U)

#define IS_OB_EPOCH(VALUE)                 ((VALUE) <= 0xFFFFFFU)

#define IS_FLASH_LATENCY(LATENCY)          (((LATENCY) == FLASH_LATENCY_0)  || ((LATENCY) == FLASH_LATENCY_1) || \
                                            ((LATENCY) == FLASH_LATENCY_2)  || ((LATENCY) == FLASH_LATENCY_3) || \
                                            ((LATENCY) == FLASH_LATENCY_4)  || ((LATENCY) == FLASH_LATENCY_5) || \
                                            ((LATENCY) == FLASH_LATENCY_6)  || ((LATENCY) == FLASH_LATENCY_7) || \
                                            ((LATENCY) == FLASH_LATENCY_8)  || ((LATENCY) == FLASH_LATENCY_9) || \
                                            ((LATENCY) == FLASH_LATENCY_10) || ((LATENCY) == FLASH_LATENCY_11) || \
                                            ((LATENCY) == FLASH_LATENCY_12) || ((LATENCY) == FLASH_LATENCY_13) || \
                                            ((LATENCY) == FLASH_LATENCY_14) || ((LATENCY) == FLASH_LATENCY_15))

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @addtogroup FLASH_Private_Functions
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

#endif /* STM32H7RSxx_HAL_FLASH_H */
