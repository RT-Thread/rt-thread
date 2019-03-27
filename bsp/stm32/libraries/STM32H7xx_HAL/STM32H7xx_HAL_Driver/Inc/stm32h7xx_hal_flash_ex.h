/**
  ******************************************************************************
  * @file    stm32H7xx_hal_flash_ex.h
  * @author  MCD Application Team
  * @brief   Header file of FLASH HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32H7xx_HAL_FLASH_EX_H
#define __STM32H7xx_HAL_FLASH_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal_def.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @addtogroup FLASHEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup FLASHEx_Exported_Types FLASH Exported Types
  * @{
  */

/**
  * @brief  FLASH Erase structure definition
  */
typedef struct
{
  uint32_t TypeErase;   /*!< Mass erase or sector Erase.
                             This parameter can be a value of @ref FLASHEx_Type_Erase */

  uint32_t Banks;       /*!< Select banks to erase when Mass erase is enabled.
                             This parameter must be a value of @ref FLASHEx_Banks */
  
  uint32_t Sector;      /*!< Initial FLASH sector to erase when Mass erase is disabled
                             This parameter must be a value of @ref FLASH_Sectors */

  uint32_t NbSectors;   /*!< Number of sectors to be erased.
                             This parameter must be a value between 1 and (max number of sectors - value of Initial sector)*/

  uint32_t VoltageRange;/*!< The device voltage range which defines the erase parallelism
                             This parameter must be a value of @ref FLASHEx_Voltage_Range */

} FLASH_EraseInitTypeDef;


/**
  * @brief  FLASH Option Bytes Program structure definition
  */
typedef struct
{
  uint32_t OptionType;   /*!< Option byte to be configured.
                              This parameter can be a value of @ref FLASHEx_Option_Type */

  uint32_t WRPState;     /*!< Write protection activation or deactivation.
                              This parameter can be a value of @ref FLASHEx_WRP_State */

  uint32_t WRPSector;    /*!< Specifies the sector(s) to be write protected.
                              The value of this parameter depend on device used within the same series */

  uint32_t RDPLevel;     /*!< Set the read protection level.
                              This parameter can be a value of @ref FLASHEx_Option_Bytes_Read_Protection */

  uint32_t BORLevel;     /*!< Set the BOR Level.
                              This parameter can be a value of @ref FLASHEx_BOR_Reset_Level */

  uint32_t USERType;       /*!< User option byte(s) to be configured (used for OPTIONBYTE_USER).
                                This parameter can be a combination of @ref FLASHEx_OB_USER_Type */

  uint32_t USERConfig;   /*!< Program the FLASH User Option Byte: WWDG_SW / IWDG_SW / RST_STOP / RST_STDBY / 
                              IWDG_FREEZE_STOP / IWDG_FREEZE_SANDBY. */
  uint32_t Banks;          /*!< Select banks for WRP , PCROP and secure area config .
                                This parameter must be a value of @ref FLASHEx_Banks */ 
  uint32_t PCROPConfig;    /*!< specifies if the PCROP area shall be erased or not 
                                when RDP level decreased from Level 1 to Level 0 or during a mass erase.
                                This parameter must be a value of @ref FLASHEx_OB_PCROP_RDP enumeration */

  uint32_t PCROPStartAddr; /*!< PCROP Start address (used for OPTIONBYTE_PCROP).
                                This parameter must be a value between begin and end of a bank */
                
  uint32_t PCROPEndAddr;   /*!< PCROP End address (used for OPTIONBYTE_PCROP).
                                This parameter must be a value between PCROP Start address and end of a bank */

  uint32_t BootConfig;  /*!< Specifies if the Boot Address to be configured BOOT_ADD0, BOOT_ADD1 
                                or both. This parameter must be a value of @ref FLASHEx_OB_BOOT_OPTION enumeration */

  uint32_t BootAddr0;   /*!< Boot Address 0.
                                This parameter must be a value between begin and end of a bank */

  uint32_t BootAddr1;   /*!< Boot Address 1.
                                This parameter must be a value between begin and end of a bank */
  
  uint32_t SecureAreaConfig;  /*!< specifies if the bank secured area shall be erased or not 
                                   when RDP level decreased from Level 1 to Level 0 or during a mass erase.
                                   This parameter must be a value of @ref FLASHEx_OB_SECURE_RDP enumeration */

  uint32_t SecureAreaStartAddr; /*!< Bank Secure area Start address.
                                     This parameter must be a value between begin and end of bank1 */
                
  uint32_t SecureAreaEndAddr;   /*!< Bank Secure area End address .
                                     This parameter must be a value between Start address and end of a bank1 */

} FLASH_OBProgramInitTypeDef;

/**
  * @}
  */
/* Exported constants --------------------------------------------------------*/

/** @defgroup FLASHEx_Exported_Constants FLASH Exported Constants
  * @{
  */

/** @defgroup FLASHEx_Type_Erase FLASH Type Erase
  * @{
  */ 
#define FLASH_TYPEERASE_SECTORS         ((uint32_t)0x00U)  /*!< Sectors erase only          */
#define FLASH_TYPEERASE_MASSERASE       ((uint32_t)0x01U)  /*!< Flash Mass erase activation */
/**
  * @}
  */
  
/** @defgroup FLASHEx_Voltage_Range FLASH Voltage Range
  * @{
  */ 
#define FLASH_VOLTAGE_RANGE_1        ((uint32_t)0x00U)             /*!< Flash program/erase by 8 bits    */
#define FLASH_VOLTAGE_RANGE_2        ((uint32_t)FLASH_CR_PSIZE_0)  /*!< Flash program/erase by 16 bits   */
#define FLASH_VOLTAGE_RANGE_3        ((uint32_t)FLASH_CR_PSIZE_1)  /*!< Flash program/erase by 32 bits   */
#define FLASH_VOLTAGE_RANGE_4        ((uint32_t)FLASH_CR_PSIZE)    /*!< Flash program/erase by 64 bits   */

/**
  * @}
  */
  
/** @defgroup FLASHEx_WRP_State FLASH WRP State
  * @{
  */ 
#define OB_WRPSTATE_DISABLE       ((uint32_t)0x00U)  /*!< Disable the write protection of the desired bank 1 sectors */
#define OB_WRPSTATE_ENABLE        ((uint32_t)0x01U)  /*!< Enable the write protection of the desired bank 1 sectors  */
/**
  * @}
  */
  
/** @defgroup FLASHEx_Option_Type FLASH Option Type
  * @{
  */ 
#define OPTIONBYTE_WRP           ((uint32_t)0x01U)  /*!< WRP option byte configuration  */
#define OPTIONBYTE_RDP           ((uint32_t)0x02U)  /*!< RDP option byte configuration  */
#define OPTIONBYTE_USER          ((uint32_t)0x04U)  /*!< USER option byte configuration */
#define OPTIONBYTE_PCROP         ((uint32_t)0x08U)  /*!< PCROP option byte configuration */
#define OPTIONBYTE_BOR           ((uint32_t)0x10U)  /*!< BOR option byte configuration */
#define OPTIONBYTE_SECURE_AREA   ((uint32_t)0x20U)  /*!< secure area option byte configuration */
#define OPTIONBYTE_BOOTADD       ((uint32_t)0x40U)  /*!< BOOT ADD option byte configuration */
/**
  * @}
  */
  
/** @defgroup FLASHEx_Option_Bytes_Read_Protection FLASH Option Bytes Read Protection
  * @{
  */
#define OB_RDP_LEVEL_0       ((uint32_t)0xAA00U)
#define OB_RDP_LEVEL_1       ((uint32_t)0x5500U)
#define OB_RDP_LEVEL_2       ((uint32_t)0xCC00U)   /*!< Warning: When enabling read protection level 2 
                                                        it s no more possible to go back to level 1 or 0 */
/**
  * @}
  */ 
  
/** @defgroup FLASHEx_Option_Bytes_WWatchdog FLASH Option Bytes WWatchdog
  * @{
  */ 
#define OB_WWDG_SW           ((uint32_t)0x10U)  /*!< Software WWDG selected */
#define OB_WWDG_HW           ((uint32_t)0x00U)  /*!< Hardware WWDG selected */
/**
  * @}
  */ 
  

/** @defgroup FLASHEx_Option_Bytes_IWatchdog FLASH Option Bytes IWatchdog
  * @{
  */ 
#define OB_IWDG_SW           ((uint32_t)0x20U)  /*!< Software IWDG selected */
#define OB_IWDG_HW           ((uint32_t)0x00U)  /*!< Hardware IWDG selected */
/**
  * @}
  */ 

/** @defgroup FLASHEx_Option_Bytes_nRST_STOP FLASH Option Bytes nRST_STOP
  * @{
  */ 
#define OB_STOP_NO_RST       ((uint32_t)0x40U) /*!< No reset generated when entering in STOP */
#define OB_STOP_RST          ((uint32_t)0x00U) /*!< Reset generated when entering in STOP    */
/**
  * @}
  */ 

/** @defgroup FLASHEx_Option_Bytes_nRST_STDBY FLASH Option Bytes nRST_STDBY
  * @{
  */                               
#define OB_STDBY_NO_RST      ((uint32_t)0x80U) /*!< No reset generated when entering in STANDBY */
#define OB_STDBY_RST         ((uint32_t)0x00U) /*!< Reset generated when entering in STANDBY    */
/**
  * @}
  */

/** @defgroup FLASHEx_Option_Bytes_IWDG_FREEZE_STOP FLASH IWDG Counter Freeze in STOP
  * @{
  */
#define OB_IWDG_STOP_FREEZE      ((uint32_t)0x00000000U) /*!< Freeze IWDG counter in STOP mode */
#define OB_IWDG_STOP_ACTIVE      ((uint32_t)FLASH_OPTSR_FZ_IWDG_STOP) /*!< IWDG counter active in STOP mode */
/**
  * @}
  */

/** @defgroup FLASHEx_Option_Bytes_IWDG_FREEZE_SANDBY FLASH IWDG Counter Freeze in STANDBY
  * @{
  */
#define OB_IWDG_STDBY_FREEZE      ((uint32_t)0x00000000U) /*!< Freeze IWDG counter in STANDBY mode */
#define OB_IWDG_STDBY_ACTIVE      ((uint32_t)FLASH_OPTSR_FZ_IWDG_SDBY)  /*!< IWDG counter active in STANDBY mode */
/**
  * @}
  */

/** @defgroup FLASHEx_BOR_Reset_Level FLASH BOR Reset Level
  * @{
  */
#define OB_BOR_LEVEL3          ((uint32_t)0x00U)  /*!< Supply voltage ranges from 2.70 to 3.60 V */
#define OB_BOR_LEVEL2          ((uint32_t)0x04U)  /*!< Supply voltage ranges from 2.40 to 2.70 V */
#define OB_BOR_LEVEL1          ((uint32_t)0x08U)  /*!< Supply voltage ranges from 2.10 to 2.40 V */
#define OB_BOR_OFF             ((uint32_t)0x0CU)  /*!< Supply voltage ranges from 1.62 to 2.10 V */
/**
  * @}
  */



/** @defgroup FLASHEx_Boot_Address FLASH Boot Address
  * @{
  */
#define OB_BOOTADDR_ITCM_RAM         ((uint32_t)0x0000U)  /*!< Boot from ITCM RAM (0x00000000)                 */
#define OB_BOOTADDR_SYSTEM           ((uint32_t)0x0040U)  /*!< Boot from System memory bootloader (0x00100000) */
#define OB_BOOTADDR_ITCM_FLASH       ((uint32_t)0x0080U)  /*!< Boot from Flash on ITCM interface (0x00200000)  */
#define OB_BOOTADDR_AXIM_FLASH       ((uint32_t)0x2000U)  /*!< Boot from Flash on AXIM interface (0x08000000)  */
#define OB_BOOTADDR_DTCM_RAM         ((uint32_t)0x8000U)  /*!< Boot from DTCM RAM (0x20000000)                 */
#define OB_BOOTADDR_SRAM1            ((uint32_t)0x8004U)  /*!< Boot from SRAM1 (0x20010000)                    */
#define OB_BOOTADDR_SRAM2            ((uint32_t)0x8013U)  /*!< Boot from SRAM2 (0x2004C000)                    */
/**
  * @}
  */
  
/** @defgroup FLASH_Latency FLASH Latency
  * @{
  */
#define FLASH_LATENCY_0                FLASH_ACR_LATENCY_0WS   /*!< FLASH Zero Latency cycle      */
#define FLASH_LATENCY_1                FLASH_ACR_LATENCY_1WS   /*!< FLASH One Latency cycle       */
#define FLASH_LATENCY_2                FLASH_ACR_LATENCY_2WS   /*!< FLASH Two Latency cycles      */
#define FLASH_LATENCY_3                FLASH_ACR_LATENCY_3WS   /*!< FLASH Three Latency cycles    */
#define FLASH_LATENCY_4                FLASH_ACR_LATENCY_4WS   /*!< FLASH Four Latency cycles     */
#define FLASH_LATENCY_5                FLASH_ACR_LATENCY_5WS   /*!< FLASH Five Latency cycles     */
#define FLASH_LATENCY_6                FLASH_ACR_LATENCY_6WS   /*!< FLASH Six Latency cycles      */
#define FLASH_LATENCY_7                FLASH_ACR_LATENCY_7WS   /*!< FLASH Seven Latency cycles    */
/**
  * @}
  */


/** @defgroup FLASHEx_Banks FLASH Banks
  * @{
  */
#define FLASH_BANK_1                       ((uint32_t)0x01U)                          /*!< Bank 1   */
#define FLASH_BANK_2                       ((uint32_t)0x02U)                          /*!< Bank 2   */
#define FLASH_BANK_BOTH                    ((uint32_t)(FLASH_BANK_1 | FLASH_BANK_2)) /*!< Bank1 and Bank2  */
/**
  * @}
  */


/** @defgroup FLASHEx_OB_PCROP_RDP  FLASHEx OB PCROP RDP
  * @{
  */
#define OB_PCROP_RDP_NOT_ERASE    ((uint32_t)0x00000000U) /*!< PCROP area is not erased when the RDP level 
                                                              is decreased from Level 1 to Level 0 or during a mass erase */
#define OB_PCROP_RDP_ERASE        ((uint32_t)FLASH_PRAR_DMEP) /*!< PCROP area is erased when the RDP level is 
                                                              decreased from Level 1 to Level 0 (full mass erase) */

/**
  * @}
  */

    

/** @defgroup FLASHEx_Option_Bytes_Write_Protection FLASH Option Bytes Write Protection
  * @{
  */
#define OB_WRP_SECTOR_0       ((uint32_t)0x00000001U) /*!< Write protection of Sector0     */
#define OB_WRP_SECTOR_1       ((uint32_t)0x00000002U) /*!< Write protection of Sector1     */
#define OB_WRP_SECTOR_2       ((uint32_t)0x00000004U) /*!< Write protection of Sector2     */
#define OB_WRP_SECTOR_3       ((uint32_t)0x00000008U) /*!< Write protection of Sector3     */
#define OB_WRP_SECTOR_4       ((uint32_t)0x00000010U) /*!< Write protection of Sector4     */
#define OB_WRP_SECTOR_5       ((uint32_t)0x00000020U) /*!< Write protection of Sector5     */
#define OB_WRP_SECTOR_6       ((uint32_t)0x00000040U) /*!< Write protection of Sector6     */
#define OB_WRP_SECTOR_7       ((uint32_t)0x00000080U) /*!< Write protection of Sector7     */
#define OB_WRP_SECTOR_All     ((uint32_t)0x000000FFU) /*!< Write protection of all Sectors */
/**
  * @}
  */


/** @defgroup FLASHEx_OB_SECURITY  FLASHEx OB SECURITY
  * @{
  */
#define OB_SECURITY_DISABLE   ((uint32_t)0x00000U)                    /*!< security enabled */
#define OB_SECURITY_ENABLE    ((uint32_t)FLASH_OPTSR_SECURITY)    /*!< security disabled */

/**
  * @}
  */  


  
/** @defgroup FLASHEx_OB_IWDG1_SW  FLASHEx OB IWDG1 SW
  * @{
  */
#define OB_IWDG1_SW             ((uint32_t)FLASH_OPTSR_IWDG1_SW) /*!< Hardware independent watchdog 1 */
#define OB_IWDG1_HW             ((uint32_t)0x00000U)             /*!< Software independent watchdog 1 */
/**
  * @}
  */
/** @defgroup FLASHEx_OB_NRST_STOP_D1  FLASHEx OB NRST STOP D1
  * @{
  */
#define OB_STOP_RST_D1            ((uint32_t)0x0000U)                       /*!< Reset generated when entering the D1 to stop mode */
#define OB_STOP_NO_RST_D1         ((uint32_t)FLASH_OPTSR_NRST_STOP_D1)     /*!< No reset generated when entering the D1 to stop mode */

/**
  * @}
  */

/** @defgroup FLASHEx_OB_NRST_STDBY_D1  FLASHEx OB NRST STDBY D1
  * @{
  */
#define OB_STDBY_RST_D1           ((uint32_t)0x0000U)                        /*!< Reset generated when entering the D1 to standby mode */
#define OB_STDBY_NO_RST_D1        ((uint32_t)FLASH_OPTSR_NRST_STBY_D1)      /*!< No reset generated when entering the D1 to standby mode */

/**
  * @}
  */

/** @defgroup FLASHEx_OB_SWAP_BANK  FLASHEx OB SWAP BANK
  * @{
  */
#define OB_SWAP_BANK_DISABLE     ((uint32_t)0x00000U)                       /*!< Bank swap disabled */
#define OB_SWAP_BANK_ENABLE      ((uint32_t)FLASH_OPTSR_SWAP_BANK_OPT)     /*!< Bank swap enabled */

/**
  * @}
  */
  
/** @defgroup FLASHEx_OB_IOHSLV FLASHEx OB IOHSLV
  * @{
  */
#define OB_IOHSLV_DISABLE     ((uint32_t)0x00000000U)          /*!< IOHSLV disabled */
#define OB_IOHSLV_ENABLE      ((uint32_t)FLASH_OPTSR_IO_HSLV)  /*!< IOHSLV enabled */


/**
  * @}
  */  

/** @defgroup FLASHEx_OB_BOOT_OPTION  FLASHEx OB BOOT OPTION
  * @{
  */
#define OB_BOOT_ADD0             ((uint32_t)0x01U)                       /*!< Select Boot Address 0 */
#define OB_BOOT_ADD1             ((uint32_t)0x02U)                       /*!< Select Boot Address 1 */   
#define OB_BOOT_ADD_BOTH         ((uint32_t)0x03U)                       /*!< Select Boot Address 0 and 1 */ 


/**
  * @}
  */
  
 /** @defgroup FLASHEx_OB_USER_Type  FLASHEx OB USER Type
  * @{
  */
#define OB_USER_NRST_STOP_D1      ((uint32_t)0x0001U) /*!< Reset when entering Stop mode selection*/
#define OB_USER_NRST_STDBY_D1     ((uint32_t)0x0002U) /*!< Reset when entering standby mode selection*/
#define OB_USER_IWDG_STOP         ((uint32_t)0x0004U) /*!< Independent watchdog counter freeze in stop mode */
#define OB_USER_IWDG_STDBY        ((uint32_t)0x0008U) /*!< Independent watchdog counter freeze in standby mode */
#define OB_USER_ST_RAM_SIZE       ((uint32_t)0x0010U) /*!< dedicated DTCM Ram size selection */
#define OB_USER_SECURITY          ((uint32_t)0x0020U) /*!< security selection */
#define OB_USER_SWAP_BANK         ((uint32_t)0x0100U) /*!< Bank swap selection */
#define OB_USER_IOHSLV            ((uint32_t)0x0200U) /*!< IO HSLV selection */
#define OB_USER_IWDG1_SW          ((uint32_t)0x0400U) /*!< Independent watchdog selection */

/**
  * @}
  */
  
/** @defgroup FLASHEx_OB_SECURE_RDP  FLASHEx OB SECURE RDP
  * @{
  */
#define OB_SECURE_RDP_NOT_ERASE    ((uint32_t)0x00000000U)               /*!< Secure area is not erased when the RDP level 
                                                                             is decreased from Level 1 to Level 0 or during a mass erase*/
#define OB_SECURE_RDP_ERASE        ((uint32_t)FLASH_SCAR_DMES)          /*!< Secure area is erased when the RDP level is 
                                                                             decreased from Level 1 to Level 0 (full mass erase) */

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/** @defgroup FLASH_Exported_Macros FLASH Exported Macros
  * @{
  */
/**
  * @brief  Calculate the FLASH Boot Base Adress (BOOT_ADD0 or BOOT_ADD1)
  * @note   Returned value BOOT_ADDx[15:0] corresponds to boot address [29:14].
  * @param  __ADDRESS__: FLASH Boot Address (in the range 0x0000 0000 to 0x2004 FFFF with a granularity of 16KB)
  * @retval The FLASH Boot Base Adress
  */
#define __HAL_FLASH_CALC_BOOT_BASE_ADR(__ADDRESS__) ((__ADDRESS__) >> 14)
 /**
  * @}
  */
                    
/* Exported functions --------------------------------------------------------*/
/** @addtogroup FLASHEx_Exported_Functions
  * @{
  */

/** @addtogroup FLASHEx_Exported_Functions_Group1
  * @{
  */
/* Extension Program operation functions  *************************************/
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *SectorError);
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit);
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit);
void              HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit);

HAL_StatusTypeDef HAL_FLASHEx_Unlock_Bank1(void);
HAL_StatusTypeDef HAL_FLASHEx_Lock_Bank1(void);
HAL_StatusTypeDef HAL_FLASHEx_Unlock_Bank2(void);
HAL_StatusTypeDef HAL_FLASHEx_Lock_Bank2(void);

/**
  * @}
  */

/**
  * @}
  */
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup FLASHEx_Private_Macros FLASHEx Private Macros
  * @{
  */

/** @defgroup FLASHEx_IS_FLASH_Definitions FLASHEx Private macros to check input parameters
  * @{
  */

#define IS_FLASH_TYPEERASE(VALUE)    (((VALUE) == FLASH_TYPEERASE_SECTORS) || \
                                      ((VALUE) == FLASH_TYPEERASE_MASSERASE))  

#define IS_VOLTAGERANGE(RANGE)    (((RANGE) == FLASH_VOLTAGE_RANGE_1) || \
                                   ((RANGE) == FLASH_VOLTAGE_RANGE_2) || \
                                   ((RANGE) == FLASH_VOLTAGE_RANGE_3) || \
                                   ((RANGE) == FLASH_VOLTAGE_RANGE_4))  

#define IS_WRPSTATE(VALUE)    (((VALUE) == OB_WRPSTATE_DISABLE) || \
                               ((VALUE) == OB_WRPSTATE_ENABLE))  
#define IS_OPTIONBYTE(VALUE)    ((VALUE) <= (OB_USER_IWDG1_SW | OB_USER_NRST_STDBY_D1 | OB_USER_NRST_STOP_D1  |\
                                             OB_USER_IWDG_STOP| OB_USER_IWDG_STDBY    | OB_USER_SWAP_BANK     |\
                                             OB_USER_ST_RAM_SIZE   | OB_USER_SECURITY))
                                             

#define IS_OB_BOOT_ADDRESS(ADDRESS)     ((ADDRESS) <= 0x8013U)


#define IS_OB_RDP_LEVEL(LEVEL)             (((LEVEL) == OB_RDP_LEVEL_0)   ||\
                                            ((LEVEL) == OB_RDP_LEVEL_1) ||\
                                            ((LEVEL) == OB_RDP_LEVEL_2))

#define IS_OB_WWDG_SOURCE(SOURCE) (((SOURCE) == OB_WWDG_SW) || ((SOURCE) == OB_WWDG_HW))

#define IS_OB_IWDG_SOURCE(SOURCE) (((SOURCE) == OB_IWDG_SW) || ((SOURCE) == OB_IWDG_HW))

#define IS_OB_STOP_SOURCE(SOURCE) (((SOURCE) == OB_STOP_NO_RST) || ((SOURCE) == OB_STOP_RST))

#define IS_OB_STDBY_SOURCE(SOURCE) (((SOURCE) == OB_STDBY_NO_RST) || ((SOURCE) == OB_STDBY_RST))

#define IS_OB_IWDG_STOP_FREEZE(FREEZE) (((FREEZE) == OB_IWDG_STOP_FREEZE) || ((FREEZE) == OB_IWDG_STOP_ACTIVE))

#define IS_OB_IWDG_STDBY_FREEZE(FREEZE) (((FREEZE) == OB_IWDG_STDBY_FREEZE) || ((FREEZE) == OB_IWDG_STDBY_ACTIVE))

#define IS_OB_BOR_LEVEL(LEVEL) (((LEVEL) == OB_BOR_LEVEL1) || ((LEVEL) == OB_BOR_LEVEL2) ||\
                                ((LEVEL) == OB_BOR_LEVEL3) || ((LEVEL) == OB_BOR_OFF))

#define IS_FLASH_LATENCY(LATENCY) (((LATENCY) == FLASH_LATENCY_0)  || \
                                   ((LATENCY) == FLASH_LATENCY_1)  || \
                                   ((LATENCY) == FLASH_LATENCY_2)  || \
                                   ((LATENCY) == FLASH_LATENCY_3)  || \
                                   ((LATENCY) == FLASH_LATENCY_4)  || \
                                   ((LATENCY) == FLASH_LATENCY_5)  || \
                                   ((LATENCY) == FLASH_LATENCY_6)  || \
                                   ((LATENCY) == FLASH_LATENCY_7))

#define IS_FLASH_ADDRESS(ADDRESS) ((((ADDRESS) >= FLASH_BASE) && ((ADDRESS) <= FLASH_END)) || \
                                   (((ADDRESS) >= FLASH_OTP_BANK1_BASE) && ((ADDRESS) <= FLASH_OTP_BANK1_END)) || \
								   (((ADDRESS) >= FLASH_OTP_BANK2_BASE) && ((ADDRESS) <= FLASH_OTP_BANK2_END)))

#define IS_FLASH_NBSECTORS(NBSECTORS) (((NBSECTORS) != 0U) && ((NBSECTORS) <= FLASH_SECTOR_TOTAL))

#define IS_FLASH_SECTOR(SECTOR) (((SECTOR) == FLASH_SECTOR_0)   || ((SECTOR) == FLASH_SECTOR_1)   ||\
                                 ((SECTOR) == FLASH_SECTOR_2)   || ((SECTOR) == FLASH_SECTOR_3)   ||\
                                 ((SECTOR) == FLASH_SECTOR_4)   || ((SECTOR) == FLASH_SECTOR_5)   ||\
                                 ((SECTOR) == FLASH_SECTOR_6)   || ((SECTOR) == FLASH_SECTOR_7))

#define IS_OB_WRP_SECTOR(SECTOR)  ((((SECTOR) & (uint32_t)0xFFFFFF00) == 0x00000000U) && ((SECTOR) != 0x00000000U))

#define IS_FLASH_BANK(BANK)        (((BANK) == FLASH_BANK_1)  || \
                                    ((BANK) == FLASH_BANK_2)  || \
                                    ((BANK) == FLASH_BANK_BOTH))

#define IS_OB_PCROP_RDP(CONFIG)         (((CONFIG) == OB_PCROP_RDP_NOT_ERASE) || \
                                             ((CONFIG) == OB_PCROP_RDP_ERASE))

#define IS_OB_SECURE_RDP(CONFIG)         (((CONFIG) == OB_SECURE_RDP_NOT_ERASE) || \
                                             ((CONFIG) == OB_SECURE_RDP_ERASE))

#define IS_OB_USER_SWAP_BANK(VALUE)      (((VALUE) == OB_SWAP_BANK_DISABLE) || ((VALUE) == OB_SWAP_BANK_ENABLE))

#define IS_OB_USER_IOHSLV(VALUE)         (((VALUE) == OB_IOHSLV_DISABLE) || ((VALUE) == OB_IOHSLV_ENABLE))

#define IS_OB_IWDG1_SOURCE(SOURCE)       (((SOURCE) == OB_IWDG1_SW) || ((SOURCE) == OB_IWDG1_HW))
#define IS_OB_STOP_D1_RESET(VALUE)       (((VALUE) == OB_STOP_NO_RST_D1) || ((VALUE) == OB_STOP_RST_D1))

#define IS_OB_STDBY_D1_RESET(VALUE)      (((VALUE) == OB_STDBY_NO_RST_D1) || ((VALUE) == OB_STDBY_RST_D1))

#define IS_OB_USER_IWDG_STOP(VALUE)      (((VALUE) == OB_IWDG_STOP_FREEZE) || ((VALUE) == OB_IWDG_STOP_ACTIVE))

#define IS_OB_USER_IWDG_STDBY(VALUE)     (((VALUE) == OB_IWDG_STDBY_FREEZE) || ((VALUE) == OB_IWDG_STDBY_ACTIVE))

#define IS_OB_USER_SECURITY(VALUE)       (((VALUE) == OB_SECURITY_ENABLE) || ((VALUE) == OB_SECURITY_DISABLE))  /*User can only move the security bit from 0 to 1*/                      
#define IS_OB_USER_TYPE(TYPE)            (((TYPE) <= (uint32_t)0x400U) && ((TYPE) != 0))

#define IS_OB_BOOT_ADD_OPTION(VALUE)     (((VALUE) == OB_BOOT_ADD0) || \
                                           ((VALUE) == OB_BOOT_ADD1)  || \
                                           ((VALUE) == OB_BOOT_ADD_BOTH))

/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup FLASHEx_Private_Functions Extended FLASH Private functions
  * @{
  */
void FLASH_Erase_Sector(uint32_t Sector, uint32_t Bank, uint32_t VoltageRange);
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
#endif

#endif /* __STM32H7xx_HAL_FLASH_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
