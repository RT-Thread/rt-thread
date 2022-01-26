////////////////////////////////////////////////////////////////////////////////
/// @file     hal_flash.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE FLASH
///           FIRMWARE LIBRARY.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#ifndef __HAL_FLASH_H
#define __HAL_FLASH_H

// Files includes
#include "types.h"
#include "reg_common.h"
#include "reg_flash.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup FLASH_HAL
/// @brief FLASH HAL modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup FLASH_Exported_Types
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  FLASH Status
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    FLASH_BUSY = 1,                                                             ///< FLASH busy status
    FLASH_ERROR_PG,                                                             ///< FLASH programming error status
    FLASH_ERROR_WRP,                                                            ///< FLASH write protection error status
    FLASH_COMPLETE,                                                             ///< FLASH end of operation status
    FLASH_TIMEOUT                                                               ///< FLASH Last operation timed out status
} FLASH_Status;

////////////////////////////////////////////////////////////////////////////////
/// @brief  FLASH Latency
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    FLASH_Latency_0 = FLASH_ACR_LATENCY_0,                                      ///< FLASH Zero Latency cycle
    FLASH_Latency_1 = FLASH_ACR_LATENCY_1,                                      ///< FLASH One Latency cycle
    FLASH_Latency_2 = FLASH_ACR_LATENCY_2,                                      ///< FLASH Two Latency cycles
    FLASH_Latency_3 = FLASH_ACR_LATENCY_3                                       ///< FLASH Three Latency cycles
} FLASH_Latency_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  Half_Cycle_Enable_Disable
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    FLASH_HalfCycleAccess_Enable  = FLASH_ACR_HLFCYA,                           ///< FLASH Half Cycle Enable
    FLASH_HalfCycleAccess_Disable = (s32)~FLASH_ACR_HLFCYA                              ///< FLASH Half Cycle Disable
} FLASH_HalfCycleAccess_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  Prefetch_Buffer_Enable_Disable
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    FLASH_PrefetchBuffer_Enable  = FLASH_ACR_PRFTBE,                            ///< FLASH Prefetch Buffer Enable
    FLASH_PrefetchBuffer_Disable = (s32)~FLASH_ACR_PRFTBE                           ///< FLASH Prefetch Buffer Disable
} FLASH_PrefetchBuffer_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  Option_Bytes_IWatchdog
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    OB_IWDG_SW = 0x0001,                                                        ///< Software IWDG selected
    OB_IWDG_HW = 0x0000                                                         ///< Hardware IWDG selected
} OB_IWDG_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  Option_Bytes_nRST_STOP
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    OB_STOP_NoRST = 0x0002,                                                     ///< No reset generated when entering in STOP
    OB_STOP_RST   = 0x0000                                                      ///< Reset generated when entering in STOP
} OB_STOP_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  Option_Bytes_nRST_STDBY
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    OB_STDBY_NoRST = 0x0004,                                                    ///< No reset generated when entering in STANDBY
    OB_STDBY_RST   = 0x0000                                                     ///< Reset generated when entering in STANDBY
} OB_STDBY_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  FLASH_Interrupts
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    FLASH_IT_ERROR = FLASH_CR_ERRIE,                                            ///< FPEC error interrupt source
    FLASH_IT_EOP   = FLASH_CR_EOPIE                                             ///< End of FLASH Operation Interrupt source
} FLASH_IT_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  FLASH_Flags
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    FLASH_FLAG_EOP      = FLASH_SR_EOP,                                         ///< FLASH End of Operation flag
    FLASH_FLAG_PGERR    = FLASH_SR_PGERR,                                       ///< FLASH Program error flag
    FLASH_FLAG_WRPRTERR = FLASH_SR_WRPRTERR,                                    ///< FLASH Write protected error flag
    FLASH_FLAG_BSY      = FLASH_SR_BUSY,                                        ///< FLASH Busy flag
    FLASH_FLAG_OPTERR   = FLASH_OBR_OPTERR                                      ///< FLASH Option Byte error flag
} FLASH_FLAG_TypeDef;

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup FLASH_Exported_Constants
/// @{


#define RDP_Key ((u16)0x00A5)
#define FLASH_KEY1 ((u32)0x45670123)
#define FLASH_KEY2 ((u32)0xCDEF89AB)
#define EraseTimeout ((u32)0x00000FFF)
#define ProgramTimeout ((u32)0x0000000F)

#define FLASH_WRProt_Pages0to3      ((u32)0x00000001)  ///< Write protection of page 0 to 3
#define FLASH_WRProt_Pages4to7      ((u32)0x00000002)  ///< Write protection of page 4 to 7
#define FLASH_WRProt_Pages8to11     ((u32)0x00000004)  ///< Write protection of page 8 to 11
#define FLASH_WRProt_Pages12to15    ((u32)0x00000008)  ///< Write protection of page 12 to 15
#define FLASH_WRProt_Pages16to19    ((u32)0x00000010)  ///< Write protection of page 16 to 19
#define FLASH_WRProt_Pages20to23    ((u32)0x00000020)  ///< Write protection of page 20 to 23
#define FLASH_WRProt_Pages24to27    ((u32)0x00000040)  ///< Write protection of page 24 to 27
#define FLASH_WRProt_Pages28to31    ((u32)0x00000080)  ///< Write protection of page 28 to 31
#define FLASH_WRProt_Pages32to35    ((u32)0x00000100)  ///< Write protection of page 32 to 35
#define FLASH_WRProt_Pages36to39    ((u32)0x00000200)  ///< Write protection of page 36 to 39
#define FLASH_WRProt_Pages40to43    ((u32)0x00000400)  ///< Write protection of page 40 to 43
#define FLASH_WRProt_Pages44to47    ((u32)0x00000800)  ///< Write protection of page 44 to 47
#define FLASH_WRProt_Pages48to51    ((u32)0x00001000)  ///< Write protection of page 48 to 51
#define FLASH_WRProt_Pages52to55    ((u32)0x00002000)  ///< Write protection of page 52 to 55
#define FLASH_WRProt_Pages56to59    ((u32)0x00004000)  ///< Write protection of page 56 to 59
#define FLASH_WRProt_Pages60to63    ((u32)0x00008000)  ///< Write protection of page 60 to 63
#define FLASH_WRProt_Pages64to67    ((u32)0x00010000)  ///< Write protection of page 64 to 67
#define FLASH_WRProt_Pages68to71    ((u32)0x00020000)  ///< Write protection of page 68 to 71
#define FLASH_WRProt_Pages72to75    ((u32)0x00040000)  ///< Write protection of page 72 to 75
#define FLASH_WRProt_Pages76to79    ((u32)0x00080000)  ///< Write protection of page 76 to 79
#define FLASH_WRProt_Pages80to83    ((u32)0x00100000)  ///< Write protection of page 80 to 83
#define FLASH_WRProt_Pages84to87    ((u32)0x00200000)  ///< Write protection of page 84 to 87
#define FLASH_WRProt_Pages88to91    ((u32)0x00400000)  ///< Write protection of page 88 to 91
#define FLASH_WRProt_Pages92to95    ((u32)0x00800000)  ///< Write protection of page 92 to 95
#define FLASH_WRProt_Pages96to99    ((u32)0x01000000)  ///< Write protection of page 96 to 99
#define FLASH_WRProt_Pages100to103  ((u32)0x02000000)  ///< Write protection of page 100 to 103
#define FLASH_WRProt_Pages104to107  ((u32)0x04000000)  ///< Write protection of page 104 to 107
#define FLASH_WRProt_Pages108to111  ((u32)0x08000000)  ///< Write protection of page 108 to 111
#define FLASH_WRProt_Pages112to115  ((u32)0x10000000)  ///< Write protection of page 112 to 115
#define FLASH_WRProt_Pages116to119  ((u32)0x20000000)  ///< Write protection of page 115 to 119
#define FLASH_WRProt_Pages120to123  ((u32)0x40000000)  ///< Write protection of page 120 to 123
#define FLASH_WRProt_Pages124to127  ((u32)0x80000000)  ///< Write protection of page 124 to 127

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup FLASH_Exported_Variables
/// @{

#ifdef _HAL_FLASH_C_

#define GLOBAL
#else
#define GLOBAL extern
#endif

#undef GLOBAL

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup FLASH_Exported_Functions
/// @{
void  FLASH_SetLatency(FLASH_Latency_TypeDef latency);
void  FLASH_HalfCycleAccessCmd(FLASH_HalfCycleAccess_TypeDef half_cycle_access);
void  FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_TypeDef prefetch_buffer);
void  FLASH_Unlock(void);
void  FLASH_Lock(void);
void  FLASH_OPTB_Enable(void);
void  FLASH_ITConfig(FLASH_IT_TypeDef interrupt, FunctionalState state);
void  FLASH_ClearFlag(u16 flag);
void  exFLASH_EraseEE(u32 page_address);
void  exFLASH_ProgramEE(u16* buf, u32 address, u16 len);
void  exFLASH_WriteEE(u16* buf, u32 page_address, u16 len);
void* exFLASH_Locate(u32 page_address, u16 len);
void* exFLASH_ReadEE(u32 page_address, u16 len);

u8  exFLASH_FindEmpty(u16* ptr, u16 len);
u32 FLASH_GetUserOptionByte(void);
u32 FLASH_GetWriteProtectionOptionByte(void);

FLASH_Status FLASH_ErasePage(u32 page_address);
FLASH_Status FLASH_EraseAllPages(void);
FLASH_Status FLASH_EraseOptionBytes(void);
FLASH_Status FLASH_EraseProtect(void);
FLASH_Status FLASH_ProgramHalfWord(u32 address, u16 data);
FLASH_Status FLASH_ProgramWord(u32 address, u32 data);
FLASH_Status FLASH_ProgramOptionHalfWord(u32 address, u16 data);
FLASH_Status FLASH_ProgramOptionByteData(u32 address, u8 data);
FLASH_Status FLASH_ProgramProtect(u32 address, u16 data);
FLASH_Status FLASH_EnableWriteProtection(u32 page);
FLASH_Status FLASH_UserOptionByteConfig(OB_IWDG_TypeDef ob_iwdg, OB_STOP_TypeDef ob_stop, OB_STDBY_TypeDef ob_standby);
FLASH_Status FLASH_GetStatus(void);
FLASH_Status FLASH_WaitForLastOperation(u32 time_out);
FLASH_Status FLASH_ReadOutProtection(FunctionalState state);
FlagStatus   FLASH_GetPrefetchBufferStatus(void);
FlagStatus   FLASH_GetFlagStatus(u16 flag);

/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif //__HAL_FLASH_H 
////////////////////////////////////////////////////////////////////////////////
