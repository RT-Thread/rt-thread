/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_sdio.h
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file contains all the functions prototypes for the
*                      SDIO firmware library.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_SDIO_H
#define __STM32F10x_SDIO_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_map.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  u8 SDIO_ClockDiv;
  u32 SDIO_ClockEdge;
  u32 SDIO_ClockBypass;
  u32 SDIO_ClockPowerSave;
  u32 SDIO_BusWide;
  u32 SDIO_HardwareFlowControl;
} SDIO_InitTypeDef;

typedef struct
{
  u32 SDIO_Argument;
  u32 SDIO_CmdIndex;
  u32 SDIO_Response;
  u32 SDIO_Wait;
  u32 SDIO_CPSM;
} SDIO_CmdInitTypeDef;

typedef struct
{
  u32 SDIO_DataTimeOut;
  u32 SDIO_DataLength;
  u32 SDIO_DataBlockSize;
  u32 SDIO_TransferDir;
  u32 SDIO_TransferMode;
  u32 SDIO_DPSM;
} SDIO_DataInitTypeDef;

/* Exported constants --------------------------------------------------------*/
/* SDIO Clock Edge -----------------------------------------------------------*/
#define SDIO_ClockEdge_Rising               ((u32)0x00000000)
#define SDIO_ClockEdge_Falling              ((u32)0x00002000)

#define IS_SDIO_CLOCK_EDGE(EDGE) (((EDGE) == SDIO_ClockEdge_Rising) || \
                                  ((EDGE) == SDIO_ClockEdge_Falling))
/* SDIO Clock Bypass ----------------------------------------------------------*/                                  
#define SDIO_ClockBypass_Disable             ((u32)0x00000000)
#define SDIO_ClockBypass_Enable              ((u32)0x00000400)    

#define IS_SDIO_CLOCK_BYPASS(BYPASS) (((BYPASS) == SDIO_ClockBypass_Disable) || \
                                     ((BYPASS) == SDIO_ClockBypass_Enable))                             

/* SDIO Clock Power Save  ----------------------------------------------------*/ 
#define SDIO_ClockPowerSave_Disable         ((u32)0x00000000)
#define SDIO_ClockPowerSave_Enable          ((u32)0x00000200) 

#define IS_SDIO_CLOCK_POWER_SAVE(SAVE) (((SAVE) == SDIO_ClockPowerSave_Disable) || \
                                        ((SAVE) == SDIO_ClockPowerSave_Enable))

/* SDIO Bus Wide -------------------------------------------------------------*/
#define SDIO_BusWide_1b                     ((u32)0x00000000)
#define SDIO_BusWide_4b                     ((u32)0x00000800)
#define SDIO_BusWide_8b                     ((u32)0x00001000)

#define IS_SDIO_BUS_WIDE(WIDE) (((WIDE) == SDIO_BusWide_1b) || ((WIDE) == SDIO_BusWide_4b) || \
                                ((WIDE) == SDIO_BusWide_8b))
                                
/* SDIO Hardware Flow Control  -----------------------------------------------*/ 
#define SDIO_HardwareFlowControl_Disable    ((u32)0x00000000)
#define SDIO_HardwareFlowControl_Enable     ((u32)0x00004000)

#define IS_SDIO_HARDWARE_FLOW_CONTROL(CONTROL) (((CONTROL) == SDIO_HardwareFlowControl_Disable) || \
                                                ((CONTROL) == SDIO_HardwareFlowControl_Enable))
                                  
/* SDIO Power State ----------------------------------------------------------*/
#define SDIO_PowerState_OFF                 ((u32)0x00000000)
#define SDIO_PowerState_ON                  ((u32)0x00000003)

#define IS_SDIO_POWER_STATE(STATE) (((STATE) == SDIO_PowerState_OFF) || ((STATE) == SDIO_PowerState_ON)) 

/* SDIO Interrupt soucres ----------------------------------------------------*/
#define SDIO_IT_CCRCFAIL                    ((u32)0x00000001)
#define SDIO_IT_DCRCFAIL                    ((u32)0x00000002)
#define SDIO_IT_CTIMEOUT                    ((u32)0x00000004)
#define SDIO_IT_DTIMEOUT                    ((u32)0x00000008)
#define SDIO_IT_TXUNDERR                    ((u32)0x00000010)
#define SDIO_IT_RXOVERR                     ((u32)0x00000020)
#define SDIO_IT_CMDREND                     ((u32)0x00000040)
#define SDIO_IT_CMDSENT                     ((u32)0x00000080)
#define SDIO_IT_DATAEND                     ((u32)0x00000100)
#define SDIO_IT_STBITERR                    ((u32)0x00000200)
#define SDIO_IT_DBCKEND                     ((u32)0x00000400)
#define SDIO_IT_CMDACT                      ((u32)0x00000800)
#define SDIO_IT_TXACT                       ((u32)0x00001000)
#define SDIO_IT_RXACT                       ((u32)0x00002000)
#define SDIO_IT_TXFIFOHE                    ((u32)0x00004000)
#define SDIO_IT_RXFIFOHF                    ((u32)0x00008000)
#define SDIO_IT_TXFIFOF                     ((u32)0x00010000)
#define SDIO_IT_RXFIFOF                     ((u32)0x00020000)
#define SDIO_IT_TXFIFOE                     ((u32)0x00040000)
#define SDIO_IT_RXFIFOE                     ((u32)0x00080000)
#define SDIO_IT_TXDAVL                      ((u32)0x00100000)
#define SDIO_IT_RXDAVL                      ((u32)0x00200000)
#define SDIO_IT_SDIOIT                      ((u32)0x00400000)
#define SDIO_IT_CEATAEND                    ((u32)0x00800000)

#define IS_SDIO_IT(IT) ((((IT) & (u32)0xFF000000) == 0x00) && ((IT) != (u32)0x00))

/* SDIO Command Index  -------------------------------------------------------*/
#define IS_SDIO_CMD_INDEX(INDEX)            ((INDEX) < 0x40)

/* SDIO Response Type --------------------------------------------------------*/
#define SDIO_Response_No                    ((u32)0x00000000)
#define SDIO_Response_Short                 ((u32)0x00000040)
#define SDIO_Response_Long                  ((u32)0x000000C0)

#define IS_SDIO_RESPONSE(RESPONSE) (((RESPONSE) == SDIO_Response_No) || \
                                    ((RESPONSE) == SDIO_Response_Short) || \
                                    ((RESPONSE) == SDIO_Response_Long))

/* SDIO Wait Interrupt State -------------------------------------------------*/
#define SDIO_Wait_No                        ((u32)0x00000000) /* SDIO No Wait, TimeOut is enabled */
#define SDIO_Wait_IT                        ((u32)0x00000100) /* SDIO Wait Interrupt Request */
#define SDIO_Wait_Pend                      ((u32)0x00000200) /* SDIO Wait End of transfer */

#define IS_SDIO_WAIT(WAIT) (((WAIT) == SDIO_Wait_No) || ((WAIT) == SDIO_Wait_IT) || \
                            ((WAIT) == SDIO_Wait_Pend))

/* SDIO CPSM State -----------------------------------------------------------*/
#define SDIO_CPSM_Disable                    ((u32)0x00000000)
#define SDIO_CPSM_Enable                     ((u32)0x00000400)

#define IS_SDIO_CPSM(CPSM) (((CPSM) == SDIO_CPSM_Enable) || ((CPSM) == SDIO_CPSM_Disable))

/* SDIO Response Registers ---------------------------------------------------*/
#define SDIO_RESP1                          ((u32)0x00000000)
#define SDIO_RESP2                          ((u32)0x00000004)
#define SDIO_RESP3                          ((u32)0x00000008)
#define SDIO_RESP4                          ((u32)0x0000000C)

#define IS_SDIO_RESP(RESP) (((RESP) == SDIO_RESP1) || ((RESP) == SDIO_RESP2) || \
                            ((RESP) == SDIO_RESP3) || ((RESP) == SDIO_RESP4))

/* SDIO Data Length ----------------------------------------------------------*/
#define IS_SDIO_DATA_LENGTH(LENGTH) ((LENGTH) <= 0x01FFFFFF)

/* SDIO Data Block Size ------------------------------------------------------*/
#define SDIO_DataBlockSize_1b               ((u32)0x00000000)
#define SDIO_DataBlockSize_2b               ((u32)0x00000010)
#define SDIO_DataBlockSize_4b               ((u32)0x00000020)
#define SDIO_DataBlockSize_8b               ((u32)0x00000030)
#define SDIO_DataBlockSize_16b              ((u32)0x00000040)
#define SDIO_DataBlockSize_32b              ((u32)0x00000050)
#define SDIO_DataBlockSize_64b              ((u32)0x00000060)
#define SDIO_DataBlockSize_128b             ((u32)0x00000070)
#define SDIO_DataBlockSize_256b             ((u32)0x00000080)
#define SDIO_DataBlockSize_512b             ((u32)0x00000090)
#define SDIO_DataBlockSize_1024b            ((u32)0x000000A0)
#define SDIO_DataBlockSize_2048b            ((u32)0x000000B0)
#define SDIO_DataBlockSize_4096b            ((u32)0x000000C0)
#define SDIO_DataBlockSize_8192b            ((u32)0x000000D0)
#define SDIO_DataBlockSize_16384b           ((u32)0x000000E0)

#define IS_SDIO_BLOCK_SIZE(SIZE) (((SIZE) == SDIO_DataBlockSize_1b) || \
                                  ((SIZE) == SDIO_DataBlockSize_2b) || \
                                  ((SIZE) == SDIO_DataBlockSize_4b) || \
                                  ((SIZE) == SDIO_DataBlockSize_8b) || \
                                  ((SIZE) == SDIO_DataBlockSize_16b) || \
                                  ((SIZE) == SDIO_DataBlockSize_32b) || \
                                  ((SIZE) == SDIO_DataBlockSize_64b) || \
                                  ((SIZE) == SDIO_DataBlockSize_128b) || \
                                  ((SIZE) == SDIO_DataBlockSize_256b) || \
                                  ((SIZE) == SDIO_DataBlockSize_512b) || \
                                  ((SIZE) == SDIO_DataBlockSize_1024b) || \
                                  ((SIZE) == SDIO_DataBlockSize_2048b) || \
                                  ((SIZE) == SDIO_DataBlockSize_4096b) || \
                                  ((SIZE) == SDIO_DataBlockSize_8192b) || \
                                  ((SIZE) == SDIO_DataBlockSize_16384b)) 

/* SDIO Transfer Direction ---------------------------------------------------*/
#define SDIO_TransferDir_ToCard             ((u32)0x00000000)
#define SDIO_TransferDir_ToSDIO             ((u32)0x00000002)

#define IS_SDIO_TRANSFER_DIR(DIR) (((DIR) == SDIO_TransferDir_ToCard) || \
                                   ((DIR) == SDIO_TransferDir_ToSDIO))  

/* SDIO Transfer Type --------------------------------------------------------*/
#define SDIO_TransferMode_Block             ((u32)0x00000000)
#define SDIO_TransferMode_Stream            ((u32)0x00000004)

#define IS_SDIO_TRANSFER_MODE(MODE) (((MODE) == SDIO_TransferMode_Stream) || \
                                     ((MODE) == SDIO_TransferMode_Block))                                

/* SDIO DPSM State -----------------------------------------------------------*/
#define SDIO_DPSM_Disable                    ((u32)0x00000000)
#define SDIO_DPSM_Enable                     ((u32)0x00000001)

#define IS_SDIO_DPSM(DPSM) (((DPSM) == SDIO_DPSM_Enable) || ((DPSM) == SDIO_DPSM_Disable))

/* SDIO Flags ----------------------------------------------------------------*/
#define SDIO_FLAG_CCRCFAIL                  ((u32)0x00000001)
#define SDIO_FLAG_DCRCFAIL                  ((u32)0x00000002)
#define SDIO_FLAG_CTIMEOUT                  ((u32)0x00000004)
#define SDIO_FLAG_DTIMEOUT                  ((u32)0x00000008)
#define SDIO_FLAG_TXUNDERR                  ((u32)0x00000010)
#define SDIO_FLAG_RXOVERR                   ((u32)0x00000020)
#define SDIO_FLAG_CMDREND                   ((u32)0x00000040)
#define SDIO_FLAG_CMDSENT                   ((u32)0x00000080)
#define SDIO_FLAG_DATAEND                   ((u32)0x00000100)
#define SDIO_FLAG_STBITERR                  ((u32)0x00000200)
#define SDIO_FLAG_DBCKEND                   ((u32)0x00000400)
#define SDIO_FLAG_CMDACT                    ((u32)0x00000800)
#define SDIO_FLAG_TXACT                     ((u32)0x00001000)
#define SDIO_FLAG_RXACT                     ((u32)0x00002000)
#define SDIO_FLAG_TXFIFOHE                  ((u32)0x00004000)
#define SDIO_FLAG_RXFIFOHF                  ((u32)0x00008000)
#define SDIO_FLAG_TXFIFOF                   ((u32)0x00010000)
#define SDIO_FLAG_RXFIFOF                   ((u32)0x00020000)
#define SDIO_FLAG_TXFIFOE                   ((u32)0x00040000)
#define SDIO_FLAG_RXFIFOE                   ((u32)0x00080000)
#define SDIO_FLAG_TXDAVL                    ((u32)0x00100000)
#define SDIO_FLAG_RXDAVL                    ((u32)0x00200000)
#define SDIO_FLAG_SDIOIT                    ((u32)0x00400000)
#define SDIO_FLAG_CEATAEND                  ((u32)0x00800000)

#define IS_SDIO_FLAG(FLAG) (((FLAG)  == SDIO_FLAG_CCRCFAIL) || \
                            ((FLAG)  == SDIO_FLAG_DCRCFAIL) || \
                            ((FLAG)  == SDIO_FLAG_CTIMEOUT) || \
                            ((FLAG)  == SDIO_FLAG_DTIMEOUT) || \
                            ((FLAG)  == SDIO_FLAG_TXUNDERR) || \
                            ((FLAG)  == SDIO_FLAG_RXOVERR) || \
                            ((FLAG)  == SDIO_FLAG_CMDREND) || \
                            ((FLAG)  == SDIO_FLAG_CMDSENT) || \
                            ((FLAG)  == SDIO_FLAG_DATAEND) || \
                            ((FLAG)  == SDIO_FLAG_STBITERR) || \
                            ((FLAG)  == SDIO_FLAG_DBCKEND) || \
                            ((FLAG)  == SDIO_FLAG_CMDACT) || \
                            ((FLAG)  == SDIO_FLAG_TXACT) || \
                            ((FLAG)  == SDIO_FLAG_RXACT) || \
                            ((FLAG)  == SDIO_FLAG_TXFIFOHE) || \
                            ((FLAG)  == SDIO_FLAG_RXFIFOHF) || \
                            ((FLAG)  == SDIO_FLAG_TXFIFOF) || \
                            ((FLAG)  == SDIO_FLAG_RXFIFOF) || \
                            ((FLAG)  == SDIO_FLAG_TXFIFOE) || \
                            ((FLAG)  == SDIO_FLAG_RXFIFOE) || \
                            ((FLAG)  == SDIO_FLAG_TXDAVL) || \
                            ((FLAG)  == SDIO_FLAG_RXDAVL) || \
                            ((FLAG)  == SDIO_FLAG_SDIOIT) || \
                            ((FLAG)  == SDIO_FLAG_CEATAEND))

#define IS_SDIO_CLEAR_FLAG(FLAG) ((((FLAG) & (u32)0xFF3FF800) == 0x00) && ((FLAG) != (u32)0x00))

#define IS_SDIO_GET_IT(IT) (((IT)  == SDIO_IT_CCRCFAIL) || \
                            ((IT)  == SDIO_IT_DCRCFAIL) || \
                            ((IT)  == SDIO_IT_CTIMEOUT) || \
                            ((IT)  == SDIO_IT_DTIMEOUT) || \
                            ((IT)  == SDIO_IT_TXUNDERR) || \
                            ((IT)  == SDIO_IT_RXOVERR) || \
                            ((IT)  == SDIO_IT_CMDREND) || \
                            ((IT)  == SDIO_IT_CMDSENT) || \
                            ((IT)  == SDIO_IT_DATAEND) || \
                            ((IT)  == SDIO_IT_STBITERR) || \
                            ((IT)  == SDIO_IT_DBCKEND) || \
                            ((IT)  == SDIO_IT_CMDACT) || \
                            ((IT)  == SDIO_IT_TXACT) || \
                            ((IT)  == SDIO_IT_RXACT) || \
                            ((IT)  == SDIO_IT_TXFIFOHE) || \
                            ((IT)  == SDIO_IT_RXFIFOHF) || \
                            ((IT)  == SDIO_IT_TXFIFOF) || \
                            ((IT)  == SDIO_IT_RXFIFOF) || \
                            ((IT)  == SDIO_IT_TXFIFOE) || \
                            ((IT)  == SDIO_IT_RXFIFOE) || \
                            ((IT)  == SDIO_IT_TXDAVL) || \
                            ((IT)  == SDIO_IT_RXDAVL) || \
                            ((IT)  == SDIO_IT_SDIOIT) || \
                            ((IT)  == SDIO_IT_CEATAEND))

#define IS_SDIO_CLEAR_IT(IT) ((((IT) & (u32)0xFF3FF800) == 0x00) && ((IT) != (u32)0x00))
                                                        
/* SDIO Read Wait Mode -------------------------------------------------------*/
#define SDIO_ReadWaitMode_CLK               ((u32)0x00000000)
#define SDIO_ReadWaitMode_DATA2             ((u32)0x00000001)

#define IS_SDIO_READWAIT_MODE(MODE) (((MODE) == SDIO_ReadWaitMode_CLK) || \
                                     ((MODE) == SDIO_ReadWaitMode_DATA2))  

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void SDIO_DeInit(void);
void SDIO_Init(SDIO_InitTypeDef* SDIO_InitStruct);
void SDIO_StructInit(SDIO_InitTypeDef* SDIO_InitStruct);
void SDIO_ClockCmd(FunctionalState NewState);
void SDIO_SetPowerState(u32 SDIO_PowerState);
u32 SDIO_GetPowerState(void);
void SDIO_ITConfig(u32 SDIO_IT, FunctionalState NewState);
void SDIO_DMACmd(FunctionalState NewState);
void SDIO_SendCommand(SDIO_CmdInitTypeDef *SDIO_CmdInitStruct);
void SDIO_CmdStructInit(SDIO_CmdInitTypeDef* SDIO_CmdInitStruct);
u8 SDIO_GetCommandResponse(void);
u32 SDIO_GetResponse(u32 SDIO_RESP);
void SDIO_DataConfig(SDIO_DataInitTypeDef* SDIO_DataInitStruct);
void SDIO_DataStructInit(SDIO_DataInitTypeDef* SDIO_DataInitStruct);
u32 SDIO_GetDataCounter(void);
u32 SDIO_ReadData(void);
void SDIO_WriteData(u32 Data);
u32 SDIO_GetFIFOCount(void);
void SDIO_StartSDIOReadWait(FunctionalState NewState);
void SDIO_StopSDIOReadWait(FunctionalState NewState);
void SDIO_SetSDIOReadWaitMode(u32 SDIO_ReadWaitMode);
void SDIO_SetSDIOOperation(FunctionalState NewState);
void SDIO_SendSDIOSuspendCmd(FunctionalState NewState);
void SDIO_CommandCompletionCmd(FunctionalState NewState);
void SDIO_CEATAITCmd(FunctionalState NewState);
void SDIO_SendCEATACmd(FunctionalState NewState);
FlagStatus SDIO_GetFlagStatus(u32 SDIO_FLAG);
void SDIO_ClearFlag(u32 SDIO_FLAG);
ITStatus SDIO_GetITStatus(u32 SDIO_IT);
void SDIO_ClearITPendingBit(u32 SDIO_IT);

#endif /* __STM32F10x_SDIO_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
