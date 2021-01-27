/**
 **************************************************************************
 * File Name    : at32f4xx_sdio.h
 * Description  : at32f4xx SDIO header file
 * Date         : 2018-10-08
 * Version      : V1.0.5
 **************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F4xx_SDIO_H
#define __AT32F4xx_SDIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup SDIO
  * @{
  */

/** @defgroup SDIO_Exported_Types
  * @{
  */

typedef struct
{
    uint32_t SDIO_ClkEdge;                  /*!< Specifies the clock transition on which the bit capture is made.
                                                 This parameter can be a value of @ref SDIO_Clock_Edge */
                                            
    uint32_t SDIO_ClkBypass;                /*!< Specifies whether the SDIO Clock divider bypass is
                                                 enabled or disabled.
                                                 This parameter can be a value of @ref SDIO_Clock_Bypass */
                                            
    uint32_t SDIO_ClkPowerSave;             /*!< Specifies whether SDIO Clock output is enabled or
                                                 disabled when the bus is idle.
                                                 This parameter can be a value of @ref SDIO_Clock_Power_Save */
                                            
    uint32_t SDIO_BusWidth;                 /*!< Specifies the SDIO bus width.
                                                 This parameter can be a value of @ref SDIO_Bus_Wide */
                                            
    uint32_t SDIO_FlowCtrl;                 /*!< Specifies whether the SDIO hardware flow control is enabled or disabled.
                                                 This parameter can be a value of @ref SDIO_Hardware_Flow_Control */
                                            
    uint16_t SDIO_ClkPsc;                    /*!< Specifies the clock frequency of the SDIO controller.
                                                 This parameter can be a value between 0x00 and 0x3FF. */

} SDIO_InitType;

typedef struct
{
    uint32_t SDIO_Argu;                     /*!< Specifies the SDIO command argument which is sent
                                                 to a card as part of a command message. If a command
                                                 contains an argument, it must be loaded into this register
                                                 before writing the command to the command register */
                                            
    uint32_t SDIO_CmdIdx;                   /*!< Specifies the SDIO command index. It must be lower than 0x40. */
                                            
    uint32_t SDIO_Resp;                     /*!< Specifies the SDIO response type.
                                                 This parameter can be a value of @ref SDIO_Response_Type */
                                            
    uint32_t SDIO_Wait;                     /*!< Specifies whether SDIO wait-for-interrupt request is enabled or disabled.
                                                 This parameter can be a value of @ref SDIO_Wait_Interrupt_State */
                                            
    uint32_t SDIO_CPSM;                     /*!< Specifies whether SDIO Command path state machine (CPSM)
                                                 is enabled or disabled.
                                                 This parameter can be a value of @ref SDIO_CPSM_State */
} SDIO_CmdInitType;

typedef struct
{
    uint32_t SDIO_DataTimeOut;              /*!< Specifies the data timeout period in card bus clock periods. */
                                            
    uint32_t SDIO_DataLen;                  /*!< Specifies the number of data bytes to be transferred. */
                                            
    uint32_t SDIO_DataBlkSize;              /*!< Specifies the data block size for block transfer.
                                               This parameter can be a value of @ref SDIO_Data_Block_Size */
                                            
    uint32_t SDIO_TransferDir;              /*!< Specifies the data transfer direction, whether the transfer
                                               is a read or write.
                                               This parameter can be a value of @ref SDIO_Transfer_Direction */
                                            
    uint32_t SDIO_TransferMode;             /*!< Specifies whether data transfer is in stream or block mode.
                                               This parameter can be a value of @ref SDIO_Transfer_Type */
                                            
    uint32_t SDIO_DPSM;                     /*!< Specifies whether SDIO Data path state machine (DPSM)
                                               is enabled or disabled.
                                               This parameter can be a value of @ref SDIO_DPSM_State */
} SDIO_DataInitType;

/**
  * @}
  */

/** @defgroup SDIO_Exported_Constants
  * @{
  */

#if defined (AT32F413xx) || defined (AT32F415xx)
#define IS_SDIO_ALL_PERIPH(PERIPH)          ((PERIPH) == SDIO)
#elif defined (AT32F403xx) || defined (AT32F403Axx) || \
      defined (AT32F407xx)
#define IS_SDIO_ALL_PERIPH(PERIPH)          (((PERIPH) == SDIO1) || \
                                             ((PERIPH) == SDIO2))
#endif
/** @defgroup SDIO_Clock_Edge
  * @{
  */

#define SDIO_ClkEdge_Rising                 ((uint32_t)0x00000000)
#define SDIO_ClkEdge_Falling                ((uint32_t)0x00002000)
#define IS_SDIO_CLK_EDGE(EDGE)              (((EDGE) == SDIO_ClkEdge_Rising) || \
                                             ((EDGE) == SDIO_ClkEdge_Falling))
/**
  * @}
  */

/** @defgroup SDIO_Clock_Bypass
  * @{
  */

#define SDIO_ClkBypass_Disable              ((uint32_t)0x00000000)
#define SDIO_ClkBypass_Enable               ((uint32_t)0x00000400)
#define IS_SDIO_CLK_BYPASS(BYPASS)          (((BYPASS) == SDIO_ClkBypass_Disable) || \
                                             ((BYPASS) == SDIO_ClkBypass_Enable))
/**
  * @}
  */

/** @defgroup SDIO_Clock_Power_Save
  * @{
  */

#define SDIO_ClkPowerSave_Disable           ((uint32_t)0x00000000)
#define SDIO_ClkPowerSave_Enable            ((uint32_t)0x00000200)
#define IS_SDIO_CLK_POWER_SAVE(SAVE)        (((SAVE) == SDIO_ClkPowerSave_Disable) || \
                                             ((SAVE) == SDIO_ClkPowerSave_Enable))
/**
  * @}
  */

/** @defgroup SDIO_Bus_Wide
  * @{
  */

#define SDIO_BusWidth_1b                    ((uint32_t)0x00000000)
#define SDIO_BusWidth_4b                    ((uint32_t)0x00000800)
#define SDIO_BusWidth_8b                    ((uint32_t)0x00001000)
#define IS_SDIO_BUS_WIDTH(WIDTH)            (((WIDTH) == SDIO_BusWidth_1b) || ((WIDTH) == SDIO_BusWidth_4b) || \
                                             ((WIDTH) == SDIO_BusWidth_8b))

/**
  * @}
  */

/** @defgroup SDIO_Hardware_Flow_Control
  * @{
  */

#define SDIO_FlowCtrl_Disable               ((uint32_t)0x00000000)
#define SDIO_FlowCtrl_Enable                ((uint32_t)0x00004000)
#define IS_SDIO_FLOW_CTRL(CTRL)             (((CTRL) == SDIO_FlowCtrl_Disable) || \
                                             ((CTRL) == SDIO_FlowCtrl_Enable))
/**
  * @}
  */

/** @defgroup SDIO_Power_State
  * @{
  */

#define SDIO_PowerSave_OFF                  ((uint32_t)0x00000000)
#define SDIO_PowerSave_ON                   ((uint32_t)0x00000003)
#define IS_SDIO_POWER_SAVE(SAVE)            (((SAVE) == SDIO_PowerSave_OFF) || ((SAVE) == SDIO_PowerSave_ON))
/**
  * @}
  */


/** @defgroup SDIO_Interrupt_sources
  * @{
  */

#define SDIO_INT_CMDFAIL                    ((uint32_t)0x00000001)
#define SDIO_INT_DTFAIL                     ((uint32_t)0x00000002)
#define SDIO_INT_CMDTIMEOUT                 ((uint32_t)0x00000004)
#define SDIO_INT_DTTIMEOUT                  ((uint32_t)0x00000008)
#define SDIO_INT_TXERRU                     ((uint32_t)0x00000010)
#define SDIO_INT_RXERRO                     ((uint32_t)0x00000020)
#define SDIO_INT_CMDRSPCMPL                 ((uint32_t)0x00000040)
#define SDIO_INT_CMDCMPL                    ((uint32_t)0x00000080)
#define SDIO_INT_DTCMPL                     ((uint32_t)0x00000100)
#define SDIO_INT_SBITERR                    ((uint32_t)0x00000200)
#define SDIO_INT_DTBLKCMPL                  ((uint32_t)0x00000400)
#define SDIO_INT_DOCMD                      ((uint32_t)0x00000800)
#define SDIO_INT_DOTX                       ((uint32_t)0x00001000)
#define SDIO_INT_DORX                       ((uint32_t)0x00002000)
#define SDIO_INT_TXBUF_H                    ((uint32_t)0x00004000)
#define SDIO_INT_RXBUF_H                    ((uint32_t)0x00008000)
#define SDIO_INT_TXBUF_F                    ((uint32_t)0x00010000)
#define SDIO_INT_RXBUF_F                    ((uint32_t)0x00020000)
#define SDIO_INT_TXBUF_E                    ((uint32_t)0x00040000)
#define SDIO_INT_RXBUF_E                    ((uint32_t)0x00080000)
#define SDIO_INT_TXBUF                      ((uint32_t)0x00100000)
#define SDIO_INT_RXBUF                      ((uint32_t)0x00200000)
#define SDIO_INT_SDIOIF                     ((uint32_t)0x00400000)
#define SDIO_INT_ATACMPL                    ((uint32_t)0x00800000)
#define IS_SDIO_INT(INT)                    ((((INT) & (uint32_t)0xFF000000) == 0x00) && ((INT) != (uint32_t)0x00))
/**
  * @}
  */

/** @defgroup SDIO_Command_Index
  * @{
  */

#define IS_SDIO_CMD_IDX(IDX)                ((IDX) < 0x40)
/**
  * @}
  */

/** @defgroup SDIO_Response_Type
  * @{
  */

#define SDIO_Rsp_No                         ((uint32_t)0x00000000)
#define SDIO_Rsp_Short                      ((uint32_t)0x00000040)
#define SDIO_Rsp_Long                       ((uint32_t)0x000000C0)
#define IS_SDIO_RSP_TYPE(TYPE)              (((TYPE) == SDIO_Rsp_No) || \
                                             ((TYPE) == SDIO_Rsp_Short) || \
                                             ((TYPE) == SDIO_Rsp_Long))
/**
  * @}
  */

/** @defgroup SDIO_Wait_Interrupt_State
  * @{
  */

#define SDIO_Wait_No                        ((uint32_t)0x00000000) /*!< SDIO No Wait, TimeOut is enabled */
#define SDIO_Wait_INT                       ((uint32_t)0x00000100) /*!< SDIO Wait Interrupt Request */
#define SDIO_Wait_Pend                      ((uint32_t)0x00000200) /*!< SDIO Wait End of transfer */
#define IS_SDIO_WAIT(WAIT)                  (((WAIT) == SDIO_Wait_No) || ((WAIT) == SDIO_Wait_INT) || \
                                             ((WAIT) == SDIO_Wait_Pend))
/**
  * @}
  */

/** @defgroup SDIO_CPSM_State
  * @{
  */

#define SDIO_CPSM_Disable                   ((uint32_t)0x00000000)
#define SDIO_CPSM_Enable                    ((uint32_t)0x00000400)
#define IS_SDIO_CPSM(CPSM)                  (((CPSM) == SDIO_CPSM_Enable) || ((CPSM) == SDIO_CPSM_Disable))
/**
  * @}
  */

/** @defgroup SDIO_Response_Registers
  * @{
  */

#define SDIO_RSP1                           ((uint32_t)0x00000000)
#define SDIO_RSP2                           ((uint32_t)0x00000004)
#define SDIO_RSP3                           ((uint32_t)0x00000008)
#define SDIO_RSP4                           ((uint32_t)0x0000000C)
#define IS_SDIO_RSP(RSP)                    (((RSP) == SDIO_RSP1) || ((RSP) == SDIO_RSP2) || \
                                             ((RSP) == SDIO_RSP3) || ((RSP) == SDIO_RSP4))
/**
  * @}
  */

/** @defgroup SDIO_Data_Length
  * @{
  */

#define IS_SDIO_DATA_LEN(LEN)               ((LEN) <= 0x01FFFFFF)
/**
  * @}
  */

/** @defgroup SDIO_Data_Block_Size
  * @{
  */

#define SDIO_DataBlkSize_1b                 ((uint32_t)0x00000000)
#define SDIO_DataBlkSize_2b                 ((uint32_t)0x00000010)
#define SDIO_DataBlkSize_4b                 ((uint32_t)0x00000020)
#define SDIO_DataBlkSize_8b                 ((uint32_t)0x00000030)
#define SDIO_DataBlkSize_16b                ((uint32_t)0x00000040)
#define SDIO_DataBlkSize_32b                ((uint32_t)0x00000050)
#define SDIO_DataBlkSize_64b                ((uint32_t)0x00000060)
#define SDIO_DataBlkSize_128b               ((uint32_t)0x00000070)
#define SDIO_DataBlkSize_256b               ((uint32_t)0x00000080)
#define SDIO_DataBlkSize_512b               ((uint32_t)0x00000090)
#define SDIO_DataBlkSize_1024b              ((uint32_t)0x000000A0)
#define SDIO_DataBlkSize_2048b              ((uint32_t)0x000000B0)
#define SDIO_DataBlkSize_4096b              ((uint32_t)0x000000C0)
#define SDIO_DataBlkSize_8192b              ((uint32_t)0x000000D0)
#define SDIO_DataBlkSize_16384b             ((uint32_t)0x000000E0)
#define IS_SDIO_BLK_SIZE(SIZE)              (((SIZE) == SDIO_DataBlkSize_1b)    || \
                                             ((SIZE) == SDIO_DataBlkSize_2b)    || \
                                             ((SIZE) == SDIO_DataBlkSize_4b)    || \
                                             ((SIZE) == SDIO_DataBlkSize_8b)    || \
                                             ((SIZE) == SDIO_DataBlkSize_16b)   || \
                                             ((SIZE) == SDIO_DataBlkSize_32b)   || \
                                             ((SIZE) == SDIO_DataBlkSize_64b)   || \
                                             ((SIZE) == SDIO_DataBlkSize_128b)  || \
                                             ((SIZE) == SDIO_DataBlkSize_256b)  || \
                                             ((SIZE) == SDIO_DataBlkSize_512b)  || \
                                             ((SIZE) == SDIO_DataBlkSize_1024b) || \
                                             ((SIZE) == SDIO_DataBlkSize_2048b) || \
                                             ((SIZE) == SDIO_DataBlkSize_4096b) || \
                                             ((SIZE) == SDIO_DataBlkSize_8192b) || \
                                             ((SIZE) == SDIO_DataBlkSize_16384b))
/**
  * @}
  */

/** @defgroup SDIO_Transfer_Direction
  * @{
  */

#define SDIO_TransferDir_ToCard             ((uint32_t)0x00000000)
#define SDIO_TransferDir_ToSDIO             ((uint32_t)0x00000002)
#define IS_SDIO_TRANSFER_DIR(DIR)           (((DIR) == SDIO_TransferDir_ToCard) || \
                                             ((DIR) == SDIO_TransferDir_ToSDIO))
/**
  * @}
  */

/** @defgroup SDIO_Transfer_Type
  * @{
  */

#define SDIO_TransferMode_Block             ((uint32_t)0x00000000)
#define SDIO_TransferMode_Stream            ((uint32_t)0x00000004)
#define IS_SDIO_TRANSFER_MODE(MODE)         (((MODE) == SDIO_TransferMode_Stream) || \
                                             ((MODE) == SDIO_TransferMode_Block))
/**
  * @}
  */

/** @defgroup SDIO_DPSM_State
  * @{
  */

#define SDIO_DPSM_Disable                   ((uint32_t)0x00000000)
#define SDIO_DPSM_Enable                    ((uint32_t)0x00000001)
#define IS_SDIO_DPSM(DPSM)                  (((DPSM) == SDIO_DPSM_Enable) || ((DPSM) == SDIO_DPSM_Disable))
/**
  * @}
  */

/** @defgroup SDIO_Flags
  * @{
  */

#define SDIO_FLG_CMDFAIL                    ((uint32_t)0x00000001)
#define SDIO_FLG_DTFAIL                     ((uint32_t)0x00000002)
#define SDIO_FLG_CMDTIMEOUT                 ((uint32_t)0x00000004)
#define SDIO_FLG_DTTIMEOUT                  ((uint32_t)0x00000008)
#define SDIO_FLG_TXERRU                     ((uint32_t)0x00000010)
#define SDIO_FLG_RXERRO                     ((uint32_t)0x00000020)
#define SDIO_FLG_CMDRSPCMPL                 ((uint32_t)0x00000040)
#define SDIO_FLG_CMDCMPL                    ((uint32_t)0x00000080)
#define SDIO_FLG_DTCMPL                     ((uint32_t)0x00000100)
#define SDIO_FLG_SBITERR                    ((uint32_t)0x00000200)
#define SDIO_FLG_DTBLKCMPL                  ((uint32_t)0x00000400)
#define SDIO_FLG_DOCMD                      ((uint32_t)0x00000800)
#define SDIO_FLG_DOTX                       ((uint32_t)0x00001000)
#define SDIO_FLG_DORX                       ((uint32_t)0x00002000)
#define SDIO_FLG_TXBUF_H                    ((uint32_t)0x00004000)
#define SDIO_FLG_RXBUF_H                    ((uint32_t)0x00008000)
#define SDIO_FLG_TXBUF_F                    ((uint32_t)0x00010000)
#define SDIO_FLG_RXBUF_F                    ((uint32_t)0x00020000)
#define SDIO_FLG_TXBUF_E                    ((uint32_t)0x00040000)
#define SDIO_FLG_RXBUF_E                    ((uint32_t)0x00080000)
#define SDIO_FLG_TXBUF                      ((uint32_t)0x00100000)
#define SDIO_FLG_RXBUF                      ((uint32_t)0x00200000)
#define SDIO_FLG_SDIOIF                     ((uint32_t)0x00400000)
#define SDIO_FLG_ATACMPL                    ((uint32_t)0x00800000)
#define IS_SDIO_FLG(FLG)                    (((FLG)  == SDIO_FLG_CMDFAIL)    || \
                                             ((FLG)  == SDIO_FLG_DTFAIL)     || \
                                             ((FLG)  == SDIO_FLG_CMDTIMEOUT) || \
                                             ((FLG)  == SDIO_FLG_DTTIMEOUT)  || \
                                             ((FLG)  == SDIO_FLG_TXERRU)     || \
                                             ((FLG)  == SDIO_FLG_RXERRO)     || \
                                             ((FLG)  == SDIO_FLG_CMDRSPCMPL) || \
                                             ((FLG)  == SDIO_FLG_CMDCMPL)    || \
                                             ((FLG)  == SDIO_FLG_DTCMPL)     || \
                                             ((FLG)  == SDIO_FLG_SBITERR)    || \
                                             ((FLG)  == SDIO_FLG_DTBLKCMPL)  || \
                                             ((FLG)  == SDIO_FLG_DOCMD)      || \
                                             ((FLG)  == SDIO_FLG_DOTX)       || \
                                             ((FLG)  == SDIO_FLG_DORX)       || \
                                             ((FLG)  == SDIO_FLG_TXBUF_H)    || \
                                             ((FLG)  == SDIO_FLG_RXBUF_H)    || \
                                             ((FLG)  == SDIO_FLG_TXBUF_F)    || \
                                             ((FLG)  == SDIO_FLG_RXBUF_F)    || \
                                             ((FLG)  == SDIO_FLG_TXBUF_E)    || \
                                             ((FLG)  == SDIO_FLG_RXBUF_E)    || \
                                             ((FLG)  == SDIO_FLG_TXBUF)      || \
                                             ((FLG)  == SDIO_FLG_RXBUF)      || \
                                             ((FLG)  == SDIO_FLG_SDIOIF)     || \
                                             ((FLG)  == SDIO_FLG_ATACMPL))

#define IS_SDIO_CLEAR_FLG(FLG)              ((((FLG) & (uint32_t)0xFF3FF800) == 0x00) && ((FLG) != (uint32_t)0x00))

#define IS_SDIO_GET_INT(INT)                (((INT)  == SDIO_INT_CMDFAIL)    || \
                                             ((INT)  == SDIO_INT_DTFAIL)     || \
                                             ((INT)  == SDIO_INT_CMDTIMEOUT) || \
                                             ((INT)  == SDIO_INT_DTTIMEOUT)  || \
                                             ((INT)  == SDIO_INT_TXERRU)     || \
                                             ((INT)  == SDIO_INT_RXERRO)     || \
                                             ((INT)  == SDIO_INT_CMDRSPCMPL) || \
                                             ((INT)  == SDIO_INT_CMDCMPL)    || \
                                             ((INT)  == SDIO_INT_DTCMPL)     || \
                                             ((INT)  == SDIO_INT_SBITERR)    || \
                                             ((INT)  == SDIO_INT_DTBLKCMPL)  || \
                                             ((INT)  == SDIO_INT_DOCMD)      || \
                                             ((INT)  == SDIO_INT_DOTX)       || \
                                             ((INT)  == SDIO_INT_DORX)       || \
                                             ((INT)  == SDIO_INT_TXBUF_H)    || \
                                             ((INT)  == SDIO_INT_RXBUF_H)    || \
                                             ((INT)  == SDIO_INT_TXBUF_F)    || \
                                             ((INT)  == SDIO_INT_RXBUF_F)    || \
                                             ((INT)  == SDIO_INT_TXBUF_E)    || \
                                             ((INT)  == SDIO_INT_RXBUF_E)    || \
                                             ((INT)  == SDIO_INT_TXBUF)      || \
                                             ((INT)  == SDIO_INT_RXBUF)      || \
                                             ((INT)  == SDIO_INT_SDIOIF)     || \
                                             ((INT)  == SDIO_INT_ATACMPL))

#define IS_SDIO_CLEAR_INT(INT)              ((((INT) & (uint32_t)0xFF3FF800) == 0x00) && ((INT) != (uint32_t)0x00))

/**
  * @}
  */

/** @defgroup SDIO_Read_Wait_Mode
  * @{
  */

#define SDIO_ReadWaitMode_CLK               ((uint32_t)0x00000001)
#define SDIO_ReadWaitMode_DATA2             ((uint32_t)0x00000000)
#define IS_SDIO_READWAIT_MODE(MODE)         (((MODE) == SDIO_ReadWaitMode_CLK) || \
                                             ((MODE) == SDIO_ReadWaitMode_DATA2))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup SDIO_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup SDIO_Exported_Functions
  * @{
  */

void SDIO_Reset(SDIO_Type * SDIOx);
void SDIO_Init(SDIO_Type * SDIOx, SDIO_InitType* SDIO_InitStruct);
void SDIO_StructInit(SDIO_InitType* SDIO_InitStruct);
void SDIO_ClockCmd(SDIO_Type * SDIOx, FunctionalState NewState);
void SDIO_SetPowerSaveState(SDIO_Type * SDIOx, uint32_t SDIO_PowerState);
uint32_t SDIO_GetPowerSaveState(SDIO_Type * SDIOx);
void SDIO_INTConfig(SDIO_Type * SDIOx, uint32_t SDIO_INT, FunctionalState NewState);
void SDIO_DMACmd(SDIO_Type * SDIOx, FunctionalState NewState);
void SDIO_SendCommand(SDIO_Type * SDIOx, SDIO_CmdInitType *SDIO_CmdInitStruct);
void SDIO_CmdStructInit(SDIO_CmdInitType* SDIO_CmdInitStruct);
uint8_t SDIO_GetCommandResponse(SDIO_Type * SDIOx);
uint32_t SDIO_GetResponse(SDIO_Type * SDIOx, uint32_t SDIO_RESP);
void SDIO_DataConfig(SDIO_Type * SDIOx, SDIO_DataInitType* SDIO_DataInitStruct);
void SDIO_DataStructInit(SDIO_DataInitType* SDIO_DataInitStruct);
uint32_t SDIO_GetDataCounter(SDIO_Type * SDIOx);
uint32_t SDIO_ReadData(SDIO_Type * SDIOx);
void SDIO_WriteData(SDIO_Type * SDIOx, uint32_t Data);
uint32_t SDIO_GetBUFCount(SDIO_Type * SDIOx);
void SDIO_StartSDIOReadWait(SDIO_Type * SDIOx, FunctionalState NewState);
void SDIO_StopSDIOReadWait(SDIO_Type * SDIOx, FunctionalState NewState);
void SDIO_SetSDIOReadWaitMode(SDIO_Type * SDIOx, uint32_t SDIO_ReadWaitMode);
void SDIO_SetSDIOOperation(SDIO_Type * SDIOx, FunctionalState NewState);
void SDIO_SendSDIOSuspendCmd(SDIO_Type * SDIOx, FunctionalState NewState);
void SDIO_CommandCompletionCmd(SDIO_Type * SDIOx, FunctionalState NewState);
void SDIO_ATAINTCmd(SDIO_Type * SDIOx, FunctionalState NewState);
void SDIO_SendATACmd(SDIO_Type * SDIOx, FunctionalState NewState);
FlagStatus SDIO_GetFlagStatus(SDIO_Type * SDIOx, uint32_t SDIO_FLAG);
void SDIO_ClearFlag(SDIO_Type * SDIOx, uint32_t SDIO_FLAG);
ITStatus SDIO_GetINTStatus(SDIO_Type * SDIOx, uint32_t SDIO_INT);
void SDIO_ClearINTPendingBit(SDIO_Type * SDIOx, uint32_t SDIO_INT);

#ifdef __cplusplus
}
#endif

#endif /* __AT32F4xx_SDIO_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


