/***************COPYRIGHT(C)  2019 WCH. A11 rights reserved*********************
 * File Name          : ch32f10x_flash.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : This file contains all the functions prototypes for the FLASH  
 *                      firmware library.
 *******************************************************************************/ 
#ifndef __CH32F10x_FLASH_H
#define __CH32F10x_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "ch32f10x.h"

/* FLASH Status */
typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_PG,
  FLASH_ERROR_WRP,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
}FLASH_Status;


/* Flash_Latency */
#define FLASH_Latency_0                ((uint32_t)0x00000000)  /*!< FLASH Zero Latency cycle */
#define FLASH_Latency_1                ((uint32_t)0x00000001)  /*!< FLASH One Latency cycle */
#define FLASH_Latency_2                ((uint32_t)0x00000002)  /*!< FLASH Two Latency cycles */

/* Half_Cycle_Enable_Disable */
#define FLASH_HalfCycleAccess_Enable   ((uint32_t)0x00000008)  /*!< FLASH Half Cycle Enable */
#define FLASH_HalfCycleAccess_Disable  ((uint32_t)0x00000000)  /*!< FLASH Half Cycle Disable */ 

/* Prefetch_Buffer_Enable_Disable */
#define FLASH_PrefetchBuffer_Enable    ((uint32_t)0x00000010)  /*!< FLASH Prefetch Buffer Enable */
#define FLASH_PrefetchBuffer_Disable   ((uint32_t)0x00000000)  /*!< FLASH Prefetch Buffer Disable */ 

/* Values to be used with CH32F10x Low and Medium density devices */
#define FLASH_WRProt_Pages0to3         ((uint32_t)0x00000001) /*!< CH32 Low and Medium density devices: Write protection of page 0 to 3 */
#define FLASH_WRProt_Pages4to7         ((uint32_t)0x00000002) /*!< CH32 Low and Medium density devices: Write protection of page 4 to 7 */
#define FLASH_WRProt_Pages8to11        ((uint32_t)0x00000004) /*!< CH32 Low and Medium density devices: Write protection of page 8 to 11 */
#define FLASH_WRProt_Pages12to15       ((uint32_t)0x00000008) /*!< CH32 Low and Medium density devices: Write protection of page 12 to 15 */
#define FLASH_WRProt_Pages16to19       ((uint32_t)0x00000010) /*!< CH32 Low and Medium density devices: Write protection of page 16 to 19 */
#define FLASH_WRProt_Pages20to23       ((uint32_t)0x00000020) /*!< CH32 Low and Medium density devices: Write protection of page 20 to 23 */
#define FLASH_WRProt_Pages24to27       ((uint32_t)0x00000040) /*!< CH32 Low and Medium density devices: Write protection of page 24 to 27 */
#define FLASH_WRProt_Pages28to31       ((uint32_t)0x00000080) /*!< CH32 Low and Medium density devices: Write protection of page 28 to 31 */
                                                                   
/* Values to be used with CH32F10x Medium-density devices */       
#define FLASH_WRProt_Pages32to35       ((uint32_t)0x00000100) /*!< CH32 Medium-density devices: Write protection of page 32 to 35 */
#define FLASH_WRProt_Pages36to39       ((uint32_t)0x00000200) /*!< CH32 Medium-density devices: Write protection of page 36 to 39 */
#define FLASH_WRProt_Pages40to43       ((uint32_t)0x00000400) /*!< CH32 Medium-density devices: Write protection of page 40 to 43 */
#define FLASH_WRProt_Pages44to47       ((uint32_t)0x00000800) /*!< CH32 Medium-density devices: Write protection of page 44 to 47 */
#define FLASH_WRProt_Pages48to51       ((uint32_t)0x00001000) /*!< CH32 Medium-density devices: Write protection of page 48 to 51 */
#define FLASH_WRProt_Pages52to55       ((uint32_t)0x00002000) /*!< CH32 Medium-density devices: Write protection of page 52 to 55 */
#define FLASH_WRProt_Pages56to59       ((uint32_t)0x00004000) /*!< CH32 Medium-density devices: Write protection of page 56 to 59 */
#define FLASH_WRProt_Pages60to63       ((uint32_t)0x00008000) /*!< CH32 Medium-density devices: Write protection of page 60 to 63 */
#define FLASH_WRProt_Pages64to67       ((uint32_t)0x00010000) /*!< CH32 Medium-density devices: Write protection of page 64 to 67 */
#define FLASH_WRProt_Pages68to71       ((uint32_t)0x00020000) /*!< CH32 Medium-density devices: Write protection of page 68 to 71 */
#define FLASH_WRProt_Pages72to75       ((uint32_t)0x00040000) /*!< CH32 Medium-density devices: Write protection of page 72 to 75 */
#define FLASH_WRProt_Pages76to79       ((uint32_t)0x00080000) /*!< CH32 Medium-density devices: Write protection of page 76 to 79 */
#define FLASH_WRProt_Pages80to83       ((uint32_t)0x00100000) /*!< CH32 Medium-density devices: Write protection of page 80 to 83 */
#define FLASH_WRProt_Pages84to87       ((uint32_t)0x00200000) /*!< CH32 Medium-density devices: Write protection of page 84 to 87 */
#define FLASH_WRProt_Pages88to91       ((uint32_t)0x00400000) /*!< CH32 Medium-density devices: Write protection of page 88 to 91 */
#define FLASH_WRProt_Pages92to95       ((uint32_t)0x00800000) /*!< CH32 Medium-density devices: Write protection of page 92 to 95 */
#define FLASH_WRProt_Pages96to99       ((uint32_t)0x01000000) /*!< CH32 Medium-density devices: Write protection of page 96 to 99 */
#define FLASH_WRProt_Pages100to103     ((uint32_t)0x02000000) /*!< CH32 Medium-density devices: Write protection of page 100 to 103 */
#define FLASH_WRProt_Pages104to107     ((uint32_t)0x04000000) /*!< CH32 Medium-density devices: Write protection of page 104 to 107 */
#define FLASH_WRProt_Pages108to111     ((uint32_t)0x08000000) /*!< CH32 Medium-density devices: Write protection of page 108 to 111 */
#define FLASH_WRProt_Pages112to115     ((uint32_t)0x10000000) /*!< CH32 Medium-density devices: Write protection of page 112 to 115 */
#define FLASH_WRProt_Pages116to119     ((uint32_t)0x20000000) /*!< CH32 Medium-density devices: Write protection of page 115 to 119 */
#define FLASH_WRProt_Pages120to123     ((uint32_t)0x40000000) /*!< CH32 Medium-density devices: Write protection of page 120 to 123 */
#define FLASH_WRProt_Pages124to127     ((uint32_t)0x80000000) /*!< CH32 Medium-density devices: Write protection of page 124 to 127 */
                                                                   
#define FLASH_WRProt_Pages62to255      ((uint32_t)0x80000000) /*!< CH32 Medium-density devices: Write protection of page 62 to 255 */

#define FLASH_WRProt_AllPages          ((uint32_t)0xFFFFFFFF) /*!< Write protection of all Pages */

/* Option_Bytes_IWatchdog */
#define OB_IWDG_SW                     ((uint16_t)0x0001)  /*!< Software IWDG selected */
#define OB_IWDG_HW                     ((uint16_t)0x0000)  /*!< Hardware IWDG selected */

/* Option_Bytes_nRST_STOP */
#define OB_STOP_NoRST                  ((uint16_t)0x0002) /*!< No reset generated when entering in STOP */
#define OB_STOP_RST                    ((uint16_t)0x0000) /*!< Reset generated when entering in STOP */

/* Option_Bytes_nRST_STDBY  */
#define OB_STDBY_NoRST                 ((uint16_t)0x0004) /*!< No reset generated when entering in STANDBY */
#define OB_STDBY_RST                   ((uint16_t)0x0000) /*!< Reset generated when entering in STANDBY */

/* FLASH_Interrupts */	
#define FLASH_IT_ERROR                 ((uint32_t)0x00000400)  /*!< FPEC error interrupt source */
#define FLASH_IT_EOP                   ((uint32_t)0x00001000)  /*!< End of FLASH Operation Interrupt source */
#define FLASH_IT_BANK1_ERROR           FLASH_IT_ERROR          /*!< FPEC BANK1 error interrupt source */
#define FLASH_IT_BANK1_EOP             FLASH_IT_EOP            /*!< End of FLASH BANK1 Operation Interrupt source */

/* FLASH_Flags */	
#define FLASH_FLAG_BSY                 ((uint32_t)0x00000001)  /*!< FLASH Busy flag */
#define FLASH_FLAG_EOP                 ((uint32_t)0x00000020)  /*!< FLASH End of Operation flag */
#define FLASH_FLAG_PGERR               ((uint32_t)0x00000004)  /*!< FLASH Program error flag */
#define FLASH_FLAG_WRPRTERR            ((uint32_t)0x00000010)  /*!< FLASH Write protected error flag */
#define FLASH_FLAG_OPTERR              ((uint32_t)0x00000001)  /*!< FLASH Option Byte error flag */

#define FLASH_FLAG_BANK1_BSY                 FLASH_FLAG_BSY       /*!< FLASH BANK1 Busy flag*/
#define FLASH_FLAG_BANK1_EOP                 FLASH_FLAG_EOP       /*!< FLASH BANK1 End of Operation flag */
#define FLASH_FLAG_BANK1_PGERR               FLASH_FLAG_PGERR     /*!< FLASH BANK1 Program error flag */
#define FLASH_FLAG_BANK1_WRPRTERR            FLASH_FLAG_WRPRTERR  /*!< FLASH BANK1 Write protected error flag */
 
 
/*Functions used for all CH32F10x devices*/
void FLASH_SetLatency(uint32_t FLASH_Latency);
void FLASH_HalfCycleAccessCmd(uint32_t FLASH_HalfCycleAccess);
void FLASH_PrefetchBufferCmd(uint32_t FLASH_PrefetchBuffer);
void FLASH_Unlock(void);
void FLASH_Lock(void);
FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
FLASH_Status FLASH_EraseAllPages(void);
FLASH_Status FLASH_EraseOptionBytes(void);
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);
FLASH_Status FLASH_ProgramOptionByteData(uint32_t Address, uint8_t Data);
FLASH_Status FLASH_EnableWriteProtection(uint32_t FLASH_Pages);
FLASH_Status FLASH_ReadOutProtection(FunctionalState NewState);
FLASH_Status FLASH_UserOptionByteConfig(uint16_t OB_IWDG, uint16_t OB_STOP, uint16_t OB_STDBY);
uint32_t FLASH_GetUserOptionByte(void);
uint32_t FLASH_GetWriteProtectionOptionByte(void);
FlagStatus FLASH_GetReadOutProtectionStatus(void);
FlagStatus FLASH_GetPrefetchBufferStatus(void);
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_Status FLASH_GetStatus(void);
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);

/* New function used for all CH32F10x devices */
void FLASH_UnlockBank1(void);
void FLASH_LockBank1(void);
FLASH_Status FLASH_EraseAllBank1Pages(void);
FLASH_Status FLASH_GetBank1Status(void);
FLASH_Status FLASH_WaitForLastBank1Operation(uint32_t Timeout);

#ifdef __cplusplus
}
#endif


#endif /* __CH32F10x_FLASH_H */

