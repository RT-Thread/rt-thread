/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : stm32f10x_fsmc.h
* Author             : MCD Application Team
* Version            : V2.0.3Patch1
* Date               : 04/06/2009
* Description        : This file contains all the functions prototypes for the
*                      FSMC firmware library.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_FSMC_H
#define __STM32F10x_FSMC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_map.h"

/* Exported types ------------------------------------------------------------*/
/* Timing parameters For NOR/SRAM Banks */
typedef struct
{
  u32 FSMC_AddressSetupTime;
  u32 FSMC_AddressHoldTime;
  u32 FSMC_DataSetupTime;
  u32 FSMC_BusTurnAroundDuration;
  u32 FSMC_CLKDivision;
  u32 FSMC_DataLatency;
  u32 FSMC_AccessMode;
}FSMC_NORSRAMTimingInitTypeDef;

/* FSMC NOR/SRAM Init structure definition */
typedef struct
{
  u32 FSMC_Bank;
  u32 FSMC_DataAddressMux;
  u32 FSMC_MemoryType;
  u32 FSMC_MemoryDataWidth;
  u32 FSMC_BurstAccessMode;
  u32 FSMC_WaitSignalPolarity;
  u32 FSMC_WrapMode;
  u32 FSMC_WaitSignalActive;
  u32 FSMC_WriteOperation;
  u32 FSMC_WaitSignal;
  u32 FSMC_ExtendedMode;
  u32 FSMC_WriteBurst;
  /* Timing Parameters for write and read access if the  ExtendedMode is not used*/
  FSMC_NORSRAMTimingInitTypeDef* FSMC_ReadWriteTimingStruct;
  /* Timing Parameters for write access if the  ExtendedMode is used*/
  FSMC_NORSRAMTimingInitTypeDef* FSMC_WriteTimingStruct;
}FSMC_NORSRAMInitTypeDef;

/* Timing parameters For FSMC NAND and PCCARD Banks */
typedef struct
{
  u32 FSMC_SetupTime;
  u32 FSMC_WaitSetupTime;
  u32 FSMC_HoldSetupTime;
  u32 FSMC_HiZSetupTime;
}FSMC_NAND_PCCARDTimingInitTypeDef;

/* FSMC NAND Init structure definition */
typedef struct
{
  u32 FSMC_Bank;
  u32 FSMC_Waitfeature;
  u32 FSMC_MemoryDataWidth;
  u32 FSMC_ECC;
  u32 FSMC_ECCPageSize;
  u32 FSMC_TCLRSetupTime;
  u32 FSMC_TARSetupTime;
  /* FSMC Common Space Timing */
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_CommonSpaceTimingStruct;
  /* FSMC Attribute Space Timing */
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_AttributeSpaceTimingStruct;
}FSMC_NANDInitTypeDef;

/* FSMC PCCARD Init structure definition */
typedef struct
{
  u32 FSMC_Waitfeature;
  u32 FSMC_TCLRSetupTime;
  u32 FSMC_TARSetupTime;
  /* FSMC Common Space Timing */
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_CommonSpaceTimingStruct;
  /* FSMC Attribute Space Timing */
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_AttributeSpaceTimingStruct;
  /* FSMC IO Space Timing */
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_IOSpaceTimingStruct;
}FSMC_PCCARDInitTypeDef;

/* Exported constants --------------------------------------------------------*/
/*-------------------------------FSMC Banks definitions ----------------------*/
#define FSMC_Bank1_NORSRAM1                             ((u32)0x00000000)
#define FSMC_Bank1_NORSRAM2                             ((u32)0x00000002)
#define FSMC_Bank1_NORSRAM3                             ((u32)0x00000004)
#define FSMC_Bank1_NORSRAM4                             ((u32)0x00000006)
#define FSMC_Bank2_NAND                                 ((u32)0x00000010)
#define FSMC_Bank3_NAND                                 ((u32)0x00000100)
#define FSMC_Bank4_PCCARD                               ((u32)0x00001000)

#define IS_FSMC_NORSRAM_BANK(BANK) (((BANK) == FSMC_Bank1_NORSRAM1) || \
                                    ((BANK) == FSMC_Bank1_NORSRAM2) || \
                                    ((BANK) == FSMC_Bank1_NORSRAM3) || \
                                    ((BANK) == FSMC_Bank1_NORSRAM4))                           


#define IS_FSMC_NAND_BANK(BANK) (((BANK) == FSMC_Bank2_NAND) || \
                                 ((BANK) == FSMC_Bank3_NAND))

#define IS_FSMC_GETFLAG_BANK(BANK) (((BANK) == FSMC_Bank2_NAND) || \
                                    ((BANK) == FSMC_Bank3_NAND) || \
                                    ((BANK) == FSMC_Bank4_PCCARD))
                                    
#define IS_FSMC_IT_BANK(BANK) (((BANK) == FSMC_Bank2_NAND) || \
                               ((BANK) == FSMC_Bank3_NAND) || \
                               ((BANK) == FSMC_Bank4_PCCARD))                                    


/*------------------------------- NOR/SRAM Banks -----------------------------*/
/* FSMC Data/Address Bus Multiplexing ----------------------------------------*/
#define FSMC_DataAddressMux_Disable                       ((u32)0x00000000)
#define FSMC_DataAddressMux_Enable                        ((u32)0x00000002)

#define IS_FSMC_MUX(MUX) (((MUX) == FSMC_DataAddressMux_Disable) || \
                          ((MUX) == FSMC_DataAddressMux_Enable))                           

/* FSMC Memory Type ----------------------------------------------------------*/
#define FSMC_MemoryType_SRAM                            ((u32)0x00000000)
#define FSMC_MemoryType_PSRAM                           ((u32)0x00000004)
#define FSMC_MemoryType_NOR                             ((u32)0x00000008)

#define IS_FSMC_MEMORY(MEMORY) (((MEMORY) == FSMC_MemoryType_SRAM) || \
                                ((MEMORY) == FSMC_MemoryType_PSRAM)|| \
                                ((MEMORY) == FSMC_MemoryType_NOR))
                                     
/* FSMC  Data Width ----------------------------------------------------------*/
#define FSMC_MemoryDataWidth_8b                         ((u32)0x00000000)
#define FSMC_MemoryDataWidth_16b                        ((u32)0x00000010)

#define IS_FSMC_MEMORY_WIDTH(WIDTH) (((WIDTH) == FSMC_MemoryDataWidth_8b) || \
                                     ((WIDTH) == FSMC_MemoryDataWidth_16b))
                                      
                               
/* FSMC Burst Access Mode ----------------------------------------------------*/
#define FSMC_BurstAccessMode_Disable                    ((u32)0x00000000) 
#define FSMC_BurstAccessMode_Enable                     ((u32)0x00000100)

#define IS_FSMC_BURSTMODE(STATE) (((STATE) == FSMC_BurstAccessMode_Disable) || \
                                  ((STATE) == FSMC_BurstAccessMode_Enable))

/* FSMC Wait Signal Polarity -------------------------------------------------*/                                  
#define FSMC_WaitSignalPolarity_Low                     ((u32)0x00000000)
#define FSMC_WaitSignalPolarity_High                    ((u32)0x00000200)

#define IS_FSMC_WAIT_POLARITY(POLARITY) (((POLARITY) == FSMC_WaitSignalPolarity_Low) || \
                                         ((POLARITY) == FSMC_WaitSignalPolarity_High)) 
                                        
/* FSMC Wrap Mode ------------------------------------------------------------*/ 
#define FSMC_WrapMode_Disable                           ((u32)0x00000000)
#define FSMC_WrapMode_Enable                            ((u32)0x00000400) 

#define IS_FSMC_WRAP_MODE(MODE) (((MODE) == FSMC_WrapMode_Disable) || \
                                 ((MODE) == FSMC_WrapMode_Enable))
                                 
/* FSMC Wait Timing ----------------------------------------------------------*/                                 
#define FSMC_WaitSignalActive_BeforeWaitState           ((u32)0x00000000)
#define FSMC_WaitSignalActive_DuringWaitState           ((u32)0x00000800) 

#define IS_FSMC_WAIT_SIGNAL_ACTIVE(ACTIVE) (((ACTIVE) == FSMC_WaitSignalActive_BeforeWaitState) || \
                                            ((ACTIVE) == FSMC_WaitSignalActive_DuringWaitState))
                                    
/* FSMC Write Operation ------------------------------------------------------*/
#define FSMC_WriteOperation_Disable                     ((u32)0x00000000)
#define FSMC_WriteOperation_Enable                      ((u32)0x00001000)

#define IS_FSMC_WRITE_OPERATION(OPERATION) (((OPERATION) == FSMC_WriteOperation_Disable) || \
                                            ((OPERATION) == FSMC_WriteOperation_Enable))
                              
/* FSMC Wait Signal ----------------------------------------------------------*/
#define FSMC_WaitSignal_Disable                         ((u32)0x00000000)
#define FSMC_WaitSignal_Enable                          ((u32)0x00002000) 

#define IS_FSMC_WAITE_SIGNAL(SIGNAL) (((SIGNAL) == FSMC_WaitSignal_Disable) || \
                                      ((SIGNAL) == FSMC_WaitSignal_Enable))

/* FSMC Extended Mode --------------------------------------------------------*/
#define FSMC_ExtendedMode_Disable                       ((u32)0x00000000)
#define FSMC_ExtendedMode_Enable                        ((u32)0x00004000)                                  

#define IS_FSMC_EXTENDED_MODE(MODE) (((MODE) == FSMC_ExtendedMode_Disable) || \
                                     ((MODE) == FSMC_ExtendedMode_Enable)) 
                                                                 
/* FSMC Write Burst ----------------------------------------------------------*/                                  
#define FSMC_WriteBurst_Disable                         ((u32)0x00000000)
#define FSMC_WriteBurst_Enable                          ((u32)0x00080000) 

#define IS_FSMC_WRITE_BURST(BURST) (((BURST) == FSMC_WriteBurst_Disable) || \
                                    ((BURST) == FSMC_WriteBurst_Enable))

/* FSMC Address Setup Time ---------------------------------------------------*/
#define IS_FSMC_ADDRESS_SETUP_TIME(TIME) ((TIME) <= 0xF)

/* FSMC Address Hold Time ----------------------------------------------------*/
#define IS_FSMC_ADDRESS_HOLD_TIME(TIME) ((TIME) <= 0xF)

/* FSMC Data Setup Time ------------------------------------------------------*/
#define IS_FSMC_DATASETUP_TIME(TIME) (((TIME) > 0) && ((TIME) <= 0xFF))

/* FSMC Bus Turn around Duration ---------------------------------------------*/
#define IS_FSMC_TURNAROUND_TIME(TIME) ((TIME) <= 0xF)

/* FSMC CLK Division ---------------------------------------------------------*/
#define IS_FSMC_CLK_DIV(DIV) ((DIV) <= 0xF)

/* FSMC Data Latency ---------------------------------------------------------*/
#define IS_FSMC_DATA_LATENCY(LATENCY) ((LATENCY) <= 0xF)

/* FSMC Access Mode ----------------------------------------------------------*/
#define FSMC_AccessMode_A                               ((u32)0x00000000)
#define FSMC_AccessMode_B                               ((u32)0x10000000) 
#define FSMC_AccessMode_C                               ((u32)0x20000000)
#define FSMC_AccessMode_D                               ((u32)0x30000000)

#define IS_FSMC_ACCESS_MODE(MODE) (((MODE) == FSMC_AccessMode_A) || \
                                   ((MODE) == FSMC_AccessMode_B) || \
                                   ((MODE) == FSMC_AccessMode_C) || \
                                   ((MODE) == FSMC_AccessMode_D)) 
                                  
/*----------------------------- NAND and PCCARD Banks ------------------------*/
/* FSMC Wait feature ---------------------------------------------------------*/
#define FSMC_Waitfeature_Disable                        ((u32)0x00000000)
#define FSMC_Waitfeature_Enable                         ((u32)0x00000002)

#define IS_FSMC_WAIT_FEATURE(FEATURE) (((FEATURE) == FSMC_Waitfeature_Disable) || \
                                       ((FEATURE) == FSMC_Waitfeature_Enable))
                                    
/* FSMC Memory Data Width ----------------------------------------------------*/
#define FSMC_MemoryDataWidth_8b                         ((u32)0x00000000)
#define FSMC_MemoryDataWidth_16b                        ((u32)0x00000010)

#define IS_FSMC_DATA_WIDTH(WIDTH) (((WIDTH) == FSMC_MemoryDataWidth_8b) || \
                                   ((WIDTH) == FSMC_MemoryDataWidth_16b))
                                    
/* FSMC ECC ------------------------------------------------------------------*/
#define FSMC_ECC_Disable                                ((u32)0x00000000)
#define FSMC_ECC_Enable                                 ((u32)0x00000040)

#define IS_FSMC_ECC_STATE(STATE) (((STATE) == FSMC_ECC_Disable) || \
                                  ((STATE) == FSMC_ECC_Enable))
                                            
/* FSMC ECC Page Size --------------------------------------------------------*/
#define FSMC_ECCPageSize_256Bytes                       ((u32)0x00000000)
#define FSMC_ECCPageSize_512Bytes                       ((u32)0x00020000)
#define FSMC_ECCPageSize_1024Bytes                      ((u32)0x00040000)
#define FSMC_ECCPageSize_2048Bytes                      ((u32)0x00060000)
#define FSMC_ECCPageSize_4096Bytes                      ((u32)0x00080000)
#define FSMC_ECCPageSize_8192Bytes                      ((u32)0x000A0000)

#define IS_FSMC_ECCPAGE_SIZE(SIZE) (((SIZE) == FSMC_ECCPageSize_256Bytes) || \
                                    ((SIZE) == FSMC_ECCPageSize_512Bytes) || \
                                    ((SIZE) == FSMC_ECCPageSize_1024Bytes) || \
                                    ((SIZE) == FSMC_ECCPageSize_2048Bytes) || \
                                    ((SIZE) == FSMC_ECCPageSize_4096Bytes) || \
                                    ((SIZE) == FSMC_ECCPageSize_8192Bytes))
                                                              
/* FSMC TCLR Setup Time ------------------------------------------------------*/
#define IS_FSMC_TCLR_TIME(TIME) ((TIME) <= 0xFF)

/* FSMC TAR Setup Time -------------------------------------------------------*/
#define IS_FSMC_TAR_TIME(TIME) ((TIME) <= 0xFF)

/* FSMC Setup Time ----------------------------------------------------*/
#define IS_FSMC_SETUP_TIME(TIME) ((TIME) <= 0xFF)

/* FSMC Wait Setup Time -----------------------------------------------*/
#define IS_FSMC_WAIT_TIME(TIME) ((TIME) <= 0xFF)

/* FSMC Hold Setup Time -----------------------------------------------*/
#define IS_FSMC_HOLD_TIME(TIME) ((TIME) <= 0xFF)

/* FSMC HiZ Setup Time ------------------------------------------------*/
#define IS_FSMC_HIZ_TIME(TIME) ((TIME) <= 0xFF)

/* FSMC Interrupt sources ----------------------------------------------------*/
#define FSMC_IT_RisingEdge                              ((u32)0x00000008)
#define FSMC_IT_Level                                   ((u32)0x00000010)
#define FSMC_IT_FallingEdge                             ((u32)0x00000020)

#define IS_FSMC_IT(IT) ((((IT) & (u32)0xFFFFFFC7) == 0x00000000) && ((IT) != 0x00000000))

#define IS_FSMC_GET_IT(IT) (((IT) == FSMC_IT_RisingEdge) || \
                            ((IT) == FSMC_IT_Level) || \
                            ((IT) == FSMC_IT_FallingEdge)) 

/* FSMC Flags ----------------------------------------------------------------*/
#define FSMC_FLAG_RisingEdge                            ((u32)0x00000001)
#define FSMC_FLAG_Level                                 ((u32)0x00000002)
#define FSMC_FLAG_FallingEdge                           ((u32)0x00000004)
#define FSMC_FLAG_FEMPT                                 ((u32)0x00000040)

#define IS_FSMC_GET_FLAG(FLAG) (((FLAG) == FSMC_FLAG_RisingEdge) || \
                                ((FLAG) == FSMC_FLAG_Level) || \
                                ((FLAG) == FSMC_FLAG_FallingEdge) || \
                                ((FLAG) == FSMC_FLAG_FEMPT))

#define IS_FSMC_CLEAR_FLAG(FLAG) ((((FLAG) & (u32)0xFFFFFFF8) == 0x00000000) && ((FLAG) != 0x00000000))                                                                                                                                                                                                                                                                                                                                  
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void FSMC_NORSRAMDeInit(u32 FSMC_Bank);
void FSMC_NANDDeInit(u32 FSMC_Bank);
void FSMC_PCCARDDeInit(void);
void FSMC_NORSRAMInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct);
void FSMC_NANDInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct);
void FSMC_PCCARDInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct);
void FSMC_NORSRAMStructInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct);
void FSMC_NANDStructInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct);
void FSMC_PCCARDStructInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct);
void FSMC_NORSRAMCmd(u32 FSMC_Bank, FunctionalState NewState);
void FSMC_NANDCmd(u32 FSMC_Bank, FunctionalState NewState);
void FSMC_PCCARDCmd(FunctionalState NewState);
void FSMC_NANDECCCmd(u32 FSMC_Bank, FunctionalState NewState);
u32 FSMC_GetECC(u32 FSMC_Bank);
void FSMC_ITConfig(u32 FSMC_Bank, u32 FSMC_IT, FunctionalState NewState);
FlagStatus FSMC_GetFlagStatus(u32 FSMC_Bank, u32 FSMC_FLAG);
void FSMC_ClearFlag(u32 FSMC_Bank, u32 FSMC_FLAG);
ITStatus FSMC_GetITStatus(u32 FSMC_Bank, u32 FSMC_IT);
void FSMC_ClearITPendingBit(u32 FSMC_Bank, u32 FSMC_IT);

#endif /*__STM32F10x_FSMC_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
