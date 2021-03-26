/**
 ******************************************************************************
  * @brief   SDIO header file of the firmware library
 ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F10X_SDIO_H
#define __GD32F10X_SDIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @addtogroup SDIO
  * @{
  */

/** @defgroup SDIO_Exported_Types
  * @{
  */

typedef struct {
    uint32_t SDIO_ClockEdge;             /*!< Configure the SDIO Clock edge on which the bit capture is made.
                                                        This parameter can be a value of @ref SDIO_Clock_Edge*/
    uint32_t SDIO_ClockBypassState;      /*!< Configure the SDIO Clock divider bypass mode
                                                        This parameter can be a value of @ref SDIO_Clock_Bypass_State  */
    uint32_t SDIO_ClockPWRSave;          /*!< Configure the SDIO Clock output powersave mode when the bus is idle.
                                                        This parameter can be a value of @ref SDIO_Clock_Power_Save */
    uint32_t SDIO_BusMode;               /*!< Configure the SDIO bus mode.
                                                        This parameter can be a value of @ref SDIO_Bus_Mode */
    uint32_t SDIO_HWFlowCtrlState;       /*!< Configure the SDIO hardware flow control is enabled or disabled.
                                                        This parameter can be a value of @ref SDIO_HW_Flow_Control_State */
    uint8_t SDIO_ClockDiv;               /*!< Configure the clock frequency prescaler of the SDIO controller.
                                                        This parameter can be a value between 0x00 and 0xFF. */
} SDIO_InitPara;

typedef struct {
    uint32_t SDIO_CMDParameter;          /*!< Configure the SDIO command parameter which is sent to
                                                        a card as part of a command message. */
    uint32_t SDIO_CMDIndex;              /*!< Configure the SDIO command index. */

    uint32_t SDIO_ResponseType;          /*!< Configure the SDIO response type.
                                                        This parameter can be a value of @ref SDIO_Response_Type */
    uint32_t SDIO_WaitINTState;          /*!< Configure whether SDIO wait-for-interrupt request is enabled or disabled.
                                                        This parameter can be a value of @ref SDIO_Wait_Interrupt_State */
    uint32_t SDIO_CSMState;              /*!< Configure  SDIO Command state machine (CSM) is enabled or disabled.
                                                        This parameter can be a value of @ref SDIO_CSM_State */
} SDIO_CmdInitPara;

typedef struct {
    uint32_t SDIO_DataTimeOut;           /*!< Configure the data timeout period in card bus clock periods. */

    uint32_t SDIO_DataLength;            /*!< Configure the number of data bytes to be transferred. */

    uint32_t SDIO_DataBlockSize;         /*!< Configure the data block size for block transfer.
                                                        This parameter can be a value of @ref SDIO_Data_Block_Size */
    uint32_t SDIO_TransDirection;        /*!< Configure the data transfer direction, read or write.
                                                        This parameter can be a value of @ref SDIO_Transfer_Direction */
    uint32_t SDIO_TransMode;             /*!< Configure whether data transfer is in stream or block mode.
                                                        This parameter can be a value of @ref SDIO_Transfer_Mode */
    uint32_t SDIO_DSMState;              /*!< Configure whether SDIO Data state machine (DSM) is enabled or disabled.
                                                        This parameter can be a value of @ref SDIO_DSM_State */
} SDIO_DataInitPara;

/**
  * @}
  */

/** @defgroup SDIO_Exported_Constants
  * @{
  */

/** @defgroup SDIO_Clock_Edge
  * @{
  */
#define SDIO_CLOCKEDGE_RISING               ((uint32_t)0x00000000)
#define SDIO_CLOCKEDGE_FALLING              ((uint32_t)0x00002000)

/**
  * @}
  */

/** @defgroup SDIO_Clock_Bypass_State
  * @{
  */
#define SDIO_CLOCKBYPASSSTATE_DISABLE       ((uint32_t)0x00000000)
#define SDIO_CLOCKBYPASSSTATE_ENABLE        ((uint32_t)0x00000400)

/**
  * @}
  */

/** @defgroup SDIO_Clock_PWR_Save
  * @{
  */
#define SDIO_CLOCKPWRSAVE_DISABLE           ((uint32_t)0x00000000)
#define SDIO_CLOCKPWRSAVE_ENABLE            ((uint32_t)0x00000200)

/**
  * @}
  */

/** @defgroup SDIO_Bus_Mode
  * @{
  */
#define SDIO_BUSMODE_1B                     ((uint32_t)0x00000000)
#define SDIO_BUSMODE_4B                     ((uint32_t)0x00000800)
#define SDIO_BUSMODE_8B                     ((uint32_t)0x00001000)

/**
  * @}
  */

/** @defgroup SDIO_HW_Flow_Control_State
  * @{
  */

#define SDIO_HWFLOWCTRLSTATE_DISABLE        ((uint32_t)0x00000000)
#define SDIO_HWFLOWCTRLSTATE_ENABLE         ((uint32_t)0x00004000)

/**
  * @}
  */

/** @defgroup SDIO_Power_State
  * @{
  */
#define SDIO_PWRSTATE_OFF                   ((uint32_t)0x00000000)
#define SDIO_PWRSTATE_ON                    ((uint32_t)0x00000003)

/**
  * @}
  */

/** @defgroup SDIO_Interrupt_sources
  * @{
  */
#define SDIO_INT_CCRCFAIL                   ((uint32_t)0x00000001)
#define SDIO_INT_DTCRCFAIL                  ((uint32_t)0x00000002)
#define SDIO_INT_CMDTMOUT                   ((uint32_t)0x00000004)
#define SDIO_INT_DTTMOUT                    ((uint32_t)0x00000008)
#define SDIO_INT_TXURE                      ((uint32_t)0x00000010)
#define SDIO_INT_RXORE                      ((uint32_t)0x00000020)
#define SDIO_INT_CMDREND                    ((uint32_t)0x00000040)
#define SDIO_INT_CMDSENT                    ((uint32_t)0x00000080)
#define SDIO_INT_DTEND                      ((uint32_t)0x00000100)
#define SDIO_INT_STBITE                     ((uint32_t)0x00000200)
#define SDIO_INT_DTBLKEND                   ((uint32_t)0x00000400)
#define SDIO_INT_CMDRUN                     ((uint32_t)0x00000800)
#define SDIO_INT_TXRUN                      ((uint32_t)0x00001000)
#define SDIO_INT_RXRUN                      ((uint32_t)0x00002000)
#define SDIO_INT_TXFIFOHE                   ((uint32_t)0x00004000)
#define SDIO_INT_RXFIFOHF                   ((uint32_t)0x00008000)
#define SDIO_INT_TXFIFOF                    ((uint32_t)0x00010000)
#define SDIO_INT_RXFIFOF                    ((uint32_t)0x00020000)
#define SDIO_INT_TXFIFOE                    ((uint32_t)0x00040000)
#define SDIO_INT_RXFIFOE                    ((uint32_t)0x00080000)
#define SDIO_INT_TXDTVAL                    ((uint32_t)0x00100000)
#define SDIO_INT_RXDTVAL                    ((uint32_t)0x00200000)
#define SDIO_INT_SDIOINT                    ((uint32_t)0x00400000)
#define SDIO_INT_ATAEND                     ((uint32_t)0x00800000)

/**
  * @}
  */

/** @defgroup SDIO_Response_Type
  * @{
  */
#define SDIO_RESPONSETYPE_NO                ((uint32_t)0x00000000)
#define SDIO_RESPONSETYPE_SHORT             ((uint32_t)0x00000040)
#define SDIO_RESPONSETYPE_LONG              ((uint32_t)0x000000C0)

/**
  * @}
  */

/** @defgroup SDIO_Wait_Interrupt_State
  * @{
  */
#define SDIO_WAITINTSTATE_NO                ((uint32_t)0x00000000)
#define SDIO_WAITINTSTATE_INT               ((uint32_t)0x00000100)
#define SDIO_WAITINTSTATE_PEND              ((uint32_t)0x00000200)

/**
  * @}
  */

/** @defgroup SDIO_CSM_State
  * @{
  */
#define SDIO_CSMSTATE_DISABLE               ((uint32_t)0x00000000)
#define SDIO_CSMSTATE_ENABLE                ((uint32_t)0x00000400)

/**
  * @}
  */

/** @defgroup SDIO_Response_Registers
  * @{
  */
#define SDIO_RESP1                          ((uint32_t)0x00000000)
#define SDIO_RESP2                          ((uint32_t)0x00000004)
#define SDIO_RESP3                          ((uint32_t)0x00000008)
#define SDIO_RESP4                          ((uint32_t)0x0000000C)

/**
  * @}
  */

/** @defgroup SDIO_Data_Block_Size
  * @{
  */
#define SDIO_DATABLOCKSIZE_1B               ((uint32_t)0x00000000)
#define SDIO_DATABLOCKSIZE_2B               ((uint32_t)0x00000010)
#define SDIO_DATABLOCKSIZE_4B               ((uint32_t)0x00000020)
#define SDIO_DATABLOCKSIZE_8B               ((uint32_t)0x00000030)
#define SDIO_DATABLOCKSIZE_16B              ((uint32_t)0x00000040)
#define SDIO_DATABLOCKSIZE_32B              ((uint32_t)0x00000050)
#define SDIO_DATABLOCKSIZE_64B              ((uint32_t)0x00000060)
#define SDIO_DATABLOCKSIZE_128B             ((uint32_t)0x00000070)
#define SDIO_DATABLOCKSIZE_256B             ((uint32_t)0x00000080)
#define SDIO_DATABLOCKSIZE_512B             ((uint32_t)0x00000090)
#define SDIO_DATABLOCKSIZE_1024B            ((uint32_t)0x000000A0)
#define SDIO_DATABLOCKSIZE_2048B            ((uint32_t)0x000000B0)
#define SDIO_DATABLOCKSIZE_4096B            ((uint32_t)0x000000C0)
#define SDIO_DATABLOCKSIZE_8192B            ((uint32_t)0x000000D0)
#define SDIO_DATABLOCKSIZE_16384B           ((uint32_t)0x000000E0)

/**
  * @}
  */

/** @defgroup SDIO_Transfer_Direction
  * @{
  */
#define SDIO_TRANSDIRECTION_TOCARD          ((uint32_t)0x00000000)
#define SDIO_TRANSDIRECTION_TOSDIO          ((uint32_t)0x00000002)

/**
  * @}
  */

/** @defgroup SDIO_Transfer_Mode
  * @{
  */
#define SDIO_TRANSMODE_BLOCK                ((uint32_t)0x00000000)
#define SDIO_TRANSMODE_STREAM               ((uint32_t)0x00000004)

/**
  * @}
  */

/** @defgroup SDIO_DSM_State
  * @{
  */
#define SDIO_DSMSTATE_DISABLE               ((uint32_t)0x00000000)
#define SDIO_DSMSTATE_ENABLE                ((uint32_t)0x00000001)

/**
  * @}
  */

/** @defgroup SDIO_Flag
  * @{
  */
#define SDIO_FLAG_CCRCFAIL                  ((uint32_t)0x00000001)
#define SDIO_FLAG_DTCRCFAIL                 ((uint32_t)0x00000002)
#define SDIO_FLAG_CMDTMOUT                  ((uint32_t)0x00000004)
#define SDIO_FLAG_DTTMOUT                   ((uint32_t)0x00000008)
#define SDIO_FLAG_TXURE                     ((uint32_t)0x00000010)
#define SDIO_FLAG_RXORE                     ((uint32_t)0x00000020)
#define SDIO_FLAG_CMDREND                   ((uint32_t)0x00000040)
#define SDIO_FLAG_CMDSENT                   ((uint32_t)0x00000080)
#define SDIO_FLAG_DTEND                     ((uint32_t)0x00000100)
#define SDIO_FLAG_STBITE                    ((uint32_t)0x00000200)
#define SDIO_FLAG_DTBLKEND                  ((uint32_t)0x00000400)
#define SDIO_FLAG_CMDRUN                    ((uint32_t)0x00000800)
#define SDIO_FLAG_TXRUN                     ((uint32_t)0x00001000)
#define SDIO_FLAG_RXRUN                     ((uint32_t)0x00002000)
#define SDIO_FLAG_TXFIFOHE                  ((uint32_t)0x00004000)
#define SDIO_FLAG_RXFIFOHF                  ((uint32_t)0x00008000)
#define SDIO_FLAG_TXFIFOF                   ((uint32_t)0x00010000)
#define SDIO_FLAG_RXFIFOF                   ((uint32_t)0x00020000)
#define SDIO_FLAG_TXFIFOE                   ((uint32_t)0x00040000)
#define SDIO_FLAG_RXFIFOE                   ((uint32_t)0x00080000)
#define SDIO_FLAG_TXDTVAL                   ((uint32_t)0x00100000)
#define SDIO_FLAG_RXDTVAL                   ((uint32_t)0x00200000)
#define SDIO_FLAG_SDIOINT                   ((uint32_t)0x00400000)
#define SDIO_FLAG_ATAEND                    ((uint32_t)0x00800000)

/**
  * @}
  */

/** @defgroup SDIO_Read_Wait_Mode
  * @{
  */
#define SDIO_READWAITMODE_CLK               ((uint32_t)0x00000001)
#define SDIO_READWAITMODE_DAT2              ((uint32_t)0x00000000)

/**
  * @}
  */

/**
  * @}
  */


/** @defgroup SDIO_Exported_Functions
  * @{
  */
void SDIO_DeInit(void);
void SDIO_Init(SDIO_InitPara *SDIO_InitParaStruct);
void SDIO_ParaInit(SDIO_InitPara *SDIO_InitParaStruct);
void SDIO_Clock_Enable(TypeState NewState);
void SDIO_SetPWRState(uint32_t SDIO_PWRState);
uint32_t SDIO_GetPWRState(void);
void SDIO_INTConfig(uint32_t SDIO_INT, TypeState NewState);
void SDIO_DMA_Enable(TypeState NewState);
void SDIO_SendCMD(SDIO_CmdInitPara *SDIO_CmdInitParaStruct);
void SDIO_CMDParaInit(SDIO_CmdInitPara  *SDIO_CmdInitParaStruct);
uint8_t SDIO_GetCMDResponse(void);
uint32_t SDIO_GetResponse(uint32_t SDIO_RESP);
void SDIO_DataConfig(SDIO_DataInitPara *SDIO_DataInitParaStruct);
void SDIO_DataParaInit(SDIO_DataInitPara *SDIO_DataInitParaStruct);
uint32_t SDIO_GetDataCount(void);
uint32_t SDIO_ReadData(void);
void SDIO_WriteData(uint32_t Data);
uint32_t SDIO_GetFIFOCount(void);
void SDIO_StartSDIOReadWait(TypeState NewState);
void SDIO_StopSDIOReadWait(TypeState NewState);
void SDIO_SetSDIOReadWaitMode(uint32_t SDIO_ReadWaitMode);
void SDIO_SetSDIOOperation(TypeState NewState);
void SDIO_SendSDIOSuspend_Enable(TypeState NewState);
void SDIO_CMDCompletion_Enable(TypeState NewState);
void SDIO_CEATAInt_Enable(TypeState NewState);
void SDIO_SendCEATA_Enable(TypeState NewState);

TypeState SDIO_GetBitState(uint32_t SDIO_FLAG);
void SDIO_ClearBitState(uint32_t SDIO_FLAG);
TypeState SDIO_GetIntBitState(uint32_t SDIO_INT);
void SDIO_ClearIntBitState(uint32_t SDIO_INT);

#ifdef __cplusplus
}
#endif

#endif /* __GD32F10X_SDIO_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
