/**
  ******************************************************************************
  * @file    hk32f0xx_flash.h 
  * @version V1.0.1
  * @date    2019-08-15
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F0XX_FLASH_H
#define __HK32F0XX_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f0xx.h"

/** @addtogroup HK32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  FLASH Status
  */ 
typedef enum
{
  FLASH_BUSY = 1,
  FLASH_ERROR_WRP,
  FLASH_ERROR_PROGRAM,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
}FLASH_Status;

/* Exported constants --------------------------------------------------------*/
  
/** @defgroup FLASH_Exported_Constants
  * @{
  */ 
  
/** @defgroup FLASH_Latency 
  * @{
  */ 
#define FLASH_Latency_0                ((uint32_t)0x00000000)  /*!< FLASH Zero Latency cycle */
#define FLASH_Latency_1                FLASH_ACR_LATENCY       /*!< FLASH One Latency cycle */

#define IS_FLASH_LATENCY(LATENCY) (((LATENCY) == FLASH_Latency_0) || \
                                   ((LATENCY) == FLASH_Latency_1))
/**
  * @}
  */ 

/** @defgroup FLASH_Interrupts 
  * @{
  */
   
#define FLASH_IT_EOP                   FLASH_CR_EOPIE  /*!< End of programming interrupt source */
#define FLASH_IT_ERR                   FLASH_CR_ERRIE  /*!< Error interrupt source */
#define IS_FLASH_IT(IT) ((((IT) & (uint32_t)0xFFFFEBFF) == 0x00000000) && (((IT) != 0x00000000)))
/**
  * @}
  */ 

/** @defgroup FLASH_Address 
  * @{
  */

#define IS_FLASH_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && ((ADDRESS) <= 0x0800FFFF))

/**
  * @}
  */

/** @defgroup FLASH_OB_DATA_ADDRESS 
  * @{
  */  
#define IS_OB_DATA_ADDRESS(ADDRESS) (((ADDRESS) == 0x1FFFF804) || ((ADDRESS) == 0x1FFFF806)) 

/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_Write_Protection 
  * @{
  */
  
#define OB_WRP_Pages0to3               ((uint32_t)0x00000001) /* Write protection of page 0 to 3 */
#define OB_WRP_Pages4to7               ((uint32_t)0x00000002) /* Write protection of page 4 to 7 */
#define OB_WRP_Pages8to11              ((uint32_t)0x00000004) /* Write protection of page 8 to 11 */
#define OB_WRP_Pages12to15             ((uint32_t)0x00000008) /* Write protection of page 12 to 15 */
#define OB_WRP_Pages16to19             ((uint32_t)0x00000010) /* Write protection of page 16 to 19 */
#define OB_WRP_Pages20to23             ((uint32_t)0x00000020) /* Write protection of page 20 to 23 */
#define OB_WRP_Pages24to27             ((uint32_t)0x00000040) /* Write protection of page 24 to 27 */
#define OB_WRP_Pages28to31             ((uint32_t)0x00000080) /* Write protection of page 28 to 31 */
#define OB_WRP_Pages32to35             ((uint32_t)0x00000100) /* Write protection of page 32 to 35 */
#define OB_WRP_Pages36to39             ((uint32_t)0x00000200) /* Write protection of page 36 to 39 */
#define OB_WRP_Pages40to43             ((uint32_t)0x00000400) /* Write protection of page 40 to 43 */
#define OB_WRP_Pages44to47             ((uint32_t)0x00000800) /* Write protection of page 44 to 47 */
#define OB_WRP_Pages48to51             ((uint32_t)0x00001000) /* Write protection of page 48 to 51 */
#define OB_WRP_Pages52to55             ((uint32_t)0x00002000) /* Write protection of page 52 to 55 */
#define OB_WRP_Pages56to59             ((uint32_t)0x00004000) /* Write protection of page 56 to 59 */
#define OB_WRP_Pages60to63             ((uint32_t)0x00008000) /* Write protection of page 60 to 63 */

#define OB_WRP_AllPages                ((uint32_t)0x0000FFFF) /*!< Write protection of all Sectors */

#define IS_OB_WRP(PAGE) (((PAGE) != 0x0000000))


/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_Read_Protection 
  * @{
  */ 

/** 
  * @brief  FLASH_Read Protection Level  
  */ 
#define OB_RDP_Level_0   ((uint8_t)0xAA)
#define OB_RDP_Level_1   ((uint8_t)0xBB)
/*#define OB_RDP_Level_2   ((uint8_t)0xCC)*/ /* Warning: When enabling read protection level 2 
                                                it's no more possible to go back to level 1 or 0 */

#define IS_OB_RDP(LEVEL) (((LEVEL) == OB_RDP_Level_0)||\
                          ((LEVEL) == OB_RDP_Level_1))/*||\
                          ((LEVEL) == OB_RDP_Level_2))*/
/**
  * @}
  */ 

/** @defgroup FLASH_Option_Bytes_IWatchdog 
  * @{
  */

#define OB_IWDG_SW                     ((uint8_t)0x01)  /*!< Software IWDG selected */
#define OB_IWDG_HW                     ((uint8_t)0x00)  /*!< Hardware IWDG selected */
#define IS_OB_IWDG_SOURCE(SOURCE) (((SOURCE) == OB_IWDG_SW) || ((SOURCE) == OB_IWDG_HW))

/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_nRST_STOP 
  * @{
  */

#define OB_STOP_NoRST                  ((uint8_t)0x02) /*!< No reset generated when entering in STOP */
#define OB_STOP_RST                    ((uint8_t)0x00) /*!< Reset generated when entering in STOP */
#define IS_OB_STOP_SOURCE(SOURCE) (((SOURCE) == OB_STOP_NoRST) || ((SOURCE) == OB_STOP_RST))

/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_nRST_STDBY 
  * @{
  */

#define OB_STDBY_NoRST                 ((uint8_t)0x04) /*!< No reset generated when entering in STANDBY */
#define OB_STDBY_RST                   ((uint8_t)0x00) /*!< Reset generated when entering in STANDBY */
#define IS_OB_STDBY_SOURCE(SOURCE) (((SOURCE) == OB_STDBY_NoRST) || ((SOURCE) == OB_STDBY_RST))

/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_BOOT1
  * @{
  */

#define OB_BOOT1_RESET                 ((uint8_t)0x00) /*!< BOOT1 Reset */
#define OB_BOOT1_SET                   ((uint8_t)0x10) /*!< BOOT1 Set */
#define IS_OB_BOOT1(BOOT1) (((BOOT1) == OB_BOOT1_RESET) || ((BOOT1) == OB_BOOT1_SET))

/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_BOOT0
  * @{
  */

#define OB_BOOT0_RESET                 ((uint8_t)0x00) /*!< BOOT0 Reset */
#define OB_BOOT0_SET                   ((uint8_t)0x08) /*!< BOOT0 Set */
#define IS_OB_BOOT0(BOOT0) (((BOOT0) == OB_BOOT0_RESET) || ((BOOT0) == OB_BOOT0_SET))

/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_BOOT0SW
  * @{
  */

#define OB_BOOT0_SW                   ((uint8_t)0x00) /*!< BOOT0 pin disabled */  
#define OB_BOOT0_HW                   ((uint8_t)0x80) /*!< BOOT0 pin bonded with GPIO */
#define IS_OB_BOOT0SW(BOOT0) (((BOOT0) == OB_BOOT0_SW) || ((BOOT0) == OB_BOOT0_HW))

/**
  * @}
  */
  
/** @defgroup FLASH_Option_Bytes_VDDA_Analog_Monitoring
  * @{
  */

#define OB_VDDA_ANALOG_ON              ((uint8_t)0x20) /*!< Analog monitoring on VDDA Power source ON */
#define OB_VDDA_ANALOG_OFF             ((uint8_t)0x00) /*!< Analog monitoring on VDDA Power source OFF */

#define IS_OB_VDDA_ANALOG(ANALOG) (((ANALOG) == OB_VDDA_ANALOG_ON) || ((ANALOG) == OB_VDDA_ANALOG_OFF))

/**
  * @}
  */    

/** @defgroup FLASH_Option_Bytes_SRAM_Parity_Enable 
  * @{
  */

#define OB_SRAM_PARITY_SET              ((uint8_t)0x00) /*!< SRAM parity enable Set */
#define OB_SRAM_PARITY_RESET            ((uint8_t)0x40) /*!< SRAM parity enable reset */

#define IS_OB_SRAM_PARITY(PARITY) (((PARITY) == OB_SRAM_PARITY_SET) || ((PARITY) == OB_SRAM_PARITY_RESET))

/**
  * @}
  */ 
  
/** @defgroup FLASH_Flags 
  * @{
  */ 

#define FLASH_FLAG_BSY                 FLASH_SR_BSY     /*!< FLASH Busy flag */
#define FLASH_FLAG_PGERR               FLASH_SR_PGERR   /*!< FLASH Programming error flag */
#define FLASH_FLAG_WRPERR              FLASH_SR_WRPERR  /*!< FLASH Write protected error flag */
#define FLASH_FLAG_EOP                 FLASH_SR_EOP     /*!< FLASH End of Programming flag */
 
#define IS_FLASH_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFFFCB) == 0x00000000) && ((FLAG) != 0x00000000))

#define IS_FLASH_GET_FLAG(FLAG)  (((FLAG) == FLASH_FLAG_BSY) || ((FLAG) == FLASH_FLAG_PGERR) || \
                                  ((FLAG) == FLASH_FLAG_WRPERR) || ((FLAG) == FLASH_FLAG_EOP))
/**
  * @}
  */ 

/** @defgroup FLASH_Timeout_definition 
  * @{
  */ 
#define FLASH_ER_PRG_TIMEOUT         ((uint32_t)0x000B0000)

/**
  * @}
  */ 

/** @defgroup FLASH_Legacy 
  * @{
  */
#define FLASH_WRProt_Pages0to3	       OB_WRP_Pages0to3
#define FLASH_WRProt_Pages4to7	       OB_WRP_Pages4to7
#define FLASH_WRProt_Pages8to11	       OB_WRP_Pages8to11
#define FLASH_WRProt_Pages12to15	   OB_WRP_Pages12to15
#define FLASH_WRProt_Pages16to19	   OB_WRP_Pages16to19
#define FLASH_WRProt_Pages20to23	   OB_WRP_Pages20to23
#define FLASH_WRProt_Pages24to27	   OB_WRP_Pages24to27
#define FLASH_WRProt_Pages28to31	   OB_WRP_Pages28to31
#define FLASH_WRProt_Pages32to35	   OB_WRP_Pages32to35
#define FLASH_WRProt_Pages36to39	   OB_WRP_Pages36to39
#define FLASH_WRProt_Pages40to43	   OB_WRP_Pages40to21
#define FLASH_WRProt_Pages44to47	   OB_WRP_Pages44to23
#define FLASH_WRProt_Pages48to51	   OB_WRP_Pages48to51
#define FLASH_WRProt_Pages52to55	   OB_WRP_Pages52to55
#define FLASH_WRProt_Pages56to59	   OB_WRP_Pages56to59
#define FLASH_WRProt_Pages60to63	   OB_WRP_Pages60to63


#define FLASH_WRProt_AllPages          OB_WRP_AllPages
/**
  * @}
  */

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
  
/** 
  * @brief  FLASH memory functions that can be executed from FLASH.  
  */  
/* FLASH Interface configuration functions ************************************/
void FLASH_SetLatency(uint32_t FLASH_Latency);
void FLASH_PrefetchBufferCmd(FunctionalState NewState);
FlagStatus FLASH_GetPrefetchBufferStatus(void);

/* FLASH Memory Programming functions *****************************************/
void FLASH_Unlock(void);
void FLASH_Lock(void);
FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
FLASH_Status FLASH_EraseAllPages(void);
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);

/* FLASH Option Bytes Programming functions *****************************************/
void FLASH_OB_Unlock(void);
void FLASH_OB_Lock(void);
void FLASH_OB_Launch(void);
FLASH_Status FLASH_OB_Erase(void);
FLASH_Status FLASH_OB_EnableWRP(uint32_t OB_WRP);
FLASH_Status FLASH_OB_RDPConfig(uint8_t OB_RDP);
FLASH_Status FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY);
FLASH_Status FLASH_OB_BOOTConfig(uint8_t OB_BOOT1);
FLASH_Status FLASH_OB_BOOT0Config(uint8_t OB_BOOT0);
FLASH_Status FLASH_OB_BOOT0SWConfig(uint8_t OB_BOOT0SW);
FLASH_Status FLASH_OB_VDDAConfig(uint8_t OB_VDDA_ANALOG);
FLASH_Status FLASH_OB_SRAMParityConfig(uint8_t OB_SRAM_Parity);
FLASH_Status FLASH_OB_WriteUser(uint8_t OB_USER);
FLASH_Status FLASH_OB_ProgramData(uint32_t Address, uint8_t Data);
uint8_t FLASH_OB_GetUser(void);
uint32_t FLASH_OB_GetWRP(void);
FlagStatus FLASH_OB_GetRDP(void);

/* FLASH Interrupts and flags management functions **********************************/
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_Status FLASH_GetStatus(void);
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);

/** @defgroup FLASH_Legacy 
  * @{
  */
#define FLASH_EraseOptionBytes               FLASH_OB_Erase
#define FLASH_EnableWriteProtection	         FLASH_OB_EnableWRP
#define FLASH_UserOptionByteConfig	         FLASH_OB_UserConfig
#define FLASH_ProgramOptionByteData          FLASH_OB_ProgramData
#define FLASH_GetUserOptionByte	             FLASH_OB_GetUser
#define FLASH_GetWriteProtectionOptionByte   FLASH_OB_GetWRP

/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /* __HK32F0XX_FLASH_H */


